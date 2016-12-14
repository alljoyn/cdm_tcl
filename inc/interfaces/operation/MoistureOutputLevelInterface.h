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

#ifndef MOISTUREOUTPUTLEVELINTERFACE_H_
#define MOISTUREOUTPUTLEVELINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define MOISTURE_OUTPUT_LEVEL "org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel"

/**
 * MoistureOutputLevel interface members
 */
typedef enum {
    MOISTUREOUTPUTLEVEL_PROP_VERSION = 0,
    MOISTUREOUTPUTLEVEL_PROP_MOISTURE_OUTPUT_LEVEL,
    MOISTUREOUTPUTLEVEL_PROP_MAX_MOISTURE_OUTPUT_LEVEL,
    MOISTUREOUTPUTLEVEL_PROP_AUTO_MODE,
    MOISTUREOUTPUTLEVEL_MEMBER_COUNT
} MoistureOutputLevelMembers;


typedef enum {
    MOISTUREOUTPUTLEVEL_AUTO_MODE_OFF = 0,
    MOISTUREOUTPUTLEVEL_AUTO_MODE_ON = 1,
    MOISTUREOUTPUTLEVEL_AUTO_MODE_NOT_SUPPORTED = 255
} MoistureOutputLevel_AutoMode;


typedef struct {
    MoistureOutputLevel_AutoMode* elems;
    size_t numElems;
} Array_MoistureOutputLevel_AutoMode;


/**
 *  Initialise an array of AutoMode.
 */
extern void InitArray_MoistureOutputLevel_AutoMode(Array_MoistureOutputLevel_AutoMode* value, size_t numElems);

/**
 *  Copy an array of AutoMode.
 */
extern void CopyArray_MoistureOutputLevel_AutoMode(Array_MoistureOutputLevel_AutoMode* value, Array_MoistureOutputLevel_AutoMode* copy);

/**
 *  Free an array of AutoMode.
 */
extern void FreeArray_MoistureOutputLevel_AutoMode(Array_MoistureOutputLevel_AutoMode* value);

/**
 *  Extend an array of AutoMode.
 */
extern size_t ExtendArray_MoistureOutputLevel_AutoMode(Array_MoistureOutputLevel_AutoMode* value, size_t numElems);



extern const char* const intfDescOperationMoistureOutputLevel[MOISTUREOUTPUTLEVEL_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationMoistureOutputLevel;


/**
 * Emits a changed signal for the MoistureOutputLevel property
 * @param[in] newValue new value of moisture output level
 * @return ER_OK on success
 */
AJ_Status Cdm_MoistureOutputLevel_EmitMoistureOutputLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the MaxMoistureOutputLevel property
 * @param[in] newValue new value of max moisture output level
 * @return ER_OK on success
 */
AJ_Status Cdm_MoistureOutputLevel_EmitMaxMoistureOutputLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the AutoMode property
 * @param[in] newValue new value of auto mode
 * @return ER_OK on success
 */
AJ_Status Cdm_MoistureOutputLevel_EmitAutoModeChanged(AJ_BusAttachment *bus, const char *objPath, MoistureOutputLevel_AutoMode newValue);

#endif /* MOISTUREOUTPUTLEVELINTERFACE_H_ */