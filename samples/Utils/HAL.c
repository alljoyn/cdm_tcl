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


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include <ajtcl/aj_msg.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#include "HAL.h"
#include "StrBuf.h"

//======================================================================

static int PathExists(const char *path)
{
    struct stat st = {0};
    return stat(path, &st) != -1;
}




static int CreateDirectories(char *path)
{
    char *token = strtok(path, "/");
    char *prev = token - 1;

    while (token != NULL)
    {
        if (prev != path)
            *prev = '/';

        token = strtok(NULL, "/");

        if (!PathExists(path))
        {
            if (mkdir(path, 0700) != 0)
            {
                perror("mkdir");
                return 0;
            }
        }

        prev = token - 1;
    }

    return 1;
}



#define MAX_PATH_LEN 256
const char *ROOT = NULL;
const char *EXT = NULL;



void HAL_Init(const char *base_path, const char *ext)
{
    ROOT = base_path;
    EXT = ext;
}



void HAL_DefaultInit(void)
{
    static const char *root = "device_state";
    static const char *ext = ".state";
    ROOT = root;
    EXT = ext;
}


//======================================================================


FILE* HAL_WriteProperty(const char *objPath, const char *interface, const char *property)
{
    char path[MAX_PATH_LEN];
    size_t totalPathLen;

    if (ROOT == NULL || EXT == NULL)
    {
        fprintf(stderr, "HAL hasn't been initialised.\n");
        return 0;
    }

    totalPathLen = strlen(ROOT) + strlen(objPath) + 1 + strlen(interface) + 1 + strlen(property) + strlen(EXT);
    if (totalPathLen >= MAX_PATH_LEN)
    {
        fprintf(stderr, "Path length too long %lu >= %d\n", totalPathLen, MAX_PATH_LEN);
        return 0;
    }

    memset(path, 0, MAX_PATH_LEN);
    strcat(path, ROOT);
    strcat(path, objPath);
    strcat(path, "/");
    strcat(path, interface);

    if (!PathExists(path))
    {
        if (!CreateDirectories((char*)path))
            return 0;
    }

    strcat(path, "/");
    strcat(path, property);
    strcat(path, EXT);

    return fopen(path, "w");
}



FILE* HAL_ReadProperty(const char *objPath, const char *interface, const char *property)
{
    char path[MAX_PATH_LEN];
    size_t totalPathLen;

    if (ROOT == NULL || EXT == NULL)
    {
        fprintf(stderr, "HAL hasn't been initialised.\n");
        return 0;
    }

    totalPathLen = strlen(ROOT) + strlen(objPath) + 1 + strlen(property) + strlen(EXT);
    if (totalPathLen >= MAX_PATH_LEN)
    {
        fprintf(stderr, "Path length too long %lu >= %d\n", totalPathLen, MAX_PATH_LEN);
        return 0;
    }

    memset(path, 0, MAX_PATH_LEN);
    strcat(path, ROOT);
    strcat(path, objPath);
    strcat(path, "/");
    strcat(path, interface);
    strcat(path, "/");
    strcat(path, property);
    strcat(path, EXT);

    return fopen(path, "r");
}


//======================================================================

// Always but a blank before each token. The decoder relies on it.

void HAL_Encode_Int(FILE *fp, int64_t value)
{
    fprintf(fp, " %lld", value);
}



void HAL_Encode_UInt(FILE *fp, uint64_t value)
{
    fprintf(fp, " %llu", value);
}



void HAL_Encode_Double(FILE *fp, double value)
{
    fprintf(fp, " %.16g", value);
}



void HAL_Encode_String(FILE *fp, const char* value)
{
    // Apply basic quoting to control chars and double quote chars.

    if (!value) 
    {
        value = "";             // this suits the code generator
    }

    for (; *value; ++value)
    {
        if (*value < 32)
        {
            fprintf(fp, "\\x%02x", (uint8_t)*value);
        }
        else
        if (*value == '\\')
        {
            fprintf(fp, "\\\\");
        }
        else
        if (*value == '"')
        {
            fprintf(fp, "\\\"");
        }
        else
        {
            fprintf(fp, "%c", *value);
        }
    }
}



void HAL_Encode_OpenStruct(FILE *fp)
{
    fprintf(fp, " {");
}



void HAL_Encode_CloseStruct(FILE *fp)
{
    fprintf(fp, " }");
}



void HAL_Encode_OpenArray(FILE *fp)
{
    fprintf(fp, " [");
}



void HAL_Encode_CloseArray(FILE *fp)
{
    fprintf(fp, " ]");
}



void HAL_Encode_Array_Bool(FILE *fp, Array_Bool value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i)
    {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
}



