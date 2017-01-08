/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#include "RobotCleaningCyclePhaseModelImpl.h"
#include "../../../Utils/HAL.h"



static Element* HAL_Encode_RobotCleaningCyclePhase_CyclePhaseDescriptor(RobotCleaningCyclePhase_CyclePhaseDescriptor value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_RobotCleaningCyclePhase_CyclePhaseDescriptor(RobotCleaningCyclePhase_CyclePhaseDescriptor value, Element* parent)
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



static void HAL_Decode_RobotCleaningCyclePhase_CyclePhaseDescriptor(Element* elem, RobotCleaningCyclePhase_CyclePhaseDescriptor* value) UNUSED_OK;

static void HAL_Decode_RobotCleaningCyclePhase_CyclePhaseDescriptor(Element* elem, RobotCleaningCyclePhase_CyclePhaseDescriptor* value)
{
    if (strcmp(elem->name, "struct") == 0 && elem->numChildren == 3) {
        value->phase = HAL_Decode_UInt(elem->children[0]->children[0]);
        value->name = HAL_Decode_String(elem->children[1]->children[0]);
        value->description = HAL_Decode_String(elem->children[2]->children[0]);
    }
}



static Element* HAL_Encode_Array_RobotCleaningCyclePhase_CyclePhaseDescriptor(Array_RobotCleaningCyclePhase_CyclePhaseDescriptor value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_RobotCleaningCyclePhase_CyclePhaseDescriptor(Array_RobotCleaningCyclePhase_CyclePhaseDescriptor value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        BSXML_AddChild(array, HAL_Encode_RobotCleaningCyclePhase_CyclePhaseDescriptor(value.elems[i], array));
    }
    return array;
}


static void HAL_Decode_Array_RobotCleaningCyclePhase_CyclePhaseDescriptor(Element* elem, Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* value) UNUSED_OK;

static void HAL_Decode_Array_RobotCleaningCyclePhase_CyclePhaseDescriptor(Element* elem, Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* value)
{
    InitArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(value, 1);
            HAL_Decode_RobotCleaningCyclePhase_CyclePhaseDescriptor(elem->children[i], &value->elems[j]);
        }
    }
}

static Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* getPhases(void)
{
    static Array_RobotCleaningCyclePhase_CyclePhaseDescriptor s_phases;

    if (!s_phases.elems) {
        InitArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(&s_phases, 0);
        size_t i = 0;

        i = ExtendArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 1;
        s_phases.elems[i].name = strdup("seek");
        s_phases.elems[i].description = strdup("Seek some dirt");

        i = ExtendArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(&s_phases, 1);
        s_phases.elems[i].phase = 2;
        s_phases.elems[i].name = strdup("suck");
        s_phases.elems[i].description = strdup("Such it up");
    }

    return &s_phases;
}


static AJ_Status GetCyclePhase(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase", "CyclePhase");

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

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase", "SupportedCyclePhases");

    if (elem) {
        HAL_Decode_Array_uint8(elem, &value);

        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




static AJ_Status MethodGetVendorPhasesDescription(void *context, const char *objPath, char const* languageTag, Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* phasesDescription)
{
    Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* phases = getPhases();
    CopyArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(phases, phasesDescription);
    return AJ_OK;
}



static RobotCleaningCyclePhaseModel model = {
    GetCyclePhase
    , GetSupportedCyclePhases

    , MethodGetVendorPhasesDescription
};


RobotCleaningCyclePhaseModel *GetRobotCleaningCyclePhaseModel(void)
{
    return &model;
}
