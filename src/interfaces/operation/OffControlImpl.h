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

#ifndef OFFCONTROLIMPL_H_
#define OFFCONTROLIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescOperationOffControl[4];

AJ_Status CreateOffControlInterface(void** properties);
void DestroyOffControlInterface(void* properties);
AJ_Status OffControlInterfaceOnMethodHandler(AJ_Message* msg, const char* objPath, uint8_t memberIndex, void* listener, CdmPropertiesChangedByMethod* propChangedByMethod);

#endif /* OFFCONTROLIMPL_H_ */