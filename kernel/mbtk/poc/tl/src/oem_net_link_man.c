#include <stdio.h>
//#include "netdb.h"

#include "oem_net_man.h"
#include "jptt_debug.h"

/*
 *  Return: 1=OK, 0=failed.
 */
extern int lib_oem_socket_get_net_status(void);

static  int  ppp_linked  = 0;

// st: PPP linked = 1, no PPP = 0
void (*on_network_changed)(int st) = NULL;

extern int oem_net_init(void (*cb)(int)) {
    on_network_changed = cb;
    
    ppp_linked = lib_oem_socket_get_net_status();
    DEBUG_I("PPP link = %d.", ppp_linked);

    return 0;
}

extern int oem_set_net_on(int on) {
    DEBUG_I("set net on=%d", on);
    
    if (on) {
        if (ppp_linked) {
            if (on_network_changed != NULL)
                on_network_changed(1);
        }
    }
    else {
        ppp_linked = lib_oem_socket_get_net_status();
    }

    return 0;
}

extern void oem_net_deinit(void) {
    DEBUG_I("oem net deinit...");
    ppp_linked = lib_oem_socket_get_net_status();
}

// ASR do not need this
extern int oem_set_route(void) {
    return 0;
}

extern unsigned int get_local_ip() {
    return 0;
}

extern unsigned int get_remote_ip(const char *addr) {
    return 0;
}
