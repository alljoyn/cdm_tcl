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

#include <ajtcl/cdm/interfaces/CdmInterfaceCommon.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceValidation.h>
#include <ajtcl/cdm/interfaces/operation/ChannelInterface.h>
#include <ajtcl/cdm/interfaces/operation/ChannelModel.h>

#include <ajtcl/cdm/utils/CdmArray.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME CHANNEL

const char* const intfDescOperationChannel[] = {
    "$org.alljoyn.SmartSpaces.Operation.Channel",
    "@Version>q",
    "@ChannelId=s",
    "@TotalNumberOfChannels>q",
    "?GetChannelList startingRecord<q numRecords<q listOfChannelInfoRecords>a(sss)",
    "!ChannelListChanged",
    NULL
};



void FreeFields_Channel_ChannelInfoRecord(Channel_ChannelInfoRecord* value)
{
    free((void*)value->channelID);

    free((void*)value->channelNumber);

    free((void*)value->channelName);

}


void InitArray_Channel_ChannelInfoRecord(Array_Channel_ChannelInfoRecord* value, size_t numElems)
{
    Init_Array((CdmArray*)value, sizeof(Channel_ChannelInfoRecord), numElems);
}


/* Note: this only allows fields that are char*, not any other kind of pointer */
void CopyArray_Channel_ChannelInfoRecord(Array_Channel_ChannelInfoRecord* value, Array_Channel_ChannelInfoRecord* copy)
{
    if (value->elems) {
        copy->elems = malloc(value->numElems * sizeof(Channel_ChannelInfoRecord));
        for (size_t i = 0; i < value->numElems; ++i) {
            copy->elems[i].channelID = strdup(value->elems[i].channelID);
            copy->elems[i].channelNumber = strdup(value->elems[i].channelNumber);
            copy->elems[i].channelName = strdup(value->elems[i].channelName);
        }
    } else {
        copy->elems = NULL;
    }

    copy->numElems = value->numElems;

}


void FreeArray_Channel_ChannelInfoRecord(Array_Channel_ChannelInfoRecord* value)
{
    for (size_t i = 0; i < value->numElems; ++i) {
        FreeFields_Channel_ChannelInfoRecord(&value->elems[i]);
    }
    free(value->elems);
}


size_t ExtendArray_Channel_ChannelInfoRecord(Array_Channel_ChannelInfoRecord* value, size_t numElems)
{
    return Extend_Array((CdmArray*)value, sizeof(Channel_ChannelInfoRecord), numElems);
}




static AJ_Status Channel_GetChannelId(AJ_BusAttachment* busAttachment, const char* objPath, char const** out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    ChannelModel* model = (ChannelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetChannelId) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetChannelId(model, objPath, out);
}

static AJ_Status Channel_SetChannelId(AJ_BusAttachment* busAttachment, const char* objPath, char const* value)
{
    AJ_Status status;

    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    ChannelModel* model = (ChannelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->SetChannelId) {
        return AJ_ERR_NULL;
    }

        uint16_t numChannels;
        if (model->GetTotalNumberOfChannels(model, objPath, &numChannels) != AJ_OK)
            return AJ_ERR_FAILURE;

        Array_Channel_ChannelInfoRecord availableChannels;
        if (model->MethodGetChannelList(model, objPath,0, numChannels, &availableChannels) != AJ_OK)
            return AJ_ERR_FAILURE;

        if (!valueIn_Array_Channel_ChannelInfoRecord(value, &availableChannels))
            return AJ_ERR_INVALID;

        FreeArray_Channel_ChannelInfoRecord(&availableChannels);
    model->busAttachment = busAttachment;
    status = model->SetChannelId(model, objPath, value);
    return status;
}



AJ_Status Cdm_Channel_EmitChannelIdChanged(AJ_BusAttachment *bus, const char *objPath, char const* newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "ChannelId", "s", newValue);
}



