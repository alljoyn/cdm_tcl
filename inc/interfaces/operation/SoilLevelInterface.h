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

#ifndef SOILLEVELINTERFACE_H_
#define SOILLEVELINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define SOIL_LEVEL "org.alljoyn.SmartSpaces.Operation.SoilLevel"

/**
 * SoilLevel interface members
 */
typedef enum {
    SOILLEVEL_PROP_VERSION = 0,
    SOILLEVEL_PROP_MAX_LEVEL,
    SOILLEVEL_PROP_TARGET_LEVEL,
    SOILLEVEL_PROP_SELECTABLE_LEVELS,
    SOILLEVEL_MEMBER_COUNT
} SoilLevelMembers;



extern const char* const intfDescOperationSoilLevel[SOILLEVEL_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationSoilLevel;


/**
 * Emits a changed signal for the MaxLevel property
 * @param[in] newValue new value of max level
 * @return ER_OK on success
 */
AJ_Status Cdm_SoilLevel_EmitMaxLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the TargetLevel property
 * @param[in] newValue new value of target level
 * @return ER_OK on success
 */
AJ_Status Cdm_SoilLevel_EmitTargetLevelChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the SelectableLevels property
 * @param[in] newValue new value of selectable levels
 * @return ER_OK on success
 */
AJ_Status Cdm_SoilLevel_EmitSelectableLevelsChanged(AJ_BusAttachment *bus, const char *objPath, Array_uint8 newValue);

#endif /* SOILLEVELINTERFACE_H_ */