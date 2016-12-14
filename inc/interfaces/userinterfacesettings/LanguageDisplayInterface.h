/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef LANGUAGEDISPLAYINTERFACE_H_
#define LANGUAGEDISPLAYINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define LANGUAGE_DISPLAY "org.alljoyn.SmartSpaces.UserInterfaceSettings.LanguageDisplay"

/**
 * LanguageDisplay interface members
 */
typedef enum {
    LANGUAGEDISPLAY_PROP_VERSION = 0,
    LANGUAGEDISPLAY_PROP_DISPLAY_LANGUAGE,
    LANGUAGEDISPLAY_PROP_SUPPORTED_DISPLAY_LANGUAGES,
    LANGUAGEDISPLAY_MEMBER_COUNT
} LanguageDisplayMembers;



extern const char* const intfDescUserinterfacesettingsLanguageDisplay[LANGUAGEDISPLAY_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerUserinterfacesettingsLanguageDisplay;


/**
 * Emits a changed signal for the DisplayLanguage property
 * @param[in] newValue new value of display language
 * @return ER_OK on success
 */
AJ_Status Cdm_LanguageDisplay_EmitDisplayLanguageChanged(AJ_BusAttachment *bus, const char *objPath, char const* newValue);

#endif /* LANGUAGEDISPLAYINTERFACE_H_ */