static AJ_Status Channel_GetTotalNumberOfChannels(AJ_BusAttachment* busAttachment, const char* objPath, uint16_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    ChannelModel* model = (ChannelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTotalNumberOfChannels) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetTotalNumberOfChannels(model, objPath, out);
}



AJ_Status Cdm_Channel_EmitTotalNumberOfChannelsChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "TotalNumberOfChannels", "q", newValue);
}



static AJ_Status Cdm_Channel_CallGetChannelList(AJ_BusAttachment* busAttachment, const char *objPath, uint16_t startingRecord, uint16_t numRecords, Array_Channel_ChannelInfoRecord* listOfChannelInfoRecords)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    ChannelModel* model = (ChannelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->MethodGetChannelList) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->MethodGetChannelList(model, objPath, startingRecord, numRecords, listOfChannelInfoRecords);
}



/*
   Handler functions
*/
static AJ_Status Channel_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CHANNEL_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case CHANNEL_PROP_CHANNEL_ID:
        {
            char const* channel_id;
            memset(&channel_id, 0, sizeof(char const*));
            status = Channel_GetChannelId(busAttachment, objPath, &channel_id);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "s", channel_id);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                free((void*)channel_id);
            }
            break;
        }

        case CHANNEL_PROP_TOTAL_NUMBER_OF_CHANNELS:
        {
            uint16_t total_number_of_channels;
            memset(&total_number_of_channels, 0, sizeof(uint16_t));
            status = Channel_GetTotalNumberOfChannels(busAttachment, objPath, &total_number_of_channels);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "q", total_number_of_channels);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status Channel_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case CHANNEL_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;

        case CHANNEL_PROP_CHANNEL_ID:
        {
            char const* channel_id;
            status = AJ_UnmarshalArgs(msg, "s", &channel_id);
            if (status == AJ_OK) {
                status = Channel_SetChannelId(busAttachment, objPath, channel_id);
                if (status == AJ_OK && emitOnSet) {
                    status = Cdm_Channel_EmitChannelIdChanged(busAttachment, objPath, channel_id);
                }
            }
            break;
        }
    }

    return status;
}



static AJ_Status Channel_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {

    case CHANNEL_METHOD_GET_CHANNEL_LIST:
    {
        AJ_Message reply;
        uint16_t starting_record;
        status = AJ_UnmarshalArgs(msg, "q", &starting_record);

        if (status != AJ_OK) {
            return status;
        }
        uint16_t num_records;
        status = AJ_UnmarshalArgs(msg, "q", &num_records);

        if (status != AJ_OK) {
            return status;
        }
        Array_Channel_ChannelInfoRecord list_of_channel_info_records;
        memset(&list_of_channel_info_records, 0, sizeof(Array_Channel_ChannelInfoRecord));

        status = Cdm_Channel_CallGetChannelList(busAttachment, objPath, starting_record, num_records, &list_of_channel_info_records);

        AJ_MarshalReplyMsg(msg, &reply);
        if (status == AJ_OK) {
            AJ_Arg array;
            int i=0;
            status |= AJ_MarshalContainer(&reply, &array, AJ_ARG_ARRAY);
            for (; i<list_of_channel_info_records.numElems; ++i)
            {
                AJ_Arg strc;
                status |= AJ_MarshalContainer(&reply, &strc, AJ_ARG_STRUCT);
                AJ_MarshalArgs(&reply, "sss", list_of_channel_info_records.elems[i].channelID, list_of_channel_info_records.elems[i].channelNumber, list_of_channel_info_records.elems[i].channelName);
                AJ_MarshalCloseContainer(&reply, &strc);
            }
            AJ_MarshalCloseContainer(&reply, &array);
            if (status == AJ_OK) {
                status = AJ_DeliverMsg(&reply);
            }
        }

        FreeArray_Channel_ChannelInfoRecord(&list_of_channel_info_records);
        break;
    }
    }

    return status;
}



const InterfaceHandler intfHandlerOperationChannel = {
    Channel_OnGetProperty,
    Channel_OnSetProperty,
    Channel_OnMethodHandler
};
