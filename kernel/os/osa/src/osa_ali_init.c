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
#include "k_api.h"
#include "alios_hisr.h"
#include "osa.h"
#include "osa_ali.h"
#include "osa_internals.h"
#include "diag.h"
#include "UART.h"
#include "csw_mem.h"
#include "osa_mem.h"
#include "platform_nvm.h"
#include "utilities.h"

#define DEBUG_PRINT_CONTROL  0


/*
 * Defines.
 */
#define     MAX_SISR_PRIORITY       ((UINT32)OSA_SISR_MAX_PRIORITY)
#define     ALIOS_NO_TIME_SLICE      0
#define     ALIOS_AUTO_START         1
#define     ALIOS_NO_AUTO_START      0





/*
 * Macros.
 */
#define     MALLOC_REF(rEF,sIZE,callerAddress)      \
        {                                               \
            rEF = (OsaRefT)OsaMemAlloc( NULL, sIZE ) ;  \
            if ( rEF )                                  \
            {                                           \
                OsaMemSetUserParamsFast(rEF, (UINT32)OsaCurrentThreadRef(), callerAddress);   \
            }                                           \
            else                                        \
            {                                           \
                OSA_ASSERT(0) ;                         \
                return OS_NO_MEMORY ;                   \
            }                                           \
                                                        \
            memset( (void *)rEF, 0, sIZE ) ;            \
        }


#define     MALLOC(tYPE,pTR,sIZE, callerAddress)    \
        {                                               \
            pTR = (tYPE)OsaMemAlloc( NULL, sIZE ) ;     \
            if ( pTR )                                  \
            {                                           \
                OsaMemSetUserParamsFast(pTR, (UINT32)OsaCurrentThreadRef(), callerAddress);  \
            }                                           \
            else                                        \
            {                                           \
                OSA_ASSERT(0) ;                         \
                return OS_NO_MEMORY ;                   \
            }                                           \
        }


#define     FREE_REF_AND_RETURN_STATUS(sTATUS,rEF,tYPE) \
    {                                                   \
        RETURN_STATUS_ON_FAILURE(sTATUS, RHINO_SUCCESS) ;   \
                                                        \
        CacheCleanMemory( (void *)rEF, sizeof(tYPE) ) ; \
        OsaMemFree( (void *)rEF ) ;                     \
                                                        \
        return OS_SUCCESS ;                             \
    }    /*  Need to Clean Cache bucause of Nucleus *_id magic number. */

extern kstat_t krhino_mpatn_pool_init(mblk_pool_t *pool, const name_t *name,
                              void *pool_start, size_t blk_size, size_t pool_size);

extern UINT32 EEHandlerFlag;

/*
 * Static Data.
 */
static struct
{
    UINT32  *pMem ;
    UINT32  size ;
}
OsaIsr_SisrStacks[MAX_SISR_PRIORITY] ;


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
        i = MAX_SISR_PRIORITY - 1;

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

	krhino_init();

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


