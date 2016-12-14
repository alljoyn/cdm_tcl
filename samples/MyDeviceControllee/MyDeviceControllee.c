/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <ajtcl/cdm/CdmControllee.h>
#include <signal.h>
#include <stdlib.h>
#include "ControlleeSampleUtil.h"
#include "PropertyStoreOEMProvisioning.h"
#include "HWMock/interfaces/environment/TargetTemperatureModelHWMock.h"
#include "HWMock/interfaces/operation/ChannelModelHWMock.h"

#define CDM_OBJECT_PATH_MY_DEVICE "/Cdm/MyDeviceControllee"
static const char* HAL_MOCK_FILE_NAME = "./HWMockFiles/MyDeviceHWMock.rtf";
static int32_t interruptSignalId = SIGUSR1;

static const char* DEFAULT_LANGUAGES[] = { "en" };
static const char* SUPPORTED_LANGUAGES[] = { "en", "de-AT", NULL };

// Core about keys.
static const char* DEFAULT_DEVICE_NAMES[] = { "My Device Controllee", "Mein Geraet Controllee" };
static const char* DEFAULT_APP_NAMES[] = { "Controllee" };
static const char* DEFAULT_DESCRIPTIONS[] = { "My Device Controllee", "Mein Geraet Controllee" };
static const char* DEFAULT_MANUFACTURERS[] = { "Company B(EN)", "Firma B(DE-AT)" };
static const char* DEFAULT_DEVICE_MODELS[] = { "0.0.1" };
static const char* DEFAULT_DATE_OF_MANUFACTURES[] = { "2014-05-01" };
static const char* DEFAULT_SOFTWARE_VERSIONS[] = { "0.0.1" };
static const char* DEFAULT_HARDWARE_VERSIONS[] = { "0.0.1" };
static const char* DEFAULT_SUPPORT_URLS[] = { "www.company_b.com", "www.company_b.com/de-AT" };

// CDM about keys.
static const char* DEFAULT_COUNTRY_OF_PRODUCTION[] = { "USA", "USA" };
static const char* DEFAULT_CORPORATEBRAND[] = { "CO. BRAND", "CO. BRAND" };
static const char* DEFAULT_PRODUCTBRAND[] = { "P. BRAND", "P. BRAND" };
static const char* DEFAULT_LOCATION[] = { "Room1", "Zimmer1" };
static const char* DEFAULT_DEVICETYPEDESC[] = { "" };

/**
 * About supported PropertyStore provisioning.
 */
const char* deviceManufactureName = "MY COMPANY";
const char* deviceProductName = "MY DEVICE";
const char* const* propertyStoreDefaultLanguages = SUPPORTED_LANGUAGES;

const char** propertyStoreDefaultValues[CDM_PROPERTY_STORE_NUMBER_OF_KEYS] =
{
// "Default Values per language",                    "Key Name"
// Runtime keys.
    NULL,                                           /*DeviceId*/
    NULL,                                           /*AppId*/
    DEFAULT_DEVICE_NAMES,                           /*DeviceName*/

// Mandatory about keys.
    DEFAULT_LANGUAGES,                              /*DefaultLanguage*/
    DEFAULT_APP_NAMES,                              /*AppName*/
    DEFAULT_DESCRIPTIONS,                           /*Description*/
    DEFAULT_MANUFACTURERS,                          /*Manufacturer*/
    DEFAULT_DEVICE_MODELS,                          /*ModelNumber*/
    DEFAULT_DATE_OF_MANUFACTURES,                   /*DateOfManufacture*/
    DEFAULT_SOFTWARE_VERSIONS,                      /*SoftwareVersion*/
    NULL,                                           /*AJSoftwareVersion*/

// Optional about keys.
    DEFAULT_HARDWARE_VERSIONS,                      /*HardwareVersion*/
    DEFAULT_SUPPORT_URLS,                           /*SupportUrl*/

// CDM about keys.
    DEFAULT_COUNTRY_OF_PRODUCTION,                  /*CountryOfProduction*/
    DEFAULT_CORPORATEBRAND,                         /*CorporateBrand*/
    DEFAULT_PRODUCTBRAND,                           /*ProductBrand*/
    DEFAULT_LOCATION,                               /*Location*/
    DEFAULT_DEVICETYPEDESC,                         /*DeviceTypeDescription*/
};

