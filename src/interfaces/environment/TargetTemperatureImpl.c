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

#include <math.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/interfaces/environment/TargetTemperature.h>
#include "TargetTemperatureImpl.h"

#define INTERFACE_VERSION 1
#define INTERFACE_NAME TARGET_TEMPERATURE_INTERFACE_NAME

const char* const intfDescEnvironmentTargetTemperature[] = {
    "$" INTERFACE_NAME,
    "@Version>q",
    "@TargetValue=d",
    "@MinValue>d",
    "@MaxValue>d",
    "@StepValue>d",
    NULL
};

const InterfaceHandler intfHandlerEnvironmentTargetTemperature = {
#ifdef USE_DEPRECATED_INTERFACE_TYPES
    NULL,   // InterfaceRegistered
#endif
    TargetTemperatureInterfaceOnGetProperty,
    TargetTemperatureInterfaceOnSetProperty,
    NULL
};


static AJ_Status AdjustTargetValue(TargetTemperatureModel* model, const char* objPath, double* outTargetValue)
{
    double stepValue;
    double minValue;
    double maxValue;

    if (!model || !objPath || !outTargetValue) {
        return AJ_ERR_INVALID;
    }
    
    AJ_Status status = model->GetStepValue(model, objPath, &stepValue);
    if (status != AJ_OK) {
        return status;
    }
    if (stepValue == 0.0) {
        return AJ_OK;
    }

    status = model->GetMinValue(model, objPath, &minValue);
    if (status != AJ_OK) {
        return status;
    }

    status = model->GetMaxValue(model, objPath, &maxValue);
    if (status != AJ_OK) {
        return status;
    }

    double div = *outTargetValue / stepValue;
    double value = floor(div + 0.5) * stepValue;
    *outTargetValue = (value < minValue) ? minValue : (value > maxValue ? maxValue : value);

    return status;
}

AJ_Status TargetTemperatureInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_OK;

    switch (memberIndex) {
    case TARGET_TEMPERATURE_PROP_VERSION:
        status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
        break;
    case TARGET_TEMPERATURE_PROP_TARGET_VALUE: {
        double targetValue;
        status = Cdm_TargetTemperatureInterfaceGetTargetValue(objPath, &targetValue);
        if (status == AJ_OK) {
            status = AJ_MarshalArgs(replyMsg, "d", targetValue);
        }
        break;
    }
    case TARGET_TEMPERATURE_PROP_MIN_VALUE: {
        double minValue;
        status = Cdm_TargetTemperatureInterfaceGetMinValue(objPath, &minValue);
        if (status == AJ_OK) {
            status = AJ_MarshalArgs(replyMsg, "d", minValue);
        }
        break;
    }
    case TARGET_TEMPERATURE_PROP_MAX_VALUE: {
        double maxValue;
        status = Cdm_TargetTemperatureInterfaceGetMaxValue(objPath, &maxValue);
        if (status == AJ_OK) {
            status = AJ_MarshalArgs(replyMsg, "d", maxValue);
        }
        break;
    }
    case TARGET_TEMPERATURE_PROP_STEP_VALUE: {
        double stepValue;
        status = Cdm_TargetTemperatureInterfaceGetStepValue(objPath, &stepValue);
        if (status == AJ_OK) {
            status = AJ_MarshalArgs(replyMsg, "d", stepValue);
        }
        break;
    }
    default:
        status = AJ_ERR_INVALID;
    }

    return status;
}

AJ_Status TargetTemperatureInterfaceOnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_OK;

    switch (memberIndex) {
    case TARGET_TEMPERATURE_PROP_VERSION:
        status = AJ_ERR_DISALLOWED;
        break;
    case TARGET_TEMPERATURE_PROP_TARGET_VALUE: {
        double targetValue;
        status = AJ_UnmarshalArgs(replyMsg, "d", &targetValue);

        if (status == AJ_OK) {
            status = Cdm_TargetTemperatureInterfaceSetTargetValue(busAttachment, objPath, targetValue);
        }
        break;
    }
    case TARGET_TEMPERATURE_PROP_MIN_VALUE:
        status = AJ_ERR_DISALLOWED;
        break;
    case TARGET_TEMPERATURE_PROP_MAX_VALUE:
        status = AJ_ERR_DISALLOWED;
        break;
    case TARGET_TEMPERATURE_PROP_STEP_VALUE:
        status = AJ_ERR_DISALLOWED;
        break;
    default:
        status = AJ_ERR_INVALID;
    }

    return status;
}


