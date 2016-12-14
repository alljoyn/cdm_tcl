/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <stdlib.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/aj_config.h>
#include <ajtcl/aj_link_timeout.h>
#include <ajtcl/aj_cert.h>
#include <ajtcl/services/ServicesHandlers.h>
#include <ajtcl/services/Common/AllJoynLogo.h>
#include <ajtcl/cdm/CdmControllee.h>
#include "PropertyStoreOEMProvisioning.h"
#include "ControlleeSampleUtil.h"

/**
 * Logger definition.
 */
#ifndef NDEBUG
#ifndef ER_DEBUG_CDMAPP
#define ER_DEBUG_CDMAPP 0
#endif
AJ_EXPORT uint8_t dbgCDMAPP = ER_DEBUG_CDMAPP;
#endif

/**
 * Interrupt / volatile flag definitions.
 */
volatile sig_atomic_t irqOccurred = false;
volatile bool cdmModelsInitialised = false;

/**
 * Timeout / pause values (in milliseconds).
 */
#define CDMAPP_BUS_LINK_TIMEOUT        60
#define CDMAPP_CONNECT_TIMEOUT         (1000 * 10)      // Override AJ_CONNECT_TIMEOUT to wait longer for a successful connection to a Routing Node
#define CDMAPP_CONNECT_PAUSE           (1000 * 2)       // Override AJ_CONNECT_PAUSE to be more responsive
#define CDMAPP_PRE_DISCONNECT_PAUSE    (1000 * 2)       // A little pause to let things settle
#define CDMAPP_POST_DISCONNECT_PAUSE   (1000 * 2)       // A little pause to let things settle
#define CDMAPP_UNMARSHAL_TIMEOUT       (1000 * 1)       // Override AJ_UNMARSHAL_TIMEOUT to be more responsive

/**
 * Application wide globals.
 */
#define ROUTING_NODE_NAME "org.alljoyn.BusNode"
#define AJ_ABOUT_SERVICE_PORT 900
#define MAX_INIT_ATTEMPTS 1
#define FAILED_INIT_REATTEMPT_TIME 0

static CDM_MainParams* cdmMainParams = NULL;
static uint8_t initAttempts = 0;

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

AJ_Status Cdm_DefaultAppConnectedHandler(AJ_BusAttachment* busAttachment)
{
    return AJ_OK;
}

AJ_Status Cdm_DefaultAppUpdateHandler(AJ_BusAttachment* busAttachment)
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
                status = AJ_BusBindSessionPort(busAttachment, cdmMainParams->sessionPort, NULL, 0);
                if (status != AJ_OK) {
                    goto ErrorExit;
                }
                nextServicesInitializationState = INIT_ABOUT;
                break;
            case INIT_ABOUT:
                status = AJ_AboutInit(busAttachment, cdmMainParams->sessionPort);
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
        if (initAttempts > cdmMainParams->maxInitAttempts) {
            status = AJ_ERR_READ; // Force disconnect from Routing Node
        } else {
            AJ_ErrPrintf(("Application UpdateHandler init attempt %u of %u.\n", initAttempts, cdmMainParams->maxInitAttempts));
            
            if (cdmMainParams->failedInitReattemptTime > 0) {
                AJ_Sleep(cdmMainParams->failedInitReattemptTime);
            }
        }
    } else if (status == AJ_ERR_WRITE) {
        status = AJ_ERR_READ; // Force disconnect from Routing Node
    }

    return status;
}

AJSVC_ServiceStatus Cdm_DefaultAppMessageProcessor(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* status)
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
        session_accepted |= (port == cdmMainParams->sessionPort);
        session_accepted |= AJSVC_CheckSessionAccepted(port, sessionId, joiner);
        *status = AJ_BusReplyAcceptSession(msg, session_accepted);
        AJ_AlwaysPrintf(("%s session session_id=%u joiner=%s for port %u\n", (session_accepted ? "Accepted" : "Rejected"), sessionId, joiner, port));

        cdmMainParams->AppSessionAcceptedHandler(port, sessionId, joiner);
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

AJ_Status Cdm_DefaultAppSessionAcceptedHandler(uint16_t port, uint32_t sessionId, const char* joiner)
{
    return AJ_OK;
}

