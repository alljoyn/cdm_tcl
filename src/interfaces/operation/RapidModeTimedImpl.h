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

#ifndef RAPIDMODETIMEDIMPL_H_
#define RAPIDMODETIMEDIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescOperationRapidModeTimed[5];

AJ_Status CreateRapidModeTimedInterface(void** properties);
void DestroyRapidModeTimedInterface(void* properties);
AJ_Status RapidModeTimedInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status RapidModeTimedInterfaceOnSetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener, bool* propChanged);
AJ_Status RapidModeTimedInterfaceEmitPropertiesChanged(AJ_BusAttachment* busAttachment, const char* objPath, void* properties, uint8_t memberIndex);

#endif /* RAPIDMODETIMEDIMPL_H_ */