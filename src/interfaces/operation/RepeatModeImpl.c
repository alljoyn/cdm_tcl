/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/operation/RepeatModeInterface.h>
#include <ajtcl/cdm/interfaces/operation/RepeatModeModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME REPEAT_MODE

const char* const intfDescOperationRepeatMode[] = {
    "$org.alljoyn.SmartSpaces.Operation.RepeatMode",
    "@Version>q",
    "@RepeatMode=b",
    NULL
};




static AJ_Status RepeatMode_GetRepeatMode(AJ_BusAttachment* busAttachment, const char* objPath, bool* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    RepeatModeModel* model = (RepeatModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetRepeatMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetRepeatMode(model, objPath, out);
}



static AJ_Status RepeatMode_SetRepeatMode(AJ_BusAttachment* busAttachment, const char* objPath, bool value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    RepeatModeModel* model = (RepeatModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetRepeatMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetRepeatMode(model, objPath, value);
}



AJ_Status Cdm_RepeatMode_EmitRepeatModeChanged(AJ_BusAttachment *bus, const char *objPath, bool newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "RepeatMode", "b", newValue);
}




//
// Handler functions
//
static AJ_Status RepeatMode_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case REPEATMODE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case REPEATMODE_PROP_REPEAT_MODE:
        {
            bool repeat_mode;
            status = RepeatMode_GetRepeatMode(busAttachment, objPath, &repeat_mode);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "b", repeat_mode);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status RepeatMode_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case REPEATMODE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case REPEATMODE_PROP_REPEAT_MODE:
        {
            bool repeat_mode;
            status = AJ_UnmarshalArgs(msg, "b", &repeat_mode);
            if (status == AJ_OK) {
                status = RepeatMode_SetRepeatMode(busAttachment, objPath, repeat_mode);
                if (status == AJ_OK) {
                    status= Cdm_RepeatMode_EmitRepeatModeChanged(busAttachment, objPath, repeat_mode);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status RepeatMode_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationRepeatMode = {
    RepeatMode_OnGetProperty,
    RepeatMode_OnSetProperty,
    RepeatMode_OnMethodHandler
};