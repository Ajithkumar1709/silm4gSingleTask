#include <stdio.h>
#include <string.h>
#include "mbtk_esim_api.h"
#include "mbtk_comm_api.h"
#include "menu_demo_api.h"
#include "jparser.h"
#include "mbtk_api.h"

void esim_chip_demo(void);
void esim_profile_demo(void);
void esim_notification_demo(void);

static demo_menu_info menu_info[] =
{
    {"chip","[opt],[param]",esim_chip_demo,NULL},
    {"profile","[opt],[param1],[param2],[param3],[param4],[param5],[param6]",esim_profile_demo,NULL},
    {"notification","[opt],[param1],[param2],[param3],[param4]",esim_notification_demo,NULL},
};

demo_menu_info *esim_demo_menu_info(unsigned int *num)
{
    *num = sizeof(menu_info)/sizeof(menu_info[0]);
    return menu_info;
}


int esim_demo_wait_network(void)
{
    if (ol_wait_network_regist(120) != mbtk_data_call_ok)
    {
        op_uart_printf("esim_demo_wait_network ol_wait_network_regist time out\n");
        return -1;
    }
    op_uart_printf("esim_demo_wait_network execute ol_data_call_start \n");
    if (ol_data_call_start(mbtk_cid_index_2, mbtk_data_call_v4, "ctnet", NULL, NULL, 0) != mbtk_data_call_ok)
    {
        op_uart_printf("esim_demo_wait_network ol_data_call_start fail\n");
        return -1;
    }
    return 0;
}


void esim_info_callback(EsimMessageType_t msg_type, const char *json_data, int json_data_len)
{
    op_uart_printf(json_data);
}

void esim_error_callback(EsimMessageType_t msg_type, const char *json_data, int json_data_len)
{
    op_uart_printf(json_data);
}


void esim_chip_demo(void)
{
    int opt;
    int ret;
    DEMO_MEUN_GET_INT_PARAM(0,&opt, 0,3,0);

    ol_esim_set_location(0);
    ol_esim_set_info_callback(esim_info_callback);
    ol_esim_set_error_callback(esim_error_callback);
    
    switch(opt)
    {
        case 0:     //chip info
        {
            ret = ol_esim_chip_info();
            if(ret)
            {
                op_uart_printf("ol_esim_chip_info ret = %d", ret);
                break;
            }
            break;
        }
        case 1:     //chip defaultsmdp
        {
            char smdp[64] = {0};
            DEMO_MEUN_GET_STR_PARAM(1,smdp,64,"");
            /**example
             * ol_esim_chip_defaultsmdp("rsp-0001.linksfield.net");
            **/
            ret = ol_esim_chip_defaultsmdp(smdp);
            if(ret)
            {
                op_uart_printf("ol_esim_chip_defaultsmdp ret = %d", ret);
                break;
            }
            break;
        }
        case 2:     //chip purge
        {
            ret = ol_esim_chip_purge();
            if(ret)
            {
                op_uart_printf("ol_esim_chip_purge ret = %d", ret);
                break;
            }
            break;
        }
        default:
        {
            op_uart_printf("unknown chip opt");
            break;
        }
    }
}

