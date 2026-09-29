/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : osa_symbian.h
Description : Definition of OSA Software Layer data types specific to the 
              Symbian EPOC OS.

Notes       : 

Copyright (c) 2001 Intel CCD. All Rights Reserved
=========================================================================== */
#ifndef _OSA_SYMBIAN_H
#define _OSA_SYMBIAN_H


#ifdef OSA_SYMBIAN

#ifdef __cplusplus
extern "C" {
#endif

//#include <e32base.h>
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "osa_types.h"
//#include <e32std.h>
#include "gbl_types.h"

/************************************************************************
 * External Interfaces
 ***********************************************************************/
#ifndef OSA_NU_TARGET  
 
    /* These definitions are needed as we do not yet have the INTC
     * package yet from Israel.
     */
//    typedef UINT32                  INTC_InterruptSources; 
    #define INTC_RC_OK              0
    #define INTC_MAX_INTERRUPT_SOURCES   110

#else
        #include "intc.h"
#endif

//extern UINT32           OSA_RtcCounter;
//extern CRITICAL_SECTION csOSAContextLock;

/*************************************************************************
 * Constants
 *************************************************************************/
#define OSA_MIN_STACK_SIZE      256
#define OSA_ENABLE_INTERRUPTS   1
#define OSA_DISABLE_INTERRUPTS  2
#define OSA_PIPE_MEM_OVERHEAD   4
#define OSA_SUSPEND             0xFFFF
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
#define OSA_MAX_TASK_NAME_SIZE  8
#define OSA_MAX_PRIORITY        31
#define OSA_MAX_NATIVE_PRIORITY 1000      /* Symbian priorities are 0 lowest to 1000 highest (opposite to OSA)

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

/*************************************************************************
 * WinCE Specific Types
 *************************************************************************/
 typedef void*      OSAFlagRef;
 typedef UINT32     OS_Hisr_t;
 typedef UINT32     OS_MemPool_t;
 typedef UINT8      OSA_STATUS;
 
/* Remain for backwards compatibility */ 
 typedef UINT8              OS_STATUS;
 typedef void*              OSFlagRef;

// typedef TThreadFunction (*funcPtrType)(TAny*);
 typedef struct
 {
    UINT32      os_ref;
    UINT32      id;
    UINT8       priority;
    UINT8       taskName[OSA_MAX_TASK_NAME_SIZE];
    UINT8       filler[3];
 } OS_Task_t;

/* Semaphore reference */
 typedef struct
 {
    UINT32      os_sema;
    UINT8       semaName[OSA_MAX_TASK_NAME_SIZE];
 } OS_Sema_t;

/* Mutex reference */
 typedef struct
 {
    UINT32  os_mutex;
    UINT8   mutexName[OSA_MAX_TASK_NAME_SIZE];
    UINT32  owner;
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
 } OS_PartitionPool_t;
 
/* Partition memory pool header */
 typedef struct _OS_PartMemHdr
 {
    struct _OS_PartMemHdr   *next;
    OS_PartitionPool_t      *pool;
 } OS_PartMemHdr;

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

/* Message queue reference */
 typedef struct
 {
    PLocalMsgQInfo   os_ref;
 } OS_MsgQ_t;

/* Mailbox queue reference */
 typedef struct
 {
    LocalMsgQInfo   os_ref;
 } OS_Mbox_t;

/* Timer information */
 typedef void (*timerCBPtrType)(UINT32);
 typedef struct
 {
    UINT32      os_ref;
    UINT32      state;
    UINT32      ticksLeft;
    UINT32      reschedTicks;
    UINT32      expirations;
    timerCBPtrType  callback;
    UINT32      timerArgc;
 } OS_Timer_t; 
        
/* Timer status information structure */
 typedef struct
 {
    UINT32    status;           /* timer status OS_ENABLED, OS_DISABLED    */
    UINT32    expirations;      /* number of expirations for cyclic timers */
 } OSATimerStatus;


/*
 ** OS System call prototypes
 */
EXPORT_C void OSA_Initialize(void);
EXPORT_C OSA_STATUS OSA_TaskCreate( OS_Task_t *, UINT8 *, UINT8, UINT32, void *, void *);
EXPORT_C OSA_STATUS OSA_TaskDelete  ( OS_Task_t task ); 
EXPORT_C OSA_STATUS OSA_TaskSuspend ( OS_Task_t task );
EXPORT_C OSA_STATUS OSA_TaskResume  ( OS_Task_t task );
EXPORT_C OSA_STATUS OSA_TaskGetPriority( OS_Task_t *task, UINT8 *oldPriority);
EXPORT_C OSA_STATUS OSA_TaskChangePriority( OS_Task_t *task, UINT8 newPriority, UINT8 *oldPriority);
EXPORT_C void OSA_TaskSleep  ( UINT32 ticks ); 
//GLDEF_C TInt OSA_TaskStartWrapper(void *argv);
EXPORT_C OSA_STATUS OSA_QueueCreate ( OS_MsgQ_t *msgQRef, char *queueName, UINT32 maxSize, UINT32 maxNumber, void *queueAddr, UINT8 waitingMode );
EXPORT_C OSA_STATUS OSA_QueueDelete ( OS_MsgQ_t *msgQRef );
EXPORT_C OSA_STATUS OSA_QueueSend   ( OS_MsgQ_t *msgQRef, UINT32 size, UINT8 *msg, UINT32 timeout);
EXPORT_C OSA_STATUS OSA_QueueRecv   ( OS_MsgQ_t *msgQRef, UINT8 *msg, UINT32 size, UINT32 timeout );
EXPORT_C OSA_STATUS OSA_QueuePoll   ( OS_MsgQ_t *msgQRef, UINT32 *msgCount );

EXPORT_C OSA_STATUS OSA_FlagCreate  ( OS_Flag_t *flagRef, UINT8 * );
EXPORT_C OSA_STATUS OSA_FlagDelete  ( OS_Flag_t *flagRef);
EXPORT_C OSA_STATUS OSA_FlagSetBits ( OS_Flag_t *flagRef, UINT32 mask, UINT32 operation);
EXPORT_C OSA_STATUS OSA_FlagWait    ( OS_Flag_t *flagRef, UINT32 mask, UINT32 operation, UINT32* flags, UINT32 timeout );

EXPORT_C OSA_STATUS OSA_TimerCreate ( OS_Timer_t *timer );
EXPORT_C OSA_STATUS OSA_TimerDelete ( OS_Timer_t *timer );
EXPORT_C OSA_STATUS OSA_TimerStart  ( OS_Timer_t *timer, UINT32 time, UINT32 resched, void (*handler)(UINT32), UINT32 argc );
EXPORT_C OSA_STATUS OSA_TimerStop   ( OS_Timer_t *timer );
EXPORT_C OSA_STATUS OSA_TimerGetStatus( OS_Timer_t *timer, OSATimerStatus* status );
EXPORT_C void OSA_ClockTick(void);
EXPORT_C UINT32 OSA_GetTicks(void);

EXPORT_C OSA_STATUS OSA_SemaCreate  ( OS_Sema_t *sema, UINT8 *, UINT32 initialCount, UINT8 waitingMode );
EXPORT_C OSA_STATUS OSA_SemaDelete  ( OS_Sema_t *sema );
EXPORT_C OSA_STATUS OSA_SemaAcquire ( OS_Sema_t *sema, UINT32 timeout );
EXPORT_C OSA_STATUS OSA_SemaRelease ( OS_Sema_t *sema );
EXPORT_C OSA_STATUS OSA_SemaPoll    ( OS_Sema_t *sema, UINT32* count );

EXPORT_C OSA_STATUS OSA_MutexCreate ( OS_Mutex_t *mutex, UINT8 * );
EXPORT_C OSA_STATUS OSA_MutexDelete ( OS_Mutex_t *mutex );
EXPORT_C OSA_STATUS OSA_MutexLock   ( OS_Mutex_t *mutex, UINT32 timeout );
EXPORT_C OSA_STATUS OSA_MutexUnlock ( OS_Mutex_t *mutex );

EXPORT_C OSA_STATUS OSA_MemPoolCreate( OS_PartitionPool_t *pool, UINT32 poolType, UINT8 *poolBase, UINT32 poolSize, UINT32 partitionSize);
EXPORT_C OSA_STATUS OSA_MemPoolDelete( OS_PartitionPool_t *pool, UINT32 poolType );
EXPORT_C OSA_STATUS OSA_MemAlloc    ( void *pool, UINT32 poolType, UINT32 size, void **mem, UINT32 timeout );
EXPORT_C OSA_STATUS OSA_MemFree     ( void *pool, UINT32 poolType, void* mem );

OSA_STATUS OSA_FIsrCreate  ( UINT32, void(*)(UINT8) );
OSA_STATUS OSA_SIsrCreate  ( UINT32, OS_Hisr_t *, void(*)(void), UINT8, UINT8 *, UINT32 );
OSA_STATUS OSA_SIsrDelete  ( OS_Hisr_t *);
OSA_STATUS OSA_SIsrNotify  ( UINT32 isrNum );

EXPORT_C void OSA_ContextLock(void);
EXPORT_C void OSA_ContextUnLock(void);
EXPORT_C OSA_STATUS OSA_TranslateErrorCode(UINT32 osErrCode);


/*
 ** OS System call macros
 */

#define OSA_INIT OSA_Initialize()
#define OSA_RUN /* Symbian does not need to do anything more before the scheduler runs */
#define OSA_GET_REF(pool, ref, size) \
    { \
        OSA_STATUS rtn; \
        if(!(ref = malloc((UINT32)size)) ) { \
            return(OS_FAIL); } \
        OSA_SEMA_ACQUIRE(pool->poolSemaphore, OSA_SUSPEND, rtn); \
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
        OSA_SEMA_RELEASE(pool->poolSemaphore, rtn); \
        ref->refCheck = NULL; \
        free(ref); \
    }

/*
 ** Thread priority conversion macros
 ** OSA uses 0 highest, 31 lowest, Symbian uses 1000 highest, 1 lowest
 */
#define OSA_CONVERT_OSA_PRIORITY_TO_NATIVE_OS(osaPriority, nativePriority) \
    { \
        nativePriority = ((osaPriority * OSA_MAX_NATIVE_PRIORITY) / OSA_MAX_PRIORITY); \
        nativePriority = (OSA_MAX_NATIVE_PRIORITY - nativePriority); \
    }

#define OSA_CONVERT_NATIVE_PRIORITY_TO_OSA(osaPriority, nativePriority) \
    { \
        osaPriority = (((OSA_MAX_NATIVE_PRIORITY - nativePriority) * OSA_MAX_PRIORITY) / OSA_MAX_NATIVE_PRIORITY); \
    }

/* Thread Control */

#define OSA_TASK_CREATE(taskPtr, stackPtr, stackSize, priority, name,\
                       taskStart, argv, rtn) \
    { \
        rtn = OSA_TaskCreate( taskPtr, (unsigned char *)name, (unsigned char)priority, stackSize, taskStart, argv); \
    }

