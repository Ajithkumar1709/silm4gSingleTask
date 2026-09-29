/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : osa_tx_utils.c
Description :
Notes       :

Copyright (c) 2008 Marvell MISL. All Rights Reserved
=========================================================================== */

/*
 * Include File.
 */
#include <string.h>
#include "nucleus.h"
#include "gbl_types.h"
#include "k_api.h"
#include "alios_hisr.h"
#include "osa.h"
#include "osa_ali.h"
#include "osa_internals.h"
#include "osa_utils.h"
#include "UART.h"

#define FPU_AVL 0
#define NEON_AVL 0

typedef struct {
#if (FPU_AVL)
    long FPEXC;
    long FPSCR;
#if (NEON_AVL)
    /* The Cortex-A5 FPU is a SIMD v2 + VFPv4-D32 implementation of the ARMv7 floating-point architecture */
    long FPU[64];
#else
    /* The Cortex-A5 FPU is a VFPv4-D16 implementation of the ARMv7 floating-point architecture */
    long FPU[32];
#endif
#endif
    long m_CPSR;
    long m_R0;
    long m_R1;
    long m_R2;
    long m_R3;
    long m_R4;
    long m_R5;
    long m_R6;
    long m_R7;
    long m_R8;
    long m_R9;
    long m_R10;
    long m_R11;
    long m_R12;
    long m_LR;
    long m_PC;
}context_t;


/***********************************************************************
 *
 * Name:        OsaTaskGetCurrentRef
 *
 * Description: Get Task Ref.
 *
 * Parameters:
 *  OsaRefT                 *pOsaRef    [OT]    Task Reference.
 *
 * Returns:
 *      OS_SUCCESS
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaTaskGetCurrentRef( OsaRefT *pOsaRef, void *pForFutureUse )
{
	ktask_t *pRef;
	OSA_ASSERT(pOsaRef) ;

	pRef = krhino_cur_task_get();
	if(pRef){
		if(pRef->b_prio > 2)		//priority 0-2 is used for HISR
			*pOsaRef = (OsaRefT )pRef;
		else
			*pOsaRef = NULL;
	}else
		*pOsaRef = (OsaRefT )pRef;


    return OS_SUCCESS ;
}

OSA_STATUS OsaTaskGetStatus(OsaRefT *pOsaRef)
{
    ktask_t *pRef = (ktask_t *)pOsaRef;
    if( pRef ) {
        switch(pRef->task_state) {
            case K_RDY:
            case K_PEND:
                return OSA_TASK_READY;
            case K_SLEEP:
				return OSA_TASK_SLEEP;
            case K_SUSPENDED:
            case K_SLEEP_SUSPENDED:
            case K_PEND_SUSPENDED:
                return OSA_TASK_SUSPENDED;
            case K_DELETED:
                return OSA_TASK_TERMINATED;
            case K_SEED:
            default:
                return OSA_TASK_STATE_UNKNOWN;
        }
    } else {
        return OSA_TASK_STATE_UNKNOWN;
    }
}


OsaRefT OsaTaskGetCurrent( )
{
	return (OsaRefT)krhino_cur_task_get();
}

BOOL  OsaTaskSetCurrent(OsaRefT OsaRef )
{
	return TRUE;
}

OSA_STATUS OsaHISRGetCurrentRef( OsaRefT *pOsaRef, void *pForFutureUse )
{
	ktask_t *pTxRef;
	OSA_ASSERT(pOsaRef) ;

	pTxRef = krhino_cur_task_get();
	if(pTxRef){
		if(pTxRef->b_prio <= 2)		//priority 0-2 is used for HISR
			*pOsaRef = (OsaRefT )pTxRef;
		else
			*pOsaRef = NULL;
	}else
		*pOsaRef = (OsaRefT )pTxRef;

    return OS_SUCCESS ;
}

/***********************************************************************
 *
 * Name:        OsaSemaphorePoll
 *
 * Description: Poll semaphore.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *  UINT32                  *pCount         [OT]    Current semaphore count.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaSemaphorePoll( OsaRefT OsaRef, UINT32 *pCount, void *pForFutureUse )
{
    ksem_t
        *pSemRef = (ksem_t *)OsaRef ;

    OSA_ASSERT(pCount) ;
    OSA_ASSERT(pSemRef) ;

	krhino_sem_count_get(pSemRef, (sem_count_t*)pCount);

    return OS_SUCCESS ;
}

/***********************************************************************
 *
 * Name:        OsaMsgQPoll
 *
 * Description: Get the number of messages in queue.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *  UINY32                  *pCount         [OT]    Number of messages in queue.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaMsgQPoll( OsaRefT OsaRef, UINT32 *pCount, void *pForFutureUse )
{
	OsaMsgQT
		*pMsgQRef = (OsaMsgQT *)OsaRef;

	kbuf_queue_info_t  info;

    OSA_ASSERT(pMsgQRef) ;
    OSA_ASSERT(pCount) ;

	if( krhino_buf_queue_info_get(&pMsgQRef->queue, &info) == RHINO_SUCCESS )
	{
    	*pCount = (UINT32)info.cur_num;
		return OS_SUCCESS ;
	}
	else
	{
		OSA_ASSERT(0);
	}

    return OS_FAIL;
}

/***********************************************************************
 *
 * Name:        OsaMailboxQPoll
 *
 * Description: Gen the number of messages in queue.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *  UINY32                  *pCount         [OT]    Number of messages in queue.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaMailboxQPoll( OsaRefT OsaRef, UINT32 *pCount, void *pForFutureUse )
{
	OsaMbQT
		*pMsgQRef = (OsaMbQT *)OsaRef;

	msg_info_t  info;

    OSA_ASSERT(pMsgQRef) ;
    OSA_ASSERT(pCount) ;

	if( krhino_queue_info_get(&pMsgQRef->queue, &info) == RHINO_SUCCESS )
	{
		*pCount = (UINT32)info.msg_q.cur_num;
		return OS_SUCCESS ;
	}
	else
	{
		OSA_ASSERT(0);
	}

    return OS_FAIL ;
}

/***********************************************************************
 *
 * Name:        OsaTimerStatus
 *
 * Description: Get timer status.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaTimerStatus( OsaRefT OsaRef, OsaTimerStatusParamsT *pParams )
{

	CPSR_ALLOC();

    OsaTimerT
        *pTxTimer = (OsaTimerT *)OsaRef ;

    if ( ! OsaRef )
        return OS_INVALID_REF ;

    OSA_ASSERT(pParams) ;

	/* Disable interrupts.	*/
	RHINO_CRITICAL_ENTER();

	if( pTxTimer->timer && pTxTimer->timer->timer_state == TIMER_ACTIVE )
        pParams->status = OS_ENABLED ;
    else
        pParams->status = OS_DISABLED ;

	RHINO_CRITICAL_EXIT();

    return OS_SUCCESS ;
}


