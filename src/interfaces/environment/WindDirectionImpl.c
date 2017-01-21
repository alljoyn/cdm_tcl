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

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

#include <ajtcl/cdm/interfaces/CdmInterfaceCommon.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceValidation.h>
#include <ajtcl/cdm/interfaces/environment/WindDirectionInterface.h>
#include <ajtcl/cdm/interfaces/environment/WindDirectionModel.h>

#include <ajtcl/cdm/utils/CdmArray.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME WIND_DIRECTION

const char* const intfDescEnvironmentWindDirection[] = {
    "$org.alljoyn.SmartSpaces.Environment.WindDirection",
    "@Version>q",
    "@HorizontalDirection=q",
    "@HorizontalMax>q",
    "@HorizontalAutoMode=y",
    "@VerticalDirection=q",
    "@VerticalMax>q",
    "@VerticalAutoMode=y",
    NULL
};


void InitArray_WindDirection_AutoMode(Array_WindDirection_AutoMode* value, size_t numElems)
{
    Init_Array((CdmArray*)value, sizeof(WindDirection_AutoMode), numElems);
}


void CopyArray_WindDirection_AutoMode(Array_WindDirection_AutoMode* value, Array_WindDirection_AutoMode* copy)
{
    Copy_Array((CdmArray*)value, sizeof(WindDirection_AutoMode), (CdmArray*)copy);
}


void FreeArray_WindDirection_AutoMode(Array_WindDirection_AutoMode* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_WindDirection_AutoMode(Array_WindDirection_AutoMode* value, size_t numElems)
{
    return Extend_Array((CdmArray*)value, sizeof(WindDirection_AutoMode), numElems);
}




static AJ_Status WindDirection_GetHorizontalDirection(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    WindDirectionModel* model = (WindDirectionModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetHorizontalDirection) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetHorizontalDirection(model, objPath, out);
}

static AJ_Status clampHorizontalDirection(WindDirectionModel* model, const char* objPath, uint16_t value, uint16_t *out)
{

    uint16_t minValue = 0;

    uint16_t maxValue;
    if (model->GetHorizontalMax(model, objPath, &maxValue) != AJ_OK)
        return AJ_ERR_FAILURE;

    uint16_t stepValue = 0;

    *out = clamp_uint16(value, minValue, maxValue, stepValue);
    return AJ_OK;
}

static AJ_Status WindDirection_SetHorizontalDirection(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t *value)
{
    AJ_Status status;

    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    WindDirectionModel* model = (WindDirectionModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetHorizontalDirection) {
        return AJ_ERR_NULL;
    }

    status = clampHorizontalDirection(model, objPath, *value, value);
    if (status != AJ_OK)
        return status;

    model->busAttachment = busAttachment;
    status = model->SetHorizontalDirection(model, objPath, *value);
    return status;
}



AJ_Status Cdm_WindDirection_EmitHorizontalDirectionChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "HorizontalDirection", "q", newValue);
}



static AJ_Status WindDirection_GetHorizontalMax(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    WindDirectionModel* model = (WindDirectionModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetHorizontalMax) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetHorizontalMax(model, objPath, out);
}



AJ_Status Cdm_WindDirection_EmitHorizontalMaxChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "HorizontalMax", "q", newValue);
}



static AJ_Status WindDirection_GetHorizontalAutoMode(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    WindDirectionModel* model = (WindDirectionModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetHorizontalAutoMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetHorizontalAutoMode(model, objPath, out);
}

static AJ_Status ValidateHorizontalAutoMode(WindDirectionModel* model, const char* objPath, WindDirection_AutoMode value)
{

    switch (value)
    {
        case WINDDIRECTION_AUTO_MODE_OFF:
        case WINDDIRECTION_AUTO_MODE_ON:
            break;
        case WINDDIRECTION_AUTO_MODE_NOT_SUPPORTED:
        default:
            return AJ_ERR_INVALID;
    }

    return AJ_OK;
}

static AJ_Status WindDirection_SetHorizontalAutoMode(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t value)
{
    AJ_Status status;

    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    WindDirectionModel* model = (WindDirectionModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetHorizontalAutoMode) {
        return AJ_ERR_NULL;
    }

    status = ValidateHorizontalAutoMode(model, objPath, value);
    if (status != AJ_OK)
        return status;

    model->busAttachment = busAttachment;
    status = model->SetHorizontalAutoMode(model, objPath, value);
    return status;
}



AJ_Status Cdm_WindDirection_EmitHorizontalAutoModeChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "HorizontalAutoMode", "y", newValue);
}



