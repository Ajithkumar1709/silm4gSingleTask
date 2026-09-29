#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

#include "mbtk_os.h"
#include "mbtk_socket_api.h"
#include "mbtk_datacall_api.h"
#include "mbtk_sim_api.h"
#include "mbtk_circle_buf.h"
#include "mbtk_log.h"

#if (defined(MBTK_POC_SUPPORT_ZZD) || defined(MBTK_POC_SUPPORT_HAWK)|| defined(MBTK_POC_SUPPORT_CHAYU))
// ----------------------------------------------------------- data struct defination -----------------------------------------------------//
#define OEM_SOCK_DEBUG_THREAD  0

#define OEM_SOCK_CACHE_RECV    1

#ifdef OEM_SOCK_DEBUG_THREAD
uint8_t oem_test_connect = 0;
uint8_t oem_test_recv    = 0;
#endif

struct timeval
{
	int tv_sec;        /* seconds */
	int tv_usec;       /* and microseconds */
};

#define OEM_SOCK_MAX_NUM 6

#define OEM_SOCK_POINT_UDP_INFO(socket_id)                       \
                                            do                     \
                                            {                    \
                                                socket_id += 3;    \
                                            }while(0)            \


#define OEM_SOCK_PIONT_UDP_LINK(socket_id)                       \
                                            do                    \
                                            {                    \
                                                socket_id -= 3; \
                                            }while(0)            \


typedef struct 
{
    int sock_fd;
    int sock_id;
}oem_socket_map_struct;


typedef enum 
{
    sock_type_none,
    sock_type_tcp,
    sock_type_udp,
    sock_type_end
}oem_socket_type_enum;


typedef enum 
{
    sock_status_initial,
    sock_status_creat,
    sock_status_connected,
    sock_status_closed,
}oem_socket_status_enum;


typedef struct 
{
    uint16_t remote_port;
    char remote_ip[50];
    uint8_t prefer_select;
    oem_socket_type_enum soc_type;
    oem_socket_status_enum status;
}oem_socket_info_struct;


typedef struct 
{
    int soc_fd;           // platform really socket_fd;
    int soc_id;           // oem apis map soc_id (0 - 3);
    oem_socket_info_struct soc_info;
}oem_socket_struct;


static uint8_t oem_net_status = 0;
oem_socket_struct oem_socket[OEM_SOCK_MAX_NUM] = {0};
#define oem_socket_max_fd   64 
// in 2020/10/27   socket[0]/socket[1] is used to tcp   socket[2]/socket[3] is used to udp


#ifdef OEM_SOCK_CACHE_RECV
DRV_CIRCLE_BUF_T oem_sock_cache_buf_cb[OEM_SOCK_MAX_NUM] = {0};
static uint8_t oem_sock_cache_buf[OEM_SOCK_MAX_NUM][1024 * 5];
#endif



// ------------------------------------------------- external code -----------------------------------------------------------------------//

extern void OEMNetworkStatusChange(int result);
extern void OEMSocket_TCP_Connected(unsigned char socket_id);
extern int OEMSocket_RecvTCPDataCB(unsigned char socket_id);
extern int OEMSocket_RecvUDPDataCB(unsigned char socket_id);

extern uint8_t watch_modem_get_ims_reg_state_req(void);


typedef enum 
{
    sock_msg_initial,
    sock_msg_setup,
    sock_msg_connected,
    sock_msg_recv,
    sock_msg_err,
}oem_socket_msg_enum;



typedef enum 
{
    sock_thread_index_0,
    sock_thread_index_1,
    sock_thread_index_2,
    sock_thread_index_3,
    sock_thread_index_4,
    sock_thread_index_5,
    sock_thread_index_max
}oem_socket_task_index_enum;


typedef struct 
{
    uint8_t soc_id;
    uint8_t soc_msg;
    uint16_t  soc_len;
}oem_socket_msg_struct;


static mbtk_taskref socket_task_ref[sock_thread_index_max];
static mbtk_msgqref socket_msgq_ref[sock_thread_index_max];

  
static mbtk_taskref net_task_ref;
static mbtk_taskref socket_manage_task_ref;

#define oem_sock_msgq_max_count 10
#define oem_sock_thread_stack_size 8096
#define oem_sock_thread_priority 70

#define oem_net_thread_stack_size 10240
#define oem_net_thread_priority 200


void oem_sock_thread_1(void *argv);  // for tcp link 1
void oem_sock_thread_2(void *argv);  // for tcp link 2
void oem_sock_thread_3(void *argv);  // for tcp link 3
void oem_sock_thread_4(void *argv);  // for udp link 1
void oem_sock_thread_5(void *argv);  // for udp link 2
void oem_sock_thread_6(void *argv);  // for udp link 3


