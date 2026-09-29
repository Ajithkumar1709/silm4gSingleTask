#ifndef _OL_FLASH_FS_H_
#define _OL_FLASH_FS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ol_fs_pub.h"

/********************************
*for file_open <mode> like
*		"rb"		read only	
*		"rb+"	read and write
*		"wb"		create,read,write,truncate
*		"wb+"	create,read,write,truncate
*		"ab"		create,read,write,append
*		"ab+"	create,read,write,append
所有项目中，不同分区用不同的盘符来区分
有nvm分区的，对应盘符是C:
有customer_fs分区的，对应盘符是U:
如果是sd卡或者外挂emmc的，对应盘符一般为D：

*********************************/


 typedef enum
{
	SSP_CLOCK_13M,
	SSP_CLOCK_26M,
	SSP_CLOCK_52M
} SSP_Clock;

typedef enum
{
	FS_ERR_OK          = 0,    // No error
    FS_ERR_BLOCK       = -1,   // Error LFS block
    FS_ERR_IO          = -5,   // Error during device operation
    FS_ERR_CORRUPT     = -52,  // Corrupted
    FS_ERR_NOENT       = -2,   // No directory entry
    FS_ERR_EXIST       = -17,  // Entry already exists
    FS_ERR_NOTDIR      = -20,  // Entry is not a dir
    FS_ERR_ISDIR       = -21,  // Entry is a dir
    FS_ERR_NOTEMPTY    = -39,  // Dir is not empty
    FS_ERR_BADF        = -9,   // Bad file number
    FS_ERR_FBIG        = -27,  // File too large
    FS_ERR_INVAL       = -22,  // Invalid parameter
    FS_ERR_NOSPC       = -28,  // No space left on device
    FS_ERR_NOMEM       = -12,  // No more memory available
    FS_ERR_NAMETOOLONG = -36,  // File name too long

}FS_ERROR;

// ssp flash
typedef enum
{
    SSP_PORT_0			= 0,
    SSP_PORT_1			= 1,
    SSP_PORT_2			= 2,
} SSP_PORT;


typedef int (*spi_nor_read_fun)(unsigned int addr, unsigned int buf_addr, unsigned int size);
typedef int (*spi_nor_write_fun)(unsigned int addr, unsigned int buf_addr, unsigned int size);
typedef int (*spi_nor_earse_fun)(unsigned int addr, unsigned int size);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_open
 * DESCRIPTION 
 *  		This API is to open a file with the mode.  
 * PARAMETERS 
 *		lpFileName		[IN]:The file name of the file you want to open
 *		mode				[IN]:how to open the file
 * RETURN VALUES
 *		>=0 : a file handle will be return
 *		<0   : error ,see enum OL_FILE_ERR
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_ffs_open(char* lpFileName, char * mode);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_read
 * DESCRIPTION 
 *  		This API is to read data from a opened file.  
 * PARAMETERS 
 *		fileHandle							[IN]: a file handle give by ol_ffs_open
 *		readBuffer						[OUT]: a pointer to read buffer
 *		numberOfBytesToRead		[IN]:number of bytes to read
 * RETURN VALUES
 *		>=0 : concrete length of read data
 *		<0   : error ,see enum OL_FILE_ERR
 * RETURN MESSAGE
 * 		 NONE
 * 
 *****************************************************************************/
extern int ol_ffs_read(int fileHandle, char *readBuffer, unsigned int numberOfBytesToRead);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_write
 * DESCRIPTION 
 *  		This API is to write data into a file which can be written.  
 * PARAMETERS 
 *		fileHandle							[IN]: a file handle give by ol_ffs_open
 *		writeBuffer						[IN]: a pointer to write buffer
 *		numberOfBytesToWrite	[IN]: number of bytes to write
 * RETURN VALUES
 *		>=0 : exact length of write data
 *		<0   : error ,see enum OL_FILE_ERR
 * RETURN MESSAGE
 * 		 NONE
 * 
 *****************************************************************************/
