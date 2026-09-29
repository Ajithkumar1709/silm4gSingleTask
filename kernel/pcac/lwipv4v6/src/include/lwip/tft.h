#ifndef __TFT_H__
#define __TFT_H__

#include "lwipopts.h"
#include "ip_nat.h"

#if IS_LWIP_PLATFORM_1802_1802S
#include "Dialer_Task.h"
#include "teldef.h"
typedef struct TftInfoList_st   TftInfoList_CM;
#else
#include "pdpdef.h"
#endif

typedef struct _tft_result_st {
    void * pf_info;
	unsigned char epsid; //secondary cid
	unsigned char qfi;
	unsigned char psi;
	unsigned char rsvd;
}tft_result_st;

static inline void tft_init_tft_result(tft_result_st * tft_result, struct netif * inp)
{
    tft_result->epsid = netif_get_cid(inp);
    tft_result->qfi = 0;
    tft_result->psi = 0;
    tft_result->pf_info = NULL;
}

static inline void tft_get_tft_info_from_pbuf(tft_result_st * tft_result, struct pbuf * p)
{
    if ((NULL == p)
    || (NULL == p->pf_info)
    || (NULL == tft_result)) {
        return;
    }

    tft_result->epsid = p->epsid;
    tft_result->qfi = p->qfi;
    tft_result->psi = p->psi;
    tft_result->pf_info = p->pf_info;
}

static inline void tft_set_pbuf_tft_from_tft_stru(struct pbuf * p, tft_result_st * tft_result)
{
    if ((NULL == p) 
    || (NULL == tft_result)
    || (NULL == tft_result->pf_info)) {
        return;
    }

    p->epsid = tft_result->epsid;
    p->qfi = tft_result->qfi;
    p->psi = tft_result->psi;
    p->pf_info = tft_result->pf_info;
}

static inline void tft_set_pbuf_tft_from_nat_entry(struct pbuf * p, ip_nat_table_t *nat_entry)
{
    if ((NULL == nat_entry) 
    || (NULL == p)) {
        return;
    }

    /*if exist p->pf_info, don't update pbuf tft*/
    /*for app pbuf, maybe do tft_route before, this tft info is the latest, not the tft result store in nat_entry*/
    /*and reverse, the pbuf tft is latest, we use it to update nat_entry here.*/
    /*for app pbuf, will alway do tft_route, so cache for nat_entry is un-useble*/
    if (p->pf_info) {
        p->nat_entry = nat_entry;
        nat_entry->epsid = p->epsid;
        nat_entry->qfi = p->qfi;
        nat_entry->psi = p->psi;
        nat_entry->pf_info = p->pf_info;
        return;
    }

    /*update p tft_info even nat_entry->pf_info is NULL*/
    /*if nat_entry->pf_info is NULL, that maybe happed by tft_new or tft_delete trigger*/
    /*if nat_entry->pf_info is NULL, this pbuf will do ip_route when pdp_output*/
    if (netif_is_IF_PDN(nat_entry->netif_nw)) {
        p->nat_entry = nat_entry;
        p->epsid = nat_entry->epsid;
        p->qfi = nat_entry->qfi;
        p->psi = nat_entry->psi;
        p->pf_info = nat_entry->pf_info;
        return;
    }
}

static inline void tft_set_nat_entry_tft_from_pbuf(ip_nat_table_t *nat_entry, struct pbuf * p)
{
    if ((NULL == nat_entry) 
    || (NULL == p)) {
        return;
    }

    nat_entry->epsid = p->epsid;
    nat_entry->qfi = p->qfi;
    nat_entry->psi = p->psi;
    nat_entry->pf_info = p->pf_info;
}

err_t tft_ulrate_control(u8_t protocol, struct netif *inp, struct pbuf *p, int* psendFlag);
err_t tft_route_fn(struct pbuf *p, struct netif *inp, const char *func, const int line);
err_t tft_route_ip6_fn(struct pbuf *p, struct netif *inp, const char *func, const int line);

#define tft_route(p, inp)       tft_route_fn(p, inp, __FUNCTION__, __LINE__)
#define tft_route_ip6(p, inp)   tft_route_ip6_fn(p, inp, __FUNCTION__, __LINE__)

#endif

