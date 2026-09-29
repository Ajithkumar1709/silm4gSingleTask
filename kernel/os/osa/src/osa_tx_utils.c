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
#include "osa.h"
#include "osa_tx.h"
#include "osa_internals.h"
#include "osa_utils.h"
#include "diag.h"
#include "UART.h"
#include "tx_semaphore.h"
#include "tx_mutex.h"
#include "tx_queue.h"
#include "tx_event_flags.h"
#include "tx_block_pool.h"

char *pNoneName = "None";

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
	TX_THREAD *pTxRef;
	OSA_ASSERT(pOsaRef) ;

	pTxRef = tx_thread_identify();
	if(pTxRef){
		if(pTxRef->tx_thread_priority > 2)		//priority 0-2 is used for HISR
			*pOsaRef = (OsaRefT )pTxRef;
		else
			*pOsaRef = TX_NULL;
	}else
		*pOsaRef = (OsaRefT )pTxRef;


    return OS_SUCCESS ;
}

OSA_STATUS OsaHISRGetCurrentRef( OsaRefT *pOsaRef, void *pForFutureUse )
{
	TX_THREAD *pTxRef;
	OSA_ASSERT(pOsaRef) ;

	pTxRef = tx_thread_identify();
	if(pTxRef){
		if(pTxRef->tx_thread_priority <= 2)		//priority 0-2 is used for HISR
			*pOsaRef = (OsaRefT )pTxRef;
		else
			*pOsaRef = TX_NULL;
	}else
		*pOsaRef = (OsaRefT )pTxRef;

    return OS_SUCCESS ;
}


OSA_STATUS OsaGetCurrentThreadRef(OsaRefT *pOsaRef, void *pForFutureUse )
{
	TX_THREAD *pTxRef;
	OSA_ASSERT(pOsaRef);
	pTxRef = tx_thread_identify();

	*pOsaRef = (OsaRefT )pTxRef;
	return OS_SUCCESS ;
}

OSA_STATUS OsaGetThreadListHead(OsaRefT *pListHead, void *pForFutureUse )
{
	OSA_ASSERT(pListHead);
	*pListHead = (OsaRefT )_tx_thread_created_ptr;
	return OS_SUCCESS ;
}

OSA_STATUS OsaGetCreatedThreadCount(unsigned long *count, void *pForFutureUse )
{
	OSA_ASSERT(count);
	*count =_tx_thread_created_count;
	return OS_SUCCESS ;
}

OsaRefT OsaCurrentThreadRef(void)
{
	extern TX_THREAD * _tx_thread_current_ptr;
	return (OsaRefT)_tx_thread_current_ptr;
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
    OsaSemaphoreT
        *pSemRef = (OsaSemaphoreT *)OsaRef ;

    OSA_ASSERT(pCount) ;
    OSA_ASSERT(pSemRef) ;

    *pCount = (UINT32)pSemRef->TxRef.tx_semaphore_count ;

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

    TX_QUEUE
        *pTxQ = (TX_QUEUE *)&pMsgQRef->TxRef;

    OSA_ASSERT(pTxQ) ;
    OSA_ASSERT(pCount) ;

    *pCount = (UINT32)pTxQ->tx_queue_enqueued ;

    return OS_SUCCESS ;
}