static AJ_Status WindDirection_GetVerticalDirection(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    WindDirectionModel* model = (WindDirectionModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetVerticalDirection) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetVerticalDirection(model, objPath, out);
}

static AJ_Status clampVerticalDirection(WindDirectionModel* model, const char* objPath, uint16_t value, uint16_t *out)
{

    uint16_t minValue = 0;

    uint16_t maxValue;
    if (model->GetVerticalMax(model, objPath, &maxValue) != AJ_OK)
        return AJ_ERR_FAILURE;

    uint16_t stepValue = 0;

    *out = clamp_uint16(value, minValue, maxValue, stepValue);
    return AJ_OK;
}

static AJ_Status WindDirection_SetVerticalDirection(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t *value)
{
    AJ_Status status;

    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    WindDirectionModel* model = (WindDirectionModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetVerticalDirection) {
        return AJ_ERR_NULL;
    }

    status = clampVerticalDirection(model, objPath, *value, value);
    if (status != AJ_OK)
        return status;

    model->busAttachment = busAttachment;
    status = model->SetVerticalDirection(model, objPath, *value);
    return status;
}



AJ_Status Cdm_WindDirection_EmitVerticalDirectionChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "VerticalDirection", "q", newValue);
}



static AJ_Status WindDirection_GetVerticalMax(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    WindDirectionModel* model = (WindDirectionModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetVerticalMax) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetVerticalMax(model, objPath, out);
}



AJ_Status Cdm_WindDirection_EmitVerticalMaxChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "VerticalMax", "q", newValue);
}



static AJ_Status WindDirection_GetVerticalAutoMode(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    WindDirectionModel* model = (WindDirectionModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetVerticalAutoMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetVerticalAutoMode(model, objPath, out);
}

static AJ_Status ValidateVerticalAutoMode(WindDirectionModel* model, const char* objPath, WindDirection_AutoMode value)
{

    switch (value)
    {
        case WINDDIRECTION_AUTO_MODE_OFF:
        case WINDDIRECTION_AUTO_MODE_ON:
            break;
        case WINDDIRECTION_AUTO_MODE_NOT_SUPPORTED:
        default:
            return AJ_ERR_INVALID;
    }

    return AJ_OK;
}

static AJ_Status WindDirection_SetVerticalAutoMode(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t value)
{
    AJ_Status status;

    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    WindDirectionModel* model = (WindDirectionModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetVerticalAutoMode) {
        return AJ_ERR_NULL;
    }

    status = ValidateVerticalAutoMode(model, objPath, value);
    if (status != AJ_OK)
        return status;

    model->busAttachment = busAttachment;
    status = model->SetVerticalAutoMode(model, objPath, value);
    return status;
}



AJ_Status Cdm_WindDirection_EmitVerticalAutoModeChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "VerticalAutoMode", "y", newValue);
}




