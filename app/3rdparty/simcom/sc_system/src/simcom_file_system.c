#include <stdlib.h>
#include <string.h>
#include "simcom_file_system.h"
#include "ol_flash_fs.h"
#include "mbtk_err.h"

extern void open_is_app_ota_package(int handle);
extern void close_is_app_ota_package(void);

int sAPI_fformat(char *vol)
{
    simcom_api_not_support();
    return 0;
}

SCFILE *sAPI_fopen(const char *fname, const char *mode)
{
    int handle;
    SCFILE *file_hdl = NULL;

    handle = ol_ffs_open((char *)fname, (char *)mode);
    if(handle >= 0)
    {
        file_hdl = (SCFILE *)malloc(sizeof(SCFILE));
        memset(file_hdl, 0x0, sizeof(SCFILE));
        file_hdl->fatfs_file_handle = handle;
        
        open_is_app_ota_package(handle);
    }
    return file_hdl;
}

int sAPI_fclose(SCFILE *fp)
{
    int ret;

    ret = ol_ffs_close(fp->fatfs_file_handle);

    if(ret == 0)
    {
        free(fp);
    }
    close_is_app_ota_package();
    return ret;
}

int sAPI_fwrite(const void *buffer, size_t size, size_t num, SCFILE *fp)
{
    return ol_ffs_write(fp->fatfs_file_handle, (char *)buffer, size * num);
}

int sAPI_fread(void *buffer, size_t size, size_t num, SCFILE *fp)
{
    return ol_ffs_read(fp->fatfs_file_handle, buffer, size * num);
}

int sAPI_fseek(SCFILE *fp, long offset, int whence)
{
    return ol_ffs_seek(fp->fatfs_file_handle, offset, whence);
}

long sAPI_ftell(SCFILE *fp)
{
    simcom_api_not_support();
    return 0;
}

int sAPI_frewind(SCFILE *fp)
{
    simcom_api_not_support();
    return 0;
}

int sAPI_fsize(SCFILE *fp)
{
    return ol_ffs_getsize_ex(fp->fatfs_file_handle);
}

int sAPI_fsync(SCFILE *fp)
{
    return ol_ffs_sync(fp->fatfs_file_handle);
}

int sAPI_mkdir(const char *path, unsigned int mode)
{
    simcom_api_not_support();
    return 0;
}

SCDIR *sAPI_opendir(const char *path)
{
    simcom_api_not_support();
    return 0;
}

int sAPI_closedir(SCDIR *dirp)
{
    simcom_api_not_support();
    return 0;
}

struct dirent *sAPI_readdir(SCDIR *dirp)
{
    simcom_api_not_support();
    return 0;
}

int sAPI_seekdir(SCDIR *dirp, unsigned long offset)
{
    simcom_api_not_support();
    return 0;
}

int sAPI_telldir(SCDIR *dirp)
{
    simcom_api_not_support();
    return 0;
}

int sAPI_remove(const char *fname)
{
    return ol_ffs_delete((char *)fname);
}
int sAPI_rename(const char *oldpath, const char *newpath)
{
    simcom_api_not_support();
    return 0;
}

int sAPI_access(const char *path, int mode)
{
    simcom_api_not_support();
    return 0;
}

int sAPI_stat(const char *path, struct dirent *info)
{
    simcom_api_not_support();
    return 0;
}

long long sAPI_GetSize(char *disc)
{
    simcom_api_not_support();
    return 0;
}

long long sAPI_GetFreeSize(char *disc)
{
    return ol_ffs_getfreespace(disc);
}
long long sAPI_GetUsedSize(char *disc)
{
    simcom_api_not_support();
    return 0;
}


