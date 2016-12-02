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

#ifndef RESOURCESSAVING_H_
#define RESOURCESSAVING_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * ResourceSaving interface listener
 */
typedef struct {
    /**
     * Handler for getting ResourceSavingMode property
     * @param[in] objPath object path
     * @param[out] resourceSavingMode The current resource saving mode of the device
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetResourceSavingMode) (const char* objPath, bool* resourceSavingMode);

    /**
     * Handler for setting ResourceSavingMode property
     * @param[in] objPath object path
     * @param[in] resourceSavingMode The current resource saving mode of the device
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetResourceSavingMode) (const char* objPath, const bool resourceSavingMode);

} ResourceSavingListener;

/**
 * Get resourceSavingMode of ResourceSaving interface
 * @param[in] objPath the object path including the interface
 * @param[out] resourceSavingMode The current resource saving mode of the device
 * @return AJ_OK on success
 */
AJ_Status Cdm_ResourceSavingInterfaceGetResourceSavingMode(const char* objPath, bool* resourceSavingMode);

/**
 * Set resourceSavingMode of Channel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] resourceSavingMode The current resource saving mode of the device
 * @return AJ_OK on success
 */
AJ_Status Cdm_ResourceSavingInterfaceSetResourceSavingMode(AJ_BusAttachment* busAttachment, const char* objPath, const bool resourceSavingMode);

#endif /* RESOURCESSAVING_H_ */