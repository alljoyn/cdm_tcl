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

#ifndef HID_H_
#define HID_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * InputEvent struct
 */
typedef struct {
    uint16_t type;
    uint16_t code;
    int32_t value;
} InputEvent;

/**
 * SupportedInputEvent struct
 */
typedef struct {
    uint16_t type;
    uint16_t code;
    int32_t min;
    int32_t max;
} SupportedInputEvent;

typedef struct {
    /**
     * Handler for getting SupportedInputEvent property
     * @param[in] objPath object path
     * @param[out] supportedEvents List of supported input events by a device.
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetSupportedEvents) (const char* objPath, SupportedInputEvent* supportedEvents);

    /**
     * Handler for InjectEvents method
     * @param[in] objPath object path
     * @param[in] inputEvent Inject the user input events for human interface devices
     * @param[in] numRecords InputEvent Record count
     * @return AJ_OK on success
     */
    AJ_Status (*OnInjectEvents) (const char* objPath, const InputEvent* inputEvent, const size_t numRecords);
} HidListener;

/**
 * Get displayLanguage of Hid interface
 * @param[in] objPath the object path including the interface
 * @param[out] supportedEvents List of supported input events by a device.
 * @return AJ_OK on success
 */
AJ_Status Cdm_HidInterfaceGetSupportedEvents(const char* objPath, SupportedInputEvent* supportedEvents);

/**
 * Set displayLanguage of Hid interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] supportedEvents List of supported input events by a device.
 * @param[in] supportedEventListSize SupportedInputEvent List size
 * @return AJ_OK on success
 */
AJ_Status Cdm_HidInterfaceSetSupportedEvents(AJ_BusAttachment* busAttachment, const char* objPath, const SupportedInputEvent* supportedEvents, const size_t supportedEventListSize);

#endif /* HID_H_ */