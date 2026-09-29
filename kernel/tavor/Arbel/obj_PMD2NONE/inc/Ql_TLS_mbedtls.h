
#include "mbedtls/config.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/net_sockets.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
#include "mbedtls/debug.h"



typedef struct nettype_tls_params {
    mbedtls_net_context         socket_fd;        /**< mbed TLS network context. */
    mbedtls_entropy_context     entropy;          /**< mbed TLS entropy. */
    mbedtls_ctr_drbg_context    ctr_drbg;         /**< mbed TLS ctr_drbg. */
    mbedtls_ssl_context         ssl;              /**< mbed TLS control context. */
    mbedtls_ssl_config          ssl_conf;         /**< mbed TLS configuration context. */
#if defined(MBEDTLS_X509_CRT_PARSE_C)
    mbedtls_x509_crt            ca_cert;          /**< mbed TLS CA certification. */
    mbedtls_x509_crt            client_cert;      /**< mbed TLS Client certification. */
#endif
    mbedtls_pk_context          private_key;      /**< mbed TLS Client key. */
} net_tls_params_t;


