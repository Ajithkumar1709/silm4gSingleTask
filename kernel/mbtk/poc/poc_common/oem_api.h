#ifndef __MBTK_OEM_COMM_H__
#define __MBTK_OEM_COMM_H__

#include "mbtk_log.h"

#define OEM_MSGQ_MSG_SIZE       (sizeof(oem_msg_struct))
#define OEM_MSGQ_QUEUE_SIZE     (50)
#define OEM_THREAD_STACKSIZE    (4096*5)
#define OEM_THREAD_PRIO         50


typedef struct oem_msg_str
{
    uint8 msg_id;
    void *param;
}oem_msg_struct;


typedef struct mbtk_event_msg
{
    uint8 type;
    void *data;
}mbtk_event_msg;


enum req
{
    MI_OEM_REQ = 29,
    //SVCID_OEM = 30,
};


#endif /*__MBTK_OEM_COMM_H__*/

