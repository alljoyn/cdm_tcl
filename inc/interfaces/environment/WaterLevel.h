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

#ifndef WATERLEVEL_H_
#define WATERLEVEL_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * WaterLevel interface listener
 */
typedef struct {
    /**
     * Handler for getting SupplySource property
     * @param[in] objPath object path
     * @param[out] supplySource target fan speed level
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetSupplySource) (const char* objPath, uint8_t* supplySource);

    /**
     * Handler for getting CurrentLevel property
     * @param[in] objPath object path
     * @param[out] currentLevel target fan speed level
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetCurrentLevel) (const char* objPath, uint8_t* currentLevel);

    /**
     * Handler for getting MaxLevel property
     * @param[in] objPath object path
     * @param[out] maxLevel target fan speed level
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetMaxLevel) (const char* objPath, uint8_t* maxLevel);

} WaterLevelListener;

/**
 * Get supplySource of WaterLevel interface
 * @param[in] objPath the object path including the interface
 * @param[out] supplySource water supply source
 * @return AJ_OK on success
 */
AJ_Status Cdm_WaterLevelInterfaceGetSupplySource(const char* objPath, uint8_t* supplySource);

/**
 * Set supplySource of WaterLevel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] supplySource water supply source
 * @return AJ_OK on success
 */
AJ_Status Cdm_WaterLevelInterfaceSetSupplySource(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t supplySource);

/**
 * Get currentLevel of WaterLevel interface
 * @param[in] objPath the object path including the interface
 * @param[out] currentLevel current water level
 * @return AJ_OK on success
 */
AJ_Status Cdm_WaterLevelInterfaceGetCurrentLevel(const char* objPath, uint8_t* currentLevel);

/**
 * Set currentLevel of WaterLevel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] currentLevel current water level
 * @return AJ_OK on success
 */
AJ_Status Cdm_WaterLevelInterfaceSetCurrentLevel(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t currentLevel);

/**
 * Get maxLevel of WaterLevel interface
 * @param[in] objPath the object path including the interface
 * @param[out] maxLevel max water level
 * @return AJ_OK on success
 */
AJ_Status Cdm_WaterLevelInterfaceGetMaxLevel(const char* objPath, uint8_t* maxLevel);

/**
 * Set maxLevel of WaterLevel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] maxLevel max water level
 * @return AJ_OK on success
 */
AJ_Status Cdm_WaterLevelInterfaceSetMaxLevel(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t maxLevel);


#endif /* WATERLEVEL_H_ */