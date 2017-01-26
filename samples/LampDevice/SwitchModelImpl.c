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

#include "SwitchModelImpl.h"
#include "../Utils/HAL.h"


static AJ_Status GetIsOn(void *context, const char *objPath, bool *out)
{
    AJ_Status result = AJ_OK;
    bool value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.OnOffStatus", "IsOn");

    if (elem) {
        value = HAL_Decode_Bool(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}


AJ_Status HandleOnOffStatusCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.OnOffStatus") == 0)
    {
        if (strcmp(cmd->property, "IsOn") == 0)
        {
            bool value;
            status = GetIsOn(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                OnOffStatusModel* model = (OnOffStatusModel*)context;
                status = Cdm_OnOffStatus_EmitIsOnChanged(model->busAttachment, cmd->objPath, value);
            }

        }
    }
    return status;
}

static AJ_Status MethodSwitchOn(void *context, const char *objPath)
{
    bool value = true;

    Element* elem = HAL_Encode_Bool(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.OnOffStatus", "IsOn", elem);
    BSXML_FreeElement(elem);

    if (Cdm_EmitSignalOnPropertySet())
    {
        OnControlModel* model = (OnControlModel*)context;
        Cdm_OnOffStatus_EmitIsOnChanged(model->busAttachment, objPath, value);
    }

    return AJ_OK;
}


static AJ_Status MethodSwitchOff(void *context, const char *objPath)
{
    bool value = false;

    Element* elem = HAL_Encode_Bool(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.OnOffStatus", "IsOn", elem);
    BSXML_FreeElement(elem);

    if (Cdm_EmitSignalOnPropertySet())
    {
        OffControlModel* model = (OffControlModel*)context;
        Cdm_OnOffStatus_EmitIsOnChanged(model->busAttachment, objPath, value);
    }

    return AJ_OK;
}



static OffControlModel offControlModel= {

    MethodSwitchOff
};


OffControlModel *GetOffControlModel(void)
{
    return &offControlModel;
}


static OnControlModel onControlModel = {

    MethodSwitchOn
};


OnControlModel *GetOnControlModel(void)
{
    return &onControlModel;
}

static OnOffStatusModel onOffStatusModel = {
    GetIsOn

};


OnOffStatusModel *GetOnOffStatusModel(void)
{
    return &onOffStatusModel;
}