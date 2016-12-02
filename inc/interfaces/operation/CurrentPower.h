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

#ifndef CURRENTPOWER_H_
#define CURRENTPOWER_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * CurrentPower interface listener
 */
typedef struct {
    /**
     * Handler for getting CurrentPower property
     * @param[in] objPath object path
     * @param[out] currentPower power consumption of the device in watts (W)
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetCurrentPower) (const char* objPath, double* currentPower);

    /**
     * Handler for getting Precision property
     * @param[in] objPath object path
     * @param[out] precision the number of watts the
                actual power consumption must change before CurrentPower is updated
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetPrecision) (const char* objPath, double* precision);

    /**
     * Handler for getting UpdateMinTime property
     * @param[in] objPath object path
     * @param[out] updateMinTime The minimum time between updates of the CurrentPower property in milliseconds
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetUpdateMinTime) (const char* objPath, uint16_t* updateMinTime);

} CurrentPowerListener;

/**
 * Get currentPower of CurrentPower interface
 * @param[in] objPath the object path including the interface
 * @param[out] currentPower power consumption of the device in watts (W)
 * @return AJ_OK on success
 */
AJ_Status Cdm_CurrentPowerInterfaceGetCurrentPower(const char* objPath, double* currentPower);

/**
 * Set currentPower of CurrentPower of CurrentPower interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] currentPower power consumption of the device in watts (W)
 * @return AJ_OK on success
 */
AJ_Status Cdm_CurrentPowerInterfaceSetCurrentPower(AJ_BusAttachment* busAttachment, const char* objPath, const double currentPower);

/**
 * Get precision of CurrentPower interface
 * @param[in] objPath the object path including the interface
 * @param[out] precision the number of watts the
                actual power consumption must change before CurrentPower is updated
 * @return AJ_OK on success
 */
AJ_Status Cdm_CurrentPowerInterfaceGetPrecision(const char* objPath, double* precision);

/**
 * Set precision of Precision of CurrentPower interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] precision the number of watts the
                actual power consumption must change before CurrentPower is updated
 * @return AJ_OK on success
 */
AJ_Status Cdm_CurrentPowerInterfaceSetPrecision(AJ_BusAttachment* busAttachment, const char* objPath, const double precision);

/**
 * Get updateMinTime of CurrentPower interface
 * @param[in] objPath the object path including the interface
 * @param[out] updateMinTime The minimum time between updates of the CurrentPower property in milliseconds
 * @return AJ_OK on success
 */
AJ_Status Cdm_CurrentPowerInterfaceGetUpdateMinTime(const char* objPath, uint16_t* updateMinTime);

/**
 * Set updateMinTime of UpdateMinTime of CurrentPower interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] updateMinTime The minimum time between updates of the CurrentPower property in milliseconds
 * @return AJ_OK on success
 */
AJ_Status Cdm_CurrentPowerInterfaceSetUpdateMinTime(AJ_BusAttachment* busAttachment, const char* objPath, const uint16_t updateMinTime);

#endif /* CURRENTPOWER_H_ */