/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <ajtcl/alljoyn.h>

#include <ajtcl/services/Common/AllJoynLogo.h>
#include <ajtcl/services/ServicesHandlers.h>
#include <ajtcl/aj_link_timeout.h>

#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_System.h>
#include <ajtcl/cdm/utils/PropertyStoreOEMProvisioning.h>


#define ROUTING_NODE_NAME "org.alljoyn.BusNode"
#define AJ_ABOUT_SERVICE_PORT 900
#define MAX_INIT_ATTEMPTS 1
#define FAILED_INIT_REATTEMPT_TIME 0

#define CDMAPP_BUS_LINK_TIMEOUT        60
#define CDMAPP_CONNECT_TIMEOUT         (1000 * 10)      // Override AJ_CONNECT_TIMEOUT to wait longer for a successful connection to a Routing Node
#define CDMAPP_CONNECT_PAUSE           (1000 * 2)       // Override AJ_CONNECT_PAUSE to be more responsive
#define CDMAPP_PRE_DISCONNECT_PAUSE    (1000 * 2)       // A little pause to let things settle
#define CDMAPP_POST_DISCONNECT_PAUSE   (1000 * 2)       // A little pause to let things settle
#define CDMAPP_UNMARSHAL_TIMEOUT       (1000 * 1)       // Override AJ_UNMARSHAL_TIMEOUT to be more responsive


/**
 * Default AllJoyn application handlers.
 */
typedef enum {
    INIT_START = 0,
    INIT_SERVICES = INIT_START,
    INIT_SERVICES_PORT,
    INIT_ABOUT,
    INIT_CHECK_ANNOUNCE,
    INIT_FINISHED = INIT_CHECK_ANNOUNCE
} enum_init_state_t;

static enum_init_state_t currentServicesInitializationState = INIT_START;
static enum_init_state_t nextServicesInitializationState = INIT_START;
static uint8_t initAttempts = 0;

static uint16_t sessionPort = AJ_ABOUT_SERVICE_PORT;
static uint32_t unmarshalTimeout = CDMAPP_UNMARSHAL_TIMEOUT;
static uint8_t maxInitAttempts = MAX_INIT_ATTEMPTS;
static uint32_t failedInitReattemptTime = FAILED_INIT_REATTEMPT_TIME;

