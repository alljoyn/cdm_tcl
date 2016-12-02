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

#ifndef CURRENTAIRQUALITYLEVELIMPL_H_
#define CURRENTAIRQUALITYLEVELIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescEnvironmentCurrentAirQualityLevel[6];

AJ_Status CreateCurrentAirQualityLevelInterface(void** properties);
void DestroyCurrentAirQualityLevelInterface(void* properties);
AJ_Status CurrentAirQualityLevelInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);

#endif // CURRENTAIRQUALITYLEVELIMPL_H_