char sock_msgq_name_buf[sock_thread_index_max][20] = {"sock_msgq_1", "sock_msgq_2", "sock_msgq_3", "sock_msgq_4", "sock_msgq_5", "sock_msgq_6"};
char sock_thread_name_buf[sock_thread_index_max][20] = {"sock_thread_1", "sock_thread_2", "sock_thread_3", "sock_thread_4", "sock_thread_5", "sock_thread_6"};
int oem_sock_thread_func[sock_thread_index_max] = {oem_sock_thread_1, oem_sock_thread_2, oem_sock_thread_3, oem_sock_thread_4, oem_sock_thread_5, oem_sock_thread_6};


// ---------------------------------------------------------------- internal apis --------------------------------------------------------//
static int mbtk_oem_log_enable = 1;
void oem_mbtk_socket_log_enable()
{
    mbtk_oem_log_enable = 1;
}
void oem_mbtk_socket_log_disable()
{
    mbtk_oem_log_enable = 0;
}

void oem_socket_debug(const char *fmt,...)
{
    va_list ap;
    char buffer[128] = {0};
    static int fatal_uart_inited = 0;

    memset(buffer, 0, sizeof(buffer));
    va_start(ap, fmt);
    vsnprintf(buffer, sizeof(buffer)-1, fmt, ap);
    va_end(ap);

    if(mbtk_oem_log_enable == 1)
    {
        mbtk_app_log("%s\n",buffer);
    }
}


void oem_initial_sock_info(void)
{
    int index;
    for(index = 0; index < OEM_SOCK_MAX_NUM; index++)
    {
        memset(&oem_socket[index], 0, sizeof(oem_socket_struct));
    }
}


extern uint8_t network_registed;
void oem_net_check_status(void)
{
    int status = 0;
    static bool cfun_inited = false;
    char sim_status = 0;
    
    oem_socket_debug("oem_net_check_status cfun_inited[%d], oem_net_status[%d] \n", cfun_inited, oem_net_status);
    if(!cfun_inited)
    {        
        mbtk_get_sim_status(&sim_status);
        if(sim_status!=mbtk_sim_ready)
            return;

        
        mbtk_set_modem_function(1, 0);
        cfun_inited = true;
    }

#if 1
    status = mbtk_get_data_call_state();//network_registed;//mbtk_check_cid1_status();
#else 
    status = watch_modem_get_ims_reg_state_req();
#endif

    if(oem_net_status == 1 && status == 0)
    {
        int index;
        for(index = 0; index < OEM_SOCK_MAX_NUM; index++)//close all socket
        {
            if(oem_socket[index].soc_fd != 0)
            {
                mbtk_socket_close(oem_socket[index].soc_fd);
            }
        }
        oem_initial_sock_info();
    }
    
    if(status != oem_net_status)
    {
        oem_net_status = status;
        oem_socket_debug("OEMNetworkStatusChange");
        OEMNetworkStatusChange(oem_net_status);
    }

}



void oem_sock_thread_1(void *argv)
{
    while(1)
    {
        oem_soc_thread_func(sock_thread_index_0);
    }
}


void oem_sock_thread_2(void *argv)
{
    while(1)
    {
        oem_soc_thread_func(sock_thread_index_1);
    }
}


void oem_sock_thread_3(void *argv)
{
    while(1)
    {
        oem_soc_thread_func(sock_thread_index_2);
    }
}


void oem_sock_thread_4(void *argv)
{
    while(1)
    {
        oem_soc_thread_func(sock_thread_index_3);
    }
}

void oem_sock_thread_5(void *argv)
{
    while(1)
    {
        oem_soc_thread_func(sock_thread_index_4);
    }
}

void oem_sock_thread_6(void *argv)
{
    while(1)
    {
        oem_soc_thread_func(sock_thread_index_5);
    }
}

int oem_interal_socket(int socket_id)
{
    int iret = 0;
        
    switch(oem_socket[socket_id].soc_info.soc_type)
    {
        case sock_type_tcp :
        {
            iret = mbtk_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            break;
        }

        case sock_type_udp :
        {
            iret = mbtk_socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            break;
        }
        
        default :
            return -1;
    }

    oem_socket_debug("oem_interal_socket mbtk_socket iret[%d] \n", iret);

    if(iret < 0)
    {
        return -1;
    }

    return iret;
}




