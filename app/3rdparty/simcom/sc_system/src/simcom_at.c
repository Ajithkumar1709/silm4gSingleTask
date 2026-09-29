#include "simcom_at.h"
#include "simcom_common.h"
#include "simcom_os.h"

#include "mbtk_open_at.h"
#include "ol_os_comm_event.h"

sMsgQRef gAtUrcMsgQueue = NULL;


mbtk_taskref MBTK_At_taskRef = NULL;
mbtk_msgqref Mbtk_At_msgRef = NULL;
mbtk_semref Mbtk_At_semRef = NULL;

void mbtK_at_thread(void *param)
{
    int result = 0;
    int event = 0;
    char *rsp_str = NULL;
    
    SIM_MSG_T msg = {0};
    msg.msg_id = SRV_URC;
    msg.arg1 = SC_URC_INTERNAL_AT_RESP_MASK;
    
    while(1)
    {
        //wait at event
        ol_os_sem_request(Mbtk_At_semRef, MBTK_OS_SUSPEND);
        result = ol_os_msgq_recv(Mbtk_At_msgRef, &event, sizeof(int), 5*200);
        rsp_str = (char *)malloc(128);
        memset(rsp_str, 0x0, 128);
        
        if (result == mbtk_os_success && event == OL_EVENT_AT_RESP)
        {
            ol_read_at_response(rsp_str,128);
            msg.arg2 = strlen(rsp_str);
            
        }
        else if(result == mbtk_os_timeout)
        {
            msg.arg2 = mbtk_os_timeout;
        }
        else
        {
            msg.arg2 = mbtk_os_fail;
        }
        msg.arg3 = rsp_str;
        sAPI_MsgQSend(gAtUrcMsgQueue, &msg);
        ol_at_deinit();
    }
}


int sAPI_AtSend(char *command, unsigned int cmd_len)
{
    int result = 0;

    if(!Mbtk_At_msgRef)
    {
        result = ol_os_msgq_creat(&Mbtk_At_msgRef, "Mbtk_At_msg", sizeof(int), 20, MBTK_OS_FIFO);
        if (result != mbtk_os_success)
        {
            return -1;
        }

    }
    if(!Mbtk_At_semRef)
    {
        result = ol_os_sem_creat(&Mbtk_At_semRef, 0, MBTK_OS_FIFO);
        if(result != mbtk_os_success)
        {
            return -1;
        }
    }
    
    if(!MBTK_At_taskRef)
    {
        result = ol_os_task_creat(&MBTK_At_taskRef, NULL, 1024, 200, "MBTK_At_task", mbtK_at_thread, NULL);
        if(result != mbtk_os_success)
        {
            return -1;
        }
    }

    if(Mbtk_At_msgRef && MBTK_At_taskRef)
    {
        if (ol_at_init(&Mbtk_At_msgRef) != OL_E_NONE)
        {
            ol_os_msgq_delete(Mbtk_At_msgRef);
            Mbtk_At_msgRef = NULL;
            return -1;
        }
    }
    
    result = ol_send_at_command(command);
    if(result != OL_E_NONE)
    {
        return -1;
    }

    ol_os_sem_release(Mbtk_At_semRef);
    return 0;
}


