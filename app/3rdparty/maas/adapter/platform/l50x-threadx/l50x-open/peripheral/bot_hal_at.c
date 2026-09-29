#include "bot_platform.h"
#include "bot_hal_at.h"

static bot_at_rx_cb g_at_callback = NULL;
int bot_hal_at_send(unsigned char * cmd, unsigned int len)
{
    int result = 0;
    int event = 0;
    static mbtk_msgqref msgref = NULL;
    if(cmd == NULL || len < 2)
    {
        bot_printf("bot_hal_at_send fail because cmd is null or len is error!\r");
        return -1;
    }
    if(msgref == NULL)
    {
        result = ol_os_msgq_creat(&msgref, "visual_at", sizeof(int), 20, MBTK_OS_FIFO);
        if(result != mbtk_os_success)
        {
            bot_printf("bot create msgref fail!\r");
            return;
        }
        bot_printf("bot create msgref success!\r");
        //init at
        if(ol_at_init(&msgref) != 0)
        {
            bot_printf("bot at init fail!\r");
            ol_os_msgq_delete(msgref);
            msgref = NULL;
            return -1;
        }
        bot_printf("bot at init success!\r");
    }
    //send at
    result = ol_send_at_command(cmd);
    if(result != 0)
    {
        bot_printf("send at cmd fail(%d)\r", result);
        return -1;
    }
    //wait at event
    result = ol_os_msgq_recv(msgref, &event, sizeof(int), 5*200);
    
#define MBTK_EVENT_AT_RESP 100
    if(result == mbtk_os_success && event == MBTK_EVENT_AT_RESP)
    {
        //at event recved,read resp
        char rsp_str[256] = {0};
        ol_read_at_response(rsp_str,256);
        bot_hal_at_callback(rsp_str, strlen(rsp_str));      
        bot_printf("bot at rsp str = %s\r",rsp_str);
    }
    else
    {
        bot_printf("bot at rsp err or timeout\r");
        return -1;
    }
    return 0;
}

int bot_hal_at_cb_register(bot_at_rx_cb cb)
{
    if (cb == NULL) {
        bot_printf("bot_hal_at_cb_register fail because cb is NULL");
        return -1;
    }
    g_at_callback = cb;
    
    return 0;
}

int bot_hal_at_callback(unsigned char *data, unsigned int len)
{
    if (data == NULL) {
        bot_printf("bot_hal_at_callback fail because data is null\r");
        return -1;
    }

    if (g_at_callback != NULL) {
        g_at_callback(data, len);
        return 0;
    }
    else
    {
        bot_printf("bot_hal_at_callback fail because g_at_callback is NULL");
        return -1;
    }
}