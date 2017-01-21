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
#include <ajtcl/cdm/utils/CdmAboutData.h>
#include <ajtcl/cdm/utils/PropertyStoreOEMProvisioning.h>

#include <ajtcl/cdm/utils/BSXML.h>

/*
 * TODO: Support multi languages properly
 */

const char *deviceManufactureName;
const char *deviceProductName;
const char* const* propertyStoreDefaultLanguages;

static const char* DEFAULT_DEVICETYPEDESC[] = { "" };

const char **propertyStoreDefaultValues[CDM_PROPERTY_STORE_NUMBER_OF_KEYS] =
{
/* "Default Values per language",   "Key Name" */
/* Runtime keys. */
    NULL,                           /*DeviceId*/
    NULL,                           /*AppId*/
    NULL,                           /*DeviceName*/

/*  Mandatory about keys. */
    NULL,                           /*DefaultLanguage*/
    NULL,                           /*AppName*/
    NULL,                           /*Description*/
    NULL,                           /*Manufacturer*/
    NULL,                           /*ModelNumber*/
    NULL,                           /*DateOfManufacture*/
    NULL,                           /*SoftwareVersion*/
    NULL,                           /*AJSoftwareVersion*/

/* Optional about keys. */
    NULL,                           /*HardwareVersion*/
    NULL,                           /*SupportUrl*/

/* CDM about keys. */
    NULL,                           /*CountryOfProduction*/
    NULL,                           /*CorporateBrand*/
    NULL,                           /*ProductBrand*/
    NULL,                           /*Location*/
    DEFAULT_DEVICETYPEDESC,         /*DeviceTypeDescription*/
};

static char machineIdVar[MACHINE_ID_LENGTH + 1] = { 0 };
static char *machineIdVars[] = { machineIdVar };
static char deviceNameVar[DEVICE_NAME_VALUE_LENGTH + 1] = { 0 };
static char *deviceNameVars[] = { deviceNameVar, deviceNameVar };

PropertyStoreConfigEntry propertyStoreRuntimeValues[AJSVC_PROPERTY_STORE_NUMBER_OF_RUNTIME_KEYS] =
    {
        { machineIdVars,             MACHINE_ID_LENGTH + 1 },               /*DeviceId*/
        { machineIdVars,             MACHINE_ID_LENGTH + 1 },               /*AppId*/
        { deviceNameVars,            DEVICE_NAME_VALUE_LENGTH + 1 },        /*DeviceName*/
    };

DeviceTypeDescription *deviceTypeDescription;


#define ARRAY_MAX 10

typedef struct {
    const char* element;
    int elemSize;
} ArrayElement;

typedef struct {
    ArrayElement values[ARRAY_MAX];
    int numElements;
} Array;


typedef struct {
    long dataSize;

    ArrayElement *defaultLanguage;

    Array languages;
    Array deviceNames;
    Array appNames;
    Array descriptions;
    Array manufacturers;
    Array deviceModels;
    Array manufactureDates;
    Array softwareVersions;
    Array hardwareVersions;
    Array supportUrls;

    /* cdm additions */
    Array countries;
    Array corporateBrands;
    Array productBrands;
    Array locations;

    Array deviceTypes;
    Array devicePaths;

    int numDevices;
} ABOUT_ANALYSIS;

static void AddArrayElement(Array* array, const char* element, int elemSize)
{
    int curIndex;

    if (array == NULL || element == NULL || elemSize == 0)
        return;

    curIndex = array->numElements;
    array->values[curIndex].element = element;
    array->values[curIndex].elemSize = elemSize;

    ++array->numElements;
}

static int ProcessElement(Element *root, const char *elementName, Array* array, long *dataSize)
{
    Element **elems = BSXML_GetPath(root, elementName);
    Element **elemItr;

    if (!elems)
        return 0;

    elemItr = &elems[0];

    while ((*elemItr)) {
        int len = (int)strlen((*elemItr)->content);
        AddArrayElement(array, (*elemItr)->content, len);
        *dataSize += len + 1;
        ++elemItr;
    }

    return 1;
}