int oem_internal_connect(int socket_id) 
{
    int iret = 0;
    fd_set readfd, writefd;
    struct timeval tv;
    int value, value_len;
    int noneblock = 1;

    oem_socket_debug("oem_internal_connect sockid[%d], fd[%d], ip[%s], port[%d] \n", socket_id, oem_socket[socket_id].soc_fd, oem_socket[socket_id].soc_info.remote_ip, oem_socket[socket_id].soc_info.remote_port);

    if(oem_socket[socket_id].soc_fd == 0)
    {
        oem_socket_debug("oem_internal_connect socke fd is 0 \n");
        return -1;
    }

    FD_ZERO(&readfd);
    FD_ZERO(&writefd);
    FD_SET(oem_socket[socket_id].soc_fd, &readfd);
    FD_SET(oem_socket[socket_id].soc_fd, &writefd);

    mbtk_socket_ioctl(oem_socket[socket_id].soc_fd, FIONBIO, &noneblock);

    tv.tv_sec = 30; // 15s for connect
    tv.tv_usec = 0;

    iret = mbtk_socket_connect(oem_socket[socket_id].soc_fd, oem_socket[socket_id].soc_info.remote_ip, oem_socket[socket_id].soc_info.remote_port);
    oem_socket_debug("oem_internal_connect mbtk_socket_connect iret[%d] \n", iret);
    if(iret == ERROK)
    {
        return 0;
    }
    else if(mbtk_get_socket_errno() == EINPROGRESS)
    {
        iret = mbtk_socket_select(oem_socket[socket_id].soc_fd + 1, &readfd, &writefd, NULL, &tv);
        oem_socket_debug("oem_internal_connect mbtk_socket_select iret[%d] \n", iret);
        switch(iret)
        {
            case -1 :
            {
                oem_socket_debug("oem_internal_connect mbtk_socket_select err[%d] \n", mbtk_get_socket_errno());
                return -1;
            }
            
            case 0 :
            {
                oem_socket_debug("oem_internal_connect mbtk_socket_select timeout \n");
                return -1;
            }
    
            default :
            {
                value_len = sizeof(value);
                iret = mbtk_socket_getopt(oem_socket[socket_id].soc_fd, SOL_SOCKET, SO_ERROR, &value, &value_len);

                oem_socket_debug("oem_internal_connect mbtk_socket_getopt iret %d, error %d\n",iret, mbtk_get_socket_errno());
                if(value == ECONNRESET)
                {
                    oem_socket_debug("oem_internal_connect mbtk_socket_select ECONNRESET \n");
                    return -1;
                }
                else 
                {
                    FD_CLR(oem_socket[socket_id].soc_fd, &readfd);
                    FD_CLR(oem_socket[socket_id].soc_fd, &writefd);
                    oem_socket_debug("oem_internal_connect success \n");
                    return 0;
                }
            }
        }
    }
    else
    {
        return -1;
    }
}


int oem_internal_send(int socket_id, uint8_t *buf, uint16_t len, uint8_t *ipaddr, uint16_t port)
{
    int iret = 0;
    
    switch(oem_socket[socket_id].soc_info.soc_type)
    {
        case sock_type_tcp :
        {
            iret = mbtk_socket_send(oem_socket[socket_id].soc_fd, buf, len, 0);
            break;
        }
        
        case sock_type_udp :
        {
            iret = mbtk_socket_sendto(oem_socket[socket_id].soc_fd, buf, len, 0, ipaddr, port);            
            break;
        }
        
        default :
        {
            return -1;
        }
    }

    oem_socket_debug("oem_internal_send send len[%d] \n", iret);

    if(iret < 0)
    {
        return -1;
    }

    return iret;
}



int oem_internal_recv(int socket_id, uint8_t *buf, uint16_t len)
{
    int iret = 0;
    
    switch(oem_socket[socket_id].soc_info.soc_type)
    {
        case sock_type_tcp :
        {
            iret = mbtk_socket_recv(oem_socket[socket_id].soc_fd, buf, len, 0);
            break;
        }

        case sock_type_udp :
        {
            iret = mbtk_socket_recvfrom(oem_socket[socket_id].soc_fd, buf, len, 0, NULL, NULL);
            break;
        }

        default :
        {
            return -1;
        }
    }
    
    oem_socket_debug("oem_interal_recv recv len[%d] \n", iret);

    if(iret < 0)
    {
        return -1;
    }
    
    return iret;
}

#ifdef OEM_SOCK_CACHE_RECV

int oem_internal_cache_recv(int socket_id, uint8_t *buf, uint16_t len)
{
    int readlen = DRV_CBufPayloadSize(&oem_sock_cache_buf_cb[socket_id]);
    
    oem_socket_debug("oem_internal_cache_recv len[%d] readlen[%d] \n", len, readlen);

    readlen = (len > readlen) ? readlen : len;

    readlen = DRV_CBufRead(&oem_sock_cache_buf_cb[socket_id], buf, readlen);

    oem_socket_debug("oem_internal_cache_recv DRV_CBufRead really readlen[%d] \n", readlen);


    if(readlen > 0)
    {
        return readlen;
    }
    else
    {
        return 0;
    }
}

#endif


int oem_internal_close(int socket_id)
{
    int iret = 0;

    iret = mbtk_socket_close(oem_socket[socket_id].soc_fd);
    
    oem_socket_debug("mbtk_close fd %d,socket_id %d iret[%d] \n", oem_socket[socket_id].soc_fd, socket_id,iret);

    if(iret < 0)
    {
        return -1;
    }

    memset(&oem_socket[socket_id], 0, sizeof(oem_socket_struct));

#ifdef OEM_SOCK_CACHE_RECV
    DRV_CBufFlush(&oem_sock_cache_buf_cb[socket_id]);
#endif

    return 0;
}




void oem_net_thread_func(void *argv)
{
    while(1)
    {
        oem_net_check_status();
        mbtk_os_task_sleep(200); // sleep 1s
    }
}




