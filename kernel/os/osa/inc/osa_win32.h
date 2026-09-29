/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : osa_win32.h
Description : Definition of OSA Software Layer data types specific to the 
              Microsoft Windows OS.

Notes       : 

Copyright (c) 2001 Intel CCD. All Rights Reserved
=========================================================================== */

#ifndef _OSA_WIN32_H
#define _OSA_WIN32_H

#ifdef OSA_WIN32
#include <windows.h>  
#include <stdio.h>
#include "gbl_types.h"
#include "osa_types.h"

/************************************************************************
 * External Interfaces
 ***********************************************************************/

extern void INTERRUPTS_ON(void);
extern void INTERRUPTS_OFF(void);
extern UINT32           OSA_RtcCounter;
extern CRITICAL_SECTION csOSAContextLock;

/*************************************************************************
 * Constants
 *************************************************************************/

#define OSA_MIN_STACK_SIZE      256
#define OSA_ENABLE_INTERRUPTS   1
#define OSA_DISABLE_INTERRUPTS  2
#define OSA_PIPE_MEM_OVERHEAD   4
#define OSA_NO_SUSPEND          0
#define OSA_FLAG_AND            5
#define OSA_FLAG_AND_CLEAR      6
#define OSA_FLAG_OR             7
#define OSA_FLAG_OR_CLEAR       8
#define OSA_FIXED               9
#define OSA_VARIABLE            10
#define OSA_FIFO                11
#define OSA_PRIORITY            12
#define OSA_POOL_MEM_OVERHEAD         8   /* Fixed pool overhead per partition */
#define OSA_FIXED_POOL_MEM_OVERHEAD   sizeof(OS_PartMemHdr)   /* Fixed pool overhead per partition */
#define OSA_VAR_POOL_MEM_OVERHEAD     12  /* Variable pool overhead per partition */
#define OSA_MAX_TASK_NAME_SIZE          8
#define OSA_MAX_PRIORITY                31
#define OSA_MAX_NATIVE_PRIORITY         255       /* Win32 priorities are 255 lowest to 0 highest */

/* Remain for backwards compatibility */
#define OS_SUSPEND              OSA_SUSPEND       
#define OS_NO_SUSPEND           OSA_NO_SUSPEND    
#define OS_FLAG_AND             OSA_FLAG_AND      
#define OS_FLAG_AND_CLEAR       OSA_FLAG_AND_CLEAR
#define OS_FLAG_OR              OSA_FLAG_OR       
#define OS_FLAG_OR_CLEAR        OSA_FLAG_OR_CLEAR 
#define OS_FIXED                OSA_FIXED            
#define OS_VARIABLE             OSA_VARIABLE         
#define OS_FIFO                 OSA_FIFO
#define OS_PRIORITY             OSA_PRIORITY

#define OSA_TIMER_STACK      20000
#define OSA_TIMER_PRIORITY   20                                        
#define OSA_TICK_STACK       20000
#define OSA_TICK_PRIORITY    25

/*************************************************************************
 * WinC32 Specific Types
 *************************************************************************/
 typedef HANDLE     OS_Hisr_t;
 typedef HANDLE     OS_MemPool_t;
// typedef HANDLE     OS_PartitionPool_t;
 typedef HANDLE     OS_Proc_t;
#ifdef __cplusplus
	#define OSA_STATUS   UINT8
#else
	#define OSA_STATUS   UINT8
#endif
 

/* Remain for backwards compatibility */ 
#ifdef __cplusplus
	#define OS_STATUS extern "C" UINT8
#else
	#define OS_STATUS  UINT8
#endif


 typedef void (*funcPtrType)(void*);
 typedef struct
 {
    HANDLE      task;
    DWORD       id;
    funcPtrType taskStartPtr;
    void        *argv;
    UINT8       priority;
    UINT8       filler[3];
 } OS_Task_t;


/* Semaphore reference */
 typedef struct
 {
    HANDLE  os_sema;
    UINT32  count;
 } OS_Sema_t;

/* Mutex reference */
 typedef struct
 {

    HANDLE  os_mutex;
    UINT32  owner;
    UINT32  locked;
 } OS_Mutex_t;

/* Flag reference */
 typedef struct
 {
    UINT32      flag;
    OS_Sema_t   semaphore;
 } OS_Flag_t;

