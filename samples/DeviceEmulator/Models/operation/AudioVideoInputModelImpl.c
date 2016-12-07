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

#include "AudioVideoInputModelImpl.h"
#include "../../../Utils/HAL.h"





static int HAL_Encode_AudioVideoInput_InputSource(FILE* fp, AudioVideoInput_InputSource value) UNUSED_OK;

static int HAL_Encode_AudioVideoInput_InputSource(FILE* fp, AudioVideoInput_InputSource value)
{
    HAL_Encode_OpenStruct(fp);
    HAL_Encode_UInt(fp, value.id);
    HAL_Encode_Int(fp, value.sourceType);
    HAL_Encode_Int(fp, value.signalPresence);
    HAL_Encode_UInt(fp, value.portNumber);
    HAL_Encode_String(fp, value.friendlyName);
    HAL_Encode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Decode_AudioVideoInput_InputSource(FILE* fp, AudioVideoInput_InputSource* value) UNUSED_OK;

static int HAL_Decode_AudioVideoInput_InputSource(FILE* fp, AudioVideoInput_InputSource* value)
{
    HAL_Decode_OpenStruct(fp);
    value->id = HAL_Decode_UInt(fp);
    value->sourceType = HAL_Decode_Int(fp);
    value->signalPresence = HAL_Decode_Int(fp);
    value->portNumber = HAL_Decode_UInt(fp);
    value->friendlyName = HAL_Decode_String(fp);
    HAL_Decode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_AudioVideoInput_InputSource(FILE* fp, Array_AudioVideoInput_InputSource value) UNUSED_OK;

static int HAL_Encode_Array_AudioVideoInput_InputSource(FILE* fp, Array_AudioVideoInput_InputSource value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_AudioVideoInput_InputSource(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_AudioVideoInput_InputSource(FILE* fp, Array_AudioVideoInput_InputSource* value) UNUSED_OK;

static int HAL_Decode_Array_AudioVideoInput_InputSource(FILE* fp, Array_AudioVideoInput_InputSource* value)
{
    InitArray_AudioVideoInput_InputSource(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_AudioVideoInput_InputSource(value, 1);
        HAL_Decode_AudioVideoInput_InputSource(fp, &value->elems[i]);
    }
    return AJ_OK;
}


static int HAL_Encode_AudioVideoInput_SourceType(FILE* fp, AudioVideoInput_SourceType value) UNUSED_OK;

static int HAL_Encode_AudioVideoInput_SourceType(FILE* fp, AudioVideoInput_SourceType value)
{
    HAL_Encode_Int(fp, value);
    return AJ_OK;
}



static int HAL_Decode_AudioVideoInput_SourceType(FILE* fp, AudioVideoInput_SourceType* value) UNUSED_OK;

static int HAL_Decode_AudioVideoInput_SourceType(FILE* fp, AudioVideoInput_SourceType* value)
{
    *value = (AudioVideoInput_SourceType)(int)HAL_Decode_Int(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_AudioVideoInput_SourceType(FILE* fp, Array_AudioVideoInput_SourceType value) UNUSED_OK;

static int HAL_Encode_Array_AudioVideoInput_SourceType(FILE* fp, Array_AudioVideoInput_SourceType value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_AudioVideoInput_SourceType(FILE* fp, Array_AudioVideoInput_SourceType* value) UNUSED_OK;

static int HAL_Decode_Array_AudioVideoInput_SourceType(FILE* fp, Array_AudioVideoInput_SourceType* value)
{
    InitArray_AudioVideoInput_SourceType(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_AudioVideoInput_SourceType(value, 1);
        value->elems[i] = (AudioVideoInput_SourceType)(int)HAL_Decode_Int(fp);
    }
    return AJ_OK;
}


static int HAL_Encode_AudioVideoInput_SignalPresence(FILE* fp, AudioVideoInput_SignalPresence value) UNUSED_OK;

static int HAL_Encode_AudioVideoInput_SignalPresence(FILE* fp, AudioVideoInput_SignalPresence value)
{
    HAL_Encode_Int(fp, value);
    return AJ_OK;
}



static int HAL_Decode_AudioVideoInput_SignalPresence(FILE* fp, AudioVideoInput_SignalPresence* value) UNUSED_OK;

static int HAL_Decode_AudioVideoInput_SignalPresence(FILE* fp, AudioVideoInput_SignalPresence* value)
{
    *value = (AudioVideoInput_SignalPresence)(int)HAL_Decode_Int(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_AudioVideoInput_SignalPresence(FILE* fp, Array_AudioVideoInput_SignalPresence value) UNUSED_OK;

static int HAL_Encode_Array_AudioVideoInput_SignalPresence(FILE* fp, Array_AudioVideoInput_SignalPresence value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_AudioVideoInput_SignalPresence(FILE* fp, Array_AudioVideoInput_SignalPresence* value) UNUSED_OK;

static int HAL_Decode_Array_AudioVideoInput_SignalPresence(FILE* fp, Array_AudioVideoInput_SignalPresence* value)
{
    InitArray_AudioVideoInput_SignalPresence(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_AudioVideoInput_SignalPresence(value, 1);
        value->elems[i] = (AudioVideoInput_SignalPresence)(int)HAL_Decode_Int(fp);
    }
    return AJ_OK;
}




static AJ_Status GetInputSourceId(void *context, const char *objPath, AudioVideoInput_SourceType *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "AudioVideoInput", "InputSourceId");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "AudioVideoInput", "InputSourceId");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        int const value = {0};
        HAL_Encode_Int(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "AudioVideoInput", "InputSourceId");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    int value;
    value = HAL_Decode_Int(fp);
    *out = (AudioVideoInput_SourceType)(int)value;
    fclose(fp);
    return result;
}



static AJ_Status SetInputSourceId(void *context, const char *objPath, AudioVideoInput_SourceType input)
{
    AJ_Status result = AJ_OK;
    int value = input;

    FILE* fp = HAL_WriteProperty("/cdm/emulated", "AudioVideoInput", "InputSourceId");
    HAL_Encode_Int(fp, value);
    fclose(fp);
    return result;
}


static AJ_Status GetSupportedInputSources(void *context, const char *objPath, Array_AudioVideoInput_InputSource *out)
{
    AJ_Status result = AJ_OK;

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "AudioVideoInput", "SupportedInputSources");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "AudioVideoInput", "SupportedInputSources");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        Array_AudioVideoInput_InputSource const value = {0};
        HAL_Encode_Array_AudioVideoInput_InputSource(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "AudioVideoInput", "SupportedInputSources");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    Array_AudioVideoInput_InputSource value;
    HAL_Decode_Array_AudioVideoInput_InputSource(fp, &value);

    *out = value;
    fclose(fp);
    return result;
}




static AudioVideoInputModel model = {
    GetInputSourceId
    , SetInputSourceId
    , GetSupportedInputSources

};


AudioVideoInputModel *GetAudioVideoInputModel(void)
{
    return &model;
}