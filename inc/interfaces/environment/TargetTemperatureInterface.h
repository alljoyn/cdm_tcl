/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef TARGETTEMPERATUREINTERFACE_H_
#define TARGETTEMPERATUREINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define TARGET_TEMPERATURE "org.alljoyn.SmartSpaces.Environment.TargetTemperature"

/**
 * TargetTemperature interface members
 */
typedef enum {
    TARGETTEMPERATURE_PROP_VERSION = 0,
    TARGETTEMPERATURE_PROP_TARGET_VALUE,
    TARGETTEMPERATURE_PROP_MIN_VALUE,
    TARGETTEMPERATURE_PROP_MAX_VALUE,
    TARGETTEMPERATURE_PROP_STEP_VALUE,
    TARGETTEMPERATURE_MEMBER_COUNT
} TargetTemperatureMembers;



extern const char* const intfDescEnvironmentTargetTemperature[TARGETTEMPERATURE_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerEnvironmentTargetTemperature;


/**
 * Emits a changed signal for the TargetValue property
 * @param[in] newValue new value of target value
 * @return ER_OK on success
 */
AJ_Status Cdm_TargetTemperature_EmitTargetValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue);

/**
 * Emits a changed signal for the MinValue property
 * @param[in] newValue new value of min value
 * @return ER_OK on success
 */
AJ_Status Cdm_TargetTemperature_EmitMinValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue);

/**
 * Emits a changed signal for the MaxValue property
 * @param[in] newValue new value of max value
 * @return ER_OK on success
 */
AJ_Status Cdm_TargetTemperature_EmitMaxValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue);

/**
 * Emits a changed signal for the StepValue property
 * @param[in] newValue new value of step value
 * @return ER_OK on success
 */
AJ_Status Cdm_TargetTemperature_EmitStepValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue);

#endif /* TARGETTEMPERATUREINTERFACE_H_ */