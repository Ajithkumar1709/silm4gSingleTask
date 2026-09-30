#include "dataStore.h"
#include "mbtk_comm_api.h"
#include "ol_flash_fs.h"
#include "memoryHandle.h"
#include <string.h>

static char dataLogFile[] = "C:/dataLogds.txt";

static mbtk_mutexref dataFileMutex = NULL;
static U2 currentFileIndex = 0;
static U4 dataStoreCount = 0;

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

/* Slot-indexed read/write on the circular log: slot N lives at
 * N * sizeof(fsDataBackUp_t), so any slot can be rewritten in place without
 * disturbing the others. */
static U1 fileWrite(int fd, U2 index, fsDataBackUp_t *fileData)
{
    int written;

    if (ol_ffs_seek(fd, (index * (sizeof(fsDataBackUp_t))), OL_FS_SEEK_SET) != 0) {
        op_uart_printf("-1-dataStore:seek failed, index=%d\r\n", index);
        return 0;
    }
    written = ol_ffs_write(fd, (char *)fileData, sizeof(fsDataBackUp_t));
    if (written < 0) {
        op_uart_printf("-1-dataStore:write file failed %d\r\n", index);
        return 0;
    }
    /* Without this, a write can succeed and even read back correctly while
     * the device stays powered, but still be sitting in a write-back cache
     * that hasn't reached physical flash yet -- a power cut before the next
     * flush loses it, reverting the file to whatever was last synced. */
    ol_ffs_sync(fd);
    return 1;
}

static U1 fileRead(int fd, U2 index, fsDataBackUp_t *fileData)
{
    int readResult;

    ol_ffs_seek(fd, (index * sizeof(fsDataBackUp_t)), OL_FS_SEEK_SET);
    readResult = ol_ffs_read(fd, (char *)fileData, sizeof(fsDataBackUp_t));

    if (readResult < 0) {
        op_uart_printf("-1-dataStore:read failed %d\r\n", index);
        return 0;
    }
    return 1;
}

/* Scans the circular log from slot 0 and returns the first slot marked
 * D_FILE_INDEXNOTUSED (the write pointer left there by the previous boot),
 * so writing resumes there instead of clobbering already-logged entries.
 * If every slot up to D_MAX_FILEINDEX is used, the log is full; wrap back to
 * slot 0 (oldest entry overwritten) rather than returning the out-of-range
 * D_MAX_FILEINDEX itself. */
static U2 fileReadDu(fsDataBackUp_t *fileData)
{
    U1 readState;
    U2 fileIndex;
    int dataFile;

    dataFile = ol_ffs_open(dataLogFile, "ab+");
    ol_ffs_close(dataFile);
    dataFile = ol_ffs_open(dataLogFile, "rb+");
    op_uart_printf("-1-dataStore:fileReadDu initial FilePosition=%d\r\n", ol_ffs_ftell(dataFile));
    for (fileIndex = 0; fileIndex < D_MAX_FILEINDEX; fileIndex++) {
        memset(fileData->data, 0, sizeof(fileData->data));
        readState = fileRead(dataFile, fileIndex, fileData);
        op_uart_printf("-1-dataStore:fileReadDu FilePosition=%d In=%d\r\n", ol_ffs_ftell(dataFile), fileIndex);
        if (!readState) {
            op_uart_printf("-1-dataStore:fileReadDu read failed at index=%d, stopping scan\r\n", fileIndex);
            break;
        }
        if (fileData->state != D_FILE_INDEXUSED) {
            op_uart_printf("-1-dataStore:fileReadDu found NOTUSED slot at index=%d, state=%d\r\n", fileIndex, fileData->state);
            ol_ffs_close(dataFile);
            return fileIndex;
        }
    }
    ol_ffs_close(dataFile);
    return (fileIndex >= D_MAX_FILEINDEX) ? 0 : fileIndex;
}

