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

#include "DishWashingCyclePhaseModelImpl.h"
#include "../../../Utils/HAL.h"





static int HAL_Encode_DishWashingCyclePhase_CyclePhaseDescriptor(FILE* fp, DishWashingCyclePhase_CyclePhaseDescriptor value) UNUSED_OK;

static int HAL_Encode_DishWashingCyclePhase_CyclePhaseDescriptor(FILE* fp, DishWashingCyclePhase_CyclePhaseDescriptor value)
{
    HAL_Encode_OpenStruct(fp);
    HAL_Encode_UInt(fp, value.phase);
    HAL_Encode_String(fp, value.name);
    HAL_Encode_String(fp, value.description);
    HAL_Encode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Decode_DishWashingCyclePhase_CyclePhaseDescriptor(FILE* fp, DishWashingCyclePhase_CyclePhaseDescriptor* value) UNUSED_OK;

static int HAL_Decode_DishWashingCyclePhase_CyclePhaseDescriptor(FILE* fp, DishWashingCyclePhase_CyclePhaseDescriptor* value)
{
    HAL_Decode_OpenStruct(fp);
    value->phase = HAL_Decode_UInt(fp);
    value->name = HAL_Decode_String(fp);
    value->description = HAL_Decode_String(fp);
    HAL_Decode_CloseStruct(fp);
    return AJ_OK;
}



static int HAL_Encode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(FILE* fp, Array_DishWashingCyclePhase_CyclePhaseDescriptor value) UNUSED_OK;

static int HAL_Encode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(FILE* fp, Array_DishWashingCyclePhase_CyclePhaseDescriptor value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_DishWashingCyclePhase_CyclePhaseDescriptor(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
    return AJ_OK;
}


static int HAL_Decode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(FILE* fp, Array_DishWashingCyclePhase_CyclePhaseDescriptor* value) UNUSED_OK;

static int HAL_Decode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(FILE* fp, Array_DishWashingCyclePhase_CyclePhaseDescriptor* value)
{
    InitArray_DishWashingCyclePhase_CyclePhaseDescriptor(value, 0);

    HAL_Decode_OpenArray(fp);
    for (;;) {
        if (HAL_Decode_TestCloseArray(fp)) {
            break;
        }
        size_t i = ExtendArray_DishWashingCyclePhase_CyclePhaseDescriptor(value, 1);
        HAL_Decode_DishWashingCyclePhase_CyclePhaseDescriptor(fp, &value->elems[i]);
    }
    return AJ_OK;
}

static Array_DishWashingCyclePhase_CyclePhaseDescriptor* getPhases(void)
{
    static Array_DishWashingCyclePhase_CyclePhaseDescriptor s_phases;

    if (!s_phases.elems) {
        InitArray_DishWashingCyclePhase_CyclePhaseDescriptor(&s_phases, 0);
        size_t i = 0;

        i = ExtendArray_DishWashingCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 1;
        s_phases.elems[i].name = strdup("fill");
        s_phases.elems[i].description = strdup("Fill with water");

        i = ExtendArray_DishWashingCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 2;
        s_phases.elems[i].name = strdup("wash");
        s_phases.elems[i].description = strdup("Wash the dishes");

        i = ExtendArray_DishWashingCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 3;
        s_phases.elems[i].name = strdup("dry");
        s_phases.elems[i].description = strdup("Dry the dishes");

    }

    return &s_phases;
}



static AJ_Status GetCyclePhase(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "DishWashingCyclePhase", "CyclePhase");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "DishWashingCyclePhase", "CyclePhase");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        HAL_Encode_UInt(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "DishWashingCyclePhase", "CyclePhase");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    value = HAL_Decode_UInt(fp);
    *out = value;
    fclose(fp);
    return result;
}


static AJ_Status GetSupportedCyclePhases(void *context, const char *objPath, Array_uint8 *out)
{
    AJ_Status result = AJ_OK;
    Array_uint8 value = {0};

    FILE* fp = HAL_ReadProperty("/cdm/emulated", "DishWashingCyclePhase", "SupportedCyclePhases");

    if (!fp) {
        fp = HAL_WriteProperty("/cdm/emulated", "DishWashingCyclePhase", "SupportedCyclePhases");

        if (!fp) {
            return AJ_ERR_FAILURE;
        }

        HAL_Encode_Array_uint8(fp, value);
        fclose(fp);
    }

    fp = HAL_ReadProperty("/cdm/emulated", "DishWashingCyclePhase", "SupportedCyclePhases");

    if (!fp) {
        return AJ_ERR_FAILURE;
    }

    HAL_Decode_Array_uint8(fp, &value);

    *out = value;
    fclose(fp);
    return result;
}




static AJ_Status MethodGetVendorPhasesDescription(void *context, const char *objPath, char const* languageTag, Array_DishWashingCyclePhase_CyclePhaseDescriptor* phasesDescription)
{
    Array_DishWashingCyclePhase_CyclePhaseDescriptor* phases = getPhases();
    CopyArray_DishWashingCyclePhase_CyclePhaseDescriptor(phases, phasesDescription);
    return AJ_OK;
}



static DishWashingCyclePhaseModel model = {
    GetCyclePhase
    , GetSupportedCyclePhases

    , MethodGetVendorPhasesDescription
};


DishWashingCyclePhaseModel *GetDishWashingCyclePhaseModel(void)
{
    return &model;
}