AJ_Status Cdm_DefaultAppDisconnectedHandler(AJ_BusAttachment* busAttachment, uint8_t restart)
{
    if (restart) {
        AJ_BusUnbindSession(busAttachment, cdmMainParams->sessionPort);
    }

    AJ_AboutSetShouldAnnounce();
    currentServicesInitializationState = nextServicesInitializationState = INIT_START;
    initAttempts = 0;

    return AJSVC_DisconnectHandler(busAttachment);
}

/**
 * Default authentication listener callback.
 * - Security code based on code from ajtcl/samples/secure/SecureServiceECDHE.c.
 */
static const size_t NUM_SUITES = 4;
static const uint32_t suites[NUM_SUITES] = { AUTH_SUITE_ECDHE_ECDSA, AUTH_SUITE_ECDHE_SPEKE, AUTH_SUITE_ECDHE_PSK, AUTH_SUITE_ECDHE_NULL };
static const uint32_t keyexpiration = 0xFFFFFFFF;

static X509CertificateChain* chain = NULL;

static AJ_Status DefaultAuthListenerCallback(uint32_t authmechanism, uint32_t command, AJ_Credential* cred)
{
    AJ_Status status = AJ_ERR_INVALID;
    X509CertificateChain* node;

    AJ_AlwaysPrintf(("DefaultAuthListenerCallback authmechanism %08X command %d\n", authmechanism, command));

    switch (authmechanism) {
    case AUTH_SUITE_ECDHE_NULL:
        cred->expiration = cdmMainParams->securityParams.defaultCallbackParams.keyExpiration;
        status = AJ_OK;
        break;
    case AUTH_SUITE_ECDHE_SPEKE:
        switch (command) {
        case AJ_CRED_PASSWORD:
            cred->data = (uint8_t*)cdmMainParams->securityParams.defaultCallbackParams.spekePassword;
            cred->len = strlen(cdmMainParams->securityParams.defaultCallbackParams.spekePassword);
            cred->expiration = cdmMainParams->securityParams.defaultCallbackParams.keyExpiration;
            status = AJ_OK;
            break;
        }
        break;

    // The ECDHE_PSK auth mechanism is deprecated as of 16.04 and ECDHE_SPEKE should be used instead.
    case AUTH_SUITE_ECDHE_PSK:
        switch (command) {
        case AJ_CRED_PUB_KEY:
            cred->data = (uint8_t*) cdmMainParams->securityParams.defaultCallbackParams.pskPublicKey;
            cred->len = strlen(cdmMainParams->securityParams.defaultCallbackParams.pskPublicKey);
            cred->expiration = cdmMainParams->securityParams.defaultCallbackParams.keyExpiration;
            status = AJ_OK;
            break;
        case AJ_CRED_PRV_KEY:
            cred->data = (uint8_t*) cdmMainParams->securityParams.defaultCallbackParams.pskPrivateKey;
            cred->len = strlen(cdmMainParams->securityParams.defaultCallbackParams.pskPrivateKey);
            cred->expiration = cdmMainParams->securityParams.defaultCallbackParams.keyExpiration;
            status = AJ_OK;
            break;
        }
        break;
    case AUTH_SUITE_ECDHE_ECDSA:
        switch (command) {
        case AJ_CRED_PRV_KEY:
            AJ_ASSERT(sizeof (AJ_ECCPrivateKey) == cred->len);
            
            status = AJ_DecodePrivateKeyPEM((AJ_ECCPrivateKey*) cred->data, cdmMainParams->securityParams.defaultCallbackParams.ecdsaPEMPrivateKey);
            cred->expiration = cdmMainParams->securityParams.defaultCallbackParams.keyExpiration;
            break;
        case AJ_CRED_CERT_CHAIN:
            switch (cred->direction) {
            case AJ_CRED_REQUEST:
                // Free previous certificate chain
                AJ_X509FreeDecodedCertificateChain(chain);
                chain = AJ_X509DecodeCertificateChainPEM(cdmMainParams->securityParams.defaultCallbackParams.ecdsaPEMCertificate);
                if (NULL == chain) {
                    return AJ_ERR_INVALID;
                }
                cred->data = (uint8_t*) chain;
                cred->expiration = cdmMainParams->securityParams.defaultCallbackParams.keyExpiration;
                status = AJ_OK;
                break;
            case AJ_CRED_RESPONSE:
                node = (X509CertificateChain*) cred->data;
                status = AJ_X509VerifyChain(node, NULL, AJ_CERTIFICATE_IDN_X509);
                while (node) {
                    AJ_DumpBytes("CERTIFICATE", node->certificate.der.data, node->certificate.der.size);
                    node = node->next;
                }
                break;
            }
            break;
        }
        break;
    default:
        break;
    }
    return status;
}