void HAL_Encode_Array_string(FILE *fp, Array_string value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i)
    {
        HAL_Encode_String(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
}




void HAL_Encode_Array_uint8(FILE *fp, Array_uint8 value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i)
    {
        HAL_Encode_UInt(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
}



void HAL_Encode_Array_uint16(FILE *fp, Array_uint16 value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i)
    {
        HAL_Encode_UInt(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
}



void HAL_Encode_Array_uint32(FILE *fp, Array_uint32 value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i)
    {
        HAL_Encode_UInt(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
}



void HAL_Encode_Array_uint64(FILE *fp, Array_uint64 value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i)
    {
        HAL_Encode_UInt(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
}



void HAL_Encode_Array_int16(FILE *fp, Array_int16 value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i)
    {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
}



void HAL_Encode_Array_int32(FILE *fp, Array_int32 value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i)
    {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
}



void HAL_Encode_Array_int64(FILE *fp, Array_int64 value)
{
    HAL_Encode_OpenArray(fp);
    for (size_t i = 0; i < value.numElems; ++i)
    {
        HAL_Encode_Int(fp, value.elems[i]);
    }
    HAL_Encode_CloseArray(fp);
}


//======================================================================


static void skipWS(FILE* fp)
{
    for (;;)
    {
        int c = fgetc(fp);

        if (c < 0)
        {
            break;
        }

        if (!isspace(c))
        {
            // Step back one
            fseek(fp, -1, SEEK_CUR);
            break;
        }
    }
}



static void readToWS(FILE* fp, StrBuf* buf)
{
    // This leaves the file on the first WS found.
    StrBuf_Clear(buf);

    for (;;)
    {
        int c = fgetc(fp);

        if (c < 0)
        {
            break;
        }

        if (isspace(c))
        {
            break;
        }

        StrBuf_AppendChar(buf, c);
    }
}



static int lookahead(FILE* fp, const char* token)
{
    /* Read ahead looking for WS followed by the token.
       If found then the file will be left at the following
       character. If not found then the file's position will not
       be changed.

       Returns 1 for found, 0 for not found, -1 for eof.
    */
    long start = ftell(fp);
    int  result = 1;

    skipWS(fp);

    for (;;)
    {
        int c = fgetc(fp);

        if (c < 0)
        {
            result = -1;
            break;
        }

        if (c != *token)
        {
            result = 0;
            break;
        }

        ++token;
    }

    if (result != 1)
    {
        fseek(fp, start, SEEK_SET);
    }

    return result;
}



static bool decode_Int(StrBuf* buf, int64_t* out)
{
    char* endptr = NULL;
    *out = strtoll(buf->chars, &endptr, 10);
    return *buf->chars && !*endptr;
}



static bool decode_UInt(StrBuf* buf, uint64_t* out)
{
    char* endptr = NULL;
    *out = strtoull(buf->chars, &endptr, 10);
    return *buf->chars && !*endptr;
}



static bool decode_Double(StrBuf* buf, double* out)
{
    char* endptr = NULL;
    *out = strtod(buf->chars, &endptr);
    return *buf->chars && !*endptr;
}



static int decode_String(FILE* fp, char** out)
{
    // We don't free the buffer but return its chars directly to the caller
    // The return code is -1 if eof, -2 if a string was read or the code of rejected character.
    StrBuf buf;
    bool inStr = false;
    bool done  = false;
    int  result = -2;

    skipWS(fp);
    StrBuf_Init(&buf);

    while (!done)
    {
        int c = fgetc(fp);

        if (c < 0)
        {
            result = -1;
            break;
        }

        if (!inStr)
        {
            if (c == '"')
            {
                inStr = true;
            }
            else
            {
                result = c;
                done = true;
            }
        }
        else
        {
            if (c == '\\')
            {
                // A quoted " or \xFF
                char c2 = fgetc(fp);

                if (c2 == 'x')
                {
                    char h1 = fgetc(fp);
                    char h2 = fgetc(fp);

                    if (isxdigit(h1) && isxdigit(h2))
                    {
                        char hex[3];
                        unsigned char x;
                        hex[0] = h1;
                        hex[1] = h2;
                        hex[2] = 0;
                        sscanf(hex, "%hhx", &x);
                        StrBuf_AppendChar(&buf, (char)x);
                    }
                }
                else
                {
                    // For simplicity, allow anything to be quoted
                    StrBuf_AppendChar(&buf, c2);
                }
            }
            else
            if (c == '"')
            {
                result = -2;
                *out = buf.chars;
                done = true;
            }
            else
            {
                StrBuf_AppendChar(&buf, c);
            }
        }
    }

    return result;
}



int64_t HAL_Decode_Int(FILE *fp)
{
    StrBuf buf;
    int64_t value = 0;

    StrBuf_Init(&buf);
    skipWS(fp);
    readToWS(fp, &buf);

    if (!decode_Int(&buf, &value))
    {
        fprintf(stderr, "Invalid HAL integer %s\n", buf.chars);
    }

    StrBuf_Free(&buf);
    return value;
}



uint64_t HAL_Decode_UInt(FILE *fp)
{
    StrBuf buf;
    uint64_t value = 0;

    StrBuf_Init(&buf);
    skipWS(fp);
    readToWS(fp, &buf);

    if (!decode_UInt(&buf, &value))
    {
        fprintf(stderr, "Invalid HAL integer %s\n", buf.chars);
    }

    StrBuf_Free(&buf);
    return value;
}



const char* HAL_Decode_String(FILE *fp)
{
    char* out = 0;

    if (decode_String(fp, &out) != -2 )
    {
        fprintf(stderr, "Invalid HAL string\n");
    }

    if (!out)
    {
        out = strdup("");
    }

    return out;
}



double HAL_Decode_Double(FILE *fp)
{
    StrBuf buf;
    double value = 0;

    StrBuf_Init(&buf);
    skipWS(fp);
    readToWS(fp, &buf);

    if (!decode_Double(&buf, &value))
    {
        fprintf(stderr, "Invalid HAL double %s\n", buf.chars);
    }

    StrBuf_Free(&buf);
    return value;
}



void HAL_Decode_OpenStruct(FILE *fp)
{
    StrBuf buf;

    StrBuf_Init(&buf);
    skipWS(fp);
    readToWS(fp, &buf);

    if (strcmp(buf.chars, "{") != 0)
    {
        fprintf(stderr, "Missing opening brace");
    }

    StrBuf_Free(&buf);
}



void HAL_Decode_CloseStruct(FILE *fp)
{
    StrBuf buf;

    StrBuf_Init(&buf);
    skipWS(fp);
    readToWS(fp, &buf);

    if (strcmp(buf.chars, "}") != 0)
    {
        fprintf(stderr, "Missing closing brace");
    }
    StrBuf_Free(&buf);
}



void HAL_Decode_OpenArray(FILE *fp)
{
    StrBuf buf;

    StrBuf_Init(&buf);
    skipWS(fp);
    readToWS(fp, &buf);

    if (strcmp(buf.chars, "[") != 0)
    {
        fprintf(stderr, "Missing array opening");
    }
    StrBuf_Free(&buf);
}



bool HAL_Decode_TestCloseArray(FILE *fp)
{
    // Treat eof as the closing of an array
    return lookahead(fp, "]") != 0;
}



void HAL_Decode_CloseArray(FILE *fp)
{
    if (!HAL_Decode_TestCloseArray(fp))
    {
        fprintf(stderr, "Missing array closing");
    }
}



void HAL_Decode_Array_Bool(FILE *fp, Array_Bool *value)
{
    StrBuf buf;

    StrBuf_Init(&buf);
    InitArray_Bool(value, 0);
    HAL_Decode_OpenArray(fp);

    while (!feof(fp))
    {
        int64_t v = 0;

        skipWS(fp);
        readToWS(fp, &buf);

        if (strcmp(buf.chars, "]") == 0)
        {
            break;
        }

        if (decode_Int(&buf, &v))
        {
            ExtendArray_Bool(value, 1);
            value->elems[value->numElems - 1] = v;
        }
        else
        {
            fprintf(stderr, "Invalid HAL integer %s\n", buf.chars);
        }
    }
}



void HAL_Decode_Array_string(FILE *fp, Array_string *value)
{
    InitArray_string(value, 0);
    HAL_Decode_OpenArray(fp);

    while (!feof(fp))
    {
        char* out = 0;
        int code = decode_String(fp, &out);

        if (code == -2)
        {
            ExtendArray_string(value, 1);
            if (!out)
            {
                out = strdup("");
            }
            value->elems[value->numElems - 1] = out;
        }
        else
        if (code == -1)
        {
            // end of file
            fprintf(stderr, "Invalid HAL string\n");
        }
        else
        if (code == ']')
        {
            break;
        }
        else
        {
            fprintf(stderr, "Missing HAL string\n");
        }
    }
}



void HAL_Decode_Array_double(FILE *fp, Array_double *value)
{
    StrBuf buf;

    StrBuf_Init(&buf);
    InitArray_double(value, 0);
    HAL_Decode_OpenArray(fp);

    while (!feof(fp))
    {
        double v = 0;

        skipWS(fp);
        readToWS(fp, &buf);

        if (strcmp(buf.chars, "]") == 0)
        {
            break;
        }

        if (decode_Double(&buf, &v))
        {
            ExtendArray_double(value, 1);
            value->elems[value->numElems - 1] = v;
        }
        else
        {
            fprintf(stderr, "Invalid HAL double %s\n", buf.chars);
        }
    }
}



void HAL_Decode_Array_uint8(FILE *fp, Array_uint8 *value)
{
    StrBuf buf;

    StrBuf_Init(&buf);
    InitArray_uint8(value, 0);
    HAL_Decode_OpenArray(fp);

    while (!feof(fp))
    {
        uint64_t v = 0;

        skipWS(fp);
        readToWS(fp, &buf);

        if (strcmp(buf.chars, "]") == 0)
        {
            break;
        }

        if (decode_UInt(&buf, &v))
        {
            ExtendArray_uint8(value, 1);
            value->elems[value->numElems - 1] = v;
        }
        else
        {
            fprintf(stderr, "Invalid HAL integer %s\n", buf.chars);
        }
    }
}



void HAL_Decode_Array_uint16(FILE *fp, Array_uint16 *value)
{
    StrBuf buf;

    StrBuf_Init(&buf);
    InitArray_uint16(value, 0);
    HAL_Decode_OpenArray(fp);

    while (!feof(fp))
    {
        uint64_t v = 0;

        skipWS(fp);
        readToWS(fp, &buf);

        if (strcmp(buf.chars, "]") == 0)
        {
            break;
        }

        if (decode_UInt(&buf, &v))
        {
            ExtendArray_uint16(value, 1);
            value->elems[value->numElems - 1] = v;
        }
        else
        {
            fprintf(stderr, "Invalid HAL integer %s\n", buf.chars);
        }
    }
}



void HAL_Decode_Array_uint32(FILE *fp, Array_uint32 *value)
{
    StrBuf buf;

    StrBuf_Init(&buf);
    InitArray_uint32(value, 0);
    HAL_Decode_OpenArray(fp);

    while (!feof(fp))
    {
        uint64_t v = 0;

        skipWS(fp);
        readToWS(fp, &buf);

        if (strcmp(buf.chars, "]") == 0)
        {
            break;
        }

        if (decode_UInt(&buf, &v))
        {
            ExtendArray_uint32(value, 1);
            value->elems[value->numElems - 1] = v;
        }
        else
        {
            fprintf(stderr, "Invalid HAL integer %s\n", buf.chars);
        }
    }
}



void HAL_Decode_Array_uint64(FILE *fp, Array_uint64 *value)
{
    StrBuf buf;

    StrBuf_Init(&buf);
    InitArray_uint64(value, 0);
    HAL_Decode_OpenArray(fp);

    while (!feof(fp))
    {
        uint64_t v = 0;

        skipWS(fp);
        readToWS(fp, &buf);

        if (strcmp(buf.chars, "]") == 0)
        {
            break;
        }

        if (decode_UInt(&buf, &v))
        {
            ExtendArray_uint64(value, 1);
            value->elems[value->numElems - 1] = v;
        }
        else
        {
            fprintf(stderr, "Invalid HAL integer %s\n", buf.chars);
        }
    }
}



void HAL_Decode_Array_int16(FILE *fp, Array_int16 *value)
{
    StrBuf buf;

    StrBuf_Init(&buf);
    InitArray_int16(value, 0);
    HAL_Decode_OpenArray(fp);

    while (!feof(fp))
    {
        int64_t v = 0;

        skipWS(fp);
        readToWS(fp, &buf);

        if (strcmp(buf.chars, "]") == 0)
        {
            break;
        }

        if (decode_Int(&buf, &v))
        {
            ExtendArray_int16(value, 1);
            value->elems[value->numElems - 1] = v;
        }
        else
        {
            fprintf(stderr, "Invalid HAL integer %s\n", buf.chars);
        }
    }
}



void HAL_Decode_Array_int32(FILE *fp, Array_int32 *value)
{
    StrBuf buf;

    StrBuf_Init(&buf);
    InitArray_int32(value, 0);
    HAL_Decode_OpenArray(fp);

    while (!feof(fp))
    {
        int64_t v = 0;

        skipWS(fp);
        readToWS(fp, &buf);

        if (strcmp(buf.chars, "]") == 0)
        {
            break;
        }

        if (decode_Int(&buf, &v))
        {
            ExtendArray_int32(value, 1);
            value->elems[value->numElems - 1] = v;
        }
        else
        {
            fprintf(stderr, "Invalid HAL integer %s\n", buf.chars);
        }
    }
}



void HAL_Decode_Array_int64(FILE *fp, Array_int64 *value)
{
    StrBuf buf;

    StrBuf_Init(&buf);
    InitArray_int64(value, 0);
    HAL_Decode_OpenArray(fp);

    while (!feof(fp))
    {
        int64_t v = 0;

        skipWS(fp);
        readToWS(fp, &buf);

        if (strcmp(buf.chars, "]") == 0)
        {
            break;
        }

        if (decode_Int(&buf, &v))
        {
            ExtendArray_int64(value, 1);
            value->elems[value->numElems - 1] = v;
        }
        else
        {
            fprintf(stderr, "Invalid HAL integer %s\n", buf.chars);
        }
    }
}

