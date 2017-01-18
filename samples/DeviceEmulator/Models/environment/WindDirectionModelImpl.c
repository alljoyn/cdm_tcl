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

#include "WindDirectionModelImpl.h"
#include "../../../Utils/HAL.h"


static Element* HAL_Encode_WindDirection_AutoMode(WindDirection_AutoMode value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_WindDirection_AutoMode(WindDirection_AutoMode value, Element* parent)
{
    return HAL_Encode_UInt(value, parent);
}



static void HAL_Decode_WindDirection_AutoMode(Element* elem, uint8_t *value) UNUSED_OK;

static void HAL_Decode_WindDirection_AutoMode(Element* elem, uint8_t *value)
{
    *value = (uint8_t)HAL_Decode_UInt(elem);
}



static Element* HAL_Encode_Array_WindDirection_AutoMode(Array_WindDirection_AutoMode value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_WindDirection_AutoMode(Array_WindDirection_AutoMode value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_WindDirection_AutoMode(Element* elem, Array_WindDirection_AutoMode* value) UNUSED_OK;

static void HAL_Decode_Array_WindDirection_AutoMode(Element* elem, Array_WindDirection_AutoMode* value)
{
    InitArray_WindDirection_AutoMode(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_WindDirection_AutoMode(value, 1);
            value->elems[j] = (uint8_t)HAL_Decode_UInt(elem->children[i]);
        }
    }
}




static AJ_Status GetHorizontalDirection(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "HorizontalDirection");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}



static AJ_Status SetHorizontalDirection(void *context, const char *objPath, uint16_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    Element* elem = HAL_Encode_UInt(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "HorizontalDirection", elem);
    BSXML_FreeElement(elem);

    return result;
}

static AJ_Status GetHorizontalMax(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "HorizontalMax");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}

static AJ_Status GetHorizontalAutoMode(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint8_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "HorizontalAutoMode");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}



static AJ_Status SetHorizontalAutoMode(void *context, const char *objPath, uint8_t input)
{
    AJ_Status result = AJ_OK;
    uint8_t value = input;

    Element* elem = HAL_Encode_UInt(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "HorizontalAutoMode", elem);
    BSXML_FreeElement(elem);

    return result;
}

static AJ_Status GetVerticalDirection(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "VerticalDirection");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}



static AJ_Status SetVerticalDirection(void *context, const char *objPath, uint16_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    Element* elem = HAL_Encode_UInt(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "VerticalDirection", elem);
    BSXML_FreeElement(elem);

    return result;
}

static AJ_Status GetVerticalMax(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "VerticalMax");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}

static AJ_Status GetVerticalAutoMode(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint8_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "VerticalAutoMode");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}



static AJ_Status SetVerticalAutoMode(void *context, const char *objPath, uint8_t input)
{
    AJ_Status result = AJ_OK;
    uint8_t value = input;

    Element* elem = HAL_Encode_UInt(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Environment.WindDirection", "VerticalAutoMode", elem);
    BSXML_FreeElement(elem);

    return result;
}




AJ_Status HandleWindDirectionCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.WindDirection") == 0)
    {
        if (strcmp(cmd->property, "HorizontalDirection") == 0)
        {
            uint16_t value;
            status = GetHorizontalDirection(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                WindDirectionModel* model = (WindDirectionModel*)context;
                status = Cdm_WindDirection_EmitHorizontalDirectionChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "HorizontalMax") == 0)
        {
            uint16_t value;
            status = GetHorizontalMax(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                WindDirectionModel* model = (WindDirectionModel*)context;
                status = Cdm_WindDirection_EmitHorizontalMaxChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "HorizontalAutoMode") == 0)
        {
            uint8_t value;
            status = GetHorizontalAutoMode(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                WindDirectionModel* model = (WindDirectionModel*)context;
                status = Cdm_WindDirection_EmitHorizontalAutoModeChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "VerticalDirection") == 0)
        {
            uint16_t value;
            status = GetVerticalDirection(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                WindDirectionModel* model = (WindDirectionModel*)context;
                status = Cdm_WindDirection_EmitVerticalDirectionChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "VerticalMax") == 0)
        {
            uint16_t value;
            status = GetVerticalMax(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                WindDirectionModel* model = (WindDirectionModel*)context;
                status = Cdm_WindDirection_EmitVerticalMaxChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "VerticalAutoMode") == 0)
        {
            uint8_t value;
            status = GetVerticalAutoMode(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                WindDirectionModel* model = (WindDirectionModel*)context;
                status = Cdm_WindDirection_EmitVerticalAutoModeChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
    }
    return status;
}



static WindDirectionModel model = {
    GetHorizontalDirection
    , SetHorizontalDirection
    , GetHorizontalMax
    , GetHorizontalAutoMode
    , SetHorizontalAutoMode
    , GetVerticalDirection
    , SetVerticalDirection
    , GetVerticalMax
    , GetVerticalAutoMode
    , SetVerticalAutoMode

};


WindDirectionModel *GetWindDirectionModel(void)
{
    return &model;
}
