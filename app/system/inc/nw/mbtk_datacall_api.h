
#ifndef __MBTK_DATACALL_API_H
#define __MBTK_DATACALL_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "ol_nw_pub.h"

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


typedef enum 
{
	mbtk_data_call_deactive_req,
	mbtk_data_call_active_req
}mbtk_data_call_active_req_enum;

typedef void (*mbtk_data_call_callback)(uint8_t index, uint8_t status);
typedef void (*mbtk_nw_status_callback)(mbtk_nw_status_struct *status);

typedef enum 
{
	mbtk_data_call_err = 0,
	mbtk_data_call_ok = 1
}mbtk_data_call_return_enum;


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

#include "mbtk_socket_api.h"


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
	int iptype;//mbtk_data_call_iptype_enum
	mbtk_data_call_ipv4_info_strcut v4info;
	mbtk_data_call_ipv6_info_strcut v6info;
}mbtk_data_call_info_strcut;





/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_wait_network_regist
 * DESCRIPTION 
 *          This API is use to blocking waiting network regist. 
 * PARAMETERS 
 *        sec    [IN]: max wait time
 * RETURN VALUES
 *         mbtk_data_call_ok: successful
 *         mbtk_data_call_err: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_data_call_return_enum ol_wait_network_regist(int sec);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_wait_network_regist
 * DESCRIPTION 
 *          This API is use to regist data call callback. 
 * PARAMETERS 
 *        callback    [IN]: callback
 * RETURN VALUES
 *         mbtk_data_call_ok: successful
 *         mbtk_data_call_err: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_data_call_return_enum ol_regist_data_call_callback(mbtk_data_call_callback callback);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_data_call_start
 * DESCRIPTION 
 *          This API is use to start datacall.
 * PARAMETERS 
 *        callback    [IN]: callback
 * RETURN VALUES
 *         mbtk_data_call_ok: successful
 *         mbtk_data_call_err: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_data_call_return_enum ol_data_call_start(mbtk_data_call_cid_index_enum index, mbtk_data_call_iptype_enum iptype, char * apn, char * user, char * pwd, int veritype);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_data_call_stop
 * DESCRIPTION 
 *          This API is use to stop datacall.
 * PARAMETERS 
 *        index    [IN]: index, see enum mbtk_data_call_cid_index_enum
 *        iptype    [IN]: iptype, see enum mbtk_data_call_iptype_enum
 * RETURN VALUES
 *         mbtk_data_call_ok: successful
 *         mbtk_data_call_err: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_data_call_return_enum ol_data_call_stop(mbtk_data_call_cid_index_enum index, mbtk_data_call_iptype_enum iptype);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_data_call_info
 * DESCRIPTION 
 *          This API is use to get data call info.
 * PARAMETERS 
 *        index    [IN]: index, see enum mbtk_data_call_cid_index_enum
 *        iptype   [IN]: iptype, see enum mbtk_data_call_iptype_enum
 *        info     [IN]: info
 * RETURN VALUES
 *         mbtk_data_call_ok: successful
 *         mbtk_data_call_err: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_data_call_return_enum ol_get_data_call_info(mbtk_data_call_cid_index_enum index, mbtk_data_call_iptype_enum iptype, mbtk_data_call_info_strcut *info);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_set_data_call_auto_reconnect
 * DESCRIPTION 
 *          This API is use to set data call auto reconnect.
 * PARAMETERS 
 *        index    [IN]: index, see enum mbtk_data_call_cid_index_enum
 *        reconn   [IN]: reconn, see enum mbtk_data_call_atuo_reconn_enum
 * RETURN VALUES
 *         mbtk_data_call_ok: successful
 *         mbtk_data_call_err: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_data_call_return_enum ol_set_data_call_auto_reconnect(mbtk_data_call_cid_index_enum index, mbtk_data_call_atuo_reconn_enum reconn);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_data_call_state
 * DESCRIPTION 
 *          This API is use to get data call state.
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *         data call state value: see enum mbtk_data_call_state
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_data_call_state ol_get_data_call_state(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_set_cid_status
 * DESCRIPTION 
 *          This API is use to set cid status.
 * PARAMETERS 
 *        index    [IN]: index, see enum mbtk_data_call_cid_index_enum
 *        status   [IN]: status, see enum mbtk_data_call_active_req_enum
 * RETURN VALUES
 *         mbtk_data_call_ok: successful
 *         mbtk_data_call_err: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_data_call_return_enum ol_set_cid_status(mbtk_data_call_cid_index_enum index, mbtk_data_call_active_req_enum status);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_regist_nw_cb
 * DESCRIPTION 
 *          This API is use to regist nw cb.
 * PARAMETERS 
 *        callback    [IN]: callback
 * RETURN VALUES
 *         mbtk_data_call_ok: successful
 *         mbtk_data_call_err: error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_data_call_return_enum ol_regist_nw_cb(mbtk_nw_status_callback callback);

#ifdef __cplusplus
}
#endif

#endif


