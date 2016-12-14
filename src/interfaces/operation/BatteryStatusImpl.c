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
#include <ajtcl/cdm/interfaces/operation/BatteryStatusInterface.h>
#include <ajtcl/cdm/interfaces/operation/BatteryStatusModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME BATTERY_STATUS

const char* const intfDescOperationBatteryStatus[] = {
    "$org.alljoyn.SmartSpaces.Operation.BatteryStatus",
    "@Version>q",
    "@CurrentValue>y",
    "@IsCharging>b",
    NULL
};




static AJ_Status BatteryStatus_GetCurrentValue(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    BatteryStatusModel* model = (BatteryStatusModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetCurrentValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetCurrentValue(model, objPath, out);
}



AJ_Status Cdm_BatteryStatus_EmitCurrentValueChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "CurrentValue", "y", newValue);
}



static AJ_Status BatteryStatus_GetIsCharging(AJ_BusAttachment* busAttachment, const char* objPath, bool* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    BatteryStatusModel* model = (BatteryStatusModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetIsCharging) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetIsCharging(model, objPath, out);
}



AJ_Status Cdm_BatteryStatus_EmitIsChargingChanged(AJ_BusAttachment *bus, const char *objPath, bool newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "IsCharging", "b", newValue);
}




//
// Handler functions
//
static AJ_Status BatteryStatus_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case BATTERYSTATUS_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case BATTERYSTATUS_PROP_CURRENT_VALUE:
        {
            uint8_t current_value;
            status = BatteryStatus_GetCurrentValue(busAttachment, objPath, &current_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", current_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case BATTERYSTATUS_PROP_IS_CHARGING:
        {
            bool is_charging;
            status = BatteryStatus_GetIsCharging(busAttachment, objPath, &is_charging);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "b", is_charging);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status BatteryStatus_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case BATTERYSTATUS_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status BatteryStatus_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationBatteryStatus = {
    BatteryStatus_OnGetProperty,
    BatteryStatus_OnSetProperty,
    BatteryStatus_OnMethodHandler
};