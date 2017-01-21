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

#include "MoistureOutputLevelModelImpl.h"
#include "../../../Utils/HAL.h"


static Element* HAL_Encode_MoistureOutputLevel_AutoMode(MoistureOutputLevel_AutoMode value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_MoistureOutputLevel_AutoMode(MoistureOutputLevel_AutoMode value, Element* parent)
{
    return HAL_Encode_UInt(value, parent);
}



static void HAL_Decode_MoistureOutputLevel_AutoMode(Element* elem, uint8_t *value) UNUSED_OK;

static void HAL_Decode_MoistureOutputLevel_AutoMode(Element* elem, uint8_t *value)
{
    *value = (uint8_t)HAL_Decode_UInt(elem);
}



static Element* HAL_Encode_Array_MoistureOutputLevel_AutoMode(Array_MoistureOutputLevel_AutoMode value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_MoistureOutputLevel_AutoMode(Array_MoistureOutputLevel_AutoMode value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    size_t i = 0;
    for (; i < value.numElems; ++i) {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_MoistureOutputLevel_AutoMode(Element* elem, Array_MoistureOutputLevel_AutoMode* value) UNUSED_OK;

static void HAL_Decode_Array_MoistureOutputLevel_AutoMode(Element* elem, Array_MoistureOutputLevel_AutoMode* value)
{
    InitArray_MoistureOutputLevel_AutoMode(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        size_t i = 0;
        for (; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_MoistureOutputLevel_AutoMode(value, 1);
            value->elems[j] = (uint8_t)HAL_Decode_UInt(elem->children[i]);
        }
    }
}




static AJ_Status GetMoistureOutputLevel(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel", "MoistureOutputLevel");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}



static AJ_Status SetMoistureOutputLevel(void *context, const char *objPath, uint8_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    Element* elem = HAL_Encode_UInt(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel", "MoistureOutputLevel", elem);
    BSXML_FreeElement(elem);

    return result;
}

static AJ_Status GetMaxMoistureOutputLevel(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel", "MaxMoistureOutputLevel");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}

static AJ_Status GetAutoMode(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint8_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel", "AutoMode");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}



static AJ_Status SetAutoMode(void *context, const char *objPath, uint8_t input)
{
    AJ_Status result = AJ_OK;
    uint8_t value = input;

    Element* elem = HAL_Encode_UInt(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel", "AutoMode", elem);
    BSXML_FreeElement(elem);

    return result;
}




AJ_Status HandleMoistureOutputLevelCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel") == 0)
    {
        if (strcmp(cmd->property, "MoistureOutputLevel") == 0)
        {
            uint8_t value;
            status = GetMoistureOutputLevel(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                MoistureOutputLevelModel* model = (MoistureOutputLevelModel*)context;
                status = Cdm_MoistureOutputLevel_EmitMoistureOutputLevelChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "MaxMoistureOutputLevel") == 0)
        {
            uint8_t value;
            status = GetMaxMoistureOutputLevel(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                MoistureOutputLevelModel* model = (MoistureOutputLevelModel*)context;
                status = Cdm_MoistureOutputLevel_EmitMaxMoistureOutputLevelChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "AutoMode") == 0)
        {
            uint8_t value;
            status = GetAutoMode(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                MoistureOutputLevelModel* model = (MoistureOutputLevelModel*)context;
                status = Cdm_MoistureOutputLevel_EmitAutoModeChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
    }
    return status;
}



static MoistureOutputLevelModel model = {
    GetMoistureOutputLevel
    , SetMoistureOutputLevel
    , GetMaxMoistureOutputLevel
    , GetAutoMode
    , SetAutoMode

};


MoistureOutputLevelModel *GetMoistureOutputLevelModel(void)
{
    return &model;
}
