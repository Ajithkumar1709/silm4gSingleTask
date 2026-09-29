#ifndef _SIMCOM_OS_H
#define _SIMCOM_OS_H

//#include "simcom_common.h"
#include "mbtk_pub_type.h"

#if 0
#ifndef UINT8
typedef unsigned char   UINT8;
#endif

#ifndef UINT16
typedef unsigned short  UINT16;
#endif

#ifndef UINT32
typedef unsigned long   UINT32;
#endif

#if 0
#ifndef UINT64
typedef unsigned long long  UINT64;
#endif
#endif

#ifndef BOOL
typedef unsigned char   BOOL;
#endif

#ifndef INT8
typedef signed char     INT8;
#endif

#ifndef INT16
typedef signed short    INT16;
#endif

#ifndef INT32
typedef signed long     INT32;
#endif

#ifndef INT64
typedef long long  INT64;
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif
#endif


typedef void*   sTaskRef;
typedef void*   sSemaRef;
typedef void*   sMutexRef;
typedef void*   sMsgQRef;
typedef void*   sTimerRef;
typedef void*   sFlagRef;

typedef struct sim_msg_cell
{
    UINT32 msg_id;
    int arg1;
    int arg2;
    void *arg3;
} SIM_MSG_T;

#define SC_MIN_STACK_SIZE      256
#define SC_ENABLE_INTERRUPTS   1
#define SC_DISABLE_INTERRUPTS  2
#define SC_SUSPEND             0xFFFFFFFF
#define SC_NO_SUSPEND          0
#define SC_FLAG_AND            5
#define SC_FLAG_AND_CLEAR      6
#define SC_FLAG_OR             7
#define SC_FLAG_OR_CLEAR       8
#define SC_FIXED               9
#define SC_VARIABLE            10
#define SC_FIFO                11
#define SC_PRIORITY            12
#define SC_GLOBAL              13
#define SC_OS_INDEPENDENT      14



#define SC_DEFAULT_TASK_PRIORITY    90
#define SC_DEFAULT_THREAD_STACKSIZE 4096
/*========================================================================
 *  SC Return Error Codes
 *========================================================================*/

typedef enum
{
    SC_SUCCESS = 0,        /* 0x0 -no errors                                        */
    SC_FAIL,               /* 0x1 -operation failed code                            */
    SC_TIMEOUT,            /* 0x2 -Timed out waiting for a resource                 */
    SC_NO_RESOURCES,       /* 0x3 -Internal OS resources expired                    */
    SC_INVALID_POINTER,    /* 0x4 -0 or out of range pointer value                  */
    SC_INVALID_REF,        /* 0x5 -invalid reference                                */
    SC_INVALID_DELETE,     /* 0x6 -deleting an unterminated task                    */
    SC_INVALID_PTR,        /* 0x7 -invalid memory pointer                           */
    SC_INVALID_MEMORY,     /* 0x8 -invalid memory pointer                           */
    SC_INVALID_SIZE,       /* 0x9 -out of range size argument                       */
    SC_INVALID_MODE,       /* 0xA, 10 -invalid mode                                 */
    SC_INVALID_PRIORITY,   /* 0xB, 11 -out of range task priority                   */
    SC_UNAVAILABLE,        /* 0xC, 12 -Service requested was unavailable or in use  */
    SC_POOL_EMPTY,         /* 0xD, 13 -no resources in resource pool                */
    SC_QUEUE_FULL,         /* 0xE, 14 -attempt to send to full messaging queue      */
    SC_QUEUE_EMPTY,        /* 0xF, 15 -no messages on the queue                     */
    SC_NO_MEMORY,          /* 0x10, 16 -no memory left                              */
    SC_DELETED,            /* 0x11, 17 -service was deleted                         */
    SC_SEM_DELETED,        /* 0x12, 18 -semaphore was deleted                       */
    SC_MUTEX_DELETED,      /* 0x13, 19 -mutex was deleted                           */
    SC_MSGQ_DELETED,       /* 0x14, 20 -msg Q was deleted                           */
    SC_MBOX_DELETED,       /* 0x15, 21 -mailbox Q was deleted                       */
    SC_FLAG_DELETED,       /* 0x16, 22 -flag was deleted                            */
    SC_INVALID_VECTOR,     /* 0x17, 23 -interrupt vector is invalid                 */
    SC_NO_TASKS,           /* 0x18, 24 -exceeded max # of tasks in the system       */
    SC_NO_FLAGS,           /* 0x19, 25 -exceeded max # of flags in the system       */
    SC_NO_SEMAPHORES,      /* 0x1A, 26 -exceeded max # of semaphores in the system  */
    SC_NO_MUTEXES,         /* 0x1B, 27 -exceeded max # of mutexes in the system     */
    SC_NO_QUEUES,          /* 0x1C, 28 -exceeded max # of msg queues in the system  */
    SC_NO_MBOXES,          /* 0x1D, 29 -exceeded max # of mbox queues in the system */
    SC_NO_TIMERS,          /* 0x1E, 30 -exceeded max # of timers in the system      */
    SC_NO_MEM_POOLS,       /* 0x1F, 31 -exceeded max # of mem pools in the system   */
    SC_NO_INTERRUPTS,      /* 0x20, 32 -exceeded max # of isr's in the system       */
    SC_FLAG_NOT_PRESENT,   /* 0x21, 33 -requested flag combination not present      */
    SC_UNSUPPORTED,        /* 0x22, 34 -service is not supported by the OS          */
    SC_NO_MEM_CELLS,       /* 0x23, 35 -no global memory cells                      */
    SC_DUPLICATE_NAME,     /* 0x24, 36 -duplicate global memory cell name           */
    SC_INVALID_PARM        /* 0x25, 37 -invalid parameter                           */
}SC_STATUS;