static char machineIdVar[MACHINE_ID_LENGTH + 1] = { 0 };
static char* machineIdVars[] = { machineIdVar };
static char deviceNameVar[DEVICE_NAME_VALUE_LENGTH + 1] = { 0 };
static char* deviceNameVars[] = { deviceNameVar, deviceNameVar };

PropertyStoreConfigEntry propertyStoreRuntimeValues[AJSVC_PROPERTY_STORE_NUMBER_OF_RUNTIME_KEYS] =
{
//  {"Buffers for Values per language", "Buffer Size"},                  "Key Name"
    { machineIdVars,             MACHINE_ID_LENGTH + 1 },               /*DeviceId*/
    { machineIdVars,             MACHINE_ID_LENGTH + 1 },               /*AppId*/
    { deviceNameVars,            DEVICE_NAME_VALUE_LENGTH + 1 },        /*DeviceName*/
};

DeviceTypeDescription deviceTypeDescription[] = {
    // (DeviceType, ObjectPath)
    { OTHER, CDM_OBJECT_PATH_MY_DEVICE },
};

/**
 * Security authentication suites.
 * - DO NOT REUSE THESE VALUES. They are copied from ajtcl/samples/secure/SecureServiceECDHE.c.
 */
static const char pem_prv[] = {
    "-----BEGIN EC PRIVATE KEY-----"
    "MDECAQEEICCRJMbxSiWUqj4Zs7jFQRXDJdBRPWX6fIVqE1BaXd08oAoGCCqGSM49"
    "AwEH"
    "-----END EC PRIVATE KEY-----"
};

static const char pem_x509[] = {
    "-----BEGIN CERTIFICATE-----"
    "MIIBuDCCAV2gAwIBAgIHMTAxMDEwMTAKBggqhkjOPQQDAjBCMRUwEwYDVQQLDAxv"
    "cmdhbml6YXRpb24xKTAnBgNVBAMMIDgxM2FkZDFmMWNiOTljZTk2ZmY5MTVmNTVk"
    "MzQ4MjA2MB4XDTE1MDcyMjIxMDYxNFoXDTE2MDcyMTIxMDYxNFowQjEVMBMGA1UE"
    "CwwMb3JnYW5pemF0aW9uMSkwJwYDVQQDDCAzOWIxZGNmMjBmZDJlNTNiZGYzMDU3"
    "NzMzMjBlY2RjMzBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABGJ/9F4xHn3Klw7z"
    "6LREmHJgzu8yJ4i09b4EWX6a5MgUpQoGKJcjWgYGWb86bzbciMCFpmKzfZ42Hg+k"
    "BJs2ZWajPjA8MAwGA1UdEwQFMAMBAf8wFQYDVR0lBA4wDAYKKwYBBAGC3nwBATAV"
    "BgNVHSMEDjAMoAoECELxjRK/fVhaMAoGCCqGSM49BAMCA0kAMEYCIQDixoulcO7S"
    "df6Iz6lvt2CDy0sjt/bfuYVW3GeMLNK1LAIhALNklms9SP8ZmTkhCKdpC+/fuwn0"
    "+7RX8CMop11eWCih"
    "-----END CERTIFICATE-----"
};

static const char psk_hint[] = "<anonymous>";
static const char psk_char[] = "faaa0af3dd3f1e0379da046a3ab6ca44";
static const char ecspeke_password[] = "1234";

/**
 * Controllee models.
 */
static HALMock halMock;
static TargetTemperatureModelHWMock targetTemperatureModelHWMock;
static ChannelModelHWMock channelModelHWMock;

/**
 * Hardware interrupt callback.
 */
static void InterruptCallback(int32_t signalId)
{
    irqOccurred = true;
}

