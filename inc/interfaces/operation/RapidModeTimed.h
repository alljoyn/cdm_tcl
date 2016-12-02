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

#ifndef RAPIDMODETIMED_H_
#define RAPIDMODETIMED_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * RapidModeTimed interface listener
 */
typedef struct {
    /**
     * Handler for getting RapidModeMinutesRemaining property
     * @param[in] objPath object path
     * @param[out] value time remaining in rapid mode
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetRapidModeMinutesRemaining) (const char* objPath, uint16_t* value);

    /**
     * Handler for setting RapidModeMinutesRemaining property
     * @param[in] objPath object path
     * @param[in] value time remaining in rapid mode
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetRapidModeMinutesRemaining) (const char* objPath, const uint16_t value);

    /**
     * Handler for getting MaxSetMinutes property
     * @param[in] objPath object path
     * @param[out] value the maximum rapid mode set time
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetMaxSetMinutes) (const char* objPath, uint16_t* value);
} RapidModeTimedListener;

/**
 * Get time remaining in rapid mode of RapidModeTimed interface
 * @param[in] objPath the object path including the interface
 * @param[out] value time remaining in rapid mode
 * @return AJ_OK on success
 */
AJ_Status Cdm_RapidModeTimedInterfaceGetRapidModeMinutesRemaining(const char* objPath, uint16_t* value);

/**
 * Set time remaining in rapid mode of RapidModeTimed interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] value time remaining in rapid mode
 * @return AJ_OK on success
 */
AJ_Status Cdm_RapidModeTimedInterfaceSetRapidModeMinutesRemaining(AJ_BusAttachment* busAttachment, const char* objPath, const uint16_t value);

/**
 * Get the maximum rapid mode set time of RapidModeTimed interface
 * @param[in] objPath the object path including the interface
 * @param[out] value the maximum rapid mode set time
 * @return AJ_OK on success
 */
AJ_Status Cdm_RapidModeTimedInterfaceGetMaxSetMinutes(const char* objPath, uint16_t* value);

/**
 * Set the maximum rapid mode set time of RapidModeTimed interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] value the maximum rapid mode set time
 * @return AJ_OK on success
 */
AJ_Status Cdm_RapidModeTimedInterfaceSetMaxSetMinutes(AJ_BusAttachment* busAttachment, const char* objPath, const uint16_t value);

#endif /* RAPIDMODETIMED_H_ */