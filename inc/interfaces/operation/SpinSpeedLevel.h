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

#ifndef SPINSPEEDLEVEL_H_
#define SPINSPEEDLEVEL_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * SpinSpeedLevel interface listener
 */
typedef struct {
    /**
     * Handler for getting MaxLevel property
     * @param[in] objPath object path
     * @param[out] maxLevel max level
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetMaxLevel) (const char* objPath, uint8_t* maxLevel);

    /**
     * Handler for getting TargetLevel property
     * @param[in] objPath object path
     * @param[out] targetLevel target level
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetTargetLevel) (const char* objPath, uint8_t* targetLevel);

    /**
     * Handler for setting TargetLevel property
     * @param[in] objPath object path
     * @param[in] targetLevel target level
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetTargetLevel) (const char* objPath, const uint8_t targetLevel);

    /**
     * Handler for getting SelectableLevels property
     * @param[in] objPath object path
     * @param[out] selectableLevels selectable levels
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetSelectableLevels) (const char* objPath, uint8_t* selectableLevels);

} SpinSpeedLevelListener;

/**
 * Get MaxLevel of SpinSpeedLevel interface
 * @param[in] objPath the object path including the interface
 * @param[out] maxLevel max level
 * @return AJ_OK on success
 */
AJ_Status Cdm_SpinSpeedLevelInterfaceGetMaxLevel(const char* objPath, uint8_t* maxLevel);

/**
 * Set MaxLevel of SpinSpeedLevel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] maxLevel max level
 * @return AJ_OK on success
 */
AJ_Status Cdm_SpinSpeedLevelInterfaceSetMaxLevel(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t maxLevel);

/**
 * Get TargetLevel of SpinSpeedLevel interface
 * @param[in] objPath the object path including the interface
 * @param[out] targetLevel target level
 * @return AJ_OK on success
 */
AJ_Status Cdm_SpinSpeedLevelInterfaceGetTargetLevel(const char* objPath, uint8_t* targetLevel);

/**
 * Set TargetLevel of SpinSpeedLevel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] targetLevel target level
 * @return AJ_OK on success
 */
AJ_Status Cdm_SpinSpeedLevelInterfaceSetTargetLevel(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t targetLevel);

/**
 * Get SelectableLevels of SpinSpeedLevel interface
 * @param[in] objPath the object path including the interface
 * @param[out] selectableLevels selectable levels
 * @return AJ_OK on success
 */
AJ_Status Cdm_SpinSpeedLevelInterfaceGetSelectableLevels(const char* objPath, uint8_t* selectableLevels);

/**
 * Set SelectableLevels of SpinSpeedLevel interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] selectableLevels selectable levels
 * @param[in] selectableLevelsSize selectable levels size
 * @return AJ_OK on success
 */
AJ_Status Cdm_SpinSpeedLevelInterfaceSetSelectableLevels(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t* selectableLevels, const size_t selectableLevelsSize);


#endif /* SPINSPEEDLEVEL_H_ */