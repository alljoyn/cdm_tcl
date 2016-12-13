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

#ifndef ALLJOYN_CDM_ARRAY_H
#define ALLJOYN_CDM_ARRAY_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* This is the generic carrier for an array.
 * The user must know the type of the elements.
 */
typedef struct CDM_Array {
    void* elems;
    size_t numElems;
    } CDM_Array;


/*
 * Some of the automatically-generated functions will be unused.
 */
#define UNUSED_OK __attribute__((unused))


extern void Init_Array(CDM_Array* array, size_t elemSize, size_t numElems);
extern void Copy_Array(CDM_Array* array, size_t elemSize, CDM_Array* copy);
extern size_t Extend_Array(CDM_Array* array, size_t elemSize, size_t numElems);

// These structs must match CDM_Array.
#define MK_ARRAY(TYPE, NAME) typedef struct Array_ ## NAME {TYPE* elems; size_t numElems;} Array_ ## NAME; \
FREE_ARRAY(TYPE, NAME) \
INIT_ARRAY(TYPE, NAME) \
EXTEND_ARRAY(TYPE, NAME)

#define FREE_ARRAY(TYPE, NAME) extern void FreeArray_ ## NAME(Array_ ## NAME* array);
#define INIT_ARRAY(TYPE, NAME) static inline void InitArray_ ## NAME(Array_ ## NAME* array, size_t numElems){Init_Array((CDM_Array*)array, sizeof(TYPE), numElems);}
#define EXTEND_ARRAY(TYPE, NAME) static inline size_t ExtendArray_ ## NAME(Array_ ## NAME* array, size_t numElems){return Extend_Array((CDM_Array*)array, sizeof(TYPE), numElems);}

// Beware that stdbool.h defines a macro called 'bool'
#define MAKE_ARRAYS \
MK_ARRAY(bool, Bool) \
MK_ARRAY(char*, string) \
MK_ARRAY(uint8_t, uint8) \
MK_ARRAY(int16_t, int16) \
MK_ARRAY(uint16_t, uint16) \
MK_ARRAY(int32_t, int32) \
MK_ARRAY(uint32_t, uint32) \
MK_ARRAY(int64_t, int64) \
MK_ARRAY(uint64_t, uint64) \
MK_ARRAY(double, double)

MAKE_ARRAYS

// We only need some of these and strings are a special case
#define COPY_ARRAY(TYPE, NAME) static inline void CopyArray_ ## NAME(Array_ ## NAME* array, Array_ ## NAME* copy){Copy_Array((CDM_Array*)array, sizeof(TYPE), (CDM_Array*)copy);}

COPY_ARRAY(bool, Bool) \
COPY_ARRAY(uint8_t, uint8) \
COPY_ARRAY(int16_t, int16) \
COPY_ARRAY(uint16_t, uint16) \
COPY_ARRAY(int32_t, int32) \
COPY_ARRAY(uint32_t, uint32) \
COPY_ARRAY(int64_t, int64) \
COPY_ARRAY(uint64_t, uint64) \
COPY_ARRAY(double, double)

extern void CopyArray_string(Array_string* array, Array_string* copy);

#undef MK_ARRAY
#undef FREE_ARRAY
#undef INIT_ARRAY
#undef MAKE_ARRAYS

#endif //ALLJOYN_CDM_ARRAY_H