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

#ifndef DISHWASHINGCYCLEPHASEIMPL_H_
#define DISHWASHINGCYCLEPHASEIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescOperationDishWashingCyclePhase[6];

AJ_Status CreateDishWashingCyclePhaseInterface(void** properties);
void DestroyDishWashingCyclePhaseInterface(void* properties);
AJ_Status DishWashingCyclePhaseInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status DishWashingCyclePhaseInterfaceOnMethodHandler(AJ_Message* msg, const char* objPath, uint8_t memberIndex, void* listener, CdmPropertiesChangedByMethod* propChangedByMethod);

#endif /* DISHWASHINGCYCLEPHASEIMPL_H_ */