/**
 * Main callbacks.
 */
static AJ_Status AppConnectedHandler(AJ_BusAttachment* busAttachment)
{
    printf("App connected to routing node!\n");

    // Register callback for signal to mimic hardware interrupts.
    // - Note: this is done after connecting to routing node to avoid problems.
    signal(interruptSignalId, InterruptCallback);

    return Cdm_DefaultAppConnectedHandler(busAttachment);
}

static AJ_Status AppDisconnectedHandler(AJ_BusAttachment* busAttachment, uint8_t restart)
{
    printf("App disconnected from routing node!\n");
    DeinitHALMock(&halMock);

    // Deregister the hardware interrupt handler when not connected to bus.
    signal(interruptSignalId, SIG_DFL);

    // Delegate to default util handler.
    return Cdm_DefaultAppDisconnectedHandler(busAttachment, restart);
}

static AJ_Status HardwareInterruptHandler(AJ_BusAttachment* busAttachment)
{
    printf("Hardware interrupt occurred!\n");
    AJ_Status status = AJ_OK;
    if (cdmModelsInitialised) {
        status = HALMock_EmitPropertyChangedSignals(&halMock);
    }
    return status;
}

static AJ_Status InitCdmInterfaces()
{
    AJ_Status status = AJ_OK;

    status = Cdm_AddInterface(CDM_OBJECT_PATH_MY_DEVICE, TARGET_TEMPERATURE_INTERFACE_NAME, intfDescEnvironmentTargetTemperature, &intfHandlerEnvironmentTargetTemperature, &targetTemperatureModelHWMock);
    status = Cdm_AddInterface(CDM_OBJECT_PATH_MY_DEVICE, CHANNEL_INTERFACE_NAME, intfDescOperationChannel, &intfHandlerOperationChannel, &channelModelHWMock);

    return status;
}

static AJ_Status InitCdmModels(AJ_BusAttachment* busAttachment)
{
    AJ_Status status = AJ_OK;

    status = InitHALMock(&halMock, busAttachment, HAL_MOCK_FILE_NAME);
    if (status != AJ_OK) {
        return status;
    }

    status = SetupTargetTemperatureModelHWMock(&targetTemperatureModelHWMock, &halMock, CDM_OBJECT_PATH_MY_DEVICE);
    if (status != AJ_OK) {
        goto CleanupHALMock;
    }

    status = SetupChannelModelHWMock(&channelModelHWMock, &halMock, CDM_OBJECT_PATH_MY_DEVICE);
    if (status != AJ_OK) {
        goto CleanupHALMock;
    }

CleanupHALMock:
    DeinitHALMock(&halMock);
    return status;
}

/**
 * Application entry point.
 */
int main(int argc, char** argv)
{
    if (argc > 1) {
        interruptSignalId = atoi(argv[1]);
    }
    printf("Opened %s - use 'kill -%d <PID>' (e.g. kill -10 12345) to mimic hardware interrupts.\n", DEFAULT_DEVICE_NAMES[0], interruptSignalId);

    CDM_MainParams mainParams;
    memset(&mainParams, 0, sizeof(CDM_MainParams));

    mainParams.AppConnectedHandler = AppConnectedHandler;
    mainParams.AppDisconnectedHandler = AppDisconnectedHandler;
    mainParams.InterruptHandler = HardwareInterruptHandler;
    mainParams.InitCdmInterfaces = InitCdmInterfaces;
    mainParams.InitCdmModels = InitCdmModels;
    mainParams.securityParams.defaultCallbackParams.pskPublicKey = psk_hint;
    mainParams.securityParams.defaultCallbackParams.pskPrivateKey = psk_char;
    mainParams.securityParams.defaultCallbackParams.spekePassword = ecspeke_password;
    mainParams.securityParams.defaultCallbackParams.ecdsaPEMPrivateKey = pem_prv;
    mainParams.securityParams.defaultCallbackParams.ecdsaPEMCertificate = pem_x509;

    return CDM_Main(&mainParams);
}