#include "mbtk_comm_api.h"
#include "ol_mqttclient.h"
#include "mbtk_socket_api.h"
#include "mbtk_datacall_api.h"
#include "mbtk_device_api.h"
#include "ntp_api.h"
#include "ol_nw_api.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define MQTT_LOCAL_CID mbtk_cid_index_2
#define MQTT_LOCAL_CID_PDN_TYPE mbtk_data_call_v4v6   /* same as my_demo mqttTask.c */

/* Broker (same as Quectel DEFAULT_BROKER_HOST_NAME / DEFAULT_BROKER_PORT) */
#define DEFAULT_BROKER_HOST_NAME "iotpro.io"
#define DEFAULT_BROKER_PORT      "8883"   /* string: ol_mqtt_set_port takes char* */

/* ThingsBoard-style topics (same family as my_demo mqttTask.c) */
#define MQTT_TELEMETRY_TOPIC     "v1/devices/me/telemetry"
#define MQTT_RPC_REQUEST_TOPIC   "v1/devices/me/rpc/request/+"

/* ol_mqtt_set_ssl_vsn value: SSL_VSN_TLSV12 (mbtk_ssl_hal.h). Quectel used
 * QL_SSL_VERSION_ALL, but this SDK's mbedTLS build only enables TLS 1.2. */
#define MQTT_SSL_VERSION 3

/* 1 = verify broker cert against ca_crt (normal)
 * 0 = TEST ONLY: don't verify broker (client cert/key still sent) -
 *     if connect works with 0 but not 1, ca_crt is the wrong CA */
#define MQTT_VERIFY_SERVER 1

static char imei_no[17];

/* APN from operator name (copied from my_demo mqttTask.c mqtt_task_get_apn) */
static char *mqtt_demo_get_apn(void)
{
	ol_OPERATOR_INFO operator_info = {0};
	char operator_name[sizeof(operator_info.long_eons)];
	size_t name_length, index;

	if (ol_nw_get_operator_info(&operator_info) != 0)
	{
		op_uart_printf("mqtt_demo: operator info failed, using default APN\r\n");
		return "www";
	}

	strncpy(operator_name, operator_info.long_eons, sizeof(operator_name) - 1);
	operator_name[sizeof(operator_name) - 1] = '\0';
	if (operator_name[0] == '\0')
	{
		strncpy(operator_name, operator_info.short_eons, sizeof(operator_name) - 1);
		operator_name[sizeof(operator_name) - 1] = '\0';
	}

	op_uart_printf("mqtt_demo: operator long_eons=%s short_eons=%s\r\n",
	               operator_info.long_eons, operator_info.short_eons);

	name_length = strlen(operator_name);
	for (index = 0; index < name_length; index++)
	{
		operator_name[index] = (char)toupper((unsigned char)operator_name[index]);
	}

	if (strstr(operator_name, "AIRTEL") != NULL)
		return "airtelgprs.com";
	if (strstr(operator_name, "CELLONE") != NULL || strstr(operator_name, "BSNL") != NULL)
		return "bsnlnet";
	if (strstr(operator_name, "VI") != NULL || strstr(operator_name, "VODAFONE") != NULL)
		return "www";
	if (strstr(operator_name, "JIO") != NULL)
		return "jionet";

	return "www";
}

int mqtt_demo_wait_network(void)
{
	char *apn;
	int result;

	if(ol_wait_network_regist(120) != mbtk_data_call_ok)
	{
		op_uart_printf("mqtt_demo_wait_network ol_wait_network_regist time out\n");
		return -1;
	}
	apn = mqtt_demo_get_apn();
	op_uart_printf("mqtt_demo_wait_network execute ol_data_call_start APN=%s\r\n", apn);
	result = ol_data_call_start(MQTT_LOCAL_CID, MQTT_LOCAL_CID_PDN_TYPE, apn, NULL, NULL, 0);
	if(result != mbtk_data_call_ok)
	{
		op_uart_printf("mqtt_demo_wait_network ol_data_call_start fail %d\r\n", result);
		return -1;
	}

	return 0;
}

