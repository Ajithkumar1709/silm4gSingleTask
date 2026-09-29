#include <stdio.h>
#include <string.h>
#include "sockets.h"
#include "netdb.h"
#include "jptt_debug.h"

extern unsigned short OS_Wrap_htons(unsigned short us);

#define OS_TICK     (5)

/*
** network sockets
*/

/*
** ASR block-access test, tested OK
** block-access or nonblock-access both OK.
*/
extern int OS_Wrap_make_tcp_socket(const char* addr, unsigned short port, int s_tout, int r_tout) {
    int cfd;
    int timeOut;    
    int res, nbio;
    //struct sockaddr_in sadd;
    struct sockaddr_in si_add;
    
    DEBUG_D("os wrap get new sock at: %d", port);
    
    if((cfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0) {
        DEBUG_E("create socket fail !");
        return -1;
    }

    nbio = 0;   // no-blocking for test
    ioctlsocket(cfd, FIONBIO, &nbio);
    
    /*memset(&sadd, 0, sizeof(struct sockaddr_in));
    sadd.sin_family = AF_INET;
    sadd.sin_port = OS_Wrap_htons(0);
    sadd.sin_addr.s_addr = inet_addr("127.0.0.1");
    DEBUG_D("local ip = %x, port = %d", sadd.sin_addr.s_addr, sadd.sin_port);
    if ((res = bind(cfd, (struct sockaddr *)&sadd, sizeof(struct sockaddr_in))) < 0) {
        DEBUG_E("t socket BIND failed: %s (%d).", strerror(errno), errno);
        goto mktcp_err_exit;
    }*/

    timeOut = r_tout * 1000;
    res = setsockopt(cfd, SOL_SOCKET, SO_RCVTIMEO, (void*)&timeOut, sizeof(timeOut));
    if (res < 0) {
        DEBUG_E("set rcv timeout failed");
        goto mktcp_err_exit;
    }
    
    timeOut = s_tout * 1000;
    res = setsockopt(cfd, SOL_SOCKET, SO_SNDTIMEO, (void*)&timeOut, sizeof(timeOut));
    if (res < 0) {
        DEBUG_E("set snd timeout failed");
        goto mktcp_err_exit;
    }

    if (port != 0) {
        memset(&si_add, 0, sizeof(struct sockaddr_in));
        si_add.sin_family = AF_INET;
        si_add.sin_addr.s_addr = inet_addr(addr); //* (UINT32 *) host_entry->h_addr_list[0];
        si_add.sin_port = OS_Wrap_htons(port);

        res = connect(cfd, (struct sockaddr *)(&si_add), sizeof(struct sockaddr));
        DEBUG_I("connect %d ret: %d", cfd, res);
        if(res == -1) {
            DEBUG_E("t socket %d connect failed (%d), lwerr=%d.", cfd, res, errno);
            goto mktcp_err_exit;
        }
    }

    return cfd;

mktcp_err_exit:
    closesocket(cfd);
    return -1;
}

extern int OS_Wrap_connect_tcp_socket(int cfd, const char* addr, unsigned short port) {
    return -1;
}

extern int OS_Wrap_connect_by_name(int sock, const char *host, int hport, char *raddr) {
    return -1;    // -1:dis-connected, 0:connected
}

extern int OS_Wrap_receive_tcp_socket(int cfd, char *buffer, int length) {
    return recv(cfd, buffer, length, 0);
}

extern int OS_Wrap_send_tcp_socket(int cfd, char *buffer, int length) {
    return send(cfd, buffer, length, 0);
}

extern void OS_Wrap_shutdown_tcp_socket(int cfd) {
    DEBUG_I("shut down socket %d.", cfd);
    shutdown(cfd, SHUT_RDWR);
}

extern int OS_Wrap_set_tcp_timeout(int cfd, int ms) {
    int timeOut, res;
    
    timeOut = (ms==0? 6*60*1000:ms);   // max timeout is 6min
    res = setsockopt(cfd, SOL_SOCKET, SO_RCVTIMEO, (void*)&timeOut, sizeof(timeOut));
    if (res < 0) {
        DEBUG_E("set rcv timeout failed");
    }
    return 0;
}

/*
extern int OS_Wrap_socket_wait_readable(int h_socket, unsigned int ms) {
    fd_set sock_set;
    struct timeval interval;
    int res;
    
    FD_ZERO(&sock_set);
    FD_SET(h_socket, &sock_set);
 
    interval.tv_sec = (ms/1000);
    interval.tv_usec = (ms%1000)*1000;
 
    res = select(h_socket+1, &sock_set, NULL, NULL, &interval);
    if (res <= 0) {
        return res;
    }
    
	res = FD_ISSET(h_socket, &sock_set);

	return res;
}*/

extern void OS_Wrap_socket_block(int h_socket, int block) {
    int nbio;

    nbio = !block;
    ioctlsocket(h_socket, FIONBIO, &nbio);

    return;
}

/*
** datagram socket
*/

extern int OS_Wrap_get_udp_socket(void) {
    int cfd, nbio;
    //struct sockaddr_in si_add;
    
    cfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if(cfd < 0) {
        DEBUG_E("create udp socket fail !");
        return -1;
    }

    nbio = 0;   // for ASR test blocking
    ioctlsocket(cfd, FIONBIO, &nbio);

    /*memset(&si_add, 0, sizeof(struct sockaddr_in));
    si_add.sin_family = AF_INET;
    si_add.sin_addr.s_addr = inet_addr("127.0.0.1");
    si_add.sin_port = OS_Wrap_htons(0);
    if (0 > bind(cfd, (struct sockaddr *)&si_add, sizeof(struct sockaddr))) {
        DEBUG_E("bind udp failed.");
        closesocket(cfd);
        return -1;
    }*/
    
    return cfd;
}

extern int OS_Wrap_receive_udp(int usock, char *from_a, unsigned short from_p, char* buffer, int blen) {
    struct sockaddr_in s_addr;
    unsigned int sin_len;
	DEBUG_I("socket %d.", usock);

    if (from_a != NULL) {
        sin_len = sizeof(struct sockaddr_in);
        memset(&s_addr, 0, sin_len);
        s_addr.sin_family = AF_INET;
        s_addr.sin_addr.s_addr = inet_addr(from_a);  
        s_addr.sin_port = OS_Wrap_htons(from_p);
        
        return recvfrom(usock, buffer, blen, 0, (struct sockaddr *)&s_addr, (socklen_t *)&sin_len);
    } else {
        return recvfrom(usock, buffer, blen, 0, NULL, NULL);
    }
}

extern int OS_Wrap_send_udp(int usock, char *to_a, unsigned short to_p, char* buffer, int slen) {
    struct sockaddr_in s_addr;
	DEBUG_I("socket %d.", usock);

    memset(&s_addr, 0, sizeof(struct sockaddr_in));
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(to_a);  
    s_addr.sin_port = OS_Wrap_htons(to_p);
    return sendto(usock, buffer, slen, 0, (struct sockaddr *)&s_addr, sizeof(struct sockaddr));
}

extern int OS_Wrap_set_udp_r_timeout(int usock, int msec) {
    if (setsockopt(usock, SOL_SOCKET, SO_RCVTIMEO, &msec, sizeof(int)) < 0) {
        DEBUG_E("UDP setsockopt SO_RCVTIMEO failed.");
    }
    
    return 0;
}

extern int OS_Wrap_set_udp_s_timeout(int usock, int msec) {
    if (setsockopt(usock, SOL_SOCKET, SO_SNDTIMEO, &msec, sizeof(int)) < 0) {
        DEBUG_E("UDP setsockopt SO_SNDTIMEO failed\n");
    }
    
    return 0;
}

extern int OS_Wrap_set_usock_s_buffer(int sock, int slen) {
    if (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char *)&slen, sizeof(slen)) < 0) {
        DEBUG_E("UDP setsockopt SO_SNDBUF failed\n");
        return -1;
    }
    
    return 0;
}

extern void OS_Wrap_close_socket(int usock) {
    int res;
    
    res = closesocket(usock);
    DEBUG_I("socket %d close ret: %d.", usock, res);
}

extern int OS_Wrap_socket_rbuf_ready(int h_socket) {
    return 0;
}

