#include "mbtk_comm_api.h"
#include "ol_mqttclient.h"
#include "mbtk_datacall_api.h"
#include "mbtk_device_api.h"
#include "mbtk_sim_api.h"
#include "ntp_api.h"
#include "ol_nw_api.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "modules/publish.h"
#include "modules/rpcHandler.h"

#define RPC_BUF_SIZE 256
static char rpc_buf[RPC_BUF_SIZE];

static void configSend(uint8_t *payload, unsigned short datalength)
{
    unsigned short len = datalength;

    if (len >= sizeof(rpc_buf))
    {
        len = sizeof(rpc_buf) - 1;
    }
    memset(rpc_buf, 0x00, sizeof(rpc_buf));
    memcpy(rpc_buf, payload, len);
    jsonextract(rpc_buf);
}

#define MQTT_TASK_CID mbtk_cid_index_2
#define MQTT_TASK_PDN mbtk_data_call_v4v6
#define MQTT_TASK_HOST "iotpro.io"
#define MQTT_TASK_PORT "9114"

static char mqtt_client_imei[17];
 uint8_t mqtt_connected=0;

typedef enum
{
    MQTT_STATE_NETWORK_REGISTER,
    MQTT_STATE_DATA_CALL,
    MQTT_STATE_CLIENT_INIT,
    MQTT_STATE_CONNECT,
    MQTT_STATE_SUBSCRIBE,
    MQTT_STATE_EXIT
} mqtt_state_t;

static void mqtt_task_error(void *client, ol_mqtt_error_t error)
{
    (void)client;
    op_uart_printf("-1-mqttTask:error: %d\r\n", error);

    switch (error)
    {
    /* Genuine connection-breaking errors: force a reconnect */
    case MQTT_SOCKET_FAILED_ERROR:
    case MQTT_SOCKET_UNKNOWN_HOST_ERROR:
    case MQTT_CONNECT_FAILED_ERROR:
    case MQTT_NOT_CONNECT_ERROR:
    case MQTT_RECONNECT_TIMEOUT_ERROR:
    case MQTT_SSL_CERT_ERROR:
    case MQTT_SEND_PACKET_ERROR:
        mqtt_connected = 0;
        break;

    /* Benign/transient notifications (e.g. nothing to read this poll):
       keep the connection alive, just log it */
    default:
        break;
    }
}

volatile unsigned char sharedAttrResponseReceived = 0;

static void mqtt_task_attr_response_message(void *client, message_data_t *message)
{
    (void)client;

    if (message->message->payload != NULL && message->message->payloadlen > 0)
    {
        op_uart_printf("-1-mqttTask:shared attr response len=%d\r\n", (int)message->message->payloadlen);
        configSend((uint8_t *)message->message->payload, (unsigned short)message->message->payloadlen);
        sharedAttrResponseReceived = 1;
    }
}

int mqtt_publish(mqtt_client_t *client, void *data,
                 size_t data_size, uint8_t topic)
{
    mqtt_message_t message = {0};
    const char *topic_name;
    int result;

      char *jsonStr = NULL;
      int jsonLen = 0;
  
    if (client == NULL || data == NULL || data_size == 0)
    {
        return -1;
    }

    if (topic == 1)
    {
        topic_name = "v1/devices/me/telemetry";
        jsonStr = extractJsonData(data, data_size);
        if (jsonStr != NULL) {
         jsonLen = strlen(jsonStr);
         }
        data_size=jsonLen;
        data=jsonStr;
    }
    else if (topic == 2)
    {
        topic_name = "v1/devices/me/attributes";
    }
       else if (topic == 3)
    {
        topic_name = "v1/devices/me/attributes";
        jsonStr = extractJsonConfigAttributesData(data, data_size);
        if (jsonStr != NULL) {
         jsonLen = strlen(jsonStr);
         }
        data_size=jsonLen;
        data=jsonStr;
    }
    else if (topic == 4)
    {
        topic_name = "v1/devices/me/attributes/request/1";
    }
    else
    {
        return -1;
    }

    message.qos = QOS1;
    message.payload = data;
    message.payloadlen = data_size;
    op_uart_printf("-1-mqttTask:publish topic=%s payload=%.*s\r\n",
                   topic_name, (int)data_size, (char *)data);
    result = ol_mqtt_publish(client, topic_name, &message);
    if (result != 0)
    {
        mqtt_connected = 0;
    }

    return result;
}

