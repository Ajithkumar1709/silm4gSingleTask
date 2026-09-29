/**
  ******************************************************************************
  * @file    demo_gpio.c
  * @author  SIMCom OpenSDK Team
  * @brief   Source file of gpio operation.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 SIMCom Wireless.
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simcom_system.h"
#include "simcom_os.h"
#include "simcom_common.h"
#include "simcom_gpio.h"
#include "simcom_debug.h"
#include "uart_api.h"

#define SC_MODULE_GPIO_10 mbtk_pin_67
#define SC_MODULE_GPIO_9 mbtk_pin_82
#define SC_MODULE_GPIO_09 SC_MODULE_GPIO_9

#define SC_MODULE_GPIO_MAX mbtk_pin_78
#define all_gpio mbtk_pin

int mbtk_pin[mbtk_pin_max_amout] = {
    mbtk_pin_1,  mbtk_pin_2,  mbtk_pin_3,  mbtk_pin_4,  mbtk_pin_5,  mbtk_pin_6,  mbtk_pin_7,  mbtk_pin_8,  
    mbtk_pin_9,  mbtk_pin_10, mbtk_pin_11, mbtk_pin_12, mbtk_pin_13, mbtk_pin_14, mbtk_pin_15, mbtk_pin_16, 
    mbtk_pin_17, mbtk_pin_18, mbtk_pin_19, mbtk_pin_20, mbtk_pin_21, mbtk_pin_22, mbtk_pin_23, mbtk_pin_24, 
    mbtk_pin_25, mbtk_pin_26, mbtk_pin_27, mbtk_pin_28, mbtk_pin_29, mbtk_pin_30, mbtk_pin_31, mbtk_pin_32,
    mbtk_pin_33, mbtk_pin_34, mbtk_pin_35, mbtk_pin_36, mbtk_pin_37, mbtk_pin_38, mbtk_pin_39, mbtk_pin_40,
    mbtk_pin_41, mbtk_pin_42, mbtk_pin_43, mbtk_pin_44, mbtk_pin_45, mbtk_pin_46, mbtk_pin_47, mbtk_pin_48,
    mbtk_pin_49, mbtk_pin_50, mbtk_pin_51, mbtk_pin_52, mbtk_pin_53, mbtk_pin_54, mbtk_pin_55, mbtk_pin_56,
    mbtk_pin_57, mbtk_pin_58, mbtk_pin_59, mbtk_pin_60, mbtk_pin_61, mbtk_pin_62, mbtk_pin_63, mbtk_pin_64,
    mbtk_pin_65, mbtk_pin_66, mbtk_pin_67, mbtk_pin_68, mbtk_pin_69, mbtk_pin_70, mbtk_pin_71, mbtk_pin_72,
    mbtk_pin_73, mbtk_pin_74, mbtk_pin_75, mbtk_pin_76, mbtk_pin_77, mbtk_pin_78, mbtk_pin_79, mbtk_pin_80,
    mbtk_pin_81, mbtk_pin_82, mbtk_pin_83, mbtk_pin_84, mbtk_pin_85, mbtk_pin_86, mbtk_pin_87, mbtk_pin_88,
    mbtk_pin_89, mbtk_pin_90, mbtk_pin_91, mbtk_pin_92, mbtk_pin_93, mbtk_pin_94, mbtk_pin_95, mbtk_pin_96,
    mbtk_pin_97, mbtk_pin_98, mbtk_pin_99, mbtk_pin_100, mbtk_pin_101, mbtk_pin_102, mbtk_pin_103, mbtk_pin_104,
    mbtk_pin_105, mbtk_pin_106, mbtk_pin_107, mbtk_pin_108, mbtk_pin_109, mbtk_pin_110, mbtk_pin_111, mbtk_pin_112,
    mbtk_pin_113, mbtk_pin_114, mbtk_pin_115, mbtk_pin_116, mbtk_pin_117, mbtk_pin_118, mbtk_pin_119, mbtk_pin_120,
    mbtk_pin_121, mbtk_pin_122, mbtk_pin_123, mbtk_pin_124, mbtk_pin_125, mbtk_pin_126, mbtk_pin_127, mbtk_pin_128,
    mbtk_pin_129,mbtk_pin_130, mbtk_pin_131,mbtk_pin_132,mbtk_pin_133,mbtk_pin_134,mbtk_pin_135,
};

extern void PrintfOptionMenu(char *options_list[], int array_size);
extern void PrintfResp(char *format);
//#define GPIO_INT_WAKEUP_TEST



enum SC_GPIO_SWITCH
{
    SC_GPIO_SET_DIRECTION = 1,
    SC_GPIO_GET_DIRECTION,
    SC_GPIO_SET_LEVEL,
    SC_GPIO_GET_LEVEL,
    SC_GPIO_SET_INTERRUPT = 5,
    SC_GPIO_WAKEUP_ENABLE,
    SC_GPIO_CONFIG,
    SC_INIT_NET_LIGHT,
    SC_GPIO_AUTO_INPUT_TEST,
    SC_GPIO_TURN_ON_TEST = 10,
    SC_GPIO_TURN_OFF_TEST,
    SC_GPIO_BACK = 99
};

/**
  * @brief  GPIO interrupt handle
  * @param  void
  * @note
  * @retval void
  */
