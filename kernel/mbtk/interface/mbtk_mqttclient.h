#ifndef _MBTK_MQTTCLIENT_H_
#define _MBTK_MQTTCLIENT_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "mbtk_os.h"
#include "mbtk_pub_type.h"

typedef enum mqtt_qos {
    QOS0 = 0,
    QOS1 = 1,
    QOS2 = 2,
    SUBFAIL = 0x80
} mqtt_qos_t;

typedef enum client_state {
	CLIENT_STATE_INVALID = -1,
	CLIENT_STATE_INITIALIZED = 0,
	CLIENT_STATE_CONNECTED = 1,
	CLIENT_STATE_DISCONNECTED = 2,
    CLIENT_STATE_CLEAN_SESSION = 3
}client_state_t;
	
typedef enum {
	MQTT_CMDID_CONNECT = 1, 		
	MQTT_CMDID_SUBSCRIBE,			  
	MQTT_CMDID_UNSUBSCRIBE, 	   
	MQTT_CMDID_PUBLISH,
	MQTT_CMDID_KEEP_ALIVE,
	MQTT_CMDID_DISCONNECT,			 
	MQTT_CMDID_RESEALE, 		  
 
}mqtt_cmd_id_t;

typedef enum mqtt_error {
	KAWAII_MQTT_SSL_CERT_ERROR									   = -0x001C,	   /* cetr parse failed */
	KAWAII_MQTT_SOCKET_FAILED_ERROR 							   = -0x001B,	   /* socket fd failed */
	KAWAII_MQTT_SOCKET_UNKNOWN_HOST_ERROR						   = -0x001A,	   /* socket unknown host ip or domain */ 
	KAWAII_MQTT_SET_PUBLISH_DUP_FAILED_ERROR					   = -0x0019,	   /* mqtt publish packet set udp bit failed */
	KAWAII_MQTT_CLEAN_SESSION_ERROR 							   = -0x0018,	   /* mqtt clean session error */
	KAWAII_MQTT_ACK_NODE_IS_EXIST_ERROR 						   = -0x0017,	   /* mqtt ack list is exist ack node */
	KAWAII_MQTT_ACK_HANDLER_NUM_TOO_MUCH_ERROR					   = -0x0016,	   /* mqtt ack handler number is too much */
	KAWAII_MQTT_RESUBSCRIBE_ERROR								   = -0x0015,	   /* mqtt resubscribe error */
	KAWAII_MQTT_SUBSCRIBE_ERROR 								   = -0x0014,	   /* mqtt subscribe error */
	KAWAII_MQTT_SEND_PACKET_ERROR								   = -0x0013,	   /* mqtt send a packet */
	KAWAII_MQTT_SERIALIZE_PUBLISH_ACK_PACKET_ERROR				   = -0x0012,	   /* mqtt serialize publish ack packet error */
	KAWAII_MQTT_PUBLISH_PACKET_ERROR							   = -0x0011,	   /* mqtt publish packet error */
	KAWAII_MQTT_RECONNECT_TIMEOUT_ERROR 						   = -0x0010,	   /* mqtt try reconnect, but timeout */
	KAWAII_MQTT_SUBSCRIBE_NOT_ACK_ERROR 						   = -0x000F,	   /* mqtt subscribe, but not ack */
	KAWAII_MQTT_NOT_CONNECT_ERROR								   = -0x000E,	   /* mqtt not connect */
	KAWAII_MQTT_SUBSCRIBE_ACK_PACKET_ERROR						   = -0x000D,	   /* mqtt subscribe, but ack packet error */
	KAWAII_MQTT_UNSUBSCRIBE_ACK_PACKET_ERROR					   = -0x000C,	   /* mqtt unsubscribe, but ack packet error */
	KAWAII_MQTT_PUBLISH_ACK_PACKET_ERROR						   = -0x000B,	   /* mqtt pubilsh ack packet error */
	KAWAII_MQTT_PUBLISH_ACK_TYPE_ERROR							   = -0x000A,	   /* mqtt pubilsh ack type error */
	KAWAII_MQTT_PUBREC_PACKET_ERROR 							   = -0x0009,	   /* mqtt pubrec packet error */
	KAWAII_MQTT_BUFFER_TOO_SHORT_ERROR							   = -0x0008,	   /* mqtt buffer too short */
	KAWAII_MQTT_NOTHING_TO_READ_ERROR							   = -0x0007,	   /* mqtt nothing to read */
	KAWAII_MQTT_SUBSCRIBE_QOS_ERROR 							   = -0x0006,	   /* mqtt subsrcibe qos error */
	KAWAII_MQTT_BUFFER_OVERFLOW_ERROR							   = -0x0005,	   /* mqtt buffer overflow */
	KAWAII_MQTT_CONNECT_FAILED_ERROR							   = -0x0004,	   /* mqtt connect failed */
	KAWAII_MQTT_MEM_NOT_ENOUGH_ERROR							   = -0x0003,	   /* mqtt memory not enough */
	KAWAII_MQTT_NULL_VALUE_ERROR								   = -0x0002,	   /* mqtt value is null */
	KAWAII_MQTT_FAILED_ERROR									   = -0x0001,	   /* failed */
	KAWAII_MQTT_SUCCESS_ERROR									   = 0x0000 	   /* success */
} ol_mqtt_error_t;

