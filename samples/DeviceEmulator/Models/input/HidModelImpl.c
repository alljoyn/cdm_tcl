/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "HidModelImpl.h"
#include "../../../Utils/HAL.h"



static Element* HAL_Encode_Hid_InputEvent(Hid_InputEvent value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Hid_InputEvent(Hid_InputEvent value, Element* parent)
{
    Element* struc = BSXML_NewElement("struct", parent);
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "type");
        BSXML_AddChild(field, HAL_Encode_UInt(value.type, field));
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "code");
        BSXML_AddChild(field, HAL_Encode_UInt(value.code, field));
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "value");
        BSXML_AddChild(field, HAL_Encode_Int(value.value, field));
    }
    return struc;
}



static void HAL_Decode_Hid_InputEvent(Element* elem, Hid_InputEvent* value) UNUSED_OK;

static void HAL_Decode_Hid_InputEvent(Element* elem, Hid_InputEvent* value)
{
    if (strcmp(elem->name, "struct") == 0 && elem->numChildren == 3) {
        value->type = HAL_Decode_UInt(elem->children[0]);
        value->code = HAL_Decode_UInt(elem->children[1]);
        value->value = HAL_Decode_Int(elem->children[2]);
    }
}



static Element* HAL_Encode_Array_Hid_InputEvent(Array_Hid_InputEvent value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_Hid_InputEvent(Array_Hid_InputEvent value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        BSXML_AddChild(array, HAL_Encode_Hid_InputEvent(value.elems[i], array));
    }
    return array;
}


static void HAL_Decode_Array_Hid_InputEvent(Element* elem, Array_Hid_InputEvent* value) UNUSED_OK;

static void HAL_Decode_Array_Hid_InputEvent(Element* elem, Array_Hid_InputEvent* value)
{
    InitArray_Hid_InputEvent(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < value->numElems; ++i) {
            size_t j = ExtendArray_Hid_InputEvent(value, 1);
            HAL_Decode_Hid_InputEvent(elem->children[i], &value->elems[j]);
        }
    }
}



static Element* HAL_Encode_Hid_SupportedInputEvent(Hid_SupportedInputEvent value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Hid_SupportedInputEvent(Hid_SupportedInputEvent value, Element* parent)
{
    Element* struc = BSXML_NewElement("struct", parent);
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "type");
        BSXML_AddChild(field, HAL_Encode_UInt(value.type, field));
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "code");
        BSXML_AddChild(field, HAL_Encode_UInt(value.code, field));
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "min");
        BSXML_AddChild(field, HAL_Encode_Int(value.min, field));
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "max");
        BSXML_AddChild(field, HAL_Encode_Int(value.max, field));
    }
    return struc;
}



static void HAL_Decode_Hid_SupportedInputEvent(Element* elem, Hid_SupportedInputEvent* value) UNUSED_OK;

static void HAL_Decode_Hid_SupportedInputEvent(Element* elem, Hid_SupportedInputEvent* value)
{
    if (strcmp(elem->name, "struct") == 0 && elem->numChildren == 4) {
        value->type = HAL_Decode_UInt(elem->children[0]);
        value->code = HAL_Decode_UInt(elem->children[1]);
        value->min = HAL_Decode_Int(elem->children[2]);
        value->max = HAL_Decode_Int(elem->children[3]);
    }
}



static Element* HAL_Encode_Array_Hid_SupportedInputEvent(Array_Hid_SupportedInputEvent value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_Hid_SupportedInputEvent(Array_Hid_SupportedInputEvent value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        BSXML_AddChild(array, HAL_Encode_Hid_SupportedInputEvent(value.elems[i], array));
    }
    return array;
}


static void HAL_Decode_Array_Hid_SupportedInputEvent(Element* elem, Array_Hid_SupportedInputEvent* value) UNUSED_OK;

static void HAL_Decode_Array_Hid_SupportedInputEvent(Element* elem, Array_Hid_SupportedInputEvent* value)
{
    InitArray_Hid_SupportedInputEvent(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < value->numElems; ++i) {
            size_t j = ExtendArray_Hid_SupportedInputEvent(value, 1);
            HAL_Decode_Hid_SupportedInputEvent(elem->children[i], &value->elems[j]);
        }
    }
}




static AJ_Status GetSupportedEvents(void *context, const char *objPath, Array_Hid_SupportedInputEvent *out)
{
    AJ_Status result = AJ_OK;
    Array_Hid_SupportedInputEvent value = {0};

    Element* elem = HAL_ReadProperty("/cdm/emulated", "org.alljoyn.Input.Hid", "SupportedEvents");

    if (elem) {
        HAL_Decode_Array_Hid_SupportedInputEvent(elem, &value);

        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




static AJ_Status MethodInjectEvents(void *context, const char *objPath, Array_Hid_InputEvent inputEvents)
{
    // TODO
    return AJ_ERR_FAILURE;
}



static HidModel model = {
    GetSupportedEvents

    , MethodInjectEvents
};


HidModel *GetHidModel(void)
{
    return &model;
}