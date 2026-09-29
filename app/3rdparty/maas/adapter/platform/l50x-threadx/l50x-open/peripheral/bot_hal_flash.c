/*
 *
 * Copyright (C) 2020-2021 Alibaba Group Holding Limited
*/
/**
 * @file bot_hal_flash.C
 *
* @brief flash operations which need be impementd by customer.
 *
 *
 */
#include "bot_system_utils.h"
#include "bot_system.h"
#include "bot_hal_flash.h"
#include "bot_fs.h"

#define KV_FILE_NAME  "./bot_kv"

const static bot_hal_logic_partition_t hal_partitions[] =
{
    [BOT_PARTITION_ID_KV] =
    {
        .partition_description      = "KV",
        .partition_start_addr       = 0X450000,
        .partition_length           = 0X004000,
        .partition_options          = 3,
    }
};

int bot_hal_flash_info_get(bot_partition_id_e in_partition, bot_hal_logic_partition_t *partition)
{
    bot_hal_logic_partition_t *logic_partition;
    logic_partition = (bot_hal_logic_partition_t *)&hal_partitions[in_partition];
    if(logic_partition != NULL) 
    {
        memcpy(partition, logic_partition, sizeof(bot_hal_logic_partition_t));
    }
    return 0;
}

int bot_hal_flash_init(void)
{
#define ERASE_UNIT_NUMBER 512
    int fd = 0;
    fd = ol_ffs_open(KV_FILE_NAME, "rb");
    if (fd > 0) {
        ol_ffs_close(fd);
        bot_printf("no initialization required\r");
        return 0;
    }
    bot_printf("bot_hal_flash_init required\r");
    fd = ol_ffs_open(KV_FILE_NAME, "wb");
    if (fd < 0) {
        bot_printf("bot_hal_flash_init fail\r");
        return 0;
    }
    int i = 0;
    int size = hal_partitions[BOT_PARTITION_ID_KV].partition_length;
    unsigned int offset = 0;
    char erase_buffer[ERASE_UNIT_NUMBER] = {0XFF};
    memset(erase_buffer, 0XFF, ERASE_UNIT_NUMBER);
    int times = (size / ERASE_UNIT_NUMBER) + ((size % ERASE_UNIT_NUMBER) == 0 ? 0 : 1);
    bot_printf("erase to write kv times:%d\r", times);
    for(i = 0; i < times; i++)
    {
        int erase_len = ERASE_UNIT_NUMBER;
        if((i == (times - 1)) && ((size % ERASE_UNIT_NUMBER) != 0))
        {
            erase_len = (size % ERASE_UNIT_NUMBER);
        }
        bot_hal_flash_write(0, &offset, erase_buffer, erase_len);
    }
    
    ol_ffs_close(fd);
    return 0;
}

int bot_hal_flash_read(bot_partition_id_e id, unsigned int *offset, void *buffer, unsigned int buffer_len)
{
    if((offset == NULL) || (buffer == NULL)) {
        bot_printf("bot_hal_flash_read fail:%d\r", __LINE__);
        return -1;
    }
    if (buffer_len == 0) {
        bot_printf("bot_hal_flash_read fail:%d\r", __LINE__);
        return -1;
    }

    if (id != BOT_PARTITION_ID_KV) {
        bot_printf("bot_hal_flash_read fail:%d\r", __LINE__);
        return -1;
    }

    if (((*offset)  + buffer_len) > hal_partitions[id].partition_length) {
        bot_printf("bot_hal_flash_read fail:%d\r", __LINE__);
        return -1;
    }
    int fd = 0;
    int ret = 0;
    fd = ol_ffs_open(KV_FILE_NAME, "rb");
    if (fd < 0) {
        bot_printf("read fail to open kv\r\n");
        fd = bot_hal_flash_init();
        if (fd < 0) {
            bot_printf("initial flash fail\r\n");
            return -1;
        }
        fd = ol_ffs_open(KV_FILE_NAME, "rb");
        if (fd < 0) {
            bot_printf("read fail to open again kv\r\n");
            return -1;
        }
    }

    ret = ol_ffs_seek(fd, *offset, BOT_SEEK_SET);
    if (ret < 0) {
        ol_ffs_close(fd);
        bot_printf("bot_hal_flash_read fail:%d\r", __LINE__);
        return -1;
    }
	
    ret = ol_ffs_read(fd, (char *)buffer, buffer_len);
    if (ret < 0) {
        ol_ffs_close(fd);
        bot_printf("bot_hal_flash_read fail:%d\r", __LINE__);
        return -1;
    }

    ol_ffs_close(fd);

    bot_printf("id:%d, offset:%d, buffer_len:%d\r", id, *offset, buffer_len);

    *offset += buffer_len;

    return 0;
}

