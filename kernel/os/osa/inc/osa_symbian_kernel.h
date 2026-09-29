/* e32\personality\example\personality_int.h
 *
 * Copyright (c) 2003-2003 Symbian Ltd. All rights reserved.
 *
 * Internal header file for example RTOS personality.
 * This will be included by the personality layer source files.
 */

/**
@file
@internalComponent
*/

#ifndef __OSA_SYMBIAN_PERSONALITY_INT_H__
#define __OSA_SYMBIAN_PERSONALITY_INT_H__

//#include "personality.h"
#include "gbl_types.h"
//#include "osa_types.h"
//#include "osa.h"
#include "osa_config.h"
#include <kern_priv.h>

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

// NThreadBase member data
#define iNState iSpare1
/* Information required to create a task */
typedef struct _OS_taskInfo
    {
    void        *stackPtr;
    UINT32      stackSize;
    UINT8       priority;
    void        (*taskStart)(void*);
    CHAR        *taskName;
    UINT8       filler[3];
    } OS_taskInfo;

// dummy constructor
inline NThreadBase::NThreadBase()
    {
    }

class OS_PThread : public NThread
    {
public:
    enum OS_PThreadState
        {
        EWaitMsgQ = NThreadBase::ENumNStates,
        EWaitSemaphore
        };
public:
    static TInt Create(OS_PThread* aThread, const OS_taskInfo* aInfo);
    static void MsgQIDfcFn(TAny*);
    static void StateHandler(NThread* aThread, TInt aOp, TInt aParam);
    static void ExceptionHandler(TAny* aContext, NThread* aThread);
public:
    inline OS_PThread() : iMsgQIDfc(0,0) {} // dummy constructor
    void HandleSuspend();
    void HandleResume();
    void HandleRelease(TInt aReturnCode);
    void HandlePriorityChange(TInt aNewPriority);
    void HandleTimeout();
public:
    TInt    iSetPriority;
public:
    static const SNThreadHandlers Handlers;
    };

class OS_PMemPool;
struct SMemBlock
    {
    OS_PMemPool*    iPool;
    SMemBlock*      iNext;      // only if free block
    };

typedef struct _poolinfo
    {
    unsigned    block_size;
    unsigned    block_count;
    } poolinfo;

class OS_PMemPool
    {
public:
    TInt Create(const poolinfo* aInfo);
    void* Alloc();
    void Free(void* aBlock);
public:
    SMemBlock*  iFirstFree;
    unsigned    iBlockSize;
    };

class OS_PMemMgr
    {
public:
    static void Create(void);
    static void* Alloc(unsigned aSize);
    static void Free(void* aBlock);
public:
    TInt iPoolCount;
    OS_PMemPool iPools[1];      // extend
public:
    static OS_PMemMgr* TheMgr;
    };


typedef void (*timerCBPtrType)(UINT32);

class OS_PTimer : public NTimer
    {
public:
    OS_PTimer();
    static void NTimerExpired(TAny*);
public:
    TInt        iPeriod;    // 0 if single shot
    OS_PThread* iThread;
    TUint       iExpiryCount;
    UINT32      state;
    UINT32      ticksLeft;
    UINT32      timerArgc;
    timerCBPtrType  callback;
public:
    static TInt NumTimers;
    };


class OS_PSemaphore
    {
public:
    OS_PSemaphore();
    void WaitCancel(OS_PThread* aThread);
    void SuspendWaitingThread(OS_PThread* aThread);
    void ResumeWaitingThread(OS_PThread* aThread);
    void ChangeWaitingThreadPriority(OS_PThread* aThread, TInt aNewPriority);
    void Signal();
    void ISRSignal();
    static void IDfcFn(TAny*);
public:
    TInt iCount;
    TInt iISRCount;
    TDfc iIDfc;
    SDblQue iSuspendedQ;
    TPriList<OS_PThread, KNumPriorities> iWaitQ;
public:
    static TInt NumSemaphores;
    };

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

