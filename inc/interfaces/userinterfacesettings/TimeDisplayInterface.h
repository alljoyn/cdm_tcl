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

#ifndef TIMEDISPLAYINTERFACE_H_
#define TIMEDISPLAYINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define TIME_DISPLAY "org.alljoyn.SmartSpaces.UserInterfaceSettings.TimeDisplay"

/**
 * TimeDisplay interface members
 */
typedef enum {
    TIMEDISPLAY_PROP_VERSION = 0,
    TIMEDISPLAY_PROP_DISPLAY_TIME_FORMAT,
    TIMEDISPLAY_PROP_SUPPORTED_DISPLAY_TIME_FORMATS,
    TIMEDISPLAY_MEMBER_COUNT
} TimeDisplayMembers;



extern const char* const intfDescUserinterfacesettingsTimeDisplay[TIMEDISPLAY_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerUserinterfacesettingsTimeDisplay;


/**
 * Emits a changed signal for the DisplayTimeFormat property
 * @param[in] newValue new value of display time format
 * @return ER_OK on success
 */
AJ_Status Cdm_TimeDisplay_EmitDisplayTimeFormatChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

#endif /* TIMEDISPLAYINTERFACE_H_ */