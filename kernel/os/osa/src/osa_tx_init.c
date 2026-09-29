/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : osa_nu_init.c
Description : Nucleus PLUS operating system specific code
              for the OS Abstraction Layer API.
              This file contains the functions that are usualy used during the init phase.
              The split into 2 files (this and os_nu_run.c) is done to be able to located
              only the "run" functions in a faster memory.

Notes       :

Copyright (c) 2008 Marvell MISL. All Rights Reserved
=========================================================================== */

/*
 * Include File.
 */
#include <stdio.h>
#include <string.h>
#include "gbl_types.h"
#include "intc.h"
#include "osa.h"
#include "osa_tx.h"
#include "osa_internals.h"
#include "diag.h"
#include "csw_mem.h"
#include "platform_nvm.h"
#include "utilities.h"
#include "UART.h"
#include "tx_semaphore.h"
#include "osa_mem.h"

/*
 * Defines.
 */
#define     MAX_SISR_PRIORITY       ((UINT32)OSA_SISR_MAX_PRIORITY)

#define TIMER_DELETE_TASK_STACK_SIZE 		1024
#define TIMER_DELETE_TASK_TASK_PRIORITY 	251

TX_THREAD	TimerDeleteTaskRef;
extern UINT32 EEHandlerFlag;

#define     BUF_SIZE_ALIGN(size, align)     (((size) + (align - 1)) & ~(align - 1))

__align(4) unsigned char TimerDeleteTaskStack[TIMER_DELETE_TASK_STACK_SIZE];

void TimerDeleteTask(ULONG argv);

/*
 * Macros.
 */
#define     MALLOC_REF(rEF,sIZE)                    \
    {                                               \
        rEF = (OsaRefT)OsaMemAlloc( NULL, sIZE ) ;  \
        {                                           \
	        UINT32 callerAddress ;                  \
			callerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;      \
			if ( rEF )                              \
			{                                       \
				OsaMemSetUserParamsFast(rEF, (UINT32)OsaCurrentThreadRef(), callerAddress);   \
			}                                       \
		}                                           \
        if ( ! rEF )                                \
        {                                           \
            OSA_ASSERT(0) ;                         \
            return OS_NO_MEMORY ;                   \
        }                                           \
                                                    \
        memset( (void *)rEF, 0, sIZE ) ;            \
    }


#define     MALLOC(tYPE,pTR,sIZE)                   \
    {                                               \
        pTR = (tYPE)OsaMemAlloc( NULL, sIZE ) ;     \
			{											\
				UINT32 callerAddress ;					\
				callerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;	   \
				if ( pTR )								\
				{										\
					OsaMemSetUserParamsFast(pTR, (UINT32)OsaCurrentThreadRef(), callerAddress);	 \
				}										\
			}											\
        if ( ! pTR )                                \
        {                                           \
            OSA_ASSERT(0) ;                         \
            return OS_NO_MEMORY ;                   \
        }                                           \
    }

#define     FREE_REF_AND_RETURN_STATUS(sTATUS,rEF,tYPE) \
    {                                                   \
        RETURN_STATUS_ON_FAILURE(sTATUS,TX_SUCCESS) ;   \
                                                        \
        CacheCleanMemory( (void *)rEF, sizeof(tYPE) ) ; \
        OsaMemFree( (void *)rEF ) ;                     \
                                                        \
        return OS_SUCCESS ;                             \
    }    /*  Need to Clean Cache bucause of Nucleus *_id magic number. */

/*
 * Static Data.
 */
static struct
{
    UINT32  *pMem ;
    UINT32  size ;
}
OsaIsr_SisrStacks[MAX_SISR_PRIORITY] ;

typedef struct DELTIMER
{
	OsaRefT  delete_timer;
	struct DELTIMER *previous_deleted_timer;
	struct DELTIMER *next_deleted_timer;
}DelTimer;

static DelTimer delTimer;
static DelTimer *delTimerTail = NULL;
static BOOL	delTimerTaskDone = 0;

/***********************************************************************
 *
 * Name:        OsaInit()
 *
 * Description: Initialize OS specific stuff.
 *
 * Parameters:  None
 *
 * Returns:     nothing
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaInit( OsaInitParamsT *pParams )
{
    UINT32
        align_value,
        i = MAX_SISR_PRIORITY - 1,
		status;


	uart_printf("file:%s,function:%s,line:%d\r\n", __FILE__,__func__,__LINE__);

    if ( pParams  &&  pParams->SisrStackPtr  &&  pParams->SisrStackSize )
        do
        {
            align_value = (UINT32)pParams->SisrStackPtr[i] & 3 ;
            OsaIsr_SisrStacks[i].pMem = (UINT32 *)((UINT32)pParams->SisrStackPtr[i] + align_value) ;
            OsaIsr_SisrStacks[i].size = pParams->SisrStackSize[i] - align_value ;
            memset( (void *)OsaIsr_SisrStacks[i].pMem, 0, OsaIsr_SisrStacks[i].size ) ;
        }
        while( i-- ) ;

    else
        memset( &OsaIsr_SisrStacks, 0, sizeof(OsaIsr_SisrStacks) ) ;


    OsaMem_InitPools() ;

	tx_time_set(0); //TODO:LPJ


	delTimer.delete_timer = NULL;
	delTimer.next_deleted_timer = NULL;
	delTimer.previous_deleted_timer = NULL;
	delTimerTail = &delTimer;

	uart_printf("file:%s,function:%s,line:%d\r\n", __FILE__,__func__,__LINE__);
	status = tx_thread_create(&TimerDeleteTaskRef, "TimerDel", TimerDeleteTask, 0, TimerDeleteTaskStack, TIMER_DELETE_TASK_STACK_SIZE,
								TIMER_DELETE_TASK_TASK_PRIORITY, TIMER_DELETE_TASK_TASK_PRIORITY, TX_NO_TIME_SLICE, TX_NO_ACTIVATE);


	uart_printf("file:%s,function:%s,line:%d,status:%d\r\n", __FILE__,__func__,__LINE__,status);
    ASSERT(status == OS_SUCCESS);


    return OS_SUCCESS ;
}

/***********************************************************************
 *
 * Name:        OsaRun()
 *
 * Description: Activates the OS.
 *
 * Parameters:  None
 *
 * Returns:     nothing
 *
 * Notes:
 *
 ***********************************************************************/
void OsaRun( void *pForFutureUse )
{

}

