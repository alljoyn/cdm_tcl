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

#ifndef TRIGGERSENSORINTERFACE_H_
#define TRIGGERSENSORINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define TRIGGER_SENSOR "org.alljoyn.SmartSpaces.Operation.TriggerSensor"

/**
 * TriggerSensor interface members
 */
typedef enum {
    TRIGGERSENSOR_PROP_VERSION = 0,
    TRIGGERSENSOR_PROP_CURRENTLY_TRIGGERED,
    TRIGGERSENSOR_MEMBER_COUNT
} TriggerSensorMembers;



extern const char* const intfDescOperationTriggerSensor[TRIGGERSENSOR_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationTriggerSensor;


/**
 * Emits a changed signal for the CurrentlyTriggered property
 * @param[in] newValue new value of currently triggered
 * @return ER_OK on success
 */
AJ_Status Cdm_TriggerSensor_EmitCurrentlyTriggeredChanged(AJ_BusAttachment *bus, const char *objPath, bool newValue);

#endif /* TRIGGERSENSORINTERFACE_H_ */