void dataStore_init(void)
{
    static fsDataBackUp_t fileData; /* too large for my_task's stack */

    op_uart_printf("-1-dataStore:C: total=%lu free=%lu\r\n",
                   (unsigned long)ol_ffs_gettotalspace("C:"), (unsigned long)ol_ffs_getfreespace("C:"));
    op_uart_printf("-1-dataStore:U: total=%lu free=%lu\r\n",
                   (unsigned long)ol_ffs_gettotalspace("U:"), (unsigned long)ol_ffs_getfreespace("U:"));

    ol_os_mutex_creat(&dataFileMutex, MBTK_OS_FIFO);

    currentFileIndex = fileReadDu(&fileData);
    op_uart_printf("-1-dataStore:init currentFileIndex=%d\r\n", currentFileIndex);
}

/* "ab+" only reliably lands its write at the byte offset requested when that
 * offset is already the file's true end -- it does not honor an earlier
 * seek() and instead silently appends at true EOF otherwise (confirmed on
 * hardware: this misdirected every other index's write in fsDataWrite() once
 * the log had grown past its first two slots). Pick the open mode per write
 * based on whether the target slot already exists on flash: "ab+" only for
 * genuinely growing the file, "rb+" for overwriting an existing slot. */
static U1 fsDataWriteOne(U2 index, fsDataBackUp_t *fileData)
{
    long targetOffset = (long)index * (long)sizeof(fsDataBackUp_t);
    int fileSize = ol_ffs_getsize(dataLogFile);
    const char *mode = (fileSize > 0 && targetOffset < fileSize) ? "rb+" : "ab+";
    int dataFile;
    U1 status;

    dataFile = ol_ffs_open(dataLogFile, mode);
    if (dataFile < 0) {
        op_uart_printf("-1-dataStore:fsDataWriteOne open file failed, index=%d mode=%s\r\n", index, mode);
        return 0;
    }
    status = fileWrite(dataFile, index, fileData);
    op_uart_printf("-1-dataStore:fsDataWriteOne index=%d mode=%s fileSize=%d status=%d\r\n",
                   index, mode, fileSize, status);
    ol_ffs_close(dataFile);
    return status;
}

static U1 fsDataWrite(U1 *data, U2 dataLength, U2 *currentIndex, U4 ts)
{
    static fsDataBackUp_t fileData;  /* too large for my_task's stack */
    static fsDataBackUp_t sentinel;  /* too large for my_task's stack */
    U1 status;

    memset(fileData.data, 0, sizeof(fileData.data));
    memcpy(fileData.data, data, dataLength);
    fileData.dataLength = dataLength;
    fileData.state = D_FILE_INDEXUSED;
    fileData.uploadStatus = D_NOTUPLOADED;
    fileData.ts = ts;
    fileData.crc = 0;
    fileData.crc = crc8_cal((uint8_t *)&fileData, sizeof(fileData));

    op_uart_printf("-1-dataStore:fsDataWrite startIndex=%d\r\n", *currentIndex);
    if (fsDataWriteOne(*currentIndex, &fileData)) {
        *currentIndex = (*currentIndex >= D_MAX_FILEINDEX) ? 0 : (*currentIndex + 1);
        op_uart_printf("-1-dataStore:fsDataWrite endIndex=%d\r\n", *currentIndex);

        /* Genuinely blank "next slot is empty" marker -- not a leftover
         * duplicate of the just-written record, so its own crc is
         * self-consistent instead of a stale mismatch. */
        memset(&sentinel, 0, sizeof(sentinel));
        sentinel.state = D_FILE_INDEXNOTUSED;
        status = fsDataWriteOne(*currentIndex, &sentinel);
        return status;
    }
    return 0;
}

static U1 fsDataRead(fsDataBackUp_t *fileData, U2 index)
{
    int dataFile;
    U1 status;

    dataFile = ol_ffs_open(dataLogFile, "rb");
    status = fileRead(dataFile, index, fileData);
    ol_ffs_close(dataFile);
    return status;
}

