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
#include <ajtcl/cdm/interfaces/CdmInterfaceValidation.h>
#include <ajtcl/cdm/interfaces/operation/HeatingZoneInterface.h>
#include <ajtcl/cdm/interfaces/operation/HeatingZoneModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME HEATING_ZONE

const char* const intfDescOperationHeatingZone[] = {
    "$org.alljoyn.SmartSpaces.Operation.HeatingZone",
    "@Version>q",
    "@NumberOfHeatingZones>y",
    "@MaxHeatingLevels>ay",
    "@HeatingLevels>ay",
    NULL
};




static AJ_Status HeatingZone_GetNumberOfHeatingZones(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    HeatingZoneModel* model = (HeatingZoneModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetNumberOfHeatingZones) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetNumberOfHeatingZones(model, objPath, out);
}



AJ_Status Cdm_HeatingZone_EmitNumberOfHeatingZonesChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "NumberOfHeatingZones", "y", newValue);
}



static AJ_Status HeatingZone_GetMaxHeatingLevels(AJ_BusAttachment* busAttachment, const char* objPath, Array_uint8* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    HeatingZoneModel* model = (HeatingZoneModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxHeatingLevels) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxHeatingLevels(model, objPath, out);
}



AJ_Status Cdm_HeatingZone_EmitMaxHeatingLevelsChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MaxHeatingLevels", "ay", newValue.elems, newValue.numElems);
}



static AJ_Status HeatingZone_GetHeatingLevels(AJ_BusAttachment* busAttachment, const char* objPath, Array_uint8* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    HeatingZoneModel* model = (HeatingZoneModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetHeatingLevels) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetHeatingLevels(model, objPath, out);
}



AJ_Status Cdm_HeatingZone_EmitHeatingLevelsChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "HeatingLevels", "ay", newValue.elems, newValue.numElems);
}




/*
   Handler functions
*/
static AJ_Status HeatingZone_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case HEATINGZONE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case HEATINGZONE_PROP_NUMBER_OF_HEATING_ZONES:
        {
            uint8_t number_of_heating_zones;
            memset(&number_of_heating_zones, 0, sizeof(uint8_t));
            status = HeatingZone_GetNumberOfHeatingZones(busAttachment, objPath, &number_of_heating_zones);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", number_of_heating_zones);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case HEATINGZONE_PROP_MAX_HEATING_LEVELS:
        {
            Array_uint8 max_heating_levels;
            memset(&max_heating_levels, 0, sizeof(Array_uint8));
            status = HeatingZone_GetMaxHeatingLevels(busAttachment, objPath, &max_heating_levels);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "ay", max_heating_levels.elems, sizeof(uint8_t) * max_heating_levels.numElems);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case HEATINGZONE_PROP_HEATING_LEVELS:
        {
            Array_uint8 heating_levels;
            memset(&heating_levels, 0, sizeof(Array_uint8));
            status = HeatingZone_GetHeatingLevels(busAttachment, objPath, &heating_levels);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "ay", heating_levels.elems, sizeof(uint8_t) * heating_levels.numElems);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status HeatingZone_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case HEATINGZONE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status HeatingZone_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationHeatingZone = {
    HeatingZone_OnGetProperty,
    HeatingZone_OnSetProperty,
    HeatingZone_OnMethodHandler
};
