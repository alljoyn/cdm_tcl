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

#include "TimerModelImpl.h"
#include "../../../Utils/HAL.h"




static AJ_Status GetReferenceTimer(void *context, const char *objPath, int32_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "Timer", "ReferenceTimer");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    int64_t value;
    value = HAL_Decode_Int(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetTargetTimeToStart(void *context, const char *objPath, int32_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "Timer", "TargetTimeToStart");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    int64_t value;
    value = HAL_Decode_Int(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetTargetTimeToStop(void *context, const char *objPath, int32_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "Timer", "TargetTimeToStop");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    int64_t value;
    value = HAL_Decode_Int(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetEstimatedTimeToEnd(void *context, const char *objPath, int32_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "Timer", "EstimatedTimeToEnd");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    int64_t value;
    value = HAL_Decode_Int(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetRunningTime(void *context, const char *objPath, int32_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "Timer", "RunningTime");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    int64_t value;
    value = HAL_Decode_Int(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetTargetDuration(void *context, const char *objPath, int32_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "Timer", "TargetDuration");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    int64_t value;
    value = HAL_Decode_Int(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}




static AJ_Status MethodSetTargetTimeToStart(void *context, const char *objPath, int32_t targetTimeToStart)
{
    Element* elem = HAL_Encode_Int(targetTimeToStart, NULL);
    HAL_WritePropertyElem(objPath, "Timer", "SetTargetTimeToStart", elem);
    BSXML_FreeElement(elem);
    return AJ_OK;
}



static AJ_Status MethodSetTargetTimeToStop(void *context, const char *objPath, int32_t targetTimeToStop)
{
    Element* elem = HAL_Encode_Int(targetTimeToStop, NULL);
    HAL_WritePropertyElem(objPath, "Timer", "SetTargetTimeToStop", elem);
    BSXML_FreeElement(elem);
    return AJ_OK;
}



static TimerModel model = {
    GetReferenceTimer
    , GetTargetTimeToStart
    , GetTargetTimeToStop
    , GetEstimatedTimeToEnd
    , GetRunningTime
    , GetTargetDuration

    , MethodSetTargetTimeToStart
    , MethodSetTargetTimeToStop
};


TimerModel *GetTimerModel(void)
{
    return &model;
}
