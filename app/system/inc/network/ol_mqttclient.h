#ifndef _OL_MQTTCLIENT_H_
#define _OL_MQTTCLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mbtk_pub_type.h"
#include "mbtk_os.h"

#define MQTT_SSL_VERIFY_NONE    0xFFFFFFFF

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
    MQTT_SSL_CERT_ERROR                                     = -0x001C,      /* cetr parse failed */
    MQTT_SOCKET_FAILED_ERROR                                = -0x001B,      /* socket fd failed */
    MQTT_SOCKET_UNKNOWN_HOST_ERROR                          = -0x001A,      /* socket unknown host ip or domain */ 
    MQTT_SET_PUBLISH_DUP_FAILED_ERROR                       = -0x0019,      /* mqtt publish packet set udp bit failed */
    MQTT_CLEAN_SESSION_ERROR                                = -0x0018,      /* mqtt clean session error */
    MQTT_ACK_NODE_IS_EXIST_ERROR                            = -0x0017,      /* mqtt ack list is exist ack node */
    MQTT_ACK_HANDLER_NUM_TOO_MUCH_ERROR                     = -0x0016,      /* mqtt ack handler number is too much */
    MQTT_RESUBSCRIBE_ERROR                                  = -0x0015,      /* mqtt resubscribe error */
    MQTT_SUBSCRIBE_ERROR                                    = -0x0014,      /* mqtt subscribe error */
    MQTT_SEND_PACKET_ERROR                                  = -0x0013,      /* mqtt send a packet */
    MQTT_SERIALIZE_PUBLISH_ACK_PACKET_ERROR                 = -0x0012,      /* mqtt serialize publish ack packet error */
    MQTT_PUBLISH_PACKET_ERROR                               = -0x0011,      /* mqtt publish packet error */
    MQTT_RECONNECT_TIMEOUT_ERROR                            = -0x0010,      /* mqtt try reconnect, but timeout */
    MQTT_SUBSCRIBE_NOT_ACK_ERROR                            = -0x000F,      /* mqtt subscribe, but not ack */
    MQTT_NOT_CONNECT_ERROR                                  = -0x000E,      /* mqtt not connect */
    MQTT_SUBSCRIBE_ACK_PACKET_ERROR                         = -0x000D,      /* mqtt subscribe, but ack packet error */
    MQTT_UNSUBSCRIBE_ACK_PACKET_ERROR                       = -0x000C,      /* mqtt unsubscribe, but ack packet error */
    MQTT_PUBLISH_ACK_PACKET_ERROR                           = -0x000B,      /* mqtt pubilsh ack packet error */
    MQTT_PUBLISH_ACK_TYPE_ERROR                             = -0x000A,      /* mqtt pubilsh ack type error */
    MQTT_PUBREC_PACKET_ERROR                                = -0x0009,      /* mqtt pubrec packet error */
    MQTT_BUFFER_TOO_SHORT_ERROR                             = -0x0008,      /* mqtt buffer too short */
    MQTT_NOTHING_TO_READ_ERROR                              = -0x0007,      /* mqtt nothing to read */
    MQTT_SUBSCRIBE_QOS_ERROR                                = -0x0006,      /* mqtt subsrcibe qos error */
    MQTT_BUFFER_OVERFLOW_ERROR                              = -0x0005,      /* mqtt buffer overflow */
    MQTT_CONNECT_FAILED_ERROR                               = -0x0004,      /* mqtt connect failed */
    MQTT_MEM_NOT_ENOUGH_ERROR                               = -0x0003,      /* mqtt memory not enough */
    MQTT_NULL_VALUE_ERROR                                   = -0x0002,      /* mqtt value is null */
    MQTT_FAILED_ERROR                                       = -0x0001,      /* failed */
    MQTT_SUCCESS_ERROR                                      = 0x0000        /* success */
} ol_mqtt_error_t;



typedef void (*interceptor_handler_t)(void* client, message_data_t* msg);
typedef void (*message_handler_t)(void* client, message_data_t* msg);
typedef void (*reconnect_handler_t)(void* client, void* reconnect_date);
typedef void (*error_handler_t)(void *client, ol_mqtt_error_t error);
typedef void (*mqtt_callback_handler_t)(void* client, mqtt_cmd_id_t cmd_id, ol_mqtt_error_t error);

