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

#include <ajtcl/cdm/interfaces/CdmInterfaceErrors.h>

const char* errorName[] = {
    "", //Not Error
    "org.alljoyn.Error.InvalidValue",
    "org.alljoyn.Error.FeatureNotAvailable",
    "org.alljoyn.Error.LanguageNotSupported",
    "org.alljoyn.SmartSpaces.Error.NotAcceptableDueToInternalState",
    "org.alljoyn.SmartSpaces.Error.RemoteControlDisabled",
};

const char* errorMessage[] = {
    "", //Not Error
    "Invalid value.",
    "Feature not available.",
    "The language specified is not supported.",
    "The value is not acceptable due to internal state.",
    "Remote control disabled.",
};

const char* GetInterfaceErrorName(ErrorCode errorCode)
{
    if (errorCode > MAX_ERROR_CODE) {
        return "";
    }

    return errorName[errorCode];
}

const char* GetInterfaceErrorMessage(ErrorCode errorCode)
{
    if (errorCode > MAX_ERROR_CODE) {
        return "";
    }

    return errorMessage[errorCode];
}