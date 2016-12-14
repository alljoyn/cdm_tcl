/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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
#include <ajtcl/cdm/interfaces/operation/FilterStatusInterface.h>
#include <ajtcl/cdm/interfaces/operation/FilterStatusModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME FILTER_STATUS

const char* const intfDescOperationFilterStatus[] = {
    "$org.alljoyn.SmartSpaces.Operation.FilterStatus",
    "@Version>q",
    "@ExpectedLifeInDays>q",
    "@IsCleanable>b",
    "@OrderPercentage>y",
    "@Manufacturer>s",
    "@PartNumber>s",
    "@Url>s",
    "@LifeRemaining>y",
    NULL
};




static AJ_Status FilterStatus_GetExpectedLifeInDays(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    FilterStatusModel* model = (FilterStatusModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetExpectedLifeInDays) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetExpectedLifeInDays(model, objPath, out);
}



AJ_Status Cdm_FilterStatus_EmitExpectedLifeInDaysChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "ExpectedLifeInDays", "q", newValue);
}



static AJ_Status FilterStatus_GetIsCleanable(AJ_BusAttachment* busAttachment, const char* objPath, bool* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    FilterStatusModel* model = (FilterStatusModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetIsCleanable) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetIsCleanable(model, objPath, out);
}



AJ_Status Cdm_FilterStatus_EmitIsCleanableChanged(AJ_BusAttachment *bus, const char *objPath, bool newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "IsCleanable", "b", newValue);
}



static AJ_Status FilterStatus_GetOrderPercentage(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    FilterStatusModel* model = (FilterStatusModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetOrderPercentage) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetOrderPercentage(model, objPath, out);
}



AJ_Status Cdm_FilterStatus_EmitOrderPercentageChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "OrderPercentage", "y", newValue);
}



static AJ_Status FilterStatus_GetManufacturer(AJ_BusAttachment* busAttachment, const char* objPath, char const** out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    FilterStatusModel* model = (FilterStatusModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetManufacturer) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetManufacturer(model, objPath, out);
}



static AJ_Status FilterStatus_GetPartNumber(AJ_BusAttachment* busAttachment, const char* objPath, char const** out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    FilterStatusModel* model = (FilterStatusModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetPartNumber) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetPartNumber(model, objPath, out);
}



static AJ_Status FilterStatus_GetUrl(AJ_BusAttachment* busAttachment, const char* objPath, char const** out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    FilterStatusModel* model = (FilterStatusModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetUrl) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetUrl(model, objPath, out);
}



static AJ_Status FilterStatus_GetLifeRemaining(AJ_BusAttachment* busAttachment, const char* objPath, uint8_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    FilterStatusModel* model = (FilterStatusModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetLifeRemaining) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetLifeRemaining(model, objPath, out);
}



AJ_Status Cdm_FilterStatus_EmitLifeRemainingChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "LifeRemaining", "y", newValue);
}




//
// Handler functions
//
static AJ_Status FilterStatus_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case FILTERSTATUS_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case FILTERSTATUS_PROP_EXPECTED_LIFE_IN_DAYS:
        {
            uint16_t expected_life_in_days;
            status = FilterStatus_GetExpectedLifeInDays(busAttachment, objPath, &expected_life_in_days);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", expected_life_in_days);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case FILTERSTATUS_PROP_IS_CLEANABLE:
        {
            bool is_cleanable;
            status = FilterStatus_GetIsCleanable(busAttachment, objPath, &is_cleanable);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "b", is_cleanable);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case FILTERSTATUS_PROP_ORDER_PERCENTAGE:
        {
            uint8_t order_percentage;
            status = FilterStatus_GetOrderPercentage(busAttachment, objPath, &order_percentage);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", order_percentage);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case FILTERSTATUS_PROP_MANUFACTURER:
        {
            char const* manufacturer;
            status = FilterStatus_GetManufacturer(busAttachment, objPath, &manufacturer);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "s", manufacturer);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                free((void*)manufacturer);
            }
            break;
        }

        case FILTERSTATUS_PROP_PART_NUMBER:
        {
            char const* part_number;
            status = FilterStatus_GetPartNumber(busAttachment, objPath, &part_number);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "s", part_number);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                free((void*)part_number);
            }
            break;
        }

        case FILTERSTATUS_PROP_URL:
        {
            char const* url;
            status = FilterStatus_GetUrl(busAttachment, objPath, &url);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "s", url);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                free((void*)url);
            }
            break;
        }

        case FILTERSTATUS_PROP_LIFE_REMAINING:
        {
            uint8_t life_remaining;
            status = FilterStatus_GetLifeRemaining(busAttachment, objPath, &life_remaining);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "y", life_remaining);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status FilterStatus_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case FILTERSTATUS_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status FilterStatus_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    return status;
}



const InterfaceHandler intfHandlerOperationFilterStatus = {
    FilterStatus_OnGetProperty,
    FilterStatus_OnSetProperty,
    FilterStatus_OnMethodHandler
};