#include "mbtk_comm_api.h"
#include "ol_mqttclient.h"
#include "ol_amazonaws.h"
#include "mbtk_socket_api.h"
#include "mbtk_datacall_api.h"
#include <stdio.h>

#define AWS_MQTT_LOCAL_CID mbtk_cid_index_2
#define AWS_MQTT_LOCAL_CID_PDN_TYPE mbtk_data_call_v4

int amazonaws_demo_wait_network(void)
{
	if(ol_wait_network_regist(120) != mbtk_data_call_ok)
	{
		op_uart_printf("amazonaws_demo_wait_network ol_wait_network_regist time out\n");
		return -1;
	}
	op_uart_printf("amazonaws_demo_wait_network execute ol_data_call_start \n");
	if(ol_data_call_start(AWS_MQTT_LOCAL_CID, AWS_MQTT_LOCAL_CID_PDN_TYPE, "ctnet", NULL, NULL, 0) != mbtk_data_call_ok)
	{
		op_uart_printf("amazonaws_demo_wait_network ol_data_call_start fail\n");
		return -1;
	}

	return 0;
}
static void mqtt_error_callback(void* client, ol_mqtt_error_t error)
{
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
	sprintf(payload,"{\"id\":\"%d\",\"version\":\"1.0\",\"params\":{\"aa\":{\"value\":%d}}}" ,100 + value,value);
	
    msg.qos = QOS0;
    msg.payload = (void *)payload;

    return ol_mqtt_publish(client, "topic/test", &msg);
}

static const char *aws_root_ca_crt = {
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\r\n"
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\r\n"
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\r\n"
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\r\n"
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\r\n"
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\r\n"
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\r\n"
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\r\n"
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\r\n"
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\r\n"
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\r\n"
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\r\n"
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\r\n"
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\r\n"
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\r\n"
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\r\n"
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\r\n"
"rqXRfboQnoZsG4q5WTP468SQvvG5\r\n"
"-----END CERTIFICATE-----\r\n"
};

static const char *aws_claim_crt = {
"-----BEGIN CERTIFICATE-----\r\n"
"MIIDWjCCAkKgAwIBAgIVAOuDwUJ3Ib4o1LvUpROlGfeB+7swMA0GCSqGSIb3DQEB\r\n"
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\r\n"
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzEyMjcxMTAy\r\n"
"NTdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\r\n"
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDpBGI5Zkx7EaAR9M95\r\n"
"NTPtcz2y0DjP2g1rBfmL2Gd47h2jF8e1CDsmCht08mWpi9LIhZc4XNTIKdLizgcF\r\n"
"EKveVCfEsRQ2o/BKcMqTf1GG7RuTiapLokmZXacb6AoaIVzyypxx3NVrlN8sJ/U6\r\n"
"KcQ0Pj4ApazzeNd37WJRZ49rSGR5tcCB/WSPRGxwY9Gb1LO0peu6wYmuYSzmh6a3\r\n"
"XkJl15CthmsN5z+6hICAqJlPhSZfIjnuPXrYI44ThG9SWMIYS2JdyuuT8ZYDxuqu\r\n"
"ZSPZe9v/hfVUPXSFlFBGzwMbQuG2GV4l0lDbxedTQxpRfHnc8GJ5XZDX4G7FMi0F\r\n"
"5KefAgMBAAGjYDBeMB8GA1UdIwQYMBaAFJEFQzM3yYYzj39NgSgBW6Xn6w5BMB0G\r\n"
"A1UdDgQWBBQTD39yf4E6XGDfhif9r0bMQDmyZzAMBgNVHRMBAf8EAjAAMA4GA1Ud\r\n"
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAnihLtFqN5OJxxYKmHU1zMwr0\r\n"
"3TKTv5ix13VdBA4UKuilSOAPedfcU2XFYNJwbzd9QvLx77lpU50J4xgkoWJ2hUhq\r\n"
"4g4IQxp1z5kiPfwS8xsuW9Zd3yrqFyKElFaRT3tKHk97tF29ZqnWG+3BaCWhjXAx\r\n"
"Wjl/Ux+ZPod/ukvbzsY8r7cbBuuofWAhzwYasQVKvbystpkIJ+w0XgggsxcxpV8F\r\n"
"DmD2H6F4b5mT6gQ22duwhw2tfhOOWDJb1MSf1n9di7GwoUKxNS0TC4klo/9RDroY\r\n"
"WzE7vCZHfePH1VEFrCYN5LuKKzWM/vplbyaBOoLXro4SBpm4/L9tAjsxDgLMUg==\r\n"
"-----END CERTIFICATE-----\r\n"
};