static int ProcessDevices(Element *root, ABOUT_ANALYSIS *analysis)
{
    Element **elems = BSXML_GetPath(root, "DeviceTypeDescription");
    Element **elemItr;

    if (!elems)
        return 0;

    elemItr = &elems[0];
    while((*elemItr)) {
        if (!ProcessElement(*(*elemItr)->children, "device_type", &analysis->deviceTypes, &analysis->dataSize))
            return 0;

        if (!ProcessElement(*(*elemItr)->children, "object_path", &analysis->devicePaths, &analysis->dataSize))
            return 0;

        ++analysis->numDevices;
        ++elemItr;
    }
    return 1;
}

static Element *PreparseXML(const char *xmlBuf, ABOUT_ANALYSIS *analysis)
{
    Element *root = BSXML_GetRoot(xmlBuf);

    if (!root)
        return NULL;

    if (!ProcessElement(root, "DefaultLanguage", &analysis->languages, &analysis->dataSize))
        goto ELEM_MISSING_ERROR;

    analysis->defaultLanguage = &analysis->languages.values[0];

    if (!ProcessElement(root, "DeviceName", &analysis->deviceNames, &analysis->dataSize))
        goto ELEM_MISSING_ERROR;

    if (!ProcessElement(root, "AppName", &analysis->appNames, &analysis->dataSize))
        goto ELEM_MISSING_ERROR;

    if (!ProcessElement(root, "Manufacturer", &analysis->manufacturers, &analysis->dataSize))
        goto ELEM_MISSING_ERROR;

    if (!ProcessElement(root, "ModelNumber", &analysis->deviceModels, &analysis->dataSize))
        goto ELEM_MISSING_ERROR;

    if (!ProcessElement(root, "Description", &analysis->descriptions, &analysis->dataSize))
        goto ELEM_MISSING_ERROR;

    if (!ProcessElement(root, "DateOfManufacture", &analysis->manufactureDates, &analysis->dataSize))
        goto ELEM_MISSING_ERROR;

    if (!ProcessElement(root, "SoftwareVersion", &analysis->softwareVersions, &analysis->dataSize))
        goto ELEM_MISSING_ERROR;

    /* These are optional */
    ProcessElement(root, "HardwareVersion", &analysis->hardwareVersions, &analysis->dataSize);
    ProcessElement(root, "SupportUrl", &analysis->supportUrls, &analysis->dataSize);
    ProcessElement(root, "CountryOfProduction", &analysis->countries, &analysis->dataSize);
    ProcessElement(root, "Location", &analysis->locations, &analysis->dataSize);
    ProcessElement(root, "CorporateBrand", &analysis->corporateBrands, &analysis->dataSize);
    ProcessElement(root, "ProductBrand", &analysis->productBrands, &analysis->dataSize);

    if (!ProcessDevices(root, analysis))
        goto ELEM_MISSING_ERROR;

    return root;

ELEM_MISSING_ERROR:
    BSXML_FreeElement(root);
    return NULL;

}


typedef struct
{
    CdmAboutDataBuf buf;
    CdmAboutDataBuf dataSegStart;
    long dataItr;
    long arrayItr;
    long bufSize;
} AboutDataBuilder;


typedef struct {
    Array *array;
    int index;
} ArrayToPropertyStoreMap;


static int countArrayElements(ArrayToPropertyStoreMap *mapping, int numEntries, const ABOUT_ANALYSIS *analysis)
{
    int total = 0;
    int i;

    for (i=0; i<numEntries; ++i)
        total += mapping[i].array->numElements;

    /* Count the nulls */
    total += numEntries;

    return total;
}


