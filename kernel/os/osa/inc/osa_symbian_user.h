/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : osa_symbian_user.h
Description : Definition of OSA Software Layer data types specific to the 
              Symbian EPOC OS for user mode code.

Notes       : 

Copyright (c) 2001 Intel CCD. All Rights Reserved
=========================================================================== */
#ifndef _OSA_SYMBIAN_USER_H
#define _OSA_SYMBIAN_USER_H


#ifdef ENV_SYMBIAN

#include <stdlib.h>
#include <string.h>
#include "gbl_types.h"
#include "osa_config.h"
#include "e32svr.h"
#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************
 * Constants
 *************************************************************************/
#define OSA_POOL_MEM_OVERHEAD           8   /* Fixed pool overhead per partition */
#define OSA_FIXED_POOL_MEM_OVERHEAD     sizeof(OS_PartMemHdr)   /* Fixed pool overhead per partition */
#define OSA_VAR_POOL_MEM_OVERHEAD       12  /* Variable pool overhead per partition */
#define OSA_MAX_TASK_NAME_SIZE          8
#define OSA_MAX_PRIORITY                31
#define OSA_MAX_NATIVE_PRIORITY         1000      /* Symbian priorities are 0 lowest to 1000 highest (opposite to OSA) */

 #define  OSA_NUM_GLOBAL_MEM_CELLS      5
 #define  OSA_GLOBAL_MEM_NAME_SIZE      10
 
 #define  OSA_ISRS_MAX                  32  /* Max number of ISR's (fixed)     */
 #define  OSA_MAX_MBOX_DATA_SIZE        4
 #define  OSA_MEMORY_ALIGN              (0x3)
 #define  OSA_SISR_PRIORITY             1
 #define  OSA_VAR_MEM_OVERHEAD          4  /* Variable queue memory overhead per message */
 #define  OSA_TASK_DELETED              0
 #define  OSA_TASK_RUNNING              1
 #define  OSA_TASK_SUSPENDED            2

 #define  OSA_EVENT_HISR_MAX_ENTRIES    256
 #define  OSA_EVENT_HISR_STACK_SIZE     (OSA_MIN_STACK_SIZE)
 #define  OSA_EVENT_HISR_PRIORITY       0 
 #define  OSA_SISR_STACK_SIZE           512
 #define  OSA_NAME_SIZE                 8 
 #define  OSA_MEM_CHECK_SIG             0xA5


/*************************************************************************
 * Symbian Specific Types
 *************************************************************************/
 typedef UINT32         OS_Hisr_t;
 typedef UINT32         OS_MemPool_t;
 
/* Task Reference */
 typedef void (*funcPtrType)(void*);
 typedef struct
 {
    RThread     *task;
    funcPtrType taskStartPtr;
    void        *argv;
    TThreadId   id;
 } OS_Task_t;

/* Semaphore reference */
 typedef struct
 {
    RSemaphore  os_sema;
    TInt        id;
    UINT32      count;
 } OS_Sema_t;

/* Mutex reference */
 typedef struct
 {
    RMutex  os_mutex;
    TInt    id;
    UINT32  owner;
    UINT32  locked;
 } OS_Mutex_t;

/* Flag reference */
 typedef struct
 {
    UINT32          flag;
    OS_Sema_t       semaphore;
 } OS_Flag_t;

