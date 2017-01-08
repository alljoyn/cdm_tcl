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

#ifndef CLIMATECONTROLMODEINTERFACE_H_
#define CLIMATECONTROLMODEINTERFACE_H_

#include <stdint.h>

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define CLIMATE_CONTROL_MODE "org.alljoyn.SmartSpaces.Operation.ClimateControlMode"

/**
 * ClimateControlMode interface members
 */
typedef enum {
    CLIMATECONTROLMODE_PROP_VERSION = 0,
    CLIMATECONTROLMODE_PROP_MODE,
    CLIMATECONTROLMODE_PROP_SUPPORTED_MODES,
    CLIMATECONTROLMODE_PROP_OPERATIONAL_STATE,
    CLIMATECONTROLMODE_MEMBER_COUNT
} ClimateControlModeMembers;


typedef enum {
    CLIMATECONTROLMODE_MODE_OFF = 0,
    CLIMATECONTROLMODE_MODE_HEAT = 1,
    CLIMATECONTROLMODE_MODE_COOL = 2,
    CLIMATECONTROLMODE_MODE_AUTO = 3,
    CLIMATECONTROLMODE_MODE_AUXILIARY_HEAT = 4,
    CLIMATECONTROLMODE_MODE_DRY = 5,
    CLIMATECONTROLMODE_MODE_CONTINUOUS_DRY = 6
} ClimateControlMode_Mode;


typedef struct {
    uint16_t* elems;
    size_t numElems;
} Array_ClimateControlMode_Mode;


/**
 *  Initialise an array of Mode.
 */
extern void InitArray_ClimateControlMode_Mode(Array_ClimateControlMode_Mode* value, size_t numElems);

/**
 *  Copy an array of Mode.
 */
extern void CopyArray_ClimateControlMode_Mode(Array_ClimateControlMode_Mode* value, Array_ClimateControlMode_Mode* copy);

/**
 *  Free an array of Mode.
 */
extern void FreeArray_ClimateControlMode_Mode(Array_ClimateControlMode_Mode* value);

/**
 *  Extend an array of Mode.
 */
extern size_t ExtendArray_ClimateControlMode_Mode(Array_ClimateControlMode_Mode* value, size_t numElems);


typedef enum {
    CLIMATECONTROLMODE_OPERATIONAL_STATE_IDLE = 0,
    CLIMATECONTROLMODE_OPERATIONAL_STATE_HEATING = 1,
    CLIMATECONTROLMODE_OPERATIONAL_STATE_COOLING = 2,
    CLIMATECONTROLMODE_OPERATIONAL_STATE_PENDING_HEAT = 3,
    CLIMATECONTROLMODE_OPERATIONAL_STATE_PENDING_COOL = 4,
    CLIMATECONTROLMODE_OPERATIONAL_STATE_AUXILLIARY_HEAT = 5
} ClimateControlMode_OperationalState;


typedef struct {
    uint16_t* elems;
    size_t numElems;
} Array_ClimateControlMode_OperationalState;


/**
 *  Initialise an array of OperationalState.
 */
extern void InitArray_ClimateControlMode_OperationalState(Array_ClimateControlMode_OperationalState* value, size_t numElems);

/**
 *  Copy an array of OperationalState.
 */
extern void CopyArray_ClimateControlMode_OperationalState(Array_ClimateControlMode_OperationalState* value, Array_ClimateControlMode_OperationalState* copy);

/**
 *  Free an array of OperationalState.
 */
extern void FreeArray_ClimateControlMode_OperationalState(Array_ClimateControlMode_OperationalState* value);

/**
 *  Extend an array of OperationalState.
 */
extern size_t ExtendArray_ClimateControlMode_OperationalState(Array_ClimateControlMode_OperationalState* value, size_t numElems);



extern const char* const intfDescOperationClimateControlMode[CLIMATECONTROLMODE_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationClimateControlMode;


/**
 * Emits a changed signal for the Mode property
 * @param[in] newValue new value of mode
 * @return ER_OK on success
 */
AJ_Status Cdm_ClimateControlMode_EmitModeChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

/**
 * Emits a changed signal for the SupportedModes property
 * @param[in] newValue new value of supported modes
 * @return ER_OK on success
 */
AJ_Status Cdm_ClimateControlMode_EmitSupportedModesChanged(AJ_BusAttachment *bus, const char *objPath, Array_ClimateControlMode_Mode newValue);

/**
 * Emits a changed signal for the OperationalState property
 * @param[in] newValue new value of operational state
 * @return ER_OK on success
 */
AJ_Status Cdm_ClimateControlMode_EmitOperationalStateChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

#endif /* CLIMATECONTROLMODEINTERFACE_H_ */