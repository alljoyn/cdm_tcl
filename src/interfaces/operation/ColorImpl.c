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
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/operation/ColorInterface.h>
#include <ajtcl/cdm/interfaces/operation/ColorModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME COLOR

const char* const intfDescOperationColor[] = {
    "$org.alljoyn.SmartSpaces.Operation.Color",
    "@Version>q",
    "@Hue=d",
    "@Saturation=d",
    NULL
};




static AJ_Status Color_GetHue(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    ColorModel* model = (ColorModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetHue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetHue(model, objPath, out);
}



static AJ_Status Color_SetHue(AJ_BusAttachment* busAttachment, const char* objPath, double value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    ColorModel* model = (ColorModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetHue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetHue(model, objPath, value);
}



AJ_Status Cdm_Color_EmitHueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Hue", "d", newValue);
}



static AJ_Status Color_GetSaturation(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    ColorModel* model = (ColorModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSaturation) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSaturation(model, objPath, out);
}



static AJ_Status Color_SetSaturation(AJ_BusAttachment* busAttachment, const char* objPath, double value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    ColorModel* model = (ColorModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetSaturation) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetSaturation(model, objPath, value);
}



AJ_Status Cdm_Color_EmitSaturationChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Saturation", "d", newValue);
}




//
// Handler functions
//
static AJ_Status Color_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case COLOR_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case COLOR_PROP_HUE:
        {
            double hue;
            status = Color_GetHue(busAttachment, objPath, &hue);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", hue);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case COLOR_PROP_SATURATION:
        {
            double saturation;
            status = Color_GetSaturation(busAttachment, objPath, &saturation);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", saturation);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status Color_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case COLOR_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case COLOR_PROP_HUE:
        {
            double hue;
            status = AJ_UnmarshalArgs(msg, "d", &hue);
            if (status == AJ_OK) {
                status = Color_SetHue(busAttachment, objPath, hue);
                if (status == AJ_OK) {
                    status= Cdm_Color_EmitHueChanged(busAttachment, objPath, hue);
                }
            }
            break;
        }

        case COLOR_PROP_SATURATION:
        {
            double saturation;
            status = AJ_UnmarshalArgs(msg, "d", &saturation);
            if (status == AJ_OK) {
                status = Color_SetSaturation(busAttachment, objPath, saturation);
                if (status == AJ_OK) {
                    status= Cdm_Color_EmitSaturationChanged(busAttachment, objPath, saturation);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status Color_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationColor = {
    Color_OnGetProperty,
    Color_OnSetProperty,
    Color_OnMethodHandler
};