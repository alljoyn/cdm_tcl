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

#include "HvacFanModeModelImpl.h"
#include "../../../Utils/HAL.h"


static Element* HAL_Encode_HvacFanMode_Mode(HvacFanMode_Mode value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_HvacFanMode_Mode(HvacFanMode_Mode value, Element* parent)
{
    return HAL_Encode_UInt(value, parent);
}



static void HAL_Decode_HvacFanMode_Mode(Element* elem, uint16_t *value) UNUSED_OK;

static void HAL_Decode_HvacFanMode_Mode(Element* elem, uint16_t *value)
{
    *value = (uint16_t)HAL_Decode_UInt(elem);
}



static Element* HAL_Encode_Array_HvacFanMode_Mode(Array_HvacFanMode_Mode value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_HvacFanMode_Mode(Array_HvacFanMode_Mode value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    size_t i = 0;
    for (; i < value.numElems; ++i) {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_HvacFanMode_Mode(Element* elem, Array_HvacFanMode_Mode* value) UNUSED_OK;

static void HAL_Decode_Array_HvacFanMode_Mode(Element* elem, Array_HvacFanMode_Mode* value)
{
    InitArray_HvacFanMode_Mode(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        size_t i = 0;
        for (; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_HvacFanMode_Mode(value, 1);
            value->elems[j] = (uint16_t)HAL_Decode_UInt(elem->children[i]);
        }
    }
}




static AJ_Status GetMode(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint16_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.HvacFanMode", "Mode");

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
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.HvacFanMode", "Mode", elem);
    BSXML_FreeElement(elem);

    return result;
}

static AJ_Status GetSupportedModes(void *context, const char *objPath, Array_HvacFanMode_Mode *out)
{
    AJ_Status result = AJ_OK;
    Array_HvacFanMode_Mode value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.HvacFanMode", "SupportedModes");

    if (elem) {
        HAL_Decode_Array_HvacFanMode_Mode(elem, &value);

        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




AJ_Status HandleHvacFanModeCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.HvacFanMode") == 0)
    {
        if (strcmp(cmd->property, "Mode") == 0)
        {
            uint16_t value;
            status = GetMode(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                HvacFanModeModel* model = (HvacFanModeModel*)context;
                status = Cdm_HvacFanMode_EmitModeChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "SupportedModes") == 0)
        {
            Array_HvacFanMode_Mode value;
            status = GetSupportedModes(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                HvacFanModeModel* model = (HvacFanModeModel*)context;
                status = Cdm_HvacFanMode_EmitSupportedModesChanged(model->busAttachment, cmd->objPath, value);
            }
            FreeArray_HvacFanMode_Mode(&value);
        }
    }
    return status;
}



static HvacFanModeModel model = {
    GetMode
    , SetMode
    , GetSupportedModes

};


HvacFanModeModel *GetHvacFanModeModel(void)
{
    return &model;
}
