/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef TARGETTEMPERATURE_H_
#define TARGETTEMPERATURE_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

#define TARGET_TEMPERATURE_INTERFACE_NAME "org.alljoyn.SmartSpaces.Environment.TargetTemperature"

/**
 * TargetTemperature interface members
 */
typedef enum {
    TARGET_TEMPERATURE_PROP_VERSION = 0,
    TARGET_TEMPERATURE_PROP_TARGET_VALUE,
    TARGET_TEMPERATURE_PROP_MIN_VALUE,
    TARGET_TEMPERATURE_PROP_MAX_VALUE,
    TARGET_TEMPERATURE_PROP_STEP_VALUE,

    TARGET_TEMPERATURE_MEMBER_COUNT
} TargetTemperatureMembers;

const char* const intfDescEnvironmentTargetTemperature[TARGET_TEMPERATURE_MEMBER_COUNT + 2];
const InterfaceHandler intfHandlerEnvironmentTargetTemperature;

/**
 * TargetTemperature interface model
 */
typedef struct {
    /**
     * Handler for getting TargetValue property
     * @param[in] context the abstract model instance
     * @param[in] objPath object path
     * @param[out] outTargetValue the target value
     * @return AJ_OK on success
     */
    AJ_Status (*GetTargetValue) (void* context, const char* objPath, double* outTargetValue);

    /**
     * Handler for setting TargetLevel property
     * @param[in] context the abstract model instance
     * @param[in] objPath object path
     * @param[out] targetLevel the target value
     * @return AJ_OK on success
     */
    AJ_Status (*SetTargetValue) (void* context, const char* objPath, const double targetValue);

    /**
     * Handler for getting MinValue property
     * @param[in] context the abstract model instance
     * @param[in] objPath object path
     * @param[out] outMinValue the min value
     * @return AJ_OK on success
     */
    AJ_Status (*GetMinValue) (void* context, const char* objPath, double* outMinValue);

    /**
     * Handler for getting MaxValue property
     * @param[in] context the abstract model instance
     * @param[in] objPath object path
     * @param[out] outMaxValue the max value
     * @return AJ_OK on success
     */
    AJ_Status (*GetMaxValue) (void* context, const char* objPath, double* outMaxValue);

    /**
     * Handler for getting StepValue property
     * @param[in] context the abstract model instance
     * @param[in] objPath object path
     * @param[out] outStepValue the step value
     * @return AJ_OK on success
     */
    AJ_Status (*GetStepValue) (void* context, const char* objPath, double* outStepValue);
} TargetTemperatureModel;

#ifdef USE_DEPRECATED_INTERFACE_TYPES
AJ_DEPRECATED_ON(typedef TargetTemperatureModel TargetTemperatureListener, 16.10);
#endif

/**
 * Manually emit a changed signal for a TargetTemperature interface property; useful for read-only properties
 * @param[in] busAttachment the bus attachment
 * @param[in] objPath the object path
 * @param[in] member the property to emit a changed signal for with its current model value
 * @param[in] value The new value of the property. If this parameter is null, the interface's model is queried for the value. Can be single value or array.
 * @param[in] numValues If value is an array, this value must provide the number of elements in the value array. For non-arrays, this parameter is ignored.
 */
AJ_Status Cdm_TargetTemperatureEmitPropertyChanged(AJ_BusAttachment* busAttachment, const char* objPath, TargetTemperatureMembers member, const void* value, size_t numValues);

/**
 * Get the version of the TargetTemperature interface
 * @param[out] outVersion the interface version
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceGetVersion(uint16_t* outVersion);

/**
 * Get the target value of the TargetTemperature interface
 * @param[in] objPath the object path
 * @param[out] outTargetValue the target value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceGetTargetValue(const char* objPath, double* outTargetValue);

/**
 * Set the target value of the TargetTemperature interface
 * @param[in] busAttachment the bus attachment
 * @param[in] objPath the object path
 * @param[in] targetValue the target value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceSetTargetValue(AJ_BusAttachment* busAttachment, const char* objPath, const double targetValue);

/**
 * Get the min value of the TargetTemperature interface
 * @param[in] objPath the object path
 * @param[out] outMinValue the min value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceGetMinValue(const char* objPath, double* outMinValue);

/**
 * Get the max value of the TargetTemperature interface
 * @param[in] objPath the object path
 * @param[out] outMaxValue the max value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceGetMaxValue(const char* objPath, double* outMaxValue);

/**
 * Get the step value of the TargetTemperature interface
 * @param[in] objPath the object path
 * @param[out] outStepValue the step value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceGetStepValue(const char* objPath, double* outStepValue);

#endif /* TARGETTEMPERATURE_H_ */