/* Partition memory pool reference */
 typedef struct
 {
    struct _OS_PartMemHdr   *free;      /* Free partition list */
    OS_Mutex_t              mutex;      /* Mutex to secure access */
    OS_Sema_t               sema;       /* Sema for blocking when no mem left */
    UINT32                  numFree;    /* Number of partitions free */
    void                    *chunk;
 } OS_PartitionPool_t;
 
/* Partition memory pool header */
 typedef struct _OS_PartMemHdr
 {
    struct _OS_PartMemHdr   *next;
    OS_PartitionPool_t      *pool;
#ifdef OSA_MEM_CHECK
    UINT32                  size;
    UINT32                  partSize;
#endif
 } OS_PartMemHdr;

#if defined OSA_USE_INTERNAL_MESSAGING  /* Use Internal messaging */
//
// Base Message Queue structure
// Created only ONCE for every message queue, includes the message queue as well
// Is created in the address space of invoking process/task,
// but then the pointer is mapped so that other process/task can access this as well
// in their own address space
// The memory for this structure and the message queue is shared across all processes/tasks
// that want to use the memory queue
//
#define MAX_NAME_LENGTH             128
#define OSA_MSG_QUEUE_HEADER_SIZE   sizeof(OSMsgQInfo)
typedef struct _MsgQInfo
{
    UINT8*      memPtr;                     // Original allocated memory pointer
    UINT8*      msgPtr;                     // Pointer to start of actual message queue
    UINT32      maxNumMsgs;                 // Maximum number of messages in message queue
    UINT32      maxSizeOfMsg;               // Maximum size of each message in the queue
    UINT32      readCount;                  // Number of total messages read from queue
    UINT32      writeCount;                 // Number of total messages written into queue  
    UINT8       queueName[MAX_NAME_LENGTH]; // Unique Queue Name, used to create a unique event for queue
} OSMsgQInfo, *POSMsgQInfo;

//
// Local message queue structure
// Created when the message queue is opened/initialized by each process/task that wants to use it
// This structure is created once in address space of every process/task that wants to use the
// message queue
// Includes a pointer to base memory queue
//
typedef struct _LocalMsgQInfo
{
    OS_Flag_t   recvEventHandle;
    OS_Sema_t   sendSemaphore;
    POSMsgQInfo pMsgQInfo;

} LocalMsgQInfo, *PLocalMsgQInfo;


typedef UINT32  BaseMsgQHandle;
typedef UINT32  MsgQHandle;

#endif /* OSA_USE_INTERNAL_MESSAGING  Use Internal messaging */


/* Message queue reference */
 typedef struct
 {
#if defined OSA_USE_INTERNAL_MESSAGING  /* Use Internal messaging */
    PLocalMsgQInfo   os_ref;
#else                                         /* Use WinCE 4.0 messaging */
    HANDLE      os_ref_recv;
    HANDLE      os_ref_send;
#endif
 } OS_MsgQ_t;

/* Mailbox queue reference */
 typedef struct
 {
#if defined OSA_USE_INTERNAL_MESSAGING  /* Use Internal messaging */
    LocalMsgQInfo   os_ref;
#else                                         /* Use WinCE 4.0 messaging */
    HANDLE      os_ref_recv;
    HANDLE      os_ref_send;
#endif
 } OS_Mbox_t;

/* WinC32 specific timer information */
 typedef void (*timerCBPtrType)(UINT32);
 typedef struct
 {
    UINT        os_ref;
    UINT32      state;
    UINT32      ticksLeft;
    UINT32      reschedTicks;
    UINT32      expirations;
    timerCBPtrType  callback;
    UINT32      timerArgc;
 } OS_Timer_t; 
        
/*
 ** OS System call prototypes
 */
void OSA_Initialize(void*);
OSA_STATUS OSA_Win32TaskCreate  ( OS_Task_t *, UINT8, DWORD, void(*)(void*), void* );
OSA_STATUS OSA_Win32TaskDelete  ( OS_Task_t task ); 
OSA_STATUS OSA_Win32TaskSuspend ( OS_Task_t task );
OSA_STATUS OSA_Win32TaskResume  ( OS_Task_t task );
OSA_STATUS OSA_Win32TaskGetPriority( OS_Task_t *task, UINT8 *oldPriority);
OSA_STATUS OSA_Win32TaskChangePriority( OS_Task_t *task, UINT8 newPriority, UINT8 *oldPriority);
DWORD WINAPI OSA_TaskStartWrapper(void *argv);

