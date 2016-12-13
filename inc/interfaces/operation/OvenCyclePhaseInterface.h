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

#ifndef OVENCYCLEPHASEINTERFACE_H_
#define OVENCYCLEPHASEINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define OVEN_CYCLE_PHASE "org.alljoyn.SmartSpaces.Operation.OvenCyclePhase"

/**
 * OvenCyclePhase interface members
 */
typedef enum {
    OVENCYCLEPHASE_PROP_VERSION = 0,
    OVENCYCLEPHASE_PROP_CYCLE_PHASE,
    OVENCYCLEPHASE_PROP_SUPPORTED_CYCLE_PHASES,
    OVENCYCLEPHASE_METHOD_GET_VENDOR_PHASES_DESCRIPTION,
    OVENCYCLEPHASE_MEMBER_COUNT
} OvenCyclePhaseMembers;



typedef struct {
    uint8_t phase;
    char const* name;
    char const* description;
} OvenCyclePhase_CyclePhaseDescriptor;


typedef struct {
    OvenCyclePhase_CyclePhaseDescriptor* elems;
    size_t numElems;
} Array_OvenCyclePhase_CyclePhaseDescriptor;

/**
 *  Free the fields in the CyclePhaseDescriptor but not the struct itself.
 */
extern void FreeFields_OvenCyclePhase_CyclePhaseDescriptor(OvenCyclePhase_CyclePhaseDescriptor* value);

/**
 *  Free an array of CyclePhaseDescriptor.
 */
extern void FreeArray_OvenCyclePhase_CyclePhaseDescriptor(Array_OvenCyclePhase_CyclePhaseDescriptor* value);

/**
 *  Initialise an array of CyclePhaseDescriptor.
 */
extern void InitArray_OvenCyclePhase_CyclePhaseDescriptor(Array_OvenCyclePhase_CyclePhaseDescriptor* value, size_t numElems);

/**
 *  Copy an array of CyclePhaseDescriptor.
 */
extern void CopyArray_OvenCyclePhase_CyclePhaseDescriptor(Array_OvenCyclePhase_CyclePhaseDescriptor* value, Array_OvenCyclePhase_CyclePhaseDescriptor* copy);

/**
 *  Extend an array of CyclePhaseDescriptor.
 */
extern size_t ExtendArray_OvenCyclePhase_CyclePhaseDescriptor(Array_OvenCyclePhase_CyclePhaseDescriptor* value, size_t numElems);


extern const char* const intfDescOperationOvenCyclePhase[OVENCYCLEPHASE_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationOvenCyclePhase;


/**
 * Emits a changed signal for the CyclePhase property
 * @param[in] newValue new value of cycle phase
 * @return ER_OK on success
 */
AJ_Status Cdm_OvenCyclePhase_EmitCyclePhaseChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the SupportedCyclePhases property
 * @param[in] newValue new value of supported cycle phases
 * @return ER_OK on success
 */
AJ_Status Cdm_OvenCyclePhase_EmitSupportedCyclePhasesChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue);

#endif /* OVENCYCLEPHASEINTERFACE_H_ */