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

#include "WaterLevelModelImpl.h"
#include "../../../Utils/HAL.h"




static int HAL_Encode_WaterLevel_SupplySource(FILE* fp, WaterLevel_SupplySource value) UNUSED_OK;

static int HAL_Encode_WaterLevel_SupplySource(FILE* fp, WaterLevel_SupplySource value)
{
    HAL_Encode_Int(fp, value);
    return AJ_OK;
}



static int HAL_Decode_WaterLevel_SupplySource(FILE* fp, WaterLevel_SupplySource* value) UNUSED_OK;

static int HAL_Decode_WaterLevel_SupplySource(FILE* fp, WaterLevel_SupplySource* value)
{
    *value = (WaterLevel_SupplySource)(int)HAL_Decode_Int(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_WaterLevel_SupplySource(FILE* fp, Array_WaterLevel_SupplySource value) UNUSED_OK;

static int HAL_Encode_Array_WaterLevel_SupplySource(FILE* fp, Array_WaterLevel_SupplySource value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_WaterLevel_SupplySource(FILE* fp, Array_WaterLevel_SupplySource* value) UNUSED_OK;

static int HAL_Decode_Array_WaterLevel_SupplySource(FILE* fp, Array_WaterLevel_SupplySource* value)
{
    InitArray_WaterLevel_SupplySource(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_WaterLevel_SupplySource(value, 1);
        value->elems[i] = (WaterLevel_SupplySource)(int)HAL_Decode_Int(fp);
    }
    return AJ_OK;
}




static AJ_Status GetSupplySource(void *context, const char *objPath, WaterLevel_SupplySource *out)
{
    AJ_Status result = AJ_OK;
    int value = {0};

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "WaterLevel", "SupplySource");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "WaterLevel", "SupplySource");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        HAL_Encode_Int(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "WaterLevel", "SupplySource");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    value = HAL_Decode_Int(fp);
    *out = (WaterLevel_SupplySource)(int)value;
    fclose(fp);
    return result;
}


static AJ_Status GetCurrentLevel(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "WaterLevel", "CurrentLevel");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "WaterLevel", "CurrentLevel");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "WaterLevel", "CurrentLevel");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetMaxLevel(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "WaterLevel", "MaxLevel");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "WaterLevel", "MaxLevel");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "WaterLevel", "MaxLevel");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
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
