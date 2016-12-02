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

#ifndef ALERTS_H_
#define ALERTS_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceErrors.h>

/**
 * AlertRecord struct
 */
typedef struct {
    uint8_t severity;
    uint16_t alertCode;
    bool needAcknowledgement;
} AlertRecord;

/**
 * AlertCodesDescriptor struct
 */
typedef struct {
    uint16_t alertCode;
    char* description;
} AlertCodesDescriptor;

/**
 * Alerts interface listener
 */
typedef struct {
    /**
     * Handler for getting Alerts property
     * @param[in] objPath object path
     * @param[out] alerts List of current pending alerts
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetAlerts) (const char* objPath, AlertRecord* alerts);
    /**
     * Handler for GetAlertCodesDescription method
     * @param[in] objPath object path
     * @param[in] languageTag Language to be used in the output strings
     * @param[out] description Alert codes description
     * @param[out] alertsNumber Alerts number
     * @param[out] errorCode error code
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetAlertCodesDescription) (const char* objPath, const char* languageTag,
        AlertCodesDescriptor** description, size_t* alertsNumber, ErrorCode* errorCode);

    /**
     * Handler for AcknowledgeAlert method
     * @param[in] objPath object path
     * @param[in] alertCode Alert code of the alert to be acknowledged
     * @param[out] errorCode error code
     * @return AJ_OK on success
     */
    AJ_Status (*OnAcknowledgeAlert) (const char* objPath, const uint16_t alertCode, ErrorCode* errorCode);

    /**
     * Handler for AcknowledgeAllAlerts method
     * @param[in] objPath object path
     * @param[out] errorCode error code
     * @return AJ_OK on success
     */
    AJ_Status (*OnAcknowledgeAllAlerts) (const char* objPath, ErrorCode* errorCode);

} AlertsListener;


/**
 * Get Alerts of Alerts interface
 * @param[in] objPath the object path including the interface
 * @param[out] alerts List of current pending alerts
 * @return AJ_OK on success
 */
AJ_Status Cdm_AlertsInterfaceGetAlerts(const char* objPath, AlertRecord* alerts);

/**
 * Set Alerts of Alerts interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] alerts List of current pending alerts
 * @param[in] alertsNumber Alerts number
 * @return AJ_OK on success
 */
AJ_Status Cdm_AlertsInterfaceSetAlerts(AJ_BusAttachment* busAttachment, const char* objPath,
    const AlertRecord* alerts, const size_t alertsNumber);


#endif /* ALERTS_H_ */