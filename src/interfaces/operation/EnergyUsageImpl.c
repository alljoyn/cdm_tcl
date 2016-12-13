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
#include <ajtcl/cdm/interfaces/operation/EnergyUsageInterface.h>
#include <ajtcl/cdm/interfaces/operation/EnergyUsageModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME ENERGY_USAGE

const char* const intfDescOperationEnergyUsage[] = {
    "$org.alljoyn.SmartSpaces.Operation.EnergyUsage",
    "@Version>q",
    "@CumulativeEnergy>d",
    "@Precision>d",
    "@UpdateMinTime>q",
    "?ResetCumulativeEnergy",
    NULL
};




static AJ_Status EnergyUsage_GetCumulativeEnergy(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    EnergyUsageModel* model = (EnergyUsageModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetCumulativeEnergy) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetCumulativeEnergy(model, objPath, out);
}



AJ_Status Cdm_EnergyUsage_EmitCumulativeEnergyChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "CumulativeEnergy", "d", newValue);
}



static AJ_Status EnergyUsage_GetPrecision(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    EnergyUsageModel* model = (EnergyUsageModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetPrecision) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetPrecision(model, objPath, out);
}



AJ_Status Cdm_EnergyUsage_EmitPrecisionChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Precision", "d", newValue);
}



static AJ_Status EnergyUsage_GetUpdateMinTime(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    EnergyUsageModel* model = (EnergyUsageModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetUpdateMinTime) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetUpdateMinTime(model, objPath, out);
}



AJ_Status Cdm_EnergyUsage_EmitUpdateMinTimeChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "UpdateMinTime", "q", newValue);
}



static AJ_Status Cdm_EnergyUsage_CallResetCumulativeEnergy(AJ_BusAttachment* busAttachment, const char *objPath)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    EnergyUsageModel* model = (EnergyUsageModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->MethodResetCumulativeEnergy) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->MethodResetCumulativeEnergy(model, objPath);
}



//
// Handler functions
//
static AJ_Status EnergyUsage_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case ENERGYUSAGE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case ENERGYUSAGE_PROP_CUMULATIVE_ENERGY:
        {
            double cumulative_energy;
            status = EnergyUsage_GetCumulativeEnergy(busAttachment, objPath, &cumulative_energy);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", cumulative_energy);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case ENERGYUSAGE_PROP_PRECISION:
        {
            double precision;
            status = EnergyUsage_GetPrecision(busAttachment, objPath, &precision);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", precision);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case ENERGYUSAGE_PROP_UPDATE_MIN_TIME:
        {
            uint16_t update_min_time;
            status = EnergyUsage_GetUpdateMinTime(busAttachment, objPath, &update_min_time);
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



static AJ_Status EnergyUsage_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case ENERGYUSAGE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status EnergyUsage_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {

    case ENERGYUSAGE_METHOD_RESET_CUMULATIVE_ENERGY:
    {

        status = Cdm_EnergyUsage_CallResetCumulativeEnergy(busAttachment, objPath);

        AJ_Message reply;
        AJ_MarshalReplyMsg(msg, &reply);

        if (status == AJ_OK) {
            status = AJ_DeliverMsg(&reply);
        }

        break;
    }
    }

    return status;
}



const InterfaceHandler intfHandlerOperationEnergyUsage = {
    EnergyUsage_OnGetProperty,
    EnergyUsage_OnSetProperty,
    EnergyUsage_OnMethodHandler
};