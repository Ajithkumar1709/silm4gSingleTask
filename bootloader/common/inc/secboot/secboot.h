#ifndef _SECBOOT_H_
#define _SECBOOT_H_

#define SECBOOT_DBG(fmt,...) uart_printf(fmt, ##__VA_ARGS__)
#include "tbbr_img_def.h"
#include "tbbr_oid.h"
#include "auth_common.h"
/*----------- platform add ------------*/
#include "common.h"
/*----------------------------------*/

typedef enum {
	ITEM_CP,
	ITEM_DSP,
	ITEM_APP,
	ITEM_USER1,
	ITEM_USER2,
	ITEM_USER3,
	ITEM_LOGO,
	ITEM_UPDATER,
	/*
	ITEM_CP_LOGO,
	ITEM_CP_1,
	ITEM_CP_2,
	*/
	ITEM_END
}sb_issue_item_id_t;

typedef struct{
	sb_issue_item_id_t item_id;
	const char * item_name;
	unsigned int item_cert_id;
	unsigned int item_img_id;
	const char * item_hash_oid;
}sb_issue_item_map_t;

int secboot_is_fuse_enabled(void);
#ifdef UPDATER_SECFOTA_SUPPORT
int secboot_init(void *address);
#else
int secboot_init(const char *pname);
int secboot_init_by_ram(void *address);
#endif
int secboot_item_check(sb_issue_item_id_t item_id_idx,int rest);
void set_s_fip_open_addr(const unsigned int value);
UINT32 get_s_fip_open_addr(void);
#ifdef SECBOOT_ARB_SUPPORT
INT32 secboot_nv_ctr_item_check(sb_issue_item_id_t item_id_idx, int reset);
void enable_nv_counter_write_permission(void);
void disable_nv_counter_write_permission(void);
UINT32 get_nv_counter_write_permission(void);
#endif
#endif /*_SECBOOT_H_*/

