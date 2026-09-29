/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : osa_nu_run.c
Description : Nucleus PLUS operating system specific code
              for the OS Abstraction Layer API.
              This file contains the functions that are usualy used during the run phase.
              The split into 2 files (this and os_nu_run.c) is done to be able to located
              only the "run" functions in a faster memory.

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
#include "UART.h"
#include "utilities.h"

#define DEBUG_PRINT_CONTROL  0

/*
 * Externals.
 */
extern kstat_t krhino_mpatn_alloc(mblk_pool_t *pool, void **blk);
extern kstat_t krhino_mpatn_free(void *blk);
extern uint32_t krhino_mpatn_used_space(mblk_pool_t *pool);

extern UINT32 EEHandlerFlag;

/*
 * Static Data.
 */
static struct
{
    UINT32  counter ;
    UINT32  interrupt_mask ;
}
    Osa_OrigContext ;

/***********************************************************************
 *
 * Name:        Osa_Init
 *
 * Description: Init Package
 *
 * Parameters:
 *
 * Returns:
 *
 * Notes:
 *
 ***********************************************************************/
void Osa_Init( void )
{
    memset( &Osa_OrigContext, 0, sizeof(Osa_OrigContext) ) ;
}


/***********************************************************************
 *
 * Name:        OsaTick
 *
 * Description: Tick the OS.
 *
 * Parameters:
 *
 * Returns:
 *
 * Notes:
 *
 ***********************************************************************/
UINT32 get_aos_timer_count()
{
	UINT32 delta = 0xffffffffUL;
	klist_t  *tick_head_ptr = &g_tick_head;
	klist_t  *iter;
    ktask_t  *p_tcb;

	CPSR_ALLOC();
	RHINO_CPU_INTRPT_DISABLE();

    iter          =  tick_head_ptr->next;

    if (iter != tick_head_ptr) {
        p_tcb     = krhino_list_entry(iter, ktask_t, tick_list);
        delta = (tick_i_t)p_tcb->tick_match - (tick_i_t)g_tick_count;
    }

	RHINO_CPU_INTRPT_ENABLE();

	return delta;
}

void OsaTick( void *pForFutureUse )
{
    krhino_tick_proc() ;
}

void OsaTickUpdate(UINT32 ticks)
{
	extern void tick_list_update(tick_i_t ticks);
	tick_list_update(ticks);
}

UINT32 OsaTickSuspend()
{
	return get_aos_timer_count();
}

/***********************************************************************
 *
 * Name:        OsaGetTicks
 *
 * Description: Number of ticks that passed since last reset.
 *
 * Parameters:
 *
 * Returns:
 *
 * Notes:
 *
 ***********************************************************************/
UINT32 OsaGetTicks( void *pForFutureUse )
{
    return (UINT32)krhino_sys_tick_get() ;
}

/***********************************************************************
 *
 * Name:        OsaTaskYield
 *
 * Description: Allow other task to run.
 *
 * Parameters:
 *
 * Returns:
 *
 * Notes:
 *
 ***********************************************************************/
void OsaTaskYield( void *pForFutureUse )
{
	krhino_task_yield();
}

