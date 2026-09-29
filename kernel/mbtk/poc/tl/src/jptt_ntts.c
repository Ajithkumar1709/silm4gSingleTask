#include <stdio.h>
#include <string.h>
#include "jptt_ntts.h"
#include "OS_Wrapper.h"
#include "jptt_debug.h"

static  char _TTS_SERVER[] = "114.55.225.236";
static  int  _TTS_PORT = 3332;
static  char FTP_SERVER[] = "114.55.225.236";
static  int  FTP_PORT = 21;


/*
**
*/
extern void set_service_ip(int type, char *addr, int port) {
    if (type == 1) {    // tts
        strcpy(_TTS_SERVER, addr);
        _TTS_PORT = port;
    }
    else if (type == 2) {  // ftp update
        strcpy(FTP_SERVER, addr);
        FTP_PORT = port;
    }
    (void)_TTS_PORT;
    (void)FTP_PORT;
}

extern int ntts_find_wave(const char *buf, int len) {
    return -1;
}

/*
**  fnNo = 0, stop current file.
**  fnNo may change during read.
*/
extern int ntts_get_wave(int fnNo, char *obuf, int *olen) {
    return 0;
}