/***********************************************************************
 *
 * Name:        OsaTaskCreate
 *
 * Description: Create Task.
 *
 * Parameters:
 *  OsaRefT                 *pOsaRef    [OT]    Task Reference.
 *  OsaTaskCreateParamsT    *pParams    [IN]    Input Parameters (see datatype for details).
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaTaskCreateEx( OsaRefT *pOsaRef, OsaTaskCreateParamsT *pParams )
{
    static UINT8
        objectCnt = 0 ;

    CHAR
        *pName ;

    OsaRefT
        OsaRef ;

    TX_THREAD
       *pTxTask ;

    UINT
        priority,
        status ;

    ULONG
        size ;

    VOID
        *stackPtr ;

	ULONG
		malloc_flag = 0;

    OSA_ASSERT(pOsaRef) ;
    OSA_ASSERT(pParams) ;

    MALLOC_REF( OsaRef, sizeof(TX_THREAD) ) ;
    pTxTask = (TX_THREAD *)OsaRef ;

    size = pParams->stackSize ;
    priority = pParams->priority + 3; //priority 0-2 is used for HISR, so all of the thread's priority is plused by 3.

    if ( ! pParams->stackPtr )
    {
        MALLOC( VOID *, stackPtr, size ) ;
		malloc_flag = 1;

    }
    else
    {
        stackPtr = (VOID *)(((UINT32)pParams->stackPtr + 3) & ~3) ;
        size -= (ULONG)((UINT32)stackPtr - (UINT32)pParams->stackPtr) ;
		malloc_flag = 0;
    }

    memset( (void *)stackPtr, 0xA5, size ) ;

    MALLOC( char *, pName, TX_MAX_NAME );
    if ( pParams->name ){
        strncpy(pName, pParams->name, TX_MAX_NAME-1) ;
        pName[TX_MAX_NAME-1] = '\0';
    }
    else
    {
        sprintf( pName, "Task-%d", ++objectCnt ) ;
    }

    *pOsaRef = OsaRef ;

	pTxTask->tx_app_reserved_1 = malloc_flag;

    //TODO: Pijing Liu pParams->argv
    status = tx_thread_create(pTxTask, pName, (void (*)(ULONG))pParams->entry, (ULONG)pParams->argv,
                (VOID *)stackPtr, (ULONG)size, (UINT)priority, (UINT)priority, 1, TX_AUTO_START);

    //Pijing Liu debug
    if(status != TX_SUCCESS)
    {
        *pOsaRef = NULL ;
        uart_printf("Thread Fail: %x,%s,%p,%d\r\n",status,pName,stackPtr,priority);
    }
    RETURN_STATUS( status, TX_SUCCESS ) ; //TODO: ERROR TABLE
}

OSA_STATUS OsaTaskCreate( OsaRefT *pOsaRef, OsaTaskCreateParamsT *pParams )
{
    static UINT8
        objectCnt = 0 ;

    CHAR
        *pName ;

    OsaRefT
        OsaRef ;

	TX_THREAD
       *pTxTask ;

    UINT
		priority,
        status ;

    ULONG
        size ;

    VOID
        *stackPtr ;

	ULONG
		malloc_flag = 0;

    OSA_ASSERT(pOsaRef) ;
    OSA_ASSERT(pParams) ;

	MALLOC_REF( OsaRef, sizeof(TX_THREAD) ) ;
	pTxTask = (TX_THREAD *)OsaRef ;

    size = pParams->stackSize ;
	priority = pParams->priority + 3; //priority 0-2 is used for HISR, so all of the thread's priority is plused by 3.

    if ( ! pParams->stackPtr )
    {
        MALLOC( VOID *, stackPtr, size ) ;
		malloc_flag = 1;

    }
    else
    {
        stackPtr = (VOID *)(((UINT32)pParams->stackPtr + 3) & ~3) ;
        size -= (ULONG)((UINT32)stackPtr - (UINT32)pParams->stackPtr) ;
		malloc_flag = 0;
    }

    memset( (void *)stackPtr, 0xA5, size ) ;

	MALLOC( char *, pName, TX_MAX_NAME );
    if ( pParams->name ){
        strncpy(pName, pParams->name, TX_MAX_NAME-1) ;
		pName[TX_MAX_NAME-1] = '\0';
    }
    else
    {
        sprintf( pName, "Task-%d", ++objectCnt ) ;
    }

    *pOsaRef = OsaRef ;

    pTxTask->tx_app_reserved_1 = malloc_flag ;

	//TODO: Pijing Liu pParams->argv
	status = tx_thread_create(pTxTask, pName, (void (*)(ULONG))pParams->entry, (ULONG)pParams->argv,
				(VOID *)stackPtr, (ULONG)size, (UINT)priority, (UINT)priority, TX_NO_TIME_SLICE, TX_AUTO_START);

	//Pijing Liu debug
	if(status != TX_SUCCESS)
	{
	    *pOsaRef = NULL ;
		uart_printf("Thread Fail: %x,%s,%p,%d\r\n",status,pName,stackPtr,priority);
	}
    RETURN_STATUS( status, TX_SUCCESS ) ; //TODO: ERROR TABLE
}

typedef TX_THREAD* rti_thread_t;

/***********************************************************************
 *
 * Name:        OsaTaskDelete
 *
 * Description: Delete Task.
 *
 * Parameters:
 *  OsaRefT                 OsaRef      [IN]    Task Reference.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaTaskDelete( OsaRefT OsaRef, void *pForFutureUse )
{
    CHAR
        *task_name ;

    UINT
        task_status ;

	TX_THREAD
		*pTxTask = (TX_THREAD *)OsaRef,
		*next_thread,
		*next_suspended_thread;

    UINT
        preemption_threshold,
        priority ;

    ULONG
        scheduled_count,
        time_slice ;

    void
        *stack_base ;

    UINT
		status;
	UINT32 CallerAddress ;

	OSA_ASSERT(OsaRef) ;

#if defined(__ARMCC_VERSION)
	CallerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;  //  Keep first.
#else
	CallerAddress = 0;
#endif


	status = tx_thread_info_get(pTxTask, &task_name, &task_status, &scheduled_count, &priority,
									&preemption_threshold, &time_slice, &next_thread, &next_suspended_thread);

    DIAG_FILTER( OSA, OSA_TX, OsaTaskDelete_0, DIAG_ERROR )
    diagPrintf( "caller 0x%lx, delete %s, tx status %d",CallerAddress,task_name,task_status);


    if ( status == TX_SUCCESS )
    {
        switch( task_status )
        {
            case TX_COMPLETED :
            case TX_SUSPENDED :
            case TX_SLEEP:
            case TX_QUEUE_SUSP:
            case TX_SEMAPHORE_SUSP:
            case TX_EVENT_FLAG:
            case TX_BLOCK_MEMORY :
            case TX_BYTE_MEMORY:
            case TX_IO_DRIVER :
            case TX_FILE:
            case TX_TCP_IP:
			case TX_MUTEX_SUSP:
			case TX_READY:
                status = tx_thread_terminate( pTxTask ) ;
                RETURN_STATUS_ON_FAILURE( status, TX_SUCCESS ) ;
                break ;

            case TX_TERMINATED:
                break ;

            default:
                ASSERT_EXT(0, "OsaTaskDelete status 0x%x, OsaRef 0x%x", task_status, OsaRef);
                return OS_FAIL ;
        }

    }
	extern 		void rti_delete_thread(rti_thread_t tid);
	rti_delete_thread(pTxTask);

    if ( pTxTask->tx_app_reserved_1 == 0x1)
    {
    	stack_base = pTxTask->tx_thread_stack_start;
        OsaMemFree( stack_base ) ;
    }

	OsaMemFree( pTxTask->tx_thread_name ) ;

    status = tx_thread_delete( pTxTask ) ;

    FREE_REF_AND_RETURN_STATUS( status, OsaRef, TX_THREAD ) ;
}

/***********************************************************************
 *
 * Name:        OsaTaskTerminate
 *
 * Description: Terminate Task.
 *
 * Parameters:
 *  OsaRefT                 OsaRef      [IN]    Task Reference.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaTaskTerminate( OsaRefT OsaRef, void *pForFutureUse )
{
	UINT status;

	OSA_ASSERT(OsaRef) ;
	status = tx_thread_terminate( (TX_THREAD *)OsaRef );

	RETURN_STATUS( status, TX_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaTaskSuspend
 *
 * Description: Suspend Task.
 *
 * Parameters:
 *  OsaRefT                 OsaRef      [IN]    Task Reference.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaTaskSuspend( OsaRefT OsaRef, void *pForFutureUse )
{
    UINT    status;
	UINT32 CallerAddress ;

	 OSA_ASSERT(OsaRef) ;

#if defined(__ARMCC_VERSION)
			CallerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;  //  Keep first.
#else
			CallerAddress = 0;
#endif

	status = tx_thread_suspend( (TX_THREAD *)OsaRef ) ;


	if(status != TX_SUCCESS)
	{

		if(!InProduction_Mode())
		{
			DIAG_FILTER( OSA, OSA_TX, OsaTaskSuspend_ERR, DIAG_ERROR )
			diagPrintf( "OsaTaskSuspend status %d by 0x%lx",status,CallerAddress);
		}
		WARNING(0);

		return OS_FAIL;
	}


	return OS_SUCCESS;
    //RETURN_STATUS( status, TX_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaTaskResume
 *
 * Description: Resume Task.
 *
 * Parameters:
 *  OsaRefT                 OsaRef      [IN]    Task Reference.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaTaskResume( OsaRefT OsaRef, void *pForFutureUse )
{
    UINT status = TX_SUCCESS;

	UINT32 CallerAddress ;

	OSA_ASSERT(OsaRef) ;

#if defined(__ARMCC_VERSION)
	CallerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;  //  Keep first.
#else
	CallerAddress = 0;
#endif


	status = tx_thread_resume( (TX_THREAD *)OsaRef ) ;

	if(status != TX_SUCCESS)
	{
		if(!InProduction_Mode())
		{
			DIAG_FILTER( OSA, OSA_TX, OsaTaskResume_ERR, DIAG_ERROR )
			diagPrintf( "OsaTaskResume status %d by 0x%lx",status,CallerAddress);
		}
		WARNING(0);

		return OS_FAIL;
	}
	return OS_SUCCESS;

   // RETURN_STATUS( status, TX_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaTaskSleep
 *
 * Description: Task sleep.
 *
 * Parameters:
 *  UINT32              ticks           [IN]    Ticks to sleep.
 *
 * Returns:
 *
 * Notes:
 *
 ***********************************************************************/
