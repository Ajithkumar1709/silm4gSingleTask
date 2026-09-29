/**
 * \file asros_mbedtls_config.h
 *
 * \brief Minimal configuration of features that do not require an entropy source
 */
/*
 *  Copyright (C) 2016, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */
/*
 * Minimal configuration of features that do not require an entropy source
 * Distinguishing reatures:
 * - no entropy module
 * - no TLS protocol implementation available due to absence of an entropy
 *   source
 *
 * See README.txt for usage instructions.
 */

#ifndef MBEDTLS_CONFIG_H
#define MBEDTLS_CONFIG_H

#ifdef PLAT_NEZHAC /*this macro is defined from tavor/build/arbel.mak*/
/*for 1802s and 1803, no time system define*/
#define MBEDTLS_PLATFORM_TIME_ALT
#endif

#define MBEDTLS_VERSION_C
#define LWM2M_WITH_MBEDTLS
#define MBEDTLS_PLATFORM_MEMORY
//#define MBEDTLS_CONFIG_TLS_DEBUG

#ifdef MBTK_AIDIALOG_SUPPORT_DOUBAO
#include "asros_mbedtls_config_dongle.h"
#else

#ifdef CRANE_MCU_DONGLE //this is Minimal configuration of features for data module 
/* System support */
#define MBEDTLS_HAVE_ASM
#define MBEDTLS_HAVE_TIME
#define MBEDTLS_TIMING_ALT

//#define MBEDTLS_DEBUG_C
#if (defined(CUSTOMER_LC) || defined(CUSTOMER_BOX_MINI) || defined(CUSTOMER_BOX_L)) //for customer qclould adapter
#define MBEDTLS_SSL_SERVER_NAME_INDICATION
#endif

/* mbed TLS feature support */
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_CIPHER_PADDING_PKCS7
#define MBEDTLS_REMOVE_ARC4_CIPHERSUITES
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
//#define MBEDTLS_ECP_DP_SECP384R1_ENABLED
//#define MBEDTLS_ECP_DP_CURVE25519_ENABLED
//#define MBEDTLS_ECP_NIST_OPTIM
#define MBEDTLS_ECDSA_DETERMINISTIC // closed for reduce code size
#define MBEDTLS_HMAC_DRBG_C
#define MBEDTLS_PK_RSA_ALT_SUPPORT
#define MBEDTLS_PKCS1_V15
#define MBEDTLS_PKCS1_V21
#if defined(CUSTOMER_BOX_MINI) || defined(CUSTOMER_BOX_L)
#define MBEDTLS_HAVE_TIME_DATE
#endif
//#define MBEDTLS_SELF_TEST // closed for reduce code size
//#define MBEDTLS_VERSION_FEATURES //closed for reduce code size
//#define MBEDTLS_X509_CHECK_KEY_USAGE
//#define MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE
#define MBEDTLS_PKCS5_C //add by xph pkcs#8
/* mbed TLS modules */
#define MBEDTLS_AES_C
#define MBEDTLS_ASN1_PARSE_C
//#define MBEDTLS_ASN1_WRITE_C // closed for reduce code size
#define MBEDTLS_BASE64_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_CCM_C
#define MBEDTLS_CIPHER_C
#define MBEDTLS_ECDSA_C
//#define MBEDTLS_ECP_C // closed for reduce code size
//#define MBEDTLS_ERROR_C //closed for reduce code size
//#define MBEDTLS_GCM_C
//#define MBEDTLS_HMAC_DRBG_C // closed for reduce code size
#define MBEDTLS_MD_C
#define MBEDTLS_OID_C
#define MBEDTLS_PEM_PARSE_C
#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_PK_WRITE_C
#define MBEDTLS_PLATFORM_C
#define MBEDTLS_RSA_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_SHA512_C
//#define MBEDTLS_VERSION_C // closed for reduce code size
#define MBEDTLS_X509_USE_C
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_X509_CRL_PARSE_C
#define MBEDTLS_CMAC_C
#define MBEDTLS_MD5_C
#define MBEDTLS_NET_C
#define MBEDTLS_SHA1_C
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_ENTROPY_HARDWARE_ALT
#define MBEDTLS_NO_PLATFORM_ENTROPY
#define MBEDTLS_CTR_DRBG_C
#define MBEDTLS_SSL_CLI_C
//#define MBEDTLS_SSL_SRV_C

