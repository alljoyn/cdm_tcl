/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright (c) Open Connectivity Foundation and Contributors to AllSeen
 *    Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for
 *    any purpose with or without fee is hereby granted, provided that the
 *    above copyright notice and this permission notice appear in all
 *    copies.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *     WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *     WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 *     AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 *     DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 *     PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 *     TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 *     PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <string.h>
#include <ajtcl/cdm/interfaces/operation/OvenCyclePhase.h>
#include "../../CdmControllee/CdmControlleeImpl.h"
#include "OvenCyclePhaseImpl.h"

#define INTERFACE_VERSION 1

const char* const intfDescOperationOvenCyclePhase[6] = {
    "$org.alljoyn.SmartSpaces.Operation.OvenCyclePhase",
    "@Version>q",
    "@CyclePhase>y",
    "@SupportedCyclePhases>ay",
    "?GetVendorPhasesDescription languageTag<s phasesDescription>a(yss)",
    NULL
};

typedef struct {
    uint16_t version;
    uint8_t cyclePhase;
    uint8_t* supportedCyclePhases;
} OvenCyclePhaseProperties;

static size_t supportedCyclePhasesSize = 0;

AJ_Status OvenCyclePhaseValidationCheck(const char* objPath, uint8_t cyclePhase)
{
    AJ_Status status = AJ_OK;
    OvenCyclePhaseProperties* props = NULL;
    props = (OvenCyclePhaseProperties*)GetProperties(objPath, OVEN_CYCLE_PHASE_INTERFACE);

    if (props) {
        int i = 0;
        bool check = false;
        for (i = 0; i < supportedCyclePhasesSize; i++) {
            if (props->supportedCyclePhases[i] == cyclePhase) {
                check = true;
                break;
            }
        }

        if (!check) {
            return AJ_ERR_RANGE;
        }
    } else {
        status = AJ_ERR_NO_MATCH;
    }

    return status;
}

AJ_Status CreateOvenCyclePhaseInterface(void** properties)
{
    *properties = malloc(sizeof(OvenCyclePhaseProperties));
    if (!(*properties)) {
        return AJ_ERR_RESOURCES;
    }
    memset(*properties, 0, sizeof(OvenCyclePhaseProperties));

    ((OvenCyclePhaseProperties*)*properties)->version = (uint16_t)INTERFACE_VERSION;
    ((OvenCyclePhaseProperties*)*properties)->supportedCyclePhases = NULL;

    return AJ_OK;
}

