/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#include <stdlib.h>
#include <string.h>
#include <ajtcl/alljoyn.h>
#include <ajtcl/cdm/CdmControllee.h>

#include <ajtcl/cdm/interfaces/CdmInterfaceCommon.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceValidation.h>
#include <ajtcl/cdm/interfaces/operation/TimerInterface.h>
#include <ajtcl/cdm/interfaces/operation/TimerModel.h>

#include <ajtcl/cdm/utils/CdmArray.h>

#define INTERFACE_VERSION 1
#define INTERFACE_NAME TIMER

const char* const intfDescOperationTimer[] = {
    "$org.alljoyn.SmartSpaces.Operation.Timer",
    "@Version>q",
    "@ReferenceTimer>i",
    "@TargetTimeToStart>i",
    "@TargetTimeToStop>i",
    "@EstimatedTimeToEnd>i",
    "@RunningTime>i",
    "@TargetDuration>i",
    "?SetTargetTimeToStart targetTimeToStart<i",
    "?SetTargetTimeToStop targetTimeToStop<i",
    NULL
};




static AJ_Status Timer_GetReferenceTimer(AJ_BusAttachment* busAttachment, const char* objPath, int32_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TimerModel* model = (TimerModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetReferenceTimer) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetReferenceTimer(model, objPath, out);
}



static AJ_Status Timer_GetTargetTimeToStart(AJ_BusAttachment* busAttachment, const char* objPath, int32_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TimerModel* model = (TimerModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTargetTimeToStart) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetTargetTimeToStart(model, objPath, out);
}



AJ_Status Cdm_Timer_EmitTargetTimeToStartChanged(AJ_BusAttachment *bus, const char *objPath, int32_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "TargetTimeToStart", "i", newValue);
}



static AJ_Status Timer_GetTargetTimeToStop(AJ_BusAttachment* busAttachment, const char* objPath, int32_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TimerModel* model = (TimerModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTargetTimeToStop) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetTargetTimeToStop(model, objPath, out);
}



AJ_Status Cdm_Timer_EmitTargetTimeToStopChanged(AJ_BusAttachment *bus, const char *objPath, int32_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "TargetTimeToStop", "i", newValue);
}



static AJ_Status Timer_GetEstimatedTimeToEnd(AJ_BusAttachment* busAttachment, const char* objPath, int32_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TimerModel* model = (TimerModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetEstimatedTimeToEnd) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetEstimatedTimeToEnd(model, objPath, out);
}



static AJ_Status Timer_GetRunningTime(AJ_BusAttachment* busAttachment, const char* objPath, int32_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TimerModel* model = (TimerModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetRunningTime) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetRunningTime(model, objPath, out);
}



static AJ_Status Timer_GetTargetDuration(AJ_BusAttachment* busAttachment, const char* objPath, int32_t* out)
{
    if (!objPath || !out) {
        return AJ_ERR_INVALID;
    }

    TimerModel* model = (TimerModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->GetTargetDuration) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->GetTargetDuration(model, objPath, out);
}



AJ_Status Cdm_Timer_EmitTargetDurationChanged(AJ_BusAttachment *bus, const char *objPath, int32_t newValue)
{
    return EmitPropertyChanged(bus, objPath, INTERFACE_NAME, "TargetDuration", "i", newValue);
}



static AJ_Status Cdm_Timer_CallSetTargetTimeToStart(AJ_BusAttachment* busAttachment, const char *objPath, int32_t targetTimeToStart)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    TimerModel* model = (TimerModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->MethodSetTargetTimeToStart) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->MethodSetTargetTimeToStart(model, objPath, targetTimeToStart);
}


static AJ_Status Cdm_Timer_CallSetTargetTimeToStop(AJ_BusAttachment* busAttachment, const char *objPath, int32_t targetTimeToStop)
{
    if (!objPath) {
        return AJ_ERR_INVALID;
    }

    TimerModel* model = (TimerModel*)GetInterfaceModel(objPath, INTERFACE_NAME);
    if (!model) {
        return AJ_ERR_NO_MATCH;
    }
    if (!model->MethodSetTargetTimeToStop) {
        return AJ_ERR_NULL;
    }

    model->busAttachment = busAttachment;
    return model->MethodSetTargetTimeToStop(model, objPath, targetTimeToStop);
}