/***********************************************************************
 *
 * Name:        OsaSemaphoreAcquire
 *
 * Description: Acquire semaphore.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *  UINT32                  timeout         [IN]    Timeout in OS Ticks.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
#pragma arm section code="OSA_SEMA"

OSA_STATUS OsaSemaphoreAcquire( OsaRefT OsaRef, UINT32 timeout, void *pForFutureUse )
{
    UINT32
        status ;

    OsaSemaphoreT
        *pSemRef = (OsaSemaphoreT *)OsaRef ;

	if(1 == EEHandlerFlag)
	{
		return OS_SUCCESS;
	}

    OSA_ASSERT(pSemRef) ;

	status = krhino_sem_take( &(pSemRef->sem), Osa_TimeoutValueEx(timeout) );

    RETURN_STATUS( status, RHINO_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaSemaphoreCheck
 *
 * Description: Check whether semaphore is valid or not.
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
OSA_STATUS OsaSemaphoreCheck( OsaRefT OsaRef)
{
    OsaSemaphoreT
        *pSemRef = (OsaSemaphoreT *)OsaRef ;

    if(pSemRef && (pSemRef->sem.blk_obj.obj_type == RHINO_SEM_OBJ_TYPE))
    {
        return OS_SUCCESS;
    }
    else
    {
        return OS_INVALID_REF;
    }
}


/***********************************************************************
 *
 * Name:        OsaSemaphoreReleaseEx
 *
 * Description: Release semaphore.
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
OSA_STATUS OsaSemaphoreReleaseEx( OsaRefT OsaRef, void *pForFutureUse )
{
    return OsaSemaphoreRelease(OsaRef, pForFutureUse);
}


/***********************************************************************
 *
 * Name:        OsaSemaphoreRelease
 *
 * Description: Release semaphore.
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
OSA_STATUS OsaSemaphoreRelease( OsaRefT OsaRef, void *pForFutureUse )
{
    OsaSemaphoreT
        *pSemRef = (OsaSemaphoreT *)OsaRef ;

	if(EEHandlerFlag == 1)
	{
		return OS_SUCCESS;
	}

    OSA_ASSERT(pSemRef) ;

    RETURN_STATUS( krhino_sem_give(&pSemRef->sem), RHINO_SUCCESS ) ;
}
#pragma arm section code

/***********************************************************************
 *
 * Name:        OsaMutexLock
 *
 * Description:
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *  UINT32                  timeout         [IN]    Timeout in OS Ticks.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
#pragma arm section code="OSA_MUTEX"

OSA_STATUS OsaMutexLock( OsaRefT OsaRef, UINT32 timeout, void *pForFutureUse )
{
	OsaMutexT
		*pMutexRef = (OsaMutexT *)OsaRef ;
	UINT32
        status ;

	if(EEHandlerFlag == 1)
	{
		return OS_SUCCESS;
	}

	OSA_ASSERT(pMutexRef) ;

    status = krhino_mutex_lock( &pMutexRef->mutex, Osa_TimeoutValueEx(timeout) ) ;
	RETURN_STATUS( status, RHINO_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaMutexUnlock
 *
 * Description: No Mutex in Nucleus so do Semaphore.
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

OSA_STATUS OsaMutexUnlock( OsaRefT OsaRef, void *pForFutureUse )
{
    OsaMutexT
		*pMutexRef = (OsaMutexT *)OsaRef ;
	UINT32
        status ;

	if(EEHandlerFlag == 1)
	{
		return OS_SUCCESS;
	}

	OSA_ASSERT(pMutexRef) ;

    status = krhino_mutex_unlock( &pMutexRef->mutex ) ;
	RETURN_STATUS( status, RHINO_SUCCESS ) ;
}


#pragma arm section code

/***********************************************************************
 *
 * Name:        OsaIsrNotify
 *
 * Description: Activate HISR.
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
OSA_STATUS OsaIsrNotify( OsaRefT OsaRef, void *pForFutureUse )
{
    STATUS
        status ;

    OsaIsrT
        *pIsrRef = (OsaIsrT *)OsaRef ;

    OSA_ASSERT(pIsrRef) ;

	status = _ali_hisr_activate( &pIsrRef->hisrRef );

    RETURN_STATUS( status, RHINO_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaCriticalSectionEnter
 *
 * Description: Enter into a critical section.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *
 * Returns:
 *  OsaRefT                 *pOsaRef        [OT]    Reference.
 *
 * Notes:
 *
 ***********************************************************************/
OsaRefT OsaCriticalSectionEnter( OsaRefT OsaRef, void *pForFutureUse )
{

	return (OsaRefT)disableInterrupts();	// this function only modify I&F bit
}

/***********************************************************************
 *
 * Name:        OsaCriticalSectionExit
 *
 * Description: Exit from a critical section.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *
 * Returns:
 *
 * Notes:
 *
 ***********************************************************************/
void OsaCriticalSectionExit( OsaRefT OsaRef, void *pForFutureUse )
{
    OSA_ASSERT( OsaRef != OSA_DUMMY_CRITICAL_SECTION_HANDLE ) ;

	restoreInterrupts( (UINT32)OsaRef );	//only restroe I&F bit
}


/***********************************************************************
 *
 * Name:        OsaContextLock
 *
 * Description: Lock context - No interrupts and no preemptions.
 *
 * Parameters:
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
#pragma arm section code="OSA_CONTEXT"
UINT32 OsaContextLock( void *pForFutureUse )
{
    UINT32
        status ;

	status = krhino_sched_disable();

    RETURN_STATUS( status, RHINO_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaContextRestore
 *
 * Description: Restore the context.
 *
 * Parameters:
 *
 * Returns:
 *
 * Notes:
 *
 ***********************************************************************/
