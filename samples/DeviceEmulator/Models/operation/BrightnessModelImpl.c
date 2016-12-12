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

#include "BrightnessModelImpl.h"
#include "../../../Utils/HAL.h"






static AJ_Status GetBrightness(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "Brightness", "Brightness");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "Brightness", "Brightness");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        double const value = {0};
        HAL_Encode_Double(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "Brightness", "Brightness");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    double value;
    value = HAL_Decode_Double(fp);
    *out = value;
    fclose(fp);
    return result;
}



static AJ_Status SetBrightness(void *context, const char *objPath, double input)
{
    AJ_Status result = AJ_OK;
    double value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "Brightness", "Brightness");
    HAL_Encode_Double(fp, value);
    fclose(fp);
    return result;
}




static BrightnessModel model = {
    GetBrightness
    , SetBrightness

};


BrightnessModel *GetBrightnessModel(void)
{
    return &model;
}
