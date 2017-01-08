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

#include "Serialize.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


Element* Serialize_PutBool(Element* parent, bool value)
{
    Element* scalar = BSXML_NewElement("scalar", parent);
    BSXML_AddAttribute(scalar, "type", "bool");
    BSXML_AddAttribute(scalar, "value", value? "true" : "false");
    return scalar;
}



bool Serialize_GetBool(Element* element)
{
    if (strcmp(element->name, "scalar") == 0)
    {
        const char* type  = BSXML_GetAttribute(element, "type");
        const char* value = BSXML_GetAttribute(element, "value");

        if (strcmp(type, "bool") == 0)
        {
            return strcmp(value, "true") == 0;
        }
    }

    return false;
}



Element* Serializer_PutDouble(Element* parent, double value)
{
    char buf[60];
    sprintf(buf, "%.16g", value);

    Element* scalar = BSXML_NewElement("scalar", parent);
    BSXML_AddAttribute(scalar, "type", "double");
    BSXML_AddAttribute(scalar, "value", buf);
    return scalar;
}



double Serializer_GetDouble(Element* element)
{
    if (strcmp(element->name, "scalar") == 0)
    {
        const char* type  = BSXML_GetAttribute(element, "type");
        const char* value = BSXML_GetAttribute(element, "value");

        if (strcmp(type, "double") == 0)
        {
            return strtod(value, NULL);
        }
    }

    return 0;
}



Element* Serializer_PutString(Element* parent, const char* value)
{
    Element* scalar = BSXML_NewElement("scalar", parent);
    const char* escaped = BSXML_EscapeXml(value);

    BSXML_AddAttribute(scalar, "type", "string");
    BSXML_AddAttribute(scalar, "value", escaped);
    free((void*)escaped);

    return scalar;
}



const char* Serializer_GetString(Element* element)
{
    if (strcmp(element->name, "scalar") == 0)
    {
        const char* type  = BSXML_GetAttribute(element, "type");
        const char* value = BSXML_GetAttribute(element, "value");

        if (strcmp(type, "string") == 0)
        {
            return BSXML_UnescapeXml(value);
        }
    }

    return strdup("");
}



Element* Serializer_PutInt64(Element* parent, int64_t value)
{
    char buf[60];
    sprintf(buf, "%lld", value);

    Element* scalar = BSXML_NewElement("scalar", parent);
    BSXML_AddAttribute(scalar, "type", "signed");
    BSXML_AddAttribute(scalar, "value", buf);
    return scalar;
}



int64_t Serializer_GetInt64(Element* element)
{
    if (strcmp(element->name, "scalar") == 0)
    {
        const char* type  = BSXML_GetAttribute(element, "type");
        const char* value = BSXML_GetAttribute(element, "value");

        if (strcmp(type, "signed") == 0)
        {
            return strtoll(value, NULL, 10);
        }
    }

    return 0;
}



Element* Serializer_PutUInt64(Element* parent, uint64_t value)
{
    char buf[60];
    sprintf(buf, "%llu", value);

    Element* scalar = BSXML_NewElement("scalar", parent);
    BSXML_AddAttribute(scalar, "type", "unsigned");
    BSXML_AddAttribute(scalar, "value", buf);
    return scalar;
}



uint64_t Serializer_GetUInt64(Element* element)
{
    if (strcmp(element->name, "scalar") == 0)
    {
        const char* type  = BSXML_GetAttribute(element, "type");
        const char* value = BSXML_GetAttribute(element, "value");

        if (strcmp(type, "unsigned") == 0)
        {
            return strtoull(value, NULL, 10);
        }
    }

    return 0;
}



Element* Serializer_PutInt32(Element* parent, int32_t value)
{
    char buf[60];
    sprintf(buf, "%d", value);

    Element* scalar = BSXML_NewElement("scalar", parent);
    BSXML_AddAttribute(scalar, "type", "signed");
    BSXML_AddAttribute(scalar, "value", buf);
    return scalar;
}



int32_t Serializer_GetInt32(Element* element)
{
    if (strcmp(element->name, "scalar") == 0)
    {
        const char* type  = BSXML_GetAttribute(element, "type");
        const char* value = BSXML_GetAttribute(element, "value");

        if (strcmp(type, "signed") == 0)
        {
            return strtol(value, NULL, 10);
        }
    }

    return 0;
}



Element* Serializer_PutUInt32(Element* parent, uint32_t value)
{
    char buf[60];
    sprintf(buf, "%u", value);

    Element* scalar = BSXML_NewElement("scalar", parent);
    BSXML_AddAttribute(scalar, "type", "unsigned");
    BSXML_AddAttribute(scalar, "value", buf);
    return scalar;
}



uint32_t Serializer_GetUInt32(Element* element)
{
    if (strcmp(element->name, "scalar") == 0)
    {
        const char* type  = BSXML_GetAttribute(element, "type");
        const char* value = BSXML_GetAttribute(element, "value");

        if (strcmp(type, "unsigned") == 0)
        {
            return strtoul(value, NULL, 10);
        }
    }

    return 0;
}



Element* Serializer_PutUInt8(Element* parent, uint8_t value)
{
    char buf[60];
    sprintf(buf, "%hhu", value);

    Element* scalar = BSXML_NewElement("scalar", parent);
    BSXML_AddAttribute(scalar, "type", "unsigned");
    BSXML_AddAttribute(scalar, "value", buf);
    return scalar;
}



uint8_t Serializer_GetUInt8(Element* element)
{
    if (strcmp(element->name, "scalar") == 0)
    {
        const char* type  = BSXML_GetAttribute(element, "type");
        const char* value = BSXML_GetAttribute(element, "value");

        if (strcmp(type, "unsigned") == 0)
        {
            return strtoul(value, NULL, 10);
        }
    }

    return 0;
}