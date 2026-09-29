/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : osa_nucleus.h
Description : Definition of OSA Software Layer data types specific to the
              Nucleus OS.

Notes       :

Copyright (c) 2001 Intel CCD. All Rights Reserved
=========================================================================== */
#ifndef _OSA_NUCLEUS_H
#define _OSA_NUCLEUS_H


#ifdef OSA_NUCLEUS

#include "stddef.h"    /*for size_t */ 
#include "nucleus.h"
#include "osa_types.h"
#include "gbl_types.h"
#include "osa.h"

/************************************************************************
 * External Interfaces
 ***********************************************************************/
#ifdef OSA_PC_TEST
    #include <stdio.h>

    /* These definitions are needed as we do not yet have the INTC
     * package yet from Israel.
     */
    typedef UINT32                       INTC_InterruptSources;
    #define INTC_RC_OK                   0
    #define INTC_MAX_INTERRUPT_SOURCES   110

#else
    #include "intc.h"
#endif

extern void TMT_Timer_Interrupt(void); /* Nucleus+ real-time clock int */
/*************************************************************************
 * Constants
 *************************************************************************/
#define OSA_POOL_MEM_OVERHEAD         8   /* Fixed pool overhead per partition */
#define OSA_FIXED_POOL_MEM_OVERHEAD   sizeof(OS_PartMemHdr)   /* Fixed pool overhead per partition */
#define OSA_VAR_POOL_MEM_OVERHEAD     12  /* Variable pool overhead per partition */
#define OSA_MAX_TASK_NAME_SIZE        8
#define OSA_MAX_PRIORITY              31
#define OSA_MAX_NATIVE_PRIORITY       255  /* Nucleus priorities are 255 lowest to 0 highest */

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

 #ifdef PLAT_USE_THREADX
  /*************************************************************************
  * Threadx Specific Types
  *************************************************************************/
 typedef TX_THREAD            OS_Task_t;
 typedef TX_SEMAPHORE       OS_Sema_t;
 typedef TX_SEMAPHORE       OS_Mutex_t;
 typedef TX_TIMER           OS_Timer_t;
 typedef TX_EVENT_FLAGS_GROUP		OS_EventGroup_t;
 typedef TX_EVENT_FLAGS_GROUP     	OS_Flag_t;
 typedef void*	            OS_Hisr_t;  
 typedef TX_BYTE_POOL		OS_MemPool_t;
 typedef TX_BLOCK_POOL  	OS_PartitionPool_t;
 typedef STATUS             NU_RTN_STATUS;			//TODO:
 typedef UINT32             OS_Proc_t;


 typedef struct
 {
    TX_QUEUE    os_ref;
    void        *queueMem;
    BOOL        externalMem;
    UINT8       filler[3];
 } OS_MsgQ_t;

 typedef struct
 {
    TX_QUEUE     os_ref;
    void        *queueMem;
 } OS_Mbox_t;

#elif defined(PLAT_USE_ALIOS)

 /*************************************************************************
 * AliOS Specific Types
 *************************************************************************/

typedef void* not_used_type_of_alios;

typedef not_used_type_of_alios		OS_Task_t;
typedef not_used_type_of_alios		OS_Sema_t;
typedef not_used_type_of_alios		OS_Mutex_t;
typedef not_used_type_of_alios		OS_Timer_t;
typedef not_used_type_of_alios		OS_EventGroup_t;
typedef not_used_type_of_alios		OS_Flag_t;
typedef not_used_type_of_alios		OS_Hisr_t;	
typedef not_used_type_of_alios		OS_MemPool_t;
typedef not_used_type_of_alios		OS_PartitionPool_t;
typedef STATUS 				NU_RTN_STATUS;			//TODO:
typedef UINT32 				OS_Proc_t;


typedef struct
{
	not_used_type_of_alios   os_ref;
	void		*queueMem;
	BOOL		externalMem;
	UINT8		filler[3];
} OS_MsgQ_t;

typedef struct
{
	not_used_type_of_alios  os_ref;
	void		*queueMem;
} OS_Mbox_t;



