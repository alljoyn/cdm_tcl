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

#ifndef AUDIOVOLUMEINTERFACE_H_
#define AUDIOVOLUMEINTERFACE_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/CdmControllee.h>
#include <ajtcl/cdm/utils/CDM_Array.h>

#define AUDIO_VOLUME "org.alljoyn.SmartSpaces.Operation.AudioVolume"

/**
 * AudioVolume interface members
 */
typedef enum {
    AUDIOVOLUME_PROP_VERSION = 0,
    AUDIOVOLUME_PROP_VOLUME,
    AUDIOVOLUME_PROP_MAX_VOLUME,
    AUDIOVOLUME_PROP_MUTE,
    AUDIOVOLUME_MEMBER_COUNT
} AudioVolumeMembers;



extern const char* const intfDescOperationAudioVolume[AUDIOVOLUME_MEMBER_COUNT + 2];
extern const InterfaceHandler intfHandlerOperationAudioVolume;


/**
 * Emits a changed signal for the Volume property
 * @param[in] newValue new value of volume
 * @return ER_OK on success
 */
AJ_Status Cdm_AudioVolume_EmitVolumeChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the MaxVolume property
 * @param[in] newValue new value of max volume
 * @return ER_OK on success
 */
AJ_Status Cdm_AudioVolume_EmitMaxVolumeChanged(AJ_BusAttachment *bus, const char *objPath, uint8_t newValue);

/**
 * Emits a changed signal for the Mute property
 * @param[in] newValue new value of mute
 * @return ER_OK on success
 */
AJ_Status Cdm_AudioVolume_EmitMuteChanged(AJ_BusAttachment *bus, const char *objPath, bool newValue);

#endif /* AUDIOVOLUMEINTERFACE_H_ */