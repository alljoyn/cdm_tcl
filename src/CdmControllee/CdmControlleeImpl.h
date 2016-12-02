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

#ifndef CDMCONTROLLEEIMPL_H_
#define CDMCONTROLLEEIMPL_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

typedef struct cdmIntfInfo {
    CdmInterfaceTypes intfType;
    void* properties;
    void* listener;
    struct cdmIntfInfo* intfNext;
} CdmInterfaceInfo;

typedef struct cdmObjInfo {
    const char* path;
    CdmInterfaceInfo* intfFirst;
    CdmInterfaceInfo* intfLast;
    AJ_InterfaceDescription* ajIntfDesc;
    struct cdmObjInfo* objNext;
} CdmObjectInfo;

typedef struct {
    CdmInterfaceTypes intfType;
    void* properties;
    uint8_t member_index;
    bool changed;
} CdmPropertiesChanged;

typedef struct vendorDefinedIntfInfo {
    const char* intfName;
    CdmInterfaceTypes intfType;
    const char* const* intfDesc;
    VendorDefinedInterfaceHandler* handler;
    struct vendorDefinedIntfInfo* intfNext;
} VendorDefinedInterfaceInfo;

typedef AJ_Status (*InterfaceCreator)(void** properties);
typedef void (*InterfaceDestructor)(void* properties);
typedef AJ_Status (*OnGetProperty)(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
typedef AJ_Status (*OnSetProperty)(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener, bool* propChanged);
typedef AJ_Status (*EmitPropertiesChanged)(AJ_BusAttachment* busAttachment, const char* objPath, void* properties, uint8_t memberIndex);
typedef AJ_Status (*OnMethodHandler)(AJ_Message* msg, const char* objPath, uint8_t memberIndex, void* listener, CdmPropertiesChangedByMethod* propChangedByMethod);

#endif /* CDMCONTROLLEEIMPL_H_ */