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

#ifndef AUDIOVIDEOINPUT_H_
#define AUDIOVIDEOINPUT_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * InputSource struct
 */
typedef struct  {
    uint16_t id;
    uint16_t sourceType;
    uint8_t detectedState;
    uint16_t portNumber;
    char* friendlyName;
} InputSource;

/**
 * AudioVideoInput interface listener
 */
typedef struct {
    /**
     * Handler for getting inputSourceId property
     * @param[in] objPath object path
     * @param[out] inputSourceId Activated input source id
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetInputSourceId) (const char* objPath, uint16_t* inputSourceId);

    /**
     * Handler for setting inputSourceId property
     * @param[in] objPath object path
     * @param[in] inputSourceId Activated input source id
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetInputSourceId) (const char* objPath, const uint16_t inputSourceId);

    /**
     * Handler for getting InputSource property
     * @param[in] objPath object path
     * @param[out] supportedInputSources Array of supported input sources
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetSupportedInputSources) (const char* objPath, InputSource* supportedInputSources);

} AudioVideoInputListener;

/**
 * Get inputSourceId of AudioVideoInput interface
 * @param[in] objPath the object path including the interface
 * @param[out] channelId channel id
 * @return AJ_OK on success
 */
AJ_Status Cdm_AudioVideoInputInterfaceGetInputSourceId(const char* objPath, uint16_t* inputSourceId);

/**
 * Set inputSourceId of AudioVideoInput interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] inputSourceId Activated input source id
 * @return AJ_OK on success
 */
AJ_Status Cdm_AudioVideoInputInterfaceSetInputSourceId(AJ_BusAttachment* busAttachment, const char* objPath, const uint16_t inputSourceId);

/**
 * Get InputSource of AudioVideoInput interface
 * @param[in] objPath the object path including the interface
 * @param[out] supportedInputSources Array of supported input sources
 * @return AJ_OK on success
 */
AJ_Status Cdm_AudioVideoInputInterfaceGetSupportedInputSources(const char* objPath, InputSource* supportedInputSources);

/**
 * Set InputSource of AudioVideoInput interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] supportedInputSources Array of supported input sources
 * @param[in] InputSourceSize InputSource List size
 * @return AJ_OK on success
 */
AJ_Status Cdm_AudioVideoInputInterfaceSetSupportedInputSources(AJ_BusAttachment* busAttachment, const char* objPath, const InputSource* supportedInputSources, const size_t inputSourceListSize);

#endif /* AUDIOVIDEOINPUT_H_ */