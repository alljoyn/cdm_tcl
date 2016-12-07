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

#ifndef RAPIDMODEINTERFACE_H_
#define RAPIDMODEINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define RAPID_MODE "org.alljoyn.SmartSpaces.Operation.RapidMode"

/**
 * RapidMode interface members
 */
typedef enum {
    RAPIDMODE_PROP_VERSION = 0,
    RAPIDMODE_PROP_RAPID_MODE,
    RAPIDMODE_MEMBER_COUNT
} RapidModeMembers;



extern const char* const intfDescOperationRapidMode[RAPIDMODE_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationRapidMode;


/**
 * Emits a changed signal for the RapidMode property
 * @param[in] newValue new value of rapid mode
 * @return ER_OK on success
 */
AJ_Status Cdm_RapidMode_EmitRapidModeChanged(AJ_BusAttachment *bus, const char *objPath, bool newValue);

#endif /* RAPIDMODEINTERFACE_H_ */