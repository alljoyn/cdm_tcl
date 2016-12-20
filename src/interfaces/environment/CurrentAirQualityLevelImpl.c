/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/environment/CurrentAirQualityLevelInterface.h>
#include <ajtcl/cdm/interfaces/environment/CurrentAirQualityLevelModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME CURRENT_AIR_QUALITY_LEVEL

const char* const intfDescEnvironmentCurrentAirQualityLevel[] = {
    "$org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel",
    "@Version>q",
    "@ContaminantType>y",
    "@CurrentLevel>y",
    "@MaxLevel>y",
    NULL
};


void InitArray_CurrentAirQualityLevel_ContaminantType(Array_CurrentAirQualityLevel_ContaminantType* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(CurrentAirQualityLevel_ContaminantType), numElems);
}


void CopyArray_CurrentAirQualityLevel_ContaminantType(Array_CurrentAirQualityLevel_ContaminantType* value, Array_CurrentAirQualityLevel_ContaminantType* copy)
{
    Copy_Array((CDM_Array*)value, sizeof(CurrentAirQualityLevel_ContaminantType), (CDM_Array*)copy);
}


void FreeArray_CurrentAirQualityLevel_ContaminantType(Array_CurrentAirQualityLevel_ContaminantType* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_CurrentAirQualityLevel_ContaminantType(Array_CurrentAirQualityLevel_ContaminantType* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(CurrentAirQualityLevel_ContaminantType), numElems);
}




static AJ_Status CurrentAirQualityLevel_GetContaminantType(AJ_BusAttachment* busAttachment, const char* objPath, CurrentAirQualityLevel_ContaminantType* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentAirQualityLevelModel* model = (CurrentAirQualityLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetContaminantType) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetContaminantType(model, objPath, out);
}



AJ_Status Cdm_CurrentAirQualityLevel_EmitContaminantTypeChanged(AJ_BusAttachment *bus, const char *objPath, CurrentAirQualityLevel_ContaminantType newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "ContaminantType", "y", newValue);
}



static AJ_Status CurrentAirQualityLevel_GetCurrentLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentAirQualityLevelModel* model = (CurrentAirQualityLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetCurrentLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetCurrentLevel(model, objPath, out);
}



AJ_Status Cdm_CurrentAirQualityLevel_EmitCurrentLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "CurrentLevel", "y", newValue);
}



static AJ_Status CurrentAirQualityLevel_GetMaxLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentAirQualityLevelModel* model = (CurrentAirQualityLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxLevel(model, objPath, out);
}



AJ_Status Cdm_CurrentAirQualityLevel_EmitMaxLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MaxLevel", "y", newValue);
}




//
// Handler functions
//
static AJ_Status CurrentAirQualityLevel_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CURRENTAIRQUALITYLEVEL_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case CURRENTAIRQUALITYLEVEL_PROP_CONTAMINANT_TYPE:
        {
            CurrentAirQualityLevel_ContaminantType contaminant_type;
            status = CurrentAirQualityLevel_GetContaminantType(busAttachment, objPath, &contaminant_type);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", contaminant_type);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CURRENTAIRQUALITYLEVEL_PROP_CURRENT_LEVEL:
        {
            uint8_t current_level;
            status = CurrentAirQualityLevel_GetCurrentLevel(busAttachment, objPath, &current_level);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", current_level);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CURRENTAIRQUALITYLEVEL_PROP_MAX_LEVEL:
        {
            uint8_t max_level;
            status = CurrentAirQualityLevel_GetMaxLevel(busAttachment, objPath, &max_level);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", max_level);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status CurrentAirQualityLevel_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CURRENTAIRQUALITYLEVEL_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status CurrentAirQualityLevel_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerEnvironmentCurrentAirQualityLevel = {
    CurrentAirQualityLevel_OnGetProperty,
    CurrentAirQualityLevel_OnSetProperty,
    CurrentAirQualityLevel_OnMethodHandler
};