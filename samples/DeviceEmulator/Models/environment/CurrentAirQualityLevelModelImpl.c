/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "CurrentAirQualityLevelModelImpl.h"
#include "../../../Utils/HAL.h"


static Element* HAL_Encode_CurrentAirQualityLevel_ContaminantType(CurrentAirQualityLevel_ContaminantType value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_CurrentAirQualityLevel_ContaminantType(CurrentAirQualityLevel_ContaminantType value, Element* parent)
{
    return HAL_Encode_Int(value, parent);
}



static void HAL_Decode_CurrentAirQualityLevel_ContaminantType(Element* elem, CurrentAirQualityLevel_ContaminantType* value) UNUSED_OK;

static void HAL_Decode_CurrentAirQualityLevel_ContaminantType(Element* elem, CurrentAirQualityLevel_ContaminantType* value)
{
    *value = (CurrentAirQualityLevel_ContaminantType)(int)HAL_Decode_Int(elem);
}



static Element* HAL_Encode_Array_CurrentAirQualityLevel_ContaminantType(Array_CurrentAirQualityLevel_ContaminantType value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_CurrentAirQualityLevel_ContaminantType(Array_CurrentAirQualityLevel_ContaminantType value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        BSXML_AddChild(array, HAL_Encode_Int(value.elems[i], array));
    }
    return array;
}


static void HAL_Decode_Array_CurrentAirQualityLevel_ContaminantType(Element* elem, Array_CurrentAirQualityLevel_ContaminantType* value) UNUSED_OK;

static void HAL_Decode_Array_CurrentAirQualityLevel_ContaminantType(Element* elem, Array_CurrentAirQualityLevel_ContaminantType* value)
{
    InitArray_CurrentAirQualityLevel_ContaminantType(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < value->numElems; ++i) {
            size_t j = ExtendArray_CurrentAirQualityLevel_ContaminantType(value, 1);
            value->elems[j] = (CurrentAirQualityLevel_ContaminantType)(int)HAL_Decode_Int(elem->children[i]);
        }
    }
}




static AJ_Status GetContaminantType(void *context, const char *objPath, CurrentAirQualityLevel_ContaminantType *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "CurrentAirQualityLevel", "ContaminantType");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    int value;
    value = HAL_Decode_Int(elem);
    *out = (CurrentAirQualityLevel_ContaminantType)(int)value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetCurrentLevel(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "CurrentAirQualityLevel", "CurrentLevel");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetMaxLevel(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "CurrentAirQualityLevel", "MaxLevel");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}




static CurrentAirQualityLevelModel model = {
    GetContaminantType
    , GetCurrentLevel
    , GetMaxLevel

};


CurrentAirQualityLevelModel *GetCurrentAirQualityLevelModel(void)
{
    return &model;
}
