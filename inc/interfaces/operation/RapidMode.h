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

#ifndef RAPIDMODE_H_
#define RAPIDMODE_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * RapidMode interface listener
 */
typedef struct {
    /**
     * Handler for getting RapidMode property
     * @param[in] objPath object path
     * @param[out] rapidMode True if the device works in rapid mode
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetRapidMode) (const char* objPath, bool* rapidMode);

      /**
     * Handler for setting RapidMode property
     * @param[in] objPath object path
     * @param[in] rapidMode True if the device works in rapid mode
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetRapidMode) (const char* objPath, const bool rapidMode);
} RapidModeListener;

/**
 * Get rapidMode of RapidMode interface
 * @param[in] objPath the object path including the interface
 * @param[out] rapidMode True if the device works in rapid mode
 * @return AJ_OK on success
 */
AJ_Status Cdm_RapidModeInterfaceGetRapidMode(const char* objPath, bool* rapidMode);

/**
 * Set rapidMode of RapidMode interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] rapidMode True if the device works in rapid mode
 * @return AJ_OK on success
 */
AJ_Status Cdm_RapidModeInterfaceSetRapidMode(AJ_BusAttachment* busAttachment, const char* objPath, const bool rapidMode);

#endif /* RAPIDMODE_H_ */