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

#ifndef WINDDIRECTIONIMPL_H_
#define WINDDIRECTIONIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescEnvironmentWindDirection[9];

AJ_Status CreateWindDirectionInterface(void** properties);
void DestroyWindDirectionInterface(void* properties);
AJ_Status WindDirectionInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status WindDirectionInterfaceOnSetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener, bool* propChanged);
AJ_Status WindDirectionInterfaceEmitPropertiesChanged(AJ_BusAttachment* busAttachment, const char* objPath, void* properties, uint8_t memberIndex);

#endif // WINDDIRECTIONIMPL_H_