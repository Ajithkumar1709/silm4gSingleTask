#ifndef __MBTK_DATACALL_API_INCLUDE_H
#define __MBTK_DATACALL_API_INCLUDE_H



#include "mbtk_pub_type.h"
#include "inet6.h"
#include "inet.h"


#define AF_INET         2
#define AF_INET6        10


#define MBTK_DATA_CALL_TASK_STACK_SIZE  (4*1024)
#define MBTK_DATA_CALL_TASK_PRI     180

#define MBTK_RECONN_DONE 1


typedef enum 
{
	mbtk_network_register_result,
	mbtk_data_call_active_result,
	mbtk_data_call_deactive_result,
	mbtk_voice_call_event_ind,
	mbtk_sms_report_id_ind,
}mbtk_data_call_msg_type_enum;

typedef struct 
{
	void *message;
	uint8_t type;
	uint8_t index;
	uint8_t value;
}mbtk_data_call_msg_struct;


void mbtk_send_data_call_msg(uint8_t index, uint8_t result,uint8_t value);
void mbtk_send_data_call_reg_cb_msg(uint8_t index, uint8_t result,uint8_t state, uint8_t act);
void mbtk_send_data_call_pdp_cb_msg(uint8_t index, uint8_t result,uint8_t state);

#endif