#else
/*************************************************************************
 * Nucleus Specific Types
 *************************************************************************/
 typedef NU_TASK            OS_Task_t;
 typedef NU_SEMAPHORE       OS_Sema_t;
 typedef NU_SEMAPHORE       OS_Mutex_t;
 typedef NU_TIMER           OS_Timer_t;
 typedef NU_EVENT_GROUP     OS_EventGroup_t;
 typedef NU_EVENT_GROUP     OS_Flag_t;
 typedef void*	            OS_Hisr_t;
 typedef NU_MEMORY_POOL     OS_MemPool_t;
 typedef NU_PARTITION_POOL  OS_PartitionPool_t;
 typedef STATUS             NU_RTN_STATUS;
 typedef UINT32             OS_Proc_t;


 typedef struct
 {
    NU_QUEUE    os_ref;
    void        *queueMem;
    BOOL        externalMem;
    UINT8       filler[3];
 } OS_MsgQ_t;

 typedef struct
 {
    NU_PIPE     os_ref;
    void        *queueMem;
 } OS_Mbox_t;

#endif
/*
 ** OS System call prototypes
 */
void OSA_NucleusInit(void* block);
OSA_STATUS OSA_NucleusTaskCreate  ( OS_Task_t *, void*, UINT32, UINT8, CHAR *, void(*)(void*), void* );
OSA_STATUS OSA_NucleusTaskDelete  ( OS_Task_t *task );
OSA_STATUS OSA_NucleusTaskSuspend ( OS_Task_t *task );
OSA_STATUS OSA_NucleusTaskResume  ( OS_Task_t *task );
OSA_STATUS OSA_NucleusTaskGetPriority( OS_Task_t *task, UINT8 *oldPriority);

OSA_STATUS OSA_NucleusQueueCreate ( OS_MsgQ_t *msgQRef, char *queueName, UINT32 maxSize, UINT32 maxNumber, void *queueAddr, UINT8 waitingMode );
OSA_STATUS OSA_NucleusQueueDelete ( OS_MsgQ_t *msgQRef );
OSA_STATUS OSA_NucleusQueueSend   ( OS_MsgQ_t *msgQRef, UINT32 size, UINT8 *msg, UINT32 timeout);
OSA_STATUS OSA_NucleusQueueRecv   ( OS_MsgQ_t *msgQRef, UINT8 *msg, UINT32 size, UINT32 timeout );
OSA_STATUS OSA_NucleusQueuePoll   ( OS_MsgQ_t *msgQRef, UINT32 *msgCount );

OSA_STATUS OSA_NucleusMboxCreate ( OS_Mbox_t *msgQRef, char *queueName, UINT32 maxNumber, UINT8 waitingMode );
OSA_STATUS OSA_NucleusMboxDelete ( OS_Mbox_t *msgQRef );
OSA_STATUS OSA_NucleusMboxSend   ( OS_Mbox_t *msgQRef, UINT8 *msg, UINT32 timeout);
OSA_STATUS OSA_NucleusMboxRecv   ( OS_Mbox_t *msgQRef, UINT8 *msg, UINT32 timeout );
OSA_STATUS OSA_NucleusMboxPoll   ( OS_Mbox_t *msgQRef, UINT32 *msgCount );

OSA_STATUS OSA_NucleusFlagCreate  ( OS_Flag_t *flagRef );
OSA_STATUS OSA_NucleusFlagDelete  ( OS_Flag_t *flagRef);
OSA_STATUS OSA_NucleusFlagSetBits ( OS_Flag_t *flagRef, UINT32 mask, UINT32 operation);
OSA_STATUS OSA_NucleusFlagWait    ( OS_Flag_t *flagRef, UINT32 mask, UINT32 operation, UINT32* flags, UINT32 timeout );
OSA_STATUS OSA_NucleusFlagPeek    ( OS_Flag_t *flagRef, UINT32* flags );

