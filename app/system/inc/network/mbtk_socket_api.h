
#ifndef __MBTK_SOCKET_API_H
#define __MBTK_SOCKET_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "mbtk_os.h"
#include "string.h"
#include "netdb.h"
#include "inet_chksum.h"
#include "ip4.h"
#include "ip6.h"
#include "icmp.h"
#include "icmp6.h"
#include "mbtk_datacall_api.h"


#define OL_IOCPARM_MASK    IOCPARM_MASK
#define OL_IOC_VOID        IOC_VOID
#define OL_IOC_OUT         IOC_OUT
#define OL_IOC_IN          IOC_IN
#define OL_IOC_INOUT       IOC_INOUT

#define OL_FIONREAD        FIONREAD

#define OL_FIONBIO         FIONBIO

typedef int mbtk_socket_t;

typedef struct 
{
	uint8_t iptype;
	union 
	{
		ip_addr_t ipv4;
		ip6_addr_t ipv6;
	}mbtk_ip_addr;
}mbtk_ipaddr_struct;

typedef struct 
{
	uint8_t ipv4_sta;
	uint8_t ipv6_sta;
	ip_addr_t ipv4;
	ip6_addr_t ipv6;	
}mbtk_ipaddr_struct_ex;

enum ol_socket_event_enum 
{
	OL_SOCKET_EVT_RECV_DATA       = NETCONN_EVT_RCVPLUS,        // 协议栈收到数据事件，通过长度判断为应用数据（长度大于0）或者ERR（长度为0)
	OL_SOCKET_EVT_RCVMINUS        = NETCONN_EVT_RCVMINUS,       // 协议栈接收缓冲区中的数据量减少。这可能意味着已经处理或丢弃了一些接收到的数据。
	OL_SOCKET_EVT_DATA_SEND       = NETCONN_EVT_SENDPLUS,       // 协议栈成功发送数据，仅代表数据交由移动网络协议栈发送
	OL_SOCKET_EVT_DATA_SEND_FAIL  = NETCONN_EVT_SENDMINUS,      // 协议栈限制发送事件，发送数据空间不足，发送失败
	OL_SOCKET_EVT_CONNECTED       = NETCONN_EVT_CONNECTED,      // 协议栈收到连接成功事件
	OL_SOCKET_EVT_ACCEPTED        = NETCONN_EVT_ACCEPTPLUS,     // 协议栈ACCEPT成功
	OL_SOCKET_EVT_CLOSER_IND      = NETCONN_EVT_ERROR_CLSD,     // 协议栈收到远端链接断开事件
	OL_SOCKET_EVT_RST             = NETCONN_EVT_ERROR_RST,      // 协议栈收到远端RST事件
	OL_SOCKET_EVT_ABRT            = NETCONN_EVT_ERROR_ABRT,     // 协议栈收到远端ABRT事件
	OL_SOCKET_EVT_CLOSE_WAIT      = NETCONN_EVT_CLOSE_WAIT,     // 协议栈等待关闭连接。在等待关闭连接的状态中触发。
	OL_SOCKET_EVT_SEND_ACKED      = NETCONN_EVT_SENDACKED,      // 协议栈发送数据收到了ACK
	OL_SOCKET_EVT_CLOSED          = NETCONN_EVT_CLOSE_NORMAL,   // SOCKET正常的被关闭了
};

typedef lwip_ip_packet_info mbtk_ip_packet_info;

#define IPH_V(hdr)  ((hdr)->_v_hl >> 4)
#define IPH_HL(hdr) ((hdr)->_v_hl & 0x0f)
#define IPH_TOS(hdr) ((hdr)->_tos)
#define IPH_LEN(hdr) ((hdr)->_len)
#define IPH_ID(hdr) ((hdr)->_id)
#define IPH_OFFSET(hdr) ((hdr)->_offset)
#define IPH_TTL(hdr) ((hdr)->_ttl)
#define IPH_PROTO(hdr) ((hdr)->_proto)
#define IPH_CHKSUM(hdr) ((hdr)->_chksum)


#define IP_PROTO_ICMP    1
#define IP_PROTO_IGMP    2
#define IP_PROTO_UDP     17
#define IP_PROTO_UDPLITE 136
#define IP_PROTO_TCP     6
#define IP_PROTO_GRE     47
#define IP_PROTO_ESP     50
#define IP_PROTO_AH      51