void GPIO_IntHandler(void)
{
    PrintfResp("GPIO_IntHandler enter...\r\n");
#ifdef GPIO_INT_WAKEUP_TEST
    static unsigned int i = 0;

    if (i % 2 == 0)
        sAPI_GpioSetValue(SC_MODULE_GPIO_10, 1);
    else
        sAPI_GpioSetValue(SC_MODULE_GPIO_10, 0);

    i++;
#endif
}

/**
  * @brief  GPIO to wake up system,interrupt handle
  * @param  void
  * @note
  * @retval void
  */
void GPIO_WakeupHandler(void)
{
    PrintfResp("GPIO_WakeupHandler enter...\r\n");
#ifdef GPIO_INT_WAKEUP_TEST
    static unsigned int i = 0;

    if (i % 2 == 0)
        sAPI_GpioSetValue(SC_MODULE_GPIO_09, 1);
    else
        sAPI_GpioSetValue(SC_MODULE_GPIO_09, 0);

    i++;
#endif
    /* If you want to leave sleep after wake up, please disable system sleep ! */
    sAPI_SystemSleepSet(SC_SYSTEM_SLEEP_DISABLE);
}

/**
  * @brief  GPIO demo code.
  * @param  This demo will show how to set direction\level\read\write\interrupt on GPIOs.
  * @note
  * @retval void
  */
