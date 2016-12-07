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

#ifndef LOCKCONTROLINTERFACE_H_
#define LOCKCONTROLINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define LOCK_CONTROL "org.alljoyn.SmartSpaces.Operation.LockControl"

/**
 * LockControl interface members
 */
typedef enum {
    LOCKCONTROL_PROP_VERSION = 0,
    LOCKCONTROL_METHOD_LOCK,
    LOCKCONTROL_MEMBER_COUNT
} LockControlMembers;



extern const char* const intfDescOperationLockControl[LOCKCONTROL_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationLockControl;


#endif /* LOCKCONTROLINTERFACE_H_ */