static char *mqtt_task_get_apn(void)
{
    ol_OPERATOR_INFO operator_info = {0};
    char operator_name[sizeof(operator_info.long_eons)];
    size_t name_length;

    if (ol_nw_get_operator_info(&operator_info) != 0)
    {
        op_uart_printf("-1-mqttTask:operator info failed, using default APN\r\n");
        return "www";
    }

    strncpy(operator_name, operator_info.long_eons, sizeof(operator_name) - 1);
    operator_name[sizeof(operator_name) - 1] = '\0';
    if (operator_name[0] == '\0')
    {
        strncpy(operator_name, operator_info.short_eons, sizeof(operator_name) - 1);
        operator_name[sizeof(operator_name) - 1] = '\0';
    }

    op_uart_printf("-1-mqttTask:operator long_eons=%s short_eons=%s\r\n",
                   operator_info.long_eons, operator_info.short_eons);

    name_length = strlen(operator_name);
    for (size_t index = 0; index < name_length; index++)
    {
        operator_name[index] = (char)toupper((unsigned char)operator_name[index]);
    }

    if (strstr(operator_name, "AIRTEL") != NULL)
    {
        return "airtelgprs.com";
    }
    if (strstr(operator_name, "CELLONE") != NULL ||
        strstr(operator_name, "BSNL") != NULL)
    {
        return "bsnlnet";
    }
    if (strstr(operator_name, "VI") != NULL ||
        strstr(operator_name, "VODAFONE") != NULL)
    {
        return "www";
    }
    if (strstr(operator_name, "JIO") != NULL)
    {
        return "jionet";
    }

    return "www";
}

static int MinimumFunality(void)
{
    int result;

    op_uart_printf("-1-mqttTask:MinimumFunality enter\r\n");

    /* ol_data_call_stop() was observed to hang indefinitely here after a failed
     * connect/send, stalling the whole system until the platform watchdog fires.
     * Dropping to mbtk_modem_mini_fun below already tears down any active data
     * call, so skip the explicit stop. */

    op_uart_printf("-1-mqttTask:MinimumFunality before mini_fun\r\n");
    result = ol_set_modem_function(mbtk_modem_mini_fun, 0);
    op_uart_printf("-1-mqttTask:MinimumFunality after mini_fun, result=%d\r\n", result);
    if (result != mbtk_device_api_err_none)
    {
        op_uart_printf("-1-mqttTask:minimal function failed: %d\r\n", result);
        return -1;
    }

    op_uart_printf("-1-mqttTask:MinimumFunality before sleep1\r\n");
    ol_os_task_sleep(200);
    op_uart_printf("-1-mqttTask:MinimumFunality after sleep1\r\n");

    op_uart_printf("-1-mqttTask:MinimumFunality before full_fun\r\n");
    result = ol_set_modem_function(mbtk_modem_full_fun, 0);
    op_uart_printf("-1-mqttTask:MinimumFunality after full_fun, result=%d\r\n", result);
    if (result != mbtk_device_api_err_none)
    {
        op_uart_printf("-1-mqttTask:full function failed: %d\r\n", result);
        return -1;
    }

    op_uart_printf("-1-mqttTask:MinimumFunality before sleep2\r\n");
    ol_os_task_sleep(200);
    op_uart_printf("-1-mqttTask:MinimumFunality exit\r\n");
    return 0;
}

static void mqtt_client_teardown(mqtt_client_t **client)
{
    int ret;
    int retry;

    ol_mqtt_disconnect(*client);
    for (retry = 0; retry < 5; retry++)
    {
        ret = ol_mqtt_release(*client);
        if (ret == 0)
        {
            break;
        }
        ol_os_task_sleep(200);
    }
    ol_free(*client);
    *client = NULL;
}