static OSA_STATUS OsaTaskCreate0( OsaRefT *pOsaRef, OsaTaskCreateParamsT *pParams , UINT8 AutoStart)
{
    CHAR
        *pName ;

	OsaTaskT
       *pTask ;

    UINT32
        priority,
        status ;

    UINT32
        size ;

    VOID
        *stackPtr ;

   	UINT32 callerAddress = __return_address();

    OSA_ASSERT(pOsaRef) ;
    OSA_ASSERT(pParams) ;

    priority = pParams->priority + 3; //priority 0-2 is used for HISR, so all of the thread's priority is plused by 3.

	MALLOC_REF( pTask, sizeof(OsaTaskT), callerAddress ) ;
	pTask->entry = (void*)(pParams->entry);
	pTask->entryParam = (UINT32)(pParams->argv);

	pTask->abs_task.aos_thread_id = ALI_THREAD_ID;

    size = pParams->stackSize ;

    if ( ! pParams->stackPtr )
    {
        MALLOC( VOID *, stackPtr, size, callerAddress ) ;
        pTask->allocatedStack = stackPtr;
    }
    else
    {
        stackPtr = (VOID *)(((UINT32)pParams->stackPtr + 3) & ~3) ;
        size -= (UINT32)((UINT32)stackPtr - (UINT32)pParams->stackPtr) ;
        pTask->allocatedStack = NULL;
    }

	MALLOC( char *, pName, TX_MAX_NAME, callerAddress );
    if ( pParams->name ){
        strncpy(pName, pParams->name, TX_MAX_NAME-1) ;
		pName[TX_MAX_NAME-1] = '\0';
    }
    else
    {
        OSA_ASSERT(0);
    }

    *pOsaRef = (OsaRefT)pTask;

	status = krhino_task_create(&(pTask->abs_task.hisr_task), pName, pParams->argv,
				priority, ALIOS_NO_TIME_SLICE, (VOID *)stackPtr,
				(UINT32)AOS_STACK_SIZE(size),  pParams->entry,
				AutoStart ? ALIOS_AUTO_START : ALIOS_NO_AUTO_START);
#if DEBUG_PRINT_CONTROL
    uart_printf("create task %s %d\n", pName, status);
#endif

    RETURN_STATUS( status, RHINO_SUCCESS ) ;
}



/***********************************************************************
 *
 * Name:        OsaTaskCreateEx
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
    return OsaTaskCreate0(pOsaRef, (OsaTaskCreateParamsT*)pParams, 0);
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
OSA_STATUS OsaTaskCreate( OsaRefT *pOsaRef, OsaTaskCreateParamsT *pParams )
{
    return OsaTaskCreate0(pOsaRef, (OsaTaskCreateParamsT*)pParams, 1);
}

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
	OsaTaskT
		*pTask = (OsaTaskT *)OsaRef;

    UINT32
		status;

	OSA_ASSERT(OsaRef);

	status = krhino_task_del(&(pTask->abs_task.hisr_task));
	if( status == RHINO_INV_TASK_STATE && pTask->abs_task.hisr_task.task_state == K_DELETED ) {
		/* AliOS's bug: if task has been deleted, it can not be deleted again */
		pTask->abs_task.aos_thread_id = 0;
		status = RHINO_SUCCESS;
	}

	OSA_ASSERT(status == RHINO_SUCCESS);
	OsaMemFree( (void*)(pTask->abs_task.hisr_task.task_name) ) ;
	if( pTask->allocatedStack ) {
	    OsaMemFree(pTask->allocatedStack);
	}

    FREE_REF_AND_RETURN_STATUS( status, OsaRef, OsaTaskT ) ;
}


