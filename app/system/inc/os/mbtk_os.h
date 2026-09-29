
#ifndef __MBTK_OS_H
#define __MBTK_OS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mbtk_pub_type.h"
#include "time.h"
#include "stdbool.h"
#include "mbtk_socket_api.h"

typedef void* mbtk_taskref;
typedef void* mbtk_hisrref;
typedef void* mbtk_msgqref;
typedef void* mbtk_mailboxqref;
typedef void* mbtk_semref;
typedef void* mbtk_mutexref;
typedef void* mbtk_flagref;
typedef void* mbtk_osmemref;
typedef void* mbtk_ostimerref;


typedef void  *mbtk_osref;
typedef uint8_t mbtk_os_status;
typedef struct 
{
	uint32_t status;
}mbtk_os_timer_status_struct;



#define MBTK_OS_NULL                NULL
#define MBTK_OS_TIMER_DEAD          0
#define MBTK_OS_TIMER_CREATED       1
#define MBTK_OS_TIMER_ACTIVE        2
#define MBTK_OS_TIMER_INACTIVE      3
#define MBTK_OS_ENABLED             2
#define MBTK_OS_DISABLED            3



#define MBTK_OS_SUSPEND    			0xFFFFFFFF
#define MBTK_OS_NO_SUSPEND          0
#define MBTK_OS_ENABLE_INTERRUPTS   1
#define MBTK_OS_DISABLEE_INTERRUPTS 2
#define MBTK_OS_PIPE_MEM_OVERHEAD   4
#define MBTK_OS_FLAG_AND           	5
#define MBTK_OS_FLAG_AND_CLEAR     	6
#define MBTK_OS_FLAG_OR             7
#define MBTK_OS_FLAG_OR_CLEAR       8
#define MBTK_OS_FIXED               9
#define MBTK_OS_FIFO       			11
#define MBTK_OS_PRIORITY   			12


#define MBTK_OS_HISR_PRIORITY_HIGH 0
#define MBTK_OS_HISR_PRIORITY_MID  1
#define MBTK_OS_HISR_PRIORITY_LOW  2



typedef enum
{
	mbtk_os_success = 0,     		/* 0x0 -no errors										  */
	mbtk_os_fail,					/* 0x1 -operation failed code							  */
	mbtk_os_timeout,				/* 0x2 -Timed out waiting for a resource				  */
	mbtk_os_no_resources,			/* 0x3 -Internal OS resources expired					  */
	mbtk_os_invalid_pointer,		/* 0x4 -0 or out of range pointer value				      */
	mbtk_os_invalid_ref,			/* 0x5 -invalid reference								  */
	mbtk_os_invalid_del,			/* 0x6 -deleting an unterminated task					  */
	mbtk_os_invalid_ptr,			/* 0x7 -invalid memory pointer 							  */
	mbtk_os_invalid_mem,			/* 0x8 -invalid memory pointer 							  */
	mbtk_os_invalid_size,			/* 0x9 -out of range size argument 						  */
	mbtk_os_invalid_mode,			/* 0xA, 10 -invalid mode								  */
	mbtk_os_invalid_priority,		/* 0xB, 11 -out of range task priority 					  */
	mbtk_os_unavailable,			/* 0xC, 12 -Service requested was unavailable or in use   */
	mbtk_os_pool_empty,				/* 0xD, 13 -no resources in resource pool				  */
	mbtk_os_queque_full,			/* 0xE, 14 -attempt to send to full messaging queue		  */	
	mbtk_os_queue_empty,			/* 0xF, 15 -no messages on the queue					  */
	mbtk_os_no_mem,					/* 0x10, 16 -no memory left								  */
	mbtk_os_deleted,				/* 0x11, 17 -service was deleted						  */
	mbtk_os_sem_deleted,			/* 0x12, 18 -semaphore was deleted 						  */
	mbtk_os_mutex_deleted,			/* 0x13, 19 -mutex was deleted 							  */
	mbtk_os_msgq_deleted,			/* 0x14, 20 -msg Q was deleted 							  */
	mbtk_os_mbox_deleted,			/* 0x15, 21 -mailbox Q was deleted 						  */
	mbtk_os_flag_deleted,			/* 0x16, 22 -flag was deleted							  */
    mbtk_os_invalid_vector,			/* 0x17, 23 -interrupt vector is invalid				  */
    mbtk_os_no_tasks,				/* 0x18, 24 -exceeded max # of tasks in the system 		  */
    mbtk_os_no_flags,				/* 0x19, 25 -exceeded max # of flags in the system 		  */
    mbtk_os_no_sems,				/* 0x1A, 26 -exceeded max # of semaphores in the system   */
    mbtk_os_no_mutexs,				/* 0x1B, 27 -exceeded max # of mutexes in the system	  */
    mbtk_os_no_queues,				/* 0x1C, 28 -exceeded max # of msg queues in the system   */
    mbtk_os_no_mboxs,				/* 0x1D, 29 -exceeded max # of mbox queues in the system  */
    mbtk_os_no_timers,				/* 0x1E, 30 -exceeded max # of timers in the system	      */
    mbtk_os_no_mem_pools,			/* 0x1F, 31 -exceeded max # of mem pools in the system    */
    mbtk_os_no_interrupts,			/* 0x20, 32 -exceeded max # of isr's in the system 	 	  */
    mbtk_os_flag_not_present,		/* 0x21, 33 -requested flag combination not present	 	  */
    mbtk_os_unsupported,			/* 0x22, 34 -service is not supported by the OS		 	  */
    mbtk_os_no_mem_cells,			/* 0x23, 35 -no global memory cells					      */
    mbtk_os_duplicate_name,			/* 0x24, 36 -duplicate global memory cell name 			  */
    mbtk_os_invalid_param			/* 0x25, 37 -invalid parameter                            */
}mbtk_os_return_enum;







