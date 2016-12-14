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

#ifndef HIDINTERFACE_H_
#define HIDINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define HID "org.alljoyn.Input.Hid"

/**
 * Hid interface members
 */
typedef enum {
    HID_PROP_VERSION = 0,
    HID_PROP_SUPPORTED_EVENTS,
    HID_METHOD_INJECT_EVENTS,
    HID_MEMBER_COUNT
} HidMembers;



typedef struct {
    uint16_t type;
    uint16_t code;
    int32_t value;
} Hid_InputEvent;


typedef struct {
    Hid_InputEvent* elems;
    size_t numElems;
} Array_Hid_InputEvent;

/**
 *  Free the fields in the InputEvent but not the struct itself.
 */
extern void FreeFields_Hid_InputEvent(Hid_InputEvent* value);

/**
 *  Free an array of InputEvent.
 */
extern void FreeArray_Hid_InputEvent(Array_Hid_InputEvent* value);

/**
 *  Initialise an array of InputEvent.
 */
extern void InitArray_Hid_InputEvent(Array_Hid_InputEvent* value, size_t numElems);

/**
 *  Copy an array of InputEvent.
 */
extern void CopyArray_Hid_InputEvent(Array_Hid_InputEvent* value, Array_Hid_InputEvent* copy);

/**
 *  Extend an array of InputEvent.
 */
extern size_t ExtendArray_Hid_InputEvent(Array_Hid_InputEvent* value, size_t numElems);


typedef struct {
    uint16_t type;
    uint16_t code;
    int32_t min;
    int32_t max;
} Hid_SupportedInputEvent;


typedef struct {
    Hid_SupportedInputEvent* elems;
    size_t numElems;
} Array_Hid_SupportedInputEvent;

/**
 *  Free the fields in the SupportedInputEvent but not the struct itself.
 */
extern void FreeFields_Hid_SupportedInputEvent(Hid_SupportedInputEvent* value);

/**
 *  Free an array of SupportedInputEvent.
 */
extern void FreeArray_Hid_SupportedInputEvent(Array_Hid_SupportedInputEvent* value);

/**
 *  Initialise an array of SupportedInputEvent.
 */
extern void InitArray_Hid_SupportedInputEvent(Array_Hid_SupportedInputEvent* value, size_t numElems);

/**
 *  Copy an array of SupportedInputEvent.
 */
extern void CopyArray_Hid_SupportedInputEvent(Array_Hid_SupportedInputEvent* value, Array_Hid_SupportedInputEvent* copy);

/**
 *  Extend an array of SupportedInputEvent.
 */
extern size_t ExtendArray_Hid_SupportedInputEvent(Array_Hid_SupportedInputEvent* value, size_t numElems);


extern const char* const intfDescInputHid[HID_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerInputHid;


/**
 * Emits a changed signal for the SupportedEvents property
 * @param[in] newValue new value of supported events
 * @return ER_OK on success
 */
AJ_Status Cdm_Hid_EmitSupportedEventsChanged(AJ_BusAttachment *bus, const char *objPath, Array_Hid_SupportedInputEvent newValue);

#endif /* HIDINTERFACE_H_ */