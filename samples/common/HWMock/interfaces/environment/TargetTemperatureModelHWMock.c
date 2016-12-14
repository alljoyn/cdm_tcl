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

#include "HWMock/interfaces/environment/TargetTemperatureModelHWMock.h"
#include "HWMock/HALMockCommonHandlers.h"

/**
 * Base model function implementations.
 */
AJ_Status TargetTemperatureModelHWMock_GetTargetValue(void* context, const char* objPath, double* outTargetValue)
{
    TargetTemperatureModelHWMock* modelHWMock = ((TargetTemperatureModelHWMock*)context);
    if (!modelHWMock->hal) {
        return AJ_ERR_INVALID;
    }
    
    AJ_Status status = HALMock_GetValue(modelHWMock->hal, objPath, TARGET_TEMPERATURE_INTERFACE_NAME, "TargetValue", HALMock_ReadDoubleHandler, outTargetValue);
    printf("TargetTemperatureModelHWMock_GetTargetValue() called! Status = %d\n", status);
    return status;
}

AJ_Status TargetTemperatureModelHWMock_SetTargetValue(void* context, const char* objPath, const double targetValue)
{
    TargetTemperatureModelHWMock* modelHWMock = ((TargetTemperatureModelHWMock*)context);
    if (!modelHWMock->hal) {
        return AJ_ERR_INVALID;
    }

    AJ_Status status = HALMock_SetValue(modelHWMock->hal, objPath, TARGET_TEMPERATURE_INTERFACE_NAME, "TargetValue", HALMock_WriteDoubleHandler, &targetValue, 1);
    printf("TargetTemperatureModelHWMock_SetTargetValue() called! Status = %d\n", status);
    return status;
}

AJ_Status TargetTemperatureModelHWMock_GetMinValue(void* context, const char* objPath, double* outMinValue)
{
    TargetTemperatureModelHWMock* modelHWMock = ((TargetTemperatureModelHWMock*)context);
    if (!modelHWMock->hal) {
        return AJ_ERR_INVALID;
    }

    AJ_Status status = HALMock_GetValue(modelHWMock->hal, objPath, TARGET_TEMPERATURE_INTERFACE_NAME, "MinValue", HALMock_ReadDoubleHandler, outMinValue);
    printf("TargetTemperatureModelHWMock_GetMinValue() called! Status = %d\n", status);
    return status;
}

AJ_Status TargetTemperatureModelHWMock_GetMaxValue(void* context, const char* objPath, double* outMaxValue)
{
    TargetTemperatureModelHWMock* modelHWMock = ((TargetTemperatureModelHWMock*)context);
    if (!modelHWMock->hal) {
        return AJ_ERR_INVALID;
    }

    AJ_Status status = HALMock_GetValue(modelHWMock->hal, objPath, TARGET_TEMPERATURE_INTERFACE_NAME, "MaxValue", HALMock_ReadDoubleHandler, outMaxValue);
    printf("TargetTemperatureModelHWMock_GetMaxValue() called! Status = %d\n", status);
    return status;
}

AJ_Status TargetTemperatureModelHWMock_GetStepValue(void* context, const char* objPath, double* outStepValue)
{
    TargetTemperatureModelHWMock* modelHWMock = ((TargetTemperatureModelHWMock*)context);
    if (!modelHWMock->hal) {
        return AJ_ERR_INVALID;
    }

    AJ_Status status = HALMock_GetValue(modelHWMock->hal, objPath, TARGET_TEMPERATURE_INTERFACE_NAME, "StepValue", HALMock_ReadDoubleHandler, outStepValue);
    printf("TargetTemperatureModelHWMock_GetStepValue() called! Status = %d\n", status);
    return status;
}


/**
 * Mock hardware property changed callbacks.
 */
AJ_Status TargetTemperatureModelHWMock_OnTargetValueChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString)
{
    double targetValue;
    AJ_Status status = HALMock_ReadDoubleHandler(valueString, &targetValue);
    printf("TargetTemperatureModelHWMock_OnTargetValueChanged() called!\n");
    if (status != AJ_OK) {
        return status;
    }
    
    return Cdm_TargetTemperatureEmitPropertyChanged(busAttachment, objPath, TARGET_TEMPERATURE_PROP_TARGET_VALUE, &targetValue, 0);
}

