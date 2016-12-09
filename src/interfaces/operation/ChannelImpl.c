/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <stdlib.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/interfaces/operation/Channel.h>
#include "ChannelImpl.h"

#define INTERFACE_VERSION 1
#define INTERFACE_NAME CHANNEL_INTERFACE_NAME

const char* const intfDescOperationChannel[] = {
    "$" INTERFACE_NAME,
    "@Version>q",
    "@ChannelId=s",
    "@TotalNumberOfChannels>q",
    "?GetChannelList startingRecord<q numRecords<q listOfChannelRecords>a(sss)",
    "!ChannelListChanged",
    NULL
};

const InterfaceHandler intfHandlerOperationChannel = {
#ifdef USE_DEPRECATED_INTERFACE_TYPES
    NULL,   // InterfaceRegistered
#endif
    ChannelInterfaceOnGetProperty,
    ChannelInterfaceOnSetProperty,
    ChannelInterfaceOnMethodHandler
};


AJ_Status ChannelInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_OK;

    switch (memberIndex) {
    case CHANNEL_PROP_VERSION:
        status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
        break;
    case CHANNEL_PROP_CHANNEL_ID: {
        char* channelId;
        uint32_t channelIdLen;
        status = Cdm_ChannelInterfaceGetChannelId(objPath, NULL, &channelIdLen);
        
        if (status == AJ_OK) {
            channelId = malloc(channelIdLen + 1);
            if (channelId) {
                status = Cdm_ChannelInterfaceGetChannelId(objPath, channelId, NULL);
                if (status == AJ_OK) {
                    status = AJ_MarshalArgs(replyMsg, "s", channelId);
                }

                free(channelId);
            } else {
                status = AJ_ERR_RESOURCES;
            }
        }
        
        break;
    }
    case CHANNEL_PROP_TOTAL_NUMBER_OF_CHANNELS: {
        uint16_t totalNumberOfChannels;
        status = Cdm_ChannelInterfaceGetTotalNumberOfChannels(objPath, &totalNumberOfChannels);
        if (status == AJ_OK) {
            status = AJ_MarshalArgs(replyMsg, "q", totalNumberOfChannels);
        }
        break;
    }
    case CHANNEL_METHOD_GET_CHANNEL_LIST:
        status = AJ_ERR_INVALID;
        break;
    case CHANNEL_SIGNAL_CHANNEL_LIST_CHANGED:
        status = AJ_ERR_INVALID;
        break;
    default:
        status = AJ_ERR_INVALID;
    }

    return status;
}

AJ_Status ChannelInterfaceOnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_OK;

    switch (memberIndex) {
    case CHANNEL_PROP_VERSION:
        status = AJ_ERR_DISALLOWED;
        break;
    case CHANNEL_PROP_CHANNEL_ID: {
        char* channelId;
        status = AJ_UnmarshalArgs(replyMsg, "s", &channelId);
        if (status == AJ_OK) {
            status = Cdm_ChannelInterfaceSetChannelId(busAttachment, objPath, channelId);
        }
        break;
    }
    case CHANNEL_PROP_TOTAL_NUMBER_OF_CHANNELS:
        status = AJ_ERR_DISALLOWED;
        break;
    case CHANNEL_METHOD_GET_CHANNEL_LIST:
        status = AJ_ERR_INVALID;
        break;
    case CHANNEL_SIGNAL_CHANNEL_LIST_CHANGED:
        status = AJ_ERR_INVALID;
        break;
    default:
        status = AJ_ERR_INVALID;
    }

    return status;
}

