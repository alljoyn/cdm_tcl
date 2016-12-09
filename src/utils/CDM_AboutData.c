/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <stdio.h>
#include <ajtcl/cdm/utils/CDM_AboutData.h>
#include <ajtcl/cdm/utils/PropertyStoreOEMProvisioning.h>

#include <expat.h>

/*
 * TODO: Support multi languages properly
 */

const char *deviceManufactureName;
const char *deviceProductName;
const char* const* propertyStoreDefaultLanguages; // = SUPPORTED_LANGUAGES;

const char **propertyStoreDefaultValues[CDM_PROPERTY_STORE_NUMBER_OF_KEYS] =
{
// "Default Values per language",   "Key Name"
// Runtime keys.
    NULL,                           /*DeviceId*/
    NULL,                           /*AppId*/
    NULL,                           /*DeviceName*/

// Mandatory about keys.
    NULL,                           /*DefaultLanguage*/
    NULL,                           /*AppName*/
    NULL,                           /*Description*/
    NULL,                           /*Manufacturer*/
    NULL,                           /*ModelNumber*/
    NULL,                           /*DateOfManufacture*/
    NULL,                           /*SoftwareVersion*/
    NULL,                           /*AJSoftwareVersion*/

// Optional about keys.
    NULL,                           /*HardwareVersion*/
    NULL,                           /*SupportUrl*/

// CDM about keys.
    NULL,                           /*CountryOfProduction*/
    NULL,                           /*CorporateBrand*/
    NULL,                           /*ProductBrand*/
    NULL,                           /*Location*/
    NULL,                           /*DeviceTypeDescription*/
};

static char machineIdVar[MACHINE_ID_LENGTH + 1] = { 0 };
static char *machineIdVars[] = { machineIdVar };
static char deviceNameVar[DEVICE_NAME_VALUE_LENGTH + 1] = { 0 };
static char *deviceNameVars[] = { deviceNameVar, deviceNameVar };

