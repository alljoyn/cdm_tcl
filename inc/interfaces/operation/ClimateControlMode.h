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

#ifndef CLIMATECONTROLMODE_H_
#define CLIMATECONTROLMODE_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * ClimateControlMode interface listener
 */
typedef struct {
    /**
     * Handler for getting Mode property
     * @param[in] objPath object path
     * @param[out] mode mode of device
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetMode) (const char* objPath, uint16_t* mode);

    /**
     * Handler for setting Mode property
     * @param[in] objPath object path
     * @param[in] mode mode of device
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetMode) (const char* objPath, const uint16_t mode);

    /**
     * Handler for getting SupportedModes property
     * @param[in] objPath object path
     * @param[out] supportedModes supported modes
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetSupportedModes) (const char* objPath, uint16_t* supportedModes);

    /**
     * Handler for getting OperationalState property
     * @param[in] objPath object path
     * @param[out] operationalState status of device
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetOperationalState) (const char* objPath, uint16_t* operationalState);

} ClimateControlModeListener;

/**
 * Get mode of ClimateControlMode interface
 * @param[in] objPath the object path including the interface
 * @param[out] mode mode of device
 * @return AJ_OK on success
 */
AJ_Status Cdm_ClimateControlModeInterfaceGetMode(const char* objPath, uint16_t* mode);

/**
 * Set mode of ClimateControlMode interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] mode mode of device
 * @return AJ_OK on success
 */
AJ_Status Cdm_ClimateControlModeInterfaceSetMode(AJ_BusAttachment* busAttachment, const char* objPath, const uint16_t mode);

/**
 * Get supportedModes of ClimateControlMode interface
 * @param[in] objPath the object path including the interface
 * @param[out] supportedModes supported modes
 * @return AJ_OK on success
 */
AJ_Status Cdm_ClimateControlModeInterfaceGetSupportedModes(const char* objPath, uint16_t* supportedModes);

/**
 * Set supportedModes of ClimateControlMode interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] supportedModes supported modes
 * @return AJ_OK on success
 */
AJ_Status Cdm_ClimateControlModeInterfaceSetSupportedModes(AJ_BusAttachment* busAttachment, const char* objPath, const uint16_t* supportedModes, const size_t supportedModeSize);

/**
 * Get operationalState of ClimateControlMode interface
 * @param[in] objPath the object path including the interface
 * @param[out] operationalState status of device
 * @return AJ_OK on success
 */
AJ_Status Cdm_ClimateControlModeInterfaceGetOperationalState(const char* objPath, uint16_t* operationalState);

/**
 * Set operationalState of ClimateControlMode interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] operationalState status of device
 * @return AJ_OK on success
 */
AJ_Status Cdm_ClimateControlModeInterfaceSetOperationalState(AJ_BusAttachment* busAttachment, const char* objPath, const uint16_t operationalState);

#endif /* CLIMATECONTROLMODE_H_ */