/* Partition memory pool reference */
 typedef struct
 {
    struct _OS_PartMemHdr   *free;      /* Free partition list */
    OS_Mutex_t              mutex;      /* Mutex to secure access */
    OS_Sema_t               sema;       /* Sema for blocking when no mem left */
    UINT32                  numFree;    /* Number of partitions free */
    TInt                    id;
    RChunk                  *chunk;
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

#ifndef OSA_USE_INTERNAL_MESSAGING
/* Message Queue reference */
 typedef struct
 {
    RMsgQueueBase   *os_queue;
    TInt            id;
    UINT32          maxSize;
    UINT32          maxNum;
 } OS_MsgQ_t;

/* Mailbox Queue reference */
 typedef struct
 {
    RMsgQueueBase   os_queue;
    TInt            id;
 } OS_Mbox_t;

#else
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
#endif

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
        



 /*=======================================================================
  *  OS Memory Pool Structure
  *======================================================================*/
#if (OSA_MEM_POOLS)
  typedef struct _OS_Mem
  {
    OS_MemPool_t        vPoolRef;   /* Variable pool ref */
    OS_PartitionPool_t  fPoolRef;   /* Fixed pool ref */
    UINT32          type;               /* Pool type OSA_FIXED/OSA_VARIABLE */
    void            *refCheck;
    UINT8           *poolBase;
    UINT32          poolSize;
    UINT32          partitionSize;
    struct _OS_Mem  *next;
    struct _OS_Mem  *prev;
  } OS_Mem;
    
  typedef struct
  {
    UINT32          numCreated;             /* # created memory pools */
    OS_Sema_t       poolSemaphore;          /* pool semaphore */
    OS_Mem          memPools[OSA_MEM_POOLS_MAX]; /* Memory pools */
    OS_Mem          *head;                  /* Active list */
    OS_Mem          *free;                  /* Free list */
  } OS_MemPool;
#endif
 
 /*=======================================================================
  *  OS Task Structures
  *=====================================================================*/
#if (OSA_TASKS)
  typedef struct _OS_Task
  {
    OS_Task_t         os_ref;
    void              *refCheck;
    struct _OS_Task*  next;
    struct _OS_Task*  prev;
    UINT8             state;
    char              name[OSA_NAME_SIZE];    /* Service name */
    UINT8             padding[3];
  } OS_Task;

  typedef struct
  {
    UINT32          numCreated;
    OS_Sema_t       poolSemaphore;
    OS_Task         task[OSA_TASKS_MAX];
    OS_Task         *free;                  /* Free list */
    OS_Task         *head;                  /* Active list */
  } OS_TaskPool;
#endif

 /*=======================================================================
  *  Event Flag Structures
  *======================================================================*/
#if (OSA_FLAGS)
  typedef struct _OS_Flag
  {
    OS_Flag_t       os_ref;
    void            *refCheck;
    UINT32          eventMask;
    struct _OS_Flag *next;
    struct _OS_Flag *prev;
  } OS_Flag;

  typedef struct
  {
    UINT32          numCreated;
    OS_Sema_t       poolSemaphore;
    UINT32          counter;
    OS_Flag         eventGroups[OSA_FLAGS_MAX];  
    OS_Flag         *head;                  /* Active queue list */
    OS_Flag         *free;                  /* Free queue list */
  } OS_FlagPool;
#endif

 /*========================================================================
  *  OS Message Structures
  *========================================================================*/
#if (OSA_MSG_QUEUES)
  typedef struct _OS_MsgQueue
  {
    OS_MsgQ_t           os_ref;               /* OS queue reference */
    void                *refCheck;
    struct _OS_MsgQueue *next;
    struct _OS_MsgQueue *prev;
    UINT32              msgCount;
#ifdef OSA_DEBUG
    UINT32              maxNumber;
    UINT32              maxMsgSize;
    UINT32              totalMsgReceived;     /* used for statistics */  
    UINT32              totalBytesReceived;
    UINT32              maxMsgInQueue;
    struct _OSA_ControlBlock    *controlBlock;
    OS_Sema_t           *poolSema;
#endif
  } OS_MsgQueue;

  typedef struct
  {
    UINT32          numCreated;
    OS_Sema_t       poolSemaphore;
    OS_MsgQueue     queues[OSA_MSG_QUEUES_MAX];
    OS_MsgQueue     *free;                  /* Free queue list */
    OS_MsgQueue     *head;                  /* Active queue list */
  } OS_MsgQPool;
#endif

 /*=======================================================================
  *  OS Mailbox Structures
  *=====================================================================*/
#if (OSA_MBOX_QUEUES)
  typedef struct _OS_Mbox
  {
    OS_Mbox_t       os_ref;
    void            *refCheck;
    struct _OS_Mbox *next;
    struct _OS_Mbox *prev;
    UINT32          msgCount;
#ifdef OSA_DEBUG
    UINT32          maxNumber;
    UINT32          totalMsgReceived;     /* used for statistics */  
    UINT32          maxMsgInQueue;
    OSA_ControlBlock    *controlBlock;
    OS_Sema_t           *poolSema;
#endif
  } OS_Mbox;

  typedef struct
  {
    UINT32          numCreated;             /* # created mailboxes */
    OS_Sema_t       poolSemaphore;          /* timer pool semaphore */
    OS_Mbox         mboxes[OSA_MBOX_QUEUES_MAX]; /* Mailboxes */
    OS_Mbox         *free;                  /* Free mailbox list */
    OS_Mbox         *head;                  /* Active mailbox list */
  } OS_MboxPool;
#endif

 /*=======================================================================
  *  OS Timer Structures
  *=====================================================================*/
#if (OSA_TIMERS)
  typedef struct _OS_Timer
  {
    OS_Timer_t       os_ref;
    void             *refCheck;
    UINT32           state;
    struct _OS_Timer *next;
    struct _OS_Timer *prev;
  } OS_Timer;

  typedef struct
  {
    UINT32          numCreated;             /* # created timers */
    OS_Sema_t       poolSemaphore;          /* timer pool semaphore */
    OS_Timer        timers[OSA_TIMERS_MAX];  /* Timers */
    OS_Timer        *free;                  /* Free timers list */
    OS_Timer        *head;                  /* Active timers list */
  } OS_TimerPool;
#endif

 /*=======================================================================
  *  Semaphore
  *=====================================================================*/
#if (OSA_SEMAPHORES)
  typedef struct _OS_Sema
  {
    OS_Sema_t        os_ref;
    void             *refCheck;
    struct _OS_Sema  *next;
    struct _OS_Sema  *prev;
  } OS_Sema;


  typedef struct
  {
    UINT32           numCreated;
    OS_Sema_t        poolSemaphore;
    OS_Sema          semaphores[OSA_SEMAPHORES_MAX];
    OS_Sema          *free;
    OS_Sema          *head;
    UINT32           counter;
  } OS_SemaPool;
#endif

 /*=======================================================================
  *  Mutex
  *=====================================================================*/
#if (OSA_MUTEXES)
  typedef struct _OS_Mutex
  {
    OS_Mutex_t        os_ref;
    void              *refCheck;
    OS_Task_t         *owner;
    struct _OS_Mutex  *next;
    struct _OS_Mutex  *prev;
    UINT8             basePriority;     /* Orig priority for priority inheritance */
    UINT8             currentPriority;  /* Highest priority of waiting tasks      */
    UINT8             highestWaiting;   /* Max priority of tasks waiting          */
    UINT8             numTasks;         /* # tasks in mutex Q including owner     */
    OS_Sema_t         *poolSema;
  } OS_Mutex;


  typedef struct
  {
    UINT32          numCreated;
    UINT32          counter;
    OS_Sema_t       poolSemaphore;
    OS_Mutex        mutexes[OSA_MUTEXES_MAX];
    OS_Mutex        *free;
    OS_Mutex        *head;
  } OS_MutexPool;
#endif

#if (OSA_INTERRUPTS)
 /*=======================================================================
  *  Interrupts
  *======================================================================*/
  typedef struct _OS_Isr
  {
    OS_Hisr_t       os_ref;
    void            *refCheck;
    UINT32          eventMask;
  } OS_Isr;

  typedef struct
  {
    UINT32          numCreated;
  } OS_IsrPool;
#endif

 /*=======================================================================
  *  OS Global Memory
  *======================================================================*/
#if (OSA_GLOBAL_MEM_POOL_SIZE)  

  typedef struct
  {
    char              name[OSA_GLOBAL_MEM_NAME_SIZE];
    UINT32            size;
    UINT32            offset;   // Offset into the global memory pool
    OS_Mutex_t        mutex;
  } OS_GlobalMemCell;

  typedef struct
  {
    UINT8             numCells;
    UINT32            bytesRemaining;
    OS_Mutex_t        mutex;
    OS_GlobalMemCell  cell[OSA_NUM_GLOBAL_MEM_CELLS];
    char              mem[OSA_GLOBAL_MEM_POOL_SIZE];
  } OS_GlobalMemPool;

#endif

 /*=======================================================================
  *  OS Statistics
  *======================================================================*/
  
  typedef struct
  {
    UINT32      sysMsgCount;                        /* System msg counter */
    UINT32      sysMaxMsgAllowed;                   /* Max msgs in system */
    UINT32      sysTotalMsgReceived;                /* Sys tot msg received */
    UINT32      sysMaxMsgs;                         /* Max # msgs in sys queue */
    UINT32      sysMboxCount;
    UINT32      sysMaxMboxAllowed;
    UINT32      sysTotalMboxReceived;
    UINT32      sysMaxMboxMsgs;
  } OS_SystemStats;


 /*=======================================================================
  *  OS Control Block
  *======================================================================*/
  
  typedef struct _OSA_ControlBlock
  {
     OS_Sema_t            csOSAContextLock;  //Tianbo: global context lock for user
     OS_Sema_t            csOSAContextLockInternal;  // For internal OSA usage
     OS_Sema_t            OSA_TickSemaphore;
     UINT32               OSA_RtcCounter; 
     OS_Task_t            OSATimerTask;
     OS_Task_t            OSATickTask;
     RChunk               globalChunk;
#if (OSA_MSG_QUEUES)
     OS_MsgQPool          msgQPool;
#endif
#if (OSA_MBOX_QUEUES)
     OS_MboxPool          mboxPool;
#endif
#if (OSA_TASKS)
     OS_TaskPool          taskPool;
#endif
#if (OSA_TIMERS)
     OS_TimerPool         timerPool;
#endif
#if (OSA_SEMAPHORES)
     OS_SemaPool          semaPool;
#endif
#if (OSA_MUTEXES)
     OS_MutexPool         mutexPool;
#endif
#if (OSA_FLAGS)
     OS_FlagPool          eventPool;
#endif
#if (OSA_INTERRUPTS)
     OS_IsrPool           isrPool;
#endif
#ifdef OSA_DEBUG
     OS_SystemStats       stats;
#endif
#if (OSA_MBOX_QUEUES && OSA_MEM_POOLS)
     OS_MemPool_t         mboxPoolMem;
#endif
#if (OSA_MSG_QUEUES && OSA_MEM_POOLS)
     OS_MemPool_t         heapPool;
#endif
#if (OSA_MEM_POOLS)
     OS_MemPool           memPool; 
#endif
#if (OSA_GLOBAL_MEM_POOL_SIZE)
     OS_GlobalMemPool     memGlobalPool;
#endif

  } OSA_ControlBlock;


OSA_STATUS OSA_TaskCreate( OS_Task_t *, UINT8 *, UINT8, UINT32, void(*)(void*), void *);
OSA_STATUS OSA_TaskDelete  ( OS_Task_t task ); 
OSA_STATUS OSA_TaskSuspend ( OS_Task_t task );
OSA_STATUS OSA_TaskResume  ( OS_Task_t task );
OSA_STATUS OSA_TaskGetPriority( OS_Task_t *task, UINT8 *oldPriority);
OSA_STATUS OSA_TaskChangePriority( OS_Task_t *task, UINT8 newPriority, UINT8 *oldPriority);
void OSA_TaskSleep  ( UINT32 ticks ); 

OSA_STATUS OSA_QueueCreate ( OS_MsgQ_t *msgQRef, char *queueName, UINT32 maxSize, UINT32 maxNumber, void *queueAddr, UINT8 waitingMode );
OSA_STATUS OSA_QueueDelete ( OS_MsgQ_t *msgQRef );
OSA_STATUS OSA_QueueSend   ( OS_MsgQ_t *msgQRef, UINT32 size, UINT8 *msg, UINT32 timeout);
OSA_STATUS OSA_QueueRecv   ( OS_MsgQ_t *msgQRef, UINT8 *msg, UINT32 size, UINT32 timeout );
OSA_STATUS OSA_QueuePoll   ( OS_MsgQ_t *msgQRef, UINT32 *msgCount );

OSA_STATUS OSA_FlagCreate  ( OS_Flag_t *flagRef, char * );
OSA_STATUS OSA_FlagDelete  ( OS_Flag_t *flagRef);
OSA_STATUS OSA_FlagSetBits ( OS_Flag_t *flagRef, UINT32 mask, UINT32 operation);
OSA_STATUS OSA_FlagWait    ( OS_Flag_t *flagRef, UINT32 mask, UINT32 operation, UINT32* flags, UINT32 timeout );

OSA_STATUS OSA_SemaCreate  ( OS_Sema_t *sema, char *, UINT32 initialCount, UINT8 waitingMode );
OSA_STATUS OSA_SemaDelete  ( OS_Sema_t *sema );
OSA_STATUS OSA_SemaAcquire ( OS_Sema_t *sema, UINT32 timeout );
OSA_STATUS OSA_SemaRelease ( OS_Sema_t *sema );
OSA_STATUS OSA_SemaPoll ( OS_Sema_t *sema, UINT32 *count );

OSA_STATUS OSA_TimerCreate ( OS_Timer_t *timer );
OSA_STATUS OSA_TimerDelete ( OS_Timer_t *timer );
OSA_STATUS OSA_TimerStart  ( OS_Timer_t *timer, UINT32 time, UINT32 resched, void (*handler)(UINT32), UINT32 argc );
OSA_STATUS OSA_TimerStop   ( OS_Timer_t *timer );
OSA_STATUS OSA_TimerGetStatus( OS_Timer_t *timer, OSATimerStatus* status );
void OSA_ClockTick(OSA_ControlBlock*);
UINT32 OSA_GetTicks(void);

OSA_STATUS OSA_MutexCreate ( OS_Mutex_t *mutex, char* name );
OSA_STATUS OSA_MutexDelete ( OS_Mutex_t *mutex );
OSA_STATUS OSA_MutexLock   ( OS_Mutex_t *mutex, UINT32 timeout );
OSA_STATUS OSA_MutexUnlock ( OS_Mutex_t *mutex );

OSA_STATUS OSA_MemPoolCreate( OS_Mem *pool, UINT32 poolType, UINT8 *poolBase, UINT32 poolSize, UINT32 partitionSize);
OSA_STATUS OSA_MemPoolDelete( OS_Mem *pool, UINT32 poolType );
OSA_STATUS OSA_MemAlloc    ( OS_Mem *pool, UINT32 poolType, UINT32 size, UINT32 partSize, void **mem, UINT32 timeout );
OSA_STATUS OSA_MemFree     ( OS_Mem *pool, UINT32 poolType, void* mem );

BOOL OSA_GetControlBlock(OSA_ControlBlock** );

OS_GlobalMemCell* OSA_FindGlobalMemCell(const char* name);

 /*=======================================================================
  *  Macros
  *======================================================================*/

/* Task Management */  
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
        TTimeIntervalMicroSeconds32 sleep(ticks*1000);              \
        User::After(sleep);                                         \
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
        OSA_ControlBlock* block;                                    \
        BOOL stat = OSA_GetControlBlock(&block);                    \
        TThreadId currentId;                                        \
        OS_Task *task = block->taskPool.head;                       \
        if(NULL == task) OSA_ASSERT (FALSE);                        \
        currentId = RThread().Id();                                 \
        while(task != NULL) {                                       \
            if(currentId == task->os_ref.id)                  \
            {                                                       \
                taskPtr = (OS_Task_t *)&task->os_ref;               \
                break;                                              \
            }                                                       \
            task = task->next;                                      \
        }                                                           \
    }
