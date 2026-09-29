
#include "bot_system.h"

#define SIOCGIFHWADDR 1

typedef struct
{
    char imsi[32];
    char ccid[32];
    int rssi;
}DEV_NET_INFO_T;

static u8* mbtk_net_task_stack = NULL;
static DEV_NET_INFO_T dev_net_info = {0};
static mbtk_taskref network_thread_id = NULL;
static int is_net_connect = 0;

static int network_init(void)
{
    int ret = 0;
    if(is_net_connect == 0)
    {
        is_net_connect = ol_wait_network_regist(300);
        if(is_net_connect == 1)
        {
            ol_get_sim_imsi(dev_net_info.imsi);
            if(ol_data_call_start(mbtk_cid_index_2, mbtk_data_call_v4v6, "", NULL, NULL, 0) != mbtk_data_call_ok)
            {
                bot_printf("network_init ol_data_call_start fail\n");
                return -1;
            }
        }
    }
    return is_net_connect;
}

static int network_loop(void)
{
    int ret = -1;
    memset(&dev_net_info, 0, sizeof(dev_net_info));
    ret = network_init();
    if(ret == 1)
    {
        while (1) {
            is_net_connect = ol_wait_network_regist(5);
            if(is_net_connect == 0)
            {
                bot_printf("network disconnection!\r");
                return -1;
            }
            bot_msleep(2000);
        }
    }
    return 0;
}

static void network_task(void * arg)
{
    static int net_work_times = 0;
    bot_printf("input network_task\r");
    while (1) {
        bot_printf("network_task times:%d\r", net_work_times++);
        network_loop();
        bot_msleep(1000);
    }
    bot_os_free(mbtk_net_task_stack);
    ol_os_task_delete(network_thread_id);
    network_thread_id = NULL;
    return;
}

int bot_network_init(void)
{
#define MBTK_TASK_STACK_SIZE (1024 * 4)
    bot_printf("start bot_network_init\r");
    u8 *mbtk_net_task_stack = bot_os_alloc(MBTK_TASK_STACK_SIZE);
    if(mbtk_net_task_stack == NULL)
    {
        bot_printf("malloc stack fail!\r");
        return -1;
    }
    if (network_thread_id == NULL) {
        bot_printf("doing bot_network_init\r");
        int status = ol_os_task_creat(&network_thread_id, mbtk_net_task_stack, 
            MBTK_TASK_STACK_SIZE, 223, "network_task", network_task, NULL);
        if(status != mbtk_os_success)
        {
            bot_os_free(mbtk_net_task_stack);
            bot_printf("bot_task_create fail\r");
            return -1;
        }
    }
    return 0;

}

int bot_network_is_ready(void)
{
    bot_printf("bot_network_is_ready:%d\r", is_net_connect);
    return is_net_connect;
}

int bot_network_rssi_get(signed short *rssi)
{
    if(rssi == NULL)
    {
        bot_printf("bot_network_rssi_get fail because rssi is null\r");
        return -1;
    }
    signed short csq = 0;
    mbtk_device_api_err_enum ret = ol_nw_get_csq(&csq);
    if(mbtk_device_api_err_none != ret)
    {
        bot_printf("mbtk_get_csq fail(%d)\r", ret);
        return ret;
    }
    
    bot_printf("csq: %d\n\r", csq);
    if (csq < 70) {
        *rssi = csq * 2 - 113;
    }
    if (csq >= 100) {
        *rssi = csq - 216;
    }
    dev_net_info.rssi = *rssi;
    
    bot_printf("rssi:%d\r", *rssi);
    return mbtk_device_api_err_none;
}

char *bot_network_get_mac(void)
{
#define MAC_ADDR_SIZE 16
    static char bot_network_mac[MAC_ADDR_SIZE] = {0};
    mbtk_device_api_err_enum ret = ol_get_mac(bot_network_mac);
    if(mbtk_device_api_err_none != ret)
    {
        bot_printf("bot_network_get_mac fail(%d)\r\n", ret);
        return NULL;
    }
    int i = 0;
    bot_printf("bot_network_get_mac:");
    for(i = 0; i < MAC_ADDR_SIZE; i++)
    {
        bot_printf("%2X", bot_network_mac[i]);
    }
    return bot_network_mac;
}

int bot_network_ccid_get(char *ccid)
{
    mbtk_sim_api_err_enum ret = 0;
    if(ccid == NULL)
    {
        bot_printf("bot_network_ccid_get fail because ccid is null\r");
        return -1;
    }
    if(dev_net_info.ccid[0] == 0)
    {
        ret = ol_get_sim_iccid(ccid);
        if(mbtk_sim_api_err_none != ret)
        {
            bot_printf("mbtk_sim_get_iccid fail(%d)\r", ret);
            return ret;
        }
        memcpy(dev_net_info.ccid, ccid, 32);
    }
    else
    {
        memcpy(ccid, dev_net_info.ccid, 32);
    }
    bot_printf("bot_network_ccid_get:%s\r", ccid);
    return mbtk_sim_api_err_none;
}

int bot_network_imei_get(char *imei)
{
    if(imei == NULL)
    {
        bot_printf("mbtk_get_imei fail because imei is null\r");
        return -1;
    }
    mbtk_device_api_err_enum ret = ol_get_device_imei(imei);
    if(mbtk_device_api_err_none != ret)
    {
        bot_printf("mbtk_get_imei fail(%d)\r", ret);
        return ret;
    }
    bot_snprintf(imei, 32, "%s", imei);
    
    bot_printf("bot_network_imei_get:%s\r", imei);
    return mbtk_device_api_err_none;
}

int bot_network_lbs_get(unsigned short *mcc, unsigned short *mnc, unsigned int *cid, unsigned int *lac)
{
#define TEMP_BUF_SIZE 5
    char temp_buf[TEMP_BUF_SIZE];
    ol_REG_STATUS_INFO reg_info = {0};
    
    if(bot_network_is_ready() == 0)
    {
        bot_printf("bot_network_lbs_get fail because net is not ready\r");
        return -1;
    }
    
    int ret = ol_nw_get_reg_status(&reg_info, 1);
    memset(temp_buf, 0, TEMP_BUF_SIZE);
    memcpy(temp_buf, dev_net_info.imsi, 3);
    *mcc = strtol(temp_buf, NULL, 10);
    memset(temp_buf, 0, TEMP_BUF_SIZE);
    memcpy(temp_buf, dev_net_info.imsi + 3, 2);
    *mnc = strtol(temp_buf, NULL, 10);
    *cid = reg_info.cid;
    *lac = reg_info.lac;
    
    return 0;

}

int bot_network_rat_get(unsigned char *rat)
{
    if(rat == NULL)
    {
        bot_printf("bot_network_rat_get fail because rat is null\r");
        return -1;
    }
    ol_REG_STATUS_INFO reg_info = {0};
    int ret = ol_nw_get_reg_status(&reg_info, 1);
    if(ret < 0)
    {
        bot_printf("bot_network_rat_get fail\r");
        return -1;
    }
    else
    {
        *rat = reg_info.act;
        bot_printf("bot_network_rat_get succ:%d\r", *rat);
        return 0;
    }
}

int bot_network_dns_available(void)
{
    return 0;
}