/**
 * Default interrupt handler.
 */
static AJ_Status DefaultInterruptHandler()
{
    return AJ_OK;
}

/**
 * Default CDM handlers.
 */
static AJ_Status DefaultInitCdmInterfaces()
{
    return AJ_OK;
}

static AJ_Status DefaultInitCdmModels(AJ_BusAttachment* busAttachment)
{
    return AJ_OK;
}

/**
 * Initialise default CDM state.
 */
static AJ_Status CDM_MainParamsSetDefaults(CDM_MainParams* mainParams)
{
    AJ_Status status = AJ_OK;

    if (!mainParams) {
        return AJ_ERR_INVALID;
    }

    if (!mainParams->AppConnectedHandler) {
        mainParams->AppConnectedHandler = Cdm_DefaultAppConnectedHandler;
    }

    if (!mainParams->AppDisconnectedHandler) {
        mainParams->AppDisconnectedHandler = Cdm_DefaultAppDisconnectedHandler;
    }

    if (!mainParams->AppUpdateHandler) {
        mainParams->AppUpdateHandler = Cdm_DefaultAppUpdateHandler;
    }

    if (!mainParams->AppMessageProcessor) {
        mainParams->AppMessageProcessor = Cdm_DefaultAppMessageProcessor;
    }

    if (!mainParams->AppSessionAcceptedHandler) {
        mainParams->AppSessionAcceptedHandler = Cdm_DefaultAppSessionAcceptedHandler;
    }

    if (!mainParams->InterruptHandler) {
        mainParams->InterruptHandler = DefaultInterruptHandler;
    }

    if (!mainParams->InitCdmInterfaces) {
        mainParams->InitCdmInterfaces = DefaultInitCdmInterfaces;
    }

    if (!mainParams->InitCdmModels) {
        mainParams->InitCdmModels = DefaultInitCdmModels;
    }

    if (!mainParams->aboutIconParams.mimeType) {
        mainParams->aboutIconParams.mimeType = AJ_LogoMimeType;
    }

    if (!mainParams->aboutIconParams.content) {
        mainParams->aboutIconParams.content = AJ_LogoData;
    }

    if (mainParams->aboutIconParams.contentSize == 0) {
        mainParams->aboutIconParams.contentSize = AJ_LogoSize;
    }

    if (!mainParams->aboutIconParams.url) {
        mainParams->aboutIconParams.url = AJ_LogoURL;
    }

    if (!mainParams->routingNodeParams.name) {
        mainParams->routingNodeParams.name = ROUTING_NODE_NAME;
    }

    if (mainParams->routingNodeParams.busLinkTimeout == 0) {
        mainParams->routingNodeParams.busLinkTimeout = CDMAPP_BUS_LINK_TIMEOUT;
    }

    if (mainParams->routingNodeParams.connectTimeout == 0) {
        mainParams->routingNodeParams.connectTimeout = CDMAPP_CONNECT_TIMEOUT;
    }

    if (mainParams->routingNodeParams.connectPause == 0) {
        mainParams->routingNodeParams.connectPause = CDMAPP_CONNECT_PAUSE;
    }

    if (mainParams->routingNodeParams.preDisconnectPause == 0) {
        mainParams->routingNodeParams.preDisconnectPause = CDMAPP_PRE_DISCONNECT_PAUSE;
    }

    if (mainParams->routingNodeParams.postDisconnectPause == 0) {
        mainParams->routingNodeParams.postDisconnectPause = CDMAPP_POST_DISCONNECT_PAUSE;
    }

    if (!mainParams->securityParams.AuthListenerCallback ||
        !mainParams->securityParams.authSuites ||
        mainParams->securityParams.numAuthSuites == 0) {

        // Set the callback and auth suites to defaults if all three variables aren't specified.
        mainParams->securityParams.AuthListenerCallback = DefaultAuthListenerCallback;
        mainParams->securityParams.authSuites = suites;
        mainParams->securityParams.numAuthSuites = NUM_SUITES;

        // All default callback parameters MUST be provided if using the default auth listener callback.
        if (!mainParams->securityParams.defaultCallbackParams.pskPrivateKey ||
            !mainParams->securityParams.defaultCallbackParams.pskPublicKey ||
            !mainParams->securityParams.defaultCallbackParams.spekePassword ||
            !mainParams->securityParams.defaultCallbackParams.ecdsaPEMPrivateKey ||
            !mainParams->securityParams.defaultCallbackParams.ecdsaPEMCertificate) {
            
            status = AJ_ERR_INVALID;
        }
    }

    if (mainParams->securityParams.defaultCallbackParams.keyExpiration == 0) {
        mainParams->securityParams.defaultCallbackParams.keyExpiration = keyexpiration;
    }

    if (mainParams->sessionPort == 0) {
        mainParams->sessionPort = AJ_ABOUT_SERVICE_PORT;
    }

    if (mainParams->unmarshalTimeout == 0) {
        mainParams->unmarshalTimeout = CDMAPP_UNMARSHAL_TIMEOUT;
    }

    if (cdmMainParams->maxInitAttempts == 0) {
        cdmMainParams->maxInitAttempts = MAX_INIT_ATTEMPTS;
    }

    if (cdmMainParams->failedInitReattemptTime) {
        cdmMainParams->failedInitReattemptTime = FAILED_INIT_REATTEMPT_TIME;
    }

    return status;
}

