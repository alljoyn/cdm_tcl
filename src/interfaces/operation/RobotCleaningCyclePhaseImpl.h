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

#ifndef ROBOTCLEANINGCYCLEPHASEIMPL_H_
#define ROBOTCLEANINGCYCLEPHASEIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescOperationRobotCleaningCyclePhase[6];

AJ_Status CreateRobotCleaningCyclePhaseInterface(void** properties);
void DestroyRobotCleaningCyclePhaseInterface(void* properties);
AJ_Status RobotCleaningCyclePhaseInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status RobotCleaningCyclePhaseInterfaceOnMethodHandler(AJ_Message* msg, const char* objPath, uint8_t memberIndex, void* listener, CdmPropertiesChangedByMethod* propChangedByMethod);

#endif /* ROBOTCLEANINGCYCLEPHASEIMPL_H_ */