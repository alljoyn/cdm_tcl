/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include "HWMock/HALMock.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef AJ_Status (*FileLineHandler)(const char* line, int32_t startPos, uint32_t lineSize, uint32_t lineIndex, void* ioStruct);

typedef struct {
    HALMock* halMock;
} InitCachedPropertiesIOStruct;

typedef struct {
    const char* objPath;
    const char* intfName;
    const char* propName;
    ReadPropertyHandler readPropertyHandler;
    void* outValue;
    bool outValueInitialised;
} GetValueIOStruct;

typedef struct {
    HALMock* halMock;
} SetValueIOStruct;

typedef struct {
    HALMock* halMock;
} EmitPropertyChangedSignalsIOStruct;

static char* SkipWhiteSpaces(char* s)
{
    if (s) {
        while (isspace(*s)) {
            s++;
        }
    }
    return s;
}

static AJ_Status InitCachedPropertiesLineHandler(const char* line, int32_t startPos, uint32_t lineSize, uint32_t lineIndex, void* ioStruct)
{
    HALMock* halMock = ((InitCachedPropertiesIOStruct*)ioStruct)->halMock;

    if (lineIndex >= halMock->propertyCount) {
        return AJ_ERR_RANGE;
    }
    
    halMock->cachedProperties[lineIndex] = malloc(sizeof(HALMockProperty));
    if (!halMock->cachedProperties[lineIndex]) {
        return AJ_ERR_RESOURCES;
    }

    memset(halMock->cachedProperties[lineIndex], 0, sizeof(HALMockProperty));
    
    halMock->cachedProperties[lineIndex]->line = malloc(lineSize);
    if (!halMock->cachedProperties[lineIndex]->line) {
        free(halMock->cachedProperties[lineIndex]);
        return AJ_ERR_RESOURCES;
    }

    strncpy(halMock->cachedProperties[lineIndex]->line, line, lineSize);
    halMock->cachedProperties[lineIndex]->line[lineSize - 1] = '\0';
    
    return AJ_OK;
}

static AJ_Status GetValueLineHandler(const char* line, int32_t startPos, uint32_t lineSize, uint32_t lineIndex, void* ioStruct)
{
    GetValueIOStruct* getValueIOStruct = (GetValueIOStruct*)ioStruct;
    if (getValueIOStruct->outValueInitialised) {
        return AJ_OK;
    }

    char* tempLine = malloc(lineSize);
    if (!tempLine) {
        return AJ_ERR_RESOURCES;
    }
    strncpy(tempLine, line, lineSize);

    // Check for <object path>:<interface name>:<property name> in order.
    AJ_Status status = AJ_OK;
    char* p = tempLine;
    p = strstr(p, getValueIOStruct->objPath);
    if (!p) {
        goto CleanupTempline;
    }
    p = strstr(p, getValueIOStruct->intfName);
    if (!p) {
        goto CleanupTempline;
    }
    p = strstr(p, getValueIOStruct->propName);
    if (!p) {
        goto CleanupTempline;
    }

    // Skip property name and point to property data.
    p = strtok(p, ": ");
    p = strtok(NULL, "");
    p = SkipWhiteSpaces(p);
    if (!p) {
        goto CleanupTempline;
    }

    status = getValueIOStruct->readPropertyHandler(p, getValueIOStruct->outValue);
    if (status == AJ_OK) {
        getValueIOStruct->outValueInitialised = true;
    }

CleanupTempline:
    free(tempLine);
    return status;
}