void esim_profile_demo(void)
{
    int opt;
    int ret;
    DEMO_MEUN_GET_INT_PARAM(0,&opt, 0,7,0);

    ol_esim_set_location(0);
    ol_esim_set_info_callback(esim_info_callback);
    ol_esim_set_error_callback(esim_error_callback);
    switch(opt)
    {
        case 0:     //profile list
        {
            ret = ol_esim_profile_list();
            if(ret)
            {
                op_uart_printf("ol_esim_profile_list ret = %d", ret);
                break;
            }
            break;
        }
        case 1:     //profile nickname
        {
            char iccid[32] = {0};
            char alias[32] = {0};
            DEMO_MEUN_GET_STR_PARAM(1,iccid,32,"");
            DEMO_MEUN_GET_STR_PARAM(2,alias,32,"");
            
            /**example
             * ol_esim_profile_nickname("89801029000001343203", "link_progile");
            **/
            ret = ol_esim_profile_nickname(iccid, alias);
            if(ret)
            {
                op_uart_printf("ol_esim_profile_nickname ret = %d", ret);
                break;
            }
            break;
        }
        case 2:     //profile enable
        {
            char iccid[32] = {0};
            int refreshflag = 0;
            DEMO_MEUN_GET_STR_PARAM(1,iccid,32,"");
            DEMO_MEUN_GET_INT_PARAM(2,&refreshflag, 0,1,0);

            /**example
             * ol_esim_profile_enable("89801029000001343203", 1);
            **/
            ret = ol_esim_profile_enable(iccid, refreshflag);
            if(ret)
            {
                op_uart_printf("ol_esim_profile_enable ret = %d", ret);
                break;
            }
            ol_set_modem_function(0, 0);
            ol_set_modem_function(1, 0);
            break;
        }
        case 3:     //profile disable
        {
            char iccid[32] = {0};
            int refreshflag = 0;
            DEMO_MEUN_GET_STR_PARAM(1,iccid,32,"");
            DEMO_MEUN_GET_INT_PARAM(2,&refreshflag, 0,5,0);

            /**example
             * ol_esim_profile_disable("89801029000001343203", 1);
            **/
            ret = ol_esim_profile_disable(iccid, refreshflag);
            if(ret)
            {
                op_uart_printf("ol_esim_profile_disable ret = %d", ret);
                break;
            }
            ol_set_modem_function(0, 0);
            ol_set_modem_function(1, 0);
            break;
        }
        case 4:     //profile delete
        {
            char iccid[32] = {0};
            int refreshflag = 0;
            DEMO_MEUN_GET_STR_PARAM(1,iccid,32,"");

            /**example
             * ol_esim_profile_delete("89801029000001343203");
            **/
            ret = ol_esim_profile_delete(iccid);
            if(ret)
            {
                op_uart_printf("ol_esim_profile_delete ret = %d", ret);
                break;
            }
            break;
        }
        case 5:     //profile download
        {
            char iccid[32] = {0};
            int numbers;
            char opt_string[5][256] = {0};
            EsimProfileOptList_t opt_list[5] = {0};

            for(numbers = 0; numbers < 6; numbers++)
            {
                DEMO_MEUN_GET_INT_PARAM((numbers*2) + 1,&opt_list[numbers].opt_int, 0,6,0);
                if(opt_list[numbers].opt_int <= 0)
                {
                    break;
                }
                DEMO_MEUN_GET_STR_PARAM((numbers*2) + 2, opt_string[numbers],256,"");
                opt_list[numbers].opt_string = opt_string[numbers];
            }
            if (esim_demo_wait_network() != 0)
            {
                op_uart_printf("esim_demo_wait_network fail\n");
                break;
            }
            
            /**example
             * EsimProfileOptList_t opt_list[1] = {{MBTK_ESIM_PROFILE_OPT_A, "LPA:1$rsp-0001.linksfield.net$5H9MY-PTG45-3F5YM-ZFP9V"}};
             * ol_esim_profile_download(opt_list, sizeof(opt_list)/sizeof(opt_list[0]), 60);
            **/
            ret = ol_esim_profile_download(opt_list, numbers, 60);
            if(ret)
            {
                op_uart_printf("ol_esim_profile_download ret = %d", ret);
                break;
            }
            
            ol_esim_profile_read_new_iccid(iccid);
            op_uart_printf("new profile iccid : [%s]", iccid);
            
            break;
        }
        case 6:     //profile discovery
        {
            int numbers;
            char opt_string[5][64] = {0};
            EsimProfileOptList_t opt_list[5] = {0};

            for(numbers = 0; numbers < 5; numbers++)
            {
                DEMO_MEUN_GET_INT_PARAM(numbers + 1,&opt_list[numbers].opt_int, 0,5,0);
                if(opt_list[numbers].opt_int <= 0)
                {
                    break;
                }
                DEMO_MEUN_GET_STR_PARAM( numbers+2, opt_string[numbers],64,"");
                opt_list[numbers].opt_string = opt_string[numbers];
            }
            if (esim_demo_wait_network() != 0)
            {
                op_uart_printf("esim_demo_wait_network fail\n");
                break;
            }
            
            /**example
             * EsimProfileOptList_t opt_list[1] = {{MBTK_ESIM_PROFILE_OPT_S, "rsp-0001.linksfield.net"}};
             * ol_esim_profile_discovery(opt_list, sizeof(opt_list)/sizeof(opt_list[0]), 60);
            **/
            ret = ol_esim_profile_discovery(opt_list, numbers,60);
            if(ret)
            {
                op_uart_printf("ol_esim_profile_discovery ret = %d", ret);
                break;
            }
            break;
        }
        default:
        {
            op_uart_printf("unknown profile opt");
            break;
        }
    }
}


