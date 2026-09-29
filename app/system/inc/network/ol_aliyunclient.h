#ifndef _OL_ALIYUNCLIENT_H_
#define _OL_ALIYUNCLIENT_H_

#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    MQTT_DIRECT_CONNECTION,
    
    ONE_MACHINE_ONE_SECRET,
        
    ONE_TYPE_ONE_SECRET_WL,
    
    ONE_TYPE_ONE_SECRET_NWL,

} aiot_con_mode_t;


typedef enum {
    AIOT_MQTTRECV_PUB,
        
    AIOT_MQTTRECV_HEARTBEAT_RESPONSE,
    
    AIOT_MQTTRECV_SUB_ACK,
    
    AIOT_MQTTRECV_UNSUB_ACK,
    
    AIOT_MQTTRECV_PUB_ACK,

} aiot_mqtt_recv_type_t;


typedef enum {
    AIOT_MQTTEVT_CONNECT,
        
    AIOT_MQTTEVT_RECONNECT,
    
    AIOT_MQTTEVT_DISCONNECT
    
} aiot_mqtt_event_type_t;

typedef enum {
    AIOT_MQTTDISCONNEVT_NETWORK_DISCONNECT,
        
    AIOT_MQTTDISCONNEVT_HEARTBEAT_DISCONNECT
} aiot_mqtt_disconnect_event_type_t;

typedef struct {
    aiot_mqtt_event_type_t type;
    union {
        aiot_mqtt_disconnect_event_type_t disconnect;
    } data;
} aiot_mqtt_event_t;


typedef struct {
    char *host;
    uint16_t port;
    char *client_id;
    char *user_name;
    char *password;
    char *product_key;
    char *product_secret;
    char *device_name;
    char *device_secret;
    aiot_con_mode_t con_mode;
    bool is_ssl;
    void *process_thread;
    void *recv_thread;
    void *event_handler_cb;
    void *recv_handler_cb;
    void *mqtt_handle;
}aliyun_client_t;

typedef struct {
    aiot_mqtt_recv_type_t type;
    union {
        struct {
            uint8_t qos;
            char *topic;
            uint16_t topic_len;
            uint8_t *payload;
            uint32_t payload_len;
        } pub;
        struct {
            int32_t res;
            uint8_t max_qos;
            uint16_t packet_id;
        } sub_ack;
        struct {
            uint16_t packet_id;
        } unsub_ack;
        struct {
            uint16_t packet_id;
        } pub_ack;
    } data;
} aiot_mqtt_recv_t;

typedef void (*aiot_mqtt_recv_handler_t)(void *handle, const aiot_mqtt_recv_t *packet, void *userdata);


/*****************************************************************************
 *
 * FUNCTION 
 *      ol_aliyun_lease
 * DESCRIPTION 
 *      This API is to create mqtt client.
 * PARAMETERS 
        void
 * RETURN VALUES
         NULL            create error
         not NULL        create sucess
 *****************************************************************************/
extern aliyun_client_t *ol_aliyun_lease(void);

