/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#include <ajtcl/cdm/interfaces/operation/OffControlInterface.h>
#include <ajtcl/cdm/interfaces/operation/OffControlModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME OFF_CONTROL

const char* const intfDescOperationOffControl[] = {
    "$org.alljoyn.SmartSpaces.Operation.OffControl",
    "@Version>q",
    "?SwitchOff",
    NULL
};




static AJ_Status Cdm_OffControl_CallSwitchOff(AJ_BusAttachment* busAttachment, const char *objPath)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    OffControlModel* model = (OffControlModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->MethodSwitchOff) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->MethodSwitchOff(model, objPath);
}



//
// Handler functions
//
static AJ_Status OffControl_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case OFFCONTROL_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;
    }

    return status;
}



static AJ_Status OffControl_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case OFFCONTROL_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status OffControl_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {

    case OFFCONTROL_METHOD_SWITCH_OFF:
    {

        status = Cdm_OffControl_CallSwitchOff(busAttachment, objPath);

        AJ_Message reply;
        AJ_MarshalReplyMsg(msg, &reply);

        if (status == AJ_OK) {
            status = AJ_DeliverMsg(&reply);
        }

        break;
    }
    }

    return status;
}



const InterfaceHandler intfHandlerOperationOffControl = {
    OffControl_OnGetProperty,
    OffControl_OnSetProperty,
    OffControl_OnMethodHandler
};