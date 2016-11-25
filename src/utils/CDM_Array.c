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

#include <ajtcl/cdm/utils/CDM_Array.h>

#define MK_ARRAY(TYPE, NAME) void Free_ ## NAME(Array_ ## NAME* array){free(array->elems));

#define MAKE_ARRAYS \
MK_ARRAY(bool, Bool) \
MK_ARRAY(uint8_t, uint8) \
MK_ARRAY(int16_t, int16) \
MK_ARRAY(uint16_t, uint16) \
MK_ARRAY(int32_t, int32) \
MK_ARRAY(uint32_t, uint32) \
MK_ARRAY(int64_t, int64) \
MK_ARRAY(uint64_t, uint64) \
MK_ARRAY(double, double)

void Free_string(Array_string* array)
{
    for (size_t i = 0; i < array->numElems; ++i)
    {
        free(array->elems[i]);
    }

    free(array->elems);
}