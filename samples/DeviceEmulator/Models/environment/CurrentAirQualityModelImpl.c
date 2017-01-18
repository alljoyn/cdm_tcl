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

#include "CurrentAirQualityModelImpl.h"
#include "../../../Utils/HAL.h"


static Element* HAL_Encode_CurrentAirQuality_ContaminantType(CurrentAirQuality_ContaminantType value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_CurrentAirQuality_ContaminantType(CurrentAirQuality_ContaminantType value, Element* parent)
{
    return HAL_Encode_UInt(value, parent);
}



static void HAL_Decode_CurrentAirQuality_ContaminantType(Element* elem, uint8_t *value) UNUSED_OK;

static void HAL_Decode_CurrentAirQuality_ContaminantType(Element* elem, uint8_t *value)
{
    *value = (uint8_t)HAL_Decode_UInt(elem);
}



static Element* HAL_Encode_Array_CurrentAirQuality_ContaminantType(Array_CurrentAirQuality_ContaminantType value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_CurrentAirQuality_ContaminantType(Array_CurrentAirQuality_ContaminantType value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_CurrentAirQuality_ContaminantType(Element* elem, Array_CurrentAirQuality_ContaminantType* value) UNUSED_OK;

static void HAL_Decode_Array_CurrentAirQuality_ContaminantType(Element* elem, Array_CurrentAirQuality_ContaminantType* value)
{
    InitArray_CurrentAirQuality_ContaminantType(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_CurrentAirQuality_ContaminantType(value, 1);
            value->elems[j] = (uint8_t)HAL_Decode_UInt(elem->children[i]);
        }
    }
}




static AJ_Status GetContaminantType(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint8_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "ContaminantType");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}

static AJ_Status GetCurrentValue(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;
    double value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "CurrentValue");

    if (elem) {
        value = HAL_Decode_Double(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}

static AJ_Status GetMinValue(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;
    double value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "MinValue");

    if (elem) {
        value = HAL_Decode_Double(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}

static AJ_Status GetMaxValue(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;
    double value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "MaxValue");

    if (elem) {
        value = HAL_Decode_Double(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}

static AJ_Status GetPrecision(void *context, const char *objPath, double *out)
{
    AJ_Status result = AJ_OK;
    double value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "Precision");

    if (elem) {
        value = HAL_Decode_Double(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}

static AJ_Status GetUpdateMinTime(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality", "UpdateMinTime");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




AJ_Status HandleCurrentAirQualityCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality") == 0)
    {
        if (strcmp(cmd->property, "ContaminantType") == 0)
        {
            uint8_t value;
            status = GetContaminantType(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentAirQualityModel* model = (CurrentAirQualityModel*)context;
                status = Cdm_CurrentAirQuality_EmitContaminantTypeChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "CurrentValue") == 0)
        {
            double value;
            status = GetCurrentValue(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentAirQualityModel* model = (CurrentAirQualityModel*)context;
                status = Cdm_CurrentAirQuality_EmitCurrentValueChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "MinValue") == 0)
        {
            double value;
            status = GetMinValue(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentAirQualityModel* model = (CurrentAirQualityModel*)context;
                status = Cdm_CurrentAirQuality_EmitMinValueChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "MaxValue") == 0)
        {
            double value;
            status = GetMaxValue(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentAirQualityModel* model = (CurrentAirQualityModel*)context;
                status = Cdm_CurrentAirQuality_EmitMaxValueChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "Precision") == 0)
        {
            double value;
            status = GetPrecision(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentAirQualityModel* model = (CurrentAirQualityModel*)context;
                status = Cdm_CurrentAirQuality_EmitPrecisionChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "UpdateMinTime") == 0)
        {
            uint16_t value;
            status = GetUpdateMinTime(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentAirQualityModel* model = (CurrentAirQualityModel*)context;
                status = Cdm_CurrentAirQuality_EmitUpdateMinTimeChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
    }
    return status;
}



static CurrentAirQualityModel model = {
    GetContaminantType
    , GetCurrentValue
    , GetMinValue
    , GetMaxValue
    , GetPrecision
    , GetUpdateMinTime

};


CurrentAirQualityModel *GetCurrentAirQualityModel(void)
{
    return &model;
}
