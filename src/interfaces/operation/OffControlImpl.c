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

#include <string.h>
#include <ajtcl/cdm/interfaces/operation/OffControl.h>
#include "../../CdmControllee/CdmControlleeImpl.h"
#include "OffControlImpl.h"

#define INTERFACE_VERSION 1

const char* const intfDescOperationOffControl[] = {
    "$org.alljoyn.SmartSpaces.Operation.OffControl",
    "@Version>q",
    "?SwitchOff",
    NULL
};

typedef struct {
    uint16_t version;
} OffControlProperties;

AJ_Status CreateOffControlInterface(void** properties)
{
    *properties = malloc(sizeof(OffControlProperties));
    if (!(*properties)) {
        return AJ_ERR_RESOURCES;
    }
    memset(*properties, 0, sizeof(OffControlProperties));

    ((OffControlProperties*)*properties)->version = (uint16_t)INTERFACE_VERSION;

    return AJ_OK;
}

void DestroyOffControlInterface(void* properties)
{
    if (properties) {
        OffControlProperties* props = (OffControlProperties*)properties;

        free(props);
    }
}

AJ_Status OffControlInterfaceOnMethodHandler(AJ_Message* msg, const char* objPath, uint8_t memberIndex, void* listener, CdmPropertiesChangedByMethod* propChangedByMethod)
{
    AJ_Status status = AJ_OK;

    if (!listener) {
        return AJ_ERR_INVALID;
    }

    if (!propChangedByMethod) {
        return AJ_ERR_INVALID;
    }

    OffControlListener* lt = (OffControlListener*)listener;

    switch (memberIndex) {
    case 1 :
        if (!lt->OnSwitchOff) {
            status = AJ_ERR_NULL;
        } else {
            ErrorCode errorCode = NOT_ERROR;
            AJ_Message reply;
            status = lt->OnSwitchOff(objPath, &errorCode);

            AJ_MarshalReplyMsg(msg, &reply);
            if (status != AJ_OK) {
                AJ_MarshalErrorMsgWithInfo(msg, &reply, GetInterfaceErrorName(errorCode), GetInterfaceErrorMessage(errorCode));
            }
            status = AJ_DeliverMsg(&reply);
        }
        break;
    default:
        status = AJ_ERR_INVALID;
    }

    return status;
}