#define OSA_TASK_DELETE(taskPtr, rtn)                               \
    {                                                               \
        rtn = OSA_TaskDelete( taskPtr );                            \
    }

#define OSA_TASK_SUSPEND(taskPtr, rtn)                              \
    {                                                               \
        rtn = OSA_TaskSuspend( taskPtr );                           \
    }

#define OSA_TASK_RESUME(taskPtr, rtn)                               \
    {                                                               \
        rtn = OSA_TaskResume( taskPtr );                            \
    }
#define OSA_TASK_SLEEP(ticks)                                       \
    {                                                               \
        OSA_TaskSleep( ticks );                                     \
    }
#define OSA_TASK_CHANGE_PRIORITY(taskPtr, newPriority, oldPriority, rtn)\
    {                                                               \
        rtn = OSA_TaskChangePriority( taskPtr, newPriority, oldPriority );  \
    }
#define OSA_TASK_GET_PRIORITY(taskPtr, oldPriority, rtn)            \
    {                                                               \
        rtn = OSA_TaskGetPriority( taskPtr, oldPriority );          \
    }
#define OSA_TASK_IDENTIFY(taskPtr)                                  \
    {                                                               \
    }
#define OSA_TASK_YIELD OSA_TaskSleep( 1 )
#define OSA_TASK_EQUAL(taskPtr, rtn)                                \
    {                                                               \
    }

