



#ifndef __MBTK_SOCKET_API_H
#define __MBTK_SOCKET_API_H


#include "mbtk_socket_api_include.h"



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




mbtk_socket_t mbtk_socket(int domain, int type, int protocol);

mbtk_socket_t mbtk_socket_with_cb(int domain, int type, int protocol, socket_callback callback);

int mbtk_get_random_port(void);

int mbtk_socket_bind(mbtk_socket_t socket, const struct sockaddr *pname, int namelen);

int mbtk_socket_connect(mbtk_socket_t socket, const char *addr, uint16_t port);

int mbtk_socket_addr_connect(mbtk_socket_t socket, const struct sockaddr *pname, int namelen);

int mbtk_socket_send(mbtk_socket_t socket, uint8_t *pbuf, size_t bufsize, uint32_t flags);

int mbtk_socket_sendto(mbtk_socket_t socket, void *pbuf, size_t sendsize, uint32_t flags,
                             const char *to, uint16_t toport);

int mbtk_socket_recv(mbtk_socket_t socket, uint8_t *recvbuf, size_t wantsize, uint32_t flags);

int mbtk_socket_recvfrom(mbtk_socket_t socket, void* recvbuf, int wantsize, uint32_t flags,
                                  char *addr, uint16_t *port);

int mbtk_socket_listen(mbtk_socket_t socket, int backlog);

int mbtk_socket_accept(mbtk_socket_t socket,  char *addr, uint16_t *port);

int mbtk_socket_close(mbtk_socket_t socket);

int mbtk_socket_shutdown(mbtk_socket_t socket, int how);

int mbtk_socket_close_with_linger(mbtk_socket_t socket, uint8_t linger_onff, uint8_t sec);

int mbtk_socket_select(int max_fd, fd_set *readset, fd_set *writeset, fd_set *exceptset,
                            struct timeval *timeout);

int mbtk_socket_ioctl(mbtk_socket_t socket, int ctlcmd, void *arg);

int mbtk_get_hostbyname(const char *name, mbtk_ipaddr_struct *taddr);

int mbtk_get_hostbyname_ex(const char *name, mbtk_ipaddr_struct_ex *taddr);

int mbtk_get_hostbyname_local_cid(const char *name, mbtk_ipaddr_struct *taddr, mbtk_data_call_cid_index_enum cid);

int mbtk_socket_getsockname(mbtk_socket_t socket,  const struct sockaddr *pname, int *pnamelen);

int mbtk_socket_getpeername(mbtk_socket_t socket,  const struct sockaddr *pname, int *pnamelen);

int mbtk_socket_getopt(mbtk_socket_t socket, int level, int optname, void *poptval, int *poptlen);

int mbtk_socket_setopt(mbtk_socket_t socket, int level, int optname, const void *poptval, int optlen);

char *mbtk_inet_ntop(int fd, const void *src, char *dst, int size);

int mbtk_inet_pton(int fd, const char *src, void *dst);

int mbtk_socket_bind_local_cid(mbtk_data_call_cid_index_enum cid, mbtk_socket_t socket, mbtk_data_call_iptype_enum iptype, uint16_t port);

int mbtk_get_socket_errno(void);

void mbtk_inet6_addr(struct in6_addr *inaddr, ip6_addr_t *addr);

unsigned char *mbtk_socket_errno_trans_string(unsigned int errcode);

void mbtk_get_pdp_ipv4addr(unsigned char *ipv4addr, unsigned char cid);

void mbtk_get_pdp_ipv6addr(unsigned char *ipv6addr, unsigned char cid);

uint16_t ol_ip_standard_chksum(void *dataptr, int len);

int mbtk_get_net_addr_by_pcid(unsigned char cid,char *ip_addr, char *mask, char *gateway,char *dns);

uint16_t ol_set_ip_default_ttl(uint8_t value);
uint16_t ol_get_ip_default_ttl(void);
void ol_set_ping_access_flag(char on_off);
#endif

