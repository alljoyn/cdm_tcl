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
#include <ajtcl/cdm/interfaces/operation/DishWashingCyclePhaseInterface.h>
#include <ajtcl/cdm/interfaces/operation/DishWashingCyclePhaseModel.h>

#include <ajtcl/cdm/utils/CdmArray.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME DISH_WASHING_CYCLE_PHASE

const char* const intfDescOperationDishWashingCyclePhase[] = {
    "$org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase",
    "@Version>q",
    "@CyclePhase>y",
    "@SupportedCyclePhases>ay",
    "?GetVendorPhasesDescription languageTag<s phasesDescription>a(yss)",
    NULL
};



void FreeFields_DishWashingCyclePhase_CyclePhaseDescriptor(DishWashingCyclePhase_CyclePhaseDescriptor* value)
{
    
    free((void*)value->name);

    free((void*)value->description);

}


void InitArray_DishWashingCyclePhase_CyclePhaseDescriptor(Array_DishWashingCyclePhase_CyclePhaseDescriptor* value, size_t numElems)
{
    Init_Array((CdmArray*)value, sizeof(DishWashingCyclePhase_CyclePhaseDescriptor), numElems);
}


/* Note: this only allows fields that are char*, not any other kind of pointer */
void CopyArray_DishWashingCyclePhase_CyclePhaseDescriptor(Array_DishWashingCyclePhase_CyclePhaseDescriptor* value, Array_DishWashingCyclePhase_CyclePhaseDescriptor* copy)
{
    if (value->elems) {
        copy->elems = malloc(value->numElems * sizeof(DishWashingCyclePhase_CyclePhaseDescriptor));
        for (size_t i = 0; i < value->numElems; ++i) {
            copy->elems[i].phase = value->elems[i].phase;
            copy->elems[i].name = strdup(value->elems[i].name);
            copy->elems[i].description = strdup(value->elems[i].description);
        }
    } else {
        copy->elems = NULL;
    }

    copy->numElems = value->numElems;

}


void FreeArray_DishWashingCyclePhase_CyclePhaseDescriptor(Array_DishWashingCyclePhase_CyclePhaseDescriptor* value)
{
    for (size_t i = 0; i < value->numElems; ++i) {
        FreeFields_DishWashingCyclePhase_CyclePhaseDescriptor(&value->elems[i]);
    }
    free(value->elems);
}


size_t ExtendArray_DishWashingCyclePhase_CyclePhaseDescriptor(Array_DishWashingCyclePhase_CyclePhaseDescriptor* value, size_t numElems)
{
    return Extend_Array((CdmArray*)value, sizeof(DishWashingCyclePhase_CyclePhaseDescriptor), numElems);
}




static AJ_Status DishWashingCyclePhase_GetCyclePhase(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    DishWashingCyclePhaseModel* model = (DishWashingCyclePhaseModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetCyclePhase) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetCyclePhase(model, objPath, out);
}



AJ_Status Cdm_DishWashingCyclePhase_EmitCyclePhaseChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "CyclePhase", "y", newValue);
}



static AJ_Status DishWashingCyclePhase_GetSupportedCyclePhases(AJ_BusAttachment* busAttachment, const char* objPath, Array_uint8* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    DishWashingCyclePhaseModel* model = (DishWashingCyclePhaseModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupportedCyclePhases) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupportedCyclePhases(model, objPath, out);
}



AJ_Status Cdm_DishWashingCyclePhase_EmitSupportedCyclePhasesChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "SupportedCyclePhases", "ay", newValue.elems, newValue.numElems);
}



static AJ_Status Cdm_DishWashingCyclePhase_CallGetVendorPhasesDescription(AJ_BusAttachment* busAttachment, const char *objPath, char const* languageTag, Array_DishWashingCyclePhase_CyclePhaseDescriptor* phasesDescription)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    DishWashingCyclePhaseModel* model = (DishWashingCyclePhaseModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->MethodGetVendorPhasesDescription) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->MethodGetVendorPhasesDescription(model, objPath, languageTag, phasesDescription);
}



/*
   Handler functions
*/
static AJ_Status DishWashingCyclePhase_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case DISHWASHINGCYCLEPHASE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case DISHWASHINGCYCLEPHASE_PROP_CYCLE_PHASE:
        {
            uint8_t cycle_phase;
            memset(&cycle_phase, 0, sizeof(uint8_t));
            status = DishWashingCyclePhase_GetCyclePhase(busAttachment, objPath, &cycle_phase);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", cycle_phase);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case DISHWASHINGCYCLEPHASE_PROP_SUPPORTED_CYCLE_PHASES:
        {
            Array_uint8 supported_cycle_phases;
            memset(&supported_cycle_phases, 0, sizeof(Array_uint8));
            status = DishWashingCyclePhase_GetSupportedCyclePhases(busAttachment, objPath, &supported_cycle_phases);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "ay", supported_cycle_phases.elems, sizeof(uint8_t) * supported_cycle_phases.numElems);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                FreeArray_uint8(&supported_cycle_phases);
            }
            break;
        }
    }

    return status;
}



static AJ_Status DishWashingCyclePhase_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case DISHWASHINGCYCLEPHASE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status DishWashingCyclePhase_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {

    case DISHWASHINGCYCLEPHASE_METHOD_GET_VENDOR_PHASES_DESCRIPTION:
    {
        AJ_Message reply;
        char const* language_tag;
        status = AJ_UnmarshalArgs(msg, "s", &language_tag);

        if (status != AJ_OK) {
            return status;
        }
        Array_DishWashingCyclePhase_CyclePhaseDescriptor phases_description;
        memset(&phases_description, 0, sizeof(Array_DishWashingCyclePhase_CyclePhaseDescriptor));

        status = Cdm_DishWashingCyclePhase_CallGetVendorPhasesDescription(busAttachment, objPath, language_tag, &phases_description);

        AJ_MarshalReplyMsg(msg, &reply);
        if (status == AJ_OK) {
            AJ_Arg array;
            int i=0;
            status |= AJ_MarshalContainer(&reply, &array, AJ_ARG_ARRAY);
            for (; i<phases_description.numElems; ++i)
            {
                AJ_Arg strc;
                status |= AJ_MarshalContainer(&reply, &strc, AJ_ARG_STRUCT);
                AJ_MarshalArgs(&reply, "yss", phases_description.elems[i].phase, phases_description.elems[i].name, phases_description.elems[i].description);
                AJ_MarshalCloseContainer(&reply, &strc);
            }
            AJ_MarshalCloseContainer(&reply, &array);
            if (status == AJ_OK) {
                status = AJ_DeliverMsg(&reply);
            }
        }

        FreeArray_DishWashingCyclePhase_CyclePhaseDescriptor(&phases_description);
        break;
    }
    }

    return status;
}



const InterfaceHandler intfHandlerOperationDishWashingCyclePhase = {
    DishWashingCyclePhase_OnGetProperty,
    DishWashingCyclePhase_OnSetProperty,
    DishWashingCyclePhase_OnMethodHandler
};