OSA_STATUS OSA_NucleusTimerDelete ( OS_Timer_t *timer );
OSA_STATUS OSA_NucleusTimerStart  ( OS_Timer_t *timer, UINT32 time, UINT32 resched, void (*handler)(UINT32), UINT32 argc );
OSA_STATUS OSA_NucleusTimerStop   ( OS_Timer_t *timer );
OSA_STATUS OSA_NucleusTimerGetStatus( OS_Timer_t *timer, OSATimerStatus* status );

OSA_STATUS OSA_NucleusSemaCreate  ( OS_Sema_t *sema, UINT32 initialCount, UINT8 waitingMode );
OSA_STATUS OSA_NucleusSemaDelete  ( OS_Sema_t *sema );
OSA_STATUS OSA_NucleusSemaAcquire ( OS_Sema_t *sema, UINT32 timeout );
OSA_STATUS OSA_NucleusSemaRelease ( OS_Sema_t *sema );
OSA_STATUS OSA_NucleusSemaPoll    ( OS_Sema_t *sema, UINT32* count );
OSA_STATUS OSA_NucleusMemPoolCreate( void *pool, UINT32 poolType, UINT8 *poolBase, UINT32 poolSize, UINT32 partitionSize, UINT8 waitingMode );
OSA_STATUS OSA_NucleusMemPoolDelete( void* pool, UINT32 poolType );
OSA_STATUS OSA_NucleusMemAlloc    ( void *pool, UINT32 poolType, UINT32 size, void **mem, UINT32 timeout );
OSA_STATUS OSA_NucleusMemFree     ( void *pool, UINT32 poolType, void* mem );
#if (OSA_INTERRUPTS)
OSA_STATUS OSA_NucleusFIsrCreate  ( UINT32, void(*)(UINT8) );
OSA_STATUS OSA_NucleusSIsrCreate  ( UINT32, OS_Hisr_t *, void(*)(void), UINT8, UINT8 *, UINT32 );
OSA_STATUS OSA_NucleusSIsrDelete  ( OS_Hisr_t *);
OSA_STATUS OSA_NucleusSIsrNotify  ( OS_Hisr_t *);
#endif


BOOL OSA_GetControlBlock(void**, size_t, BOOL );

/*
 ** OS System call macros
 */

#define OSA_INIT(a) OSA_NucleusInit(a)
#define OSA_RUN /* Nucleus does not need to do anything more before the scheduler runs */
#define OSA_GET_REF(pool, ref, size) \
    { \
        OSA_STATUS rtn; \
        OSA_SEMA_ACQUIRE(pool->poolSemaphore, OSA_SUSPEND, rtn); \
        OSA_GET_FROM_FREE_LIST(pool->free, ref); \
        OSA_ADD_TO_ACTIVE_LIST((pool->head), ref); \
        pool->numCreated++; \
        if(rtn==OS_SUCCESS) /*do release only if acquire succeed*/ \
           { OSA_SEMA_RELEASE(pool->poolSemaphore, rtn);} \
        ref->refCheck = (void *)ref; \
    }
#define OSA_DELETE_REF(pool, ref) \
    { \
        OSA_STATUS rtn; \
        OSA_SEMA_ACQUIRE(pool->poolSemaphore, OSA_SUSPEND, rtn); \
        OSA_DELETE_FROM_ACTIVE_LIST((pool->head), ref); \
        pool->numCreated--; \
        OSA_ADD_TO_FREE_LIST((pool->free), ref); \
        if(rtn==OS_SUCCESS) /*do release only if acquire succeed*/ \
          { OSA_SEMA_RELEASE(pool->poolSemaphore, rtn);} \
        ref->refCheck = NULL; \
    }


/* Thread Control */

#define OSA_TASK_CREATE(taskPtr, stackPtr, stackSize, priority, name,\
                       taskStart, argv, rtn) \
    { \
        rtn = OSA_NucleusTaskCreate( taskPtr, stackPtr, stackSize, priority, name, taskStart, argv);    \
    }

#define OSA_TASK_DELETE(taskPtr, rtn)                               \
    {                                                               \
        rtn = OSA_NucleusTaskDelete( &taskPtr );                    \
    }

#define OSA_TASK_SUSPEND(taskPtr, rtn)                              \
    {                                                               \
        rtn = OSA_NucleusTaskSuspend( &taskPtr );                   \
    }

