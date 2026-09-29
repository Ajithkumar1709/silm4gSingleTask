/**************************************************************************/
/*                                                                        */
/*            Copyright (c) 2002 by Express Logic Inc.                    */
/*                                                                        */
/*  This software is copyrighted by and is the sole property of Express   */
/*  Logic, Inc.  All rights, title, ownership, or other interests         */
/*  in the software remain the property of Express Logic, Inc.  This      */
/*  software may only be used in accordance with the corresponding        */
/*  license agreement.  Any unauthorized use, duplication, transmission,  */
/*  distribution, or disclosure of this software is expressly forbidden.  */
/*                                                                        */
/*  This Copyright notice may not be removed or modified without prior    */
/*  written consent of Express Logic, Inc.                                */
/*                                                                        */
/*  Express Logic, Inc. reserves the right to modify this software        */
/*  without notice.                                                       */
/*                                                                        */
/*  Express Logic, Inc.                                                   */
/*  11423 West Bernardo Court               info@expresslogic.com         */
/*  San Diego, CA  92127                    http://www.expresslogic.com   */
/*                                                                        */
/*                                                                        */
/**************************************************************************/

/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/**   ThreadX Component                                                   */
/**                                                                       */
/**   POSIX Compliancy Wrapper (POSIX)                                    */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

/**************************************************************************/
/*                                                                        */
/*  EKP DEFINITIONS                                        RELEASE        */
/*                                                                        */
/*    tx_posix.h                                          PORTABLE C      */
/*                                                           1.0          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Express Logic, Inc.                                                 */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This file defines the constants, structures, etc.needed to          */
/*    implement the Evacuation Kit for POSIX Users (POSIX)                */
/*                                                                        */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  06-01-2002         Atul kulkarni             Initial Version          */
/*                                                                        */
/*  21-Oct-2008        DP                        Lots of fixes            */
/*                                                                        */
/**************************************************************************/

#ifndef TX_POSIX
#define TX_POSIX

#include "tx_api.h"
#include "tx_utils.h"  /* application Threadx utilities */
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************/
/* Macros to convert between semaphore, queue, scheduler                */
/************************************************************************/
#define  MAKE_TX_SEM(sem)             ((TX_SEMAPHORE *)sem)
#define  MAKE_POSIX_QUEUE(queue)      ((POSIX_MSG_QUEUE *)queue)
#define  MAKE_POSIX_SEM(sem)          ((sem_t *)sem)

/************************************************************************/
/* Define max values for message queue services                         */
/************************************************************************/
#define  MQ_MAXMSG                      512             /* MQ_MAXMSG 1024 (POSIX value).   */
#define  MQ_MSGSIZE                     64             /* MQ_MSGSIZE 4096 (POSIX value)   */
#define  MQ_FLAGS                       0
#define  MQ_PRIO_MAX                    32              /* Maximum priority of message.    */

/************************************************************************/
/*                          Global Variables                            */
/************************************************************************/

/* Define the system configuration constants for the Evacuation Kit for
   POSIX Users.This is where the number of system objects
   (pthreads, message queues, semaphores etc.)are defined.              */

/************************************************************************/
/*               SYSTEM CONFIGURATION PARAMETERS                        */
/************************************************************************/

/* Define the maximum number of simultaneous POSIX semaphores
    supported.  */
#define  SEM_NSEMS_MAX                  100

/* Define the maximum length of name of semaphore .  */
#define  SEM_NAME_MAX                   20

/* Max value of semaphore while initialization.  */
#define  SEM_VALUE_MAX                  100

/* Define the maximum number of simultaneous POSIX message queues supported.  */
#define  POSIX_MAX_QUEUES               128

/* Define the maximum number of simultaneous POSIX pthreads supported.  */
#define  PTHREAD_THREADS_MAX            128

/* Define the maximum number of simultaneous POSIX mutexes supported.  */
#define  POSIX_MAX_MUTEX                128

/* Define the maximum length of name of message queue.  */
#define  MQ_PATH_MAX                       32 //10