#define OSA_TASK_YIELD OSA_TaskSleep( 1 )
#define OSA_TASK_EQUAL(taskPtr, rtn)                                \
    {                                                               \
    }


/* Messaging */
#define OSA_QUEUE_CREATE(qRef, name, size, num, addr, mode, rtn)    \
    {                                                               \
        rtn = OSA_QueueCreate(qRef, name, size, num, addr, mode);   \
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
        rtn = OSA_QueueCreate(&qRef, name, OSA_MAX_MBOX_DATA_SIZE, num, 0L, mode);    \
    }
#define OSA_MAILBOX_DELETE(qRef, rtn)                               \
    {                                                               \
        rtn = OSA_QueueDelete(&(OS_MsgQ_t)qRef);                    \
    }
#define OSA_MAILBOX_SEND(qRef, ptr, timeout, rtn)                   \
    {                                                               \
        rtn = OSA_QueueSend(&(OS_MsgQ_t)qRef, OSA_MAX_MBOX_DATA_SIZE, ptr, timeout); \
    }
#define OSA_MAILBOX_RECV(qRef, msg, timeout, rtn)                   \
    {                                                               \
        rtn = OSA_QueueRecv(&(OS_MsgQ_t)qRef, msg, OSA_MAX_MBOX_DATA_SIZE, timeout); \
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

/* Memory Management */
#define OSA_MEM_ALLOC(pool, type, size, partSize, mem, timeout, rtn)\
    {                                                               \
        rtn = OSA_MemAlloc( pool, type, size, partSize, mem, timeout );\
    }
#define OSA_MEM_FREE(pool, type, mem, rtn)                          \
    {                                                               \
        rtn = OSA_MemFree( pool, type, mem );                \
    }
#define OSA_MEM_POOL_CREATE(pool, type, base, size, partition, mode, rtn) \
    {                                                               \
        rtn = OSA_MemPoolCreate(pool, type, base, size, partition); \
    }
#define OSA_MEM_POOL_DELETE(pool, type, rtn)                        \
    {                                                               \
        rtn = OSA_MemPoolDelete(pool, type);                        \
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

// Tianbo: changed to reflect the global context lock
#define OSA_CONTEXT_LOCK                                            \
    {                                                               \
        OSA_ControlBlock* block;                                    \
        OSA_STATUS ret;                                             \
        BOOL stat = OSA_GetControlBlock(&block);                    \
        OSA_SEMA_ACQUIRE(block->csOSAContextLock, OSA_SUSPEND, ret);\
    }

 // Tianbo: changed to reflect global context lock          
#define OSA_CONTEXT_UNLOCK                                          \
    {                                                               \
        OSA_ControlBlock* block;                                    \
        OSA_STATUS ret;                                             \
        BOOL stat = OSA_GetControlBlock(&block);                    \
        OSA_SEMA_RELEASE(block->csOSAContextLock, ret);             \
    }

/* Need internal context lock for OSA as it conflicts with one used by user */
#define OSA_CONTEXT_LOCK_INTERNAL                                   \
    {                                                               \
        OSA_ControlBlock* block;                                    \
        OSA_STATUS ret;                                             \
        BOOL stat = OSA_GetControlBlock(&block);                    \
        OSA_SEMA_ACQUIRE(block->csOSAContextLockInternal, OSA_SUSPEND, ret); \
    }

 // Tianbo: changed to reflect global context lock          
#define OSA_CONTEXT_UNLOCK_INTERNAL                                 \
    {                                                               \
        OSA_ControlBlock* block;                                    \
        OSA_STATUS ret;                                             \
        BOOL stat = OSA_GetControlBlock(&block);                    \
        OSA_SEMA_RELEASE(block->csOSAContextLockInternal, ret);     \
    }

#define OSA_GET_SYSTEM_TIME(secsPtr, milliSecsPtr, rtn)             \
    {                                                               \
    }
#define OSA_CLOCK_TICK(a) OSA_ClockTick(a)

    

/* Checks reference for NULL and validates with current stored value */
/*   ref   - api reference tested for NULL                           */
/*   osRef - tested for valid stored pointer to internal reference   */
#ifndef OSA_DEBUG
#define OSA_REF_CHECK
#else
#define OSA_REF_CHECK(ref, osRef)\
    {\
        OSA_ASSERT(ref!=NULL);\
        if(ref == NULL)\
            return(OS_INVALID_REF);\
        OSA_ASSERT(osRef->refCheck==&osRef->os_ref);\
        if(osRef->refCheck != &osRef->os_ref) \
            return(OS_INVALID_REF);\
    }
#endif


#ifdef OSA_USE_DYNAMIC_REFS
#define OSA_GET_REF(pool, ref, size) \
    { \
        if(!((void*)ref = User::Alloc((UINT32)size)) ) { \
            OSA_ASSERT (FALSE); } \
        ref->refCheck = (void *)ref; \
    }
#define OSA_DELETE_REF(pool, ref) \
    { \
        ref->refCheck = NULL; \
        User::Free(ref); \
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

 /* Linked List management macros. Structure must have *next & *prev. */

 /* Add the item to the front of the list */
#define OSA_ADD_TO_ACTIVE_LIST(head, item)  {\
    item->prev = OS_NULL;\
    if (head == OS_NULL) { \
        head = item;\
        item->next = OS_NULL;} \
    else {\
        head->prev = item; \
        item->next = head;\
        head = item; }}

/* Delete the item from the active list */
#define OSA_DELETE_FROM_ACTIVE_LIST(head, item) {\
    if (item->prev != OS_NULL) {\
        (item->prev)->next = item->next; }\
    else {\
        head = item->next; }\
    if (item->next != OS_NULL) {\
        (item->next)->prev = item->prev;} \
    item->prev = OS_NULL;\
    item->next = OS_NULL; }

/* Get the first item from the free list */
#define OSA_GET_FROM_FREE_LIST(head, item) {\
    if (head != OS_NULL)  {\
        item = head;\
        head = head->next;\
        item->next = OS_NULL;} \
    else {\
        item = OS_NULL; }}

/* Add to the front of the free list */
#define OSA_ADD_TO_FREE_LIST(head, item) {\
    item->next = OS_NULL;\
    item->next = head;\
    head = item; }

#ifdef __cplusplus
}
#endif /* ifdef cplusplus */

#endif /* OSA_SYMBIAN */

#endif /* _OSA_SYMBIAN_H */