void oem_sock_select_thread(uint8_t sock_id)
{
    uint8_t sock_fd = 0;
    uint8_t sock_status = 0;
    fd_set readfd;
    int iret = 0;
    sock_fd = oem_socket[sock_id].soc_fd;
    sock_status = oem_socket[sock_id].soc_info.status;

    FD_ZERO(&readfd);
    FD_SET(sock_fd, &readfd);    

    oem_socket_debug("oem_sock_select_thread socket id[%d] fd[%d], status[%d] \n",sock_id, sock_fd, sock_status);

#ifndef OEM_SOCK_CACHE_RECV

    while(oem_socket[sock_id].soc_info.status == sock_status_connected)
    {
        if(oem_socket[sock_id].soc_info.prefer_select)
        {
            while((iret = mbtk_socket_select(oem_socket_max_fd, &readfd, NULL, NULL, NULL)) <= 0)
            {
                mbtk_os_task_sleep(10); // 
            }

            oem_socket_debug("oem_sock_select_thread[%d] mbtk_socket_select iret = %d \n", sock_id, iret);

            if(FD_ISSET(sock_fd, &readfd))
            {
                oem_socket_debug("oem_sock_select_thread sockfd[%d] readfd is set \n", sock_id);
                if(oem_socket[sock_id].soc_info.soc_type == sock_type_tcp)
                {
                    OEMSocket_RecvTCPDataCB(sock_id);
                }
                else if(oem_socket[sock_id].soc_info.soc_type == sock_type_udp) 
                {
                    OEM_SOCK_PIONT_UDP_LINK(sock_id);
                    OEMSocket_RecvUDPDataCB(sock_id);
                    OEM_SOCK_POINT_UDP_INFO(sock_id);
                }
                oem_socket[sock_id].soc_info.prefer_select = 0;
#ifdef OEM_SOCK_DEBUG_THREAD
                oem_test_recv = 1;
#endif
            }
            else 
            {
                oem_socket[sock_id].soc_info.prefer_select = 1;
            }
        }
        else 
        {
            mbtk_os_task_sleep(200);
        }
    }
#else 
    uint8_t sock_temp_recv_buf[4096] = {0};
    int sock_temp_recv_len = 0;

    while(oem_socket[sock_id].soc_info.status == sock_status_connected)
    {
        if((iret = mbtk_socket_select(sock_fd+1, &readfd, NULL, NULL, NULL)) <= 0)
        {
            mbtk_os_task_sleep(10); // 
        }

        oem_socket_debug("oem_sock_select_thread[%d] mbtk_socket_select iret = %d \n", sock_id, iret);

        if(FD_ISSET(sock_fd, &readfd))
        {
            oem_socket_debug("oem_sock_select_thread sockfd[%d] readfd is set \n", sock_id);

            memset(sock_temp_recv_buf, 0, sizeof(sock_temp_recv_buf));

            sock_temp_recv_len = oem_internal_recv(oem_socket[sock_id].soc_id, sock_temp_recv_buf, sizeof(sock_temp_recv_buf));
            if(sock_temp_recv_len < 0)
            {
                oem_socket_debug("oem_sock_select_thread mbtk_socket_recv sockfd[%d], len[%d], err[%d] \n", sock_id, sock_temp_recv_len, mbtk_get_socket_errno());
                mbtk_socket_close(oem_socket[sock_id].soc_fd);
                
                //OEMSocket_TcpCloseCB(sock_id);
                #ifndef MBTK_POC_SUPPORT_CHAYU
                OEMSocket_TCP_Connected(sock_id);
                #endif
                
                #ifdef MBTK_POC_SUPPORT_HAWK
                OEMSocket_TcpCloseCB(sock_id);
                #endif
                break;
            }

            oem_socket_debug("oem_sock_select_thread mbtk_socket_recv sockfd[%d], len[%d]  \n", sock_id, sock_temp_recv_len );

            DRV_CBufWrite(&oem_sock_cache_buf_cb[sock_id], sock_temp_recv_buf, sock_temp_recv_len);

        }
        else 
        {
            oem_socket_debug("oem_sock_select_thread select not care soc_fd \n");
        }

        if(oem_socket[sock_id].soc_info.prefer_select)
        {
            int cache_size = DRV_CBufPayloadSize(&oem_sock_cache_buf_cb[sock_id]);
            oem_socket_debug("oem_sock_select_thread get DRV_CBufPayloadSize [%d] \n", cache_size);
            if(cache_size > 0)
            {
                switch(oem_socket[sock_id].soc_info.soc_type)
                {
                    case sock_type_tcp :
                    {
                        oem_socket[sock_id].soc_info.prefer_select = 0;
                        OEMSocket_RecvTCPDataCB(sock_id);
                        break;
                    }

                    case sock_type_udp :
                    {
                        oem_socket[sock_id].soc_info.prefer_select = 0;
                        OEM_SOCK_PIONT_UDP_LINK(sock_id);
                        OEMSocket_RecvUDPDataCB(sock_id);
                        OEM_SOCK_POINT_UDP_INFO(sock_id);
                        break;
                    }

                    default :
                    {
                        oem_socket_debug("oem_sock_select_thread swtich sock_type err type [%d] \n", oem_socket[sock_id].soc_info.soc_type);
                        break;
                    }
                }
            }        
        }
        else
        {
            mbtk_os_task_sleep(10);
        }
    }
    DRV_CBufFlush(&oem_sock_cache_buf_cb[sock_id]);
#endif
    FD_CLR(sock_fd, &readfd);
    oem_socket_debug("oem_sock_select_thread out id[%d] fd[%d], status[%d] \n", sock_id, sock_fd, oem_socket[sock_id].soc_info.status);
}




