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
#include <ajtcl/cdm/interfaces/environment/WaterLevelInterface.h>
#include <ajtcl/cdm/interfaces/environment/WaterLevelModel.h>

#include <ajtcl/cdm/utils/CdmArray.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME WATER_LEVEL

const char* const intfDescEnvironmentWaterLevel[] = {
    "$org.alljoyn.SmartSpaces.Environment.WaterLevel",
    "@Version>q",
    "@SupplySource>y",
    "@CurrentLevel>y",
    "@MaxLevel>y",
    NULL
};


void InitArray_WaterLevel_SupplySource(Array_WaterLevel_SupplySource* value, size_t numElems)
{
    Init_Array((CdmArray*)value, sizeof(WaterLevel_SupplySource), numElems);
}


void CopyArray_WaterLevel_SupplySource(Array_WaterLevel_SupplySource* value, Array_WaterLevel_SupplySource* copy)
{
    Copy_Array((CdmArray*)value, sizeof(WaterLevel_SupplySource), (CdmArray*)copy);
}


void FreeArray_WaterLevel_SupplySource(Array_WaterLevel_SupplySource* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_WaterLevel_SupplySource(Array_WaterLevel_SupplySource* value, size_t numElems)
{
    return Extend_Array((CdmArray*)value, sizeof(WaterLevel_SupplySource), numElems);
}




static AJ_Status WaterLevel_GetSupplySource(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    WaterLevelModel* model = (WaterLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupplySource) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupplySource(model, objPath, out);
}



AJ_Status Cdm_WaterLevel_EmitSupplySourceChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "SupplySource", "y", newValue);
}



static AJ_Status WaterLevel_GetCurrentLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    WaterLevelModel* model = (WaterLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetCurrentLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetCurrentLevel(model, objPath, out);
}



AJ_Status Cdm_WaterLevel_EmitCurrentLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "CurrentLevel", "y", newValue);
}



static AJ_Status WaterLevel_GetMaxLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    WaterLevelModel* model = (WaterLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxLevel(model, objPath, out);
}



AJ_Status Cdm_WaterLevel_EmitMaxLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MaxLevel", "y", newValue);
}




/*
   Handler functions
*/
static AJ_Status WaterLevel_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case WATERLEVEL_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case WATERLEVEL_PROP_SUPPLY_SOURCE:
        {
            uint8_t supply_source;
            memset(&supply_source, 0, sizeof(uint8_t));
            status = WaterLevel_GetSupplySource(busAttachment, objPath, &supply_source);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", supply_source);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case WATERLEVEL_PROP_CURRENT_LEVEL:
        {
            uint8_t current_level;
            memset(&current_level, 0, sizeof(uint8_t));
            status = WaterLevel_GetCurrentLevel(busAttachment, objPath, &current_level);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", current_level);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case WATERLEVEL_PROP_MAX_LEVEL:
        {
            uint8_t max_level;
            memset(&max_level, 0, sizeof(uint8_t));
            status = WaterLevel_GetMaxLevel(busAttachment, objPath, &max_level);
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



static AJ_Status WaterLevel_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case WATERLEVEL_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status WaterLevel_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerEnvironmentWaterLevel = {
    WaterLevel_OnGetProperty,
    WaterLevel_OnSetProperty,
    WaterLevel_OnMethodHandler
};
