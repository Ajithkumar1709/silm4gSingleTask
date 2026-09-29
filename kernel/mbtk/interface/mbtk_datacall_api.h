
#ifndef __MBTK_DATACALL_API_H
#define __MBTK_DATACALL_API_H


#include "mbtk_datacall_api_include.h"
#include "mbtk_nw_api.h"
typedef enum 
{
	mbtk_cid_index_invalid = 0,
	mbtk_cid_index_1,
	mbtk_cid_index_2,
	mbtk_cid_index_3,
	mbtk_cid_index_4,
	mbtk_cid_index_5,
	mbtk_cid_index_6,
	mbtk_cid_index_7,
	mbtk_cid_index_8,
	mbtk_cid_index_9,
	mbtk_cid_index_10,
	mbtk_cid_index_11,
	mbtk_cid_index_12,
	mbtk_cid_index_13,
	mbtk_cid_index_14,
	mbtk_cid_index_15,
	mbtk_cid_index_max
}mbtk_data_call_cid_index_enum;


typedef enum 
{
	mbtk_data_call_v4,
	mbtk_data_call_v6,
	mbtk_data_call_v4v6
}mbtk_data_call_iptype_enum;







typedef void (*mbtk_data_call_callback)(uint8_t index, uint8_t status);
typedef void (*mbtk_nw_status_callback)(mbtk_nw_status_struct *status);


typedef enum 
{
	mbtk_data_call_err = 0,
	mbtk_data_call_ok = 1
}mbtk_data_call_return_enum;


typedef enum 
{
	mbtk_data_call_finish,
	mbtk_data_call_net_err,
	mbtk_data_call_param_invalid,
	mbtk_data_call_sys_err
}mbtk_data_call_result_err_enum;

typedef enum 
{
	mbtk_data_call_status_active_fail,
	mbtk_data_call_status_active_success,
	mbtk_data_call_status_deactive_fail,
	mbtk_data_call_status_deactive_suceess
}mbtk_data_call_status_enum;


typedef enum 
{
	mbtk_data_call_deactive_req,
	mbtk_data_call_active_req
}mbtk_data_call_active_req_enum;


typedef enum 
{
	mbtk_auto_reconnect_disable,
	mbtk_auto_reconnect_enable
}mbtk_data_call_atuo_reconn_enum;


typedef enum 
{
	mbtk_not_active,
	mbtk_actived
}mbtk_data_call_state;




typedef struct 
{
	struct in_addr ip;
	struct in_addr pri_dns;
	struct in_addr sec_dns;
}mbtk_data_call_ipv4_addr_struct;

typedef struct 
{
	struct in6_addr ip;
	struct in6_addr pri_dns;
	struct in6_addr sec_dns;
}mbtk_data_call_ipv6_addr_struct;


typedef struct 
{
	int state;
	int reconnect;
	mbtk_data_call_ipv4_addr_struct ipv4addr;
}mbtk_data_call_ipv4_info_strcut;

typedef struct 
{
	int state;
	int reconnect;
	mbtk_data_call_ipv6_addr_struct ipv6addr;
}mbtk_data_call_ipv6_info_strcut;



typedef struct 
{
	int index; //mbtk_data_call_cid_index_enum
	int iptype; //mbtk_data_call_iptype_enum
	mbtk_data_call_ipv4_info_strcut v4info;
	mbtk_data_call_ipv6_info_strcut v6info;
}mbtk_data_call_info_strcut;


int demo_data_call(void);

mbtk_data_call_return_enum mbtk_wait_network_register(int sec);

mbtk_data_call_return_enum mbtk_regist_data_call_cb(mbtk_data_call_callback callback);

mbtk_data_call_return_enum mbtk_data_call_start(mbtk_data_call_cid_index_enum index, 
														mbtk_data_call_iptype_enum iptype, 
														char * apn, char * user, char * pwd, int veritype);

mbtk_data_call_return_enum mbtk_data_call_stop(mbtk_data_call_cid_index_enum index,
												mbtk_data_call_iptype_enum iptype);

mbtk_data_call_return_enum mbtk_get_data_call_info(mbtk_data_call_cid_index_enum index, 
													mbtk_data_call_iptype_enum iptype,
													mbtk_data_call_info_strcut *info);

mbtk_data_call_return_enum mbtk_set_auto_reconnect(mbtk_data_call_cid_index_enum index, 
													mbtk_data_call_atuo_reconn_enum reconn);


uint8_t mbtk_get_data_call_state();

int mbtk_get_local_rrc_release_interval(void);
int mbtk_set_local_rrc_release_interval(unsigned int time);

mbtk_data_call_return_enum mbtk_regist_nw_cb(mbtk_nw_status_callback callback);
int mbtk_set_cid_status(mbtk_data_call_cid_index_enum index, mbtk_data_call_active_req_enum status);




#endif