typedef void mqtt_client_t;

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_client_id
 * DESCRIPTION 
 *  		This API is to set mqtt client id, set is a point, if is malloc string ,can not be free until finish
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    id[IN]               id
 * RETURN VALUES
	    id point
 *****************************************************************************/
extern char* ol_mqtt_set_client_id(mqtt_client_t *, char*);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_user_name
 * DESCRIPTION 
 *  		This API is to set mqtt user name, set is a point, if is malloc string ,can not be free until finish
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    name[IN]               id
 * RETURN VALUES
	    name point
 *****************************************************************************/
extern char* ol_mqtt_set_user_name(mqtt_client_t *, char*);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_password
 * DESCRIPTION 
 *  		This API is to set mqtt password, set is a point, if is malloc string ,can not be free until finish
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    password[IN]               password
 * RETURN VALUES
 *		password point
 *****************************************************************************/
extern char* ol_mqtt_set_password(mqtt_client_t *, char*);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_host
 * DESCRIPTION 
 *  		This API is to set mqtt host, set is a point, if is malloc string ,can not be free until finish
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    host[IN]               			host
 * RETURN VALUES
 *		host point
 *****************************************************************************/
extern char* ol_mqtt_set_host(mqtt_client_t *, char*);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_port
 * DESCRIPTION 
 *  		This API is to set mqtt port, set is a point, if is malloc string ,can not be free until finish
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    port[IN]               			port
 * RETURN VALUES
 *		port point
 *****************************************************************************/
extern char* ol_mqtt_set_port(mqtt_client_t *, char*);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_ssl_vsn
 * DESCRIPTION 
 *  		This API is to set mqtt ssl version
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
 *	  vsn[IN]               		ssl version setting 
 * RETURN VALUES
 		ca point
 *****************************************************************************/
extern uint32_t ol_mqtt_set_ssl_vsn(mqtt_client_t *, uint32_t);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_ca
 * DESCRIPTION 
 *  		This API is to set mqtt ca crt if use ssl connect need ca crt
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    ca[IN]               		buffer hold ca crt 
 * RETURN VALUES
 		ca point
 *****************************************************************************/
extern char* ol_mqtt_set_ca(mqtt_client_t *, char*);
/******************************************************************************
*
* FUNCTIO
*       ol_mqtt_set_cli_crt
* DESCRIPTION
*       This API is to set mqtt client crt if use ssl connect need client crt
* PARAMETERS
        mqtt_client_t[IN]               mqtt client
        cli_crt[IN]               		buffer hold client crt
* RETURN VALUES
        cli_crt point
******************************************************************************/
extern char* ol_mqtt_set_cli_crt(mqtt_client_t *, char*);
/******************************************************************************
*
* FUNCTIO
*       ol_mqtt_set_cli_key
* DESCRIPTION
*       This API is to set mqtt client key if use ssl connect need client key
* PARAMETERS
        mqtt_client_t[IN]               mqtt client
        cli_key[IN]               		buffer hold client key
* RETURN VALUES
        cli_key point
******************************************************************************/
extern char* ol_mqtt_set_cli_key(mqtt_client_t *, char*);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_reconnect_data
 * DESCRIPTION 
 *  		This API is to set mqtt reconnet data
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    data[IN]                      reconnect data
 * RETURN VALUES
 		data point
 *****************************************************************************/
extern void* ol_mqtt_set_reconnect_data(mqtt_client_t *, void*);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_keep_alive_interval
 * DESCRIPTION 
 *  		This API is to set keep alive interval
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    interval[IN]               		interval (ms)
 * RETURN VALUES
 		interval
 *****************************************************************************/
extern uint16_t ol_mqtt_set_keep_alive_interval(mqtt_client_t *, uint16_t);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_ca
 * DESCRIPTION 
 *  		This API is to set mqtt ca srt if use ssl connect need ca crt
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    flag[IN]               		flag
 * RETURN VALUES
 		flag
 *****************************************************************************/
extern uint32_t ol_mqtt_set_will_flag(mqtt_client_t *, uint32_t);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_clean_session
 * DESCRIPTION 
 *  		This API is to set mqtt clean session
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    cleanflag[IN]               	cleanflag
 * RETURN VALUES
 		cleanflag
 *****************************************************************************/