void esim_notification_demo(void)
{
    int opt;
    int ret;
    DEMO_MEUN_GET_INT_PARAM(0,&opt, 0,3,0);

    ol_esim_set_location(0);
    ol_esim_set_info_callback(esim_info_callback);
    ol_esim_set_error_callback(esim_error_callback);
    switch(opt)
    {
        case 0:     //notification list
        {
            ret = ol_esim_notification_list();
            if(ret)
            {
                op_uart_printf("ol_esim_notification_list ret = %d", ret);
                break;
            }
            break;
        }
        case 1:
        {
            int remove_flag;
            int all_flag;

            unsigned long sequence_id[5] = {0};
            
            DEMO_MEUN_GET_INT_PARAM(1,&remove_flag, 0,1,0);
            DEMO_MEUN_GET_INT_PARAM(2,&all_flag, 0,1,0);

            DEMO_MEUN_GET_INT_PARAM(3,&sequence_id[0], 0,65536,0);
            DEMO_MEUN_GET_INT_PARAM(4,&sequence_id[1], 0,65536,0);
            DEMO_MEUN_GET_INT_PARAM(5,&sequence_id[2], 0,65536,0);
            DEMO_MEUN_GET_INT_PARAM(6,&sequence_id[3], 0,65536,0);
            DEMO_MEUN_GET_INT_PARAM(7,&sequence_id[4], 0,65536,0);
            
            if (esim_demo_wait_network() != 0)
            {
                op_uart_printf("esim_demo_wait_network fail\n");
                
                break;
            }
            
            /**example
             * unsigned long sequence_id[5] = {1,2,3,4,5};
             * ol_esim_notification_process(0, 0, sequence_id, sizeof(sequence_id)/sizeof(sequence_id[0]), 60);
            **/
            ret = ol_esim_notification_process(remove_flag, all_flag, sequence_id, sizeof(sequence_id)/sizeof(sequence_id[0]), 60);
            if(ret)
            {
                op_uart_printf("ol_esim_notification_process ret = %d", ret);
                break;
            }
            break;
        }
        
        case 2:
        {
            
            int all_flag;

            unsigned long sequence_id[5] = {0};
            
            DEMO_MEUN_GET_INT_PARAM(1,&all_flag, 0,1,0);

            DEMO_MEUN_GET_INT_PARAM(2,&sequence_id[0], 0,65536,0);
            DEMO_MEUN_GET_INT_PARAM(3,&sequence_id[1], 0,65536,0);
            DEMO_MEUN_GET_INT_PARAM(4,&sequence_id[2], 0,65536,0);
            DEMO_MEUN_GET_INT_PARAM(5,&sequence_id[3], 0,65536,0);
            DEMO_MEUN_GET_INT_PARAM(6,&sequence_id[4], 0,65536,0);

            /**example
             * unsigned long sequence_id[5] = {1,2,3,4,5};
             * ol_esim_notification_remove(0, sequence_id, sizeof(sequence_id)/sizeof(sequence_id[0]));
            **/
            ret = ol_esim_notification_remove(all_flag, sequence_id, sizeof(sequence_id)/sizeof(sequence_id[0]));
            if(ret)
            {
                op_uart_printf("ol_esim_notification_remove ret = %d", ret);
                break;
            }
            break;
        }
        default:
        {
            op_uart_printf("unknown notification opt");
            break;
        }
    }
}
