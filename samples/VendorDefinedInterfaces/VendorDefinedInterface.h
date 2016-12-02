/**
 * @file
 */
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

#ifndef VENDORDEFINEDINTERFACE_H_
#define VENDORDEFINEDINTERFACE_H_

#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

#define VENDOR_DEFINED_INTERFACE_NAME "com.foo.bar.test"

const char* const intfDescVendorDefined[6];

/**
 * VendorDefined interface listener
 */
typedef struct {
    /**
     * Handler for getting TestProperty property
     * @param[in] objPath object path
     * @param[out] testProperty testProperty
     * @return AJ_OK on success
     */
    AJ_Status (*OnGetTestProperty) (const char* objPath, int32_t* testProperty);

    /**
     * Handler for setting TestProperty property
     * @param[in] objPath object path
     * @param[in] testProperty testProperty
     * @return AJ_OK on success
     */
    AJ_Status (*OnSetTestProperty) (const char* objPath, int32_t* testProperty);

    /**
     * Handler for TestMethod method
     * @param[in] objPath object path
     * @return AJ_OK on success
     */
    AJ_Status (*OnTestMethod) (const char* objPath, int32_t arg1);
} VendorDefinedListener;

void VendorDefinedInterfaceRegistered(CdmInterfaceTypes intfType);
AJ_Status CreateVendorDefinedInterface(void** properties);
void DestroyVendorDefinedInterface(void* properties);
AJ_Status VendorDefinedInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener);
AJ_Status VendorDefinedInterfaceOnSetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener, bool* propChanged);
AJ_Status VendorDefinedInterfaceEmitPropertiesChanged(AJ_BusAttachment* busAttachment, const char* objPath, void* properties, uint8_t memberIndex);
AJ_Status VendorDefinedInterfaceOnMethodHandler(AJ_Message* msg, const char* objPath, uint8_t memberIndex, void* listener, CdmPropertiesChangedByMethod* propChangedByMethod);

/**
 * Get TestProperty of VendorDefined interface
 * @param[in] objPath the object path including the interface
 * @param[out] testProperty testProperty
 * @return AJ_OK on success
 */
AJ_Status Cdm_VendorDefinedInterfaceGetTestProperty(const char* objPath, int32_t* testProperty);

/**
 * Set TestProperty of VendorDefined interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] testProperty testProperty
 * @return AJ_OK on success
 */
AJ_Status Cdm_VendorDefinedInterfaceSetTestProperty(AJ_BusAttachment* busAttachment, const char* objPath, int32_t testProperty);

/**
 * Emit TestSignal signal of VendorDefined interface
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path including the interface
 * @param[in] sessionId session id
 * @return AJ_OK on success
 */
AJ_Status Cdm_VendorDefinedInterfaceEmitTestSignal(AJ_BusAttachment* busAttachment, const char* objPath, uint32_t sessionId);

#endif /* VENDORDEFINEDINTERFACE_H_ */