#define IP6H_V(hdr)  ((ntohl((hdr)->_v_tc_fl) >> 28) & 0x0f)
#define IP6H_TC(hdr) ((ntohl((hdr)->_v_tc_fl) >> 20) & 0xff)
#define IP6H_FL(hdr) (ntohl((hdr)->_v_tc_fl) & 0x000fffff)
#define IP6H_PLEN(hdr) (ntohs((hdr)->_plen))
#define IP6H_NEXTH(hdr) ((hdr)->_nexth)
#define IP6H_NEXTH_P(hdr) ((u8_t *)(hdr) + 6)
#define IP6H_HOPLIM(hdr) ((hdr)->_hoplim)


#define IP6_NEXTH_HOPBYHOP  0
#define IP6_NEXTH_TCP       6
#define IP6_NEXTH_UDP       17
#define IP6_NEXTH_ENCAPS    41
#define IP6_NEXTH_ROUTING   43
#define IP6_NEXTH_FRAGMENT  44
#define IP6_NEXTH_GRE       47
#define IP6_NEXTH_ESP       50
#define IP6_NEXTH_AH        51
#define IP6_NEXTH_ICMP6     58
#define IP6_NEXTH_NONE      59
#define IP6_NEXTH_DESTOPTS  60
#define IP6_NEXTH_UDPLITE   136


// -------------------------------------------- SOCEKT PROTOCOL --------------------------------------------------//
#define OL_SOCK_STREAM     SOCK_STREAM
#define OL_SOCK_DGRAM      SOCK_DGRAM
#define OL_SOCK_RAW        SOCK_RAW

// -------------------------------------------- SOCEKT PROTOCOL --------------------------------------------------//
#define	OL_SOL_SOCKET      SOL_SOCKET         /* options for socket level */
#define OL_IPPROTO_IP      IPPROTO_IP         /* internet control protocol */
#define OL_IPPROTO_ICMP    1                  /* control message protocol */
#define OL_IPPROTO_TCP     IPPROTO_TCP        /* tcp */
#define OL_IPPROTO_UDP     IPPROTO_UDP        /* user datagram protocol */

// --------------------------------------------- SOCEKT IPTYPE ---------------------------------------------------//

#define OL_AF_UNSPEC       AF_UNSPEC         //none-IP
#define OL_AF_INET         AF_INET           //IPV4
#define OL_AF_INET6        AF_INET6          //IPV6


// ----------------------------------------------- SHUT DOWN OPT -------------------------------------------------//
#define OL_SHUT_RD         SHUT_RD
#define OL_SHUT_WR         SHUT_WR
#define OL_SHUT_RDWR       SHUT_RDWR


// ----------------------------------------------- COMMON OPT ----------------------------------------------------//

#define OL_SO_DEBUG        SO_DEBUG /* Unimplemented: turn on debugging info recording */
#define OL_SO_ACCEPTCONN   SO_ACCEPTCONN /* socket has had listen() */
#define OL_SO_REUSEADDR    SO_REUSEADDR /* Allow local address reuse */
#define OL_SO_KEEPALIVE    SO_KEEPALIVE /* keep connections alive */
#define OL_SO_DONTROUTE    SO_DONTROUTE /* Unimplemented: just use interface addresses */
#define OL_SO_BROADCAST    SO_BROADCAST /* permit to send and to receive broadcast messages (see IP_SOF_BROADCAST option) */
#define OL_SO_USELOOPBACK  SO_USELOOPBACK /* Unimplemented: bypass hardware when possible */
#define OL_SO_LINGER       SO_LINGER /* linger on close if data present */
#define OL_SO_DONTLINGER   SO_DONTLINGER
#define OL_SO_OOBINLINE    SO_OOBINLINE /* Unimplemented: leave received OOB data in line */
#define OL_SO_REUSEPORT    SO_REUSEPORT /* Unimplemented: allow local address & port reuse */
#define OL_SO_IPSEC        SO_IPSEC /* denote ipsec using */

#define OL_SO_SNDBUF       SO_SNDBUF  /* Unimplemented: send buffer size */
#define OL_SO_RCVBUF       SO_RCVBUF  /* receive buffer size */
#define OL_SO_SNDLOWAT     SO_SNDLOWAT  /* Unimplemented: send low-water mark */
#define OL_SO_RCVLOWAT     SO_RCVLOWAT  /* Unimplemented: receive low-water mark */
#define OL_SO_SNDTIMEO     SO_SNDTIMEO  /* Unimplemented: send timeout */
#define OL_SO_RCVTIMEO     SO_RCVTIMEO  /* receive timeout */
#define OL_SO_ERROR        SO_ERROR  /* get error status and clear */
#define OL_SO_TYPE         SO_TYPE  /* get socket type */
#define OL_SO_CONTIMEO     SO_CONTIMEO  /* Unimplemented: connect timeout */
#define OL_SO_NO_CHECK     SO_NO_CHECK  /* don't create UDP checksum */
#define OL_SO_BINDTODEVICE SO_BINDTODEVICE /* bind to device */
#define OL_SO_BIO          SO_BIO  /* set socket into blocking mode */
#define OL_SO_NBIO         SO_NBIO  /* set socket into non-blocking mode */
#define OL_SO_NONBLOCK     SO_NONBLOCK  /* set/get socket blocking mode via optval param*/


