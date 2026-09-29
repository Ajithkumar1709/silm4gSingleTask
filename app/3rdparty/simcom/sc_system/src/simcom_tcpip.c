#include "simcom_tcpip.h"
#include "lwipv4v6/netdb.h"
#include "mbtk_datacall_api.h"
#include "mbtk_err.h"

INT32 sAPI_TcpipGetErrno(void)
{
    return errno;
}

INT32 sAPI_TcpipPdpActive(int cid, int channel)
{
    mbtk_data_call_return_enum rec;
    
    switch (channel)
    {
        case 0: // 串口
            break;
        case 1: // USB
            break;
        default:
            // channel 参数无效
        return SC_TCPIP_SUCCESS; // 返回错误码
    }
    
    rec = ol_data_call_start(cid, mbtk_data_call_v4v6, NULL, NULL, NULL, OL_NW_AUTH_NONE);

    if(rec != mbtk_data_call_ok)
        return SC_TCPIP_FAIL;
    return SC_TCPIP_SUCCESS;
}

INT32 sAPI_TcpipPdpDeactive(int cid, int channel)
{
    mbtk_data_call_return_enum rec;
    
    switch (channel)
    {
        case 0: // 串口
            break;
        case 1: // USB
            break;
        default:
            // channel 参数无效
        return SC_TCPIP_FAIL; // 返回错误码
    }
    
    rec = ol_data_call_stop(cid, mbtk_data_call_v4v6);

    if(rec != mbtk_data_call_ok)
        return SC_TCPIP_FAIL;
    return SC_TCPIP_SUCCESS;
}

INT32 sAPI_TcpipPdpDeactiveNotify(sMsgQRef msgQ)
{
    simcom_api_not_support();
    return SC_TCPIP_SUCCESS;
}

INT32 sAPI_TcpipGetSocketPdpAddr(int cid, int channel, struct simcom_ip_info *info)
{
    simcom_api_not_support();
    return SC_TCPIP_SUCCESS;
}

INT32 sAPI_TcpipSocket(INT32 domain,INT32 type,INT32 protocol)
{
    return socket(domain, type, protocol);
}

INT32 sAPI_TcpipBind(INT32 sockfd, const SCsockAddr *addr,UINT32 addrlen)
{
    return bind(sockfd, addr, addrlen);
}

INT32 sAPI_TcpipListen(INT32 sockfd, INT32 backlog)
{
    return listen(sockfd, backlog);
}

INT32 sAPI_TcpipAccept(INT32 sockfd, SCsockAddr *addr, UINT32 *addrlen)
{
    return accept(sockfd, addr, addrlen);
}

INT32 sAPI_TcpipConnect(INT32 sockfd, const SCsockAddr *addr,UINT32 addrlen)
{
    return connect(sockfd, addr, addrlen);
}

INT32 sAPI_TcpipSend(INT32 sockfd, const void *buf, INT32 len, INT32 flags)
{
    return send(sockfd, buf, len, flags);
}

INT32 sAPI_TcpipRecv(INT32 sockfd, void *buf, INT32 len, INT32 flags)
{
    return recv(sockfd, buf, len, flags);
}

INT32 sAPI_TcpipSendto(INT32 sockfd, const void *buf, INT32 len, INT32 flags,const SCsockAddr *dest_addr, UINT32 addrlen)
{
    return sendto(sockfd, buf, len, flags, dest_addr, addrlen);
}

INT32 sAPI_TcpipRecvfrom(INT32 sockfd, void *buf, INT32 len, INT32 flags,SCsockAddr *src_addr, UINT32 *addrlen)
{
    return recvfrom(sockfd, buf, len, flags, src_addr, addrlen);
}

INT32 sAPI_TcpipClose(INT32 fd)
{
    return close(fd);
}

INT32 sAPI_TcpipShutdown(INT32 sockfd, INT32 how)
{
    return shutdown(sockfd, how);
}

INT32 sAPI_TcpipGetsockname(INT32 sockfd, SCsockAddr *addr, UINT32 *addrlen)
{
    return getsockname(sockfd, addr, addrlen);
}

INT32 sAPI_TcpipGetpeername(INT32 sockfd, SCsockAddr *addr, UINT32 *addrlen)
{
    return getpeername(sockfd, addr, addrlen);
}

INT32 sAPI_TcpipGetsockopt(INT32 sockfd, INT32 level, INT32 optname,void *optval, UINT32 *optlen)
{
    return getsockopt(sockfd, level, optname, optval, optlen);
}

INT32 sAPI_TcpipSetsockopt(INT32 sockfd, INT32 level, INT32 optname,const void *optval, UINT32 optlen)
{
    return setsockopt(sockfd, level, optname, optval, optlen);
}

INT32 sAPI_TcpipIoctlsocket(INT32 fd,INT32 level,INT32 value)
{
    return ioctlsocket(fd, level, (void *)value);
}

SChostent * sAPI_TcpipGethostbyname(const INT8 *name)
{
    return gethostbyname(name);
}

INT32 sAPI_TcpipSelect(INT32 nfds, SCfdSet *readfds, SCfdSet *writefds,SCfdSet *exceptfds, SCtimeval *timeout)
{
    return select(nfds, readfds, writefds, exceptfds, timeout);
}

UINT32 sAPI_TcpipInet_addr(const INT8 *cp)
{
    return inet_addr(cp);
}

UINT16 sAPI_TcpipHtons(UINT16 hostshort)
{
    return htons(hostshort);
}

UINT16 sAPI_TcpipNtohs(UINT16 hostshort)
{
    return ntohs(hostshort);
}

INT8 *sAPI_TcpipInet_ntoa(UINT32 in)
{
    return inet_ntoa(in);
}

const INT8 *sAPI_TcpipInet_ntop(INT32 af, const void *src,INT8 *dst, UINT32 size)
{
    return inet_ntop(af, src, dst, size);
}

INT32 sAPI_TcpipGetsocketErrno(int sockfd)
{
    return getsockerrno(sockfd);
}

UINT32 sAPI_TcpipHtonl(INT32 hostlong)
{
    return htonl(hostlong);
}

int sAPI_TcpipGetaddrinfo(const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res)
{
    return getaddrinfo(nodename, servname, hints, res);
}

int sAPI_TcpipGetaddrinfo_with_pcid(const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res, u8_t pcid)
{
    return getaddrinfo_with_pcid(nodename, servname, hints, res, pcid);
}

void sAPI_TcpipFreeaddrinfo(struct addrinfo *ati)
{
    freeaddrinfo(ati);
}

int sAPI_TcpipSocket_with_callback(int domain, int type, int protocol,socket_callback callback)
{
    return socket_with_callback(domain, type, protocol, callback);
}

int sAPI_TcpipInet_pton(int af, const char *src, void *dst)
{
    return inet_pton(af, src, dst);
}