int bot_hal_flash_write(bot_partition_id_e id, unsigned int *offset, const void *buffer, unsigned int buffer_len)
{
    void* wr_buffer = (void*)buffer;
    
    bot_printf("id:%d, offset:%d, buffer_len:%d, data:\r", id, *offset, buffer_len);
    if((offset == NULL) || (wr_buffer == NULL)) {
        bot_printf("bot_hal_flash_write fail:%d\r", __LINE__);
        return -1;
    }
    if (buffer_len == 0) {
        bot_printf("bot_hal_flash_write fail:%d\r", __LINE__);
        return -1;
    }

    if (id != BOT_PARTITION_ID_KV) {
        bot_printf("bot_hal_flash_write fail:%d\r", __LINE__);
        return -1;
    }

    if (((*offset)  + buffer_len) >  hal_partitions[id].partition_length) {
        bot_printf("bot_hal_flash_write fail:%d\r", __LINE__);
        return -1;
    }
    int fd = 0;
    int ret = 0;
    fd = ol_ffs_open(KV_FILE_NAME, "rb+");
    if (fd < 0) {
        bot_printf("fail to open kv\r\n");
        fd = bot_hal_flash_init();
        if (fd < 0) {
            bot_printf("initial flash fail\r\n");
            return -1;
        }
        fd = ol_ffs_open(KV_FILE_NAME, "rb");
        if (fd < 0) {
            bot_printf("fail to open again kv\r\n");
            return -1;
        }
    }

    ret = ol_ffs_seek(fd, *offset, BOT_SEEK_SET);
    if (ret < 0) {
        bot_printf("bot_hal_flash_write fail:%d\r", __LINE__);
        ol_ffs_close(fd);
        return -1;
    }

    ret = ol_ffs_write(fd, buffer, buffer_len);
    if (ret < 0) {
        bot_printf("bot_hal_flash_write fail:%d\r", __LINE__);
        ol_ffs_close(fd);
        return -1;
    }
    
    bot_printf("bot_hal_flash_write succ:%d\r", __LINE__);

    ol_ffs_close(fd);
    
    *offset += buffer_len;
    return 0;
}

int bot_hal_flash_erase(bot_partition_id_e id, unsigned int offset, unsigned int size)
{
#define ERASE_UNIT_NUMBER 512
    if (id != BOT_PARTITION_ID_KV) {
        return -1;
    }

    if (((offset)  + size) >  hal_partitions[id].partition_length) {
        bot_printf("flash offset over\r\n");
        return -1;
    }

    int fd = -1;
    int ret = 0;
    int i = 0;
    char erase_buffer[ERASE_UNIT_NUMBER] = {0XFF};
    memset(erase_buffer, 0XFF, ERASE_UNIT_NUMBER);
    int times = (size / ERASE_UNIT_NUMBER) + ((size % ERASE_UNIT_NUMBER) == 0 ? 0 : 1);
    bot_printf("erase to write kv times:%d\r\n", times);
    for(i = 0; i < times; i++)
    {
        int erase_len = ERASE_UNIT_NUMBER;
        if((i == (times - 1)) && ((size % ERASE_UNIT_NUMBER) != 0))
        {
            erase_len = (size % ERASE_UNIT_NUMBER);
        }
        bot_hal_flash_write(id, &offset, erase_buffer, erase_len);
    }
    
    return 0;
}

