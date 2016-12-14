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

#ifndef HEATINGZONEINTERFACE_H_
#define HEATINGZONEINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define HEATING_ZONE "org.alljoyn.SmartSpaces.Operation.HeatingZone"

/**
 * HeatingZone interface members
 */
typedef enum {
    HEATINGZONE_PROP_VERSION = 0,
    HEATINGZONE_PROP_NUMBER_OF_HEATING_ZONES,
    HEATINGZONE_PROP_MAX_HEATING_LEVELS,
    HEATINGZONE_PROP_HEATING_LEVELS,
    HEATINGZONE_MEMBER_COUNT
} HeatingZoneMembers;



extern const char* const intfDescOperationHeatingZone[HEATINGZONE_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationHeatingZone;


/**
 * Emits a changed signal for the NumberOfHeatingZones property
 * @param[in] newValue new value of number of heating zones
 * @return ER_OK on success
 */
AJ_Status Cdm_HeatingZone_EmitNumberOfHeatingZonesChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the MaxHeatingLevels property
 * @param[in] newValue new value of max heating levels
 * @return ER_OK on success
 */
AJ_Status Cdm_HeatingZone_EmitMaxHeatingLevelsChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue);

/**
 * Emits a changed signal for the HeatingLevels property
 * @param[in] newValue new value of heating levels
 * @return ER_OK on success
 */
AJ_Status Cdm_HeatingZone_EmitHeatingLevelsChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue);

#endif /* HEATINGZONEINTERFACE_H_ */