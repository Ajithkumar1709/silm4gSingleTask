#include <stdio.h>
#include <string.h>
#include "osa.h"
#include "asserts.h"

#include "OS_Wrapper.h"
#include "jptt_debug.h"


#define OS_TICK   (5)

#define U_DIR_PATH          "/tourlink"

/*
**  golobal defines
*/

typedef struct {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
} rtc_time_t;

void lib_oem_set_rtc_time(rtc_time_t *t);

static int days_of_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char fbuff[64];



// mutex
#define MUTEX_MAX  (16)

typedef struct {
    int occupied;
    OSMutexRef mtx;
} OS_Wrap_mutex_t;

static OS_Wrap_mutex_t os_wrap_mtx[MUTEX_MAX];

// semaphore
#define SEMAPHORE_MAX (4)

typedef struct {
    int occupied;
    OSSemaRef sema;
} OS_Wrap_semaphore_t;

static OS_Wrap_semaphore_t os_wrap_sema[SEMAPHORE_MAX];


// thread
#define THREAD_MAX       (8)
#define THRD_MSG_NORMAL  (70)
#define THRD_MSG_HIGH    (50)

typedef struct {
    int occupied;
    OSTaskRef tid;
    unsigned int stk_sz;
    unsigned char *pstk;
} OS_Wrap_thread_t;

static OS_Wrap_thread_t  os_wrap_thrd[THREAD_MAX];

// timer
#define JPTT_TIMER_TOTAL (13)  // 1 RTC + 12 ordinary timer.

struct OS_Wrap_timer_rec {
    int no;
    OSTimerRef tid;
    int valid;
};


// RTC timer No.=0, others = 1~12
struct  OS_Wrap_timer_rec os_wrap_timer_list[JPTT_TIMER_TOTAL] = {{0, 0, 0}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}, \
                                                                  {4, 0, 0}, {5, 0, 0}, {6, 0, 0}, {7, 0, 0}, \
                                                                  {8, 0, 0}, {9, 0, 0}, {10,0, 0}, {11,0, 0}, \
                                                                  {12,0, 0}};

void (*on_timeout_handler)(UINT32 tno) = NULL;

/*
**
**
**
*/
static int jfs_init(void) {
    unsigned short tldir;
    int res;

    tldir = FDI_OpenDir(U_DIR_PATH);
    if (tldir != 0) {
        FDI_CloseDir(tldir);
        return 0;
    }

    res = FDI_MakeDir(U_DIR_PATH);
    DEBUG_D("mkdir %s ret: %d", U_DIR_PATH, res);
    return res;
}

extern int OS_Wrap_init_system(void) {
    OSA_STATUS status;
    int i;
    
    for (i=0; i<MUTEX_MAX; i++) {
        os_wrap_mtx[i].occupied = 0;
        status = OSAMutexCreate(&os_wrap_mtx[i].mtx, OS_FIFO);
        ASSERT(status == OS_SUCCESS);
    }

    for (i=0; i<SEMAPHORE_MAX; i++) {
        os_wrap_sema[i].occupied = 0;
        status = OSASemaphoreCreate(&os_wrap_sema[i].sema, 0, OSA_FIFO);
        ASSERT(status == OS_SUCCESS);
    }
    
    for (i=0; i<THREAD_MAX; i++) {
        os_wrap_thrd[i].occupied = 0;
        os_wrap_thrd[i].pstk = NULL;
    }

    jfs_init();
    
    return 0;
}

extern void OS_Wrap_deinit_system(void) {
    OSA_STATUS status;
    int i;

    for (i=0; i<MUTEX_MAX; i++) {
        os_wrap_mtx[i].occupied = -1;
        status = OSAMutexDelete(os_wrap_mtx[i].mtx);
        ASSERT(status == OS_SUCCESS);
    }

    for (i=0; i<SEMAPHORE_MAX; i++) {
        os_wrap_sema[i].occupied = -1;
        status = OSASemaphoreDelete(os_wrap_sema[i].sema);
        ASSERT(status == OS_SUCCESS);
    }
}

