#include <stdio.h>
#include <string.h>

#ifdef OS_LINUX
 #include <unistd.h>
 #include <pthread.h>
 #include <semaphore.h>
 #include <assert.h>
#else
 #include "osa.h"
 #include "asserts.h"
#endif

#include "jptt_debug.h"

void tl_poc_transfer_msgQ(void *UIQ, void **PocQ);
void tl_poc_set_atc(char *abuf, int alen);
void tl_poc_get_reply(char *rbuf, int rlen);

#ifdef OS_LINUX
 static  pthread_t     tid_lnk;
 static  sem_t         sem_rply;
#else
 static  OSTaskRef     tid_lnk;
 static  unsigned char *plnk_stk;
 #define LNK_STK_SZ    (4096+3072)  // add 3K for http download

 static  OSSemaRef     sem_rply;
#endif

static  volatile int   poc_init_OK  = 0;
static  void  (*on_poc_ack)(char *, int) = NULL;


/*
** POC reply -> UI, ui get
*/
static char *get_1_line(char *rbuf, int *slen) {
    int off;
    
	off = 0;
    *slen = 0;
    while (rbuf[off]=='\r' || rbuf[off]=='\n') {
        off ++;
        if (off >= strlen(rbuf))
            return rbuf+off;
    }

    while(rbuf[off+(*slen)]!='\r' && rbuf[off+(*slen)]!='\n') {
        (*slen) ++;
        if (off+(*slen) >= strlen(rbuf))
            return rbuf+off;
    }

    return rbuf+off;
}

#ifdef OS_LINUX
 void *thrd_mklnk(void * argv) {
#else
 void thrd_mklnk(void * argv) {
#endif
    void *PocQ;
    static char rbuf[2048];  // size same as reply_buff[2048]
    
#ifdef OS_LINUX
    sem_init(&sem_rply, 0, 0);
    tl_poc_transfer_msgQ((void *)&sem_rply, &PocQ);
    DEBUG_I("set 1, return: 2");
#else
    OS_STATUS status;
    status = OSASemaphoreCreate(&sem_rply, 0, OSA_FIFO);
    ASSERT(status == OS_SUCCESS);
    tl_poc_transfer_msgQ((void *)sem_rply, &PocQ);
    DEBUG_I("set %x, return: %x", (unsigned int)sem_rply, (unsigned int)PocQ);
#endif

    poc_init_OK = 1;
    
    while (1) {
        char *p_hd;
        int rlen;

#ifdef OS_LINUX
        sem_wait(&sem_rply);
#else
        OSASemaphoreAcquire(sem_rply, OS_SUSPEND);
#endif
        memset(rbuf, 0, sizeof(rbuf));
        tl_poc_get_reply(rbuf, sizeof(rbuf));
        DEBUG_I("emcu buff get: %u bytes", (unsigned int)strlen(rbuf));
        
        for (p_hd=rbuf; p_hd-rbuf<strlen(rbuf); ) {
            p_hd = get_1_line(p_hd, &rlen);
            if (rlen >= 2 && on_poc_ack != NULL)   // "OK" is shortest
                on_poc_ack(p_hd, rlen);            // do not need string copy.
            
            p_hd = p_hd+rlen;
        }
    };
#ifdef OS_LINUX
    sem_destroy(&sem_rply);
    return NULL;
#else
//    OSASemaphoreDelete(sem_rply);
//    return;
#endif
}

extern void jemcu_atc_callback(void (*cb)(char *str, int rlen)) {
#ifdef OS_LINUX
    int res;
    
    on_poc_ack = cb;
    
    res = pthread_create(&tid_lnk, NULL, thrd_mklnk, NULL);
    assert(res == 0);

    do {
        usleep(20*1000);
    } while (0 == poc_init_OK);
#else
    OS_STATUS res;

    on_poc_ack = cb;

    plnk_stk = OsaMemAlloc(NULL, LNK_STK_SZ);
    ASSERT(plnk_stk != NULL);
    res = OSATaskCreate(&tid_lnk, plnk_stk, LNK_STK_SZ, 1, "TMPLK", thrd_mklnk, NULL);
    ASSERT(res == OS_SUCCESS);
    
    while (!poc_init_OK) {
        OSATaskSleep(100/5);
    }
#endif
    
    DEBUG_I("jemcu poc link init OK %d", poc_init_OK);
}

/*
** UI atc -> POC
*/
extern void jemcu_atc_send(char *sbuf, int slen) {
    if (!!poc_init_OK) {
        tl_poc_set_atc(sbuf, slen);
    }
}
