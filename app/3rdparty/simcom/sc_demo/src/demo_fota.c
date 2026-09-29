/**
  ******************************************************************************
  * @file    demo_fota.c
  * @author  SIMCom OpenSDK Team
  * @brief   Source file of fota function,  this is used to update core FW.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 SIMCom Wireless.
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "simcom_fota_download.h"
#include "simcom_uart.h"
#include "simcom_common.h"
#include "simcom_file_system.h"
#include "uart_api.h"
#include "simcom_debug.h"


#define LOG_ERR()         do{printf("%s error, line: %d\r\n", __func__, __LINE__);}while (0)


extern void ui_print(const char *format, ...);
extern void PrintfOptionMenu(char *options_list[], int array_size);
extern void PrintfResp(char *format);


enum SC_FOTA_SWITCH
{
    SC_FTP_FOTA = 1,

    SC_HTTP_FOTA,

#ifndef CRANEL_OTA
    SC_LOCAL_FOTA,
#endif
    SC_FOTA_BACK = 99
};

/**
  * @brief  Fota operation callback to indicated the downloading finishing percentage.
  * @param  void
  * @note   isok will be used to indicate the download result.
  * @retval void
  */
int fotacb(int isok)
{
    SC_MiniSysStatus MiniSysStatus = {0, 0};
    sAPI_GetMiniSysStatus(&MiniSysStatus);
    if (isok == 100)
    {
        if (MiniSysStatus.stage == 1) //first stage
        {
            PrintfResp("fist download is successful.\r\n");
        }
        else if (MiniSysStatus.stage == 2) //second stage
        {
            PrintfResp("second download is successful.\r\n");
        }
        else
        {
            PrintfResp("pre download is successful.\r\n");
        }
    }
    else
    {
        if (MiniSysStatus.stage == 1) //first stage
        {
            PrintfResp("fist download is fail.\r\n");
        }
        else if (MiniSysStatus.stage == 2) //second stage
        {
            PrintfResp("second download is fail.\r\n");
        }
        else
        {
            PrintfResp("pre download is fail.\r\n");
        }
    }
    return 0;
}

/**
  * @brief  Fota demo
  * @param  void
  * @note   suppor HTTP and FTP\local update. For local update need sAPI_FsSwitchDir to change director
  * @retval void
  */
void FotaDemo(void)
{
    UINT32 opt = 0;
    char *note = "\r\nPlease select an option to test from the items listed below.\r\n";
    #ifndef CRANEL_OTA
    char *options_list[] =
    {
        "1. FTP fota",

        "2. HTTP fota",

        "3. LOCAL fota",

        "8. Check Current mini sys Status",
        "99. back",
    };
    #else
        char *options_list[] =
    {
        "1. FTP fota",

        "2. HTTP fota",

        "8. Check Current mini sys Status",
        "99. back",
    };
    #endif

    while (1)
    {
        PrintfResp(note);
        PrintfOptionMenu(options_list, sizeof(options_list) / sizeof(options_list[0]));

        opt = UartReadValue();

        switch (opt)
        {

            case SC_FTP_FOTA:
            {
                struct SC_FotaApiParam param = {0};

                
                ui_print("\r\nPlease input ftp host\r\n");
                UartReadLine(param.host, 512);
                ui_print("\r\nPlease input ftp username\r\n");
                UartReadLine(param.username, 512);
                ui_print("\r\nPlease input ftp password\r\n");
                UartReadLine(param.password, 512);
                param.mode = 0;//ftp
                param.sc_fota_cb = NULL;

                sAPI_FotaServiceBegin((void *)&param);
                break;
            }

            case SC_HTTP_FOTA:
            {
                struct SC_FotaApiParam param = {0};
                ui_print("\r\nPlease input http host\r\n");
                UartReadLine(param.host, 512);
                ui_print("\r\nPlease input http username\r\n");
                UartReadLine(param.username, 512);
                ui_print("\r\nPlease input http password\r\n");
                UartReadLine(param.password, 512);
                param.mode = 1;//http
                param.sc_fota_cb = NULL;

                sAPI_FotaServiceBegin((void *)&param);
                break;
            }

#if 0 //ndef CRANEL_OTA
            case SC_LOCAL_FOTA:
            {
                int ret = -1;
                FILE *fp = NULL;
                size_t read_len = 0;
                int filesize = 0;

                void *read_data = (void *)malloc(1024);
                if (!read_data)
                {
                    LOG_ERR();
                    goto error;
                }

                ret = sAPI_FsSwitchDir("sys_patch.bin", DIR_C_TO_SIMDIR);
                if (ret)
                {
                    LOG_ERR();
                    goto error;
                }

                fp = fopen("c:/sys_patch.bin", "rb");
                if (fp == NULL)
                {
                    LOG_ERR();
                    goto error;
                }
                filesize = sAPI_fsize((SCFILE *)fp);
                printf("file size : [%d]", filesize);

                while (1)
                {
                    memset(read_data, 0, 1024);
                    read_len = fread(read_data, 1024, 1, fp);
                    if (read_len == 0)
                        break;
                    if (sAPI_FotaImageWrite(read_data, read_len, filesize) != 0)
                    {
                        LOG_ERR();
                        goto error;
                    }
                }

                if (sAPI_FotaImageVerify(filesize) != 0)
                {
                    LOG_ERR();
                    goto error;
                }
                printf("first fota image write suc, verify suc");
error:
                if (fp)
                    fclose(fp);
                if (read_data)
                    free(read_data);

                break;
            }
#endif

            case 8:
            {
                char tmp[60];
                SC_MiniSysStatus MiniSysStatus = {0, 0};
                sAPI_GetMiniSysStatus(&MiniSysStatus);
                sprintf(tmp, "\r\nCurrent minisys enable.enable %d stage %d\r\n", MiniSysStatus.enable, MiniSysStatus.stage);

                PrintfResp(tmp);
                break;
            }

            case SC_FOTA_BACK:
                return;
        }
    }
}