void mqtt_error_callback(void* client, ol_mqtt_error_t error)
{
    /* -7 (nothing to read) / 0 (success) are normal yield-thread noise */
    if (error == MQTT_NOTHING_TO_READ_ERROR || error == MQTT_SUCCESS_ERROR)
        return;
    op_uart_printf("op_uart_printf error_num = %d", error);
    if(error == MQTT_CONNECT_FAILED_ERROR)
    {
        op_uart_printf("MQTT CONNECT ERROR");
    }
}

static void sub_topic_handle1(void* client, message_data_t* msg)
{
    (void) client;
	op_uart_printf("sub_topic_handle1\r\n");
	op_uart_printf("topic: %s\r\n",msg->topic_name);
	op_uart_printf("message:%s\r\n",(char*)msg->message->payload);
}

static int mqtt_publish_handle1(mqtt_client_t *client)
{
    mqtt_message_t msg;
    memset(&msg, 0, sizeof(msg));

	static int value = 0;
	char payload[128] = {0};

	if(value == 10)
		value = 0;
	value ++;
	/* simple ThingsBoard telemetry JSON */
	sprintf(payload, "{\"tlsTest\":%d}", value);

    msg.qos = QOS1;
    msg.payload = (void *)payload;
    msg.payloadlen = strlen(payload);   /* was never set -> empty publish */

    op_uart_printf("mqtt_demo publish topic=%s payload=%s\r\n", MQTT_TELEMETRY_TOPIC, payload);
    return ol_mqtt_publish(client, MQTT_TELEMETRY_TOPIC, &msg);
}

/* Broker CA root: CN=iotpro.io, OU=iotpro.io (Schnell Energy Equipments P Ltd), valid 2024-08-26 .. 2034-08-24.
 * From photocell_Final_TLS_03010104/steps/iotpro/ca-root.pem */
