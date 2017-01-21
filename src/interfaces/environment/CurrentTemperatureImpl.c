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
#include <ajtcl/cdm/interfaces/environment/CurrentTemperatureInterface.h>
#include <ajtcl/cdm/interfaces/environment/CurrentTemperatureModel.h>

#include <ajtcl/cdm/utils/CdmArray.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME CURRENT_TEMPERATURE

const char* const intfDescEnvironmentCurrentTemperature[] = {
    "$org.alljoyn.SmartSpaces.Environment.CurrentTemperature",
    "@Version>q",
    "@CurrentValue>d",
    "@Precision>d",
    "@UpdateMinTime>q",
    NULL
};




static AJ_Status CurrentTemperature_GetCurrentValue(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentTemperatureModel* model = (CurrentTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetCurrentValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetCurrentValue(model, objPath, out);
}



AJ_Status Cdm_CurrentTemperature_EmitCurrentValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "CurrentValue", "d", newValue);
}



static AJ_Status CurrentTemperature_GetPrecision(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentTemperatureModel* model = (CurrentTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetPrecision) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetPrecision(model, objPath, out);
}



AJ_Status Cdm_CurrentTemperature_EmitPrecisionChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Precision", "d", newValue);
}



static AJ_Status CurrentTemperature_GetUpdateMinTime(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentTemperatureModel* model = (CurrentTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetUpdateMinTime) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetUpdateMinTime(model, objPath, out);
}



AJ_Status Cdm_CurrentTemperature_EmitUpdateMinTimeChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "UpdateMinTime", "q", newValue);
}




/*
   Handler functions
*/
static AJ_Status CurrentTemperature_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CURRENTTEMPERATURE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case CURRENTTEMPERATURE_PROP_CURRENT_VALUE:
        {
            double current_value;
            memset(&current_value, 0, sizeof(double));
            status = CurrentTemperature_GetCurrentValue(busAttachment, objPath, &current_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", current_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CURRENTTEMPERATURE_PROP_PRECISION:
        {
            double precision;
            memset(&precision, 0, sizeof(double));
            status = CurrentTemperature_GetPrecision(busAttachment, objPath, &precision);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", precision);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CURRENTTEMPERATURE_PROP_UPDATE_MIN_TIME:
        {
            uint16_t update_min_time;
            memset(&update_min_time, 0, sizeof(uint16_t));
            status = CurrentTemperature_GetUpdateMinTime(busAttachment, objPath, &update_min_time);
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



static AJ_Status CurrentTemperature_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CURRENTTEMPERATURE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status CurrentTemperature_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerEnvironmentCurrentTemperature = {
    CurrentTemperature_OnGetProperty,
    CurrentTemperature_OnSetProperty,
    CurrentTemperature_OnMethodHandler
};
