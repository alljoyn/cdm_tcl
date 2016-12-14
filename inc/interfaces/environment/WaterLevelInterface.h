/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef WATERLEVELINTERFACE_H_
#define WATERLEVELINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define WATER_LEVEL "org.alljoyn.SmartSpaces.Environment.WaterLevel"

/**
 * WaterLevel interface members
 */
typedef enum {
    WATERLEVEL_PROP_VERSION = 0,
    WATERLEVEL_PROP_SUPPLY_SOURCE,
    WATERLEVEL_PROP_CURRENT_LEVEL,
    WATERLEVEL_PROP_MAX_LEVEL,
    WATERLEVEL_MEMBER_COUNT
} WaterLevelMembers;


typedef enum {
    WATERLEVEL_SUPPLY_SOURCE_TANK = 0,
    WATERLEVEL_SUPPLY_SOURCE_PIPE = 1,
    WATERLEVEL_SUPPLY_SOURCE_NOT_SUPPORTED = 255
} WaterLevel_SupplySource;


typedef struct {
    WaterLevel_SupplySource* elems;
    size_t numElems;
} Array_WaterLevel_SupplySource;


/**
 *  Initialise an array of SupplySource.
 */
extern void InitArray_WaterLevel_SupplySource(Array_WaterLevel_SupplySource* value, size_t numElems);

/**
 *  Copy an array of SupplySource.
 */
extern void CopyArray_WaterLevel_SupplySource(Array_WaterLevel_SupplySource* value, Array_WaterLevel_SupplySource* copy);

/**
 *  Free an array of SupplySource.
 */
extern void FreeArray_WaterLevel_SupplySource(Array_WaterLevel_SupplySource* value);

/**
 *  Extend an array of SupplySource.
 */
extern size_t ExtendArray_WaterLevel_SupplySource(Array_WaterLevel_SupplySource* value, size_t numElems);



extern const char* const intfDescEnvironmentWaterLevel[WATERLEVEL_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerEnvironmentWaterLevel;


/**
 * Emits a changed signal for the SupplySource property
 * @param[in] newValue new value of supply source
 * @return ER_OK on success
 */
AJ_Status Cdm_WaterLevel_EmitSupplySourceChanged(AJ_BusAttachment *bus, const char *objPath, WaterLevel_SupplySource newValue);

/**
 * Emits a changed signal for the CurrentLevel property
 * @param[in] newValue new value of current level
 * @return ER_OK on success
 */
AJ_Status Cdm_WaterLevel_EmitCurrentLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the MaxLevel property
 * @param[in] newValue new value of max level
 * @return ER_OK on success
 */
AJ_Status Cdm_WaterLevel_EmitMaxLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

#endif /* WATERLEVELINTERFACE_H_ */