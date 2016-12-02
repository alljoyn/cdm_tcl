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

#ifndef AUDIOVOLUME_H_
#define AUDIOVOLUME_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * AudioVolume interface listener
 */
typedef struct {
    /**
     * Handler for getting Volume property
     * @param[in] objPath object path
     * @param[out] volume volume
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetVolume) (const char* objPath, uint8_t* volume);

    /**
     * Handler for setting Volume property
     * @param[in] objPath object path
     * @param[in] volume volume
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetVolume) (const char* objPath, const uint8_t volume);

    /**
     * Handler for getting MaxVolume property
     * @param[in] objPath object path
     * @param[out] maxVolume the maximum volume
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetMaxVolume) (const char* objPath, uint8_t* maxVolume);

    /**
     * Handler for getting Mute property
     * @param[in] objPath object path
     * @param[out] mute mute
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetMute) (const char* objPath, bool* mute);

    /**
     * Handler for setting Mute property
     * @param[in] objPath object path
     * @param[in] mute mute
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetMute) (const char* objPath, const bool mute);
} AudioVolumeListener;

/**
 * Get volume of AudioVolume interface
 * @param[in] objPath the object path including the interface
 * @param[out] volume volume
 * @return AJ_OK on success
 */
AJ_Status Cdm_AudioVolumeInterfaceGetVolume(const char* objPath, uint8_t* volume);

/**
 * Set volume of AudioVolume interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] volume volume
 * @return AJ_OK on success
 */
AJ_Status Cdm_AudioVolumeInterfaceSetVolume(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t volume);

/**
 * Get the maximum volume of AudioVolume interface
 * @param[in] objPath the object path including the interface
 * @param[out] maxVolume the maximum volume
 * @return AJ_OK on success
 */
AJ_Status Cdm_AudioVolumeInterfaceGetMaxVolume(const char* objPath, uint8_t* maxVolume);

/**
 * Set the maximum volume of AudioVolume interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] maxVolume the maximum volume
 * @return AJ_OK on success
 */
AJ_Status Cdm_AudioVolumeInterfaceSetMaxVolume(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t maxVolume);

/**
 * Get mute of AudioVolume interface
 * @param[in] objPath the object path including the interface
 * @param[out] mute mute
 * @return AJ_OK on success
 */
AJ_Status Cdm_AudioVolumeInterfaceGetMute(const char* objPath, bool* mute);

/**
 * Set mute of AudioVolume interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] mute mute
 * @return AJ_OK on success
 */
AJ_Status Cdm_AudioVolumeInterfaceSetMute(AJ_BusAttachment* busAttachment, const char* objPath, const bool mute);

#endif /* AUDIOVOLUME_H_ */