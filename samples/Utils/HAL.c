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


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#include <ajtcl/aj_msg.h>
#include <ajtcl/cdm/utils/CdmArray.h>
#include <ajtcl/cdm/utils/StrBuf.h>

#include "HAL.h"
#include "FileIO.h"


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
    static const char *ext = "";
    ROOT = root;
    EXT = ext;
}


bool HAL_WritePropertyXml(const char *objPath, const char *interface, const char *property, const char* xml, bool force)
{
    char path[MAX_PATH_LEN];
    size_t totalPathLen;

    if (ROOT == NULL || EXT == NULL)
    {
        fprintf(stderr, "HAL hasn't been initialised.\n");
        return false;
    }

    totalPathLen = strlen(ROOT) + strlen(objPath) + 1 + strlen(interface) + 1 + strlen(property) + strlen(EXT);
    if (totalPathLen >= MAX_PATH_LEN)
    {
        fprintf(stderr, "Path length too long %lu >= %d\n", totalPathLen, MAX_PATH_LEN);
        return false;
    }

    memset(path, 0, MAX_PATH_LEN);
    strcat(path, ROOT);
    strcat(path, objPath);
    strcat(path, "/");
    strcat(path, interface);

    if (!PathExists(path))
    {
        if (!CreateDirectories((char*)path))
        {
            return false;
        }
    }

    strcat(path, "/");
    strcat(path, property);
    strcat(path, EXT);

    if (!force)
    {
        /* See if it exists first. */
        FILE* fp = fopen(path, "r");

        if (fp)
        {
            fclose(fp);
            return false;
        }
    }

    FILE* fp = fopen(path, "w");

    if (fp)
    {
        fputs(xml, fp);

        size_t l = strlen(xml);

        if (l == 0 || xml[l - 1] != '\n')
        {
            fputs("\n", fp);
        }

        fclose(fp);
    }

    return true;
}



bool HAL_WritePropertyElem(const char *objPath, const char *interface, const char *property, const Element* elem)
{
    const char* xml = BSXML_Generate(elem);
    bool ok = HAL_WritePropertyXml(objPath, interface, property, xml, true);
    free((void*)xml);
    return ok;
}



Element* HAL_ReadProperty(const char *objPath, const char *interface, const char *property)
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

    StrBuf buf;
    StrBuf_Init(&buf);
    Element* elem = NULL;

    if (ReadFile(path, &buf))
    {
        elem = BSXML_GetRoot(buf.chars);
    }

    StrBuf_Free(&buf);
    return elem;
}


Element* HAL_Encode_Bool(bool value, Element* parent)
{
    Element* scalar = BSXML_NewElement("scalar", parent);
    BSXML_AddAttribute(scalar, "type", "bool");
    BSXML_AddAttribute(scalar, "value", value? "true" : "false");
    return scalar;
}



static Element* encodeScalar(const char* num, const char* type, Element* parent)
{
    Element* scalar = BSXML_NewElement("scalar", parent);
    BSXML_AddAttribute(scalar, "type", type);
    BSXML_AddAttribute(scalar, "value", num);
    return scalar;
}



Element* HAL_Encode_Int(int64_t value, Element* parent)
{
    char nbuf[60];
    sprintf(nbuf, " %lld", value);
    return encodeScalar(nbuf, "signed", parent);
}



Element* HAL_Encode_UInt(uint64_t value, Element* parent)
{
    char nbuf[60];
    sprintf(nbuf, " %llu", value);
    return encodeScalar(nbuf, "unsigned", parent);
}



Element* HAL_Encode_Double(double value, Element* parent)
{
    char nbuf[60];
    sprintf(nbuf, " %.16g", value);
    return encodeScalar(nbuf, "double", parent);
}



Element* HAL_Encode_String(const char* value, Element* parent)
{
    return encodeScalar(value, "string", parent);
}



Element* HAL_Encode_Array_Bool(Array_Bool value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    size_t i = 0;
    for (; i < value.numElems; ++i)
    {
        HAL_Encode_Bool(value.elems[i], array);
    }
    return array;
}



