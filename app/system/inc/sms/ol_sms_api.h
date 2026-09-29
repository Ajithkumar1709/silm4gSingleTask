#ifndef _MBTK_SMS_API_H_
#define _MBTK_SMS_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "time.h"

#define MBTK_SMS_MAX_DATA_LEN    500
#define MBTK_SMS_AT_TIMEOUT    60
typedef enum
{
    SMS_STAT_REC_UNREAD, //Received unread messages
    SMS_STAT_REC_READ, //Received read messages
    SMS_STAT_STO_UNSENT, //Stored unsent messages
    SMS_STAT_STO_SENT, //Stored sent messages
    SMS_STAT_ALL, //All messages
}mbtk_sms_list_stat;

typedef enum
{
    SMS_DEL_NORMAL, //delete msg reference index
    SMS_DEL_ALL_1, //delete all read msg
    SMS_DEL_ALL_2, //delete all read and snet msg
    SMS_DEL_ALL_3, //delete all read and snet and unsnet msg
    SMS_DEL_ALL_4, //delete all msg
}mbtk_sms_del_mode;

typedef enum
{
    SMS_PERFORM_SM,
    SMS_PERFORM_ME,
}mbtk_sms_perform_id;


typedef struct
{
    unsigned char perform_id;
    unsigned char used;
    unsigned char total;
}mbtk_sms_mem;

typedef struct
{
    mbtk_sms_mem read;
    mbtk_sms_mem write;
    mbtk_sms_mem recv;
}mbtk_sms_mem_list;

typedef struct
{
    unsigned char msg_type;
    unsigned char sca[40];
    unsigned char tosca;
}mbtk_sms_config;

typedef struct
{    
    unsigned char decorde_type;
    unsigned char msg_data[MBTK_SMS_MAX_DATA_LEN];
    unsigned int msg_len;
}mbtk_sms_msg;


typedef struct
{
    unsigned char     tsYear;
    unsigned char     tsMonth;
    unsigned char     tsDay;
    unsigned char     tsHour;
    unsigned char     tsMinute;
    unsigned char     tsSecond;
    unsigned char     tsTimezone;
    unsigned char     tsZoneSign;
}mbtk_sms_timestamp;

typedef struct
{
    unsigned char msgid;
    unsigned char stat;
    unsigned char da[40];
    mbtk_sms_timestamp timestamp;
    mbtk_sms_msg msg;
}mbtk_sms_info;

typedef void (*mbtk_sms_report_cb)(mbtk_sms_info *msg_info);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_sms_mem
 * DESCRIPTION 
 *  	This API is used to get msg memory area info 
 * PARAMETERS 
 *    simid : sim index,if not support dual sim,default 0
 *		mem_list : a pointer to mbtk_sms_mem_list struct
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern int ol_sms_mem(unsigned char simid,mbtk_sms_mem_list *mem_list);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_sms_config
 * DESCRIPTION 
 *  	This API is used to set msg server config
 * PARAMETERS 
 *    simid : sim index,if not support dual sim,default 0
 *		config : a pointer to mbtk_sms_config
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern int ol_sms_config(unsigned char simid,mbtk_sms_config *config);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_sms_list
 * DESCRIPTION 
 *  	This API is used to get msg list 
 * PARAMETERS 
 *    simid : sim index,if not support dual sim,default 0
 *		stat : msg status,see mbtk_sms_list_stat enum
 *		list_array : a array to recv msg list
 *		offset : offset in msg memory
 *		max_count : max number of list_array
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern int ol_sms_list(unsigned char simid,unsigned char stat,void *list_array,unsigned int offset,unsigned int max_count);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_sms_write
 * DESCRIPTION 
 *  	This API is used write a msg to msg memory area
 * PARAMETERS 
 *    simid : sim index,if not support dual sim,default 0
 *		da : a porinter to destination address
 *		data_str : a porinter to data string
 *		ret_index : index of this msg in msg memory area
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_sms_write(unsigned char simid,unsigned char *da,unsigned char *data_str,unsigned int *ret_index);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_sms_send
 * DESCRIPTION 
 *  	This API is used to send msg which in the msg memory area
 * PARAMETERS 
 *   	simid : sim index,if not support dual sim,default 0
 *		index : index of this msg in msg memory area,return by ol_sms_write
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_sms_send(unsigned char simid,unsigned int index);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_sms_read
 * DESCRIPTION 
 *  	This API is used to read msg info in msg memory area
 * PARAMETERS 
 *    simid : sim index,if not support dual sim,default 0
 *		index : index of this msg in msg memory area
 *		msg_info : a pointer to struct mbtk_sms_info
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_sms_read(unsigned char simid,unsigned int index,mbtk_sms_info *msg_info);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_sms_delete
 * DESCRIPTION 
 *  	This API is used to delete a msg in msg memory area
 * PARAMETERS 
 *    simid : sim index,if not support dual sim,default 0
 *		mode : delete mode,see mbtk_sms_del_mode
 *		index : index of this msg in msg memory area
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_sms_delete(unsigned char simid,unsigned char mode,unsigned int index);
/*****************************************************************************
 *
 * FUNCTIO
 *      ol_sms_readly_status
 * DESCRIPTION 
 *      This API is used to Querying the Short Message Status
 * PARAMETERS
 *      NONE
 * RETURN VALUES
 *      SMS Ready : 1
 *      NOT Ready : 0
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
extern int ol_sms_readly_status(void);
/*****************************************************************************
 *
 * FUNCTIO
 *      ol_sms_get_sca
 * DESCRIPTION 
 *      This API is used to get the SMS center number
 * PARAMETERS
 *      getcfg : a pointer to mbtk_sms_config
 * RETURN VALUES
 *      SUCCESS : 0
 *      FAIL : -1
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
extern int ol_sms_get_sca(mbtk_sms_config *getcfg);


/*****************************************************************************
 *
 * FUNCTIO
 *      ol_sms_report_register
 * DESCRIPTION 
 *      This API is used to Register a callback function to handle incoming SMS messages
 * PARAMETERS
 *      cb_func : callback function
 * RETURN VALUES
 *      SUCCESS : 0
 *      FAIL : -1
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
extern int ol_sms_report_register(mbtk_sms_report_cb cb_func);

#ifdef __cplusplus
}
#endif

#endif

