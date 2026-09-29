#ifndef _SIMCOM_TCPIP_H_
#define _SIMCOM_TCPIP_H_
#include "simcom_os.h"
#include "lwipv4v6/netdb.h"

#define SC_FD_SETSIZE 128

#define  SC_SOL_SOCKET  0xfff    /* options for socket level */
#define  SC_SO_ERROR        0x1007 


#define  SC_ECONNRESET     104
#define  SC_ECONNABORTED   103  /* Software caused connection abort */

#define SC_AF_INET         2

/* Socket protocol types (TCP/UDP/RAW) */
#define SC_SOCK_STREAM     1
#define SC_SOCK_DGRAM      2
#define SC_SOCK_RAW        3


#define SC_SO_ACCEPTCONN   0x0002 /* socket has had listen() */
#define SC_SO_REUSEADDR    0x0004 /* Allow local address reuse */
#define SC_SO_KEEPALIVE    0x0008 /* keep connections alive */

#define SC_TCP_KEEPALIVE       0x02    /* send KEEPALIVE probes when idle for pcb->keep_idle milliseconds */
#define SC_TCP_KEEPIDLE        0x03    /* set pcb->keep_idle  - Same as TCP_KEEPALIVE, but use seconds for get/setsockopt */
#define SC_TCP_KEEPINTVL       0x04    /* set pcb->keep_intvl - Use seconds for get/setsockopt */
#define SC_TCP_KEEPCNT         0x05    /* set pcb->keep_cnt   - Use number of probes sent for get/setsockopt */
#define SC_TCP_TIMEROUT        0x06    /* set pcb->TCP_TIMEROUT   - Use number of probes sent for get/setsockopt */
#define SC_TCP_MSS_VALUE       0x07    /* set pcb->mss   - Use number of probes only for get/setsockopt */

/** 255.255.255.255 */
#define SC_IPADDR_NONE         ((UINT32)0xffffffffUL)

#define SC_IPPROTO_IP      0
#define SC_IPPROTO_TCP     6
#define SC_IPPROTO_UDP     17


typedef enum {
    INVALID,
    TCPIP_PDP_IPV4,
    TCPIP_PDP_IPV6,
    TCPIP_PDP_IPV4V6
}SCipType_e;

typedef enum {
    SC_TCPIP_SUCCESS,
    SC_TCPIP_FAIL = -1
}SCipReturnCode;

typedef struct 
{
	INT32 tv_sec;        /* seconds */
	INT32 tv_usec;       /* and microseconds */
}SCtimeval;




typedef struct{
  UINT32 s_addr;
}SCinAddr;

typedef struct  {
  UINT8 sin_len;
  UINT8 sin_family;
  UINT16 sin_port;
  SCinAddr sin_addr;
#define SC_SIN_ZERO_LEN 8
  INT8 sin_zero[SC_SIN_ZERO_LEN];
}SCsockAddrIn;



typedef struct  {
  UINT8 fd_bits [(SC_FD_SETSIZE * 2 + 7)/8];
} SCfdSet;


 typedef struct  {
    INT8  *h_name;      /* Official name of the host. */
    INT8 **h_aliases;   /* A pointer to an array of pointers to alternative host names,
                           terminated by a null pointer. */
    INT32    h_addrtype;  /* Address type. */
    INT32    h_length;    /* The length, in bytes, of the address. */
    INT8 **h_addr_list; /* A pointer to an array of pointers to network addresses (in
                           network byte order) for the host, terminated by a null pointer. */
#define h_addr h_addr_list[0] /* for backward compatibility */
}SChostent;




typedef struct{
  UINT8 sa_len;
  UINT8 sa_family;
#if LWIP_IPV6
  UINT8 sa_data[22];
#else /* LWIP_IPV6 */
  UINT8 sa_data[14];
#endif /* LWIP_IPV6 */
}SCsockAddr;


typedef struct SCipInfo {
    SCipType_e type;
    u32_t ip4[32];
    u32_t ip6[32];
}SCipInfo;

typedef struct simcom_ip_info {
    SCipType_e type;
    struct in_addr ip4;
    struct in6_addr ip6;
}simcom_ip_info;


#define SC_IOCPARM_MASK    0x7fU           /* parameters must be < 128 bytes */
#define SC_IOC_VOID        0x20000000UL    /* no parameters */
#define SC_IOC_OUT         0x40000000UL    /* copy out parameters */
#define SC_IOC_IN          0x80000000UL    /* copy in parameters */
#define SC_IOC_INOUT       (SC_IOC_IN|SC_IOC_OUT)
                                        /* 0x20000000 distinguishes new &
                                           old ioctl's */
#define SC_IO(x,y)        (SC_IOC_VOID|((x)<<8)|(y))

#define SC_IOR(x,y,t)     (SC_IOC_OUT|(((UINT32)sizeof(t)&SC_IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define SC_IOW(x,y,t)     (SC_IOC_IN|(((UINT32)sizeof(t)&SC_IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define SC_FIONBIO     SC_IOW('f', 126, UINT32) /* set/clear non-blocking i/o */

