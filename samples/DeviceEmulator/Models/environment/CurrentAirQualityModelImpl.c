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

#include "CurrentAirQualityModelImpl.h"
#include "../../../Utils/HAL.h"


static Element* HAL_Encode_CurrentAirQuality_ContaminantType(CurrentAirQuality_ContaminantType value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_CurrentAirQuality_ContaminantType(CurrentAirQuality_ContaminantType value, Element* parent)
{
    return HAL_Encode_Int(value, parent);
}



static void HAL_Decode_CurrentAirQuality_ContaminantType(Element* elem, CurrentAirQuality_ContaminantType* value) UNUSED_OK;

static void HAL_Decode_CurrentAirQuality_ContaminantType(Element* elem, CurrentAirQuality_ContaminantType* value)
{
    *value = (CurrentAirQuality_ContaminantType)(int)HAL_Decode_Int(elem);
}



static Element* HAL_Encode_Array_CurrentAirQuality_ContaminantType(Array_CurrentAirQuality_ContaminantType value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_CurrentAirQuality_ContaminantType(Array_CurrentAirQuality_ContaminantType value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        BSXML_AddChild(array, HAL_Encode_Int(value.elems[i], array));
    }
    return array;
}


static void HAL_Decode_Array_CurrentAirQuality_ContaminantType(Element* elem, Array_CurrentAirQuality_ContaminantType* value) UNUSED_OK;

static void HAL_Decode_Array_CurrentAirQuality_ContaminantType(Element* elem, Array_CurrentAirQuality_ContaminantType* value)
{
    InitArray_CurrentAirQuality_ContaminantType(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < value->numElems; ++i) {
            size_t j = ExtendArray_CurrentAirQuality_ContaminantType(value, 1);
            value->elems[j] = (CurrentAirQuality_ContaminantType)(int)HAL_Decode_Int(elem->children[i]);
        }
    }
}




static AJ_Status GetContaminantType(void *context, const char *objPath, CurrentAirQuality_ContaminantType *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "ContaminantType");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    int value;
    value = HAL_Decode_Int(elem);
    *out = (CurrentAirQuality_ContaminantType)(int)value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetCurrentValue(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "CurrentValue");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    double value;
    value = HAL_Decode_Double(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetMinValue(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "MinValue");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    double value;
    value = HAL_Decode_Double(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetMaxValue(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "MaxValue");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    double value;
    value = HAL_Decode_Double(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetPrecision(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "Precision");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    double value;
    value = HAL_Decode_Double(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetUpdateMinTime(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "CurrentAirQuality", "UpdateMinTime");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}




static CurrentAirQualityModel model = {
    GetContaminantType
    , GetCurrentValue
    , GetMinValue
    , GetMaxValue
    , GetPrecision
    , GetUpdateMinTime

};


CurrentAirQualityModel *GetCurrentAirQualityModel(void)
{
    return &model;
}
