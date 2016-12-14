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
#include <ajtcl/cdm/interfaces/environment/TargetTemperatureLevelInterface.h>
#include <ajtcl/cdm/interfaces/environment/TargetTemperatureLevelModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME TARGET_TEMPERATURE_LEVEL

const char* const intfDescEnvironmentTargetTemperatureLevel[] = {
    "$org.alljoyn.SmartSpaces.Environment.TargetTemperatureLevel",
    "@Version>q",
    "@MaxLevel>y",
    "@TargetLevel=y",
    "@SelectableTemperatureLevels>ay",
    NULL
};




static AJ_Status TargetTemperatureLevel_GetMaxLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureLevelModel* model = (TargetTemperatureLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxLevel(model, objPath, out);
}



AJ_Status Cdm_TargetTemperatureLevel_EmitMaxLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MaxLevel", "y", newValue);
}



static AJ_Status TargetTemperatureLevel_GetTargetLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureLevelModel* model = (TargetTemperatureLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTargetLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetTargetLevel(model, objPath, out);
}



static AJ_Status TargetTemperatureLevel_SetTargetLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureLevelModel* model = (TargetTemperatureLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetTargetLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetTargetLevel(model, objPath, value);
}



AJ_Status Cdm_TargetTemperatureLevel_EmitTargetLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "TargetLevel", "y", newValue);
}



static AJ_Status TargetTemperatureLevel_GetSelectableTemperatureLevels(AJ_BusAttachment* busAttachment, const char* objPath, Array_uint8* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureLevelModel* model = (TargetTemperatureLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSelectableTemperatureLevels) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSelectableTemperatureLevels(model, objPath, out);
}



AJ_Status Cdm_TargetTemperatureLevel_EmitSelectableTemperatureLevelsChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "SelectableTemperatureLevels", "ay", newValue.elems, newValue.numElems);
}




//
// Handler functions
//
static AJ_Status TargetTemperatureLevel_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case TARGETTEMPERATURELEVEL_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case TARGETTEMPERATURELEVEL_PROP_MAX_LEVEL:
        {
            uint8_t max_level;
            status = TargetTemperatureLevel_GetMaxLevel(busAttachment, objPath, &max_level);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", max_level);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TARGETTEMPERATURELEVEL_PROP_TARGET_LEVEL:
        {
            uint8_t target_level;
            status = TargetTemperatureLevel_GetTargetLevel(busAttachment, objPath, &target_level);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", target_level);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TARGETTEMPERATURELEVEL_PROP_SELECTABLE_TEMPERATURE_LEVELS:
        {
            Array_uint8 selectable_temperature_levels;
            status = TargetTemperatureLevel_GetSelectableTemperatureLevels(busAttachment, objPath, &selectable_temperature_levels);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "ay", selectable_temperature_levels);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status TargetTemperatureLevel_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case TARGETTEMPERATURELEVEL_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case TARGETTEMPERATURELEVEL_PROP_TARGET_LEVEL:
        {
            uint8_t target_level;
            status = AJ_UnmarshalArgs(msg, "y", &target_level);
            if (status == AJ_OK) {
                status = TargetTemperatureLevel_SetTargetLevel(busAttachment, objPath, target_level);
                if (status == AJ_OK) {
                    status= Cdm_TargetTemperatureLevel_EmitTargetLevelChanged(busAttachment, objPath, target_level);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status TargetTemperatureLevel_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerEnvironmentTargetTemperatureLevel = {
    TargetTemperatureLevel_OnGetProperty,
    TargetTemperatureLevel_OnSetProperty,
    TargetTemperatureLevel_OnMethodHandler
};