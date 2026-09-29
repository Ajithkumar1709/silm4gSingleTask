
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

extern aliyun_client_t *mbtk_aliyun_lease(void);
extern int32_t mbtk_aliyun_set_con_mode(aliyun_client_t *aliyun_c, aiot_con_mode_t con_mode, bool is_ssl);
extern int32_t mbtk_aliyun_set_host(aliyun_client_t *aliyun_c, char *host);
extern int32_t mbtk_aliyun_set_port(aliyun_client_t *aliyun_c, uint16_t port);
extern int32_t mbtk_aliyun_set_client_id(aliyun_client_t *aliyun_c, char *client_id);
extern int32_t mbtk_aliyun_set_user_name(aliyun_client_t *aliyun_c, char *user_name);
extern int32_t mbtk_aliyun_set_password(aliyun_client_t *aliyun_c, char *password);
extern int32_t mbtk_aliyun_set_product_key(aliyun_client_t *aliyun_c, char *product_key);
extern int32_t mbtk_aliyun_set_product_secret(aliyun_client_t *aliyun_c, char *product_secret);
extern int32_t mbtk_aliyun_set_device_name(aliyun_client_t *aliyun_c, char *device_name);
extern int32_t mbtk_aliyun_set_device_secret(aliyun_client_t *aliyun_c, char *device_secret);
extern int32_t mbtk_aliyun_set_event_handler(aliyun_client_t *aliyun_c, void *event_handler);
extern int32_t mbtk_aliyun_set_recv_handler(aliyun_client_t *aliyun_c, void *recv_handler);
extern int32_t mbtk_aliyun_set_keep_alive_sec(aliyun_client_t *aliyun_c, uint16_t sec);
extern int32_t mbtk_aliyun_set_heartbeat_interval_ms(aliyun_client_t *aliyun_c, uint32_t interval_ms);
extern int32_t mbtk_aliyun_set_cmd_timeout(aliyun_client_t *aliyun_c, uint32_t timeout);
extern int32_t mbtk_aliyun_set_clean_session(aliyun_client_t *aliyun_c, uint8_t clean_session);
extern int32_t mbtk_aliyun_device_auth(aliyun_client_t *aliyun_c);
extern int32_t mbtk_aliyun_connect(aliyun_client_t *aliyun_c);
extern int32_t mbtk_aliyun_sub(aliyun_client_t *aliyun_c, char *sub_topic, aiot_mqtt_recv_handler_t handler, uint8_t qos);
extern int32_t mbtk_aliyun_pub(aliyun_client_t *aliyun_c, char *pub_topic, char *pub_payload, uint32_t pub_payload_len, uint8_t qos);
extern int32_t mbtk_aliyun_unsub(aliyun_client_t *aliyun_c, char *unsub_topic);
extern int32_t mbtk_aliyun_disconnect(aliyun_client_t *aliyun_c);
extern int32_t mbtk_aliyun_release(aliyun_client_t *aliyun_c);



