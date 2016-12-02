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

#ifndef AIRRECIRCULATIONMODE_H_
#define AIRRECIRCULATIONMODE_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * AirRecirculationMode interface listener
 */
typedef struct {
    /**
     * Handler for getting IsRecirculating property
     * @param[in] objPath object path
     * @param[out] isRecirculating isRecirculating
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetIsRecirculating) (const char* objPath, bool* isRecirculating);

    /**
     * Handler for setting IsRecirculating property
     * @param[in] objPath object path
     * @param[out] isRecirculating isRecirculating
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetIsRecirculating) (const char* objPath, const bool isRecirculating);

} AirRecirculationModeListener;

/**
 * Get isRecirculating of AirRecirculationMode interface
 * @param[in] objPath the object path including the interface
 * @param[out] isRecirculating isRecirculating
 * @return AJ_OK on success
 */
AJ_Status Cdm_AirRecirculationModeInterfaceGetIsRecirculating(const char* objPath, bool* isRecirculating);

/**
 * Set isRecirculating of AirRecirculationMode interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] isRecirculating isRecirculating
 * @return AJ_OK on success
 */
AJ_Status Cdm_AirRecirculationModeInterfaceSetIsRecirculating(AJ_BusAttachment* busAttachment, const char* objPath, const bool isRecirculating);

#endif /* AIRRECIRCULATIONMODE_H_ */