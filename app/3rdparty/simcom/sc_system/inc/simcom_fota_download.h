#ifndef _SC_FOTA_DOWNLOAD_H_
#define _SC_FOTA_DOWNLOAD_H_

 
#define FOTA_SERVER_CONTEXT_STRLEN	512

typedef struct SC_FotaApiParam{
    char host[FOTA_SERVER_CONTEXT_STRLEN];
    char username[FOTA_SERVER_CONTEXT_STRLEN];
    char password[FOTA_SERVER_CONTEXT_STRLEN];
    unsigned char mode; /*0: ftp, 1: http*/
    void *sc_fota_cb;
}SC_FotaApiParam;

typedef struct {
    int enable;
    int stage;
}SC_MiniSysStatus;

int sAPI_FotaServiceBegin(void* pram);
void sAPI_GetMiniSysStatus(SC_MiniSysStatus *MiniSysStatus);


#endif
