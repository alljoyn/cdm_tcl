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
#include <ajtcl/cdm/interfaces/operation/CurrentPowerInterface.h>
#include <ajtcl/cdm/interfaces/operation/CurrentPowerModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME CURRENT_POWER

const char* const intfDescOperationCurrentPower[] = {
    "$org.alljoyn.SmartSpaces.Operation.CurrentPower",
    "@Version>q",
    "@CurrentPower>d",
    "@Precision>d",
    "@UpdateMinTime>q",
    NULL
};




static AJ_Status CurrentPower_GetCurrentPower(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentPowerModel* model = (CurrentPowerModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetCurrentPower) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetCurrentPower(model, objPath, out);
}



AJ_Status Cdm_CurrentPower_EmitCurrentPowerChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "CurrentPower", "d", newValue);
}



static AJ_Status CurrentPower_GetPrecision(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentPowerModel* model = (CurrentPowerModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetPrecision) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetPrecision(model, objPath, out);
}



AJ_Status Cdm_CurrentPower_EmitPrecisionChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Precision", "d", newValue);
}



static AJ_Status CurrentPower_GetUpdateMinTime(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentPowerModel* model = (CurrentPowerModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetUpdateMinTime) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetUpdateMinTime(model, objPath, out);
}



AJ_Status Cdm_CurrentPower_EmitUpdateMinTimeChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "UpdateMinTime", "q", newValue);
}




//
// Handler functions
//
static AJ_Status CurrentPower_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CURRENTPOWER_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case CURRENTPOWER_PROP_CURRENT_POWER:
        {
            double current_power;
            status = CurrentPower_GetCurrentPower(busAttachment, objPath, &current_power);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", current_power);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CURRENTPOWER_PROP_PRECISION:
        {
            double precision;
            status = CurrentPower_GetPrecision(busAttachment, objPath, &precision);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", precision);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CURRENTPOWER_PROP_UPDATE_MIN_TIME:
        {
            uint16_t update_min_time;
            status = CurrentPower_GetUpdateMinTime(busAttachment, objPath, &update_min_time);
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



static AJ_Status CurrentPower_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CURRENTPOWER_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status CurrentPower_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationCurrentPower = {
    CurrentPower_OnGetProperty,
    CurrentPower_OnSetProperty,
    CurrentPower_OnMethodHandler
};