void GpioDemo(void)
{
    UINT32 opt = 0;
    SC_GPIOReturnCode ret;
    char *note = "\r\nPlease select an option to test from the items listed below.\r\n";
    char *options_list[] =
    {
        "1. GPIO set direction",
        "2. GPIO get direction",
        "3. GPIO set level",
        "4. GPIO get level",
        "5. GPIO set interrupt",
        "6. GPIO wakeup",
        "7. GPIO parameters config",
        "8. Init NET Light",
        "10. high level check",
        "11. low level check",
        "99. back",

    };
    unsigned int gpio_num;
    unsigned int direction;
    unsigned int gpio_level = 0;
#ifdef GPIO_INT_WAKEUP_TEST
    SC_GPIOConfiguration pinConfig;
    pinConfig.initLv = 0;
    pinConfig.isr =  NULL;
    pinConfig.pinDir = SC_GPIO_IN_PIN;
    pinConfig.pinEd = SC_GPIO_TWO_EDGE;
    pinConfig.wu = GPIO_WakeupHandler;
    pinConfig.pinPull = SC_GPIO_PULLUP_ENABLE;//pull_up

    ret = sAPI_GpioConfig(SC_MODULE_GPIO_10, pinConfig);
    if (ret == SC_GPIORC_OK)
    {
        PrintfResp("\r\nConfig GPIO successed !\r\n");
    }
    else
    {
        printf("\r\nConfig GPIO failed ret =%d!\r\n", ret);
    }

    ret = sAPI_GpioConfig(SC_MODULE_GPIO_9, pinConfig);
    if (ret == SC_GPIORC_OK)
    {
        PrintfResp("\r\nConfig GPIO successed !\r\n");
    }
    else
    {
        printf("\r\nConfig GPIO failed ret= %d!\r\n", ret);
    }
#endif

    while (1)
    {
        PrintfResp(note);
        PrintfOptionMenu(options_list, sizeof(options_list) / sizeof(options_list[0]));

        opt = UartReadValue();

        switch (opt)
        {
            case SC_GPIO_SET_DIRECTION:
            {
                PrintfResp("\r\nPlease input gpio number.\r\n");
                gpio_num = UartReadValue();

                if (gpio_num >= SC_MODULE_GPIO_MAX)
                {
                    PrintfResp("\r\nincorrect SC MODULE GPIO NUMBER.\r\n");
                    break;
                }

                PrintfResp("\r\nPlease input direction.     0:input    1:output.\r\n");
                direction = UartReadValue();

                ret = sAPI_GpioSetDirection(gpio_num, direction);
                if (ret != SC_GPIORC_OK)
                    printf("sAPI_setGpioDirection:    failed.");
                else
                    printf("sAPI_setGpioDirection:    success.");

                PrintfResp("\r\noperation successful!\r\n");

                break;
            }
            case SC_GPIO_GET_DIRECTION:
            {
                PrintfResp("\r\nPlease input gpio number.\r\n");
                gpio_num = UartReadValue();

                if (gpio_num >= SC_MODULE_GPIO_MAX)
                {
                    PrintfResp("\r\nincorrect SC MODULE GPIO NUMBER.\r\n");
                    break;
                }

                direction = sAPI_GpioGetDirection(gpio_num);

                char tmp[40];

                sprintf(tmp, "\r\nthe direction of gpio_%d is %d \r\n", gpio_num, direction);

                PrintfResp(tmp);
                PrintfResp("\r\noperation successful!\r\n");

                break;
            }
            case SC_GPIO_SET_LEVEL:
            {
                PrintfResp("\r\nPlease input gpio number.\r\n");
                gpio_num = UartReadValue();

                if (gpio_num >= SC_MODULE_GPIO_MAX)
                {
                    PrintfResp("\r\nincorrect SC MODULE GPIO NUMBER.\r\n");
                    break;
                }

                PrintfResp("\r\nPlease input gpio level.    0:low level    1:high level.\r\n");
                gpio_level = UartReadValue();

                ret = sAPI_GpioSetValue(gpio_num, gpio_level);
                if (ret != SC_GPIORC_OK)
                    printf("sAPI_GpioSetValue:    failed.");
                else
                    printf("sAPI_GpioSetValue:    success.");

                PrintfResp("\r\noperation successful!\r\n");

                break;
            }
            case SC_GPIO_GET_LEVEL:
            {
                PrintfResp("\r\nPlease input gpio number.\r\n");
                gpio_num = UartReadValue();

                if (gpio_num >= SC_MODULE_GPIO_MAX)
                {
                    PrintfResp("\r\nincorrect SC MODULE GPIO NUMBER.\r\n");
                    break;
                }

                ret = sAPI_GpioGetValue(gpio_num);

                char tmp[40];

                sprintf(tmp, "\r\nthe level of gpio_%d is %d \r\n", gpio_num, ret);

                PrintfResp(tmp);
                PrintfResp("\r\noperation successful!\r\n");

                break;
            }
            case SC_GPIO_SET_INTERRUPT:
            {
                PrintfResp("\r\nPlease input gpio number.\r\n");
                gpio_num = UartReadValue();

                if (gpio_num >= SC_MODULE_GPIO_MAX)
                {
                    PrintfResp("\r\nincorrect SC MODULE GPIO NUMBER.\r\n");
                    break;
                }
                ret = sAPI_GpioSetDirection(gpio_num, 0);
                if (ret != SC_GPIORC_OK)
                {
                    printf("sAPI_setGpioDirection:    failed.");
                    break;
                }
                ret = sAPI_GpioConfigInterrupt(gpio_num, SC_GPIO_TWO_EDGE, GPIO_IntHandler);
                if (ret != SC_GPIORC_OK)
                {
                    printf("sAPI_GpioConfigInterrupt:    failed.");
                    break;
                }

                PrintfResp("\r\noperation successful!\r\n");
                break;
            }
            case SC_GPIO_WAKEUP_ENABLE:
            {
                PrintfResp("\r\nPlease input wake up gpio number.\r\n");
                gpio_num = UartReadValue();

                if (gpio_num >= SC_MODULE_GPIO_MAX)
                {
                    PrintfResp("\r\nincorrect SC MODULE GPIO NUMBER.\r\n");
                    break;
                }

                ret = sAPI_GpioWakeupEnable(gpio_num, SC_GPIO_FALL_EDGE);
                if (ret != SC_GPIORC_OK)
                {
                    PrintfResp("\r\nGpio set wake up failed !\r\n");
                    break;
                }

                PrintfResp("\r\nGpio set wake up successful !\r\n");
                break;
            }
            case SC_GPIO_CONFIG:
            {
                PrintfResp("\r\nPlease input all parameters, delimited by comma.\r\n");
                PrintfResp("\r\nSyntax: GPIO number,direction,init level,pull type,edge type\r\n");
                PrintfResp("\r\nExample: 0,0,1,1,3\r\n");
                char input_paras[40] = {0};
                UartReadLine(input_paras, 40);

                SC_GPIOConfiguration pinconfig;
                char *p_delim;
                p_delim = strtok(input_paras, ",");
                if (p_delim)
                    gpio_num = atoi(p_delim);
                else
                {
                    PrintfResp("\r\nFomat Error.\r\n");
                    break;
                }

                p_delim = strtok(NULL, ",");
                if (p_delim)
                    pinconfig.pinDir = atoi(p_delim);
                else
                {
                    PrintfResp("\r\nFomat Error.\r\n");
                    break;
                }

                p_delim = strtok(NULL, ",");
                if (p_delim)
                    pinconfig.initLv = atoi(p_delim);
                else
                {
                    PrintfResp("\r\nFomat Error.\r\n");
                    break;
                }

                p_delim = strtok(NULL, ",");
                if (p_delim)
                    pinconfig.pinPull = atoi(p_delim);
                else
                {
                    PrintfResp("\r\nFomat Error.\r\n");
                    break;
                }

                p_delim = strtok(NULL, ",");
                if (p_delim)
                    pinconfig.pinEd = atoi(p_delim);
                else
                {
                    PrintfResp("\r\nFomat Error.\r\n");
                    break;
                }

                if (pinconfig.pinEd == SC_GPIO_RISE_EDGE || pinconfig.pinEd == SC_GPIO_FALL_EDGE || pinconfig.pinEd == SC_GPIO_TWO_EDGE)
                    pinconfig.isr = GPIO_IntHandler;
                else
                    pinconfig.isr = NULL;

                pinconfig.wu = GPIO_WakeupHandler;

                ret = sAPI_GpioConfig(gpio_num, pinconfig);
                if (ret == SC_GPIORC_OK)
                    PrintfResp("\r\nConfig OK!\r\n");
                else
                {
                    char tmp[40];
                    sprintf(tmp, "\r\nConfig Error, Error code is %d\r\n", ret);
                    PrintfResp(tmp);
                }
                break;
            }
            case SC_GPIO_TURN_ON_TEST:
            {
                SC_GPIOConfiguration gpio_cfg =
                {
                    .initLv = 1,
                    .isr = NULL,
                    .pinDir = 1,
                    .pinEd = 0,
                    .wu = NULL,
                    .pinPull = 0,
                };
                int *p = all_gpio;
                do
                {
                    ret = sAPI_GpioConfig(*p, gpio_cfg);
                    if (ret)
                        printf("gpio [%d] cfg fail", *p);

                    if (sAPI_GpioGetValue(*p) != 1)
                        printf("gpio [%d] is not high level", *p);
                } while (*p ++ != SC_MODULE_GPIO_MAX);
                break;
            }
            case SC_GPIO_TURN_OFF_TEST:
            {
                SC_GPIOConfiguration gpio_cfg =
                {
                    .initLv = 0,
                    .isr = NULL,
                    .pinDir = 1,
                    .pinEd = 0,
                    .wu = NULL,
                    .pinPull = 0,
                };
                int *p = all_gpio;
                do
                {
                    ret = sAPI_GpioConfig(*p, gpio_cfg);
                    if (ret)
                        printf("gpio [%d] cfg fail", *p);

                    if (sAPI_GpioGetValue(*p) != 0)
                        printf("gpio [%d] is not low level", *p);
                } while (*p ++ != SC_MODULE_GPIO_MAX);
                break;
            }
            case SC_GPIO_BACK:
                return;
        }
    }
}
