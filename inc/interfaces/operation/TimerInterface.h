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

#ifndef TIMERINTERFACE_H_
#define TIMERINTERFACE_H_

#include <stdint.h>

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CdmArray.h>

#define TIMER "org.alljoyn.SmartSpaces.Operation.Timer"

/**
 * Timer interface members
 */
typedef enum {
    TIMER_PROP_VERSION = 0,
    TIMER_PROP_REFERENCE_TIMER,
    TIMER_PROP_TARGET_TIME_TO_START,
    TIMER_PROP_TARGET_TIME_TO_STOP,
    TIMER_PROP_ESTIMATED_TIME_TO_END,
    TIMER_PROP_RUNNING_TIME,
    TIMER_PROP_TARGET_DURATION,
    TIMER_METHOD_SET_TARGET_TIME_TO_START,
    TIMER_METHOD_SET_TARGET_TIME_TO_STOP,
    TIMER_MEMBER_COUNT
} TimerMembers;



extern const char* const intfDescOperationTimer[TIMER_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationTimer;


/**
 * Emits a changed signal for the TargetTimeToStart property
 * @param[in] newValue new value of target time to start
 * @return ER_OK on success
 */
AJ_Status Cdm_Timer_EmitTargetTimeToStartChanged(AJ_BusAttachment *bus, const char *objPath, int32_t newValue);

/**
 * Emits a changed signal for the TargetTimeToStop property
 * @param[in] newValue new value of target time to stop
 * @return ER_OK on success
 */
AJ_Status Cdm_Timer_EmitTargetTimeToStopChanged(AJ_BusAttachment *bus, const char *objPath, int32_t newValue);

/**
 * Emits a changed signal for the TargetDuration property
 * @param[in] newValue new value of target duration
 * @return ER_OK on success
 */
AJ_Status Cdm_Timer_EmitTargetDurationChanged(AJ_BusAttachment *bus, const char *objPath, int32_t newValue);

#endif /* TIMERINTERFACE_H_ */