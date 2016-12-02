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

#ifndef CYCLECONTROL_H_
#define CYCLECONTROL_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceErrors.h>

/**
 * CycleControl interface listener
 */
typedef struct {
    /**
     * Handler for getting OperationalState property
     * @param[in] objPath object path
     * @param[out] operationalState operational state
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetOperationalState) (const char* objPath, uint8_t* operationalState);

    /**
     * Handler for getting SupportedOperationalStates property
     * @param[in] objPath object path
     * @param[out] supportedOperationalStates supported operational states
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetSupportedOperationalStates) (const char* objPath, uint8_t* supportedOperationalStates);

    /**
     * Handler for getting SupportedOperationalCommands property
     * @param[in] objPath object path
     * @param[out] supportedOperationalCommands supported operational commands
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetSupportedOperationalCommands) (const char* objPath, uint8_t* supportedOperationalCommands);

    /**
     * Handler for ExecuteOperationalCommand method
     * @param[in] objPath object path
     * @param[in] command command
     * @param[out] errorCode error code
     * @return AJ_OK on success
     */
    AJ_Status (*OnExecuteOperationalCommand) (const char* objPath, const uint8_t command, ErrorCode* errorCode);
} CycleControlListener;

/**
 * Get OperationalState of CycleControl interface
 * @param[in] objPath the object path including the interface
 * @param[out] operationalState operational state
 * @return AJ_OK on success
 */
AJ_Status Cdm_CycleControlInterfaceGetOperationalState(const char* objPath, uint8_t* operationalState);

/**
 * Set OperationalState of CycleControl interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] operationalState number of heating zones
 * @return AJ_OK on success
 */
AJ_Status Cdm_CycleControlInterfaceSetOperationalState(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t operationalState);

/**
 * Get SupportedOperationalStates of CycleControl interface
 * @param[in] objPath the object path including the interface
 * @param[out] supportedOperationalStates supported operational states
 * @return AJ_OK on success
 */
AJ_Status Cdm_CycleControlInterfaceGetSupportedOperationalStates(const char* objPath, uint8_t* supportedOperationalStates);

/**
 * Set SupportedOperationalStates of CycleControl interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] supportedOperationalStates supported operational states
 * @param[in] supportedOperationalStatesSize supported operational states size
 * @return AJ_OK on success
 */
AJ_Status Cdm_CycleControlInterfaceSetSupportedOperationalStates(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t* supportedOperationalStates, const size_t supportedOperationalStatesSize);

/**
 * Get SupportedOperationalCommands of CycleControl interface
 * @param[in] objPath the object path including the interface
 * @param[out] supportedOperationalCommands supported operational commands
 * @return AJ_OK on success
 */
AJ_Status Cdm_CycleControlInterfaceGetSupportedOperationalCommands(const char* objPath, uint8_t* supportedOperationalCommands);

/**
 * Set SupportedOperationalCommands of CycleControl interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] supportedOperationalCommands supported operational commands
 * @param[in] supportedOperationalCommandsSize supported operational commands size
 * @return AJ_OK on success
 */
AJ_Status Cdm_CycleControlInterfaceSetSupportedOperationalCommands(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t* supportedOperationalCommands, const size_t supportedOperationalCommandsSize);

#endif /* CYCLECONTROL_H_ */