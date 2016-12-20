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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/input/HidInterface.h>
#include <ajtcl/cdm/interfaces/input/HidModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME HID

const char* const intfDescInputHid[] = {
    "$org.alljoyn.Input.Hid",
    "@Version>q",
    "@SupportedEvents>a(qqii)",
    "?InjectEvents inputEvents<a(qqi)",
    NULL
};



void FreeFields_Hid_InputEvent(Hid_InputEvent* value)
{
    
    
    
}


void InitArray_Hid_InputEvent(Array_Hid_InputEvent* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(Hid_InputEvent), numElems);
}


// Note: this only allows fields that are char*, not any other kind of pointer
void CopyArray_Hid_InputEvent(Array_Hid_InputEvent* value, Array_Hid_InputEvent* copy)
{
    if (value->elems) {
        copy->elems = malloc(value->numElems * sizeof(Hid_InputEvent));
        for (size_t i = 0; i < value->numElems; ++i) {
            copy->elems[i].type = value->elems[i].type;
            copy->elems[i].code = value->elems[i].code;
            copy->elems[i].value = value->elems[i].value;
        }
    } else {
        copy->elems = NULL;
    }

    copy->numElems = value->numElems;

}


void FreeArray_Hid_InputEvent(Array_Hid_InputEvent* value)
{
    for (size_t i = 0; i < value->numElems; ++i) {
        FreeFields_Hid_InputEvent(&value->elems[i]);
    }
    free(value->elems);
}


size_t ExtendArray_Hid_InputEvent(Array_Hid_InputEvent* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(Hid_InputEvent), numElems);
}



void FreeFields_Hid_SupportedInputEvent(Hid_SupportedInputEvent* value)
{
    
    
    
    
}


void InitArray_Hid_SupportedInputEvent(Array_Hid_SupportedInputEvent* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(Hid_SupportedInputEvent), numElems);
}


// Note: this only allows fields that are char*, not any other kind of pointer
void CopyArray_Hid_SupportedInputEvent(Array_Hid_SupportedInputEvent* value, Array_Hid_SupportedInputEvent* copy)
{
    if (value->elems) {
        copy->elems = malloc(value->numElems * sizeof(Hid_SupportedInputEvent));
        for (size_t i = 0; i < value->numElems; ++i) {
            copy->elems[i].type = value->elems[i].type;
            copy->elems[i].code = value->elems[i].code;
            copy->elems[i].min = value->elems[i].min;
            copy->elems[i].max = value->elems[i].max;
        }
    } else {
        copy->elems = NULL;
    }

    copy->numElems = value->numElems;

}


void FreeArray_Hid_SupportedInputEvent(Array_Hid_SupportedInputEvent* value)
{
    for (size_t i = 0; i < value->numElems; ++i) {
        FreeFields_Hid_SupportedInputEvent(&value->elems[i]);
    }
    free(value->elems);
}


size_t ExtendArray_Hid_SupportedInputEvent(Array_Hid_SupportedInputEvent* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(Hid_SupportedInputEvent), numElems);
}




static AJ_Status Hid_GetSupportedEvents(AJ_BusAttachment* busAttachment, const char* objPath, Array_Hid_SupportedInputEvent* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    HidModel* model = (HidModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupportedEvents) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupportedEvents(model, objPath, out);
}
 



static AJ_Status MarshalSupportedEvents(AJ_Message* msg, void* structure, const char* structSignature)
{
    Hid_SupportedInputEvent* value = (Hid_SupportedInputEvent*)structure;
    AJ_MarshalArgs(msg, "q", value->type);
    AJ_MarshalArgs(msg, "q", value->code);
    AJ_MarshalArgs(msg, "i", value->min);
    AJ_MarshalArgs(msg, "i", value->max);
    return AJ_OK;
}



AJ_Status Cdm_Hid_EmitSupportedEventsChanged(AJ_BusAttachment *bus, const char *objPath, Array_Hid_SupportedInputEvent newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "SupportedEvents", "a(qqii)", newValue.elems, newValue.numElems, sizeof(*newValue.elems), MarshalSupportedEvents);
}



static AJ_Status Cdm_Hid_CallInjectEvents(AJ_BusAttachment* busAttachment, const char *objPath, Array_Hid_InputEvent inputEvents)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    HidModel* model = (HidModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->MethodInjectEvents) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->MethodInjectEvents(model, objPath, inputEvents);
}



//
// Handler functions
//
static AJ_Status Hid_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case HID_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case HID_PROP_SUPPORTED_EVENTS:
        {
            Array_Hid_SupportedInputEvent supported_events;
            status = Hid_GetSupportedEvents(busAttachment, objPath, &supported_events);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "a(qqii)", supported_events.elems, supported_events.numElems);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                FreeArray_Hid_SupportedInputEvent(&supported_events);
            }
            break;
        }
    }

    return status;
}



static AJ_Status Hid_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case HID_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status Hid_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {

    case HID_METHOD_INJECT_EVENTS:
    {
        Array_Hid_InputEvent input_events;
        status = AJ_UnmarshalArgs(msg, "a(qqi)", &input_events);

        if (status != AJ_OK) {
            return status;
        }

        status = Cdm_Hid_CallInjectEvents(busAttachment, objPath, input_events);

        AJ_Message reply;
        AJ_MarshalReplyMsg(msg, &reply);

        if (status == AJ_OK) {
            status = AJ_DeliverMsg(&reply);
        }

        break;
    }
    }

    return status;
}



const InterfaceHandler intfHandlerInputHid = {
    Hid_OnGetProperty,
    Hid_OnSetProperty,
    Hid_OnMethodHandler
};