OSA_STATUS OsaTaskTerminate( OsaRefT OsaRef, void *pForFutureUse )
{
    OsaTaskT
		*pTask = (OsaTaskT *)OsaRef;

    UINT32
		status;

	OSA_ASSERT(OsaRef);

	status = krhino_task_del(&(pTask->abs_task.hisr_task));
	if( status == RHINO_INV_TASK_STATE && pTask->abs_task.hisr_task.task_state == K_DELETED ) {
		/* AliOS's bug: if task has been deleted, it can not be deleted again */
		pTask->abs_task.aos_thread_id = 0;
		status = RHINO_SUCCESS;
	}

	RETURN_STATUS( status, RHINO_SUCCESS ) ;
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
    UINT32 status;
	UINT32 CallerAddress ;

	OSA_ASSERT( OsaRef );

#if defined(__ARMCC_VERSION)
	CallerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;  //  Keep first.
#else
	CallerAddress = 0;
#endif

    status = krhino_task_suspend( (ktask_t *)OsaRef ) ;

	if(status != RHINO_SUCCESS)
	{

		DIAG_FILTER( OSA, OSA_aliOS, OsaTaskSuspend_ERR, DIAG_ERROR )
		diagPrintf( "OsaTaskSuspend status %d by 0x%lx",status,CallerAddress);
		WARNING(0);
		return OS_FAIL;
	}

	return OS_SUCCESS;
    //RETURN_STATUS( status, RHINO_SUCCESS ) ;
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
    UINT32 status;
	UINT32 CallerAddress ;

	OSA_ASSERT( OsaRef );

#if defined(__ARMCC_VERSION)
	CallerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;  //  Keep first.
#else
	CallerAddress = 0;
#endif


    status = krhino_task_resume( (ktask_t *)OsaRef ) ;
	if(status != RHINO_SUCCESS)
	{

		DIAG_FILTER( OSA, OSA_aliOS, OsaTaskResume_ERR, DIAG_ERROR )
		diagPrintf( "OsaTaskResume status %d by 0x%lx",status,CallerAddress);
		WARNING(0);
		return OS_FAIL;
	}

	return OS_SUCCESS;

    //RETURN_STATUS( status, RHINO_SUCCESS ) ;
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
		return ;

	krhino_task_sleep(ticks);
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
	UINT32
		status;

	OSA_ASSERT(OsaRef);
    OSA_ASSERT(oldPriority) ;
	UINT8 newPriorityTX,oldPriorityTX;
	newPriorityTX = newPriority + 3;

	status = krhino_task_pri_change( (ktask_t *)OsaRef, newPriorityTX, &oldPriorityTX );

	*(oldPriority) = (UINT8)oldPriorityTX - 3;

    RETURN_STATUS( status, RHINO_SUCCESS ) ;
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
	ktask_t
		*pTask = (ktask_t*)OsaRef;

	OSA_ASSERT(OsaRef);
    OSA_ASSERT(pPriority) ;
    *pPriority = (UINT8)(pTask->b_prio - 3);

    return OS_SUCCESS ;
}

