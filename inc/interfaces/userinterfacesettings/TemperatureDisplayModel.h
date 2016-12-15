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

#ifndef TEMPERATUREDISPLAYMODEL_H_
#define TEMPERATUREDISPLAYMODEL_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/interfaces/userinterfacesettings/TemperatureDisplayInterface.h>

/**
 * TemperatureDisplay interface model
 */
typedef struct {

    /**
     * Get DisplayTemperatureUnit
     * @param[out] value current display temperature unit. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetDisplayTemperatureUnit)(void *context, const char *objPath, uint8_t* value);

     /**
     * Set DisplayTemperatureUnit
     * @param[in] value The display temperature unit to set
     * @return ER_OK on success
     */
    AJ_Status (*SetDisplayTemperatureUnit)(void *context, const char *objPath, uint8_t value);

    /**
     * Get SupportedDisplayTemperatureUnits
     * @param[out] value current supported display temperature units. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetSupportedDisplayTemperatureUnits)(void *context, const char *objPath, Array_uint8* value);

    AJ_BusAttachment* busAttachment;

} TemperatureDisplayModel;

#endif /* TEMPERATUREDISPLAYMODEL_H_ */