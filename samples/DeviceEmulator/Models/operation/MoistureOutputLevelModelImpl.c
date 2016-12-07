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

#include "MoistureOutputLevelModelImpl.h"
#include "../../../Utils/HAL.h"




static int HAL_Encode_MoistureOutputLevel_AutoMode(FILE* fp, MoistureOutputLevel_AutoMode value) UNUSED_OK;

static int HAL_Encode_MoistureOutputLevel_AutoMode(FILE* fp, MoistureOutputLevel_AutoMode value)
{
    HAL_Encode_Int(fp, value);
    return AJ_OK;
}



static int HAL_Decode_MoistureOutputLevel_AutoMode(FILE* fp, MoistureOutputLevel_AutoMode* value) UNUSED_OK;

static int HAL_Decode_MoistureOutputLevel_AutoMode(FILE* fp, MoistureOutputLevel_AutoMode* value)
{
    *value = (MoistureOutputLevel_AutoMode)(int)HAL_Decode_Int(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_MoistureOutputLevel_AutoMode(FILE* fp, Array_MoistureOutputLevel_AutoMode value) UNUSED_OK;

static int HAL_Encode_Array_MoistureOutputLevel_AutoMode(FILE* fp, Array_MoistureOutputLevel_AutoMode value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_MoistureOutputLevel_AutoMode(FILE* fp, Array_MoistureOutputLevel_AutoMode* value) UNUSED_OK;

static int HAL_Decode_Array_MoistureOutputLevel_AutoMode(FILE* fp, Array_MoistureOutputLevel_AutoMode* value)
{
    InitArray_MoistureOutputLevel_AutoMode(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_MoistureOutputLevel_AutoMode(value, 1);
        value->elems[i] = (MoistureOutputLevel_AutoMode)(int)HAL_Decode_Int(fp);
    }
    return AJ_OK;
}




static AJ_Status GetMoistureOutputLevel(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "MoistureOutputLevel", "MoistureOutputLevel");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "MoistureOutputLevel", "MoistureOutputLevel");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "MoistureOutputLevel", "MoistureOutputLevel");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}



static AJ_Status SetMoistureOutputLevel(void *context, const char *objPath, uint8_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "MoistureOutputLevel", "MoistureOutputLevel");
    HAL_Encode_UInt(fp, value);
    fclose(fp);
    return result;
}


static AJ_Status GetMaxMoistureOutputLevel(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "MoistureOutputLevel", "MaxMoistureOutputLevel");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "MoistureOutputLevel", "MaxMoistureOutputLevel");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        uint64_t const value = {0};
        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "MoistureOutputLevel", "MaxMoistureOutputLevel");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetAutoMode(void *context, const char *objPath, MoistureOutputLevel_AutoMode *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "MoistureOutputLevel", "AutoMode");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "MoistureOutputLevel", "AutoMode");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        int const value = {0};
        HAL_Encode_Int(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "MoistureOutputLevel", "AutoMode");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    int value;
    value = HAL_Decode_Int(fp);
    *out = (MoistureOutputLevel_AutoMode)(int)value;
    fclose(fp);
    return result;
}



static AJ_Status SetAutoMode(void *context, const char *objPath, MoistureOutputLevel_AutoMode input)
{
    AJ_Status result = AJ_OK;
    int value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "MoistureOutputLevel", "AutoMode");
    HAL_Encode_Int(fp, value);
    fclose(fp);
    return result;
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