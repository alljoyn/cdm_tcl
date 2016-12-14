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
#include <ajtcl/cdm/interfaces/operation/AudioVolumeInterface.h>
#include <ajtcl/cdm/interfaces/operation/AudioVolumeModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME AUDIO_VOLUME

const char* const intfDescOperationAudioVolume[] = {
    "$org.alljoyn.SmartSpaces.Operation.AudioVolume",
    "@Version>q",
    "@Volume=y",
    "@MaxVolume>y",
    "@Mute=b",
    NULL
};




static AJ_Status AudioVolume_GetVolume(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    AudioVolumeModel* model = (AudioVolumeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetVolume) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetVolume(model, objPath, out);
}



static AJ_Status AudioVolume_SetVolume(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    AudioVolumeModel* model = (AudioVolumeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetVolume) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetVolume(model, objPath, value);
}



AJ_Status Cdm_AudioVolume_EmitVolumeChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Volume", "y", newValue);
}



static AJ_Status AudioVolume_GetMaxVolume(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    AudioVolumeModel* model = (AudioVolumeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxVolume) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxVolume(model, objPath, out);
}



AJ_Status Cdm_AudioVolume_EmitMaxVolumeChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MaxVolume", "y", newValue);
}



static AJ_Status AudioVolume_GetMute(AJ_BusAttachment* busAttachment, const char* objPath, bool* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    AudioVolumeModel* model = (AudioVolumeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMute) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMute(model, objPath, out);
}



static AJ_Status AudioVolume_SetMute(AJ_BusAttachment* busAttachment, const char* objPath, bool value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    AudioVolumeModel* model = (AudioVolumeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetMute) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetMute(model, objPath, value);
}



AJ_Status Cdm_AudioVolume_EmitMuteChanged(AJ_BusAttachment *bus, const char *objPath, bool newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Mute", "b", newValue);
}




//
// Handler functions
//
static AJ_Status AudioVolume_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case AUDIOVOLUME_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case AUDIOVOLUME_PROP_VOLUME:
        {
            uint8_t volume;
            status = AudioVolume_GetVolume(busAttachment, objPath, &volume);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", volume);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case AUDIOVOLUME_PROP_MAX_VOLUME:
        {
            uint8_t max_volume;
            status = AudioVolume_GetMaxVolume(busAttachment, objPath, &max_volume);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", max_volume);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case AUDIOVOLUME_PROP_MUTE:
        {
            bool mute;
            status = AudioVolume_GetMute(busAttachment, objPath, &mute);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "b", mute);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status AudioVolume_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case AUDIOVOLUME_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case AUDIOVOLUME_PROP_VOLUME:
        {
            uint8_t volume;
            status = AJ_UnmarshalArgs(msg, "y", &volume);
            if (status == AJ_OK) {
                status = AudioVolume_SetVolume(busAttachment, objPath, volume);
                if (status == AJ_OK) {
                    status= Cdm_AudioVolume_EmitVolumeChanged(busAttachment, objPath, volume);
                }
            }
            break;
        }

        case AUDIOVOLUME_PROP_MUTE:
        {
            bool mute;
            status = AJ_UnmarshalArgs(msg, "b", &mute);
            if (status == AJ_OK) {
                status = AudioVolume_SetMute(busAttachment, objPath, mute);
                if (status == AJ_OK) {
                    status= Cdm_AudioVolume_EmitMuteChanged(busAttachment, objPath, mute);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status AudioVolume_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationAudioVolume = {
    AudioVolume_OnGetProperty,
    AudioVolume_OnSetProperty,
    AudioVolume_OnMethodHandler
};