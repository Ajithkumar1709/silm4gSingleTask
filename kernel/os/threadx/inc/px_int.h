/*
 * px_int.h
 *
 *
 *
 */

#ifndef PX_INT_H_
#define PX_INT_H_


/* dp 09-Jul-2008 ; include XASSERT */
#include  <string.h>
#include "stdlib.h"
#include "tx_posix.h"

/*Following are Marvell defines for debug purpose */
#ifdef DEBUG

extern void _assert(const char *, const char *, int);
extern void XAssertFail(const char *, const char *, int, unsigned long int);
# define ASSERT(e) ((e) ? (void)0 : _assert(#e, __FILE__, __LINE__))
# define XASSERT(e,errvalue) ((e) ? (void)0 : XAssertFail(#e, __FILE__,__LINE__,(errvalue)))

/* turn on extra checking */
#define SANITY_CHECKS

#else
#define ASSERT(e)
#define XASSERT(e,errvalue)

#endif

//#define PTR_FREE(ptr)  do { memFree((ptr)); (ptr)=NULL; } while(0)

/* Define several ThreadX equates for use inside of POSIX. */
#define  TX_INITIALIZE_IN_PROGRESS      0xF0F0F0F0UL
#define  TX_INITIALIZE_ALMOST_DONE      0xF0F0F0F1UL

/* Include necessary definition for memory related routines(from tx_byt.c). */
#define  TX_BYTE_BLOCK_FREE             0xFFFFEEEEUL
#define  TX_BYTE_BLOCK_ALLOC            0xAAAAAAAAUL
#define  TX_BYTE_POOL_ID                0x42595445UL

/* Threadx min and max priority */
#define TX_HIGHEST_PRIORITY                 0
#define TX_LOWEST_PRIORITY                 255

#define PX_HIGHEST_PRIORITY                SCHED_PRIO_MAX // defined in tx_posix.h, 31 expected
#define PX_LOWEST_PRIORITY                 SCHED_PRIO_MIN // defined in tx_posix.h, 1 expected

// macro to convert a pthread thread priority to a ThreadX thread priority
#define PTHR_TO_TX_PRIORITY_CONVERT(pth_pri)  (TX_LOWEST_PRIORITY - (pth_pri) + 1)

// macro to convert a ThreadX thread priority to a pthread thread priority
#define TX_TO_PTHR_PRIORITY_CONVERT(tx_pri)   (TX_LOWEST_PRIORITY - (tx_pri) + 1)

/* dp 09-Jul-2008 ; flags for pthread_join()/pthread_exit() event flags
 * rendezvous
 */
#define POSIX_TCB_JOIN_PARENT  (1<<0)
#define POSIX_TCB_JOIN_CHILD   (1<<1)
#define POSIX_TCB_JOIN_CHILD_EXIT (1<<2)
#define POSIX_TCB_JOIN_PARENT_RELEASE (1<<3)

/* Pthread Key Data storage defs */
#define PTHREAD_KEY_SALT                    0
#define PTHREAD_DESTRUCTOR_ITERATIONS       4



/************ Extern functions **************/
extern UINT            _tx_thread_resume(TX_THREAD *thread_ptr);
extern VOID            _tx_thread_system_return(VOID);
extern UINT            _tx_timer_deactivate(TX_TIMER_INTERNAL *timer_ptr);

/************ Extern Variables **************/
extern TX_THREAD *     _tx_thread_current_ptr;
extern TX_THREAD *     _tx_thread_execute_ptr;



/* declares posix objects in the px_pth_init.c file */
#ifdef  PX_OBJECT_INIT
#define PX_OBJECT_DECLARE
#else
#define PX_OBJECT_DECLARE extern
#endif

/**************************************************************************/
/*                             Global Definitions                         */
/**************************************************************************/

/* The ThreadX work queue for the POSIX System Manager.    */
PX_OBJECT_DECLARE TX_QUEUE                     posix_work_queue;

/* Define the thread for the System Manager functionality.  */
PX_OBJECT_DECLARE TX_THREAD                    posix_system_manager;


/**************************************************************************/
/*                       Local definitions                                 */
/**************************************************************************/

/* Define a byte pool control block for the heap memory used
   by POSIX.  */
PX_OBJECT_DECLARE  TX_BYTE_POOL          posix_heap_byte_pool;

/* Define a static pool of pthread Control Blocks (TCB). If more pthreades are
   required the constant PTHREAD_THREADS_MAX (in tx_posix.h) may be modified.   */
PX_OBJECT_DECLARE POSIX_TCB             ptcb_pool[PTHREAD_THREADS_MAX];

#if POSIX_MAX_QUEUES!= 0
/* Define a static pool of queues.If more pthread message queues are required
   the constant POSIX_MAX_QUEUES (in tx_posix.h) may be modified.               */
PX_OBJECT_DECLARE POSIX_MSG_QUEUE       posix_queue_pool[POSIX_MAX_QUEUES];
/* Define a queue attribute.            */
PX_OBJECT_DECLARE struct mq_attr        posix_qattr_default;
#endif