static int WriteArray(const Array *array, AboutDataBuilder *writer)
{
    int i;
    void *curArrayPos;
    void *curDataPos;

    for (i=0; i<array->numElements; ++i)
    {
        if (writer->dataItr + array->values[i].elemSize> writer->bufSize)
            return 0;

        /* write data entry to the data part */
        curDataPos = writer->dataSegStart + writer->dataItr;
        memcpy(curDataPos, array->values[i].element, array->values[i].elemSize);
        writer->dataItr += array->values[i].elemSize + 1;

        /* write address of data into the array entry */
        curArrayPos = writer->buf + writer->arrayItr;
        if ((char*)curArrayPos + sizeof(void*) >= writer->dataSegStart)
            return 0;

        memcpy(curArrayPos, &curDataPos, sizeof(void*));
        writer->arrayItr += sizeof(void*);
    }

    /* Array is done. Add extra for a null terminator */
    writer->arrayItr += sizeof(void*);

    return 1;
}


static int WritePropertyStoreDefaultValues(ArrayToPropertyStoreMap *mapping, int numEntries, AboutDataBuilder *aboutDataBuf)
{
    int i;
    void *curArrayStart;

    if (mapping == NULL || aboutDataBuf == NULL || aboutDataBuf->buf == NULL)
        return 0;

    for (i=0; i<numEntries; ++i) {
        if (mapping[i].array->numElements == 0)
            continue;

        curArrayStart = aboutDataBuf->buf + aboutDataBuf->arrayItr;
        if (!WriteArray(mapping[i].array, aboutDataBuf)) {
            printf("Error writing %d array to buffer.\n", i);
            return 0;
        }
        /* write the array start into the property store array */
        memcpy(&propertyStoreDefaultValues[mapping[i].index], &curArrayStart, sizeof(void*));
    }
    return 1;
}


static int WriteSupportedLanguages(const ABOUT_ANALYSIS *analysis, char *languagesArrayStart)
{
    int i;

    if (analysis == NULL || languagesArrayStart == NULL)
        return 0;

    for (i=0; i<analysis->languages.numElements; ++i) {
        memcpy(languagesArrayStart + (i * sizeof(void*)), &propertyStoreDefaultValues[3][i], sizeof(void*));
    }

    return 1;
}


static int WriteStandAlonePropertyStoreData(void *languagesArrayStart, void *deviceTypeArrayStart)
{
    if (languagesArrayStart == NULL)
        return 0;

    memcpy(&deviceManufactureName, &propertyStoreDefaultValues[6][0], sizeof(void*));
    memcpy(&deviceProductName, &propertyStoreDefaultValues[4][0], sizeof(void*));
    memcpy(&propertyStoreDefaultLanguages, &languagesArrayStart, sizeof(void*));

    deviceTypeDescription = deviceTypeArrayStart;
    return 1;
}

static int WriteDeviceTypesDescriptions(const ABOUT_ANALYSIS *analysis, void *deviceTypesArrayStart, AboutDataBuilder *aboutDataBuf)
{
    int i;
    DeviceTypeDescription *desc = (DeviceTypeDescription*)deviceTypesArrayStart;
    void *curPos;

    if (analysis == NULL || aboutDataBuf == NULL || deviceTypesArrayStart == NULL)
        return 0;

    if (analysis->numDevices == analysis->deviceTypes.numElements && analysis->numDevices != analysis->devicePaths.numElements)
        return 0;

    for (i=0; i<analysis->numDevices; ++i)
    {
        if (aboutDataBuf->dataItr > aboutDataBuf->bufSize)
            return 0;

        curPos = aboutDataBuf->dataSegStart + aboutDataBuf->dataItr;
        memcpy(curPos, analysis->devicePaths.values[i].element, analysis->devicePaths.values[i].elemSize);
        aboutDataBuf->dataItr += analysis->devicePaths.values[i].elemSize + 1;

        desc[i].type = (DeviceType)(int)atoi(analysis->deviceTypes.values[i].element);
        desc[i].objectpath = curPos;
    }
    return 1;
}


