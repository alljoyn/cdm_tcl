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

#ifndef TARGETTEMPERATUREIMPL_H_
#define TARGETTEMPERATUREIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescEnvironmentTargetTemperature[7];

AJ_Status CreateTargetTemperatureInterface(void** properties);
void DestroyTargetTemperatureInterface(void* properties);
AJ_Status TargetTemperatureInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status TargetTemperatureInterfaceOnSetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener, bool* propChanged);
AJ_Status TargetTemperatureInterfaceEmitPropertiesChanged(AJ_BusAttachment* busAttachment, const char* objPath, void* properties, uint8_t memberIndex);

#endif // TARGETTEMPERATUREIMPL_H_