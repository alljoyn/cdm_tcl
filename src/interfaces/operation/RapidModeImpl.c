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

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

#include <ajtcl/cdm/interfaces/CdmInterfaceCommon.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceValidation.h>
#include <ajtcl/cdm/interfaces/operation/RapidModeInterface.h>
#include <ajtcl/cdm/interfaces/operation/RapidModeModel.h>

#include <ajtcl/cdm/utils/CdmArray.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME RAPID_MODE

const char* const intfDescOperationRapidMode[] = {
    "$org.alljoyn.SmartSpaces.Operation.RapidMode",
    "@Version>q",
    "@RapidMode=b",
    NULL
};




static AJ_Status RapidMode_GetRapidMode(AJ_BusAttachment* busAttachment, const char* objPath, bool* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    RapidModeModel* model = (RapidModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetRapidMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetRapidMode(model, objPath, out);
}

static AJ_Status RapidMode_SetRapidMode(AJ_BusAttachment* busAttachment, const char* objPath, bool value)
{
    AJ_Status status;

    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    RapidModeModel* model = (RapidModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetRapidMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    status = model->SetRapidMode(model, objPath, value);
    return status;
}



AJ_Status Cdm_RapidMode_EmitRapidModeChanged(AJ_BusAttachment *bus, const char *objPath, bool newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "RapidMode", "b", newValue);
}




/*
   Handler functions
*/
static AJ_Status RapidMode_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case RAPIDMODE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case RAPIDMODE_PROP_RAPID_MODE:
        {
            bool rapid_mode;
            memset(&rapid_mode, 0, sizeof(bool));
            status = RapidMode_GetRapidMode(busAttachment, objPath, &rapid_mode);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "b", rapid_mode);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status RapidMode_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case RAPIDMODE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case RAPIDMODE_PROP_RAPID_MODE:
        {
            bool rapid_mode;
            status = AJ_UnmarshalArgs(msg, "b", &rapid_mode);
            if (status == AJ_OK) {
                status = RapidMode_SetRapidMode(busAttachment, objPath, rapid_mode);
                if (status == AJ_OK && emitOnSet) {
                    status = Cdm_RapidMode_EmitRapidModeChanged(busAttachment, objPath, rapid_mode);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status RapidMode_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationRapidMode = {
    RapidMode_OnGetProperty,
    RapidMode_OnSetProperty,
    RapidMode_OnMethodHandler
};