/* Define size of the posix heap memory segment.                              */
/* NOTE:  This region should be large enough to supply the memory       */
/*        for all pthread stacks, pthread control blocks in the system  */

//-jrs #define  DEMO_STACK_SIZE            2048
#define  DEMO_STACK_SIZE            8192
#define  TX_REGION0_CONSTANT        32
#define  TX_REGION0_SIZE                ( (DEMO_STACK_SIZE+16) * TX_REGION0_CONSTANT)
#define  POSIX_HEAP_SIZE_IN_BYTES       (TX_REGION0_SIZE * 4)

#define  POSIX_TOTAL_MEMORY_REQUIRED    (32 + POSIX_SYSTEM_STACK_SIZE + POSIX_HEAP_SIZE_IN_BYTES + (WORK_QUEUE_DEPTH*WORK_REQ_SIZE))

/* Define number of CPU ticks per second */
#ifndef CPU_TICKS_PER_SECOND
#define  CPU_TICKS_PER_SECOND           200  /* assuming 10 mSec tick */
#endif

#ifndef NANOSECONDS_IN_CPU_TICK
#define  NANOSECONDS_IN_CPU_TICK        5000000  /* assuming 10 mSec tick */
#endif

#ifndef NANOSECONDS_PER_SECOND
#define  NANOSECONDS_PER_SECOND         1000000000  /* one BILLLLLION!!! */
#endif

/* Define queue control specific data definitions.  */

#define  TX_SEMAPHORE_ID                0x53454D41UL
#define  TX_MUTEX_ID                    0x4D555445UL
#define  TX_QUEUE_ID                    0x51554555UL
#define  PX_QUEUE_ID                    0x50515545UL

/************************************************************************/
/*             Misc. POSIX-related definitions .                        */
/************************************************************************/
#define  POSIX_STACK_PADDING            1024
#define  POSIX_SYSTEM_STACK_SIZE        1024
#define  POSIX_PTHREAD_STACK_SIZE       1024

/************************************************************************/
/*               ARCHITECTURE DEFINITIONS                               */
/************************************************************************/
/* Define all supported architectures here.  */

#define  POSIX_POWERPC                  1
#define  POSIX_68K                      2
#define  POSIX_ARM                      3
#define  POSIX_MIPS                     4

/* Define POSIX_ARCH as one of the above list.  */

#define  POSIX_ARCH                     POSIX_ARM

/* Make sure POSIX_ARCH is defined.  */

#ifndef  POSIX_ARCH
#error   Must define symbol POSIX_ARCH to *something*!
#endif

/* Define the minimum stack size for each supported architecture here.  */

#define  MIN_STACKSIZE_ARM           2048

/************************************************************************/
/*               MISCELLANEOUS CONSTANTS                                */
/************************************************************************/
/* Requests/commands to SysMgr task.  */

#define   SYSMGR_DELETE_TASK            0


/************************************************************************/
/*               MISCELLANEOUS CONSTANTS                                */
/************************************************************************/
/* Requests/commands to SysMgr task.  */

#define   SYSMGR_DELETE_TASK            0

/* pthread name length */
#define   PTHREAD_NAME_LEN              4

#define   PTHREAD_CREATE_DETACHED       1
#define   PTHREAD_CREATE_JOINABLE       0

/* scheduler related constants */

#define   SCHED_PRIO_MAX                253
#define   SCHED_PRIO_MIN                3

/* time slice value in ticks for round robin scheduler */
#define   SCHED_RR_TIME_SLICE           DEFAULT_TIME_SLICE

#define   PTHREAD_MUTEX_NORMAL          1
#define   PTHREAD_MUTEX_RECURSIVE       2
#define   PTHREAD_MUTEX_ERRORCHECK      3
#define   PTHREAD_MUTEX_DEFAULT         PTHREAD_MUTEX_RECURSIVE

#define   PTHREAD_PRIO_INHERIT          1

#define   PTHREAD_PROCESS_PRIVATE       1
#define   PTHREAD_PROCESS_SHARED        2

#define   PTHREAD_CANCEL_ENABLE         0           /* default */

