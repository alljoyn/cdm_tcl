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

#ifndef MOISTUREOUTPUTLEVEL_H_
#define MOISTUREOUTPUTLEVEL_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * MoistureOutputLevel interface listener
 */
typedef struct {
    /**
     * Handler for getting MoistureOutputLevel property
     * @param[in] objPath object path
     * @param[out] value moisture output level
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetMoistureOutputLevel) (const char* objPath, uint8_t* value);

    /**
     * Handler for setting MoistureOutputLevel property
     * @param[in] objPath object path
     * @param[in] value moisture output level
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetMoistureOutputLevel) (const char* objPath, const uint8_t value);

    /**
     * Handler for getting MaxMoistureOutputLevel property
     * @param[in] objPath object path
     * @param[out] value the maximum moisture output level
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetMaxMoistureOutputLevel) (const char* objPath, uint8_t* value);

    /**
     * Handler for getting AutoMode property
     * @param[in] objPath object path
     * @param[out] autoMode auto mode
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetAutoMode) (const char* objPath, uint8_t* autoMode);

    /**
     * Handler for setting AutoMode property
     * @param[in] objPath object path
     * @param[in] autoMode auto mode
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetAutoMode) (const char* objPath, const uint8_t autoMode);
} MoistureOutputLevelListener;

/**
 * Get moisture output level of MoistureOutputLevel interface
 * @param[in] objPath the object path including the interface
 * @param[out] value moisture output level
 * @return AJ_OK on success
 */
AJ_Status Cdm_MoistureOutputLevelInterfaceGetMoistureOutputLevel(const char* objPath, uint8_t* value);

/**
 * Set moisture output level of MoistureOutputLevel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] value moisture output level
 * @return AJ_OK on success
 */
AJ_Status Cdm_MoistureOutputLevelInterfaceSetMoistureOutputLevel(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t value);

/**
 * Get the maximum moisture output level of MoistureOutputLevel interface
 * @param[in] objPath the object path including the interface
 * @param[out] value the maximum moisture output level
 * @return AJ_OK on success
 */
AJ_Status Cdm_MoistureOutputLevelInterfaceGetMaxMoistureOutputLevel(const char* objPath, uint8_t* value);

/**
 * Set the maximum moisture output level of MoistureOutputLevel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] value the maximum moisture output level
 * @return AJ_OK on success
 */
AJ_Status Cdm_MoistureOutputLevelInterfaceSetMaxMoistureOutputLevel(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t value);

/**
 * Get auto mode of MoistureOutputLevel interface
 * @param[in] objPath the object path including the interface
 * @param[out] autoMode auto mode
 * @return AJ_OK on success
 */
AJ_Status Cdm_MoistureOutputLevelInterfaceGetAutoMode(const char* objPath, uint8_t* autoMode);

/**
 * Set auto mode of MoistureOutputLevel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] autoMode auto mode
 * @return AJ_OK on success
 */
AJ_Status Cdm_MoistureOutputLevelInterfaceSetAutoMode(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t autoMode);

#endif /* MOISTUREOUTPUTLEVEL_H_ */