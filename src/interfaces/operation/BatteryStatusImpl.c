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

#include <ajtcl/cdm/interfaces/operation/BatteryStatus.h>
#include "../../CdmControllee/CdmControlleeImpl.h"
#include "BatteryStatusImpl.h"

#define INTERFACE_VERSION 1

const char* const intfDescOperationBatteryStatus[] = {
    "$org.alljoyn.SmartSpaces.Operation.BatteryStatus",
    "@Version>q",
    "@CurrentValue>y",
    "@IsCharging>b",
    NULL
};

typedef struct {
    uint16_t version;
    uint8_t currentValue;
    bool isCharging;
} BatteryStatusProperties;

AJ_Status CreateBatteryStatusInterface(void** properties)
{
    *properties = malloc(sizeof(BatteryStatusProperties));
    if (!(*properties)) {
        return AJ_ERR_RESOURCES;
    }
    memset(*properties, 0, sizeof(BatteryStatusProperties));

    ((BatteryStatusProperties*)*properties)->version = (uint16_t)INTERFACE_VERSION;

    return AJ_OK;
}

void DestroyBatteryStatusInterface(void* properties)
{
    if (properties) {
    	BatteryStatusProperties* props = (BatteryStatusProperties*)properties;

        free(props);
    }
}

static AJ_Status EmitPropChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* propName, const char* signature, void* val)
{
    AJ_Status status = AJ_OK;
    uint32_t msgId = 0;
    AJ_Message msg;
    AJ_Arg array, strc;

    if (!busAttachment) {
        return AJ_ERR_INVALID;
    }

    status = MakePropChangedId(objPath, &msgId);
    if (status == AJ_OK) {
        AJ_MarshalSignal(busAttachment, &msg, msgId, NULL, 0, AJ_FLAG_GLOBAL_BROADCAST, 0);
        AJ_MarshalArgs(&msg, "s", intfDescOperationBatteryStatus[0]+1); //To remove '$'
        AJ_MarshalContainer(&msg, &array, AJ_ARG_ARRAY);
        AJ_MarshalContainer(&msg, &strc, AJ_ARG_DICT_ENTRY);
        if (!strcmp(signature, "y")) {
            AJ_MarshalArgs(&msg, "sv", propName, signature, *(uint8_t*)val);
        } else  if (!strcmp(signature, "b")) {
            AJ_MarshalArgs(&msg, "sv", propName, signature, *(bool*)val);
        } else {
            return AJ_ERR_SIGNATURE;
        }
        AJ_MarshalCloseContainer(&msg, &strc);
        AJ_MarshalCloseContainer(&msg, &array);
        AJ_MarshalContainer(&msg, &array, AJ_ARG_ARRAY);
        AJ_MarshalCloseContainer(&msg, &array);
        status = AJ_DeliverMsg(&msg);
    }

    return status;
}

AJ_Status BatteryStatusInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener)
{
    AJ_Status status = AJ_OK;
    BatteryStatusProperties* props = NULL;
    BatteryStatusListener* lt = NULL;

    if (!properties) {
        return AJ_ERR_INVALID;
    }

    if (listener) {
        lt = (BatteryStatusListener*)listener;
    }
    props = (BatteryStatusProperties*)properties;

    switch (memberIndex) {
    case 0 :
        status = AJ_MarshalArgs(replyMsg, "q", props->version);
        break;
    case 1 :
        {
            uint8_t currentValue;
            if (lt && lt->OnGetCurrentValue) {
                status = lt->OnGetCurrentValue(objPath, &currentValue);
                if (status == AJ_OK) {
                    props->currentValue = currentValue;
                }
            }
            status = AJ_MarshalArgs(replyMsg, "y", props->currentValue);
        }
        break;
    case 2 :
        {
            bool isCharging;
            if (lt && lt->OnGetIsCharging) {
                status = lt->OnGetIsCharging(objPath, &isCharging);
                if (status == AJ_OK) {
                    props->isCharging = isCharging;
                }
            }
            status = AJ_MarshalArgs(replyMsg, "b", props->isCharging);
        }
        break;
    default:
        status = AJ_ERR_INVALID;
    }

    return status;
}

AJ_Status Cdm_BatteryStatusInterfaceGetCurrentValue(const char* objPath, uint8_t* currentValue)
{
    AJ_Status status = AJ_OK;
    BatteryStatusProperties* props = NULL;

    if (!currentValue) {
        return AJ_ERR_INVALID;
    }

    props = (BatteryStatusProperties*)GetProperties(objPath, BATTERY_STATUS_INTERFACE);
    if (props) {
        *currentValue = props->currentValue;
    } else {
        status = AJ_ERR_NO_MATCH;
    }

    return status;
}

AJ_Status Cdm_BatteryStatusInterfaceSetCurrentValue(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t currentValue)
{
    AJ_Status status = AJ_OK;
    BatteryStatusProperties* props = NULL;

    if (!busAttachment) {
        return AJ_ERR_INVALID;
    }

    if (currentValue > 100) {
        return AJ_ERR_RANGE;
    }

    props = (BatteryStatusProperties*)GetProperties(objPath, BATTERY_STATUS_INTERFACE);
    if (props) {
        if (props->currentValue != currentValue) {
            props->currentValue = currentValue;
            status = EmitPropChanged(busAttachment, objPath, "CurrentValue", "y", &(props->currentValue));
        }
    } else {
        status = AJ_ERR_NO_MATCH;
    }

    return status;
}

AJ_Status Cdm_BatteryStatusInterfaceGetIsCharging(const char* objPath, bool* isCharging)
{
    AJ_Status status = AJ_OK;
    BatteryStatusProperties* props = NULL;

    if (!isCharging) {
        return AJ_ERR_INVALID;
    }

    props = (BatteryStatusProperties*)GetProperties(objPath, BATTERY_STATUS_INTERFACE);
    if (props) {
        *isCharging = props->isCharging;
    } else {
        status = AJ_ERR_NO_MATCH;
    }

    return status;
}

AJ_Status Cdm_BatteryStatusInterfaceSetIsCharging(AJ_BusAttachment* busAttachment, const char* objPath, const bool isCharging)
{
    AJ_Status status = AJ_OK;
    BatteryStatusProperties* props = NULL;

    if (!busAttachment) {
        return AJ_ERR_INVALID;
    }

    props = (BatteryStatusProperties*)GetProperties(objPath, BATTERY_STATUS_INTERFACE);
    if (props) {
        if (props->isCharging != isCharging) {
            props->isCharging = isCharging;
            status = EmitPropChanged(busAttachment, objPath, "IsCharging", "b", &(props->isCharging));
        }
    } else {
        status = AJ_ERR_NO_MATCH;
    }

    return status;
}