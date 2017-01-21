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

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

#include <ajtcl/cdm/interfaces/CdmInterfaceCommon.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceValidation.h>
#include <ajtcl/cdm/interfaces/operation/CycleControlInterface.h>
#include <ajtcl/cdm/interfaces/operation/CycleControlModel.h>

#include <ajtcl/cdm/utils/CdmArray.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME CYCLE_CONTROL

const char* const intfDescOperationCycleControl[] = {
    "$org.alljoyn.SmartSpaces.Operation.CycleControl",
    "@Version>q",
    "@OperationalState>y",
    "@SupportedOperationalStates>ay",
    "@SupportedOperationalCommands>ay",
    "?ExecuteOperationalCommand command<y",
    NULL
};


void InitArray_CycleControl_OperationalState(Array_CycleControl_OperationalState* value, size_t numElems)
{
    Init_Array((CdmArray*)value, sizeof(CycleControl_OperationalState), numElems);
}


void CopyArray_CycleControl_OperationalState(Array_CycleControl_OperationalState* value, Array_CycleControl_OperationalState* copy)
{
    Copy_Array((CdmArray*)value, sizeof(CycleControl_OperationalState), (CdmArray*)copy);
}


void FreeArray_CycleControl_OperationalState(Array_CycleControl_OperationalState* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_CycleControl_OperationalState(Array_CycleControl_OperationalState* value, size_t numElems)
{
    return Extend_Array((CdmArray*)value, sizeof(CycleControl_OperationalState), numElems);
}


void InitArray_CycleControl_OperationalCommands(Array_CycleControl_OperationalCommands* value, size_t numElems)
{
    Init_Array((CdmArray*)value, sizeof(CycleControl_OperationalCommands), numElems);
}


void CopyArray_CycleControl_OperationalCommands(Array_CycleControl_OperationalCommands* value, Array_CycleControl_OperationalCommands* copy)
{
    Copy_Array((CdmArray*)value, sizeof(CycleControl_OperationalCommands), (CdmArray*)copy);
}


void FreeArray_CycleControl_OperationalCommands(Array_CycleControl_OperationalCommands* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_CycleControl_OperationalCommands(Array_CycleControl_OperationalCommands* value, size_t numElems)
{
    return Extend_Array((CdmArray*)value, sizeof(CycleControl_OperationalCommands), numElems);
}




static AJ_Status CycleControl_GetOperationalState(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CycleControlModel* model = (CycleControlModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetOperationalState) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetOperationalState(model, objPath, out);
}



AJ_Status Cdm_CycleControl_EmitOperationalStateChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "OperationalState", "y", newValue);
}



static AJ_Status CycleControl_GetSupportedOperationalStates(AJ_BusAttachment* busAttachment, const char* objPath, Array_CycleControl_OperationalState* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CycleControlModel* model = (CycleControlModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupportedOperationalStates) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupportedOperationalStates(model, objPath, out);
}



static AJ_Status CycleControl_GetSupportedOperationalCommands(AJ_BusAttachment* busAttachment, const char* objPath, Array_CycleControl_OperationalCommands* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    CycleControlModel* model = (CycleControlModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupportedOperationalCommands) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupportedOperationalCommands(model, objPath, out);
}



static AJ_Status Cdm_CycleControl_CallExecuteOperationalCommand(AJ_BusAttachment* busAttachment, const char *objPath, CycleControl_OperationalCommands command)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    CycleControlModel* model = (CycleControlModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->MethodExecuteOperationalCommand) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->MethodExecuteOperationalCommand(model, objPath, (CycleControl_OperationalCommands)(int)command);
}



/*
   Handler functions
*/
static AJ_Status CycleControl_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CYCLECONTROL_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case CYCLECONTROL_PROP_OPERATIONAL_STATE:
        {
            uint8_t operational_state;
            memset(&operational_state, 0, sizeof(uint8_t));
            status = CycleControl_GetOperationalState(busAttachment, objPath, &operational_state);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", operational_state);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CYCLECONTROL_PROP_SUPPORTED_OPERATIONAL_STATES:
        {
            Array_CycleControl_OperationalState supported_operational_states;
            memset(&supported_operational_states, 0, sizeof(Array_CycleControl_OperationalState));
            status = CycleControl_GetSupportedOperationalStates(busAttachment, objPath, &supported_operational_states);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "ay", supported_operational_states.elems, sizeof(uint8_t) * supported_operational_states.numElems);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                FreeArray_CycleControl_OperationalState(&supported_operational_states);
            }
            break;
        }

        case CYCLECONTROL_PROP_SUPPORTED_OPERATIONAL_COMMANDS:
        {
            Array_CycleControl_OperationalCommands supported_operational_commands;
            memset(&supported_operational_commands, 0, sizeof(Array_CycleControl_OperationalCommands));
            status = CycleControl_GetSupportedOperationalCommands(busAttachment, objPath, &supported_operational_commands);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "ay", supported_operational_commands.elems, sizeof(uint8_t) * supported_operational_commands.numElems);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                FreeArray_CycleControl_OperationalCommands(&supported_operational_commands);
            }
            break;
        }
    }

    return status;
}



static AJ_Status CycleControl_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CYCLECONTROL_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status CycleControl_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {

    case CYCLECONTROL_METHOD_EXECUTE_OPERATIONAL_COMMAND:
    {
        AJ_Message reply;
        CycleControl_OperationalCommands command;
        status = AJ_UnmarshalArgs(msg, "y", &command);

        if (status != AJ_OK) {
            return status;
        }

        status = Cdm_CycleControl_CallExecuteOperationalCommand(busAttachment, objPath, command);

        AJ_MarshalReplyMsg(msg, &reply);
        if (status == AJ_OK) {
            status = AJ_DeliverMsg(&reply);
        }

        break;
    }
    }

    return status;
}



const InterfaceHandler intfHandlerOperationCycleControl = {
    CycleControl_OnGetProperty,
    CycleControl_OnSetProperty,
    CycleControl_OnMethodHandler
};
