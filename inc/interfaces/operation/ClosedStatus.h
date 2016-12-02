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

#ifndef CLOSEDSTATUS_H_
#define CLOSEDSTATUS_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * ClosedStatus interface listener
 */
typedef struct {
    /**
     * Handler for getting IsClosed property
     * @param[in] objPath object path
     * @param[out] isClosed isClosed
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetIsClosed) (const char* objPath, bool* isClosed);

} ClosedStatusListener;

/**
 * Get isClosed of ClosedStatus interface
 * @param[in] objPath the object path including the interface
 * @param[out] isClosed isClosed
 * @return AJ_OK on success
 */
AJ_Status Cdm_ClosedStatusInterfaceGetIsClosed(const char* objPath, bool* isClosed);

/**
 * Set isClosed of ClosedStatus interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] isClosed isClosed
 * @return AJ_OK on success
 */
AJ_Status Cdm_ClosedStatusInterfaceSetIsClosed(AJ_BusAttachment* busAttachment, const char* objPath, const bool isClosed);

#endif /* CLOSEDSTATUS_H_ */