extern void *ol_malloc(u32 num);
extern void ol_free(void *free);

#define malloc ol_malloc
#define free ol_free

/*memory opreation*/
/*****************************************************************************
 * FUNCTION
 *  sAPI_Malloc
 *
 * DESCRIPTION
 *  Allocate a block of Size bytes of memory from the default memory pool, 
 *  returning a pointer to the beginning of the block.
 *  
 * PARAMETERS
 *  size: Number of bytes to be allocated.
 *
 * RETURNS
 *  Points to the first address of an allocated memory space.
 *  If return is NULL, description failed to allocate memory
 *
 * NOTE
 *  
 *****************************************************************************/
#define sAPI_Malloc(size) ol_malloc(size)


/*****************************************************************************
 * FUNCTION
 *  sAPI_Free
 *
 * DESCRIPTION
 *  sAPI_Free() is used to free the memory to the defaultmemory pool
 *  
 * PARAMETERS
 *  p: The first address of the memory that needs to be released
 *
 * RETURNS
 *  None.
 *
 * NOTE
 *  
 *****************************************************************************/ 
#define sAPI_Free(pArg)  \
    do {  \
        if (pArg != NULL) {  \
            ol_free(pArg);  \
            pArg = NULL;  \
        } \
    }while(0);


 /*****************************************************************************
  * FUNCTION
  *  sAPI_TaskCreate
  *
  * DESCRIPTION
  *  sAPI_TaskCreate() is used to Create a task, this task will be started automatically.
  *  
  * PARAMETERS
  *  taskRef: OS assigned reference to the task
  *  stackPtr: Pointer to the low address of the stack
  *  stackSize: Maximum size of the stack
  *  priority: initial priority of the task. Range 0＃31 where 0 is the highest priority and 31 is the lowest priority.
  *  SC_NO_PRIORITY_CONVERSION is enabled, priority range is defaulted to the old 0 ＃ 255 range.
  *  taskName: Pointer to an 8 character name for the task. The name does not have to be null-terminated.
  *  taskStart: Entry function of the task
  *  argv: Argument to be passed into task entry function
  *
  * RETURNS
  *  @SC_STATUS
  *
  * NOTE
  *  
  *****************************************************************************/
SC_STATUS sAPI_TaskCreate(sTaskRef *taskRef,
                               void* stackPtr,
                               UINT32 stackSize, 
                               UINT8 priority, 
                               char *taskName, 
                               void (*taskStart)(void*), 
                               void* argv);

/*****************************************************************************
* FUNCTION
*  sAPI_TaskDelete
*
* DESCRIPTION
*  sAPI_TaskDelete() is used to deleted the specified task.
*  
* PARAMETERS
*  taskRef: Reference to the task.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_TaskDelete(sTaskRef taskRef);

/*****************************************************************************
* FUNCTION
*  sAPI_TaskSuspend
*
* DESCRIPTION
*  sAPI_TaskSuspend() is used to request that a specific task be suspended including the current task.
*  
* PARAMETERS
*  taskRef: Reference to the task.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_TaskSuspend(sTaskRef taskRef);

/*****************************************************************************
* FUNCTION
*  sAPI_TaskResume
*
* DESCRIPTION
*  sAPI_TaskResume() is used to request that a specified task be resumed.
*  
* PARAMETERS
*  taskRef: Reference to the task.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_TaskResume(sTaskRef taskRef);

/*****************************************************************************
* FUNCTION
*  sAPI_TaskSleep
*
* DESCRIPTION
*  Suspend the current executing task for specified time. 1s = 200 tick
*  
* PARAMETERS
*  ticks: Number of OS clock ticks to sleep.
*
* RETURNS
*  None.
*
* NOTE
*  
*****************************************************************************/
void sAPI_TaskSleep(UINT32 ticks);