extern int ol_ffs_write(int fileHandle, char *writeBuffer, unsigned int numberOfBytesToWrite);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_seek
 * DESCRIPTION 
 *  		This API is to repositions the offset of the open file.  
 * PARAMETERS 
 *		fileHandle		[IN]: a file handle give by ol_ffs_open
 *		offset			[IN]: number of bytes to move the file pointer
 *		whence			[IN]: The file pointer reference position. see ol_fs_pub.h
 * RETURN VALUES
 *		=0 : file seek success
 *		<0   : error ,see enum OL_FILE_ERR
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_ffs_seek(int  fileHandle, long offset, int whence);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_ftell
 * DESCRIPTION 
 *  		This API is to get the offset of the open file. 
 * PARAMETERS 
 *		fileHandle		[IN]: a file handle give by ol_ffs_open
 * RETURN VALUES
 *		>0 : number of bytes to move the file pointer
 *		<=0   : error ,see enum OL_FILE_ERR
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_ffs_ftell(int fileHandle);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_close
 * DESCRIPTION 
 *  		This API is to close a file handle.  
 * PARAMETERS 
 *		fileHandle		[IN]: a file handle give by ol_ffs_open
 * RETURN VALUES
 *		=0 : close file  success
 *		<0   : error ,see enum OL_FILE_ERR
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_ffs_close(int fileHandle);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_sync
 * DESCRIPTION 
 *  		This API is to sync file data to flash.  
 * PARAMETERS 
 *		lpFileName	[IN]: a pointer to file name
 * RETURN VALUES
 *		>=0 : concrete file size
 *		<0   : error ,see enum OL_FILE_ERR
 * RETURN MESSAGE
 * 		 NONE
 * 
 *****************************************************************************/
extern int ol_ffs_sync(int fileHandle);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_getsize
 * DESCRIPTION 
 *  		This API is to get the file size.  
 * PARAMETERS 
 *		lpFileName	[IN]: a pointer to file name
 * RETURN VALUES
 *		>=0 : concrete file size
 *		<0   : error ,see enum OL_FILE_ERR
 * RETURN MESSAGE
 * 		 NONE
 * 
 *****************************************************************************/
extern int ol_ffs_getsize(char *lpFileName);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_getsize
 * DESCRIPTION 
 *  		This API is to get the file size.  
 * PARAMETERS 
 *		lpFileName	[IN]: a pointer to file name
 * RETURN VALUES
 *		>=0 : concrete file size
 *		<0   : error ,see enum OL_FILE_ERR
 * RETURN MESSAGE
 * 		 NONE
 * 
 *****************************************************************************/
extern FS_ERROR ol_ffs_getsize_ex(int fileHandle);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_delete
 * DESCRIPTION 
 *  		This API is to delete a file.  
 * PARAMETERS 
 *		lpFileName	[IN]: a pointer to file name
 * RETURN VALUES
 *		=0 : delete file success
 *		<0   : error ,see enum OL_FILE_ERR
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_ffs_delete(char *lpFileName);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_rename
 * DESCRIPTION 
 *  		This API is to rename a file.  
 * PARAMETERS 
 *		lpFileName			[IN]: a pointer to old file name
 *		newLpFileName	[IN]:	 a pointer to new file name
 * RETURN VALUES
 *		=0 : rename file success
 *		<0   : error ,see enum OL_FILE_ERR
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_ffs_rename(char *lpFileName, char *newLpFileName);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_findfirst
 * DESCRIPTION 
 *  		This API is to get the first file information witch matching lpFileName
 * PARAMETERS 
 *		lpFileName			[IN]: a pointer to old file name
 *		pFindData				[IN]:	 a pointer to file information struct,see ol_FS_FIND_DATA
 * RETURN VALUES
 *		=0 : find the first file matched
 *		<0   : error ,see enum OL_FILE_ERR
 * RETURN MESSAGE
 * 		 NONE
 * 	
 *****************************************************************************/
extern int ol_ffs_findfirst(char *lpFileName, ol_PFS_FIND_DATA pFindData);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_findnext
 * DESCRIPTION 
 *  		This API is to get the first file information witch matching lpFileName give by ol_ffs_findfirst 
 * PARAMETERS 
 *		pFindData				[IN]:	 a pointer to file information struct,see ol_FS_FIND_DATA
 * RETURN VALUES
 *		=0 : rename file success
 *		<0   : View error code table
 * RETURN MESSAGE
 * 		 NONE
 * 
 *****************************************************************************/
