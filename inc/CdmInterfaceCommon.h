/******************************************************************************
 *    Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef CDMINTERFACECOMMON_H_
#define CDMINTERFACECOMMON_H_

#include <ajtcl/aj_bus.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * Emit a changed signal for the given property with the appropriate property data. Note that this
 * is not intended to be called directly by the vendor, but is required in the public framework so
 * that outside interfaces may make use of this code. Should call interface's emit property changed
 * handler instead.
 * @param[in] busAttachment bus attachment
 * @param[in] objPath the object path
 * @param[in] intfName the interface name
 * @param[in] propName the property name
 * @param[in] signature property type signature
 * @param[in] ...
 *            For basic property type:
 *              @param[in] value the property value
 *            For array of basic property type:
 *              @param[in] valueList the array of values in property
 *              @param[in] listLength the number of elements in array
 *            For struct property type:
 *              @param[in] structure the property structure, passed by pointer
 *              @param[in] MarshalStructFunc delegate provided by interface of the form:
                            AJ_Status (*MarshalStructFunc)(AJ_Message* msg, void* structure, const char* structSignature)
 *            For array of struct property type:
 *              @param[in] structureList the property array of structures, passed by pointer
 *              @param[in] listLength the number of structures in array
 *              @param[in] sizeOfStruct the size of one structure in bytes
 *              @param[in] MarshalStructFunc delegate provided by interface of the form:
                            AJ_Status (*MarshalStructFunc)(AJ_Message* msg, void* structure, const char* structSignature)
 * @return AJ_OK on success
 */
AJ_Status EmitPropertyChanged(AJ_BusAttachment* busAttachment, const char* objPath, const char* intfName, const char* propName, const char* signature, ...);

#endif /* CDMINTERFACECOMMON_H_ */