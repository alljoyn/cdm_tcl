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

#ifndef REMOTECONTROLLABILITY_H_
#define REMOTECONTROLLABILITY_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * RemoteControllability interface listener
 */
typedef struct {
    /**
     * Handler for getting IsControllable property
     * @param[in] objPath object path
     * @param[out] isControllable isControllable
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetIsControllable) (const char* objPath, bool* isControllable);

} RemoteControllabilityListener;

/**
 * Get isControllable of RemoteControllability interface
 * @param[in] objPath the object path including the interface
 * @param[out] isControllable isControllable
 * @return AJ_OK on success
 */
AJ_Status Cdm_RemoteControllabilityInterfaceGetIsControllable(const char* objPath, bool* isControllable);

/**
 * Set isControllable of RemoteControllability interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] isControllable isControllable
 * @return AJ_OK on success
 */
AJ_Status Cdm_RemoteControllabilityInterfaceSetIsControllable(AJ_BusAttachment* busAttachment, const char* objPath, const bool isControllable);

#endif /* REMOTECONTROLLABILITY_H_ */