UINT32 OsaContextRestore( void *pForFutureUse )
{
    UINT32
        status ;

	status = krhino_sched_enable();
	if(status == RHINO_SCHED_DISABLE)
	{
		return OS_SUCCESS;
	}

    RETURN_STATUS( status, RHINO_SUCCESS ) ;

}
#pragma arm section code
/***********************************************************************
 *
 * Name:        OsaMsgQSend
 *
 * Description: Send to message Q.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *  OsaMsgQSendParamsT      *pParams        [IN]    Input Parameters (see datatype for details).
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
#pragma arm section code="OSA_MSGQ"
OSA_STATUS OsaMsgQSend( OsaRefT OsaRef, OsaMsgQSendParamsT *pParams )
{
    UINT32
        status ;

	OsaMsgQT
		*pMsgQRef = (OsaMsgQT *)OsaRef;

    OSA_ASSERT(pParams && OsaRef) ;

	/* size unit is byte */
	status = krhino_buf_queue_send( &pMsgQRef->queue, (VOID *)pParams->msgPtr, pParams->size );
#if DEBUG_PRINT_CONTROL
	if(status != RHINO_SUCCESS)
	    uart_printf("OsaMsgQSend err=%d\n", status);
#endif
    RETURN_STATUS( status, RHINO_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaMsgQRecv
 *
 * Description: Recieve from message Q.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *  OsaMsgQRecvParamsT      *pParams        [IN]    Input Parameters (see datatype for details).
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaMsgQRecv( OsaRefT OsaRef, OsaMsgQRecvParamsT *pParams )
{
    UINT32
        status ;

	OsaMsgQT
		*pMsgQRef = (OsaMsgQT *)OsaRef;

    OSA_ASSERT(OsaRef && pParams) ;

	/* size unit is byte */
	status = krhino_buf_queue_recv( &pMsgQRef->queue, Osa_TimeoutValueEx(pParams->timeout),
									(VOID *)pParams->msgPtr, (size_t *)&pParams->size ) ;
#if DEBUG_PRINT_CONTROL
    if(status != RHINO_SUCCESS)
        uart_printf("OsaMsgQRecv err=%d\n", status);
#endif
    RETURN_STATUS( status, RHINO_SUCCESS ) ;
}
#pragma arm section code

/***********************************************************************
 *
 * Name:        OsaMailboxQSend
 *
 * Description: Write data to mailbox Q.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *  UINT32                  mboxData        [IN]    Data to put in mailbox.
 *  UINT32                  timeout         [IN]    timeout.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaMailboxQSend( OsaRefT OsaRef, UINT32 mboxData, UINT32 timeout, void *pForFutureUse )
{
	OsaMbQT
		*pMsgQRef = (OsaMbQT *)OsaRef;

	UINT32 status;

	OSA_ASSERT(OsaRef);

	/* AliOS queue does not support timeout. If queue is full, let it ASSERT */
	status = krhino_queue_back_send( &pMsgQRef->queue, (VOID *)mboxData ) ;
#if DEBUG_PRINT_CONTROL
    if(status != RHINO_SUCCESS)
        uart_printf("OsaMailboxQSend err=%d\n", status);
#endif
    RETURN_STATUS( status, RHINO_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaMailboxQRecv
 *
 * Description: Read from mailbox Q.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *  UINT32                  mboxData        [OT]    Data to put in mailbox.
 *  UINT32                  timeout         [IN]    timeout.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaMailboxQRecv( OsaRefT OsaRef, UINT32 *mboxData, UINT32 timeout, void *pForFutureUse )
{
	OsaMbQT
		*pMsgQRef = (OsaMbQT *)OsaRef;

    UINT32
		status;

	OSA_ASSERT(OsaRef && mboxData);
	status = krhino_queue_recv( &pMsgQRef->queue, Osa_TimeoutValueEx(timeout), (VOID *)mboxData );
#if DEBUG_PRINT_CONTROL
    if(status != RHINO_SUCCESS)
        uart_printf("OsaMailboxQRecv err=%d\n", status);
#endif
    RETURN_STATUS( status, RHINO_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaFlagSet
 *
 * Description: Set an event.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *  UINT32                  mask            [IN]    Flag mask.
 *  UINT32                  operation       [IN]    OSA_FLAG_AND, OSA_FLAG_OR.
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
#pragma arm section code="OSA_FLAG"
OSA_STATUS OsaFlagSet( OsaRefT OsaRef, UINT32 mask, UINT32 operation, void *pForFutureUse )
{
	OsaFlagT
		*pFlagRef = (OsaFlagT*)OsaRef;
	UINT32
		status;

	if(!OsaRef)
		return OS_INVALID_REF;

	status = krhino_event_set( &pFlagRef->event, (UINT32)mask, (UINT32)((operation == OSA_FLAG_AND) ? RHINO_AND : RHINO_OR) ) ;
#if DEBUG_PRINT_CONTROL
    if(status != RHINO_SUCCESS)
        uart_printf("OsaFlagSet err=%d\n", status);
#endif
    RETURN_STATUS( status, RHINO_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaFlagWait
 *
 * Description: Wait for event.
 *
 * Parameters:
 *  OsaRefT                 OsaRef          [IN]    Reference.
 *  OsaFlagWaitParamsT      *pParams        [IN]    Input Parameters (see datatype for details).
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaFlagWait( OsaRefT OsaRef, OsaFlagWaitParamsT *pParams )
{
	OsaFlagT
		*pFlagRef = (OsaFlagT*)OsaRef;

    UINT32
        Operation ;

    UINT32
        status ;

    if(!(OsaRef && pParams))
   		return OS_INVALID_REF;

    switch( pParams->operation )
    {
        case OSA_FLAG_OR_CLEAR:
            Operation = RHINO_OR_CLEAR;
            break;
        case OSA_FLAG_OR:
            Operation = RHINO_OR ;
            break;
        case OSA_FLAG_AND_CLEAR:
            Operation = RHINO_AND_CLEAR ;
            break;
        case OSA_FLAG_AND:
            Operation = RHINO_AND ;
            break;
        default:
            OSA_ASSERT(0) ;
            return OS_INVALID_PARM ;
    }

	status = krhino_event_get( &pFlagRef->event, (uint32_t)pParams->mask, Operation,
									(uint32_t *)pParams->flags, Osa_TimeoutValueEx(pParams->timeout) ) ;

#if DEBUG_PRINT_CONTROL
    if(status != RHINO_SUCCESS)
        uart_printf("OsaFlagWait err=%d\n", status);
#endif

    RETURN_STATUS( status, RHINO_SUCCESS ) ;
}
#pragma arm section code
static void alios_timer_callback(void*timer, void *arg)
{
	OsaTimerT
        *pTimer = (OsaTimerT *)arg ;

	OSA_ASSERT(pTimer) ;

	if( pTimer->callBackRoutine && pTimer->started )
	{
		rti_timer_switch_to((UINT32)pTimer->callBackRoutine, NULL, TIME_RECORD_TYPE);
		pTimer->callBackRoutine(pTimer->timerArgc);
	}
}


/***********************************************************************
 *
 * Name:        OsaTimerStart
 *
 * Description: Create a Timer if needed and activate it.
 *
 * Parameters:
 *  OsaRefT                     OsaRef      [IN]    Reference.
 *  OsaTimerParamsT             *pParams    [OP,IN] Input Parameters (see datatype for details).
 *
 * Returns:
 *  OSA_STATUS  OSA Complition Code.
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaTimerStart( OsaRefT OsaRef, OsaTimerParamsT *pParams )
{
    OsaTimerT
        *pTimer = (OsaTimerT *)OsaRef ;

    CHAR
        *pName ;

    UINT32
        status, cpsr ;

	CHAR
		newTimer = 0;

    OSA_ASSERT(OsaRef) ;
	OSA_ASSERT(pParams);

#define ALIOS_TIMER_AUTOSTART   1

	if( pTimer->initialTime != pParams->initialTime ||
		pTimer->rescheduleTime != pParams->rescheduleTime ||
		pTimer->callBackRoutine != pParams->callBackRoutine ||
		pTimer->timerArgc != pParams->timerArgc ) {

		newTimer = 1;
	}

	if( pTimer->timer ) {
		if( pTimer->started ) {
			pTimer->started = 0;
			status = krhino_timer_stop( pTimer->timer );
			OSA_ASSERT( status == RHINO_SUCCESS );
		}
		if( newTimer ) {
			status = krhino_timer_dyn_del( pTimer->timer ) ;
			RETURN_STATUS_ON_FAILURE( status, RHINO_SUCCESS ) ;
			pTimer->timer = NULL;
		}
	}

	cpsr = disableInterrupts();

	pTimer->initialTime = pParams->initialTime;
	pTimer->rescheduleTime = pParams->rescheduleTime;
	pTimer->callBackRoutine = pParams->callBackRoutine;
	pTimer->timerArgc = pParams->timerArgc;
	pTimer->started = 1;

	restoreInterrupts( cpsr );

	pName = (CHAR *)(pParams->name ? pParams->name : pTimer->name) ;
	if( pTimer->timer ) {
		status = krhino_timer_start( pTimer->timer );
	} else {

		/*
		 * NOTE: do NOT use krhino_timer_create() because OsaTimerDelete()
		 * will free ktimer_t before timer stop-command getting executed
		 * in timer_task
		 */
		status = krhino_timer_dyn_create( &pTimer->timer, pName, alios_timer_callback,
			pParams->initialTime, pParams->rescheduleTime, (void*)pTimer, ALIOS_TIMER_AUTOSTART);
	}
#if DEBUG_PRINT_CONTROL
    if(status != RHINO_SUCCESS)
        uart_printf("OsaTimerStart err=%d\n", status);
#endif
    RETURN_STATUS( status, RHINO_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaTimerStop
 *
 * Description: Stop timer.
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
OSA_STATUS OsaTimerStop( OsaRefT OsaRef, void *pForFutureUse )
{
    OsaTimerT
        *pTimer = (OsaTimerT *)OsaRef ;

    UINT32
        status = RHINO_SUCCESS, cpsr;

	OSA_ASSERT(OsaRef);

	if( pTimer->timer ) {

		cpsr = disableInterrupts();
		pTimer->started = 0;
		restoreInterrupts( cpsr );

		status = krhino_timer_stop( pTimer->timer );
		//OSA_ASSERT( status == RHINO_SUCCESS );
	}

#if DEBUG_PRINT_CONTROL
    if(status != RHINO_SUCCESS)
        uart_printf("OsaTimerStop err=%d\n", status);
#endif

    RETURN_STATUS( status, RHINO_SUCCESS ) ;
}


#pragma arm section code="OSA_MEM"
OSA_STATUS	OsaPartitionAllocate(OsaRefT *pOsaRef, void **return_pointer, UINT32 suspend){

	mblk_pool_t
		*pPool;

	UINT32
		status;

	OSA_ASSERT(pOsaRef && return_pointer);

	pPool = (mblk_pool_t *)(*pOsaRef);
	OSA_ASSERT(pPool);

	status = krhino_mpatn_alloc(pPool, return_pointer);

#if DEBUG_PRINT_CONTROL
    if(status != RHINO_SUCCESS)
        uart_printf("OsaPartitionAllocate err=%d\n", status);
#endif

	RETURN_STATUS( status, RHINO_SUCCESS ) ;
}


OSA_STATUS	OsaPartitionFree(OsaRefT OsaRef){
	void
		*pBlock = (void *)OsaRef;

	UINT32
		status;

	OSA_ASSERT(OsaRef);

	status = krhino_mpatn_free(pBlock);

#if DEBUG_PRINT_CONTROL
    if(status != RHINO_SUCCESS)
        uart_printf("OsaPartitionFree err=%d\n", status);
#endif

	RETURN_STATUS( status, RHINO_SUCCESS ) ;
}

UINT32 OsaPartitionGetPoolUsedCount(OsaRefT *OsaRef)
{
    OSA_ASSERT(OsaRef);
	return krhino_mpatn_used_space((mblk_pool_t*)OsaRef);
}

UINT32 OsaControlInterrupts( UINT32 mask, void *pForFutureUse )
{
	UINT32 cpsr_;

	__asm{MRS cpsr_, CPSR};

	mask = (mask & 0x3F) | (cpsr_ & (~0x3F));

	__asm{MSR CPSR_c, mask};

	return (cpsr_ & 0x3F);
}

#pragma arm section code