static const char *ca_crt = {
"-----BEGIN CERTIFICATE-----\r\n"
"MIIGUzCCBDugAwIBAgIULDuA9DFUd/9M7R2lXPr+4oINuRYwDQYJKoZIhvcNAQEL\r\n"
"BQAwgbgxCzAJBgNVBAYTAklOMRIwEAYDVQQIDAlUYW1pbG5hZHUxEzARBgNVBAcM\r\n"
"CkNvaW1iYXRvcmUxKDAmBgNVBAoMH1NjaG5lbGwgRW5lcmd5IEVxdWlwbWVudHMg\r\n"
"UCBMdGQxEjAQBgNVBAsMCWlvdHByby5pbzESMBAGA1UEAwwJaW90cHJvLmlvMS4w\r\n"
"LAYJKoZIhvcNAQkBFh9uYW5kaGFrdW1hci5sQHNjaG5lbGxlbmVyZ3kuY29tMB4X\r\n"
"DTI0MDgyNjA5NTk1N1oXDTM0MDgyNDA5NTk1N1owgbgxCzAJBgNVBAYTAklOMRIw\r\n"
"EAYDVQQIDAlUYW1pbG5hZHUxEzARBgNVBAcMCkNvaW1iYXRvcmUxKDAmBgNVBAoM\r\n"
"H1NjaG5lbGwgRW5lcmd5IEVxdWlwbWVudHMgUCBMdGQxEjAQBgNVBAsMCWlvdHBy\r\n"
"by5pbzESMBAGA1UEAwwJaW90cHJvLmlvMS4wLAYJKoZIhvcNAQkBFh9uYW5kaGFr\r\n"
"dW1hci5sQHNjaG5lbGxlbmVyZ3kuY29tMIICIjANBgkqhkiG9w0BAQEFAAOCAg8A\r\n"
"MIICCgKCAgEArRiiiM4OvKLhD55jzOeNuqP8NK8zDrvylW+VkjjYFXbHobxqXjJv\r\n"
"fHXfl51AMCABlofWlqiFsMTpc5pJ5HBEhXTK4I2jUQo6BC8cspQ1FDG5sDt8EjCI\r\n"
"fA+4Sum0I4mu5aMJtUmlxsjjxA9NsWWhbnVX0tZs43Mhf6gnMAsVNvjKRftFpbsq\r\n"
"tClcrXDk1YyINSRY4TVTsA8I4gEN7AtEpFF/wJfvYk/5Y/2myJCFbvTEGJYgNd/E\r\n"
"BOu/NuGjJo5S2Ruh2up7X/XZuwvLrkakEzjkWzu9amZd9mfZw9Ec9Ul6CQChlhpT\r\n"
"16j3h3TVjB1eotch4NRJ3VjIt8BMssosUF6u4kSThF5olItuIiybpqHupCU3j56/\r\n"
"xazFAiKhsNzp++2FgTMvNoHPuqdOUci5xdQ9M4LQD5HtnXxqUZJ5pIZ5THOv5HHG\r\n"
"It8pp9zWdFDc9015U2HvGqnY0ugyACDHgIEzvvRxJ1rY9DXvdfTiRe3IZXd/ngVt\r\n"
"swzO06WomsJc6Pc6Ov/M4DsBl1AzGrsbVUjr2IRT0moj0NTfu2eK/16LvrMna83R\r\n"
"/vZUGQKhFHx9agw5vWQGncKnsbm7SorAduNe2pE1RZyceLOlGnFhlIEe06lsyJ2k\r\n"
"geb+NhGLpjXkz1VEm7C9P/zIOPUs+DVnkR0V1feviondfG1rB0kkKjUCAwEAAaNT\r\n"
"MFEwHQYDVR0OBBYEFFjqd4PerPs8Pe5ND1b4sfD/Hqk1MB8GA1UdIwQYMBaAFFjq\r\n"
"d4PerPs8Pe5ND1b4sfD/Hqk1MA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQEL\r\n"
"BQADggIBACDNjyD7EAVjKs1W+/3v6am0W90VKOqv6JfPQKnxXa9xmE6EewR+cneQ\r\n"
"CI2ooMIH/CS4A9asFzx+KAh3VbyT4bflx6aosQWzSj4QkeXGgdkLl2xlClLPx1ou\r\n"
"EOX5cnFyjGZn3Itkp3Gze9T+SBN0+4hYlJQHrl7QtKo4oEFfJBEETSvQh/FLgsTY\r\n"
"RKpgskpXHk1TThYvsJPzNVNlkxbkgPaE5v2YeeiiM27Jr17JaijN2Pi8QpI7xBZO\r\n"
"dlh/DIbJZ1y8loi2xEX2YNO5n/8l/MC7nFId0YtmLzq+zQuZbeMYptDlzC192nnn\r\n"
"vjMwTgQeLaD0SBKoVfBCE/CtBr4IDpXK/9T+1tu407PINlmpYzARWG01fiGoktJv\r\n"
"q1wfcbraIGTbjDr2JWsx6GApIQzk8NIKbxN5j54n1AEVKylMTGcvyxuZRVr/Acny\r\n"
"dWFhuVW6nJxWeqWIr6knDXlqW6pH5ej4y2aoeHf8yvRFnPWBlyZd/9Fb0JnjMc6d\r\n"
"4JozoK4KgpyHgAv+3KJEHFXGS3wcfHaf1bgWYtBnqAENFK9Uape6L9129qc8Wp0p\r\n"
"VdClnGdXdrp5YDZAXCNHX8kOoyViEWehB3eywba3RgY3V7BS9Cb5g3PSw35b78iu\r\n"
"CUsqIKzN5sXig94gHGFyrfpxHvQE1YMilLVEw8Y5raxThD7/xozx\r\n"
"-----END CERTIFICATE-----\r\n"
};

