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

#include <ajtcl/cdm/utils/CDM_Array.h>
#include <string.h>

#define MK_FREE_FUNC(TYPE, NAME) void FreeArray_ ## NAME(struct Array_ ## NAME* array) \
{\
    free(array->elems);\
}\

#define MK_FREE_FUNCS \
MK_FREE_FUNC(bool, Bool) \
MK_FREE_FUNC(uint8_t, uint8) \
MK_FREE_FUNC(int16_t, int16) \
MK_FREE_FUNC(uint16_t, uint16) \
MK_FREE_FUNC(int32_t, int32) \
MK_FREE_FUNC(uint32_t, uint32) \
MK_FREE_FUNC(int64_t, int64) \
MK_FREE_FUNC(uint64_t, uint64) \
MK_FREE_FUNC(double, double)

MK_FREE_FUNCS

void FreeArray_string(Array_string* array)
{
    for (size_t i = 0; i < array->numElems; ++i)
    {
        free(array->elems[i]);
    }

    free(array->elems);
}



void Init_Array(CDM_Array* array, size_t elemSize, size_t numElems)
{
    if (numElems == 0) {
        array->elems = NULL;
    } else {
        array->elems = calloc(numElems, elemSize);
    }

    array->numElems = numElems;
}



void Copy_Array(CDM_Array* array, size_t elemSize, CDM_Array* copy)
{
    if (array->elems) {
        copy->elems = malloc(array->numElems * elemSize);
        memcpy(copy->elems, array->elems, array->numElems * elemSize);
    } else {
        copy->elems = NULL;
    }

    copy->numElems = array->numElems;
}



void CopyArray_string(Array_string* array, Array_string* copy)
{
    if (array->elems) {
        copy->elems = malloc(array->numElems * sizeof(char*));
        for (size_t i = 0; i < array->numElems; ++i) {
            copy->elems[i] = strdup(array->elems[i]);
        }
    } else {
        copy->elems = NULL;
    }

    copy->numElems = array->numElems;
}



size_t Extend_Array(CDM_Array* array, size_t elemSize, size_t numElems)
{
    size_t old = array->numElems;
    array->elems = realloc(array->elems, elemSize * (numElems + array->numElems));
    array->numElems += numElems;
    return old;
}