static AJ_Status CacheValueLineHandler(const char* line, int32_t startPos, uint32_t lineSize, uint32_t lineIndex, void* ioStruct)
{
    HALMock* halMock = ((SetValueIOStruct*)ioStruct)->halMock;

    if (lineIndex >= halMock->propertyCount) {
        return AJ_ERR_RANGE;
    }
    if (!halMock->cachedProperties[lineIndex] || !halMock->cachedProperties[lineIndex]->line) {
        return AJ_ERR_NULL;
    }

    // Check keys are equal.
    char* tempLine = malloc(lineSize);
    if (!tempLine) {
        return AJ_ERR_RESOURCES;
    }
    strncpy(tempLine, line, lineSize);

    AJ_Status status = AJ_ERR_NO_MATCH;
    char* lineObjPath = strtok(tempLine, ": ");
    if (!lineObjPath) {
        goto CleanupTempline;
    }
    char* lineIntfName = strtok(NULL, ": ");
    if (!lineIntfName) {
        goto CleanupTempline;
    }
    char* linePropName = strtok(NULL, ": ");
    if (!linePropName) {
        goto CleanupTempline;
    }
    char* lineValue = strtok (NULL, "");
    lineValue = SkipWhiteSpaces(lineValue);
    if (!lineValue) {
        goto CleanupTempline;
    }

    // Check if value has changed.
    char* p = halMock->cachedProperties[lineIndex]->line;
    p = strstr(p, lineObjPath);
    if (!p) {
        goto CleanupTempline;
    }
    p = strstr(p, lineIntfName);
    if (!p) {
        goto CleanupTempline;
    }
    p = strstr(p, linePropName);
    if (!p) {
        goto CleanupTempline;
    }

    p = strstr(p, ":");
    p++;  // Skip past colon.
    char* cachedValue = SkipWhiteSpaces(p);
    if (!cachedValue) {
        goto CleanupTempline;
    }

    // Replace the cached property line if value changed.
    if (strcmp(lineValue, cachedValue) != 0) {
        free(halMock->cachedProperties[lineIndex]->line);
        halMock->cachedProperties[lineIndex]->line = malloc(lineSize);
        if (!halMock->cachedProperties[lineIndex]->line) {
            goto CleanupTempline;
        }

        strncpy(halMock->cachedProperties[lineIndex]->line, line, lineSize);
        halMock->cachedProperties[lineIndex]->line[lineSize - 1] = '\0';
    }

    status = AJ_OK;
    
CleanupTempline:
    free(tempLine);
    return status;
}

static AJ_Status EmitPropertyChangedSignalsLineHandler(const char* line, int32_t startPos, uint32_t lineSize, uint32_t lineIndex, void* ioStruct)
{
    HALMock* halMock = ((EmitPropertyChangedSignalsIOStruct*)ioStruct)->halMock;

    if (lineIndex >= halMock->propertyCount) {
        return AJ_ERR_RANGE;
    }
    if (!halMock->cachedProperties[lineIndex] || !halMock->cachedProperties[lineIndex]->line) {
        return AJ_ERR_NULL;
    }

    // Check keys are equal.
    char* tempLine = malloc(lineSize);
    if (!tempLine) {
        return AJ_ERR_RESOURCES;
    }
    strncpy(tempLine, line, lineSize);

    AJ_Status status = AJ_ERR_NO_MATCH;
    char* lineObjPath = strtok(tempLine, ": ");
    if (!lineObjPath) {
        goto TempLineCleanup;
    }
    char* lineIntfName = strtok(NULL, ": ");
    if (!lineIntfName) {
        goto TempLineCleanup;
    }
    char* linePropName = strtok(NULL, ": ");
    if (!linePropName) {
        goto TempLineCleanup;
    }
    char* lineValue = strtok (NULL, "");
    lineValue = SkipWhiteSpaces(lineValue);
    if (!lineValue) {
        goto TempLineCleanup;
    }

    // Check if value has changed.
    char* p = halMock->cachedProperties[lineIndex]->line;
    p = strstr(p, lineObjPath);
    if (!p) {
        goto TempLineCleanup;
    }
    p = strstr(p, lineIntfName);
    if (!p) {
        goto TempLineCleanup;
    }
    p = strstr(p, linePropName);
    if (!p) {
        goto TempLineCleanup;
    }

    p = strstr(p, ":");
    p++;  // Skip past colon.
    char* cachedValue = SkipWhiteSpaces(p);
    if (!cachedValue) {
        goto TempLineCleanup;
    }

    status = AJ_OK;
    
    // Replace the cached property line if value changed.
    if (strcmp(lineValue, cachedValue) != 0) {
        free(halMock->cachedProperties[lineIndex]->line);
        halMock->cachedProperties[lineIndex]->line = malloc(lineSize);
        if (!halMock->cachedProperties[lineIndex]->line) {
            status = AJ_ERR_RESOURCES;
            goto TempLineCleanup;
        }

        strncpy(halMock->cachedProperties[lineIndex]->line, line, lineSize);
        halMock->cachedProperties[lineIndex]->line[lineSize - 1] = '\0';

        // Notify that property has changed.
        PropertyChangedCallback propertyChangedCallback = halMock->cachedProperties[lineIndex]->propertyChangedCallback;
        if (propertyChangedCallback) {
            status = propertyChangedCallback(halMock->busAttachment, lineObjPath, lineValue);
        }
    }
    
TempLineCleanup:
    free(tempLine);
    return status;
}

