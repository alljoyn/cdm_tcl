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
#include <ajtcl/cdm/interfaces/operation/AirRecirculationModeInterface.h>
#include <ajtcl/cdm/interfaces/operation/AirRecirculationModeModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME AIR_RECIRCULATION_MODE

const char* const intfDescOperationAirRecirculationMode[] = {
    "$org.alljoyn.SmartSpaces.Operation.AirRecirculationMode",
    "@Version>q",
    "@IsRecirculating=b",
    NULL
};




static AJ_Status AirRecirculationMode_GetIsRecirculating(AJ_BusAttachment* busAttachment, const char* objPath, bool* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    AirRecirculationModeModel* model = (AirRecirculationModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetIsRecirculating) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetIsRecirculating(model, objPath, out);
}



static AJ_Status AirRecirculationMode_SetIsRecirculating(AJ_BusAttachment* busAttachment, const char* objPath, bool value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    AirRecirculationModeModel* model = (AirRecirculationModeModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetIsRecirculating) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetIsRecirculating(model, objPath, value);
}



AJ_Status Cdm_AirRecirculationMode_EmitIsRecirculatingChanged(AJ_BusAttachment *bus, const char *objPath, bool newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "IsRecirculating", "b", newValue);
}




//
// Handler functions
//
static AJ_Status AirRecirculationMode_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case AIRRECIRCULATIONMODE_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case AIRRECIRCULATIONMODE_PROP_IS_RECIRCULATING:
        {
            bool is_recirculating;
            status = AirRecirculationMode_GetIsRecirculating(busAttachment, objPath, &is_recirculating);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "b", is_recirculating);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status AirRecirculationMode_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case AIRRECIRCULATIONMODE_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case AIRRECIRCULATIONMODE_PROP_IS_RECIRCULATING:
        {
            bool is_recirculating;
            status = AJ_UnmarshalArgs(msg, "b", &is_recirculating);
            if (status == AJ_OK) {
                status = AirRecirculationMode_SetIsRecirculating(busAttachment, objPath, is_recirculating);
                if (status == AJ_OK) {
                    status= Cdm_AirRecirculationMode_EmitIsRecirculatingChanged(busAttachment, objPath, is_recirculating);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status AirRecirculationMode_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationAirRecirculationMode = {
    AirRecirculationMode_OnGetProperty,
    AirRecirculationMode_OnSetProperty,
    AirRecirculationMode_OnMethodHandler
};
