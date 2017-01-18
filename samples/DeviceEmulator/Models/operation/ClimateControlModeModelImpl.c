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

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "ClimateControlModeModelImpl.h"
#include "../../../Utils/HAL.h"


static Element* HAL_Encode_ClimateControlMode_Mode(ClimateControlMode_Mode value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_ClimateControlMode_Mode(ClimateControlMode_Mode value, Element* parent)
{
    return HAL_Encode_UInt(value, parent);
}



static void HAL_Decode_ClimateControlMode_Mode(Element* elem, uint16_t *value) UNUSED_OK;

static void HAL_Decode_ClimateControlMode_Mode(Element* elem, uint16_t *value)
{
    *value = (uint16_t)HAL_Decode_UInt(elem);
}



static Element* HAL_Encode_Array_ClimateControlMode_Mode(Array_ClimateControlMode_Mode value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_ClimateControlMode_Mode(Array_ClimateControlMode_Mode value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_ClimateControlMode_Mode(Element* elem, Array_ClimateControlMode_Mode* value) UNUSED_OK;

static void HAL_Decode_Array_ClimateControlMode_Mode(Element* elem, Array_ClimateControlMode_Mode* value)
{
    InitArray_ClimateControlMode_Mode(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_ClimateControlMode_Mode(value, 1);
            value->elems[j] = (uint16_t)HAL_Decode_UInt(elem->children[i]);
        }
    }
}


static Element* HAL_Encode_ClimateControlMode_OperationalState(ClimateControlMode_OperationalState value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_ClimateControlMode_OperationalState(ClimateControlMode_OperationalState value, Element* parent)
{
    return HAL_Encode_UInt(value, parent);
}



static void HAL_Decode_ClimateControlMode_OperationalState(Element* elem, uint16_t *value) UNUSED_OK;

static void HAL_Decode_ClimateControlMode_OperationalState(Element* elem, uint16_t *value)
{
    *value = (uint16_t)HAL_Decode_UInt(elem);
}



static Element* HAL_Encode_Array_ClimateControlMode_OperationalState(Array_ClimateControlMode_OperationalState value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_ClimateControlMode_OperationalState(Array_ClimateControlMode_OperationalState value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_ClimateControlMode_OperationalState(Element* elem, Array_ClimateControlMode_OperationalState* value) UNUSED_OK;

static void HAL_Decode_Array_ClimateControlMode_OperationalState(Element* elem, Array_ClimateControlMode_OperationalState* value)
{
    InitArray_ClimateControlMode_OperationalState(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_ClimateControlMode_OperationalState(value, 1);
            value->elems[j] = (uint16_t)HAL_Decode_UInt(elem->children[i]);
        }
    }
}




static AJ_Status GetMode(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint16_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.ClimateControlMode", "Mode");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}



static AJ_Status SetMode(void *context, const char *objPath, uint16_t input)
{
    AJ_Status result = AJ_OK;
    uint16_t value = input;

    Element* elem = HAL_Encode_UInt(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.ClimateControlMode", "Mode", elem);
    BSXML_FreeElement(elem);

    return result;
}

static AJ_Status GetSupportedModes(void *context, const char *objPath, Array_ClimateControlMode_Mode *out)
{
    AJ_Status result = AJ_OK;
    Array_ClimateControlMode_Mode value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.ClimateControlMode", "SupportedModes");

    if (elem) {
        HAL_Decode_Array_ClimateControlMode_Mode(elem, &value);

        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}

static AJ_Status GetOperationalState(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint16_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.ClimateControlMode", "OperationalState");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




AJ_Status HandleClimateControlModeCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.ClimateControlMode") == 0)
    {
        if (strcmp(cmd->property, "Mode") == 0)
        {
            uint16_t value;
            status = GetMode(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                ClimateControlModeModel* model = (ClimateControlModeModel*)context;
                status = Cdm_ClimateControlMode_EmitModeChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "SupportedModes") == 0)
        {
            Array_ClimateControlMode_Mode value;
            status = GetSupportedModes(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                ClimateControlModeModel* model = (ClimateControlModeModel*)context;
                status = Cdm_ClimateControlMode_EmitSupportedModesChanged(model->busAttachment, cmd->objPath, value);
            }
            FreeArray_ClimateControlMode_Mode(&value);
        }
        if (strcmp(cmd->property, "OperationalState") == 0)
        {
            uint16_t value;
            status = GetOperationalState(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                ClimateControlModeModel* model = (ClimateControlModeModel*)context;
                status = Cdm_ClimateControlMode_EmitOperationalStateChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
    }
    return status;
}



static ClimateControlModeModel model = {
    GetMode
    , SetMode
    , GetSupportedModes
    , GetOperationalState

};


ClimateControlModeModel *GetClimateControlModeModel(void)
{
    return &model;
}