static const char *aws_claim_private_key = {
"-----BEGIN RSA PRIVATE KEY-----\r\n"
"MIIEowIBAAKCAQEA6QRiOWZMexGgEfTPeTUz7XM9stA4z9oNawX5i9hneO4doxfH\r\n"
"tQg7JgobdPJlqYvSyIWXOFzUyCnS4s4HBRCr3lQnxLEUNqPwSnDKk39Rhu0bk4mq\r\n"
"S6JJmV2nG+gKGiFc8sqccdzVa5TfLCf1OinEND4+AKWs83jXd+1iUWePa0hkebXA\r\n"
"gf1kj0RscGPRm9SztKXrusGJrmEs5oemt15CZdeQrYZrDec/uoSAgKiZT4UmXyI5\r\n"
"7j162COOE4RvUljCGEtiXcrrk/GWA8bqrmUj2Xvb/4X1VD10hZRQRs8DG0Lhthle\r\n"
"JdJQ28XnU0MaUXx53PBieV2Q1+BuxTItBeSnnwIDAQABAoIBAExckGfpG2U1aHSZ\r\n"
"+qfpBIRrQKvpysRq2/zXr2jh2T7rIbFB6MNt2BxmMYtIqIJAfSoThXQGEAEsm5yS\r\n"
"EgDZ7sjkYUf3E/24CdYLUoe1sJz79Q6LjdBNdbsZ0tq1VyIrDs/OECjMSvB/kAdj\r\n"
"bNzLtS29vAnwQVZkoo/9rjupKXnpVkaSde3JQLGCP09YbaEuZE9pZFxCzGFT+ul3\r\n"
"IicgrndtnFtGTRgviwMQPVSvKgMKA0icSIRM2pwLWA1wsd7DorSlF99eKyZPQIeb\r\n"
"547t0rflVBT79cYvxfbRUVtLCr1ExSxkhzafV0rUbN0fBq6EKcfrtuLgRV2LCs49\r\n"
"WVqLQ6ECgYEA+1rC52tAkZl0byQzH8Wj2fAgLUQUxdOw0n7LCiI4mwPQ8oUwbp5a\r\n"
"c8xxxtn6MhMKJT44j+ZO/qEbWNSIY/rPI30j/TiUxFYMe8uWg/OF/OK7mCKpxC1y\r\n"
"VJfXLwQqt6ALMXedZvflkZTyyr1YREvLPwn/fMtyRDDLGO3X8xFSjo8CgYEA7VLc\r\n"
"uBF3h2pynMnW1QdDm0BDwlRnXFqPNqQGtZAwwYWFmepeikA4l+GXFs3/oL8bxhtH\r\n"
"plQzlb+MnHYm7YNodxa9ckaAupZ3NFZXPuVut7Ve6rw2JCIpfc0op9zOibjxmF3u\r\n"
"mi4Mnx19iyiOHWQfSwKN7hNj0SF4YlRpkmm13fECgYBw2Z8IJ68lr7AG9km9yg52\r\n"
"msjXiemJqDGLUEH4msSvVFdLi2DjSVVzCCdNEDC0qrezYOwkL1LoH40XpNRXjxPQ\r\n"
"6y5tUin4vGl+azl4pK1TjLiM5YMzAPSD5mhGQ6iqKMDdxMZ2pHX9ltIrFDe88gqe\r\n"
"ku6SKQV0eDO3TZHXH7/hIQKBgHcFq7SU7gF4HWsMvzWvovRl0pXPhtcGg/S/Zq4A\r\n"
"VrN3p3190VQ8ySVC+mdxgNa5gdBlNhXw/L4JhxehGfzcfrPbL7/0I/NwKvCQrMja\r\n"
"gCCaUbQgGHceuvhgwBcP4nWnz2K/GT8yARp7y87S1BNhd2BDM7NG/jSQOLP36cqI\r\n"
"QbHBAoGBAOopXs9Pe3BWu8lplG7D1N2IewzQ8j9BVL1jdEj/EhUpZ/4HSLE2dGrC\r\n"
"ugXgpC2twXnM5ozI0pPJK97H5kpLXhsII1322MU2IyABT0P1khPMeZtwQb/ImewS\r\n"
"7Bs0q+Gw5YIIT40PMggyUBPx7xmH4k2fxWKhRtZPEYyiP4za46Nk\r\n"
"-----END RSA PRIVATE KEY-----\r\n"
};