/*
** mutex functions
**
*/
extern void *OS_Wrap_get_mutex() {
    int i;
    
    for (i=0; i<MUTEX_MAX; i++) {
        if (0 == os_wrap_mtx[i].occupied) {
            os_wrap_mtx[i].occupied = 1;
            return (void *)&os_wrap_mtx[i].mtx;
        }
    }
    ASSERT(0);
    return NULL;
}

extern void OS_Wrap_ret_mutex(void *mtx) {
    int i;
    
    for (i=0; i<MUTEX_MAX; i++) {
        if (mtx == &os_wrap_mtx[i].mtx) {
            os_wrap_mtx[i].occupied = 0;
            return;
        }
    }
}

// these 3 functions return 0 for SUCCESS
extern int OS_Wrap_mutex_lock(void *mtx) {
    OSA_STATUS status;

    status = OSAMutexLock(*((OSMutexRef *)mtx), OS_SUSPEND);
    ASSERT(status == OS_SUCCESS);
    return 0;
}

extern int OS_Wrap_mutex_trylock(void *mtx) {
    OSA_STATUS status;

    status = OSAMutexLock(*((OSMutexRef *)mtx), OS_NO_SUSPEND);
    //ASSERT(status == OS_SUCCESS);
    DEBUG_D("mutex trylock ret: %d", status);
    return (status==OS_SUCCESS)? 0:-1;
}

extern int OS_Wrap_mutex_unlock(void *mtx) {
    OSA_STATUS status;

    status = OSAMutexUnlock(*((OSMutexRef *)mtx));
    ASSERT(status == OS_SUCCESS);
    return 0;
}

/*
** semaphore functions
**
*/
extern void *OS_Wrap_get_semaphore() {
    int i;
    
    for (i=0; i<SEMAPHORE_MAX; i++) {
        if (0 == os_wrap_sema[i].occupied) {
            os_wrap_sema[i].occupied = 1;
            return (void *)&os_wrap_sema[i].sema;
        }
    }
    ASSERT(0);
    return NULL;
}

extern void OS_Wrap_ret_semaphore(void *sema) {
    int i;
    
    for (i=0; i<SEMAPHORE_MAX; i++) {
        if (sema == &os_wrap_sema[i].sema) {
            os_wrap_sema[i].occupied = 0;
            return;
        }
    }
}

extern int OS_Wrap_semaphore_post(void *sema) {
    OSA_STATUS status;

    status = OSASemaphoreRelease(*(OSSemaRef *)sema);
    ASSERT(status == OS_SUCCESS);
    return 0;
}

extern int OS_Wrap_semaphore_wait(void *sema) {
    OSA_STATUS status;

    status = OSASemaphoreAcquire(*(OSSemaRef *)sema, OS_SUSPEND);
    ASSERT(status == OS_SUCCESS);
    return 0;
}

/*
**
** Time Interfaces
**
*/
extern unsigned long current_time_millis() {
    return (OSAGetTicks() * OS_TICK);
}

extern void OS_Wrap_usleep(int us) {
    OSATaskSleep(us / 1000 / OS_TICK);
}

static rtc_time_t mkwallclock(unsigned int sec) {
    rtc_time_t wc0;

    wc0.tm_sec = sec % 60;
    wc0.tm_min = (sec / 60) % 60;
    wc0.tm_hour = (sec / 3600) % 24;

    wc0.tm_mday = (int)(sec / 86400);
    wc0.tm_wday = 4 + (wc0.tm_mday % 7);    /* 1970-1-1 is thursday. 0 = sunday */

    /* counting years */
    for (wc0.tm_year=1970; wc0.tm_mday>=0; wc0.tm_year++) {
        int is_leapy;
        is_leapy = !!((wc0.tm_year%4) == 0 && (wc0.tm_year%100) != 0);
        if (wc0.tm_mday - (is_leapy? 366:365) <= 0) {
            days_of_month[1] = is_leapy? 29:28;
            break;
        }
        wc0.tm_mday -= (is_leapy? 366:365);
    }

    /* count month and days */
    for (wc0.tm_mon=1; wc0.tm_mon<=12; wc0.tm_mon++) {
        if (wc0.tm_mday - days_of_month[wc0.tm_mon-1] <= 0) {
            break;
        }
        wc0.tm_mday -= days_of_month[wc0.tm_mon-1];
    }

    return wc0;
}

