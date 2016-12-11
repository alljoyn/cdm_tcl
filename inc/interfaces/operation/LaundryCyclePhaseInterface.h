/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef LAUNDRYCYCLEPHASEINTERFACE_H_
#define LAUNDRYCYCLEPHASEINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define LAUNDRY_CYCLE_PHASE "org.alljoyn.SmartSpaces.Operation.LaundryCyclePhase"

/**
 * LaundryCyclePhase interface members
 */
typedef enum {
    LAUNDRYCYCLEPHASE_PROP_VERSION = 0,
    LAUNDRYCYCLEPHASE_PROP_CYCLE_PHASE,
    LAUNDRYCYCLEPHASE_PROP_SUPPORTED_CYCLE_PHASES,
    LAUNDRYCYCLEPHASE_METHOD_GET_VENDOR_PHASES_DESCRIPTION,
    LAUNDRYCYCLEPHASE_MEMBER_COUNT
} LaundryCyclePhaseMembers;



typedef struct {
    uint8_t phase;
    char const* name;
    char const* description;
} LaundryCyclePhase_CyclePhaseDescriptor;


typedef struct {
    LaundryCyclePhase_CyclePhaseDescriptor* elems;
    size_t numElems;
} Array_LaundryCyclePhase_CyclePhaseDescriptor;

/**
 *  Free the fields in the CyclePhaseDescriptor but not the struct itself.
 */
extern void FreeFields_LaundryCyclePhase_CyclePhaseDescriptor(LaundryCyclePhase_CyclePhaseDescriptor* value);

/**
 *  Free an array of CyclePhaseDescriptor.
 */
extern void FreeArray_LaundryCyclePhase_CyclePhaseDescriptor(Array_LaundryCyclePhase_CyclePhaseDescriptor* value);

/**
 *  Initialise an array of CyclePhaseDescriptor.
 */
extern void InitArray_LaundryCyclePhase_CyclePhaseDescriptor(Array_LaundryCyclePhase_CyclePhaseDescriptor* value, size_t numElems);

/**
 *  Copy an array of CyclePhaseDescriptor.
 */
extern void CopyArray_LaundryCyclePhase_CyclePhaseDescriptor(Array_LaundryCyclePhase_CyclePhaseDescriptor* value, Array_LaundryCyclePhase_CyclePhaseDescriptor* copy);

/**
 *  Extend an array of CyclePhaseDescriptor.
 */
extern size_t ExtendArray_LaundryCyclePhase_CyclePhaseDescriptor(Array_LaundryCyclePhase_CyclePhaseDescriptor* value, size_t numElems);


extern const char* const intfDescOperationLaundryCyclePhase[LAUNDRYCYCLEPHASE_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationLaundryCyclePhase;


/**
 * Emits a changed signal for the CyclePhase property
 * @param[in] newValue new value of cycle phase
 * @return ER_OK on success
 */
AJ_Status Cdm_LaundryCyclePhase_EmitCyclePhaseChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the SupportedCyclePhases property
 * @param[in] newValue new value of supported cycle phases
 * @return ER_OK on success
 */
AJ_Status Cdm_LaundryCyclePhase_EmitSupportedCyclePhasesChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue);

#endif /* LAUNDRYCYCLEPHASEINTERFACE_H_ */