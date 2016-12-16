/**
 * @file
 */
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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceErrors.h>

/**
 * ChannelInfoRecord struct
 */
typedef struct {
    char* channelId;
    char* channelNumber;
    char* channelName;
} ChannelInfoRecord;

/**
 * Channel interface listener
 */
typedef struct {
    /**
     * Handler for getting ChannelId property
     * @param[in] objPath object path
     * @param[out] channelId channel id
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetChannelId) (const char* objPath, char* channelId);

    /**
     * Handler for setting ChannelId property
     * @param[in] objPath object path
     * @param[in] channelId channel id
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetChannelId) (const char* objPath, const char* channelId);

    /**
     * Handler for getting TotalNumberOfChannels property
     * @param[in] objPath object path
     * @param[out] totalNumberOfChannels total number of channels
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetTotalNumberOfChannels) (const char* objPath, uint16_t* totalNumberOfChannels);

    /**
     * Handler for GetChannelList method
     * @param[in] objPath object path
     * @param[in] startingRecord starting record
     * @param[in] numRecords the number of records
     * @param[out] listOfChannelInfoRecords list of channel info records
     * @param[out] numReturnedRecords the number of returned channel info records
     * @param[out] errorCode error code
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetChannelList) (const char* objPath, const uint16_t startingRecord, const uint16_t numRecords,
                                   ChannelInfoRecord** listOfChannelInfoRecords, uint16_t* numReturnedRecords, ErrorCode* errorCode);
} ChannelListener;

/**
 * Get channel id of Channel interface
 * @param[in] objPath the object path including the interface
 * @param[out] channelId channel id
 * @return AJ_OK on success
 */
AJ_Status Cdm_ChannelInterfaceGetChannelId(const char* objPath, char* channelId);

/**
 * Set channel id of Channel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] channelId channel id
 * @return AJ_OK on success
 */
AJ_Status Cdm_ChannelInterfaceSetChannelId(AJ_BusAttachment* busAttachment, const char* objPath, const char* channelId);

/**
 * Get total number of channels of Channel interface
 * @param[in] objPath the object path including the interface
 * @param[out] totalNumberOfChannels total number of channels
 * @return AJ_OK on success
 */
AJ_Status Cdm_ChannelInterfaceGetTotalNumberOfChannels(const char* objPath, uint16_t* totalNumberOfChannels);

/**
 * Set total number of channels of Channel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] totalNumberOfChannels total number of channels
 * @return AJ_OK on success
 */
AJ_Status Cdm_ChannelInterfaceSetTotalNumberOfChannels(AJ_BusAttachment* busAttachment, const char* objPath, const uint16_t totalNumberOfChannels);

/**
 * Emit ChannelListChanged signal of Channel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] sessionId session id
 * @return AJ_OK on success
 */
AJ_Status Cdm_ChannelInterfaceEmitChannelListChanged(AJ_BusAttachment* busAttachment, const char* objPath, const uint32_t sessionId);

#endif /* CHANNEL_H_ */