void OsaTaskSleep( UINT32 ticks, void *pForFutureUse )
{
	if(1 == EEHandlerFlag)
	{
		return ;
    }

	tx_thread_sleep(ticks);

}

/***********************************************************************
 *
 * Name:        OsaTaskChangePriority
 *
 * Description: Change task priority.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Task Reference.
 *  UINT8                   newPriority     [IN]    New Priority.
 *  UINT8                   *oldPriority    [OT]    Old Priority.
 *
 * Returns:
 *      OS_SUCCESS
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaTaskChangePriority( OsaRefT OsaRef, UINT8 newPriority, UINT8 *oldPriority, void *pForFutureUse )
{
    OSA_ASSERT(oldPriority) ;
	UINT newPriorityTX,oldPriorityTX;
	newPriorityTX = newPriority + 3;
	tx_thread_priority_change( (TX_THREAD *)OsaRef, (UINT)newPriorityTX, (UINT *)&oldPriorityTX );

	*(oldPriority) = (UINT8)oldPriorityTX - 3;
    return OS_SUCCESS ;
}

/***********************************************************************
 *
 * Name:        OsaTaskGetPriority
 *
 * Description: Get task priority.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Task Reference.
 *  UINT8                   *pPriority      [OT]    Priority.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaTaskGetPriority( OsaRefT OsaRef, UINT8 *pPriority, void *pForFutureUse )
{
    CHAR
        *task_name ;

    UINT
        task_status ;

	TX_THREAD
		*next_thread,
		*next_suspended_thread;

    UINT
        preemption_threshold,
        priority ;

    ULONG
        scheduled_count,
        time_slice ;

	UINT
		status = tx_thread_info_get((TX_THREAD *)OsaRef, &task_name, &task_status, &scheduled_count, &priority,
									&preemption_threshold, &time_slice, &next_thread, &next_suspended_thread);

    OSA_ASSERT(pPriority) ;
    *pPriority = (UINT8)priority - 3;

    RETURN_STATUS( status, TX_SUCCESS ) ;
}





OSA_STATUS OsaHisrCreate(OsaRefT* OsaRef, CHAR* name, VOID (*hisr_entry)(VOID), unsigned char priority)
{
	CHAR *pName ;
	static UINT8 objectCnt = 0 ;
	OSA_STATUS status;


	MALLOC_REF( *OsaRef, sizeof(TX_HISR) ) ;

	MALLOC(char *, pName, TX_MAX_NAME);
	if ( name ){

		strncpy(pName, name, TX_MAX_NAME-1) ;
		pName[TX_MAX_NAME-1] = '\0';
	}
	else
	{
		sprintf( pName, "Hisr-%d", ++objectCnt ) ;
	}

	status = tx_hisr_create((TX_HISR *)*OsaRef, pName, (void (*)(ULONG))hisr_entry, 0, priority);
	RETURN_STATUS( status, TX_SUCCESS ) ;
}



OSA_STATUS OsaHisrActivate(OsaRefT *hisr)
{
	OSA_STATUS status;
	status = tx_hisr_activate((TX_HISR *)*hisr);
	RETURN_STATUS( status, TX_SUCCESS ) ;
}


OSA_STATUS OsaHisrDel(OsaRefT *hisr)
{
	OSA_STATUS status = 0;

	OSA_ASSERT(*hisr) ;
	extern 		void rti_delete_thread(rti_thread_t tid);
	rti_delete_thread(&((TX_HISR *)*hisr)->tx_hisr_thread);

	status = (INT32)tx_hisr_delete((TX_HISR *)*hisr);

	OsaMemFree(*hisr);

	RETURN_STATUS( status, TX_SUCCESS ) ;
}



OSA_STATUS OsaHISRGetPriority( OsaRefT OsaRef, UINT8 *pPriority, void *pForFutureUse )
{
    CHAR
        *hisr_name ;

    UINT
        hisr_status ;

	TX_THREAD
		*next_hisr_thread,
		*next_suspended_hisr_thread;

    UINT
        preemption_threshold,
        priority ;

    ULONG
        scheduled_count,
        time_slice ;

	UINT
		status = tx_thread_info_get(&(((TX_HISR *)OsaRef)->tx_hisr_thread), &hisr_name, &hisr_status, &scheduled_count, &priority,
									&preemption_threshold, &time_slice, &next_hisr_thread, &next_suspended_hisr_thread);

    OSA_ASSERT(pPriority) ;
    *pPriority = (UINT8)priority;

    RETURN_STATUS( status, TX_SUCCESS ) ;
}


/***********************************************************************
 *
 * Name:        OsaSemaphoreCreate
 *
 * Description: Create Semaphore.
 *
 * Parameters:
 *  OsaRefT                     *pOsaRef    [OT]    Reference.
 *  OsaSemaphoreCreateParamsT   *pParams    [IN]    Input Parameters (see datatype for details).
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaSemaphoreCreate( OsaRefT *pOsaRef, OsaSemaphoreCreateParamsT *pParams, UINT32 callerAddress)
{
    static UINT8
        objectCnt = 0 ;

    CHAR
        *pName ;

    OsaRefT
        OsaRef ;

	UINT8
		waitingMode = OSA_FIFO;

    UINT
        status ;

    UINT32
        initialCount = 1,
        maximumCount = 1 ;

    OsaSemaphoreT
        *pSemRef ;

	OSA_ASSERT(pOsaRef) ;
	OSA_ASSERT(pParams) ;

/*
 * Set Parameters
 */
    if ( pParams )
    {
        if ( ! pParams->maximumCount )
            maximumCount = pParams->initialCount ? pParams->initialCount : 0xFFFFFFFE ; //TODO: Pijing Liu
        else if ( pParams->initialCount <= pParams->maximumCount )
            maximumCount = pParams->maximumCount ;
        else
            OSA_ASSERT(0) ;

        initialCount = pParams->initialCount ;

        if ( pParams->waitingMode == OSA_FIFO )
           waitingMode = OSA_FIFO ;
		else
		   waitingMode = OSA_PRIORITY;

    }

	/*
 * Create Semaphore
 */
    MALLOC_REF( OsaRef, sizeof(OsaSemaphoreT) ) ;
	if (callerAddress!=NULL && OsaRef!=NULL)
	{
		OsaMemSetUserParamsFast(OsaRef, (UINT32)OsaCurrentThreadRef(), callerAddress);
	}

    pSemRef = (OsaSemaphoreT *)OsaRef ;
    pSemRef->maximumCount = maximumCount ;
	pSemRef->waitingMode = waitingMode;

    MALLOC( char *, pName, TX_MAX_NAME );

	if (callerAddress!=NULL && pName!=NULL)
	{
		OsaMemSetUserParamsFast(pName, (UINT32)OsaCurrentThreadRef(), callerAddress);
	}
    if ( pParams && pParams->name ){
        strncpy(pName, pParams->name, TX_MAX_NAME-1) ;
		pName[TX_MAX_NAME-1] = '\0';
    }
    else
    {
        sprintf( pName, "Sem-%d", ++objectCnt ) ;
    }

	status = tx_semaphore_create( &(pSemRef->TxRef), pName, initialCount);

	*pOsaRef = OsaRef ;

    RETURN_STATUS( status, TX_SUCCESS ) ;//TODO:error table
}