#define SC_SOCKET_OFFSET  (0) /*note: must set to 0*/

#define SC_MEMP_NUM_NETCONN 128

#define SC_FDSETSAFESET(n, code)  do {\
    if ((((int)(n) - SC_SOCKET_OFFSET) < (SC_MEMP_NUM_NETCONN * 2)) \
       && (((int)(n) - SC_SOCKET_OFFSET) >= 0)) {code;}\
    } while(0)
    
#define SC_FDSETSAFEGET(n, code) (((((int)(n) - SC_SOCKET_OFFSET) < (SC_MEMP_NUM_NETCONN * 2)) \
       && (((int)(n) - SC_SOCKET_OFFSET) >= 0)) ? (code) : 0)   

#define SC_FD_SET(n, p)  SC_FDSETSAFESET(n, (p)->fd_bits[((n) - SC_SOCKET_OFFSET)/8] |=  (1 << (((n) - SC_SOCKET_OFFSET) & 7)))
#define SC_FD_CLR(n, p)  SC_FDSETSAFESET(n, (p)->fd_bits[((n) - SC_SOCKET_OFFSET)/8] &= ~(1 << (((n) - SC_SOCKET_OFFSET) & 7)))
#define SC_FD_ISSET(n,p) SC_FDSETSAFEGET(n, (p)->fd_bits[((n) - SC_SOCKET_OFFSET)/8] &   (1 << (((n) - SC_SOCKET_OFFSET) & 7)))
#define SC_FD_ZERO(p)    memset((void*)(p),0,sizeof(*(p)))


INT32 sAPI_TcpipGetErrno(void);
INT32 sAPI_TcpipPdpActive(int cid, int channel);
INT32 sAPI_TcpipPdpDeactive(int cid, int channel);
INT32 sAPI_TcpipPdpDeactiveNotify(sMsgQRef msgQ);
INT32 sAPI_TcpipGetSocketPdpAddr(int cid, int channel, struct simcom_ip_info *info);

INT32 sAPI_TcpipSocket(INT32 domain,INT32 type,INT32 protocol);
INT32 sAPI_TcpipBind(INT32 sockfd, const SCsockAddr *addr,UINT32 addrlen);
INT32 sAPI_TcpipListen(INT32 sockfd, INT32 backlog);
INT32 sAPI_TcpipAccept(INT32 sockfd, SCsockAddr *addr, UINT32 *addrlen);

INT32 sAPI_TcpipConnect(INT32 sockfd, const SCsockAddr *addr,UINT32 addrlen);

INT32 sAPI_TcpipSend(INT32 sockfd, const void *buf, INT32 len, INT32 flags);
INT32 sAPI_TcpipRecv(INT32 sockfd, void *buf, INT32 len, INT32 flags);

INT32 sAPI_TcpipSendto(INT32 sockfd, const void *buf, INT32 len, INT32 flags,const SCsockAddr *dest_addr, UINT32 addrlen);
INT32 sAPI_TcpipRecvfrom(INT32 sockfd, void *buf, INT32 len, INT32 flags,SCsockAddr *src_addr, UINT32 *addrlen);
INT32 sAPI_TcpipClose(INT32 fd);
INT32 sAPI_TcpipShutdown(INT32 sockfd, INT32 how);
INT32 sAPI_TcpipGetsockname(INT32 sockfd, SCsockAddr *addr, UINT32 *addrlen);
INT32 sAPI_TcpipGetpeername(INT32 sockfd, SCsockAddr *addr, UINT32 *addrlen);
INT32 sAPI_TcpipGetsockopt(INT32 sockfd, INT32 level, INT32 optname,void *optval, UINT32 *optlen);
INT32 sAPI_TcpipSetsockopt(INT32 sockfd, INT32 level, INT32 optname,const void *optval, UINT32 optlen);
INT32 sAPI_TcpipIoctlsocket(INT32 fd,INT32 level,INT32 value);

SChostent * sAPI_TcpipGethostbyname(const INT8 *name);
INT32 sAPI_TcpipSelect(INT32 nfds, SCfdSet *readfds, SCfdSet *writefds,SCfdSet *exceptfds, SCtimeval *timeout);


UINT32 sAPI_TcpipInet_addr(const INT8 *cp);
UINT16 sAPI_TcpipHtons(UINT16 hostshort);
UINT16 sAPI_TcpipNtohs(UINT16 hostshort);

INT8 *sAPI_TcpipInet_ntoa(UINT32 in);
const INT8 *sAPI_TcpipInet_ntop(INT32 af, const void *src,INT8 *dst, UINT32 size);
INT32 sAPI_TcpipGetsocketErrno(int sockfd);
UINT32 sAPI_TcpipHtonl(INT32 hostlong);
int sAPI_TcpipGetaddrinfo(const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res);
int sAPI_TcpipGetaddrinfo_with_pcid(const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res, u8_t pcid);
void sAPI_TcpipFreeaddrinfo(struct addrinfo *ati);
int sAPI_TcpipSocket_with_callback(int domain, int type, int protocol,socket_callback callback);
int sAPI_TcpipInet_pton(int af, const char *src, void *dst);


#endif




