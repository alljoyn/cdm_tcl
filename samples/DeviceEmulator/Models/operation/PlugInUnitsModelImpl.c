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

#include "PlugInUnitsModelImpl.h"
#include "../../../Utils/HAL.h"



static Element* HAL_Encode_PlugInUnits_PlugInInfo(PlugInUnits_PlugInInfo value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_PlugInUnits_PlugInInfo(PlugInUnits_PlugInInfo value, Element* parent)
{
    Element* struc = BSXML_NewElement("struct", parent);
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "objectPath");
        HAL_Encode_String(value.objectPath, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "deviceId");
        HAL_Encode_UInt(value.deviceId, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "pluggedIn");
        HAL_Encode_Bool(value.pluggedIn, field);
    }
    return struc;
}



static void HAL_Decode_PlugInUnits_PlugInInfo(Element* elem, PlugInUnits_PlugInInfo* value) UNUSED_OK;

static void HAL_Decode_PlugInUnits_PlugInInfo(Element* elem, PlugInUnits_PlugInInfo* value)
{
    if (strcmp(elem->name, "struct") == 0 && elem->numChildren == 3) {
        value->objectPath = HAL_Decode_String(elem->children[0]->children[0]);
        value->deviceId = HAL_Decode_UInt(elem->children[1]->children[0]);
        value->pluggedIn = HAL_Decode_Bool(elem->children[2]->children[0]);
    }
}



static Element* HAL_Encode_Array_PlugInUnits_PlugInInfo(Array_PlugInUnits_PlugInInfo value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_PlugInUnits_PlugInInfo(Array_PlugInUnits_PlugInInfo value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_PlugInUnits_PlugInInfo(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_PlugInUnits_PlugInInfo(Element* elem, Array_PlugInUnits_PlugInInfo* value) UNUSED_OK;

static void HAL_Decode_Array_PlugInUnits_PlugInInfo(Element* elem, Array_PlugInUnits_PlugInInfo* value)
{
    InitArray_PlugInUnits_PlugInInfo(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_PlugInUnits_PlugInInfo(value, 1);
            HAL_Decode_PlugInUnits_PlugInInfo(elem->children[i], &value->elems[j]);
        }
    }
}



static AJ_Status GetPlugInUnits(void *context, const char *objPath, Array_PlugInUnits_PlugInInfo *out)
{
    AJ_Status result = AJ_OK;
    Array_PlugInUnits_PlugInInfo value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.PlugInUnits", "PlugInUnits");

    if (elem) {
        HAL_Decode_Array_PlugInUnits_PlugInInfo(elem, &value);

        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




static PlugInUnitsModel model = {
    GetPlugInUnits

};


PlugInUnitsModel *GetPlugInUnitsModel(void)
{
    return &model;
}