#define   PTHREAD_CANCEL_DISABLE        1

#define   PTHREAD_CANCEL_DEFERRED       0          /* default */

#define   PTHREAD_CANCEL_ASYNCHRONOUS   1

#define   PTHREAD_INHERIT_SCHED         1

#define   PTHREAD_EXPLICIT_SCHED        0

#define   PTHREAD_ONCE_INIT             {0, 0, {0,NULL,0,0,NULL,0,NULL,NULL}}

enum pth_once_state {
  PTH_ONCE_INIT      = 0x0,
  PTH_ONCE_DONE      = 0x1,
  PTH_ONCE_STARTED   = 0x2,
  PTH_ONCE_CANCELLED = 0x3
};


/************************************************************************/
/*               ERROR CODES (those defined outside of POSIX)           */
/************************************************************************/

#ifdef   ERROR
#undef   ERROR
#define  ERROR                  -1
#else
#define  ERROR                  -1
#endif


#ifndef  OK
#define  OK                     0
#endif

#ifndef _WIN32
/* dp 01-Jul-2008 ; XXX remove BOOL since it collides with ATypes.h */
//typedef  ULONG                  BOOL;
#endif

/* dp 01-Jul-2008 ; changed "OK" to "TX_POSIX_SUCCESS" to avoid collision
 * with ATypes.h
 */
#ifndef  TX_POSIX_SUCCESS
#define  TX_POSIX_SUCCESS                     0
#endif

#ifndef  FALSE
#define  FALSE                  0
#endif

#ifndef  TRUE
#define  TRUE                   1
#endif

#ifndef  NULL
#define  NULL                   0
#endif

#define  NO_ERROR               0        /* Okay, no error  */

#define   WORK_REQ_SIZE         TX_2_ULONG
#define   WORK_QUEUE_DEPTH      50

#define   SYSMGR_PRIORITY       0
#define   SYSMGR_THRESHOLD      0

/* Pthread Key Data storage defs */
#define PTHREAD_KEYS_MAX                    1024
#define PTHREAD_2NDARY_KEY_TBL_SIZE         32
#define PTHREAD_2NDARY_KEY_DATA_SIZE        PTHREAD_2NDARY_KEY_TBL_SIZE
#define PTHREAD_PRIMARY_KEY_DATA_SIZE       ((PTHREAD_KEYS_MAX + PTHREAD_2NDARY_KEY_TBL_SIZE-1) / PTHREAD_2NDARY_KEY_DATA_SIZE)

/* STRUCTURES RELATED TO pthreads  */

typedef struct pthread_attr_obj
{
     /* dp 07-Oct-2008 ; to verify data structure is valid when passed to
      * mutex functions
      */
     ULONG cookie;

     ULONG                pthread_flags;
     INT                  detach_state;
     INT                  inherit_sched;
     INT                  sched_policy;
     struct sched_param   sched_attr;
     VOID                *stack_address;
     ULONG                stack_size;
     INT                  inuse;
}pthread_attr_t;


typedef  INT    ssize_t ;
typedef  ULONG  pthread_t;
typedef  UINT   pthread_key_t;
typedef  void (*destructor_func_t) (void*);

typedef  struct priv_key_index_s
{
    bool                            in_use;
    destructor_func_t               destr_func;
} priv_key_index_t ;

typedef struct priv_key_data_s
{
    bool                            in_use;
    const void*                     key_value;
} priv_key_data_t ;


#ifndef _SYS_TYPES_H  //Have to prevent mode_t define collision with system types.h
typedef  ULONG  mode_t;
#endif
/* Define POSIX Pthread control block tructure.  */

