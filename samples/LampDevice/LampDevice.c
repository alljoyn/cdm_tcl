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
#include "../Utils/Utils.h"

#include "SwitchModelImpl.h"
#include "HSVModelImpl.h"

static const char* ObjPath = "/Cdm/Lamp";


static const char* AboutData =
    "<AboutData>"
        "  <AppId></AppId>"
        "  <DefaultLanguage>en</DefaultLanguage>"
        "  <DeviceName>Virtual Lamp (Color)</DeviceName>"
        "  <DeviceId></DeviceId>"
        "  <AppName>AllJoyn CDM Controllee</AppName>"
        "  <Manufacturer>Alljoyn Sample</Manufacturer>"
        "  <ModelNumber>Wxfy388i</ModelNumber>"
        "  <Description>This is a Full Featured Lamp Controllee Application</Description>"
        "  <DateOfManufacture>10/1/2199</DateOfManufacture>"
        "  <SoftwareVersion>12.20.44 build 44454</SoftwareVersion>"
        "  <HardwareVersion>355.499.b</HardwareVersion>"
        "  <SupportUrl>http://www.alljoyn.org</SupportUrl>"
        "  <CountryOfProduction>USA</CountryOfProduction>"
        "  <CorporateBrand>Lamp Corportate Brand</CorporateBrand>"
        "  <ProductBrand>Lamp Product Brand</ProductBrand>"
        "  <Location>Room1</Location>"
        "  <DeviceTypeDescription>"
        "      <TypeDescription>"
        "          <device_type>23</device_type>"
        "          <object_path>/Cdm/Lamp</object_path>"
        "      </TypeDescription>"
        "  </DeviceTypeDescription>"
        "</AboutData>";

static const uint32_t suites[4] = { AUTH_SUITE_ECDHE_ECDSA, AUTH_SUITE_ECDHE_SPEKE, AUTH_SUITE_ECDHE_PSK, AUTH_SUITE_ECDHE_NULL };

static void InitProperties(void)
{
    OnControlModel *onControlsModel = GetOnControlModel();
    BrightnessModel *brightnessModel = GetBrightnessModel();
    ColorModel *colorModel = GetColorModel();

    onControlsModel->MethodSwitchOn(NULL, ObjPath);
    brightnessModel->SetBrightness(NULL, ObjPath, 0.5);
    colorModel->SetHue(NULL, ObjPath, 0.0);
    colorModel->SetSaturation(NULL, ObjPath, 0.1);
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
        if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.OnOffStatus") == 0)
        {
            OnOffStatusModel *onOffStatusModel = GetOnOffStatusModel();
            status = HandleOnOffStatusCommand(cmd, onOffStatusModel);
        }
        else
        if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.Brightness") == 0)
        {
            BrightnessModel *brightnessModel = GetBrightnessModel();
            status = HandleBrightnessCommand(cmd, brightnessModel);
        }
        else
        if (strcmp(cmd->interface, "org.alljoyn.SmartSpaces.Operation.Color") == 0)
        {
            ColorModel *colorModel = GetColorModel();
            status = HandleColorCommand(cmd, colorModel);
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
    bool emitOnSet;
    bool useCommands = false;

    CdmAboutIconParams iconParams;
    CdmRoutingNodeParams routingNodeParams;
    CdmBusAttachment bus;
    CdmAboutDataBuf aboutData;

    FindArgValue(argc, argv, "--certs-dir", "certificates/security", &certsDir);
    FindArgValue(argc, argv, "--state-dir", "emulated_device_state", &stateDir);
    useCommands = (ArgExists(argc, argv, "--use-commands") > 0);
    emitOnSet = (ArgExists(argc, argv, "--emit-on-set") > 0);
    HAL_Init(stateDir, "");

    InitProperties();

    Cdm_SetSuites(suites, 4);

    if (AJ_OK != Cdm_LoadFiles(certsDir)) {
        fprintf(stderr, "Invalid certificate files\n");
        return 1;
    }

    aboutData = Cdm_CreateAboutDataFromXml(AboutData);

    Cdm_SetDefaultAboutIconParams(&iconParams);
    status = Cdm_SystemInit(&iconParams, emitOnSet);
    if (status != AJ_OK)
    {
        fprintf(stderr, "SystemInit failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto CLEANUP;
    }

    status = Cdm_AddInterface(ObjPath, ON_OFF_STATUS, intfDescOperationOnOffStatus, &intfHandlerOperationOnOffStatus, GetOnOffStatusModel());
    if (status != AJ_OK)
    {
        fprintf(stderr, "Cdm_AddInterface failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto CLEANUP;
    }

    status = Cdm_AddInterface(ObjPath, OFF_CONTROL, intfDescOperationOffControl, &intfHandlerOperationOffControl, GetOffControlModel());
    if (status != AJ_OK)
    {
        fprintf(stderr, "Cdm_AddInterface failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto CLEANUP;
    }

    status = Cdm_AddInterface(ObjPath, ON_CONTROL, intfDescOperationOnControl, &intfHandlerOperationOnControl, GetOnControlModel());
    if (status != AJ_OK)
    {
        fprintf(stderr, "Cdm_AddInterface failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto CLEANUP;
    }

    status = Cdm_AddInterface(ObjPath, BRIGHTNESS, intfDescOperationBrightness, &intfHandlerOperationBrightness, GetBrightnessModel());
    if (status != AJ_OK)
    {
        fprintf(stderr, "Cdm_AddInterface failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto CLEANUP;
    }

    status = Cdm_AddInterface(ObjPath, COLOR, intfDescOperationColor, &intfHandlerOperationColor, GetColorModel());
    if (status != AJ_OK)
    {
        fprintf(stderr, "Cdm_AddInterface failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto CLEANUP;
    }

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