extern uint32_t ol_mqtt_set_clean_session(mqtt_client_t *, uint32_t);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_version
 * DESCRIPTION 
 *  		This API is to set mqtt version
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    version[IN]               version
 * RETURN VALUES
 *		version
 *****************************************************************************/
extern uint32_t ol_mqtt_set_version(mqtt_client_t *, uint32_t);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_cmd_timeout
 * DESCRIPTION 
 *  		This API is to set mqtt cmd timeout time, millisecond
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    timeout[IN]               timeout time(ms)
 * RETURN VALUES
 *		timeout time
 *****************************************************************************/
extern uint32_t ol_mqtt_set_cmd_timeout(mqtt_client_t *, uint32_t);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_read_buf_size
 * DESCRIPTION 
 *  		This API is to set mqtt read buffer size
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    read_buf_size[IN]               read buffer size
 * RETURN VALUES
 *		read_buf_size
 *****************************************************************************/
extern uint32_t ol_mqtt_set_read_buf_size(mqtt_client_t *, uint32_t);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_write_buf_size
 * DESCRIPTION 
 *  		This API is to set mqtt write buffer size
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    read_buf_size[IN]               write buffer size
 * RETURN VALUES
 *		write_buf_size
 *****************************************************************************/
extern uint32_t ol_mqtt_set_write_buf_size(mqtt_client_t *, uint32_t);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_reconnect_try_duration
 * DESCRIPTION 
 *  		This API is to set mqtt reconnect try duration
 * PARAMETERS 
 *		mqtt_client_t[IN]               	 mqtt client
	    reconnect_duration[IN]               duration(ms)
 * RETURN VALUES
 *		duration
 *****************************************************************************/
extern uint32_t ol_mqtt_set_reconnect_try_duration(mqtt_client_t *, uint32_t);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_conn_timeout
 * DESCRIPTION 
 *  		This API is to set mqtt connect timeout
 * PARAMETERS 
 *		mqtt_client_t[IN]               	 mqtt client
	    conn_timeout[IN]               timeout(ms)
 * RETURN VALUES
 *		duration
 *****************************************************************************/
extern uint32_t ol_mqtt_set_conn_timeout(mqtt_client_t *, uint32_t );

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_reconnect_handler
 * DESCRIPTION 
 *  		This API is to set reconnect handler
 * PARAMETERS 
 *		mqtt_client_t[IN]               	 mqtt client
	    reconnect_handler_t[IN]               handler
 * RETURN VALUES
 *		reconnect_handler_t
 *****************************************************************************/
extern reconnect_handler_t ol_mqtt_set_reconnect_handler(mqtt_client_t *, reconnect_handler_t);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_interceptor_handler
 * DESCRIPTION 
 *  		This API is to set interceptor handler
 * PARAMETERS 
 *		mqtt_client_t[IN]               	 mqtt client
	    interceptor_handler_t[IN]               handler
 * RETURN VALUES
 *		interceptor_handler_t
 *****************************************************************************/
extern interceptor_handler_t ol_mqtt_set_interceptor_handler(mqtt_client_t *, interceptor_handler_t);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_error_callback
 * DESCRIPTION 
 *  		This API is to set interceptor handler
 * PARAMETERS 
 *		mqtt_client_t[IN]               	 mqtt client
	    error_handler_t[IN]               handler
 * RETURN VALUES
 *		error_handler_t
 *****************************************************************************/
extern int ol_mqtt_set_error_callback(mqtt_client_t*, error_handler_t);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_lease
 * DESCRIPTION 
 *  		This API is to create mqtt client 
 * PARAMETERS 
 *		void
 * RETURN VALUES
          NULL            create error
          not NULL        mqtt_client_t
 *****************************************************************************/

