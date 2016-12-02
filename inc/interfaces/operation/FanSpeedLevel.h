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

#ifndef FANSPEEDLEVEL_H_
#define FANSPEEDLEVEL_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * FanSpeedLevel interface listener
 */
typedef struct {
    /**
     * Handler for getting FanSpeedLevel property
     * @param[in] objPath object path
     * @param[out] fanSpeedLevel Fan speed level of a device
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetFanSpeedLevel) (const char* objPath, uint8_t* fanSpeedLevel);

    /**
     * Handler for setting FanSpeedLevel property
     * @param[in] objPath object path
     * @param[in] fanSpeedLevel Fan speed level of a device
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetFanSpeedLevel) (const char* objPath, const uint8_t fanSpeedLevel);

    /**
     * Handler for getting MaxFanSpeedLevel property
     * @param[in] objPath object path
     * @param[out] maxFanSpeedLevel target fan speed level
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetMaxFanSpeedLevel) (const char* objPath, uint8_t* maxFanSpeedLevel);

    /**
     * Handler for getting AutoMode property
     * @param[in] objPath object path
     * @param[out] autoMode state of the auto mode
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetAutoMode) (const char* objPath, uint8_t* autoMode);

    /**
     * Handler for setting FanSpeedLevel property
     * @param[in] objPath object path
     * @param[in] autoMode state of the auto mode
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetAutoMode) (const char* objPath, const uint8_t autoMode);

} FanSpeedLevelListener;

/**
 * Get fanSpeedLevel of FanSpeedLevel interface
 * @param[in] objPath the object path including the interface
 * @param[out] fanSpeedLevel Fan speed level of a device
 * @return AJ_OK on success
 */
AJ_Status Cdm_FanSpeedLevelInterfaceGetFanSpeedLevel(const char* objPath, uint8_t* fanSpeedLevel);

/**
 * Set fanSpeedLevel of FanSpeedLevel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] fanSpeedLevel Fan speed level of a device
 * @return AJ_OK on success
 */
AJ_Status Cdm_FanSpeedLevelInterfaceSetFanSpeedLevel(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t fanSpeedLevel);

/**
 * Get maxFanSpeedLevel of FanSpeedLevel interface
 * @param[in] objPath the object path including the interface
 * @param[out] maxFanSpeedLevel target fan speed level
 * @return AJ_OK on success
 */
AJ_Status Cdm_FanSpeedLevelInterfaceGetMaxFanSpeedLevel(const char* objPath, uint8_t* maxFanSpeedLevel);

/**
 * Set maxFanSpeedLevel of FanSpeedLevel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] maxFanSpeedLevel target fan speed level
 * @return AJ_OK on success
 */
AJ_Status Cdm_FanSpeedLevelInterfaceSetMaxFanSpeedLevel(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t maxFanSpeedLevel);


/**
 * Get autoMode of FanSpeedLevel interface
 * @param[in] objPath the object path including the interface
 * @param[out] autoMode state of the auto mode
 * @return AJ_OK on success
 */
AJ_Status Cdm_FanSpeedLevelInterfaceGetAutoMode(const char* objPath, uint8_t* autoMode);

/**
 * Set autoMode of FanSpeedLevel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] autoMode state of the auto mode
 * @return AJ_OK on success
 */
AJ_Status Cdm_FanSpeedLevelInterfaceSetAutoMode(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t autoMode);

#endif /* FANSPEEDLEVEL_H_ */