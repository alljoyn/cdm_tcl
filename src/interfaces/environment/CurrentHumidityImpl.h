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

#ifndef CURRENTHUMIDITYIMPL_H_
#define CURRENTHUMIDITYIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescEnvironmentCurrentHumidity[5];

AJ_Status CreateCurrentHumidityInterface(void** properties);
void DestroyCurrentHumidityInterface(void* properties);
AJ_Status CurrentHumidityInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);

#endif // CURRENTHUMIDITYIMPL_H_