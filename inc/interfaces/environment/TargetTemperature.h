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

#ifndef TARGETTEMPERATURE_H_
#define TARGETTEMPERATURE_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

/**
 * TargetTemperature interface listener
 */
typedef struct {
    /**
     * Handler for getting TargetValue property
     * @param[in] objPath object path
     * @param[out] targetValue the target value
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetTargetValue) (const char* objPath, double* targetValue);

    /**
     * Handler for setting TargetLevel property
     * @param[in] objPath object path
     * @param[out] targetLevel the target value
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetTargetValue) (const char* objPath, const double targetValue);

    /**
     * Handler for getting MinValue property
     * @param[in] objPath object path
     * @param[out] minValue the minimum value
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetMinValue) (const char* objPath, double* minValue);

    /**
     * Handler for getting MaxValue property
     * @param[in] objPath object path
     * @param[out] maxValue the maximum value
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetMaxValue) (const char* objPath, double* maxValue);

    /**
     * Handler for getting StepValue property
     * @param[in] objPath object path
     * @param[out] stepValue the step value
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetStepValue) (const char* objPath, double* stepValue);

} TargetTemperatureListener;


/**
 * Get the target value of TargetTemperature interface
 * @param[in] objPath the object path including the interface
 * @param[out] targetValue the target value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceGetTargetValue(const char* objPath, double* targetValue);

/**
 * Set the target value of TargetTemperature interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] targetValue the target value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceSetTargetValue(AJ_BusAttachment* busAttachment, const char* objPath, const double targetValue);

/**
 * Get the minimum value of TargetTemperature interface
 * @param[in] objPath the object path including the interface
 * @param[out] minValue the minimum value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceGetMinValue(const char* objPath, double* minValue);

/**
 * Set the minimum value of TargetTemperature interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] minValue the minimum value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceSetMinValue(AJ_BusAttachment* busAttachment, const char* objPath, const double minValue);

/**
 * Get the maximum value of TargetTemperature interface
 * @param[in] objPath the object path including the interface
 * @param[out] maxValue the maximum value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceGetMaxValue(const char* objPath, double* maxValue);

/**
 * Set the maximum value of TargetTemperature interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] maxValue the maximum value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceSetMaxValue(AJ_BusAttachment* busAttachment, const char* objPath, const double maxValue);

/**
 * Get the step value of TargetTemperature interface
 * @param[in] objPath the object path including the interface
 * @param[out] stepValue the step value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceGetStepValue(const char* objPath, double* stepValue);

/**
 * Set the step value of TargetTemperature interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] stepValue the step value
 * @return AJ_OK on success
 */
AJ_Status Cdm_TargetTemperatureInterfaceSetStepValue(AJ_BusAttachment* busAttachment, const char* objPath, const double stepValue);

#endif /* TARGETTEMPERATURE_H_ */