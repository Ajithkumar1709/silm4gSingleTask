#ifndef __OEM_NET_MAN_H__
#define __OEM_NET_MAN_H__

typedef enum {
    NET_BROKEN   = 0x00,
    NET_LINKED   = 0x01,
    NET_RECONFIG = 0x02      // means broken & recover quickly
} oem_net_status_t;

extern int oem_net_init(void (*cb)(int st));
extern void oem_net_deinit(void);

// switch on/off, may deactive then active net interface
extern int oem_set_net_on(int on);

// config route. linux config router
extern int oem_set_route(void);

#endif
