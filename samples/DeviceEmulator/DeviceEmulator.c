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
#include <stdlib.h>

#include <ajtcl/aj_status.h>
#include <ajtcl/cdm/utils/CDM_System.h>
#include <ajtcl/cdm/utils/CDM_AboutData.h>
#include <ajtcl/cdm/utils/CDM_Security.h>

#include <ajtcl/cdm/CdmControllee.h>

#include <ajtcl/cdm/interfaces/operation/OnOffStatusInterface.h>

#include "DeviceConfig.h"
#include "InterfaceFactory.h"
#include "../Utils/HAL.h"

#include "Models/operation/OnOffStatusModelImpl.h"


/**
 * Security authentication suites.
 * - DO NOT REUSE THESE VALUES. They are copied from ajtcl/samples/secure/SecureServiceECDHE.c.
 */

static const uint32_t suites[4] = { AUTH_SUITE_ECDHE_ECDSA, AUTH_SUITE_ECDHE_SPEKE, AUTH_SUITE_ECDHE_PSK, AUTH_SUITE_ECDHE_NULL };
//static const char pem_prv[] = {
//    "-----BEGIN EC PRIVATE KEY-----"
//        "MDECAQEEICCRJMbxSiWUqj4Zs7jFQRXDJdBRPWX6fIVqE1BaXd08oAoGCCqGSM49"
//        "AwEH"
//        "-----END EC PRIVATE KEY-----"
//};
//
//static const char pem_x509[] = {
//    "-----BEGIN CERTIFICATE-----"
//        "MIIBuDCCAV2gAwIBAgIHMTAxMDEwMTAKBggqhkjOPQQDAjBCMRUwEwYDVQQLDAxv"
//        "cmdhbml6YXRpb24xKTAnBgNVBAMMIDgxM2FkZDFmMWNiOTljZTk2ZmY5MTVmNTVk"
//        "MzQ4MjA2MB4XDTE1MDcyMjIxMDYxNFoXDTE2MDcyMTIxMDYxNFowQjEVMBMGA1UE"
//        "CwwMb3JnYW5pemF0aW9uMSkwJwYDVQQDDCAzOWIxZGNmMjBmZDJlNTNiZGYzMDU3"
//        "NzMzMjBlY2RjMzBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABGJ/9F4xHn3Klw7z"
//        "6LREmHJgzu8yJ4i09b4EWX6a5MgUpQoGKJcjWgYGWb86bzbciMCFpmKzfZ42Hg+k"
//        "BJs2ZWajPjA8MAwGA1UdEwQFMAMBAf8wFQYDVR0lBA4wDAYKKwYBBAGC3nwBATAV"
//        "BgNVHSMEDjAMoAoECELxjRK/fVhaMAoGCCqGSM49BAMCA0kAMEYCIQDixoulcO7S"
//        "df6Iz6lvt2CDy0sjt/bfuYVW3GeMLNK1LAIhALNklms9SP8ZmTkhCKdpC+/fuwn0"
//        "+7RX8CMop11eWCih"
//        "-----END CERTIFICATE-----"
//};

static const char ecspeke_password[] = "1234";
static const char psk_password[] = "faaa0af3dd3f1e0379da046a3ab6ca44";

static void CreateInterfaces(DEM_Config* config)
{
    for (int i = 0; i < config->numObjects; ++i) {
        DEM_Object* obj = &config->objects[i];

        for (int j = 0; j < obj->numInterfaces; ++j) {
            fprintf(stdout, "Creating interface %s\n", obj->interfaces[j].name);
            createInterface("/cdm/emulated", obj->interfaces[j].name);
        }
    }
}



int main(int argc, char *argv[])
{
    int retVal = 0;
    AJ_Status status;

    HAL_DefaultInit();

    CDM_AboutIconParams iconParams;
    CDM_RoutingNodeParams routingNodeParams;
    CDM_BusAttachment bus;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: DeviceEmulator xml-file\n");
        return 1;
    }

    Cdm_SetSuites(suites, 4);
    Cdm_EnableSPEKE(ecspeke_password);
    Cdm_EnablePSK(psk_password);

    DEM_Config *config = DEM_CreateConfig(argv[1]);

    if (!config) {
        fprintf(stderr, "Invalid XML file\n");
        return 1;
    }

    const CDM_AboutDataBuf aboutData = CDM_CreateAboutDataFromXml(config->aboutData);

    CDM_SetDefaultAboutIconParams(&iconParams);
    status = CDM_SystemInit(&iconParams);
    if (status != AJ_OK)
    {
        fprintf(stderr, "SystemInit failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto CLEANUP;
    }

    CreateInterfaces(config);

    bus.isConnected = 0;
    CDM_SetDefaultRoutingNodeParams(&routingNodeParams);
    status = CDM_SystemConnect(&routingNodeParams, &bus);
    if (status != AJ_OK || bus.isConnected == 0)
    {
        fprintf(stderr, "SystemConnect failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto CLEANUP;
    }

    status = Cdm_EnableSecurity(&bus.bus, NULL);
    if (status != AJ_OK)
    {
        fprintf(stderr, "Cdm_EnableSecurity failed: %s\n", AJ_StatusText(status));
        retVal = 1;
        goto SHUTDOWN;
    }

    status = Cdm_MessageLoop(&bus);


SHUTDOWN:
    CDM_SystemStop();

CLEANUP:
    CDM_DestroyAboutData(aboutData);
    DEM_FreeConfig(config);

    return retVal;
}
