#include "simcom_ntp_client.h"
#include "mbtk_os.h"
#include "ntp_api.h"
#include "ol_nw_api.h"
#include "simcom_ntp_client.h"
#include "simcom_common.h"
#include "mbtk_err.h"

mbtk_taskref MBTK_Ntp_taskRef = NULL;
mbtk_semref MBTK_Ntp_semRef = NULL;

sMsgQRef SC_Ntp_msgQRef = NULL;

void mbtk_ntp_thread(void *param)
{
    int time_out;
    int status;
    SIM_MSG_T ntp_result = {SC_SRV_NTP, SC_NTP_OK, 0, NULL};
    ol_REG_STATUS_INFO reg_info;
    
    while(1)
    {
        ol_os_sem_request(MBTK_Ntp_semRef, MBTK_OS_SUSPEND);

        time_out = 10;
        status = 0;
        
        memset(&reg_info, 0x0, sizeof(ol_REG_STATUS_INFO));
        ol_nw_get_reg_status(&reg_info, 1);
        if(reg_info.state != OL_NW_REG_STA_REG_HPLMN && reg_info.state != OL_NW_REG_STA_REG_ROAMING)
        {
            ntp_result.arg1 = SC_NTP_ERROR_NETWORK_FAIL;
            goto result_send;
        }
        
        do
        {
            status = ol_ntp_get_status();
            ol_os_task_sleep(200);
            if(time_out <= 0)
            {
                ntp_result.arg1 = SC_NTP_ERROR_TIME_OUT;
                goto result_send;
            }
            time_out--;
        }while(status == 0);
      
        ntp_result.arg1 = SC_NTP_OK;
        
result_send:
        sAPI_MsgQSend(SC_Ntp_msgQRef, &ntp_result);
    }
}


SCntpReturnCode sAPI_NtpUpdate(SCntpOperationType commad_type, char* host_addr, int time_zone, sMsgQRef magQ_urc)
{
    int result = SC_NTP_OK;
    switch(commad_type)
    {
        case SC_NTP_OP_SET:
        {
            if(ol_ntp_set_host_name(host_addr) != 0)
                result = SC_NTP_ERROR;
            
            ol_set_timezone(time_zone);
            break;
        }
        case SC_NTP_OP_GET:
        {
            char * host_name  = ol_ntp_get_host_name();
            if(host_name == NULL)
                result = SC_NTP_ERROR;
            
            memcpy(host_addr, host_name, strlen(host_name));
            break;
        }
        case SC_NTP_OP_EXC:
        {
            if(magQ_urc)
                SC_Ntp_msgQRef = magQ_urc;
            else
                return SC_NTP_ERROR_INVALID_PARAM;
        
            if(!MBTK_Ntp_semRef)
            {
                if(ol_os_sem_creat(&MBTK_Ntp_semRef, 0, MBTK_OS_FIFO) != mbtk_os_success)
                {
                    return SC_NTP_ERROR;
                }
            }
            if(!MBTK_Ntp_taskRef)
            {
                if(ol_os_task_creat(&MBTK_Ntp_taskRef, NULL, 1024, 200, "MBTK_Ntp_task", mbtk_ntp_thread, NULL) != mbtk_os_success)
                {
                    return SC_NTP_ERROR;
                }
            }
            if(MBTK_Ntp_semRef)
            {
                ol_ntp_sync_time(); /*sync and auotomatic*/
                ol_os_sem_release(MBTK_Ntp_semRef);
            }
            break;
        }
    }

    return result;
}

void sAPI_GetSysLocalTime(tm_rtc *currUtcTime)
{
    unsigned int t;
    struct tm* lt;
    struct tm lt2 = {0};
    lt = &lt2;
    
    t = ol_time(&t);
    lt = ol_gmtime(&t);
    
    currUtcTime->tm_sec = lt->tm_sec;
    currUtcTime->tm_min = lt->tm_min;
    currUtcTime->tm_hour = lt->tm_hour;
    currUtcTime->tm_mday = lt->tm_mday;
    currUtcTime->tm_mon = lt->tm_mon;
    currUtcTime->tm_year = lt->tm_year;
    currUtcTime->tm_wday = lt->tm_wday;
}


