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

#ifndef ALLJOYN_STRBUF_H
#define ALLJOYN_STRBUF_H

#include <ajtcl/cdm/utils/CDM_Array.h>

typedef struct {
    char* chars;                /* never NULL, always NUL-terminated */
    size_t numChars;
    size_t capacity;
    } StrBuf;


void StrBuf_Init(StrBuf* buf);

/**
 * This frees the string within the buffer, not the buffer itself.
 */
void StrBuf_Free(StrBuf* buf);


void StrBuf_AppendChar(StrBuf* buf, char c);
void StrBuf_AppendStr(StrBuf* buf, const char* s);
void StrBuf_AppendStrNum(StrBuf* buf, const char* s, size_t numChars);


/**
 * Retrieve the text of the buffer leaving it empty.
 * The caller must free the text.
 */
const char* StrBuf_FetchClear(StrBuf* buf);

/**
 * Retrieve the text of the buffer leaving it in an unitialised state.
 * The caller must free the text.
 */
const char* StrBuf_FetchFree(StrBuf* buf);


void StrBuf_Clear(StrBuf* buf);

#endif /*ALLJOYN_STRBUF_H*/