OSA_STATUS OSA_Win32QueueCreate ( OS_MsgQ_t *msgQRef, char *queueName, UINT32 maxSize, UINT32 maxNumber, void *queueAddr, UINT8 waitingMode );
OSA_STATUS OSA_Win32QueueDelete ( OS_MsgQ_t *msgQRef );
OSA_STATUS OSA_Win32QueueSend   ( OS_MsgQ_t *msgQRef, UINT32 size, UINT8 *msg, UINT32 timeout);
OSA_STATUS OSA_Win32QueueRecv   ( OS_MsgQ_t *msgQRef, UINT8 *msg, UINT32 size, UINT32 timeout );
OSA_STATUS OSA_Win32QueuePoll   ( OS_MsgQ_t *msgQRef, UINT32 *msgCount );


OSA_STATUS OSA_Win32FlagCreate  ( OS_Flag_t *flagRef );
OSA_STATUS OSA_Win32FlagDelete  ( OS_Flag_t *flagRef);
OSA_STATUS OSA_Win32FlagSetBits ( OS_Flag_t *flagRef, UINT32 mask, UINT32 operation);
OSA_STATUS OSA_Win32FlagWait    ( OS_Flag_t *flagRef, UINT32 mask, UINT32 operation, UINT32* flags, UINT32 timeout );


OSA_STATUS OSA_Win32TimerCreate ( OS_Timer_t *timer );
OSA_STATUS OSA_Win32TimerDelete ( OS_Timer_t *timer );
OSA_STATUS OSA_Win32TimerStart  ( OS_Timer_t *timer, UINT32 time, UINT32 resched, void (*handler)(UINT32), UINT32 argc );
OSA_STATUS OSA_Win32TimerStop   ( OS_Timer_t *timer );
OSA_STATUS OSA_Win32TimerGetStatus( OS_Timer_t *timer, OSATimerStatus* status );
void OSA_Win32ClockTick(void *);

OSA_STATUS OSA_Win32SemaCreate  ( OS_Sema_t *sema, UINT32 initialCount, UINT8 waitingMode );
OSA_STATUS OSA_Win32SemaDelete  ( OS_Sema_t *sema );
OSA_STATUS OSA_Win32SemaAcquire ( OS_Sema_t *sema, UINT32 timeout );
OSA_STATUS OSA_Win32SemaRelease ( OS_Sema_t *sema );
OSA_STATUS OSA_Win32SemaPoll    ( OS_Sema_t *sema, UINT32* count );

OSA_STATUS OSA_Win32MutexCreate ( OS_Mutex_t *mutex );
OSA_STATUS OSA_Win32MutexDelete ( OS_Mutex_t *mutex );
OSA_STATUS OSA_Win32MutexLock   ( OS_Mutex_t *mutex, UINT32 timeout );
OSA_STATUS OSA_Win32MutexUnlock ( OS_Mutex_t *mutex );

OSA_STATUS OSA_Win32MemPoolCreate( OS_MemPool_t *pool, DWORD poolSize );
OSA_STATUS OSA_Win32MemPoolDelete( OS_MemPool_t *pool );
OSA_STATUS OSA_Win32MemAlloc    (UINT32 size, void **mem);
OSA_STATUS OSA_Win32MemFree     (void* mem );

BOOL OSA_GetControlBlock(void**, size_t, BOOL );
OSA_STATUS OSA_Win32FIsrCreate  ( UINT32, void(*)(UINT8) );
OSA_STATUS OSA_Win32SIsrCreate  ( UINT32, OS_Hisr_t *, void(*)(void), UINT8, UINT8 *, UINT32 );
OSA_STATUS OSA_Win32SIsrDelete  ( OS_Hisr_t *);
OSA_STATUS OSA_Win32SIsrNotify  ( UINT32 isrNum );
OSA_STATUS OSA_TranslateErrorCode(DWORD osErrCode);

BOOL    WINAPI OSA_Init();
BOOL    OSA_Deinit(DWORD dwData);
BOOL    WINAPI OSA_DllEntry(HANDLE  hInstDll,DWORD   dwReason, LPVOID  lpvReserved); 
DWORD   OSA_Open (DWORD dwData, DWORD dwAccess, DWORD dwShareMode);
BOOL    OSA_Close(DWORD dwData);
DWORD   OSA_Read (DWORD dwData,  LPVOID pBuf, DWORD Len);
DWORD   OSA_Write(DWORD dwData, LPCVOID pBuf, DWORD Len);
VOID    OSA_PowerUp  (VOID);
BOOL    OSA_PowerDown(VOID);
BOOL    OSA_IOControl(DWORD p1, DWORD p2, PBYTE p3, DWORD p4, PBYTE p5, DWORD p6, PDWORD p7); 