/* Messaging */
#define OSA_QUEUE_CREATE(qRef, name, size, num, addr, mode, rtn)    \
    {                                                               \
        rtn = OSA_QueueCreate(qRef, name, size, num, addr, mode);\
    }
#define OSA_QUEUE_DELETE(qRef, rtn)                                 \
    {                                                               \
        rtn = OSA_QueueDelete(&qRef);                               \
    }
#define OSA_QUEUE_SEND(qRef, size, ptr, timeout, rtn)               \
    {                                                               \
        rtn = OSA_QueueSend(&qRef, size, ptr, timeout);             \
    }
#define OSA_QUEUE_RECV(qRef, msg, size, timeout, rtn)               \
    {                                                               \
        rtn = OSA_QueueRecv(&qRef, msg, size, timeout);             \
    }

#define OSA_QUEUE_POLL(qRef, msgCount, rtn)                         \
    {                                                               \
        rtn = OS_UNSUPPORTED;                                       \
    }

/* Mailboxes */
#define OSA_MAILBOX_CREATE(qRef, name, num, mode, rtn)              \
    {                                                               \
        rtn = OSA_QueueCreate((OS_MsgQ_t *)qRef, name, OSA_MAX_MBOX_DATA_SIZE, num, 0L, mode);    \
    }