#define OSA_TASK_RESUME(taskPtr, rtn)                               \
    {                                                               \
        rtn = OSA_NucleusTaskResume( &taskPtr );                    \
    }
#define OSA_TASK_SLEEP(ticks)                                       \
    {                                                               \
        NU_Sleep(ticks);                                            \
    }
#ifdef OSA_NO_PRIORITY_CONVERSION
#define OSA_TASK_CHANGE_PRIORITY(taskPtr, newPriority, oldPriority, rtn)\
    {                                                               \
        UINT8 priority;                                             \
        priority = NU_Change_Priority( taskPtr, (OPTION)(newPriority));\
        *oldPriority = priority;                                    \
        rtn = OS_SUCCESS;                                           \
    }
#else
#define OSA_TASK_CHANGE_PRIORITY(taskPtr, newPriority, oldPriority, rtn)\
    {                                                               \
        UINT8 priority;                                             \
        priority = NU_Change_Priority( taskPtr, (OPTION)(((newPriority+1)*8)-1));\
        *oldPriority = (UINT8)(((priority+1)/8)-1);                 \
        rtn = OS_SUCCESS;                                           \
    }
#endif
#define OSA_TASK_GET_PRIORITY(taskPtr, oldPriority, rtn)            \
    {                                                               \
        rtn = OSA_NucleusTaskGetPriority( taskPtr, oldPriority );   \
    }
#define OSA_TASK_IDENTIFY(taskPtr)                                  \
    {                                                               \
        taskPtr = NU_Current_Task_Pointer();                        \
    }
#define OSA_TASK_YIELD NU_Relinquish();
#define OSA_TASK_EQUAL(taskPtr, rtn)                                \
    {                                                               \
        OS_Task_t *currTask;                                        \
        currTask = NU_Current_Task_Pointer();                       \
        if(taskPtr == currTask)                                     \
            rtn = TRUE;                                             \
        else                                                        \
            rtn = FALSE;                                            \
    }

/* Messaging */
#define OSA_QUEUE_CREATE(qRef, name, size, num, addr, mode, rtn)    \
    {                                                               \
        rtn = OSA_NucleusQueueCreate(qRef, name, size, num, addr, mode);  \
    }
#define OSA_QUEUE_DELETE(qRef, rtn)                                 \
    {                                                               \
        rtn = OSA_NucleusQueueDelete(&qRef);                        \
    }
#define OSA_QUEUE_SEND(qRef, size, ptr, timeout, rtn)               \
    {                                                               \
        rtn = OSA_NucleusQueueSend(&qRef, size, ptr, timeout);      \
    }
#define OSA_QUEUE_RECV(qRef, msg, size, timeout, rtn)               \
    {                                                               \
        rtn = OSA_NucleusQueueRecv(&qRef, msg, size, timeout);      \
    }
#define OSA_QUEUE_POLL(qRef, msgCount, rtn)                         \
    {                                                               \
        rtn = OSA_NucleusQueuePoll(&qRef, msgCount);                \
    }

/* Mailboxes */
#define OSA_MAILBOX_CREATE(qRef, name, num, mode, rtn)              \
    {                                                               \
        rtn = OSA_NucleusMboxCreate(qRef, name, num, mode);         \
    }
#define OSA_MAILBOX_DELETE(qRef, rtn)                               \
    {                                                               \
        rtn = OSA_NucleusMboxDelete(&qRef);                         \
    }
#define OSA_MAILBOX_SEND(qRef, ptr, timeout, rtn)                   \
    {                                                               \
        rtn = OSA_NucleusMboxSend(&qRef, ptr, timeout);             \
    }
#define OSA_MAILBOX_RECV(qRef, msg, timeout, rtn)                   \
    {                                                               \
        rtn = OSA_NucleusMboxRecv(&qRef, msg, timeout);             \
    }
#define OSA_MAILBOX_POLL(qRef, msgCount, rtn)                       \
    {                                                               \
        rtn = OSA_NucleusMboxPoll(&qRef, msgCount);                 \
    }

