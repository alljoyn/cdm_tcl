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
#include <ajtcl/cdm/interfaces/operation/AlertsInterface.h>
#include <ajtcl/cdm/interfaces/operation/AlertsModel.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME ALERTS

const char* const intfDescOperationAlerts[] = {
    "$org.alljoyn.SmartSpaces.Operation.Alerts",
    "@Version>q",
    "@Alerts>a(yqb)",
    "?GetAlertCodesDescription languageTag<s description>a(qs)",
    "?AcknowledgeAlert alertCode<q",
    "?AcknowledgeAllAlerts",
    NULL
};



void FreeFields_Alerts_AlertRecord(Alerts_AlertRecord* value)
{
    
    
    
}


void InitArray_Alerts_AlertRecord(Array_Alerts_AlertRecord* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(Alerts_AlertRecord), numElems);
}


/* Note: this only allows fields that are char*, not any other kind of pointer */
void CopyArray_Alerts_AlertRecord(Array_Alerts_AlertRecord* value, Array_Alerts_AlertRecord* copy)
{
    if (value->elems) {
        copy->elems = malloc(value->numElems * sizeof(Alerts_AlertRecord));
        for (size_t i = 0; i < value->numElems; ++i) {
            copy->elems[i].severity = value->elems[i].severity;
            copy->elems[i].alertCode = value->elems[i].alertCode;
            copy->elems[i].needAcknowledgement = value->elems[i].needAcknowledgement;
        }
    } else {
        copy->elems = NULL;
    }

    copy->numElems = value->numElems;

}


void FreeArray_Alerts_AlertRecord(Array_Alerts_AlertRecord* value)
{
    for (size_t i = 0; i < value->numElems; ++i) {
        FreeFields_Alerts_AlertRecord(&value->elems[i]);
    }
    free(value->elems);
}


size_t ExtendArray_Alerts_AlertRecord(Array_Alerts_AlertRecord* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(Alerts_AlertRecord), numElems);
}



void FreeFields_Alerts_AlertCodesDescriptor(Alerts_AlertCodesDescriptor* value)
{
    
    free((void*)value->description);

}


void InitArray_Alerts_AlertCodesDescriptor(Array_Alerts_AlertCodesDescriptor* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(Alerts_AlertCodesDescriptor), numElems);
}


/* Note: this only allows fields that are char*, not any other kind of pointer */
void CopyArray_Alerts_AlertCodesDescriptor(Array_Alerts_AlertCodesDescriptor* value, Array_Alerts_AlertCodesDescriptor* copy)
{
    if (value->elems) {
        copy->elems = malloc(value->numElems * sizeof(Alerts_AlertCodesDescriptor));
        for (size_t i = 0; i < value->numElems; ++i) {
            copy->elems[i].alertCode = value->elems[i].alertCode;
            copy->elems[i].description = strdup(value->elems[i].description);
        }
    } else {
        copy->elems = NULL;
    }

    copy->numElems = value->numElems;

}


void FreeArray_Alerts_AlertCodesDescriptor(Array_Alerts_AlertCodesDescriptor* value)
{
    for (size_t i = 0; i < value->numElems; ++i) {
        FreeFields_Alerts_AlertCodesDescriptor(&value->elems[i]);
    }
    free(value->elems);
}


size_t ExtendArray_Alerts_AlertCodesDescriptor(Array_Alerts_AlertCodesDescriptor* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(Alerts_AlertCodesDescriptor), numElems);
}


void InitArray_Alerts_Severity(Array_Alerts_Severity* value, size_t numElems)
{
    Init_Array((CDM_Array*)value, sizeof(Alerts_Severity), numElems);
}


void CopyArray_Alerts_Severity(Array_Alerts_Severity* value, Array_Alerts_Severity* copy)
{
    Copy_Array((CDM_Array*)value, sizeof(Alerts_Severity), (CDM_Array*)copy);
}


void FreeArray_Alerts_Severity(Array_Alerts_Severity* value)
{
    free((void*)value->elems);
    value->elems = 0;
}


size_t ExtendArray_Alerts_Severity(Array_Alerts_Severity* value, size_t numElems)
{
    return Extend_Array((CDM_Array*)value, sizeof(Alerts_Severity), numElems);
}




static AJ_Status Alerts_GetAlerts(AJ_BusAttachment* busAttachment, const char* objPath, Array_Alerts_AlertRecord* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    AlertsModel* model = (AlertsModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetAlerts) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetAlerts(model, objPath, out);
}
 



static AJ_Status MarshalAlerts(AJ_Message* msg, void* structure, const char* structSignature)
{
    Alerts_AlertRecord* value = (Alerts_AlertRecord*)structure;
    AJ_MarshalArgs(msg, "y", value->severity);
    AJ_MarshalArgs(msg, "q", value->alertCode);
    AJ_MarshalArgs(msg, "b", value->needAcknowledgement);
    return AJ_OK;
}



