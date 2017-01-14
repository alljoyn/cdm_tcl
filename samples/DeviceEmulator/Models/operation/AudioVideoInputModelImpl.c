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
#include <stdint.h>
#include <stdbool.h>

#include "AudioVideoInputModelImpl.h"
#include "../../../Utils/HAL.h"



static Element* HAL_Encode_AudioVideoInput_InputSource(AudioVideoInput_InputSource value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_AudioVideoInput_InputSource(AudioVideoInput_InputSource value, Element* parent)
{
    Element* struc = BSXML_NewElement("struct", parent);
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "id");
        HAL_Encode_UInt(value.id, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "sourceType");
        HAL_Encode_UInt(value.sourceType, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "signalPresence");
        HAL_Encode_UInt(value.signalPresence, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "portNumber");
        HAL_Encode_UInt(value.portNumber, field);
    }
    {
        Element* field = BSXML_NewElement("field", struc);
        BSXML_AddAttribute(field, "name", "friendlyName");
        HAL_Encode_String(value.friendlyName, field);
    }
    return struc;
}



static void HAL_Decode_AudioVideoInput_InputSource(Element* elem, AudioVideoInput_InputSource* value) UNUSED_OK;

static void HAL_Decode_AudioVideoInput_InputSource(Element* elem, AudioVideoInput_InputSource* value)
{
    if (strcmp(elem->name, "struct") == 0 && elem->numChildren == 5) {
        value->id = HAL_Decode_UInt(elem->children[0]->children[0]);
        value->sourceType = HAL_Decode_UInt(elem->children[1]->children[0]);
        value->signalPresence = HAL_Decode_UInt(elem->children[2]->children[0]);
        value->portNumber = HAL_Decode_UInt(elem->children[3]->children[0]);
        value->friendlyName = HAL_Decode_String(elem->children[4]->children[0]);
    }
}



static Element* HAL_Encode_Array_AudioVideoInput_InputSource(Array_AudioVideoInput_InputSource value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_AudioVideoInput_InputSource(Array_AudioVideoInput_InputSource value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_AudioVideoInput_InputSource(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_AudioVideoInput_InputSource(Element* elem, Array_AudioVideoInput_InputSource* value) UNUSED_OK;

static void HAL_Decode_Array_AudioVideoInput_InputSource(Element* elem, Array_AudioVideoInput_InputSource* value)
{
    InitArray_AudioVideoInput_InputSource(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_AudioVideoInput_InputSource(value, 1);
            HAL_Decode_AudioVideoInput_InputSource(elem->children[i], &value->elems[j]);
        }
    }
}


static Element* HAL_Encode_AudioVideoInput_SourceType(AudioVideoInput_SourceType value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_AudioVideoInput_SourceType(AudioVideoInput_SourceType value, Element* parent)
{
    return HAL_Encode_UInt(value, parent);
}



static void HAL_Decode_AudioVideoInput_SourceType(Element* elem, uint16_t *value) UNUSED_OK;

static void HAL_Decode_AudioVideoInput_SourceType(Element* elem, uint16_t *value)
{
    *value = (uint16_t)HAL_Decode_UInt(elem);
}



static Element* HAL_Encode_Array_AudioVideoInput_SourceType(Array_AudioVideoInput_SourceType value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_AudioVideoInput_SourceType(Array_AudioVideoInput_SourceType value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_AudioVideoInput_SourceType(Element* elem, Array_AudioVideoInput_SourceType* value) UNUSED_OK;

static void HAL_Decode_Array_AudioVideoInput_SourceType(Element* elem, Array_AudioVideoInput_SourceType* value)
{
    InitArray_AudioVideoInput_SourceType(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_AudioVideoInput_SourceType(value, 1);
            value->elems[j] = (uint16_t)HAL_Decode_UInt(elem->children[i]);
        }
    }
}


static Element* HAL_Encode_AudioVideoInput_SignalPresence(AudioVideoInput_SignalPresence value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_AudioVideoInput_SignalPresence(AudioVideoInput_SignalPresence value, Element* parent)
{
    return HAL_Encode_UInt(value, parent);
}



static void HAL_Decode_AudioVideoInput_SignalPresence(Element* elem, uint8_t *value) UNUSED_OK;

static void HAL_Decode_AudioVideoInput_SignalPresence(Element* elem, uint8_t *value)
{
    *value = (uint8_t)HAL_Decode_UInt(elem);
}



static Element* HAL_Encode_Array_AudioVideoInput_SignalPresence(Array_AudioVideoInput_SignalPresence value, Element* parent) UNUSED_OK;

static Element* HAL_Encode_Array_AudioVideoInput_SignalPresence(Array_AudioVideoInput_SignalPresence value, Element* parent)
{
    Element* array = BSXML_NewElement("array", parent);
    for (size_t i = 0; i < value.numElems; ++i) {
        HAL_Encode_UInt(value.elems[i], array);
    }
    return array;
}


static void HAL_Decode_Array_AudioVideoInput_SignalPresence(Element* elem, Array_AudioVideoInput_SignalPresence* value) UNUSED_OK;

static void HAL_Decode_Array_AudioVideoInput_SignalPresence(Element* elem, Array_AudioVideoInput_SignalPresence* value)
{
    InitArray_AudioVideoInput_SignalPresence(value, 0);

    if (strcmp(elem->name, "array") == 0) {
        for (size_t i = 0; i < elem->numChildren; ++i) {
            size_t j = ExtendArray_AudioVideoInput_SignalPresence(value, 1);
            value->elems[j] = (uint8_t)HAL_Decode_UInt(elem->children[i]);
        }
    }
}



static AJ_Status GetInputSourceId(void *context, const char *objPath, uint16_t *out)
{
    AJ_Status result = AJ_OK;
    uint64_t value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.AudioVideoInput", "InputSourceId");

    if (elem) {
        value = HAL_Decode_UInt(elem);
        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}



static AJ_Status SetInputSourceId(void *context, const char *objPath, uint16_t input)
{
    AJ_Status result = AJ_OK;
    uint64_t value = input;

    Element* elem = HAL_Encode_UInt(value, NULL);
    HAL_WritePropertyElem(objPath, "org.alljoyn.SmartSpaces.Operation.AudioVideoInput", "InputSourceId", elem);
    BSXML_FreeElement(elem);

    return result;
}

static AJ_Status GetSupportedInputSources(void *context, const char *objPath, Array_AudioVideoInput_InputSource *out)
{
    AJ_Status result = AJ_OK;
    Array_AudioVideoInput_InputSource value = {0};

    Element* elem = HAL_ReadProperty(objPath, "org.alljoyn.SmartSpaces.Operation.AudioVideoInput", "SupportedInputSources");

    if (elem) {
        HAL_Decode_Array_AudioVideoInput_InputSource(elem, &value);

        BSXML_FreeElement(elem);
    }

    *out = value;
    return result;
}




static AudioVideoInputModel model = {
    GetInputSourceId
    , SetInputSourceId
    , GetSupportedInputSources

};


AudioVideoInputModel *GetAudioVideoInputModel(void)
{
    return &model;
}
