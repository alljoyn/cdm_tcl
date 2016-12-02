/**
 * @file
 */
/******************************************************************************
 *  * 
 *    Copyright (c) 2016 Open Connectivity Foundation and AllJoyn Open
 *    Source Project Contributors and others.
 *    
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0

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