/* cli_crt / cli_key: per-device, kept out of git */
#include "mqtt_device_certs.h"

/* Equivalent of Quectel mqtt_init() + thingsboardCloud_ssl_cfg
 * (verify_level = MQTT_SSL_VERIFY_SERVER_CLIENT -> CA + client cert + key) */
static int mqtt_init(mqtt_client_t *client)
{
	int i;

	if (ol_get_device_imei((uint8_t *)imei_no) != 0)
	{
		op_uart_printf("mqtt_init: IMEI read fail\r\n");
		return -1;
	}
	imei_no[sizeof(imei_no) - 1] = '\0';
	op_uart_printf("mqtt_init: IMEI=%s\r\n", imei_no);

	/* Cert validity is checked against system time, so sync NTP first (up to ~10 s) */
	if (ol_ntp_get_status() != 1)
	{
		ol_ntp_sync_time();
		for (i = 0; i < 50 && ol_ntp_get_status() != 1; i++)
		{
			ol_os_task_sleep(40); /* 200 ms */
		}
	}
	op_uart_printf("mqtt_init: ntp status=%d\r\n", ol_ntp_get_status());

	/* TLS: existing embedded certificates */
#if MQTT_VERIFY_SERVER
	ol_mqtt_set_ca(client, (char *)ca_crt);
#else
	op_uart_printf("mqtt_init: TEST MODE - broker cert NOT verified\r\n");
	ol_mqtt_set_ca(client, (char *)MQTT_SSL_VERIFY_NONE);
#endif
	ol_mqtt_set_cli_crt(client, (char *)cli_crt);
	ol_mqtt_set_cli_key(client, (char *)cli_key);
	ol_mqtt_set_ssl_vsn(client, MQTT_SSL_VERSION);

	ol_mqtt_set_host(client, DEFAULT_BROKER_HOST_NAME);
	ol_mqtt_set_port(client, DEFAULT_BROKER_PORT);
	ol_mqtt_set_keep_alive_interval(client, 60);   /* keep_alive = 60 (seconds; header says ms but library uses s) */
	ol_mqtt_set_clean_session(client, 1);          /* clean_session = 1 */
	ol_mqtt_set_will_flag(client, 0);              /* will_qos/retain/topic/msg = 0/NULL */
	ol_mqtt_set_client_id(client, imei_no);        /* client_id   = imei_no */
	ol_mqtt_set_user_name(client, imei_no);        /* client_user = imei_no */
	ol_mqtt_set_password(client, imei_no);         /* client_pass = imei_no */
	ol_mqtt_set_cmd_timeout(client, 5000);         /* pkt_timeout = 5 s */

	ol_mqtt_set_error_callback(client, mqtt_error_callback);
	/* retry_times = 3: no direct API here; retry is handled by the caller */
	return 0;
}



void mqtt_demo(void)
{
	mqtt_client_t *client = NULL;
    int i = 0,ret = 0;
		
	op_uart_printf("mqtt demo start!!\r\n");

	if(mqtt_demo_wait_network() != 0)
	{
		op_uart_printf("mqtt_demo socket_demo_wait_network fail\n");
		return ;
	}
	
    client = ol_mqtt_lease();
	if(client){
		if (mqtt_init(client) != 0)
		{
			op_uart_printf("mqtt_demo: mqtt_init fail\r\n");
			ol_mqtt_release(client);
			ol_free(client);
			return;
		}

		ret = ol_mqtt_connect(client);
		op_uart_printf("mqtt_connect ret = %d\r\n",ret);
		ol_os_task_sleep(2*200);
		ret = ol_mqtt_subscribe(client, MQTT_RPC_REQUEST_TOPIC, QOS1, sub_topic_handle1);
		op_uart_printf("mqtt_subscribe ret = %d\r\n",ret);
		ol_os_task_sleep(4*200);

		for(i = 0; i < 5 ;i++)
		{
			ret = mqtt_publish_handle1(client);
			op_uart_printf("%d time mqtt_publish_handle1 ret = %d\r\n",i,ret);
			ol_os_task_sleep(4 * 1000);
		}

		ol_mqtt_disconnect(client);
		do{
			ret = ol_mqtt_release(client);
			ol_os_task_sleep(200);
		}while(ret!=0);
		
		ol_free(client);
	}
	op_uart_printf("mqtt demo end!!\r\n");
}