// --------------------------------------ONLY FOR IP/ICMP CONNECTION ---------------------------------------------//

#define OL_IP_TOS          IP_TOS
#define OL_IP_TTL          IP_TTL

// --------------------------------------ONLY FOR IP/ICMP CONNECTION ---------------------------------------------//


// ----------------------------------------------- SOCEKT OPT ----------------------------------------------------//



// ---------------------------------------------- SOCKET IOCTL ---------------------------------------------------//


#define OL_SOCKET_NUM       NUM_SOCKETS

#define OL_SOCKET_OFFSET    LWIP_SOCKET_OFFSET

#define OL_FD_SETSIZE       FD_SETSIZE
#define OL_FDSETSAFESET(n, code)  FDSETSAFESET(n, code)
#define OL_FDSETSAFEGET(n, code)  FDSETSAFEGET(n, code)

#define OL_FD_SET(n, p)  FD_SET(n, p)
#define OL_FD_CLR(n, p)  FD_CLR(n, p)
#define OL_FD_ISSET(n,p) FD_ISSET(n, p)
#define OL_FD_ZERO(p)    FD_ZERO(p)

typedef fd_set ol_fd_set;

#define  OL_ERROK               ERROK  /* err ok set, no err happen */
#define  OL_EPERM               EPERM  /* Operation not permitted */
#define  OL_ENOENT              ENOENT  /* No such file or directory */
#define  OL_ESRCH               ESRCH  /* No such process */
#define  OL_EINTR               EINTR  /* Interrupted system call */
#define  OL_EIO                 EIO  /* I/O error */
#define  OL_ENXIO               ENXIO  /* No such device or address */
#define  OL_E2BIG               E2BIG  /* Arg list too long */
#define  OL_ENOEXEC             ENOEXEC  /* Exec format error */
#define  OL_EBADF               EBADF  /* Bad file number */
#define  OL_ECHILD              ECHILD  /* No child processes */
#define  OL_EAGAIN              EAGAIN  /* Try again */
#define  OL_ENOMEM              ENOMEM  /* Out of memory */
#define  OL_EACCES              EACCES  /* Permission denied */
#define  OL_EFAULT              EFAULT  /* Bad address */
#define  OL_ENOTBLK             ENOTBLK  /* Block device required */
#define  OL_EBUSY               EBUSY  /* Device or resource busy */
#define  OL_EEXIST              EEXIST  /* File exists */
#define  OL_EXDEV               EXDEV  /* Cross-device link */
#define  OL_ENODEV              ENODEV  /* No such device */
#define  OL_ENOTDIR             ENOTDIR  /* Not a directory */
#define  OL_EISDIR              EISDIR  /* Is a directory */
#define  OL_EINVAL              EINVAL  /* Invalid argument */
#define  OL_ENFILE              ENFILE  /* File table overflow */
#define  OL_EMFILE              EMFILE  /* Too many open files */
#define  OL_ENOTTY              ENOTTY  /* Not a typewriter */
#define  OL_ETXTBSY             ETXTBSY  /* Text file busy */
#define  OL_EFBIG               EFBIG  /* File too large */
#define  OL_ENOSPC              ENOSPC  /* No space left on device */
#define  OL_ESPIPE              ESPIPE  /* Illegal seek */
#define  OL_EROFS               EROFS  /* Read-only file system */
#define  OL_EMLINK              EMLINK  /* Too many links */
#define  OL_EPIPE               EPIPE  /* Broken pipe */
#define  OL_LWIPEDOM            LWIPEDOM  /* Math argument out of domain of func */
#define  OL_LWIPERANGE          LWIPERANGE  /* Math result not representable */
#define  OL_EDEADLK             EDEADLK  /* Resource deadlock would occur */
#define  OL_ENAMETOOLONG        ENAMETOOLONG  /* File name too long */
#define  OL_ENOLCK              ENOLCK  /* No record locks available */
#define  OL_ENOSYS              ENOSYS  /* Function not implemented */
#define  OL_ENOTEMPTY           ENOTEMPTY  /* Directory not empty */
#define  OL_ELOOP               ELOOP  /* Too many symbolic links encountered */
#define  OL_EWOULDBLOCK         EWOULDBLOCK  /* Operation would block */
#define  OL_ENOMSG              ENOMSG  /* No message of desired type */
#define  OL_EIDRM               EIDRM  /* Identifier removed */
#define  OL_ECHRNG              ECHRNG  /* Channel number out of range */
#define  OL_EL2NSYNC            EL2NSYNC  /* Level 2 not synchronized */
#define  OL_EL3HLT              EL3HLT  /* Level 3 halted */
#define  OL_EL3RST              EL3RST  /* Level 3 reset */
#define  OL_ELNRNG              ELNRNG  /* Link number out of range */
#define  OL_EUNATCH             EUNATCH  /* Protocol driver not attached */
#define  OL_ENOCSI              ENOCSI  /* No CSI structure available */
#define  OL_EL2HLT              EL2HLT  /* Level 2 halted */
#define  OL_EBADE               EBADE  /* Invalid exchange */
#define  OL_EBADR               EBADR  /* Invalid request descriptor */
#define  OL_EXFULL              EXFULL  /* Exchange full */
#define  OL_ENOANO              ENOANO  /* No anode */
#define  OL_EBADRQC             EBADRQC  /* Invalid request code */
#define  OL_EBADSLT             EBADSLT  /* Invalid slot */
#define  OL_EDEADLOCK           EDEADLOCK
#define  OL_EBFONT              EBFONT  /* Bad font file format */
#define  OL_ENOSTR              ENOSTR  /* Device not a stream */
#define  OL_ENODATA             ENODATA  /* No data available */
#define  OL_ETIME               ETIME  /* Timer expired */
#define  OL_ENOSR               ENOSR  /* Out of streams resources */
#define  OL_ENONET              ENONET  /* Machine is not on the network */
#define  OL_ENOPKG              ENOPKG  /* Package not installed */
#define  OL_EREMOTE             EREMOTE  /* Object is remote */
#define  OL_ENOLINK             ENOLINK  /* Link has been severed */
#define  OL_EADV                EADV  /* Advertise error */
#define  OL_ESRMNT              ESRMNT  /* Srmount error */
#define  OL_ECOMM               ECOMM  /* Communication error on send */
#define  OL_EPROTO              EPROTO  /* Protocol error */
#define  OL_EMULTIHOP           EMULTIHOP  /* Multihop attempted */
#define  OL_EDOTDOT             EDOTDOT  /* RFS specific error */
#define  OL_EBADMSG             EBADMSG  /* Not a data message */
#define  OL_EOVERFLOW           EOVERFLOW  /* Value too large for defined data type */
#define  OL_ENOTUNIQ            ENOTUNIQ  /* Name not unique on network */
#define  OL_EBADFD              EBADFD  /* File descriptor in bad state */
#define  OL_EREMCHG             EREMCHG  /* Remote address changed */
#define  OL_ELIBACC             ELIBACC  /* Can not access a needed shared library */
#define  OL_ELIBBAD             ELIBBAD  /* Accessing a corrupted shared library */
#define  OL_ELIBSCN             ELIBSCN  /* .lib section in a.out corrupted */
#define  OL_ELIBMAX             ELIBMAX  /* Attempting to link in too many shared libraries */
#define  OL_ELIBEXEC            ELIBEXEC  /* Cannot exec a shared library directly */
#define  OL_LWIPEILSEQ          LWIPEILSEQ  /* Illegal byte sequence */
#define  OL_ERESTART            ERESTART  /* Interrupted system call should be restarted */
#define  OL_ESTRPIPE            ESTRPIPE  /* Streams pipe error */
#define  OL_EUSERS              EUSERS  /* Too many users */
#define  OL_ENOTSOCK            ENOTSOCK  /* Socket operation on non-socket */
#define  OL_EDESTADDRREQ        EDESTADDRREQ  /* Destination address required */
#define  OL_EMSGSIZE            EMSGSIZE  /* Message too long */
#define  OL_EPROTOTYPE          EPROTOTYPE  /* Protocol wrong type for socket */
#define  OL_ENOPROTOOPT         ENOPROTOOPT  /* Protocol not available */
#define  OL_EPROTONOSUPPORT     EPROTONOSUPPORT  /* Protocol not supported */
#define  OL_ESOCKTNOSUPPORT     ESOCKTNOSUPPORT  /* Socket type not supported */
#define  OL_EOPNOTSUPP          EOPNOTSUPP  /* Operation not supported on transport endpoint */
#define  OL_EPFNOSUPPORT        EPFNOSUPPORT  /* Protocol family not supported */
#define  OL_EAFNOSUPPORT        EAFNOSUPPORT  /* Address family not supported by protocol */
#define  OL_EADDRINUSE          EADDRINUSE  /* Address already in use */
#define  OL_EADDRNOTAVAIL       EADDRNOTAVAIL  /* Cannot assign requested address */
#define  OL_ENETDOWN            ENETDOWN  /* Network is down */
#define  OL_ENETUNREACH         ENETUNREACH  /* Network is unreachable */
#define  OL_ENETRESET           ENETRESET  /* Network dropped connection because of reset */
#define  OL_ECONNABORTED        ECONNABORTED  /* Software caused connection abort */
#define  OL_ECONNRESET          ECONNRESET  /* Connection reset by peer */
#define  OL_ENOBUFS             ENOBUFS  /* No buffer space available */
#define  OL_EISCONN             EISCONN  /* Transport endpoint is already connected */
#define  OL_ENOTCONN            ENOTCONN  /* Transport endpoint is not connected */
#define  OL_ESHUTDOWN           ESHUTDOWN  /* Cannot send after transport endpoint shutdown */
#define  OL_ETOOMANYREFS        ETOOMANYREFS  /* Too many references: cannot splice */
#define  OL_ETIMEDOUT           ETIMEDOUT  /* Connection timed out */
#define  OL_ECONNREFUSED        ECONNREFUSED  /* Connection refused */
#define  OL_EHOSTDOWN           EHOSTDOWN  /* Host is down */
#define  OL_EHOSTUNREACH        EHOSTUNREACH  /* No route to host */
#define  OL_EALREADY            EALREADY  /* Operation already in progress */
#define  OL_EINPROGRESS         EINPROGRESS  /* Operation now in progress */
#define  OL_ESTALE              ESTALE  /* Stale NFS file handle */
#define  OL_EUCLEAN             EUCLEAN  /* Structure needs cleaning */
#define  OL_ENOTNAM             ENOTNAM  /* Not a XENIX named type file */
#define  OL_ENAVAIL             ENAVAIL  /* No XENIX semaphores available */
#define  OL_EISNAM              EISNAM  /* Is a named type file */
#define  OL_EREMOTEIO           EREMOTEIO  /* Remote I/O error */
#define  OL_EDQUOT              EDQUOT  /* Quota exceeded */
#define  OL_ENOMEDIUM           ENOMEDIUM  /* No medium found */
#define  OL_EMEDIUMTYPE         EMEDIUMTYPE  /* Wrong medium type */