extern unsigned int mk_linux_ts(int wc1_year, int wc1_mon, int wc1_day, int wc1_hour, int wc1_minu, int wc1_sec) {
    unsigned int lsec;
    int days;
    rtc_time_t wc0;
    
    days = 0;

    for (wc0.tm_year=1970; wc0.tm_year<=wc1_year; wc0.tm_year++) {
        int is_leapy;
        is_leapy = !!((wc0.tm_year%4) == 0 && (wc0.tm_year%100) != 0);
        if (wc0.tm_year == wc1_year) {
            days_of_month[1] = is_leapy? 29:28;
            break;
        }
        days += is_leapy? 366:365;
    }
    
    for (wc0.tm_mon=1; wc0.tm_mon<wc1_mon; wc0.tm_mon++) {
        days += days_of_month[wc0.tm_mon-1];
    }
    
    days += wc1_day;
    lsec = days*24*60*60;
    lsec += wc1_hour*60*60;
    lsec += wc1_minu*60;
    lsec += wc1_sec;
    
    return lsec;
}

static char g_wallclock_inited = 0;
char OS_Wrap_get_clc_set()
{
	return g_wallclock_inited;
}

extern void OS_Wrap_set_wallclock(unsigned int s) {
    rtc_time_t wc;
    int res = -1;

    DEBUG_D(" timer %d ", s);

    wc = mkwallclock(s);
   // lib_oem_set_rtc_time(&wc);
   
    DEBUG_D(" timer %d s: %d", s);
    PMIC_RTC_SetTime(&wc,0);
    g_wallclock_inited = 1;
}

extern unsigned int OS_Wrap_get_wallclock() {
    return 0;
}


/*
** Timer Interfaces
** Linx: for RTC_TIMER type: CLOCK_REALTIME_ALARM ( = 8) is used.
** 
*/
extern void OS_Wrap_set_timeout_handler(void (*h)(int)) {
    on_timeout_handler = (void (*)(UINT32))h;
}

extern int OS_Wrap_create_timer(int tno) {
    OS_STATUS res;
    
    if (tno < 0 || tno >= JPTT_TIMER_TOTAL)
        return -1;

    res = OSATimerCreate(&os_wrap_timer_list[tno].tid);
    ASSERT(res == OS_SUCCESS);
    DEBUG_D("timer_%d create ret: %d", tno, res);
    return 0;
}

extern int OS_Wrap_arm_timer(int tno, int msec) {
    OS_STATUS res;
    
    if (tno < 0 || tno >= JPTT_TIMER_TOTAL)
        return -1;
    
    if (os_wrap_timer_list[tno].tid == 0) {
        DEBUG_E("arm timer meet invalid timer: %d", tno);
        return -1;
    }
    
    res = OSATimerStart(os_wrap_timer_list[tno].tid,
                        (msec+OS_TICK-1)/OS_TICK,
                        0,
                        on_timeout_handler,
                        (unsigned int )tno);
    ASSERT(res == OS_SUCCESS);

    return 0;
}

extern int OS_Wrap_disarm_timer(int tno) {
    OS_STATUS res;
    
    if (tno < 0 || tno >= JPTT_TIMER_TOTAL)
        return -1;
    
    if (os_wrap_timer_list[tno].tid == 0) {
        DEBUG_E("arm timer meet invalid timer: %d", tno);
        return -1;
    }

    res = OSATimerStop(os_wrap_timer_list[tno].tid);
    ASSERT(res == OS_SUCCESS);

    return 0;
}

extern int OS_Wrap_delete_timer(int tno) {
    OS_STATUS res;
    
    if (tno < 0 || tno >= JPTT_TIMER_TOTAL)
        return -1;

    res = OSATimerDelete(os_wrap_timer_list[tno].tid);
    ASSERT(res == OS_SUCCESS);
    os_wrap_timer_list[tno].tid = NULL;

    return 0;
}

/*
**  thread interface
*/
static void os_thrd_init_stack(OS_Wrap_thread_t* thrd0, unsigned int stck_sz) {
    thrd0->pstk = OsaMemAlloc(NULL, stck_sz);
    ASSERT(thrd0->pstk != NULL);
    thrd0->stk_sz = stck_sz;
    // fill with empty-flag '0xef'
    memset(thrd0->pstk, 0xef, stck_sz);
}

