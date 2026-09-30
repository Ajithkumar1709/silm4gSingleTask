#include "../common.h"
#include "memoryHandle.h"
#include "lampStatusFinder.h"
#include "mbtk_comm_api.h"
#include "ol_flash_fs.h"
#include "ntp_api.h"
#include <string.h>

#define CONFIG_STORE_FILE          "C:/storedDatas.bin"
#define CONFIG_STORE_BACKUP_FILE   "C:/configStoreBak.bin"
#define CONFIG_STORE_FIRST_BOOT_MAGIC  0x55

storedDatas_t storedDatas;

static uint8_t crc8_cal(uint8_t *data, uint16_t length)
{
    uint8_t crc = 0x00;

    uint8_t extract;
    uint8_t sum;

    for (uint16_t i = 0; i < length; i++) {
        extract = *data;
        for (uint8_t tempI = 8; tempI; tempI--) {
            sum = (crc ^ extract) & 0x01;
            crc >>= 1;
            if (sum)
                crc ^= 0x8C;
            extract >>= 1;
        }
        data++;
    }

    return crc;
}

static int memoryHandle_readFile(char *fileName, storedDatas_t *storedDatas)
{
    int handle;
    int ret = -1;
    uint8_t crcTemp;

    memset(storedDatas, 0, sizeof(storedDatas_t));

    handle = ol_ffs_open(fileName, "rb");
    if (handle >= 0) {
        ret = ol_ffs_read(handle, (char *)storedDatas, sizeof(storedDatas_t));
        ol_ffs_close(handle);
    }

    if (ret != sizeof(storedDatas_t)) {
        op_uart_printf("-1-memoryHandle:storedDatas memoryHandle_readFile %s read file failed\r\n", fileName);
        return 1;
    }

    crcTemp = storedDatas->checksum;
    storedDatas->checksum = 0;
    storedDatas->checksum = crc8_cal((uint8_t *)storedDatas, sizeof(storedDatas_t));

    op_uart_printf("-1-memoryHandle:storedDatas memoryHandle_readFile %s storedCrc=%d calcCrc=%d\r\n",
                   fileName, crcTemp, storedDatas->checksum);

    if (crcTemp != storedDatas->checksum) {
        op_uart_printf("-1-memoryHandle:storedDatas memoryHandle_readFile %s crc fail\r\n", fileName);
        return 1;
    }

    return 0;
}

static int memoryHandle_writeFile(char *fileName, storedDatas_t *storedDatas)
{
    int handle;
    int ret;

    storedDatas->checksum = 0;
    storedDatas->checksum = crc8_cal((uint8_t *)storedDatas, sizeof(storedDatas_t));

    handle = ol_ffs_open(fileName, "wb");
    if (handle < 0) {
        op_uart_printf("-1-memoryHandle:open %s for write failed, errno=%d\r\n", fileName, handle);
        return -1;
    }

    ret = ol_ffs_write(handle, (char *)storedDatas, sizeof(storedDatas_t));
    ol_ffs_close(handle);

    if (ret != sizeof(storedDatas_t)) {
        op_uart_printf("-1-memoryHandle:write %s failed, ret=%d\r\n", fileName, ret);
        return -1;
    }

    return 0;
}

static int memoryHandle_readConfigStoreFile(void)
{
    return memoryHandle_readFile(CONFIG_STORE_FILE, &storedDatas);
}

static int memoryHandle_writeConfigStoreFile(void)
{
    return memoryHandle_writeFile(CONFIG_STORE_FILE, &storedDatas);
}

static int memoryHandle_readConfigStoreBackupFile(void)
{
    return memoryHandle_readFile(CONFIG_STORE_BACKUP_FILE, &storedDatas);
}

static int memoryHandle_writeConfigStoreBackupFile(void)
{
    return memoryHandle_writeFile(CONFIG_STORE_BACKUP_FILE, &storedDatas);
}

static void memoryHandle_loadDefaultConfigStore(void)
{
    storedDatas.Minvoltage      = MIN_VOLT;
    storedDatas.Minpower        = MIN_POWER;
    storedDatas.periodicTime    = PERIODIC_DURATION;
    storedDatas.maxPayload      = MAX_PAYLOAD_PER_DAY;
    storedDatas.firstBoot      = CONFIG_STORE_FIRST_BOOT_MAGIC;
    storedDatas.lastFaultStatus = FAULT_NONE;

    memoryHandle_writeConfigStoreWithBackup();
    op_uart_printf("-1-memoryHandle:storedDatas loadDefaultConfigStore\r\n");
}

void memoryHandle_writeConfigStoreWithBackup(void)
{
    memoryHandle_writeConfigStoreBackupFile();
    memoryHandle_writeConfigStoreFile();
}

void memoryHandle_readConfigStoreWithBackup(void)
{
    if (memoryHandle_readConfigStoreFile()) {
        op_uart_printf("-1-memoryHandle:storedDatas memoryHandle_readConfigStoreFile crc fail\r\n");
        if (memoryHandle_readConfigStoreBackupFile()) {
            op_uart_printf("-1-memoryHandle:storedDatas memoryHandle_readConfigStoreBackupFile crc fail\r\n");
            memoryHandle_loadDefaultConfigStore();
        }
    }
}

void memoryHandle_firstBoot(void)
{
    memoryHandle_readConfigStoreWithBackup();
}

storedDatas_t *memoryHandle_getConfigStore(void)
{
    return &storedDatas;
}

//================================daily max payload counter===============================
#define IST_OFFSET_SEC   19800u   /* UTC + 5:30 */
#define SECONDS_PER_DAY  86400u

/* Resets storedDatas.maxPayloadCounter when the IST day changes. Returns 0 if
 * NTP time isn't available (then nothing is blocked or counted, same as the
 * old project's RTC_SET check). */
static U1 maxPayLoadDayCheck(void)
{
    U4 today;

    if (ol_ntp_get_status() != 1) {
        return 0;
    }
    today = ((U4)ol_ntp_get_utc_time() + IST_OFFSET_SEC) / SECONDS_PER_DAY;
    if (today != storedDatas.currentDay) {
        op_uart_printf("-1-memoryHandle:Payload Counter Reset, day %lu -> %lu\r\n",
                       (unsigned long)storedDatas.currentDay, (unsigned long)today);
        storedDatas.currentDay = today;
        storedDatas.maxPayloadCounter = 0;
        memoryHandle_writeConfigStoreWithBackup();
    }
    return 1;
}

U1 maxPayLoadChecker(void)
{
    if (!maxPayLoadDayCheck()) {
        return 1;
    }
    op_uart_printf("-1-memoryHandle:maxPayload=%lu maxPayloadCounter=%lu\r\n",
                   (unsigned long)storedDatas.maxPayload, (unsigned long)storedDatas.maxPayloadCounter);
    if ((storedDatas.maxPayload != 0) && (storedDatas.maxPayloadCounter >= storedDatas.maxPayload)) {
        return 0;
    }
    return 1;
}

void maxPayLoadCount(void)
{
    if (!maxPayLoadDayCheck()) {
        return;
    }
    storedDatas.maxPayloadCounter++;
    memoryHandle_writeConfigStoreWithBackup();
}