/***********************************************************************
 *
 * Name:        OsaMsgQFreeRate
 *
 * Description: Get the number of messages in queue.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *  UINY32                  *pFreeRate      [OT]    The free rate of queue.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaMsgQFreeRate( OsaRefT OsaRef, UINT32 *pFreeRate )
{
	OsaMsgQT
		*pMsgQRef = (OsaMsgQT *)OsaRef;

    TX_QUEUE
        *pTxQ = (TX_QUEUE *)&pMsgQRef->TxRef;

    OSA_ASSERT(pTxQ) ;
    OSA_ASSERT(pFreeRate) ;

    *pFreeRate = (UINT32)((pTxQ->tx_queue_available_storage * 100) / pTxQ->tx_queue_capacity);

    return OS_SUCCESS ;
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
	OsaMsgQT
		*pMsgQRef = (OsaMsgQT *)OsaRef;

	TX_QUEUE
        *pTxQ = (TX_QUEUE *)&pMsgQRef->TxRef;

    OSA_ASSERT(pTxQ) ;
    OSA_ASSERT(pCount) ;

    *pCount = (UINT32)pTxQ->tx_queue_enqueued ;

    return OS_SUCCESS ;
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

TX_INTERRUPT_SAVE_AREA

    TX_TIMER
        *pTxTimer = (TX_TIMER *)OsaRef ;

    if ( ! OsaRef )
        return OS_INVALID_REF ;

    OSA_ASSERT(pParams) ;

	/* Disable interrupts.	*/
	TX_DISABLE

    if ( pTxTimer->tx_timer_id == OSA_UNINITIALIZED_TIMER )
        pParams->status = OS_DISABLED ;

    else if ( pTxTimer->tx_timer_id != TX_TIMER_ID )
        return OS_INVALID_REF ;

    if ((pTxTimer->tx_timer_internal.tx_timer_internal_list_head >= _tx_timer_list_start) &&
        (pTxTimer->tx_timer_internal.tx_timer_internal_list_head < _tx_timer_list_end))
        pParams->status = OS_ENABLED ;
    else
        pParams->status = OS_DISABLED ;

	TX_RESTORE

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
	TX_THREAD **   	 pointer_list = (TX_THREAD **)ptrList;
	TX_THREAD        *node_ptr;                  /* Pointer to each TCB       */
	UNSIGNED         pointers;                  /* Number of pointers in list*/

    /* Switch to supervisor mode */


    /* Initialize the number of pointers returned.  */
    pointers =  0;

    /* Protect the task created list.  */

TX_INTERRUPT_SAVE_AREA

	TX_DISABLE

    /* Loop until all task pointers are in the list or until the maximum
       list size is reached.  */

	node_ptr = _tx_thread_created_ptr;
    while ((node_ptr) && (pointers < maximum_pointers) && (node_ptr->tx_thread_priority > 2))//NOTE: priority 0-2 is used for HISR
    {

        /* Place the node into the destination list.  */
        *pointer_list++ =  (TX_THREAD *) node_ptr;

        /* Increment the pointers variable.  */
        pointers++;

        /* Position the node pointer to the next node.  */
        node_ptr =  node_ptr->tx_thread_created_next;

        /* Determine if the pointer is at the head of the list.  */
        if (node_ptr == _tx_thread_created_ptr)		//it is a circular linked list

            /* The list search is complete.  */
            node_ptr =  TX_NULL;
    }

    /* Release protection.  */


    /* Return to user mode */


	TX_RESTORE

    /* Return the number of pointers in the list.  */
    return(pointers);
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
	TX_HISR **   	 pointer_list = (TX_HISR **)ptrList;
	TX_THREAD        *node_ptr;                  /* Pointer to each TX_THREAD contained in TX_HISR struct     */
	UNSIGNED         pointers;                  /* Number of pointers in list*/


    /* Switch to supervisor mode */


    /* Initialize the number of pointers returned.  */
    pointers =  0;

    /* Protect the task created list.  */


TX_INTERRUPT_SAVE_AREA

	TX_DISABLE

    /* Loop until all task pointers are in the list or until the maximum
       list size is reached.  */

	node_ptr = _tx_thread_created_ptr;
    while ((node_ptr) && (pointers < maximum_pointers) && (node_ptr->tx_thread_priority <= 2))//NOTE: priority 0-2 is used for HISR
    {

        /* Place the node into the destination list.  */
        *pointer_list++ =  (TX_HISR *) node_ptr;//TX_THREAD is the first member in the TX_HISR struct

        /* Increment the pointers variable.  */
        pointers++;

        /* Position the node pointer to the next node.  */
        node_ptr =  node_ptr->tx_thread_created_next;

        /* Determine if the pointer is at the head of the list.  */
        if (node_ptr == _tx_thread_created_ptr)		//it is a circular linked list

            /* The list search is complete.  */
            node_ptr =  TX_NULL;
    }

    /* Release protection.  */


    /* Return to user mode */

	TX_RESTORE

    /* Return the number of pointers in the list.  */
    return(pointers);
}