typedef enum 
{
	mbtk_task_ready,
	mbtk_task_completed,
	mbtk_task_terminated,
	mbtk_task_suspended,
	mbtk_task_sleep,
	mbtk_task_queue_susp,
	mbtk_task_sem_susp,
	mbtk_task_event_falg,
	mbtk_task_block_mem,
	mbtk_task_mutex_susp,
	mbtk_task_state_unkown
}mbtk_task_state_enum;



typedef struct 
{
    char                	*task_name;                		
    unsigned int        	task_priority;             	
    unsigned long        	task_stack_def_val;       
    mbtk_task_state_enum    task_state;             
    unsigned long       	task_stack_ptr;          
    unsigned long       	task_stack_start;         
    unsigned long       	task_stack_end;           
    unsigned long       	task_stack_size;           	
    unsigned long       	task_run_count;           
} mbtk_task_info_struct;

typedef struct 
{
    char                	*task_name;                		
    unsigned int        	task_priority;             	
    unsigned long        	task_stack_def_val;       
    mbtk_task_state_enum    task_state;             
    unsigned long       	task_stack_ptr;          
    unsigned long       	task_stack_start;         
    unsigned long       	task_stack_end;           
    unsigned long       	task_stack_size;           	
    unsigned long       	task_run_count;           
    
    unsigned long           pStackInuse;
    unsigned long           pStackPeak;
    UINT32                  poolSize ;
} mbtk_task_info_struct_ex;

#define MBTK_DUMP_INFO_SIZE 100
#define MBTK_DUMP_INFO_NUM 2
#define MBTK_DUMP_HEAP_SIZE 2048

typedef struct
{
	char dump_heap[MBTK_DUMP_HEAP_SIZE];
}mbtk_dump_info;


