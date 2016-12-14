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

#include <ajtcl/cdm/utils/CDM_Array.h>
#include "BSXML.h"

//======================================================================

void HAL_Init(const char *base_path, const char *ext);
void HAL_DefaultInit(void);

// Write some XML to the file.
bool HAL_WritePropertyXml(const char *objPath, const char *interface, const char *property, const char* xml, bool force);

// Write an XML tree to the file.
bool HAL_WritePropertyElem(const char *objPath, const char *interface, const char *property, const Element* elem);

// Read the XML from the file.
Element* HAL_ReadProperty(const char *objPath, const char *interface, const char *property);

//======================================================================

extern Element* HAL_Encode_Bool(bool value, Element* parent);
extern Element* HAL_Encode_Int(int64_t value, Element* parent);
extern Element* HAL_Encode_UInt(uint64_t value, Element* parent);
extern Element* HAL_Encode_String(const char* value, Element* parent);
extern Element* HAL_Encode_Double(double value, Element* parent);

extern Element* HAL_Encode_Array_Bool(Array_Bool value, Element* parent);
extern Element* HAL_Encode_Array_string(Array_string value, Element* parent);

extern Element* HAL_Encode_Array_uint8(Array_uint8 value, Element* parent);
extern Element* HAL_Encode_Array_uint16(Array_uint16 value, Element* parent);
extern Element* HAL_Encode_Array_uint32(Array_uint32 value, Element* parent);
extern Element* HAL_Encode_Array_uint64(Array_uint64 value, Element* parent);

extern Element* HAL_Encode_Array_int16(Array_int16 value, Element* parent);
extern Element* HAL_Encode_Array_int32(Array_int32 value, Element* parent);
extern Element* HAL_Encode_Array_int64(Array_int64 value, Element* parent);



// These decode an XML tree.
extern int64_t HAL_Decode_Int(Element* elem);
extern uint64_t HAL_Decode_UInt(Element* elem);
extern double HAL_Decode_Double(Element* elem);

// Ownership of the string is transferred to the caller
extern const char* HAL_Decode_String(Element* elem);

extern void HAL_Decode_Array_Bool(Element* elem, Array_Bool *array);
extern void HAL_Decode_Array_string(Element* elem, Array_string *array);
extern void HAL_Decode_Array_double(Element* elem, Array_double *array);

extern void HAL_Decode_Array_uint8(Element* elem, Array_uint8 *array);
extern void HAL_Decode_Array_uint16(Element* elem, Array_uint16 *array);
extern void HAL_Decode_Array_uint32(Element* elem, Array_uint32 *array);
extern void HAL_Decode_Array_uint64(Element* elem, Array_uint64 *array);

extern void HAL_Decode_Array_int16(Element* elem, Array_int16 *array);
extern void HAL_Decode_Array_int32(Element* elem, Array_int32 *array);
extern void HAL_Decode_Array_int64(Element* elem, Array_int64 *array);

//======================================================================
#endif //ALLJOYN_HAL_H
