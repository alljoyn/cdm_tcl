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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <ajtcl/aj_debug.h>
#include <ajtcl/aj_cert.h>

#include <ajtcl/cdm/utils/CdmSecurity.h>

static const char *anyPassword = NULL;
static const char *ecdsaPEMPrivateKey = NULL;
static const char *ecdsaPEMCertificate = NULL;
static uint32_t keyExpiration =  0xFFFFFFFF;

/* static char *publicBuf = NULL; */
/* static char *privateBuf = NULL; */

static const uint32_t *securitySuites;
static int numSecuritySuites = 0;

static X509CertificateChain* chain = NULL;

void Cdm_SetSuites(const uint32_t *suites, int numSuites)
{
    securitySuites = suites;
    numSecuritySuites = numSuites;
}

void Cdm_EnablePSK(const char *password)
{
    anyPassword = password;
}

void Cdm_DisablePSK(void)
{
    anyPassword = NULL;
}

void Cdm_EnableSPEKE(const char *password)
{
    anyPassword = password;
}

void Cdm_DisableSPEKE(void)
{
    anyPassword = NULL;
}

void Cdm_EnableECDSA(const char *privateKey, const char *certificate)
{
    ecdsaPEMPrivateKey = privateKey;
    ecdsaPEMCertificate = certificate;
}

void Cdm_DisableECDSA(void)
{
    ecdsaPEMPrivateKey = NULL;
    ecdsaPEMCertificate = NULL;
}

/*======================================================================*/

enum FilePart {PartNone, PartIdentity, PartRoot, PartPassword, PartKey};


static void AppendTo(char c, char** chunk, size_t* length, size_t* capacity)
{
    /*  Append c to the string buffer. Keep a NUL byte at the end.
    */
    if (*length + 2 > *capacity) {
        *capacity = (*capacity + 2) * 2;
        *chunk = realloc(*chunk, *capacity);
    }
    (*chunk)[*length] = c;
    (*length)++;
    (*chunk)[*length] = 0;
}



static bool Getline(FILE* fp, char** line, size_t* length, size_t* capacity)
{
    for(size_t n = 0; ; ++n) {
        int c = fgetc(fp);

        if (c == EOF) {
            return n > 0;
        }

        AppendTo((char)c, line, length, capacity);
        if (c == '\n') {
            return true;
        }
    }
}



static void FlushPart(enum FilePart part, char* chunk)
{
    if (strlen(chunk) == 0) {
        return;
    }

    switch (part)
    {
    case PartIdentity:
        ecdsaPEMCertificate = strdup(chunk);
        break;

    case PartRoot:
        // Not used
        break;

    case PartPassword:
    {
        char* p = strchr(chunk, '\n');
        if (p) {
            *p = 0;
        }
        anyPassword = strdup(chunk);
        break;
    }

    case PartKey:
        ecdsaPEMPrivateKey = strdup(chunk);
        break;

    case PartNone:
        break;
    }
}



static bool LoadOneFile(const char* path)
{
    FILE* fp;
    char* chunk;
    size_t chunkLen;
    size_t chunkCap;
    char* line;
    size_t lineLen;
    size_t lineCap;
    size_t lnum;
    enum FilePart which;

    fp = fopen(path, "r");

    if (!fp) {
        return false;
    }

    chunk = strdup("");
    chunkLen = 0;
    chunkCap = 0;
    line = strdup("");
    lineCap = 0;
    lnum = 0;
    which = PartNone;

    for (;;) {
        lineLen = 0;

        if (!Getline(fp, &line, &lineLen, &lineCap)) {
            break;
        }
        ++lnum;

        if (strncmp(line, "identity", 8) == 0) {
            FlushPart(which, chunk);
            chunkLen = 0;
            which = PartIdentity;
        } else if (strncmp(line, "root", 4) == 0) {
            FlushPart(which, chunk);
            chunkLen = 0;
            which = PartRoot;
        } else if (strncmp(line, "password", 8) == 0) {
            FlushPart(which, chunk);
            chunkLen = 0;
            which = PartPassword;
        } else if (strncmp(line, "key", 3) == 0) {
            FlushPart(which, chunk);
            chunkLen = 0;
            which = PartKey;
        } else if (lineLen > 0 && (line[0] == ' ' || line[0] == '\t')) {
            // An indented piece that is part of the chunk.
            // Trim leading and trailing space
            char* left = line;
            char* right = &line[lineLen - 1];

            while (isspace(*left)) {
                ++left;
            }

            while (right >= left && isspace(*right)) {
                --right;
            }

            right[1] = 0;
            
            if (*left == 0 || *left == '#') {
                continue;
            }

            for (; left <= right; ++left) {
                AppendTo(*left, &chunk, &chunkLen, &chunkCap);
            }

            AppendTo('\n', &chunk, &chunkLen, &chunkCap);
        } else if (lineLen > 0 && line[0] != '\n') {
            fprintf(stderr, "%s: line %zu: Unrecognised line\n", path, lnum);
        }
    }

    if (chunkLen > 0) {
        FlushPart(which, chunk);
    }
    fclose(fp);
    free((void*)chunk);
    return true;
}



