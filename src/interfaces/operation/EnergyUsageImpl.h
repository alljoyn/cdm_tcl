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

#ifndef ENERGYUSAGEIMPL_H_
#define ENERGYUSAGEIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescOperationEnergyUsage[7];

AJ_Status CreateEnergyUsageInterface(void** properties);
void DestroyEnergyUsageInterface(void* properties);
AJ_Status EnergyUsageInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status EnergyUsageInterfaceOnMethodHandler(AJ_Message* msg, const char* objPath, uint8_t memberIndex, void* listener, CdmPropertiesChangedByMethod* propChangedByMethod);
AJ_Status EnergyUsageInterfaceEmitPropertiesChanged(AJ_BusAttachment* busAttachment, const char* objPath, void* properties, uint8_t memberIndex);

#endif /* ENERGYUSAGEIMPL_H_ */