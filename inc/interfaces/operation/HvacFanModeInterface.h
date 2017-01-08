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

#ifndef HVACFANMODEINTERFACE_H_
#define HVACFANMODEINTERFACE_H_

#include <stdint.h>

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define HVAC_FAN_MODE "org.alljoyn.SmartSpaces.Operation.HvacFanMode"

/**
 * HvacFanMode interface members
 */
typedef enum {
    HVACFANMODE_PROP_VERSION = 0,
    HVACFANMODE_PROP_MODE,
    HVACFANMODE_PROP_SUPPORTED_MODES,
    HVACFANMODE_MEMBER_COUNT
} HvacFanModeMembers;


typedef enum {
    HVACFANMODE_MODE_AUTO = 0,
    HVACFANMODE_MODE_CIRCULATION = 1,
    HVACFANMODE_MODE_CONTINUOUS = 2
} HvacFanMode_Mode;


typedef struct {
    uint16_t* elems;
    size_t numElems;
} Array_HvacFanMode_Mode;


/**
 *  Initialise an array of Mode.
 */
extern void InitArray_HvacFanMode_Mode(Array_HvacFanMode_Mode* value, size_t numElems);

/**
 *  Copy an array of Mode.
 */
extern void CopyArray_HvacFanMode_Mode(Array_HvacFanMode_Mode* value, Array_HvacFanMode_Mode* copy);

/**
 *  Free an array of Mode.
 */
extern void FreeArray_HvacFanMode_Mode(Array_HvacFanMode_Mode* value);

/**
 *  Extend an array of Mode.
 */
extern size_t ExtendArray_HvacFanMode_Mode(Array_HvacFanMode_Mode* value, size_t numElems);



extern const char* const intfDescOperationHvacFanMode[HVACFANMODE_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationHvacFanMode;


/**
 * Emits a changed signal for the Mode property
 * @param[in] newValue new value of mode
 * @return ER_OK on success
 */
AJ_Status Cdm_HvacFanMode_EmitModeChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

/**
 * Emits a changed signal for the SupportedModes property
 * @param[in] newValue new value of supported modes
 * @return ER_OK on success
 */
AJ_Status Cdm_HvacFanMode_EmitSupportedModesChanged(AJ_BusAttachment *bus, const char *objPath, Array_HvacFanMode_Mode newValue);

#endif /* HVACFANMODEINTERFACE_H_ */