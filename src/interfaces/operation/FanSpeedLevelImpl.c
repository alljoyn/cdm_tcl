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
#include <ajtcl/cdm/interfaces/operation/FanSpeedLevelInterface.h>
#include <ajtcl/cdm/interfaces/operation/FanSpeedLevelModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME FAN_SPEED_LEVEL

const char* const intfDescOperationFanSpeedLevel[] = {
    "$org.alljoyn.SmartSpaces.Operation.FanSpeedLevel",
    "@Version>q",
    "@FanSpeedLevel=y",
    "@MaxFanSpeedLevel>y",
    "@AutoMode=y",
    NULL
};


void InitArray_FanSpeedLevel_AutoMode(Array_FanSpeedLevel_AutoMode* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(FanSpeedLevel_AutoMode), numElems);
}


void CopyArray_FanSpeedLevel_AutoMode(Array_FanSpeedLevel_AutoMode* value, Array_FanSpeedLevel_AutoMode* copy)
{
    Copy_Array((CDM_Array*)value, sizeof(FanSpeedLevel_AutoMode), (CDM_Array*)copy);
}


void FreeArray_FanSpeedLevel_AutoMode(Array_FanSpeedLevel_AutoMode* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_FanSpeedLevel_AutoMode(Array_FanSpeedLevel_AutoMode* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(FanSpeedLevel_AutoMode), numElems);
}




static AJ_Status FanSpeedLevel_GetFanSpeedLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    FanSpeedLevelModel* model = (FanSpeedLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetFanSpeedLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetFanSpeedLevel(model, objPath, out);
}



static AJ_Status FanSpeedLevel_SetFanSpeedLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    FanSpeedLevelModel* model = (FanSpeedLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetFanSpeedLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetFanSpeedLevel(model, objPath, value);
}



AJ_Status Cdm_FanSpeedLevel_EmitFanSpeedLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "FanSpeedLevel", "y", newValue);
}



static AJ_Status FanSpeedLevel_GetMaxFanSpeedLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    FanSpeedLevelModel* model = (FanSpeedLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxFanSpeedLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxFanSpeedLevel(model, objPath, out);
}



static AJ_Status FanSpeedLevel_GetAutoMode(AJ_BusAttachment* busAttachment, const char* objPath, FanSpeedLevel_AutoMode* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    FanSpeedLevelModel* model = (FanSpeedLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetAutoMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetAutoMode(model, objPath, out);
}



static AJ_Status FanSpeedLevel_SetAutoMode(AJ_BusAttachment* busAttachment, const char* objPath, FanSpeedLevel_AutoMode value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    FanSpeedLevelModel* model = (FanSpeedLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetAutoMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetAutoMode(model, objPath, value);
}



AJ_Status Cdm_FanSpeedLevel_EmitAutoModeChanged(AJ_BusAttachment *bus, const char *objPath, FanSpeedLevel_AutoMode newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "AutoMode", "y", newValue);
}




//
// Handler functions
//
static AJ_Status FanSpeedLevel_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case FANSPEEDLEVEL_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case FANSPEEDLEVEL_PROP_FAN_SPEED_LEVEL:
        {
            uint8_t fan_speed_level;
            status = FanSpeedLevel_GetFanSpeedLevel(busAttachment, objPath, &fan_speed_level);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", fan_speed_level);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case FANSPEEDLEVEL_PROP_MAX_FAN_SPEED_LEVEL:
        {
            uint8_t max_fan_speed_level;
            status = FanSpeedLevel_GetMaxFanSpeedLevel(busAttachment, objPath, &max_fan_speed_level);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", max_fan_speed_level);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case FANSPEEDLEVEL_PROP_AUTO_MODE:
        {
            FanSpeedLevel_AutoMode auto_mode;
            status = FanSpeedLevel_GetAutoMode(busAttachment, objPath, &auto_mode);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", auto_mode);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status FanSpeedLevel_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case FANSPEEDLEVEL_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case FANSPEEDLEVEL_PROP_FAN_SPEED_LEVEL:
        {
            uint8_t fan_speed_level;
            status = AJ_UnmarshalArgs(msg, "y", &fan_speed_level);
            if (status == AJ_OK) {
                status = FanSpeedLevel_SetFanSpeedLevel(busAttachment, objPath, fan_speed_level);
                if (status == AJ_OK) {
                    status= Cdm_FanSpeedLevel_EmitFanSpeedLevelChanged(busAttachment, objPath, fan_speed_level);
                }
            }
            break;
        }

        case FANSPEEDLEVEL_PROP_AUTO_MODE:
        {
            uint8_t auto_mode;
            status = AJ_UnmarshalArgs(msg, "y", &auto_mode);
            if (status == AJ_OK) {
                status = FanSpeedLevel_SetAutoMode(busAttachment, objPath, (FanSpeedLevel_AutoMode)(int)auto_mode);
                if (status == AJ_OK) {
                    status= Cdm_FanSpeedLevel_EmitAutoModeChanged(busAttachment, objPath, auto_mode);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status FanSpeedLevel_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationFanSpeedLevel = {
    FanSpeedLevel_OnGetProperty,
    FanSpeedLevel_OnSetProperty,
    FanSpeedLevel_OnMethodHandler
};
