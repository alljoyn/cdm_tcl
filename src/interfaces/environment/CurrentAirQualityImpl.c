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
#include <ajtcl/cdm/interfaces/environment/CurrentAirQualityInterface.h>
#include <ajtcl/cdm/interfaces/environment/CurrentAirQualityModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME CURRENT_AIR_QUALITY

const char* const intfDescEnvironmentCurrentAirQuality[] = {
    "$org.alljoyn.SmartSpaces.Environment.CurrentAirQuality",
    "@Version>q",
    "@ContaminantType>y",
    "@CurrentValue>d",
    "@MinValue>d",
    "@MaxValue>d",
    "@Precision>d",
    "@UpdateMinTime>q",
    NULL
};


void InitArray_CurrentAirQuality_ContaminantType(Array_CurrentAirQuality_ContaminantType* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(CurrentAirQuality_ContaminantType), numElems);
}


void CopyArray_CurrentAirQuality_ContaminantType(Array_CurrentAirQuality_ContaminantType* value, Array_CurrentAirQuality_ContaminantType* copy)
{
    Copy_Array((CDM_Array*)value, sizeof(CurrentAirQuality_ContaminantType), (CDM_Array*)copy);
}


void FreeArray_CurrentAirQuality_ContaminantType(Array_CurrentAirQuality_ContaminantType* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_CurrentAirQuality_ContaminantType(Array_CurrentAirQuality_ContaminantType* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(CurrentAirQuality_ContaminantType), numElems);
}




static AJ_Status CurrentAirQuality_GetContaminantType(AJ_BusAttachment* busAttachment, const char* objPath, CurrentAirQuality_ContaminantType* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentAirQualityModel* model = (CurrentAirQualityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetContaminantType) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetContaminantType(model, objPath, out);
}



AJ_Status Cdm_CurrentAirQuality_EmitContaminantTypeChanged(AJ_BusAttachment *bus, const char *objPath, CurrentAirQuality_ContaminantType newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "ContaminantType", "y", newValue);
}



static AJ_Status CurrentAirQuality_GetCurrentValue(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentAirQualityModel* model = (CurrentAirQualityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetCurrentValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetCurrentValue(model, objPath, out);
}



AJ_Status Cdm_CurrentAirQuality_EmitCurrentValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "CurrentValue", "d", newValue);
}



static AJ_Status CurrentAirQuality_GetMinValue(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentAirQualityModel* model = (CurrentAirQualityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMinValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMinValue(model, objPath, out);
}



AJ_Status Cdm_CurrentAirQuality_EmitMinValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MinValue", "d", newValue);
}



static AJ_Status CurrentAirQuality_GetMaxValue(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentAirQualityModel* model = (CurrentAirQualityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxValue(model, objPath, out);
}



AJ_Status Cdm_CurrentAirQuality_EmitMaxValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MaxValue", "d", newValue);
}



static AJ_Status CurrentAirQuality_GetPrecision(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentAirQualityModel* model = (CurrentAirQualityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetPrecision) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetPrecision(model, objPath, out);
}



AJ_Status Cdm_CurrentAirQuality_EmitPrecisionChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Precision", "d", newValue);
}



static AJ_Status CurrentAirQuality_GetUpdateMinTime(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentAirQualityModel* model = (CurrentAirQualityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetUpdateMinTime) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetUpdateMinTime(model, objPath, out);
}



AJ_Status Cdm_CurrentAirQuality_EmitUpdateMinTimeChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "UpdateMinTime", "q", newValue);
}




//
// Handler functions
//
static AJ_Status CurrentAirQuality_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CURRENTAIRQUALITY_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case CURRENTAIRQUALITY_PROP_CONTAMINANT_TYPE:
        {
            CurrentAirQuality_ContaminantType contaminant_type;
            status = CurrentAirQuality_GetContaminantType(busAttachment, objPath, &contaminant_type);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", contaminant_type);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CURRENTAIRQUALITY_PROP_CURRENT_VALUE:
        {
            double current_value;
            status = CurrentAirQuality_GetCurrentValue(busAttachment, objPath, &current_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", current_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CURRENTAIRQUALITY_PROP_MIN_VALUE:
        {
            double min_value;
            status = CurrentAirQuality_GetMinValue(busAttachment, objPath, &min_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", min_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CURRENTAIRQUALITY_PROP_MAX_VALUE:
        {
            double max_value;
            status = CurrentAirQuality_GetMaxValue(busAttachment, objPath, &max_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", max_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CURRENTAIRQUALITY_PROP_PRECISION:
        {
            double precision;
            status = CurrentAirQuality_GetPrecision(busAttachment, objPath, &precision);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", precision);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CURRENTAIRQUALITY_PROP_UPDATE_MIN_TIME:
        {
            uint16_t update_min_time;
            status = CurrentAirQuality_GetUpdateMinTime(busAttachment, objPath, &update_min_time);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", update_min_time);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status CurrentAirQuality_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CURRENTAIRQUALITY_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status CurrentAirQuality_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerEnvironmentCurrentAirQuality = {
    CurrentAirQuality_OnGetProperty,
    CurrentAirQuality_OnSetProperty,
    CurrentAirQuality_OnMethodHandler
};