AJ_Status Cdm_TargetTemperatureEmitPropertyChanged(AJ_BusAttachment* busAttachment, const char* objPath, TargetTemperatureMembers member, const void* value, size_t numValues)
{
    AJ_Status status = AJ_OK;
    
    switch (member) {
    case TARGET_TEMPERATURE_PROP_VERSION:
        status = AJ_ERR_DISALLOWED;
        break;
    case TARGET_TEMPERATURE_PROP_TARGET_VALUE: {
        double targetValue;
        if (value) {
            targetValue = *(double*)value;
        } else {
            status = Cdm_TargetTemperatureInterfaceGetTargetValue(objPath, &targetValue);
        }

        if (status == AJ_OK) {
            status = EmitPropertyChanged(busAttachment, objPath, INTERFACE_NAME, "TargetValue", "d", targetValue);
        }
        break;
    }
    case TARGET_TEMPERATURE_PROP_MIN_VALUE: {
        double minValue;
        if (value) {
            minValue = *(double*)value;
        } else {
            status = Cdm_TargetTemperatureInterfaceGetMinValue(objPath, &minValue);
        }

        if (status == AJ_OK) {
            status = EmitPropertyChanged(busAttachment, objPath, INTERFACE_NAME, "MinValue", "d", minValue);
        }
        break;
    }
    case TARGET_TEMPERATURE_PROP_MAX_VALUE: {
        double maxValue;
        if (value) {
            maxValue = *(double*)value;
        } else {
            status = Cdm_TargetTemperatureInterfaceGetMaxValue(objPath, &maxValue);
        }

        if (status == AJ_OK) {
            status = EmitPropertyChanged(busAttachment, objPath, INTERFACE_NAME, "MaxValue", "d", maxValue);
        }
        break;
    }
    case TARGET_TEMPERATURE_PROP_STEP_VALUE: {
        double stepValue;
        if (value) {
            stepValue = *(double*)value;
        } else {
            status = Cdm_TargetTemperatureInterfaceGetStepValue(objPath, &stepValue);
        }

        if (status == AJ_OK) {
            status = EmitPropertyChanged(busAttachment, objPath, INTERFACE_NAME, "StepValue", "d", stepValue);
        }
        break;
    }
    default:
        status = AJ_ERR_INVALID;
    }

    return status;
}

AJ_Status Cdm_TargetTemperatureInterfaceGetVersion(uint16_t* outVersion)
{
    *outVersion = INTERFACE_VERSION;
    return AJ_OK;
}

AJ_Status Cdm_TargetTemperatureInterfaceGetTargetValue(const char* objPath, double* outTargetValue)
{
    if (!objPath || !outTargetValue) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureModel* model = (TargetTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTargetValue) {
        return AJ_ERR_NULL;
    }
    
    return model->GetTargetValue(model, objPath, outTargetValue);
}

AJ_Status Cdm_TargetTemperatureInterfaceSetTargetValue(AJ_BusAttachment* busAttachment, const char* objPath, const double targetValue)
{
    if (!busAttachment || !objPath) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureModel* model = (TargetTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTargetValue || !model->SetTargetValue) {
        return AJ_ERR_NULL;
    }

    double newTargetValue = targetValue;
    AJ_Status status = AdjustTargetValue(model, objPath, &newTargetValue);
    if (status != AJ_OK) {
        return status;
    }

    double oldTargetValue;
    status = Cdm_TargetTemperatureInterfaceGetTargetValue(objPath, &oldTargetValue);
    if (status != AJ_OK) {
        return status;
    }

    if (fabs(oldTargetValue - newTargetValue) > 0.0001) {
        status = model->SetTargetValue(model, objPath, newTargetValue);

        if (status == AJ_OK) {
            status = Cdm_TargetTemperatureEmitPropertyChanged(busAttachment, objPath, TARGET_TEMPERATURE_PROP_TARGET_VALUE, &newTargetValue, 0);
        }
    }

    return status;
}

AJ_Status Cdm_TargetTemperatureInterfaceGetMinValue(const char* objPath, double* outMinValue)
{
    if (!objPath || !outMinValue) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureModel* model = (TargetTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMinValue) {
        return AJ_ERR_NULL;
    }

    return model->GetMinValue(model, objPath, outMinValue);
}

AJ_Status Cdm_TargetTemperatureInterfaceGetMaxValue(const char* objPath, double* outMaxValue)
{
    if (!objPath || !outMaxValue) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureModel* model = (TargetTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxValue) {
        return AJ_ERR_NULL;
    }

    return model->GetMaxValue(model, objPath, outMaxValue);
}

AJ_Status Cdm_TargetTemperatureInterfaceGetStepValue(const char* objPath, double* outStepValue)
{
    if (!objPath || !outStepValue) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureModel* model = (TargetTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetStepValue) {
        return AJ_ERR_NULL;
    }
    
    return model->GetStepValue(model, objPath, outStepValue);
}
