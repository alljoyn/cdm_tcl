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

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/operation/OvenCyclePhaseInterface.h>
#include <ajtcl/cdm/interfaces/operation/OvenCyclePhaseModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME OVEN_CYCLE_PHASE

const char* const intfDescOperationOvenCyclePhase[] = {
    "$org.alljoyn.SmartSpaces.Operation.OvenCyclePhase",
    "@Version>q",
    "@CyclePhase>y",
    "@SupportedCyclePhases>ay",
    "?GetVendorPhasesDescription languageTag<s phasesDescription>a(yss)",
    NULL
};



void FreeFields_OvenCyclePhase_CyclePhaseDescriptor(OvenCyclePhase_CyclePhaseDescriptor* value)
{
    
    free((void*)value->name);

    free((void*)value->description);

}


void InitArray_OvenCyclePhase_CyclePhaseDescriptor(Array_OvenCyclePhase_CyclePhaseDescriptor* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(OvenCyclePhase_CyclePhaseDescriptor), numElems);
}


// Note: this only allows fields that are char*, not any other kind of pointer
void CopyArray_OvenCyclePhase_CyclePhaseDescriptor(Array_OvenCyclePhase_CyclePhaseDescriptor* value, Array_OvenCyclePhase_CyclePhaseDescriptor* copy)
{
    if (value->elems) {
        copy->elems = malloc(value->numElems * sizeof(OvenCyclePhase_CyclePhaseDescriptor));
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


void FreeArray_OvenCyclePhase_CyclePhaseDescriptor(Array_OvenCyclePhase_CyclePhaseDescriptor* value)
{
    for (size_t i = 0; i < value->numElems; ++i) {
        FreeFields_OvenCyclePhase_CyclePhaseDescriptor(&value->elems[i]);
    }
    free(value->elems);
}


size_t ExtendArray_OvenCyclePhase_CyclePhaseDescriptor(Array_OvenCyclePhase_CyclePhaseDescriptor* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(OvenCyclePhase_CyclePhaseDescriptor), numElems);
}




static AJ_Status OvenCyclePhase_GetCyclePhase(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    OvenCyclePhaseModel* model = (OvenCyclePhaseModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetCyclePhase) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetCyclePhase(model, objPath, out);
}



AJ_Status Cdm_OvenCyclePhase_EmitCyclePhaseChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "CyclePhase", "y", newValue);
}



static AJ_Status OvenCyclePhase_GetSupportedCyclePhases(AJ_BusAttachment* busAttachment, const char* objPath, Array_uint8* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    OvenCyclePhaseModel* model = (OvenCyclePhaseModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupportedCyclePhases) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupportedCyclePhases(model, objPath, out);
}



AJ_Status Cdm_OvenCyclePhase_EmitSupportedCyclePhasesChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "SupportedCyclePhases", "ay", newValue.elems, newValue.numElems);
}



static AJ_Status Cdm_OvenCyclePhase_CallGetVendorPhasesDescription(AJ_BusAttachment* busAttachment, const char *objPath, char const* languageTag, Array_OvenCyclePhase_CyclePhaseDescriptor* phasesDescription)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    OvenCyclePhaseModel* model = (OvenCyclePhaseModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
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
static AJ_Status OvenCyclePhase_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case OVENCYCLEPHASE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case OVENCYCLEPHASE_PROP_CYCLE_PHASE:
        {
            uint8_t cycle_phase;
            status = OvenCyclePhase_GetCyclePhase(busAttachment, objPath, &cycle_phase);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", cycle_phase);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case OVENCYCLEPHASE_PROP_SUPPORTED_CYCLE_PHASES:
        {
            Array_uint8 supported_cycle_phases;
            status = OvenCyclePhase_GetSupportedCyclePhases(busAttachment, objPath, &supported_cycle_phases);
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



static AJ_Status OvenCyclePhase_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case OVENCYCLEPHASE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status OvenCyclePhase_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {

    case OVENCYCLEPHASE_METHOD_GET_VENDOR_PHASES_DESCRIPTION:
    {
        char const* language_tag;
        status = AJ_UnmarshalArgs(msg, "s", &language_tag);

        if (status != AJ_OK) {
            return status;
        }
        Array_OvenCyclePhase_CyclePhaseDescriptor phases_description;

        status = Cdm_OvenCyclePhase_CallGetVendorPhasesDescription(busAttachment, objPath, language_tag, &phases_description);

        AJ_Message reply;
        AJ_MarshalReplyMsg(msg, &reply);

        if (status == AJ_OK) {
            status |= AJ_MarshalArgs(&reply, "a(yss)", phases_description.elems, phases_description.numElems);
            if (status == AJ_OK) {
                status = AJ_DeliverMsg(&reply);
            }
        }

        FreeArray_OvenCyclePhase_CyclePhaseDescriptor(&phases_description);
        break;
    }
    }

    return status;
}



const InterfaceHandler intfHandlerOperationOvenCyclePhase = {
    OvenCyclePhase_OnGetProperty,
    OvenCyclePhase_OnSetProperty,
    OvenCyclePhase_OnMethodHandler
};
