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

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "AlertsModelImpl.h"
#include "../../../Utils/HAL.h"



static Element* HAL_Encode_Alerts_AlertRecord(Alerts_AlertRecord value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Alerts_AlertRecord(Alerts_AlertRecord value, Element* parent)
{
    Element* struc = BSXML_NewElement("struct", parent);
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "severity");
        HAL_Encode_UInt(value.severity, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "alertCode");
        HAL_Encode_UInt(value.alertCode, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "needAcknowledgement");
        HAL_Encode_Bool(value.needAcknowledgement, field);
    }
    return struc;
}



static void HAL_Decode_Alerts_AlertRecord(Element* elem, Alerts_AlertRecord* value) UNUSED_OK;

static void HAL_Decode_Alerts_AlertRecord(Element* elem, Alerts_AlertRecord* value)
{
    if (strcmp(elem->name, "struct") == 0 && elem->numChildren == 3) {
        value->severity = HAL_Decode_UInt(elem->children[0]->children[0]);
        value->alertCode = HAL_Decode_UInt(elem->children[1]->children[0]);
        value->needAcknowledgement = HAL_Decode_Bool(elem->children[2]->children[0]);
    }
}



static Element* HAL_Encode_Array_Alerts_AlertRecord(Array_Alerts_AlertRecord value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_Alerts_AlertRecord(Array_Alerts_AlertRecord value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Alerts_AlertRecord(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_Alerts_AlertRecord(Element* elem, Array_Alerts_AlertRecord* value) UNUSED_OK;

static void HAL_Decode_Array_Alerts_AlertRecord(Element* elem, Array_Alerts_AlertRecord* value)
{
    InitArray_Alerts_AlertRecord(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_Alerts_AlertRecord(value, 1);
            HAL_Decode_Alerts_AlertRecord(elem->children[i], &value->elems[j]);
        }
    }
}



static Element* HAL_Encode_Alerts_AlertCodesDescriptor(Alerts_AlertCodesDescriptor value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Alerts_AlertCodesDescriptor(Alerts_AlertCodesDescriptor value, Element* parent)
{
    Element* struc = BSXML_NewElement("struct", parent);
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "alertCode");
        HAL_Encode_UInt(value.alertCode, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "description");
        HAL_Encode_String(value.description, field);
    }
    return struc;
}



static void HAL_Decode_Alerts_AlertCodesDescriptor(Element* elem, Alerts_AlertCodesDescriptor* value) UNUSED_OK;

static void HAL_Decode_Alerts_AlertCodesDescriptor(Element* elem, Alerts_AlertCodesDescriptor* value)
{
    if (strcmp(elem->name, "struct") == 0 && elem->numChildren == 2) {
        value->alertCode = HAL_Decode_UInt(elem->children[0]->children[0]);
        value->description = HAL_Decode_String(elem->children[1]->children[0]);
    }
}



static Element* HAL_Encode_Array_Alerts_AlertCodesDescriptor(Array_Alerts_AlertCodesDescriptor value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_Alerts_AlertCodesDescriptor(Array_Alerts_AlertCodesDescriptor value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Alerts_AlertCodesDescriptor(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_Alerts_AlertCodesDescriptor(Element* elem, Array_Alerts_AlertCodesDescriptor* value) UNUSED_OK;

static void HAL_Decode_Array_Alerts_AlertCodesDescriptor(Element* elem, Array_Alerts_AlertCodesDescriptor* value)
{
    InitArray_Alerts_AlertCodesDescriptor(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_Alerts_AlertCodesDescriptor(value, 1);
            HAL_Decode_Alerts_AlertCodesDescriptor(elem->children[i], &value->elems[j]);
        }
    }
}


static Element* HAL_Encode_Alerts_Severity(Alerts_Severity value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Alerts_Severity(Alerts_Severity value, Element* parent)
{
    return HAL_Encode_UInt(value, parent);
}



static void HAL_Decode_Alerts_Severity(Element* elem, uint8_t *value) UNUSED_OK;

static void HAL_Decode_Alerts_Severity(Element* elem, uint8_t *value)
{
    *value = (uint8_t)HAL_Decode_UInt(elem);
}



static Element* HAL_Encode_Array_Alerts_Severity(Array_Alerts_Severity value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_Alerts_Severity(Array_Alerts_Severity value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_Alerts_Severity(Element* elem, Array_Alerts_Severity* value) UNUSED_OK;

static void HAL_Decode_Array_Alerts_Severity(Element* elem, Array_Alerts_Severity* value)
{
    InitArray_Alerts_Severity(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_Alerts_Severity(value, 1);
            value->elems[j] = (uint8_t)HAL_Decode_UInt(elem->children[i]);
        }
    }
}


static AJ_Status WriteAlerts(const char *objPath, const Array_Alerts_AlertRecord* alerts)
{
    Element* elem = HAL_Encode_Array_Alerts_AlertRecord(*alerts, NULL);
    bool ok = HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts", elem);
    BSXML_FreeElement(elem);
    return ok? AJ_OK : AJ_ERR_FAILURE;
}


static AJ_Status GetAlerts(void *context, const char *objPath, Array_Alerts_AlertRecord *out)
{
    AJ_Status result = AJ_OK;
    Array_Alerts_AlertRecord value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "Alerts");

    if (elem) {
        HAL_Decode_Array_Alerts_AlertRecord(elem, &value);

        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




static AJ_Status MethodGetAlertCodesDescription(void *context, const char *objPath, char const* languageTag, Array_Alerts_AlertCodesDescriptor* description)
{
    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.Alerts", "__AlertCodesDescriptor");

    if (elem) {
        HAL_Decode_Array_Alerts_AlertCodesDescriptor(elem, description);
        BSXML_FreeElement(elem);
        return AJ_OK;
    }

    return AJ_ERR_FAILURE;
}



static AJ_Status MethodAcknowledgeAlert(void *context, const char *objPath, uint16_t alertCode)
{
    AJ_Status status;
    Array_Alerts_AlertRecord alerts;
    Array_Alerts_AlertRecord newAlerts;
    int found = 0;
    int i;

    status = GetAlerts(context, objPath, &alerts);
    if (status != AJ_OK) {
        return status;
    }

    /* Check that the given alert is in the array.  */
    for (i = 0; i < alerts.numElems; ++i) {
        if (alerts.elems[i].alertCode == alertCode) {
            found = 1;
        }
    }

    if (found) {
        InitArray_Alerts_AlertRecord(&newAlerts, 0);

        for (i = 0; i < alerts.numElems; ++i) {
            if (alerts.elems[i].alertCode != alertCode) {
                size_t ix = ExtendArray_Alerts_AlertRecord(&newAlerts, 1);
                newAlerts.elems[ix] = alerts.elems[i];
            }
        }

        status = WriteAlerts(objPath, &newAlerts);

        if (status == AJ_OK && Cdm_EmitSignalOnPropertySet())
        {
            AlertsModel* model = (AlertsModel*)context;
            status = Cdm_Alerts_EmitAlertsChanged(model->busAttachment, objPath, newAlerts);
        }

        FreeArray_Alerts_AlertRecord(&newAlerts);
    }

    FreeArray_Alerts_AlertRecord(&alerts);
    return status;
}



static AJ_Status MethodAcknowledgeAllAlerts(void *context, const char *objPath)
{
    AJ_Status status;
    Array_Alerts_AlertRecord newAlerts;

    InitArray_Alerts_AlertRecord(&newAlerts, 0);

    status = WriteAlerts(objPath, &newAlerts);

    if (status == AJ_OK && Cdm_EmitSignalOnPropertySet()) {
        AlertsModel* model = (AlertsModel*)context;
        status = Cdm_Alerts_EmitAlertsChanged(model->busAttachment, objPath, newAlerts);
    }

    return status;
}



AJ_Status HandleAlertsCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.Alerts") == 0)
    {
        if (strcmp(cmd->property, "Alerts") == 0)
        {
            Array_Alerts_AlertRecord value;
            status = GetAlerts(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                AlertsModel* model = (AlertsModel*)context;
                status = Cdm_Alerts_EmitAlertsChanged(model->busAttachment, cmd->objPath, value);
            }
            FreeArray_Alerts_AlertRecord(&value);
        }
    }
    return status;
}



static AlertsModel model = {
    GetAlerts

    , MethodGetAlertCodesDescription
    , MethodAcknowledgeAlert
    , MethodAcknowledgeAllAlerts
};


AlertsModel *GetAlertsModel(void)
{
    return &model;
}
