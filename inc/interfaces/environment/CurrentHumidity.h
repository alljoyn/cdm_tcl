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

#ifndef CURRENTHUMIDITY_H_
#define CURRENTHUMIDITY_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * CurrentHumidity interface listener
 */
typedef struct {
    /**
     * Handler for getting CurrentValue property
     * @param[in] objPath object path
     * @param[out] currentValue the current value
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetCurrentValue) (const char* objPath, uint8_t* currentValue);

    /**
     * Handler for getting MaxValue property
     * @param[in] objPath object path
     * @param[out] maxValue the max value
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetMaxValue) (const char* objPath, uint8_t* maxValue);

} CurrentHumidityListener;

/**
 * Get the current value of CurrentHumidity interface
 * @param[in] objPath the object path including the interface
 * @param[out] currentValue the current value
 * @return AJ_OK on success
 */
AJ_Status Cdm_CurrentHumidityInterfaceGetCurrentValue(const char* objPath, uint8_t* currentValue);

/**
 * Set the current value of CurrentHumidity interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] currentValue the current value
 * @return AJ_OK on success
 */
AJ_Status Cdm_CurrentHumidityInterfaceSetCurrentValue(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t currentValue);

/**
 * Get the maxValue of CurrentHumidity interface
 * @param[in] objPath the object path including the interface
 * @param[out] maxValue the maxValue
 * @return AJ_OK on success
 */
AJ_Status Cdm_CurrentHumidityInterfaceGetMaxValue(const char* objPath, uint8_t* maxValue);

/**
 * Set the maxValue of CurrentHumidity interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] maxValue the maxValue
 * @return AJ_OK on success
 */
AJ_Status Cdm_CurrentHumidityInterfaceSetMaxValue(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t maxValue);

#endif /* CURRENTHUMIDITY_H_ */