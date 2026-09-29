#include "../common.h"
#include "memoryHandle.h"
#include "lampStatusFinder.h"
#include "mbtk_comm_api.h"
#include "ol_flash_fs.h"
#include <string.h>

#define CONFIG_STORE_FILE          "C:/configStore.bin"
#define CONFIG_STORE_BACKUP_FILE   "C:/configStoreBak.bin"
#define CONFIG_STORE_FIRST_BOOT_MAGIC  0x55

configStore_t configStore;

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

static int memoryHandle_readFile(char *fileName, configStore_t *configStore)
{
    int handle;
    int ret = -1;
    uint8_t crcTemp;

    memset(configStore, 0, sizeof(configStore_t));

    handle = ol_ffs_open(fileName, "rb");
    if (handle >= 0) {
        ret = ol_ffs_read(handle, (char *)configStore, sizeof(configStore_t));
        ol_ffs_close(handle);
    }

    if (ret != sizeof(configStore_t)) {
        op_uart_printf("-1-memoryHandle:configStore memoryHandle_readFile %s read file failed\r\n", fileName);
        return 1;
    }

    crcTemp = configStore->checksum;
    configStore->checksum = 0;
    configStore->checksum = crc8_cal((uint8_t *)configStore, sizeof(configStore_t));

    op_uart_printf("-1-memoryHandle:configStore memoryHandle_readFile %s storedCrc=%d calcCrc=%d\r\n",
                   fileName, crcTemp, configStore->checksum);

    if (crcTemp != configStore->checksum) {
        op_uart_printf("-1-memoryHandle:configStore memoryHandle_readFile %s crc fail\r\n", fileName);
        return 1;
    }

    return 0;
}

static int memoryHandle_writeFile(char *fileName, configStore_t *configStore)
{
    int handle;
    int ret;

    configStore->checksum = 0;
    configStore->checksum = crc8_cal((uint8_t *)configStore, sizeof(configStore_t));

    handle = ol_ffs_open(fileName, "wb");
    if (handle < 0) {
        op_uart_printf("-1-memoryHandle:open %s for write failed, errno=%d\r\n", fileName, handle);
        return -1;
    }

    ret = ol_ffs_write(handle, (char *)configStore, sizeof(configStore_t));
    ol_ffs_close(handle);

    if (ret != sizeof(configStore_t)) {
        op_uart_printf("-1-memoryHandle:write %s failed, ret=%d\r\n", fileName, ret);
        return -1;
    }

    return 0;
}

static int memoryHandle_readConfigStoreFile(void)
{
    return memoryHandle_readFile(CONFIG_STORE_FILE, &configStore);
}

static int memoryHandle_writeConfigStoreFile(void)
{
    return memoryHandle_writeFile(CONFIG_STORE_FILE, &configStore);
}

static int memoryHandle_readConfigStoreBackupFile(void)
{
    return memoryHandle_readFile(CONFIG_STORE_BACKUP_FILE, &configStore);
}

static int memoryHandle_writeConfigStoreBackupFile(void)
{
    return memoryHandle_writeFile(CONFIG_STORE_BACKUP_FILE, &configStore);
}

static void memoryHandle_loadDefaultConfigStore(void)
{
    configStore.Minvoltage      = MIN_VOLT;
    configStore.Minpower        = MIN_POWER;
    configStore.periodicTime    = PERIODIC_DURATION;
    configStore.firstBoot       = CONFIG_STORE_FIRST_BOOT_MAGIC;
    configStore.lastFaultStatus = FAULT_NONE;

    memoryHandle_writeConfigStoreWithBackup();
    op_uart_printf("-1-memoryHandle:configStore loadDefaultConfigStore\r\n");
}

void memoryHandle_writeConfigStoreWithBackup(void)
{
    memoryHandle_writeConfigStoreBackupFile();
    memoryHandle_writeConfigStoreFile();
}

void memoryHandle_readConfigStoreWithBackup(void)
{
    if (memoryHandle_readConfigStoreFile()) {
        op_uart_printf("-1-memoryHandle:configStore memoryHandle_readConfigStoreFile crc fail\r\n");
        if (memoryHandle_readConfigStoreBackupFile()) {
            op_uart_printf("-1-memoryHandle:configStore memoryHandle_readConfigStoreBackupFile crc fail\r\n");
            memoryHandle_loadDefaultConfigStore();
        }
    }
}

void memoryHandle_firstBoot(void)
{
    memoryHandle_readConfigStoreWithBackup();
}

configStore_t *memoryHandle_getConfigStore(void)
{
    return &configStore;
}
