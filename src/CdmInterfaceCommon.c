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

#include <ajtcl/aj_msg.h>
#include <ajtcl/cdm/CdmInterfaceCommon.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum {
    SIGNATURE_BASIC = 0,        // Basic type, length of 1 (e.g. 'n')
    SIGNATURE_ARRAY_BASIC,      // Array of basic type, length of 2 (e.g. 'an')
    SIGNATURE_STRUCT,           // Struct, begins and ends with braces (e.g. '(nnn)')
    SIGNATURE_ARRAY_STRUCT,     // Array of structs, prefixes struct with 'a' (e.g. 'a(nnn)')

    SIGNATURE_TYPE_COUNT,
    
    SIGNATURE_UNSUPPORTED
} PropSignatureType;

typedef AJ_Status (*MarshalStructFunc)(AJ_Message*, void*, const char*);
typedef AJ_Status (*MarshalArgHandler)(va_list*, AJ_Message*, const char*, const char*);

static PropSignatureType GetPropSignatureType(const char* signature)
{
    PropSignatureType propSignatureType = SIGNATURE_UNSUPPORTED;

    if (signature) {
        size_t signatureLength = strlen(signature);

        if (signatureLength == 1) {
            propSignatureType = SIGNATURE_BASIC;
        } else if (signatureLength > 1) {
            char firstChar = signature[0];

            if (firstChar == 'a') {
                if (signatureLength == 2) {
                    propSignatureType = SIGNATURE_ARRAY_BASIC;
                } else {
                    char secondChar = signature[1];
                    if (secondChar == '(') {
                        propSignatureType = SIGNATURE_ARRAY_STRUCT;
                    }
                }
            } else if (firstChar == '(') {
                propSignatureType = SIGNATURE_STRUCT;
            }
        }
    }

    return propSignatureType;
}

static AJ_Status MarshalSignatureBasic(va_list* vaList, AJ_Message* msg, const char* propName, const char* signature)
{
    AJ_Status status = AJ_OK;

    if (!signature) {
        return AJ_ERR_INVALID;
    }

    switch (signature[0]) {
        case 'b':
            AJ_MarshalArgs(msg, "sv", propName, signature, (bool)va_arg(*vaList, uint32_t));
            break;
        case 'd':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, double));
            break;
        case 'i':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, int32_t));
            break;
        case 'n':
            AJ_MarshalArgs(msg, "sv", propName, signature, (int16_t)va_arg(*vaList, int32_t));
            break;
        case 'o':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, char*));
            break;
        case 'q':
            AJ_MarshalArgs(msg, "sv", propName, signature, (uint16_t)va_arg(*vaList, uint32_t));
            break;
        case 's':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, char*));
            break;
        case 't':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, uint64_t));
            break;
        case 'u':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, uint32_t));
            break;
        case 'x':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, int64_t));
            break;
        case 'y':
            AJ_MarshalArgs(msg, "sv", propName, signature, (uint8_t)va_arg(*vaList, uint32_t));
            break;
        default:
            status = AJ_ERR_SIGNATURE;
    }

    return status;
}

static AJ_Status MarshalSignatureArrayBasic(va_list* vaList, AJ_Message* msg, const char* propName, const char* signature)
{
    AJ_Status status = AJ_OK;

    if (!signature || strlen(signature) != 2) {
        return AJ_ERR_INVALID;
    }

    switch (signature[1]) {
        case 'b':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, bool*), va_arg(*vaList, size_t));
            break;
        case 'd':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, double*), va_arg(*vaList, size_t));
            break;
        case 'i':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, int32_t*), va_arg(*vaList, size_t));
            break;
        case 'n':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, int16_t*), va_arg(*vaList, size_t));
            break;
        case 'q':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, uint16_t*), va_arg(*vaList, size_t));
            break;
        case 't':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, uint64_t*), va_arg(*vaList, size_t));
            break;
        case 'u':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, uint32_t*), va_arg(*vaList, size_t));
            break;
        case 'x':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, int64_t*), va_arg(*vaList, size_t));
            break;
        case 'y':
            AJ_MarshalArgs(msg, "sv", propName, signature, va_arg(*vaList, uint8_t*), va_arg(*vaList, size_t));
            break;
        default:
            status = AJ_ERR_SIGNATURE;
    }

    return status;
}

