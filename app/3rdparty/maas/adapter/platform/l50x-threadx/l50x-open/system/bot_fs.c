/***********************************************************************************************************************
 * Copyright (C) 2021-2022 Alibaba Group Holding Limited
 * description: source file of 
 * author:      
 * date:        2021-09-14
***********************************************************************************************************************/
/***********************************************************************************************************************
 * Including File
***********************************************************************************************************************/
#include "bot_system.h"
#include "bot_fs.h"


/***********************************************************************************************************************
 * Macro Definition
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Enumeration Definition
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Type & Structure Definition
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variable Definition
***********************************************************************************************************************/

/***********************************************************************************************************************
 * Fuction Declaration
***********************************************************************************************************************/
/******************************************** API about I/O operation *************************************************/
#if (BOT_FS_STREAM_ENABLED == BOT_OFF)

/**
 * @brief bot_open() opens the file or device by its @path.
 *
 * @param[in] path   the path of the file or device to open.
 * @param[in] flag   the flag of open operation.
 *
 * @return  new file descriptor: On success.
 *          negative error code: On error, the code indicating the cause
 *          of the error.
 */
static bot_fd_t bot_open(const char *path, bot_fs_flag_t flag);

/**
 * @brief bot_close() closes the file or device associated with file
 *        descriptor @fd.
 *
 * @param[in] fd  the file descriptor of the file or device.
 *
 * @return  0: On success.
 *          negative error code: On error, the code indicating the cause
 *          of the error.
 */
static int bot_close(bot_fd_t fd);

/**
 * @brief bot_seek() repositions the file offset of the open file
 *        description associated with the file descriptor @fd to the
 *        argument @offset according to the directive @whence as follows:
 *
 *        BOT_SEEK_SET: The file offset is set to @offset bytes.
 *        BOT_SEEK_CUR: The file offset is set to its current location
 *                      plus @offset bytes.
 *        BOT_SEEK_END: The file offset is set to the size of the file
 *                      plus @offset bytes.
 *
 * @param[in] fd      The file descriptor of the file.
 * @param[in] offset  The offset relative to @whence directive.
 * @param[in] whence  The start position where to seek. must be one of: 
 * 
 * @return  On success, return the resulting offset location as measured
 *          in bytes from the beginning of the file.
 *          On error, neagtive error code is returned to indicate the cause
 *          of the error.
 */
static int bot_seek(bot_fd_t fd, int offset, int whence);
#if 0
/**
 * @brief bot_tell() get the current location of file. 
 *
 * @param[in] fd  the file descriptor of the file.
 *
 * @return  On success return 0.
 *          negative error code: On error, the code indicating the cause
 *          of the error.
 */
static long bot_tell(bot_fd_t fd);
#endif
/**
 * @brief bot_read() attempts to read up to @size bytes from file
 *        descriptor @fd into the buffer starting at @buff.
 *
 * @param[in]  fd       the file descriptor of the file or device.
 * @param[out] buff     the buffer to read bytes into.
 * @param[in]  size     the number of bytes to read.
 *
 * @return  On success, the number of bytes is returned (0 indicates end
 *          of file) and the file position is advanced by this number.
 *          negative error code: On error, the code indicating the cause
 *          of the error.
 */
static int bot_read(bot_fd_t fd, void *buff, unsigned int size);

/**
 * @brief bot_write() writes up to @size bytes from the buffer starting
 *        at @buff to the file referred to by the file descriptor @fd.
 *
 * @param[in] fd        the file descriptor of the file or device.
 * @param[in] buff      the buffer to write bytes from.
 * @param[in] size      the number of bytes to write.
 *
 * @return  On success, the number of bytes written is returned, and the file
 *          position is advanced by this number..
 *          negative error code: On error, the code indicating the cause
 *          of the error.
 */
static int bot_write(bot_fd_t fd, const void *buff, unsigned int size);

/**
 * @brief bot_fsync causes the pending modifications of the specified file to
 *        be written to the underlying filesystems.
 *
 * @param[in] fd  the file descriptor of the file.
 *
 * @return  On success return 0.
 *          negative error code: On error, the code indicating the cause
 *          of the error.
 */
static int bot_fsync(bot_fd_t fd);
#if 0
/**
 * @brief bot_fstat() return information about a file pointed to by @path
 *        in the buffer pointed to by @st_buff.
 *
 * @param[in]  fd       The file descriptor.
 * @param[out] st_bufff  The buffer to receive information.
 *
 * @return  On success, return 0.
 *          On error, negative error code is returned to indicate the cause
 *          of the error.
 */
static int bot_fstat(bot_fd_t fd, bot_stat_t *st_bufff);