AJ_Status ChannelInterfaceOnMethodHandler(AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_OK;

    switch (memberIndex) {
    case CHANNEL_PROP_VERSION:
        status = AJ_ERR_INVALID;
        break;
    case CHANNEL_PROP_CHANNEL_ID:
        status = AJ_ERR_INVALID;
        break;
    case CHANNEL_PROP_TOTAL_NUMBER_OF_CHANNELS:
        status = AJ_ERR_INVALID;
        break;
    case CHANNEL_METHOD_GET_CHANNEL_LIST: {
        uint16_t startingRecord;
        uint16_t numRecords;
        ChannelInfoRecord* listOfChannelInfoRecords;
        uint16_t numReturnedRecords;
        ErrorCode errorCode;

        status = AJ_UnmarshalArgs(msg, "qq", &startingRecord, &numRecords);
        if (status == AJ_OK) {
            listOfChannelInfoRecords = malloc(numRecords * sizeof(ChannelInfoRecord));

            if (listOfChannelInfoRecords) {
                // Query channel list size to ensure there are enough elements.
                status = Cdm_ChannelInterfaceGetChannelList(msg, objPath, startingRecord, numRecords, NULL, &numReturnedRecords, &errorCode);
                
                if (status == AJ_OK) {
                    // Get channel list from model and send a reply message.
                    status = Cdm_ChannelInterfaceGetChannelList(msg, objPath, startingRecord, numRecords, listOfChannelInfoRecords, &numReturnedRecords, &errorCode);
                }

                for (uint16_t i = 0; i < numRecords; i++) {
                    ChannelInfoRecord* record = &listOfChannelInfoRecords[i];

                    if (record->channelID) {
                        free(record->channelID);
                    }
                    if (record->channelNumber) {
                        free(record->channelNumber);
                    }
                    if (record->channelName) {
                        free(record->channelName);
                    }
                }
                
                free(listOfChannelInfoRecords);
            } else {
                status = AJ_ERR_RESOURCES;
            }
        }
        break;
    }
    case CHANNEL_SIGNAL_CHANNEL_LIST_CHANGED:
        status = AJ_ERR_INVALID;
        break;
    default:
        status = AJ_ERR_INVALID;
    }

    return status;
}


AJ_Status Cdm_ChannelEmitPropertyChanged(AJ_BusAttachment* busAttachment, const char* objPath, ChannelMembers member, const void* value, size_t numValues)
{
    AJ_Status status = AJ_OK;

    switch (member) {
    case CHANNEL_PROP_VERSION:
        status = AJ_ERR_DISALLOWED;
        break;
    case CHANNEL_PROP_CHANNEL_ID: {
        char* channelId;
        if (value) {
            channelId = (char*)value;
        } else {
            uint32_t channelIdLen;
            status = Cdm_ChannelInterfaceGetChannelId(objPath, NULL, &channelIdLen);
            
            channelId = malloc(channelIdLen + 1);
            if (channelId) {
                status = Cdm_ChannelInterfaceGetChannelId(objPath, channelId, NULL);
            } else {
                status = AJ_ERR_RESOURCES;
            }
        }

        if (status == AJ_OK) {
            status = EmitPropertyChanged(busAttachment, objPath, INTERFACE_NAME, "ChannelId", "s", channelId);
        }
        
        if (!value) {
            free(channelId);
        }

        break;
    }
    case CHANNEL_PROP_TOTAL_NUMBER_OF_CHANNELS: {
        uint16_t totalNumberOfChannels;
        if (value) {
            totalNumberOfChannels = *(uint16_t*)value;
        } else {
            status = Cdm_ChannelInterfaceGetTotalNumberOfChannels(objPath, &totalNumberOfChannels);
        }

        if (status == AJ_OK) {
            status = EmitPropertyChanged(busAttachment, objPath, INTERFACE_NAME, "TotalNumberOfChannels", "q", totalNumberOfChannels);
        }
        break;
    }
    case CHANNEL_METHOD_GET_CHANNEL_LIST:
        status = AJ_ERR_INVALID;
        break;
    case CHANNEL_SIGNAL_CHANNEL_LIST_CHANGED:
        status = AJ_ERR_INVALID;
        break;
    default:
        status = AJ_ERR_INVALID;
    }

    return status;
}

AJ_Status Cdm_ChannelInterfaceGetVersion(uint16_t* outVersion)
{
    *outVersion = INTERFACE_VERSION;
    return AJ_OK;
}

AJ_Status Cdm_ChannelInterfaceGetChannelId(const char* objPath, char* outChannelId, uint32_t* outChannelIdLen)
{
    if (!objPath || (!outChannelId && !outChannelIdLen)) {
        return AJ_ERR_INVALID;
    }

    ChannelModel* model = (ChannelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTotalNumberOfChannels) {
        return AJ_ERR_NULL;
    }
    
    return model->GetChannelId(model, objPath, outChannelId, outChannelIdLen);
}

