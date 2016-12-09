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

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "HWMock/HALMockCommonHandlers.h"

static char* SkipWhiteSpaces(char* s)
{
    if (s) {
        while (isspace(*s)) {
            s++;
        }
    }
    return s;
}

static AJ_Status ConvertToAJStatus(int32_t sscanfRetVal)
{
    return (sscanfRetVal != 0 && sscanfRetVal != EOF) ? AJ_OK : AJ_ERR_INVALID;
}

/**
 * Read handlers.
 */
AJ_Status HALMock_ReadBoolHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    return ConvertToAJStatus(sscanf(fileData, "%u", (bool*)outValue));
}

AJ_Status HALMock_ReadUint8Handler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    return ConvertToAJStatus(sscanf(fileData, "%u", (uint8_t*)outValue));
}

AJ_Status HALMock_ReadUint16Handler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    return ConvertToAJStatus(sscanf(fileData, "%u", (uint16_t*)outValue));
}

AJ_Status HALMock_ReadUint32Handler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    return ConvertToAJStatus(sscanf(fileData, "%u", (uint32_t*)outValue));
}

AJ_Status HALMock_ReadUint64Handler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    return ConvertToAJStatus(sscanf(fileData, "%u", (uint64_t*)outValue));
}

AJ_Status HALMock_ReadInt16Handler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    return ConvertToAJStatus(sscanf(fileData, "%d", (int16_t*)outValue));
}

AJ_Status HALMock_ReadInt32Handler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    return ConvertToAJStatus(sscanf(fileData, "%d", (int32_t*)outValue));
}

AJ_Status HALMock_ReadInt64Handler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    return ConvertToAJStatus(sscanf(fileData, "%d", (int64_t*)outValue));
}

AJ_Status HALMock_ReadDoubleHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    return ConvertToAJStatus(sscanf(fileData, "%lf", (double*)outValue));
}

AJ_Status HALMock_ReadStringLengthHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    *(uint32_t*)outValue = strlen(fileData);
    return AJ_OK;
}

AJ_Status HALMock_ReadStringHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    strcpy((char*)outValue, fileData);
    ((char*)outValue)[strlen(fileData)] = '\0';
    return AJ_OK;
}

AJ_Status HALMock_ReadArrayLengthHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    return ConvertToAJStatus(sscanf(fileData, "(count:%u)", (uint32_t*)outValue));
}

AJ_Status HALMock_ReadBoolArrayHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    
    const char* p = fileData;
    uint32_t arrayLength;
    int32_t offset;
    AJ_Status status = ConvertToAJStatus(sscanf(p, "(count:%u)[%n", &arrayLength, &offset));
    if (status != AJ_OK) {
        return status;
    }
    if (arrayLength == 0) {
        return AJ_OK;
    }
    p += offset;
    
    for (size_t i = 0; i < (arrayLength - 1); i++) {
        status = ConvertToAJStatus(sscanf(p, "%u, %n", &((bool*)outValue)[i], &offset));
        if (status != AJ_OK) {
            return status;
        }
        p += offset;
    }
    
    return ConvertToAJStatus(sscanf(p, "%u", &((bool*)outValue)[arrayLength - 1]));
}

AJ_Status HALMock_ReadUint8ArrayHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    
    const char* p = fileData;
    uint32_t arrayLength;
    int32_t offset;
    AJ_Status status = ConvertToAJStatus(sscanf(p, "(count:%u)[%n", &arrayLength, &offset));
    if (status != AJ_OK) {
        return status;
    }
    if (arrayLength == 0) {
        return AJ_OK;
    }
    p += offset;
    
    for (size_t i = 0; i < (arrayLength - 1); i++) {
        status = ConvertToAJStatus(sscanf(p, "%u, %n", &((uint8_t*)outValue)[i], &offset));
        if (status != AJ_OK) {
            return status;
        }
        p += offset;
    }
    
    return ConvertToAJStatus(sscanf(p, "%u", &((uint8_t*)outValue)[arrayLength - 1]));
}