/***********************************************************************
 *
 * Name:        OsaTaskList()
 *
 * Description:  This function builds a list of task pointers, starting at the
 *      		specified location.  The number of task pointers placed in the
 *     		list is equivalent to the total number of tasks or the maximum
 *    			 number of pointers specified in the call.
 *
 * Parameters:
 *  		ptrList                        Pointer to the list area
 *      	maximum_pointers                    Maximum number of pointers
 *
 * Returns:
 *  		Number of tasks placed in list
 *
 * Notes: it is priority should be more than 2(0-2 is used for HISR)
 *
 ***********************************************************************/
UINT32 OSATaskList(OSATaskRef *ptrList, UINT32 maximum_pointers){

	/* AliOS does not support task list */

    /* Return the number of pointers in the list.  */
    return(0);
}

/***********************************************************************
 *
 * Name:        OsaHISRList()
 *
 * Description:  This function builds a list of HISR pointers, starting at the
 *      		specified location.  The number of HISR pointers placed in the
 *     		list is equivalent to the total number of HISRs or the maximum
 *    			 number of pointers specified in the call.
 *
 * Parameters:
 *  		ptrList                        Pointer to the list area
 *      	maximum_pointers                    Maximum number of pointers
 *
 * Returns:
 *  		Number of HISRs placed in list
 *
 * Notes: HISR priority is 0-2, other priority is used for normal thread
 *
 ***********************************************************************/
UINT32 OSAHISRList(OSAHISRRef *ptrList, UINT32 maximum_pointers){

	/* AliOS does not support task list */

    return(0);
}


UINT32 OSATaskIsValid(OsaRefT OsaRef){
	OsaTaskT
		*pTask = (OsaTaskT*)OsaRef;

	if(OsaRef)
		return ( pTask->abs_task.aos_thread_id == ALI_THREAD_ID && pTask->abs_task.hisr_task.b_prio >= 3 );
	else
		return 0;
}


UINT32 OSAHISRIsValid(OsaRefT OsaRef){
	ktask_t
		*pTask = (ktask_t*)OsaRef;

	if(OsaRef)
		return ( pTask->task_state != K_DELETED && pTask->b_prio < 3 );
	else
		return 0;
}