static AJ_Status DefaultAppUpdateHandler(AJ_BusAttachment* busAttachment)
{
    AJ_Status status = AJ_OK;

    if (AJ_GetUniqueName(busAttachment)) {
        if (currentServicesInitializationState == nextServicesInitializationState) {
            switch (currentServicesInitializationState) {
                case INIT_SERVICES:
                    status = AJSVC_ConnectedHandler(busAttachment);
                    if (status != AJ_OK) {
                        goto ErrorExit;
                    }
                    currentServicesInitializationState = nextServicesInitializationState = INIT_SERVICES_PORT;
                    break;
                case INIT_SERVICES_PORT:
                    status = AJ_BusBindSessionPort(busAttachment, sessionPort, NULL, 0);
                    if (status != AJ_OK) {
                        goto ErrorExit;
                    }
                    nextServicesInitializationState = INIT_ABOUT;
                    break;
                case INIT_ABOUT:
                    status = AJ_AboutInit(busAttachment, sessionPort);
                    if (status != AJ_OK) {
                        goto ErrorExit;
                    }
                    currentServicesInitializationState = nextServicesInitializationState = INIT_CHECK_ANNOUNCE;
                    break;
                case INIT_CHECK_ANNOUNCE:
                    status = AJ_AboutAnnounce(busAttachment);
                    if (status != AJ_OK) {
                        goto ErrorExit;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return status;

ErrorExit:
    AJ_ErrPrintf(("Application UpdateHandler returned an error: %s.\n", (AJ_StatusText(status))));
    if (status == AJ_ERR_RESOURCES) {
        initAttempts++;
        if (initAttempts > maxInitAttempts) {
            status = AJ_ERR_READ; // Force disconnect from Routing Node
        } else {
            AJ_ErrPrintf(("Application UpdateHandler init attempt %u of %u.\n", initAttempts, maxInitAttempts));

            if (failedInitReattemptTime > 0) {
                AJ_Sleep(failedInitReattemptTime);
            }
        }
    } else if (status == AJ_ERR_WRITE) {
        status = AJ_ERR_READ; // Force disconnect from Routing Node
    }

    return status;
}

static AJ_Status DefaultAppSessionAcceptedHandler(uint16_t port, uint32_t sessionId, const char* joiner)
{
    return AJ_OK;
}

static SessionAcceptedHandler sessionAcceptedHandler = DefaultAppSessionAcceptedHandler;

static AJSVC_ServiceStatus DefaultAppMessageProcessor(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* status)
{
    AJSVC_ServiceStatus serviceStatus = AJSVC_SERVICE_STATUS_HANDLED;

    if (msg->msgId == AJ_METHOD_ACCEPT_SESSION) {    // Process all incoming request to join a session and pass request for acceptance by all services
        uint16_t port;
        char* joiner;
        uint32_t sessionId = 0;

        *status = AJ_UnmarshalArgs(msg, "qus", &port, &sessionId, &joiner);
        if (*status != AJ_OK) {
            return serviceStatus;
        }

        uint8_t session_accepted = FALSE;
        session_accepted |= (port == sessionPort);
        session_accepted |= AJSVC_CheckSessionAccepted(port, sessionId, joiner);
        *status = AJ_BusReplyAcceptSession(msg, session_accepted);
        AJ_AlwaysPrintf(("%s session session_id=%u joiner=%s for port %u\n", (session_accepted ? "Accepted" : "Rejected"), sessionId, joiner, port));

        sessionAcceptedHandler(port, sessionId, joiner);
    } else {
        switch (currentServicesInitializationState) {
            case INIT_SERVICES_PORT:
                if (msg->msgId == AJ_REPLY_ID(AJ_METHOD_BIND_SESSION_PORT)) {
                    currentServicesInitializationState = nextServicesInitializationState;
                }
                break;
            default:
                serviceStatus = AJSVC_MessageProcessorAndDispatcher(busAttachment, msg, status);
                break;
        }
    }

    return serviceStatus;
}


static AppUpdateHandler appUpdateHandler = DefaultAppUpdateHandler;
static MessageProcessor messageProcessor = DefaultAppMessageProcessor;



void CDM_SetDefaultAboutIconParams(CDM_AboutIconParams *params)
{
    if (params != NULL) {
        params->mimeType = (const char*)AJ_LogoMimeType;
        params->content = AJ_LogoData;
        params->contentSize = AJ_LogoSize;
        params->url = AJ_LogoURL;
    }
}

void CDM_SetDefaultRoutingNodeParams(CDM_RoutingNodeParams *params)
{
    if (params != NULL) {
        params->name = ROUTING_NODE_NAME;
        params->connectTimeout = CDMAPP_CONNECT_TIMEOUT;
        params->connectPause = CDMAPP_CONNECT_PAUSE;
        params->preDisconnectPause = CDMAPP_PRE_DISCONNECT_PAUSE;
        params->postDisconnectPause = CDMAPP_POST_DISCONNECT_PAUSE;
    }
}

AJ_Status CDM_SystemInit(CDM_AboutIconParams *iconParams)
{
    AJ_Status status;
    AJ_Initialize();
    AJ_AboutSetIcon(iconParams->content, iconParams->contentSize, iconParams->mimeType, iconParams->url);

    status = PropertyStore_Init();
    if (status != AJ_OK)
    {
        AJ_ErrPrintf(("PropertyStore_Init() failed: %s\n", (AJ_StatusText(status))));
        return status;
    }

    status = Cdm_Init();
    if (status != AJ_OK)
        AJ_ErrPrintf(("Cdm_Init() failed: %s\n", (AJ_StatusText(status))));

    return status;
}

AJ_Status CDM_SystemConnect(CDM_RoutingNodeParams *routingNodeParams, CDM_BusAttachment *busAttachment)
{
    AJ_Status status;

    if (routingNodeParams == NULL || busAttachment == NULL)
    {
        AJ_ErrPrintf(("Invalid Parameter for CDM_SystemConnect\n"));
        return AJ_ERR_FAILURE;
    }

    status = Cdm_Start();
    if (status != AJ_OK) {
        AJ_ErrPrintf(("Cdm_Start() failed: %s\n", (AJ_StatusText(status))));
        return status;
    }

    return AJSVC_RoutingNodeConnect(&busAttachment->bus,
                                    routingNodeParams->name,
                                    routingNodeParams->connectTimeout,
                                    routingNodeParams->connectPause,
                                    routingNodeParams->busLinkTimeout,
                                    &busAttachment->isConnected);
}

AJ_Status Cdm_MessageLoop(CDM_BusAttachment *busAttachment)
{
    AJ_Status status = AJ_OK;

    if (busAttachment == NULL || !busAttachment->isConnected)
        return AJ_ERR_FAILURE;

    while (status != AJ_ERR_READ && status != AJ_ERR_WRITE && status != AJ_ERR_RESTART && status != AJ_ERR_RESTART_APP)
    {
        status = appUpdateHandler(&busAttachment->bus);

        if (status == AJ_OK) {
            AJ_Message msg;
            status = AJ_UnmarshalMsg(&busAttachment->bus, &msg, unmarshalTimeout);
            bool isUnmarshalingSuccessful = (status==AJ_OK);

            if (status==AJ_ERR_TIMEOUT) {
                if (AJ_ERR_LINK_TIMEOUT==AJ_BusLinkStateProc(&busAttachment->bus)) {
                    status = AJ_ERR_READ;             // Something's not right. force disconnect
                }
            }

            if (isUnmarshalingSuccessful) {
                AJSVC_ServiceStatus serviceStatus = Cdm_MessageProcessor(&busAttachment->bus, &msg, &status);

                if (serviceStatus==AJSVC_SERVICE_STATUS_NOT_HANDLED) {
                    serviceStatus = messageProcessor(&busAttachment->bus, &msg, &status);
                }
                if (serviceStatus==AJSVC_SERVICE_STATUS_NOT_HANDLED) {
                    //Pass to the built-in bus message handlers
                    status = AJ_BusHandleBusMessage(&msg);
                }
                AJ_NotifyLinkActive();
            }

            //Unmarshaled messages must be closed to free resources
            AJ_CloseMsg(&msg);
        }
    }
    printf("%s\n", AJ_StatusText(status));
    return status;
}

void CDM_SystemStop(void)
{
    Cdm_Deinit();
}