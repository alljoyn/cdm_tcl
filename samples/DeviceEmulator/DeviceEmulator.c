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

#include "DeviceConfig.h"
#include "InterfaceFactory.h"
#include "DeviceCommand.h"
#include "../Utils/HAL.h"


static const uint32_t suites[4] = { AUTH_SUITE_ECDHE_ECDSA, AUTH_SUITE_ECDHE_SPEKE, AUTH_SUITE_ECDHE_PSK, AUTH_SUITE_ECDHE_NULL };
static DEM_Config* theConfig;


static void InitProperties(bool force)
{
    int i = 0;
    for (; i < theConfig->numObjects; ++i) {
        DEM_Object* obj = &theConfig->objects[i];

        int j = 0;
        for (; j < obj->numInterfaces; ++j) {
            DEM_Interface* iface = &obj->interfaces[j];

            int k = 0;
            /* Set some initial property values. */
            for (; k < iface->numProperties; ++k) {
                DEM_Property* prop = &iface->properties[k];
                if (prop->initialState) {
                    HAL_WritePropertyXml(obj->objectPath, iface->name, prop->name, prop->initialState, force || !prop->defaultOnly);
                }
            }
        }
    }
}

static void CreateInterfaces()
{
    int i = 0;
    for (; i < theConfig->numObjects; ++i) {
        DEM_Object* obj = &theConfig->objects[i];

        int j = 0;
        for (; j < obj->numInterfaces; ++j) {
            DEM_Interface* iface = &obj->interfaces[j];
            createInterface(obj->objectPath, iface->name);
        }
    }
}

static AJ_Status MainCommandHandler(const Command* cmd)
{
    if (strcmp(cmd->name, "reset") == 0) {
        InitProperties(true);
        return AJ_OK;
    }

    return DeviceCommandHandler(cmd);
}

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

int main(int argc, char *argv[])
{
    int retVal = 0;
    AJ_Status status;

    char *certsDir;
    char *stateDir;
    bool emitOnSet;
    bool noCommands = false;

    CdmAboutIconParams iconParams;
    CdmRoutingNodeParams routingNodeParams;
    CdmBusAttachment bus;
    CdmAboutDataBuf aboutData;

    FindArgValue(argc, argv, "--state-dir", "emulated_device_state", &stateDir);
    FindArgValue(argc, argv, "--certs-dir", "certificates/security", &certsDir);
    emitOnSet = (ArgExists(argc, argv, "--emit-on-set") > 0);
    noCommands = (ArgExists(argc, argv, "--no-commands") > 0);

    HAL_Init(stateDir, "");

    if (argc < 2)
    {
        fprintf(stderr, "Usage: DeviceEmulator xml-file\n");
        return 1;
    }

    Cdm_SetSuites(suites, 4);
    if (AJ_OK != Cdm_LoadFiles(certsDir)) {
        fprintf(stderr, "Invalid certificate files\n");
        return 1;
    }

    theConfig = DEM_CreateConfig(argv[1]);

    if (!theConfig) {
        fprintf(stderr, "Invalid XML file\n");
        return 1;
    }

    aboutData = Cdm_CreateAboutDataFromXml(theConfig->aboutData);

    Cdm_SetDefaultAboutIconParams(&iconParams);
    status = Cdm_SystemInit(&iconParams, emitOnSet);
    if (status != AJ_OK)
    {
        fprintf(stderr, "SystemInit failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto CLEANUP;
    }

    CreateInterfaces();
    InitProperties(false);

    if (!noCommands)
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
    DEM_FreeConfig(theConfig);

    return retVal;
}

