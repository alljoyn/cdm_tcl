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

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceErrors.h>

#define CHANNEL_INTERFACE_NAME "org.alljoyn.SmartSpaces.Operation.Channel"

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

/**
 * ChannelInfoRecord struct
 */
typedef struct {
    char* channelID;
    char* channelNumber;
    char* channelName;
} ChannelInfoRecord;

const char* const intfDescOperationChannel[CHANNEL_MEMBER_COUNT + 2];
const InterfaceHandler intfHandlerOperationChannel;

/**
 * Channel interface model
 */
typedef struct {
    /**
     * Handler for getting ChannelId property
     * @param[in] context the abstract model instance
     * @param[in] objPath object path
     * @param[out] outChannelId the channel id
     * @param[out] outChannelIdLen the channel id length
     * @return AJ_OK on success
     */
    AJ_Status (*GetChannelId) (void* context, const char* objPath, char* outChannelId, uint32_t* outChannelIdLen);

    /**
     * Handler for setting ChannelId property
     * @param[in] context the abstract model instance
     * @param[in] objPath object path
     * @param[out] channelId the channel id
     * @return AJ_OK on success
     */
    AJ_Status (*SetChannelId) (void* context, const char* objPath, const char* channelId);

    /**
     * Handler for getting TotalNumberOfChannels property
     * @param[in] context the abstract model instance
     * @param[in] objPath object path
     * @param[out] outTotalNumberOfChannels the total number of channels
     * @return AJ_OK on success
     */
    AJ_Status (*GetTotalNumberOfChannels) (void* context, const char* objPath, uint16_t* outTotalNumberOfChannels);

    /**
     * Handler for GetChannelList method
     * @param[in] context the abstract model instance
     * @param[in] objPath object path
     * @param[in] startingRecord the starting record
     * @param[in] numRecords the num records
     * @param[out] outListOfChannelInfoRecords the list of channel info records
     * @param[out] outNumReturnedRecords the number of channel info records returned
     * @param[out] outErrorCode an error code
     * @return AJ_OK on success
     */
    AJ_Status (*GetChannelList) (void* context, const char* objPath, uint16_t startingRecord, uint16_t numRecords, ChannelInfoRecord* outListOfChannelInfoRecords, uint16_t* outNumReturnedRecords, ErrorCode* outErrorCode);
} ChannelModel;

#ifdef USE_DEPRECATED_INTERFACE_TYPES
AJ_DEPRECATED_ON(typedef ChannelModel ChannelListener, 16.10);
#endif

/**
 * Manually emit a changed signal for a Channel interface property; useful for read-only properties
 * @param[in] busAttachment the bus attachment
 * @param[in] objPath the object path
 * @param[in] member the property to emit a changed signal for with its current model value
 * @param[in] value The new value of the property. If this parameter is null, the interface's model is queried for the value. Can be single value or array.
 * @param[in] numValues If value is an array, this value must provide the number of elements in the value array. For non-arrays, this parameter is ignored.
 */
AJ_Status Cdm_ChannelEmitPropertyChanged(AJ_BusAttachment* busAttachment, const char* objPath, ChannelMembers member, const void* value, size_t numValues);

/**
 * Get the version of the Channel interface
 * @param[out] outVersion the interface version
 * @return AJ_OK on success
 */
AJ_Status Cdm_ChannelInterfaceGetVersion(uint16_t* outVersion);

/**
 * Get the channel id of the Channel interface
 * @param[in] objPath the object path
 * @param[out] outChannelId the channel id
 * @param[out] outChannelIdLen the channel id length
 * @return AJ_OK on success
 */
AJ_Status Cdm_ChannelInterfaceGetChannelId(const char* objPath, char* outChannelId, uint32_t* outChannelIdLen);

/**
 * Set the channel id of the Channel interface
 * @param[in] busAttachment the bus attachment
 * @param[in] objPath the object path
 * @param[in] channelId the channel id
 * @return AJ_OK on success
 */
AJ_Status Cdm_ChannelInterfaceSetChannelId(AJ_BusAttachment* busAttachment, const char* objPath, const char* channelId);

/**
 * Get the total number of channels of the Channel interface
 * @param[in] objPath the object path
 * @param[out] outTotalNumberOfChannels the total number of channels
 * @return AJ_OK on success
 */
AJ_Status Cdm_ChannelInterfaceGetTotalNumberOfChannels(const char* objPath, uint16_t* outTotalNumberOfChannels);

/**
 * Get the channel list of the Channel interface
 * @param[in] msg message
 * @param[in] objPath object path
 * @param[in] startingRecord the starting record
 * @param[in] numRecords the num records
 * @param[out] outListOfChannelInfoRecords the list of channel info records
 * @param[out] outNumReturnedRecords the number of channel info records returned
 * @param[out] outErrorCode an error code
 * @return AJ_OK on success
 */
AJ_Status Cdm_ChannelInterfaceGetChannelList(AJ_Message* msg, const char* objPath, uint16_t startingRecord, uint16_t numRecords, ChannelInfoRecord* outListOfChannelInfoRecords, uint16_t* outNumReturnedRecords, ErrorCode* outErrorCode);

/**
 * Emit ChannelListChanged signal of the Channel interface
 * @param[in] busAttachment the bus attachment
 * @param[in] objPath the object path
 * @param[in] sessionId the session id (0 = global broadcast)
 * @return AJ_OK on success
 */
AJ_Status Cdm_ChannelInterfaceEmitChannelListChanged(AJ_BusAttachment* busAttachment, const char* objPath, uint32_t sessionId);

#endif /* CHANNEL_H_ */