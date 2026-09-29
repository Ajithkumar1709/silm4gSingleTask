
#ifndef __MBTK_OS_H
#define __MBTK_OS_H


#include "mbtk_pub_type.h"



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

#define MBTK_DUMP_HEAP_SIZE 2048

typedef struct
{
	char dump_heap[MBTK_DUMP_HEAP_SIZE];
	UINT16 dump_heap_size;
}mbtk_dump_info;



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





// ----------------------------------------------------  TASK --------------------------------------------------------------//


mbtk_os_status mbtk_os_task_creat(mbtk_taskref * taskref, void * stackptr, uint32_t stacksize,
										uint8_t priority, char * taskname, void (* taskfunc)(void *), void * argv); // creat a task can't run lisr and timercallback


mbtk_os_status mbtk_os_task_creat_ex(mbtk_taskref * taskref, void * stackptr, uint32_t stacksize,
										uint8_t priority, char * taskname, void ( *taskfunc)(void *), void * argv); // creat a task ex, can't run lisr and timercallback


mbtk_os_status mbtk_os_task_delete(mbtk_taskref taskref);// delet a task , can't run lisr and timer callback

mbtk_os_status mbtk_os_task_suspend(mbtk_taskref taskref);

mbtk_os_status mbtk_os_task_resume(mbtk_taskref taskref);

void mbtk_os_task_sleep(uint32_t ticks); // 1 tick = 5ms

mbtk_os_status mbtk_os_task_get_current_ref(mbtk_taskref * taskref);

mbtk_os_status mbtk_os_task_terminate(mbtk_taskref taskref); // stop a task

#if 0

mbtk_os_status mbtk_os_task_change_priority(mbtk_osref osref, uint8_t new_priority, uint8_t *old_priority);

mbtk_os_status mbtk_os_task_get_priority(mbtk_osref osref, uint8_t * priority);

#endif



// ----------------------------------------------------  HISR --------------------------------------------------------------//

void mbtk_os_creat_hisr(mbtk_hisrref * hisrref, char * hisrname, void (* hisr_entry)(void), uint8_t hisr_priority);

void mbtk_os_active_hisr(mbtk_hisrref * hisrref);

void mbtk_os_delete_hisr(mbtk_hisrref *hisrref);

#if 0
mbtk_os_status mbtk_os_hisr_get_priority(mbtk_osref osref, uint8_t * priority);

mbtk_os_status mbtk_os_hisr_get_current_ref(mbtk_osref * osref);
#endif

// ----------------------------------------------------  MESSAGE --------------------------------------------------------------//

mbtk_os_status mbtk_os_msgq_creat(mbtk_msgqref * msgref, char * queuename, uint32_t maxsize, uint32_t maxnum, uint8_t mode);

mbtk_os_status mbtk_os_msgq_send(mbtk_msgqref msgref, uint8_t size, char * msgptr, uint32_t timeout);

mbtk_os_status mbtk_os_msgq_recv(mbtk_msgqref msgref, char * msgptr, uint8_t size, uint32_t timeout);

mbtk_os_status mbtk_os_msgq_poll(mbtk_msgqref      msgref, uint32_t * msgcount);

mbtk_os_status mbtk_os_msgq_delete(mbtk_msgqref msgref);

mbtk_os_status mbtk_os_msgq_flush(mbtk_msgqref msgref);
// ----------------------------------------------------  MESSAGE --------------------------------------------------------------//


mbtk_os_status mbtk_os_mailboxq_creat(mbtk_mailboxqref * mailboxqref, char * queuename, uint32_t maxnum, uint8_t mode);

mbtk_os_status mbtk_os_mailboxq_send(mbtk_mailboxqref mailboxqref, void * msgptr, uint32_t timeout);

mbtk_os_status mbtk_os_mailboxq_recv(mbtk_mailboxqref mailboxqref, void ** msgptr, uint32_t timeout);

mbtk_os_status mbtk_os_mailboxq_delete(mbtk_mailboxqref mailboxqref);


// ----------------------------------------------------  SEMAPHORE --------------------------------------------------------------//


