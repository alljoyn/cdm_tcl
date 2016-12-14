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

#ifndef ALLJOYN_SERIALIZE_H
#define ALLJOYN_SERIALIZE_H

#include <stdint.h>
#include <stdbool.h>
#include "BSXML.h"

//======================================================================

extern Element* Serialize_PutBool(Element* parent, bool value);
extern bool Serialize_GetBool(Element* element);

extern Element* Serializer_PutDouble(Element* parent, double value);
extern double Serializer_GetDouble(Element* element);

extern Element* Serializer_PutString(Element* parent, const char* value);
extern const char* Serializer_GetString(Element* element);

extern Element* Serializer_PutInt64(Element* parent, int64_t value);
extern int64_t Serializer_GetInt64(Element* element);

extern Element* Serializer_PutUInt64(Element* parent, uint64_t value);
extern uint64_t Serializer_GetUInt64(Element* element);

extern Element* Serializer_PutInt32(Element* parent, int32_t value);
extern int32_t Serializer_GetInt32(Element* element);

extern Element* Serializer_PutUInt32(Element* parent, uint32_t value);
extern uint32_t Serializer_GetUInt32(Element* element);

extern Element* Serializer_PutUInt8(Element* parent, uint8_t value);
extern uint8_t Serializer_GetUInt8(Element* element);

//======================================================================
#endif // ALLJOYN_SERIALIZE_H