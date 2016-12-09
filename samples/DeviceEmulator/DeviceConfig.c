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
#include <stdlib.h>
#include <memory.h>
#include <expat.h>

#include "DeviceConfig.h"

static long ReadXMLFile(const char *filepath, char **xmlBuf)
{
    if (xmlBuf == NULL)
        return 0;

    FILE *fp = fopen(filepath, "r");
    fseek(fp, 0L, SEEK_END);
    long bufSize = ftell(fp);
    rewind(fp);

    *xmlBuf = malloc(bufSize);
    if (*xmlBuf == NULL)
        goto ALLOC_ERROR;

    long numRead = fread(*xmlBuf, 1, bufSize, fp);
    if (numRead == bufSize)
        goto DONE;

    // If this point is reached, an error occured reading the file.
    free(xmlBuf);

ALLOC_ERROR:
    bufSize = 0;

DONE:
    fclose(fp);
    return bufSize;
}

typedef struct {
    long nameLen;
    long aboutStart;
    long aboutEnd;
    long dataSize;
    long numObjects;
    long numInterfaces;

    int skip;
    int depth;
    XML_Parser parser;
} CONFIG_ANALYSIS;


typedef struct {
    DEM_Config *config;

    DEM_Object *curObject;
    DEM_Object *objectsList;
    DEM_Interface *interfacesList;

    int totalObjectsParsed;
    int totalInterfacesParsed;

    char *curDataItr;
    XML_Parser parser;
    const char *xmlBuf;

    int skip;
    int depth;
    long skipBlockStart;

    long totalSize;
} CONFIG_BUILDER;

static void Preparse_DeviceNameHandler(CONFIG_ANALYSIS *analysis, const char **attrs)
{
    if ((attrs[0] != NULL) && (strncmp(attrs[0], "name", 4) == 0) && (attrs[1] != NULL))
        analysis->dataSize += strlen(attrs[1]) + 1;
}

static void Preparse_AboutDataHandler(CONFIG_ANALYSIS *analysis)
{
    analysis->aboutStart = XML_GetCurrentByteIndex(analysis->parser);
    analysis->skip = analysis->depth;
}

static void Preparse_ObjectHandler(CONFIG_ANALYSIS *analysis, const char **attrs) {
    if ((attrs[0]!=NULL) && (strncmp(attrs[0], "path", 4)==0) && (attrs[1]!=NULL))
    {
        ++analysis->numObjects;
        analysis->dataSize += strlen(attrs[1]) + 1;
    }
}

static void Preparse_InterfaceHandler(CONFIG_ANALYSIS *analysis, const char **attrs) {
    if ((attrs[0]!=NULL) && (strncmp(attrs[0], "name", 4)==0) && (attrs[1]!=NULL))
    {
        ++analysis->numInterfaces;
        analysis->dataSize += strlen(attrs[1]) + 1;
    }
}

static void XMLCALL Preparse_StartElement(void *data, const char* name, const char **attrs)
{
    CONFIG_ANALYSIS *analysis = (CONFIG_ANALYSIS*)data;
    ++analysis->depth;

    if (strcmp(name, "DeviceEmulator") == 0)
        Preparse_DeviceNameHandler(analysis, attrs);
    else if (strcmp(name, "AboutData") == 0)
        Preparse_AboutDataHandler(analysis);
    else if (strcmp(name, "Object") == 0)
        Preparse_ObjectHandler(analysis, attrs);
    else if (strcmp(name, "Interface") == 0)
        Preparse_InterfaceHandler(analysis, attrs);
}

static void XMLCALL Preparse_EndElement(void *data, const char *name)
{
    CONFIG_ANALYSIS *analysis = (CONFIG_ANALYSIS*)data;

    if (analysis->skip == analysis->depth) {
        if (strcmp(name, "AboutData") == 0) {
            analysis->aboutEnd = XML_GetCurrentByteIndex(analysis->parser) + strlen(name) + 3;
            analysis->dataSize += (analysis->aboutEnd - analysis->aboutStart) + 1;
        }
        analysis->skip = 0;
    }

    --analysis->depth;
}

