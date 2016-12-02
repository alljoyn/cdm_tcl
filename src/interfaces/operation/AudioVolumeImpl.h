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

#ifndef AUDIOVOLUMEIMPL_H_
#define AUDIOVOLUMEIMPL_H_

#include <ajtcl/alljoyn.h>

const char* const intfDescOperationAudioVolume[6];

AJ_Status CreateAudioVolumeInterface(void** properties);
void DestroyAudioVolumeInterface(void* properties);
AJ_Status AudioVolumeInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status AudioVolumeInterfaceOnSetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener, bool* propChanged);
AJ_Status AudioVolumeInterfaceEmitPropertiesChanged(AJ_BusAttachment* busAttachment, const char* objPath, void* properties, uint8_t memberIndex);

#endif // AUDIOVOLUMEIMPL_H_