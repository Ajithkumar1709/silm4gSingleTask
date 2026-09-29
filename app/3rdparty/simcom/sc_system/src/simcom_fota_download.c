#include <string.h>
#include "simcom_fota_download.h"
#include "mbtk_err.h"
#include "ol_fota.h"
#include "mbtk_datacall_api.h"


#define FOTA_LOCAL_CID mbtk_cid_index_2
#define FOTA_LOCAL_CID_PDN_TYPE mbtk_data_call_v4v6

static int mbtk_fota_wait_network(void)
{
    if (ol_wait_network_regist(120) != mbtk_data_call_ok)
    {
        return -1;
    }

    ol_os_task_sleep(200 *5);
    
    if(ol_data_call_start(FOTA_LOCAL_CID, FOTA_LOCAL_CID_PDN_TYPE, "ctnet", NULL, NULL, 0) != mbtk_data_call_ok)
    {
        return -1;
    }
 
    return 0;
}


int sAPI_FotaServiceBegin(void* pram)
{
    SC_FotaApiParam *param = pram;
    mbtk_fota_server_info server_info = {0};
    strncpy(server_info.host, param->host, FOTA_SERVER_CONTEXT_STRLEN);
    strncpy(server_info.username, param->username, FOTA_SERVER_CONTEXT_STRLEN);
    strncpy(server_info.password, param->password, FOTA_SERVER_CONTEXT_STRLEN);
    server_info.mode = param->mode;
    
    if (mbtk_fota_wait_network() != 0)
    {
        return 3;
    }
    return ol_mini_fota_firmware_download(&server_info, param->sc_fota_cb);

}
void sAPI_GetMiniSysStatus(SC_MiniSysStatus *MiniSysStatus)
{
    simcom_api_not_support();
}

