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

#ifndef CLIMATECONTROLMODEMODEL_H_
#define CLIMATECONTROLMODEMODEL_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/interfaces/operation/ClimateControlModeInterface.h>

/**
 * ClimateControlMode interface model
 */
typedef struct {

    /**
     * Get Mode
     * @param[out] value current mode. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetMode)(void *context, const char *objPath, ClimateControlMode_Mode* value);

     /**
     * Set Mode
     * @param[in] value The mode to set
     * @return ER_OK on success
     */
    AJ_Status (*SetMode)(void *context, const char *objPath, ClimateControlMode_Mode value);

    /**
     * Get SupportedModes
     * @param[out] value current supported modes. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetSupportedModes)(void *context, const char *objPath, Array_ClimateControlMode_Mode* value);

    /**
     * Get OperationalState
     * @param[out] value current operational state. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetOperationalState)(void *context, const char *objPath, ClimateControlMode_OperationalState* value);

    AJ_BusAttachment* busAttachment;

} ClimateControlModeModel;

#endif /* CLIMATECONTROLMODEMODEL_H_ */