//#ifndef CUSTOMER_SMART
#define MBEDTLS_CERTS_C // need open?
//#endif

#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
#define MBEDTLS_ECDH_C
#define MBEDTLS_ECDSA_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C // closed for reduce code size
#define MBEDTLS_ECP_C // closed for reduce code size


//#define MBEDTLS_SSL_SESSION_TICKETS
//#define MBEDTLS_SSL_RENEGOTIATION

//#define MBEDTLS_DEBUG_C // closed for reduce code size
#define MBEDTLS_KEY_EXCHANGE_PSK_ENABLED 
#define MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_DTLS_HELLO_VERIFY
#define MBEDTLS_PLATFORM_MEMORY
#define MBEDTLS_PLATFORM_SNPRINTF_ALT
#define MBEDTLS_PLATFORM_PRINTF_ALT
#define MBEDTLS_SSL_TLS_C
#define MBEDTLS_SSL_PROTO_TLS1_2
#define MBEDTLS_SSL_PROTO_TLS1
#define MBEDTLS_SSL_PROTO_TLS1_1
#define MBEDTLS_SSL_PROTO_SSL3
#define MBEDTLS_SSL_KEEP_PEER_CERTIFICATE
#define MBEDTLS_TLS_DEFAULT_ALLOW_SHA1_IN_KEY_EXCHANGE //add by xph 20201027
#define MBEDTLS_TLS_DEFAULT_ALLOW_SHA1_IN_CERTIFICATES
//#define MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED
//#define MBEDTLS_DHM_C
//#define MBEDTLS_CAMELLIA_C
#define MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
#define MBEDTLS_DES_C
//#define MBEDTLS_ARC4_C
#define MBEDTLS_ECP_C
#define MBEDTLS_GCM_C
#define MBEDTLS_ECDH_C
#define MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED
#ifdef MBTK_ESIM_SUPPORT
#define MBEDTLS_SSL_SERVER_NAME_INDICATION
#define MBEDTLS_X509_ALLOW_UNSUPPORTED_CRITICAL_EXTENSION
#endif
#define MBEDTLS_SSL_CIPHERSUITES \
        MBEDTLS_TLS_RSA_WITH_AES_256_CBC_SHA256, \
        MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA256, \
        MBEDTLS_TLS_RSA_WITH_AES_256_CBC_SHA, \
        MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA, \
        MBEDTLS_TLS_RSA_WITH_3DES_EDE_CBC_SHA, \
        MBEDTLS_TLS_PSK_WITH_AES_128_GCM_SHA256,\
        MBEDTLS_TLS_PSK_WITH_AES_256_GCM_SHA384,\
        MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256,\
        MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,\
        MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
#else

/* System support */
#define MBEDTLS_HAVE_ASM
#define MBEDTLS_HAVE_TIME

/* mbed TLS feature support */
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_CIPHER_PADDING_PKCS7
#define MBEDTLS_REMOVE_ARC4_CIPHERSUITES
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#define MBEDTLS_ECP_DP_SECP384R1_ENABLED
#define MBEDTLS_ECP_DP_CURVE25519_ENABLED
#define MBEDTLS_ECP_NIST_OPTIM
//#define MBEDTLS_ECDSA_DETERMINISTIC // closed for reduce code size
#define MBEDTLS_PK_RSA_ALT_SUPPORT
#define MBEDTLS_PKCS1_V15
#define MBEDTLS_PKCS1_V21
//#define MBEDTLS_SELF_TEST // closed for reduce code size
//#define MBEDTLS_VERSION_FEATURES //closed for reduce code size
#define MBEDTLS_X509_CHECK_KEY_USAGE
#define MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE

/* mbed TLS modules */
#define MBEDTLS_AES_C
#define MBEDTLS_ASN1_PARSE_C
//#define MBEDTLS_ASN1_WRITE_C // closed for reduce code size
#define MBEDTLS_BASE64_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_CCM_C
#define MBEDTLS_CIPHER_C

