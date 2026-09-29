/**
 * @file lv_customer_api.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "mbtk_cust_comm.h"


int user_api_test(const char *fmt, ...)
{
	mbtk_app_log("user_api_test\n");
}

#define TCP_CON_TYPE    0x40000000
#define CONEVENT_WAIT_ERROR         TCP_CON_TYPE+0x00000001
#define CONNECT_FAILED              TCP_CON_TYPE+0x00000002
#define SET_KEEPALIVE_ERROR         TCP_CON_TYPE+0x00000003
#define RECV_EVENT_CREAT_ERROR      TCP_CON_TYPE+0x00000004

#define TCP_RECV_TYPE 0x50000000
#define RECV_EVENT_OPEN_ERROR       TCP_RECV_TYPE+0x00000001
#define RECV_TIMEOUT                TCP_RECV_TYPE+0x00000002
#define RECV_SOCKET_DISCONNECT      TCP_RECV_TYPE+0x00000003
#define RECV_SOCKET_CLOSE           TCP_RECV_TYPE+0x00000004
#define SOCKETRECV_CALL_ERROR       TCP_RECV_TYPE+0x00000005
#define RECV SUCCESS

// TCP发送错误,以下是 sdk tcp send()函数可能返回的错误值
#define TCP_SEND_TYPE  0x60000000
#define SEND_SOCKET_DISCONNECT  TCP_SEND_TYPE+0x00000001 
#define SOCKETSEND_CALL_ERROR   TCP_SEND_TYPE+0x00000002
#define SEND_TIMEOUT            TCP_SEND_TYPE+0x00000003

#define TCP_CLOSE_TYPE   0x70000000
#define TCP_UNLINK       TCP_CLOSE_TYPE+0x00000001




static mbtk_cust_wifi_info cust_wifi_info = {0};
static cust_get_network_mode_f cust_network_mode = 0;

int mbtk_customer_wifi_register(mbtk_cust_wifi_info *wifi_info)
{
    if (!wifi_info)
        return -1;

    memcpy(&cust_wifi_info, wifi_info, sizeof(mbtk_cust_wifi_info));
	
    return 0;
}

int mbtk_customer_netmode_register(cust_get_network_mode_f net_info)
{
    if (!net_info)
        return -1;

    cust_network_mode = net_info;
    return 0;
}

int cust_wifi_init(void)
{
    if (cust_wifi_info.init) {
        cust_wifi_info.init();
        return 0;
    }

    return -1;
}
#include "mbtk_log.h"

int cust_wifi_create_socket(int type)
{

    if (cust_wifi_info.wifi_soc_create) {
        return cust_wifi_info.wifi_soc_create(type);
    }

    return -1;
}
int cust_wifi_connect(int soc_fd, const char *ipaddr, int port)
{	
    if (cust_wifi_info.wifi_connect) {
        return cust_wifi_info.wifi_connect(soc_fd, ipaddr, port);
    }

    return -1;
}

int cust_wifi_recv(int soc_fd, void *buf, int count, int *readlen, int timeout)
{

    if (cust_wifi_info.wifi_recv) {
        return cust_wifi_info.wifi_recv(soc_fd, buf, count, readlen, timeout);
    }

    return -1;
}

int cust_wifi_send(int soc_fd, const void *buf, int count, int *writelen, int timeout)
{
    if (cust_wifi_info.wifi_send) {
        return cust_wifi_info.wifi_send(soc_fd, buf, count, writelen, timeout);
    }

    return -1;
}

int cust_wifi_close(int soc_fd)
{
    if (cust_wifi_info.wifi_close) {
        return cust_wifi_info.wifi_close(soc_fd);
    }

    return -1;
}

int cust_wifi_get_host_ip(const char *hostname, char *ipaddress)
{
    if (cust_wifi_info.get_host_ip) {
        return cust_wifi_info.get_host_ip(hostname, ipaddress);
    }

    return -1;
}

// 0 是4g
// 1 wifi
int cust_get_network_mode(void)
{
    if (cust_network_mode)
        return cust_network_mode();

    return 0;
}


int cust_error_code_hanler(int err_code)
{
    switch(err_code)
    {
        case RECV_TIMEOUT:
        case SEND_TIMEOUT:
            return EAGAIN;
		case RECV_SOCKET_CLOSE:
		case SEND_SOCKET_DISCONNECT:
			return ECONNRESET;
    }

    return err_code;
}