Element* HAL_Encode_Array_string(Array_string value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    size_t i = 0;
    for (; i < value.numElems; ++i)
    {
        HAL_Encode_String(value.elems[i], array);
    }
    return array;
}




Element* HAL_Encode_Array_uint8(Array_uint8 value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    size_t i = 0;
    for (; i < value.numElems; ++i)
    {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}



Element* HAL_Encode_Array_uint16(Array_uint16 value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    size_t i = 0;
    for (; i < value.numElems; ++i)
    {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}



Element* HAL_Encode_Array_uint32(Array_uint32 value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    size_t i = 0;
    for (; i < value.numElems; ++i)
    {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}



Element* HAL_Encode_Array_uint64(Array_uint64 value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    size_t i = 0;
    for (; i < value.numElems; ++i)
    {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}



Element* HAL_Encode_Array_int16(Array_int16 value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    size_t i = 0;
    for (; i < value.numElems; ++i)
    {
        HAL_Encode_Int(value.elems[i], array);
    }
    return array;
}



Element* HAL_Encode_Array_int32(Array_int32 value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    size_t i = 0;
    for (; i < value.numElems; ++i)
    {
        HAL_Encode_Int(value.elems[i], array);
    }
    return array;
}



Element* HAL_Encode_Array_int64(Array_int64 value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    size_t i = 0;
    for (; i < value.numElems; ++i)
    {
        HAL_Encode_Int(value.elems[i], array);
    }
    return array;
}

bool HAL_Decode_Bool(Element* elem)
{
    bool v = 0;

    if (strcmp(elem->name, "scalar") == 0)
    {
        const char* atype  = BSXML_GetAttribute(elem, "type");
        const char* avalue = BSXML_GetAttribute(elem, "value");

        if (strcmp(atype, "bool") == 0)
        {
            v = strcmp(avalue, "true") == 0;
        }
    }

    return v;
}



int64_t HAL_Decode_Int(Element* elem)
{
    int64_t v = 0;

    if (strcmp(elem->name, "scalar") == 0)
    {
        const char* atype  = BSXML_GetAttribute(elem, "type");
        const char* avalue = BSXML_GetAttribute(elem, "value");

        if (strcmp(atype, "signed") == 0)
        {
            v = strtoll(avalue, NULL, 10);
        }
    }

    return v;
}



uint64_t HAL_Decode_UInt(Element* elem)
{
    uint64_t v = 0;

    if (strcmp(elem->name, "scalar") == 0)
    {
        const char* atype  = BSXML_GetAttribute(elem, "type");
        const char* avalue = BSXML_GetAttribute(elem, "value");

        if (strcmp(atype, "unsigned") == 0)
        {
            v = strtoull(avalue, NULL, 10);
        }
    }

    return v;
}



double HAL_Decode_Double(Element* elem)
{
    double v = 0;

    if (strcmp(elem->name, "scalar") == 0)
    {
        const char* atype  = BSXML_GetAttribute(elem, "type");
        const char* avalue = BSXML_GetAttribute(elem, "value");

        if (strcmp(atype, "double") == 0)
        {
            v = strtod(avalue, NULL);
        }
    }

    return v;
}



const char* HAL_Decode_String(Element* elem)
{
    const char* v = 0;

    if (strcmp(elem->name, "scalar") == 0)
    {
        const char* atype  = BSXML_GetAttribute(elem, "type");
        const char* avalue = BSXML_GetAttribute(elem, "value");

        if (strcmp(atype, "string") == 0)
        {
            v = strdup(avalue);
        }
    }

    return v;
}



void HAL_Decode_Array_Bool(Element* elem, Array_Bool *array)
{
    if (strcmp(elem->name, "array") == 0)
    {
        size_t i = 0;
        array->numElems = elem->numChildren;
        array->elems = malloc(sizeof(bool) * array->numElems);

        for (; i < elem->numChildren; ++i)
        {
            Element* child = elem->children[i];
            array->elems[i] = (bool)(HAL_Decode_Int(child) & 1);
        }
    }
}



void HAL_Decode_Array_string(Element* elem, Array_string *array)
{
    if (strcmp(elem->name, "array") == 0)
    {
        size_t i = 0;
        array->numElems = elem->numChildren;
        array->elems = malloc(sizeof(char*) * array->numElems);

        for (; i < elem->numChildren; ++i)
        {
            Element* child = elem->children[i];
            array->elems[i] = (char*)HAL_Decode_String(child);
        }
    }
}



void HAL_Decode_Array_double(Element* elem, Array_double *array)
{
    if (strcmp(elem->name, "array") == 0)
    {
        size_t i = 0;
        array->numElems = elem->numChildren;
        array->elems = malloc(sizeof(double) * array->numElems);

        for (; i < elem->numChildren; ++i)
        {
            Element* child = elem->children[i];
            array->elems[i] = HAL_Decode_Double(child);
        }
    }
}



void HAL_Decode_Array_uint8(Element* elem, Array_uint8 *array)
{
    if (strcmp(elem->name, "array") == 0)
    {
        size_t i = 0;
        array->numElems = elem->numChildren;
        array->elems = malloc(sizeof(uint8_t) * array->numElems);

        for (; i < elem->numChildren; ++i)
        {
            Element* child = elem->children[i];
            array->elems[i] = (uint8_t)HAL_Decode_UInt(child);
        }
    }
}



void HAL_Decode_Array_uint16(Element* elem, Array_uint16 *array)
{
    if (strcmp(elem->name, "array") == 0)
    {
        size_t i = 0;
        array->numElems = elem->numChildren;
        array->elems = malloc(sizeof(uint16_t) * array->numElems);

        for (; i < elem->numChildren; ++i)
        {
            Element* child = elem->children[i];
            array->elems[i] = (uint16_t)HAL_Decode_UInt(child);
        }
    }
}



void HAL_Decode_Array_uint32(Element* elem, Array_uint32 *array)
{
    if (strcmp(elem->name, "array") == 0)
    {
        size_t i = 0;
        array->numElems = elem->numChildren;
        array->elems = malloc(sizeof(uint32_t) * array->numElems);

        for (; i < elem->numChildren; ++i)
        {
            Element* child = elem->children[i];
            array->elems[i] = (uint32_t)HAL_Decode_UInt(child);
        }
    }
}



void HAL_Decode_Array_uint64(Element* elem, Array_uint64 *array)
{
    if (strcmp(elem->name, "array") == 0)
    {
        size_t i = 0;
        array->numElems = elem->numChildren;
        array->elems = malloc(sizeof(uint64_t) * array->numElems);

        for (; i < elem->numChildren; ++i)
        {
            Element* child = elem->children[i];
            array->elems[i] = (uint64_t)HAL_Decode_UInt(child);
        }
    }
}



void HAL_Decode_Array_int16(Element* elem, Array_int16 *array)
{
    if (strcmp(elem->name, "array") == 0)
    {
        size_t i = 0;
        array->numElems = elem->numChildren;
        array->elems = malloc(sizeof(int16_t) * array->numElems);

        for (; i < elem->numChildren; ++i)
        {
            Element* child = elem->children[i];
            array->elems[i] = (int16_t)HAL_Decode_UInt(child);
        }
    }
}



void HAL_Decode_Array_int32(Element* elem, Array_int32 *array)
{
    if (strcmp(elem->name, "array") == 0)
    {
        size_t i = 0;
        array->numElems = elem->numChildren;
        array->elems = malloc(sizeof(int32_t) * array->numElems);

        for (; i < elem->numChildren; ++i)
        {
            Element* child = elem->children[i];
            array->elems[i] = (int32_t)HAL_Decode_UInt(child);
        }
    }
}



void HAL_Decode_Array_int64(Element* elem, Array_int64 *array)
{
    if (strcmp(elem->name, "array") == 0)
    {
        size_t i = 0;
        array->numElems = elem->numChildren;
        array->elems = malloc(sizeof(int64_t) * array->numElems);

        for (; i < elem->numChildren; ++i)
        {
            Element* child = elem->children[i];
            array->elems[i] = (int64_t)HAL_Decode_UInt(child);
        }
    }
}
