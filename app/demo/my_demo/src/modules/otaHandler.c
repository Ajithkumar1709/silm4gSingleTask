#include "otaHandler.h"
#include "ol_fota.h"
#include "mbtk_pmu.h"
#include "mbtk_comm_api.h"
#include "mbtk_os.h"
#include "../common.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// #define OTA_FTP_HOST      "seepl18.net.in"
// #define OTA_FTP_PORT      "21"
// #define OTA_FTP_USER      "fesppp.b"
// #define OTA_FTP_PASS      "spPpes.d"
// #define OTA_FTP_DIR       "/ilm4g"
#define OTA_HTTP_BASE_URL "http://136.119.181.84:80"
#define OTA_FILE_NAME_MAX 64

#define OTA_WATCHDOG_TIMEOUT_SEC 600 /* 10 minutes: HTTP FOTA download + verify */

static mbtk_taskref otaTaskRef = NULL;
static mbtk_taskref otaWatchdogTaskRef = NULL;
static volatile unsigned char otaInProgress = 0;
static char otaFileName[OTA_FILE_NAME_MAX] = {0};

static void otaHandler_publishStatus(int status, int result, int progress)
{
    mqttQueue_t mqttQueue = {0};
    int len;

    len = snprintf((char *)mqttQueue.data, sizeof(mqttQueue.data),
                    "{\"ota_status\":%d,\"ota_result\":%d,\"ota_progress\":%d}",
                    status, result, progress);
    if (len <= 0)
    {
        return;
    }

    mqttQueue.dataSize = (unsigned int)len;
    mqttQueue.topic = 2;
    if (mqttProcessQueue != NULL)
    {
        ol_os_msgq_send(mqttProcessQueue, sizeof(mqttQueue), &mqttQueue, MBTK_OS_NO_SUSPEND);
    }
}

static void otaHandler_callback(void *param)
{
    mbtk_fota_status_result_t *status_res = param;
    int progress = ol_fota_get_proccess();

    op_uart_printf("-1-otaHandler:callback status=%d res=%d progress=%d\r\n",
                   status_res->status, status_res->res, progress);

    otaHandler_publishStatus(status_res->status, status_res->res, progress);

    if (status_res->status == MBTK_FOTA_SUCCEED ||
        status_res->status == MBTK_FOTA_FAIL)
    {
        otaInProgress = 0;
    }

   /* if (status_res->status == MBTK_FOTA_SETFLAG)
    {
       
        ol_os_task_sleep(400); // 400 ticks * 5ms = ~2s
        ol_power_reset();
    }*/
}

static void otaHandler_watchdogTask(void *arg)
{
    int elapsed;

    (void)arg;

    op_uart_printf("-1-otaHandler:watchdog started, timeout=%ds\r\n", OTA_WATCHDOG_TIMEOUT_SEC);

    for (elapsed = 0; elapsed < OTA_WATCHDOG_TIMEOUT_SEC; elapsed++)
    {
        ol_os_task_sleep(200); /* 200 ticks * 5ms = 1s */
        if (!otaInProgress)
        {
            break;
        }
    }

    if (otaInProgress)
    {
        op_uart_printf("-1-otaHandler:watchdog timeout, forcing OTA state reset\r\n");
        otaHandler_publishStatus(MBTK_FOTA_FAIL, -2, 0); /* -2 = watchdog timeout */
        otaInProgress = 0;
    }

    ol_os_task_delete(otaWatchdogTaskRef);
    otaWatchdogTaskRef = NULL;
}

static void otaHandler_task(void *arg)
{
    mbtk_fota_server_info server_info = {0};
    int ret;

    (void)arg;

    op_uart_printf("-1-otaHandler:task entered\r\n");

    // server_info.mode = 0; /* ftp */
    // snprintf(server_info.host, sizeof(server_info.host), "%s:%s%s/%s",
    //          OTA_FTP_HOST, OTA_FTP_PORT, OTA_FTP_DIR, otaFileName);
    // snprintf(server_info.username, sizeof(server_info.username), "%s", OTA_FTP_USER);
    // snprintf(server_info.password, sizeof(server_info.password), "%s", OTA_FTP_PASS);
    //
    // op_uart_printf("-1-otaHandler:starting FTP OTA from %s\r\n", server_info.host);
    // ret = ol_fota_firmware_download(&server_info, false, otaHandler_callback);

    server_info.mode = 1; /* http */
    snprintf(server_info.host, sizeof(server_info.host), "%s/%s",
             OTA_HTTP_BASE_URL, otaFileName);

    /* mini FOTA is a stub in the current kernel (always returns -1), use differential FOTA instead */
    // op_uart_printf("-1-otaHandler:starting HTTP mini FOTA from %s\r\n", server_info.host);
    // ret = ol_mini_fota_firmware_download(&server_info, otaHandler_callback);

    op_uart_printf("-1-otaHandler:starting HTTP differential FOTA from %s\r\n", server_info.host);
    ret = ol_fota_firmware_download(&server_info, true, otaHandler_callback); /* auto reboot, same as tested fota_demo */
    if (ret != 0)
    {
        op_uart_printf("-1-otaHandler:ol_fota_firmware_download failed, ret=%d\r\n", ret);
        otaHandler_publishStatus(MBTK_FOTA_FAIL, ret, 0);
        otaInProgress = 0;
    }

    ol_os_task_delete(otaTaskRef);
    otaTaskRef = NULL;
}

void otaHandler_checkUpgradeResult(void)
{
    int upgrade_result = ol_fota_get_upgrade_result();

    op_uart_printf("-1-otaHandler:boot upgrade_result=%d (0=NONE,1=FAIL,2=SUCCESS)\r\n",
                   upgrade_result);

    if (upgrade_result == FOTA_UPGRED_FAIL || upgrade_result == FOTA_UPGRED_SUCCESS)
    {
        mqttQueue_t mqttQueue = {0};
        int len;

        len = snprintf((char *)mqttQueue.data, sizeof(mqttQueue.data),
                        "{\"ota_boot_result\":%d}", upgrade_result);
        if (len > 0 && mqttProcessQueue != NULL)
        {
            mqttQueue.dataSize = (unsigned int)len;
            mqttQueue.topic = 2;
            ol_os_msgq_send(mqttProcessQueue, sizeof(mqttQueue), &mqttQueue, MBTK_OS_NO_SUSPEND);
        }
    }
}

void otaHandler_start(const char *fileName)
{
    if (otaInProgress)
    {
        op_uart_printf("-1-otaHandler:OTA already in progress, ignoring request\r\n");
        return;
    }

    if (fileName == NULL || fileName[0] == '\0')
    {
        op_uart_printf("-1-otaHandler:no OTA file name given, ignoring request\r\n");
        return;
    }

    snprintf(otaFileName, sizeof(otaFileName), "%s", fileName);

    otaInProgress = 1;
    if (ol_os_task_creat(&otaTaskRef, NULL, 8192, 220, "ota_task", otaHandler_task, NULL) != mbtk_os_success)
    {
        op_uart_printf("-1-otaHandler:failed to create OTA task\r\n");
        otaInProgress = 0;
        return;
    }
    op_uart_printf("-1-otaHandler:OTA task created\r\n");

    if (ol_os_task_creat(&otaWatchdogTaskRef, NULL, 2048, 220, "ota_watchdog", otaHandler_watchdogTask, NULL) != mbtk_os_success)
    {
        op_uart_printf("-1-otaHandler:failed to create OTA watchdog task\r\n");
        otaWatchdogTaskRef = NULL;
    }
}