/**
 * @brief bot_fstatfs() return information about the file system to by @path
 *        in the buffer pointed to by @sf_buff.
 *
 * @param[in]  fd       The path of the file to be quried.
 * @param[out] sf_buff  The buffer to receive information.
 *
 * @return  On success, return 0.
 *          On error, negative error code is returned to indicate the cause
 *          of the error.
 */
static int bot_fstatfs(bot_fd_t fd, bot_statfs_t *sf_buff);
#endif
#endif
/***********************************************************************************************************************
 * Fuction Implementation
***********************************************************************************************************************/
int bot_fs_init(void)
{
    int ret = bot_mkdir(BOT_FS_USER_DIR);
    if (ret != BOT_OK) {
        bot_printf("%s() create %s fail, ret = %d\n", __func__, BOT_FS_USER_DIR, ret);
    }
    return ret;
}

/***************************************** API about directory operation **********************************************/
static bool bot_is_exit_dir(const char *path, const char * dir_name)
{
    OL_LFS_INFO info = {0};
    int ret = false;
    int fd = 0;
    
    if(path == NULL)
    {
        return false;
    }
    fd = ol_ffs_opendir(path);
    if(fd < 0)
    {
        bot_printf("bot_is_exit_dir dir open fail: %s\r", path);
        return false;
    }
    
    bot_printf("bot_is_exit_dir dir opened: %s\r", path);
    while(1)
    {
        ret = ol_ffs_readdir(fd, &info);
        if(ret < 0)
        {
            bot_printf("bot_is_exit_dir dir read fail: %s\r", path);
            ret = false;
            break;
        }
        else if(ret == 0)
        {
            bot_printf("bot_is_exit_dir end of dir list\r");
            ret = false;
            break;
        }
        else
        {
            bot_printf("info.name:%s <--> dir_name:%s\r", info.name, dir_name);
            if(strlen(info.name) == strlen(dir_name))
            {
                if(memcmp(info.name, dir_name, strlen(dir_name)) == 0)
                {
                    ret = true;
                    bot_printf("bot_is_exit_dir find dir(%s)\r", dir_name);
                    break;
                }
            }
        }
    }
    ol_ffs_closedir(fd);
    bot_printf("bot_is_exit_dir dir closed: %s\r", path);
    return ret;
}

int bot_exitdir(const char * path)
{
    int i = 0;

    int path_len = strlen(path);

    bot_printf("bot_exitdir1 path is:%s", path);
    bot_printf("bot_exitdir1 path len is:%d", path_len);

    if(path == NULL || path_len <= 0)
    {
        bot_printf("bot_exitdir fail -> path is NULL");
        return -1;
    }
    char* temp_path = malloc(path_len + 1);
    memset(temp_path, 0, path_len + 1);
    char dir_name[30] = {0};
    bool is_get_first_path = false;
    int j = 0;
    bool ret = false;
    for(i = 0; i < path_len; i++)
    {
        if(is_get_first_path == false)
        {
            if(path[i] == '/')
            {
                memcpy(temp_path, path, i);
                is_get_first_path = true;
                j = 0;
                continue;
            }
        }
        else
        {
            if(path[i] == '/' || i == (path_len - 1))
            {
                memset(dir_name, 0, sizeof(dir_name));
                if(i == (path_len - 1))
                {
                    memcpy(dir_name, path+i-j, j+1);
                }
                else
                {
                    memcpy(dir_name, path+i-j, j);
                }
                ret = bot_is_exit_dir(temp_path, dir_name);
                if(ret == false)break;
                memcpy(temp_path, path, i);
                j=0;
                continue;
            }
            j++;
        }
    }
    free(temp_path);

    if(ret == false)
    {
        bot_printf("bot_exitdir path(%s) not exist", path);
        return -1;
    }
    bot_printf("bot_exitdir path(%s) is exist", path);
    return 0;
}

int bot_mkdir(const char *path)
{
    if(path == NULL || strlen(path) <= 0)
    {
        bot_printf("bot_mkdir fail -> path is NULL");
        return -1;
    }
    int ret = 0;
    int all_len = strlen(path);
    char* path_str = malloc(all_len + 1);
    if(path_str == NULL)
    {
        bot_printf("bot_mkdir fail -> malloc fail");
        return -1;
    }
    int i = 0;
    memset(path_str, 0, all_len);
    for(i = 0; i < all_len; i++)
    {
        if(all_len > 1 && i < 1)
        {
            if(path[0] == '/')
            {
                continue;
            }
        }
        
        if(all_len > 2 && i < 2)
        {
            if(path[0] == '.' && path[1] == '/')
            {
                continue;
            }
        }
        
        if(path[i] == '/' || (i == (all_len - 1)))
        {
            if(i == (all_len - 1))
            {
                memset(path_str, 0, all_len + 1);
                memcpy(path_str, path, all_len);
                bot_printf("mkdir end:%s\n", path_str);
                ret = ol_ffs_createdir(path_str);
                free(path_str);
                break;
            }
            else
            {
                memset(path_str, 0, all_len + 1);
                memcpy(path_str, path, i);
                bot_printf("mkdir:%s\n", path_str);
                ret = ol_ffs_createdir(path_str);
            }
            if (ret < 0 && ret != -17) {
                bot_printf("%s() ql_mkdir %s fail, ret = %d\n", __func__, path, ret);
                free(path_str);
                return ret;
            }
        }
    }

    if(ret == -17)
    {
        ret = 0;
    }
    bot_printf("%s() ql_mkdir %s and ret = %d\n", __func__, path, ret);
    return ret;
}
#if 0
int bot_rmdir(const char *path)
{
    // TODO return fibo_file_rmdir(path);
    return 0;
}

