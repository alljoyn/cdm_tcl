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
#include <ajtcl/cdm/interfaces/userinterfacesettings/TimeDisplayInterface.h>
#include <ajtcl/cdm/interfaces/userinterfacesettings/TimeDisplayModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME TIME_DISPLAY

const char* const intfDescUserinterfacesettingsTimeDisplay[] = {
    "$org.alljoyn.SmartSpaces.UserInterfaceSettings.TimeDisplay",
    "@Version>q",
    "@DisplayTimeFormat=y",
    "@SupportedDisplayTimeFormats>ay",
    NULL
};




static AJ_Status TimeDisplay_GetDisplayTimeFormat(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TimeDisplayModel* model = (TimeDisplayModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetDisplayTimeFormat) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetDisplayTimeFormat(model, objPath, out);
}



static AJ_Status TimeDisplay_SetDisplayTimeFormat(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    TimeDisplayModel* model = (TimeDisplayModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetDisplayTimeFormat) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetDisplayTimeFormat(model, objPath, value);
}



AJ_Status Cdm_TimeDisplay_EmitDisplayTimeFormatChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "DisplayTimeFormat", "y", newValue);
}



static AJ_Status TimeDisplay_GetSupportedDisplayTimeFormats(AJ_BusAttachment* busAttachment, const char* objPath, Array_uint8* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TimeDisplayModel* model = (TimeDisplayModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupportedDisplayTimeFormats) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupportedDisplayTimeFormats(model, objPath, out);
}




//
// Handler functions
//
static AJ_Status TimeDisplay_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case TIMEDISPLAY_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case TIMEDISPLAY_PROP_DISPLAY_TIME_FORMAT:
        {
            uint8_t display_time_format;
            status = TimeDisplay_GetDisplayTimeFormat(busAttachment, objPath, &display_time_format);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", display_time_format);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TIMEDISPLAY_PROP_SUPPORTED_DISPLAY_TIME_FORMATS:
        {
            Array_uint8 supported_display_time_formats;
            status = TimeDisplay_GetSupportedDisplayTimeFormats(busAttachment, objPath, &supported_display_time_formats);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "ay", supported_display_time_formats);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status TimeDisplay_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case TIMEDISPLAY_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case TIMEDISPLAY_PROP_DISPLAY_TIME_FORMAT:
        {
            uint8_t display_time_format;
            status = AJ_UnmarshalArgs(msg, "y", &display_time_format);
            if (status == AJ_OK) {
                status = TimeDisplay_SetDisplayTimeFormat(busAttachment, objPath, display_time_format);
                if (status == AJ_OK) {
                    status= Cdm_TimeDisplay_EmitDisplayTimeFormatChanged(busAttachment, objPath, display_time_format);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status TimeDisplay_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerUserinterfacesettingsTimeDisplay = {
    TimeDisplay_OnGetProperty,
    TimeDisplay_OnSetProperty,
    TimeDisplay_OnMethodHandler
};