static AJ_Status MarshalSignatureStruct(va_list* vaList, AJ_Message* msg, const char* propName, const char* signature)
{
    AJ_Status status = AJ_OK;
    AJ_Arg argStruct;

    if (!signature) {
        return AJ_ERR_INVALID;
    }

    size_t strLength = strlen(signature);
    if (signature[0] != '(' || signature[strLength - 1] != ')') {
        return AJ_ERR_INVALID;
    }

    AJ_MarshalArgs(msg, "s", propName);
    AJ_MarshalVariant(msg, signature);
    AJ_MarshalContainer(msg, &argStruct, AJ_ARG_STRUCT);

    size_t structSigLen = (strLength - 1);   // Includes null terminator.
    char* structSignature = malloc(structSigLen * sizeof(char));
    if (!structSignature) {
        return AJ_ERR_RESOURCES;
    }

    // Extract struct signature within the braces (e.g. 'nnn' from '(nnn)').
    strncpy(structSignature, (signature + 1), (structSigLen - 1));
    structSignature[structSigLen - 1] = '\0';

    // Delegate marshaling of struct arguments to interface's handler function.
    void* structure = va_arg(*vaList, void*);
    MarshalStructFunc func = va_arg(*vaList, MarshalStructFunc);
    status = func(msg, structure, structSignature);
    
    AJ_MarshalCloseContainer(msg, &argStruct);
    
    free(structSignature);

    return status;
}

static AJ_Status MarshalSignatureArrayStruct(va_list* vaList, AJ_Message* msg, const char* propName, const char* signature)
{
    AJ_Status status = AJ_OK;
    AJ_Arg argArray;
    AJ_Arg argStruct;

    if (!signature) {
        return AJ_ERR_INVALID;
    }

    size_t strLength = strlen(signature);
    if (signature[0] != 'a' || signature[1] != '(' || signature[strLength - 1] != ')') {
        return AJ_ERR_INVALID;
    }

    AJ_MarshalArgs(msg, "s", propName);
    AJ_MarshalVariant(msg, signature);
    AJ_MarshalContainer(msg, &argArray, AJ_ARG_ARRAY);
    
    void* structures = va_arg(*vaList, void*);
    size_t arrayLength = va_arg(*vaList, size_t);
    size_t sizeOfStruct = va_arg(*vaList, size_t);
    MarshalStructFunc func = va_arg(*vaList, MarshalStructFunc);

    size_t structSigLen = (strLength - 2);   // Includes null terminator.
    char* structSignature = malloc(structSigLen * sizeof(char));
    if (!structSignature) {
        return AJ_ERR_RESOURCES;
    }

    // Extract struct signature within the braces (e.g. 'nnn' from 'a(nnn)').
    strncpy(structSignature, (signature + 2), (structSigLen - 1));
    structSignature[structSigLen - 1] = '\0';

    // Delegate marshaling of struct arguments to interface's handler function.
    char* p = (char*)structures;
    for (int i = 0; i < arrayLength; i++) {
        AJ_MarshalContainer(msg, &argStruct, AJ_ARG_STRUCT);
        
        status = func(msg, (void*)p, structSignature);
        if (status != AJ_OK) {
            goto SignatureCleanup;
        }
        p += sizeOfStruct;
    
        AJ_MarshalCloseContainer(msg, &argStruct);
    }

    AJ_MarshalCloseContainer(msg, &argArray);

SignatureCleanup:
    free(structSignature);

    return status;
}

static const MarshalArgHandler marshalArgHandlers[SIGNATURE_TYPE_COUNT] = {
    MarshalSignatureBasic,
    MarshalSignatureArrayBasic,
    MarshalSignatureStruct,
    MarshalSignatureArrayStruct
};

AJ_Status EmitPropertyChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* intfName, const char* propName, const char* signature, ...)
{
    if (!busAttachment || !objPath || !intfName || !propName || !signature) {
        return AJ_ERR_INVALID;
    }

    uint32_t msgId = 0;
    AJ_Status status = MakePropChangedId(objPath, &msgId);
    if (status != AJ_OK) {
        return status;
    }

    AJ_Message msg;
    AJ_Arg argArray;
    AJ_Arg argDictEntry;

    AJ_MarshalSignal(busAttachment, &msg, msgId, NULL, 0, AJ_FLAG_GLOBAL_BROADCAST, 0);
    AJ_MarshalArgs(&msg, "s", intfName);
    AJ_MarshalContainer(&msg, &argArray, AJ_ARG_ARRAY);
    AJ_MarshalContainer(&msg, &argDictEntry, AJ_ARG_DICT_ENTRY);

    va_list vaList;
    va_start(vaList, signature);
    PropSignatureType propSignatureType = GetPropSignatureType(signature);

    if (propSignatureType == SIGNATURE_UNSUPPORTED) {
        return AJ_ERR_SIGNATURE;
    }
    
    status = marshalArgHandlers[propSignatureType](&vaList, &msg, propName, signature);
    if (status != AJ_OK) {
        return status;
    }

    va_end(vaList);

    AJ_MarshalCloseContainer(&msg, &argDictEntry);
    AJ_MarshalCloseContainer(&msg, &argArray);
    AJ_MarshalContainer(&msg, &argArray, AJ_ARG_ARRAY);
    AJ_MarshalCloseContainer(&msg, &argArray);
    
    return AJ_DeliverMsg(&msg);
}