AJ_Status HALMock_ReadUint16ArrayHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    
    const char* p = fileData;
    uint32_t arrayLength;
    int32_t offset;
    AJ_Status status = ConvertToAJStatus(sscanf(p, "(count:%u)[%n", &arrayLength, &offset));
    if (status != AJ_OK) {
        return status;
    }
    if (arrayLength == 0) {
        return AJ_OK;
    }
    p += offset;
    
    for (size_t i = 0; i < (arrayLength - 1); i++) {
        status = ConvertToAJStatus(sscanf(p, "%u, %n", &((uint16_t*)outValue)[i], &offset));
        if (status != AJ_OK) {
            return status;
        }
        p += offset;
    }
    
    return ConvertToAJStatus(sscanf(p, "%u", &((uint16_t*)outValue)[arrayLength - 1]));
}

AJ_Status HALMock_ReadUint32ArrayHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    
    const char* p = fileData;
    uint32_t arrayLength;
    int32_t offset;
    AJ_Status status = ConvertToAJStatus(sscanf(p, "(count:%u)[%n", &arrayLength, &offset));
    if (status != AJ_OK) {
        return status;
    }
    if (arrayLength == 0) {
        return AJ_OK;
    }
    p += offset;
    
    for (size_t i = 0; i < (arrayLength - 1); i++) {
        status = ConvertToAJStatus(sscanf(p, "%u, %n", &((uint32_t*)outValue)[i], &offset));
        if (status != AJ_OK) {
            return status;
        }
        p += offset;
    }
    
    return ConvertToAJStatus(sscanf(p, "%u", &((uint32_t*)outValue)[arrayLength - 1]));
}

AJ_Status HALMock_ReadUint64ArrayHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    
    const char* p = fileData;
    uint32_t arrayLength;
    int32_t offset;
    AJ_Status status = ConvertToAJStatus(sscanf(p, "(count:%u)[%n", &arrayLength, &offset));
    if (status != AJ_OK) {
        return status;
    }
    if (arrayLength == 0) {
        return AJ_OK;
    }
    p += offset;
    
    for (size_t i = 0; i < (arrayLength - 1); i++) {
        status = ConvertToAJStatus(sscanf(p, "%u, %n", &((uint64_t*)outValue)[i], &offset));
        if (status != AJ_OK) {
            return status;
        }
        p += offset;
    }
    
    return ConvertToAJStatus(sscanf(p, "%u", &((uint64_t*)outValue)[arrayLength - 1]));
}

AJ_Status HALMock_ReadInt16ArrayHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    
    const char* p = fileData;
    uint32_t arrayLength;
    int32_t offset;
    AJ_Status status = ConvertToAJStatus(sscanf(p, "(count:%u)[%n", &arrayLength, &offset));
    if (status != AJ_OK) {
        return status;
    }
    if (arrayLength == 0) {
        return AJ_OK;
    }
    p += offset;
    
    for (size_t i = 0; i < (arrayLength - 1); i++) {
        status = ConvertToAJStatus(sscanf(p, "%d, %n", &((int16_t*)outValue)[i], &offset));
        if (status != AJ_OK) {
            return status;
        }
        p += offset;
    }
    
    return ConvertToAJStatus(sscanf(p, "%d", &((int16_t*)outValue)[arrayLength - 1]));
}

AJ_Status HALMock_ReadInt32ArrayHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    
    const char* p = fileData;
    uint32_t arrayLength;
    int32_t offset;
    AJ_Status status = ConvertToAJStatus(sscanf(p, "(count:%u)[%n", &arrayLength, &offset));
    if (status != AJ_OK) {
        return status;
    }
    if (arrayLength == 0) {
        return AJ_OK;
    }
    p += offset;
    
    for (size_t i = 0; i < (arrayLength - 1); i++) {
        status = ConvertToAJStatus(sscanf(p, "%d, %n", &((int32_t*)outValue)[i], &offset));
        if (status != AJ_OK) {
            return status;
        }
        p += offset;
    }
    
    return ConvertToAJStatus(sscanf(p, "%d", &((int32_t*)outValue)[arrayLength - 1]));
}

AJ_Status HALMock_ReadInt64ArrayHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    
    const char* p = fileData;
    uint32_t arrayLength;
    int32_t offset;
    AJ_Status status = ConvertToAJStatus(sscanf(p, "(count:%u)[%n", &arrayLength, &offset));
    if (status != AJ_OK) {
        return status;
    }
    if (arrayLength == 0) {
        return AJ_OK;
    }
    p += offset;
    
    for (size_t i = 0; i < (arrayLength - 1); i++) {
        status = ConvertToAJStatus(sscanf(p, "%d, %n", &((int64_t*)outValue)[i], &offset));
        if (status != AJ_OK) {
            return status;
        }
        p += offset;
    }
    
    return ConvertToAJStatus(sscanf(p, "%d", &((int64_t*)outValue)[arrayLength - 1]));
}

