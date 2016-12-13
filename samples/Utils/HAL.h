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

#ifndef ALLJOYN_HAL_H
#define ALLJOYN_HAL_H

#include <ajtcl/cdm/utils/CDM_Array.h>

//======================================================================

typedef int (*HAL_ReaderFunc)(FILE *fp, const char*, void*);

void HAL_Init(const char *base_path, const char *ext);
void HAL_DefaultInit(void);

// This opens the file for writing. The caller must close it.
FILE* HAL_WriteProperty(const char *objPath, const char *interface, const char *property);

// This opens the file for reading. The caller must close it.
FILE* HAL_ReadProperty(const char *objPath, const char *interface, const char *property);

//======================================================================

extern void HAL_Encode_Int(FILE *fp, int64_t value);
extern void HAL_Encode_UInt(FILE *fp, uint64_t value);
extern void HAL_Encode_String(FILE *fp, const char* value);
extern void HAL_Encode_Double(FILE *fp, double value);

extern void HAL_Encode_OpenStruct(FILE *fp);
extern void HAL_Encode_CloseStruct(FILE *fp);
extern void HAL_Encode_OpenArray(FILE *fp);
extern void HAL_Encode_CloseArray(FILE *fp);

extern void HAL_Encode_Array_Bool(FILE *fp, Array_Bool value);
extern void HAL_Encode_Array_string(FILE *fp, Array_string value);

extern void HAL_Encode_Array_uint8(FILE *fp, Array_uint8 value);
extern void HAL_Encode_Array_uint16(FILE *fp, Array_uint16 value);
extern void HAL_Encode_Array_uint32(FILE *fp, Array_uint32 value);
extern void HAL_Encode_Array_uint64(FILE *fp, Array_uint64 value);

extern void HAL_Encode_Array_int16(FILE *fp, Array_int16 value);
extern void HAL_Encode_Array_int32(FILE *fp, Array_int32 value);
extern void HAL_Encode_Array_int64(FILE *fp, Array_int64 value);



// These leave the file at the next character after the token.
extern int64_t HAL_Decode_Int(FILE *fp);
extern uint64_t HAL_Decode_UInt(FILE *fp);
extern double HAL_Decode_Double(FILE *fp);

// Ownership of the string is transferred to the caller
extern const char* HAL_Decode_String(FILE *fp);

// These just skip the delimiters
extern void HAL_Decode_OpenStruct(FILE *fp);
extern void HAL_Decode_CloseStruct(FILE *fp);
extern void HAL_Decode_OpenArray(FILE *fp);
extern void HAL_Decode_CloseArray(FILE *fp);
extern bool HAL_Decode_TestCloseArray(FILE *fp);

extern void HAL_Decode_Array_Bool(FILE *fp, Array_Bool *value);
extern void HAL_Decode_Array_string(FILE *fp, Array_string *value);
extern void HAL_Decode_Array_double(FILE *fp, Array_double *value);

extern void HAL_Decode_Array_uint8(FILE *fp, Array_uint8 *value);
extern void HAL_Decode_Array_uint16(FILE *fp, Array_uint16 *value);
extern void HAL_Decode_Array_uint32(FILE *fp, Array_uint32 *value);
extern void HAL_Decode_Array_uint64(FILE *fp, Array_uint64 *value);

extern void HAL_Decode_Array_int16(FILE *fp, Array_int16 *value);
extern void HAL_Decode_Array_int32(FILE *fp, Array_int32 *value);
extern void HAL_Decode_Array_int64(FILE *fp, Array_int64 *value);

//======================================================================
#endif //ALLJOYN_HAL_H