#define OSA_MAILBOX_DELETE(qRef, rtn)                               \
    {                                                               \
        rtn = OSA_QueueDelete((OS_MsgQ_t *)&qRef);                  \
    }
#define OSA_MAILBOX_SEND(qRef, ptr, timeout, rtn)                   \
    {                                                               \
        rtn = OSA_QueueSend((OS_MsgQ_t *)&qRef, OSA_MAX_MBOX_DATA_SIZE, ptr, timeout); \
    }
#define OSA_MAILBOX_RECV(qRef, msg, timeout, rtn)                   \
    {                                                               \
        rtn = OSA_QueueRecv((OS_MsgQ_t *)&qRef, msg, OSA_MAX_MBOX_DATA_SIZE, timeout); \
    }
#define OSA_MAILBOX_POLL(qRef, msgCount, rtn)                       \
    {                                                               \
        rtn = OS_UNSUPPORTED;                                       \
    }

/* Events */
#define OSA_FLAG_CREATE(flagRef, name, rtn)                         \
    {                                                               \
        rtn = OSA_FlagCreate(flagRef, name);                        \
    }
#define OSA_FLAG_DELETE(flagRef, rtn)                               \
    {                                                               \
        rtn = OSA_FlagDelete(flagRef);                              \
    }

#define OSA_FLAG_SET_BITS(flagRef, mask, operation, rtn)            \
    {                                                               \
        rtn = OSA_FlagSetBits(flagRef, mask, operation);            \
    }

#define OSA_FLAG_WAIT(flagRef, reqValue, mode, currValue, timeout, rtn) \
    {                                                               \
        rtn = OSA_FlagWait(flagRef, reqValue, mode, currValue, timeout);  \
    }
#define OSA_FLAG_PEEK(flagRef, value, rtn)                          \
    {                                                               \
        *value = flagRef.flag;                                      \
        rtn = OS_SUCCESS;                                           \
    }


/* Timers */
#define OSA_TIMER_CREATE(timerRef, rtn)                             \
    {                                                               \
        rtn = OSA_TimerCreate(timerRef);                            \
    }
#define OSA_TIMER_DELETE(timerRef, rtn)                             \
    {                                                               \
        rtn = OSA_TimerDelete(&timerRef);                           \
    }