/***********************************************************************
 *
 * Name:        OsaSemaphoreDelete
 *
 * Description: Delete semaphore.
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
OSA_STATUS OsaSemaphoreDelete( OsaRefT OsaRef, void *pForFutureUse )
{
    UINT
        status ;

    OsaSemaphoreT
        *pSemRef = (OsaSemaphoreT *)OsaRef ;

    OSA_ASSERT(pSemRef) ;

	OsaMemFree(pSemRef->TxRef.tx_semaphore_name);

    status = tx_semaphore_delete( &(pSemRef->TxRef) );

    FREE_REF_AND_RETURN_STATUS( status, OsaRef, OsaSemaphoreT ) ;
}

/***********************************************************************
 *
 * Name:        OsaMutexCreate
 *
 * Description: No Mutex in Nucleus so do Semaphore.
 *
 * Parameters:
 *  OsaRefT                     *pOsaRef    [OT]    Reference.
 *  OsaMutexCreateParamsT       *pParams    [IN]    Input Parameters (see datatype for details).
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaMutexCreate( OsaRefT *pOsaRef, OsaMutexCreateParamsT *pParams , UINT32 callerAddress)
{
    OsaSemaphoreCreateParamsT
        SemParams ;
	UINT32 localCallerAddress ;
	localCallerAddress= (__ARMCC_VERSION >= 200000&&!callerAddress) ? __return_address() : callerAddress ;
    memset( &SemParams, 0, sizeof(SemParams) ) ;

    if ( pParams )
    {
        SemParams.name = pParams->name ;
        SemParams.bSharedForIpc = pParams->bSharedForIpc ;

        if ( pParams->waitingMode == OSA_FIFO )
            SemParams.waitingMode = OSA_FIFO ;
        else
            SemParams.waitingMode = OSA_PRIORITY ;
    }

    SemParams.initialCount = 1 ;
    SemParams.maximumCount = 1 ;


    return OsaSemaphoreCreate( pOsaRef, &SemParams,localCallerAddress) ;
}

/***********************************************************************
 *
 * Name:        OsaMutexDelete
 *
 * Description: No Mutex in Nucleus so do Semaphore.
 *
 * Parameters:
 *  OsaRefT                     OsaRef      [IN]    Reference.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaMutexDelete( OsaRefT OsaRef, void *pForFutureUse )
{
    return OsaSemaphoreDelete( OsaRef, pForFutureUse ) ;
}

#if 0
/***********************************************************************
 *
 * Name:        OsaIsrCreate
 *
 * Description: Register the LISR in INTC (if FISR & intSource exist) and create a HISR (if SISR exist).
 *
 * Parameters:
 *  OsaRefT                     *pOsaRef    [OT]    Reference.
 *  OsaIsrCreateParamsT         *pParams    [IN]    Input Parameters (see datatype for details).
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaIsrCreate( OsaRefT *pOsaRef, OsaIsrCreateParamsT *pParams )
{
    static UINT8
        objectCnt = 0 ;

    CHAR
        *pName ;

    OsaRefT
        OsaRef ;

    OsaIsrT
        *pIsrRef ;

    UINT
        status ;

    UINT32
        *pStack,
        size ;

/*
 * Check Parameters.
 */
    OSA_ASSERT(pOsaRef) ;
    OSA_ASSERT(pParams) ;

    if ( pParams->intSource == OSA_NULL_INT_SOURCE )
        ;

    else if ( pParams->intSource >= INTC_MAX_INTERRUPT_SOURCES )
    {
        OSA_ASSERT(0) ;
        return OS_INVALID_VECTOR ;
    }