AJ_Status HALMock_ReadDoubleArrayHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    
    const char* p = fileData;
    uint32_t arrayLength;
    int32_t offset;
    AJ_Status status = ConvertToAJStatus(sscanf(p, "(count:%u)[%n", &arrayLength, &offset));
    if (status != AJ_OK) {
        return status;
    }
    if (arrayLength == 0) {
        return AJ_OK;
    }
    p += offset;
    
    for (size_t i = 0; i < (arrayLength - 1); i++) {
        status = ConvertToAJStatus(sscanf(p, "%lf, %n", &((double*)outValue)[i], &offset));
        if (status != AJ_OK) {
            return status;
        }
        p += offset;
    }
    
    return ConvertToAJStatus(sscanf(p, "%lf", &((double*)outValue)[arrayLength - 1]));
}

AJ_Status HALMock_ReadPerStringLengthsInArrayHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    
    const char* p = fileData;
    uint32_t arrayLength;
    int32_t offset;
    AJ_Status status = ConvertToAJStatus(sscanf(p, "(count:%u)[%n", &arrayLength, &offset));
    if (status != AJ_OK) {
        return status;
    }
    if (arrayLength == 0) {
        return AJ_OK;
    }
    p += offset;
    
    uint32_t remainingLength = strlen(p);
    char* remainingData = malloc(remainingLength + 1);
    if (!remainingData) {
        return AJ_ERR_RESOURCES;
    }
    strncpy(remainingData, p, remainingLength + 1);
    remainingData[remainingLength] = '\0';
    
    char* remainingIt = remainingData;
    for (uint32_t i = 0; i < arrayLength; i++) {
        char* strtokInput = (i == 0) ? remainingIt : NULL;
        remainingIt = strtok(strtokInput, ",]");
        ((uint32_t*)outValue)[i] = strlen(remainingIt);
        
        remainingIt = SkipWhiteSpaces(remainingIt);
    }
    
    free(remainingData);
    
    return status;
}

AJ_Status HALMock_ReadStringArrayHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }
    
    char** outStringArray = ((StringArrayHandlerInput*)outValue)->outStringArray;
    if (!outStringArray) {
        return AJ_ERR_NULL;
    }
    
    const char* p = fileData;
    uint32_t arrayLength;
    int32_t offset;
    AJ_Status status = ConvertToAJStatus(sscanf(p, "(count:%u)[%n", &arrayLength, &offset));
    if (status != AJ_OK) {
        return status;
    }
    if (arrayLength == 0) {
        return AJ_OK;
    }
    p += offset;
    
    uint32_t remainingLength = strlen(p);
    char* remainingData = malloc(remainingLength + 1);
    if (!remainingData) {
        return AJ_ERR_RESOURCES;
    }
    strncpy(remainingData, p, remainingLength + 1);
    remainingData[remainingLength] = '\0';
    
    char* remainingIt = remainingData;
    for (uint32_t i = 0; i < arrayLength; i++) {
        char* strtokInput = (i == 0) ? remainingIt : NULL;
        remainingIt = strtok(strtokInput, ",]");
        
        uint32_t remainingItLen = strlen(remainingIt);
        strncpy(outStringArray[i], remainingIt, remainingItLen + 1);
        outStringArray[i][remainingItLen] = '\0';
        
        remainingIt = SkipWhiteSpaces(remainingIt);
    }
    
    free(remainingData);
    
    return status;
}


/**
 * Write handlers.
 */
AJ_Status HALMock_WriteDoubleHandler(const void* value, uint32_t numValues, char* outFormatData, uint32_t formatDataLen, int32_t* outWrittenCount)
{
    int32_t numCharsWritten = snprintf(outFormatData, formatDataLen, "%.3lf", *(double*)value);
    if (outWrittenCount) {
    	*outWrittenCount = numCharsWritten;
    }
    return AJ_OK;
}
