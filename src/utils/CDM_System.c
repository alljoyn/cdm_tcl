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

void CDM_SystemStop(void)
{
    Cdm_Deinit();
}