static void mqtt_sub_Callback(void* client, message_data_t* msg)
{
    (void) client;
	op_uart_printf("sub_topic_handle1\r\n");
	op_uart_printf("topic: %s\r\n",msg->topic_name);
	op_uart_printf("message:%s\r\n",(char*)msg->message->payload);
}

void mqtt_Callback(void* client, mqtt_cmd_id_t cmd_id, ol_mqtt_error_t error)
{
	op_uart_printf("[mqtt_Callback]");
    if(cmd_id != MQTT_CMDID_RESEALE)
    {
        op_uart_printf("[mqtt_Callback]cmd_id:%d, error: %d\n", cmd_id,error);
    }
	
	mqtt_message_t pub_data;
	
    if(error != 0)
    {
        return ;
    }

	if(cmd_id == MQTT_CMDID_CONNECT)
	{
        ol_mqtt_subscribe_asyn((mqtt_client_t *)client,"mobiletk",1,(void*)mqtt_sub_Callback);
	}
	else if(cmd_id == MQTT_CMDID_SUBSCRIBE)
	{
        memset(&pub_data, 0, sizeof(mqtt_message_t));
        pub_data.payloadlen = 5;
        pub_data.payload = (void *)"1234";
        ol_mqtt_publish_asyn((mqtt_client_t *)client,"mobiletk",&pub_data);
	}
	else if(cmd_id == MQTT_CMDID_PUBLISH)
	{
        ol_mqtt_unsubscribe_asyn((mqtt_client_t *)client,"mobiletk");
	}
	else if(cmd_id == MQTT_CMDID_UNSUBSCRIBE)
	{
        ol_mqtt_keep_alive_asyn((mqtt_client_t *)client);
	}
	else if(cmd_id == MQTT_CMDID_KEEP_ALIVE)
	{
        ol_mqtt_disconnect_asyn((mqtt_client_t *)client);
	}
	else if(cmd_id == MQTT_CMDID_DISCONNECT)
	{
	    ol_mqtt_release_asyn((mqtt_client_t *)client);
	}
	else if(cmd_id == MQTT_CMDID_RESEALE)
	{
        op_uart_printf("[mqtt_Callback] success \n");
	}
}

char host[] = "118.114.239.159";
char port[] = "30073";
char user_name[] = "mbtk_test1";
char password[] = "test";
char client_id[] = "test";

void mqtt_test_non_block(void)
{
	mqtt_client_t *client = NULL;
    int ret = 0;
	op_uart_printf("mqtt demo start!!\r\n");

	if(mqtt_demo_wait_network() != 0)
	{
		op_uart_printf("mqtt_demo socket_demo_wait_network fail\n");
		return;
	}
    client = ol_mqtt_lease();

    if(client){
        ol_mqtt_set_host(client, host);
        ol_mqtt_set_port(client, port);
        ol_mqtt_set_user_name(client, user_name);
        ol_mqtt_set_password(client, password);
        ol_mqtt_set_client_id(client, client_id);
        ol_mqtt_set_clean_session(client, 1);
        
        ret = ol_mqtt_connect_asyn(client,mqtt_Callback);
        if(ret != 0)
        {
		   ol_mqtt_disconnect(client);
           ol_mqtt_release(client);
           ol_free(client);
        }
    }

	
   
    
    
}


