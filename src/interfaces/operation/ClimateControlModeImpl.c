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
#include <ajtcl/cdm/interfaces/operation/ClimateControlModeInterface.h>
#include <ajtcl/cdm/interfaces/operation/ClimateControlModeModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME CLIMATE_CONTROL_MODE

const char* const intfDescOperationClimateControlMode[] = {
    "$org.alljoyn.SmartSpaces.Operation.ClimateControlMode",
    "@Version>q",
    "@Mode=q",
    "@SupportedModes>aq",
    "@OperationalState>q",
    NULL
};


void InitArray_ClimateControlMode_Mode(Array_ClimateControlMode_Mode* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(ClimateControlMode_Mode), numElems);
}


void CopyArray_ClimateControlMode_Mode(Array_ClimateControlMode_Mode* value, Array_ClimateControlMode_Mode* copy)
{
    Copy_Array((CDM_Array*)value, sizeof(ClimateControlMode_Mode), (CDM_Array*)copy);
}


void FreeArray_ClimateControlMode_Mode(Array_ClimateControlMode_Mode* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_ClimateControlMode_Mode(Array_ClimateControlMode_Mode* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(ClimateControlMode_Mode), numElems);
}


void InitArray_ClimateControlMode_OperationalState(Array_ClimateControlMode_OperationalState* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(ClimateControlMode_OperationalState), numElems);
}


void CopyArray_ClimateControlMode_OperationalState(Array_ClimateControlMode_OperationalState* value, Array_ClimateControlMode_OperationalState* copy)
{
    Copy_Array((CDM_Array*)value, sizeof(ClimateControlMode_OperationalState), (CDM_Array*)copy);
}


void FreeArray_ClimateControlMode_OperationalState(Array_ClimateControlMode_OperationalState* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_ClimateControlMode_OperationalState(Array_ClimateControlMode_OperationalState* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(ClimateControlMode_OperationalState), numElems);
}




static AJ_Status ClimateControlMode_GetMode(AJ_BusAttachment* busAttachment, const char* objPath, ClimateControlMode_Mode* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    ClimateControlModeModel* model = (ClimateControlModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMode(model, objPath, out);
}



static AJ_Status ClimateControlMode_SetMode(AJ_BusAttachment* busAttachment, const char* objPath, ClimateControlMode_Mode value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    ClimateControlModeModel* model = (ClimateControlModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetMode(model, objPath, value);
}



AJ_Status Cdm_ClimateControlMode_EmitModeChanged(AJ_BusAttachment *bus, const char *objPath, ClimateControlMode_Mode newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Mode", "q", newValue);
}



static AJ_Status ClimateControlMode_GetSupportedModes(AJ_BusAttachment* busAttachment, const char* objPath, Array_ClimateControlMode_Mode* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    ClimateControlModeModel* model = (ClimateControlModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupportedModes) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupportedModes(model, objPath, out);
}



AJ_Status Cdm_ClimateControlMode_EmitSupportedModesChanged(AJ_BusAttachment *bus, const char *objPath, Array_ClimateControlMode_Mode newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "SupportedModes", "aq", newValue.elems, newValue.numElems);
}



static AJ_Status ClimateControlMode_GetOperationalState(AJ_BusAttachment* busAttachment, const char* objPath, ClimateControlMode_OperationalState* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    ClimateControlModeModel* model = (ClimateControlModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetOperationalState) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetOperationalState(model, objPath, out);
}



AJ_Status Cdm_ClimateControlMode_EmitOperationalStateChanged(AJ_BusAttachment *bus, const char *objPath, ClimateControlMode_OperationalState newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "OperationalState", "q", newValue);
}




//
// Handler functions
//
static AJ_Status ClimateControlMode_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CLIMATECONTROLMODE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case CLIMATECONTROLMODE_PROP_MODE:
        {
            ClimateControlMode_Mode mode;
            status = ClimateControlMode_GetMode(busAttachment, objPath, &mode);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", mode);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case CLIMATECONTROLMODE_PROP_SUPPORTED_MODES:
        {
            Array_ClimateControlMode_Mode supported_modes;
            status = ClimateControlMode_GetSupportedModes(busAttachment, objPath, &supported_modes);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "aq", supported_modes.elems, supported_modes.numElems);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                FreeArray_ClimateControlMode_Mode(&supported_modes);
            }
            break;
        }

        case CLIMATECONTROLMODE_PROP_OPERATIONAL_STATE:
        {
            ClimateControlMode_OperationalState operational_state;
            status = ClimateControlMode_GetOperationalState(busAttachment, objPath, &operational_state);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", operational_state);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status ClimateControlMode_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CLIMATECONTROLMODE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case CLIMATECONTROLMODE_PROP_MODE:
        {
            uint16_t mode;
            status = AJ_UnmarshalArgs(msg, "q", &mode);
            if (status == AJ_OK) {
                status = ClimateControlMode_SetMode(busAttachment, objPath, (ClimateControlMode_Mode)(int)mode);
                if (status == AJ_OK) {
                    status= Cdm_ClimateControlMode_EmitModeChanged(busAttachment, objPath, mode);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status ClimateControlMode_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationClimateControlMode = {
    ClimateControlMode_OnGetProperty,
    ClimateControlMode_OnSetProperty,
    ClimateControlMode_OnMethodHandler
};
