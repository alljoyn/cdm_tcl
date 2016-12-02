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

#ifndef ONOFFSTATUSLIMPL_H_
#define ONOFFSTATUSLIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescOperationOnOffStatus[4];

AJ_Status CreateOnOffStatusInterface(void** properties);
void DestroyOnOffStatusInterface(void* properties);
AJ_Status OnOffStatusInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);

#endif /* ONOFFSTATUSLIMPL_H_ */