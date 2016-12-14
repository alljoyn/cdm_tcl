/******************************************************************************
 *  * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef _HAL_MOCK_H
#define _HAL_MOCK_H

#include "HALMockProperty.h"

typedef struct {
	AJ_BusAttachment* busAttachment;
	const char* hwFileName;
	HALMockProperty** cachedProperties;
	uint32_t propertyCount;
} HALMock;

typedef AJ_Status (*ReadPropertyHandler)(const char* fileData, void* outValue);
typedef AJ_Status (*WritePropertyHandler)(const void* value, uint32_t numValues, char* outFormatData, uint32_t formatDataLen, int32_t* outWrittenCount);

AJ_Status HALMock_GetValue(HALMock* halMock, const char* objPath, const char* intfName, const char* propName, ReadPropertyHandler readPropertyHandler, void* outValue);
AJ_Status HALMock_SetValue(HALMock* halMock, const char* objPath, const char* intfName, const char* propName, WritePropertyHandler writePropertyHandler, const void* value, uint32_t numValues);

AJ_Status HALMock_SetPropertyChangedCallback(HALMock* halMock, const char* objPath, const char* intfName, const char* propName, PropertyChangedCallback propertyChangedCallback);
AJ_Status HALMock_EmitPropertyChangedSignals(HALMock* halMock);

AJ_Status InitHALMock(HALMock* halMock, AJ_BusAttachment* busAttachment, const char* hwFileName);
void DeinitHALMock(HALMock* halMock);

#endif /* _HAL_MOCK_H */