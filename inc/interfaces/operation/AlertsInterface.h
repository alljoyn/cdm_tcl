/******************************************************************************
 * Copyright (c) Open Connectivity Foundation (OCF) and AllJoyn Open
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

#ifndef ALERTSINTERFACE_H_
#define ALERTSINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define ALERTS "org.alljoyn.SmartSpaces.Operation.Alerts"

/**
 * Alerts interface members
 */
typedef enum {
    ALERTS_PROP_VERSION = 0,
    ALERTS_PROP_ALERTS,
    ALERTS_METHOD_GET_ALERT_CODES_DESCRIPTION,
    ALERTS_METHOD_ACKNOWLEDGE_ALERT,
    ALERTS_METHOD_ACKNOWLEDGE_ALL_ALERTS,
    ALERTS_MEMBER_COUNT
} AlertsMembers;


typedef enum {
    ALERTS_SEVERITY_WARNING = 0,
    ALERTS_SEVERITY_ALARM = 1,
    ALERTS_SEVERITY_FAULT = 2
} Alerts_Severity;


typedef struct {
    Alerts_Severity* elems;
    size_t numElems;
} Array_Alerts_Severity;


/**
 *  Initialise an array of Severity.
 */
extern void InitArray_Alerts_Severity(Array_Alerts_Severity* value, size_t numElems);

/**
 *  Copy an array of Severity.
 */
extern void CopyArray_Alerts_Severity(Array_Alerts_Severity* value, Array_Alerts_Severity* copy);

/**
 *  Free an array of Severity.
 */
extern void FreeArray_Alerts_Severity(Array_Alerts_Severity* value);

/**
 *  Extend an array of Severity.
 */
extern size_t ExtendArray_Alerts_Severity(Array_Alerts_Severity* value, size_t numElems);



typedef struct {
    Alerts_Severity severity;
    uint16_t alertCode;
    bool needAcknowledgement;
} Alerts_AlertRecord;


typedef struct {
    Alerts_AlertRecord* elems;
    size_t numElems;
} Array_Alerts_AlertRecord;

/**
 *  Free the fields in the AlertRecord but not the struct itself.
 */
extern void FreeFields_Alerts_AlertRecord(Alerts_AlertRecord* value);

/**
 *  Free an array of AlertRecord.
 */
extern void FreeArray_Alerts_AlertRecord(Array_Alerts_AlertRecord* value);

/**
 *  Initialise an array of AlertRecord.
 */
extern void InitArray_Alerts_AlertRecord(Array_Alerts_AlertRecord* value, size_t numElems);

/**
 *  Copy an array of AlertRecord.
 */
extern void CopyArray_Alerts_AlertRecord(Array_Alerts_AlertRecord* value, Array_Alerts_AlertRecord* copy);

/**
 *  Extend an array of AlertRecord.
 */
extern size_t ExtendArray_Alerts_AlertRecord(Array_Alerts_AlertRecord* value, size_t numElems);


typedef struct {
    uint16_t alertCode;
    char const* description;
} Alerts_AlertCodesDescriptor;


typedef struct {
    Alerts_AlertCodesDescriptor* elems;
    size_t numElems;
} Array_Alerts_AlertCodesDescriptor;

/**
 *  Free the fields in the AlertCodesDescriptor but not the struct itself.
 */
extern void FreeFields_Alerts_AlertCodesDescriptor(Alerts_AlertCodesDescriptor* value);

/**
 *  Free an array of AlertCodesDescriptor.
 */
extern void FreeArray_Alerts_AlertCodesDescriptor(Array_Alerts_AlertCodesDescriptor* value);

/**
 *  Initialise an array of AlertCodesDescriptor.
 */
extern void InitArray_Alerts_AlertCodesDescriptor(Array_Alerts_AlertCodesDescriptor* value, size_t numElems);

/**
 *  Copy an array of AlertCodesDescriptor.
 */
extern void CopyArray_Alerts_AlertCodesDescriptor(Array_Alerts_AlertCodesDescriptor* value, Array_Alerts_AlertCodesDescriptor* copy);

/**
 *  Extend an array of AlertCodesDescriptor.
 */
extern size_t ExtendArray_Alerts_AlertCodesDescriptor(Array_Alerts_AlertCodesDescriptor* value, size_t numElems);


extern const char* const intfDescOperationAlerts[ALERTS_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationAlerts;


/**
 * Emits a changed signal for the Alerts property
 * @param[in] newValue new value of alerts
 * @return ER_OK on success
 */
AJ_Status Cdm_Alerts_EmitAlertsChanged(AJ_BusAttachment *bus, const char *objPath, Array_Alerts_AlertRecord newValue);

#endif /* ALERTSINTERFACE_H_ */