static void os_thrd_chk_stack(int idx, unsigned char *pstk, unsigned int stk_sz) {
    int i;

    for (i=0; i<stk_sz/4; i+=4) {
        if (!(*(pstk+4*i)==0xef && *(pstk+4*i+1)==0xef && *(pstk+4*i+2)==0xef && *(pstk+4*i+3)==0xef)) 
            break;
    }

    DEBUG_I("thrd_%d: %d / %u empty, is 0x%x%x%x%x.", idx, i, stk_sz, (*pstk)&0xff, (*(pstk+1))&0xff, (*(pstk+2))&0xff, (*(pstk+3))&0xff);
}

extern void * OS_Wrap_create_thread_with_prio(void (*func)(void *), void *param, unsigned int stack_sz, int prio) {
    OS_STATUS res;
    char tname[6];
    int i;
    
    for (i=0; i<THREAD_MAX; i++) {
        if (os_wrap_thrd[i].occupied == 0) {
            os_wrap_thrd[i].occupied = 1;
            os_thrd_init_stack(&os_wrap_thrd[i], stack_sz);
            memset(tname, 0, sizeof(tname));
            sprintf(tname, "JT%d", i);
            res = OSATaskCreate(&os_wrap_thrd[i].tid, os_wrap_thrd[i].pstk, stack_sz, prio==1? THRD_MSG_HIGH:THRD_MSG_NORMAL, tname, func, param);
            ASSERT(res == OS_SUCCESS);
            DEBUG_D("thrd_%d created. stack=%u", i, stack_sz);
            return &os_wrap_thrd[i].tid;
        }
    }
    ASSERT(0);
    return NULL;
}

extern void * OS_Wrap_create_thread(void (*func)(void *), void *param, unsigned int stack_sz) {
    OS_STATUS res;
    char tname[6];
    int i;
    
    for (i=0; i<THREAD_MAX; i++) {
        if (os_wrap_thrd[i].occupied == 0) {
            os_wrap_thrd[i].occupied = 1;
            os_thrd_init_stack(&os_wrap_thrd[i], stack_sz);
            memset(tname, 0, sizeof(tname));
            sprintf(tname, "JT%d", i);
            res = OSATaskCreate(&os_wrap_thrd[i].tid, os_wrap_thrd[i].pstk, stack_sz, THRD_MSG_NORMAL, tname, func, param);
            ASSERT(res == OS_SUCCESS);
            DEBUG_D("thrd_%d created. stack=%u", i, stack_sz);
            return &os_wrap_thrd[i].tid;
        }
    }
    ASSERT(0);
    return NULL;
}

extern void OS_Wrap_thread_check_stack() {
    int i;
    for (i=0; i<THREAD_MAX; i++) {
        if (os_wrap_thrd[i].occupied == 1) {
            os_thrd_chk_stack(i, os_wrap_thrd[i].pstk, os_wrap_thrd[i].stk_sz);
        }
    }
}

extern void OS_Wrap_thread_change_priority(void *tid, int newp) {
    int i;
    UINT8 oldp;

    for (i=0; i<THREAD_MAX; i++) {
        if (os_wrap_thrd[i].occupied && (void *)&os_wrap_thrd[i].tid==tid) {
            OSATaskChangePriority(os_wrap_thrd[i].tid, newp, &oldp);
            return;
        }
    }
    ASSERT(0);
}

extern void OS_Wrap_thread_yield() {
    OSATaskYield();
}

static int os_thread_delete(int tno) {
    OS_STATUS status;
    
    status = OSATaskDelete(os_wrap_thrd[tno].tid);
    ASSERT(status == OS_SUCCESS);
    os_wrap_thrd[tno].tid = NULL;
    OsaMemFree(os_wrap_thrd[tno].pstk);
    os_wrap_thrd[tno].pstk = NULL;
    return OS_SUCCESS;
}

