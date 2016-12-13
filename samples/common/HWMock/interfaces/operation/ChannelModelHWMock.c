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
#include "HWMock/interfaces/operation/ChannelModelHWMock.h"
#include "HWMock/interfaces/operation/ChannelHALMockHandlers.h"
#include "HWMock/HALMockCommonHandlers.h"

/**
 * Base model function implementations.
 */
AJ_Status ChannelModelHWMock_GetChannelId(void* context, const char* objPath, char* outChannelId, uint32_t* outChannelIdLen)
{
    ChannelModelHWMock* modelHWMock = ((ChannelModelHWMock*)context);
    if (!modelHWMock->hal || (!outChannelId && !outChannelIdLen)) {
        return AJ_ERR_INVALID;
    }

    AJ_Status status = AJ_OK;
    if (outChannelIdLen) {
        status = HALMock_GetValue(modelHWMock->hal, objPath, CHANNEL_INTERFACE_NAME, "ChannelId", HALMock_ReadStringLengthHandler, outChannelIdLen);
        if (status != AJ_OK) {
            return status;
        }
    }

    if (outChannelId) {
        status = HALMock_GetValue(modelHWMock->hal, objPath, CHANNEL_INTERFACE_NAME, "ChannelId", HALMock_ReadStringHandler, outChannelId);
        if (status != AJ_OK) {
            return status;
        }
    }
    
    printf("ChannelModelHWMock_GetChannelId() called! Status = %d\n", status);
    return status;
}

AJ_Status ChannelModelHWMock_SetChannelId(void* context, const char* objPath, const char* channelId)
{
    // TODO
    return AJ_OK;
    /*ChannelModelHWMock* modelHWMock = ((ChannelModelHWMock*)context);
    if (!modelHWMock->hal) {
        return AJ_ERR_INVALID;
    }
    
    AJ_Status status = HALMock_SetValue(modelHWMock->hal, objPath, CHANNEL_INTERFACE_NAME, "ChannelId", HALMock_WriteStringHandler, channelId, 1);
    printf("ChannelModelHWMock_SetChannelId() called! Status = %d\n", status);
    return status;*/
}

AJ_Status ChannelModelHWMock_GetTotalNumberOfChannels(void* context, const char* objPath, uint16_t* outTotalNumberOfChannels)
{
    ChannelModelHWMock* modelHWMock = ((ChannelModelHWMock*)context);
    if (!modelHWMock->hal) {
        return AJ_ERR_INVALID;
    }
    
    AJ_Status status = HALMock_GetValue(modelHWMock->hal, objPath, CHANNEL_INTERFACE_NAME, "TotalNumberOfChannels", HALMock_ReadUint16Handler, outTotalNumberOfChannels);
    printf("ChannelModelHWMock_GetTotalNumberOfChannels() called! Status = %d\n", status);
    return status;
}