extern int ol_ffs_findnext(ol_PFS_FIND_DATA pFindData);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_findclose
 * DESCRIPTION 
 *  		This API is to close the find opration 
 * PARAMETERS 
 *		NONE
 * RETURN VALUES
 *		=0 : rename file success
 *		<0   : View error code table
 * RETURN MESSAGE
 * 		 NONE
 * 
 *****************************************************************************/
extern int ol_ffs_findclose(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_fprintf
 * DESCRIPTION 
 *  		This API is to input a formated string to file.  
 * PARAMETERS 
 *			fileHandle 	[IN]:a file handle give by ol_ffs_open
 *			fmt				[IN]:string format
 * RETURN VALUES
 *			int 
 * RETURN MESSAGE
 * 		 NONE
 * EXAMPLE
 *  				
 *****************************************************************************/
extern int  ol_ffs_fprintf(int fileHandle,const char *fmt,...);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_fscanf
 * DESCRIPTION 
 *  		This API is to get params form a formated string.  
 * PARAMETERS 
 *			fileHandle 	[IN]:a file handle give by ol_ffs_open
 *			fmt				[IN]:string format
 * RETURN VALUES
 *			int 
 * RETURN MESSAGE
 * 		 NONE
 * EXAMPLE
 *  				
 *****************************************************************************/
extern int ol_ffs_fscanf(int fileHandle,const char *fmt,...);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_gettotalspace
 * DESCRIPTION 
 *  		This API is to get the total file space.  
 * PARAMETERS 
 *			NONE
 * RETURN VALUES
 *			unsigned int,total file space.
 * RETURN MESSAGE
 * 		 NONE
 * EXAMPLE
 *  				
 *****************************************************************************/
extern unsigned long long ol_ffs_gettotalspace(char *path);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_getfreespace
 * DESCRIPTION 
 *  		This API is to get the free file space.  
 * PARAMETERS 
 *			NONE
 * RETURN VALUES
 *			unsigned int,free file space.
 * RETURN MESSAGE
 * 		 NONE
 * EXAMPLE
 *  				
 *****************************************************************************/
extern unsigned long long ol_ffs_getfreespace(char *path);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_getusedspace
 * DESCRIPTION 
 *  		This API is to get used file space.  
 * PARAMETERS 
 *			NONE
 * RETURN VALUES
 *			unsigned int,used file space.
 * RETURN MESSAGE
 * 		 NONE
 * EXAMPLE
 *  			
 *****************************************************************************/
extern unsigned long long ol_ffs_getusedspace(char *path);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_FFS_Format
 * DESCRIPTION 
 *  		This API is to get used file space.  
 * PARAMETERS 
 *			NONE
 * RETURN VALUES
 *			unsigned int,used file space.
 * RETURN MESSAGE
 * 		 NONE
 * EXAMPLE
 *  			
 *****************************************************************************/
extern int ol_ffs_format(char *path);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_createdir
 * DESCRIPTION 
 *  		This API is to create a directory.  
 * PARAMETERS 
 *		lpDirName		[IN]:The directory name of the directory you want to create
 * RETURN VALUES
 *		=0 : a directory created successfully
 *		other : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_ffs_createdir(char *lpDirName);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_deletedir
 * DESCRIPTION 
 *  		This API is to delect a directory.  
 * PARAMETERS 
 *		lpDirName		[IN]:The directory name of the directory you want to delect
 * RETURN VALUES
 *		=0 : a directory delected successfully
 *		other : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_ffs_deletedir(char *lpDirName);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_opendir
 * DESCRIPTION 
 *  		This API is to open a directory.  
 * PARAMETERS 
 *		lpDirName		[IN]:The directory name of the directory you want to open
 * RETURN VALUES
 *		>0 : a directory handle will be return
 *		other : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern unsigned int ol_ffs_opendir(char *lpDirName);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_readdir
 * DESCRIPTION 
 *  		This API is to read directory info from a opened directory.  
 * PARAMETERS 
 *		dirHandle							[IN]: a directory handle give by ol_ffs_open
 *		fs_info						[OUT]: a pointer to read directory info
 * RETURN VALUES
 *		=0 : read directory info successfully
 *		other : error
 * RETURN MESSAGE
 * 		 NONE
 * 
 *****************************************************************************/
extern int ol_ffs_readdir(unsigned int dirHandle, ol_PFS_FIND_DATA fsData);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_closedir
 * DESCRIPTION 
 *  		This API is to close a directory handle.  
 * PARAMETERS 
 *		dirHandle		[IN]: a directory handle give by ol_ffs_opendir
 * RETURN VALUES
 *		=0 : close directory successfully
 *		other : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_ffs_closedir(unsigned int dirHandle);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_setpos
 * DESCRIPTION 
 *  		This API is to set the location of the file.  
 * PARAMETERS 
 *		fileHandle		[IN]: a file handle give by ol_ffs_open
 *      pos             [IN]: a pointer to the location of the file.
 * RETURN VALUES
 *		=0 : setting the file location succeeded
 *		other : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_ffs_setpos(int fileHandle, int *pos);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_getpos
 * DESCRIPTION 
 *  		This API is to get the current location of the file.  
 * PARAMETERS 
 *		fileHandle		[IN]: a file handle give by ol_ffs_open
 *      pos             [OUT]: a pointer to the location of the file.
 * RETURN VALUES
 *		=0 : getting the file location succeeded.
 *		other : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_ffs_getpos(int fileHandle, int *pos);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_eof
 * DESCRIPTION 
 *  		This API is to tests the end-of-file identifier for a given stream.
 * PARAMETERS 
 *		fileHandle		[IN]: a file handle give by ol_ffs_open
 * RETURN VALUES
 *		=1 : is the end-of-file character.
 *		=0 : Not an end-of-file character.
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
 
extern int ol_ffs_eof(int fileHandle);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_ffs_error
 * DESCRIPTION 
 *  		This API is to gets the error identifier for the given stream.
 * PARAMETERS 
 *		fileHandle		[IN]: a file handle give by ol_ffs_open
 * RETURN VALUES
 *		error code : FS_ERROR
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_ffs_error(int fileHandle);

/*****************************************************************************
* DESCRIPTION
*    挂载外部flash到文件系统
*
	//C是nvm，不支持此种方式挂载, U是customer fs，默认情况下
* PARAMETERS
*   disk_sym    盘符，
*   patition_name   分区名，分区是用的customer fs命名的，那么需要填写此项，否则此项无需填写,  长度最大14字节
                    (目前固定是customer_fs，暂时请勿设置其他值)
*   is_format    挂载时候是否需要格式化,该参数暂时无效
    spi_port     外部flash使用的spi端口号, SSP_PORT 枚举
    spi_clock    typedef enum
				{
					SSP_CLOCK_13M = 0x0,
					SSP_CLOCK_26M = 0x1,
					SSP_CLOCK_52M = 0x2,
				} SSP_Clock;
    startaddr    文件系统的起始地址  （外部flash统一开头是0x90000000, 地址需要4K对齐)
    size         文件系统分区大小（需要至少4K的倍数）
    
* RETURN VALUES
*
*****************************************************************************/
int ol_extfs_init(char disk_sym, char *patition_name, unsigned char is_format, 
                      unsigned char spi_port, unsigned char spi_clock, 
                      unsigned int startaddr, unsigned int size);
					  
					  
					  
/*****************************************************************************
* DESCRIPTION
*    挂载外部flash到文件系统
*

	//C是nvm，U是customer fs，默认情况下
* PARAMETERS
*   disk_sym    盘符，如果是外部flash，并且以上两个盘符在项目中已存在的情况下，则不能占用以上盘符
*   patition_name   分区名，分区是用的customer fs或者nvm命名的，那么需要填写此项，否则此项无需填写
*   is_format    挂载时候是否需要格式化
    startaddr    文件系统的起始地址  （外部flash统一开头是0x90000000, 地址需要4K对齐)
    size         文件系统分区大小（需要至少4K的倍数）
    read         自行实现的spi读接口
    write        自行实现的spi写接口
    earse        自行实现的spi擦除接口
    
* RETURN VALUES
*
*****************************************************************************/

int ol_extfs_init_ex(char disk_sym, 
	 					  char *patition_name, 
	 					  unsigned char is_format, 
	 					  unsigned int startaddr, 
	 					  unsigned int size,
	 					  spi_nor_read_fun read,
	 					  spi_nor_write_fun write,
	 					  spi_nor_earse_fun earse);
						  
						  
#ifdef __cplusplus
}
#endif

#endif
