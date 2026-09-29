#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "UART.h"
#include "mbtk_aliyunclient.h"


aliyun_client_t *mbtk_aliyun_lease(void)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_lease();
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_con_mode(aliyun_client_t *aliyun_c, aiot_con_mode_t con_mode, bool is_ssl)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_con_mode(aliyun_c, con_mode, is_ssl);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_host(aliyun_client_t *aliyun_c, char *host)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_host(aliyun_c, host);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_client_id(aliyun_client_t *aliyun_c, char *client_id)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_client_id(aliyun_c, client_id);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_user_name(aliyun_client_t *aliyun_c, char *user_name)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_user_name(aliyun_c, user_name);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_password(aliyun_client_t *aliyun_c, char *password)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_password(aliyun_c, password);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_product_key(aliyun_client_t *aliyun_c, char *product_key)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_product_key(aliyun_c, product_key);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_product_secret(aliyun_client_t *aliyun_c, char *product_secret)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_product_secret(aliyun_c, product_secret);
#else
    uart_printf("not support");
    return NULL;
#endif
}


int32_t mbtk_aliyun_set_device_name(aliyun_client_t *aliyun_c, char *device_name)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_device_name(aliyun_c, device_name);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_device_secret(aliyun_client_t *aliyun_c, char *device_secret)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_device_secret(aliyun_c, device_secret);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_event_handler(aliyun_client_t *aliyun_c, void *event_handler)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_event_handler(aliyun_c, event_handler);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_recv_handler(aliyun_client_t *aliyun_c, void *recv_handler)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_recv_handler(aliyun_c, recv_handler);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_keep_alive_sec(aliyun_client_t *aliyun_c, uint16_t sec)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_keep_alive_sec(aliyun_c, sec);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_heartbeat_interval_ms(aliyun_client_t *aliyun_c, uint32_t interval_ms)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_heartbeat_interval_ms(aliyun_c, interval_ms);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_cmd_timeout(aliyun_client_t *aliyun_c, uint32_t timeout)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_cmd_timeout(aliyun_c, timeout);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_set_clean_session(aliyun_client_t *aliyun_c, uint8_t clean_session)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_set_clean_session(aliyun_c, clean_session);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_device_auth(aliyun_client_t *aliyun_c)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_device_auth(aliyun_c);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_connect(aliyun_client_t *aliyun_c)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_connect(aliyun_c);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_sub(aliyun_client_t *aliyun_c, char *sub_topic, aiot_mqtt_recv_handler_t handler, uint8_t qos)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_sub(aliyun_c, sub_topic, handler, qos);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_pub(aliyun_client_t *aliyun_c, char *pub_topic, char *pub_payload, uint32_t pub_payload_len, uint8_t qos)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_pub(aliyun_c, pub_topic, pub_payload, pub_payload_len, qos);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_unsub(aliyun_client_t *aliyun_c, char *unsub_topic)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_unsub(aliyun_c, unsub_topic);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_disconnect(aliyun_client_t *aliyun_c)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_disconnect(aliyun_c);
#else
    uart_printf("not support");
    return NULL;
#endif
}

int32_t mbtk_aliyun_release(aliyun_client_t *aliyun_c)
{
#ifdef MBTK_ALIYUN_SUPPORT
    return aliyun_disconnect(aliyun_c);
#else
    uart_printf("not support");
    return NULL;
#endif
}