OSA_STATUS OsaHISRGetPriority( OsaRefT OsaRef, UINT8 *pPriority, void *pForFutureUse )
{
	OSA_ASSERT(OsaRef);
    OSA_ASSERT(pPriority) ;

	*pPriority = ((RHINO_HISR*)OsaRef)->abs_task.hisr_task.b_prio;

    return OS_SUCCESS ;
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

    OsaSemaphoreT
        *pSem ;

	blk_policy_t
		waitingMode = BLK_POLICY_FIFO;

    UINT32
        status ;

    UINT32
        initialCount = 1;


	OSA_ASSERT(pOsaRef) ;

/*
 * Set Parameters
 */
    if ( pParams )
    {
        initialCount = pParams->initialCount ;

        if ( pParams->waitingMode == OSA_FIFO )
           waitingMode = BLK_POLICY_FIFO ;
		else
		   waitingMode = BLK_POLICY_PRI;

    }

	/*
 * Create Semaphore
 */
    MALLOC_REF( pSem, sizeof(OsaSemaphoreT), callerAddress ) ;

    MALLOC( char *, pName, TX_MAX_NAME, callerAddress );
    if ( pParams && pParams->name ){
        strncpy(pName, pParams->name, TX_MAX_NAME-1) ;
		pName[TX_MAX_NAME-1] = '\0';
    }
    else
    {
        sprintf( pName, "Sem-%d", ++objectCnt ) ;
    }

	status = krhino_sem_create( &pSem->sem, pName, initialCount);

	/* TODO: ugly AliOS API can NOT set waiting mode. Hope AliOS to improve it */
	pSem->sem.blk_obj.blk_policy = waitingMode;

	*pOsaRef = pSem ;

    RETURN_STATUS( status, RHINO_SUCCESS ) ;//TODO:error table
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
    UINT32
        status ;

    OsaSemaphoreT
        *pSemRef = (OsaSemaphoreT *)OsaRef ;

    OSA_ASSERT(pSemRef) ;

    status = krhino_sem_del( &pSemRef->sem );

	OsaMemFree((void*)(pSemRef->sem.blk_obj.name));

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
	static UINT8
        objectCnt = 0 ;

	OsaMutexT
		*pMutex ;

    CHAR
        *pName ;

    UINT32
        status ;

	OSA_ASSERT(pOsaRef);

	MALLOC_REF( pMutex, sizeof(OsaMutexT), callerAddress ) ;

	MALLOC( char *, pName, TX_MAX_NAME, callerAddress );
	if ( pParams && pParams->name ){
		strncpy(pName, pParams->name, TX_MAX_NAME-1) ;
		pName[TX_MAX_NAME-1] = '\0';
	}
	else
	{
		sprintf( pName, "Mut-%d", ++objectCnt ) ;
	}

	status = krhino_mutex_create( &pMutex->mutex, pName );


	/* TODO: ugly AliOS API can NOT set waiting mode. Hope AliOS to improve it */
    if ( pParams )
    {
        if ( pParams->waitingMode == OSA_FIFO )
            pMutex->mutex.blk_obj.blk_policy = BLK_POLICY_FIFO ;
        else
            pMutex->mutex.blk_obj.blk_policy = BLK_POLICY_PRI ;
    }

	*pOsaRef = pMutex;

	RETURN_STATUS( status, RHINO_SUCCESS ) ;
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
    UINT32
        status ;

    OsaMutexT
        *pMutex = (OsaMutexT *)OsaRef ;

    OSA_ASSERT(pMutex) ;

    status = krhino_mutex_del( &pMutex->mutex );

	OsaMemFree((void*)(pMutex->mutex.blk_obj.name));

    FREE_REF_AND_RETURN_STATUS( status, OsaRef, OsaMutexT ) ;

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
    OsaRefT
        OsaRef ;

    OsaIsrT
        *pIsrRef ;

    UINT32
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
        UINT8
            priority = (UINT8)pParams->priority ;

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

		status = _ali_hisr_create( &pIsrRef->hisrRef, pParams->name, (VOID(*)(UINT32))pParams->sisrRoutine,
									0, priority);

    }

    else
        status = RHINO_SUCCESS ;

    *pOsaRef = OsaRef ;

    RETURN_STATUS( status, RHINO_SUCCESS ) ;
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
    UINT32
        status ;

    OsaIsrT
        *pIsrRef = (OsaIsrT *)OsaRef ;

    OSA_ASSERT(pIsrRef) ;

    if ( pIsrRef->fisrRoutine )
        INTCUnbind( (INTC_InterruptSources)pIsrRef->intSource ) ;

    if ( pIsrRef->sisrRoutine ){
		status = _ali_hisr_delete( &pIsrRef->hisrRef );
    }
    else
        status = OS_SUCCESS ;

    FREE_REF_AND_RETURN_STATUS( status, OsaRef, OsaIsrT ) ;
}
#endif


OSA_STATUS OsaHisrCreate(OsaRefT* hisr, CHAR* name, VOID (*hisr_entry)(VOID), unsigned char priority)
{
	OSA_STATUS status;
	OsaRefT  p;
	RHINO_HISR *_p;
	UINT32 callerAddress = __return_address();

	OSA_ASSERT(hisr);

	MALLOC_REF( p, sizeof(RHINO_HISR), callerAddress ) ;

	status =_ali_hisr_create((RHINO_HISR *)p, name, (void (*)(UINT32))hisr_entry, 0, priority);
	*hisr = p;

	_p = p;
	_p->abs_task.hisr_task.sys_info[AOS_KERNEL_SYS_INFO_KEY_HISR] = p;

	RETURN_STATUS( status, RHINO_SUCCESS ) ;
}


OSA_STATUS OsaHisrActivate(OsaRefT *hisr)
{
	OSA_STATUS status;

	OSA_ASSERT(hisr);
	status = _ali_hisr_activate((RHINO_HISR *)*hisr);
	RETURN_STATUS( status, RHINO_SUCCESS ) ;
}


OSA_STATUS OsaHisrDel(OsaRefT *hisr)
{
	OSA_STATUS status;
	RHINO_HISR *_p;

	OSA_ASSERT(*hisr) ;
	_p = (RHINO_HISR *)(*hisr);
	_p->abs_task.hisr_task.sys_info[AOS_KERNEL_SYS_INFO_KEY_HISR] = 0;

	status = _ali_hisr_delete((RHINO_HISR *)*hisr);

	OsaMemFree(*hisr);

	RETURN_STATUS( status, RHINO_SUCCESS ) ;
}


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

	OsaMsgQT
		*pMsgQ;

    UINT32
        status ;

    UINT32
        qSize  ;

    void
        *qAddr ;

    OSA_ASSERT(pOsaRef) ;
    OSA_ASSERT(pParams) ;