PropertyStoreConfigEntry propertyStoreRuntimeValues[AJSVC_PROPERTY_STORE_NUMBER_OF_RUNTIME_KEYS] =
    {
//  {"Buffers for Values per language", "Buffer Size"},                  "Key Name"
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

    //cdm additions
    Array countries;
    Array corporateBrands;
    Array productBrands;
    Array locations;

    Array deviceTypes;
    Array devicePaths;

    Array *curArray;

    int numDevices;

    int skip;
    int depth;
    XML_Parser parser;
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

static int isElement(const char *name, const char *expected) {
    return strncmp(name, expected, strlen(expected)) == 0;
}

static void XMLCALL StartElement(void *data, const char* name, const char **attrs)
{
    ABOUT_ANALYSIS *analysis = (ABOUT_ANALYSIS*)data;
    ++analysis->depth;

    if (isElement(name, "DefaultLanguage")) {
        analysis->curArray = &analysis->languages;
        analysis->defaultLanguage = &analysis->languages.values[analysis->languages.numElements];
    }
    else if (isElement(name, "DeviceName"))
        analysis->curArray = &analysis->deviceNames;
    else if (isElement(name, "AppName"))
        analysis->curArray = &analysis->appNames;
    else if (isElement(name, "Manufacturer"))
        analysis->curArray = &analysis->manufacturers;
    else if (isElement(name, "ModelNumber"))
        analysis->curArray = &analysis->deviceModels;
    else if (isElement(name, "Description"))
        analysis->curArray = &analysis->descriptions;
    else if (isElement(name, "DateOfManufacture"))
        analysis->curArray = &analysis->manufactureDates;
    else if (isElement(name, "SoftwareVersion"))
        analysis->curArray = &analysis->softwareVersions;
    else if (isElement(name, "HardwareVersion"))
        analysis->curArray = &analysis->hardwareVersions;
    else if (isElement(name, "SupportUrl"))
        analysis->curArray = &analysis->supportUrls;
    else if (isElement(name, "CountryOfProduction"))
        analysis->curArray = &analysis->countries;
    else if (isElement(name, "Location"))
        analysis->curArray = &analysis->locations;
    else if (isElement(name, "CorporateBrand"))
        analysis->curArray = &analysis->corporateBrands;
    else if (isElement(name, "ProductBrand"))
        analysis->curArray = &analysis->productBrands;
    else if (isElement(name, "TypeDescription"))
        ++analysis->numDevices;
    else if (isElement(name, "device_type"))
        analysis->curArray = &analysis->deviceTypes;
    else if (isElement(name, "object_path"))
        analysis->curArray = &analysis->devicePaths;
}

static void XMLCALL CharHandler(void *data, const char *txt, int txtLen)
{
    ABOUT_ANALYSIS *analysis = (ABOUT_ANALYSIS*)data;
    int dataSize = (analysis->curArray == &analysis->deviceTypes) ? 0 : (txtLen + 1);
    if (analysis->curArray) {
        AddArrayElement(analysis->curArray, txt, txtLen);
        analysis->dataSize += dataSize;
    }
}

static void XMLCALL EndElement(void *data, const char *name)
{
    ABOUT_ANALYSIS *analysis = (ABOUT_ANALYSIS*)data;

    if (analysis->skip == analysis->depth) {
        analysis->skip = 0;
    }

    analysis->curArray = NULL;
    --analysis->depth;
}

static int PreparseXML(const char *xmlBuf, int bufSize, ABOUT_ANALYSIS *analysis)
{
    int retVal = 0;
    XML_Parser xmlParser = XML_ParserCreate(NULL);
    if (!xmlParser)
    {
        fprintf(stderr, "Error create xml parser.\n");
        return 0;
    }

    analysis->parser = xmlParser;

    XML_SetUserData(xmlParser, analysis);
    XML_SetCharacterDataHandler(xmlParser, CharHandler);
    XML_SetElementHandler(xmlParser, StartElement, EndElement);
    retVal = XML_Parse(xmlParser, xmlBuf, bufSize, 1);

    XML_ParserFree(xmlParser);
    analysis->parser = NULL;

    return retVal;
}

typedef struct
{
    CDM_AboutDataBuf buf;
    long itr;
    long bufSize;
} AboutDataBuilder;

static int WriteArray(const Array *array, AboutDataBuilder *writer)
{
    int i;
    void *curPos;

    for (i=0; i<array->numElements; ++i)
    {
        if (writer->itr > writer->bufSize)
            return 0;

        curPos = writer->buf + writer->itr;
        memcpy(curPos, array->values[i].element, array->values[i].elemSize);
        writer->itr += array->values[i].elemSize + 1;
    }

    writer->itr += sizeof(void*);
    return 1;
}

typedef struct {
    Array *array;
    int index;
} ArrayToPropertyStoreMap;

static int countArraysWithEntries(ArrayToPropertyStoreMap *mapping, int numEntries)
{
    int total = 0;
    int i;
    for (i=0; i<numEntries; ++i)
        total += (mapping[i].array->numElements > 0) ? 1 : 0;

    return total;
}

static int WritePropertyStoreDefaultValues(ArrayToPropertyStoreMap *mapping, int numEntries, AboutDataBuilder *aboutDataBuf)
{
    char *propertyArrayItr = aboutDataBuf->buf;
    int i;
    char *entry;

    if (mapping == NULL || aboutDataBuf == NULL || aboutDataBuf->buf == NULL)
        return 0;

    for (i=0; i<numEntries; ++i) {
        if (mapping[i].array->numElements == 0)
            continue;

        entry = aboutDataBuf->buf + aboutDataBuf->itr;
        if (!WriteArray(mapping[i].array, aboutDataBuf)) {
            printf("Error writing %d array to buffer.\n", i);
            return 0;
        }

        // Setup the property store array of lists of strings
        memcpy(propertyArrayItr, &entry, sizeof(void*));
        memcpy(&propertyStoreDefaultValues[mapping[i].index], &propertyArrayItr, sizeof(void*));
        propertyArrayItr += sizeof(void*);
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
        if (aboutDataBuf->itr > aboutDataBuf->bufSize)
            return 0;

        curPos = aboutDataBuf->buf + aboutDataBuf->itr;
        memcpy(curPos, analysis->devicePaths.values[i].element, analysis->devicePaths.values[i].elemSize);
        aboutDataBuf->itr += analysis->devicePaths.values[i].elemSize + 1;

        desc[i].type = (DeviceType)atoi(analysis->deviceTypes.values[i].element);
        desc[i].objectpath = curPos;
    }

    //void *nullDesc = &desc[i];
    //memcpy(&propertyStoreDefaultValues[17], &desc, sizeof(void*));
    return 1;
}

const CDM_AboutDataBuf CDM_CreateAboutDataFromXml(const char *aboutData)
{
    static ABOUT_ANALYSIS analysis;
    static ArrayToPropertyStoreMap mapping[] = {
        // 0 Device Id
        // 1 App Id
        {&analysis.deviceNames, 2},
        {&analysis.languages, 3},
        {&analysis.appNames, 4},
        {&analysis.descriptions, 5},
        {&analysis.manufacturers, 6},
        {&analysis.deviceModels, 7},
        {&analysis.manufactureDates, 8},
        {&analysis.softwareVersions, 9},
        // 10 is ajVersion
        {&analysis.hardwareVersions, 11},
        {&analysis.supportUrls, 12},
        {&analysis.countries, 13},
        {&analysis.corporateBrands, 14},
        {&analysis.productBrands, 15},
        {&analysis.locations, 16},
    };

    int bufSize = (int)strlen(aboutData);
    AboutDataBuilder aboutDataBuf;
    char *languagesArrayStart;
    char *deviceTypesArrayStart;
    int numArrays;

    int propertyStoreArraySize;
    int supportedLanguagesArraySize;
    int deviceTypeArraySize;

    int totalArraysSize;

    memset(&analysis, 0, sizeof(ABOUT_ANALYSIS));
    if (!PreparseXML(aboutData, bufSize, &analysis))
        return NULL;

    numArrays = countArraysWithEntries(mapping, (sizeof(mapping) / sizeof(ArrayToPropertyStoreMap)));
    propertyStoreArraySize = (numArrays + 1) * sizeof(void*);
    supportedLanguagesArraySize = (analysis.languages.numElements + 1) * sizeof(void*);
    deviceTypeArraySize = (analysis.numDevices + 1) * sizeof(DeviceTypeDescription);
    totalArraysSize = propertyStoreArraySize + supportedLanguagesArraySize + deviceTypeArraySize;

    analysis.dataSize += numArrays * sizeof(void*) + totalArraysSize;
    aboutDataBuf.buf = malloc(analysis.dataSize);
    memset(aboutDataBuf.buf, 0, analysis.dataSize);

    aboutDataBuf.bufSize = analysis.dataSize;
    aboutDataBuf.itr = totalArraysSize;

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

    return aboutDataBuf.buf;

ERROR:
    free(aboutDataBuf.buf);
    return NULL;
}

void CDM_DestroyAboutData(CDM_AboutDataBuf aboutData)
{
    if (aboutData != NULL)
        free(aboutData);
}