void oem_soc_thread_func(oem_socket_task_index_enum index)
{
    int iret = 0;
    uint8_t sock_id = 0;
    oem_socket_msg_struct oem_sock_msg = {0}; 
    mbtk_os_status os_status = mbtk_os_success;

    while(1)
    {
        oem_socket_debug("oem_soc_thread[%d]_func running \n", index);
        os_status = mbtk_os_msgq_recv(socket_msgq_ref[index], &oem_sock_msg, sizeof(oem_socket_msg_struct), MBTK_OS_SUSPEND);
        if(os_status != mbtk_os_success)
        {
            oem_socket_debug("soc_thread_func[%d] recv msg fail, os_status[%d] \n", os_status);
            return -1;
        }

        oem_socket_debug("oem_soc_thread[%d] recv msg.msg[%d], socket_id[%d]", index, oem_sock_msg.soc_msg, oem_sock_msg.soc_id);    

        if(oem_sock_msg.soc_id != index)
        {
            oem_socket_debug("soc_thread_func[%d] is not fit with sock id[%d]\n", index, oem_sock_msg.soc_id);
            return -1;
        }
        
        sock_id = oem_sock_msg.soc_id;            
        oem_socket_debug("sock_fd[%d], soc_type[%d], soc_msg[%d] \n",oem_socket[sock_id].soc_fd,  oem_socket[sock_id].soc_info.soc_type, oem_sock_msg.soc_msg);

        switch(oem_sock_msg.soc_msg)
        {
            case sock_msg_setup :
            {
                struct sockaddr_in addr_in = {0};
                uint16_t local_port = 0;
                
                if(oem_socket[sock_id].soc_info.soc_type == sock_type_tcp)
                {
                    local_port = mbtk_get_random_port();

                    addr_in.sin_len = sizeof(struct sockaddr_in);
                    addr_in.sin_family = AF_INET;
                    addr_in.sin_addr.s_addr = 0;
                    addr_in.sin_port = mbtk_htons(local_port);

                    iret = mbtk_socket_bind(oem_socket[sock_id].soc_fd, (struct sockaddr *)&addr_in, sizeof(struct sockaddr_in));
                    if(iret < 0)
                    {
                        oem_internal_close(sock_id);
                        return;
                    }
                    iret = oem_internal_connect(oem_socket[sock_id].soc_id);//do connect
                    if(iret < 0)
                    {
                        oem_internal_close(sock_id);
                    }
                    else 
                    {
#ifdef OEM_SOCK_DEBUG_THREAD
                        oem_test_connect = 1;
#endif
                        oem_socket[sock_id].soc_info.status = sock_status_connected;
                        oem_socket[sock_id].soc_info.prefer_select = 1;
                        OEMSocket_TCP_Connected(sock_id);
                    }
                }
            }
        }

        oem_sock_select_thread(sock_id);
    }
}


#ifdef OEM_SOCK_CACHE_RECV
void oem_cache_recv_init(uint8_t index)
{
    DRV_CBufInit(&oem_sock_cache_buf_cb[index], oem_sock_cache_buf[index], sizeof(oem_sock_cache_buf[index]));
}
#endif

int oem_internal_init(void) // creat socket task/msgq/semphore(mutex)
{
    mbtk_os_status os_status = mbtk_os_success;
    char *sock_thread_stack_ptr[sock_thread_index_max] = {NULL, NULL, NULL, NULL};
    char *net_thread_stack_ptr = NULL;
    int index;
    
    if(net_thread_stack_ptr = mbtk_malloc(oem_net_thread_stack_size) == NULL)
    {
        oem_socket_debug("oem_internal_init malloc net_thread_stack_ptr fail \n");
        return -1;
    }

    os_status = mbtk_os_task_creat(&net_task_ref, net_thread_stack_ptr, oem_net_thread_stack_size, oem_net_thread_priority, "oem_net_thread", oem_net_thread_func, NULL);
    if(os_status != mbtk_os_success)
    {
        oem_socket_debug("oem_internal_init mbtk_os_task_creat fail, os_status[%d] \n", os_status);
        return -1;
    }


    for(index = 0; index < sock_thread_index_max; index++)
    {
        os_status = mbtk_os_msgq_creat(&socket_msgq_ref[index], sock_msgq_name_buf[index], sizeof(oem_socket_msg_struct), oem_sock_msgq_max_count, MBTK_OS_FIFO);
        if(os_status != mbtk_os_success)
        {
            oem_socket_debug("oem_internal_init mbtk_os_msgq_creat socket[%d]_msgq fail , os_status[%d] \n", index, os_status);
            return -1;
        }

        if(sock_thread_stack_ptr[index] = mbtk_malloc(oem_sock_thread_stack_size) == NULL)
        {
            oem_socket_debug("oem_internal_init malloc sock_thread[%d]_stack_ptr fail\n", index);
            return -1;
        }

        os_status = mbtk_os_task_creat(&socket_task_ref[index], sock_thread_stack_ptr[index], oem_sock_thread_stack_size, oem_sock_thread_priority, oem_sock_thread_func[index], oem_sock_thread_func[index], NULL);
        if(os_status != mbtk_os_success)
        {
            oem_socket_debug("oem_internal_init mbtk_os_task_creat sock_thread[%d] fail, os_status[%d] \n", index, os_status);
            return -1;
        }

#ifdef OEM_SOCK_CACHE_RECV
         oem_cache_recv_init(index);
#endif
    }

    oem_socket_debug("oem_internal_init compelet !\n");
    return 0;
}


