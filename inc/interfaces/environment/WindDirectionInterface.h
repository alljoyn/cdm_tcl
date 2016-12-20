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

#ifndef WINDDIRECTIONINTERFACE_H_
#define WINDDIRECTIONINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define WIND_DIRECTION "org.alljoyn.SmartSpaces.Environment.WindDirection"

/**
 * WindDirection interface members
 */
typedef enum {
    WINDDIRECTION_PROP_VERSION = 0,
    WINDDIRECTION_PROP_HORIZONTAL_DIRECTION,
    WINDDIRECTION_PROP_HORIZONTAL_MAX,
    WINDDIRECTION_PROP_HORIZONTAL_AUTO_MODE,
    WINDDIRECTION_PROP_VERTICAL_DIRECTION,
    WINDDIRECTION_PROP_VERTICAL_MAX,
    WINDDIRECTION_PROP_VERTICAL_AUTO_MODE,
    WINDDIRECTION_MEMBER_COUNT
} WindDirectionMembers;


typedef enum {
    WINDDIRECTION_AUTO_MODE_OFF = 0,
    WINDDIRECTION_AUTO_MODE_ON = 1,
    WINDDIRECTION_AUTO_MODE_NOT_SUPPORTED = 255
} WindDirection_AutoMode;


typedef struct {
    WindDirection_AutoMode* elems;
    size_t numElems;
} Array_WindDirection_AutoMode;


/**
 *  Initialise an array of AutoMode.
 */
extern void InitArray_WindDirection_AutoMode(Array_WindDirection_AutoMode* value, size_t numElems);

/**
 *  Copy an array of AutoMode.
 */
extern void CopyArray_WindDirection_AutoMode(Array_WindDirection_AutoMode* value, Array_WindDirection_AutoMode* copy);

/**
 *  Free an array of AutoMode.
 */
extern void FreeArray_WindDirection_AutoMode(Array_WindDirection_AutoMode* value);

/**
 *  Extend an array of AutoMode.
 */
extern size_t ExtendArray_WindDirection_AutoMode(Array_WindDirection_AutoMode* value, size_t numElems);



extern const char* const intfDescEnvironmentWindDirection[WINDDIRECTION_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerEnvironmentWindDirection;


/**
 * Emits a changed signal for the HorizontalDirection property
 * @param[in] newValue new value of horizontal direction
 * @return ER_OK on success
 */
AJ_Status Cdm_WindDirection_EmitHorizontalDirectionChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

/**
 * Emits a changed signal for the HorizontalMax property
 * @param[in] newValue new value of horizontal max
 * @return ER_OK on success
 */
AJ_Status Cdm_WindDirection_EmitHorizontalMaxChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

/**
 * Emits a changed signal for the HorizontalAutoMode property
 * @param[in] newValue new value of horizontal auto mode
 * @return ER_OK on success
 */
AJ_Status Cdm_WindDirection_EmitHorizontalAutoModeChanged(AJ_BusAttachment *bus, const char *objPath, WindDirection_AutoMode newValue);

/**
 * Emits a changed signal for the VerticalDirection property
 * @param[in] newValue new value of vertical direction
 * @return ER_OK on success
 */
AJ_Status Cdm_WindDirection_EmitVerticalDirectionChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

/**
 * Emits a changed signal for the VerticalMax property
 * @param[in] newValue new value of vertical max
 * @return ER_OK on success
 */
AJ_Status Cdm_WindDirection_EmitVerticalMaxChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

/**
 * Emits a changed signal for the VerticalAutoMode property
 * @param[in] newValue new value of vertical auto mode
 * @return ER_OK on success
 */
AJ_Status Cdm_WindDirection_EmitVerticalAutoModeChanged(AJ_BusAttachment *bus, const char *objPath, WindDirection_AutoMode newValue);

#endif /* WINDDIRECTIONINTERFACE_H_ */