#ifndef _MBTK_FLASH_FILE_SYSTEM_H_
#define _MBTK_FLASH_FILE_SYSTEM_H_



#define OL_FS_FILE_NAME_LEN 128
//err_no
typedef enum
{
	FILE_ERR_NONE = 0,
	FILE_ERR_EOF = -1,
	FILE_ERR_PARAM = -2,
	FILE_ERR_NOT_EXIST = -3,
	FILE_ERR_ACCESS = -4,
	FILE_ERR_OPEN = -5,
	FILE_ERR_READ = -6,
	FILE_ERR_WRITE = -7,
	

}MBTK_FILE_ERR;

//for file_seek <whence>
#define MBTK_FS_SEEK_SET 0
#define MBTK_FS_SEEK_CUR 1
#define MBTK_FS_SEEK_END 2


//for filefind info
typedef struct
{
	char 	file_name[OL_FS_FILE_NAME_LEN + 1];
	int   	time;          /* updated time stamp when modified */
	int  	date;          /* updated date stamp when modified */
	int  	size;          /* size of file data in bytes */
}ol_FS_FIND_DATA, *ol_PFS_FIND_DATA;


/********************************
*for file_open <mode> like
*		"rb"		read only	
*		"rb+"	read and write
*		"wb"		create,read,write,truncate
*		"wb+"	create,read,write,truncate
*		"ab"		create,read,write,append
*		"ab+"	create,read,write,append
*********************************/

int ol_FFS_Open(char* lpFileName, char * mode);
int ol_FFS_Read(int fileHandle, char *readBuffer, unsigned int numberOfBytesToRead);
int ol_FFS_Write(int fileHandle, char *writeBuffer, unsigned int numberOfBytesToWrite);
int ol_FFS_Seek(int  fileHandle, long offset, int whence);
int ol_FFS_Close(int fileHandle);
int ol_FFS_Ftell(int fileHandle);
int ol_FFS_GetSize(char *lpFileName);
int ol_FFS_Delete(char *lpFileName);
int ol_FFS_Rename(char *lpFileName, char *newLpFileName);
int ol_FFS_FindFirst(char *lpFileName, ol_PFS_FIND_DATA pFindData);
int ol_FFS_FindNext(ol_PFS_FIND_DATA pFindData);
int ol_FFS_FindClose(void);
int ol_FFS_Format(char *path);
unsigned long long ol_FFS_GetFreeSpace(char *path);
unsigned long long ol_FFS_GetUsedSpace(char *path);
unsigned long long ol_FFS_GetTotalSpace(char *path);
int ol_FFS_Fprintf(int fileHandle,const char *fmt,...);
int ol_FFS_Fscanf(int fileHandle,const char *fmt,...);


int ol_FFS_CreateDir(char *lpDirName);
int ol_FFS_DeleteDir(char *lpDirName);
unsigned int ol_FFS_OpenDir(char *lpDirName);
int ol_FFS_ReadDir(unsigned int dirHandle, ol_PFS_FIND_DATA fsData);
int ol_FFS_CloseDir(unsigned int dirHandle);

#endif