UINT32 OSAHISRIsValid(OsaRefT OsaRef)
{
	TX_THREAD *pTxTask = (TX_THREAD*)OsaRef;

	if(OsaRef)
		return ((pTxTask->tx_thread_id == TX_THREAD_ID) && (pTxTask->tx_thread_priority < 3));
	else
		return 0;
}

/***********************************************************************
 *
 * Name:        OsaThreadList()
 *
 * Description:  This function builds a list of thread pointers, starting at the
 *      		specified location.  The number of thread pointers placed in the
 *     		list is equivalent to the total number of thread or the maximum
 *    			 number of pointers specified in the call.
 *
 * Parameters:
 *  		ptrList                        Pointer to the list area
 *      	maximum_pointers                    Maximum number of pointers
 *
 * Returns:
 *  		Number of tasks placed in list
 *
 *
 *
 ***********************************************************************/
unsigned long OsaThreadList(OsaRefT *ptrList, unsigned long maximum_pointers,void *pForFutureUse)
{
	TX_THREAD **   	 pointer_list = (TX_THREAD **)ptrList;
	TX_THREAD        *node_ptr;                  /* Pointer to each TCB       */
	unsigned long         pointers;                  /* Number of pointers in list*/

    /* Initialize the number of pointers returned.  */
    pointers =  0;

    /* Protect the task created list.  */

TX_INTERRUPT_SAVE_AREA

	TX_DISABLE

    /* Loop until all task pointers are in the list or until the maximum
       list size is reached.  */

	node_ptr = _tx_thread_created_ptr;
    while ((node_ptr) && (pointers < maximum_pointers))//NOTE: priority 0-2 is used for HISR
    {

        /* Place the node into the destination list.  */
        *pointer_list++ =  (TX_THREAD *) node_ptr;

        /* Increment the pointers variable.  */
        pointers++;

        /* Position the node pointer to the next node.  */
        node_ptr =  node_ptr->tx_thread_created_next;

        /* Determine if the pointer is at the head of the list.  */
        if (node_ptr == _tx_thread_created_ptr)
        {

            /* The list search is complete.  */
            node_ptr =  TX_NULL;
			break;
        }

    }

    /* Release protection.  */
	TX_RESTORE

  	return pointers ;
}
VOID* OSATaskGetStackStart(OSATaskRef OsaRef){
	TX_THREAD
		*pTxTask = (TX_THREAD*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxTask->tx_thread_stack_start);
}

UINT32	OSATaskGetStackSize(OSATaskRef OsaRef){
	TX_THREAD
		*pTxTask = (TX_THREAD*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxTask->tx_thread_stack_size);
}