typedef struct platform_timer {
    uint32_t time;
} platform_timer_t;

typedef struct platform_mutex {
    void * mutex;
} platform_mutex_t;

typedef struct mqtt_list_node {
    struct mqtt_list_node *next;
    struct mqtt_list_node *prev;
} mqtt_list_t;

typedef struct network {
    const char                  *host;
    const char                  *port;
    int                         socket;
#if 1//def KAWAII_MQTT_NETWORK_TYPE_TLS
    int                         channel;        /* tcp or tls */
    const char                  *ca_crt;
    const char                  *cli_crt;
    const char                  *cli_key;
    unsigned int                ca_crt_len;
    unsigned int                cli_crt_len;
    unsigned int                cli_key_len;
    unsigned int                timeout_ms;            // SSL handshake timeout in millisecond
    void                        *nettype_tls_params;
#endif
} network_t;

typedef struct platform_thread {
    mbtk_taskref thread;
} platform_thread_t;

typedef struct mqtt_connack_data {
    uint8_t rc;
    uint8_t session_present;
} mqtt_connack_data_t;

typedef struct mqtt_message {
    mqtt_qos_t          qos;
    uint8_t             retained;
    uint8_t             dup;
    uint16_t            id;
    size_t              payloadlen;
    void                *payload;
} mqtt_message_t;

typedef struct message_data {
    char                topic_name[128];
    mqtt_message_t      *message;
} message_data_t;

typedef void (*interceptor_handler_t)(void* client, message_data_t* msg);
typedef void (*message_handler_t)(void* client, message_data_t* msg);
typedef void (*reconnect_handler_t)(void* client, void* reconnect_date);
typedef void (*error_handler_t)(void *client, ol_mqtt_error_t error);
typedef void (*mqtt_callback_handler_t)(void* client, mqtt_cmd_id_t cmd_id, ol_mqtt_error_t error);

typedef struct message_handlers {
    mqtt_list_t         list;
    mqtt_qos_t          qos;
    const char*         topic_filter;
    message_handler_t   handler;
} message_handlers_t;

typedef struct ack_handlers {
    mqtt_list_t         list;
    platform_timer_t    timer;
    uint32_t            type;
    uint16_t            packet_id;
    message_handlers_t  *handler;
    uint16_t            payload_len;
    uint8_t             *payload;
} ack_handlers_t;

typedef struct mqtt_will_options {
    mqtt_qos_t          will_qos;
    uint8_t             will_retained;
    char                *will_topic;
    char                *will_message;
} mqtt_will_options_t;

typedef struct mqtt_client {
    char                        *mqtt_client_id;
    char                        *mqtt_user_name;
    char                        *mqtt_password;
    char                        *mqtt_host;
    char                        *mqtt_port;
    char                        *mqtt_ca;
    char                        *mqtt_cli_crt;
    char                        *mqtt_cli_key;
    void                        *mqtt_reconnect_data;
    uint8_t                     *mqtt_read_buf;
    uint8_t                     *mqtt_write_buf;
    uint16_t                    mqtt_keep_alive_interval;
    uint16_t                    mqtt_packet_id;
    uint32_t                    mqtt_will_flag          : 1;
    uint32_t                    mqtt_clean_session      : 1;
    uint32_t                    mqtt_ping_outstanding   : 2;
    uint32_t                    mqtt_version            : 4;
    uint32_t                    mqtt_ack_handler_number : 24;
    uint32_t                    mqtt_cmd_timeout;
	uint32_t                    mqtt_conn_timeout;	
    uint32_t                    mqtt_read_buf_size;
    uint32_t                    mqtt_write_buf_size;
    uint32_t                    mqtt_reconnect_try_duration;
    size_t                      mqtt_client_id_len;
    size_t                      mqtt_user_name_len;
    size_t                      mqtt_password_len;
    mqtt_will_options_t         *mqtt_will_options;
    client_state_t              mqtt_client_state;
    platform_mutex_t            mqtt_write_lock;
    platform_mutex_t            mqtt_global_lock;
    mqtt_list_t                 mqtt_msg_handler_list;
    mqtt_list_t                 mqtt_ack_handler_list;
    network_t                   *mqtt_network;
    platform_thread_t           *mqtt_thread;
    platform_timer_t            mqtt_last_sent;
    platform_timer_t            mqtt_last_received;
    reconnect_handler_t         mqtt_reconnect_handler;
    error_handler_t             mqtt_error_callback;
    interceptor_handler_t       mqtt_interceptor_handler;
} mqtt_client_t;



