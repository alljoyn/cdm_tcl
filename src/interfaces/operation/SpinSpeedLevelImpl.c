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
#include <ajtcl/cdm/interfaces/operation/SpinSpeedLevelInterface.h>
#include <ajtcl/cdm/interfaces/operation/SpinSpeedLevelModel.h>

#include <ajtcl/cdm/utils/CdmArray.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME SPIN_SPEED_LEVEL

const char* const intfDescOperationSpinSpeedLevel[] = {
    "$org.alljoyn.SmartSpaces.Operation.SpinSpeedLevel",
    "@Version>q",
    "@MaxLevel>y",
    "@TargetLevel=y",
    "@SelectableLevels>ay",
    NULL
};




static AJ_Status SpinSpeedLevel_GetMaxLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    SpinSpeedLevelModel* model = (SpinSpeedLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxLevel(model, objPath, out);
}



static AJ_Status SpinSpeedLevel_GetTargetLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    SpinSpeedLevelModel* model = (SpinSpeedLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTargetLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetTargetLevel(model, objPath, out);
}

static AJ_Status ValidateTargetLevel(SpinSpeedLevelModel* model, const char* objPath, uint8_t value)
{

    Array_uint8 validValues;
    if (model->GetSelectableLevels(model, objPath, &validValues) != AJ_OK)
        return AJ_ERR_FAILURE;

    AJ_Status status = (valueIn_Array_uint8(value, &validValues) == 1) ? AJ_OK : AJ_ERR_NO_MATCH;

    FreeArray_uint8(&validValues);
    return status;
}

static AJ_Status clampTargetLevel(SpinSpeedLevelModel* model, const char* objPath, uint8_t value, uint8_t *out)
{

    uint8_t minValue = 0;

    uint8_t maxValue;
    if (model->GetMaxLevel(model, objPath, &maxValue) != AJ_OK)
        return AJ_ERR_FAILURE;

    uint8_t stepValue = 0;

    *out = clamp_uint8(value, minValue, maxValue, stepValue);
    return AJ_OK;
}

static AJ_Status SpinSpeedLevel_SetTargetLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t *value)
{
    AJ_Status status;

    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    SpinSpeedLevelModel* model = (SpinSpeedLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetTargetLevel) {
        return AJ_ERR_NULL;
    }

    status = clampTargetLevel(model, objPath, *value, value);
    if (status != AJ_OK)
        return status;

    status = ValidateTargetLevel(model, objPath, *value);
    if (status != AJ_OK)
        return status;

    model->busAttachment = busAttachment;
    status = model->SetTargetLevel(model, objPath, *value);
    return status;
}



AJ_Status Cdm_SpinSpeedLevel_EmitTargetLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "TargetLevel", "y", newValue);
}



static AJ_Status SpinSpeedLevel_GetSelectableLevels(AJ_BusAttachment* busAttachment, const char* objPath, Array_uint8* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    SpinSpeedLevelModel* model = (SpinSpeedLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetSelectableLevels) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetSelectableLevels(model, objPath, out);
}



AJ_Status Cdm_SpinSpeedLevel_EmitSelectableLevelsChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "SelectableLevels", "ay", newValue.elems, newValue.numElems);
}




/*
   Handler functions
*/
static AJ_Status SpinSpeedLevel_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case SPINSPEEDLEVEL_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case SPINSPEEDLEVEL_PROP_MAX_LEVEL:
        {
            uint8_t max_level;
            memset(&max_level, 0, sizeof(uint8_t));
            status = SpinSpeedLevel_GetMaxLevel(busAttachment, objPath, &max_level);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", max_level);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case SPINSPEEDLEVEL_PROP_TARGET_LEVEL:
        {
            uint8_t target_level;
            memset(&target_level, 0, sizeof(uint8_t));
            status = SpinSpeedLevel_GetTargetLevel(busAttachment, objPath, &target_level);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", target_level);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case SPINSPEEDLEVEL_PROP_SELECTABLE_LEVELS:
        {
            Array_uint8 selectable_levels;
            memset(&selectable_levels, 0, sizeof(Array_uint8));
            status = SpinSpeedLevel_GetSelectableLevels(busAttachment, objPath, &selectable_levels);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "ay", selectable_levels.elems, sizeof(uint8_t) * selectable_levels.numElems);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                FreeArray_uint8(&selectable_levels);
            }
            break;
        }
    }

    return status;
}



static AJ_Status SpinSpeedLevel_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case SPINSPEEDLEVEL_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case SPINSPEEDLEVEL_PROP_TARGET_LEVEL:
        {
            uint8_t target_level;
            status = AJ_UnmarshalArgs(msg, "y", &target_level);
            if (status == AJ_OK) {
                status = SpinSpeedLevel_SetTargetLevel(busAttachment, objPath, &target_level);
                if (status == AJ_OK && emitOnSet) {
                    status = Cdm_SpinSpeedLevel_EmitTargetLevelChanged(busAttachment, objPath, target_level);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status SpinSpeedLevel_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationSpinSpeedLevel = {
    SpinSpeedLevel_OnGetProperty,
    SpinSpeedLevel_OnSetProperty,
    SpinSpeedLevel_OnMethodHandler
};