/*
 * Register the LISR if needed.
 */
    else if ( ! pParams->fisrRoutine )
        ;

    else if ( INTC_RC_OK != INTCBind((INTC_InterruptSources)pParams->intSource,pParams->fisrRoutine) )
    {
        OSA_ASSERT(0) ;
        return OS_FAIL ;
    }

/*
 * Alloc Memory for Ref.
 */
    MALLOC_REF( OsaRef, sizeof(OsaIsrT) ) ;

    pIsrRef = (OsaIsrT *)OsaRef ;

    pIsrRef->intSource = pParams->intSource ;
    pIsrRef->fisrRoutine = pParams->fisrRoutine ;

/*
 * Create HISR if needed.
 */
    if ( pParams->sisrRoutine )
    {
        UINT32
            priority = (UINT32)pParams->priority ;

        if ( priority >= OSA_SISR_MAX_PRIORITY )
        {
            OSA_ASSERT(0) ;
            return OS_INVALID_PRIORITY ;
        }

        pStack = OsaIsr_SisrStacks[priority].pMem ;

        if ( ! pStack )
        {
            size = pParams->stackSize ? pParams->stackSize : 2048 ;
            MALLOC( UINT32 *, pStack, size ) ;
            memset( (void *)pStack, 0xA5, size ) ;
            OsaIsr_SisrStacks[priority].pMem = pStack ;
            OsaIsr_SisrStacks[priority].size = size ;
        }

        else
            size = OsaIsr_SisrStacks[priority].size ;

        pIsrRef->sisrRoutine = pParams->sisrRoutine ;

        MALLOC( char *, pName, TX_MAX_NAME );
    	if ( pParams->name ){
        	strncpy(pName, pParams->name, TX_MAX_NAME-1) ;
			pName[TX_MAX_NAME-1] = '\0';
    	}
        else
        {
            sprintf( pName, "HISR-%d", ++objectCnt ) ;
        }

		status = tx_hisr_create( &pIsrRef->TxRef, pName,(VOID(*)(ULONG))pParams->sisrRoutine,
									0, (UINT)priority);

    }

    else
        status = TX_SUCCESS ;

    *pOsaRef = OsaRef ;

    RETURN_STATUS( status, TX_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaIsrDelete
 *
 * Description: Delete the ISR.
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
OSA_STATUS OsaIsrDelete( OsaRefT OsaRef, void *pForFutureUse )
{
    UINT
        status ;

    OsaIsrT
        *pIsrRef = (OsaIsrT *)OsaRef ;

    OSA_ASSERT(pIsrRef) ;

    if ( pIsrRef->fisrRoutine )
        INTCUnbind( (INTC_InterruptSources)pIsrRef->intSource ) ;

    if ( pIsrRef->sisrRoutine ){
		status = tx_hisr_delete( &pIsrRef->TxRef );

		OsaMemFree(pIsrRef->TxRef.tx_hisr_thread.tx_thread_name);

    }
    else
        status = TX_SUCCESS ;

    FREE_REF_AND_RETURN_STATUS( status, OsaRef, OsaIsrT ) ;
}
#endif
/***********************************************************************
 *
 * Name:        OsaCriticalSectionCreate
 *
 * Description: Create a critical section.
 *
 * Parameters:
 *  OsaMutexCreateParamsT       *pParams    [IN]    Input Parameters (see datatype for details).
 *
 * Returns:
 *  OsaRefT                     *pOsaRef    [OT]    Reference.
 *
 * Notes:
 *
 ***********************************************************************/
OsaRefT OsaCriticalSectionCreate( OsaCriticalSectionCreateParamsT *pParams )
{

    return OSA_DUMMY_CRITICAL_SECTION_HANDLE ;
}

/***********************************************************************
 *
 * Name:        OsaCriticalSectionDelete
 *
 * Description: Delete a critical section.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *
 * Returns:
 *
 * Notes:
 *
 ***********************************************************************/
void OsaCriticalSectionDelete( OsaRefT OsaRef, void *pForFutureUse )
{

}

/***********************************************************************
 *
 * Name:        OsaMsgQCreate
 *
 * Description: Create a message Q..
 *
 * Parameters:
 *  OsaRefT                     *pOsaRef    [OT]    Reference.
 *  OsaMsgQCreateParamsT        *pParams    [IN]    Input Parameters (see datatype for details).
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes: the message size is in the term of ULONG
 		NU: the queue size is the total number of ULONG elements.  TX: the queue size is the total number of bytes.
 *
 ***********************************************************************/
OSA_STATUS OsaMsgQCreate( OsaRefT *pOsaRef, OsaMsgQCreateParamsT *pParams , UINT32 callerAddress)
{
    static UINT8
        objectCnt = 0 ;

    CHAR
        *pName ;

    OsaRefT
        OsaRef ;

	OsaMsgQT
		*pMsgQRef ;

    UINT
        status ;

    ULONG
        msgSize,
        qSize  ;

    void
        *qAddr ;

    OSA_ASSERT(pOsaRef) ;
    OSA_ASSERT(pParams) ;

/*
 * Alloc Q.
 */
    //qSize = (pParams->maxSize + sizeof(ULONG)) * (pParams->maxMsg) ;

	qSize = (BUF_SIZE_ALIGN(pParams->maxSize,sizeof(ULONG))) * (pParams->maxMsg) ;

    MALLOC( void *, qAddr, qSize ) ;

    if ( pParams->maxSize > sizeof(ULONG) * TX_64_ULONG)
    {
       	return OS_INVALID_SIZE;
    }
    else
    {
        msgSize = OSA_MSGQ_MSG_SIZE(pParams->maxSize) ;		//all sizes are in terms of ULONG data element
    }

	MALLOC_REF( OsaRef, sizeof(OsaMsgQT) ) ;

	if (callerAddress!=NULL && OsaRef!=NULL)
	{
		OsaMemSetUserParamsFast(OsaRef, (UINT32)OsaCurrentThreadRef(), callerAddress);
	}

	pMsgQRef = (OsaMsgQT *)OsaRef ;

/*
 * Prepare Parameters.
 */
 	if ( pParams->waitingMode == OSA_FIFO )
        pMsgQRef->waitingMode = OSA_FIFO ;
    else
        pMsgQRef->waitingMode = OSA_PRIORITY ;



    MALLOC( char *, pName, TX_MAX_NAME );

	if (callerAddress!=NULL && pName!=NULL)
	{
		OsaMemSetUserParamsFast(pName, (UINT32)OsaCurrentThreadRef(), callerAddress);
	}
    if ( pParams->name ){
        strncpy(pName, pParams->name, TX_MAX_NAME-1) ;
		pName[TX_MAX_NAME-1] = '\0';
    }
    else
    {
        sprintf( pName, "Queue-%d", ++objectCnt ) ;
    }

/*
 * Create Q.
 */
    status = tx_queue_create( (TX_QUEUE *)&pMsgQRef->TxRef, pName, msgSize, (VOID *)qAddr, qSize);

    *pOsaRef = OsaRef ;
//Pijing Liu debug
	if(status != TX_SUCCESS)
		uart_printf("pjliu: LINE:%d, FUNC:%s, status = 0x%x, qSize = %u, msgSize = %u\r\n", __LINE__, __FUNCTION__, status, qSize, msgSize);

    RETURN_STATUS( status, TX_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaMsgQDelete
 *
 * Description: Delete message Q.
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
OSA_STATUS OsaMsgQDelete( OsaRefT OsaRef, void *pForFutureUse )
{
    OsaMsgQT
        *pMsgQRef = (OsaMsgQT *)OsaRef ;

    UINT
        status ;

    OSA_ASSERT(pMsgQRef) ;

	if ( OsaMemGetPoolRef(NULL,(void *)pMsgQRef->TxRef.tx_queue_start, NULL) )
        OsaMemFree( (void *)pMsgQRef->TxRef.tx_queue_start ) ;

	OsaMemFree( pMsgQRef->TxRef.tx_queue_name );

	status = tx_queue_delete( &pMsgQRef->TxRef ) ;

    FREE_REF_AND_RETURN_STATUS( status, pMsgQRef, OsaMsgQT ) ;
}

/***********************************************************************
 *
 * Name:        OsaMailboxQCreate
 *
 * Description: Create a mailbox Q.
 *              Each mailbox entry is 32 bit.
 *
 * Parameters:
 *  OsaRefT                     *pOsaRef    [OT]    Reference.
 *  OsaMailboxQCreateParamsT    *pParams    [IN]    Input Parameters (see datatype for details).
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaMailboxQCreate( OsaRefT *pOsaRef, OsaMailboxQCreateParamsT *pParams )
{
    OsaMsgQCreateParamsT
        Params ;
	UINT32 callerAddress ;
	callerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;
    OSA_ASSERT(pParams) ;

    memset( (void *)&Params, 0 , sizeof(Params) ) ;

    Params.maxSize = sizeof(ULONG) ;
    Params.maxMsg = pParams->maxMsg ;
    Params.name = pParams->name ;
    Params.bSharedForIpc = pParams->bSharedForIpc ;
    Params.waitingMode = pParams->waitingMode ;

    return OsaMsgQCreate( pOsaRef, &Params,callerAddress ) ;
}

/***********************************************************************
 *
 * Name:        OsaMailboxQDelete
 *
 * Description: Delete mailbox Q.
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
OSA_STATUS OsaMailboxQDelete( OsaRefT OsaRef, void *pForFutureUse )
{
    return OsaMsgQDelete( OsaRef, pForFutureUse ) ;
}

/***********************************************************************
 *
 * Name:        OsaFlagCreate
 *
 * Description: Create a flag event group.
 *
 * Parameters:
 *  OsaRefT                     *pOsaRef    [OT]    Reference.
 *  OsaFlagCreateParamsT        *pParams    [IN]    Input Parameters (see datatype for details).
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaFlagCreate( OsaRefT *pOsaRef, OsaFlagCreateParamsT *pParams )
{
    static UINT8
        objectCnt = 0 ;

    CHAR
        *pName ;

    TX_EVENT_FLAGS_GROUP
        *OsaRef ;

    UINT
        status ;


    OSA_ASSERT(pOsaRef) ;

	MALLOC_REF( OsaRef, sizeof(TX_EVENT_FLAGS_GROUP) ) ;

	MALLOC( char *, pName, TX_MAX_NAME );
	if ( pParams && pParams->name ){
		strncpy(pName, pParams->name, TX_MAX_NAME-1) ;
		pName[TX_MAX_NAME-1] = '\0';
	}
	else
	{
		sprintf( pName, "Flag-%d", ++objectCnt ) ;
	}

	status = tx_event_flags_create( OsaRef, pName );

    *pOsaRef = (OsaRefT)OsaRef ;
//Pijing Liu debug
	if(status != TX_SUCCESS){
		uart_printf("ERROR: %s: status = 0x%x\r\n", __FUNCTION__, status);
	}

	RETURN_STATUS( status, TX_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaFlagDelete
 *
 * Description: Delete event group.
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
OSA_STATUS OsaFlagDelete( OsaRefT OsaRef, void *pForFutureUse )
{
    UINT
		status;
	TX_EVENT_FLAGS_GROUP
		*pOsaRef = (TX_EVENT_FLAGS_GROUP *)OsaRef;

	OsaMemFree( pOsaRef->tx_event_flags_group_name );

	status = tx_event_flags_delete( (TX_EVENT_FLAGS_GROUP *)OsaRef );


    FREE_REF_AND_RETURN_STATUS( status, OsaRef, TX_EVENT_FLAGS_GROUP ) ;
}

/***********************************************************************
 *
 * Name:        OsaTimerCreate
 *
 * Description: Create a Timer, if no input params the timer will be created on OsaTimerStart.
 *
 * Parameters:
 *  OsaRefT                     *pOsaRef    [OT]    Reference.
 *  OsaTimerParamsT             *pParams    [OP,IN] Input Parameters (see datatype for details).
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaTimerCreate( OsaRefT *pOsaRef, OsaTimerParamsT *pParams )
{
    static UINT8
        objectCnt = 0 ;

    CHAR
        *pName ;

    OsaRefT
        OsaRef = NULL;

    TX_TIMER
        *pTxTimer ;

    UINT
        status ;

    OSA_ASSERT(pOsaRef) ;

    MALLOC_REF( OsaRef, sizeof(TX_TIMER) ) ;

	pTxTimer = OsaRef;

    if ( ! pParams )
    {
		MALLOC( char *, pTxTimer->tx_timer_name, TX_MAX_NAME );

        pTxTimer->tx_timer_id = OSA_UNINITIALIZED_TIMER ;
        snprintf( pTxTimer->tx_timer_name, TX_MAX_NAME, "Timer-%d", ++objectCnt ) ;
        status = OS_SUCCESS ;
		pTxTimer->tx_app_reserved = 1;
    }
	else
    {
		MALLOC( char *, pName, TX_MAX_NAME );
		if ( pParams->name ){
			strncpy(pName, pParams->name, TX_MAX_NAME-1) ;
			pName[TX_MAX_NAME-1] = '\0';
		}
        else
        {
            snprintf( pName, TX_MAX_NAME, "Timer-%d", ++objectCnt ) ;
        }

		status = tx_timer_create( pTxTimer, pName, (void(*)(ULONG))pParams->callBackRoutine,
									pParams->timerArgc, pParams->initialTime, pParams->rescheduleTime, TX_NO_ACTIVATE ) ;
    }

	*pOsaRef = OsaRef ;

    RETURN_STATUS( status, TX_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaTimerDelete
 *
 * Description: Delete timer.
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
OSA_STATUS OsaTimerDelete( OsaRefT OsaRef, void *pForFutureUse )
{
    TX_TIMER
        *pTxTimer = (TX_TIMER *)OsaRef ;

    UINT
        status,
		cpsr;

    OSA_ASSERT(OsaRef) ;

    if ( pTxTimer->tx_timer_id== OSA_UNINITIALIZED_TIMER )
    {
    	OsaMemFree(pTxTimer->tx_timer_name); //TODO: Pijing Liu
    	pTxTimer->tx_timer_id = 0 ;
        status = TX_SUCCESS ;
    }else{
		//ThreadX timers cannot delete itself or other timers in its entry function
    	if(_tx_thread_current_ptr == &_tx_timer_thread){
			OSA_ASSERT(delTimerTail);

			cpsr = disableInterrupts();

			if(delTimerTail->delete_timer == NULL){
				delTimerTail->delete_timer = OsaRef;
				delTimerTail->next_deleted_timer = NULL;
				delTimerTail->previous_deleted_timer = NULL;
			}else{//barely run to here
				OSA_ASSERT(delTimerTail->next_deleted_timer == NULL);

				MALLOC_REF( delTimerTail->next_deleted_timer, sizeof(DelTimer) ) ;

				delTimerTail->next_deleted_timer->delete_timer = OsaRef;
				delTimerTail->next_deleted_timer->next_deleted_timer = NULL;
				delTimerTail->next_deleted_timer->previous_deleted_timer = delTimerTail;
				delTimerTail = delTimerTail->next_deleted_timer;
			}

			restoreInterrupts(cpsr);

			OsaTimerStop(OsaRef, NULL);

			if(TimerDeleteTaskRef.tx_thread_state == TX_SUSPENDED){
				status = tx_thread_resume(&TimerDeleteTaskRef);
				RETURN_STATUS( status, TX_SUCCESS ) ;
			}else if(delTimerTaskDone){
				/*TimerDeleteTaskRef is still running and it just finish processing the deleted timer list.
				   As a new Timer is attached to the list, need the task to re-process the deleted timer list .*/

				delTimerTaskDone = FALSE;
				status = tx_thread_terminate(&TimerDeleteTaskRef);
				if(status)
					RETURN_STATUS( status, TX_SUCCESS ) ;
				status = tx_thread_reset(&TimerDeleteTaskRef);
				if(status)
					RETURN_STATUS( status, TX_SUCCESS ) ;
				status = tx_thread_resume(&TimerDeleteTaskRef);
				RETURN_STATUS( status, TX_SUCCESS ) ;
			}else{
				return TX_SUCCESS;
			}

    	}

		OsaMemFree(pTxTimer->tx_timer_name);
		status = tx_timer_delete( (TX_TIMER *)OsaRef ) ;
    }

    FREE_REF_AND_RETURN_STATUS( status, OsaRef, TX_TIMER ) ;
}

