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
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *    WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *    AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *    DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *    PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *    TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *    PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef BATTERYSTATUS_H_
#define BATTERYSTATUS_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * BatteryStatus interface listener
 */
typedef struct  {
    /**
     * Handler for getting CurrentValue property
     * @param[in] objPath object path
     * @param[out] currentValue remaining battery value
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetCurrentValue) (const char* objPath, uint8_t* currentValue);

    /**
     * Handler for getting IsCharging property
     * @param[in] objPath object path
     * @param[out] isCharging Charging status
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetIsCharging) (const char* objPath, bool* isCharging);

} BatteryStatusListener;

/**
 * Get currentValue of BatteryStatus interface
 * @param[in] objPath the object path including the interface
 * @param[out] currentValue remaining battery value
 * @return AJ_OK on success
 */
AJ_Status Cdm_BatteryStatusInterfaceGetCurrentValue(const char* objPath, uint8_t* currentValue);

/**
 * Set currentValue of BatteryStatus interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] currentValue remaining battery value
 * @return AJ_OK on success
 */
AJ_Status Cdm_BatteryStatusInterfaceSetCurrentValue(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t currentValue);

/**
 * Get isCharging of BatteryStatus interface
 * @param[in] objPath the object path including the interface
 * @param[out] isCharging Charging status
 * @return AJ_OK on success
 */
AJ_Status Cdm_BatteryStatusInterfaceGetIsCharging(const char* objPath, bool* isCharging);

/**
 * Set isCharging of BatteryStatus interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] isCharging Charging status
 * @return AJ_OK on success
 */
AJ_Status Cdm_BatteryStatusInterfaceSetIsCharging(AJ_BusAttachment* busAttachment, const char* objPath, const bool isCharging);

#endif /* BATTERYSTATUS_H_ */