void (*OSATaskGetEntry(OSATaskRef OsaRef))(void *){
	TX_THREAD
		*pTxTask = (TX_THREAD*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (void(*)(void *))(pTxTask->tx_thread_entry);
}

UINT32	OSATaskGetEntryParam(OSATaskRef OsaRef){
	TX_THREAD
		*pTxTask = (TX_THREAD*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxTask->tx_thread_entry_parameter);
}

char*	OSATaskGetName(OSATaskRef OsaRef){
	TX_THREAD
		*pTxTask = (TX_THREAD*)OsaRef;

	OSA_ASSERT(OsaRef);

	if(pTxTask->tx_thread_id == TX_THREAD_ID)
	{
	    return (pTxTask->tx_thread_name);
	}
	else
	{
        return pNoneName;
	}
}

UINT32	OSATaskGetSysParam1(OSATaskRef OsaRef){
	TX_THREAD
		*pTxTask = (TX_THREAD*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxTask->tx_system_reserved_1);
}

void OSATaskSetSysParam1(OSATaskRef OsaRef, UINT32 value){
	TX_THREAD
		*pTxTask = (TX_THREAD*)OsaRef;

	OSA_ASSERT(OsaRef);

	pTxTask->tx_system_reserved_1 = value;
}

UINT32	OSATaskGetSysParam2(OSATaskRef OsaRef){
	TX_THREAD
		*pTxTask = (TX_THREAD*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxTask->tx_system_reserved_2);
}

void OSATaskSetSysParam2(OSATaskRef OsaRef, UINT32 value){
	TX_THREAD
		*pTxTask = (TX_THREAD*)OsaRef;

	OSA_ASSERT(OsaRef);

	pTxTask->tx_system_reserved_2 = value;
}

UINT32	OSATaskGetSysParam3(OSATaskRef OsaRef){
	TX_THREAD
		*pTxTask = (TX_THREAD*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxTask->tx_system_reserved_3);
}

void OSATaskSetSysParam3(OSATaskRef OsaRef, UINT32 value){
	TX_THREAD
		*pTxTask = (TX_THREAD*)OsaRef;

	OSA_ASSERT(OsaRef);

	pTxTask->tx_system_reserved_3 = value;
}

void*	OSAHISRGetStackStart(OSAHISRRef OsaRef){
	TX_HISR
		*pTxHisr = (TX_HISR*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxHisr->tx_hisr_thread.tx_thread_stack_start);
}

UINT32 OSAHISRGetStackSize(OSAHISRRef OsaRef){
	TX_HISR
		*pTxHisr = (TX_HISR*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxHisr->tx_hisr_thread.tx_thread_stack_size);
}

void (*OSAHISRGetEntry(OsaRefT OsaRef))(void){
	TX_HISR
		*pTxHisr = (TX_HISR*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (void (*)(void))(pTxHisr->tx_hisr_thread.tx_thread_entry);
}

char*  OSAHISRGetName(OSAHISRRef OsaRef){
	TX_HISR
		*pTxHisr = (TX_HISR*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxHisr->tx_hisr_thread.tx_thread_name);
}

UINT32	OSAHISRGetAppParam1(OSAHISRRef OsaRef){
	TX_HISR
		*pTxHisr = (TX_HISR*)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxHisr->tx_hisr_thread.tx_app_reserved_1);
}

void 	OSAHISRSetAppParam1(OSAHISRRef OsaRef, UINT32 value){
	TX_HISR
		*pTxHisr = (TX_HISR*)OsaRef;

	OSA_ASSERT(OsaRef);

	pTxHisr->tx_hisr_thread.tx_app_reserved_1 = value;
}

UINT32	OSAPartitionPoolGetAllocated(OSAPartitionPoolRef OsaRef){
	TX_BLOCK_POOL
		*pTxPool = (TX_BLOCK_POOL *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxPool->tx_block_pool_performance_allocate_count);
}

char*	OSAPartitionPoolGetName(OSAPartitionPoolRef OsaRef){
	TX_BLOCK_POOL
		*pTxPool = (TX_BLOCK_POOL *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxPool->tx_block_pool_name);
}

UINT32	OSAPartitionPoolGetAvailble(OSAPartitionPoolRef OsaRef){
	TX_BLOCK_POOL
		*pTxPool = (TX_BLOCK_POOL *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxPool->tx_block_pool_available);

}

UINT32	OSAPartitionPoolGetPartitionSize(OSAPartitionPoolRef OsaRef){
	TX_BLOCK_POOL
		*pTxPool = (TX_BLOCK_POOL *)OsaRef;

	OSA_ASSERT(OsaRef);

	return (pTxPool->tx_block_pool_block_size);
}

OSA_STATUS	OSAMsgQFrontSend(OsaRefT OsaRef, void *message,
                                        UINT32 size, UINT32 suspend){
	TX_QUEUE
		*pTxMsgQ = (TX_QUEUE *)OsaRef;

	UINT
		status;

	OSA_ASSERT(OsaRef);

	status = tx_queue_front_send(pTxMsgQ, message, Osa_TimeoutValue(suspend));

	RETURN_STATUS( status, TX_SUCCESS ) ;
}

BOOL OSAPartitionInUse(  void* BlockPtr, void* PoolPtr )
{
     /****************
   	In threadX, if the block has been allocated,  before its data area a 4 bytes area stores the ptr of associated poll,
   	otherwise it store the ptr point to next available block
   	*************/
     UCHAR  *blockPtr = (UCHAR *)BlockPtr ;
	 UCHAR  *workPtr;
     BOOL  retVal = TRUE;

	 workPtr = blockPtr - sizeof(UCHAR *);

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

	TX_BLOCK_POOL
		*pTxPool;

	UCHAR
		*workPtr;

	OSA_ASSERT(BlockPtr);

	workPtr =  ((UCHAR *) BlockPtr) - sizeof(UCHAR *);
    pTxPool =  *((TX_BLOCK_POOL **) workPtr);

	return pTxPool;

}

UINT32 OsaGetInterruptCount(void){
	extern volatile ULONG  _tx_thread_system_state;
	return _tx_thread_system_state;
}

static const struct
{
    unsigned int      tx_thread_state ;
    OSA_TASK_STATE    osa_task_state ;
}
taskStateTable[] =
{
	{TX_READY,   OSA_TASK_READY },
	{TX_COMPLETED,   OSA_TASK_COMPLETED },
	{TX_TERMINATED,   OSA_TASK_TERMINATED },
	{TX_SUSPENDED,   OSA_TASK_SUSPENDED },
	{TX_SLEEP,   OSA_TASK_SLEEP },
	{TX_QUEUE_SUSP,   OSA_TASK_QUEUE_SUSP },
	{TX_SEMAPHORE_SUSP,   OSA_TASK_SEMAPHORE_SUSP },
	{TX_EVENT_FLAG,   OSA_TASK_EVENT_FLAG },
	{TX_BLOCK_MEMORY,   OSA_TASK_BLOCK_MEMORY },
	{TX_MUTEX_SUSP,   OSA_TASK_MUTEX_SUSP },
} ;

static OSA_TASK_STATE Osa_TranslateTaskState(UINT state)
{
    UINT16      i;
	UINT16 table_num = sizeof(taskStateTable)/sizeof(taskStateTable[0]);

	for( i=0 ; i<table_num ; i++ )
    {
        if ( taskStateTable[i].tx_thread_state == state )
        {
            return taskStateTable[i].osa_task_state ;
        }
	}
	return OSA_TASK_STATE_UNKNOWN;
}

OSA_STATUS OsaGetTaskInfo(OsaRefT OsaRef, OSA_TASK *task_info)
{
	TX_THREAD
		*pTxTask = (TX_THREAD*)OsaRef;

	OSA_ASSERT(OsaRef);
	OSA_ASSERT(task_info);
	task_info->task_name = pTxTask->tx_thread_name;
	task_info->task_priority = pTxTask->tx_thread_priority;
	task_info->task_stack_start = (unsigned long)pTxTask->tx_thread_stack_start;
	task_info->task_stack_end= (unsigned long)pTxTask->tx_thread_stack_end;
	task_info->task_stack_size= pTxTask->tx_thread_stack_size;
	task_info->task_stack_ptr= (unsigned long)pTxTask->tx_thread_stack_ptr;
	task_info->task_stack_def_val = TX_STACK_FILL;
	task_info->task_state = Osa_TranslateTaskState(pTxTask->tx_thread_state);
	task_info->task_run_count = pTxTask->tx_thread_run_count;
	return OS_SUCCESS;
}




/***********************************************************************
 *
 * Name:        Osa_TimeoutValue()
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
UINT32 Osa_TimeoutValue( UINT32 timeout )
{

    if ( timeout == OS_SUSPEND )
        return TX_WAIT_FOREVER;

    if ( timeout == OS_NO_SUSPEND )
        return TX_NO_WAIT;

    return (UINT32)timeout ;
}

OSA_STATUS OsaListAllCreatedTasks( void )
{
    UINT16 i;
	TX_THREAD				*thread_ptr;

	thread_ptr =  _tx_thread_created_ptr;


	DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedTasks_1,  DIAG_DEBUG )
	diagPrintf( "total task+HISR: %d", _tx_thread_created_count);

	uart_printf( "total task+HISR: %d\r\n", _tx_thread_created_count);

	for(i = 0; i< _tx_thread_created_count; i++)
    {

		if(thread_ptr->tx_thread_original_priority <= 2 )
		{
			DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedTasks_HISR_2,  DIAG_DEBUG )
			diagPrintf( "HISR name: %s, ref: 0x%lx", thread_ptr->tx_thread_name,(UINT32)thread_ptr );


			uart_printf( "HISR name: %s, ref: 0x%lx\r\n", thread_ptr->tx_thread_name,(UINT32)thread_ptr );
		}
		else
		{
			DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedTasks_TASK_2,  DIAG_DEBUG )
	    	diagPrintf( "TASK name: %s, ref: 0x%lx", thread_ptr->tx_thread_name,(UINT32)thread_ptr );

			uart_printf( "TASK name: %s, ref: 0x%lx\r\n", thread_ptr->tx_thread_name,(UINT32)thread_ptr );
		}

        /* Move to the next thread.  */
        thread_ptr =  thread_ptr -> tx_thread_created_next;
    }

	return OS_SUCCESS;
}


