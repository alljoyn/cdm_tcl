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

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/operation/HvacFanModeInterface.h>
#include <ajtcl/cdm/interfaces/operation/HvacFanModeModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME HVAC_FAN_MODE

const char* const intfDescOperationHvacFanMode[] = {
    "$org.alljoyn.SmartSpaces.Operation.HvacFanMode",
    "@Version>q",
    "@Mode=q",
    "@SupportedModes>aq",
    NULL
};


void InitArray_HvacFanMode_Mode(Array_HvacFanMode_Mode* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(HvacFanMode_Mode), numElems);
}


void CopyArray_HvacFanMode_Mode(Array_HvacFanMode_Mode* value, Array_HvacFanMode_Mode* copy)
{
    Copy_Array((CDM_Array*)value, sizeof(HvacFanMode_Mode), (CDM_Array*)copy);
}


void FreeArray_HvacFanMode_Mode(Array_HvacFanMode_Mode* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_HvacFanMode_Mode(Array_HvacFanMode_Mode* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(HvacFanMode_Mode), numElems);
}




static AJ_Status HvacFanMode_GetMode(AJ_BusAttachment* busAttachment, const char* objPath, HvacFanMode_Mode* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    HvacFanModeModel* model = (HvacFanModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMode(model, objPath, out);
}



static AJ_Status HvacFanMode_SetMode(AJ_BusAttachment* busAttachment, const char* objPath, HvacFanMode_Mode value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    HvacFanModeModel* model = (HvacFanModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetMode(model, objPath, value);
}



AJ_Status Cdm_HvacFanMode_EmitModeChanged(AJ_BusAttachment *bus, const char *objPath, HvacFanMode_Mode newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Mode", "q", newValue);
}



static AJ_Status HvacFanMode_GetSupportedModes(AJ_BusAttachment* busAttachment, const char* objPath, Array_HvacFanMode_Mode* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    HvacFanModeModel* model = (HvacFanModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupportedModes) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupportedModes(model, objPath, out);
}



AJ_Status Cdm_HvacFanMode_EmitSupportedModesChanged(AJ_BusAttachment *bus, const char *objPath, Array_HvacFanMode_Mode newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "SupportedModes", "aq", newValue.elems, newValue.numElems);
}




//
// Handler functions
//
static AJ_Status HvacFanMode_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case HVACFANMODE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case HVACFANMODE_PROP_MODE:
        {
            HvacFanMode_Mode mode;
            status = HvacFanMode_GetMode(busAttachment, objPath, &mode);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", mode);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case HVACFANMODE_PROP_SUPPORTED_MODES:
        {
            Array_HvacFanMode_Mode supported_modes;
            status = HvacFanMode_GetSupportedModes(busAttachment, objPath, &supported_modes);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "aq", supported_modes.elems, supported_modes.numElems);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                FreeArray_HvacFanMode_Mode(&supported_modes);
            }
            break;
        }
    }

    return status;
}



static AJ_Status HvacFanMode_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case HVACFANMODE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case HVACFANMODE_PROP_MODE:
        {
            uint16_t mode;
            status = AJ_UnmarshalArgs(msg, "q", &mode);
            if (status == AJ_OK) {
                status = HvacFanMode_SetMode(busAttachment, objPath, (HvacFanMode_Mode)(int)mode);
                if (status == AJ_OK) {
                    status= Cdm_HvacFanMode_EmitModeChanged(busAttachment, objPath, mode);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status HvacFanMode_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationHvacFanMode = {
    HvacFanMode_OnGetProperty,
    HvacFanMode_OnSetProperty,
    HvacFanMode_OnMethodHandler
};