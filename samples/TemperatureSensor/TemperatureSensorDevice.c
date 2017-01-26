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

#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ajtcl/aj_status.h>
#include <ajtcl/cdm/utils/CdmSystem.h>
#include <ajtcl/cdm/utils/CdmAboutData.h>
#include <ajtcl/cdm/utils/CdmSecurity.h>

#include <ajtcl/cdm/CdmControllee.h>

#include "../Utils/HAL.h"
#include "CurrentTemperatureModelImpl.h"

static const char* ObjPath = "/Cdm/TempSensor";


static const char* AboutData = 
"<AboutData>"
"    <AppId>5CE75C2B-3C3D-48B6-AA8C-C551F30B5F5C</AppId>"
"    <DefaultLanguage>en</DefaultLanguage>"
"    <DeviceName>Virtual Temperature Sensor</DeviceName>"
"    <DeviceId>5CE75C2B-3C3D-48B6-AA8C-C551F30B5F5C</DeviceId>"
"    <AppName>Room Temperature</AppName>"
"    <Manufacturer>Raspberry Pi</Manufacturer>"
"    <ModelNumber>1.0</ModelNumber>"
"    <Description>Raspberry Pi Temperature/Humidity Sensor using the Sense Hat</Description>"
"    <DateOfManufacture>2015-01-08</DateOfManufacture>"
"    <SoftwareVersion>1.0.0</SoftwareVersion>"
"    <HardwareVersion>3.0.0</HardwareVersion>"
"    <SupportUrl>www.example.com</SupportUrl>"
"    <CountryOfProduction>Australia</CountryOfProduction>"
"    <CorporateBrand>Brand1</CorporateBrand>"
"    <ProductBrand>Brand2</ProductBrand>"
"    <Location>Kitchen</Location>"
"    <DeviceTypeDescription>"
"        <TypeDescription>"
"            <device_type>1</device_type>"
"            <object_path>/Cdm/TempSensor</object_path>"
"        </TypeDescription>"
"    </DeviceTypeDescription>"
"</AboutData>";

static const uint32_t suites[4] = { AUTH_SUITE_ECDHE_ECDSA, AUTH_SUITE_ECDHE_SPEKE, AUTH_SUITE_ECDHE_PSK, AUTH_SUITE_ECDHE_NULL };

static int ArgExists(int argc, char **argv, const char *arg)
{
    int i=0;
    for (; i<argc; ++i)
    {
        if (strcmp(arg, argv[i]) == 0)
        {
            return i;
        }
    }

    return 0;
}

static void FindArgValue(int argc, char **argv, const char *arg, const char *defValue, char **out)
{
    int index = ArgExists(argc, argv, arg);
    *out = (index != 0 && index + 1 < argc) ? argv[index + 1] : (char*)defValue;
}

static AJ_Status MainCommandHandler(const Command* cmd)
{
    AJ_Status status = AJ_ERR_FAILURE;

    if (strcmp(cmd->name, "reset") == 0) {
        InitProperties();
        return AJ_OK;
    }

    if (strcmp(cmd->name, "changed") == 0)
    {
        if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.CurrentHumidity") == 0)
        {
            status = HandleCurrentHumidityCommand(cmd, NULL);
        }
        else
        if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Environment.CurrentTemperature") == 0)
        {
            status = HandleCurrentTemperatureCommand(cmd, NULL);
        }
    }
    else
    {
        fprintf(stderr, "Error: unrecognised command %s\n", cmd->name);
        status = AJ_ERR_FAILURE;
    }

    return status;
}

int main(int argc, char *argv[])
{
    int retVal = 0;
    AJ_Status status;

    char *certsDir;
    char *stateDir;
    bool useCommands = false;

    CdmAboutIconParams iconParams;
    CdmRoutingNodeParams routingNodeParams;
    CdmBusAttachment bus;
    CdmAboutDataBuf aboutData;

    FindArgValue(argc, argv, "--certs-dir", "certificates/security", &certsDir);
    FindArgValue(argc, argv, "--state-dir", "emulated_device_state", &stateDir);
    useCommands = (ArgExists(argc, argv, "--use-commands") > 0);
    HAL_Init(stateDir, "");

    Cdm_SetSuites(suites, 4);

    if (AJ_OK != Cdm_LoadFiles(certsDir)) {
        fprintf(stderr, "Invalid certificate files\n");
        return 1;
    }

    aboutData = Cdm_CreateAboutDataFromXml(AboutData);

    Cdm_SetDefaultAboutIconParams(&iconParams);
    status = Cdm_SystemInit(&iconParams, true);
    if (status != AJ_OK)
    {
        fprintf(stderr, "SystemInit failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto CLEANUP;
    }

    status = Cdm_AddInterface(ObjPath, CURRENT_TEMPERATURE, intfDescEnvironmentCurrentTemperature, &intfHandlerEnvironmentCurrentTemperature, GetCurrentTemperatureModel());
    if (status != AJ_OK)
    {
        fprintf(stderr, "Cdm_AddInterface failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto CLEANUP;
    }

    status = Cdm_AddInterface(ObjPath, CURRENT_HUMIDITY, intfDescEnvironmentCurrentHumidity, &intfHandlerEnvironmentCurrentHumidity, GetCurrentHumidityModel());
    if (status != AJ_OK)
    {
        fprintf(stderr, "Cdm_AddInterface failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto CLEANUP;
    }

    InitProperties();

    if (useCommands)
    {
        StartCommands(MainCommandHandler);
    }

    while(1) {
        bus.isConnected = 0;
        Cdm_SetDefaultRoutingNodeParams(&routingNodeParams);
        status = Cdm_SystemConnect(&routingNodeParams, &bus);
        if (status!=AJ_OK || bus.isConnected==0) {
            fprintf(stderr, "SystemConnect failed: %s\n", AJ_StatusText(status));
            retVal = 1;
            goto CLEANUP;
        }

        status = Cdm_EnableSecurity(&bus.bus, NULL);
        if (status!=AJ_OK) {
            fprintf(stderr, "Cdm_EnableSecurity failed: %s\n", AJ_StatusText(status));
            retVal = 1;
            goto SHUTDOWN;
        }

        InitCurrentTemperatureModel(&bus.bus, ObjPath);

        status = Cdm_MessageLoop(&bus);

        status = Cdm_HandleMessageLoopExit(status, &bus, &routingNodeParams);
        if (status != AJ_OK) {
            retVal = 1;
            goto SHUTDOWN;
        }
    }

SHUTDOWN:
    Cdm_SystemStop();

CLEANUP:
    Cdm_DestroyAboutData(aboutData);

    return retVal;
}

