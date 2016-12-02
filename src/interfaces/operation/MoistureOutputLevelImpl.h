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

#ifndef MOISTUREOUTPUTLEVELIMPL_H_
#define MOISTUREOUTPUTLEVELIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescOperationMoistureOutputLevel[6];

AJ_Status CreateMoistureOutputLevelInterface(void** properties);
void DestroyMoistureOutputLevelInterface(void* properties);
AJ_Status MoistureOutputLevelInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status MoistureOutputLevelInterfaceOnSetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener, bool* propChanged);
AJ_Status MoistureOutputLevelInterfaceEmitPropertiesChanged(AJ_BusAttachment* busAttachment, const char* objPath, void* properties, uint8_t memberIndex);

#endif /* MOISTUREOUTPUTLEVELIMPL_H_ */