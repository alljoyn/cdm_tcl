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
#include <ajtcl/cdm/interfaces/userinterfacesettings/TemperatureDisplayInterface.h>
#include <ajtcl/cdm/interfaces/userinterfacesettings/TemperatureDisplayModel.h>

#include <ajtcl/cdm/utils/CdmArray.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME TEMPERATURE_DISPLAY

const char* const intfDescUserinterfacesettingsTemperatureDisplay[] = {
    "$org.alljoyn.SmartSpaces.UserInterfaceSettings.TemperatureDisplay",
    "@Version>q",
    "@DisplayTemperatureUnit=y",
    "@SupportedDisplayTemperatureUnits>ay",
    NULL
};




static AJ_Status TemperatureDisplay_GetDisplayTemperatureUnit(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TemperatureDisplayModel* model = (TemperatureDisplayModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetDisplayTemperatureUnit) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetDisplayTemperatureUnit(model, objPath, out);
}

static AJ_Status ValidateDisplayTemperatureUnit(TemperatureDisplayModel* model, const char* objPath, uint8_t value)
{

    Array_uint8 validValues;
    if (model->GetSupportedDisplayTemperatureUnits(model, objPath, &validValues) != AJ_OK)
        return AJ_ERR_FAILURE;

    AJ_Status status = (valueIn_Array_uint8(value, &validValues) == 1) ? AJ_OK : AJ_ERR_NO_MATCH;

    FreeArray_uint8(&validValues);
    return status;
}

static AJ_Status TemperatureDisplay_SetDisplayTemperatureUnit(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t value)
{
    AJ_Status status;

    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    TemperatureDisplayModel* model = (TemperatureDisplayModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetDisplayTemperatureUnit) {
        return AJ_ERR_NULL;
    }

    status = ValidateDisplayTemperatureUnit(model, objPath, value);
    if (status != AJ_OK)
        return status;

    model->busAttachment = busAttachment;
    status = model->SetDisplayTemperatureUnit(model, objPath, value);
    return status;
}



AJ_Status Cdm_TemperatureDisplay_EmitDisplayTemperatureUnitChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "DisplayTemperatureUnit", "y", newValue);
}



static AJ_Status TemperatureDisplay_GetSupportedDisplayTemperatureUnits(AJ_BusAttachment* busAttachment, const char* objPath, Array_uint8* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TemperatureDisplayModel* model = (TemperatureDisplayModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupportedDisplayTemperatureUnits) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupportedDisplayTemperatureUnits(model, objPath, out);
}




/*
   Handler functions
*/
static AJ_Status TemperatureDisplay_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case TEMPERATUREDISPLAY_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case TEMPERATUREDISPLAY_PROP_DISPLAY_TEMPERATURE_UNIT:
        {
            uint8_t display_temperature_unit;
            memset(&display_temperature_unit, 0, sizeof(uint8_t));
            status = TemperatureDisplay_GetDisplayTemperatureUnit(busAttachment, objPath, &display_temperature_unit);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", display_temperature_unit);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TEMPERATUREDISPLAY_PROP_SUPPORTED_DISPLAY_TEMPERATURE_UNITS:
        {
            Array_uint8 supported_display_temperature_units;
            memset(&supported_display_temperature_units, 0, sizeof(Array_uint8));
            status = TemperatureDisplay_GetSupportedDisplayTemperatureUnits(busAttachment, objPath, &supported_display_temperature_units);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "ay", supported_display_temperature_units.elems, sizeof(uint8_t) * supported_display_temperature_units.numElems);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                FreeArray_uint8(&supported_display_temperature_units);
            }
            break;
        }
    }

    return status;
}



static AJ_Status TemperatureDisplay_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case TEMPERATUREDISPLAY_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case TEMPERATUREDISPLAY_PROP_DISPLAY_TEMPERATURE_UNIT:
        {
            uint8_t display_temperature_unit;
            status = AJ_UnmarshalArgs(msg, "y", &display_temperature_unit);
            if (status == AJ_OK) {
                status = TemperatureDisplay_SetDisplayTemperatureUnit(busAttachment, objPath, display_temperature_unit);
                if (status == AJ_OK && emitOnSet) {
                    status = Cdm_TemperatureDisplay_EmitDisplayTemperatureUnitChanged(busAttachment, objPath, display_temperature_unit);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status TemperatureDisplay_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerUserinterfacesettingsTemperatureDisplay = {
    TemperatureDisplay_OnGetProperty,
    TemperatureDisplay_OnSetProperty,
    TemperatureDisplay_OnMethodHandler
};