OSA_STATUS OsaListAllCreatedTimers( void )
{
    UINT16 i;
	TX_TIMER                *timer_ptr;

	timer_ptr =  _tx_timer_created_ptr;


	DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedTimers_1,  DIAG_DEBUG )
	diagPrintf( "total timer: %d", _tx_timer_created_count);

	uart_printf( "total timer: %d\r\n", _tx_timer_created_count);

	for(i = 0; i< _tx_timer_created_count; i++)
    {

		DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedTimers_2,  DIAG_DEBUG )
    	diagPrintf( "timer name: %s, ref: 0x%lx", timer_ptr->tx_timer_name,(UINT32)timer_ptr );

		uart_printf( "timer name: %s, ref: 0x%lx\r\n", timer_ptr->tx_timer_name,(UINT32)timer_ptr );

        /* Move to the next timer.  */
        timer_ptr =  timer_ptr -> tx_timer_created_next;
    }

	return OS_SUCCESS;
}


OSA_STATUS OsaListAllCreatedEventFlags( void )
{
    UINT16 i;
	TX_EVENT_FLAGS_GROUP    *event_flags_ptr;

	event_flags_ptr =  _tx_event_flags_created_ptr;


	DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedEventFlags_1,  DIAG_DEBUG )
	diagPrintf( "total event flag: %d", _tx_event_flags_created_count);

	uart_printf( "total event flag: %d\r\n", _tx_event_flags_created_count);

	for(i = 0; i< _tx_event_flags_created_count; i++)
    {

		DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedEventFlags_2,  DIAG_DEBUG )
    	diagPrintf( "event flag name: %s, ref: 0x%lx", event_flags_ptr->tx_event_flags_group_name,(UINT32)event_flags_ptr );

		uart_printf( "event flag name: %s, ref: 0x%lx\r\n", event_flags_ptr->tx_event_flags_group_name,(UINT32)event_flags_ptr);


       	/* Move to the next event flags group.  */
        event_flags_ptr =  event_flags_ptr -> tx_event_flags_group_created_next;
    }

	return OS_SUCCESS;
}