// ---------------------------------------------- SOCKET APIS ----------------------------------------------------//


/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_socket
 * DESCRIPTION 
 *          This API is to create socket. 
 * PARAMETERS 
 *        domain    [IN]: indicate the protocol family used
 *        type      [IN]: indicates the socket type
 *        protocol  [IN]: protocol
 * RETURN VALUES
 *         > 0: socket handle
 *         <=0: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_socket_t ol_socket(int domain, int type, int protocol);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_socket_with_callback
 * DESCRIPTION 
 *          This API is to create socket with callback. 
 * PARAMETERS 
 *        domain    [IN]: indicate the protocol family used
 *        type      [IN]: indicates the socket type
 *        protocol  [IN]: protocol
 *        callback  [IN]: socket event callback
 * RETURN VALUES
 *         > 0: socket handle
 *         <=0: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_socket_t ol_socket_with_callback(int domain, int type, int protocol, socket_callback callback);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_random_port
 * DESCRIPTION 
 *          This API is to get random port. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *         > 0: socket port
 *         <=0: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_get_random_port(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_bind
 * DESCRIPTION 
 *          This API is to bind the created socket to the specified IP address and port. 
 * PARAMETERS 
 *        socket    [IN]: socket handle
 *        pname    [IN]: socket pname
 *        namelen    [IN]: socket namelen
 * RETURN VALUES
 *         =0: successful
 *         <0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_bind(mbtk_socket_t socket, const struct sockaddr *pname, int namelen);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_connect
 * DESCRIPTION 
 *          This API is used to establish a socket connection with the server. 
 * PARAMETERS 
 *        socket  [IN]: socket handle
 *        addr    [IN]: addr
 *        port    [IN]: port
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_connect(mbtk_socket_t socket, const char *addr, uint16_t port);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_addr_connect
 * DESCRIPTION 
 *          This API is used to establish a socket connection with the server. 
 * PARAMETERS 
 *        socket   [IN]: socket handle
 *        pname    [IN]: pname
 *        namelen  [IN]: namelen
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_addr_connect(mbtk_socket_t socket, const struct sockaddr *pname, int namelen);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_send
 * DESCRIPTION 
 *          This API is use to send tcp data. 
 * PARAMETERS 
 *        socket   [IN]: socket handle
 *        pbuf     [IN]: pbuf
 *        bufsize  [IN]: bufsize
 *        flags    [IN]: flags
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_send(mbtk_socket_t socket, uint8_t *pbuf, size_t bufsize, uint32_t flags);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_sendto
 * DESCRIPTION 
 *          This API is use to send udp data. 
 * PARAMETERS 
 *        socket   [IN]: socket handle
 *        pbuf     [IN]: pbuf
 *        bufsize  [IN]: bufsize
 *        flags    [IN]: flags
 *        to       [IN]: to, peer address
 *        toport   [IN]: toport, peer port
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_sendto(mbtk_socket_t socket, void *pbuf, size_t sendsize, uint32_t flags, const char *to, uint16_t toport);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_recv
 * DESCRIPTION 
 *          This API is use to recv tcp data. 
 * PARAMETERS 
 *        socket    [IN]: socket handle
 *        recvbuf   [IN]: recvbuf
 *        wantsize  [IN]: wantsize
 *        flags     [IN]: flags
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_recv(mbtk_socket_t socket, uint8_t *recvbuf, size_t wantsize, uint32_t flags);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_recvfrom
 * DESCRIPTION 
 *          This API is use to recv udp data. 
 * PARAMETERS 
 *        socket    [IN]: socket handle
 *        recvbuf   [IN]: recvbuf
 *        wantsize  [IN]: wantsize
 *        flags     [IN]: flags
 *        addr      [IN]: addr, peer address
 *        port      [IN]: port, peer port
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_recvfrom(mbtk_socket_t socket, void* recvbuf, int wantsize, uint32_t flags, char *addr, uint16_t *port);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_listen
 * DESCRIPTION 
 *          This API is use to implement monitoring service. 
 * PARAMETERS 
 *        socket    [IN]: socket handle
 *        backlog   [IN]: backlog, the maximum number of connections
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_listen(mbtk_socket_t socket, int backlog);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_accept
 * DESCRIPTION 
 *          This API is use to get the next successful connection from the completed connection queue. 
 * PARAMETERS 
 *        socket    [IN]: socket handle
 *        addr   [IN]: addr, sockaddr_ variable address
 *        port   [IN]: port
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_accept(mbtk_socket_t socket,  char *addr, uint16_t *port);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_close
 * DESCRIPTION 
 *          This API is use to close socket. 
 * PARAMETERS 
 *        socket    [IN]: socket handle
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_close(mbtk_socket_t socket);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_shutdown
 * DESCRIPTION 
 *          This API is prohibited to receive and send data on a socket. 
 * PARAMETERS 
 *        socket    [IN]: socket handle
 *        how       [IN]: how, used to describe which operations are prohibited
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_shutdown(mbtk_socket_t socket, int how);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_close_with_linger
 * DESCRIPTION 
 *          This API is close socket with linger. 
 * PARAMETERS 
 *        socket       [IN]: socket handle
 *        linger_onff  [IN]: linger_onff
 *        sec          [IN]: sec
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_close_with_linger(mbtk_socket_t socket, uint8_t linger_onff, uint8_t sec);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_select
 * DESCRIPTION 
 *          This API is select socket. 
 * PARAMETERS 
 *        socket       [IN]: socket handle
 *        readset      [IN]: readset
 *        sewritesetc  [IN]: writeset
 *        exceptset    [IN]: exceptset
 *        timeout      [IN]: timeout
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_select(int max_fd, ol_fd_set *readset, ol_fd_set *writeset, ol_fd_set *exceptset, ol_timeval *timeout);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ioctl
 * DESCRIPTION 
 *          This API is use to ioctl socket. 
 * PARAMETERS 
 *        socket       [IN]: socket handle
 *        ctlcmd       [IN]: ctlcmd
 *        arg          [IN]: arg
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_ioctl(mbtk_socket_t socket, int ctlcmd, void *arg);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_gethostbyname
 * DESCRIPTION 
 *          This API is use to get host. 
 * PARAMETERS 
 *        name        [IN]: domain name
 *        taddr       [IN]: ip addr
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_gethostbyname(const char *name, mbtk_ipaddr_struct *taddr);
extern int ol_gethostbyname_ex(const char *name, mbtk_ipaddr_struct_ex *taddr);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_gethostbyname_local_cid
 * DESCRIPTION 
 *          This API is use to get host. 
 * PARAMETERS 
 *        name        [IN]: domain name
 *        taddr       [IN]: ip addr
 *        cid         [IN]: cid
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_gethostbyname_local_cid(const char *name, mbtk_ipaddr_struct *taddr, mbtk_data_call_cid_index_enum cid);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_getsocketname
 * DESCRIPTION 
 *          This API is use to get socket name. 
 * PARAMETERS 
 *        socket       [IN]: socket handle
 *        pname        [IN]: pname
 *        pnamelen     [IN]: pnamelen
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_getsocketname(mbtk_socket_t socket,  const struct sockaddr *pname, int *pnamelen);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_getpeername
 * DESCRIPTION 
 *          This API is use to get peer socket name. 
 * PARAMETERS 
 *        socket       [IN]: socket handle
 *        pname        [IN]: pname
 *        pnamelen     [IN]: pnamelen
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_getpeername(mbtk_socket_t socket,  const struct sockaddr *pname, int *pnamelen);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_getsocketopt
 * DESCRIPTION 
 *          This API is use to get the options associated with a socket. 
 * PARAMETERS 
 *        socket       [IN]: socket handle
 *        level        [IN]: level
 *        optname      [IN]: optname
 *        poptval      [IN]: poptval
 *        poptlen      [IN]: poptlen
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_getsocketopt(mbtk_socket_t socket, int level, int optname, void *poptval, int *poptlen);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_setsocketopt
 * DESCRIPTION 
 *          This API is use to set the options associated with a socket. 
 * PARAMETERS 
 *        socket       [IN]: socket handle
 *        level        [IN]: level
 *        optname      [IN]: optname
 *        poptval      [IN]: poptval
 *        poptlen      [IN]: poptlen
 * RETURN VALUES
 *         >=0: successful
 *         < 0: fail
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_setsocketopt(mbtk_socket_t socket, int level, int optname, const void *poptval, int optlen);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_inet_ntop
 * DESCRIPTION 
 *          This API is use to converts an Internet network address to a string in Internet standard format. 
 * PARAMETERS 
 *        fd       [IN]: socket handle
 *        src      [IN]: src
 *        dst      [IN]: dst
 *        size     [IN]: size
 * RETURN VALUES
 *         NULL: error
 *         other: successful
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern char *ol_inet_ntop(int fd, const void *src, char *dst, int size);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_inet_pton
 * DESCRIPTION 
 *          This API is use to convert the Internet network address in the standard text representation to the digital binary form. 
 * PARAMETERS 
 *        fd       [IN]: socket handle
 *        src      [IN]: src
 *        dst      [IN]: dst
 * RETURN VALUES
 *         NULL: error
 *         other: successful
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_inet_pton(int fd, const char *src, void *dst);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_bind_local_cid
 * DESCRIPTION 
 *          This API is use to bind local cid. 
 * PARAMETERS 
 *        cid      [IN]: cid
 *        socket   [IN]: socket handle
 *        iptype   [IN]: iptype
 *        port     [IN]: port
 * RETURN VALUES
 *         NULL: error
 *         other: successful
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_bind_local_cid(mbtk_data_call_cid_index_enum cid, mbtk_socket_t socket, mbtk_data_call_iptype_enum iptype, uint16_t port);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_htonl
 * DESCRIPTION 
 *          This API is use to convert the long integer of the host sequence to the network sequence. 
 * PARAMETERS 
 *        val      [IN]: val
 * RETURN VALUES
 *         converted value
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern uint32_t ol_htonl(uint32_t val);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_htons
 * DESCRIPTION 
 *          This API is use to convert the short integer of the host sequence to the network sequence. 
 * PARAMETERS 
 *        val      [IN]: val
 * RETURN VALUES
 *         converted value
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern uint16_t ol_htons(uint16_t val);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ntohl
 * DESCRIPTION 
 *          This API is use to convert the long integer of the network sequence to the host sequence. 
 * PARAMETERS 
 *        val      [IN]: val
 * RETURN VALUES
 *         converted value
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern uint32_t ol_ntohl(uint32_t val);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ntohs
 * DESCRIPTION 
 *          This API is use to convert the short integer of the network sequence to the host sequence. 
 * PARAMETERS 
 *        val      [IN]: val
 * RETURN VALUES
 *         converted value
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern uint16_t ol_ntohs(uint16_t val); 

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_socket_errno
 * DESCRIPTION 
 *          This API is use to get socket errno. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *         socket errno
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_get_socket_errno(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_inet_addr
 * DESCRIPTION 
 *          This API is use to convert IP string to IN_ADDR. 
 * PARAMETERS 
 *        cp      [IN]: cp, ip string
 * RETURN VALUES
 *         IN_ADDR
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern uint32_t ol_inet_addr(const char *cp);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_inet_aton
 * DESCRIPTION 
 *          This API is use to convert decimal ip to binary. 
 * PARAMETERS 
 *        cp      [IN]: cp, ip string
 *        addr    [IN]: addr
 * RETURN VALUES
 *         0: successful
 *      other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_inet_aton(const char *cp, ip_addr_t *addr);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_inet_ntoa
 * DESCRIPTION 
 *          This API is use to convert binary ip to decimal. 
 * PARAMETERS 
 *        addr    [IN]: addr
 * RETURN VALUES
 *      NULL: error
 *     other: ip string
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern char *ol_inet_ntoa(const ip_addr_t *addr);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_inet6_addr
 * DESCRIPTION 
 *          This API is use to convert IPV6 string to IN_ADDR. 
 * PARAMETERS 
 *        inaddr  [IN]: inaddr
 *        addr    [IN]: addr, ipv6 string
 * RETURN VALUES
 *         IN_ADDR
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_inet6_addr(struct in6_addr *inaddr, ip6_addr_t *addr);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_inet_aton
 * DESCRIPTION 
 *          This API is use to convert decimal ipv6 to binary. 
 * PARAMETERS 
 *        cp      [IN]: cp, ipv6 string
 *        addr    [IN]: addr
 * RETURN VALUES
 *         0: successful
 *      other: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_inet6_aton(const char *cp, ip6_addr_t *addr);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_inet6_ntoa
 * DESCRIPTION 
 *          This API is use to convert binary ipv6 to decimal. 
 * PARAMETERS 
 *        addr    [IN]: addr
 * RETURN VALUES
 *      NULL: error
 *     other: ipv6 string
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern char *ol_inet6_ntoa(const ip6_addr_t *addr);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_soc_errno_trans_string
 * DESCRIPTION 
 *          This API is use to convert errno to string. 
 * PARAMETERS 
 *        errcode    [IN]: errcode
 * RETURN VALUES
 *      NULL: error
 *     other: errcode string
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern unsigned char * ol_soc_errno_trans_string(unsigned char errcode);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_pdp_ipv4addr
 * DESCRIPTION 
 *          This API is use to get pdp ipv4addr. 
 * PARAMETERS 
 *        ipv4addr    [IN]: ipv4addr
 *        cid         [IN]: cid
 * RETURN VALUES
 *      NULL
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_get_pdp_ipv4addr(unsigned char *ipv4addr, unsigned char cid);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_pdp_ipv6addr
 * DESCRIPTION 
 *          This API is use to get pdp ipv6addr. 
 * PARAMETERS 
 *        ipv6addr    [IN]: ipv6addr
 *        cid         [IN]: cid
 * RETURN VALUES
 *      NULL
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_get_pdp_ipv6addr(unsigned char *ipv6addr, unsigned char cid);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_ip_standard_chksum
 * DESCRIPTION 
 *          This API is use to standard chksum. 
 * PARAMETERS 
 *        dataptr    [IN]: dataptr
 *        len         [IN]: len
 * RETURN VALUES
 *      chksum value
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern uint16_t ol_ip_standard_chksum(void *dataptr, int len);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_set_ip_default_ttl
 * DESCRIPTION 
 *          This API is use to set ip default ttl. 
 * PARAMETERS 
 *        value    [IN]: value
 * RETURN VALUES
 *      NULL
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern uint16_t ol_set_ip_default_ttl(uint8_t value);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_ip_default_ttl
 * DESCRIPTION 
 *          This API is use to get ip default ttl. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *      ip default ttl value
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern uint16_t ol_get_ip_default_ttl(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_set_ping_access_flag
 * DESCRIPTION 
 *          This API is use to set ping access flag. 
 * PARAMETERS 
 *        on_off    [IN]: on_off
 * RETURN VALUES
 *      NULL
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern void ol_set_ping_access_flag(char on_off);


// ---------------------------------------------- SOCKET APIS ----------------------------------------------------//

#ifdef __cplusplus
}
#endif

#endif