AJ_Status Cdm_Alerts_EmitAlertsChanged(AJ_BusAttachment *bus, const char *objPath, Array_Alerts_AlertRecord newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "Alerts", "a(yqb)", newValue.elems, newValue.numElems, sizeof(*newValue.elems), MarshalAlerts);
}



static AJ_Status Cdm_Alerts_CallGetAlertCodesDescription(AJ_BusAttachment* busAttachment, const char *objPath, char const* languageTag, Array_Alerts_AlertCodesDescriptor* description)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    AlertsModel* model = (AlertsModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->MethodGetAlertCodesDescription) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->MethodGetAlertCodesDescription(model, objPath, languageTag, description);
}


static AJ_Status Cdm_Alerts_CallAcknowledgeAlert(AJ_BusAttachment* busAttachment, const char *objPath, uint16_t alertCode)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    AlertsModel* model = (AlertsModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->MethodAcknowledgeAlert) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->MethodAcknowledgeAlert(model, objPath, alertCode);
}


static AJ_Status Cdm_Alerts_CallAcknowledgeAllAlerts(AJ_BusAttachment* busAttachment, const char *objPath)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    AlertsModel* model = (AlertsModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->MethodAcknowledgeAllAlerts) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->MethodAcknowledgeAllAlerts(model, objPath);
}



/*
   Handler functions
*/
static AJ_Status Alerts_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case ALERTS_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case ALERTS_PROP_ALERTS:
        {
            Array_Alerts_AlertRecord alerts;
            memset(&alerts, 0, sizeof(Array_Alerts_AlertRecord));
            status = Alerts_GetAlerts(busAttachment, objPath, &alerts);
            if (status == AJ_OK) {
                AJ_Arg array;
                int i=0;
                status |= AJ_MarshalContainer(replyMsg, &array, AJ_ARG_ARRAY);
                for (; i<alerts.numElems; ++i)
                {
                    AJ_Arg strc;
                    status |= AJ_MarshalContainer(replyMsg, &strc, AJ_ARG_STRUCT);
                    AJ_MarshalArgs(replyMsg, "yqb", alerts.elems[i].severity, alerts.elems[i].alertCode, alerts.elems[i].needAcknowledgement);
                    AJ_MarshalCloseContainer(replyMsg, &strc);
                }
                AJ_MarshalCloseContainer(replyMsg, &array);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                FreeArray_Alerts_AlertRecord(&alerts);
            }
            break;
        }
    }

    return status;
}



static AJ_Status Alerts_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case ALERTS_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status Alerts_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {

    case ALERTS_METHOD_GET_ALERT_CODES_DESCRIPTION:
    {
        AJ_Message reply;
        char const* language_tag;
        status = AJ_UnmarshalArgs(msg, "s", &language_tag);

        if (status != AJ_OK) {
            return status;
        }
        Array_Alerts_AlertCodesDescriptor description;
        memset(&description, 0, sizeof(Array_Alerts_AlertCodesDescriptor));

        status = Cdm_Alerts_CallGetAlertCodesDescription(busAttachment, objPath, language_tag, &description);

        AJ_MarshalReplyMsg(msg, &reply);
        if (status == AJ_OK) {
            AJ_Arg array;
            int i=0;
            status |= AJ_MarshalContainer(&reply, &array, AJ_ARG_ARRAY);
            for (; i<description.numElems; ++i)
            {
                AJ_Arg strc;
                status |= AJ_MarshalContainer(&reply, &strc, AJ_ARG_STRUCT);
                AJ_MarshalArgs(&reply, "qs", description.elems[i].alertCode, description.elems[i].description);
                AJ_MarshalCloseContainer(&reply, &strc);
            }
            AJ_MarshalCloseContainer(&reply, &array);
            if (status == AJ_OK) {
                status = AJ_DeliverMsg(&reply);
            }
        }

        FreeArray_Alerts_AlertCodesDescriptor(&description);
        break;
    }

    case ALERTS_METHOD_ACKNOWLEDGE_ALERT:
    {
        AJ_Message reply;
        uint16_t alert_code;
        status = AJ_UnmarshalArgs(msg, "q", &alert_code);

        if (status != AJ_OK) {
            return status;
        }

        status = Cdm_Alerts_CallAcknowledgeAlert(busAttachment, objPath, alert_code);

        AJ_MarshalReplyMsg(msg, &reply);
        if (status == AJ_OK) {
            status = AJ_DeliverMsg(&reply);
        }

        break;
    }

    case ALERTS_METHOD_ACKNOWLEDGE_ALL_ALERTS:
    {
        AJ_Message reply;

        status = Cdm_Alerts_CallAcknowledgeAllAlerts(busAttachment, objPath);

        AJ_MarshalReplyMsg(msg, &reply);
        if (status == AJ_OK) {
            status = AJ_DeliverMsg(&reply);
        }

        break;
    }
    }

    return status;
}



const InterfaceHandler intfHandlerOperationAlerts = {
    Alerts_OnGetProperty,
    Alerts_OnSetProperty,
    Alerts_OnMethodHandler
};