bot_dir_t *bot_opendir(const char *path)
{
    // TODO return fibo_file_opendir(path);
    return 0;
}

int bot_closedir(bot_dir_t *dir)
{
    // TODO return fibo_file_closedir(dir);
    return 0;
}

bot_dirent_t *bot_readdir(bot_dir_t *dir)
{
    // TODO return fibo_file_readdir(dir);
    return 0;
}

void bot_rewinddir(bot_dir_t *dir)
{
    bot_printf("not suppot yet!\n");
}

long bot_telldir(bot_dir_t *dir)
{
    // TODO return (long)fibo_file_telldir(dir);
    return 0;
}

void bot_seekdir(bot_dir_t *dir, long offset)
{
    // TODO fibo_file_seekdir(dir, offset);
    return 0;
}

int bot_chdir(const char *path)
{
    bot_printf("not suppot yet!\n");
    return -1;
}
#endif

/******************************************** API about file operation ************************************************/
char open_mode[5] = {0};
bot_file_t bot_fopen(const char *path, const char *mode)
{
    memset(open_mode, 0, sizeof(open_mode));
    memcpy(open_mode, mode, strlen(mode));
#if BOT_FS_STREAM_ENABLED
    return fopen(path, mode);
#else
    bot_fs_flag_t flag;
    if ((strcmp(mode, "r") == 0) || (strcmp(mode, "rb") == 0) || (strcmp(mode, "rt") == 0)) {
        memcpy(open_mode, "rb", strlen("rb"));
    } else if ((strcmp(mode, "r+") == 0) || (strcmp(mode, "rb+") == 0) || (strcmp(mode, "rt+") == 0)) {
        memcpy(open_mode, "rb+", strlen("rb+"));
    } else if ((strcmp(mode, "ab") == 0) || (strcmp(mode, "at") == 0)) {
        memcpy(open_mode, "ab", strlen("ab"));
    } else if (strcmp(mode, "w") == 0) {
        memcpy(open_mode, "wb", strlen("wb"));
    } else if (strcmp(mode, "w+") == 0) {
        memcpy(open_mode, "wb+", strlen("wb+"));
    } else if (strcmp(mode, "a") == 0) {
        memcpy(open_mode, "ab", strlen("ab"));
    } else if (strcmp(mode, "a+") == 0) {
       memcpy(open_mode, "ab", strlen("ab"));
    } else if ((strcmp(mode, "wb") == 0) || (strcmp(mode, "wt") == 0)) {
       memcpy(open_mode, "wb", strlen("wb"));
    } else if ((strcmp(mode, "wb+") == 0) || (strcmp(mode, "wt+") == 0)) {
       memcpy(open_mode, "wb+", strlen("wb+"));
    } else if ((strcmp(mode, "at+") == 0) || (strcmp(mode, "ab+") == 0)) {
       memcpy(open_mode, "ab", strlen("ab"));
    } else {
        return BOT_FILE_INIT_VALUE;
    }
    return bot_open(path, flag);
#endif  

}

int bot_fclose(bot_file_t fp)
{
#if BOT_FS_STREAM_ENABLED
    return fclose(fp);
#else
    return bot_close(fp);
#endif
}

int bot_fread(void *buff, unsigned int size, unsigned int count, bot_file_t fp)
{
#if BOT_FS_STREAM_ENABLED
    return fread(buff, size, count, fp);
#else
    return bot_read(fp, buff, size * count);
#endif
}

int bot_fwrite(const void *buff, unsigned int size, unsigned int count, bot_file_t fp)
{
#if BOT_FS_STREAM_ENABLED
    return fwrite(buff, size, count, fp);
#else
    return bot_write(fp, buff, size * count);
#endif
}

int bot_fseek(bot_file_t fp, int offset, int whence)
{
    int ret = BOT_NOT_OK;
#if BOT_FS_STREAM_ENABLED
    ret = fseek(fp, offset, whence);
    if (ret == 0) {
        ret = BOT_OK;
    }
#else
    ret = bot_seek(fp, offset, whence);
    if (ret >= 0) {
        ret = BOT_OK;
    }
#endif
    return ret;
}