/*****************************************************************************
* FUNCTION
*  sAPI_TaskGetCurrentRef
*
* DESCRIPTION
*  sAPI_TaskResume() is used to get the currently executing task.
*  
* PARAMETERS
*  taskRef: OS assigned reference to the task.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_TaskGetCurrentRef(sTaskRef *taskRef);

/*****************************************************************************
* FUNCTION
*  sAPI_TaskTerminate
*
* DESCRIPTION
*  Terminate a task. Please use this API carefully. A task in a terminated state cannotexecute again.
*  
* PARAMETERS
*  taskRef: Reference to the task.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_TaskTerminate(sTaskRef taskRef);

/*****************************************************************************
 * FUNCTION
 *  sAPI_MsgQCreate
 *
 * DESCRIPTION
 *  This function requests that a message queue be created. All memory used to store messages on the message queue is allocated by the operating system.
 *  
 * PARAMETERS
 *  msgQRef: Pointer to location to hold message queue reference allocated by the operating system
 *  queueName: 8 character name of queue.The name does not have to be null-terminated.
 *  maxSize: Maximum size of a message on the queue. This is used for error checking by sAPI_MsgQSend().
 *  maxNumber: Maximum number of messages on the queue.
 *  waitingMode: Defines scheduling of waiting events: SC_FIFO, or SC_PRIORITY. 
 *
 * RETURNS
 *  @SC_STATUS
 *
 * NOTE
 *  
 *****************************************************************************/
SC_STATUS sAPI_MsgQCreate(sMsgQRef *msgQRef, 
                               char *queueName, 
                               UINT32 maxSize, 
                               UINT32 maxNumber, 
                               UINT32 waitingMode);

