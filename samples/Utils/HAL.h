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

#ifndef ALLJOYN_HAL_H
#define ALLJOYN_HAL_H

typedef int (*HAL_WriterFunc)(FILE *fp, void*);
typedef int (*HAL_ReaderFunc)(FILE *fp, const char*, void*);

void HAL_Init(const char *base_path, const char *ext);
void HAL_DefaultInit();

int HAL_WriteProperty(const char *objPath, const char *interface, const char *property, HAL_WriterFunc write, void *data);
int HAL_ReadProperty(const char *objPath, const char *interface, const char *property, HAL_ReaderFunc read, void *out);

int HAL_writeBool(FILE *fp, void* data);
int HAL_writeInt(FILE *fp, void* data);

int HAL_readBool(FILE *fp, const char *buf, void *data);
int HAL_readInt(FILE *fp, const char *buf, void *data);

#endif //ALLJOYN_HAL_H