static int32_t FindNextOccurrenceOfChar(FILE* readableFile, char c)
{
    int32_t pos = -1;

    if (readableFile) {
        int32_t oldFilePos = ftell(readableFile);
        pos = oldFilePos;
        int32_t currentChar;
        while ((currentChar = fgetc(readableFile)) != EOF) {
            if ((char)currentChar == c) {
                break;
            }
            pos++;
        }

        // Reset EOF flag and revert back to old position in file.
        rewind(readableFile);
        fseek(readableFile, oldFilePos, SEEK_SET);
    }

    return pos;
}

static AJ_Status ReadFilePerLine(HALMock* halMock, FileLineHandler fileLineHandler, void* ioStruct, uint32_t* linesRead)
{
    AJ_Status status = AJ_OK;

    if (!halMock || !halMock->hwFileName) {
        return AJ_ERR_INVALID;
    }

    FILE* hwMockFile = fopen(halMock->hwFileName, "r");

    if (hwMockFile) {
        uint32_t lineIndex = 0;

        while (!feof(hwMockFile)) {
            int32_t startOfLine = ftell(hwMockFile);
            int32_t endOfLine = FindNextOccurrenceOfChar(hwMockFile, '\n');
            if (endOfLine == -1) {                  // Exit if no newline.
                status = AJ_ERR_NO_MATCH;
                break;
            } else if (endOfLine == startOfLine) {  // Skip past newline from previous iteration.
                fgetc(hwMockFile);
                continue;
            }

            int32_t lineSize = (endOfLine - startOfLine) + 1;    // Includes newline character.
            char* line = malloc(lineSize);

            if (!line) {
                status = AJ_ERR_RESOURCES;
                break;
            }

            bool eofReached = (fgets(line, lineSize, hwMockFile) == NULL);  // Read the line.
            if (!eofReached) {
                line[lineSize - 1] = '\0';   // Replace newline with null terminator.
                if (fileLineHandler) {
                    status = fileLineHandler(line, startOfLine, lineSize, lineIndex, ioStruct);
                }
                lineIndex++;
            }

            free(line);

            if (eofReached || status != AJ_OK) {
                break;
            }
        }

        fclose(hwMockFile);

        if (linesRead) {
            *linesRead = lineIndex;
        }
    } else {
        printf("HW mock file '%s' not found!\n", halMock->hwFileName);
        status = AJ_ERR_INVALID;
    }

    return status;
}

