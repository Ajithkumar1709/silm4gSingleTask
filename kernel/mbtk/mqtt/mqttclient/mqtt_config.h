/*
 * @Author: jiejie
 * @Github: https://github.com/jiejieTop
 * @LastEditTime: 2020-09-14 14:55:11
 * @Description: the code belongs to jiejie, please keep the author information and source code according to the license.
 */
#ifndef _MQTT_CONFIG_H_
#define _MQTT_CONFIG_H_

#define KAWAII_MQTT_LOG_BASE_LEVEL      (0)
#define KAWAII_MQTT_LOG_ERR_LEVEL       (KAWAII_MQTT_LOG_BASE_LEVEL + 1)
#define KAWAII_MQTT_LOG_WARN_LEVEL      (KAWAII_MQTT_LOG_ERR_LEVEL + 1)
#define KAWAII_MQTT_LOG_INFO_LEVEL      (KAWAII_MQTT_LOG_WARN_LEVEL + 1)
#define KAWAII_MQTT_LOG_DEBUG_LEVEL     (KAWAII_MQTT_LOG_INFO_LEVEL + 1)

#define KAWAII_MQTT_LOG_MAX_LENGTH      (256)

/*Customer log defined here!!!*/
#undef mqtt_printf
//#include "UART.h"
#include "diag_API.h"
//#define mqtt_printf(fmt,args...)	    CPUartLogPrintf(fmt, ##args)

static inline void mqtt_log_printf(const char *fmt, ...)
{
    va_list ap;
    char mqtt_log_buffer[KAWAII_MQTT_LOG_MAX_LENGTH];
    memset(mqtt_log_buffer, 0, KAWAII_MQTT_LOG_MAX_LENGTH);

    va_start(ap, fmt);
    vsnprintf(mqtt_log_buffer, KAWAII_MQTT_LOG_MAX_LENGTH, fmt, ap);
    va_end(ap);

    DIAG_FILTER(MIFI, MQTT, LOG, DIAG_INFORMATION);
    diagPrintf("%s", mqtt_log_buffer);
}

#define mqtt_printf(fmt,args...)        mqtt_log_printf(fmt, ##args)

#define KAWAII_MQTT_LOG_LEVEL           (KAWAII_MQTT_LOG_DEBUG_LEVEL)


#if 1//ndef REMOVE_MBEDTLS
#define KAWAII_MQTT_NETWORK_TYPE_TLS
#endif
#define KAWAII_MQTT_MAX_PACKET_ID                  (0xFFFF - 1)
#define KAWAII_MQTT_TOPIC_LEN_MAX                  128
#define KAWAII_MQTT_ACK_HANDLER_NUM_MAX            64
#define KAWAII_MQTT_DEFAULT_BUF_SIZE               1024
#define KAWAII_MQTT_DEFAULT_CMD_TIMEOUT            5000
#define KAWAII_MQTT_MAX_CMD_TIMEOUT                20000
#define KAWAII_MQTT_MIN_CMD_TIMEOUT                1000
#define KAWAII_MQTT_KEEP_ALIVE_INTERVAL            50         // unit: second
#define KAWAII_MQTT_VERSION                        4           // 4 is mqtt 3.1.1
#define KAWAII_MQTT_RECONNECT_DEFAULT_DURATION     1000
#define KAWAII_MQTT_THREAD_STACK_SIZE              4096
#define KAWAII_MQTT_THREAD_PRIO                    90
#define KAWAII_MQTT_THREAD_TICK                    50

#endif /* _MQTT_CONFIG_H_ */
