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

#ifndef CURRENTAIRQUALITYLEVELINTERFACE_H_
#define CURRENTAIRQUALITYLEVELINTERFACE_H_

#include <stdint.h>

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define CURRENT_AIR_QUALITY_LEVEL "org.alljoyn.SmartSpaces.Environment.CurrentAirQualityLevel"

/**
 * CurrentAirQualityLevel interface members
 */
typedef enum {
    CURRENTAIRQUALITYLEVEL_PROP_VERSION = 0,
    CURRENTAIRQUALITYLEVEL_PROP_CONTAMINANT_TYPE,
    CURRENTAIRQUALITYLEVEL_PROP_CURRENT_LEVEL,
    CURRENTAIRQUALITYLEVEL_PROP_MAX_LEVEL,
    CURRENTAIRQUALITYLEVEL_MEMBER_COUNT
} CurrentAirQualityLevelMembers;


typedef enum {
    CURRENTAIRQUALITYLEVEL_CONTAMINANT_TYPE_CH2O = 0,
    CURRENTAIRQUALITYLEVEL_CONTAMINANT_TYPE_CO2 = 1,
    CURRENTAIRQUALITYLEVEL_CONTAMINANT_TYPE_CO = 2,
    CURRENTAIRQUALITYLEVEL_CONTAMINANT_TYPE_PM2_5 = 3,
    CURRENTAIRQUALITYLEVEL_CONTAMINANT_TYPE_PM10 = 4,
    CURRENTAIRQUALITYLEVEL_CONTAMINANT_TYPE_VOC = 5,
    CURRENTAIRQUALITYLEVEL_CONTAMINANT_TYPE_SMOKE = 253,
    CURRENTAIRQUALITYLEVEL_CONTAMINANT_TYPE_ODOR = 254,
    CURRENTAIRQUALITYLEVEL_CONTAMINANT_TYPE_AIR_POLLUTION = 255
} CurrentAirQualityLevel_ContaminantType;


typedef struct {
    uint8_t* elems;
    size_t numElems;
} Array_CurrentAirQualityLevel_ContaminantType;


/**
 *  Initialise an array of ContaminantType.
 */
extern void InitArray_CurrentAirQualityLevel_ContaminantType(Array_CurrentAirQualityLevel_ContaminantType* value, size_t numElems);

/**
 *  Copy an array of ContaminantType.
 */
extern void CopyArray_CurrentAirQualityLevel_ContaminantType(Array_CurrentAirQualityLevel_ContaminantType* value, Array_CurrentAirQualityLevel_ContaminantType* copy);

/**
 *  Free an array of ContaminantType.
 */
extern void FreeArray_CurrentAirQualityLevel_ContaminantType(Array_CurrentAirQualityLevel_ContaminantType* value);

/**
 *  Extend an array of ContaminantType.
 */
extern size_t ExtendArray_CurrentAirQualityLevel_ContaminantType(Array_CurrentAirQualityLevel_ContaminantType* value, size_t numElems);



extern const char* const intfDescEnvironmentCurrentAirQualityLevel[CURRENTAIRQUALITYLEVEL_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerEnvironmentCurrentAirQualityLevel;


/**
 * Emits a changed signal for the ContaminantType property
 * @param[in] newValue new value of contaminant type
 * @return ER_OK on success
 */
AJ_Status Cdm_CurrentAirQualityLevel_EmitContaminantTypeChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the CurrentLevel property
 * @param[in] newValue new value of current level
 * @return ER_OK on success
 */
AJ_Status Cdm_CurrentAirQualityLevel_EmitCurrentLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the MaxLevel property
 * @param[in] newValue new value of max level
 * @return ER_OK on success
 */
AJ_Status Cdm_CurrentAirQualityLevel_EmitMaxLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

#endif /* CURRENTAIRQUALITYLEVELINTERFACE_H_ */