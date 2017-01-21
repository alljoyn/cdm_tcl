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
#include <ajtcl/cdm/interfaces/userinterfacesettings/LanguageDisplayInterface.h>
#include <ajtcl/cdm/interfaces/userinterfacesettings/LanguageDisplayModel.h>

#include <ajtcl/cdm/utils/CdmArray.h>

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

static AJ_Status ValidateDisplayLanguage(LanguageDisplayModel* model, const char* objPath, char const* value)
{

    Array_string validValues;
    if (model->GetSupportedDisplayLanguages(model, objPath, &validValues) != AJ_OK)
        return AJ_ERR_FAILURE;

    AJ_Status status = (valueIn_Array_string(value, &validValues) == 1) ? AJ_OK : AJ_ERR_NO_MATCH;

    FreeArray_string(&validValues);
    return status;
}

static AJ_Status LanguageDisplay_SetDisplayLanguage(AJ_BusAttachment* busAttachment, const char* objPath, char const* value)
{
    AJ_Status status;

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

    status = ValidateDisplayLanguage(model, objPath, value);
    if (status != AJ_OK)
        return status;

    model->busAttachment = busAttachment;
    status = model->SetDisplayLanguage(model, objPath, value);
    return status;
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




/*
   Handler functions
*/
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
            memset(&display_language, 0, sizeof(char const*));
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
            memset(&supported_display_languages, 0, sizeof(Array_string));
            status = LanguageDisplay_GetSupportedDisplayLanguages(busAttachment, objPath, &supported_display_languages);
            if (status == AJ_OK) {
                AJ_Arg array;
                int i=0;
                status |= AJ_MarshalContainer(replyMsg, &array, AJ_ARG_ARRAY);
                for (; i<supported_display_languages.numElems; ++i)
                {
                    status |= AJ_MarshalArgs(replyMsg, "s", supported_display_languages.elems[i]);
                }
                status |= AJ_MarshalCloseContainer(replyMsg, &array);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                FreeArray_string(&supported_display_languages);
            }
            break;
        }
    }

    return status;
}



static AJ_Status LanguageDisplay_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
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
                if (status == AJ_OK && emitOnSet) {
                    status = Cdm_LanguageDisplay_EmitDisplayLanguageChanged(busAttachment, objPath, display_language);
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