static int PreparseXML(const char *xmlBuf, long bufSize, CONFIG_ANALYSIS *analysis)
{
    int retVal = 0;
    XML_Parser xmlParser = XML_ParserCreate(NULL);
    if (!xmlParser)
    {
        fprintf(stderr, "Error create xml parser.\n");
        return 0;
    }

    analysis->dataSize = 0;
    analysis->numObjects = 0;
    analysis->numInterfaces = 0;

    analysis->depth = 0;
    analysis->skip = 0;
    analysis->parser = xmlParser;

    XML_SetUserData(xmlParser, analysis);
    XML_SetElementHandler(xmlParser, Preparse_StartElement, Preparse_EndElement);
    retVal = XML_Parse(xmlParser, xmlBuf, bufSize, 1);

    XML_ParserFree(xmlParser);
    analysis->parser = NULL;

    return retVal;
}

static void CreateConfig(const char* xmlBuf, long bufSize, CONFIG_ANALYSIS *analysis, CONFIG_BUILDER *configBuilder)
{
    long objects_list_size = sizeof(DEM_Object) * analysis->numObjects;
    long interfaces_list_size = sizeof(DEM_Interface) * analysis->numInterfaces;
    long dataStart;
    void *ptr;

    long totalSize = sizeof(DEM_Config) + objects_list_size + interfaces_list_size + analysis->dataSize;
    memset(configBuilder, 0, sizeof(CONFIG_BUILDER));

    configBuilder->config = malloc(totalSize);
    if (configBuilder->config == NULL)
        return;

    memset(configBuilder->config, 0, totalSize);

    ptr = (void*)((char*)configBuilder->config + sizeof(DEM_Config));
    configBuilder->objectsList = (DEM_Object*)ptr;
    configBuilder->config->objects = configBuilder->objectsList;

    ptr = (void*)((char*)configBuilder->objectsList + objects_list_size);
    configBuilder->interfacesList = (DEM_Interface*)ptr;

    dataStart = sizeof(DEM_Config) + objects_list_size + interfaces_list_size;

    configBuilder->curDataItr = (char*)configBuilder->config + dataStart;
    configBuilder->xmlBuf = xmlBuf;
    configBuilder->totalSize = totalSize;
}

static void Populate_DeviceNameHandler(CONFIG_BUILDER *builder, const char **attrs)
{
    long deviceNameLen;

    if ((attrs[0] != NULL) && (strncmp(attrs[0], "name", 4) == 0) && (attrs[1] != NULL)) {
        builder->config->deviceName = builder->curDataItr;
        deviceNameLen = strlen(attrs[1]);
        memcpy(builder->config->deviceName, attrs[1], deviceNameLen);
        builder->curDataItr += deviceNameLen + 1;
    }
}

static void Populate_AboutDataHandler(CONFIG_BUILDER *builder)
{
    builder->skipBlockStart = XML_GetCurrentByteIndex(builder->parser);
    builder->skip = builder->depth;
}

static void Populate_ObjectHandler(CONFIG_BUILDER *builder, const char **attrs)
{
    DEM_Object* curObj;
    long objectPathLen;

    if ((attrs[0] != NULL) && (strncmp(attrs[0], "path", 4) == 0) && (attrs[1] != NULL)) {
        curObj = &builder->objectsList[builder->totalObjectsParsed];
        builder->curObject = curObj;

        curObj->objectPath = builder->curDataItr;
        objectPathLen = strlen(attrs[1]);
        memcpy(curObj->objectPath, attrs[1], objectPathLen);
        builder->curDataItr += objectPathLen + 1;

        curObj->interfaces = &builder->interfacesList[builder->totalInterfacesParsed];

        ++builder->totalObjectsParsed;
    }
}

