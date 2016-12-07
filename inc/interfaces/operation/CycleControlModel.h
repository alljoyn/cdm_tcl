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

#ifndef CYCLECONTROLMODEL_H_
#define CYCLECONTROLMODEL_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/interfaces/operation/CycleControlInterface.h>

/**
 * CycleControl interface model
 */
typedef struct {

    /**
     * Get OperationalState
     * @param[out] value current operational state. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetOperationalState)(void *context, const char *objPath, CycleControl_OperationalState* value);

    /**
     * Get SupportedOperationalStates
     * @param[out] value current supported operational states. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetSupportedOperationalStates)(void *context, const char *objPath, Array_CycleControl_OperationalState* value);

    /**
     * Get SupportedOperationalCommands
     * @param[out] value current supported operational commands. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetSupportedOperationalCommands)(void *context, const char *objPath, Array_CycleControl_OperationalCommands* value);

     /**
      * Call ExecuteOperationalCommand
      * @param[in] command
      */
    AJ_Status (*MethodExecuteOperationalCommand)(void *context, const char *objPath, CycleControl_OperationalCommands command);

    AJ_BusAttachment* busAttachment;

} CycleControlModel;

#endif /* CYCLECONTROLMODEL_H_ */