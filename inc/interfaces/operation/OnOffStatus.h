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

#ifndef ONOFFSTATUS_H_
#define ONOFFSTATUS_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * OnOffStatus interface listener
 */
typedef struct {
    /**
     * Handler for getting OnOff property
     * @param[in] objPath object path
     * @param[out] isOn Current on/off state of the appliance
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetIsOn) (const char* objPath, bool* isOn);

} OnOffStatusListener;

/**
 * Get isOn of OnOffStatus interface
 * @param[in] objPath the object path including the interface
 * @param[out] isOn Current on/off state of the appliance
 * @return AJ_OK on success
 */
AJ_Status Cdm_OnOffStatusInterfaceGetIsOn(const char* objPath, bool* isOn);

/**
 * Set isOn  of OnOffStatus interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] isOn Current on/off state of the appliance
 * @return AJ_OK on success
 */
AJ_Status Cdm_OnOffStatusInterfaceSetIsOn(AJ_BusAttachment* busAttachment, const char* objPath, const bool isOn);

#endif /* ONOFFSTATUS_H_ */