/*************************************************************************
 * WinCE Specific Types
 *************************************************************************/
 typedef void*          OSAFlagRef;
 typedef UINT32         OS_Hisr_t;
 typedef UINT8          OSA_STATUS;
 typedef OS_PMemPool    OS_MemPool_t;
 typedef OS_PSemaphore  *OS_Sema_t;
 typedef OS_PThread     *OS_Task_t;
 typedef OS_PTimer      *OS_Timer_t;
 
/* Remain for backwards compatibility */ 
 typedef UINT8              OS_STATUS;
 typedef void*              OSFlagRef;

// typedef TThreadFunction (*funcPtrType)(TAny*);
// typedef struct
// {
//    OS_PThread  *os_task;
// } OS_Task_t;

// typedef struct _OS_Sema_t
// {
//    UINT32  os_sema;
// } OS_Sema_t;


/* Mutex reference */
 typedef struct
 {
    NFastMutex  *os_mutex;
    BOOL        locked;
    OS_Task_t   owner;
    UINT8       mutexName[OSA_MAX_TASK_NAME_SIZE];
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
// typedef struct
// {
//    OS_PTimer   *os_timer;
// } OS_Timer_t; 
        
/* Timer status information structure */
 typedef struct
 {
    UINT32    status;           /* timer status OS_ENABLED, OS_DISABLED    */
    UINT32    expirations;      /* number of expirations for cyclic timers */
 } OSATimerStatus;


 /*=======================================================================
  *  OS Memory Pool Structure
  *======================================================================*/
#if (OSA_MEM_POOLS)
  typedef struct _OS_Mem
  {
    union
    {   
        OS_MemPool_t        vPoolRef;   /* Variable pool ref */
        OS_PartitionPool_t  fPoolRef;   /* Fixed pool ref */
    }u;
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
    OS_Flag         *head;                  /* Active queue list */
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
#endif
  } OS_MsgQueue;

  typedef struct
  {
    UINT32          numCreated;
    OS_Sema_t       poolSemaphore;
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
#endif
  } OS_Mbox;

  typedef struct
  {
    UINT32          numCreated;             /* # created mailboxes */
    OS_Sema_t       poolSemaphore;          /* timer pool semaphore */
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
  } OS_Mutex;


  typedef struct
  {
    UINT32          numCreated;
    UINT32          counter;
    OS_Sema_t       poolSemaphore;
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
  
  typedef struct
  {
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

  } OSA_ControlBlock;


EXPORT_C OSA_STATUS OSA_QueueCreate ( OS_MsgQ_t *msgQRef, char *queueName, UINT32 maxSize, UINT32 maxNumber, void *queueAddr, UINT8 waitingMode );
EXPORT_C OSA_STATUS OSA_QueueDelete ( OS_MsgQ_t *msgQRef );
EXPORT_C OSA_STATUS OSA_QueueSend   ( OS_MsgQ_t *msgQRef, UINT32 size, UINT8 *msg, UINT32 timeout);
EXPORT_C OSA_STATUS OSA_QueueRecv   ( OS_MsgQ_t *msgQRef, UINT8 *msg, UINT32 size, UINT32 timeout );
EXPORT_C OSA_STATUS OSA_QueuePoll   ( OS_MsgQ_t *msgQRef, UINT32 *msgCount );

EXPORT_C OSA_STATUS OSA_FlagCreate  ( OS_Flag_t *flagRef, UINT8 * );
EXPORT_C OSA_STATUS OSA_FlagDelete  ( OS_Flag_t *flagRef);
EXPORT_C OSA_STATUS OSA_FlagSetBits ( OS_Flag_t *flagRef, UINT32 mask, UINT32 operation);
EXPORT_C OSA_STATUS OSA_FlagWait    ( OS_Flag_t *flagRef, UINT32 mask, UINT32 operation, UINT32* flags, UINT32 timeout );

EXPORT_C OSA_STATUS OSA_SemaCreate  ( OS_Sema_t *sema, UINT8 *, UINT32 initialCount, UINT8 waitingMode );
EXPORT_C OSA_STATUS OSA_SemaDelete  ( OS_Sema_t *sema );
EXPORT_C OSA_STATUS OSA_SemaAcquire ( OS_Sema_t *sema, UINT32 timeout );
EXPORT_C OSA_STATUS OSA_SemaRelease ( OS_Sema_t *sema );

EXPORT_C OSA_STATUS OSA_TimerCreate ( OS_Timer_t *timer );
EXPORT_C OSA_STATUS OSA_TimerStart  ( OS_Timer_t *timer, UINT32 time, UINT32 resched, void (*handler)(UINT32), UINT32 argc );
EXPORT_C OSA_STATUS OSA_TimerStop   ( OS_Timer_t *timer );
EXPORT_C OSA_STATUS OSA_TimerGetStatus( OS_Timer_t *timer, OSATimerStatus* status );

EXPORT_C OSA_STATUS OSA_MutexCreate ( OS_Mutex_t *mutex, char* name );
EXPORT_C OSA_STATUS OSA_MutexDelete ( OS_Mutex_t *mutex );
EXPORT_C OSA_STATUS OSA_MutexLock   ( OS_Mutex_t *mutex, UINT32 timeout );
EXPORT_C OSA_STATUS OSA_MutexUnlock ( OS_Mutex_t *mutex );

EXPORT_C OSA_STATUS OSA_MemPoolCreate( OS_PartitionPool_t *pool, UINT32 poolType, UINT8 *poolBase, UINT32 poolSize, UINT32 partitionSize);
EXPORT_C OSA_STATUS OSA_MemPoolDelete( OS_PartitionPool_t *pool, UINT32 poolType );
EXPORT_C OSA_STATUS OSA_MemAlloc    ( void *pool, UINT32 poolType, UINT32 size, void **mem, UINT32 timeout );
EXPORT_C OSA_STATUS OSA_MemFree     ( void *pool, UINT32 poolType, void* mem );
 /*=======================================================================
  *  Macros
  *======================================================================*/
  
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
        rtn = OSA_QueuePoll(&qRef, msgCount);                       \
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
        Kern::Free((TAny*)timerRef);                                \
        rtn = OS_SUCCESS;                                           \
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
        status->status        = timerRef->state;                    \
        status->expirations   = timerRef->iExpiryCount;             \
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
        Kern::Free((TAny*)sema);                                    \
        rtn = OS_SUCCESS;                                           \
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
        *count = sema->iCount;                                      \
        rtn = OS_SUCCESS;                                           \
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
#define OSA_CONTEXT_LOCK NKern::Lock()

#define OSA_CONTEXT_UNLOCK NKern::Unlock()

#define OSA_GET_SYSTEM_TIME(secsPtr, milliSecsPtr, rtn)             \
    {                                                               \
    }

    

/* Checks reference for NULL and validates with current stored value */
/*   ref   - api reference tested for NULL                           */
/*   osRef - tested for valid stored pointer to internal reference   */
#ifndef OSA_DEBUG
#define OSA_REF_CHECK
#else
#define OSA_REF_CHECK(ref, osRef)\
    {\
        if(ref == NULL)\
            return(OS_INVALID_REF);\
        if(osRef->refCheck != &osRef->os_ref)\
            return(OS_INVALID_REF);\
    }
#endif


#define OSA_GET_REF(pool, ref, size) \
    { \
        OSA_STATUS rtn; \
        if(!((void*)ref = Kern::AllocZ((UINT32)size)) ) { \
            return(OS_FAIL); } \
        NKern::Lock(); \
        OSA_ADD_TO_ACTIVE_LIST((pool->head), ref); \
        pool->numCreated++; \
        NKern::Unlock(); \
        ref->refCheck = (void *)ref; \
    }
#define OSA_DELETE_REF(pool, ref) \
    { \
        OSA_STATUS rtn; \
        NKern::Lock(); \
        OSA_DELETE_FROM_ACTIVE_LIST((pool->head), ref); \
        pool->numCreated--; \
        NKern::Unlock(); \
        ref->refCheck = NULL; \
        Kern::Free(ref); \
    }

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

#endif