#ifdef SUPPORT_TLS_SUITEB
#define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
#define MBEDTLS_ECDH_C
#define MBEDTLS_ECDSA_C
#define MBEDTLS_ASN1_WRITE_C // closed for reduce code size
#define MBEDTLS_ECP_C // closed for reduce code size
#endif

//#define MBEDTLS_ERROR_C //closed for reduce code size
#define MBEDTLS_GCM_C
//#define MBEDTLS_HMAC_DRBG_C // closed for reduce code size
#define MBEDTLS_MD_C
#define MBEDTLS_OID_C
#define MBEDTLS_PEM_PARSE_C
#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_PK_WRITE_C
#define MBEDTLS_PLATFORM_C
#define MBEDTLS_RSA_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_SHA512_C
//#define MBEDTLS_VERSION_C // closed for reduce code size
#define MBEDTLS_X509_USE_C
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_X509_CRL_PARSE_C
#define MBEDTLS_CMAC_C
#define MBEDTLS_MD5_C
#define MBEDTLS_NET_C
#define MBEDTLS_SHA1_C
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_ENTROPY_HARDWARE_ALT
#define MBEDTLS_NO_PLATFORM_ENTROPY
#define MBEDTLS_CTR_DRBG_C
#define MBEDTLS_SSL_CLI_C
//#define MBEDTLS_SSL_SRV_C
#define MBEDTLS_CERTS_C // need open?
//#define MBEDTLS_SSL_SESSION_TICKETS
#define MBEDTLS_SSL_RENEGOTIATION

#define MBEDTLS_DEBUG_C

#define MBEDTLS_SSL_TLS_C
#define MBEDTLS_SSL_PROTO_TLS1_2
#define MBEDTLS_SSL_PROTO_SSL3
#define MBEDTLS_SSL_KEEP_PEER_CERTIFICATE

#define MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED
#define MBEDTLS_DHM_C
#define MBEDTLS_CAMELLIA_C
#define MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
#define MBEDTLS_DES_C
#define MBEDTLS_ARC4_C

#define MBEDTLS_SSL_CIPHERSUITES \
        MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CBC_SHA256, \
        MBEDTLS_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384, \
        MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CBC_SHA, \
        MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CBC_SHA256, \
        MBEDTLS_TLS_DHE_RSA_WITH_AES_128_GCM_SHA256, \
        MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CBC_SHA, \
        MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256, \
        MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA, \
        MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256, \
        MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA, \
        MBEDTLS_TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA, \
        MBEDTLS_TLS_RSA_WITH_AES_256_CBC_SHA256, \
        MBEDTLS_TLS_RSA_WITH_AES_256_GCM_SHA384, \
        MBEDTLS_TLS_RSA_WITH_AES_256_CBC_SHA, \
        MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256, \
        MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA, \
        MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA256, \
        MBEDTLS_TLS_RSA_WITH_AES_128_GCM_SHA256, \
        MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA, \
        MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256, \
        MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA, \
        MBEDTLS_TLS_RSA_WITH_3DES_EDE_CBC_SHA, \
        MBEDTLS_TLS_RSA_WITH_RC4_128_SHA, \
        MBEDTLS_TLS_RSA_WITH_RC4_128_MD5

#endif

#endif

#ifdef LWM2M_WITH_MBEDTLS
#define MBEDTLS_CONFIG_DTLS
#define MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_SRV_C
#if defined(MBEDTLS_CONFIG_CRYPTO_AES)
#define MBEDTLS_CTR_DRBG_C
#endif
#define MBEDTLS_KEY_EXCHANGE_PSK_ENABLED
#define MBEDTLS_KEY_EXCHANGE__SOME__PSK_ENABLED
#define MBEDTLS_PSK_MAX_LEN            16 /* 128 bits */
#endif /* LWM2M_WITH_MBEDTLS */

/* Miscellaneous options */
//#define MBEDTLS_AES_ROM_TABLES

#include "mbedtls\check_config.h"
#include "asros_mbedtls_platform_alt.h"

#endif /* MBEDTLS_CONFIG_H */
