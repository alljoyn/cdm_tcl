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

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/operation/RapidModeTimedInterface.h>
#include <ajtcl/cdm/interfaces/operation/RapidModeTimedModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME RAPID_MODE_TIMED

const char* const intfDescOperationRapidModeTimed[] = {
    "$org.alljoyn.SmartSpaces.Operation.RapidModeTimed",
    "@Version>q",
    "@RapidModeMinutesRemaining=q",
    "@MaxSetMinutes>q",
    NULL
};




static AJ_Status RapidModeTimed_GetRapidModeMinutesRemaining(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    RapidModeTimedModel* model = (RapidModeTimedModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetRapidModeMinutesRemaining) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetRapidModeMinutesRemaining(model, objPath, out);
}



static AJ_Status RapidModeTimed_SetRapidModeMinutesRemaining(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t value)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    RapidModeTimedModel* model = (RapidModeTimedModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetRapidModeMinutesRemaining) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->SetRapidModeMinutesRemaining(model, objPath, value);
}



AJ_Status Cdm_RapidModeTimed_EmitRapidModeMinutesRemainingChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "RapidModeMinutesRemaining", "q", newValue);
}



static AJ_Status RapidModeTimed_GetMaxSetMinutes(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    RapidModeTimedModel* model = (RapidModeTimedModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetMaxSetMinutes) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetMaxSetMinutes(model, objPath, out);
}




//
// Handler functions
//
static AJ_Status RapidModeTimed_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case RAPIDMODETIMED_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case RAPIDMODETIMED_PROP_RAPID_MODE_MINUTES_REMAINING:
        {
            uint16_t rapid_mode_minutes_remaining;
            status = RapidModeTimed_GetRapidModeMinutesRemaining(busAttachment, objPath, &rapid_mode_minutes_remaining);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", rapid_mode_minutes_remaining);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case RAPIDMODETIMED_PROP_MAX_SET_MINUTES:
        {
            uint16_t max_set_minutes;
            status = RapidModeTimed_GetMaxSetMinutes(busAttachment, objPath, &max_set_minutes);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", max_set_minutes);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status RapidModeTimed_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case RAPIDMODETIMED_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case RAPIDMODETIMED_PROP_RAPID_MODE_MINUTES_REMAINING:
        {
            uint16_t rapid_mode_minutes_remaining;
            status = AJ_UnmarshalArgs(msg, "q", &rapid_mode_minutes_remaining);
            if (status == AJ_OK) {
                status = RapidModeTimed_SetRapidModeMinutesRemaining(busAttachment, objPath, rapid_mode_minutes_remaining);
                if (status == AJ_OK) {
                    status= Cdm_RapidModeTimed_EmitRapidModeMinutesRemainingChanged(busAttachment, objPath, rapid_mode_minutes_remaining);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status RapidModeTimed_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationRapidModeTimed = {
    RapidModeTimed_OnGetProperty,
    RapidModeTimed_OnSetProperty,
    RapidModeTimed_OnMethodHandler
};