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

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "HWMock/interfaces/operation/ChannelHALMockHandlers.h"

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

AJ_Status ChannelHALMock_ReadChannelInfoRecordLengthsHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }

    ReadChannelInfoRecordLengthsHandlerInput* lengthsHandlerInput = (ReadChannelInfoRecordLengthsHandlerInput*)outValue;
    if (!lengthsHandlerInput || !lengthsHandlerInput->channelInfoRecordLengths) {
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
    if (remainingData) {
        strncpy(remainingData, p, remainingLength + 1);
        remainingData[remainingLength] = '\0';

        char** subStringPosList = malloc(arrayLength * sizeof(char*));
        if (subStringPosList) {
            memset(subStringPosList, 0, arrayLength * sizeof(char*));

            char* remainingIt = remainingData;
            for (uint32_t i = 0; i < arrayLength; i++) {
                remainingIt = strstr(remainingIt, "{");
                if (remainingIt) {
                    remainingIt++;  // Skip past the {
                    subStringPosList[i] = remainingIt;

                    remainingIt = strstr(remainingIt, "}");
                } else {
                    break;
                }
            }

            remainingIt = remainingData;
            uint32_t currentStruct = 0;
            for (uint32_t i = 0; i < arrayLength; i++) {
                if (subStringPosList[i]) {
                    char* strtokInput = (i == 0) ? subStringPosList[i] : NULL;
                    uint32_t channelIDLen;
                    uint32_t channelNumberLen;
                    uint32_t channelNameLen;

                    remainingIt = strtok(strtokInput, ",}");
                    channelIDLen = strlen(remainingIt);
                    remainingIt = SkipWhiteSpaces(remainingIt);

                    remainingIt = strtok(NULL, ",}");
                    channelNumberLen = strlen(remainingIt);
                    remainingIt = SkipWhiteSpaces(remainingIt);

                    remainingIt = strtok(NULL, ",}");
                    channelNameLen = strlen(remainingIt);
                    remainingIt = SkipWhiteSpaces(remainingIt);

                    // Store the lengths of each string for structs in the given range.
                    if (i >= lengthsHandlerInput->startingRecord && currentStruct < lengthsHandlerInput->numRecords) {
                        lengthsHandlerInput->channelInfoRecordLengths[currentStruct].channelIDLen = channelIDLen;
                        lengthsHandlerInput->channelInfoRecordLengths[currentStruct].channelNumberLen = channelNumberLen;
                        lengthsHandlerInput->channelInfoRecordLengths[currentStruct].channelNameLen = channelNameLen;
                        currentStruct++;
                    }
                }
            }

            free(subStringPosList);
        } else {
            status = AJ_ERR_RESOURCES;
        }
        
        free(remainingData);
    } else {
        status = AJ_ERR_RESOURCES;
    }
    
    return status;
}

AJ_Status ChannelHALMock_ReadChannelInfoRecordArrayHandler(const char* fileData, void* outValue)
{
    if (!fileData || !outValue) {
        return AJ_ERR_NULL;
    }

    ReadChannelInfoRecordArrayHandlerInput* arrayHandlerInput = (ReadChannelInfoRecordArrayHandlerInput*)outValue;
    if (!arrayHandlerInput || !arrayHandlerInput->listOfChannelInfoRecords) {
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
    if (remainingData) {
        strncpy(remainingData, p, remainingLength + 1);
        remainingData[remainingLength] = '\0';

        char** subStringPosList = malloc(arrayLength * sizeof(char*));
        if (subStringPosList) {
            memset(subStringPosList, 0, arrayLength * sizeof(char*));
        
            char* remainingIt = remainingData;
            for (uint32_t i = 0; i < arrayLength; i++) {
                remainingIt = strstr(remainingIt, "{");
                if (remainingIt) {
                    remainingIt++;  // Skip past the {
                    subStringPosList[i] = remainingIt;

                    remainingIt = strstr(remainingIt, "}");
                } else {
                    break;
                }
            }

            remainingIt = remainingData;
            uint32_t currentStruct = 0;
            for (uint32_t i = 0; i < arrayLength; i++) {
                if (subStringPosList[i]) {
                    char* strtokInput = (i == 0) ? subStringPosList[i] : NULL;
                    char* channelID;
                    char* channelNumber;
                    char* channelName;

                    remainingIt = strtok(strtokInput, ",}");
                    channelID = remainingIt;
                    remainingIt = SkipWhiteSpaces(remainingIt);

                    remainingIt = strtok(NULL, ",}");
                    channelNumber = remainingIt;
                    remainingIt = SkipWhiteSpaces(remainingIt);

                    remainingIt = strtok(NULL, ",}");
                    channelName = remainingIt;
                    remainingIt = SkipWhiteSpaces(remainingIt);

                    // Store the lengths of each string for structs in the given range.
                    if (i >= arrayHandlerInput->startingRecord && currentStruct < arrayHandlerInput->numRecords) {
                        uint32_t strLength;

                        if (channelID) {
                            strLength = strlen(channelID);
                            if (arrayHandlerInput->listOfChannelInfoRecords[currentStruct].channelID) {
                                strncpy(arrayHandlerInput->listOfChannelInfoRecords[currentStruct].channelID, channelID, strLength + 1);
                                arrayHandlerInput->listOfChannelInfoRecords[currentStruct].channelID[strLength] = '\0';
                            }
                        }

                        if (channelNumber) {
                            strLength = strlen(channelNumber);
                            if (arrayHandlerInput->listOfChannelInfoRecords[currentStruct].channelNumber) {
                                strncpy(arrayHandlerInput->listOfChannelInfoRecords[currentStruct].channelNumber, channelNumber, strLength + 1);
                                arrayHandlerInput->listOfChannelInfoRecords[currentStruct].channelNumber[strLength] = '\0';
                            }
                        }

                        if (channelName) {
                            strLength = strlen(channelName);
                            if (arrayHandlerInput->listOfChannelInfoRecords[currentStruct].channelName) {
                                strncpy(arrayHandlerInput->listOfChannelInfoRecords[currentStruct].channelName, channelName, strLength + 1);
                                arrayHandlerInput->listOfChannelInfoRecords[currentStruct].channelName[strLength] = '\0';
                            }
                        }

                        currentStruct++;
                    }
                }
            }

            free(subStringPosList);
        } else {
            status = AJ_ERR_RESOURCES;
        }
        
        free(remainingData);
    } else {
        status = AJ_ERR_RESOURCES;
    }
    
    return status;
}