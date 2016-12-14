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

#ifndef _TARGET_TEMPERATURE_MODEL_HW_MOCK_H_
#define _TARGET_TEMPERATURE_MODEL_HW_MOCK_H_

#include <ajtcl/cdm/interfaces/environment/TargetTemperature.h>
#include "HWMock/HALMock.h"

/**
 * TargetTemperature model extended to support mock hardware operations.
 */
typedef struct {
	TargetTemperatureModel baseModel;

	HALMock* hal;
} TargetTemperatureModelHWMock;

/**
 * Base model function implementations which interface with HAL.
 */
AJ_Status TargetTemperatureModelHWMock_GetTargetValue(void* context, const char* objPath, double* outTargetValue);
AJ_Status TargetTemperatureModelHWMock_SetTargetValue(void* context, const char* objPath, const double targetValue);
AJ_Status TargetTemperatureModelHWMock_GetMinValue(void* context, const char* objPath, double* outMinValue);
AJ_Status TargetTemperatureModelHWMock_GetMaxValue(void* context, const char* objPath, double* outMaxValue);
AJ_Status TargetTemperatureModelHWMock_GetStepValue(void* context, const char* objPath, double* outStepValue);

/**
 * Callbacks for when properties are changed directly on mock hardware outside of the model.
 */
AJ_Status TargetTemperatureModelHWMock_OnTargetValueChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString);
AJ_Status TargetTemperatureModelHWMock_OnMinValueChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString);
AJ_Status TargetTemperatureModelHWMock_OnMaxValueChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString);
AJ_Status TargetTemperatureModelHWMock_OnStepValueChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString);

/**
 * TargetTemperature mock hardware model setup function.
 */
AJ_Status SetupTargetTemperatureModelHWMock(TargetTemperatureModelHWMock* modelSW, HALMock* halMock, const char* objPath);

#endif /* _TARGET_TEMPERATURE_MODEL_HW_MOCK_H_ */