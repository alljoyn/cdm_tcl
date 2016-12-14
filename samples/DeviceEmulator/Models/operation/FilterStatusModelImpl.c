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

#include "FilterStatusModelImpl.h"
#include "../../../Utils/HAL.h"




static AJ_Status GetExpectedLifeInDays(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "FilterStatus", "ExpectedLifeInDays");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetIsCleanable(void *context, const char *objPath, bool *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "FilterStatus", "IsCleanable");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    int64_t value;
    value = HAL_Decode_Int(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetOrderPercentage(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "FilterStatus", "OrderPercentage");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetManufacturer(void *context, const char *objPath, char const* *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "FilterStatus", "Manufacturer");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    char const* value;
    value = HAL_Decode_String(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetPartNumber(void *context, const char *objPath, char const* *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "FilterStatus", "PartNumber");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    char const* value;
    value = HAL_Decode_String(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetUrl(void *context, const char *objPath, char const* *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "FilterStatus", "Url");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    char const* value;
    value = HAL_Decode_String(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}


static AJ_Status GetLifeRemaining(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "FilterStatus", "LifeRemaining");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    uint64_t value;
    value = HAL_Decode_UInt(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}




static FilterStatusModel model = {
    GetExpectedLifeInDays
    , GetIsCleanable
    , GetOrderPercentage
    , GetManufacturer
    , GetPartNumber
    , GetUrl
    , GetLifeRemaining

};


FilterStatusModel *GetFilterStatusModel(void)
{
    return &model;
}
