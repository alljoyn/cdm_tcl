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

#ifndef CHANNELINTERFACE_H_
#define CHANNELINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define CHANNEL "org.alljoyn.SmartSpaces.Operation.Channel"

/**
 * Channel interface members
 */
typedef enum {
    CHANNEL_PROP_VERSION = 0,
    CHANNEL_PROP_CHANNEL_ID,
    CHANNEL_PROP_TOTAL_NUMBER_OF_CHANNELS,
    CHANNEL_METHOD_GET_CHANNEL_LIST,
    CHANNEL_SIGNAL_CHANNEL_LIST_CHANGED,
    CHANNEL_MEMBER_COUNT
} ChannelMembers;



typedef struct {
    char const* channelID;
    char const* channelNumber;
    char const* channelName;
} Channel_ChannelInfoRecord;


typedef struct {
    Channel_ChannelInfoRecord* elems;
    size_t numElems;
} Array_Channel_ChannelInfoRecord;

/**
 *  Free the fields in the ChannelInfoRecord but not the struct itself.
 */
extern void FreeFields_Channel_ChannelInfoRecord(Channel_ChannelInfoRecord* value);

/**
 *  Free an array of ChannelInfoRecord.
 */
extern void FreeArray_Channel_ChannelInfoRecord(Array_Channel_ChannelInfoRecord* value);

/**
 *  Initialise an array of ChannelInfoRecord.
 */
extern void InitArray_Channel_ChannelInfoRecord(Array_Channel_ChannelInfoRecord* value, size_t numElems);

/**
 *  Copy an array of ChannelInfoRecord.
 */
extern void CopyArray_Channel_ChannelInfoRecord(Array_Channel_ChannelInfoRecord* value, Array_Channel_ChannelInfoRecord* copy);

/**
 *  Extend an array of ChannelInfoRecord.
 */
extern size_t ExtendArray_Channel_ChannelInfoRecord(Array_Channel_ChannelInfoRecord* value, size_t numElems);


extern const char* const intfDescOperationChannel[CHANNEL_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationChannel;


/**
 * Emits a changed signal for the ChannelId property
 * @param[in] newValue new value of channel id
 * @return ER_OK on success
 */
AJ_Status Cdm_Channel_EmitChannelIdChanged(AJ_BusAttachment *bus, const char *objPath, char const* newValue);

/**
 * Emits a changed signal for the TotalNumberOfChannels property
 * @param[in] newValue new value of total number of channels
 * @return ER_OK on success
 */
AJ_Status Cdm_Channel_EmitTotalNumberOfChannelsChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

/**
 * Emits a ChannelListChanged signal
 * @return ER_OK on success
 */
AJ_Status Cdm_Channel_EmitChannelListChanged();

#endif /* CHANNELINTERFACE_H_ */