typedef struct pthread_control_block
{
    /* This pthread's ThreadX TCB.  */
    /* dp 07-Oct-2008 ; MUST be the first member of the structure because
     * tx_posix.c will cast a TX_THREAD to a PCB. I add the cookie check to make
     * sure we don't get a TX_THREAD not part of a PCB.
     */
    TX_THREAD            thread_info;

    /* dp 07-Oct-2008 ; to verify data structure is valid when passed to
     * pthread functions
     */
    ULONG cookie;

    /* This pthread's unique identifier */
    pthread_t            pthreadID;
    /* To check if posix Pthread is in use.  */
    UINT                 in_use;
    /* All pthread attributes contained in the a pthread_attr_t object */
    ULONG                pthread_flags;
    INT                  detach_state;
    INT                  inherit_sched;
    INT                  sched_policy;
    struct sched_param   sched_attr;
    VOID                *stack_address;
    ULONG                stack_size;
    INT                  cancel_state;
    INT                  cancel_type;
    /* Identifier of the target thread to which this pthread is joined */
    pthread_t            joined_to_pthreadID;
    /* Identifier of the caller thread which has joined to this thread*/
    pthread_t            joined_by_pthreadID;
    /* To check if posix pthread is joined to any other pthread */
    UINT                 is_joined_to;
    /* To check if posix Pthread is joined by any other pthread */
    UINT                 is_joined_by;
    /* To check if posix Pthread is in detached state or not */
    UINT                 is_detached;
    /* Value returned by the terminating thread which is joined to this thread */
    VOID                *value_ptr;
    /* Define the original pthread priority.  */
    ULONG                orig_priority;
    /* Define the current pthread priority.  */
    ULONG                 current_priority;
    /* Define the pthread's pre-emption threshold.  */
    ULONG                 threshold;
    /* Define the pthread's timeslice.  */
    ULONG                 time_slice;
    /* specify pthread start routine */
    VOID                 *(*start_routine)(VOID *);
    /* specify argument for start up routine */
    ULONG               *entry_parameter;

    /* dp 09-Jul-2008 ; use event flags to synchronize pthread_join() and
     * pthread_exit()
     */
    TX_EVENT_FLAGS_GROUP join_flags;

    /* to hold error code for this pthread */
     ULONG                perrno;

     /* to hold pthread cancel request */
     UINT                 cancel_request;

     /*EH: Added following 5 to support pthread_lock/unlock*/
     UINT                 lockCnt;

     /*define current work priority*/
     UINT                 priority;

     /* Save current priority during lock  */
     UINT                 saved_priority_locked;

     /* Save current time slice during lock  */
     UINT                 saved_time_slice_locked;

     /* Define the task's timeslice.  */
     ULONG                taskIncTicks;

    /* dp 15-Jul-2008 ; make errno threadsafe */
    //INT errno;

    /* Thread specific key data arry */
    priv_key_data_t       key_data[PTHREAD_PRIMARY_KEY_DATA_SIZE];
    priv_key_data_t       *key_data_2ndary[PTHREAD_2NDARY_KEY_TBL_SIZE];
    bool                  key_data_dirty_flag;
	
    VOID                 *stack_address_unaligned;	
	bool                  stack_flag;

} POSIX_TCB;

typedef struct pthread_mutex_attr_obj
{
    /* dp 07-Oct-2008 ; to verify data structure is valid when passed to
     * mutex functions
     */
    ULONG cookie;

    INT                 type;
    INT                 protocol;
    INT                 pshared;
    INT                 in_use;
}pthread_mutexattr_t;

/* Define POSIX mutex structure.  */

typedef struct pthread_mutex_control_block
{
    /* This mutex's ThreadX Control block  */
    TX_MUTEX      tx_mutex;

    /* This mutex's attributes */
    INT           type;

    /* Is this Mutex object is in use?  */
    INT           in_use;

}pthread_mutex_t;


struct mq_attr {
	 /* No. of maximum messages.  */
    ULONG  mq_maxmsg;
    /* Size of the message.  */
    ULONG mq_msgsize;
    /* Flags are ignored as these are passed separately in open().  */
    ULONG mq_flags;
    ULONG mq_curmsgs;
};

/*     STRUCTURES RELATED TO POSIX MESSAGE QUEUE   */

