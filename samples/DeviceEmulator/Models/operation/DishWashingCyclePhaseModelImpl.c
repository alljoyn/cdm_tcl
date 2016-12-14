/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "DishWashingCyclePhaseModelImpl.h"
#include "../../../Utils/HAL.h"



static Element* HAL_Encode_DishWashingCyclePhase_CyclePhaseDescriptor(DishWashingCyclePhase_CyclePhaseDescriptor value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_DishWashingCyclePhase_CyclePhaseDescriptor(DishWashingCyclePhase_CyclePhaseDescriptor value, Element* parent)
{
    Element* struc = BSXML_NewElement("struct", parent);
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "phase");
        BSXML_AddChild(field, HAL_Encode_UInt(value.phase, field));
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "name");
        BSXML_AddChild(field, HAL_Encode_String(value.name, field));
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "description");
        BSXML_AddChild(field, HAL_Encode_String(value.description, field));
    }
    return struc;
}



static void HAL_Decode_DishWashingCyclePhase_CyclePhaseDescriptor(Element* elem, DishWashingCyclePhase_CyclePhaseDescriptor* value) UNUSED_OK;

static void HAL_Decode_DishWashingCyclePhase_CyclePhaseDescriptor(Element* elem, DishWashingCyclePhase_CyclePhaseDescriptor* value)
{
    if (strcmp(elem->name, "struct") == 0 && elem->numChildren == 3) {
        value->phase = HAL_Decode_UInt(elem->children[0]);
        value->name = HAL_Decode_String(elem->children[1]);
        value->description = HAL_Decode_String(elem->children[2]);
    }
}



static Element* HAL_Encode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(Array_DishWashingCyclePhase_CyclePhaseDescriptor value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(Array_DishWashingCyclePhase_CyclePhaseDescriptor value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        BSXML_AddChild(array, HAL_Encode_DishWashingCyclePhase_CyclePhaseDescriptor(value.elems[i], array));
    }
    return array;
}


static void HAL_Decode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(Element* elem, Array_DishWashingCyclePhase_CyclePhaseDescriptor* value) UNUSED_OK;

static void HAL_Decode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(Element* elem, Array_DishWashingCyclePhase_CyclePhaseDescriptor* value)
{
    InitArray_DishWashingCyclePhase_CyclePhaseDescriptor(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < value->numElems; ++i) {
            size_t j = ExtendArray_DishWashingCyclePhase_CyclePhaseDescriptor(value, 1);
            HAL_Decode_DishWashingCyclePhase_CyclePhaseDescriptor(elem->children[i], &value->elems[j]);
        }
    }
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

    Element* elem = HAL_ReadProperty("/cdm/emulated", "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase", "CyclePhase");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}


static AJ_Status GetSupportedCyclePhases(void *context, const char *objPath, Array_uint8 *out)
{
    AJ_Status result = AJ_OK;
    Array_uint8 value = {0};

    Element* elem = HAL_ReadProperty("/cdm/emulated", "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase", "SupportedCyclePhases");

    if (elem) {
        HAL_Decode_Array_uint8(elem, &value);

        BSXML_FreeElement(elem);
    }

    *out = value;
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