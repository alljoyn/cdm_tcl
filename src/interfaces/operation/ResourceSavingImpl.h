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

#ifndef RESOURCESSAVINGIMPL_H_
#define RESOURCESSAVINGIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescOperationResourceSaving[4];

AJ_Status CreateResourceSavingInterface(void** properties);
void DestroyResourceSavingInterface(void* properties);
AJ_Status ResourceSavingInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status ResourceSavingInterfaceOnSetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener, bool* propChanged);
AJ_Status ResourceSavingInterfaceEmitPropertiesChanged(AJ_BusAttachment* busAttachment, const char* objPath, void* properties, uint8_t memberIndex);

#endif /* RESOURCESSAVINGIMPL_H_ */