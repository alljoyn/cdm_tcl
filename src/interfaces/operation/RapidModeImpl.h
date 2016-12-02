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

#ifndef RAPIDMODEIMPL_H_
#define RAPIDMODEIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescOperationRapidMode[4];

AJ_Status CreateRapidModeInterface(void** properties);
void DestroyRapidModeInterface(void* properties);
AJ_Status RapidModeInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status RapidModeInterfaceOnSetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener, bool* propChanged);
AJ_Status RapidModeInterfaceEmitPropertiesChanged(AJ_BusAttachment* busAttachment, const char* objPath, void* properties, uint8_t memberIndex);

#endif /* RAPIDMODEIMPL_H_ */