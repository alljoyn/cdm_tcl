/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef _CHANNEL_HAL_MOCK_HANDLERS_H_
#define _CHANNEL_HAL_MOCK_HANDLERS_H_

#include <ajtcl/cdm/interfaces/operation/Channel.h>

typedef struct {
	uint32_t channelIDLen;
    uint32_t channelNumberLen;
    uint32_t channelNameLen;
} ChannelInfoRecordLengths;

typedef struct {
	ChannelInfoRecordLengths* channelInfoRecordLengths;
	uint16_t startingRecord;
	uint16_t numRecords;
} ReadChannelInfoRecordLengthsHandlerInput;

typedef struct {
	ChannelInfoRecord* listOfChannelInfoRecords;
	uint16_t startingRecord;
	uint16_t numRecords;
} ReadChannelInfoRecordArrayHandlerInput;

AJ_Status ChannelHALMock_ReadChannelInfoRecordLengthsHandler(const char* fileData, void* outValue);
AJ_Status ChannelHALMock_ReadChannelInfoRecordArrayHandler(const char* fileData, void* outValue);

#endif /* _CHANNEL_HAL_MOCK_HANDLERS_H_ */