/*
 * Copyright (C) 2015-2020 Alibaba Group Holding Limited
 */

#include "bot_platform.h"
#include "bot_socket.h"
#include "bot_system.h"
#include <stdio.h>


int BOT_FD_ISSET(int fd, ol_fd_set *set)
{
    return (OL_FD_ISSET(fd, set));
}


void BOT_FD_SET(int fd, ol_fd_set *set)
{
    OL_FD_SET(fd, set);
}

void BOT_FD_ZERO(ol_fd_set *set)
{
    OL_FD_ZERO(set);
}


int bot_socket_errno(void)
{
    return ol_get_socket_errno();
}

int bot_socket_open(int domain, int type, int protocol)
{
    int soc_fd = 0;
    int user_proto = (protocol == bot_net_tcp ? OL_IPPROTO_IP : OL_IPPROTO_UDP);
    if((soc_fd = ol_socket(domain, type, user_proto)) < 0)
    {
        return -1;
    }
    return soc_fd;
}

int bot_socket_write(int sockfd, const void *data, size_t size)
{
    return ol_send(sockfd, data, size, 0);
}

int bot_socket_read(int sockfd, void *data, size_t len)
{
    return ol_recv(sockfd, data, len, 0);
}

int bot_socket_connect(int sockfd, const struct sockaddr *name, socklen_t namelen)
{
    return ol_addr_connect(sockfd, name, namelen);
}

int bot_socket_select(int maxfdp1, ol_fd_set *readset, ol_fd_set *writeset, ol_fd_set *exceptset, ol_timeval *timeout)
{
    return ol_select(maxfdp1, readset, writeset, exceptset, timeout);
}

int bot_socket_close(int sockfd)
{
    return ol_close(sockfd);
}

int bot_socket_shutdown(int sockfd, int how)
{
    return ol_shutdown(sockfd, how);
}

int bot_socket_app_connect(int *fd, const char *host, const char *port, bot_net_proto_type_e proto )
{
    int ret = -1;
    int onoff = 1;
    ol_fd_set readfd, writefd;
    ol_timeval tv;
    int value = 0;
    int value_len = 0;
    int port_num = 0;
    
    if (fd == NULL) 
    {
        bot_printf("bot_socket_app_connect fail because fd is null\r");
        return ret;
    }
    if (host == NULL || port == NULL) 
    {
        bot_printf("bot_socket_app_connect fail because host or port is null\r");
        return ret;
    }
    if(proto != bot_net_tcp && proto != bot_net_udp)
    {
        bot_printf("bot_socket_app_connect fail because proto value(%d) error\r", proto);
        return ret;
    }
    bot_printf("bot_socket_app_connect server: %s:%s ,proto:%d\r", host, port ,proto);

    bot_printf("check port:%s", port);
    int param_num = sscanf(port, "%5d", &port_num);
    if(param_num != 1)
    {
        bot_printf("bot_socket_app_connect check port fail\r");
        return ret;
    }
    bot_printf("check port succ:%d", port_num);
    
    int soc_fd = bot_socket_open(OL_AF_INET, OL_SOCK_STREAM, proto);
    bot_printf("bot_socket_app_connect soc_fd = %d \r", soc_fd);
    if(soc_fd  < 0)
    {
        bot_printf("bot_socket_app_connect fail, soc_fd = %d \r", soc_fd);
        return -1;
    }
    BOT_FD_ZERO(&readfd);
    BOT_FD_ZERO(&writefd);
    BOT_FD_SET(soc_fd, &readfd);
    BOT_FD_SET(soc_fd, &writefd);

    ol_ioctl(soc_fd, OL_FIONBIO, &onoff);

    tv.tv_sec = 10; // 10s for connect
    tv.tv_usec = 0;
    ret = ol_connect(soc_fd, host, port_num);
    if(ret == 0)
    {
        *fd = soc_fd;
        ret = 0;
        bot_printf("bot_socket_app_connect connect success\r");
    }
    else if(bot_socket_errno() == OL_EINPROGRESS)
    {
        bot_printf("bot_socket_app_connect bot_socket_select enter\r");
        ret = bot_socket_select(soc_fd + 1, &readfd, &writefd, NULL, &tv);
        bot_printf("bot_socket_app_connect bot_socket_select iret = %d\r", ret);
        switch(ret)
        {
            case -1:
            {
                bot_socket_close(soc_fd);
                bot_printf("bot_socket_app_connect bot_socket_select fail \r");
                return -1;
            }
            case 0:
            {
                bot_socket_close(soc_fd);
                bot_printf("bot_socket_app_connect bot_socket_select timeout \r");
                return -1;
            }
            default:
            {
                // before connect read err
                value_len = sizeof(value);
                ol_getsocketopt(soc_fd, OL_SOL_SOCKET, OL_SO_ERROR, &value, (socklen_t *)&value_len);
                if(value != OL_ERROK)
                {
                    bot_socket_close(soc_fd);
                    bot_printf("bot_socket_demo connect recv rst %d\r", value);
                    return -1;
                }
                else
                {
                    bot_printf("bot_socket_demo connect success \r");
                    *fd = soc_fd;
                    ret = 0;
                    OL_FD_CLR(soc_fd, &readfd);
                    OL_FD_CLR(soc_fd, &writefd);
                    break;
                }
             }
        }
    }
    else 
    {
        bot_printf("bot_socket_demo connect iret = %d, errno = %d \r", ret, bot_socket_errno());
        bot_socket_close(soc_fd);
        return -1;
    }

    return ret;
}