/**************************strcut tm defined at <time.h>
struct tm
{
  int	tm_sec;
  int	tm_min;
  int	tm_hour;
  int	tm_mday;
  int	tm_mon;
  int	tm_year;
  int	tm_wday;
  int	tm_yday;
  int	tm_isdst;
  long int tm_gmtoff;
  const char *tm_zone;
};
**************************/
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_task_creat
 * DESCRIPTION 
 *  	This API is used to creat a task.  
 * PARAMETERS 
 *		taskref		[IN]:A pointer type variable that points to the task reference
 *		stackptr	[IN]:The task's own stack pointer
 *		stacksize	[IN]:The task's own stack size
 *		priority	[IN]:The priority of the task
 *		taskname	[IN]:The name of the task
 *		taskfunc	[IN]:The execution function of the task
 *		argv	    [IN]:Arguments to the execution function of the task
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_task_creat(mbtk_taskref * taskref, void * stackptr, u32 stacksize,
									u8 priority, char * taskname, void (* taskfunc)(void *), void * argv);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_task_delete
 * DESCRIPTION 
 *  	This function is used to delete the task specified in the incoming taskref. 
 * PARAMETERS 
 *		taskref		[IN]:A variables referenced by the task
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_task_delete(mbtk_taskref taskref);// delet a task , can't run lisr and timer callback
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_task_suspend
 * DESCRIPTION 
 *  	This function is used to suspend the task specified in the incoming taskref.  
 * PARAMETERS 
 *		taskref		[IN]:A variables referenced by the task
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_task_suspend(mbtk_taskref taskref);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_task_resume
 * DESCRIPTION 
 *  	This function is used to resume the task specified in the incoming taskref.  
 * PARAMETERS 
 *		taskref		[IN]:A variables referenced by the task
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_task_resume(mbtk_taskref taskref);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_task_sleep
 * DESCRIPTION 
 *  	This API is used to sleep specified ticks for a task who call this api.
 * PARAMETERS 
 *		ticks		[IN]:Tick value of task sleep (1tick = 5ms)
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_os_task_sleep(uint32_t ticks); // 1 tick = 5ms
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_task_get_current_ref
 * DESCRIPTION 
 *  	This API is used to get the task reference who call this api.
 * PARAMETERS 
 *		taskref		[IN]:A pointer type variable that points to the task reference
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_task_get_current_ref(mbtk_taskref * taskref);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_task_terminate
 * DESCRIPTION 
 *  	This function is used to stop the task specified in the incoming taskref. 
 * PARAMETERS 
 *		taskref		[IN]:A variables referenced by the task
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_task_terminate(mbtk_taskref taskref); // stop a task

// ----------------------------------------------------  HISR --------------------------------------------------------------//
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_creat_hisr
 * DESCRIPTION 
 *  	This API is used to creat a HISR task, usually used to execute other code after LISR calling it.  
 * PARAMETERS 
 *		hisrref		   [IN]:A pointer type variable that points to the HISR task reference
 *		hisrname	   [IN]:The name of the HISR task
 *		hisr_entry	   [IN]:The execution function of the HISR task
 *		hisr_priority  [IN]:The priority of the HISR task
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_os_creat_hisr(mbtk_hisrref * hisrref, char * hisrname, void (* hisr_entry)(void), uint8_t hisr_priority);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_active_hisr
 * DESCRIPTION 
 *  	This API is used to activate the HISR task passed the incomming HISR task reference pointer.  
 * PARAMETERS 
 *		hisrref		   [IN]:A pointer type variable that points to the HISR task references
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_os_active_hisr(mbtk_hisrref * hisrref);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_delete_hisr
 * DESCRIPTION 
 *  	This API is used to delete the HISR task passed the incomming HISR task reference pointer.  
 * PARAMETERS 
 *		hisrref		   [IN]:A pointer type variable that points to the HISR task references
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_os_delete_hisr(mbtk_hisrref *hisrref);
// ----------------------------------------------------  MESSAGE --------------------------------------------------------------//
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_msgq_creat
 * DESCRIPTION 
 *  	This API is used to creat a message queue.  
 * PARAMETERS 
 *		msgref		[IN]:A pointer type variable that points to the message queue reference
 *		queuename	[IN]:The name of message queue.
 *		maxsize	    [IN]:The maximum size of a single message in the message queue
 *		maxnum	    [IN]:The maximum number of messages that a message queue can hold
 *		mode	    [IN]:The mode of message queue hanle message.
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_msgq_creat(mbtk_msgqref * msgref, char * queuename, uint32_t maxsize, uint32_t maxnum, uint8_t mode);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_msgq_send
 * DESCRIPTION 
 *  	This API is used to send a message to specified message queue.  
 * PARAMETERS 
 *		msgref		[IN]:A variables referenced by the message queue
 *		size	    [IN]:The size of send message.
 *		msgptr	    [IN]:The Pointer of the sending message
 *		timeout	    [IN]:The timeout for the message sending
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_msgq_send(mbtk_msgqref msgref, uint8_t size, char * msgptr, uint32_t timeout);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_msgq_recv
 * DESCRIPTION 
 *  	This API is used to recv a message to specified message queue.  
 * PARAMETERS 
 *		msgref		[IN]:A variables referenced by the message queue
 *		msgptr 	    [IN]:The pointer of the recv message
 *		size	    [IN]:The size of recv message.
 *		timeout	    [IN]:The timeout for the message recving
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_msgq_recv(mbtk_msgqref msgref, char * msgptr, uint8_t size, uint32_t timeout);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_msgq_poll
 * DESCRIPTION 
 *  	This API is used to get message's count by specified message queue.  
 * PARAMETERS 
 *		msgref		[IN]:A variables referenced by the message queue
 *		msgcount 	[IN]:The Pointer of the message count
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_msgq_poll(mbtk_msgqref		msgref, uint32_t * msgcount);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_msgq_delete
 * DESCRIPTION 
 *  	This API is used to delet message queue passed incoming message queue reference.  
 * PARAMETERS 
 *		msgref		[IN]:A variables referenced by the message queue
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_msgq_delete(mbtk_msgqref msgref);