static void Populate_InterfaceHandler(CONFIG_BUILDER *builder, const char **attrs)
{
    DEM_Interface* curInterface;
    long InterfaceNameLen;

    if ((attrs[0] != NULL) && (strncmp(attrs[0], "name", 4) == 0) && (attrs[1] != NULL)) {
        curInterface = &builder->interfacesList[builder->totalInterfacesParsed];

        curInterface->name = builder->curDataItr;
        InterfaceNameLen = strlen(attrs[1]);
        memcpy(curInterface->name, attrs[1], InterfaceNameLen);
        builder->curDataItr += InterfaceNameLen + 1;

        ++builder->curObject->numInterfaces;
        ++builder->totalInterfacesParsed;
    }
}

static void XMLCALL Populate_StartElement(void *data, const char* name, const char **attrs)
{
    CONFIG_BUILDER *builder = (CONFIG_BUILDER*)data;
    ++builder->depth;

    if (strcmp(name, "DeviceEmulator") == 0)
        Populate_DeviceNameHandler(builder, attrs);
    else if (strcmp(name, "AboutData") == 0)
        Populate_AboutDataHandler(builder);
    else if (strcmp(name, "Object") == 0)
        Populate_ObjectHandler(builder, attrs);
    else if (strcmp(name, "Interface") == 0)
        Populate_InterfaceHandler(builder, attrs);
}

static void XMLCALL Populate_EndElement(void *data, const char *name)
{
    CONFIG_BUILDER *builder = (CONFIG_BUILDER*)data;

    if (builder->skip == builder->depth) {
        if (strcmp(name, "AboutData") == 0) {
            long aboutBlockEnd = XML_GetCurrentByteIndex(builder->parser) + strlen(name) + 3;
            long blockSize = aboutBlockEnd - builder->skipBlockStart;

            builder->config->aboutData = builder->curDataItr;
            memcpy(builder->config->aboutData, &builder->xmlBuf[builder->skipBlockStart], blockSize);
            builder->curDataItr += blockSize + 1;
        }
        builder->skip = 0;
    }

    --builder->depth;
}

static void PopulateConfig(const char* xmlBuf, long bufSize, CONFIG_BUILDER *configBuilder)
{
    int retVal = 0;
    XML_Parser xmlParser = XML_ParserCreate(NULL);
    if (!xmlParser)
    {
        fprintf(stderr, "Error create xml parser.\n");
        return;
    }

    configBuilder->parser = xmlParser;

    XML_SetUserData(xmlParser, configBuilder);
    XML_SetElementHandler(xmlParser, Populate_StartElement, Populate_EndElement);
    retVal = XML_Parse(xmlParser, xmlBuf, bufSize, 1);

    XML_ParserFree(xmlParser);
}

#include <assert.h>

DEM_Config *DEM_CreateConfig(const char *deviceXmlPath)
{
    CONFIG_ANALYSIS analysis;
    CONFIG_BUILDER configBuilder;
    int result = 0;
    char *xmlBuf;
    long bufSize = ReadXMLFile(deviceXmlPath, &xmlBuf);
    char* endPtr;

    if (bufSize == 0 || xmlBuf == NULL) {
        fprintf(stderr, "Error reading xml file.\n");
        return NULL;
    }

    result = PreparseXML(xmlBuf, bufSize, &analysis);
    if (result)
        CreateConfig(xmlBuf, bufSize, &analysis, &configBuilder);

    if (configBuilder.config == NULL)
        return NULL;

    PopulateConfig(xmlBuf, bufSize, &configBuilder);
    configBuilder.config->numObjects = configBuilder.totalObjectsParsed;

    endPtr = (char*)configBuilder.config + configBuilder.totalSize;
    assert(endPtr == configBuilder.curDataItr);

    free(xmlBuf);
    return configBuilder.config;
}

void DEM_FreeConfig(DEM_Config *config)
{
    if (config != NULL)
        free(config);
}