extern mqtt_client_t *ol_mqtt_lease(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_release
 * DESCRIPTION 
 *  		This API is to release mqtt client 
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    opt[IN]               set audio callbacke					enum {
																		 HTTPCLIENT_GETINFO_RESPONSE_CODE,
																		 HTTPCLIENT_GETINFO_TCP_STATE,
																	 };
		value[OUT]                option value
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_release(mqtt_client_t* );

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_connect
 * DESCRIPTION 
 *  		This API is to connect to mqtt server, this command is block
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_connect(mqtt_client_t* );

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_disconnect
 * DESCRIPTION 
 *  		This API is to disconnet from mqtt server
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_disconnect(mqtt_client_t* );

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_http_client_getinfo
 * DESCRIPTION 
 *  		This API is to send keep alive to server
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_keep_alive(mqtt_client_t* );


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_subscribe
 * DESCRIPTION 
 *  		This API is to subscribe topic 
 * PARAMETERS 
 *		mqtt_client_t[IN]           mqtt client
 *	    topic[IN]			   		topic_filter string
 		qos[IN]                    qos         [0,1,2]
 		message_handler_t          message handler
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_subscribe(mqtt_client_t* , const char* topic_filter, mqtt_qos_t , message_handler_t );

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_unsubscribe
 * DESCRIPTION 
 *  		This API is to unsubscribe topic
 * PARAMETERS 
 *		mqtt_client_t[IN]           mqtt client
 *	    topic_filter[IN]			topic_filter string
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_unsubscribe(mqtt_client_t* , const char* topic_filter);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_publish
 * DESCRIPTION 
 *  		This API is to public message
 * PARAMETERS 
 *		mqtt_client_t[IN]           mqtt client
 *	    topic[IN]			   		topic string
 		msg[IN]                     publish message
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_publish(mqtt_client_t* , const char* topic, mqtt_message_t* msg);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_list_subscribe_topic
 * DESCRIPTION 
 *  		This API is to list subscribe topic, (only list in log)
 * PARAMETERS 
 *		mqtt_client_t[IN]           mqtt client
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_list_subscribe_topic(mqtt_client_t* c);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_set_will_options
 * DESCRIPTION 
 *  		This API is to set will option
 * PARAMETERS 
 *		mqtt_client_t[IN]           mqtt client
 *	    topic[IN]			   		topic string
 		qos[IN]                     qos
		retained[IN]				retained
		message[IN]					message	
 		
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_set_will_options(mqtt_client_t* c, char *topic_filter, mqtt_qos_t qos, uint8_t retained, char *message);  

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_connect_asyn
 * DESCRIPTION 
 *  		This API is to connect to mqtt server with non block mode
 * PARAMETERS 
 *		http_client_list[IN]               http client
	    callback_handle						callback function when receve message
	    									typedef enum {
											    MQTT_CMDID_CONNECT = 1,         
											    MQTT_CMDID_SUBSCRIBE,             
											    MQTT_CMDID_UNSUBSCRIBE,        
											    MQTT_CMDID_PUBLISH,
											    MQTT_CMDID_KEEP_ALIVE,
											    MQTT_CMDID_DISCONNECT,           
											    MQTT_CMDID_RESEALE,           
											}mqtt_cmd_id_t;
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_connect_asyn(mqtt_client_t* c,mqtt_callback_handler_t callback_handle);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_subscribe_asyn
 * DESCRIPTION 
 *  		This API is to subscribe topic with non block mode
 * PARAMETERS 
 *		mqtt_client_t[IN]               client
	    topic_filter[IN]               topic_filter
		qos[IN]                			qos
		handler[IN]
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_subscribe_asyn(mqtt_client_t* c, const char* topic_filter, mqtt_qos_t qos, void *handler);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_unsubscribe_asyn
 * DESCRIPTION 
 *  		This API is to unsubscribe topic from server
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    topic_filter[IN]               topic_filter string
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_unsubscribe_asyn(mqtt_client_t* c, const char* topic_filter);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_publish_asyn
 * DESCRIPTION 
 *  		This API is to publish message to server
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
	    topic_filter[IN]               topic_filter string
	    msg[IN]						   message
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_publish_asyn(mqtt_client_t* c, const char* topic_filter, mqtt_message_t* msg);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_keep_alive_asyn
 * DESCRIPTION 
 *  		This API is to send keep alive message to server
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_keep_alive_asyn(mqtt_client_t* c);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_disconnect_asyn
 * DESCRIPTION 
 *  		This API is to disconnect from mqtt server
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_disconnect_asyn(mqtt_client_t* c);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mqtt_release_asyn
 * DESCRIPTION 
 *  		This API is to release mqtt client
 * PARAMETERS 
 *		mqtt_client_t[IN]               mqtt client
 * RETURN VALUES
 *		ol_mqtt_error_t
 *****************************************************************************/
extern int ol_mqtt_release_asyn(mqtt_client_t* c);

#ifdef __cplusplus
}
#endif

#endif
