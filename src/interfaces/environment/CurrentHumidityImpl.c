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
#include <ajtcl/cdm/interfaces/environment/CurrentHumidityInterface.h>
#include <ajtcl/cdm/interfaces/environment/CurrentHumidityModel.h>

#include <ajtcl/cdm/utils/CdmArray.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME CURRENT_HUMIDITY

const char* const intfDescEnvironmentCurrentHumidity[] = {
    "$org.alljoyn.SmartSpaces.Environment.CurrentHumidity",
    "@Version>q",
    "@CurrentValue>y",
    "@MaxValue>y",
    NULL
};




static AJ_Status CurrentHumidity_GetCurrentValue(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentHumidityModel* model = (CurrentHumidityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetCurrentValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetCurrentValue(model, objPath, out);
}



AJ_Status Cdm_CurrentHumidity_EmitCurrentValueChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "CurrentValue", "y", newValue);
}



static AJ_Status CurrentHumidity_GetMaxValue(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CurrentHumidityModel* model = (CurrentHumidityModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxValue(model, objPath, out);
}



AJ_Status Cdm_CurrentHumidity_EmitMaxValueChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MaxValue", "y", newValue);
}




/*
   Handler functions
*/
static AJ_Status CurrentHumidity_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CURRENTHUMIDITY_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case CURRENTHUMIDITY_PROP_CURRENT_VALUE:
        {
            uint8_t current_value;
            memset(&current_value, 0, sizeof(uint8_t));
            status = CurrentHumidity_GetCurrentValue(busAttachment, objPath, &current_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", current_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CURRENTHUMIDITY_PROP_MAX_VALUE:
        {
            uint8_t max_value;
            memset(&max_value, 0, sizeof(uint8_t));
            status = CurrentHumidity_GetMaxValue(busAttachment, objPath, &max_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", max_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status CurrentHumidity_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CURRENTHUMIDITY_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status CurrentHumidity_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerEnvironmentCurrentHumidity = {
    CurrentHumidity_OnGetProperty,
    CurrentHumidity_OnSetProperty,
    CurrentHumidity_OnMethodHandler
};
