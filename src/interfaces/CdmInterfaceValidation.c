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

#include <math.h>
#include <ajtcl/cdm/interfaces/CdmInterfaceValidation.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define MK_CLAMP_FUNC(TYPE, NAME) \
static TYPE mapValueToStepIncrement_##NAME(TYPE value, TYPE step) \
{ \
    double stepValue = (double)step; \
    double div = (value / stepValue); \
    return (TYPE)(floor(div + 0.5) * stepValue); \
} \
\
TYPE clamp_##NAME(TYPE value, TYPE min, TYPE max, TYPE step) \
{ \
    TYPE v = (step == 0) ? value : mapValueToStepIncrement_##NAME(value, step); \
    return MIN(MAX(v, min), max); \
}

MK_CLAMP_FUNC(uint8_t, uint8)
MK_CLAMP_FUNC(uint16_t, uint16)

static double mapValueToStepIncrement_double(double value, double step)
{
    double stepValue = step;
    double div = (value / stepValue);
    return floor(div + 0.5) * stepValue;
}

double clamp_double(double value, double min, double max, double step)
{
    double v = (step < 0.00001 && step > -0.00001) ? value : mapValueToStepIncrement_double(value, step);
    return MIN(MAX(v, min), max);
}

#define MK_VALUEIN_ARRAY_FUNC(TYPE, NAME) \
int valueIn_Array_##NAME(TYPE value, Array_##NAME *values) \
{ \
    size_t i=0; \
    if (values == NULL) \
        return 0; \
\
    for(; i < values->numElems; ++i) \
    { \
        if (values->elems[i] == value) \
            return 1; \
    } \
    return 0; \
}

MK_VALUEIN_ARRAY_FUNC(uint8_t, uint8)
MK_VALUEIN_ARRAY_FUNC(ClimateControlMode_Mode, ClimateControlMode_Mode)

int valueIn_Array_AudioVideoInput_InputSource(uint16_t value, Array_AudioVideoInput_InputSource *values)
{
    size_t i=0;
    if (values == NULL)
        return 0;

    for(; i < values->numElems; ++i)
    {
        if (value == values->elems[i].id)
            return 1;
    }
    return 0;
}

int valueIn_Array_Channel_ChannelInfoRecord(char const* value, Array_Channel_ChannelInfoRecord *values)
{
    size_t i=0;
    if (values == NULL)
        return 0;

    for(; i < values->numElems; ++i)
    {
        if (strcmp(value, values->elems[i].channelID) == 0)
            return 1;
    }
    return 0;
}

int valueIn_Array_string(char const* value, Array_string *values)
{
    size_t i=0;
    if (values == NULL)
        return 0;

    for(; i < values->numElems; ++i)
    {
        if (strcmp(value, values->elems[i]) == 0)
            return 1;
    }
    return 0;
}