#define KAWAII_MQTT_CLIENT_SET_STATEMENT(name, type)           \
    extern type mqtt_set_##name(mqtt_client_t *, type);

KAWAII_MQTT_CLIENT_SET_STATEMENT(client_id, char*)
KAWAII_MQTT_CLIENT_SET_STATEMENT(user_name, char*)
KAWAII_MQTT_CLIENT_SET_STATEMENT(password, char*)
KAWAII_MQTT_CLIENT_SET_STATEMENT(host, char*)
KAWAII_MQTT_CLIENT_SET_STATEMENT(port, char*)
KAWAII_MQTT_CLIENT_SET_STATEMENT(ca, char*)
KAWAII_MQTT_CLIENT_SET_STATEMENT(reconnect_data, void*)
KAWAII_MQTT_CLIENT_SET_STATEMENT(keep_alive_interval, uint16_t)
KAWAII_MQTT_CLIENT_SET_STATEMENT(will_flag, uint32_t)
KAWAII_MQTT_CLIENT_SET_STATEMENT(clean_session, uint32_t)
KAWAII_MQTT_CLIENT_SET_STATEMENT(version, uint32_t)
KAWAII_MQTT_CLIENT_SET_STATEMENT(cmd_timeout, uint32_t)
KAWAII_MQTT_CLIENT_SET_STATEMENT(read_buf_size, uint32_t)
KAWAII_MQTT_CLIENT_SET_STATEMENT(write_buf_size, uint32_t)
KAWAII_MQTT_CLIENT_SET_STATEMENT(reconnect_try_duration, uint32_t)
KAWAII_MQTT_CLIENT_SET_STATEMENT(reconnect_handler, reconnect_handler_t)
KAWAII_MQTT_CLIENT_SET_STATEMENT(error_callback, error_handler_t)
KAWAII_MQTT_CLIENT_SET_STATEMENT(interceptor_handler, interceptor_handler_t)
KAWAII_MQTT_CLIENT_SET_STATEMENT(conn_timeout, uint32_t)

extern void mqtt_sleep_ms(uint32_t ms);
extern mqtt_client_t *mqtt_lease(void);
extern int mqtt_release(mqtt_client_t* c);
extern int mqtt_connect(mqtt_client_t* c);
extern int mqtt_disconnect(mqtt_client_t* c);
extern int mqtt_keep_alive(mqtt_client_t* c);
extern int mqtt_subscribe(mqtt_client_t* c, const char* topic_filter, mqtt_qos_t qos, message_handler_t msg_handler);
extern int mqtt_unsubscribe(mqtt_client_t* c, const char* topic_filter);
extern int mqtt_publish(mqtt_client_t* c, const char* topic_filter, mqtt_message_t* msg);
extern int mqtt_list_subscribe_topic(mqtt_client_t* c);
extern int mqtt_set_will_options(mqtt_client_t* c, char *topic, mqtt_qos_t qos, uint8_t retained, char *message);
extern int mqtt_connect_asyn(mqtt_client_t* c,mqtt_callback_handler_t callback_handle);
extern int mqtt_subscribe_asyn(mqtt_client_t* c, const char* topic_filter, mqtt_qos_t qos, void *handler);
extern int mqtt_unsubscribe_asyn(mqtt_client_t* c, const char* topic_filter);
extern int mqtt_publish_asyn(mqtt_client_t* c, const char* topic_filter, mqtt_message_t* msg);
extern int mqtt_keep_alive_asyn(mqtt_client_t* c);
extern int mqtt_disconnect_asyn(mqtt_client_t* c);
extern int mqtt_release_asyn(mqtt_client_t* c);

#endif /* _MQTTCLIENT_H_ */

