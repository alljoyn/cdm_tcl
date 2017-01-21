/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#ifndef ALLJOYN_CDM_SYSTEM_H
#define ALLJOYN_CDM_SYSTEM_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/services/ServicesHandlers.h>

typedef struct {
    const char* mimeType;
    const uint8_t* content;
    size_t contentSize;
    const char* url;
} CdmAboutIconParams;

typedef struct {
    const char* name;
    uint32_t busLinkTimeout;
    uint32_t connectTimeout;
    uint32_t connectPause;
    uint32_t preDisconnectPause;
    uint32_t postDisconnectPause;
} CdmRoutingNodeParams;

typedef struct {
    AJ_BusAttachment bus;
    uint8_t isConnected;
} CdmBusAttachment;

typedef AJ_Status (*AppUpdateHandler)(AJ_BusAttachment* busAttachment);
typedef AJSVC_ServiceStatus (*MessageProcessor)(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* status);
typedef AJ_Status (*SessionAcceptedHandler) (uint16_t port, uint32_t sessionId, const char* joiner);
typedef AJ_Status (*AppDisconnectedHandler) (AJ_BusAttachment* busAttachment, uint8_t restart);

void Cdm_SetDefaultAboutIconParams(CdmAboutIconParams *params);
void Cdm_SetDefaultRoutingNodeParams(CdmRoutingNodeParams *params);

AJ_Status Cdm_SystemInit(CdmAboutIconParams *iconParams, bool emitChangedOnSetProprty);
AJ_Status Cdm_SystemConnect(CdmRoutingNodeParams *routingNodeParams, CdmBusAttachment *busAttachment);

AJ_Status Cdm_MessageLoop(CdmBusAttachment *busAttachment);
AJ_Status Cdm_HandleMessageLoopExit(AJ_Status loopExitStatus, CdmBusAttachment *busAttachment, CdmRoutingNodeParams *routingNodeParams);

void Cdm_SystemStop(void);


#endif /* ALLJOYN_CDM_SYSTEM_H */