AJ_Status HALMock_GetValue(HALMock* halMock, const char* objPath, const char* intfName, const char* propName, ReadPropertyHandler readPropertyHandler, void* outValue)
{
    if (!halMock || !halMock->hwFileName || !objPath || !intfName || !propName || !readPropertyHandler || !outValue) {
        return AJ_ERR_INVALID;
    }

    GetValueIOStruct ioStruct = { objPath, intfName, propName, readPropertyHandler, outValue };
    return ReadFilePerLine(halMock, GetValueLineHandler, &ioStruct, NULL);
}

static int32_t GetPropertyIndex(HALMockProperty** properties, int32_t propertyCount, const char* objPath, const char* intfName, const char* propName)
{
    int32_t index = -1;

    if (properties) {
        for (int32_t i = 0; i < propertyCount; i++) {
            if (properties[i]) {
                if (HALMockProperty_MatchesKey(properties[i], objPath, intfName, propName)) {
                    index = i;
                    break;
                }
            }
        }
    }

    return index;
}

AJ_Status HALMock_SetValue(HALMock* halMock, const char* objPath, const char* intfName, const char* propName, WritePropertyHandler writePropertyHandler, const void* value, uint32_t numValues)
{
    AJ_Status status = AJ_OK;

    if (!halMock || !halMock->hwFileName || !halMock->cachedProperties || !objPath || !intfName || !propName || !writePropertyHandler || !value) {
        return AJ_ERR_INVALID;
    }

    SetValueIOStruct ioStruct = { halMock };
    status = ReadFilePerLine(halMock, CacheValueLineHandler, &ioStruct, NULL);
    if (status != AJ_OK) {
        return status;
    }

    int32_t index = GetPropertyIndex(halMock->cachedProperties, halMock->propertyCount, objPath, intfName, propName);
    if (index == -1) {
        return AJ_ERR_NO_MATCH;
    }

    int32_t charsWritten = -1;
    status = writePropertyHandler(value, numValues, NULL, 0, &charsWritten);
    if (status != AJ_OK) {
        return status;
    }
    if (charsWritten < 0) {
        return AJ_ERR_FAILURE;
    }
    charsWritten++;  // Add 1 character because writePropertyHandler also writes null terminator.

    free(halMock->cachedProperties[index]->line);

    // Allocate for key of the format "objPath:intfName:propName: formatData\0".
    uint32_t totalLineSize = strlen(objPath) + strlen(intfName) + strlen(propName) + 4 + charsWritten;
    halMock->cachedProperties[index]->line = malloc(totalLineSize);
    if (!halMock->cachedProperties[index]->line) {
        return AJ_ERR_RESOURCES;
    }

    int32_t totalKeySize = sprintf(halMock->cachedProperties[index]->line, "%s:%s:%s: ", objPath, intfName, propName);
    if (totalKeySize < 0) {
        return AJ_ERR_FAILURE;
    }

    // Move ahead past the formatted line key.
    status = writePropertyHandler(value, numValues, (halMock->cachedProperties[index]->line + totalKeySize), charsWritten, &charsWritten);
    if (status != AJ_OK) {
        return status;
    }
    if (charsWritten < 0) {
        return AJ_ERR_FAILURE;
    }

    halMock->cachedProperties[index]->line[totalLineSize - 1] = '\0';

    // Write cached properties to file.
    FILE* hwMockFile = fopen(halMock->hwFileName, "w");

    if (hwMockFile) {
        uint32_t lastPropertyIndex = halMock->propertyCount - 1;
        for (uint32_t i = 0; i < lastPropertyIndex; i++) {
            if (halMock->cachedProperties[i] && halMock->cachedProperties[i]->line) {
                fputs(halMock->cachedProperties[i]->line, hwMockFile);
                fputc('\n', hwMockFile);
            }
        }
        if (halMock->cachedProperties[lastPropertyIndex] && halMock->cachedProperties[lastPropertyIndex]->line) {
            fputs(halMock->cachedProperties[lastPropertyIndex]->line, hwMockFile);
        }

        fclose(hwMockFile);

        /*if (linesRead) {
            *linesRead = lineIndex;
        }*/
    } else {
        printf("HW mock file '%s' not found!\n", halMock->hwFileName);
        status = AJ_ERR_INVALID;
    }

    return status;
}

