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

extern void bot_app_entry(void);

int main(int argc, char **argv)
{
    bot_app_entry();
    exit(0);
}
