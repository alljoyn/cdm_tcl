/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#ifndef CDMCONTROLLEE_H_
#define CDMCONTROLLEE_H_

#include <ajtcl/services/ServicesCommon.h>
#include <ajtcl/alljoyn.h>
#include <stdbool.h>

typedef enum {
    UNDEFINED_INTERFACE             = 0,
    /* INPUT */
    HID_INTERFACE,

    /* Environment */
    CURRENT_AIR_QUALITY_INTERFACE,
    CURRENT_AIR_QUALITY_LEVEL_INTERFACE,
    CURRENT_HUMIDITY_INTERFACE,
    CURRENT_TEMPERATURE_INTERFACE,
    TARGET_HUMIDITY_INTERFACE,
    TARGET_TEMPERATURE_INTERFACE,
    TARGET_TEMPERATURE_LEVEL_INTERFACE,
    WATER_LEVEL_INTERFACE,
    WIND_DIRECTION_INTERFACE,

    /* Operation */
    AIR_RECIRCULATION_MODE_INTERFACE,
    ALERTS_INTERFACE,
    AUDIO_VIDEO_INPUT_INTERFACE,
    AUDIO_VOLUME_INTERFACE,
    BATTERY_STATUS_INTERFACE,
    CHANNEL_INTERFACE,
    CLIMATE_CONTROL_MODE_INTERFACE,
    CLOSED_STATUS_INTERFACE,
    CURRENT_POWER_INTERFACE,
    CYCLE_CONTROL_INTERFACE,
    DISH_WASHING_CYCLE_PHASE_INTERFACE,
    ENERGY_USAGE_INTERFACE,
    FAN_SPEED_LEVEL_INTERFACE,
    FILTER_STATUS_INTERFACE,
    HEATING_ZONE_INTERFACE,
    HVAC_FAN_MODE_INTERFACE,
    LAUNDRY_CYCLE_PHASE_INTERFACE,
    MOISTURE_OUTPUT_LEVEL_INTERFACE,
    ON_OFF_STATUS_INTERFACE,
    OFF_CONTROL_INTERFACE,
    ON_CONTROL_INTERFACE,
    OVEN_CYCLE_PHASE_INTERFACE,
    PLUG_IN_UNITS_INTERFACE,
    RAPID_MODE_INTERFACE,
    RAPID_MODE_TIMED_INTERFACE,
    REMOTE_CONTROLLABILITY_INTERFACE,
    REPEAT_MODE_INTERFACE,
    RESOURCE_SAVING_INTERFACE,
    ROBOT_CLEANING_CYCLE_PHASE_INTERFACE,
    SOIL_LEVEL_INTERFACE,
    SPIN_SPEED_LEVEL_INTERFACE,
    TIMER_INTERFACE,

    /* UserInterfaceSettings */
    LANGUAGE_DISPLAY_INTERFACE,
    TEMPERATURE_DISPLAY_INTERFACE,
    TIME_DISPLAY_INTERFACE,

    LAST_BASIC_INTERFACE_TYPE,
    NUMBER_OF_BASIC_INTERFACE_TYPE,
    MAX_BASIC_INTERFACE_TYPE        = NUMBER_OF_BASIC_INTERFACE_TYPE,
} CdmInterfaceTypes;

/**
 * Structure which holds the handler functions for a given interface.
 */
typedef struct {
    /**
     * Handler called when getting property value is requested.
     * @param[in] replyMsg put the reply in here and call AJ_DeliverMsg
     * @param[in] objPath the object path including the interface
     * @param[in] memberIndex index of the property in the interface description
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetProperty)(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex);

    /**
     * Handler called when setting property value is requested.
     * @param[in] busAttachment bus attachment in case a signal is to be emitted
     * @param[in] msg the original message containing the propery value
     * @param[in] objPath the object path including the interface
     * @param[in] memberIndex index of the property in the interface description
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetProperty)(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet);

    /**
     * Handler called when method is called.
     * @param[in] msg message with the method args
     * @param[in] objPath the object path including the interface
     * @param[in] memberIndex index of the method in the interface description
     * @return AJ_OK on success
     */
    AJ_Status (*OnMethodHandler)(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex);
} InterfaceHandler;

/**
 * Initialize CDM service framework.
 * @param[in] emitSignalOnSetProperty
 *            - true results in a changed signal will be automatically emitted during OnSetProperty
 *            - false no signal is emitted
 * @return AJ_OK on success.
 */
AJ_Status Cdm_Init(bool emitSignalOnSetProperty);

/**
 * Deinitialize CDM service framework.
 */
void Cdm_Deinit(void);

/**
 * Add interface.
 * @param[in] objPath the object path without the interface name
 * @param[in] intfName interface name
 * @param[in] intfDesc interface description
 * @param[in] intfHandler interface handler
 * @param[in] intfModel interface model
 * @return  Return AJ_Status
 *          - AJ_OK on success
 *          - AJ_ERR_INVALID if any input parameter is null
 *          - AJ_ERR_DISALLOWED if the interface name has already been registered for the given
 *            object path
 *          - AJ_ERR_RESOURCES if memory allocation fails
 *          - An error status otherwise
 AJ_ERR_RESOURCES
 */
AJ_Status Cdm_AddInterface(const char* objPath, const char* intfName, const char* const* intfDesc, const InterfaceHandler* intfHandler, void* intfModel);

/**
 * Start CDM service framework.
 * Objects with interfaces are registered.
 * @return AJ_OK on success
 */
AJ_Status Cdm_Start(void);

/**
 * Returns whether CDM was initialised to emit changed signals when a property value is changed
 * @return bool a true value is used to indicate CDM will emit a changed signal when OnSetProperty is called
 */
bool Cdm_EmitSignalOnPropertySet();

/**
 * Function used to process CDM messages.
 * @param[in] busAttachment bus attachment
 * @param[in] msg message
 * @param[out] status status
 * @return service status
 */
AJSVC_ServiceStatus Cdm_MessageProcessor(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* status);

/**
 * Get pointer to the interface's model
 * @param[in] objPath the object path
 * @param[in] intfName interface name
 * @return pointer to properties belonged to the interface
 */
void* GetInterfaceModel(const char* objPath, const char* intfName);

/**
 * Make message identifier (mainly used for emitting signal)
 * @param[in] objPath the object path including the interface
 * @param[in] intfName interface name
 * @param[in] memberIndex index of the member in the interface description
 * @param[out] msgId message identifier made
 * @return AJ_OK on success
 */
AJ_Status MakeMessageId(const char* objPath, const char* intfName, uint8_t memberIndex, uint32_t* msgId);

/**
 * Make message identifier for PropertiesChanged signal
 * @param[in] objPath the object path including the interface
 * @param[out] msgId message identifier made
 * @return AJ_OK on success
 */
AJ_Status MakePropChangedId(const char* objPath, uint32_t* msgId);

#endif /* CDMCONTROLLEE_H_ */