/* Events */
#define OSA_FLAG_CREATE(flagRef, name, rtn)                         \
    {                                                               \
        rtn = OSA_NucleusFlagCreate(flagRef);                       \
    }
#define OSA_FLAG_DELETE(flagRef, rtn)                               \
    {                                                               \
        rtn = OSA_NucleusFlagDelete(flagRef);                       \
    }
#define OSA_FLAG_SET_BITS(flagRef, mask, operation, rtn)            \
    {                                                               \
        rtn = OSA_NucleusFlagSetBits(flagRef, mask, operation);     \
    }
#define OSA_FLAG_WAIT(flagRef, reqValue, mode, currValue, timeout, rtn) \
    {                                                               \
        rtn = OSA_NucleusFlagWait(flagRef, reqValue, mode, currValue, timeout);  \
    }
#define OSA_FLAG_PEEK(flagRef, value, rtn)                          \
    {                                                               \
        rtn = OSA_NucleusFlagPeek(&flagRef, value);                 \
    }


/* Timers */
#define OSA_TIMER_CREATE(timerRef, rtn)                             \
    {                                                               \
        rtn = OS_SUCCESS;                                           \
    }
#define OSA_TIMER_DELETE(timerRef, rtn)                             \
    {                                                               \
        rtn = OSA_NucleusTimerDelete(&timerRef);                    \
    }

#define OSA_TIMER_START(timerRef, time, resched, handler,           \
                       argc, rtn)                                   \
    {                                                               \
        rtn = OSA_NucleusTimerStart(&timerRef, time, resched, handler, argc); \
    }
#define OSA_TIMER_STOP(timerRef, rtn)                               \
    {                                                               \
        rtn = OSA_NucleusTimerStop(&timerRef);                      \
    }
#define OSA_TIMER_STATUS(timerRef, status, rtn)                     \
    {                                                               \
        rtn = OSA_NucleusTimerGetStatus(&timerRef, status);         \
    }

#define OSA_MEM_ALLOC(pool, type, size, partSize, mem, timeout, rtn)\
    {                                                               \
        rtn = OSA_NucleusMemAlloc( pool, type, size, mem, timeout );\
    }
#define OSA_MEM_FREE(pool, type, mem, rtn)                          \
    {                                                               \
        rtn = OSA_NucleusMemFree( pool, type, mem );                \
    }
#define OSA_MEM_POOL_CREATE(pool, name, type, base, size, partition, mode, rtn) \
    {                                                               \
        rtn = OSA_NucleusMemPoolCreate( pool, type, base, size, partition, mode ); \
    }
#define OSA_MEM_POOL_DELETE(pool, type, rtn)                        \
    {                                                               \
        rtn = OSA_NucleusMemPoolDelete( pool, type );               \
    }

/* Semaphores */
#define OSA_SEMA_CREATE(sema, name, initialCount, waitingMode, rtn )\
    {                                                               \
        rtn = OSA_NucleusSemaCreate(sema, initialCount, waitingMode);\
    }
#define OSA_SEMA_DELETE(sema, rtn)                                  \
    {                                                               \
        rtn = OSA_NucleusSemaDelete(&sema);                         \
    }

#define OSA_SEMA_ACQUIRE(sema, timeout, rtn)                        \
    {                                                               \
        rtn = OSA_NucleusSemaAcquire(&sema, timeout);               \
    }
#define OSA_SEMA_RELEASE(sema, rtn) \
    { \
        rtn = OSA_NucleusSemaRelease(&sema); \
    }
#define OSA_SEMA_POLL(sema, count, rtn)                             \
    {                                                               \
        rtn = OSA_NucleusSemaPoll(&sema, count);                    \
    }

/* Mutexes */
#define OSA_MUTEX_CREATE(mutex, name, waitingMode, rtn )            \
    {                                                               \
        rtn = OSA_NucleusSemaCreate(mutex, 1, waitingMode);         \
    }
#define OSA_MUTEX_DELETE(mutex, rtn)                                \
    {                                                               \
        rtn = OSA_NucleusSemaDelete(&mutex);                        \
    }
