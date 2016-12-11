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

#ifndef CYCLECONTROLINTERFACE_H_
#define CYCLECONTROLINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define CYCLE_CONTROL "org.alljoyn.SmartSpaces.Operation.CycleControl"

/**
 * CycleControl interface members
 */
typedef enum {
    CYCLECONTROL_PROP_VERSION = 0,
    CYCLECONTROL_PROP_OPERATIONAL_STATE,
    CYCLECONTROL_PROP_SUPPORTED_OPERATIONAL_STATES,
    CYCLECONTROL_PROP_SUPPORTED_OPERATIONAL_COMMANDS,
    CYCLECONTROL_METHOD_EXECUTE_OPERATIONAL_COMMAND,
    CYCLECONTROL_MEMBER_COUNT
} CycleControlMembers;


typedef enum {
    CYCLECONTROL_OPERATIONAL_STATE_IDLE = 0,
    CYCLECONTROL_OPERATIONAL_STATE_WORKING = 1,
    CYCLECONTROL_OPERATIONAL_STATE_READY_TO_START = 2,
    CYCLECONTROL_OPERATIONAL_STATE_DELAYED_START = 3,
    CYCLECONTROL_OPERATIONAL_STATE_PAUSED = 4,
    CYCLECONTROL_OPERATIONAL_STATE_END_OF_CYCLE = 5
} CycleControl_OperationalState;


typedef struct {
    CycleControl_OperationalState* elems;
    size_t numElems;
} Array_CycleControl_OperationalState;


/**
 *  Initialise an array of OperationalState.
 */
extern void InitArray_CycleControl_OperationalState(Array_CycleControl_OperationalState* value, size_t numElems);

/**
 *  Copy an array of OperationalState.
 */
extern void CopyArray_CycleControl_OperationalState(Array_CycleControl_OperationalState* value, Array_CycleControl_OperationalState* copy);

/**
 *  Free an array of OperationalState.
 */
extern void FreeArray_CycleControl_OperationalState(Array_CycleControl_OperationalState* value);

/**
 *  Extend an array of OperationalState.
 */
extern size_t ExtendArray_CycleControl_OperationalState(Array_CycleControl_OperationalState* value, size_t numElems);


typedef enum {
    CYCLECONTROL_OPERATIONAL_COMMANDS_START = 0,
    CYCLECONTROL_OPERATIONAL_COMMANDS_STOP = 1,
    CYCLECONTROL_OPERATIONAL_COMMANDS_PAUSE = 2,
    CYCLECONTROL_OPERATIONAL_COMMANDS_RESUME = 3
} CycleControl_OperationalCommands;


typedef struct {
    CycleControl_OperationalCommands* elems;
    size_t numElems;
} Array_CycleControl_OperationalCommands;


/**
 *  Initialise an array of OperationalCommands.
 */
extern void InitArray_CycleControl_OperationalCommands(Array_CycleControl_OperationalCommands* value, size_t numElems);

/**
 *  Copy an array of OperationalCommands.
 */
extern void CopyArray_CycleControl_OperationalCommands(Array_CycleControl_OperationalCommands* value, Array_CycleControl_OperationalCommands* copy);

/**
 *  Free an array of OperationalCommands.
 */
extern void FreeArray_CycleControl_OperationalCommands(Array_CycleControl_OperationalCommands* value);

/**
 *  Extend an array of OperationalCommands.
 */
extern size_t ExtendArray_CycleControl_OperationalCommands(Array_CycleControl_OperationalCommands* value, size_t numElems);



extern const char* const intfDescOperationCycleControl[CYCLECONTROL_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationCycleControl;


/**
 * Emits a changed signal for the OperationalState property
 * @param[in] newValue new value of operational state
 * @return ER_OK on success
 */
AJ_Status Cdm_CycleControl_EmitOperationalStateChanged(AJ_BusAttachment *bus, const char *objPath, CycleControl_OperationalState newValue);

#endif /* CYCLECONTROLINTERFACE_H_ */