/***********************************************************************
 *
 * Name:        TimerDeleteTask
 *
 * Description: Delete timer which cannot be delted in system timer thread.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *
 * Returns:
 *
 *
 * Notes:
 *
 ***********************************************************************/

void TimerDeleteTask(ULONG argv){

	OsaRefT
		*pDelTimer = NULL;

	UINT32
		status,
		cpsr;


	while(1){

		delTimerTaskDone = FALSE;

		//if there is no timer need to delete, this task should never be resumed.
		OSA_ASSERT(delTimerTail->delete_timer);

		//work through the list to delete all pending Timers.
		while(1){

			cpsr = disableInterrupts();

			//it may has new timers attached to the list between restoreInterrupts() and OsaTimerDelete()
			if(delTimerTail->delete_timer == NULL){
				delTimerTaskDone = TRUE;
				break;
			}

			if(delTimerTail->previous_deleted_timer == NULL){
				//only one timer need  to be deleted
				pDelTimer = delTimerTail->delete_timer;
				delTimerTail->delete_timer = NULL;
			}else{//barely run to here
				pDelTimer = delTimerTail->delete_timer;
				delTimerTail->delete_timer = NULL;
				delTimerTail = delTimerTail->previous_deleted_timer;
				OsaMemFree(delTimerTail->next_deleted_timer);
				delTimerTail->next_deleted_timer = NULL;
			}

			restoreInterrupts(cpsr);


			OsaTimerDelete(pDelTimer, NULL);

		}



		status = tx_thread_suspend(&TimerDeleteTaskRef);
		if(status != TX_SUCCESS)
			OSA_ASSERT(0);

	}
}


