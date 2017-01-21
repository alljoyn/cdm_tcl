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

#include "DishWashingCyclePhaseModelImpl.h"
#include "../../../Utils/HAL.h"



static Element* HAL_Encode_DishWashingCyclePhase_CyclePhaseDescriptor(DishWashingCyclePhase_CyclePhaseDescriptor value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_DishWashingCyclePhase_CyclePhaseDescriptor(DishWashingCyclePhase_CyclePhaseDescriptor value, Element* parent)
{
    Element* struc = BSXML_NewElement("struct", parent);
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "phase");
        HAL_Encode_UInt(value.phase, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "name");
        HAL_Encode_String(value.name, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "description");
        HAL_Encode_String(value.description, field);
    }
    return struc;
}



static void HAL_Decode_DishWashingCyclePhase_CyclePhaseDescriptor(Element* elem, DishWashingCyclePhase_CyclePhaseDescriptor* value) UNUSED_OK;

static void HAL_Decode_DishWashingCyclePhase_CyclePhaseDescriptor(Element* elem, DishWashingCyclePhase_CyclePhaseDescriptor* value)
{
    if (strcmp(elem->name, "struct") == 0 && elem->numChildren == 3) {
        value->phase = HAL_Decode_UInt(elem->children[0]->children[0]);
        value->name = HAL_Decode_String(elem->children[1]->children[0]);
        value->description = HAL_Decode_String(elem->children[2]->children[0]);
    }
}



static Element* HAL_Encode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(Array_DishWashingCyclePhase_CyclePhaseDescriptor value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(Array_DishWashingCyclePhase_CyclePhaseDescriptor value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    size_t i = 0;
    for (; i < value.numElems; ++i) {
        HAL_Encode_DishWashingCyclePhase_CyclePhaseDescriptor(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(Element* elem, Array_DishWashingCyclePhase_CyclePhaseDescriptor* value) UNUSED_OK;

static void HAL_Decode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(Element* elem, Array_DishWashingCyclePhase_CyclePhaseDescriptor* value)
{
    InitArray_DishWashingCyclePhase_CyclePhaseDescriptor(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        size_t i = 0;
        for (; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_DishWashingCyclePhase_CyclePhaseDescriptor(value, 1);
            HAL_Decode_DishWashingCyclePhase_CyclePhaseDescriptor(elem->children[i], &value->elems[j]);
        }
    }
}




static AJ_Status GetCyclePhase(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase", "CyclePhase");

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

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase", "SupportedCyclePhases");

    if (elem) {
        HAL_Decode_Array_uint8(elem, &value);

        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




static AJ_Status MethodGetVendorPhasesDescription(void *context, const char *objPath, char const* languageTag, Array_DishWashingCyclePhase_CyclePhaseDescriptor* phasesDescription)
{
    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase", "__PhaseDescription");

    if (elem) {
        HAL_Decode_Array_DishWashingCyclePhase_CyclePhaseDescriptor(elem, phasesDescription);
        BSXML_FreeElement(elem);
        return AJ_OK;
    }

    return AJ_ERR_FAILURE;
}



AJ_Status HandleDishWashingCyclePhaseCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase") == 0)
    {
        if (strcmp(cmd->property, "CyclePhase") == 0)
        {
            uint8_t value;
            status = GetCyclePhase(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                DishWashingCyclePhaseModel* model = (DishWashingCyclePhaseModel*)context;
                status = Cdm_DishWashingCyclePhase_EmitCyclePhaseChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "SupportedCyclePhases") == 0)
        {
            Array_uint8 value;
            status = GetSupportedCyclePhases(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                DishWashingCyclePhaseModel* model = (DishWashingCyclePhaseModel*)context;
                status = Cdm_DishWashingCyclePhase_EmitSupportedCyclePhasesChanged(model->busAttachment, cmd->objPath, value);
            }
            FreeArray_uint8(&value);
        }
    }
    return status;
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
