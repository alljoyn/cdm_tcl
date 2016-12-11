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

#ifndef WINDDIRECTIONMODEL_H_
#define WINDDIRECTIONMODEL_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/interfaces/environment/WindDirectionInterface.h>

/**
 * WindDirection interface model
 */
typedef struct {

    /**
     * Get HorizontalDirection
     * @param[out] value current horizontal direction. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetHorizontalDirection)(void *context, const char *objPath, uint16_t* value);

     /**
     * Set HorizontalDirection
     * @param[in] value The horizontal direction to set
     * @return ER_OK on success
     */
    AJ_Status (*SetHorizontalDirection)(void *context, const char *objPath, uint16_t value);

    /**
     * Get HorizontalMax
     * @param[out] value current horizontal max. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetHorizontalMax)(void *context, const char *objPath, uint16_t* value);

    /**
     * Get HorizontalAutoMode
     * @param[out] value current horizontal auto mode. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetHorizontalAutoMode)(void *context, const char *objPath, WindDirection_AutoMode* value);

     /**
     * Set HorizontalAutoMode
     * @param[in] value The horizontal auto mode to set
     * @return ER_OK on success
     */
    AJ_Status (*SetHorizontalAutoMode)(void *context, const char *objPath, WindDirection_AutoMode value);

    /**
     * Get VerticalDirection
     * @param[out] value current vertical direction. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetVerticalDirection)(void *context, const char *objPath, uint16_t* value);

     /**
     * Set VerticalDirection
     * @param[in] value The vertical direction to set
     * @return ER_OK on success
     */
    AJ_Status (*SetVerticalDirection)(void *context, const char *objPath, uint16_t value);

    /**
     * Get VerticalMax
     * @param[out] value current vertical max. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetVerticalMax)(void *context, const char *objPath, uint16_t* value);

    /**
     * Get VerticalAutoMode
     * @param[out] value current vertical auto mode. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetVerticalAutoMode)(void *context, const char *objPath, WindDirection_AutoMode* value);

     /**
     * Set VerticalAutoMode
     * @param[in] value The vertical auto mode to set
     * @return ER_OK on success
     */
    AJ_Status (*SetVerticalAutoMode)(void *context, const char *objPath, WindDirection_AutoMode value);

    AJ_BusAttachment* busAttachment;

} WindDirectionModel;

#endif /* WINDDIRECTIONMODEL_H_ */