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

#ifndef CDMINTERFACEERRORS_H_
#define CDMINTERFACEERRORS_H_

/**
 * Error Code
 */
typedef enum {
    NOT_ERROR = 0,
    INVALID_VALUE,
    FEATURE_NOT_AVAILABLE,
    LANGUAGE_NOT_SUPPORTED,
    NOT_ACCEPTABLE_DUE_TO_INTERNAL_STATE,
    REMOTE_CONTROL_DISABLED,
    MAX_ERROR_CODE = REMOTE_CONTROL_DISABLED
} ErrorCode;

/**
 * Get interface error name
 * @param[in] errorCode error code
 * @return Error name
 */
const char* GetInterfaceErrorName(ErrorCode errorCode);

/**
 * Get interface error message
 * @param[in] errorCode error code
 * @return Error message
 */
const char* GetInterfaceErrorMessage(ErrorCode errorCode);

#endif /* CDMINTERFACEERRORS_H_ */