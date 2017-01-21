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

#ifndef ALLJOYN_CDM_SECURITY_H
#define ALLJOYN_CDM_SECURITY_H

#include <stdlib.h>
#include <stdint.h>

#include <ajtcl/aj_status.h>
#include <ajtcl/aj_bus.h>


void Cdm_SetSuites(const uint32_t *suites, int numSuites);

void Cdm_EnablePSK(const char *password);
void Cdm_DisablePSK(void);

void Cdm_EnableSPEKE(const char *password);
void Cdm_DisableSPEKE(void);

void Cdm_EnableECDSA(const char *privateKey, const char *certificate);
void Cdm_DisableECDSA(void);

/**
 * Load the security parameters from the PREFIX.pub and PREFIX.priv files.
 * @param[in] pathPrefix directory and file prefix
 * @return AJ_OK on success
 */
AJ_Status Cdm_LoadFiles(const char* pathPrefix);


/**
 * Enable security.
 * @param[in] busAttachment bus attachment
 * @param[in] suites the authentication suites to enable
 * @param[in] numOfSuites the number of authentication suites
 * @param[in] authListenerCallback the auth listener callback function
 * @return AJ_OK on success
 */
AJ_Status Cdm_EnableSecurity(AJ_BusAttachment *busAttachment, AJ_AuthListenerFunc authListenerCallback);

#endif /* ALLJOYN_CDM_SECURITY_H */
