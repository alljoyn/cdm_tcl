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

#ifndef CURRENTPOWERINTERFACE_H_
#define CURRENTPOWERINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define CURRENT_POWER "org.alljoyn.SmartSpaces.Operation.CurrentPower"

/**
 * CurrentPower interface members
 */
typedef enum {
    CURRENTPOWER_PROP_VERSION = 0,
    CURRENTPOWER_PROP_CURRENT_POWER,
    CURRENTPOWER_PROP_PRECISION,
    CURRENTPOWER_PROP_UPDATE_MIN_TIME,
    CURRENTPOWER_MEMBER_COUNT
} CurrentPowerMembers;



extern const char* const intfDescOperationCurrentPower[CURRENTPOWER_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationCurrentPower;


/**
 * Emits a changed signal for the CurrentPower property
 * @param[in] newValue new value of current power
 * @return ER_OK on success
 */
AJ_Status Cdm_CurrentPower_EmitCurrentPowerChanged(AJ_BusAttachment *bus, const char *objPath, double newValue);

/**
 * Emits a changed signal for the Precision property
 * @param[in] newValue new value of precision
 * @return ER_OK on success
 */
AJ_Status Cdm_CurrentPower_EmitPrecisionChanged(AJ_BusAttachment *bus, const char *objPath, double newValue);

/**
 * Emits a changed signal for the UpdateMinTime property
 * @param[in] newValue new value of update min time
 * @return ER_OK on success
 */
AJ_Status Cdm_CurrentPower_EmitUpdateMinTimeChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

#endif /* CURRENTPOWERINTERFACE_H_ */