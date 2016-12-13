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

#ifndef CHANNELMODEL_H_
#define CHANNELMODEL_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/interfaces/operation/ChannelInterface.h>

/**
 * Channel interface model
 */
typedef struct {

    /**
     * Get ChannelId
     * @param[out] value current channel id. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetChannelId)(void *context, const char *objPath, char const** value);

     /**
     * Set ChannelId
     * @param[in] value The channel id to set
     * @return ER_OK on success
     */
    AJ_Status (*SetChannelId)(void *context, const char *objPath, char const* value);

    /**
     * Get TotalNumberOfChannels
     * @param[out] value current total number of channels. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetTotalNumberOfChannels)(void *context, const char *objPath, uint16_t* value);

     /**
      * Call GetChannelList
      * @param[in] startingRecord
      * @param[in] numRecords
      * @param[out] listOfChannelInfoRecords The caller will free the memory if the type is not a scalar.
      */
    AJ_Status (*MethodGetChannelList)(void *context, const char *objPath, uint16_t startingRecord, uint16_t numRecords, Array_Channel_ChannelInfoRecord* listOfChannelInfoRecords);

    AJ_BusAttachment* busAttachment;

} ChannelModel;

#endif /* CHANNELMODEL_H_ */