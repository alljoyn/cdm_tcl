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

#ifndef TARGETTEMPERATURELEVELIMPL_H_
#define TARGETTEMPERATURELEVELIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescEnvironmentTargetTemperatureLevel[6];

AJ_Status CreateTargetTemperatureLevelInterface(void** properties);
void DestroyTargetTemperatureLevelInterface(void* properties);
AJ_Status TargetTemperatureLevelInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status TargetTemperatureLevelInterfaceOnSetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener, bool* propChanged);
AJ_Status TargetTemperatureLevelInterfaceEmitPropertiesChanged(AJ_BusAttachment* busAttachment, const char* objPath, void* properties, uint8_t memberIndex);

#endif // TARGETTEMPERATURELEVELIMPL_H_