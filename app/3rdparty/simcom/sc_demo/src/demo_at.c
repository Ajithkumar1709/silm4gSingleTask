#include <stdio.h>
#include <string.h>
#include "simcom_at.h"
#include "simcom_debug.h"
#include "uart_api.h"

extern void ui_print(const char *format, ...);

void AtDemo(void)
{
    int ret = 0;
    char command[100];
    char send_command[100 + 2];
    ui_print("\r\nPlease input at command\r\n");
    UartReadLine(command, 100);
    sprintf(send_command, "%s\r\n", command);
    sAPI_AtSend(send_command, strlen(send_command));
    if (ret != 0)
    {
        ui_print("send %s fail", send_command);
    }
}

