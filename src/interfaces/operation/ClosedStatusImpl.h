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

#ifndef CLOSEDSTATUSIMPL_H_
#define CLOSEDSTATUSIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescOperationClosedStatus[4];

AJ_Status CreateClosedStatusInterface(void** properties);
void DestroyClosedStatusInterface(void* properties);
AJ_Status ClosedStatusInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);

#endif // CLOSEDSTATUSIMPL_H_