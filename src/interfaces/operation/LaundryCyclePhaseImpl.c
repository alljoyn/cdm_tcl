/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/operation/LaundryCyclePhaseInterface.h>
#include <ajtcl/cdm/interfaces/operation/LaundryCyclePhaseModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME LAUNDRY_CYCLE_PHASE

const char* const intfDescOperationLaundryCyclePhase[] = {
    "$org.alljoyn.SmartSpaces.Operation.LaundryCyclePhase",
    "@Version>q",
    "@CyclePhase>y",
    "@SupportedCyclePhases>ay",
    "?GetVendorPhasesDescription languageTag<s phasesDescription>a(yss)",
    NULL
};



void FreeFields_LaundryCyclePhase_CyclePhaseDescriptor(LaundryCyclePhase_CyclePhaseDescriptor* value)
{
    
    free((void*)value->name);

    free((void*)value->description);

}


void InitArray_LaundryCyclePhase_CyclePhaseDescriptor(Array_LaundryCyclePhase_CyclePhaseDescriptor* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(LaundryCyclePhase_CyclePhaseDescriptor), numElems);
}


// Note: this only allows fields that are char*, not any other kind of pointer
void CopyArray_LaundryCyclePhase_CyclePhaseDescriptor(Array_LaundryCyclePhase_CyclePhaseDescriptor* value, Array_LaundryCyclePhase_CyclePhaseDescriptor* copy)
{
    if (value->elems) {
        copy->elems = malloc(value->numElems * sizeof(LaundryCyclePhase_CyclePhaseDescriptor));
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


void FreeArray_LaundryCyclePhase_CyclePhaseDescriptor(Array_LaundryCyclePhase_CyclePhaseDescriptor* value)
{
    for (size_t i = 0; i < value->numElems; ++i) {
        FreeFields_LaundryCyclePhase_CyclePhaseDescriptor(&value->elems[i]);
    }
    free(value->elems);
}


size_t ExtendArray_LaundryCyclePhase_CyclePhaseDescriptor(Array_LaundryCyclePhase_CyclePhaseDescriptor* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(LaundryCyclePhase_CyclePhaseDescriptor), numElems);
}




static AJ_Status LaundryCyclePhase_GetCyclePhase(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    LaundryCyclePhaseModel* model = (LaundryCyclePhaseModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetCyclePhase) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetCyclePhase(model, objPath, out);
}



AJ_Status Cdm_LaundryCyclePhase_EmitCyclePhaseChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "CyclePhase", "y", newValue);
}



static AJ_Status LaundryCyclePhase_GetSupportedCyclePhases(AJ_BusAttachment* busAttachment, const char* objPath, Array_uint8* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    LaundryCyclePhaseModel* model = (LaundryCyclePhaseModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupportedCyclePhases) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupportedCyclePhases(model, objPath, out);
}



AJ_Status Cdm_LaundryCyclePhase_EmitSupportedCyclePhasesChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "SupportedCyclePhases", "ay", newValue.elems, newValue.numElems);
}



static AJ_Status Cdm_LaundryCyclePhase_CallGetVendorPhasesDescription(AJ_BusAttachment* busAttachment, const char *objPath, char const* languageTag, Array_LaundryCyclePhase_CyclePhaseDescriptor* phasesDescription)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    LaundryCyclePhaseModel* model = (LaundryCyclePhaseModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->MethodGetVendorPhasesDescription) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->MethodGetVendorPhasesDescription(model, objPath, languageTag, phasesDescription);
}



//
// Handler functions
//
static AJ_Status LaundryCyclePhase_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case LAUNDRYCYCLEPHASE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case LAUNDRYCYCLEPHASE_PROP_CYCLE_PHASE:
        {
            uint8_t cycle_phase;
            status = LaundryCyclePhase_GetCyclePhase(busAttachment, objPath, &cycle_phase);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", cycle_phase);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case LAUNDRYCYCLEPHASE_PROP_SUPPORTED_CYCLE_PHASES:
        {
            Array_uint8 supported_cycle_phases;
            status = LaundryCyclePhase_GetSupportedCyclePhases(busAttachment, objPath, &supported_cycle_phases);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "ay", supported_cycle_phases);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status LaundryCyclePhase_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case LAUNDRYCYCLEPHASE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status LaundryCyclePhase_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {

    case LAUNDRYCYCLEPHASE_METHOD_GET_VENDOR_PHASES_DESCRIPTION:
    {
        char const* language_tag;
        status = AJ_UnmarshalArgs(msg, "s", &language_tag);

        if (status != AJ_OK) {
            return status;
        }
        Array_LaundryCyclePhase_CyclePhaseDescriptor phases_description;

        status = Cdm_LaundryCyclePhase_CallGetVendorPhasesDescription(busAttachment, objPath, language_tag, &phases_description);

        AJ_Message reply;
        AJ_MarshalReplyMsg(msg, &reply);

        if (status == AJ_OK) {
            status |= AJ_MarshalArgs(&reply, "a(yss)", phases_description.elems, phases_description.numElems);
            if (status == AJ_OK) {
                status = AJ_DeliverMsg(&reply);
            }
        }

        FreeArray_LaundryCyclePhase_CyclePhaseDescriptor(&phases_description);
        break;
    }
    }

    return status;
}



const InterfaceHandler intfHandlerOperationLaundryCyclePhase = {
    LaundryCyclePhase_OnGetProperty,
    LaundryCyclePhase_OnSetProperty,
    LaundryCyclePhase_OnMethodHandler
};