extern mbtk_os_status ol_os_msgq_flush(mbtk_msgqref msgref);
// ----------------------------------------------------  MESSAGE --------------------------------------------------------------//
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_mailboxq_creat
 * DESCRIPTION 
 *  	This API is used to creat a mailbox queue.  
 * PARAMETERS 
 *		mailboxqref [IN]:A pointer type variable that points to the mailbox queue reference
 *		queuename	[IN]:The name of mailbox queue.
 *		maxnum	    [IN]:The maximum number of messages that a mailbox queue can hold
 *		mode	    [IN]:The mode of mailbox queue hanle message.
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_mailboxq_creat(mbtk_mailboxqref * mailboxqref, char * queuename, uint32_t maxnum, uint8_t mode);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_mailboxq_send
 * DESCRIPTION 
 *  	This API is used to send a message to specified mailbox queue.
 * PARAMETERS 
 *		mailboxqref [IN]:A variables referenced by the mailbox queue
 *		msgptr	    [IN]:The pointer of the send message
 *		timeout	    [IN]:The timeout for the message sending
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_mailboxq_send(mbtk_mailboxqref mailboxqref, void * msgptr, uint32_t timeout);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_mailboxq_recv
 * DESCRIPTION 
 *  	This API is used to recv a message to specified mailbox queue.
 * PARAMETERS 
 *		mailboxqref [IN]:A variables referenced by the mailbox queue
 *		msgptr	    [IN]:The pointer of the recv message
 *		timeout	    [IN]:The timeout for the message recving
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_mailboxq_recv(mbtk_mailboxqref mailboxqref, void ** msgptr, uint32_t timeout);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_mailboxq_delete
 * DESCRIPTION 
 *  	This API is used to delet mailbox queue passed incoming message mailbox reference.  
 * PARAMETERS 
 *		msgref		[IN]:A variables referenced by the mailbox queue
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_mailboxq_delete(mbtk_mailboxqref mailboxqref);
// ----------------------------------------------------  SEMAPHORE --------------------------------------------------------------//
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_sem_creat
 * DESCRIPTION 
 *  	This API is used to creat a semaphore.  
 * PARAMETERS 
 *		semref		 [IN]:A pointer type variable that points to the semaphore reference
 *		initialcount [IN]:The number of semaphore
 *		waitmode	 [IN]:The mode of task wait semaphore
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_sem_creat(mbtk_semref * semref, uint32_t initialcount, uint8_t waitmode);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_sem_request
 * DESCRIPTION 
 *  	This API is used to request a semaphore.  
 * PARAMETERS 
 *		semref		 [IN]:A variables referenced by the semaphore
 *		timeout  	 [IN]:The timeout to wait for a semaphore
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_sem_request(mbtk_semref semref, uint32_t timeout);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_sem_release
 * DESCRIPTION 
 *  	This API is used to release a semaphore.  
 * PARAMETERS 
 *		semref		 [IN]:A variables referenced by the semaphore
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_sem_release(mbtk_semref semref);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_sem_poll
 * DESCRIPTION 
 *  	This API is used to get semaphore's count.  
 * PARAMETERS 
 *		semref		 [IN]:A variables referenced by the semaphore
 *		semcount	 [IN]:The pointer for number of semaphore
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_sem_poll(mbtk_semref semref, uint32_t * semcount);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_sem_delete
 * DESCRIPTION 
 *  	This API is used to delete semaphore.  
 * PARAMETERS 
 *		semref		 [IN]:A variables referenced by the semaphore
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_sem_delete(mbtk_semref semref);
// ----------------------------------------------------  MUTEX --------------------------------------------------------------//
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_mutex_creat
 * DESCRIPTION 
 *  	This API is used to creat a mutex lock.  
 * PARAMETERS 
 *		semref		 [IN]:A pointer type variable that points to the mutex lock reference
 *		waitmode	 [IN]:The mode of task wait mutex lock
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_mutex_creat(mbtk_mutexref * mutexref, uint8_t waitmode);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_mutex_delete
 * DESCRIPTION 
 *  	This API is used to delete mutex lock.  
 * PARAMETERS 
 *		mutexref     [IN]:A variables referenced by the mutex lock
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_mutex_delete(mbtk_mutexref mutexref);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_mutex_lock
 * DESCRIPTION 
 *  	This API is used to requset a mutex lock.  
 * PARAMETERS 
 *		mutexref	 [IN]:A variables referenced by the mutex lock
 *      timeout	     [IN]:The timeout to wait for a mutex lock
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_mutex_lock(mbtk_mutexref mutexref, uint32_t timeout);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_mutex_unlock
 * DESCRIPTION 
 *  	This API is used to release a mutex lock.  
 * PARAMETERS 
 *		mutexref	 [IN]:A variables referenced by the mutex lock
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_mutex_unlock(mbtk_mutexref mutexref);
// ----------------------------------------------------  FLAG --------------------------------------------------------------//
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_flag_creat
 * DESCRIPTION 
 *  	This API is used to creat flag.  
 * PARAMETERS 
 *		flagref		 [IN]:A pointer type variable that points to the flag reference
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_flag_creat(mbtk_flagref * flagref);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_flag_delete
 * DESCRIPTION 
 *  	This API is used to delet flag.  
 * PARAMETERS 
 *		flagref		 [IN]:A variables referenced by the flag
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_flag_delete(mbtk_flagref flagref);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_flag_set
 * DESCRIPTION 
 *  	This API is used to release flag.  
 * PARAMETERS 
 *		flagref		 [IN]:A variables referenced by the flag
 *		mask	     [IN]:flag mask code
 *		operation	 [IN]:flag or or flag and
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_flag_set(mbtk_flagref flagref, uint32_t mask, uint32_t operation);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_flag_wait
 * DESCRIPTION 
 *  	This API is used to request flag.  
 * PARAMETERS 
 *		flagref		 [IN]:A variables referenced by the flag
 *		mask	     [IN]:flag mask code
 *		operation	 [IN]:flag or or flag and
 *		flag    	 [IN]:recv flag
 *		timeout 	 [IN]:The timeout to wait for flag
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_flag_wait(mbtk_flagref flagref, uint32_t mask, uint32_t operation, uint32_t * flag, uint32_t timeout);
// ---------------------------------------------------- timer  --------------------------------------------------------------//
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_timer_creat
 * DESCRIPTION 
 *  	This API is used to creat a timer.  
 * PARAMETERS 
 *		timerref	 [IN]:A pointer type variable that points to the timer reference
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_timer_creat(mbtk_ostimerref * timerref);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_timer_start
 * DESCRIPTION 
 *  	This API is used to start the timer passed incomming timer reference.  
 * PARAMETERS 
 *		timerref	     [IN]:A variables referenced by the timer
 *		initialtime	     [IN]:Timer initializes the timing time
 *		rescheduletime	 [IN]:Timer subsequent cycle time
 *		callbackfunc	 [IN]:A pointer type variable that points timeout callback function
 *		timer_argc	     [IN]:A pointer type variable that points timeout callback function arguments
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_timer_start(mbtk_ostimerref timerref, uint32_t initialtime, uint32_t rescheduletime, void (* callbackfunc)(uint32_t), uint32_t timer_argc);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_timer_stop
 * DESCRIPTION 
 *  	This API is used to stop the timer passed incomming timer reference.  
 * PARAMETERS 
 *		timerref	     [IN]:A variables referenced by the timer
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_timer_stop(mbtk_ostimerref timerref);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_timer_delete
 * DESCRIPTION 
 *  	This API is used to delete the timer passed incomming timer reference.  
 * PARAMETERS 
 *		timerref	     [IN]:A variables referenced by the timer
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_timer_delete(mbtk_ostimerref timerref);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_get_timer_status
 * DESCRIPTION 
 *  	This API is used to get the timer status passed incomming timer reference.  
 * PARAMETERS 
 *		timerref	     [IN]:A variables referenced by the timer
 *		status  	     [IN]:timer current status
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_get_timer_status(mbtk_ostimerref timerref, mbtk_os_timer_status_struct *status);

