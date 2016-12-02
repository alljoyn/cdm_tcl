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

#ifndef OFFCONTROL_H_
#define OFFCONTROL_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceErrors.h>

/**
 * OffControl interface listener
 */
typedef struct {
    /**
     * Handler for SwitchOff method
     * @param[in] objPath object path
     * @param[out] errorCode error code
     * @return AJ_OK on success
     */
    AJ_Status (*OnSwitchOff) (const char* objPath, ErrorCode* errorCode);

} OffControlListener;

#endif /* OFFCONTROL_H_ */