#ifndef __APP_UPDATE_H__
#define __APP_UPDATE_H__

typedef struct {
    void *info;
}SCAppPackageInfo;

int sAPI_AppPackageOpen(char *mode);
int sAPI_AppPackageWrite(char * data, unsigned int size);
int sAPI_AppPackageRead(char * data, unsigned int size);
int sAPI_AppPackageClose(void);
//SCAppDwonLoadReturnCode sApi_AppDownload(SCAppDownloadPram *pram);
int sAPI_AppPackageCrc (SCAppPackageInfo *pInfo);

#endif
