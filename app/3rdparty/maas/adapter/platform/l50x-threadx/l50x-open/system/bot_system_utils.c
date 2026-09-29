/*
 *
 * Copyright (C) 2020-2021 Alibaba Group Holding Limited
*/
/**
 * @file bot_system.C
 *
 * @brief dedicated iot adapter system functions which need be impementd by customer.
 *
 *
 */
#include "bot_system_utils.h"
#include "bot_system.h"

#define BOT_PRINTF_BUF_SIZE     1024u * 2u
#define BOT_TIMESTAMP_FORMAT    "%02x%02x%02x%02x%02x%02x"

#define BOT_CUSTOMER_HW_VERSION_LEN     40u


static uint8_t *printf_buf = NULL;

void bot_printf(const char *fmt, ...)
{
    if (printf_buf == NULL) {
        printf_buf = bot_os_alloc(BOT_PRINTF_BUF_SIZE);
        if (printf_buf == NULL) {
            return;
        }
    }

    va_list args;
    va_start(args, fmt);
    vsnprintf(printf_buf, BOT_PRINTF_BUF_SIZE, fmt, args);
    op_uart_printf("bot %s",printf_buf);
    va_end(args);
}

int bot_snprintf(_IN_ char *str, const int len, const char *fmt, ...)
{
    va_list args;
    int rc;
    va_start(args, fmt);
    rc = vsnprintf(str, len, fmt, args);
    va_end(args);

    return rc;
}

int bot_vsnprintf(_IN_ char *str, _IN_ const int len, _IN_ const char *format,
                  va_list ap)
{
    return vsnprintf(str, len, format, ap);
}


const char* bot_software_version_get(void)
{
    mbtk_device_firmware_ver_struct* version_obj = NULL;
    int ret = ol_get_firmware_version(&version_obj);
    if(ret == mbtk_device_api_err_none && version_obj != NULL)
    {
        bot_printf("bot_software_version_get succ(%s)\r", version_obj->softversion);
        return (const char*)(version_obj->softversion);
    }
    else
    {
        bot_printf("bot_software_version_get fail(%d)\r", ret);
        return NULL;
    }
}

static char g_hw[BOT_CUSTOMER_HW_VERSION_LEN] = "LYNQ-L505C-3E";
const char* bot_hardware_version_get(void)
{
    bot_printf("g_hw: %s\n", g_hw);
    return g_hw;
}


int bot_random_generate(uint8_t * random, unsigned size)
{
    if(random == NULL || size <= 0)
    {
        return 0;
    }
    static unsigned int last_time_num = 0;
    unsigned int time_num = (unsigned)ol_time(NULL);
    //以秒为种子，1s内第1+次调用不再重设种子
    if(last_time_num != time_num)
    {
        srand(time_num);
    }
    bot_printf("bot_random_generate time_num== %u\r", time_num);
    int i = 0;
    for(i = 0; i < size; i++)
    {
        random[i] = (rand() % 255);
    }
    last_time_num = time_num;
    return 1;
}

