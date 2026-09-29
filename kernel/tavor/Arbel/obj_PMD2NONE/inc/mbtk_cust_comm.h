#include "lwip/sockets.h"
#include "lwip/netdb.h"
#ifndef REMOVE_MBEDTLS
#include "MQTTQlRTOS.h"
#include "MQTTClient.h"
#endif

typedef struct mbtk_fun_table
{
	void *fun_ptr;
	unsigned int fun_hash;
}mbtk_fun_table_c;

int user_api_test(const char *fmt, ...);


typedef int (*wifi_init_f)(void);
typedef int (*wifi_create_socket_f)(int type);
typedef int (*wifi_connect_f)(int soc_fd, const char *ipaddr, int port);
typedef int (*wifi_recv_f)(int soc_fd, void *buf, int count, int *readlen, int timeout);
typedef int (*wifi_send_f)(int soc_fd, const void *buf, int count, int *writelen, int timeout);
typedef int (*wifi_close_f)(int soc_fd);
typedef int (*wifi_get_host_ip_f)(const char *hostname, char *ipaddress);
typedef int (*wifi_get_socet_st_f)(int soc_fd);
typedef int (*cust_get_network_mode_f)(void);
typedef struct mbtk_cust_wifi_info {
    wifi_init_f init;
    wifi_create_socket_f wifi_soc_create;
    wifi_connect_f wifi_connect;
    wifi_recv_f wifi_recv;
    wifi_send_f wifi_send;
    wifi_close_f wifi_close;
    wifi_get_host_ip_f get_host_ip;
} mbtk_cust_wifi_info;

typedef enum {
    SOCKET_TYPE_TCP = 0,
    SOCKET_TYPE_UDP,
    SOCKET_TYPE_NULL
} HAL_SOCKET_TYPE_E;
int mbtk_customer_wifi_register(mbtk_cust_wifi_info *wifi_info);
int mbtk_customer_netmode_register(cust_get_network_mode_f net_info);
int mbtk_oem_play_tone_ex(int type);