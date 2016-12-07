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

#ifndef ALERTSMODEL_H_
#define ALERTSMODEL_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/interfaces/operation/AlertsInterface.h>

/**
 * Alerts interface model
 */
typedef struct {

    /**
     * Get Alerts
     * @param[out] value current alerts. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetAlerts)(void *context, const char *objPath, Array_Alerts_AlertRecord* value);

     /**
      * Call GetAlertCodesDescription
      * @param[in] languageTag
      * @param[out] description The caller will free the memory if the type is not a scalar.
      */
    AJ_Status (*MethodGetAlertCodesDescription)(void *context, const char *objPath, char const* languageTag, Array_Alerts_AlertCodesDescriptor* description);

     /**
      * Call AcknowledgeAlert
      * @param[in] alertCode
      */
    AJ_Status (*MethodAcknowledgeAlert)(void *context, const char *objPath, uint16_t alertCode);

     /**
      * Call AcknowledgeAllAlerts
      */
    AJ_Status (*MethodAcknowledgeAllAlerts)(void *context, const char *objPath);

    AJ_BusAttachment* busAttachment;

} AlertsModel;

#endif /* ALERTSMODEL_H_ */