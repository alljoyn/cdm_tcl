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

#ifndef TARGETHUMIDITYIMPL_H_
#define TARGETHUMIDITYIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescEnvironmentTargetHumidity[8];

AJ_Status CreateTargetHumidityInterface(void** properties);
void DestroyTargetHumidityInterface(void* properties);
AJ_Status TargetHumidityInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status TargetHumidityInterfaceOnSetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener, bool* propChanged);
AJ_Status TargetHumidityInterfaceEmitPropertiesChanged(AJ_BusAttachment* busAttachment, const char* objPath, void* properties, uint8_t memberIndex);

#endif // TARGETHUMIDITYIMPL_H_