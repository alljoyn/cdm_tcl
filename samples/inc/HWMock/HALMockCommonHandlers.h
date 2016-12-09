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

#ifndef _HAL_MOCK_COMMON_HANDLERS_H
#define _HAL_MOCK_COMMON_HANDLERS_H

#include <stdio.h>
#include <ajtcl/aj_status.h>
#include <ajtcl/aj_target.h>

typedef struct {
    char** outStringArray;
} StringArrayHandlerInput;

/**
 * Read handlers.
 */
AJ_Status HALMock_ReadBoolHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadUint8Handler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadUint16Handler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadUint32Handler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadUint64Handler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadInt16Handler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadInt32Handler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadInt64Handler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadDoubleHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadStringLengthHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadStringHandler(const char* fileData, void* outValue);

AJ_Status HALMock_ReadArrayLengthHandler(const char* fileData, void* outValue);

AJ_Status HALMock_ReadBoolArrayHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadUint8ArrayHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadUint16ArrayHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadUint32ArrayHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadUint64ArrayHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadInt16ArrayHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadInt32ArrayHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadInt64ArrayHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadDoubleArrayHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadPerStringLengthsInArrayHandler(const char* fileData, void* outValue);
AJ_Status HALMock_ReadStringArrayHandler(const char* fileData, void* outValue);

/**
 * Write handlers.
 */
AJ_Status HALMock_WriteDoubleHandler(const void* value, uint32_t numValues, char* outFormatData, uint32_t formatDataLen, int32_t* outWrittenCount);

#endif /* _HAL_MOCK_COMMON_HANDLERS_H */