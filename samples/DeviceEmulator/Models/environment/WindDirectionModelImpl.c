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

#include "WindDirectionModelImpl.h"
#include "../../../Utils/HAL.h"


static Element* HAL_Encode_WindDirection_AutoMode(WindDirection_AutoMode value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_WindDirection_AutoMode(WindDirection_AutoMode value, Element* parent)
{
    return HAL_Encode_Int(value, parent);
}



static void HAL_Decode_WindDirection_AutoMode(Element* elem, WindDirection_AutoMode* value) UNUSED_OK;

static void HAL_Decode_WindDirection_AutoMode(Element* elem, WindDirection_AutoMode* value)
{
    *value = (WindDirection_AutoMode)(int)HAL_Decode_Int(elem);
}



static Element* HAL_Encode_Array_WindDirection_AutoMode(Array_WindDirection_AutoMode value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_WindDirection_AutoMode(Array_WindDirection_AutoMode value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        BSXML_AddChild(array, HAL_Encode_Int(value.elems[i], array));
    }
    return array;
}


static void HAL_Decode_Array_WindDirection_AutoMode(Element* elem, Array_WindDirection_AutoMode* value) UNUSED_OK;

static void HAL_Decode_Array_WindDirection_AutoMode(Element* elem, Array_WindDirection_AutoMode* value)
{
    InitArray_WindDirection_AutoMode(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < value->numElems; ++i) {
            size_t j = ExtendArray_WindDirection_AutoMode(value, 1);
            value->elems[j] = (WindDirection_AutoMode)(int)HAL_Decode_Int(elem->children[i]);
        }
    }
}




static AJ_Status GetHorizontalDirection(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "WindDirection", "HorizontalDirection");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}



static AJ_Status SetHorizontalDirection(void *context, const char *objPath, uint16_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    Element* elem = HAL_Encode_UInt(value, NULL);
    HAL_WritePropertyElem("/cdm/emulated", "WindDirection", "HorizontalDirection", elem);
    BSXML_FreeElement(elem);

    return result;
}


static AJ_Status GetHorizontalMax(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "WindDirection", "HorizontalMax");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetHorizontalAutoMode(void *context, const char *objPath, WindDirection_AutoMode *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "WindDirection", "HorizontalAutoMode");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    int value;
    value = HAL_Decode_Int(elem);
    *out = (WindDirection_AutoMode)(int)value;

    BSXML_FreeElement(elem);
    return result;
}



static AJ_Status SetHorizontalAutoMode(void *context, const char *objPath, WindDirection_AutoMode input)
{
    AJ_Status result = AJ_OK;
    int value = input;

    Element* elem = HAL_Encode_Int(value, NULL);
    HAL_WritePropertyElem("/cdm/emulated", "WindDirection", "HorizontalAutoMode", elem);
    BSXML_FreeElement(elem);

    return result;
}


static AJ_Status GetVerticalDirection(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "WindDirection", "VerticalDirection");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}



static AJ_Status SetVerticalDirection(void *context, const char *objPath, uint16_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    Element* elem = HAL_Encode_UInt(value, NULL);
    HAL_WritePropertyElem("/cdm/emulated", "WindDirection", "VerticalDirection", elem);
    BSXML_FreeElement(elem);

    return result;
}


static AJ_Status GetVerticalMax(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "WindDirection", "VerticalMax");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetVerticalAutoMode(void *context, const char *objPath, WindDirection_AutoMode *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "WindDirection", "VerticalAutoMode");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    int value;
    value = HAL_Decode_Int(elem);
    *out = (WindDirection_AutoMode)(int)value;

    BSXML_FreeElement(elem);
    return result;
}



static AJ_Status SetVerticalAutoMode(void *context, const char *objPath, WindDirection_AutoMode input)
{
    AJ_Status result = AJ_OK;
    int value = input;

    Element* elem = HAL_Encode_Int(value, NULL);
    HAL_WritePropertyElem("/cdm/emulated", "WindDirection", "VerticalAutoMode", elem);
    BSXML_FreeElement(elem);

    return result;
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