extern int OS_Wrap_thread_cancel(void *tid) {
    int i;

    for (i=0; i<THREAD_MAX; i++) {
        if (os_wrap_thrd[i].occupied && (void *)&os_wrap_thrd[i].tid==tid) {
            os_thread_delete(i);
            os_wrap_thrd[i].occupied = 0;
            return 0;
        }
    }

    return -1;
}

extern int OS_Wrap_thread_join(void *tid) {
    int i;

    for (i=0; i<THREAD_MAX; i++){
        if (os_wrap_thrd[i].occupied && (void *)&os_wrap_thrd[i].tid==tid) {
            os_thread_delete(i);
            os_wrap_thrd[i].occupied = 0;
            return 0;
        }
    }
    return 0;
}

/* this func run in the Thread(tid) */
extern void OS_Wrap_thread_exit(void *tid) {
/*    int i;

    if (tid != NULL) for (i=0; i<THREAD_MAX; i++) {
        if (os_wrap_thrd[i].occupied && (void *)&os_wrap_thrd[i].tid==tid) {
            os_wrap_thrd[i].occupied = 0;
            break;
        }
    }*/
}

extern int OS_Wrap_thread_detach(void *tid) {
    return 0;
}


/*
**  AMR codec used memory functions
*/

extern void *oscl_malloc(unsigned int sz) {
    void *pmem;
    
    pmem = OsaMemAlloc(NULL, sz);
    ASSERT(pmem != NULL);
    return pmem;
}
extern void oscl_free(void *ptr) {
    ASSERT(ptr != NULL);
    OsaMemFree(ptr);
}

extern int OS_Wrap_free_memory_size(void) {
    return 1234;
}

extern void *oscl_memset(void *src, int c, unsigned int n) {return memset(src,c,n);}
extern void *oscl_memmove(void *dest, const void *src, unsigned int n) {return memmove(dest,src,n);}
extern void *oscl_memcpy(void *dest, const void *src, unsigned int n) {return memcpy(dest,src,n);}

extern unsigned short OS_Wrap_ntohs(unsigned short us) {
    return ((us&0xff00) >> 8) | ((us&0xff) << 8);
}
  
extern unsigned int OS_Wrap_ntohl(unsigned int ui) {
    return ((ui&0xff000000) >> 24) | ((ui&0xff0000) >> 8) | ((ui&0xff00) << 8) | ((ui&0xff) << 24);
}

extern unsigned short OS_Wrap_htons(unsigned short us) {
    return ((us&0xff00) >> 8) | ((us&0xff) << 8);
}

extern unsigned int OS_Wrap_htonl(unsigned int ui) {
    return ((ui&0xff000000) >> 24) | ((ui&0xff0000) >> 8) | ((ui&0xff00) << 8) | ((ui&0xff) << 24);
}

/*
** FILE access
*/

/* open and read out all data then close it.
** return data length or -1 when failure
*/
extern char *mk_file_name(const char *fname) {
    memset(fbuff, 0, sizeof(fbuff));
    strcpy(fbuff, U_DIR_PATH);
    strcat(fbuff, "/");
    strcat(fbuff, fname);
    return fbuff;
}

extern int OS_Wrap_read_file(const char *fname, char *dbuf, int blen) {
    unsigned short rfile;
    size_t rlen;
    int res;
    
    rfile = FDI_fopen(mk_file_name(fname), "rb");
    if (rfile == 0) {
        return -1;
    }

    rlen = FDI_fread(dbuf, 1, (size_t)blen, rfile);
    DEBUG_D("read %d of file return:%d", blen, (int)rlen);
    
    res = FDI_fclose(rfile);
    (void)res;

    return (int)rlen;
}

extern int OS_Wrap_write_file(const char *fname, char *dbuf, int blen) {
    unsigned short rfile;
    size_t wlen;
    int res;

    rfile = FDI_fopen(mk_file_name(fname), "wb");
    if (rfile == 0) {
        return -1;
    }

    wlen = FDI_fwrite(dbuf, 1, (size_t)blen, rfile);
    DEBUG_D("write %d of file return:%d", blen, (int)wlen);
    
    res = FDI_fclose(rfile);
    (void)res;

    return (int)wlen;
}

extern void OS_Wrap_delete_file(const char *fname) {
    int res;

    res = FDI_remove(mk_file_name(fname));
    (void)res;
}

