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

#include "EnergyUsageModelImpl.h"
#include "../../../Utils/HAL.h"






static AJ_Status GetCumulativeEnergy(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;
    double value = {0};

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "EnergyUsage", "CumulativeEnergy");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "EnergyUsage", "CumulativeEnergy");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        HAL_Encode_Double(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "EnergyUsage", "CumulativeEnergy");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    value = HAL_Decode_Double(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetPrecision(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;
    double value = {0};

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "EnergyUsage", "Precision");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "EnergyUsage", "Precision");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        HAL_Encode_Double(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "EnergyUsage", "Precision");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    value = HAL_Decode_Double(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetUpdateMinTime(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "EnergyUsage", "UpdateMinTime");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "EnergyUsage", "UpdateMinTime");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "EnergyUsage", "UpdateMinTime");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}




static AJ_Status MethodResetCumulativeEnergy(void *context, const char *objPath)
{
    FILE* fp = HAL_WriteProperty("/cdm/emulated", "EnergyUsage", "CumulativeEnergy");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    HAL_Encode_Double(fp, 0);
    fclose(fp);

}



static EnergyUsageModel model = {
    GetCumulativeEnergy
    , GetPrecision
    , GetUpdateMinTime

    , MethodResetCumulativeEnergy
};


EnergyUsageModel *GetEnergyUsageModel(void)
{
    return &model;
}