/*
   Handler functions
*/
static AJ_Status WindDirection_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case WINDDIRECTION_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case WINDDIRECTION_PROP_HORIZONTAL_DIRECTION:
        {
            uint16_t horizontal_direction;
            memset(&horizontal_direction, 0, sizeof(uint16_t));
            status = WindDirection_GetHorizontalDirection(busAttachment, objPath, &horizontal_direction);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", horizontal_direction);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case WINDDIRECTION_PROP_HORIZONTAL_MAX:
        {
            uint16_t horizontal_max;
            memset(&horizontal_max, 0, sizeof(uint16_t));
            status = WindDirection_GetHorizontalMax(busAttachment, objPath, &horizontal_max);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", horizontal_max);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case WINDDIRECTION_PROP_HORIZONTAL_AUTO_MODE:
        {
            uint8_t horizontal_auto_mode;
            memset(&horizontal_auto_mode, 0, sizeof(uint8_t));
            status = WindDirection_GetHorizontalAutoMode(busAttachment, objPath, &horizontal_auto_mode);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", horizontal_auto_mode);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case WINDDIRECTION_PROP_VERTICAL_DIRECTION:
        {
            uint16_t vertical_direction;
            memset(&vertical_direction, 0, sizeof(uint16_t));
            status = WindDirection_GetVerticalDirection(busAttachment, objPath, &vertical_direction);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", vertical_direction);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case WINDDIRECTION_PROP_VERTICAL_MAX:
        {
            uint16_t vertical_max;
            memset(&vertical_max, 0, sizeof(uint16_t));
            status = WindDirection_GetVerticalMax(busAttachment, objPath, &vertical_max);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", vertical_max);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case WINDDIRECTION_PROP_VERTICAL_AUTO_MODE:
        {
            uint8_t vertical_auto_mode;
            memset(&vertical_auto_mode, 0, sizeof(uint8_t));
            status = WindDirection_GetVerticalAutoMode(busAttachment, objPath, &vertical_auto_mode);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", vertical_auto_mode);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status WindDirection_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case WINDDIRECTION_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case WINDDIRECTION_PROP_HORIZONTAL_DIRECTION:
        {
            uint16_t horizontal_direction;
            status = AJ_UnmarshalArgs(msg, "q", &horizontal_direction);
            if (status == AJ_OK) {
                status = WindDirection_SetHorizontalDirection(busAttachment, objPath, &horizontal_direction);
                if (status == AJ_OK && emitOnSet) {
                    status = Cdm_WindDirection_EmitHorizontalDirectionChanged(busAttachment, objPath, horizontal_direction);
                }
            }
            break;
        }

        case WINDDIRECTION_PROP_HORIZONTAL_AUTO_MODE:
        {
            uint8_t horizontal_auto_mode;
            status = AJ_UnmarshalArgs(msg, "y", &horizontal_auto_mode);
            if (status == AJ_OK) {
                status = WindDirection_SetHorizontalAutoMode(busAttachment, objPath, (WindDirection_AutoMode)(int)horizontal_auto_mode);
                if (status == AJ_OK && emitOnSet) {
                    status = Cdm_WindDirection_EmitHorizontalAutoModeChanged(busAttachment, objPath, horizontal_auto_mode);
                }
            }
            break;
        }

        case WINDDIRECTION_PROP_VERTICAL_DIRECTION:
        {
            uint16_t vertical_direction;
            status = AJ_UnmarshalArgs(msg, "q", &vertical_direction);
            if (status == AJ_OK) {
                status = WindDirection_SetVerticalDirection(busAttachment, objPath, &vertical_direction);
                if (status == AJ_OK && emitOnSet) {
                    status = Cdm_WindDirection_EmitVerticalDirectionChanged(busAttachment, objPath, vertical_direction);
                }
            }
            break;
        }

        case WINDDIRECTION_PROP_VERTICAL_AUTO_MODE:
        {
            uint8_t vertical_auto_mode;
            status = AJ_UnmarshalArgs(msg, "y", &vertical_auto_mode);
            if (status == AJ_OK) {
                status = WindDirection_SetVerticalAutoMode(busAttachment, objPath, (WindDirection_AutoMode)(int)vertical_auto_mode);
                if (status == AJ_OK && emitOnSet) {
                    status = Cdm_WindDirection_EmitVerticalAutoModeChanged(busAttachment, objPath, vertical_auto_mode);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status WindDirection_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerEnvironmentWindDirection = {
    WindDirection_OnGetProperty,
    WindDirection_OnSetProperty,
    WindDirection_OnMethodHandler
};
