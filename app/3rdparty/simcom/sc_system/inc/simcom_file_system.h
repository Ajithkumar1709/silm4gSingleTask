#ifndef SIMCOM_FILE_SYSTEM_H
#define SIMCOM_FILE_SYSTEM_H

#include "simcom_os.h"
#include "lfs.h"

/****************************************************************************************************************************************************

General rules for naming (both directories and files):

    * The name is a ascii string.
    
    * The length of actual fully qualified names of files(C:/) can not exceed 112. 
    
    * The length of actual fully qualified names of directories and files(D:/) can not exceed 250.
    
    * Directory and file names can not include the following characters:    \  :  *  ?  “  <  >  |  ,  ;
    
    * Between directory name and file/directory name, use character “/” as list separator, so it can not appear in directory name or file name.

****************************************************************************************************************************************************/



/***************************************************SCfsReturnCode**************************************************************************************
****************************************************************************************************************************************************/
#define MAX_FULL_NAME_LENGTH    255

typedef enum
{
    LOC_FLASH,
    LOC_EXT_FLASH,
    LOC_SD_CARD,
} SC_FILE_LOCATION;

typedef struct dirent_t
{
    unsigned char type;
    unsigned long size;
    char name[MAX_FULL_NAME_LENGTH];
}dirent_t;

typedef struct
{
    void *disk;
    lfs_file_t file;
    SC_FILE_LOCATION loc;
    unsigned int fatfs_file_handle;
} SCFILE;

typedef struct
{
    void *disk;
    lfs_dir_t dir;
    struct lfs_info info;
    SC_FILE_LOCATION loc;
#ifdef FEATURE_SIMCOM_SD_CARD
    unsigned int handle;
    char path[MAX_FULL_NAME_LENGTH];
    int fileIndex;
#endif
} SCDIR;


int sAPI_fformat(char *vol);
SCFILE *sAPI_fopen(const char *fname, const char *mode);
int sAPI_fclose(SCFILE *fp);
int sAPI_fwrite(const void *buffer, size_t size, size_t num, SCFILE *fp);
int sAPI_fread(void *buffer, size_t size, size_t num, SCFILE *fp);
int sAPI_fseek(SCFILE *fp, long offset, int whence);
long sAPI_ftell(SCFILE *fp);
int sAPI_frewind(SCFILE *fp);
int sAPI_fsize(SCFILE *fp);
int sAPI_fsync(SCFILE *fp);
int sAPI_mkdir(const char *path, unsigned int mode);
SCDIR *sAPI_opendir(const char *path);
int sAPI_closedir(SCDIR *dirp);
struct dirent *sAPI_readdir(SCDIR *dirp);
int sAPI_seekdir(SCDIR *dirp, unsigned long offset);
int sAPI_telldir(SCDIR *dirp);
int sAPI_remove(const char *fname);
int sAPI_rename(const char *oldpath, const char *newpath);
int sAPI_access(const char *path, int mode);
int sAPI_stat(const char *path, struct dirent *info);
long long sAPI_GetSize(char *disc);
long long sAPI_GetFreeSize(char *disc);
long long sAPI_GetUsedSize(char *disc);

#endif


