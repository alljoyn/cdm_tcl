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

#ifndef MOISTUREOUTPUTLEVELMODEL_H_
#define MOISTUREOUTPUTLEVELMODEL_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/interfaces/operation/MoistureOutputLevelInterface.h>

/**
 * MoistureOutputLevel interface model
 */
typedef struct {

    /**
     * Get MoistureOutputLevel
     * @param[out] value current moisture output level. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetMoistureOutputLevel)(void *context, const char *objPath, uint8_t* value);

     /**
     * Set MoistureOutputLevel
     * @param[in] value The moisture output level to set
     * @return ER_OK on success
     */
    AJ_Status (*SetMoistureOutputLevel)(void *context, const char *objPath, uint8_t value);

    /**
     * Get MaxMoistureOutputLevel
     * @param[out] value current max moisture output level. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetMaxMoistureOutputLevel)(void *context, const char *objPath, uint8_t* value);

    /**
     * Get AutoMode
     * @param[out] value current auto mode. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetAutoMode)(void *context, const char *objPath, MoistureOutputLevel_AutoMode* value);

     /**
     * Set AutoMode
     * @param[in] value The auto mode to set
     * @return ER_OK on success
     */
    AJ_Status (*SetAutoMode)(void *context, const char *objPath, MoistureOutputLevel_AutoMode value);

    AJ_BusAttachment* busAttachment;

} MoistureOutputLevelModel;

#endif /* MOISTUREOUTPUTLEVELMODEL_H_ */