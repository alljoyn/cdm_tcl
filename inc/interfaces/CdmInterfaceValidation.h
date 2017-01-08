/******************************************************************************
 * Copyright (c) 2016 Open Connectivity Foundation (OCF) and AllJoyn Open
 *    Source Project (AJOSP) Contributors and others.
 *
 *    SPDX-License-Identifier: Apache-2.0
 *
 *    All rights reserved. This program and the accompanying materials are
 *    made available under the terms of the Apache License, Version 2.0
 *    which accompanies this distribution, and is available at
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Copyright 2016 Open Connectivity Foundation and Contributors to
 *    AllSeen Alliance. All rights reserved.
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

#ifndef ALLJOYN_CDMINTERFACEVALIDATION_H
#define ALLJOYN_CDMINTERFACEVALIDATION_H

#include <stdint.h>
#include <ajtcl/cdm/utils/Cdm_Array.h>
#include <ajtcl/cdm/interfaces/operation/AudioVideoInputInterface.h>
#include <ajtcl/cdm/interfaces/operation/ChannelInterface.h>
#include <ajtcl/cdm/interfaces/operation/ClimateControlModeInterface.h>

#define MK_CLAMP(TYPE, NAME) TYPE clamp_##NAME(TYPE value, TYPE min, TYPE max, TYPE step);

MK_CLAMP(double, double)
MK_CLAMP(uint8_t, uint8)
MK_CLAMP(uint16_t, uint16)

#define MK_VALUEIN_ARRAY(TYPE, NAME) int valueIn_Array_##NAME(TYPE value, Array_##NAME *values);

MK_VALUEIN_ARRAY(uint8_t, uint8)
MK_VALUEIN_ARRAY(uint16_t, AudioVideoInput_InputSource)
MK_VALUEIN_ARRAY(char*, Channel_ChannelInfoRecord)
MK_VALUEIN_ARRAY(ClimateControlMode_Mode, ClimateControlMode_Mode)


#endif /* ALLJOYN_CDMINTERFACEVALIDATION_H */
