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

#ifndef ENERGYUSAGEINTERFACE_H_
#define ENERGYUSAGEINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define ENERGY_USAGE "org.alljoyn.SmartSpaces.Operation.EnergyUsage"

/**
 * EnergyUsage interface members
 */
typedef enum {
    ENERGYUSAGE_PROP_VERSION = 0,
    ENERGYUSAGE_PROP_CUMULATIVE_ENERGY,
    ENERGYUSAGE_PROP_PRECISION,
    ENERGYUSAGE_PROP_UPDATE_MIN_TIME,
    ENERGYUSAGE_METHOD_RESET_CUMULATIVE_ENERGY,
    ENERGYUSAGE_MEMBER_COUNT
} EnergyUsageMembers;



extern const char* const intfDescOperationEnergyUsage[ENERGYUSAGE_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationEnergyUsage;


/**
 * Emits a changed signal for the CumulativeEnergy property
 * @param[in] newValue new value of cumulative energy
 * @return ER_OK on success
 */
AJ_Status Cdm_EnergyUsage_EmitCumulativeEnergyChanged(AJ_BusAttachment *bus, const char *objPath, double newValue);

/**
 * Emits a changed signal for the Precision property
 * @param[in] newValue new value of precision
 * @return ER_OK on success
 */
AJ_Status Cdm_EnergyUsage_EmitPrecisionChanged(AJ_BusAttachment *bus, const char *objPath, double newValue);

/**
 * Emits a changed signal for the UpdateMinTime property
 * @param[in] newValue new value of update min time
 * @return ER_OK on success
 */
AJ_Status Cdm_EnergyUsage_EmitUpdateMinTimeChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

#endif /* ENERGYUSAGEINTERFACE_H_ */