const CdmAboutDataBuf Cdm_CreateAboutDataFromXml(const char *aboutData)
{
    static ABOUT_ANALYSIS analysis;
    static ArrayToPropertyStoreMap mapping[] = {
        /* 0 Device Id */
        /* 1 App Id */
        {&analysis.deviceNames, 2},
        {&analysis.languages, 3},
        {&analysis.appNames, 4},
        {&analysis.descriptions, 5},
        {&analysis.manufacturers, 6},
        {&analysis.deviceModels, 7},
        {&analysis.manufactureDates, 8},
        {&analysis.softwareVersions, 9},
        /* 10 is ajVersion */
        {&analysis.hardwareVersions, 11},
        {&analysis.supportUrls, 12},
        {&analysis.countries, 13},
        {&analysis.corporateBrands, 14},
        {&analysis.productBrands, 15},
        {&analysis.locations, 16},
    };

    AboutDataBuilder aboutDataBuf;
    char *languagesArrayStart;
    char *deviceTypesArrayStart;
    int numArrayElements;
    int numPropStoreArrays = (sizeof(mapping) / sizeof(ArrayToPropertyStoreMap));

    int propertyStoreArraySize;
    int supportedLanguagesArraySize;
    int deviceTypeArraySize;

    int totalArraysSize;

    memset(&analysis, 0, sizeof(ABOUT_ANALYSIS));
    Element *xmlRoot = PreparseXML(aboutData, &analysis);
    if (!xmlRoot)
        return NULL;

    /* The total number of pointers across all the arrays */
    numArrayElements = countArrayElements(mapping, numPropStoreArrays, &analysis);

    /* The total amount of memory required by the property store arrays */
    propertyStoreArraySize = numArrayElements * sizeof(void*);

    /* the total amount of memory required by the supported languages array */
    supportedLanguagesArraySize = (analysis.languages.numElements + 1) * sizeof(void*);

    /* the total amount of memory required by the device types array */
    deviceTypeArraySize = (analysis.numDevices + 1) * sizeof(DeviceTypeDescription);

    /* The total size of all the arrays */
    totalArraysSize = propertyStoreArraySize + supportedLanguagesArraySize + deviceTypeArraySize;

    analysis.dataSize += totalArraysSize;
    aboutDataBuf.buf = malloc(analysis.dataSize);
    memset(aboutDataBuf.buf, 0, analysis.dataSize);

    aboutDataBuf.bufSize = analysis.dataSize;
    aboutDataBuf.dataSegStart = aboutDataBuf.buf + totalArraysSize;
    aboutDataBuf.dataItr = 0;
    aboutDataBuf.arrayItr = 0;

    languagesArrayStart = aboutDataBuf.buf + propertyStoreArraySize;
    deviceTypesArrayStart = aboutDataBuf.buf + propertyStoreArraySize + supportedLanguagesArraySize;

    if (!WritePropertyStoreDefaultValues(mapping, sizeof(mapping) / sizeof(ArrayToPropertyStoreMap), &aboutDataBuf))
        goto ERROR;

    if (!WriteSupportedLanguages(&analysis, languagesArrayStart))
        goto ERROR;

    if (!WriteDeviceTypesDescriptions(&analysis, deviceTypesArrayStart, &aboutDataBuf))
        goto ERROR;

    if (!WriteStandAlonePropertyStoreData(languagesArrayStart, deviceTypesArrayStart))
        goto ERROR;

    BSXML_FreeElement(xmlRoot);
    return aboutDataBuf.buf;

ERROR:
    BSXML_FreeElement(xmlRoot);
    free(aboutDataBuf.buf);
    return NULL;
}

void Cdm_DestroyAboutData(CdmAboutDataBuf aboutData)
{
    if (aboutData != NULL)
        free(aboutData);
}