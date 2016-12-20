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

#ifndef DISHWASHINGCYCLEPHASEINTERFACE_H_
#define DISHWASHINGCYCLEPHASEINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define DISH_WASHING_CYCLE_PHASE "org.alljoyn.SmartSpaces.Operation.DishWashingCyclePhase"

/**
 * DishWashingCyclePhase interface members
 */
typedef enum {
    DISHWASHINGCYCLEPHASE_PROP_VERSION = 0,
    DISHWASHINGCYCLEPHASE_PROP_CYCLE_PHASE,
    DISHWASHINGCYCLEPHASE_PROP_SUPPORTED_CYCLE_PHASES,
    DISHWASHINGCYCLEPHASE_METHOD_GET_VENDOR_PHASES_DESCRIPTION,
    DISHWASHINGCYCLEPHASE_MEMBER_COUNT
} DishWashingCyclePhaseMembers;



typedef struct {
    uint8_t phase;
    char const* name;
    char const* description;
} DishWashingCyclePhase_CyclePhaseDescriptor;


typedef struct {
    DishWashingCyclePhase_CyclePhaseDescriptor* elems;
    size_t numElems;
} Array_DishWashingCyclePhase_CyclePhaseDescriptor;

/**
 *  Free the fields in the CyclePhaseDescriptor but not the struct itself.
 */
extern void FreeFields_DishWashingCyclePhase_CyclePhaseDescriptor(DishWashingCyclePhase_CyclePhaseDescriptor* value);

/**
 *  Free an array of CyclePhaseDescriptor.
 */
extern void FreeArray_DishWashingCyclePhase_CyclePhaseDescriptor(Array_DishWashingCyclePhase_CyclePhaseDescriptor* value);

/**
 *  Initialise an array of CyclePhaseDescriptor.
 */
extern void InitArray_DishWashingCyclePhase_CyclePhaseDescriptor(Array_DishWashingCyclePhase_CyclePhaseDescriptor* value, size_t numElems);

/**
 *  Copy an array of CyclePhaseDescriptor.
 */
extern void CopyArray_DishWashingCyclePhase_CyclePhaseDescriptor(Array_DishWashingCyclePhase_CyclePhaseDescriptor* value, Array_DishWashingCyclePhase_CyclePhaseDescriptor* copy);

/**
 *  Extend an array of CyclePhaseDescriptor.
 */
extern size_t ExtendArray_DishWashingCyclePhase_CyclePhaseDescriptor(Array_DishWashingCyclePhase_CyclePhaseDescriptor* value, size_t numElems);


extern const char* const intfDescOperationDishWashingCyclePhase[DISHWASHINGCYCLEPHASE_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationDishWashingCyclePhase;


/**
 * Emits a changed signal for the CyclePhase property
 * @param[in] newValue new value of cycle phase
 * @return ER_OK on success
 */
AJ_Status Cdm_DishWashingCyclePhase_EmitCyclePhaseChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the SupportedCyclePhases property
 * @param[in] newValue new value of supported cycle phases
 * @return ER_OK on success
 */
AJ_Status Cdm_DishWashingCyclePhase_EmitSupportedCyclePhasesChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue);

#endif /* DISHWASHINGCYCLEPHASEINTERFACE_H_ */