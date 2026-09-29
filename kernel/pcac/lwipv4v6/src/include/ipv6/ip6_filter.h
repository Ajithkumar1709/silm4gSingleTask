#ifndef __IPV6_FILTER_H__
#define __IPV6_FILTER_H__

#include "opt.h"
#include "pbuf.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ip6_info_t
{
    u16_t   src_port;       // src port,    0 - invalid
    u16_t   dst_port;       // dst port,    0 - invalid
    u32_t   src_ip[4];      // src ip,      0 - invalid
    u32_t   dst_ip[4];      // dst ip,      0 - invalid
}ip6_info_t;

typedef struct _ip6_elt_t
{
    u16_t   port_start;     // port start,  0 - invalid
    u16_t   port_end;       // port end,    0 - invalid
    u32_t   prefix_len;     // prefix length, 0 - invalid
    u32_t   ip_addr[4];     // ip6 address,  0 - invalid
}ip6_elt_t;

typedef struct _ip6_filter_t
{
    u16_t       flag;       // 0: not using; 1: using
    u8_t        type;       // 1 - tcp, 2 - udp, 3 - tcp and udp
    u8_t        action;     // 0: allow the packet; 1: drop the packet;

    ip6_elt_t   src;        // source
    ip6_elt_t   dst;        // destination
}ip6_filter_t;

typedef struct _ip6_filter_param_list
{
    unsigned char   protocol;           /*0: invalid; 1:TCP,2:UDP,3:BOTH TCP/UDP,4:ICMP */
    unsigned char   action;             //0: allow the packet; 1: drop the packet;
    unsigned char   src_prefix_len;     //0: invalid 128,96,64
    unsigned char   dest_prefix_len;    //0: invalid 128,96,64

    unsigned int    src_ip[4];          //0: invalid
    unsigned int    des_ip[4];          //0: invalid

    unsigned short  src_port_start;     //0: invalid
    unsigned short  src_port_end;       //0: invalid

    unsigned short  des_port_start;     //0: invalid
    unsigned short  des_port_end;       //0: invalid

    struct _ip6_filter_param_list *next;
}ip6_filter_param_list;

int ip6_filter_set_rules(ip6_filter_param_list* list);

#ifdef __cplusplus
}
#endif

#endif /* __IP_FILTER_H__ */

