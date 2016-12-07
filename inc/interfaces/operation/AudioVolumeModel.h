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

#ifndef AUDIOVOLUMEMODEL_H_
#define AUDIOVOLUMEMODEL_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/interfaces/operation/AudioVolumeInterface.h>

/**
 * AudioVolume interface model
 */
typedef struct {

    /**
     * Get Volume
     * @param[out] value current volume. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetVolume)(void *context, const char *objPath, uint8_t* value);

     /**
     * Set Volume
     * @param[in] value The volume to set
     * @return ER_OK on success
     */
    AJ_Status (*SetVolume)(void *context, const char *objPath, uint8_t value);

    /**
     * Get MaxVolume
     * @param[out] value current max volume. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetMaxVolume)(void *context, const char *objPath, uint8_t* value);

    /**
     * Get Mute
     * @param[out] value current mute. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetMute)(void *context, const char *objPath, bool* value);

     /**
     * Set Mute
     * @param[in] value The mute to set
     * @return ER_OK on success
     */
    AJ_Status (*SetMute)(void *context, const char *objPath, bool value);

    AJ_BusAttachment* busAttachment;

} AudioVolumeModel;

#endif /* AUDIOVOLUMEMODEL_H_ */