void DestroyOvenCyclePhaseInterface(void* properties)
{
    if (properties) {
        OvenCyclePhaseProperties* props = (OvenCyclePhaseProperties*)properties;
        if (props->supportedCyclePhases) {
            free(props->supportedCyclePhases);
        }
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
        AJ_MarshalArgs(&msg, "s", intfDescOperationOvenCyclePhase[0]+1); //To remove '$'
        AJ_MarshalContainer(&msg, &array, AJ_ARG_ARRAY);
        AJ_MarshalContainer(&msg, &strc, AJ_ARG_DICT_ENTRY);
        if (!strcmp(signature, "y")) {
            AJ_MarshalArgs(&msg, "sv", propName, signature, *(uint8_t*)val);
        } else if (!strcmp(signature, "ay")) {
            AJ_MarshalArgs(&msg, "sv", propName, signature, (uint8_t*)val, sizeof(uint8_t) * supportedCyclePhasesSize);

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

AJ_Status OvenCyclePhaseInterfaceOnGetProperty(AJ_Message* replyMsg, const char* objPath, void* properties, uint8_t memberIndex, void* listener)
{
    AJ_Status status = AJ_OK;
    OvenCyclePhaseProperties* props = NULL;
    OvenCyclePhaseListener* lt = NULL;

    if (!properties) {
        return AJ_ERR_INVALID;
    }

    if (listener) {
        lt = (OvenCyclePhaseListener*)listener;
    }
    props = (OvenCyclePhaseProperties*)properties;

    switch (memberIndex) {
    case 0 :
        status = AJ_MarshalArgs(replyMsg, "q", props->version);
        break;
    case 1 :
        {
            uint8_t cyclePhase;
            if (lt && lt->OnGetCyclePhase) {
                status = lt->OnGetCyclePhase(objPath, &cyclePhase);
                if (status == AJ_OK) {
                    props->cyclePhase = cyclePhase;
                }
            }
            status = AJ_MarshalArgs(replyMsg, "y", props->cyclePhase);
        }
        break;
    case 2 :
        {
            uint8_t* supportedCyclePhases = (uint8_t*)malloc(sizeof(uint8_t) * supportedCyclePhasesSize);

            if (lt && lt->OnGetSupportedCyclePhases) {
                status = lt->OnGetSupportedCyclePhases(objPath, supportedCyclePhases);
                if (status == AJ_OK) {
                    if (props->supportedCyclePhases) {
                        free(props->supportedCyclePhases);
                    }
                    props->supportedCyclePhases = (uint8_t*)malloc(sizeof(uint8_t) * supportedCyclePhasesSize);
                    memcpy(props->supportedCyclePhases, supportedCyclePhases, sizeof(uint8_t) * supportedCyclePhasesSize);
                }
            }
            if (!props->supportedCyclePhases) {
                free(supportedCyclePhases);
                return AJ_ERR_NULL;
            }
            status = AJ_MarshalArgs(replyMsg, "ay", props->supportedCyclePhases, sizeof(uint8_t) * supportedCyclePhasesSize);
        }
        break;
    default:
        status = AJ_ERR_INVALID;
    }

    return status;
}

AJ_Status OvenCyclePhaseInterfaceOnMethodHandler(AJ_Message* msg, const char* objPath, uint8_t memberIndex, void* listener, CdmPropertiesChangedByMethod* propChangedByMethod)
{
    AJ_Status status = AJ_OK;

    if (!listener) {
        return AJ_ERR_INVALID;
    }

    if (!propChangedByMethod) {
        return AJ_ERR_INVALID;
    }

    OvenCyclePhaseListener* lt = (OvenCyclePhaseListener*)listener;

    switch (memberIndex) {
    case 3 :
        if (!lt->OnGetVendorPhasesDescription) {
            status = AJ_ERR_NULL;
        } else {
            char* languageTag;
            OvenCyclePhaseCyclePhaseDescriptor* phasesDescription = NULL;
            uint16_t numReturnedRecords = 0;

            status = AJ_UnmarshalArgs(msg, "s", &languageTag);

            if (status == AJ_OK) {
                ErrorCode errorCode = NOT_ERROR;
                AJ_Message reply;
                status = lt->OnGetVendorPhasesDescription(objPath, languageTag, &phasesDescription, &numReturnedRecords, &errorCode);

                if (status == AJ_OK) {
                    AJ_Arg array, strc;
                    int i = 0;

                    AJ_MarshalReplyMsg(msg, &reply);
                    AJ_MarshalContainer(&reply, &array, AJ_ARG_ARRAY);
                    for (i=0; i<numReturnedRecords; i++) {
                        AJ_MarshalContainer(&reply, &strc, AJ_ARG_STRUCT);
                        AJ_MarshalArgs(&reply, "yss", ((phasesDescription+i)->phase), ((phasesDescription+i)->name), ((phasesDescription+i)->description));
                        AJ_MarshalCloseContainer(&reply, &strc);
                    }
                    AJ_MarshalCloseContainer(&reply, &array);
                } else {
                    AJ_MarshalReplyMsg(msg, &reply);
                    AJ_MarshalErrorMsgWithInfo(msg, &reply, GetInterfaceErrorName(errorCode), GetInterfaceErrorMessage(errorCode));
                }
                status = AJ_DeliverMsg(&reply);
            }
        }
        break;
    default:
        status = AJ_ERR_INVALID;
    }

    return status;
}

AJ_Status Cdm_OvenCyclePhaseInterfaceGetCyclePhase(const char* objPath, uint8_t* cyclePhase)
{
    AJ_Status status = AJ_OK;
    OvenCyclePhaseProperties* props = NULL;

    if (!cyclePhase) {
        return AJ_ERR_INVALID;
    }

    props = (OvenCyclePhaseProperties*)GetProperties(objPath, OVEN_CYCLE_PHASE_INTERFACE);
    if (props) {
        *cyclePhase = props->cyclePhase;
    } else {
        status = AJ_ERR_NO_MATCH;
    }

    return status;
}

AJ_Status Cdm_OvenCyclePhaseInterfaceSetCyclePhase(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t cyclePhase)
{
    AJ_Status status = AJ_OK;
    OvenCyclePhaseProperties* props = NULL;

    if (!busAttachment) {
        return AJ_ERR_INVALID;
    }

    status = OvenCyclePhaseValidationCheck(objPath, cyclePhase);

    if (status != AJ_OK) {
        return status;
    }

    props = (OvenCyclePhaseProperties*)GetProperties(objPath, OVEN_CYCLE_PHASE_INTERFACE);
    if (props) {
         if (props->cyclePhase != cyclePhase) {
            props->cyclePhase = cyclePhase;

            status = EmitPropChanged(busAttachment, objPath, "CyclePhase", "y", &(props->cyclePhase));
        }
    } else {
        status = AJ_ERR_NO_MATCH;
    }

    return status;
}

AJ_Status Cdm_OvenCyclePhaseInterfaceGetSupportedCyclePhases(const char* objPath, uint8_t* supportedCyclePhases)
{
    AJ_Status status = AJ_OK;
    OvenCyclePhaseProperties* props = NULL;

    if (!supportedCyclePhases) {
        return AJ_ERR_INVALID;
    }

    props = (OvenCyclePhaseProperties*)GetProperties(objPath, OVEN_CYCLE_PHASE_INTERFACE);

    if (props) {
        if (!props->supportedCyclePhases) {
            return AJ_ERR_NULL;
        }
        memcpy(supportedCyclePhases, props->supportedCyclePhases, sizeof(uint8_t) * supportedCyclePhasesSize);

    } else {
        status = AJ_ERR_NO_MATCH;
    }

    return status;
}

AJ_Status Cdm_OvenCyclePhaseInterfaceSetSupportedCyclePhases(AJ_BusAttachment* busAttachment, const char* objPath, const uint8_t* supportedCyclePhases, const size_t supportedCyclePhasesListSize)
{
    AJ_Status status = AJ_OK;
    OvenCyclePhaseProperties* props = NULL;

    if (!busAttachment) {
        return AJ_ERR_INVALID;
    }

    if (!supportedCyclePhases) {
        return AJ_ERR_INVALID;
    }

    props = (OvenCyclePhaseProperties*)GetProperties(objPath, OVEN_CYCLE_PHASE_INTERFACE);
    if (props) {
        if (props->supportedCyclePhases) {
            free(props->supportedCyclePhases);
        }

        supportedCyclePhasesSize = supportedCyclePhasesListSize;

        props->supportedCyclePhases = (uint8_t*)malloc(sizeof(uint8_t) * supportedCyclePhasesSize);

        memcpy(props->supportedCyclePhases, supportedCyclePhases, sizeof(uint8_t) * supportedCyclePhasesSize);

        status = EmitPropChanged(busAttachment, objPath, "SupportedCyclePhases", "ay", props->supportedCyclePhases);
    } else {
        status = AJ_ERR_NO_MATCH;
    }

    return status;
}