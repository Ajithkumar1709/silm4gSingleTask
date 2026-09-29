/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @Date: 2019-12-09 21:31:02
 * @LastEditTime: 2020-05-21 01:09:29
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */
#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <stdbool.h>
#include "mqtt_defconfig.h"

#define     NETWORK_CHANNEL_TCP     0
#define     NETWORK_CHANNEL_TLS     1

#define     MQTT_SSL_VERIFY_NONE    0xFFFFFFFF

typedef struct network {
    const char                  *host;
    const char                  *port;
    int                         socket;
#ifdef KAWAII_MQTT_NETWORK_TYPE_TLS
    int                         channel;        /* tcp or tls */
    const char                  *ca_crt;
    const char                  *cli_crt;
    const char                  *cli_key;
    bool                        ca_crt_is_file;
    bool                        cli_crt_is_file;
    bool                        cli_key_is_file;
    unsigned int                ca_crt_len;
    unsigned int                cli_crt_len;
    unsigned int                cli_key_len;
    unsigned int                timeout_ms;            // SSL handshake timeout in millisecond
    void                        *nettype_tls_params;
#endif
} network_t;

int network_init(network_t *n, const char *host, const char *port, const char *ca, const char *cli_crt, const char *cli_key);
int network_set_ca(network_t *n, const char *ca);
int network_set_cli_crt(network_t *n, const char *cli_crt);
int network_set_cli_key(network_t *n, const char *cli_key);
void network_set_channel(network_t *n, int channel);
int network_set_host_port(network_t* n, char *host, char *port);
int network_read(network_t* n, unsigned char* buf, int len, int timeout);
int network_write(network_t* n, unsigned char* buf, int len, int timeout);
int network_connect(network_t *n, int timeout);
void network_disconnect(network_t *n);
void network_release(network_t* n);
int network_sockerrno(network_t *n);

#endif
