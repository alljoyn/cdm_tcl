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
#include <ajtcl/cdm/interfaces/environment/TargetHumidityInterface.h>
#include <ajtcl/cdm/interfaces/environment/TargetHumidityModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME TARGET_HUMIDITY

const char* const intfDescEnvironmentTargetHumidity[] = {
    "$org.alljoyn.SmartSpaces.Environment.TargetHumidity",
    "@Version>q",
    "@TargetValue=y",
    "@MinValue>y",
    "@MaxValue>y",
    "@StepValue>y",
    "@SelectableHumidityLevels>ay",
    NULL
};




static AJ_Status TargetHumidity_GetTargetValue(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TargetHumidityModel* model = (TargetHumidityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTargetValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetTargetValue(model, objPath, out);
}



static AJ_Status TargetHumidity_SetTargetValue(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    TargetHumidityModel* model = (TargetHumidityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetTargetValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetTargetValue(model, objPath, value);
}



AJ_Status Cdm_TargetHumidity_EmitTargetValueChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "TargetValue", "y", newValue);
}



static AJ_Status TargetHumidity_GetMinValue(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TargetHumidityModel* model = (TargetHumidityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMinValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMinValue(model, objPath, out);
}



AJ_Status Cdm_TargetHumidity_EmitMinValueChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MinValue", "y", newValue);
}



static AJ_Status TargetHumidity_GetMaxValue(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TargetHumidityModel* model = (TargetHumidityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxValue(model, objPath, out);
}



AJ_Status Cdm_TargetHumidity_EmitMaxValueChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MaxValue", "y", newValue);
}



static AJ_Status TargetHumidity_GetStepValue(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TargetHumidityModel* model = (TargetHumidityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetStepValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetStepValue(model, objPath, out);
}



AJ_Status Cdm_TargetHumidity_EmitStepValueChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "StepValue", "y", newValue);
}



static AJ_Status TargetHumidity_GetSelectableHumidityLevels(AJ_BusAttachment* busAttachment, const char* objPath, Array_uint8* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TargetHumidityModel* model = (TargetHumidityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSelectableHumidityLevels) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSelectableHumidityLevels(model, objPath, out);
}



AJ_Status Cdm_TargetHumidity_EmitSelectableHumidityLevelsChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "SelectableHumidityLevels", "ay", newValue.elems, newValue.numElems);
}




//
// Handler functions
//
static AJ_Status TargetHumidity_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case TARGETHUMIDITY_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case TARGETHUMIDITY_PROP_TARGET_VALUE:
        {
            uint8_t target_value;
            status = TargetHumidity_GetTargetValue(busAttachment, objPath, &target_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", target_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TARGETHUMIDITY_PROP_MIN_VALUE:
        {
            uint8_t min_value;
            status = TargetHumidity_GetMinValue(busAttachment, objPath, &min_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", min_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TARGETHUMIDITY_PROP_MAX_VALUE:
        {
            uint8_t max_value;
            status = TargetHumidity_GetMaxValue(busAttachment, objPath, &max_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", max_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TARGETHUMIDITY_PROP_STEP_VALUE:
        {
            uint8_t step_value;
            status = TargetHumidity_GetStepValue(busAttachment, objPath, &step_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", step_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TARGETHUMIDITY_PROP_SELECTABLE_HUMIDITY_LEVELS:
        {
            Array_uint8 selectable_humidity_levels;
            status = TargetHumidity_GetSelectableHumidityLevels(busAttachment, objPath, &selectable_humidity_levels);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "ay", selectable_humidity_levels);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status TargetHumidity_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case TARGETHUMIDITY_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case TARGETHUMIDITY_PROP_TARGET_VALUE:
        {
            uint8_t target_value;
            status = AJ_UnmarshalArgs(msg, "y", &target_value);
            if (status == AJ_OK) {
                status = TargetHumidity_SetTargetValue(busAttachment, objPath, target_value);
                if (status == AJ_OK) {
                    status= Cdm_TargetHumidity_EmitTargetValueChanged(busAttachment, objPath, target_value);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status TargetHumidity_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerEnvironmentTargetHumidity = {
    TargetHumidity_OnGetProperty,
    TargetHumidity_OnSetProperty,
    TargetHumidity_OnMethodHandler
};