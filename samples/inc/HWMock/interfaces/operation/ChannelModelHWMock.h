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

#ifndef _CHANNEL_MODEL_HW_MOCK_H_
#define _CHANNEL_MODEL_HW_MOCK_H_

#include <ajtcl/cdm/interfaces/operation/Channel.h>
#include "HWMock/HALMock.h"

/**
 * Channel model extended to support mock hardware operations.
 */
typedef struct {
	ChannelModel baseModel;

	HALMock* hal;
} ChannelModelHWMock;

/**
 * Base model function implementations which interface with HAL.
 */
AJ_Status ChannelModelHWMock_GetChannelId(void* context, const char* objPath, char* outChannelId, uint32_t* outChannelIdLen);
AJ_Status ChannelModelHWMock_SetChannelId(void* context, const char* objPath, const char* channelId);
AJ_Status ChannelModelHWMock_GetTotalNumberOfChannels(void* context, const char* objPath, uint16_t* outTotalNumberOfChannels);
AJ_Status ChannelModelHWMock_GetChannelList(void* context, const char* objPath, uint16_t startingRecord, uint16_t numRecords, ChannelInfoRecord* outListOfChannelInfoRecords, uint16_t* outNumReturnedRecords, ErrorCode* outErrorCode);

/**
 * Callbacks for when properties are changed directly on mock hardware outside of the model.
 */
AJ_Status ChannelModelHWMock_OnChannelIdChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString);
AJ_Status ChannelModelHWMock_OnTotalNumberOfChannelsChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString);
AJ_Status ChannelModelHWMock_OnChannelListChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* valueString);

/**
 * Channel mock hardware model setup function.
 */
AJ_Status SetupChannelModelHWMock(ChannelModelHWMock* modelSW, HALMock* halMock, const char* objPath);

#endif /* _CHANNEL_MODEL_HW_MOCK_H_ */