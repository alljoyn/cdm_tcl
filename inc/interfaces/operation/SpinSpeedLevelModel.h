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

#ifndef SPINSPEEDLEVELMODEL_H_
#define SPINSPEEDLEVELMODEL_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/interfaces/operation/SpinSpeedLevelInterface.h>

/**
 * SpinSpeedLevel interface model
 */
typedef struct {

    /**
     * Get MaxLevel
     * @param[out] value current max level. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetMaxLevel)(void *context, const char *objPath, uint8_t* value);

    /**
     * Get TargetLevel
     * @param[out] value current target level. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetTargetLevel)(void *context, const char *objPath, uint8_t* value);

     /**
     * Set TargetLevel
     * @param[in] value The target level to set
     * @return ER_OK on success
     */
    AJ_Status (*SetTargetLevel)(void *context, const char *objPath, uint8_t value);

    /**
     * Get SelectableLevels
     * @param[out] value current selectable levels. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetSelectableLevels)(void *context, const char *objPath, Array_uint8* value);

    AJ_BusAttachment* busAttachment;

} SpinSpeedLevelModel;

#endif /* SPINSPEEDLEVELMODEL_H_ */