/*
 ** OS System call macros
 */

#define OSA_INIT(a) OSA_Initialize(a)
#define OSA_RUN /* WinC32 does not need to do anything more before the scheduler runs */
#ifdef OSA_USE_DYNAMIC_REFS
#define OSA_GET_REF(pool, ref, size) \
    { \
        if(!((void*)ref = malloc((UINT32)size)) ) { \
            OSA_ASSERT (FALSE); } \
        ref->refCheck = (void *)ref; \
    }
#define OSA_DELETE_REF(pool, ref) \
    { \
        ref->refCheck = NULL; \
        free(ref); \
    }
#else
#define OSA_GET_REF(pool, ref, size) \
    { \
        OSA_STATUS rtn; \
        OSA_SEMA_ACQUIRE(pool->poolSemaphore, OSA_SUSPEND, rtn); \
        OSA_GET_FROM_FREE_LIST(pool->free, ref); \
        OSA_ADD_TO_ACTIVE_LIST((pool->head), ref); \
        pool->numCreated++; \
        OSA_SEMA_RELEASE(pool->poolSemaphore, rtn); \
        ref->refCheck = (void *)ref; \
    }
#define OSA_DELETE_REF(pool, ref) \
    { \
        OSA_STATUS rtn; \
        OSA_SEMA_ACQUIRE(pool->poolSemaphore, OSA_SUSPEND, rtn); \
        OSA_DELETE_FROM_ACTIVE_LIST((pool->head), ref); \
        pool->numCreated--; \
        OSA_ADD_TO_FREE_LIST((pool->free), ref); \
        OSA_SEMA_RELEASE(pool->poolSemaphore, rtn); \
        ref->refCheck = NULL; \
    }
#endif

/* Thread Control */



#define OSA_TASK_CREATE(taskPtr, stackPtr, stackSize, priority, name,\
                       taskStart, argv, rtn) \
    { \
        rtn = OSA_Win32TaskCreate( taskPtr, priority, stackSize, taskStart, argv);    \
    }



#define OSA_TASK_DELETE(taskPtr, rtn)                               \
    {                                                               \
        rtn = OSA_Win32TaskDelete( taskPtr );                       \
    }

#define OSA_TASK_SUSPEND(taskPtr, rtn)                              \
    {                                                               \
        rtn = OSA_Win32TaskSuspend( taskPtr );                      \
    }

#define OSA_TASK_RESUME(taskPtr, rtn)                               \
    {                                                               \
        rtn = OSA_Win32TaskResume( taskPtr );                       \
    }
#define OSA_TASK_SLEEP(ticks)                                       \
    {                                                               \
        Sleep(ticks);                                               \
    }
#define OSA_TASK_CHANGE_PRIORITY(taskPtr, newPriority, oldPriority, rtn)\
    {                                                               \
        rtn = OSA_Win32TaskChangePriority( taskPtr, newPriority, oldPriority );  \
    }
#define OSA_TASK_GET_PRIORITY(taskPtr, oldPriority, rtn)            \
    {                                                               \
        rtn = OSA_Win32TaskGetPriority( taskPtr, oldPriority );     \
    }

#define OSA_TASK_YIELD Sleep(0L);

OS_Task_t * OsaTaskIdentify();
#define OSA_TASK_IDENTIFY(taskPtr)   \
	taskPtr = OsaTaskIdentify();                             
OSA_STATUS OsaTaskEqual(OS_Task_t *taskPtr);
#define OSA_TASK_EQUAL(taskPtr, rtn) \
rtn = OsaTaskEqual(taskPtr);
/* Messaging */

#define OSA_QUEUE_CREATE(qRef, name, size, num, addr, mode, rtn)    \
    {                                                               \
        rtn = OSA_Win32QueueCreate(qRef, name, size, num, addr, mode);\
    }
#define OSA_QUEUE_DELETE(qRef, rtn)                                 \
    {                                                               \
        rtn = OSA_Win32QueueDelete(&qRef);                          \
    }
