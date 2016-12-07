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

#ifndef ONOFFSTATUSINTERFACE_H_
#define ONOFFSTATUSINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define ON_OFF_STATUS "org.alljoyn.SmartSpaces.Operation.OnOffStatus"

/**
 * OnOffStatus interface members
 */
typedef enum {
    ONOFFSTATUS_PROP_VERSION = 0,
    ONOFFSTATUS_PROP_IS_ON,
    ONOFFSTATUS_MEMBER_COUNT
} OnOffStatusMembers;



extern const char* const intfDescOperationOnOffStatus[ONOFFSTATUS_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationOnOffStatus;


/**
 * Emits a changed signal for the IsOn property
 * @param[in] newValue new value of is on
 * @return ER_OK on success
 */
AJ_Status Cdm_OnOffStatus_EmitIsOnChanged(AJ_BusAttachment *bus, const char *objPath, bool newValue);

#endif /* ONOFFSTATUSINTERFACE_H_ */