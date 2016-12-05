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

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/environment/TargetTemperatureInterface.h>
#include <ajtcl/cdm/interfaces/environment/TargetTemperatureModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME TARGET_TEMPERATURE

const char* const intfDescEnvironmentTargetTemperature[] = {
    "$org.alljoyn.SmartSpaces.Environment.TargetTemperature",
    "@Version>q",
    "@TargetValue=d",
    "@MinValue>d",
    "@MaxValue>d",
    "@StepValue>d",
    NULL
};




static AJ_Status TargetTemperature_GetTargetValue(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureModel* model = (TargetTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTargetValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetTargetValue(model, objPath, out);
}



static AJ_Status TargetTemperature_SetTargetValue(AJ_BusAttachment* busAttachment, const char* objPath, double value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureModel* model = (TargetTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetTargetValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetTargetValue(model, objPath, value);
}



AJ_Status Cdm_TargetTemperature_EmitTargetValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "TargetValue", "d", newValue);
}



static AJ_Status TargetTemperature_GetMinValue(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureModel* model = (TargetTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMinValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMinValue(model, objPath, out);
}



AJ_Status Cdm_TargetTemperature_EmitMinValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MinValue", "d", newValue);
}



static AJ_Status TargetTemperature_GetMaxValue(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureModel* model = (TargetTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxValue(model, objPath, out);
}



AJ_Status Cdm_TargetTemperature_EmitMaxValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MaxValue", "d", newValue);
}



static AJ_Status TargetTemperature_GetStepValue(AJ_BusAttachment* busAttachment, const char* objPath, double* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TargetTemperatureModel* model = (TargetTemperatureModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetStepValue) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetStepValue(model, objPath, out);
}



AJ_Status Cdm_TargetTemperature_EmitStepValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "StepValue", "d", newValue);
}




//
// Handler functions
//
static AJ_Status TargetTemperature_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case TARGETTEMPERATURE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case TARGETTEMPERATURE_PROP_TARGET_VALUE:
        {
            double target_value;
            status = TargetTemperature_GetTargetValue(busAttachment, objPath, &target_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", target_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TARGETTEMPERATURE_PROP_MIN_VALUE:
        {
            double min_value;
            status = TargetTemperature_GetMinValue(busAttachment, objPath, &min_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", min_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TARGETTEMPERATURE_PROP_MAX_VALUE:
        {
            double max_value;
            status = TargetTemperature_GetMaxValue(busAttachment, objPath, &max_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", max_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TARGETTEMPERATURE_PROP_STEP_VALUE:
        {
            double step_value;
            status = TargetTemperature_GetStepValue(busAttachment, objPath, &step_value);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "d", step_value);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status TargetTemperature_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case TARGETTEMPERATURE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case TARGETTEMPERATURE_PROP_TARGET_VALUE:
        {
            double target_value;
            status = AJ_UnmarshalArgs(msg, "d", &target_value);
            if (status == AJ_OK) {
                status = TargetTemperature_SetTargetValue(busAttachment, objPath, target_value);
                if (status == AJ_OK) {
                    status= Cdm_TargetTemperature_EmitTargetValueChanged(busAttachment, objPath, target_value);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status TargetTemperature_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerEnvironmentTargetTemperature = {
    TargetTemperature_OnGetProperty,
    TargetTemperature_OnSetProperty,
    TargetTemperature_OnMethodHandler
};