void dataStore_dumpAll(void)
{
    static fsDataBackUp_t fileData; /* too large for my_task's stack */
    U1 status;
    U2 i;

    for (i = 0; i < D_MAX_FILEINDEX; i++) {
        memset(&fileData, 0, sizeof(fileData));
        status = fsDataRead(&fileData, i);
        if (status) {
            op_uart_printf("-1-dataStore:dumpAll index=%d state=%d dataLength=%d uploadStatus=%d ts=%lu crc=%d\r\n",
                           i, fileData.state, fileData.dataLength, fileData.uploadStatus, fileData.ts, fileData.crc);
        } else {
            op_uart_printf("-1-dataStore:dumpAll index=%d read failed\r\n", i);
        }
    }
}

static fsDataBackUp_t fileDataUploadStateBu;

void fsDataUpdateUploadState(U2 uploadateIndex)
{
    static fsDataBackUp_t fileData; /* too large for my_task's stack */
    int dataFile;
    uint8_t crc_temp;

    /* Guards the same log file storeDtata()/fsDataWrite() write to. */
    if (ol_os_mutex_lock(dataFileMutex, 2000) != mbtk_os_success) {
        op_uart_printf("-1-dataStore:fsDataUpdateUploadState mutex lock timed out, index=%d\r\n", uploadateIndex);
        return;
    }

    fsDataRead(&fileData, uploadateIndex);
    op_uart_printf("-1-dataStore:fsDataUpdateUploadState readback index=%d state=%d dataLength=%d uploadStatus=%d ts=%lu\r\n",
                   uploadateIndex, fileData.state, fileData.dataLength, fileData.uploadStatus, fileData.ts);
    crc_temp = fileData.crc;
    fileData.crc = 0;
    fileData.crc = crc8_cal((uint8_t *)&fileData, sizeof(fileData));
    op_uart_printf("-1-dataStore:fsDataUpdateUploadState crc=%d,%d\r\n", crc_temp, fileData.crc);

    if (crc_temp == fileData.crc) {
        op_uart_printf("-1-dataStore:MQTT STATE UPDATED %d\r\n", fileData.uploadStatus);
        fileData.uploadStatus = D_UPLOADED;
        fileData.crc = 0;
        fileData.crc = crc8_cal((uint8_t *)&fileData, sizeof(fileData));
        op_uart_printf("-1-dataStore:fsDataUpdateUploadState state=%d,dataLength=%d,uploadStatus=%d,ts=%lu crc=%d\r\n",
                       fileData.state, fileData.dataLength, fileData.uploadStatus, fileData.ts, fileData.crc);
        fileDataUploadStateBu = fileData;

        /* Field-confirmed (isolated repro test): a file grown via "ab+"
         * (like fsDataWrite() does) silently fails to persist a later
         * update if that update also reopens with "ab+" -- the write
         * reports success but the byte never actually changes on flash.
         * Reopening with "rb+" for this in-place update instead does
         * persist correctly, confirmed against the same reproduction. */
        dataFile = ol_ffs_open(dataLogFile, "rb+");
        fileWrite(dataFile, uploadateIndex, &fileData);
        ol_ffs_close(dataFile);
    }

    ol_os_mutex_unlock(dataFileMutex);
}

