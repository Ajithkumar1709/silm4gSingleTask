#include <stdio.h>
#include <string.h>

#include "osa.h"

#include "OS_Wrapper.h"
#include "jptt_debug.h"


#define UART_ACK_LEN   (128)
#define MAX_ATC_SIZE   (256)
#define OS_TICK   (5)

static  void    (*on_uart_received)(char *, int) = NULL;
static  void    (*on_poc_reply)(const char *, int) = NULL;

static  int       module_ready  = 0;

/*
**
*/

static void (*on_modem_rdy)(char *imei) = NULL;
static void (*on_iccid)(char *obuf, int olen) = NULL;
static void (*on_rssi)(int val1, int val2) = NULL;
static void (*on_op)(char *ostr, int olen, int act) = NULL;
static void (*on_mode)(int val0) = NULL;
static void (*on_nw_scan)(int val0) = NULL;
static void (*on_nw_info)(int xG) = NULL;
static void (*on_hw_ver)(char *tag) = NULL;
static void (*on_power_down)(void) = NULL;

/*
**   UART  AT-command interfaces
**
*/

static void oem_msleep(int ms) {
    OSATaskSleep(ms / OS_TICK);
}

extern int oem_atc_wait_modem_ready(void (*cb)(char *)) {
    char imei[20+20];
    char *ps1;
    int res;
    
    on_modem_rdy = cb;
    
    memset(imei, 0, sizeof(imei));
    res = lib_oem_get_device_serial_number(imei);
    DEBUG_D("get imei = %s, ret = %d", imei, res);
    
    ps1 = strchr(imei, '\n');
    if (ps1 != NULL)
        *ps1 = '\0';

    on_modem_rdy(imei);  // cb with imei means MODEM is ready
    return 0;
}

extern int oem_atc_get_iccid(void (*cb)(char *obuf, int olen)) {
    char iccid[32];
    int i, res, card;
	char sim_status = 0;

    on_iccid = cb;    
    memset(iccid, 0, sizeof(iccid));

    // wait 5s for sim card ready.
    card = 0;
    for (i=0; i<5; i++) {
	    int ret=0;
	    mbtk_get_sim_status(&sim_status);
	    
	    DEBUG_D("get card st sim_status %d", sim_status);
        if (sim_status == 1) {
            res = mbtk_sim_get_iccid(iccid);
            break;
        }

        oem_msleep(1000);
    }
	DEBUG_D("get card st iccid %s", iccid);

    if (sim_status == 1 && res == 0) {
        on_iccid(iccid, strlen(iccid));
    } else {
        on_iccid(NULL, 0);
    }
    
    return 0;
}

extern int oem_atc_get_rssi(void (*cb)(int val1, int val2)) {
    int csq;

    on_rssi = cb;
    
    csq = lib_oem_get_rssi();    // -130 ~ -44, [2,30] = [-109,53dBm], 31 = -51dBm^; 7=-99dBm
    DEBUG_I("get rssi ret: %d", csq);
    if (csq == 0) {
        on_rssi(-136, 99);
        return 0;
    }

    on_rssi(csq-5, 99);

    return 0;
}

/*
** success: 0=NULL (not login), 1="ct", 2="cm", 3="cn"
** failure: -1=NULL
*/
static int is_empty_s(char *s) {
    if (s == NULL) return 1;
    if (s[0] == '\0') return 1;
    return 0;
}

extern int oem_atc_get_operator(void (*cb)(char *ostr, int olen, int act)) {
    int res;

    on_op = cb;

    if (!module_ready) {
        while (1) {
            oem_msleep(1000);
            res = lib_oem_socket_get_net_status();
            if (res == 1)
                break;
        }
        module_ready = 1;
    }

    on_op("CT", 2, 1);

    return 0;
}

/*
** 2=2G 3=3G 4=4G
** 0=no network
*/
extern int oem_atc_get_nw_info(void (*cb)(int xG)) {
    on_nw_info = cb;
    // TODO...

    on_nw_info(4);
    return 0;
}

extern int oem_atc_get_hw_version(void (*cb)(char *tag)) {
    static char model[8];
    char *ps1;
    int rlen;
    
    on_hw_ver = cb;
    memset(model, 0, sizeof(model));
    
    ps1 = lib_oem_get_model();
    DEBUG_D("get model = %s", ps1);

    rlen = strlen(ps1);
    if (rlen > 7)
        rlen = 7;
    
    strncpy(model, ps1, rlen);
    on_hw_ver(model);

    return 0;
}

// +CCLK: "18/10/15,07:36:53+32"
extern int oem_atc_wallclock(char *outs) {
    /*ql_rtc_time_t wc;
    int res;
    
    res = ql_rtc_get_time(&wc);
    sprintf(outs, "\"%02d/%02d/%02d,%02d:%02d:%02d+%02d\"", wc.tm_year%100, wc.tm_mon, wc.tm_mday, wc.tm_hour, wc.tm_min, wc.tm_sec, 32);
    (void)res;
    */
    return 0;
}

extern int oem_atc_restart_UE() {
    int res;
    
    //res = lib_oem_module_init();
    DEBUG_D("module init ret: %d", res);
    oem_msleep(2000);

    return 0;
}

extern int oem_atc_power_down(void (*cb)(void)) {
    on_power_down = cb;

    on_power_down();
    return 0;
}

/*
**
*/

extern void oem_atc_start_gps() {
}

extern void oem_atc_stop_gps() {
}


/*
**  JPtt uart interface
**
*/

extern int joem_start_uart_man(void (*cb)(char *, int), void (*hk)(const char *, int)) {
    DEBUG_D("start uart man with %u %u", (unsigned int)cb, (unsigned int)hk);

    on_uart_received = cb;
    on_poc_reply = hk;

    module_ready = 0;

    return 0;
}

extern void joem_stop_uart_man(void) {
}

// send line (ended with "\r\n") to mcu (on uart)
extern int joem_uart_send(const char *obuf, int olen) {
    DEBUG_D("oem uart send: %s (%d)", obuf, olen);
    
    return atRespStr( 1, 0, 0, obuf);
}

extern void joem_on_poc_atc(char *rbuf, int rlen) {
    if (on_uart_received != NULL)
        on_uart_received(rbuf, rlen);
}

void OEMPOC_AT_Recv(char* buf ,int len)
{
    MLOG_D(MLOG_POC, POC,"OEMPOC_AT_Recv %s\r\n", buf);
    joem_on_poc_atc(buf, len);
}


void emcu_on_poc_ack(const char *ack,int alen)
{
}