/*****************************************************************************
 *
 * FUNCTION 
 *      ol_aliyun_set_con_mode
 * DESCRIPTION 
 *      This API is to set aliyun connection mode.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        aiot_con_mode_t[IN]             connection mode
            typedef enum {
             MQTT_DIRECT_CONNECTION,
             ONE_MACHINE_ONE_SECRET,
             ONE_TYPE_ONE_SECRET_WL,
             ONE_TYPE_ONE_SECRET_NWL,
            } aiot_con_mode_t;
        bool[IN]                      is_ssl
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_con_mode(aliyun_client_t *aliyun_c, aiot_con_mode_t con_mode, bool is_ssl);

/*****************************************************************************
 *
 * FUNCTION 
 *      ol_aliyun_set_host
 * DESCRIPTION 
 *      This API is to set aliyun host.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        char*[IN]                       host
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_host(aliyun_client_t *aliyun_c, char *host);

/*****************************************************************************
 *
 * FUNCTION 
 *      ol_aliyun_set_client_id
 * DESCRIPTION 
 *      This API is to set aliyun mqtt client_id.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        char*[IN]                       client_id
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_client_id(aliyun_client_t *aliyun_c, char *client_id);

/*****************************************************************************
 *
 * FUNCTION 
 *      ol_aliyun_set_user_name
 * DESCRIPTION 
 *      This API is to set aliyun mqtt user_name.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        char*[IN]                       user_name
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_user_name(aliyun_client_t *aliyun_c, char *user_name);

/*****************************************************************************
 *
 * FUNCTION 
 *      ol_aliyun_set_password
 * DESCRIPTION 
 *      This API is to set aliyun mqtt password.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        char*[IN]                       password
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_password(aliyun_client_t *aliyun_c, char *password);

/*****************************************************************************
 *
 * FUNCTION 
 *      ol_aliyun_set_product_key
 * DESCRIPTION 
 *      This API is to set aliyun product key.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        char*[IN]                       product_key
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_product_key(aliyun_client_t *aliyun_c, char *product_key);

/*****************************************************************************
 *
 * FUNCTION 
 *      ol_aliyun_set_product_secret
 * DESCRIPTION 
 *      This API is to set aliyun product secret.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        char*[IN]                       product_secret
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_product_secret(aliyun_client_t *aliyun_c, char *product_secret);

/*****************************************************************************
 *
 * FUNCTION 
 *      ol_aliyun_set_device_name
 * DESCRIPTION 
 *      This API is to set aliyun device name.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        char*[IN]                       device_name
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_device_name(aliyun_client_t *aliyun_c, char *device_name);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_set_device_secret
 * DESCRIPTION 
 *      This API is to set aliyun device secret.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        char*[IN]                       device_secret
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_device_secret(aliyun_client_t *aliyun_c, char *device_secret);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_set_event_handler
 * DESCRIPTION 
 *      This API is to set aliyun event handler call_back FUNCTIONn.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        void*[IN]                       event_handler call_back FUNCTIONn
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_event_handler(aliyun_client_t *aliyun_c, void *event_handler);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_set_recv_handler
 * DESCRIPTION 
 *      This API is to set aliyun event handler call_back FUNCTIONn.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        void*[IN]                       event_handler call_back FUNCTIONn
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_recv_handler(aliyun_client_t *aliyun_c, void *recv_handler);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_set_keep_alive_sec
 * DESCRIPTION 
 *      This API is to set aliyun keep_alive_sec.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        uint16_t[IN]                    sec
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_keep_alive_sec(aliyun_client_t *aliyun_c, uint16_t sec);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_set_heartbeat_interval_ms
 * DESCRIPTION 
 *      This API is to set aliyun heartbeat_interval_ms.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        uint32_t[IN]                    interval_ms
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_heartbeat_interval_ms(aliyun_client_t *aliyun_c, uint32_t interval_ms);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_set_cmd_timeout
 * DESCRIPTION 
 *      This API is to set aliyun send and recv timeout.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        uint32_t[IN]                    timeout
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_cmd_timeout(aliyun_client_t *aliyun_c, uint32_t timeout);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_set_clean_session
 * DESCRIPTION 
 *      This API is to set aliyun clean_session.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        uint8_t[IN]                     clean_session
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_set_clean_session(aliyun_client_t *aliyun_c, uint8_t clean_session);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_device_auth
 * DESCRIPTION 
 *      This API is to auth aliyun device.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_device_auth(aliyun_client_t *aliyun_c);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_connect
 * DESCRIPTION 
 *      This API is to connect to aliyun.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_connect(aliyun_client_t *aliyun_c);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_sub
 * DESCRIPTION 
 *      This API is to subscribe topic.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        char*[IN]                       sub_topic
        aiot_mqtt_recv_handler_t[IN]    handler
        uint8_t[IN]                     qos
 * RETURN VALUES
         -1                     error
        >=0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_sub(aliyun_client_t *aliyun_c, char *sub_topic, aiot_mqtt_recv_handler_t handler, uint8_t qos);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_pub
 * DESCRIPTION 
 *      This API is to public message.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        char*[IN]                       pub_topic
        char*[IN]                       pub_payload
        uint32_t[IN]                    pub_payload_len
        uint8_t                         qos
 * RETURN VALUES
         -1                     error
        >=0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_pub(aliyun_client_t *aliyun_c, char *pub_topic, char *pub_payload, uint32_t pub_payload_len, uint8_t qos);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_unsub
 * DESCRIPTION 
 *      This API is to unsubscribe topic.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
        char*[IN]                       unsub_topic
 * RETURN VALUES
         -1                     error
        >=0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_unsub(aliyun_client_t *aliyun_c, char *unsub_topic);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_disconnect
 * DESCRIPTION 
 *      This API is to disconnect from aliyun.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_disconnect(aliyun_client_t *aliyun_c);

/*****************************************************************************
 *
 * FUNCTIONN 
 *      ol_aliyun_release
 * DESCRIPTION 
 *      This API is to realse aliyun client.
 * PARAMETERS 
        aliyun_client_t[IN]             aliyun client
 * RETURN VALUES
         -1                     error
          0                     sucess
 *****************************************************************************/
extern int32_t ol_aliyun_release(aliyun_client_t *aliyun_c);


#ifdef __cplusplus
}
#endif

#endif