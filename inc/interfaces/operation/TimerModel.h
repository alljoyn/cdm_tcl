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

#ifndef TIMERMODEL_H_
#define TIMERMODEL_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/interfaces/operation/TimerInterface.h>

/**
 * Timer interface model
 */
typedef struct {

    /**
     * Get ReferenceTimer
     * @param[out] value current reference timer. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetReferenceTimer)(void *context, const char *objPath, int32_t* value);

    /**
     * Get TargetTimeToStart
     * @param[out] value current target time to start. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetTargetTimeToStart)(void *context, const char *objPath, int32_t* value);

    /**
     * Get TargetTimeToStop
     * @param[out] value current target time to stop. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetTargetTimeToStop)(void *context, const char *objPath, int32_t* value);

    /**
     * Get EstimatedTimeToEnd
     * @param[out] value current estimated time to end. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetEstimatedTimeToEnd)(void *context, const char *objPath, int32_t* value);

    /**
     * Get RunningTime
     * @param[out] value current running time. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetRunningTime)(void *context, const char *objPath, int32_t* value);

    /**
     * Get TargetDuration
     * @param[out] value current target duration. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetTargetDuration)(void *context, const char *objPath, int32_t* value);

     /**
      * Call SetTargetTimeToStart
      * @param[in] targetTimeToStart
      */
    AJ_Status (*MethodSetTargetTimeToStart)(void *context, const char *objPath, int32_t targetTimeToStart);

     /**
      * Call SetTargetTimeToStop
      * @param[in] targetTimeToStop
      */
    AJ_Status (*MethodSetTargetTimeToStop)(void *context, const char *objPath, int32_t targetTimeToStop);

    AJ_BusAttachment* busAttachment;

} TimerModel;

#endif /* TIMERMODEL_H_ */