#define OSA_QUEUE_SEND(qRef, size, ptr, timeout, rtn)               \
    {                                                               \
        rtn = OSA_Win32QueueSend(&qRef, size, ptr, timeout);        \
    }
#define OSA_QUEUE_RECV(qRef, msg, size, timeout, rtn)               \
    {                                                               \
        rtn = OSA_Win32QueueRecv(&qRef, msg, size, timeout);        \
    }
#define OSA_QUEUE_POLL(qRef, msgCount, rtn)                         \
    {                                                               \
        rtn = OSA_Win32QueuePoll(&qRef, msgCount);                  \
    }


/* Mailboxes */

#define OSA_MAILBOX_CREATE(qRef, name, num, mode, rtn)              \
    {                                                               \
        rtn = OSA_Win32QueueCreate((OS_MsgQ_t *)qRef, name, OSA_MAX_MBOX_DATA_SIZE, num, 0L, mode);    \
    }
#define OSA_MAILBOX_DELETE(qRef, rtn)                               \
    {                                                               \
        rtn = OSA_Win32QueueDelete((OS_MsgQ_t *)&qRef);                          \
    }
#define OSA_MAILBOX_SEND(qRef, ptr, timeout, rtn)                   \
    {                                                               \
        rtn = OSA_Win32QueueSend((OS_MsgQ_t *)&qRef, OSA_MAX_MBOX_DATA_SIZE, ptr, timeout);        \
    }
#define OSA_MAILBOX_RECV(qRef, msg, timeout, rtn)                   \
    {                                                               \
        rtn = OSA_Win32QueueRecv((OS_MsgQ_t *)&qRef, msg, OSA_MAX_MBOX_DATA_SIZE, timeout);        \
    }
#define OSA_MAILBOX_POLL(qRef, msgCount, rtn)                       \
    {                                                               \
        rtn = OSA_Win32QueuePoll((OS_MsgQ_t *)&qRef, msgCount);                  \
    }


/* Events */

#define OSA_FLAG_CREATE(flagRef, name, rtn)                         \
    {                                                               \
        rtn = OSA_Win32FlagCreate(flagRef);                         \
    }
#define OSA_FLAG_DELETE(flagRef, rtn)                               \
    {                                                               \
        rtn = OSA_Win32FlagDelete(flagRef);                         \
    }
#define OSA_FLAG_SET_BITS(flagRef, mask, operation, rtn)            \
    {                                                               \
        rtn = OSA_Win32FlagSetBits(flagRef, mask, operation);       \
    }

#define OSA_FLAG_WAIT(flagRef, reqValue, mode, currValue, timeout, rtn) \
    {                                                               \
        rtn = OSA_Win32FlagWait(flagRef, reqValue, mode, currValue, timeout);  \
    }
#define OSA_FLAG_PEEK(flagRef, value, rtn)                          \
    {                                                               \
        *value = flagRef.flag;                                      \
        rtn = OS_SUCCESS;                                           \
    }


/* Timers */
#define OSA_TIMER_CREATE(timerRef, rtn)                             \
    {                                                               \
        rtn = OSA_Win32TimerCreate(timerRef);                       \
    }
#define OSA_TIMER_DELETE(timerRef, rtn)                             \
    {                                                               \
        rtn = OSA_Win32TimerDelete(&timerRef);                      \
    }
#define OSA_TIMER_START(timerRef, time, resched, handler,           \
                       argc, rtn)                                   \
    {                                                               \
        rtn = OSA_Win32TimerStart(&timerRef, time, resched, handler, argc); \
    }
#define OSA_TIMER_STOP(timerRef, rtn)                               \
    {                                                               \
        rtn = OSA_Win32TimerStop(&timerRef);                        \
    }
#define OSA_TIMER_STATUS(timerRef, status, rtn)                     \
    {                                                               \
        status->status        = timerRef.state;                     \
        status->expirations   = timerRef.expirations;               \
        rtn = OS_SUCCESS;                                           \
    }
#define OSA_MEM_ALLOC(pool, type, size, partSize, mem, timeout, rtn)\
    {                                                               \
        rtn = OSA_Win32MemAlloc(size, mem);\
    }
#define OSA_MEM_FREE(pool, type, mem, rtn)                          \
    {                                                               \
        rtn = OSA_Win32MemFree(  mem );                  \
    }
#define OSA_MEM_POOL_CREATE(pool, name, type, base, size, partition, mode, rtn) \
    {                                                               \
        rtn = OS_SUCCESS;                                           \
    }