OSA_STATUS OsaListAllCreatedMemBlockPools( void )
{
    UINT16 i;
	TX_BLOCK_POOL           *block_pool_ptr;


	block_pool_ptr =  _tx_block_pool_created_ptr;


	DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedBlockPools_1,  DIAG_DEBUG )
	diagPrintf( "total block pool: %d", _tx_block_pool_created_count);

	uart_printf( "total  block pool: %d\r\n", _tx_block_pool_created_count);

	for(i = 0; i< _tx_block_pool_created_count; i++)
    {

		DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedBlockPools_2,  DIAG_DEBUG )
    	diagPrintf( "block pool name: %s, ref: 0x%lx", block_pool_ptr->tx_block_pool_name,(UINT32)block_pool_ptr );

		uart_printf("block pool name: %s, ref: 0x%lx\r\n", block_pool_ptr->tx_block_pool_name,(UINT32)block_pool_ptr );


        /* Move to the next block pool.  */
        block_pool_ptr =  block_pool_ptr -> tx_block_pool_created_next;
    }

	return OS_SUCCESS;
}

OSA_STATUS OsaListAllCreatedMsgQs( void )
{
    UINT16 i;
	TX_QUEUE                *queue_ptr;

	queue_ptr =  _tx_queue_created_ptr;


	DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedMsgQs_1,  DIAG_DEBUG )
	diagPrintf( "total message queue: %d", _tx_queue_created_count);

	uart_printf( "total message queue: %d\r\n", _tx_queue_created_count);

	for(i = 0; i< _tx_queue_created_count; i++)
    {

		DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedMsgQs_2,  DIAG_DEBUG )
    	diagPrintf( "message queue name: %s, ref: 0x%lx", queue_ptr->tx_queue_name,(UINT32)queue_ptr );

		uart_printf( "message queue name: %s, ref: 0x%lx\r\n", queue_ptr->tx_queue_name,(UINT32)queue_ptr  );


        /* Move to the next queue.  */
        queue_ptr =  queue_ptr -> tx_queue_created_next;
    }

	return OS_SUCCESS;
}

