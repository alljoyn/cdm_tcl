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

#ifndef REPEATMODE_H_
#define REPEATMODE_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * RepeatMode interface listener
 */
typedef struct {
    /**
     * Handler for getting RepeatMode property
     * @param[in] objPath object path
     * @param[out] repeatMode True if the device works in repeat mode
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetRepeatMode) (const char* objPath, bool* repeatMode);

      /**
     * Handler for setting RepeatMode property
     * @param[in] objPath object path
     * @param[in] repeatMode True if the device works in repeat mode
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetRepeatMode) (const char* objPath, const bool repeatMode);
} RepeatModeListener;

/**
 * Get repeatMode of RepeatMode interface
 * @param[in] objPath the object path including the interface
 * @param[out] repeatMode True if the device works in repeat mode
 * @return AJ_OK on success
 */
AJ_Status Cdm_RepeatModeInterfaceGetRepeatMode(const char* objPath, bool* repeatMode);

/**
 * Set repeatMode of RepeatMode interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] repeatMode True if the device works in repeat mode
 * @return AJ_OK on success
 */
AJ_Status Cdm_RepeatModeInterfaceSetRepeatMode(AJ_BusAttachment* busAttachment, const char* objPath, const bool repeatMode);

#endif /* REPEATMODE_H_ */