#define OSA_MEM_POOL_DELETE(pool, type, rtn)                        \
    {                                                               \
        rtn = OS_SUCCESS;                                           \
    }

/* Semaphores */
#define OSA_SEMA_CREATE(sema, name, initialCount, waitingMode, rtn )\
    {                                                               \
        rtn = OSA_Win32SemaCreate(sema, initialCount, waitingMode);\
    }
#define OSA_SEMA_DELETE(sema, rtn)                                  \
    {                                                               \
        rtn = OSA_Win32SemaDelete(&sema);                           \
    }
#define OSA_SEMA_ACQUIRE(sema, timeout, rtn)                        \
    {                                                               \
        rtn = OSA_Win32SemaAcquire(&sema, timeout);                 \
    }
#define OSA_SEMA_RELEASE(sema, rtn)                                 \
    {                                                               \
        rtn = OSA_Win32SemaRelease(&sema);                          \
    }
#define OSA_SEMA_POLL(sema, count, rtn)                             \
    {                                                               \
        rtn = OSA_Win32SemaPoll(&sema, count);                      \
    }
    
/* Mutexes */
#define OSA_MUTEX_CREATE(mutex, name, waitingMode, rtn )            \
    {                                                               \
        rtn = OSA_Win32MutexCreate(mutex);                          \
    }
#define OSA_MUTEX_DELETE(mutex, rtn)                                \
    {                                                               \
        rtn = OSA_Win32MutexDelete(&mutex);                         \
    }
#define OSA_MUTEX_LOCK(mutex, timeout, rtn)                         \
    {                                                               \
        rtn = OSA_Win32MutexLock(&mutex, timeout);                  \
    }
#define OSA_MUTEX_UNLOCK(mutex, rtn)                                \
    {                                                               \
        rtn = OSA_Win32MutexUnlock(&mutex);                         \
    }

/* Context lock */
#define OSA_CONTEXT_LOCK EnterCriticalSection (&csOSAContextLock)
#define OSA_CONTEXT_UNLOCK LeaveCriticalSection (&csOSAContextLock)
#define OSA_ISR_CREATE_FISR(isrNum, func, rtn)                      \
    {                                                               \
        rtn = OSA_Win32FIsrCreate(isrNum, func);                    \
    }
#define OSA_ISR_CREATE_SISR(isrNum, isr, func, priority, stack, size, rtn)\
    {                                                               \
        rtn = OSA_Win32SIsrCreate(isrNum, isr, func, priority, stack, size);\
    }
#define OSA_ISR_DELETE_SISR(isr, rtn)                               \
    {                                                               \
        rtn = OSA_Win32SIsrDelete(isr);                             \
    }
#define OSA_ISR_NOTIFY_SISR(isr, rtn)                               \
    {                                                               \
        rtn = OSA_Win32SIsrNotify(isr);                             \
    }
#define OSA_INTERRUPT_ENABLE(number, rtn)                           \
    {                                                               \
        rtn = OS_SUCCESS;                                           \
    }
/*        INTERRUPTS_ON();                                            \*/
#define OSA_INTERRUPT_DISABLE(number, rtn)                          \
    {                                                               \
        rtn = OS_SUCCESS;                                           \
    }
/*        INTERRUPTS_OFF();                                           \*/

/* RTC services */
#define OSA_GET_TIME(time)                                          \
    {                                                               \
        time = GetTickCount();                                      \
    }
#define OSA_GET_SYSTEM_TIME(secsPtr, milliSecsPtr, rtn)             \
    {                                                               \
        UINT32 currentTime;                                         \
                                                                    \
        currentTime = GetTickCount() * OSA_TICK_FREQ_IN_MILLISEC;   \
                                                                    \
        *secsPtr = currentTime / 1000 ;                             \
        *milliSecsPtr = (UINT16)                                    \
                        (( currentTime - (*secsPtr * 1000))/ 10)*10;\
        rtn = OS_SUCCESS;                                           \
    }
#define OSA_CLOCK_TICK(a) OSA_Win32ClockTick(a)

#define OSA_ERROR(err)                                              \
    {                                                               \
        printf("\n*** OSA_ERROR -> %d *** \n File: %s\n Line: %ld\n", err, __FILE__, __LINE__);\
    }

#endif /* OSA_WIN32 */



#endif /* _OSA_WIN32_H */

