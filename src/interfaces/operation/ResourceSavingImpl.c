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
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceValidation.h>
#include <ajtcl/cdm/interfaces/operation/ResourceSavingInterface.h>
#include <ajtcl/cdm/interfaces/operation/ResourceSavingModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME RESOURCE_SAVING

const char* const intfDescOperationResourceSaving[] = {
    "$org.alljoyn.SmartSpaces.Operation.ResourceSaving",
    "@Version>q",
    "@ResourceSavingMode=b",
    NULL
};




static AJ_Status ResourceSaving_GetResourceSavingMode(AJ_BusAttachment* busAttachment, const char* objPath, bool* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    ResourceSavingModel* model = (ResourceSavingModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetResourceSavingMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetResourceSavingMode(model, objPath, out);
}

static AJ_Status ResourceSaving_SetResourceSavingMode(AJ_BusAttachment* busAttachment, const char* objPath, bool value)
{
    AJ_Status status;

    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    ResourceSavingModel* model = (ResourceSavingModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetResourceSavingMode) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    status = model->SetResourceSavingMode(model, objPath, value);
    return status;
}



AJ_Status Cdm_ResourceSaving_EmitResourceSavingModeChanged(AJ_BusAttachment *bus, const char *objPath, bool newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "ResourceSavingMode", "b", newValue);
}




/*
   Handler functions
*/
static AJ_Status ResourceSaving_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case RESOURCESAVING_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case RESOURCESAVING_PROP_RESOURCE_SAVING_MODE:
        {
            bool resource_saving_mode;
            memset(&resource_saving_mode, 0, sizeof(bool));
            status = ResourceSaving_GetResourceSavingMode(busAttachment, objPath, &resource_saving_mode);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "b", resource_saving_mode);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status ResourceSaving_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case RESOURCESAVING_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case RESOURCESAVING_PROP_RESOURCE_SAVING_MODE:
        {
            bool resource_saving_mode;
            status = AJ_UnmarshalArgs(msg, "b", &resource_saving_mode);
            if (status == AJ_OK) {
                status = ResourceSaving_SetResourceSavingMode(busAttachment, objPath, resource_saving_mode);
                if (status == AJ_OK && emitOnSet) {
                    status = Cdm_ResourceSaving_EmitResourceSavingModeChanged(busAttachment, objPath, resource_saving_mode);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status ResourceSaving_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationResourceSaving = {
    ResourceSaving_OnGetProperty,
    ResourceSaving_OnSetProperty,
    ResourceSaving_OnMethodHandler
};