mbtk_os_status mbtk_os_sem_creat(mbtk_semref * semref, uint32_t initialcount, uint8_t waitmode);

mbtk_os_status mbtk_os_sem_request(mbtk_semref semref, uint32_t timeout);

mbtk_os_status mbtk_os_sem_release(mbtk_semref semref);

mbtk_os_status mbtk_os_sem_poll(mbtk_semref semref, uint32_t * semcount);

mbtk_os_status mbtk_os_sem_delete(mbtk_semref semref);

// ----------------------------------------------------  MUTEX --------------------------------------------------------------//


mbtk_os_status mbtk_os_mutex_creat(mbtk_mutexref * mutexref, uint8_t waitmode);

mbtk_os_status mbtk_os_mutex_delete(mbtk_mutexref mutexref);

mbtk_os_status mbtk_os_mutex_lock(mbtk_mutexref mutexref, uint32_t timeout);

mbtk_os_status mbtk_os_mutex_unlock(mbtk_mutexref mutexref);


// ----------------------------------------------------  FLAG --------------------------------------------------------------//


mbtk_os_status mbtk_os_flag_creat(mbtk_flagref * flagref);

mbtk_os_status mbtk_os_flag_delete(mbtk_flagref flagref);

mbtk_os_status mbtk_os_flag_set(mbtk_flagref flagref, uint32_t mask, uint32_t operation);

mbtk_os_status mbtk_os_flag_wait(mbtk_flagref flagref, uint32_t mask, uint32_t operation, uint32_t * flag, uint32_t timeout);




// ---------------------------------------------------- OS MEM  --------------------------------------------------------------//

#if 0
mbtk_os_status mbtk_os_mempool_creat(mbtk_osmemref * memref, uint8_t poolbase, uint32_t poolsize);
// not provided now

#endif



// ---------------------------------------------------- timer  --------------------------------------------------------------//

mbtk_os_status mbtk_os_timer_creat(mbtk_ostimerref * timerref);

mbtk_os_status mbtk_os_timer_start(mbtk_ostimerref timerref, uint32_t initialtime, uint32_t rescheduletime, void (* callbackfunc)(uint32_t), uint32_t timer_argc);

mbtk_os_status mbtk_os_timer_stop(mbtk_ostimerref timerref);

mbtk_os_status mbtk_os_timer_delete(mbtk_ostimerref timerref);

mbtk_os_status mbtk_os_get_timer_status(mbtk_ostimerref timerref, mbtk_os_timer_status_struct *status);



// ---------------------------------------------------- common debug interface ---------------------------------------------------//

#if 0
mbtk_os_status mbtk_os_list_all_task(void); // list all task/hisr by diag;

mbtk_os_status mbtk_os_list_all_timer(void); // list all timer by diag;

// not provided now

#endif



// -------------------------------------------------- os system apis ------------------------------------------------------//


mbtk_os_status mbtk_os_context_lock(void); // diable isr and scheduler

mbtk_os_status mbtk_os_context_unlock(void);

mbtk_os_status mbtk_os_context_lock_ex(void); // enable isr disable scheduler

mbtk_os_status mbtk_os_context_unlock_ex(void);



mbtk_os_status mbtk_os_get_current_taskref(mbtk_taskref * taskref);

mbtk_os_status mbtk_os_get_task_info(mbtk_taskref         taskref, mbtk_task_info_struct * taskinfo);

mbtk_os_status mbtk_os_get_created_task_count(uint32_t *count);

mbtk_os_status mbtk_os_get_max_task_count(uint32_t *count);

char * mbtk_os_get_version(void);

mbtk_os_status mbtk_os_change_task_priority(mbtk_taskref taskref, uint8_t new_priority, uint8_t *old_priority);

void mbtk_os_task_yield(void);

uint32_t mbtk_os_get_ticks(void);
void mbtk_os_set_ticks(uint32_t ticks);
void mbtk_settime(void *time,uint8 type, int8 timezone);

int mbtk_random(void* output, unsigned int len);


uint8_t mbtk_set_dump_flag(uint8_t flag);
uint8_t mbtk_get_dump_flag(void);























#endif // #ifdef __MBTK_OS_H
