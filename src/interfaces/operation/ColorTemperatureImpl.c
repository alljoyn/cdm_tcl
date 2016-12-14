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
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/operation/ColorTemperatureInterface.h>
#include <ajtcl/cdm/interfaces/operation/ColorTemperatureModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME COLOR_TEMPERATURE

const char* const intfDescOperationColorTemperature[] = {
    "$org.alljoyn.SmartSpaces.Operation.ColorTemperature",
    "@Version>q",
    "@Temperature=d",
    "@MinTemperature>d",
    "@MaxTemperature>d",
    NULL
};




static AJ_Status ColorTemperature_GetTemperature(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    ColorTemperatureModel* model = (ColorTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTemperature) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetTemperature(model, objPath, out);
}



static AJ_Status ColorTemperature_SetTemperature(AJ_BusAttachment* busAttachment, const char* objPath, double value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    ColorTemperatureModel* model = (ColorTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetTemperature) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetTemperature(model, objPath, value);
}



AJ_Status Cdm_ColorTemperature_EmitTemperatureChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Temperature", "d", newValue);
}



static AJ_Status ColorTemperature_GetMinTemperature(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    ColorTemperatureModel* model = (ColorTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMinTemperature) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMinTemperature(model, objPath, out);
}



static AJ_Status ColorTemperature_GetMaxTemperature(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    ColorTemperatureModel* model = (ColorTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxTemperature) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxTemperature(model, objPath, out);
}




//
// Handler functions
//
static AJ_Status ColorTemperature_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case COLORTEMPERATURE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case COLORTEMPERATURE_PROP_TEMPERATURE:
        {
            double temperature;
            status = ColorTemperature_GetTemperature(busAttachment, objPath, &temperature);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", temperature);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case COLORTEMPERATURE_PROP_MIN_TEMPERATURE:
        {
            double min_temperature;
            status = ColorTemperature_GetMinTemperature(busAttachment, objPath, &min_temperature);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", min_temperature);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case COLORTEMPERATURE_PROP_MAX_TEMPERATURE:
        {
            double max_temperature;
            status = ColorTemperature_GetMaxTemperature(busAttachment, objPath, &max_temperature);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", max_temperature);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status ColorTemperature_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case COLORTEMPERATURE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case COLORTEMPERATURE_PROP_TEMPERATURE:
        {
            double temperature;
            status = AJ_UnmarshalArgs(msg, "d", &temperature);
            if (status == AJ_OK) {
                status = ColorTemperature_SetTemperature(busAttachment, objPath, temperature);
                if (status == AJ_OK) {
                    status= Cdm_ColorTemperature_EmitTemperatureChanged(busAttachment, objPath, temperature);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status ColorTemperature_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationColorTemperature = {
    ColorTemperature_OnGetProperty,
    ColorTemperature_OnSetProperty,
    ColorTemperature_OnMethodHandler
};