/* Define POSIX message queue structure.  */
typedef struct msg_que
{
    /* Define ThreadX queue.  */
    TX_QUEUE                      queue;
    /* To check if posix queue is in use.  */
    UINT                          in_use;
    /* To check if queue is unlinked.  */
    UINT                          unlink_flag;
    /* Name of queue.  */
    /* dp 10-Jul-2008 ; change to a real string same as I did with sem_t (see
     * struct POSIX_SEMAPHORE_STRUCT for more details)
     */
    char                          mq_name[MQ_PATH_MAX+1];

    /* Attribute of queue.  */
    struct mq_attr                q_attr;
    /* To check no. of times queue is opened.  */
    UINT                          open_count;
    /* Address for variable length message.  */
    VOID                        * storage;

    /* Byte pool for variable length message.  */
    //TX_BYTE_POOL                  vq_message_area;

    /* POSIX queue ID.  */
    ULONG                         px_queue_id;

} POSIX_MSG_QUEUE;

/* Define Queue Descriptor.  */
typedef struct mq_des
{
    /* dp 15-Jul-2008 ; to verify data structure is valid when passed to mqd
     * functions
     */
    ULONG cookie;

    /* Queue FLAGS.  */
    ULONG                         f_flag;
    /* message Queue structure.  */
    POSIX_MSG_QUEUE             * f_data;

}*mqd_t;


/* STRUCTURES RELATED TO POSIX SEMAPHORES  */

typedef struct POSIX_SEMAPHORE_STRUCT
{
    /* dp 06-Oct-2008 ; to verify data structure is valid when passed to sem
     * functions
     */
    /* ThreadX semaphore.  */
    TX_SEMAPHORE sem;

    /* To check if semaphore is in use.  */
    UINT in_use;

    /* semaphore identifier  */
    ULONG psemId;

    /* number of attachments  */
     ULONG                         refCnt;        /* previously it was int  */

     /* name of semaphore  */
    /* dp 08-Jul-2008 ; change to a real string so we can really save the
     * name as opposed to saving a pointer to the name to fix problem with
     * non-constant strings;  note the +1 for string NULL
     */
    char sem_name[SEM_NAME_MAX+1];
    /* Open Count.  */
    ULONG count;
    /* For unlink flag.  */
    ULONG unlink_flag;

} sem_t;

typedef sem_t *SEM_ID;

#define SEM_FAILED ((sem_t *)ERROR)

typedef struct pthread_cond_obj
{
    /* dp 06-Oct-2008 ; to verify data structure is valid when passed to sem
     * functions
     */
    //ULONG cookie;

    /* This pthread condition variable's internal counting Semaphore  */
    TX_SEMAPHORE        cond_semaphore;

    INT                 type;
    INT                 in_use;
}pthread_cond_t;

typedef struct pthread_condattr_obj
{
     INT                 type;
     INT                 in_use;
}pthread_condattr_t;



typedef struct  pthread_once_obj
{
  UINT          state;
  ULONG          flags;
  TX_EVENT_FLAGS_GROUP   event;
}pthread_once_t;

//typedef void *timer_t;
#if 0
#define SIGEV_THREAD  1
#define SIGSTOP      19

union sigval {
    /** integer signal value */
    int sival_int;

    /** pointer signal value */
    void* sival_ptr;
};

struct sigevent {
    /** notification type */
    int sigev_notify;

    int sigev_signo;

    union sigval sigev_value;

    void (*sigev_notify_function)( union sigval );

    pthread_attr_t *sigev_notify_attributes;
};

struct tx_posix_timer {
    ULONG cookie;
    struct sigevent sigevent;
    TX_TIMER tx_timer;
};
#endif

/* dp 15-Jul-2008 ; cookies to verify pointers passed to the tx_posix
 * functions
 */
#define TX_POSIX_MSGQ_COOKIE 0x238501c3
#define TX_POSIX_SEMAPHORE_COOKIE 0x8E4BD887
#define TX_POSIX_PTHREAD_COND_COOKIE 0x512B54F4
#define TX_POSIX_PTHREAD_MUTEX_COOKIE 0xF0A4E42C
#define TX_POSIX_PTHREAD_MUTEX_ATTR_COOKIE 0xA88ED765
#define TX_POSIX_PTHREAD_ATTR_COOKIE 0x30E4280A
#define TX_POSIX_PTHREAD_COOKIE 0x50FE974F
#define TX_POSIX_TIMER_COOKIE 0x0DFD81AF

