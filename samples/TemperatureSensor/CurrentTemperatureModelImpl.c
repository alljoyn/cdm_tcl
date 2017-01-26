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

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#include "CurrentTemperatureModelImpl.h"
#include "GetTemp.h"

/*  There is a race condition here. If watcher thread tries to emit a signal
    while there is a request for a current property value being processed
    then they will collide in the bus attachment's outgoing message buffer.
*/
pthread_t WatcherThread;

AJ_BusAttachment *TheBus;
const char* TheObjPath;

static Data     CurrentData;
static double   Precision   = 0.1;
static uint16_t UpdateMinTime = 1;
static int      PollInterval = 999999;  // in microseconds


static void* Watcher(void* arg)
{
    for (;;)
    {
        Data data;
        struct timespec ts;

        ts.tv_sec = 0;
        ts.tv_nsec = PollInterval * 1000;

        nanosleep(&ts, NULL);
        GetData(&data);

        if (fabs(CurrentData.temperature - data.temperature) >= Precision) {
            CurrentData.temperature = data.temperature;
            Cdm_CurrentTemperature_EmitCurrentValueChanged(TheBus, TheObjPath, CurrentData.temperature);
        }

        if (fabs(CurrentData.humidity - data.humidity) >= Precision) {
            CurrentData.humidity = data.humidity;
            Cdm_CurrentHumidity_EmitCurrentValueChanged(TheBus, TheObjPath, CurrentData.humidity);
        }
    }
    return 0;
}

void InitProperties(void)
{
    InitGetTemp();
}

void InitCurrentTemperatureModel(AJ_BusAttachment *bus, const char* objPath)
{
    TheBus = bus;
    TheObjPath = objPath;
    PollInterval = InitGetTemp();
    pthread_create(&WatcherThread, NULL, Watcher, NULL);
}



static AJ_Status GetCurrentTemperatureValue(void *context, const char *objPath, double *out)
{
    *out = CurrentData.temperature;
    return AJ_OK;
}



static AJ_Status GetPrecision(void *context, const char *objPath, double *out)
{
    *out = Precision;
    return AJ_OK;
}


static AJ_Status GetUpdateMinTime(void *context, const char *objPath, uint16_t *out)
{
    *out = UpdateMinTime;
    return AJ_OK;
}



static AJ_Status GetHumidityValue(void *context, const char *objPath, uint8_t *out)
{
    *out = lround(CurrentData.humidity);
    return AJ_OK;
}



static AJ_Status GetHumidityMaxValue(void *context, const char *objPath, uint8_t *out)
{
    *out = 100.0;
    return AJ_OK;
}



static CurrentTemperatureModel tempModel = {
    GetCurrentTemperatureValue
    , GetPrecision
    , GetUpdateMinTime
};



static CurrentHumidityModel humidityModel = {
    GetHumidityValue
    , GetHumidityMaxValue
};


CurrentTemperatureModel *GetCurrentTemperatureModel(void)
{
    return &tempModel;
}


CurrentHumidityModel *GetCurrentHumidityModel(void)
{
    return &humidityModel;
}


AJ_Status HandleCurrentHumidityCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.CurrentHumidity") == 0)
    {
        if (strcmp(cmd->property, "CurrentValue") == 0)
        {
            uint8_t value;
            status = GetHumidityValue(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentHumidityModel* model = (CurrentHumidityModel*)context;
                status = Cdm_CurrentHumidity_EmitCurrentValueChanged(model->busAttachment, cmd->objPath, value);
            }

        }
        if (strcmp(cmd->property, "MaxValue") == 0)
        {
            uint8_t value;
            status = GetHumidityMaxValue(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentHumidityModel* model = (CurrentHumidityModel*)context;
                status = Cdm_CurrentHumidity_EmitMaxValueChanged(model->busAttachment, cmd->objPath, value);
            }

        }
    }
    return status;
}


AJ_Status HandleCurrentTemperatureCommand(const Command* cmd, void* context)
{
    AJ_Status status = AJ_OK;
    if (strcmp(cmd->name, "changed") == 0 && strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.CurrentTemperature") == 0)
    {
        if (strcmp(cmd->property, "CurrentValue") == 0)
        {
            double value;
            status = GetCurrentTemperatureValue(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentTemperatureModel* model = (CurrentTemperatureModel*)context;
                status = Cdm_CurrentTemperature_EmitCurrentValueChanged(model->busAttachment, cmd->objPath, value);
            }

        }
        if (strcmp(cmd->property, "Precision") == 0)
        {
            double value;
            status = GetPrecision(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentTemperatureModel* model = (CurrentTemperatureModel*)context;
                status = Cdm_CurrentTemperature_EmitPrecisionChanged(model->busAttachment, cmd->objPath, value);
            }

        }
        if (strcmp(cmd->property, "UpdateMinTime") == 0)
        {
            uint16_t value;
            status = GetUpdateMinTime(context, cmd->objPath, &value);
            if (status == AJ_OK)
            {
                CurrentTemperatureModel* model = (CurrentTemperatureModel*)context;
                status = Cdm_CurrentTemperature_EmitUpdateMinTimeChanged(model->busAttachment, cmd->objPath, value);
            }

        }
    }
    return status;
}