/*
   Handler functions
*/
static AJ_Status Timer_OnGetProperty(AJ_BusAttachment* busAttachment, AJ_Message* replyMsg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case TIMER_PROP_VERSION:
            status = AJ_MarshalArgs(replyMsg, "q", INTERFACE_VERSION);
            break;

        case TIMER_PROP_REFERENCE_TIMER:
        {
            int32_t reference_timer;
            memset(&reference_timer, 0, sizeof(int32_t));
            status = Timer_GetReferenceTimer(busAttachment, objPath, &reference_timer);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "i", reference_timer);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TIMER_PROP_TARGET_TIME_TO_START:
        {
            int32_t target_time_to_start;
            memset(&target_time_to_start, 0, sizeof(int32_t));
            status = Timer_GetTargetTimeToStart(busAttachment, objPath, &target_time_to_start);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "i", target_time_to_start);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TIMER_PROP_TARGET_TIME_TO_STOP:
        {
            int32_t target_time_to_stop;
            memset(&target_time_to_stop, 0, sizeof(int32_t));
            status = Timer_GetTargetTimeToStop(busAttachment, objPath, &target_time_to_stop);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "i", target_time_to_stop);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TIMER_PROP_ESTIMATED_TIME_TO_END:
        {
            int32_t estimated_time_to_end;
            memset(&estimated_time_to_end, 0, sizeof(int32_t));
            status = Timer_GetEstimatedTimeToEnd(busAttachment, objPath, &estimated_time_to_end);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "i", estimated_time_to_end);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TIMER_PROP_RUNNING_TIME:
        {
            int32_t running_time;
            memset(&running_time, 0, sizeof(int32_t));
            status = Timer_GetRunningTime(busAttachment, objPath, &running_time);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "i", running_time);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }

        case TIMER_PROP_TARGET_DURATION:
        {
            int32_t target_duration;
            memset(&target_duration, 0, sizeof(int32_t));
            status = Timer_GetTargetDuration(busAttachment, objPath, &target_duration);
            if (status == AJ_OK) {
                status = AJ_MarshalArgs(replyMsg, "i", target_duration);
                if (status == AJ_OK) {
                    status = AJ_DeliverMsg(replyMsg);
                }
                
            }
            break;
        }
    }

    return status;
}



static AJ_Status Timer_OnSetProperty(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex, bool emitOnSet)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {
        case TIMER_PROP_VERSION:
            status = AJ_ERR_DISALLOWED;
        break;
    }

    return status;
}



static AJ_Status Timer_OnMethodHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg, const char* objPath, uint8_t memberIndex)
{
    AJ_Status status = AJ_ERR_INVALID;

    switch (memberIndex) {

    case TIMER_METHOD_SET_TARGET_TIME_TO_START:
    {
        AJ_Message reply;
        int32_t target_time_to_start;
        status = AJ_UnmarshalArgs(msg, "i", &target_time_to_start);

        if (status != AJ_OK) {
            return status;
        }

        status = Cdm_Timer_CallSetTargetTimeToStart(busAttachment, objPath, target_time_to_start);

        AJ_MarshalReplyMsg(msg, &reply);
        if (status == AJ_OK) {
            status = AJ_DeliverMsg(&reply);
        }

        break;
    }

    case TIMER_METHOD_SET_TARGET_TIME_TO_STOP:
    {
        AJ_Message reply;
        int32_t target_time_to_stop;
        status = AJ_UnmarshalArgs(msg, "i", &target_time_to_stop);

        if (status != AJ_OK) {
            return status;
        }

        status = Cdm_Timer_CallSetTargetTimeToStop(busAttachment, objPath, target_time_to_stop);

        AJ_MarshalReplyMsg(msg, &reply);
        if (status == AJ_OK) {
            status = AJ_DeliverMsg(&reply);
        }

        break;
    }
    }

    return status;
}



const InterfaceHandler intfHandlerOperationTimer = {
    Timer_OnGetProperty,
    Timer_OnSetProperty,
    Timer_OnMethodHandler
};
