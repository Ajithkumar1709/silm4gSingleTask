#ifndef _NL_API_FS_H_
#define _NL_API_FS_H_

// Read only.
#define FS_O_RDONLY	            0

// Write only.
#define FS_O_WRONLY	     1

// Read and Write. 
#define FS_O_RDWR	            2
 
// Access. 
#define FS_O_ACCMODE	     3

// If the file exists, this flag has no effect except as noted under FS_O_EXCL below. Otherwise, the file shall be created.
#define FS_O_CREAT		      0x00100

// If FS_O_CREAT and FS_O_EXCL are set, the function shall fail if the file exists.
#define FS_O_EXCL		      0x00200

// If the file exists, and is a regular file, and the file is successfully opened FS_O_WRONLY or FS_O_RDWR, its length shall be truncated to 0.
#define FS_O_TRUNC		      0x01000

// If set, the file offset shall be set to the end of the file prior to each write.
#define FS_O_APPEND	      0x02000

typedef struct
{
    int16_t fs_index;  ///< internal fs index
    int16_t _reserved; ///< reserved
} DIR;

/**
 * @brief    创建一个指定名称的文件，文件选项分为基本选项和扩展选项
 * 基本选项：
 * FS_O_RDONLY 只读方式打开；FS_O_WRONLY 只写方式打开；FS_O_RDWR 读写方式打开。
 * 扩展选项可以与基本选项混用，使用或操作符：
 * FS_O_CREAT 若打开文件时有此选项，若文件不存在则创建文件。
 * FS_O_EXCL 主要是为了与FS_O_CREAT联合使用，若文件存在，则创建失败。
 * FS_O_TRUNC 若文件存在，把文件长度变成0。
 * FS_O_APPEND 以追加方式打开文件。
 *
 * @param < pathname>无目录结构文件名
 * @param <opt>打开文件选项 
 * 
 * @return  ≥0 - 打开（创建）成功，此为该文件句柄  <0 - 创建失败
 */
INT32 nl_file_open(const INT8 * pathname,UINT32 opt);

/**
 * @brief    关闭打开的文件
 *
 * @param <fd>打开的文件句柄
 * 
 * @return  0：成功  <0：失败
 */
INT32 nl_file_close(INT32 fd);

/**
 * @brief    从打开文件的当前位置读出数据
 *
 * @param <fd>打开的文件句柄
 * @param <buff>数据缓冲区指针
 * @param <size>数据缓冲区长度
 * 
 * @return  ≥0 - 读出的字节数  <0 - 失败
 */
INT32 nl_file_read(INT32 fd,UINT8 * buff,UINT32 size);

/**
 * @brief    从打开文件的当前位置处写入数据
 *
 * @param <fd>打开的文件句柄
 * @param <buff>数据缓冲区指针
 * @param <size>数据缓冲区长度
 * 
 * @return  ≥0 - 写入的字节数  <0 - 失败
 */
INT32 nl_file_write(INT32 fd,UINT8 * buff,UINT32 size);

/**
 * @brief    移动文件数据指针，并返回操作成功后的文件指针位置
 * Offset可以是负数，opt是移动文件指针的起始位置，有三个选项：
 * FS_SEEK_SET 从文件开头开始移动offset个字节；
 * FS_SEEK_CUR 从文件指针当前位置移动offset个字节；
 * FS_SEEK_END 从文件结束位置移动offset个字节。
 *
 * @param <fd>打开的文件句柄
 * @param <offset>从文件开始的偏移
 * @param <opt>偏移的起始位置
 * 
 * @return  ≥0 - 打开（创建）成功，此为该文件句柄  <0 - 创建失败
 */
INT32 nl_file_seek(INT32 fd,INT32 offset,UINT8 opt);

/**
 * @brief    重命名文件；使用前需close文件；
 *
 * @param < lpOldName >源文件原文件名
 * @param < lpNewName >新文件名
 * 
 * @return  0 - 成功  <0 - 失败
 */
INT32 nl_file_rename(const INT8 * lpOldName,const INT8 * lpNewName);

/**
 * @brief    创建一个路径/文件夹
 *
 * @param < name >文件夹（路径）名
 * 
 * @return  0 - 成功  <0 - 失败
 */
INT32 nl_file_mkdir(const char * name);

/**
 * @brief    检测文件是否存在
 *
 * @param < pszFileName >文件名
 * 
 * @return  1 – 文件存在  <0 – 文件不存在
 */
INT32 nl_file_exist(const INT8 * pszFileName);

/**
 * @brief    获取文件大小
 *
 * @param < pszFileName >文件名
 * 
 * @return  ≥0 - 文件长度  <0 - 操作失败
 */
INT32 nl_file_getSize(const INT8 * pszFileName);

/**
 * @brief    删除文件
 *
 * @param < pszFileName >文件名
 * 
 * @return  0  – 删除成功  <0 – 失败
 */
INT32 nl_file_delete(const INT8 * pathName);

/**
 * @brief    获取剩余文件系统大小
 * 
 * @return  ≥0 - 文件系统剩余空间大小  <0 - 操作失败
 */
INT32 nl_file_getFreeSize(void);

/**
 * @brief    获取path子目录下的所有文件和目录的列表
 * 
 * @param <path>文件夹名称
 *
 * @return  返回dir；
 */
DIR *nl_file_opendir(const char *name);

/**
 * @brief    查询目录下文件列表
 * 
 * @param <dir>文件夹名
 *
 * @return  0 执行成功
 */
INT8 nl_get_file_list(char *dir, void (*cb)(const char *filepath, size_t size, void *arg), void *args);
#endif