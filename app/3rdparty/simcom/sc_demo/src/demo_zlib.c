/*
 * @Author: Louis_Qiu
 * @Date: 2022-12-27 11:10:57
 * @Last Modified by: Louis_Qiu
 * @Last Modified time: 2022-12-28 09:42:00
 */

#include "string.h"
#include "stdlib.h"
#include "stdio.h"

#include "unzip.h"
#include "simcom_common.h"
#include "simcom_debug.h"
#include "uart_api.h"


extern void PrintfOptionMenu(char *options_list[], int array_size);
extern void PrintfResp(char *format);
extern void PrintfRespData(char *buff, UINT32 length);
extern void PrintfRespHexData(char *buff, UINT32 length);

extern int do_extract(unzFile uf, int opt_extract_without_path, int opt_overwrite, const char *password);
extern unzFile do_open(char *path);
extern int do_close(unzFile uf);


typedef enum
{
    SC_ZLIB_UNZIP                 = 1,
    SC_ZLIB_EXIT                  = 99
} SC_ZLIB_DEMO_TYPE;


void ZLIBDemo(void)
{
    UINT32 opt = 0;

    char *note = "\r\nPlease select an option to test from the items listed below.\r\n";
    char *options_list[] =
    {
        "1. unzip",
        "99. back"
    };

    while (1)
    {
        PrintfResp(note);
        PrintfOptionMenu(options_list, sizeof(options_list) / sizeof(options_list[0]));

        opt = UartReadValue();

        switch (opt)
        {
            case SC_ZLIB_UNZIP:
            {
                char path[512] = {0};
                PrintfResp("\r\nPlease input zip path.\r\n");
                UartReadLine(path, sizeof(path));
                sAPI_Debug("zlib unzip: path is %s ", path);

                unzFile uf = NULL;
                int err;

                uf = do_open(path);
                if (uf != NULL)
                {
                    err = do_extract(uf, 0, 0, NULL);
                    sAPI_Debug("ret_value[%d]", err);
                    do_close(uf);
                }
                else
                {
                    sAPI_Debug("unzip open fail!!\r\n");
                }
            }
            break;

            case SC_ZLIB_EXIT:
            {
                return;
            }
            break;

            default:
                break;
        }
    }
}