void amazonaws_demo(void)
{
	op_uart_printf("amazonaws_demo start!!\r\n");
    int i = 0,ret = 0;
    static bool aws_fp_flag = false;
    
	if(amazonaws_demo_wait_network() != 0)
	{
		op_uart_printf("mqtt_demo socket_demo_wait_network fail\n");
		return ;
	}
    static char aws_iot_thing_name[64] = {0};
    static char aws_root_ca_cert[2048] = {0};
    static char aws_iot_certificate[2048] = {0};
    static char aws_iot_private_key[2048] = {0};
    if(!aws_fp_flag)
    {
        aws_iot_info_t aws_fp_info = {0};
        aws_iot_config_t aws_fp_config = {0};
        aws_fp_config.fp_mode = FP_MODE_KEYS_CERT;
        aws_fp_config.aws_iot_endpoint = "a1dbfnz4dttvbk-ats.iot.us-east-1.amazonaws.com";
        aws_fp_config.aws_mqtt_port = "8883";
        aws_fp_config.root_ca_buffer = aws_root_ca_crt;
        aws_fp_config.claim_cert_buffer = aws_claim_crt;
        aws_fp_config.claim_private_key_buffer = aws_claim_private_key;
        aws_fp_config.provisioning_template_name = "mbtk_template1";
        aws_fp_config.device_serial_number = "123456";

        aws_fp_info.aws_root_ca_cert = aws_root_ca_cert;
        aws_fp_info.aws_iot_certificate = aws_iot_certificate;
        aws_fp_info.aws_iot_private_key = aws_iot_private_key;
        aws_fp_info.aws_iot_thing_name = aws_iot_thing_name;
        aws_fp_flag = ol_aws_iot_fleet_provisioning(aws_fp_config, &aws_fp_info);
        if(aws_fp_flag)
        {
            op_uart_printf("aws_iot_thing_name = %s", aws_iot_thing_name);
            op_uart_printf("aws_iot_thing_name_length = %d", aws_fp_info.aws_iot_thing_name_length);
        }
        
    }
	op_uart_printf("mqtt start!!\r\n");

	mqtt_client_t *client = NULL;
    client = ol_mqtt_lease();
	if(client){
		ol_mqtt_set_ca(client, (char*)aws_root_ca_cert);
		ol_mqtt_set_cli_crt(client, (char*)aws_iot_certificate);
		ol_mqtt_set_cli_key(client, (char*)aws_iot_private_key);
		ol_mqtt_set_host(client, "a1dbfnz4dttvbk-ats.iot.us-east-1.amazonaws.com");
		ol_mqtt_set_port(client, "8883");
		ol_mqtt_set_user_name(client, NULL);
		ol_mqtt_set_password(client, NULL);
		ol_mqtt_set_client_id(client, aws_iot_thing_name);
        ol_mqtt_set_read_buf_size(client, 1024);
        ol_mqtt_set_keep_alive_interval(client, 5);

		ret = ol_mqtt_connect(client);
		op_uart_printf("mqtt_connect ret = %d\r\n",ret);
		ol_os_task_sleep(2*200);
		ret = ol_mqtt_subscribe(client, "topic/mbtk_test", QOS1, sub_topic_handle1);
		op_uart_printf("mqtt_subscribe ret = %d\r\n",ret);
		ol_os_task_sleep(4*200);

		for(i = 0; i < 5 ;i++)
		{
			ret = mqtt_publish_handle1(client);
			op_uart_printf("%d time mqtt_publish_handle1 ret = %d\r\n",i,ret);
			ol_os_task_sleep(2 * 1000);
		}
        ret = ol_mqtt_unsubscribe(client, "topic/mbtk_test");
		op_uart_printf("ol_mqtt_unsubscribe ret = %d\r\n",ret);
		ol_mqtt_disconnect(client);
		do{
			ret = ol_mqtt_release(client);
			ol_os_task_sleep(200);
		}while(ret!=0);
		
		ol_free(client);
	}
	op_uart_printf("amazonaws_demo end!!\r\n");
}