AJ_Status TargetTemperatureModelHWMock_OnMinValueChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString)
{
    double minValue;
    AJ_Status status = HALMock_ReadDoubleHandler(valueString, &minValue);
    printf("TargetTemperatureModelHWMock_OnMinValueChanged() called!\n");
    if (status != AJ_OK) {
        return status;
    }

    return Cdm_TargetTemperatureEmitPropertyChanged(busAttachment, objPath, TARGET_TEMPERATURE_PROP_MIN_VALUE, &minValue, 0);
}

AJ_Status TargetTemperatureModelHWMock_OnMaxValueChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString)
{
    double maxValue;
    AJ_Status status = HALMock_ReadDoubleHandler(valueString, &maxValue);
    printf("TargetTemperatureModelHWMock_OnMaxValueChanged() called!\n");
    if (status != AJ_OK) {
        return status;
    }

    return Cdm_TargetTemperatureEmitPropertyChanged(busAttachment, objPath, TARGET_TEMPERATURE_PROP_MAX_VALUE, &maxValue, 0);
}

AJ_Status TargetTemperatureModelHWMock_OnStepValueChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString)
{
    double stepValue;
    AJ_Status status = HALMock_ReadDoubleHandler(valueString, &stepValue);
    printf("TargetTemperatureModelHWMock_OnStepValueChanged() called!\n");
    if (status != AJ_OK) {
        return status;
    }

    return Cdm_TargetTemperatureEmitPropertyChanged(busAttachment, objPath, TARGET_TEMPERATURE_PROP_STEP_VALUE, &stepValue, 0);
}


/**
 * TargetTemperature mock hardware model setup function.
 */
AJ_Status SetupTargetTemperatureModelHWMock(TargetTemperatureModelHWMock* modelHWMock, HALMock* halMock, const char* objPath)
{
	if (!modelHWMock || !halMock) {
		return AJ_ERR_INVALID;
	}
    if (!halMock->busAttachment || !halMock->hwFileName) {
        return AJ_ERR_NULL;
    }

	memset(modelHWMock, 0, sizeof(TargetTemperatureModelHWMock));

	modelHWMock->baseModel.GetTargetValue = TargetTemperatureModelHWMock_GetTargetValue;
    modelHWMock->baseModel.SetTargetValue = TargetTemperatureModelHWMock_SetTargetValue;
    modelHWMock->baseModel.GetMinValue = TargetTemperatureModelHWMock_GetMinValue;
    modelHWMock->baseModel.GetMaxValue = TargetTemperatureModelHWMock_GetMaxValue;
    modelHWMock->baseModel.GetStepValue = TargetTemperatureModelHWMock_GetStepValue;
    modelHWMock->hal = halMock;

    AJ_Status status = HALMock_SetPropertyChangedCallback(modelHWMock->hal, objPath, TARGET_TEMPERATURE_INTERFACE_NAME, "TargetValue", TargetTemperatureModelHWMock_OnTargetValueChanged);
    if (status != AJ_OK) {
        return status;
    }
    status = HALMock_SetPropertyChangedCallback(modelHWMock->hal, objPath, TARGET_TEMPERATURE_INTERFACE_NAME, "MinValue", TargetTemperatureModelHWMock_OnMinValueChanged);
    if (status != AJ_OK) {
        return status;
    }
    status = HALMock_SetPropertyChangedCallback(modelHWMock->hal, objPath, TARGET_TEMPERATURE_INTERFACE_NAME, "MaxValue", TargetTemperatureModelHWMock_OnMaxValueChanged);
    if (status != AJ_OK) {
        return status;
    }
    status = HALMock_SetPropertyChangedCallback(modelHWMock->hal, objPath, TARGET_TEMPERATURE_INTERFACE_NAME, "StepValue", TargetTemperatureModelHWMock_OnStepValueChanged);
    if (status != AJ_OK) {
        return status;
    }

    return status;
}