UINT32 OSATaskIsDead(OsaRefT OsaRef){
	ktask_t
		*pTask = (ktask_t*)OsaRef;

	OSA_ASSERT(OsaRef);

	return pTask->task_state == K_DELETED;
}



VOID* OSATaskGetStackStart(OsaRefT OsaRef){
	ktask_t
		*pTxTask = (ktask_t*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxTask->task_stack_base);
}

UINT32	OSATaskGetStackSize(OsaRefT OsaRef){
	ktask_t
		*pTxTask = (ktask_t*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxTask->stack_size);
}

VOID* OSATaskGetStackEnd(OsaRefT OsaRef){
	ktask_t
		*pTxTask = (ktask_t*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (VOID *)((UINT32)(pTxTask->task_stack) + pTxTask->stack_size - 1);
}

UINT32 OSATaskCheckStack(UINT32 * stack)
{
	OSA_ASSERT(stack);
	return (stack[0] == (UINT32)0xdeadbeaf);
}




void (*OSATaskGetEntry(OSATaskRef OsaRef))(void *){

	OsaTaskT *pTask = (OsaTaskT *)OsaRef;

	return (void(*)(void *))(pTask->entry);
}

void OSATaskSetEntry(OSATaskRef OsaRef, void (*entry)(void *)){
	/* AliOS's task does not support this operation */
	OSA_ASSERT(0);
}


UINT32	OSATaskGetEntryParam(OSATaskRef OsaRef){

	OsaTaskT *pTask = (OsaTaskT *)OsaRef;

	return pTask->entryParam;
}

char*	OSATaskGetName(OSATaskRef OsaRef){
	ktask_t
		*pTxTask = (ktask_t*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (char *)(pTxTask->task_name);
}



UINT32	OSATaskGetSysParam1(OSATaskRef OsaRef){
	OsaTaskT *pTask = (OsaTaskT *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTask->abs_task.osa_system_reserved_1);
}

void OSATaskSetSysParam1(OSATaskRef OsaRef, UINT32 value){
	OsaTaskT *pTask = (OsaTaskT *)OsaRef;

	OSA_ASSERT(OsaRef);

	pTask->abs_task.osa_system_reserved_1 = value;
}

UINT32	OSATaskGetSysParam2(OSATaskRef OsaRef){
	OsaTaskT *pTask = (OsaTaskT *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTask->abs_task.osa_system_reserved_2);
}

void OSATaskSetSysParam2(OSATaskRef OsaRef, UINT32 value){
	OsaTaskT *pTask = (OsaTaskT *)OsaRef;

	OSA_ASSERT(OsaRef);

	pTask->abs_task.osa_system_reserved_2 = value;
}

UINT32	OSATaskGetSysParam3(OSATaskRef OsaRef){
	OsaTaskT *pTask = (OsaTaskT *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTask->abs_task.osa_system_reserved_3);
}

void OSATaskSetSysParam3(OSATaskRef OsaRef, UINT32 value){
	OsaTaskT *pTask = (OsaTaskT *)OsaRef;

	OSA_ASSERT(OsaRef);

	pTask->abs_task.osa_system_reserved_3 = value;
}

UINT32	OSATaskGetAppParam1(OSATaskRef OsaRef){
	OsaTaskT *pTask = (OsaTaskT *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTask->abs_task.osa_app_reserved_1);
}

void*	OSAHISRGetStackStart(OSAHISRRef OsaRef){

	ktask_t
		*pTxTask = (ktask_t*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxTask->task_stack_base);
}

UINT32 OSAHISRGetStackSize(OSAHISRRef OsaRef){

	ktask_t
		*pTxTask = (ktask_t*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxTask->stack_size);
}

void (*OSAHISRGetEntry(OsaRefT OsaRef))(void){

	RHINO_HISR * hisr = (RHINO_HISR *)OsaRef;

	return (void (*)(void))(hisr->hisr_entry);
}

char*  OSAHISRGetName(OSAHISRRef OsaRef){
	ktask_t
		*pTxHisr = (ktask_t*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (char *)(pTxHisr->task_name);
}

UINT32	OSAHISRGetAppParam1(OSAHISRRef OsaRef){
	RHINO_HISR *hisr = (RHINO_HISR *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (hisr->abs_task.osa_app_reserved_1);
}

void 	OSAHISRSetAppParam1(OSAHISRRef OsaRef, UINT32 value){
	RHINO_HISR *hisr = (RHINO_HISR *)OsaRef;
	OSA_ASSERT(OsaRef);

	hisr->abs_task.osa_app_reserved_1 = value;
}

UINT32	OSAPartitionPoolGetAllocated(OSAPartitionPoolRef OsaRef){
	mblk_pool_t
		*pTxPool = (mblk_pool_t *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxPool->blk_whole - pTxPool->blk_avail);
}

char*	OSAPartitionPoolGetName(OSAPartitionPoolRef OsaRef){
	mblk_pool_t
		*pTxPool = (mblk_pool_t *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (char *)(pTxPool->pool_name);
}

UINT32	OSAPartitionPoolGetAvailble(OSAPartitionPoolRef OsaRef){
	mblk_pool_t
		*pTxPool = (mblk_pool_t *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxPool->blk_avail);

}

UINT32	OSAPartitionPoolGetPartitionSize(OSAPartitionPoolRef OsaRef){
	mblk_pool_t
		*pTxPool = (mblk_pool_t *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxPool->blk_size);
}

OSA_STATUS	OSAMsgQFrontSend(OsaRefT OsaRef, void *message,
                                        UINT32 size, UINT32 suspend){

	/* AliOS does not support such operation */
	OSA_ASSERT(OsaRef);

	return OS_SUCCESS ;
}

BOOL OSAPartitionInUse(  void* BlockPtr, void* PoolPtr )
{
     /****************
   	In threadX, if the block has been allocated,  before its data area a 4 bytes area stores the ptr of associated poll,
   	otherwise it store the ptr point to next available block
   	*************/
     CHAR  *blockPtr = (CHAR *)BlockPtr ;
	 CHAR  *workPtr;
     BOOL  retVal = TRUE;

	 workPtr = blockPtr - sizeof(CHAR *);

     if ( *(char **)workPtr == PoolPtr)
     {
        /* block is in use */
        retVal = TRUE;
     }
     else
     	retVal = FALSE;

     return retVal;
}

OsaRefT OSAPartitionGetPoolPtr( void* BlockPtr ){

	mblk_pool_t
		*pTxPool;

	CHAR
		*workPtr;

	OSA_ASSERT(BlockPtr);

	workPtr =  ((CHAR *) BlockPtr) - sizeof(CHAR *);
    pTxPool =  *((mblk_pool_t **) workPtr);

	return pTxPool;

}

UINT32 OsaGetInterruptCount(void){
	return g_intrpt_nested_level[cpu_cur_get()];
}



/***********************************************************************
 *
 * Name:        Osa_TimeoutValueEx()
 *
 * Description: Translate timeout value from OSA to Nucleus format.
 *
 * Parameters:
 *  STATUS  ErrorCode   -   OS Error Code.
 *
 * Returns:
 *  OSA_STATUS          -   OSA equivalence status.
 *
 * Notes:
 *
 ***********************************************************************/
UINT64 Osa_TimeoutValueEx( UINT32 timeout )
{

    if ( timeout == OS_SUSPEND )
        return (UINT64)RHINO_WAIT_FOREVER;

    if ( timeout == OS_NO_SUSPEND )
        return RHINO_NO_WAIT;

    return (UINT64)timeout ;
}



OSA_STATUS OsaListAllCreatedTasks( void )
{
    // ALIOS_TODO: implement it later ...

	return OS_SUCCESS;
}


OSA_STATUS OsaListAllCreatedTimers( void )
{
    // ALIOS_TODO: implement it later ...

	return OS_SUCCESS;
}


OSA_STATUS OsaListAllCreatedEventFlags( void )
{
    // ALIOS_TODO: implement it later ...

	return OS_SUCCESS;
}


OSA_STATUS OsaListAllCreatedMemBlockPools( void )
{
    // ALIOS_TODO: implement it later ...

	return OS_SUCCESS;
}

OSA_STATUS OsaListAllCreatedMsgQs( void )
{
    // ALIOS_TODO: implement it later ...

	return OS_SUCCESS;
}

OSA_STATUS OsaListAllCreatedSemaphores( void )
{
    // ALIOS_TODO: implement it later ...

	return OS_SUCCESS;
}


OSA_STATUS OsaListAllCreatedMutexs( void )
{
    // ALIOS_TODO: implement it later ...

	return OS_SUCCESS;
}

static OSA_TASK_STATE Osa_TranslateTaskState(OsaRefT OsaRef)
{
	ktask_t *pTxTask = (ktask_t *)OsaRef;

	switch(pTxTask->task_state)
	{
	case K_RDY:
		return OSA_TASK_READY;
	case K_DELETED:
		return OSA_TASK_TERMINATED;
	case K_SUSPENDED:
	case K_PEND_SUSPENDED:
	case K_SLEEP_SUSPENDED:
		return OSA_TASK_SUSPENDED;
	case K_SLEEP:
		return OSA_TASK_SLEEP;
	case K_PEND:
		if(pTxTask->blk_obj)
		{
			switch(pTxTask->blk_obj->obj_type)
			{
			case RHINO_SEM_OBJ_TYPE:
				return OSA_TASK_SEMAPHORE_SUSP;
			case RHINO_MUTEX_OBJ_TYPE:
				return OSA_TASK_MUTEX_SUSP;
			case RHINO_QUEUE_OBJ_TYPE:
			case RHINO_BUF_QUEUE_OBJ_TYPE:
				return OSA_TASK_QUEUE_SUSP;
			case RHINO_EVENT_OBJ_TYPE:
			case RHINO_TIMER_OBJ_TYPE:
				return OSA_TASK_EVENT_FLAG;
			case RHINO_MM_OBJ_TYPE:
				return OSA_TASK_BLOCK_MEMORY;
			default:
				return OSA_TASK_STATE_UNKNOWN;
			}

		}
	default:
		return OSA_TASK_STATE_UNKNOWN;
	}

}


OSA_STATUS OsaGetTaskInfo(OsaRefT OsaRef, OSA_TASK *task_info)
{
	ktask_t *pTxTask = (ktask_t *)OsaRef;

	OSA_ASSERT(OsaRef);
	OSA_ASSERT(task_info);
	task_info->task_name          = (char *)pTxTask->task_name;
	task_info->task_priority      = pTxTask->b_prio;
	task_info->task_stack_start   = (unsigned long)pTxTask->task_stack_base;
	task_info->task_stack_end     = (unsigned long)pTxTask->task_stack_base + pTxTask->stack_size - 1;
	task_info->task_stack_size    = pTxTask->stack_size;
	task_info->task_stack_ptr     = (unsigned long)pTxTask->task_stack;
	task_info->task_stack_def_val = RHINO_TASK_STACK_OVF_MAGIC;
	task_info->task_state         = Osa_TranslateTaskState(OsaRef);
	task_info->task_run_count     = pTxTask->task_ctx_switch_times;
	return OS_SUCCESS;
}

OSA_STATUS OsaGetCurrentThreadRef(OsaRefT *pOsaRef, void *pForFutureUse )
{
	OSA_ASSERT(pOsaRef);

	*pOsaRef = (OsaRefT)(g_active_task[0]);
	return OS_SUCCESS ;
}

OsaRefT OsaCurrentThreadRef(void)
{
	extern ktask_t* g_active_task[];
	return (OsaRefT)(g_active_task[0]);
}

OSA_STATUS OsaGetThreadListHead(OsaRefT *pListHead, void *pForFutureUse )
{
	OSA_ASSERT(pListHead);
	*pListHead = (OsaRefT )(&(g_kobj_list.task_head));
	return OS_SUCCESS ;
}

extern uint32_t create_task_count;
OSA_STATUS OsaGetCreatedThreadCount(unsigned long *count, void *pForFutureUse )
{
	OSA_ASSERT(count);
	*count = create_task_count;
	return OS_SUCCESS ;
}

unsigned long OsaThreadList(OsaRefT *ptrList, unsigned long maximum_pointers,void *pForFutureUse)
{
	unsigned long thread_num = 0;
	return thread_num;
}

UINT32 OsaGetThreadEntry(OsaRefT osaRef)
{
	context_t *ctx;
	ktask_t *task = (ktask_t *)osaRef;
	UINT32 entry_addr = NULL;

	if(task == NULL)
	{
		return NULL;
	}
	if(task->prio <= 2)
	{
		RHINO_HISR *hisr_ptr = (RHINO_HISR *)osaRef;
		entry_addr = (UINT32)hisr_ptr->hisr_entry;
	}
	else
	{
    	/* stack aligned by 8 byte */
    	ctx = (context_t *)((long)(task->task_stack_base + task->stack_size)&0xfffffff8);
    	ctx--;
		entry_addr = (UINT32)ctx->m_PC;
	}
	return entry_addr;
}

void OsaSetDbgDisOpt(UINT32 val)
{
	CPSR_ALLOC();
	/* Disable interrupts.	*/
	RHINO_CRITICAL_ENTER();
	krhino_set_dbg_dis_opt(val);
	RHINO_CRITICAL_EXIT();

}


UINT32 OsaGetDbgDisOpt(void)
{
	return krhino_get_dbg_dis_opt();
}

