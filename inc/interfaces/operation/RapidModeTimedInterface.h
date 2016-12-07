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

#ifndef RAPIDMODETIMEDINTERFACE_H_
#define RAPIDMODETIMEDINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define RAPID_MODE_TIMED "org.alljoyn.SmartSpaces.Operation.RapidModeTimed"

/**
 * RapidModeTimed interface members
 */
typedef enum {
    RAPIDMODETIMED_PROP_VERSION = 0,
    RAPIDMODETIMED_PROP_RAPID_MODE_MINUTES_REMAINING,
    RAPIDMODETIMED_PROP_MAX_SET_MINUTES,
    RAPIDMODETIMED_MEMBER_COUNT
} RapidModeTimedMembers;



extern const char* const intfDescOperationRapidModeTimed[RAPIDMODETIMED_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationRapidModeTimed;


/**
 * Emits a changed signal for the RapidModeMinutesRemaining property
 * @param[in] newValue new value of rapid mode minutes remaining
 * @return ER_OK on success
 */
AJ_Status Cdm_RapidModeTimed_EmitRapidModeMinutesRemainingChanged(AJ_BusAttachment *bus, const char *objPath, uint16_t newValue);

#endif /* RAPIDMODETIMEDINTERFACE_H_ */