// ------------------------------------------------------------ custoemr defination apis -----------------------------------------------------//


// ------------------------------------------------------------------- net apis --------------------------------------------------------------//

int OEMSocket_NetOpen(void)
{
    // TDO
    return 0;
}

int OEMSocket_NetClose(void)
{
    //TDO
    return 0;
}

int OEMGetNetStatus(void)
{
    return oem_net_status;
}

// ---------------------------------------------------------------- socket apis --------------------------------------------------------------//

int OEMSocket_GetIpByName(char* name, char* ip)
{
    mbtk_ipaddr_struct oem_ipaddr = {0};
    int iret = 0;

    if(name == NULL)
    {
        return -1;
    }

    oem_socket_debug("OEMSocket_GetIpByName mbtk_get_hostbyname %s\n", name);
    if(iret = mbtk_get_hostbyname(name, &oem_ipaddr) < 0)
    {
        oem_socket_debug("OEMSocket_GetIpByName mbtk_get_hostbyname fail, iret[%d] \n", iret);
        return -1;
    }

    if(oem_ipaddr.iptype == AF_INET)
    {
        strcpy(ip, mbtk_inet_ntoa(oem_ipaddr.mbtk_ip_addr.ipv4));
        oem_socket_debug("AF_INET OEMSocket_GetIpByName ip src[%s], dst[%s] \n", ip, mbtk_inet_ntoa(oem_ipaddr.mbtk_ip_addr.ipv4));
        return 0;
    }
    else if(oem_ipaddr.iptype == AF_INET6)
    {
        strcpy(ip, mbtk_inet6_ntoa(oem_ipaddr.mbtk_ip_addr.ipv6));
        oem_socket_debug("AF_INET6 OEMSocket_GetIpByName ip src[%s], dst[%s] \n", ip, mbtk_inet6_ntoa(oem_ipaddr.mbtk_ip_addr.ipv6));
        return 0;
    }
    else 
    {
        oem_socket_debug("OEMSocket_GetIpByName mbtk_get_hostbyname unkown iptype[%d] \n", oem_ipaddr.iptype);
    }
}


int OEMSocket_SetupTCP(unsigned char socket_id, char* ip, uint16 port)
{
    int iret = 0;

    mbtk_os_status os_status = mbtk_os_success;
    oem_socket_msg_struct sock_msg = {0};
    oem_socket_debug("OEMSocket_SetupTCP \n");

    if(OEMGetNetStatus() == 0)
    {
        oem_socket_debug("OEMSocket_SetupUDP OEMGetNetStatus fail \n");
        return -1;
    }

    oem_socket[socket_id].soc_id = socket_id;
    oem_socket[socket_id].soc_info.soc_type = sock_type_tcp;
    oem_socket[socket_id].soc_info.remote_port = port;
    memcpy(oem_socket[socket_id].soc_info.remote_ip, ip, strlen(ip));

    iret = oem_interal_socket(socket_id);
    if(iret < 0)
    {
        oem_socket_debug("OEMSocket_SetupTCP mbtk_socket fail, iret[%d] \n", iret);
        return -1;
    }

    oem_socket[socket_id].soc_fd = iret;
    oem_socket[socket_id].soc_info.status = sock_status_creat;

    sock_msg.soc_msg = sock_msg_setup;
    sock_msg.soc_id = socket_id;
    sock_msg.soc_len = 0;
    
    oem_socket_debug("OEMSocket_SetupTCP mbtk_os_msgq_send socket_msgq_ref[%d] \n", socket_id);

    os_status = mbtk_os_msgq_send(socket_msgq_ref[socket_id], sizeof(oem_socket_msg_enum), &sock_msg, MBTK_OS_SUSPEND);
    if(os_status != mbtk_os_success)
    {
        memset(&oem_socket[socket_id], 0, sizeof(oem_socket_struct));
        oem_socket_debug("OEMSocket_SetupTCP mbtk_os_msgq_send sock_msg_setup fail, os_status[%d] \n", os_status);
        return -1;
    }

    oem_socket_debug("OEMSocket_SetupTCP return sock_fd[%d] \n", iret);

#ifdef MBTK_POC_SUPPORT_HAWK
    if(iret>0)
    {
        iret =1;
    }
#endif
    
    return iret;
}

