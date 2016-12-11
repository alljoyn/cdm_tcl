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
#include <ajtcl/cdm/interfaces/operation/AudioVideoInputInterface.h>
#include <ajtcl/cdm/interfaces/operation/AudioVideoInputModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME AUDIO_VIDEO_INPUT

const char* const intfDescOperationAudioVideoInput[] = {
    "$org.alljoyn.SmartSpaces.Operation.AudioVideoInput",
    "@Version>q",
    "@InputSourceId=q",
    "@SupportedInputSources>a(qqyqs)",
    NULL
};



void FreeFields_AudioVideoInput_InputSource(AudioVideoInput_InputSource* value)
{
    
    
    
    
    free((void*)value->friendlyName);

}


void InitArray_AudioVideoInput_InputSource(Array_AudioVideoInput_InputSource* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(AudioVideoInput_InputSource), numElems);
}


// Note: this only allows fields that are char*, not any other kind of pointer
void CopyArray_AudioVideoInput_InputSource(Array_AudioVideoInput_InputSource* value, Array_AudioVideoInput_InputSource* copy)
{
    if (value->elems) {
        copy->elems = malloc(value->numElems * sizeof(AudioVideoInput_InputSource));
        for (size_t i = 0; i < value->numElems; ++i) {
            copy->elems[i].id = value->elems[i].id;
            copy->elems[i].sourceType = value->elems[i].sourceType;
            copy->elems[i].signalPresence = value->elems[i].signalPresence;
            copy->elems[i].portNumber = value->elems[i].portNumber;
            copy->elems[i].friendlyName = strdup(value->elems[i].friendlyName);
        }
    } else {
        copy->elems = NULL;
    }

    copy->numElems = value->numElems;

}


void FreeArray_AudioVideoInput_InputSource(Array_AudioVideoInput_InputSource* value)
{
    for (size_t i = 0; i < value->numElems; ++i) {
        FreeFields_AudioVideoInput_InputSource(&value->elems[i]);
    }
    free(value->elems);
}


size_t ExtendArray_AudioVideoInput_InputSource(Array_AudioVideoInput_InputSource* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(AudioVideoInput_InputSource), numElems);
}


void InitArray_AudioVideoInput_SourceType(Array_AudioVideoInput_SourceType* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(AudioVideoInput_SourceType), numElems);
}


void CopyArray_AudioVideoInput_SourceType(Array_AudioVideoInput_SourceType* value, Array_AudioVideoInput_SourceType* copy)
{
    Copy_Array((CDM_Array*)value, sizeof(AudioVideoInput_SourceType), (CDM_Array*)copy);
}


void FreeArray_AudioVideoInput_SourceType(Array_AudioVideoInput_SourceType* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_AudioVideoInput_SourceType(Array_AudioVideoInput_SourceType* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(AudioVideoInput_SourceType), numElems);
}


void InitArray_AudioVideoInput_SignalPresence(Array_AudioVideoInput_SignalPresence* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(AudioVideoInput_SignalPresence), numElems);
}


void CopyArray_AudioVideoInput_SignalPresence(Array_AudioVideoInput_SignalPresence* value, Array_AudioVideoInput_SignalPresence* copy)
{
    Copy_Array((CDM_Array*)value, sizeof(AudioVideoInput_SignalPresence), (CDM_Array*)copy);
}


void FreeArray_AudioVideoInput_SignalPresence(Array_AudioVideoInput_SignalPresence* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_AudioVideoInput_SignalPresence(Array_AudioVideoInput_SignalPresence* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(AudioVideoInput_SignalPresence), numElems);
}




static AJ_Status AudioVideoInput_GetInputSourceId(AJ_BusAttachment* busAttachment, const char* objPath, AudioVideoInput_SourceType* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    AudioVideoInputModel* model = (AudioVideoInputModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetInputSourceId) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetInputSourceId(model, objPath, out);
}



static AJ_Status AudioVideoInput_SetInputSourceId(AJ_BusAttachment* busAttachment, const char* objPath, AudioVideoInput_SourceType value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    AudioVideoInputModel* model = (AudioVideoInputModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetInputSourceId) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetInputSourceId(model, objPath, value);
}



AJ_Status Cdm_AudioVideoInput_EmitInputSourceIdChanged(AJ_BusAttachment *bus, const char *objPath, AudioVideoInput_SourceType newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "InputSourceId", "q", newValue);
}



static AJ_Status AudioVideoInput_GetSupportedInputSources(AJ_BusAttachment* busAttachment, const char* objPath, Array_AudioVideoInput_InputSource* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    AudioVideoInputModel* model = (AudioVideoInputModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupportedInputSources) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupportedInputSources(model, objPath, out);
}
 



static AJ_Status MarshalSupportedInputSources(AJ_Message* msg, void* structure, const char* structSignature)
{
    AudioVideoInput_InputSource* value = (AudioVideoInput_InputSource*)structure;
    AJ_MarshalArgs(msg, "q", value->id);
    AJ_MarshalArgs(msg, "q", value->sourceType);
    AJ_MarshalArgs(msg, "y", value->signalPresence);
    AJ_MarshalArgs(msg, "q", value->portNumber);
    AJ_MarshalArgs(msg, "s", value->friendlyName);
    return AJ_OK;
}



AJ_Status Cdm_AudioVideoInput_EmitSupportedInputSourcesChanged(AJ_BusAttachment *bus, const char *objPath, Array_AudioVideoInput_InputSource newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "SupportedInputSources", "a(qqyqs)", newValue.elems, newValue.numElems, sizeof(*newValue.elems), MarshalSupportedInputSources);
}




//
// Handler functions
//
static AJ_Status AudioVideoInput_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case AUDIOVIDEOINPUT_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case AUDIOVIDEOINPUT_PROP_INPUT_SOURCE_ID:
        {
            AudioVideoInput_SourceType input_source_id;
            status = AudioVideoInput_GetInputSourceId(busAttachment, objPath, &input_source_id);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", input_source_id);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case AUDIOVIDEOINPUT_PROP_SUPPORTED_INPUT_SOURCES:
        {
            Array_AudioVideoInput_InputSource supported_input_sources;
            status = AudioVideoInput_GetSupportedInputSources(busAttachment, objPath, &supported_input_sources);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "a(qqyqs)", supported_input_sources.elems, supported_input_sources.numElems);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                FreeArray_AudioVideoInput_InputSource(&supported_input_sources);
            }
            break;
        }
    }

    return status;
}



static AJ_Status AudioVideoInput_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case AUDIOVIDEOINPUT_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case AUDIOVIDEOINPUT_PROP_INPUT_SOURCE_ID:
        {
            uint16_t input_source_id;
            status = AJ_UnmarshalArgs(msg, "q", &input_source_id);
            if (status == AJ_OK) {
                status = AudioVideoInput_SetInputSourceId(busAttachment, objPath, (AudioVideoInput_SourceType)(int)input_source_id);
                if (status == AJ_OK) {
                    status= Cdm_AudioVideoInput_EmitInputSourceIdChanged(busAttachment, objPath, input_source_id);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status AudioVideoInput_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationAudioVideoInput = {
    AudioVideoInput_OnGetProperty,
    AudioVideoInput_OnSetProperty,
    AudioVideoInput_OnMethodHandler
};