OSA_STATUS OsaListAllCreatedSemaphores( void )
{
    UINT16 i;
	TX_SEMAPHORE            *semaphore_ptr;

	semaphore_ptr =  _tx_semaphore_created_ptr;


	DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedSemaphores_1,  DIAG_DEBUG )
	diagPrintf( "total semaphore: %d", _tx_semaphore_created_count);

	uart_printf( "total semaphore: %d\r\n", _tx_semaphore_created_count);

	for(i = 0; i< _tx_semaphore_created_count; i++)
    {

		DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedSemaphores_2,  DIAG_DEBUG )
    	diagPrintf( "semaphore name: %s, ref: 0x%lx", semaphore_ptr->tx_semaphore_name,(UINT32)semaphore_ptr );

		uart_printf( "semaphore name: %s, ref: 0x%lx\r\n", semaphore_ptr->tx_semaphore_name,(UINT32)semaphore_ptr   );


       	/* Move to the next semaphore.  */
        semaphore_ptr =  semaphore_ptr -> tx_semaphore_created_next;
    }

	return OS_SUCCESS;
}


OSA_STATUS OsaListAllCreatedMutexs( void )
{
    UINT16 i;
	TX_MUTEX                *mutex_ptr;

	mutex_ptr =  _tx_mutex_created_ptr;


	DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedMutexs_1,  DIAG_DEBUG )
	diagPrintf( "total mutex: %d", _tx_mutex_created_count);

	uart_printf( "total mutex: %d\r\n", _tx_mutex_created_count);

	for(i = 0; i< _tx_mutex_created_count; i++)
    {

		DIAG_FILTER( OSA, OSA_DUMP, OsaListAllCreatedMutexs_2,  DIAG_DEBUG )
    	diagPrintf( "mutex name: %s, ref: 0x%lx", mutex_ptr->tx_mutex_name,(UINT32)mutex_ptr );

		uart_printf( "mutex name: %s, ref: 0x%lx\r\n", mutex_ptr->tx_mutex_name,(UINT32)mutex_ptr   );


       	/* Move to the next mutex.  */
        mutex_ptr =  mutex_ptr -> tx_mutex_created_next;
    }

	return OS_SUCCESS;
}


