
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "mbtk_os.h"
#include "mbtk_device_api.h"
#include "corget_api.h"
#include "oem_api.h"

#if (defined(MBTK_POC_SUPPORT_ZZD) || defined(MBTK_POC_SUPPORT_CHAYU))


extern mbtk_msgqref g_oem_msgq;
extern mbtk_ostimerref g_oem_timer;

int OEM_SetRrcTime(int ticks)
{
    return 0;
}

void OEMSleep(int ticks)
{
    mbtk_os_task_sleep(ticks/5);
}

unsigned long OEM_Get_time(void)
{
    return mbtk_os_get_ticks()*5;
}

int OEM_SetTimer(unsigned int atime)
{
    /*creat timer*/
    mbtk_os_status status;
    mbtk_os_timer_status_struct status_s = {0};
    mbtk_os_get_timer_status(g_oem_timer, &status_s);
    if (status_s.status == MBTK_OS_TIMER_ACTIVE)
    {
        OEM_CancelTimer();
    }
    
    status = mbtk_os_timer_start(g_oem_timer, atime/5, 0, OEMTimerOut, NULL);
    //DIAG_ASSERT(status == mbtk_os_success);
    OEMLogPrintf("%s:oemtimer start.", __func__);
    return status;
}

int OEM_CancelTimer(void)
{
    OEMLogPrintf("%s: ENTER", __func__);
    return mbtk_os_timer_stop(g_oem_timer);
}

int OEM_GetICCID(char *iccid)
{
    int iret = 0;
    char imeibuf[20] = {0};

    if(iret = mbtk_sim_get_iccid(imeibuf) != mbtk_device_api_err_none)
    {
        return -1;
    }
    return 0;
}

void OEM_FotaInit(unsigned int package_size)
{
    OEMLogPrintf("do nothing", __func__);

}

int OEM_FotaWrite(char *buffer, int received)
{
#ifdef MBTK_FOTA_SUPPORT
    OEMLogPrintf("do nothing", __func__);
#endif
    return 0;
}

void oem_thread(void *arg)
{
    oem_msg_struct req;

    UINT32 reqHandle;
    while(1)
    {
        OEMLogPrintf("%s: OemMsgQRecv wait... \n", __func__);
        memset(&req,0,OEM_MSGQ_MSG_SIZE);

        mbtk_os_msgq_recv(g_oem_msgq, (void *)&req, OEM_MSGQ_MSG_SIZE, MBTK_OS_SUSPEND);
        OEMLogPrintf("%s: OemMsgQRecv: req->msg_id- %d\n", __func__, req.msg_id);
        if(req.msg_id == MI_OEM_REQ)
        {
            OEM_PendMessage(req.param);
        }
    }
}

int OEM_PostMessage(void *msg)
{
    oem_msg_struct msg_str= {0};
    mbtk_os_status osaStatus;
    int ret = 0;
    OEMLogPrintf("%s: msg - %s", __func__, (char *)msg);

    if(!g_oem_msgq)
    {
        return -1;
    }

    msg_str.msg_id = MI_OEM_REQ;
    msg_str.param = msg;
    osaStatus = mbtk_os_msgq_send(g_oem_msgq, OEM_MSGQ_MSG_SIZE, &msg_str,MBTK_OS_NO_SUSPEND);
    
    OEMLogPrintf("%s: %dsend msg done.", __func__, osaStatus);
    return ret;
}

// Tone
int OEM_PlayTone(int Type)
{
    OEMLogPrintf("OEM_PlayTone\r\n");
    mbtk_oem_play_tone(Type,0, 1);
    mbtk_os_task_sleep(20);
    mbtk_oem_play_tone(Type,0, 0);
}

int OEM_TTS_SpkEx( char* atxt)
{
    uart_printf("OEM_TTS_SpkEx %s\r\n", atxt);
    OEM_TTS_Spk(atxt);
}

int OEM_TTS_Spk( char* atxt)
{
    uint16 txt_len  = 0;
    uint16 *atxt_convert = (uint16 *)atxt;
    int i =0;
    OEMLogPrintf("OEM_TTS_Spk %s\r\n", atxt);

    if(atxt == NULL)
    {
        return 0;
    }

    txt_len = strlen(atxt)/4;
    while(i< txt_len)
    {
        *atxt_convert = OEM_ConvertFourChars(atxt+i*4);
        i++;
        atxt_convert++;
    }
    *atxt_convert = 0;
    
    OEMLogPrintf("OEM_TTS_Spk len %d\r\n", i);
    if(mbtk_tts_check_can_stop())
    {
        mbtk_tts_stop();
    }

#if defined(MBTK_POC_SUPPORT_ZZD) || defined(MBTK_POC_SUPPORT_CHAYU)
    mbtk_tts_set_cb(OEM_TTS_Status_CB);
#else
    mbtk_tts_set_cb(NULL);
#endif
    mbtk_tts_spk(atxt, txt_len, 1, 0);
    return 0;
}

#endif /*(defined(MBTK_POC_SUPPORT_ZZD) || defined(MBTK_POC_SUPPORT_CHAYU))*/




