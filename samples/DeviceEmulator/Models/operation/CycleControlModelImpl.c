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

#include "CycleControlModelImpl.h"
#include "../../../Utils/HAL.h"


static Element* HAL_Encode_CycleControl_OperationalState(CycleControl_OperationalState value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_CycleControl_OperationalState(CycleControl_OperationalState value, Element* parent)
{
    return HAL_Encode_UInt(value, parent);
}



static void HAL_Decode_CycleControl_OperationalState(Element* elem, uint8_t *value) UNUSED_OK;

static void HAL_Decode_CycleControl_OperationalState(Element* elem, uint8_t *value)
{
    *value = (uint8_t)HAL_Decode_UInt(elem);
}



static Element* HAL_Encode_Array_CycleControl_OperationalState(Array_CycleControl_OperationalState value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_CycleControl_OperationalState(Array_CycleControl_OperationalState value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_CycleControl_OperationalState(Element* elem, Array_CycleControl_OperationalState* value) UNUSED_OK;

static void HAL_Decode_Array_CycleControl_OperationalState(Element* elem, Array_CycleControl_OperationalState* value)
{
    InitArray_CycleControl_OperationalState(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_CycleControl_OperationalState(value, 1);
            value->elems[j] = (uint8_t)HAL_Decode_UInt(elem->children[i]);
        }
    }
}


static Element* HAL_Encode_CycleControl_OperationalCommands(CycleControl_OperationalCommands value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_CycleControl_OperationalCommands(CycleControl_OperationalCommands value, Element* parent)
{
    return HAL_Encode_UInt(value, parent);
}



static void HAL_Decode_CycleControl_OperationalCommands(Element* elem, uint8_t *value) UNUSED_OK;

static void HAL_Decode_CycleControl_OperationalCommands(Element* elem, uint8_t *value)
{
    *value = (uint8_t)HAL_Decode_UInt(elem);
}



static Element* HAL_Encode_Array_CycleControl_OperationalCommands(Array_CycleControl_OperationalCommands value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_CycleControl_OperationalCommands(Array_CycleControl_OperationalCommands value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_CycleControl_OperationalCommands(Element* elem, Array_CycleControl_OperationalCommands* value) UNUSED_OK;

static void HAL_Decode_Array_CycleControl_OperationalCommands(Element* elem, Array_CycleControl_OperationalCommands* value)
{
    InitArray_CycleControl_OperationalCommands(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_CycleControl_OperationalCommands(value, 1);
            value->elems[j] = (uint8_t)HAL_Decode_UInt(elem->children[i]);
        }
    }
}




static AJ_Status GetOperationalState(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint8_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.CycleControl", "OperationalState");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}

static AJ_Status GetSupportedOperationalStates(void *context, const char *objPath, Array_CycleControl_OperationalState *out)
{
    AJ_Status result = AJ_OK;
    Array_CycleControl_OperationalState value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.CycleControl", "SupportedOperationalStates");

    if (elem) {
        HAL_Decode_Array_CycleControl_OperationalState(elem, &value);

        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}

static AJ_Status GetSupportedOperationalCommands(void *context, const char *objPath, Array_CycleControl_OperationalCommands *out)
{
    AJ_Status result = AJ_OK;
    Array_CycleControl_OperationalCommands value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.CycleControl", "SupportedOperationalCommands");

    if (elem) {
        HAL_Decode_Array_CycleControl_OperationalCommands(elem, &value);

        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




static AJ_Status MethodExecuteOperationalCommand(void *context, const char *objPath, uint8_t command)
{
    AJ_Status status = AJ_OK;
    uint8_t state;
    int chg = 0;
    
    status = GetOperationalState(context, objPath, &state);
    if (status != AJ_OK) {
        return status;
    }

    switch (command)
    {
    case CYCLECONTROL_OPERATIONAL_COMMANDS_START:
        state = CYCLECONTROL_OPERATIONAL_STATE_WORKING;
        chg = 1;
        break;

    case CYCLECONTROL_OPERATIONAL_COMMANDS_STOP:
        state = CYCLECONTROL_OPERATIONAL_STATE_IDLE;
        chg = 1;
        break;

    case CYCLECONTROL_OPERATIONAL_COMMANDS_PAUSE:
        state = CYCLECONTROL_OPERATIONAL_STATE_PAUSED;
        chg = 1;
        break;

    case CYCLECONTROL_OPERATIONAL_COMMANDS_RESUME:
        state = CYCLECONTROL_OPERATIONAL_STATE_WORKING;
        chg = 1;
        break;

    default:
        break;
    }

    if (chg) {
        Element* elem = HAL_Encode_UInt(state, NULL);
        status = HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.CycleControl", "OperationalState", elem)? AJ_OK : AJ_ERR_FAILURE;
        BSXML_FreeElement(elem);

        if (status == AJ_OK && Cdm_EmitSignalOnPropertySet()) {
            CycleControlModel* model = (CycleControlModel*)context;
            status = Cdm_CycleControl_EmitOperationalStateChanged(model->busAttachment, objPath, state);
        }
    }

    return status;

}



AJ_Status HandleCycleControlCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.CycleControl") == 0)
    {
        if (strcmp(cmd->property, "OperationalState") == 0)
        {
            uint8_t value;
            status = GetOperationalState(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CycleControlModel* model = (CycleControlModel*)context;
                status = Cdm_CycleControl_EmitOperationalStateChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
    }
    return status;
}



static CycleControlModel model = {
    GetOperationalState
    , GetSupportedOperationalStates
    , GetSupportedOperationalCommands

    , MethodExecuteOperationalCommand
};


CycleControlModel *GetCycleControlModel(void)
{
    return &model;
}
