#include <stdbool.h>
#include <string.h>
#include <stddef.h>
#include "simcom_app_updater.h"
#include "mbtk_err.h"
#include "ol_flash_fs.h"
#include "ol_fota.h"

bool is_app_ota_package = false;
unsigned int mbtk_ota_package_size = 0;

void open_is_app_ota_package(int handle)
{
    
    char data[12] = {0};
    ol_ffs_read(handle, data, 12);
	if(strncmp(data,"Marvell_FBF",strlen("Marvell_FBF")) ==0)
    {
        is_app_ota_package = true;
        ol_ffs_seek(handle, 0, OL_FS_SEEK_SET);
        mbtk_ota_package_size = ol_ffs_getsize_ex(handle);
    }
    ol_ffs_seek(handle, 0, OL_FS_SEEK_SET);
}

void close_is_app_ota_package(void)
{
    is_app_ota_package = false;
    mbtk_ota_package_size = 0;
}


int sAPI_AppPackageOpen(char *mode)
{
    int ret = 0;
    ret = ol_fota_context_init(NULL, mbtk_ota_package_size, false, NULL);
    return ret;
}

int sAPI_AppPackageWrite(char * data, unsigned int size)
{
    if(size > 0)
        return ol_fota_pkg_write(data, size, mbtk_ota_package_size);
    return 0;
}

int sAPI_AppPackageRead(char * data, unsigned int size)
{
    simcom_api_not_support();
    return 0;
}

int sAPI_AppPackageClose(void)
{
    return ol_fota_pkg_flush_flash();
}
//SCAppDwonLoadReturnCode sApi_AppDownload(SCAppDownloadPram *pram);
int sAPI_AppPackageCrc (SCAppPackageInfo *pInfo)
{
    if(ol_fota_image_verify() != 0)
        return -1;
    ol_fota_context_deinit();
    return 0;
}

