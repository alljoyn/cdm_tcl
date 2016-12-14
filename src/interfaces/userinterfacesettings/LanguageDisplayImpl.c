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
#include <ajtcl/cdm/interfaces/userinterfacesettings/LanguageDisplayInterface.h>
#include <ajtcl/cdm/interfaces/userinterfacesettings/LanguageDisplayModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME LANGUAGE_DISPLAY

const char* const intfDescUserinterfacesettingsLanguageDisplay[] = {
    "$org.alljoyn.SmartSpaces.UserInterfaceSettings.LanguageDisplay",
    "@Version>q",
    "@DisplayLanguage=s",
    "@SupportedDisplayLanguages>as",
    NULL
};




static AJ_Status LanguageDisplay_GetDisplayLanguage(AJ_BusAttachment* busAttachment, const char* objPath, char const** out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    LanguageDisplayModel* model = (LanguageDisplayModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetDisplayLanguage) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetDisplayLanguage(model, objPath, out);
}



static AJ_Status LanguageDisplay_SetDisplayLanguage(AJ_BusAttachment* busAttachment, const char* objPath, char const* value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    LanguageDisplayModel* model = (LanguageDisplayModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetDisplayLanguage) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetDisplayLanguage(model, objPath, value);
}



AJ_Status Cdm_LanguageDisplay_EmitDisplayLanguageChanged(AJ_BusAttachment *bus, const char *objPath, char const* newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "DisplayLanguage", "s", newValue);
}



static AJ_Status LanguageDisplay_GetSupportedDisplayLanguages(AJ_BusAttachment* busAttachment, const char* objPath, Array_string* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    LanguageDisplayModel* model = (LanguageDisplayModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSupportedDisplayLanguages) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSupportedDisplayLanguages(model, objPath, out);
}




//
// Handler functions
//
static AJ_Status LanguageDisplay_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case LANGUAGEDISPLAY_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case LANGUAGEDISPLAY_PROP_DISPLAY_LANGUAGE:
        {
            char const* display_language;
            status = LanguageDisplay_GetDisplayLanguage(busAttachment, objPath, &display_language);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "s", display_language);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                free((void*)display_language);
            }
            break;
        }

        case LANGUAGEDISPLAY_PROP_SUPPORTED_DISPLAY_LANGUAGES:
        {
            Array_string supported_display_languages;
            status = LanguageDisplay_GetSupportedDisplayLanguages(busAttachment, objPath, &supported_display_languages);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "as", supported_display_languages);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status LanguageDisplay_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case LANGUAGEDISPLAY_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case LANGUAGEDISPLAY_PROP_DISPLAY_LANGUAGE:
        {
            char const* display_language;
            status = AJ_UnmarshalArgs(msg, "s", &display_language);
            if (status == AJ_OK) {
                status = LanguageDisplay_SetDisplayLanguage(busAttachment, objPath, display_language);
                if (status == AJ_OK) {
                    status= Cdm_LanguageDisplay_EmitDisplayLanguageChanged(busAttachment, objPath, display_language);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status LanguageDisplay_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerUserinterfacesettingsLanguageDisplay = {
    LanguageDisplay_OnGetProperty,
    LanguageDisplay_OnSetProperty,
    LanguageDisplay_OnMethodHandler
};