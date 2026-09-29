/*
 * Copyright (C) 2021 Alibaba Group Holding Limited
 *
 */

#include "bot_default_config.h"
#include "bot_system.h"
#include "bot_system_utils.h"
#include "bot_maas.h"

/* Device id for test, string format, user should change to their real device id */
#define BOT_TEST_DEVICE_ID   "TEST12345678"

/* User data for test, JSON format, user should change to their real user data */
#define USER_TEST_DATA_STRING "{\"assetId\":\"%s\",\"soh\":90,\"soc\":90,\"voltage\":3000,\"temperature\":3000,\"fullChargeCycles\":12,\"batteryStatus\":1,\"source\":0,\"coordinateSystem\":0,\"longitude\":120.03,\"latitude\":60.01,\"altitude\":30.04}"

static uint8_t g_maas_user_data[1024] = {0};

/* sample entry */
void bot_app_entry(void)
{
    int ret = 0;
    int count = 0;
    int connect_status;
    int device_status;

    /* 1. Start MaaS init */
    ret = bot_maas_init();
    if (ret != 0) {
        return;
    }

#if !BOT_COMP_AT

    /* 2. Query device connect status every second, until connected or 100S timeout */
    count = 100;
    while(count--) {
        connect_status = bot_maas_connect_status_get();
        if (connect_status == 1) {
            break;
        }
        bot_msleep(1000);
    }

    if (connect_status != 1) {
        return;
    }

    /* 3. Query device register status */
    device_status = bot_maas_device_status_get(BOT_TEST_DEVICE_ID);
    if (device_status != 1) {

        /* 4. Start device register */
        ret = bot_maas_device_register(BOT_TEST_DEVICE_ID, "3001-64.0V30AH", "ADV1.0");
        if (ret != 0) {
            return;
        }

        /* 5. Query device register status every second, until registered or 180S timeout */
        count = 180;
        while(count--) {
            device_status = bot_maas_device_status_get(BOT_TEST_DEVICE_ID);
            if (device_status == 1)
            {
                break;
            }

            bot_msleep(1000);
        }

        if (device_status != 1) {
            return;
        }
    }

    while(1){
        bot_snprintf((char*)g_maas_user_data, 1024, USER_TEST_DATA_STRING, BOT_TEST_DEVICE_ID);

        /* 6. Publish user data */
        ret = bot_maas_data_publish((uint8_t*)g_maas_user_data, strlen((char*)g_maas_user_data));
        if (ret != 0) {
            bot_printf("bot_maas_data_publish fail, ret %d\n\r", ret);
        }

        bot_msleep(60000);
    }

#endif
}

