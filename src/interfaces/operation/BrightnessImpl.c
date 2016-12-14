/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#include <ajtcl/cdm/interfaces/operation/BrightnessInterface.h>
#include <ajtcl/cdm/interfaces/operation/BrightnessModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME BRIGHTNESS

const char* const intfDescOperationBrightness[] = {
    "$org.alljoyn.SmartSpaces.Operation.Brightness",
    "@Version>q",
    "@Brightness=d",
    NULL
};




static AJ_Status Brightness_GetBrightness(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    BrightnessModel* model = (BrightnessModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetBrightness) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetBrightness(model, objPath, out);
}



static AJ_Status Brightness_SetBrightness(AJ_BusAttachment* busAttachment, const char* objPath, double value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    BrightnessModel* model = (BrightnessModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetBrightness) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetBrightness(model, objPath, value);
}



AJ_Status Cdm_Brightness_EmitBrightnessChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Brightness", "d", newValue);
}




//
// Handler functions
//
static AJ_Status Brightness_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case BRIGHTNESS_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case BRIGHTNESS_PROP_BRIGHTNESS:
        {
            double brightness;
            status = Brightness_GetBrightness(busAttachment, objPath, &brightness);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", brightness);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status Brightness_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case BRIGHTNESS_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case BRIGHTNESS_PROP_BRIGHTNESS:
        {
            double brightness;
            status = AJ_UnmarshalArgs(msg, "d", &brightness);
            if (status == AJ_OK) {
                status = Brightness_SetBrightness(busAttachment, objPath, brightness);
                if (status == AJ_OK) {
                    status= Cdm_Brightness_EmitBrightnessChanged(busAttachment, objPath, brightness);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status Brightness_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationBrightness = {
    Brightness_OnGetProperty,
    Brightness_OnSetProperty,
    Brightness_OnMethodHandler
};