static int mqtt_task_connect(mqtt_client_t **client)
{
    mqtt_state_t state = MQTT_STATE_NETWORK_REGISTER;
    int retry_count = 0;
    int result = -1;
    char *apn;

    *client = NULL;
    while (state != MQTT_STATE_EXIT)
    {
        switch (state)
        {
        case MQTT_STATE_NETWORK_REGISTER:
          op_uart_printf("-1-mqttTask:network registration\r\n");
            result = ol_wait_network_regist(120);
            if (result == mbtk_data_call_ok)
            {
                retry_count = 0;
                state = MQTT_STATE_DATA_CALL;
            }
            else if (retry_count < 1)
            {
                op_uart_printf("-1-mqttTask:network registration failed, retrying\r\n");
                state = MQTT_STATE_NETWORK_REGISTER;
            
                retry_count++;
                ol_os_task_sleep(200);
            }
            else
            {
                op_uart_printf("-1-mqttTask:network registration failed\r\n");
                state = MQTT_STATE_EXIT;
            }
            break;

        case MQTT_STATE_DATA_CALL:
            apn = mqtt_task_get_apn();
            op_uart_printf("-1-mqttTask:using APN=%s\r\n", apn);
            result = ol_data_call_start(MQTT_TASK_CID, MQTT_TASK_PDN,
                                        apn, NULL, NULL, 0);
            if (result != mbtk_data_call_ok)
            {
                op_uart_printf("-1-mqttTask:data call failed: %d\r\n", result);
                state = MQTT_STATE_EXIT;
            }
            else
            {
                if (ol_ntp_get_status() != 1)
                {
                 ol_ntp_sync_time();
               }
                state = MQTT_STATE_CLIENT_INIT;
            }
            break;

        case MQTT_STATE_CLIENT_INIT:
            *client = ol_mqtt_lease();
            if (*client == NULL)
            {
                op_uart_printf("-1-mqttTask:MQTT lease failed\r\n");
                state = MQTT_STATE_EXIT;
                break;
            }
            if (ol_get_device_imei((uint8_t *)mqtt_client_imei) != 0)
            {
                op_uart_printf("-1-mqttTask:IMEI read failed\r\n");
                state = MQTT_STATE_EXIT;
                break;
            }
            mqtt_client_imei[sizeof(mqtt_client_imei) - 1] = '\0';
            op_uart_printf("-1-mqttTask:IMEI = %s\r\n", mqtt_client_imei);
          //  ol_mqtt_set_ca(*client, (char *)MQTT_SSL_VERIFY_NONE);
          //  ol_mqtt_set_ssl_vsn(*client, 3);
           ol_mqtt_set_keep_alive_interval(*client, 60000);
           ol_mqtt_set_will_flag(*client, 0);
            ol_mqtt_set_cmd_timeout(*client, 5000);
            ol_mqtt_set_host(*client, MQTT_TASK_HOST);
            ol_mqtt_set_port(*client, MQTT_TASK_PORT);
            ol_mqtt_set_user_name(*client, mqtt_client_imei);
            ol_mqtt_set_password(*client, mqtt_client_imei);
            ol_mqtt_set_client_id(*client, mqtt_client_imei);
            ol_mqtt_set_clean_session(*client, 1);
            ol_mqtt_set_error_callback(*client, mqtt_task_error);
            state = MQTT_STATE_CONNECT;
            break;

        case MQTT_STATE_CONNECT:
            result = ol_mqtt_connect(*client);
            if (result != 0)
            {
                op_uart_printf("-1-mqttTask:connect failed: %d\r\n", result);
                state = MQTT_STATE_EXIT;
            }
            else
            {
                op_uart_printf("-1-mqttTask:connected\r\n");
                mqtt_connected = 1;
                state = MQTT_STATE_SUBSCRIBE;
            }
            break;

        case MQTT_STATE_SUBSCRIBE:
            result = ol_mqtt_subscribe(*client, "v1/devices/me/attributes/response/+", QOS1,
                                       mqtt_task_attr_response_message);
            if (result != 0)
            {
                op_uart_printf("-1-mqttTask:shared-attr subscribe failed: %d\r\n", result);
                mqtt_connected = 0;
                state = MQTT_STATE_EXIT;
            }
            else
            {
                op_uart_printf("-1-mqttTask:subscribed to shared attr response\r\n");
                return 0;
            }
            break;

        case MQTT_STATE_EXIT:
            break;
        }
    }

    if (*client != NULL)
    {
        mqtt_connected = 0;
        mqtt_client_teardown(client);
    }
    return -1;
}

int networkCheckRecovery(mqtt_client_t **client)
{
    int retry_count;
    uint8_t simStatus = mbtk_sim_unknown;

    if (*client != NULL && mqtt_connected != 0)
    {
        return 0;
    }

    /* ol_wait_network_regist(120) below can block for minutes across its own
     * internal retries; with no SIM it will never succeed, so fail fast
     * instead of blocking my_demo's whole task for up to ~30 minutes.
     * MinimumFunality() still needs to run here (mini->full modem function
     * cycle) -- that's apparently what makes the modem re-scan the SIM slot
     * after a hot-insert; skipping it entirely left a re-inserted SIM stuck
     * reporting "not ready" until a full reboot. It only takes a couple of
     * seconds, unlike the registration wait below. */
    if (ol_get_sim_status(&simStatus) != mbtk_sim_api_err_none || simStatus != mbtk_sim_ready)
    {
        op_uart_printf("-1-mqttTask:SIM not ready (status=%d), cycling modem and skipping connect attempt\r\n", simStatus);
        MinimumFunality();
        return -1;
    }

    for (retry_count = 0; retry_count < 1; retry_count++)
    {
        if (*client != NULL)
        {
            mqtt_client_teardown(client);
        }

        mqtt_connected = 0;
        if (mqtt_task_connect(client) == 0)
        {
            return 0;
        }

        if (MinimumFunality() != 0)
        {
            break;
        }
    }

    return -1;
}

