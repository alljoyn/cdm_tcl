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

#include "ChannelModelImpl.h"
#include "../../../Utils/HAL.h"



static Element* HAL_Encode_Channel_ChannelInfoRecord(Channel_ChannelInfoRecord value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Channel_ChannelInfoRecord(Channel_ChannelInfoRecord value, Element* parent)
{
    Element* struc = BSXML_NewElement("struct", parent);
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "channelID");
        HAL_Encode_String(value.channelID, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "channelNumber");
        HAL_Encode_String(value.channelNumber, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "channelName");
        HAL_Encode_String(value.channelName, field);
    }
    return struc;
}



static void HAL_Decode_Channel_ChannelInfoRecord(Element* elem, Channel_ChannelInfoRecord* value) UNUSED_OK;

static void HAL_Decode_Channel_ChannelInfoRecord(Element* elem, Channel_ChannelInfoRecord* value)
{
    if (strcmp(elem->name, "struct") == 0 && elem->numChildren == 3) {
        value->channelID = HAL_Decode_String(elem->children[0]->children[0]);
        value->channelNumber = HAL_Decode_String(elem->children[1]->children[0]);
        value->channelName = HAL_Decode_String(elem->children[2]->children[0]);
    }
}



static Element* HAL_Encode_Array_Channel_ChannelInfoRecord(Array_Channel_ChannelInfoRecord value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_Channel_ChannelInfoRecord(Array_Channel_ChannelInfoRecord value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_Channel_ChannelInfoRecord(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_Channel_ChannelInfoRecord(Element* elem, Array_Channel_ChannelInfoRecord* value) UNUSED_OK;

static void HAL_Decode_Array_Channel_ChannelInfoRecord(Element* elem, Array_Channel_ChannelInfoRecord* value)
{
    InitArray_Channel_ChannelInfoRecord(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_Channel_ChannelInfoRecord(value, 1);
            HAL_Decode_Channel_ChannelInfoRecord(elem->children[i], &value->elems[j]);
        }
    }
}


static void CopyChannel_ChannelInfoRecord(Channel_ChannelInfoRecord* value, Channel_ChannelInfoRecord* copy)
{
    copy->channelID = strdup(value->channelID);
    copy->channelNumber = strdup(value->channelNumber);
    copy->channelName = strdup(value->channelName);
}


static AJ_Status GetChannelId(void *context, const char *objPath, char const* *out)
{
    AJ_Status result = AJ_OK;
    char const* value = 0;

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.Channel", "ChannelId");

    if (elem) {
        value = HAL_Decode_String(elem);
        BSXML_FreeElement(elem);
    }
    else {
        value = strdup("");
    }

    *out = value;
    return result;
}



static AJ_Status SetChannelId(void *context, const char *objPath, char const* input)
{
    AJ_Status result = AJ_OK;
    char const* value = input;

    Element* elem = HAL_Encode_String(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.Channel", "ChannelId", elem);
    BSXML_FreeElement(elem);

    return result;
}

static AJ_Status GetTotalNumberOfChannels(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.Channel", "TotalNumberOfChannels");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




static AJ_Status MethodGetChannelList(void *context, const char *objPath, uint16_t startingRecord, uint16_t numRecords, Array_Channel_ChannelInfoRecord* listOfChannelInfoRecords)
{
    AJ_Status status = AJ_OK;
    Array_Channel_ChannelInfoRecord channels;

    InitArray_Channel_ChannelInfoRecord(&channels, 0);

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.Channel", "__ChannelList");

    if (elem) {
        HAL_Decode_Array_Channel_ChannelInfoRecord(elem, &channels);
        BSXML_FreeElement(elem);

        InitArray_Channel_ChannelInfoRecord(listOfChannelInfoRecords, 0);

        if (startingRecord < channels.numElems)
        {
            for (size_t i = startingRecord; i < startingRecord + numRecords && i < channels.numElems; ++i)
            {
                size_t j = ExtendArray_Channel_ChannelInfoRecord(listOfChannelInfoRecords, 1);
                listOfChannelInfoRecords->elems[j] = channels.elems[i];
                CopyChannel_ChannelInfoRecord(&channels.elems[i], &listOfChannelInfoRecords->elems[j]);
            }
        }
    } else {
        return AJ_ERR_FAILURE;
    }

    FreeArray_Channel_ChannelInfoRecord(&channels);
    return status;
}



AJ_Status HandleChannelCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.Channel") == 0)
    {
        if (strcmp(cmd->property, "ChannelId") == 0)
        {
            char const* value;
            status = GetChannelId(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                ChannelModel* model = (ChannelModel*)context;
                status = Cdm_Channel_EmitChannelIdChanged(model->busAttachment, cmd->objPath, value);
            }
            free((void*)value);
        }
        if (strcmp(cmd->property, "TotalNumberOfChannels") == 0)
        {
            uint16_t value;
            status = GetTotalNumberOfChannels(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                ChannelModel* model = (ChannelModel*)context;
                status = Cdm_Channel_EmitTotalNumberOfChannelsChanged(model->busAttachment, cmd->objPath, value);
            }
            
        }
    }
    return status;
}



static ChannelModel model = {
    GetChannelId
    , SetChannelId
    , GetTotalNumberOfChannels

    , MethodGetChannelList
};


ChannelModel *GetChannelModel(void)
{
    return &model;
}
