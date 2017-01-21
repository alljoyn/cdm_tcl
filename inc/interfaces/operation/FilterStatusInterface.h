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

#ifndef FILTERSTATUSINTERFACE_H_
#define FILTERSTATUSINTERFACE_H_

#include <stdint.h>

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CdmArray.h>

#define FILTER_STATUS "org.alljoyn.SmartSpaces.Operation.FilterStatus"

/**
 * FilterStatus interface members
 */
typedef enum {
    FILTERSTATUS_PROP_VERSION = 0,
    FILTERSTATUS_PROP_EXPECTED_LIFE_IN_DAYS,
    FILTERSTATUS_PROP_IS_CLEANABLE,
    FILTERSTATUS_PROP_ORDER_PERCENTAGE,
    FILTERSTATUS_PROP_MANUFACTURER,
    FILTERSTATUS_PROP_PART_NUMBER,
    FILTERSTATUS_PROP_URL,
    FILTERSTATUS_PROP_LIFE_REMAINING,
    FILTERSTATUS_MEMBER_COUNT
} FilterStatusMembers;



extern const char* const intfDescOperationFilterStatus[FILTERSTATUS_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationFilterStatus;


/**
 * Emits a changed signal for the ExpectedLifeInDays property
 * @param[in] newValue new value of expected life in days
 * @return ER_OK on success
 */
AJ_Status Cdm_FilterStatus_EmitExpectedLifeInDaysChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

/**
 * Emits a changed signal for the IsCleanable property
 * @param[in] newValue new value of is cleanable
 * @return ER_OK on success
 */
AJ_Status Cdm_FilterStatus_EmitIsCleanableChanged(AJ_BusAttachment *bus, const char *objPath, bool newValue);

/**
 * Emits a changed signal for the OrderPercentage property
 * @param[in] newValue new value of order percentage
 * @return ER_OK on success
 */
AJ_Status Cdm_FilterStatus_EmitOrderPercentageChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the LifeRemaining property
 * @param[in] newValue new value of life remaining
 * @return ER_OK on success
 */
AJ_Status Cdm_FilterStatus_EmitLifeRemainingChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

#endif /* FILTERSTATUSINTERFACE_H_ */