/*
 * Alloc Q.
 */
    qSize = pParams->maxSize * pParams->maxMsg;
    MALLOC( void *, qAddr, qSize, callerAddress ) ;

	MALLOC_REF( pMsgQ, sizeof(OsaMsgQT), callerAddress ) ;


/*
 * Prepare Parameters.
 */

    MALLOC( char *, pName, TX_MAX_NAME, callerAddress );
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
#if 0
    status = krhino_buf_queue_create( &pMsgQ->queue, pName, (VOID *)qAddr, qSize, pParams->maxSize);
#else
	status = krhino_fix_buf_queue_create( &pMsgQ->queue, pName, (VOID *)qAddr, pParams->maxSize, pParams->maxMsg);
#endif
	/* TODO: ugly AliOS API can NOT set waiting mode. Hope AliOS to improve it */
	if ( pParams )
	{
		if ( pParams->waitingMode == OSA_FIFO )
			pMsgQ->queue.blk_obj.blk_policy = BLK_POLICY_FIFO ;
		else
			pMsgQ->queue.blk_obj.blk_policy = BLK_POLICY_PRI ;
	}

	pMsgQ->buf = qAddr;
	pMsgQ->name = pName;
	pMsgQ->blockSize = pParams->maxSize;

    *pOsaRef = (OsaRefT)pMsgQ ;

    RETURN_STATUS( status, RHINO_SUCCESS ) ;
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

    UINT32
        status ;

    OSA_ASSERT(pMsgQRef) ;

	status = krhino_buf_queue_del( &pMsgQRef->queue ) ;

	OsaMemFree( pMsgQRef->name );
	OsaMemFree( pMsgQRef->buf );

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
	static UINT8 objectCnt = 0;

	CHAR
		*qAddr;

	CHAR
		*pName;

	OsaMbQT
		*pMbq;

	UINT32
        status ;

    UINT32 callerAddress = __return_address();

	OSA_ASSERT(pOsaRef);
    OSA_ASSERT(pParams);


	MALLOC_REF( pMbq, sizeof(OsaMbQT), callerAddress ) ;

    MALLOC( void *, qAddr,  pParams->maxMsg*sizeof(UINT32), callerAddress ) ;


	MALLOC( char *, pName, TX_MAX_NAME, callerAddress );
	if ( pParams->name ){
		strncpy(pName, pParams->name, TX_MAX_NAME-1) ;
		pName[TX_MAX_NAME-1] = '\0';
	}
	else
	{
		sprintf( pName, "MB-%d", ++objectCnt ) ;
	}

	pMbq->buf = qAddr;
	pMbq->name = pName;

	status = krhino_queue_create(&(pMbq->queue), pName, (void**)qAddr, pParams->maxMsg);


	/* TODO: ugly AliOS API can NOT set waiting mode. Hope AliOS to improve it */
	if ( pParams )
	{
		if ( pParams->waitingMode == OSA_FIFO )
			pMbq->queue.blk_obj.blk_policy = BLK_POLICY_FIFO ;
		else
			pMbq->queue.blk_obj.blk_policy = BLK_POLICY_PRI ;
	}

	*pOsaRef = (OsaRefT)pMbq;

	RETURN_STATUS( status, RHINO_SUCCESS ) ;
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
	OsaMbQT
		*pMbQRef = (OsaMbQT*)OsaRef;

	UINT32
        status ;

    OSA_ASSERT(pMbQRef) ;

	status = krhino_queue_del( &pMbQRef->queue ) ;

	OsaMemFree( pMbQRef->name );
	OsaMemFree( pMbQRef->buf );

    FREE_REF_AND_RETURN_STATUS( status, pMbQRef, OsaMbQT ) ;

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

    OsaFlagT
        *OsaRef ;

    UINT32
        status ;

	UINT32 callerAddress = __return_address();

    OSA_ASSERT(pOsaRef) ;

	MALLOC_REF( OsaRef, sizeof(OsaFlagT), callerAddress ) ;

	MALLOC( char *, pName, TX_MAX_NAME, callerAddress );
	if ( pParams && pParams->name ){
		strncpy(pName, pParams->name, TX_MAX_NAME-1) ;
		pName[TX_MAX_NAME-1] = '\0';
	}
	else
	{
		sprintf( pName, "Flag-%d", ++objectCnt ) ;
	}

	status = krhino_event_create( &OsaRef->event, pName, 0 );

    *pOsaRef = (OsaRefT)OsaRef ;

	RETURN_STATUS( status, RHINO_SUCCESS ) ;
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
    UINT32
		status;
	OsaFlagT
		*pOsaRef = (OsaFlagT *)OsaRef;

	OSA_ASSERT(OsaRef);

	OsaMemFree( (void*)(pOsaRef->event.blk_obj.name) );

	status = krhino_event_del( &pOsaRef->event );


    FREE_REF_AND_RETURN_STATUS( status, OsaRef, OsaFlagT ) ;
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

    OsaTimerT
        *pTxTimer ;

    UINT32
        status ;

    UINT32 callerAddress = __return_address();

    OSA_ASSERT(pOsaRef) ;

    MALLOC_REF( OsaRef, sizeof(OsaTimerT), callerAddress ) ;

	pTxTimer = OsaRef;

    if ( ! pParams )
    {
		MALLOC( char *, pName, TX_MAX_NAME, callerAddress );
        sprintf( pName, "Timer-%d", ++objectCnt ) ;

		pTxTimer->name = pName;
        status = OS_SUCCESS ;
    }
	else
    {
		OSA_ASSERT(0);  // should not be here
		status = OS_FAIL;
    }

	*pOsaRef = OsaRef ;

    RETURN_STATUS( status, OS_SUCCESS ) ;
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
    OsaTimerT
        *pTxTimer = (OsaTimerT *)OsaRef ;

    UINT32
        status = RHINO_SUCCESS;

    OSA_ASSERT(pTxTimer) ;

	if( pTxTimer->timer )
	{
		status = krhino_timer_stop( pTxTimer->timer ) ;
		OSA_ASSERT( status == RHINO_SUCCESS );
		status = krhino_timer_dyn_del( pTxTimer->timer ) ;
		OSA_ASSERT( status == RHINO_SUCCESS );
	}

	OsaMemFree((void*)(pTxTimer->name));
	pTxTimer->callBackRoutine = NULL;  /* to gurantee no side-effect */

	/* It is possible to cause exception in theory, since stop&del is carried by
	 * an async command which will by executed by timer_task of AliOS,
	 * and the OsaRef has been freed in below line
	 * and this timer get timeout at the same time */
    FREE_REF_AND_RETURN_STATUS( status, pTxTimer, OsaTimerT ) ;
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

	mblk_pool_t
		*pTxBlockPool;

	UINT32
		status;

	char
		*name;

	UINT32 callerAddress = __return_address();

	OSA_ASSERT(pOsaRef) ;
	OSA_ASSERT(pool_name);
	OSA_ASSERT(start_address);

	MALLOC_REF(OsaRef, sizeof(mblk_pool_t), callerAddress);
	pTxBlockPool = (mblk_pool_t *)OsaRef;

	MALLOC(char *, name, TX_MAX_NAME, callerAddress);
	strncpy(name, pool_name, TX_MAX_NAME);

	status = krhino_mpatn_pool_init(pTxBlockPool, name, start_address, partition_size, pool_size);

	*pOsaRef = OsaRef;

	RETURN_STATUS( status, RHINO_SUCCESS ) ;
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
	{	TRUE	, 	RHINO_SYS_FATAL_ERR				,	OS_FAIL				},
	{	TRUE	,	RHINO_SYS_SP_ERR				,	OS_INVALID_PTR 		},
	{	TRUE	,	RHINO_RUNNING					,   OS_SUCCESS			},
	{	TRUE	,	RHINO_STOPPED					,	OS_SUCCESS			},
	{	TRUE	,	RHINO_INV_PARAM					,	OS_INVALID_PARM 	},
	{	TRUE	,	RHINO_NULL_PTR					,	OS_INVALID_POINTER	},
	{	TRUE	,	RHINO_INV_ALIGN					,	OS_INVALID_MEMORY	},
	{	TRUE	,	RHINO_KOBJ_TYPE_ERR				,	OS_INVALID_PARM		},
	{	TRUE	,	RHINO_KOBJ_DEL_ERR				,   OS_INVALID_PARM		},
	{	TRUE	,	RHINO_KOBJ_DOCKER_EXIST			,   OS_INVALID_PARM		},
	{	TRUE	,	RHINO_KOBJ_BLK					,	OS_INVALID_PARM		},
	{	TRUE	,	RHINO_KOBJ_SET_FULL				,	OS_INVALID_PARM		},
	{	TRUE	,	RHINO_NOTIFY_FUNC_EXIST			,	OS_INVALID_PARM		},
	{	TRUE	,	RHINO_MM_POOL_SIZE_ERR			,	OS_INVALID_PARM		},
	{	TRUE	,	RHINO_MM_ALLOC_SIZE_ERR			,	OS_INVALID_PARM		},
	{	TRUE	,	RHINO_MM_FREE_ADDR_ERR			,   OS_INVALID_PARM		},
	{	TRUE	,	RHINO_MM_CORRUPT_ERR			,	OS_INVALID_PARM		},
	{	TRUE	,	RHINO_DYN_MEM_PROC_ERR			,   OS_INVALID_PARM		},
	{	TRUE	,	RHINO_NO_MEM					,	OS_NO_MEMORY		},
	{	TRUE	,	RHINO_RINGBUF_FULL				,   OS_NO_MEMORY		},
	{	TRUE	,	RHINO_RINGBUF_EMPTY				,   OS_SUCCESS			},
	{	TRUE	,	RHINO_SCHED_DISABLE				,	OS_SUCCESS			},
	{	TRUE	,	RHINO_SCHED_ALREADY_ENABLED		,	OS_SUCCESS			},
	{	TRUE	,	RHINO_SCHED_LOCK_COUNT_OVF		,	OS_NO_RESOURCES		},
	{	TRUE	,	RHINO_INV_SCHED_WAY				,	OS_INVALID_PARM		},
	{	TRUE	,	RHINO_TASK_INV_STACK_SIZE		,	OS_INVALID_PARM		},
	{	TRUE	,	RHINO_TASK_NOT_SUSPENDED		,   OS_SUCCESS			},
	{	TRUE	,	RHINO_TASK_DEL_NOT_ALLOWED		,	OS_UNSUPPORTED		},
	{	TRUE	,	RHINO_TASK_SUSPEND_NOT_ALLOWED	,	OS_UNSUPPORTED		},
	{	TRUE	,	RHINO_SUSPENDED_COUNT_OVF		,   OS_NO_RESOURCES		},
	{	TRUE	,	RHINO_BEYOND_MAX_PRI			,	OS_INVALID_PARM		},
	{	TRUE	,	RHINO_PRI_CHG_NOT_ALLOWED		,	OS_UNSUPPORTED		},
	{	TRUE	,	RHINO_INV_TASK_STATE			,   OS_INVALID_MODE		},
	{	TRUE	,	RHINO_IDLE_TASK_EXIST			,	OS_INVALID_PRIORITY	},
	{	FALSE	,	RHINO_NO_PEND_WAIT 				,   OS_QUEUE_EMPTY		},
	{	TRUE	,	RHINO_BLK_ABORT					,   OS_SUCCESS			},
	{	FALSE	,	RHINO_BLK_TIMEOUT				,	OS_TIMEOUT			},
	{	TRUE	,	RHINO_BLK_DEL					,   OS_DELETED			},
	{	TRUE	,	RHINO_BLK_INV_STATE				,   OS_INVALID_MODE		},
	{	TRUE	,	RHINO_BLK_POOL_SIZE_ERR			,   OS_INVALID_PARM		},
	{	TRUE	,	RHINO_TIMER_STATE_INV			,	OS_INVALID_MODE		},
	{	TRUE	,	RHINO_NO_THIS_EVENT_OPT			,	OS_INVALID_PARM		},
	{	TRUE	,	RHINO_BUF_QUEUE_INV_SIZE 		,	OS_INVALID_PARM		},
	{	TRUE	,	RHINO_BUF_QUEUE_SIZE_ZERO		,   OS_INVALID_PARM		},
	{	FALSE	,	RHINO_BUF_QUEUE_FULL			,	OS_QUEUE_FULL		},
	{	TRUE	,	RHINO_BUF_QUEUE_MSG_SIZE_OVERFLOW,	OS_INVALID_PARM		},
	{	FALSE	,	RHINO_QUEUE_FULL				,   OS_QUEUE_FULL		},
	{	TRUE	,	RHINO_QUEUE_NOT_FULL			,	OS_SUCCESS			},
	{	TRUE	,	RHINO_SEM_OVF					,	OS_INVALID_REF		},
	{	TRUE	,	RHINO_SEM_TASK_WAITING			,	OS_UNAVAILABLE		},
	{	TRUE	,	RHINO_MUTEX_NOT_RELEASED_BY_OWNER,	OS_INVALID_PARM		},
	{	FALSE	,	RHINO_MUTEX_OWNER_NESTED		,	OS_SUCCESS		},
	{	TRUE	,	RHINO_MUTEX_NESTED_OVF			,   OS_INVALID_MODE		},
	{	TRUE	,	RHINO_NOT_CALLED_BY_INTRPT		,	OS_UNSUPPORTED		},
	{	TRUE	,	RHINO_TRY_AGAIN					,	OS_SUCCESS			},
	{	TRUE	,	RHINO_WORKQUEUE_EXIST 			,	OS_UNSUPPORTED		},
	{	TRUE	,	RHINO_WORKQUEUE_NOT_EXIST		,   OS_SUCCESS			},
	{	TRUE	,	RHINO_WORKQUEUE_WORK_EXIST		,	OS_UNSUPPORTED		},
	{	TRUE	,	RHINO_WORKQUEUE_BUSY			,   OS_UNSUPPORTED		},
	{	TRUE	,	RHINO_WORKQUEUE_WORK_RUNNING	,	OS_UNSUPPORTED		},
	{	TRUE	,	RHINO_TASK_STACK_OVF			,	OS_INVALID_MEMORY	},
	{	TRUE	,	RHINO_INTRPT_STACK_OVF			,	OS_INVALID_MEMORY	},
} ;

#define     MAX_ERROR_CODES     (sizeof(OsaErrTable) / sizeof(OsaErrTable[0]))

volatile UINT32 OsaErrGlobal_TX_ErrorCode;
volatile UINT32 OsaErrGlobal_OS_ErrorCode;


BOOL Osa_TranslateErrorCode( char *callerFuncName, UINT32 ErrorCode, OSA_STATUS *pOsaStatus )
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
    diagPrintf( "OSA ASSERT: ErrCode AliOS = %ld, OSA =%ld called by %s", ErrorCode, *pOsaStatus, callerFuncName);
    DIAG_FILTER( OSA, OSA_TX, TX_ERR1, DIAG_ERROR )
    diagPrintf( "OSA ASSERT: ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~");

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
		if(*pOsaStatus == OS_DELETED)
			return FALSE;
		else
        	return TRUE ;


    if ( osaErrBehavior == OSA_ERROR_RESTORE_OK )
        *pOsaStatus = OS_SUCCESS ;

    return FALSE ;
}


UINT32 OsaTaskStackMagic(void)
{
	return RHINO_TASK_STACK_OVF_MAGIC;
}


