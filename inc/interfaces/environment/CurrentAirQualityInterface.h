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

#ifndef CURRENTAIRQUALITYINTERFACE_H_
#define CURRENTAIRQUALITYINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define CURRENT_AIR_QUALITY "org.alljoyn.SmartSpaces.Environment.CurrentAirQuality"

/**
 * CurrentAirQuality interface members
 */
typedef enum {
    CURRENTAIRQUALITY_PROP_VERSION = 0,
    CURRENTAIRQUALITY_PROP_CONTAMINANT_TYPE,
    CURRENTAIRQUALITY_PROP_CURRENT_VALUE,
    CURRENTAIRQUALITY_PROP_MIN_VALUE,
    CURRENTAIRQUALITY_PROP_MAX_VALUE,
    CURRENTAIRQUALITY_PROP_PRECISION,
    CURRENTAIRQUALITY_PROP_UPDATE_MIN_TIME,
    CURRENTAIRQUALITY_MEMBER_COUNT
} CurrentAirQualityMembers;


typedef enum {
    CURRENTAIRQUALITY_CONTAMINANT_TYPE_CH2O = 0,
    CURRENTAIRQUALITY_CONTAMINANT_TYPE_CO2 = 1,
    CURRENTAIRQUALITY_CONTAMINANT_TYPE_CO = 2,
    CURRENTAIRQUALITY_CONTAMINANT_TYPE_PM2_5 = 3,
    CURRENTAIRQUALITY_CONTAMINANT_TYPE_PM10 = 4,
    CURRENTAIRQUALITY_CONTAMINANT_TYPE_VOC = 5
} CurrentAirQuality_ContaminantType;


typedef struct {
    CurrentAirQuality_ContaminantType* elems;
    size_t numElems;
} Array_CurrentAirQuality_ContaminantType;


/**
 *  Initialise an array of ContaminantType.
 */
extern void InitArray_CurrentAirQuality_ContaminantType(Array_CurrentAirQuality_ContaminantType* value, size_t numElems);

/**
 *  Copy an array of ContaminantType.
 */
extern void CopyArray_CurrentAirQuality_ContaminantType(Array_CurrentAirQuality_ContaminantType* value, Array_CurrentAirQuality_ContaminantType* copy);

/**
 *  Free an array of ContaminantType.
 */
extern void FreeArray_CurrentAirQuality_ContaminantType(Array_CurrentAirQuality_ContaminantType* value);

/**
 *  Extend an array of ContaminantType.
 */
extern size_t ExtendArray_CurrentAirQuality_ContaminantType(Array_CurrentAirQuality_ContaminantType* value, size_t numElems);



extern const char* const intfDescEnvironmentCurrentAirQuality[CURRENTAIRQUALITY_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerEnvironmentCurrentAirQuality;


/**
 * Emits a changed signal for the ContaminantType property
 * @param[in] newValue new value of contaminant type
 * @return ER_OK on success
 */
AJ_Status Cdm_CurrentAirQuality_EmitContaminantTypeChanged(AJ_BusAttachment *bus, const char *objPath, CurrentAirQuality_ContaminantType newValue);

/**
 * Emits a changed signal for the CurrentValue property
 * @param[in] newValue new value of current value
 * @return ER_OK on success
 */
AJ_Status Cdm_CurrentAirQuality_EmitCurrentValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue);

/**
 * Emits a changed signal for the MinValue property
 * @param[in] newValue new value of min value
 * @return ER_OK on success
 */
AJ_Status Cdm_CurrentAirQuality_EmitMinValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue);

/**
 * Emits a changed signal for the MaxValue property
 * @param[in] newValue new value of max value
 * @return ER_OK on success
 */
AJ_Status Cdm_CurrentAirQuality_EmitMaxValueChanged(AJ_BusAttachment *bus, const char *objPath, double newValue);

/**
 * Emits a changed signal for the Precision property
 * @param[in] newValue new value of precision
 * @return ER_OK on success
 */
AJ_Status Cdm_CurrentAirQuality_EmitPrecisionChanged(AJ_BusAttachment *bus, const char *objPath, double newValue);

/**
 * Emits a changed signal for the UpdateMinTime property
 * @param[in] newValue new value of update min time
 * @return ER_OK on success
 */
AJ_Status Cdm_CurrentAirQuality_EmitUpdateMinTimeChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

#endif /* CURRENTAIRQUALITYINTERFACE_H_ */