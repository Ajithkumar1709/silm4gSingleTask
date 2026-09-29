#include <stdio.h>
#include <string.h>

#include "osa.h"
#include "asserts.h"
#include "jptt_debug.h"

extern int  jptt_get_ver(void);
extern int  jptt_is_running(void);
extern void joem_on_poc_atc(char *rbuf, int rlen);

static void *UI_job = NULL;

static char          reply_buff[2048];   // many lines seperated with 0d0a
static volatile int  reply_leng = 0;    // total length
static OSMutexRef    rply_mtx;

/*
** UI -> POC transfer OS References
*/
void tl_poc_transfer_msgQ(void *UIQ, void **PocQ) {
    UI_job = UIQ;
    
    DEBUG_I("jptt ver = %d", jptt_get_ver());
    if (PocQ != NULL)
        *PocQ = UI_job;
}

/*
** UI atc -> POC
*/
void tl_poc_set_atc(char *abuf, int alen) {
    joem_on_poc_atc(abuf, alen);
}

/*
** POC reply -> UI, ui get
** input buffer length is fixed and same as reply_buff
*/
void tl_poc_get_reply(char *rbuf, int rlen) {
    OSA_STATUS status;

    status = OSAMutexLock(rply_mtx, OS_SUSPEND);
    ASSERT(status == OS_SUCCESS);

    if (reply_leng > 0) {
        strncpy(rbuf, reply_buff, reply_leng);
        rbuf[reply_leng] = '\0';
        //memset(reply_buff, 0, sizeof(reply_buff));
        reply_leng = 0;
    }

    status = OSAMutexUnlock(rply_mtx);
    ASSERT(status == OS_SUCCESS);
}

/*
** POC reply -> UI, notify
*/
extern void emcu_on_poc_ack(const char *ack, int alen) {
    OSA_STATUS status;

    if (reply_leng > sizeof(reply_buff)/2) {
        OSATaskSleep(20/5);
    }

    status = OSAMutexLock(rply_mtx, OS_SUSPEND);
    ASSERT(status == OS_SUCCESS);
    
    if (reply_leng+alen < sizeof(reply_buff) - 1) {
        if (UI_job != NULL) {
            strncpy(reply_buff+reply_leng, ack, alen);
            if (reply_leng == 0)
                OSASemaphoreRelease((OSSemaRef)UI_job);
            reply_leng += alen;
            reply_buff[reply_leng] = '\0';  // ncpy not ended '\0'
        } else {
            DEBUG_I("no UI job");
        }
    } else {
        DEBUG_I("poc reply %d too long, dropped.", alen);
    }

    status = OSAMutexUnlock(rply_mtx);
    ASSERT(status == OS_SUCCESS);
}

extern int plnk_init(const char *enterprise) {
    OSA_STATUS status;

    DEBUG_I("emcu init.");

    reply_leng = 0;
    status = OSAMutexCreate(&rply_mtx, OS_FIFO);
    ASSERT(status == OS_SUCCESS);

    while (UI_job == NULL) {
        OSATaskSleep(1);    // wait application set UI_job
    }

    return 0;
}

extern void plnk_deinit(void) {
    DEBUG_I("emcu de-init.");
    UI_job = NULL;

    OSAMutexDelete(&rply_mtx);
}