/* Subtract two struct timespec values (not POSIX); also declared in ostools.h
 * but I didn't want to put ostools.h into tx_posix.c (which needs to stay as
 * clean as possible).  The implementation is in ostools.c.
 */
int timespec_sub( const struct timespec *a,
                  const struct timespec *b,
                  struct timespec *result );


/* Define POSIX API function prototypes.  */
#if 0
VOID                 *posix_initialize(VOID * posix_memory);
#else
VOID                 posix_initialize(VOID);	
#endif

INT                   mq_send(mqd_t mqdes, const char * msg_ptr,
                                size_t msg_len,ULONG msg_prio );
INT                   mq_timedsend( mqd_t mqdes, const CHAR * msg_ptr, size_t msg_len,
                              ULONG msg_prio, const struct timespec *abs_timeout);

ssize_t               mq_receive(mqd_t mqdes, VOID *pMsg, size_t msgLen,
                                   ULONG *pMsgPrio );

ssize_t               mq_timedreceive(mqd_t mqdes, VOID * pMsg, size_t msgLen,
		                           ULONG *pMsgPrio, const struct timespec *abs_timeout);

INT                   mq_unlink(const char * mqName);
INT                   mq_close(mqd_t mqdes);
mqd_t                 mq_open(const CHAR * mqName, ULONG oflags,...);
INT                   mq_getattr( mqd_t mqdes, struct mq_attr  *attr );
INT                   sem_close(sem_t  * sem);
INT                   sem_getvalue(sem_t * sem,ULONG * sval);
sem_t                *sem_open(const char * name, ULONG oflag, ...);
INT                   sem_post(sem_t * sem);
INT                   sem_trywait(sem_t * sem);
INT                   sem_unlink(const char * name);
INT                   sem_wait( sem_t * sem );
INT                   sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
INT                   sem_init(sem_t *sem , INT pshared, UINT value);
INT                   sem_destroy(sem_t *sem);

INT                   pthread_create (pthread_t *thread,  pthread_attr_t *attr,
                                      VOID *(*start_routine)(VOID*),VOID *arg);
INT                   pthread_create_named (pthread_t *thread, const char *name, pthread_attr_t *attr,
                                       void *(*start_routine)(void*),void *arg);

INT                   pthread_detach(pthread_t thread);
INT                   pthread_join(pthread_t thread, VOID **value_ptr);
INT                   pthread_equal(pthread_t thread1, pthread_t thread2);
VOID                  pthread_exit(VOID *value_ptr);
pthread_t             pthread_self(VOID);
INT                   pthread_lock(VOID);
INT                   pthread_unlock(VOID);
INT                   pthread_attr_destroy(pthread_attr_t *attr);
INT                   pthread_attr_getdetachstate( pthread_attr_t *attr,INT *detachstate);
INT                   pthread_attr_setdetachstate(pthread_attr_t *attr,INT detachstate);
INT                   pthread_attr_getinheritsched(pthread_attr_t *attr, INT *inheritsched);
INT                   pthread_attr_setinheritsched(pthread_attr_t *attr, INT inheritsched);
INT                   pthread_attr_getschedparam(pthread_attr_t *attr,struct sched_param *param);
INT                   pthread_attr_setschedparam(pthread_attr_t *attr,struct sched_param *param);
INT                   pthread_attr_getschedpolicy(pthread_attr_t *attr, INT *policy);
INT                   pthread_attr_setschedpolicy(pthread_attr_t *attr, INT policy);
INT                   pthread_attr_init(pthread_attr_t *attr);
INT                   pthread_attr_getstackaddr( pthread_attr_t *attr,VOID **stackaddr);
INT                   pthread_attr_setstackaddr(pthread_attr_t *attr,VOID *stackaddr);
INT                   pthread_attr_getstacksize( pthread_attr_t *attr, size_t *stacksize);
INT                   pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
INT                   pthread_attr_getstack( pthread_attr_t *attr,VOID **stackaddr,
                                           size_t *stacksize);