AJ_Status Cdm_LoadFiles(const char* pathPrefix)
{
    bool ok = true;
    size_t plen = strlen(pathPrefix);
    char* path = malloc(plen + 5 + 1);    // room for .priv

    strcpy(path, pathPrefix);
    strcat(path, ".pub");
    ok &= LoadOneFile(path);

    strcpy(path + plen, ".priv");
    ok &= LoadOneFile(path);

    return ok? AJ_OK : AJ_ERR_FAILURE;
}


/*======================================================================*/

static AJ_Status retreiveSPEKE(AJ_Credential* cred)
{
    AJ_Status status = AJ_ERR_INVALID;
    if (anyPassword != NULL)
    {
        cred->data = (uint8_t*)anyPassword;
        cred->len = strlen(anyPassword);
        cred->expiration = keyExpiration;
        status = AJ_OK;
    }

    return status;
}

static AJ_Status retreivePSK(AJ_Credential* cred)
{
    AJ_Status status = AJ_ERR_INVALID;
    if (anyPassword != NULL)
    {
        cred->data = (uint8_t*)anyPassword;
        cred->len = strlen(anyPassword);
        cred->expiration = keyExpiration;
        status = AJ_OK;
    }

    return status;
}

static AJ_Status DefaultAuthListenerCallback(uint32_t authmechanism, uint32_t command, AJ_Credential* cred)
{
    AJ_Status status = AJ_ERR_INVALID;
    X509CertificateChain* node;

    AJ_AlwaysPrintf(("DefaultAuthListenerCallback authmechanism %08X command %d\n", authmechanism, command));

    switch (authmechanism) {
        case AUTH_SUITE_ECDHE_NULL:
            cred->expiration = keyExpiration;
            status = AJ_OK;
            break;
        case AUTH_SUITE_ECDHE_SPEKE:
            switch (command) {
                case AJ_CRED_PASSWORD:
                    status = retreiveSPEKE(cred);
                    break;
            }
            break;

        /* The ECDHE_PSK auth mechanism is deprecated as of 16.04 and ECDHE_SPEKE should be used instead. */
        case AUTH_SUITE_ECDHE_PSK:
            switch (command) {
                case AJ_CRED_PUB_KEY:
                    status = retreivePSK(cred);
                    break;
                case AJ_CRED_PRV_KEY:
                    status = retreivePSK(cred);
                    break;
            }
            break;
        case AUTH_SUITE_ECDHE_ECDSA:
            switch (command) {
                case AJ_CRED_PRV_KEY:
                    AJ_ASSERT(sizeof (AJ_ECCPrivateKey) == cred->len);

                    status = (ecdsaPEMPrivateKey != NULL) ? AJ_DecodePrivateKeyPEM((AJ_ECCPrivateKey*)cred->data, ecdsaPEMPrivateKey) : AJ_ERR_FAILURE;
                    cred->expiration = keyExpiration;
                    break;
                case AJ_CRED_CERT_CHAIN:
                    switch (cred->direction) {
                        case AJ_CRED_REQUEST:
                            /* Free previous certificate chain */
                            AJ_X509FreeDecodedCertificateChain(chain);
                            chain = AJ_X509DecodeCertificateChainPEM(ecdsaPEMCertificate);
                            if (NULL == chain) {
                                return AJ_ERR_INVALID;
                            }
                            cred->data = (uint8_t*) chain;
                            cred->expiration = keyExpiration;
                            status = AJ_OK;
                            break;
                        case AJ_CRED_RESPONSE:
                            node = (X509CertificateChain*)((void*)cred->data);
                            status = AJ_X509VerifyChain(node, NULL, AJ_CERTIFICATE_IDN_X509);
                            while (node) {
                                AJ_DumpBytes("CERTIFICATE", node->certificate.der.data, node->certificate.der.size);
                                node = node->next;
                            }
                            break;
                    }
                    break;
            }
            break;
        default:
            break;
    }
    return status;
}

AJ_Status Cdm_EnableSecurity(AJ_BusAttachment *busAttachment, AJ_AuthListenerFunc authListenerCallback)
{
    AJ_AuthListenerFunc callback;

    AJ_Status status = (securitySuites == NULL || numSecuritySuites == 0) ? AJ_ERR_FAILURE : AJ_OK;
    if (status != AJ_OK)
    {
        /* AJ_ErrPrintf("Security suites have not been set.\n"); */
        return status;
    }

    status = AJ_BusEnableSecurity(busAttachment, securitySuites, numSecuritySuites);
    if (status != AJ_OK)
    {
        /* AJ_ErrPrintf(("Error enabling security on the bus attachment: %s\n", (AJ_StatusText(status)))); */
        return status;
    }

    callback = (authListenerCallback != NULL) ? authListenerCallback : DefaultAuthListenerCallback;
    AJ_BusSetAuthListenerCallback(busAttachment, callback);

    return AJ_OK;
}
