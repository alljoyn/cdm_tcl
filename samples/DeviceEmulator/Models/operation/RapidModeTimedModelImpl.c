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

#include "RapidModeTimedModelImpl.h"
#include "../../../Utils/HAL.h"




static AJ_Status GetRapidModeMinutesRemaining(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.RapidModeTimed", "RapidModeMinutesRemaining");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}



static AJ_Status SetRapidModeMinutesRemaining(void *context, const char *objPath, uint16_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    Element* elem = HAL_Encode_UInt(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.RapidModeTimed", "RapidModeMinutesRemaining", elem);
    BSXML_FreeElement(elem);

    return result;
}

static AJ_Status GetMaxSetMinutes(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.RapidModeTimed", "MaxSetMinutes");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




AJ_Status HandleRapidModeTimedCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.RapidModeTimed") == 0)
    {
        if (strcmp(cmd->property, "RapidModeMinutesRemaining") == 0)
        {
            uint16_t value;
            status = GetRapidModeMinutesRemaining(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                RapidModeTimedModel* model = (RapidModeTimedModel*)context;
                status = Cdm_RapidModeTimed_EmitRapidModeMinutesRemainingChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
    }
    return status;
}



static RapidModeTimedModel model = {
    GetRapidModeMinutesRemaining
    , SetRapidModeMinutesRemaining
    , GetMaxSetMinutes

};


RapidModeTimedModel *GetRapidModeTimedModel(void)
{
    return &model;
}
