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

#include "GetTemp.h"
#include <iostream>
#include <cmath>
using namespace std;

extern "C" {

static double oneDecimal(double d)
{
    return round(d * 10.0) / 10.0;
}

#ifdef __arm__

#include <RTIMULib.h>

static RTIMUSettings *settings;
static RTIMU *imu;
static RTPressure *pressure;
static RTHumidity *humidity;


int InitGetTemp(void)
{
    int interval = 999999;

    settings = new RTIMUSettings();
    imu = RTIMU::createIMU(settings);
    if (imu) {
        imu->IMUInit();
    }

    pressure = RTPressure::createPressure(settings);
    if (pressure) {
        pressure->pressureInit();
    }

    humidity = RTHumidity::createHumidity(settings);
    if (humidity) {
        humidity->humidityInit();
    }

    cout << "polling interval " << interval << "\n";
    return interval;
}



void GetData(Data *data)
{
    if (data == NULL)
        return;

    data->temperature = 21.0;
    data->humidity = 0.0;

    if (imu) {
        RTIMU_DATA imuData = imu->getIMUData();

        if (pressure) {
            pressure->pressureRead(imuData);
        }

        if (humidity) {
            humidity->humidityRead(imuData);
        }

        if (imuData.temperatureValid) {
            data->temperature = oneDecimal(imuData.temperature);
        }

        if (imuData.humidityValid) {
            data->humidity = oneDecimal(imuData.humidity);
        }
    }
}

#else

#include "../Utils/HAL.h"

int InitGetTemp(void)
{
    double tempValue = 21.0;
    double humValue = 62.0;

    Element *tempElem = HAL_Encode_Double(tempValue, NULL);
    HAL_WritePropertyElem("/Cdm/TempSensor", "org.alljoyn.SmartSpaces.Environment.CurrentTemperature", "CurrentValue", tempElem);
    BSXML_FreeElement(tempElem);

    Element *humElem = HAL_Encode_Double(humValue, NULL);
    HAL_WritePropertyElem("/Cdm/TempSensor", "org.alljoyn.SmartSpaces.Environment.CurrentHumidity", "CurrentValue", humElem);
    BSXML_FreeElement(humElem);

    return 999999;
}


void GetData(Data *data)
{
    if (data == NULL)
        return;

    double value = 0.0;
    Element *tempElem = HAL_ReadProperty("/Cdm/TempSensor", "org.alljoyn.SmartSpaces.Environment.CurrentTemperature", "CurrentValue");
    Element *humElem = HAL_ReadProperty("/Cdm/TempSensor", "org.alljoyn.SmartSpaces.Environment.CurrentHumidity", "CurrentValue");

    if (tempElem) {
        value = HAL_Decode_Double(tempElem);
        BSXML_FreeElement(tempElem);
    }
    data->temperature = oneDecimal(value);

    humElem = HAL_ReadProperty("/Cdm/TempSensor", "org.alljoyn.SmartSpaces.Environment.CurrentHumidity", "CurrentValue");
    if (humElem) {
        value = HAL_Decode_Double(humElem);
        BSXML_FreeElement(humElem);
    }
    data->humidity = value;
}

#endif
} // end of extern "C"
