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

#include <stdlib.h>

#include <ajtcl/aj_debug.h>
#include <ajtcl/aj_cert.h>

#include <ajtcl/cdm/utils/CDM_Security.h>

static const char *spekePassword = NULL;
static const char *ecdsaPEMPrivateKey = NULL;
static const char *ecdsaPEMCertificate = NULL;
static uint32_t keyExpiration =  0xFFFFFFFF;

//static char *publicBuf = NULL;
//static char *privateBuf = NULL;

static const uint32_t *securitySuites;
static int numSecuritySuites = 0;

static X509CertificateChain* chain = NULL;

void Cdm_SetSuites(const uint32_t *suites, int numSuites)
{
    securitySuites = suites;
    numSecuritySuites = numSuites;
}

void Cdm_EnableSPEKE(const char *password)
{
    spekePassword = password;
}

void Cdm_DisableSPEKE(void)
{
    spekePassword = NULL;
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

//AJ_Status Cdm_EnableFromFile(const char* pathPrefix)
//{
//    return AJ_OK;
//}

static AJ_Status retreiveSPEKE(AJ_Credential* cred)
{
    AJ_Status status = AJ_ERR_INVALID;
    if (spekePassword != NULL)
    {
        cred->data = (uint8_t*)spekePassword;
        cred->len = strlen(spekePassword);
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

            // The ECDHE_PSK auth mechanism is deprecated as of 16.04 and ECDHE_SPEKE should be used instead.
//        case AUTH_SUITE_ECDHE_PSK:
//            switch (command) {
//                case AJ_CRED_PUB_KEY:
//                    cred->data = (uint8_t*) cdmMainParams->securityParams.defaultCallbackParams.pskPublicKey;
//                    cred->len = strlen(cdmMainParams->securityParams.defaultCallbackParams.pskPublicKey);
//                    cred->expiration = cdmMainParams->securityParams.defaultCallbackParams.keyExpiration;
//                    status = AJ_OK;
//                    break;
//                case AJ_CRED_PRV_KEY:
//                    cred->data = (uint8_t*) cdmMainParams->securityParams.defaultCallbackParams.pskPrivateKey;
//                    cred->len = strlen(cdmMainParams->securityParams.defaultCallbackParams.pskPrivateKey);
//                    cred->expiration = cdmMainParams->securityParams.defaultCallbackParams.keyExpiration;
//                    status = AJ_OK;
//                    break;
//            }
//            break;
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
                            // Free previous certificate chain
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
        //AJ_ErrPrintf("Security suites have not been set.\n");
        return status;
    }

    status = AJ_BusEnableSecurity(busAttachment, securitySuites, numSecuritySuites);
    if (status != AJ_OK)
    {
        //AJ_ErrPrintf(("Error enabling security on the bus attachment: %s\n", (AJ_StatusText(status))));
        return status;
    }

    callback = (authListenerCallback != NULL) ? authListenerCallback : DefaultAuthListenerCallback;
    AJ_BusSetAuthListenerCallback(busAttachment, callback);

    return AJ_OK;
}