void payLoadAutoUpload(U2 currentFileIndex, mqtt_client_t *client)
{
    static mqttQueue_t mqttSendData;  /* too large for my_task's stack */
    static fsDataBackUp_t fileData;   /* too large for my_task's stack */
    uint8_t crc_temp;
    U2 index;
    U1 status = 0;
    int dataFile;

    index = currentFileIndex;
    for (int i = 0; i < 20; i++) {
        if (ol_os_mutex_lock(dataFileMutex, 2000) == mbtk_os_success) {
            dataFile = ol_ffs_open(dataLogFile, "ab+");
            ol_ffs_close(dataFile);
            memset(&fileData, 0, sizeof(fileData));
            status = fsDataRead(&fileData, index);
            ol_os_mutex_unlock(dataFileMutex);
        } else {
            op_uart_printf("-1-dataStore:payLoadAutoUpload mutex lock timed out, index=%d\r\n", index);
            status = 0;
        }

        if (status) {
            crc_temp = fileData.crc;
            fileData.crc = 0;
            fileData.crc = crc8_cal((uint8_t *)&fileData, sizeof(fileData));
            op_uart_printf("-1-dataStore:payLoadAutoUpload index=%d state=%d dataLength=%d uploadStatus=%d ts=%lu crc_temp=%d fileData.crc=%d\r\n",
                           index, fileData.state, fileData.dataLength, fileData.uploadStatus, fileData.ts, crc_temp, fileData.crc);
            if ((crc_temp != 0) && (fileData.crc != 0)) {
                if (crc_temp == fileData.crc) {
                    if (fileData.uploadStatus == D_NOTUPLOADED) {
                        if (!maxPayLoadChecker()) {
                            op_uart_printf("-1-dataStore:daily max payload reached, stop backlog upload\r\n");
                            break;
                        }
                        op_uart_printf("-1-dataStore:fsAutoUpload index=%d\r\n", index);
                        memset(mqttSendData.data, 0, sizeof(mqttSendData.data));
                        memcpy(mqttSendData.data, fileData.data, fileData.dataLength);
                        mqttSendData.dataSize = fileData.dataLength;
                        mqttSendData.topic = 1;
                        mqttSendData.mqttFsInfo.index = index;
                        mqttSendData.mqttFsInfo.fsUpdateRequired = 1;

                        /* Reference queues this for a separate sender task
                         * (ql_rtos_queue_release); this codebase has no such
                         * queue, so publish directly with the client handle
                         * we were given and mark uploaded on success, same
                         * as the rest of this file already does. */
                        if (mqtt_publish(client, mqttSendData.data, mqttSendData.dataSize, mqttSendData.topic) == 0) {
                            fsDataUpdateUploadState(index);
                            maxPayLoadCount();
                        }
                        ol_os_task_sleep(200); /* 5s @ 5ms/tick */
                    }
                }
            }
        } else {
            ol_os_task_sleep(10); /* 550ms @ 5ms/tick */
        }

        if (index) {
            index--;
        } else {
            index = D_MAX_FILEINDEX;
        }
    }
}

mqttQueue_t storeDtata(serveTransmitPkt_t serveTransmitPkt)
{
    static mqttQueue_t mqttSendData; /* too large for my_task's stack */

    memset(&mqttSendData, 0, sizeof(mqttSendData));
    mqttSendData.topic = 1;
    mqttSendData.dataSize = sizeof(serveTransmitPkt);
    mqttSendData.mqttFsInfo.fsUpdateRequired = 1;
    mqttSendData.mqttFsInfo.index = currentFileIndex;
    mqttSendData.maxPayloadCheck = 1;
    mqttSendData.rtc.timeInSec = serveTransmitPkt.utc;

    memcpy(mqttSendData.data, &serveTransmitPkt, sizeof(serveTransmitPkt));

    /* 10s @ 5ms/tick, matching ol_os_task_sleep() usage elsewhere in this
     * codebase, instead of blocking forever if the lock is stuck. */
    if (ol_os_mutex_lock(dataFileMutex, 2000) == mbtk_os_success) {
        fsDataWrite((U1 *)&mqttSendData.data, mqttSendData.dataSize, &currentFileIndex, serveTransmitPkt.utc);
        dataStoreCount++;
        op_uart_printf("-1-dataStore:dataStoreCount=%lu\r\n", dataStoreCount);
        ol_os_mutex_unlock(dataFileMutex);
    } else {
        op_uart_printf("-1-dataStore:mutex lock timed out, skipping store\r\n");
    }

    return mqttSendData;
}
