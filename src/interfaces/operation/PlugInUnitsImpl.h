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

#ifndef PLUGINUNITSIMPL_H_
#define PLUGINUNITSIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescOperationPlugInUnits[4];

AJ_Status CreatePlugInUnitsInterface(void** properties);
void DestroyPlugInUnitsInterface(void* properties);
AJ_Status PlugInUnitsInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
#endif /* PLUGINUNITSIMPL_H_ */