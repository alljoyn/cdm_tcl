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

#include "LanguageDisplayModelImpl.h"
#include "../../../Utils/HAL.h"




static AJ_Status GetDisplayLanguage(void *context, const char *objPath, char const* *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "LanguageDisplay", "DisplayLanguage");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    char const* value;
    value = HAL_Decode_String(elem);
    *out = value;

    BSXML_FreeElement(elem);
    return result;
}



static AJ_Status SetDisplayLanguage(void *context, const char *objPath, char const* input)
{
    AJ_Status result = AJ_OK;
    char const* value = input;

    Element* elem = HAL_Encode_String(value, NULL);
    HAL_WritePropertyElem("/cdm/emulated", "LanguageDisplay", "DisplayLanguage", elem);
    BSXML_FreeElement(elem);

    return result;
}


static AJ_Status GetSupportedDisplayLanguages(void *context, const char *objPath, Array_string *out)
{
    AJ_Status result = AJ_OK;

    Element* elem = HAL_ReadProperty("/cdm/emulated", "LanguageDisplay", "SupportedDisplayLanguages");

    if (!elem) {
        return AJ_ERR_FAILURE;
    }

    Array_string value;
    HAL_Decode_Array_string(elem, &value);

    *out = value;

    BSXML_FreeElement(elem);
    return result;
}




static LanguageDisplayModel model = {
    GetDisplayLanguage
    , SetDisplayLanguage
    , GetSupportedDisplayLanguages

};


LanguageDisplayModel *GetLanguageDisplayModel(void)
{
    return &model;
}