/***********************************************************************
 *
 * Name:        OsaPartitionPoolCreate
 *
 * Description: Create Partition Pool.
 *
 * Parameters:
 *
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/

OSA_STATUS OsaPartitionPoolCreate(OsaRefT *pOsaRef, char *pool_name,
							void *start_address, UINT32 pool_size,
							UINT32 partition_size, UINT32 suspend_type){

	OsaRefT
        OsaRef ;

	TX_BLOCK_POOL
		*pTxBlockPool;

	UINT
		status;

	char
		*name;

	OSA_ASSERT(pOsaRef) ;

	MALLOC_REF(OsaRef, sizeof(TX_BLOCK_POOL));
	pTxBlockPool = (TX_BLOCK_POOL *)OsaRef;

	MALLOC(char *, name, TX_MAX_NAME);
	strncpy(name, pool_name, TX_MAX_NAME);
	name[TX_MAX_NAME-1] = '\0';

	if(suspend_type == OS_PRIORITY)
		pTxBlockPool->tx_block_pool_reserved = OS_PRIORITY;

	status = tx_block_pool_create(pTxBlockPool, name, partition_size, start_address, pool_size);

	*pOsaRef = OsaRef;


	if(status){
		//Pijing Liu debug
		uart_printf("pjliu: FILE: %s, LINE:%d, FUNC:%s, status = 0x%x~~~~~~~~~~~~~~~~~~~~~~\r\n", __FILE__,__LINE__, __FUNCTION__, status);
	}
//	RETURN_STATUS( status, TX_SUCCESS ) ;
	return status; //PS will check this return value by themselves
}


/***********************************************************************
 *
 * Name:        Osa_TranslateErrorCode()
 *
 * Description: Translate Nucleus Error Code to OSA format.
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
static const struct
{
    BOOL        Assert ;
    STATUS      ErrorCode ;
    OSA_STATUS  OsaStatus ;
}
OsaErrTable[] =
{
	{   TRUE    ,   TX_DELETED                	  	,   OS_DELETED          },
	{   TRUE    ,   TX_SEMAPHORE_DELETED            ,   OS_SEM_DELETED      },
	{   TRUE    ,   TX_MSGQ_DELETED                 ,   OS_MSGQ_DELETED     },
	{   TRUE    ,   TX_MUTEX_DELETED                ,   OS_MUTEX_DELETED     },
	{   TRUE    ,   TX_NO_MEMORY                  	,   OS_NO_MEMORY        },
	{	TRUE	,	TX_POOL_ERROR				  	,   OS_INVALID_REF	  	},
	{	TRUE	,	TX_PTR_ERROR				  	,   OS_INVALID_POINTER  },
	{	TRUE	,	TX_WAIT_ERROR				  	,   OS_INVALID_MODE	  	},
	{	TRUE	,	TX_SIZE_ERROR				  	,   OS_INVALID_SIZE	  	},
	{   FALSE   ,   TX_GROUP_ERROR                	,   OS_INVALID_REF      }, //TODO: exist a invalid flag ref
	{	FALSE	,	TX_NO_EVENTS				  	,   OS_UNAVAILABLE	  	},
	{	TRUE	,	TX_OPTION_ERROR 		   	  	,   OS_INVALID_MODE	   	},
	{	TRUE	,	TX_QUEUE_ERROR				  	,   OS_INVALID_REF	  	},
	{	FALSE	,	TX_QUEUE_EMPTY				  	,	OS_QUEUE_EMPTY		},
	{	FALSE	,	TX_QUEUE_FULL				  	,	OS_QUEUE_FULL		},
	{	TRUE	,	TX_SEMAPHORE_ERROR			  	,   OS_INVALID_REF	  	},
	{	FALSE	,	TX_NO_INSTANCE				  	,	OS_UNAVAILABLE		},
    {   TRUE    ,   TX_THREAD_ERROR                 ,   OS_INVALID_REF      },
    {   TRUE    ,   TX_PRIORITY_ERROR             	,   OS_INVALID_PRIORITY },
	{	TRUE	,	TX_START_ERROR				  	,   OS_INVALID_PARM	  	},
	{	TRUE	,	TX_DELETE_ERROR 			  	,   OS_FAIL			  	},
	{	TRUE	,	TX_RESUME_ERROR 			  	,   OS_FAIL			  	},
	{   TRUE	,   TX_CALLER_ERROR					,	OS_FAIL			  	},
    {   FALSE   ,   TX_SUSPEND_ERROR              	,   OS_INVALID_MODE     },
	{   TRUE	,   TX_TIMER_ERROR					,	OS_INVALID_REF		},
	{	TRUE	,   TX_TICK_ERROR					,	OS_INVALID_PARM		},
	{	TRUE	,	TX_ACTIVATE_ERROR				,	OS_INVALID_PARM		},
	{	TRUE	,	TX_THRESH_ERROR					,	OS_INVALID_PARM		},
    {	FALSE	,	TX_SUSPEND_LIFTED 				,	OS_INVALID_PARM		},	//Mutex
//	{	FALSE	,	TX_WAIT_ABORTED				,							//Mutex
	{	TRUE	,	TX_WAIT_ABORT_ERROR				,	OS_INVALID_REF		},	//Mutex
    {   TRUE    ,   TX_MUTEX_ERROR                	,   OS_INVALID_REF      },
	{	FALSE	,	TX_NOT_AVAILABLE			  	,   OS_UNAVAILABLE	  	},
	{	TRUE	,	TX_NOT_OWNED 					,	OS_INVALID_REF		},	//Mutex
	{	TRUE	,	TX_INHERIT_ERROR				,	OS_INVALID_PARM     },	//Mutex
	{	FALSE	,	TX_TIMEOUT				        ,	OS_TIMEOUT          },
//	{	TRUE	,	TX_NOT_DONE					,
//	{	TRUE	,	TX_CEILING_EXCEEDED			,
//	{	TRUE	,	TX_INVALID_CEILING				,
//	{	TRUE	,	TX_FEATURE_NOT_ENABLED			,
} ;

#define     MAX_ERROR_CODES     (sizeof(OsaErrTable) / sizeof(OsaErrTable[0]))

volatile UINT32 OsaErrGlobal_TX_ErrorCode;
volatile UINT32 OsaErrGlobal_OS_ErrorCode;


BOOL Osa_TranslateErrorCode( char *callerFuncName, UINT ErrorCode, OSA_STATUS *pOsaStatus )
{
    UINT32      i;
    platformOsaErrBehavior_ts    osaErrBehavior;

    OsaErrGlobal_TX_ErrorCode = ErrorCode;

    for( i=0 ; i<MAX_ERROR_CODES-1 ; i++ )
        if ( OsaErrTable[i].ErrorCode == ErrorCode )
            break ;

    *pOsaStatus = OsaErrTable[i].OsaStatus ;

    if ( OsaErrTable[i].Assert == FALSE )
        return FALSE ;

	    //======== Handle real problem ==============
    //Keep into Global buffer for debug possibilities
    OsaErrGlobal_OS_ErrorCode = OsaErrTable[i].OsaStatus;

    DIAG_FILTER( OSA, OSA_TX, TX_ERR0, DIAG_ERROR )
    diagPrintf( "OSA ASSERT: ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");
    DIAG_FILTER( OSA, OSA_TX, TX_ERR,  DIAG_ERROR )
    diagPrintf( "OSA ASSERT: ErrCode ThreadX = %ld, OSA =%ld called by %s", ErrorCode, *pOsaStatus, callerFuncName);
    DIAG_FILTER( OSA, OSA_TX, TX_ERR1, DIAG_ERROR )
    diagPrintf( "OSA ASSERT: ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");

    //ErrorLogPrintf( "OSA ASSERT: ErrCode ThreadX = %ld, OSA =%ld called by %s", ErrorCode, *pOsaStatus, callerFuncName);

    // OSA_ERROR_DEFAULT, OSA_ERROR_ASSERT, OSA_ERROR_IGNORE, OSA_ERROR_RESTORE_OK

    if(p_PlatformNvm->OsaErrBehavior == OSA_ERROR_DEFAULT)
    {
      #if defined(FLAVOR_APP) && !defined(FLAVOR_COM)
        osaErrBehavior = OSA_ERROR_RESTORE_OK;     /*Do not assert at all the APPS subsystem in APPS/COMM system*/
      #else
        osaErrBehavior = OSA_ERROR_ASSERT;
      #endif
    }
    else
        osaErrBehavior = p_PlatformNvm->OsaErrBehavior;


    if ( osaErrBehavior == OSA_ERROR_ASSERT )
    {
		if(	(*pOsaStatus == OS_SEM_DELETED)||
           	(*pOsaStatus == OS_MSGQ_DELETED) ||
            (*pOsaStatus == OS_MUTEX_DELETED) ||
           	(*pOsaStatus == OS_DELETED))
			return FALSE;
		else
        	return TRUE ;
    }

    if ( osaErrBehavior == OSA_ERROR_RESTORE_OK )
        *pOsaStatus = OS_SUCCESS ;

    return FALSE ;
}

UINT32 OsaTaskStackMagic(void)
{
	return TX_STACK_FILL;
}