int OEMSocket_SendTCP(unsigned char socket_id,char * buffer,int buf_len)
{
    if(oem_socket[socket_id].soc_info.status != sock_status_connected)
    {
        oem_socket_debug("OEMSocket_SendTCP check socket[%d] status[%d] fail \n", socket_id, oem_socket[socket_id].soc_info.status);
        return -1;
    }

    return oem_internal_send(socket_id, buffer, buf_len, NULL, NULL);
}

void OEMSocket_ReadTcpData(unsigned char socket_id, const char* data, int length)
{
    if(oem_socket[socket_id].soc_info.status != sock_status_connected)
    {
        oem_socket_debug("OEMSocket_ReadTcpData check socket[%d] status[%d] fail \n", socket_id, oem_socket[socket_id].soc_info.status);
        return -1;
    }

    oem_socket[socket_id].soc_info.prefer_select = 1;

#ifndef OEM_SOCK_CACHE_RECV
    return oem_internal_recv(socket_id, data, length);
#else
    return oem_internal_cache_recv(socket_id, data, length);
#endif
}


int OEMSocket_CloseTCP(unsigned char socket_id)
{
    oem_socket_debug("OEMSocket_CloseTCP socket_id %d\n", socket_id);

    if(oem_socket[socket_id].soc_info.status == sock_status_initial)
    {
        oem_socket_debug("OEMSocket_CloseTCP check socket[%d] status[%d] fail \n", socket_id, oem_socket[socket_id].soc_info.status);
        return -1;
    }

    if(oem_socket[socket_id].soc_fd == 0)
    {
        oem_socket_debug("OEMSocket_CloseTCP check socket[%d] socket_fd[%d] fail \n", socket_id, oem_socket[socket_id].soc_fd);
        return -1;
    }

    return oem_internal_close(socket_id);
}


int OEMSocket_SetupUDP(unsigned char socket_id)
{
    int iret = 0;
    int iret_bind = 0;
    mbtk_os_status os_status = mbtk_os_success;
    oem_socket_msg_struct sock_msg = {0};
    struct sockaddr_in addr_in = {0};
    uint16_t local_port = 0;

    oem_socket_debug("OEMSocket_SetupUDP socket_id %d\n", socket_id);

    if(OEMGetNetStatus() == 0)
    {
        oem_socket_debug("OEMSocket_SetupUDP OEMGetNetStatus fail \n");
        return -1;
    }

    OEM_SOCK_POINT_UDP_INFO(socket_id);

    oem_socket[socket_id].soc_id = socket_id;
    oem_socket[socket_id].soc_info.soc_type = sock_type_udp;

    iret = oem_interal_socket(socket_id);

    if(iret < 0)
    {
        oem_socket_debug("OEMSocket_SetupUDP mbtk_socket fail, iret[%d] \n", iret);
        return -1;
    }
         
    oem_socket[socket_id].soc_fd = iret;
    
    local_port = mbtk_get_random_port();
    addr_in.sin_len = sizeof(struct sockaddr_in);
    addr_in.sin_family = AF_INET;
    addr_in.sin_addr.s_addr = 0;
    addr_in.sin_port = mbtk_htons(local_port);

    iret_bind = mbtk_socket_bind(oem_socket[socket_id].soc_fd, (struct sockaddr *)&addr_in, sizeof(struct sockaddr_in));
    oem_socket_debug("OEMSocket_SetupUDP mbtk_socket_bind, iret[%d] \n", iret_bind);
    if(iret_bind < 0)
    {
        oem_internal_close(socket_id);
        return;
    }         
    oem_socket[socket_id].soc_info.status = sock_status_creat;

    oem_socket_debug("OEMSocket_SetupUDP return sock_fd[%d] \n", iret);

#ifdef MBTK_POC_SUPPORT_HAWK
    if(iret>0)
    {
        iret =0;
    }
#endif
    return iret;
}


int OEMSocket_SendUDP(unsigned char socket_id, char* ip, short port, char * buffer, int buf_len)
{
    oem_socket_msg_struct sock_msg = {0};
    mbtk_os_status os_status = mbtk_os_success;

    OEM_SOCK_POINT_UDP_INFO(socket_id);

    if(oem_socket[socket_id].soc_info.status == sock_status_initial)
    {
        oem_socket_debug("OEMSocket_SendUDP check socket[%d] status[%d] fail \n", socket_id, oem_socket[socket_id].soc_info.status);
        return -1;
    }

    if(oem_socket[socket_id].soc_info.status == sock_status_creat)
    {
        oem_socket[socket_id].soc_info.status = sock_status_connected;
        oem_socket[socket_id].soc_info.prefer_select = 1;
        //这里只是为了触发 udp�?select
        sock_msg.soc_msg = sock_msg_setup;
        sock_msg.soc_id = socket_id;
        sock_msg.soc_len = 0;

        oem_socket_debug("OEMSocket_SendUDP mbtk_os_msgq_send socket_msgq_ref[%d] \n", socket_id);

        os_status = mbtk_os_msgq_send(socket_msgq_ref[socket_id], sizeof(oem_socket_msg_enum), &sock_msg, MBTK_OS_SUSPEND);
        if(os_status != mbtk_os_success)
        {
            memset(&oem_socket[socket_id], 0, sizeof(oem_socket_struct));
            oem_socket_debug("OEMSocket_SetupTCP mbtk_os_msgq_send sock_msg_setup fail, os_status[%d] \n", os_status);
            return -1;
        }
    }

    return oem_internal_send(socket_id, buffer, buf_len, ip, port);

}