/*****************************************************************************
* FUNCTION
*  sAPI_MsgQDelete
*
* DESCRIPTION
*  This function requests that the specified message queue be deleted.
*  
* PARAMETERS
*  msgQRef: Identifier that uniquely identifies the message queue
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_MsgQDelete(sMsgQRef msgQRef);

/*****************************************************************************
* FUNCTION
*  sAPI_MsgQSend
*
* DESCRIPTION
*  This function requests that a message be sent to the specified message queue.
*  
* PARAMETERS
*  msgQRef: Identifier that uniquely identifies the message queue
*  msgPtr: Starting address of the data.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_MsgQSend(sMsgQRef msgQRef, SIM_MSG_T *msgPtr);

/*****************************************************************************
* FUNCTION
*  sAPI_MsgQRecv
*
* DESCRIPTION
*  This function requests that a message be received from the specified message queue. 
*  If the queue is empty, the blocking behavior of the call is determined by the value of the ※timeout§ argument.
*  
* PARAMETERS
*  msgQRef: Identifier that uniquely identifies the message queue
*  recvMsg: Starting address of the data.
*  timeout: If timeout is set to SC_NO_SUSPEND, this call will not block. 
*  If timeout is set to SC_SUSPEND, this call will block until a message is available on the queue. 
*  If a timeout value between 1 and 4,294,967,293 is specified, the call will block until a message is available or until the timeout period, 
*  in number of OS clock ticks, elapses. 
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_MsgQRecv(sMsgQRef msgQRef,SIM_MSG_T *recvMsg, UINT32 timeout);

/*****************************************************************************
* FUNCTION
*  sAPI_MsgQPoll
*
* DESCRIPTION
*  This function checks the number of messages on the message queue.
*  
* PARAMETERS
*  msgQRef: Identifier that uniquely identifies the message queue.
*  msgCount: Return from this function, msgCount contains the number of messages on the queue.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_MsgQPoll(sMsgQRef msgQRef,UINT32* msgCount);

/*****************************************************************************
* FUNCTION
*  sAPI_SemaphoreCreate
*
* DESCRIPTION
*  This function requests that a counting semaphore be created.
*  
* PARAMETERS
*  semaRef: OS assigned reference to the semaphore.
*  initialCount: Initial count of the semaphore. 
*  waitingMode: SC_FIFO or SC_PRIORITY. ※waitingMode§ specifies how tasks are added to a semaphore＊s Wait queue.They may be added in first-in-first-out order (SC_FIFO) 
*  or in priority order (SC_PRIORITY) with the highest priority waiting task at the front on the queue.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_SemaphoreCreate(sSemaRef *semaRef, 
                                       UINT32 initialCount, 
                                       UINT32 waitingMode);

/*****************************************************************************
* FUNCTION
*  sAPI_SemaphoreDelete
*
* DESCRIPTION
*  This function requests that a counting semaphore be deleted.
*  
* PARAMETERS
*  semaRef: OS assigned reference to the semaphore
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_SemaphoreDelete(sSemaRef semaRef);

/*****************************************************************************
* FUNCTION
*  sAPI_SemaphoreAcquire
*
* DESCRIPTION
*  This function requests that the specified semaphore be decremented. If the semaphore count is zero before this call, 
*  the service cannot be satisfied immediately. In that case, the blocking behavior is specified by the ※timeout§ parameter.
*  
* PARAMETERS
*  semaRef: OS assigned reference to the semaphore
*  timeout: If timeout is set to SC_NO_SUSPEND, this call will not block. If timeout is set to SC_SUSPEND, this call will block until the semaphore count is greater than zero. 
*  If a timeout value between 1 and 4,294,967,293 is specified, the call will block until the semaphore count is greater than zero or the timeout period, in number of OS clock ticks, elapses.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_SemaphoreAcquire(sSemaRef semaRef, UINT32 timeout);

/*****************************************************************************
* FUNCTION
*  sAPI_SemaphoreRelease
*
* DESCRIPTION
*  If there are any tasks waiting for the semaphore, the first waiting task is made ready to run. 
*  If there are no tasks waiting, the value of the semaphore is incremented by one.
*  
* PARAMETERS
*  semaRef: OS assigned reference to the semaphore
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_SemaphoreRelease(sSemaRef semaRef);

/*****************************************************************************
* FUNCTION
*  sAPI_SemaphorePoll
*
* DESCRIPTION
*  This function requests that a counting semaphore be created.
*  
* PARAMETERS
*  semaRef: OS assigned reference to the semaphore
*  count: Current value of the semaphore.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_SemaphorePoll(sSemaRef semaRef,UINT32 *count);

/*****************************************************************************
* FUNCTION
*  sAPI_MutexCreate
*
* DESCRIPTION
*  This function requests that a mutex be created. Mutexes use the priority inheritance protocol to bound the time spent in priority inversions.
*  
* PARAMETERS
*  mutexRef: OS assigned reference to the Mutex.
*  waitingMode: SC_FIFO or SC_PRIORITY.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_MutexCreate(sMutexRef *mutexRef,UINT32 waitingMode);

/*****************************************************************************
* FUNCTION
*  sAPI_MutexDelete
*
* DESCRIPTION
*  This function requests that the specified mutex be deleted.
*  
* PARAMETERS
*  mutexRef: OS assigned reference to the Mutex.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_MutexDelete(sMutexRef mutexRef);

/*****************************************************************************
* FUNCTION
*  sAPI_MutexLock
*
* DESCRIPTION
*  This function requests that the specified mutex be locked. If the mutex is locked by another task before this call, 
*  the service cannot be satisfied immediately. In this case, the blocking behavior is specified by the ※timeout§ parameter.
*  
* PARAMETERS
*  mutexRef: OS assigned reference to the Mutex.
*  timeout: If timeout is set to SC_NO_SUSPEND, this call will not block. If timeout is set to SC_SUSPEND, 
*  this call will block until the semaphore count is greater than zero. If a timeout value between 1 and 4,294,967,293 is specified, 
*  the call will block until the mutex is unlocked or the timeout period, in number of OS clock ticks, elapses.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_MutexLock(sMutexRef mutexRef,UINT32 timeout);

/*****************************************************************************
* FUNCTION
*  sAPI_MutexUnLock
*
* DESCRIPTION
*  If there are any tasks waiting for the mutex, the task at the front of the Wait queue is made ready to run. 
*  Only the mutex owner may unlock a mutex.
*  
* PARAMETERS
*  mutexRef: OS assigned reference to the Mutex.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_MutexUnLock(sMutexRef mutexRef);

/*****************************************************************************
* FUNCTION
*  sAPI_FlagCreate
*
* DESCRIPTION
*  This function requests that a flag group be created.
*  
* PARAMETERS
*  flagRef: OS assigned reference to the flag.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_FlagCreate(sFlagRef *flagRef);

/*****************************************************************************
* FUNCTION
*  sAPI_FlagDelete
*
* DESCRIPTION
*  This function requests that a flag group be deleted.
*  
* PARAMETERS
*  flagRef: OS assigned reference to the flag.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_FlagDelete(sFlagRef flagRef);

/*****************************************************************************
* FUNCTION
*  sAPI_FlagSet
*
* DESCRIPTION
*  This function executes a logical OR or AND of the flag group with the input mask.
*  
* PARAMETERS
*  flagRef: OS assigned reference to the flag.
*  mask: Mask specifying which bits need to be set. A 1 in a certain bit position will set the same bit position in the flag.
*  operation: Logical operation to be executed on the flag group. SC_AND executes a logical AND and SC_OR executes a logical OR.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_FlagSet(sFlagRef flagRef, UINT32 mask, UINT32 operation);

/*****************************************************************************
* FUNCTION
*  sAPI_FlagWait
*
* DESCRIPTION
*  This function waits for the specified operation on a flag group to complete. The operation is defined by the ※operation§ input parameter. 
*  If the timeout input parameter is SC_NO_SUSPEND the operation completes immediately and the current value of the flags is returned in the output parameter ※flags§. 
*  By specifying SC_NO_SUSPEND, an application can read the current value of the flags without blocking.
*  
* PARAMETERS
*  flagRef: OS assigned reference to the flag.
*  mask: Mask of flags to wait for
*  operation: may be one of the following:
*  SC_FLAG_AND 每 Wait for all of the bits in the input mask
*  SC_FLAG_AND_CLEAR 每 Wait for all of the bits in the input mask to be set, clear all event flags on successful
*  SC_FLAG_OR 每 Wait for any of the bits in the input mask to be set, don＊t clear the event flags
*  SC_FLAG_OR_CLEAR 每 Wait for any of the bits in the input mask to completion to be set, don＊t clear the event flags
*  timeout: If timeout is set to SC_NO_SUSPEND, the operation completes immediately and the current value of the flags is returned in the output parameter ※flags§. 
*  If timeout is set to SC_SUSPEND, this call will block until the condition specified by the ※mask§ and ※operation§ inputs is satisfied. If a timeout value between 1 and 4,294,967,293 is specified, 
*  the call will block until the wait condition is satisfied or until the timeout period, in number of OS clock ticks, elapses.
*  flag: The current value of all flags
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_FlagWait(sFlagRef flagRef, UINT32 mask, UINT32 operation, UINT32* flags, UINT32 timeout);

/*****************************************************************************
* FUNCTION
*  sAPI_TimerCreate
*
* DESCRIPTION
*  This function allocates a timer. The state of the allocated timer is inactive. sAPI_TimerStart() is used to activate the timer.
*  
* PARAMETERS
*  timerRef: Address to store a reference to the timer allocated by the operating system.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_TimerCreate(sTimerRef *timerRef);

/*****************************************************************************
* FUNCTION
*  sAPI_TimerStart
*
* DESCRIPTION
*  This function requests that an inactive timer be started and the callback function executed at the expiration of the timer.
*  
* PARAMETERS
*  timerRef: OS supplied timer reference.
*  initialTime: Initial expiration time in OS clock ticks
*  rescheduleTime: If 0,cyclic timing is disabled and the timer only expires once. If not zero, it indicates the period, in OS clock ticks, of a cyclic timer.
*  callBackRoutine: Specifies the application routine to execute each time the timer expires. The callback function must not invoke any ※blocking§ operating system calls.
*  timerArgc: Argument to be passed to callback routine on expiration.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_TimerStart(sTimerRef timerRef, UINT32 initialTime, UINT32 rescheduleTime, void (*callBackRoutine)(UINT32), UINT32 timerArgc);

/*****************************************************************************
* FUNCTION
*  sAPI_TimerStop
*
* DESCRIPTION
*  This function requests that the state of an active timer be changed to inactive. Calling this function when the state of the timer is inactive has no effect.
*  
* PARAMETERS
*  timerRef: OS assigned reference to the timer.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_TimerStop(sTimerRef timerRef);

/*****************************************************************************
* FUNCTION
*  sAPI_TimerDelete
*
* DESCRIPTION
*  This function requests that the specified timer be deleted. The timer must be inactive when this function is called.
*  
* PARAMETERS
*  timerRef: OS assigned reference to the timer.
*
* RETURNS
*  @SC_STATUS
*
* NOTE
*  
*****************************************************************************/
SC_STATUS sAPI_TimerDelete(sTimerRef timerRef);

UINT32 sAPI_GetTicks(void);

void sAPI_enableDUMP(void);


#endif