static int32_t GetHALMockPropertyIndex(HALMock* halMock, const char* objPath, const char* intfName, const char* propName)
{
    int32_t index = -1;

    if (halMock && halMock->cachedProperties && halMock->propertyCount > 0) {
        for (int32_t i = 0; i < halMock->propertyCount; i++) {
            if (HALMockProperty_MatchesKey(halMock->cachedProperties[i], objPath, intfName, propName)) {
                index = i;
                break;
            }
        }
    }

    return index;
}

AJ_Status HALMock_SetPropertyChangedCallback(HALMock* halMock, const char* objPath, const char* intfName, const char* propName, PropertyChangedCallback propertyChangedCallback)
{
    if (!halMock || !halMock->cachedProperties || !objPath || !intfName || !propName) {
        return AJ_ERR_INVALID;
    }

    int32_t index = GetHALMockPropertyIndex(halMock, objPath, intfName, propName);
    if (index == -1) {
        return AJ_ERR_NO_MATCH;
    }
    if (!halMock->cachedProperties[index]) {
        return AJ_ERR_NULL;
    }
    
    halMock->cachedProperties[index]->propertyChangedCallback = propertyChangedCallback;

    return AJ_OK;
}

AJ_Status HALMock_EmitPropertyChangedSignals(HALMock* halMock)
{
    if (!halMock || !halMock->busAttachment || !halMock->hwFileName || !halMock->cachedProperties) {
        return AJ_ERR_INVALID;
    }

    EmitPropertyChangedSignalsIOStruct ioStruct = { halMock };
    return ReadFilePerLine(halMock, EmitPropertyChangedSignalsLineHandler, &ioStruct, NULL);
}

static AJ_Status ReadFileIntoCachedProperties(HALMock* halMock)
{
    if (!halMock || !halMock->hwFileName || halMock->cachedProperties) {
        return AJ_ERR_INVALID;
    }

    uint32_t linesRead = 0;
    AJ_Status status = ReadFilePerLine(halMock, NULL, NULL, &linesRead);
    if (status != AJ_OK) {
        return status;
    }
    if (linesRead == 0) {
        return AJ_ERR_NULL;
    }

    uint32_t cachedPropertiesSize = linesRead * sizeof(HALMockProperty*);
    halMock->cachedProperties = malloc(cachedPropertiesSize);
    if (!halMock->cachedProperties) {
        return AJ_ERR_RESOURCES;
    }

    memset(halMock->cachedProperties, 0, cachedPropertiesSize);
    halMock->propertyCount = linesRead;

    InitCachedPropertiesIOStruct ioStruct = { halMock };
    return ReadFilePerLine(halMock, InitCachedPropertiesLineHandler, &ioStruct, NULL);
}

AJ_Status InitHALMock(HALMock* halMock, AJ_BusAttachment* busAttachment, const char* hwFileName)
{
    if (!halMock || !hwFileName) {
        return AJ_ERR_INVALID;
    }
    if (halMock->cachedProperties) {
        DeinitHALMock(halMock);
    }

    memset(halMock, 0, sizeof(HALMock));

    halMock->busAttachment = busAttachment;
    halMock->hwFileName = hwFileName;

    return ReadFileIntoCachedProperties(halMock);
}

void DeinitHALMock(HALMock* halMock)
{
    if (halMock->cachedProperties) {
        for (uint32_t i = 0; i < halMock->propertyCount; i++) {
            if (halMock->cachedProperties[i]) {
                if (halMock->cachedProperties[i]->line) {
                    free(halMock->cachedProperties[i]->line);
                }
                free(halMock->cachedProperties[i]);
            }
        }
        free(halMock->cachedProperties);
        halMock->cachedProperties = NULL;
        halMock->propertyCount = 0;
    }
}