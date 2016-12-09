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

#ifndef ALLJOYN_CDM_SYSTEM_H
#define ALLJOYN_CDM_SYSTEM_H

#include <stdlib.h>
#include <stdint.h>

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>

typedef struct {
    const char* mimeType;
    const uint8_t* content;
    size_t contentSize;
    const char* url;
} CDM_AboutIconParams;

typedef struct {
    const char* name;
    uint32_t busLinkTimeout;
    uint32_t connectTimeout;
    uint32_t connectPause;
    uint32_t preDisconnectPause;
    uint32_t postDisconnectPause;
} CDM_RoutingNodeParams;

typedef struct {
    AJ_BusAttachment bus;
    uint8_t isConnected;
} CDM_BusAttachment;

void CDM_SetDefaultAboutIconParams(CDM_AboutIconParams *params);
void CDM_SetDefaultRoutingNodeParams(CDM_RoutingNodeParams *params);

AJ_Status CDM_SystemInit(CDM_AboutIconParams *iconParams);
AJ_Status CDM_SystemConnect(CDM_RoutingNodeParams *routingNodeParams, CDM_BusAttachment *busAttachment);

void CDM_SystemStop(void);


#endif //ALLJOYN_CDM_SYSTEM_H
