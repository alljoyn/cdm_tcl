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

#ifndef ROBOTCLEANINGCYCLEPHASEINTERFACE_H_
#define ROBOTCLEANINGCYCLEPHASEINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define ROBOT_CLEANING_CYCLE_PHASE "org.alljoyn.SmartSpaces.Operation.RobotCleaningCyclePhase"

/**
 * RobotCleaningCyclePhase interface members
 */
typedef enum {
    ROBOTCLEANINGCYCLEPHASE_PROP_VERSION = 0,
    ROBOTCLEANINGCYCLEPHASE_PROP_CYCLE_PHASE,
    ROBOTCLEANINGCYCLEPHASE_PROP_SUPPORTED_CYCLE_PHASES,
    ROBOTCLEANINGCYCLEPHASE_METHOD_GET_VENDOR_PHASES_DESCRIPTION,
    ROBOTCLEANINGCYCLEPHASE_MEMBER_COUNT
} RobotCleaningCyclePhaseMembers;



typedef struct {
    uint8_t phase;
    char const* name;
    char const* description;
} RobotCleaningCyclePhase_CyclePhaseDescriptor;


typedef struct {
    RobotCleaningCyclePhase_CyclePhaseDescriptor* elems;
    size_t numElems;
} Array_RobotCleaningCyclePhase_CyclePhaseDescriptor;

/**
 *  Free the fields in the CyclePhaseDescriptor but not the struct itself.
 */
extern void FreeFields_RobotCleaningCyclePhase_CyclePhaseDescriptor(RobotCleaningCyclePhase_CyclePhaseDescriptor* value);

/**
 *  Free an array of CyclePhaseDescriptor.
 */
extern void FreeArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* value);

/**
 *  Initialise an array of CyclePhaseDescriptor.
 */
extern void InitArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* value, size_t numElems);

/**
 *  Copy an array of CyclePhaseDescriptor.
 */
extern void CopyArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* value, Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* copy);

/**
 *  Extend an array of CyclePhaseDescriptor.
 */
extern size_t ExtendArray_RobotCleaningCyclePhase_CyclePhaseDescriptor(Array_RobotCleaningCyclePhase_CyclePhaseDescriptor* value, size_t numElems);


extern const char* const intfDescOperationRobotCleaningCyclePhase[ROBOTCLEANINGCYCLEPHASE_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationRobotCleaningCyclePhase;


/**
 * Emits a changed signal for the CyclePhase property
 * @param[in] newValue new value of cycle phase
 * @return ER_OK on success
 */
AJ_Status Cdm_RobotCleaningCyclePhase_EmitCyclePhaseChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the SupportedCyclePhases property
 * @param[in] newValue new value of supported cycle phases
 * @return ER_OK on success
 */
AJ_Status Cdm_RobotCleaningCyclePhase_EmitSupportedCyclePhasesChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue);

#endif /* ROBOTCLEANINGCYCLEPHASEINTERFACE_H_ */