AJ_Status ChannelModelHWMock_GetChannelList(void* context, const char* objPath, uint16_t startingRecord, uint16_t numRecords, ChannelInfoRecord* outListOfChannelInfoRecords, uint16_t* outNumReturnedRecords, ErrorCode* outErrorCode)
{
    ChannelModelHWMock* modelHWMock = ((ChannelModelHWMock*)context);
    if (!modelHWMock->hal || (!outListOfChannelInfoRecords && !outNumReturnedRecords)) {
        return AJ_ERR_INVALID;
    }

    AJ_Status status = AJ_OK;
    if (outNumReturnedRecords) {
        status = HALMock_GetValue(modelHWMock->hal, objPath, CHANNEL_INTERFACE_NAME, "ChannelList", HALMock_ReadArrayLengthHandler, outNumReturnedRecords);
        if (status != AJ_OK) {
            return status;
        }
        if (*outNumReturnedRecords > (startingRecord + numRecords)) {
            *outNumReturnedRecords = 0;
            return AJ_ERR_RANGE;
        }
    }
    
    if (outListOfChannelInfoRecords) {
        memset(outListOfChannelInfoRecords, 0, numRecords * sizeof(ChannelInfoRecord));

        ReadChannelInfoRecordLengthsHandlerInput lengthsHandlerInput;
        lengthsHandlerInput.channelInfoRecordLengths = malloc(numRecords * sizeof(ChannelInfoRecordLengths));

        if (!lengthsHandlerInput.channelInfoRecordLengths) {
            goto CleanupChannelInfoRecords;
        }

        lengthsHandlerInput.startingRecord = startingRecord;
        lengthsHandlerInput.numRecords = numRecords;
        memset(lengthsHandlerInput.channelInfoRecordLengths, 0, numRecords * sizeof(ChannelInfoRecordLengths));

        status = HALMock_GetValue(modelHWMock->hal, objPath, CHANNEL_INTERFACE_NAME, "ChannelList", ChannelHALMock_ReadChannelInfoRecordLengthsHandler, &lengthsHandlerInput);
        if (status != AJ_OK) {
            status = AJ_ERR_RESOURCES;
            goto CleanupChannelInfoRecords;
        }

        for (uint16_t i = 0; i < numRecords; i++) {
            ChannelInfoRecord* record = &(outListOfChannelInfoRecords)[i];
            ChannelInfoRecordLengths* recordLengths = &(lengthsHandlerInput.channelInfoRecordLengths[i]);

            record->channelID = malloc(recordLengths->channelIDLen + 1);
            if (!record->channelID) {
                status = AJ_ERR_RESOURCES;
                goto CleanupChannelInfoRecords;
            }

            record->channelNumber = malloc(recordLengths->channelNumberLen + 1);
            if (!record->channelNumber) {
                status = AJ_ERR_RESOURCES;
                goto CleanupChannelInfoRecords;
            }

            record->channelName = malloc(recordLengths->channelNameLen + 1);
            if (!record->channelName) {
                status = AJ_ERR_RESOURCES;
                goto CleanupChannelInfoRecords;
            }
        }

        ReadChannelInfoRecordArrayHandlerInput arrayHandlerInput = { outListOfChannelInfoRecords, startingRecord, numRecords };
        status = HALMock_GetValue(modelHWMock->hal, objPath, CHANNEL_INTERFACE_NAME, "ChannelList", ChannelHALMock_ReadChannelInfoRecordArrayHandler, &arrayHandlerInput);
        if (status != AJ_OK) {
            status = AJ_ERR_RESOURCES;
            goto CleanupChannelInfoRecords;
        }

CleanupChannelInfoRecords:
        free(lengthsHandlerInput.channelInfoRecordLengths);
    }
    
    printf("ChannelModelHWMock_GetChannelList() called! Status = %d\n", status);
    return status;
}


/**
 * Mock hardware property changed callbacks.
 */
AJ_Status ChannelModelHWMock_OnChannelIdChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString)
{
    // TODO
    return AJ_OK;
}

AJ_Status ChannelModelHWMock_OnTotalNumberOfChannelsChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString)
{
    uint16_t totalNumberOfChannels;
    AJ_Status status = HALMock_ReadUint16Handler(valueString, &totalNumberOfChannels);
    printf("ChannelModelHWMock_OnTargetValueChanged() called!\n");
    if (status != AJ_OK) {
        return status;
    }
    
    return Cdm_ChannelEmitPropertyChanged(busAttachment, objPath, CHANNEL_PROP_TOTAL_NUMBER_OF_CHANNELS, &totalNumberOfChannels, 0);
}

AJ_Status ChannelModelHWMock_OnChannelListChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString)
{
    return Cdm_ChannelInterfaceEmitChannelListChanged(busAttachment, objPath, 0);
}


/**
 * Channel mock hardware model setup function.
 */
AJ_Status SetupChannelModelHWMock(ChannelModelHWMock* modelHWMock, HALMock* halMock, const char* objPath)
{
	if (!modelHWMock || !halMock) {
		return AJ_ERR_INVALID;
	}
    if (!halMock->busAttachment || !halMock->hwFileName) {
        return AJ_ERR_NULL;
    }

	memset(modelHWMock, 0, sizeof(ChannelModelHWMock));

	modelHWMock->baseModel.GetChannelId = ChannelModelHWMock_GetChannelId;
    modelHWMock->baseModel.SetChannelId = ChannelModelHWMock_SetChannelId;
    modelHWMock->baseModel.GetTotalNumberOfChannels = ChannelModelHWMock_GetTotalNumberOfChannels;
    modelHWMock->baseModel.GetChannelList = ChannelModelHWMock_GetChannelList;
    modelHWMock->hal = halMock;

    AJ_Status status = HALMock_SetPropertyChangedCallback(modelHWMock->hal, objPath, CHANNEL_INTERFACE_NAME, "ChannelId", ChannelModelHWMock_OnChannelIdChanged);
    if (status != AJ_OK) {
        return status;
    }
    status = HALMock_SetPropertyChangedCallback(modelHWMock->hal, objPath, CHANNEL_INTERFACE_NAME, "TotalNumberOfChannels", ChannelModelHWMock_OnTotalNumberOfChannelsChanged);
    if (status != AJ_OK) {
        return status;
    }
    status = HALMock_SetPropertyChangedCallback(modelHWMock->hal, objPath, CHANNEL_INTERFACE_NAME, "ChannelList", ChannelModelHWMock_OnChannelListChanged);
    if (status != AJ_OK) {
        return status;
    }

    return status;
}