#if  SEM_NSEMS_MAX != 0
/* Define a static pool of semaphores. If more pthread semaphores required the
   constant SEM_NSEMS_MAX (in tx_posix.h) may be modified.                      */
PX_OBJECT_DECLARE sem_t posix_sem_pool[SEM_NSEMS_MAX];
#endif

/* Define a default pthread attribute.  */
PX_OBJECT_DECLARE pthread_attr_t posix_default_pthread_attr;

/* Define a default mutex attribute.    */
PX_OBJECT_DECLARE pthread_mutexattr_t    posix_default_mutex_attr;


/* Define a temporary posix errno.  */
PX_OBJECT_DECLARE INT foo_posix_errno;

PX_OBJECT_DECLARE unsigned int posix_errno;

/* Thread specific key data index arry */
PX_OBJECT_DECLARE UINT         pthread_key_count;
PX_OBJECT_DECLARE priv_key_index_t  pthread_key_index[PTHREAD_KEYS_MAX];

/**************************************************************************/
/*                      Local prototypes                                  */
/**************************************************************************/

 POSIX_MSG_QUEUE      *posix_mq_create ( const CHAR * mq_name,
                                                struct mq_attr * msgq_attr);

 POSIX_MSG_QUEUE      *posix_find_queue(const CHAR * mq_name);

 POSIX_MSG_QUEUE      *posix_get_new_queue(ULONG maxnum, UINT msg_size);

 ULONG                 posix_arrange_msg( TX_QUEUE * Queue, ULONG * pMsgPrio );

 ULONG                 posix_priority_search(mqd_t msgQId ,ULONG priority);

 VOID                  posix_queue_init(VOID);

 VOID                  posix_qattr_init(VOID);

 VOID                  posix_pthread_init(VOID);

 struct mq_des        *posix_get_queue_des(POSIX_MSG_QUEUE * q_ptr);

 VOID                  posix_reset_queue(POSIX_MSG_QUEUE * q_ptr);

 VOID                  posix_memory_release(VOID * memory_ptr);

#ifdef DEBUG
 VOID                  posix_internal_error_debug(ULONG error_code, const char *func);
 #define posix_internal_error(x) posix_internal_error_debug(x, __FUNCTION__)
#else
 VOID                  posix_internal_error(ULONG error_code);
#endif

 VOID                  posix_error_handler(ULONG error_code);

 INT                   posix_memory_allocate( ULONG size, VOID **memory_ptr );

 INT                   posix_queue_delete(POSIX_MSG_QUEUE  * q_ptr);

 sem_t                *posix_find_sem(const CHAR * name);

 VOID                  posix_set_sem_name( sem_t* sem, CHAR *name);

 sem_t                 *posix_get_new_sem(VOID);

 VOID                  posix_sem_reset(sem_t *sem);

 ULONG                 posix_in_thread_context(VOID);

 VOID                  posix_reset_pthread_t(POSIX_TCB *pthread_ptr );

/* dp 08-Jul-2008 ; must expose this function to the outside world so I can
 * pass the ThreadX TX_THREAD to the resource manager
 */
TX_THREAD            *posix_tid2thread(pthread_t ptid);
//static TX_THREAD            *posix_tid2thread(pthread_t ptid);

 POSIX_TCB            *posix_tid2tcb(pthread_t ptid);

 pthread_t             posix_thread2tid(TX_THREAD *thread_ptr);

 POSIX_TCB            *posix_thread2tcb(TX_THREAD *thread_ptr);

 TX_THREAD            *posix_tcb2thread (POSIX_TCB *pthread_ptr);

 VOID                  posix_thread_wrapper(ULONG pthr_ptr);

 VOID                  set_default_pthread_attr(struct pthread_attr_obj *attr);

 VOID                  set_default_mutexattr(struct pthread_mutex_attr_obj *attr);

 INT                   posix_allocate_pthread_t(POSIX_TCB **ptcb_ptr);

 VOID                  posix_copy_pthread_attr(POSIX_TCB *pthread_ptr,
                                                     struct pthread_attr_obj *attr);

 VOID                  posix_destroy_pthread(POSIX_TCB *pthread_ptr, VOID *value_ptr);

 VOID                  posix_do_pthread_delete(POSIX_TCB *pthread_ptr, VOID *value_ptr);

 VOID                  posix_system_manager_entry(ULONG input);

/* dp 07-Jul-2008 ; add abs_timeout_to_ticks() prototype */
 ULONG                 abs_timeout_to_ticks( const struct timespec *abs_timeout );

 INT                   posix_set_pthread_errno(ULONG errno_set);

 ULONG                 posix_abs_time_to_rel_ticks(struct timespec *abs_timeout);

 VOID                  posix_putback_queue(TX_QUEUE * qid);

 VOID                  posix_pth_key_index_init(void);

 VOID                  posix_pth_key_data_init(POSIX_TCB *pthread_ptr);

 VOID                  posix_pth_key_data_exit_cleanup(POSIX_TCB *pthread_ptr);

 #endif /* PX_INT_H_ */