int bot_fflush(bot_file_t fp)
{
#if BOT_FS_STREAM_ENABLED
    return fflush(fp);
#else
    return bot_fsync(fp);
#endif  
}
#if 0
long bot_ftell(bot_file_t fp)
{
#if BOT_FS_STREAM_ENABLED
    return ftell(fp);
#else
    return bot_tell(fp);
#endif 
}

int bot_stat(const char *path, bot_stat_t *st_buff)
{
#if BOT_FS_STREAM_ENABLED
    // TODO fibo_file_stat(path, st_buff);
#else
    bot_fd_t fd = bot_open(path, BOT_O_RDONLY);
    if (bot_file_is_valid(fd)) {
        int ret = bot_fstat(fd, st_buff);
        bot_close(fd);
        return ret;
    } else {
        return BOT_NOT_OK;
    }
#endif
}

int bot_statfs(const char *path, bot_statfs_t *sf_buff)
{
    
#if BOT_FS_STREAM_ENABLED
    return statfs(path, sf_buff);
#else
    bot_fd_t fd = bot_open(path, BOT_O_RDONLY);
    if (bot_file_is_valid(fd)) {
        int ret = bot_fstatfs(fd, sf_buff);
        bot_close(fd);
        return ret;
    } else {
        return BOT_NOT_OK;
    }
#endif
}

int bot_remove(const char *path)
{
    return fibo_file_delete(path);
    return 0;
}

int bot_rename(const char *oldpath, const char *newpath)
{
    return fibo_file_rename(oldpath, newpath);
    return 0;
}
#endif

bool bot_file_is_valid(bot_file_t fp)
{
    bool ret = false;
#if BOT_FS_STREAM_ENABLED
    if (fp != NULL) {
        ret = true;
    }
#else
    if (fp > 0) {
        ret = true;
    }
#endif
    return ret;
}

void bot_fs_print_errno(void)
{
//    bot_printf("error description: %s, error_no = %u\n", __func__, strerror(errno), errno);
}

int bot_unlink(const char *path)
{
    int ret = ol_ffs_delete(path);
    return ret;
}

/******************************************** API about I/O operation *************************************************/
#if (BOT_FS_STREAM_ENABLED == BOT_OFF)
static bot_fd_t bot_open(const char *path, bot_fs_flag_t flag)
{
    bot_printf("bot_open :%s, flag:%s", path, flag);
    int fd = 0;
    if(path == NULL || open_mode == NULL)
    {
        return -1;
    }

    fd = ol_ffs_open(path, open_mode);
    if(fd  < 0)
    {
        return -1;
    }
    else
    {
        return fd;
    }
}

static int bot_close(bot_fd_t fd)
{
    int ret = 0;
    if(fd <=0)
    {
        return -1;
    }
    
    ret = ol_ffs_close(fd);
    if(ret < 0)
    {
        return -1;
    }
    else
    {
        return ret;
    }
}

static int bot_seek(bot_fd_t fd, int offset, int whence)
{
    int ret = 0;
    int now_pos = 0;
    if(fd <= 0)
    {
        return -1;
    }
    
    if(offset < 0)
    {
        now_pos = ol_ffs_seek(fd, 0, whence);
        now_pos += offset;
        ret = ol_ffs_seek(fd, now_pos, BOT_SEEK_SET);
    }
    else
    {
        ret = ol_ffs_seek(fd, offset, whence);
    }
    if(ret < 0)
    {
        return -1;
    }
    else
    {
        return ret;
    }
}
#if 0
static long bot_tell(bot_fd_t fd)
{
    // TODO return fibo_file_ftell(fd);
    return 0;
}
#endif
static int bot_read(bot_fd_t fd, void *buff, unsigned int size)
{
    int num = ol_ffs_read(fd, (char *)buff, size);
    if(num < 0)
    {
        return FILE_ERR_WRITE;
    }
    else
    {
        return num;
    }
}

static int bot_write(bot_fd_t fd, const void *buff, unsigned int size)
{
    int num = ol_ffs_write(fd, (char *)buff, size);
    if(num < 0)
    {
        return FILE_ERR_WRITE;
    }
    else
    {
        return num;
    }
}

static int bot_fsync(bot_fd_t fd)
{
    return 0;
}
#if 0
static int bot_fstat(bot_fd_t fd, bot_stat_t *st_bufff)
{
    // TODO return fibo_file_fstat(fd, st_bufff);
    return 0;
}

static int bot_fstatfs(bot_fd_t fd, bot_statfs_t *sf_buff)
{
    bot_printf("not suppot yet!\n");
    return BOT_NOT_OK;
}
#endif
#endif