#define OSA_MUTEX_LOCK(mutex, timeout, rtn)                         \
    {                                                               \
        rtn = OSA_NucleusSemaAcquire(&mutex, timeout);              \
    }
#define OSA_MUTEX_UNLOCK(mutex, rtn)                                \
    {                                                               \
        rtn = OSA_NucleusSemaRelease(&mutex);                       \
    }

/* Context lock */
#define OSA_CONTEXT_LOCK NU_Change_Preemption(NU_NO_PREEMPT)

#define OSA_CONTEXT_UNLOCK NU_Change_Preemption(NU_PREEMPT)

#define OSA_SYS_CONTEXT_LOCK(prevContext)                                 \
   {                                                                      \
      prevContext->prev_interrupt_context                                 \
                     = NU_Local_Control_Interrupts(NU_DISABLE_INTERRUPTS);\
      /* Lock OS context switch, only within task */                      \
      if (NU_Current_Task_Pointer())                                      \
          prevContext->prev_task_context                                  \
                     = NU_Change_Preemption(NU_NO_PREEMPT);               \
   }

#define OSA_SYS_CONTEXT_UNLOCK {                                         \
      NU_Local_Control_Interrupts(NU_ENABLE_INTERRUPTS);                 \
      if (NU_Current_Task_Pointer())                                     \
          NU_Change_Preemption(NU_PREEMPT);                              \
   }

#define OSA_SYS_CONTEXT_RESTORE(prevContext)              \
   {                                                                     \
      NU_Local_Control_Interrupts(prevContext->prev_interrupt_context);  \
      /* Unlock OS context switch, only if the context is a task.*/      \
      if (NU_Current_Task_Pointer())                                     \
          NU_Change_Preemption(prevContext->prev_task_context);          \
   }


#if (OSA_INTERRUPTS)
#define OSA_ISR_CREATE_FISR(isrNum, func, rtn)                      \
    {                                                               \
        rtn = OSA_NucleusFIsrCreate(isrNum, func);                  \
    }
#define OSA_ISR_CREATE_SISR(isrNum, isr, func, priority, stack, size, rtn)\
    {                                                               \
        rtn = OSA_NucleusSIsrCreate(isrNum, isr, func, priority, stack, size);\
    }
#define OSA_ISR_DELETE_SISR(isr, rtn)                               \
    {                                                               \
        rtn = OSA_NucleusSIsrDelete(isr);                           \
    }
#define OSA_ISR_NOTIFY_SISR(isr, rtn)                               \
    {                                                               \
        rtn = OSA_NucleusSIsrNotify(isr);                           \
    }
#endif


#define OSA_INTERRUPT_ENABLE(number, rtn)                           \
    {                                                               \
        rtn = NU_Control_Interrupts(number);                        \
    }
#define OSA_INTERRUPT_DISABLE(number, rtn)                          \
    {                                                               \
        rtn = NU_Control_Interrupts((INT32)number);                 \
    }

/* RTC services */
#define OSA_GET_TIME(time)                                          \
    {                                                               \
        time = NU_Retrieve_Clock();                                 \
    }
#define OSA_GET_SYSTEM_TIME(secsPtr, milliSecsPtr, rtn)             \
    {                                                               \
        UNSIGNED currentTime;                                       \
                                                                    \
        currentTime = NU_Retrieve_Clock() * OSA_TICK_FREQ_IN_MILLISEC; \
                                                                    \
        *secsPtr = currentTime / 1000 ;                             \
        *milliSecsPtr = (UINT16)                                    \
                        (( currentTime - (*secsPtr * 1000))/ 10)*10;\
        rtn = OS_SUCCESS;                                           \
    }

#define OSA_CLOCK_TICK(a) TMT_Timer_Interrupt()

#define OSA_ERROR(err)                                              \
    {                                                               \
        printf("\n*** OSA_ERROR -> %d *** \n File: %s\n Line: %ld\n", err, __FILE__, __LINE__);\
    }

#endif /* OSA_NUCLEUS */

#endif /* _OSA_NUCLEUS_H */