AJ_Status Cdm_ChannelInterfaceSetChannelId(AJ_BusAttachment* busAttachment, const char* objPath, const char* channelId)
{
    if (!busAttachment || !objPath || !channelId) {
        return AJ_ERR_INVALID;
    }

    ChannelModel* model = (ChannelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetChannelId || !model->SetChannelId) {
        return AJ_ERR_NULL;
    }

    char* oldChannelId;
    uint32_t oldChannelIdLen;
    AJ_Status status = Cdm_ChannelInterfaceGetChannelId(objPath, NULL, &oldChannelIdLen);
    if (status != AJ_OK) {
        return status;
    }

    oldChannelId = malloc(oldChannelIdLen + 1);
    if (oldChannelId) {
        status = Cdm_ChannelInterfaceGetChannelId(objPath, oldChannelId, NULL);
    } else {
        status = AJ_ERR_RESOURCES;
    }

    if (strcmp(oldChannelId, channelId) != 0) {
        status = model->SetChannelId(model, objPath, channelId);

        if (status == AJ_OK) {
            status = Cdm_ChannelEmitPropertyChanged(busAttachment, objPath, CHANNEL_PROP_CHANNEL_ID, channelId, 0);
        }
    }

    free(oldChannelId);

    return status;
}

AJ_Status Cdm_ChannelInterfaceGetTotalNumberOfChannels(const char* objPath, uint16_t* outTotalNumberOfChannels)
{
    if (!objPath || !outTotalNumberOfChannels) {
        return AJ_ERR_INVALID;
    }

    ChannelModel* model = (ChannelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTotalNumberOfChannels) {
        return AJ_ERR_NULL;
    }
    
    return model->GetTotalNumberOfChannels(model, objPath, outTotalNumberOfChannels);
}

AJ_Status Cdm_ChannelInterfaceGetChannelList(AJ_Message* msg, const char* objPath, uint16_t startingRecord, uint16_t numRecords, ChannelInfoRecord* outListOfChannelInfoRecords, uint16_t* outNumReturnedRecords, ErrorCode* outErrorCode)
{
    if (!objPath || (!outListOfChannelInfoRecords && !outNumReturnedRecords)) {
        return AJ_ERR_INVALID;
    }

    ChannelModel* model = (ChannelModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetChannelList) {
        return AJ_ERR_NULL;
    }
    
    AJ_Status status = model->GetChannelList(model, objPath, startingRecord, numRecords, outListOfChannelInfoRecords, outNumReturnedRecords, outErrorCode);
    
    if (outListOfChannelInfoRecords && outNumReturnedRecords) {
        if (status == AJ_OK) {
            AJ_Message reply;
            AJ_Arg array, strc;

            AJ_MarshalReplyMsg(msg, &reply);
            AJ_MarshalContainer(&reply, &array, AJ_ARG_ARRAY);
            for (uint16_t i = 0; i < *outNumReturnedRecords; i++) {
                AJ_MarshalContainer(&reply, &strc, AJ_ARG_STRUCT);
                ChannelInfoRecord* record = &outListOfChannelInfoRecords[i];
                AJ_MarshalArgs(&reply, "sss", record->channelID, record->channelNumber, record->channelName);
                AJ_MarshalCloseContainer(&reply, &strc);
            }
            AJ_MarshalCloseContainer(&reply, &array);

            status = AJ_DeliverMsg(&reply);
        } else {
            AJ_Message reply;
            AJ_MarshalReplyMsg(msg, &reply);
            AJ_MarshalErrorMsgWithInfo(msg, &reply, GetInterfaceErrorName(*outErrorCode), GetInterfaceErrorMessage(*outErrorCode));
            status = AJ_DeliverMsg(&reply);
        }
    }

    return status;

    //return SendMethodReply((status == AJ_OK), objPath, startingRecord, numRecords, outListOfChannelInfoRecords, *outNumReturnedRecords, *outErrorCode);
}

AJ_Status Cdm_ChannelInterfaceEmitChannelListChanged(AJ_BusAttachment* busAttachment, const char* objPath, uint32_t sessionId)
{
    AJ_Status status = AJ_OK;
    AJ_Message msg;
    uint32_t msgId = 0;

    status = MakeMessageId(objPath, CHANNEL_INTERFACE_NAME, CHANNEL_SIGNAL_CHANNEL_LIST_CHANGED, &msgId);
    if (status != AJ_OK) {
        return status;
    }

    AJ_MarshalSignal(busAttachment, &msg, msgId, NULL, sessionId, AJ_FLAG_GLOBAL_BROADCAST, 0);
    return AJ_DeliverMsg(&msg);

    //return EmitSignal(busAttachment, objPath, CHANNEL_INTERFACE_NAME, CHANNEL_SIGNAL_CHANNEL_LIST_CHANGED, sessionId);
}
