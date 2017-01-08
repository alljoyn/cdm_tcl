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

#ifndef DISHWASHINGCYCLEPHASEMODEL_H_
#define DISHWASHINGCYCLEPHASEMODEL_H_

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>
#include <ajtcl/cdm/interfaces/operation/DishWashingCyclePhaseInterface.h>

/**
 * DishWashingCyclePhase interface model
 */
typedef struct {

    /**
     * Get CyclePhase
     * @param[out] value current cycle phase. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetCyclePhase)(void *context, const char *objPath, uint8_t* value);

    /**
     * Get SupportedCyclePhases
     * @param[out] value current supported cycle phases. The caller will free the memory if
     *             the type is not a scalar.
     * @param[out] numValues if the type is an array, set the number of elements here.
     */
    AJ_Status (*GetSupportedCyclePhases)(void *context, const char *objPath, Array_uint8* value);

     /**
      * Call GetVendorPhasesDescription
      * @param[in] languageTag
      * @param[out] phasesDescription The caller will free the memory if the type is not a scalar.
      */
    AJ_Status (*MethodGetVendorPhasesDescription)(void *context, const char *objPath, char const* languageTag, Array_DishWashingCyclePhase_CyclePhaseDescriptor* phasesDescription);

    AJ_BusAttachment* busAttachment;

} DishWashingCyclePhaseModel;

#endif /* DISHWASHINGCYCLEPHASEMODEL_H_ */