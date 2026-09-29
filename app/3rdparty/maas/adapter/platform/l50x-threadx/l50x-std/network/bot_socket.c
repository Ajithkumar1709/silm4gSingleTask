/*
 * Copyright (C) 2015-2020 Alibaba Group Holding Limited
 */

#include "bot_platform.h"
#include "bot_socket.h"
#include "bot_system.h"


int BOT_FD_ISSET(int fd, fd_set *set)
{
    // return (FD_ISSET(fd, set));// TODO 
    return 0;
}


void BOT_FD_SET(int fd, fd_set *set)
{
    // FD_SET(fd, set);
    return 0;
}

void BOT_FD_ZERO(fd_set *set)
{
    // FD_ZERO(set);
    return 0;
}


int bot_socket_errno(void)
{
	// return errno; // TODO 
    return 0;
}

int bot_socket_open(int domain, int type, int protocol)
{
	// return socket(domain, type, protocol);
    return 0;
}

int bot_socket_write(int sockfd, const void *data, size_t size)
{
	// return write(sockfd, data, size);
    return 0;
}

int bot_socket_read(int sockfd, void *data, size_t len)
{
	// return recv(sockfd, data, len, 0);
    return 0;
}

int bot_socket_connect(int sockfd, const struct sockaddr *name, socklen_t namelen)
{
	// return connect(sockfd, name, namelen);
    return 0;
}

int bot_socket_select(int maxfdp1, fd_set *readset, fd_set *writeset,
	fd_set *exceptset, struct timeval *timeout)
{
	// return select(maxfdp1, readset, writeset, exceptset, timeout);
    return 0;
}

int bot_socket_close(int sockfd)
{
	// return close(sockfd);
    return 0;
}

int bot_socket_shutdown(int sockfd, int how)
{
	// return shutdown(sockfd, how);
    return 0;
}

int bot_socket_app_connect(int *fd, const char *host, const char *port, bot_net_proto_type_e proto )
{
    int ret = -1;
//     struct addrinfo hints, *addr_list, *cur;

//     if ((proto >= bot_net_inv) || (proto < 0)) {
//         return ret;
//     }

//     memset( &hints, 0, sizeof( hints ) );
//     hints.ai_family = AF_UNSPEC;
//     hints.ai_socktype = proto == bot_net_udp ? SOCK_DGRAM : SOCK_STREAM;
//     hints.ai_protocol = proto == bot_net_udp ? IPPROTO_UDP : IPPROTO_TCP;

//     if( getaddrinfo( host, port, &hints, &addr_list ) != 0 )
//         return (-2);

//     for( cur = addr_list; cur != NULL; cur = cur->ai_next )
//     {
//         *fd = (int) bot_socket_open( cur->ai_family,
//                               cur->ai_socktype, cur->ai_protocol );
//         if( *fd < 0 )
//         {
//             ret = -3;
//             continue;
//         }

//         do
//         {
//             ret = bot_socket_connect(*fd, cur->ai_addr, cur->ai_addrlen );
//             if( ret == 0 )
//                 goto out;
//             else
//             {
//                 if (errno == EINTR)
//                     continue;

//                 break;
//             }
//         } while( 1 );

//         bot_socket_close( *fd );
//         ret = -4;
//     }

// out:
//     freeaddrinfo(addr_list);

    return (ret);
}