// -------------------------------------------------- os system apis ------------------------------------------------------//
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_context_lock
 * DESCRIPTION 
 *  	This API is used to lock context, IRQ and scheduler is not respond.  
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_context_lock(void); // diable isr and scheduler
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_context_unlock
 * DESCRIPTION 
 *  	This API is used to recover context, IRQ and scheduler is respond.  
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_context_unlock(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_context_lock_ex
 * DESCRIPTION 
 *  	This API is used to lock context, only IRQ respond.  
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_context_lock_ex(void); // enable isr disable scheduler
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_context_unlock_ex
 * DESCRIPTION 
 *  	This API is used to recover context, IRQ and scheduler is respond.  
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_context_unlock_ex(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_get_task_info
 * DESCRIPTION 
 *  	This API is used to get task infomation  
 * PARAMETERS 
 *      taskref		[IN]:A pointer type variable that points to the task reference
 *      taskinfo	[IN]:A pointer type variable that points to the task infomation
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_get_task_info(mbtk_taskref taskref, mbtk_task_info_struct * taskinfo);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_get_task_info_ex
 * DESCRIPTION 
 *  	This API is used to get task infomation  
 * PARAMETERS 
 *      taskref		[IN]:A pointer type variable that points to the task reference
 *      taskinfo	[IN]:A pointer type variable that points to the task infomation
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_get_task_info_ex(mbtk_taskref taskref, mbtk_task_info_struct_ex * taskinfo);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_get_created_task_count
 * DESCRIPTION 
 *  	This API is used to get created task count  
 * PARAMETERS 
 *      count   	[IN]:A pointer type variable that points to the task count
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_get_created_task_count(uint32_t *count);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_get_max_task_count
 * DESCRIPTION 
 *  	This API is used to get maximum number of tasks can be created
 * PARAMETERS 
 *      count   	[IN]:A pointer type variable that points to the task count
 * RETURN VALUES
 *		mbtk_os_success : Interface executed successfully
 *		others          : error ,see enum mbtk_os_return_enum
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_get_max_task_count(uint32_t *count);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_get_version
 * DESCRIPTION 
 *  	This API is used to get OS version
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		OS version string
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern char *ol_os_get_version(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_change_task_priority
 * DESCRIPTION 
 *  	This API is used to change the priority of a task
 * PARAMETERS 
 *      taskref	     [IN]:A variables referenced by the timer
 *      new_priority [IN]:new priority for this task
 *      old_priority [IN]:A pointer type variable that points to the old priority
 * RETURN VALUES
 *		OS version string
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_os_status ol_os_change_task_priority(mbtk_taskref taskref, uint8_t new_priority, uint8_t *old_priority);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_task_yield
 * DESCRIPTION 
 *  	This API is used to task relinquishes its right of use
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern void ol_os_task_yield(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_os_get_ticks
 * DESCRIPTION 
 *  	This API is used to get OS running ticks
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		OS ticks count
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern uint32_t ol_os_get_ticks(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_buildtime
 * DESCRIPTION 
 *  	This API is used to get build time
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		OS ticks count
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern char* ol_get_buildtime(void);
extern void ol_os_set_ticks(uint32_t ticks);
extern uint32_t ol_time(uint32_t *time);
extern void ol_set_time(void *time,uint8 type, int8 timezone);
extern struct tm *ol_gmtime(uint32_t *time);
extern struct tm *ol_localtime(const uint32_t *_timer);
extern char* ol_ctime(const unsigned int *_timer);
extern int32_t ol_get_timezone(void);
extern void ol_set_timezone(int8 timezone);

#define gmtime      ol_gmtime
#define localtime   ol_localtime
#define ctime       ol_ctime


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_dump_num
 * DESCRIPTION 
 *  	This API is used to get dump num
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		dump num
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern int16_t ol_get_dump_num(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_dump_info
 * DESCRIPTION 
 *  	This API is used to get dump info, content is  mbtk_dump_info
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		mbtk_dump_info
 * RETURN MESSAGE
 * 		NONE
 *
  ps:
      目前dumpinfo是使用的SP指针的2K的长度进行保存
      在ASR的解析工具中，使用的是这个2k长度进行4字节搜索，如果在map中搜索到相关的地址，那么则对应具体的function
 *****************************************************************************/
extern mbtk_dump_info* ol_get_dump_info(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_remove_dump
 * DESCRIPTION 
 *  	This API is used to remove dump file
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		OS ticks count
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern int ol_remove_dump(void);

extern uint8 ol_set_dump_flag(uint8 flag);
extern uint8 ol_get_dump_flag(void);
extern int  ol_gettimeofday(ol_timeval *tv, void* dummy);
extern int ol_random(void* output, unsigned int len);

#ifdef __cplusplus
}
#endif

#endif // #ifdef __MBTK_OS_H
