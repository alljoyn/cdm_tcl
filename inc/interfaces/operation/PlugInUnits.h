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
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef PLUGINUNITS_H_
#define PLUGINUNITS_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceErrors.h>

/**
 * PlugInInfo struct
 */
typedef struct {
    char* objectPath;
    uint32_t deviceId;
    bool pluggedIn;
} PlugInInfo;

/**
 * PlugInUnits interface listener
 */
typedef struct {
    /**
     * Handler for getting PlugInUnits property
     * @param[in] objPath object path
     * @param[out] plugInUnits plug in units
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetPlugInUnits) (const char* objPath, PlugInInfo* plugInUnits);

} PlugInUnitsListener;

/**
 * Get plugInUnits of PlugInUnits interface
 * @param[in] objPath the object path including the interface
 * @param[out] units plug in units
 * @return AJ_OK on success
 */
AJ_Status Cdm_PlugInUnitsInterfaceGetPlugInUnits(const char* objPath, PlugInInfo* units);

/**
 * Set plugInUnits of PlugInUnits interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] units plug in units
 * @return AJ_OK on success
 */

AJ_Status Cdm_PlugInUnitsInterfaceSetPlugInUnits(AJ_BusAttachment* busAttachment, const char* objPath, const PlugInInfo* units, const size_t plugInInfoSize);

#endif /* PLUGINUNITS_H_ */