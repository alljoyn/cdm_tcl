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

#include "WaterLevelModelImpl.h"
#include "../../../Utils/HAL.h"


static Element* HAL_Encode_WaterLevel_SupplySource(WaterLevel_SupplySource value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_WaterLevel_SupplySource(WaterLevel_SupplySource value, Element* parent)
{
    return HAL_Encode_Int(value, parent);
}



static void HAL_Decode_WaterLevel_SupplySource(Element* elem, WaterLevel_SupplySource* value) UNUSED_OK;

static void HAL_Decode_WaterLevel_SupplySource(Element* elem, WaterLevel_SupplySource* value)
{
    *value = (WaterLevel_SupplySource)(int)HAL_Decode_Int(elem);
}



static Element* HAL_Encode_Array_WaterLevel_SupplySource(Array_WaterLevel_SupplySource value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_WaterLevel_SupplySource(Array_WaterLevel_SupplySource value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        BSXML_AddChild(array, HAL_Encode_Int(value.elems[i], array));
    }
    return array;
}


static void HAL_Decode_Array_WaterLevel_SupplySource(Element* elem, Array_WaterLevel_SupplySource* value) UNUSED_OK;

static void HAL_Decode_Array_WaterLevel_SupplySource(Element* elem, Array_WaterLevel_SupplySource* value)
{
    InitArray_WaterLevel_SupplySource(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < value->numElems; ++i) {
            size_t j = ExtendArray_WaterLevel_SupplySource(value, 1);
            value->elems[j] = (WaterLevel_SupplySource)(int)HAL_Decode_Int(elem->children[i]);
        }
    }
}




static AJ_Status GetSupplySource(void *context, const char *objPath, WaterLevel_SupplySource *out)
{
    AJ_Status result = AJ_OK;
    int value = {0};

    Element* elem = HAL_ReadProperty("/cdm/emulated", "org.alljoyn.SmartSpaces.Environment.WaterLevel", "SupplySource");

    if (elem) {
        value = HAL_Decode_Int(elem);
        BSXML_FreeElement(elem);
    }

    *out = (WaterLevel_SupplySource)(int)value;
    return result;
}


static AJ_Status GetCurrentLevel(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty("/cdm/emulated", "org.alljoyn.SmartSpaces.Environment.WaterLevel", "CurrentLevel");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}


static AJ_Status GetMaxLevel(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty("/cdm/emulated", "org.alljoyn.SmartSpaces.Environment.WaterLevel", "MaxLevel");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




static WaterLevelModel model = {
    GetSupplySource
    , GetCurrentLevel
    , GetMaxLevel

};


WaterLevelModel *GetWaterLevelModel(void)
{
    return &model;
}