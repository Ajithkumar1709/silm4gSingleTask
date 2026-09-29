/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : osa_ali.h
Description : Definition of OSA Software Layer data types specific to the
              AliOS.

Notes       :

=========================================================================== */


#ifndef _OSA_ALI_H
#define _OSA_ALI_H

#include <osa.h>
#include <bsp_hisr.h>
#include <alios_hisr.h>


#define 	TX_MAX_NAME		9


#define  AOS_STACK_SIZE(X)   (X/sizeof(cpu_stack_t))

#define  AOS_KERNEL_SYS_INFO_KEY_RTI   0
#define  AOS_KERNEL_SYS_INFO_KEY_HISR  1



/*
 * Data Types.
 */
typedef struct
{
    ksem_t    sem;
}
OsaSemaphoreT ;

typedef struct
{
	abstract_task abs_task;  /* task MUST be the first member */
	void   *entry;
	UINT32  entryParam;
	UINT8  *allocatedStack;
}OsaTaskT;


typedef struct
{
    RHINO_HISR     hisrRef ;
    UINT32      intSource ;
    void        (*fisrRoutine)(UINT32) ;
    void        (*sisrRoutine)(void) ;
}
OsaIsrT ;

typedef struct
{
	kbuf_queue_t 	queue;
	void           *buf;
	CHAR           *name;
	UINT32          blockSize;
}
OsaMsgQT ;


typedef struct
{
	kqueue_t 	queue;
	CHAR       *name;
	CHAR       *buf;
}
OsaMbQT ;

typedef struct
{
    kevent_t   event;
}
OsaFlagT;


typedef struct
{
    kmutex_t    mutex;
}
OsaMutexT ;


typedef struct
{
	ktimer_t *timer;
	CHAR     *name;
	void     (*callBackRoutine)(UINT32) ;
    UINT32   timerArgc ;
    UINT32   initialTime ;
    UINT32   rescheduleTime ;
	CHAR     started;
}
OsaTimerT;

/*
 * Defines.
 */
#define     OSA_DUMMY_CRITICAL_SECTION_HANDLE       ((OsaRefT)(~0))
#define     OSA_MSGQ_MSG_SIZE(sIZE)                 ((UNSIGNED)(sIZE + sizeof(UNSIGNED) - 1) / sizeof(UNSIGNED))    /*  Size is in UNSIGNED not bytes. */


/*
 * Macros.
 */

/*
 * Data.
 */

/*
 * Functions.
 */
BOOL Osa_TranslateErrorCode( char *callerFuncName, UINT32 ErrorCode, OSA_STATUS *pOsaStatus ) ;


#endif