INT                   pthread_attr_setstack( pthread_attr_t *attr,VOID *stackaddr,
                                            size_t stacksize);
INT                   pthread_mutexattr_gettype(pthread_mutexattr_t *attr, INT *type);
INT                   pthread_mutexattr_settype(pthread_mutexattr_t *attr, INT type);
INT                   pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
INT                   pthread_mutexattr_init(pthread_mutexattr_t *attr);
INT                   pthread_mutex_destroy(pthread_mutex_t *mutex);
INT                   pthread_mutex_init(pthread_mutex_t *mutex, pthread_mutexattr_t *attr);
INT                   pthread_mutex_lock(pthread_mutex_t *mutex );
INT                   pthread_mutex_unlock(pthread_mutex_t *mutex );
INT                   pthread_mutex_trylock(pthread_mutex_t *mutex);
INT                   pthread_mutexattr_getprotocol( pthread_mutexattr_t *attr, INT *protocol);
INT                   pthread_mutexattr_setprotocol(pthread_mutexattr_t *attr, INT protocol);
INT                   pthread_mutexattr_getpshared (pthread_mutexattr_t *attr, INT *pshared);
INT                   pthread_mutexattr_setpshared (pthread_mutexattr_t *attr, INT pshared);
INT                   pthread_mutex_timedlock(pthread_mutex_t *mutex, struct timespec *abs_timeout);
INT                   pthread_setcancelstate (INT state, INT *oldstate);
INT                   pthread_setcanceltype (INT type, INT *oldtype);
INT                   pthread_cancel(pthread_t thread);
VOID                  pthread_yield(VOID);
INT                   pthread_once (pthread_once_t * once_control, VOID (*init_routine) (VOID));
VOID                  pthread_testcancel(VOID);
INT                   pthread_setschedparam(pthread_t thread, INT policy, const struct sched_param *param);
INT                   pthread_getschedparam(pthread_t thread, INT *policy, struct sched_param *param);

INT                   pthread_cond_destroy(pthread_cond_t *cond);
INT                   pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *attr);
INT                   pthread_cond_broadcast(pthread_cond_t *cond);
INT                   pthread_cond_signal(pthread_cond_t *cond);
#if 1
INT                   pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, struct timespec *abstime);
#else
int                   pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, struct timespec *abstime);
#endif
INT                   pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);

#if 0
/* Marvell change to support including <unistd.h> from toolchain */
#ifndef _SYS_UNISTD_H
#define _SYS_UNISTD_H
INT                   sleep(ULONG seconds);
#endif
INT                   nanosleep(struct timespec *req, struct timespec *rem);
INT                   clock_gettime(clockid_t t, struct timespec * tspec);
#endif
INT                   posix_get_pthread_errno(pthread_t ptid);

#if 0
INT                   timer_create( clockid_t clock_id, struct sigevent *evp, timer_t *timer_id );
INT                   timer_delete( timer_t timer_id );
INT                   timer_settime( timer_t timer_id, int flags, const struct itimerspec *value, struct itimerspec *ovalue );
#endif

/* brianm 2011-07-12 ; add key data storage funcs */
int                   pthread_key_create(pthread_key_t *key, void (*destr)(void *));
int                   pthread_key_delete(pthread_key_t key);

int                   pthread_setspecific(pthread_key_t key, const void* data);

void*                 pthread_getspecific(pthread_key_t key);

/* static mutex initializer */

#define PTHREAD_MUTEX_INITIALIZER  {{TX_MUTEX_ID, "PMTX", 0, NULL, 0, 0, 0,  NULL, 0 , NULL, NULL}, PTHREAD_MUTEX_RECURSIVE , TX_TRUE}

/* static conditional variable initializer */
#define PTHREAD_COND_INITIALIZER  {{TX_SEMAPHORE_ID, "CSEM", 0, NULL, 0, NULL, NULL}, TX_TRUE}

#ifdef __cplusplus
}
#endif

#endif      /* TX_POSIX  */