/**
 * Controllee sample main program flow.
 */
static AJ_Status MainLoop(const CDM_MainParams* mainParams)
{
    AJ_Status status = AJ_OK;
    AJ_BusAttachment busAttachment;
    uint8_t isBusConnected = FALSE;
    cdmModelsInitialised = false;

    if (!mainParams) {
        return AJ_ERR_NULL;
    }

    while (TRUE) {
        status = AJ_OK;

        // Let the vendor handle interrupts.
        if (irqOccurred) {
            irqOccurred = false;
            status = mainParams->InterruptHandler(&busAttachment);
            if (status != AJ_OK) {
                break;
            }
        }

        if (!isBusConnected) {
            status = AJSVC_RoutingNodeConnect(&busAttachment, mainParams->routingNodeParams.name, mainParams->routingNodeParams.connectTimeout, mainParams->routingNodeParams.connectPause, mainParams->routingNodeParams.busLinkTimeout, &isBusConnected);
            if (!isBusConnected) { // Failed to connect to Routing Node?
                continue; // Retry establishing connection to Routing Node.
            }

            status = Cdm_EnableSecurity(&busAttachment, mainParams->securityParams.authSuites, mainParams->securityParams.numAuthSuites, mainParams->securityParams.AuthListenerCallback);
            if (status != AJ_OK) {
                AJSVC_RoutingNodeDisconnect(&busAttachment, 1, mainParams->routingNodeParams.preDisconnectPause, mainParams->routingNodeParams.postDisconnectPause, &isBusConnected);
                break;
            }

            status = mainParams->AppConnectedHandler(&busAttachment);
        }

        status = mainParams->AppUpdateHandler(&busAttachment);

        // Initialise CDM models inside the main loop to allow for delays from hardware and resets.
        if (!cdmModelsInitialised) {
            mainParams->InitCdmModels(&busAttachment);
            if (status == AJ_OK) {
                cdmModelsInitialised = true;
            }
        }

        // Main message processing.
        if (status == AJ_OK) {
            AJ_Message msg;
            status = AJ_UnmarshalMsg(&busAttachment, &msg, mainParams->unmarshalTimeout);
            uint8_t isUnmarshalingSuccessful = (status == AJ_OK);

            if (status == AJ_ERR_TIMEOUT) {
                if (AJ_ERR_LINK_TIMEOUT == AJ_BusLinkStateProc(&busAttachment)) {
                    status = AJ_ERR_READ;             // Something's not right. force disconnect
                }
            }

            if (isUnmarshalingSuccessful) {
                AJSVC_ServiceStatus serviceStatus = Cdm_MessageProcessor(&busAttachment, &msg, &status);

                if (serviceStatus == AJSVC_SERVICE_STATUS_NOT_HANDLED) {
                    serviceStatus = mainParams->AppMessageProcessor(&busAttachment, &msg, &status);
                }
                if (serviceStatus == AJSVC_SERVICE_STATUS_NOT_HANDLED) {
                    //Pass to the built-in bus message handlers
                    status = AJ_BusHandleBusMessage(&msg);
                }
                AJ_NotifyLinkActive();
            }

            //Unmarshaled messages must be closed to free resources
            AJ_CloseMsg(&msg);
        }

        if (status == AJ_ERR_READ || status == AJ_ERR_WRITE || status == AJ_ERR_RESTART || status == AJ_ERR_RESTART_APP) {
            if (isBusConnected) {
                uint8_t forcedDisconnnect = (status != AJ_ERR_READ);
                uint8_t rebootRequired = (status == AJ_ERR_RESTART_APP);
                mainParams->AppDisconnectedHandler(&busAttachment, forcedDisconnnect);
                AJSVC_RoutingNodeDisconnect(&busAttachment, forcedDisconnnect, mainParams->routingNodeParams.preDisconnectPause, mainParams->routingNodeParams.postDisconnectPause, &isBusConnected);
                if (rebootRequired) {
                    AJ_Reboot();
                }

                // Refresh Controllee device models.
                cdmModelsInitialised = false;
            }
        }
    }     // while (TRUE)

    return status;
}

