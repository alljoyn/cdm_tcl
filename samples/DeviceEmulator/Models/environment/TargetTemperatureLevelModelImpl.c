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

#include "TargetTemperatureLevelModelImpl.h"
#include "../../../Utils/HAL.h"






static AJ_Status GetMaxLevel(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "TargetTemperatureLevel", "MaxLevel");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "TargetTemperatureLevel", "MaxLevel");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "TargetTemperatureLevel", "MaxLevel");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetTargetLevel(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "TargetTemperatureLevel", "TargetLevel");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "TargetTemperatureLevel", "TargetLevel");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "TargetTemperatureLevel", "TargetLevel");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}



static AJ_Status SetTargetLevel(void *context, const char *objPath, uint8_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "TargetTemperatureLevel", "TargetLevel");
    HAL_Encode_UInt(fp, value);
    fclose(fp);
    return result;
}


static AJ_Status GetSelectableTemperatureLevels(void *context, const char *objPath, Array_uint8 *out)
{
    AJ_Status result = AJ_OK;
    Array_uint8 value = {0};

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "TargetTemperatureLevel", "SelectableTemperatureLevels");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "TargetTemperatureLevel", "SelectableTemperatureLevels");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        HAL_Encode_Array_uint8(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "TargetTemperatureLevel", "SelectableTemperatureLevels");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    HAL_Decode_Array_uint8(fp, &value);

    *out = value;
    fclose(fp);
    return result;
}




static TargetTemperatureLevelModel model = {
    GetMaxLevel
    , GetTargetLevel
    , SetTargetLevel
    , GetSelectableTemperatureLevels

};


TargetTemperatureLevelModel *GetTargetTemperatureLevelModel(void)
{
    return &model;
}
