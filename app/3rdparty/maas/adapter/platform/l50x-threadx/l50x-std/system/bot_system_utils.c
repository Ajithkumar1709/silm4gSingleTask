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

// #define BOT_CUSTOMER_SW_VERSION_LEN     40u
#define BOT_CUSTOMER_HW_VERSION_LEN     40u


// static char g_sw[BOT_CUSTOMER_SW_VERSION_LEN] = {0};
static char g_hw[BOT_CUSTOMER_HW_VERSION_LEN] = "LYNQ-L505C-3E";
static uint8_t *printf_buf = NULL;

void bot_printf(const char *fmt, ...)
{
    va_list ap;

    if (printf_buf == NULL) {
        printf_buf = bot_os_alloc(BOT_PRINTF_BUF_SIZE);
        if (printf_buf == NULL) {
            return;
        }
    }

    va_list args;
    va_start(args, fmt);
    vsnprintf((char*)printf_buf, BOT_PRINTF_BUF_SIZE, fmt, args);
    op_uart_printf("BOT_LOG:%s",printf_buf);
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
    mbtk_device_firmware_ver_struct *firmware_ver = NULL;
    mbtk_device_api_err_enum err_num = ol_get_firmware_version(&firmware_ver);
    int len = 0;
    if ((err_num == 0) && (firmware_ver != NULL)) {
        len = strlen(firmware_ver->softversion);
        bot_printf("softversion(len = %d): %s\n", len, firmware_ver->softversion); // TODO 删除改行
        return (const char*)firmware_ver->softversion;
    } else {
        bot_printf("err_num = %d\n", err_num);
        return NULL;
    }
}

const char* bot_hardware_version_get(void)
{// TODO 待实�?
    bot_printf("g_hw: %s\n", g_hw);
    return g_hw;
}

int bot_random_generate(uint8_t * random, unsigned size)
{
    // FILE *handle;
    // ssize_t ret = 0;
    // handle = fopen("/dev/urandom", "r");
    // if (handle == NULL) {
    //     perror("open /dev/urandom failed\n");
    //     return 0;
    // }
    // ret = fread(random, size, 1, handle);
    // if (ret != 1) {
    //     bot_printf("fread error: %d\n", (int)ret);
    //     fclose(handle);
    //     return 0;
    // }
    // fclose(handle);
    
	return 1;
}

