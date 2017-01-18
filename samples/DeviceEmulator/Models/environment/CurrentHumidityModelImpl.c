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

#include "CurrentHumidityModelImpl.h"
#include "../../../Utils/HAL.h"




static AJ_Status GetCurrentValue(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.CurrentHumidity", "CurrentValue");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}

static AJ_Status GetMaxValue(void *context, const char *objPath, uint8_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Environment.CurrentHumidity", "MaxValue");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




AJ_Status HandleCurrentHumidityCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.CurrentHumidity") == 0)
    {
        if (strcmp(cmd->property, "CurrentValue") == 0)
        {
            uint8_t value;
            status = GetCurrentValue(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentHumidityModel* model = (CurrentHumidityModel*)context;
                status = Cdm_CurrentHumidity_EmitCurrentValueChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
        if (strcmp(cmd->property, "MaxValue") == 0)
        {
            uint8_t value;
            status = GetMaxValue(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentHumidityModel* model = (CurrentHumidityModel*)context;
                status = Cdm_CurrentHumidity_EmitMaxValueChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
    }
    return status;
}



static CurrentHumidityModel model = {
    GetCurrentValue
    , GetMaxValue

};


CurrentHumidityModel *GetCurrentHumidityModel(void)
{
    return &model;
}
