#include "simcom_loc.h"
#include "simcom_common.h"
#include "mbtk_err.h"
#include "ol_lbs.h"
#include "mbtk_os.h"


static sMsgQRef SC_LbsResp_msgq = NULL;


mbtk_taskref MBTK_Loc_taskRef = NULL;
mbtk_semref MBTK_Loc_semRef = NULL;


void mbtk_loc_thread(void *param)
{
    SC_lbs_info_t *sub_data = NULL;
    SIM_MSG_T msg = {SC_SRV_LBS, 0, 0, NULL};
    mbtk_lbs_info_t info;
    
    while(1)
    {
        ol_os_sem_request(MBTK_Loc_semRef, MBTK_OS_SUSPEND);

        sub_data = malloc(sizeof(SC_lbs_info_t));
        memset(&info, 0x0, sizeof(mbtk_lbs_info_t));
        memset(sub_data, 0x0, sizeof(SC_lbs_info_t));

        sub_data->u8ErrorCode = ol_lbs_get_info(NULL, 0, &info, 10);
        
        op_uart_printf("lbs_info = %s, %s", info.longitude_str,info.latitude_str);
        op_uart_printf("sub_data->u8ErrorCode = %d", sub_data->u8ErrorCode);
        if(sub_data->u8ErrorCode == 0)
        {
            sub_data->u32Lng = atof(info.longitude_str) * 1000000;
            sub_data->u32Lat = atof(info.latitude_str) * 1000000;
        }
        else
        {
            sub_data->u8ErrorCode = 1;
        }
        msg.arg3 = sub_data;
        
        sAPI_MsgQSend(SC_LbsResp_msgq, &msg);
    }
}

SC_LBS_RETURNCODE sAPI_LocTypeSet(int LocType)
{
    simcom_api_not_support();
    return SC_LBS_SUCCESS;
}

SC_LBS_RETURNCODE sAPI_LocServerSet(char *server)
{
    simcom_api_not_support();
    return SC_LBS_SUCCESS;
}

SC_LBS_RETURNCODE sAPI_LocGet(int channel, sMsgQRef magQ_urc,int type)
{
    if(!MBTK_Loc_semRef)
    {
        if(ol_os_sem_creat(&MBTK_Loc_semRef, 0, MBTK_OS_FIFO) != mbtk_os_success)
        {
            return SC_LBS_FAIL;
        }
    }
    
    if(!MBTK_Loc_taskRef)
    {
        if(ol_os_task_creat(&MBTK_Loc_taskRef, NULL, 2048, 200, "MBTK_Loc_task", mbtk_loc_thread, NULL) != mbtk_os_success)
        {
            return SC_LBS_FAIL;
        }
    }
    SC_LbsResp_msgq = magQ_urc;
    if(MBTK_Loc_semRef)
    {
        ol_os_sem_release(MBTK_Loc_semRef);
    }
    
    return SC_LBS_SUCCESS;
}

