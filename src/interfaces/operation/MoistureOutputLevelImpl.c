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
#include <ajtcl/cdm/interfaces/operation/MoistureOutputLevelInterface.h>
#include <ajtcl/cdm/interfaces/operation/MoistureOutputLevelModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME MOISTURE_OUTPUT_LEVEL

const char* const intfDescOperationMoistureOutputLevel[] = {
    "$org.alljoyn.SmartSpaces.Operation.MoistureOutputLevel",
    "@Version>q",
    "@MoistureOutputLevel=y",
    "@MaxMoistureOutputLevel>y",
    "@AutoMode=y",
    NULL
};


void InitArray_MoistureOutputLevel_AutoMode(Array_MoistureOutputLevel_AutoMode* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(MoistureOutputLevel_AutoMode), numElems);
}


void CopyArray_MoistureOutputLevel_AutoMode(Array_MoistureOutputLevel_AutoMode* value, Array_MoistureOutputLevel_AutoMode* copy)
{
    Copy_Array((CDM_Array*)value, sizeof(MoistureOutputLevel_AutoMode), (CDM_Array*)copy);
}


void FreeArray_MoistureOutputLevel_AutoMode(Array_MoistureOutputLevel_AutoMode* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_MoistureOutputLevel_AutoMode(Array_MoistureOutputLevel_AutoMode* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(MoistureOutputLevel_AutoMode), numElems);
}




static AJ_Status MoistureOutputLevel_GetMoistureOutputLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    MoistureOutputLevelModel* model = (MoistureOutputLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMoistureOutputLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMoistureOutputLevel(model, objPath, out);
}



static AJ_Status MoistureOutputLevel_SetMoistureOutputLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    MoistureOutputLevelModel* model = (MoistureOutputLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetMoistureOutputLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetMoistureOutputLevel(model, objPath, value);
}



AJ_Status Cdm_MoistureOutputLevel_EmitMoistureOutputLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MoistureOutputLevel", "y", newValue);
}



static AJ_Status MoistureOutputLevel_GetMaxMoistureOutputLevel(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    MoistureOutputLevelModel* model = (MoistureOutputLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxMoistureOutputLevel) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxMoistureOutputLevel(model, objPath, out);
}



AJ_Status Cdm_MoistureOutputLevel_EmitMaxMoistureOutputLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "MaxMoistureOutputLevel", "y", newValue);
}



static AJ_Status MoistureOutputLevel_GetAutoMode(AJ_BusAttachment* busAttachment, const char* objPath, MoistureOutputLevel_AutoMode* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    MoistureOutputLevelModel* model = (MoistureOutputLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetAutoMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetAutoMode(model, objPath, out);
}



static AJ_Status MoistureOutputLevel_SetAutoMode(AJ_BusAttachment* busAttachment, const char* objPath, MoistureOutputLevel_AutoMode value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    MoistureOutputLevelModel* model = (MoistureOutputLevelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetAutoMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetAutoMode(model, objPath, value);
}



AJ_Status Cdm_MoistureOutputLevel_EmitAutoModeChanged(AJ_BusAttachment *bus, const char *objPath, MoistureOutputLevel_AutoMode newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "AutoMode", "y", newValue);
}




//
// Handler functions
//
static AJ_Status MoistureOutputLevel_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case MOISTUREOUTPUTLEVEL_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case MOISTUREOUTPUTLEVEL_PROP_MOISTURE_OUTPUT_LEVEL:
        {
            uint8_t moisture_output_level;
            status = MoistureOutputLevel_GetMoistureOutputLevel(busAttachment, objPath, &moisture_output_level);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", moisture_output_level);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case MOISTUREOUTPUTLEVEL_PROP_MAX_MOISTURE_OUTPUT_LEVEL:
        {
            uint8_t max_moisture_output_level;
            status = MoistureOutputLevel_GetMaxMoistureOutputLevel(busAttachment, objPath, &max_moisture_output_level);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", max_moisture_output_level);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case MOISTUREOUTPUTLEVEL_PROP_AUTO_MODE:
        {
            MoistureOutputLevel_AutoMode auto_mode;
            status = MoistureOutputLevel_GetAutoMode(busAttachment, objPath, &auto_mode);
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



static AJ_Status MoistureOutputLevel_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case MOISTUREOUTPUTLEVEL_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case MOISTUREOUTPUTLEVEL_PROP_MOISTURE_OUTPUT_LEVEL:
        {
            uint8_t moisture_output_level;
            status = AJ_UnmarshalArgs(msg, "y", &moisture_output_level);
            if (status == AJ_OK) {
                status = MoistureOutputLevel_SetMoistureOutputLevel(busAttachment, objPath, moisture_output_level);
                if (status == AJ_OK) {
                    status= Cdm_MoistureOutputLevel_EmitMoistureOutputLevelChanged(busAttachment, objPath, moisture_output_level);
                }
            }
            break;
        }

        case MOISTUREOUTPUTLEVEL_PROP_AUTO_MODE:
        {
            uint8_t auto_mode;
            status = AJ_UnmarshalArgs(msg, "y", &auto_mode);
            if (status == AJ_OK) {
                status = MoistureOutputLevel_SetAutoMode(busAttachment, objPath, (MoistureOutputLevel_AutoMode)(int)auto_mode);
                if (status == AJ_OK) {
                    status= Cdm_MoistureOutputLevel_EmitAutoModeChanged(busAttachment, objPath, auto_mode);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status MoistureOutputLevel_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationMoistureOutputLevel = {
    MoistureOutputLevel_OnGetProperty,
    MoistureOutputLevel_OnSetProperty,
    MoistureOutputLevel_OnMethodHandler
};