#define OSA_TIMER_START(timerRef, time, resched, handler,           \
                       argc, rtn)                                   \
    {                                                               \
        rtn = OSA_TimerStart(&timerRef, time, resched, handler, argc); \
    }
#define OSA_TIMER_STOP(timerRef, rtn)                               \
    {                                                               \
        rtn = OSA_TimerStop(&timerRef);                             \
    }
#define OSA_TIMER_STATUS(timerRef, status, rtn)                     \
    {                                                               \
        status->status        = timerRef.state;                     \
        status->expirations   = timerRef.expirations;               \
        rtn = OS_SUCCESS;                                           \
    }

#define OSA_MEM_ALLOC(pool, type, size, mem, timeout, rtn)          \
    {                                                               \
        rtn = OSA_MemAlloc( (void*)pool, type, size, mem, timeout );\
    }
#define OSA_MEM_FREE(pool, type, mem, rtn)                          \
    {                                                               \
        rtn = OSA_MemFree( (void*)pool, type, mem );                  \
    }
#define OSA_MEM_POOL_CREATE(pool, type, base, size, partition, mode, rtn) \
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
        rtn = OSA_SemaCreate(sema, name, initialCount, waitingMode);\
    }
#define OSA_SEMA_DELETE(sema, rtn)                                  \
    {                                                               \
        rtn = OSA_SemaDelete(&sema);                                \
    }

#define OSA_SEMA_ACQUIRE(sema, timeout, rtn)                        \
    {                                                               \
        rtn = OSA_SemaAcquire(&sema, timeout);                      \
    }
#define OSA_SEMA_RELEASE(sema, rtn)                                 \
    {                                                               \
        rtn = OSA_SemaRelease(&sema);                               \
    }
#define OSA_SEMA_POLL(sema, count, rtn)                             \
    {                                                               \
        rtn = OSA_SemaPoll(&sema, count);                           \
    }
    
/* Mutexes */
#define OSA_MUTEX_CREATE(mutex, name, waitingMode, rtn )            \
    {                                                               \
        rtn = OSA_MutexCreate(mutex, name);                         \
    }
#define OSA_MUTEX_DELETE(mutex, rtn)                                \
    {                                                               \
        rtn = OSA_MutexDelete(&mutex);                              \
    }
#define OSA_MUTEX_LOCK(mutex, timeout, rtn)                         \
    {                                                               \
        rtn = OSA_MutexLock(&mutex, timeout);                       \
    }

#define OSA_MUTEX_UNLOCK(mutex, rtn)                                \
    {                                                               \
        rtn = OSA_MutexUnlock(&mutex);                              \
    }

/* Context lock */
#define OSA_CONTEXT_LOCK OSA_ContextLock()

#define OSA_CONTEXT_UNLOCK OSA_ContextUnLock()

#define OSA_ISR_CREATE_FISR(isrNum, func, rtn)                      \
    {                                                               \
        rtn = OSA_FIsrCreate(isrNum, func);                         \
    }
#define OSA_ISR_CREATE_SISR(isrNum, isr, func, priority, stack, size, rtn)\
    {                                                               \
        rtn = OSA_SIsrCreate(isrNum, isr, func, priority, stack, size);\
    }
#define OSA_ISR_DELETE_SISR(isr, rtn)                               \
    {                                                               \
        rtn = OSA_SIsrDelete(isr);                                  \
    }
#define OSA_ISR_NOTIFY_SISR(isr, rtn)                               \
    {                                                               \
        rtn = OSA_SIsrNotify(isr);                                  \
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
        time = OSA_GetTicks();                                      \
    }
#define OSA_GET_SYSTEM_TIME(secsPtr, milliSecsPtr, rtn)             \
    {                                                               \
    }

#define OSA_CLOCK_TICK OSA_ClockTick()


#ifdef __cplusplus
}
#endif /* ifdef cplusplus */

#endif /* OSA_SYMBIAN */

#endif /* _OSA_SYMBIAN_H */
