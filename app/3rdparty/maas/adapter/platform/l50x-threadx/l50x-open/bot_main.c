/*
 *
 * Copyright (C) 2020-2021 Alibaba Group Holding Limited
*/
/**
 * @file bot_main.C
 *
 * @brief main entry function for platform
 *
 *
 */
#include "bot_system_utils.h"
#include "bot_maas.h"
#include "bot_system.h"
#include "bot_default_config.h"
#include "bot_network.h"
#include "bot_hal_at.h"
#include "bot_hal_rtc.h"

extern int bot_app_entry(void);
int bot_main_input(int argc, char **argv)
{
#define MAX_MAAS_AT_RESP 500
    UINT32 run_times = 0;
    bot_printf("bot application thread enter");
    int ret = bot_app_entry();
    bot_printf("bot_app_entry result is:%d", ret);
    if (ret != 0) {
        return ret;
    }
    while(1)
    {
        run_times++;
        bot_msleep(2000);
        bot_printf("bot_main_task_input loop times:%d\r", run_times);
    }
}

