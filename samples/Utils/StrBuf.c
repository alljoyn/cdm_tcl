/******************************************************************************
 *  *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#include <string.h>
#include "StrBuf.h"


static void need(StrBuf* buf, size_t amount)
{
    // Allow for the NUL
    // This doesn't advance numChars
    int need = (buf->numChars + amount + 1) - buf->capacity;

    if (need > 0)
    {
        size_t newCap = buf->capacity;

        if (need < 32)
        {
            need = 32;
        }

        newCap += need;
        buf->chars = (char*)realloc(buf->chars, newCap);
        buf->capacity = newCap;
    }
}



void StrBuf_Init(StrBuf* buf)
{
    buf->chars = NULL;
    buf->numChars = 0;
    buf->capacity = 0;
    need(buf, 31);
    buf->chars[0] = 0;
}


void StrBuf_Free(StrBuf* buf)
{
    free(buf->chars);
}



void StrBuf_AppendChar(StrBuf* buf, char c)
{
    need(buf, buf->numChars + 1);
    buf->chars[buf->numChars] = c;
    ++buf->numChars;
    buf->chars[buf->numChars] = 0;
}



void StrBuf_AppendStr(StrBuf* buf, const char* s)
{
    StrBuf_AppendStrNum(buf, s, strlen(s));
}



void StrBuf_AppendStrNum(StrBuf* buf, const char* s, size_t n)
{
    need(buf, buf->numChars + n);
    memcpy(&buf->chars[buf->numChars], s, n);
    buf->numChars += n;
    buf->chars[buf->numChars] = 0;
}



const char* StrBuf_FetchClear(StrBuf* buf)
{
    const char* text = buf->chars;
    StrBuf_Init(buf);
    return text;
}



const char* StrBuf_FetchFree(StrBuf* buf)
{
    const char* text = buf->chars;
    buf->chars = NULL;
    return text;
}



void StrBuf_Clear(StrBuf* buf)
{
    if (buf->chars)
    {
        buf->chars[0] = 0;
        buf->numChars = 0;
    }
}

