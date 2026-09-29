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
    // bot_hal_logic_partition_t *logic_partition;
    // logic_partition = (bot_hal_logic_partition_t *)&hal_partitions[in_partition];
    // if(logic_partition != NULL) {
    //     memcpy(partition, logic_partition, sizeof(bot_hal_logic_partition_t));
    // }
    return 0;
}

int bot_hal_flash_read(bot_partition_id_e id, unsigned int *offset, void *buffer, unsigned int buffer_len)
{
    // if((offset == NULL) || (buffer == NULL)) {
    //     return -1;
    // }
    // if (buffer_len == 0) {
    //     return -1;
    // }

    // if (id != BOT_PARTITION_ID_KV) {
    //     return -1;
    // }

    // if (((*offset)  + buffer_len) > hal_partitions[id].partition_length) {
    //     return -1;
    // }
    // int fd = 0;
    // int ret;
    // // fd = open(KV_FILE_NAME, BOT_O_RDWR | BOT_O_CREAT, 0644);
    // if (fd < 0) {
    //     bot_printf("read fail to open kv\r\n");
    //     return -1;
    // }

    // // ret = lseek(fd, *offset, BOT_SEEK_SET);
    // ret = 0;
    // if (ret < 0) {
    //     bot_printf("read fail to lseek kv\r\n");
    //     return -1;
    // }

    // // ret = read(fd, buffer, buffer_len);
    // ret = 0;
    // if (ret < 0) {
    //     bot_printf("read fail to read kv\r\n");
    //     return -1;
    // }

    // bot_close(fd);

    // *offset += buffer_len;

    return 0;
}

int bot_hal_flash_write(bot_partition_id_e id, unsigned int *offset, const void *buffer, unsigned int buffer_len)
{
    // void* wr_buffer = (void*)buffer;

    // if((offset == NULL) || (wr_buffer == NULL)) {
    //     return -1;
    // }
    // if (buffer_len == 0) {
    //     return -1;
    // }

    // if (id != BOT_PARTITION_ID_KV) {
    //     return -1;
    // }

    // if (((*offset)  + buffer_len) >  hal_partitions[id].partition_length) {
    //     return -1;
    // }
    // int fd;
    // int ret;
    // // fd = open(KV_FILE_NAME, BOT_O_RDWR | BOT_O_CREAT, 0644);
    // fd = 0;
    // if (fd < 0) {
    //     bot_printf("write fail to open kv\r\n");
    //     return -1;
    // }

    // // ret = lseek(fd, *offset, BOT_SEEK_SET);
    // ret = 0;
    // if (ret < 0) {
    //     bot_printf("write fail to lseek kv\r\n");
    //     bot_close(fd);
    //     return -1;
    // }

    // // ret = write(fd, buffer, buffer_len);
    // ret = 0;
    // if (ret < 0) {
    //     bot_printf("write fail to write kv\r\n");
    //     bot_close(fd);
    //     return -1;
    // }

    // bot_close(fd);
    
    // *offset += buffer_len;
    return 0;
}

int bot_hal_flash_erase(bot_partition_id_e id, unsigned int offset, unsigned int size)
{
    // if (id != BOT_PARTITION_ID_KV) {
    //     return -1;
    // }

    // if (((offset)  + size) >  hal_partitions[id].partition_length) {
    //     bot_printf("flash offset over\r\n");
    //     return -1;
    // }

    // int fd;
    // int ret;
    // uint32_t erase = 0xFFFFFFFF;

    // // fd = open(KV_FILE_NAME, BOT_O_RDWR | BOT_O_CREAT, 0644);
    // fd = 0;
    // if (fd < 0) {
    //     bot_printf("erase fail to open kv\r\n");
    //     bot_close(fd);
    //     return -1;
    // }

    // // ret = lseek(fd, offset, BOT_SEEK_SET);
    // ret = 0;
    // if (ret < 0) {
    //     bot_printf("write fail to lseek kv\r\n");
    //     bot_close(fd);
    //     return -1;
    // }
    // int i;
    // for (i = 0; i < (size >> 2); i++) {
    //     ret = write(fd, (uint8_t*)&erase, sizeof(erase));
    //     if (ret < 0) {
    //         bot_printf("write fail to write kv\r\n");
    //         bot_close(fd);
    //         return -1;
    //     }
    // }

    // if (size & 0x03) {
    //     ret = write(fd, (uint8_t*)&erase, size & 0x03);
    //     if (ret < 0) {
    //         bot_printf("write fail to write kv\r\n");
    //         bot_close(fd);
    //         return -1;
    //     }
    // }

    // bot_close(fd);
    return 0;
}

#if 0
void bot_hal_flash_test(void)
{
    bot_hal_logic_partition_t partition;
    int offset = 0;
    int ret;
    char write_buf[36] = "hello kv flash. this is test data";
    char read_buf[36] = {0};

    memset(&partition, 0, sizeof(bot_hal_logic_partition_t));
    ret = bot_hal_flash_info_get(BOT_PARTITION_ID_KV,  &partition);
    if (ret < 0) {
        bot_printf("fail to get flash info\r\n");
        return;
    }

    offset = 0;
    bot_hal_flash_write(BOT_PARTITION_ID_KV, &offset, write_buf, 36);
    if (ret < 0) {
        bot_printf("fail to write data into flash\r\n");
        return;
    }

    offset = 0;
    bot_hal_flash_read(BOT_PARTITION_ID_KV, &offset, read_buf, 36);
    if (ret < 0) {
        bot_printf("fail to read data from flash\r\n");
        return;
    }
    bot_printf("the data in flash:%s\r\n", read_buf);

    offset = 0;
    ret = bot_hal_flash_erase(BOT_PARTITION_ID_KV, 16, 10);
    if (ret < 0) {
        bot_printf("fail to erase data in flash\r\n");
        return;
    }

    bot_hal_flash_read(BOT_PARTITION_ID_KV, &offset, read_buf, 36);
        if (ret < 0) {
        bot_printf("fail to read data from flash\r\n");
        return;
    }
    bot_printf("the data in flash:%s\r\n", read_buf);
}
#endif