int OEMSocket_UdpReadData(unsigned char socket_id, const char* data, int length)
{
    OEM_SOCK_POINT_UDP_INFO(socket_id);
    
    if(oem_socket[socket_id].soc_info.status != sock_status_connected)
    {
        oem_socket_debug("OEMSocket_ReadUdpData check socket[%d] status[%d] fail \n", socket_id, oem_socket[socket_id].soc_info.status);
        return -1;
    }

    oem_socket[socket_id].soc_info.prefer_select = 1;

#ifndef OEM_SOCK_CACHE_RECV
    return oem_internal_recv(socket_id, data, length);
#else 
    return oem_internal_cache_recv(socket_id, data, length);
#endif

}


int OEMSocket_CloseUDP(unsigned char socket_id)
{

    OEM_SOCK_POINT_UDP_INFO(socket_id);
    oem_socket_debug("OEMSocket_CloseUDP [%d] \n", socket_id);
    if(oem_socket[socket_id].soc_info.status == sock_status_initial)
    {
        oem_socket_debug("OEMSocket_CloseUDP check socket[%d] status[%d] fail \n", socket_id, oem_socket[socket_id].soc_info.status);
        return -1;
    }

    if(oem_socket[socket_id].soc_fd == 0)
    {
        oem_socket_debug("OEMSocket_CloseUDP check socket[%d] socket_fd[%d] fail \n", socket_id, oem_socket[socket_id].soc_fd);
        return -1;
    }
    
    return oem_internal_close(socket_id);

}


// ------------------------------------------------------- oem socket demo --------------------------------------------------------------------//

#if OEM_SOCK_DEBUG_THREAD

static mbtk_taskref oem_test_task_ref;

void oem_test_thread(void *argv)
{
    int iret = 0;
    mbtk_os_status os_status = mbtk_os_success;

    char recv_buf[100] = {0};
  
    while(1)
    {
        op_uart_printf("oem_test_thread run \n");
        while(OEMGetNetStatus() == 0)
        {
            mbtk_os_task_sleep(200); // wait for pdp active;
        }

        op_uart_printf("oem_test_thread pdp is active now \n");

        iret = OEMSocket_SetupTCP(0, "182.148.114.87", 6900);

        if(iret < 0)
        {
            op_uart_printf("oem_test_thread OEMSocket_SetupTCP fail, iret[%d] \n", iret);
        }

        op_uart_printf("oem_test_thread OEMSocket_SetupTCP iret[%d], soc_fd[%d] \n", iret, oem_socket[0].soc_fd);

        while(oem_test_connect == 0)
        {
            mbtk_os_task_sleep(200);
        }

        op_uart_printf("oem_test_thread OEMSocket_SetupTCP oem_test_connect is set \n");

        iret = OEMSocket_SendTCP(0, "wdnmd", 5);

        op_uart_printf("oem_test_thread OEMSocket_SendTCP iret[%d] \n" , iret);

        while(1)
        {
            while(oem_test_recv == 0)
            {
                mbtk_os_task_sleep(200);
            }
            OEMSocket_ReadTcpData(0, recv_buf, 100);
            oem_test_recv = 0;
            op_uart_printf("oem_test_thread OEMSocket_ReadTcpData buf[%s] \n", recv_buf);
        }
    }
}

int oem_socket_demo(void)
{
    mbtk_os_status os_status = mbtk_os_success;

    char *oem_test_task_stack_ptr = NULL;

    oem_test_task_stack_ptr = mbtk_malloc(2048);

    if(oem_test_task_stack_ptr == NULL)
    {
        op_uart_printf("oem_socket_demo malloc oem_test_task_stack_ptr fail \n");
        return -1;
    }

    os_status = mbtk_os_task_creat(&oem_test_task_ref, oem_test_task_stack_ptr, 2048, 222, "oem_test_task", oem_test_thread, NULL);
    if(os_status != mbtk_os_success)
    {
        op_uart_printf("oem_socket_demo creat msgq fail, os_status[%d] \n", os_status);
        return -1;
    }

    op_uart_printf("oem_socket_demo creat msgq task success \n");
    return 0;
}

#endif /*OEM_SOCK_DEBUG_THREAD*/

#endif /*MBTK_POC_SUPPORT*/