int CDM_Main(const CDM_MainParams* mainParams)
{
    AJ_Status status = AJ_OK;

    cdmMainParams = malloc(sizeof(CDM_MainParams));
    if (!cdmMainParams) {
        status = AJ_ERR_NULL;
        AJ_ErrPrintf(("CDM_MainParams malloc failed: %s\n", (AJ_StatusText(status))));
        return (int)status;
    }
    memset(cdmMainParams, 0, sizeof(CDM_MainParams));

    // Get vendor-provided parameters and initialise all others to defaults.
    if (mainParams) {
        memcpy(cdmMainParams, mainParams, sizeof(CDM_MainParams));
    }

    status = CDM_MainParamsSetDefaults(cdmMainParams);
    if (status != AJ_OK) {
        AJ_ErrPrintf(("CDM_MainParamsSetDefaults() failed: %s\n", (AJ_StatusText(status))));
        goto MainParamsCleanup;
    }

    AJ_Initialize();
    AJ_AboutSetIcon(mainParams->aboutIconParams.content, mainParams->aboutIconParams.contentSize, mainParams->aboutIconParams.mimeType, mainParams->aboutIconParams.url);

    status = PropertyStore_Init();
    if (status != AJ_OK) {
        goto MainParamsCleanup;
    }

    status = Cdm_Init();
    if (status != AJ_OK) {
        AJ_ErrPrintf(("CDM_Init() failed: %s\n", (AJ_StatusText(status))));
        goto CdmCleanup;
    }

    status = cdmMainParams->InitCdmInterfaces();
    if (status != AJ_OK) {
        AJ_ErrPrintf(("cdmMainParams->InitCdmInterfaces() failed: %s\n", (AJ_StatusText(status))));
        goto CdmCleanup;
    }

    status = Cdm_Start();
    if (status != AJ_OK) {
        AJ_ErrPrintf(("Cdm_Start() failed: %s\n", (AJ_StatusText(status))));
        goto CdmCleanup;
    }

    // Start the message handling loop.
    status = MainLoop(cdmMainParams);
    if (status != AJ_OK) {
        AJ_ErrPrintf(("MainLoop() failed: %s\n", (AJ_StatusText(status))));
        goto CdmCleanup;
    }

CdmCleanup:
    Cdm_Deinit();

MainParamsCleanup:
    free(cdmMainParams);

    return (int)status;
}