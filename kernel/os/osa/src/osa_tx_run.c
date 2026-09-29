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
#include "osa.h"
#include "osa_tx.h"
#include "osa_internals.h"
#include <tx_api.h>
#include <tx_sem.h>
#include <tx_thread.h>
#include "UART.h"
#include "utilities.h"
#include "tick_manager.h"

static volatile UINT32 tx_timer_debug[2];
static volatile UINT32 tx_semaphore_debug[2];
static volatile UINT32 tx_mutex_debug[2];
static volatile UINT32 tx_flag_debug[2];
static volatile UINT32 tx_msgq_debug[2];
extern UINT32 EEHandlerFlag;

/*
 * Externals.
 */
extern void _tx_timer_interrupt(void);
extern UINT16 _tx_timer_system_teleport(UINT32 leap_ticks);
extern UINT16 _tx_timer_nearest_count(VOID);

#define TX_TASK_PRIORITY_START		3
/*
 * Static Data.
 */
static struct
{
    UINT32  counter ;
    UINT32  interrupt_mask ;
    OPTION  task_mode ;
}
    Osa_OrigContext,Osa_OrigContextExt ;

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
	memset( &Osa_OrigContextExt, 0, sizeof(Osa_OrigContextExt) ) ;
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
void OsaTick( void *pForFutureUse )
{
    _tx_timer_interrupt() ;
}

#define MAX_MAX_SLEEP_CLOCK32K    (((MAX_TimeIn32KhzUnit/2) / TICK_INTERVAL_32KHZUNIT) * TICK_INTERVAL_32KHZUNIT)

static UINT32 OvershootTicks;  //static accumulator keeps value for correction between timers
							   //in case where we get here after the nearest timer should have expired, we do not want to
							   //simply call timer adjust with zero, because the next timer will move forward.
							   //for this case we will use the OvershootTicks to compensate for this next time.

UINT32 GetOvershootTicks(void)
{
	return OvershootTicks;
}

void ResetOvershootTicks(void)
{
	OvershootTicks = 0;
}

void OsaTickUpdate(UINT32 ticks)
{

	UINT32			TMD_Timer_Local;
	UINT32          status;

	TMD_Timer_Local = _tx_timer_nearest_count();
	if(TMD_Timer_Local < MAX_MAX_SLEEP_CLOCK32K/TICK_INTERVAL_32KHZUNIT)
	{
		// NUTickDeltaTicks - is number of ticks to report to NU, since we will call timer-interupt immediately
		// it will increment the sys-ticks and decrement the NU-timer-counter so we only update by (NUTickDeltaTicks-1)
		if( TMD_Timer_Local > (OvershootTicks + (ticks-1) )	)
		{
			status = _tx_timer_system_teleport(OvershootTicks + (ticks));
			ASSERT(status == OS_SUCCESS);
			OvershootTicks = 0;
		}
		else
		{
			OvershootTicks = OvershootTicks + ticks - TMD_Timer_Local;
			status = _tx_timer_system_teleport(TMD_Timer_Local);
			ASSERT(status == OS_SUCCESS);
		}

		// update system tick
		tx_time_set(tx_time_get() + (ticks-1));

		// by calling timer-interrupt, it will increment the ticks by +1 !
		_tx_timer_interrupt();
	}
	else
	{
		 //no timer active is impossible
		 //ASSERT(0); //removed since it was just for debug use.
		 // we update the system clock even if currently no timers active
		 tx_time_set(tx_time_get() + ticks);
	}

}

UINT32 OsaTickSuspend(void)
{
	return _tx_timer_nearest_count();
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
    return (UINT32)tx_time_get() ;
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
	tx_thread_relinquish();
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
    UINT
        status ;

    OsaSemaphoreT
        *pSemRef = (OsaSemaphoreT *)OsaRef ;

    OSA_ASSERT(pSemRef) ;

	if(EEHandlerFlag)
	{
        return OS_SUCCESS;
	}

    tx_semaphore_debug[0] = (UINT32)pSemRef;
    tx_semaphore_debug[1] = (UINT32)__return_address();

	status = tx_semaphore_get( &(pSemRef->TxRef), Osa_TimeoutValue(timeout) );
#ifndef PLAT_USE_ALIOS
    if(status == TX_SUCCESS)
    {
        pSemRef->reserved = (UINT)OsaCurrentThreadRef();
    }
#endif

    RETURN_STATUS( status, TX_SUCCESS ) ;
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

    if(pSemRef && (pSemRef->TxRef.tx_semaphore_id == TX_SEMAPHORE_ID))
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

    UINT
        status ;

    OSA_ASSERT(pSemRef) ;

    if(EEHandlerFlag)
	{
        return OS_SUCCESS;
	}

	tx_semaphore_debug[0] = (UINT32)pSemRef;
    tx_semaphore_debug[1] = (UINT32)__return_address();

    if ( pSemRef->TxRef.tx_semaphore_count < pSemRef->maximumCount ){	//Pijing Liu debug
//	if(1){		//Pijing Liu debug  //TODO: We don't know why OSA set maximumCount, but this limit may cause KiOsTick assert which uses NU OS API directly.
    	if( pSemRef->waitingMode == OSA_PRIORITY ){
			status = tx_semaphore_prioritize(&pSemRef->TxRef);
			if(status != TX_SUCCESS)
				RETURN_STATUS( status, TX_SUCCESS ) ;
		}
        status = tx_semaphore_put(&pSemRef->TxRef);
    }
    else
    {

        ASSERT_EXT(0, "Semaphore 0x%x reach the max Count", OsaRef) ;             //  Shouldn't get here.
        return OS_FAIL ;
    }

    RETURN_STATUS( status, TX_SUCCESS ) ;
}

/***********************************************************************
 *
 * Name:        OsaSemaphoreReleaseExt
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
OSA_STATUS OsaSemaphoreReleaseExt( OsaRefT OsaRef, void *pForFutureUse )
{
    OsaSemaphoreT
        *pSemRef = (OsaSemaphoreT *)OsaRef ;

    UINT
        status ;

    OSA_ASSERT(pSemRef) ;

    if(EEHandlerFlag)
	{
        return OS_SUCCESS;
	}

	tx_semaphore_debug[0] = (UINT32)pSemRef;
    tx_semaphore_debug[1] = (UINT32)__return_address();

    if ( pSemRef->TxRef.tx_semaphore_count < pSemRef->maximumCount ){	//Pijing Liu debug
//	if(1){		//Pijing Liu debug  //TODO: We don't know why OSA set maximumCount, but this limit may cause KiOsTick assert which uses NU OS API directly.
    	if( pSemRef->waitingMode == OSA_PRIORITY ){
			status = tx_semaphore_prioritize(&pSemRef->TxRef);
			if(status != TX_SUCCESS)
				RETURN_STATUS( status, TX_SUCCESS ) ;
		}
        status = tx_semaphore_put(&pSemRef->TxRef);
    }
    else
    {
        return OS_FAIL ;
    }

    RETURN_STATUS( status, TX_SUCCESS ) ;
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

	if(EEHandlerFlag == 1)
	{
		return OS_SUCCESS;
	}

	tx_mutex_debug[0] = (UINT32)OsaRef;
    tx_mutex_debug[1] = (UINT32)__return_address();

	OSA_ASSERT(OsaRef) ;

	return OsaSemaphoreAcquire( OsaRef, timeout, pForFutureUse ) ;
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
	if(EEHandlerFlag == 1)
	{
		return OS_SUCCESS;
	}

    tx_mutex_debug[0] = (UINT32)OsaRef;
    tx_mutex_debug[1] = (UINT32)__return_address();

	OSA_ASSERT(OsaRef) ;

	return OsaSemaphoreRelease( OsaRef, pForFutureUse ) ;
}
#pragma arm section code


#if 0
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

	status = tx_hisr_activate( &pIsrRef->TxRef );

    RETURN_STATUS( status, TX_SUCCESS ) ;
}
#endif
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
 * Name:        OsaControlInterrupts
 *
 * Description: Mask / Unmask the processor's interrupts.
 *
 * Parameters:
 *  UINT32                  mask        [IN]    New interrupt mask.
 *
 * Returns:
 *  UINT32                  mask        [OT]    Old interrupt mask.
 *
 * Notes:
 *
 ***********************************************************************/
UINT32 OsaControlInterrupts( UINT32 mask, void *pForFutureUse )
{

	return (UINT32)_tx_thread_interrupt_control( mask );

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
        interrupt_mask ;

    UINT
		old_threashold;

	TX_THREAD
		*pTxRef;

    UINT    status = TX_SUCCESS ;

    if ( Osa_OrigContext.counter )
    {
        Osa_OrigContext.counter++ ;
        return OS_SUCCESS ;        //  Recursive call, no need to lock again.
    }

	interrupt_mask = disableInterrupts();

  	pTxRef = tx_thread_identify();
    if ( pTxRef )
		status = tx_thread_preemption_change(pTxRef, 0, &old_threashold);
	else
		old_threashold = 0 ;    //  Avoid warning.

	if(status != TX_SUCCESS)
	{
		ASSERT_EXT(0, "OsaContextLock status 0x%x", status);
	}

    Osa_OrigContext.counter = 1 ;
    Osa_OrigContext.task_mode = old_threashold ;
    Osa_OrigContext.interrupt_mask = interrupt_mask ;

    return OS_SUCCESS ;
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
        interrupt_mask = Osa_OrigContext.interrupt_mask ;
                            //  Save data incase we re-enter Lock function before we finish this one.
    UINT
        task_mode = Osa_OrigContext.task_mode,
        old_threashold;

	TX_THREAD
		*pTxRef;
	UINT    status = TX_SUCCESS ;

    if ( ! Osa_OrigContext.counter )
    {
        OSA_ASSERT( 0 ) ;       //  A call to OsaContextRestore without a previous call to OsaContextLock
        return OS_SUCCESS ;
    }

    if ( --Osa_OrigContext.counter )
    {
        return OS_SUCCESS ;                //  Not ready to restore context.
    }

    restoreInterrupts( interrupt_mask ) ;

	pTxRef = tx_thread_identify();
    if ( pTxRef )
    {
        status = tx_thread_preemption_change(pTxRef, task_mode, &old_threashold);
    }

	if(status != TX_SUCCESS)
	{
	    if(status == TX_THRESH_ERROR)
	    {
            if ( pTxRef )
            {
                status = _tx_thread_preemption_change(pTxRef, task_mode, &old_threashold);
            }
	    }

        if(status != TX_SUCCESS)
        {
		    ASSERT_EXT(0, "OsaContextRestore status 0x%x", status);
		}
	}

    return OS_SUCCESS ;
}

extern 	UINT32 OsaGetInterruptCount(void);
/***********************************************************************
 *
 * Name:        OsaContextLockExt
 *
 * Description: Lock specific context-only interrtup and HISR preemptions allowed.
 *
 * Parameters:
 *
 * Returns:
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaContextLockExt( void *pForFutureUse )
{
    UINT
		old_threashold;

	TX_THREAD
		*pTxRef;
	UINT32 cpsr;

  	pTxRef = tx_thread_identify();
	if(OsaGetInterruptCount() || (pTxRef->tx_thread_original_priority < TX_TASK_PRIORITY_START) )
	{
		return OS_FAIL ;
	}

	if ( Osa_OrigContextExt.counter )
	{
		ASSERT(Osa_OrigContextExt.interrupt_mask == (UINT32)pTxRef);
		Osa_OrigContextExt.counter++ ;
		return OS_SUCCESS ; 	   //  Recursive call, no need to lock again.
	}

	cpsr = disableInterrupts();

    if ( pTxRef  )
    {
		tx_thread_preemption_change(pTxRef, TX_TASK_PRIORITY_START, &old_threashold);
    }
	else
	{
		old_threashold = 0;
	}

	Osa_OrigContextExt.counter = 1 ;
   	Osa_OrigContextExt.task_mode = old_threashold ;
   	Osa_OrigContextExt.interrupt_mask = (UINT32)pTxRef ;

	restoreInterrupts( cpsr ) ;

    return OS_SUCCESS ;
}

/***********************************************************************
 *
 * Name:        OsaContextRestoreExt
 *
 * Description: Restore the specific context.
 *
 * Parameters:
 *
 * Returns:
 *
 * Notes:
 *
 ***********************************************************************/
OSA_STATUS OsaContextRestoreExt( void *pForFutureUse )
{
    UINT
        task_mode = Osa_OrigContextExt.task_mode,
        old_threashold;

	TX_THREAD
		*pTxRef;
	UINT32 cpsr;


	pTxRef = tx_thread_identify();
	if(OsaGetInterruptCount() || (pTxRef->tx_thread_original_priority < TX_TASK_PRIORITY_START))
	{
		return OS_FAIL ;
	}

	cpsr = disableInterrupts();
	ASSERT(	Osa_OrigContextExt.interrupt_mask == (UINT32)pTxRef);
	ASSERT(Osa_OrigContextExt.counter !=0 );

    if ( --Osa_OrigContextExt.counter )
    {
    	restoreInterrupts( cpsr ) ;
        return OS_SUCCESS ;                //  Not ready to restore context.
    }

    if ( pTxRef )
        tx_thread_preemption_change(pTxRef, task_mode, &old_threashold);

	restoreInterrupts( cpsr ) ;

    return OS_SUCCESS ;
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


    UINT
        status ;

	OsaMsgQT
		*pMsgQRef = (OsaMsgQT *)OsaRef;
#if 0
	UINT32 callerAddress ;

#if defined(__ARMCC_VERSION)
				callerAddress= (__ARMCC_VERSION >= 200000) ? __return_address() : 0 ;  //  Keep first.
#else
				callerAddress = 0;
#endif
#endif

    OSA_ASSERT(pParams) ;
	OSA_ASSERT(pMsgQRef) ;

	if(EEHandlerFlag != 1)
	{
		tx_msgq_debug[0] = (UINT32)OsaRef;
        tx_msgq_debug[1] = (UINT32)__return_address();
	}

	if(pMsgQRef->waitingMode == OSA_PRIORITY){
		status = tx_queue_prioritize((TX_QUEUE *)&pMsgQRef->TxRef);
		if(status != TX_SUCCESS)
			RETURN_STATUS( status, TX_SUCCESS ) ;
	}

	status = tx_queue_send( (TX_QUEUE *)&pMsgQRef->TxRef, (VOID *)pParams->msgPtr, Osa_TimeoutValue(pParams->timeout) );
//Pijing Liu debug
#if 0
	if(status != TX_SUCCESS){

		fatal_printf("%s: status = 0x%x, name: %s (caller : 0x%x)\r\n",
			__FUNCTION__,
			status,
			pMsgQRef ? pMsgQRef->TxRef.tx_queue_name:"NULL",
			callerAddress);
	}
#endif
    RETURN_STATUS( status, TX_SUCCESS ) ;
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
    UINT
        status ;

	OsaMsgQT
		*pMsgQRef = (OsaMsgQT *)OsaRef;

    OSA_ASSERT(pParams) ;
	OSA_ASSERT(pMsgQRef) ;

	if(EEHandlerFlag != 1)
	{
		tx_msgq_debug[0] = (UINT32)OsaRef;
        tx_msgq_debug[1] = (UINT32)__return_address();
	}

	status = tx_queue_receive( (TX_QUEUE *)&pMsgQRef->TxRef, (VOID *)pParams->msgPtr,
								Osa_TimeoutValue(pParams->timeout) ) ;

    RETURN_STATUS( status, TX_SUCCESS ) ;
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
	OsaMsgQT
		*pMsgQRef = (OsaMsgQT *)OsaRef;

	UINT status;
	OSA_ASSERT(pMsgQRef) ;

	if(EEHandlerFlag != 1)
	{
		tx_msgq_debug[0] = (UINT32)OsaRef;
        tx_msgq_debug[1] = (UINT32)__return_address();
	}

	if(pMsgQRef->waitingMode == OSA_PRIORITY){
		status = tx_queue_prioritize((TX_QUEUE *)&pMsgQRef->TxRef);
		if(status != TX_SUCCESS)
			RETURN_STATUS( status, TX_SUCCESS ) ;
	}

	status = tx_queue_send( (TX_QUEUE *)&pMsgQRef->TxRef, (VOID *)&mboxData, Osa_TimeoutValue(timeout) ) ;

    RETURN_STATUS( status, TX_SUCCESS ) ;
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
	OsaMsgQT
		*pMsgQRef = (OsaMsgQT *)OsaRef;

    UINT
		status ;

	OSA_ASSERT(pMsgQRef) ;

	if(EEHandlerFlag != 1)
	{
		tx_msgq_debug[0] = (UINT32)OsaRef;
        tx_msgq_debug[1] = (UINT32)__return_address();
	}

	status = tx_queue_receive( (TX_QUEUE *)&pMsgQRef->TxRef, (VOID *)mboxData, Osa_TimeoutValue(timeout) );

    RETURN_STATUS( status, TX_SUCCESS ) ;
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
	UINT
		status;

	if(EEHandlerFlag != 1)
	{
		tx_flag_debug[0] = (UINT32)OsaRef;
        tx_flag_debug[1] = (UINT32)__return_address();
	}

	status = tx_event_flags_set( (TX_EVENT_FLAGS_GROUP *)OsaRef, (ULONG)mask, (UINT)((operation == OSA_FLAG_AND) ? TX_AND : TX_OR) ) ;
//Pijing Liu debug
#if 0
	if(status != TX_SUCCESS){
		uart_printf("ERROR: %s: status = 0x%x\r\n", __FUNCTION__, status);
	}
#endif

    RETURN_STATUS( status, TX_SUCCESS ) ;
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
    UINT
        TxOperation ;

    UINT
        status ;

    OSA_ASSERT(pParams) ;

	if(EEHandlerFlag != 1)
	{
		tx_flag_debug[0] = (UINT32)OsaRef;
        tx_flag_debug[1] = (UINT32)__return_address();
	}

    switch( pParams->operation )
    {
        case OSA_FLAG_OR_CLEAR:
            TxOperation = TX_OR_CLEAR;
            break;
        case OSA_FLAG_OR:
            TxOperation = TX_OR ;
            break;
        case OSA_FLAG_AND_CLEAR:
            TxOperation = TX_AND_CLEAR ;
            break;
        case OSA_FLAG_AND:
            TxOperation = TX_AND ;
            break;
        default:
            ASSERT_EXT(0, "OS flag 0x%x wait operation error 0x%x", OsaRef, pParams->operation) ;
            return OS_INVALID_PARM ;
    }

	status = tx_event_flags_get( (TX_EVENT_FLAGS_GROUP *)OsaRef, (ULONG)pParams->mask, TxOperation,
									(ULONG *)pParams->flags, Osa_TimeoutValue(pParams->timeout) ) ;


    RETURN_STATUS( status, TX_SUCCESS ) ;
}
#pragma arm section code

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
    TX_TIMER
        *pTxTimer = (TX_TIMER *)OsaRef ;

    CHAR
        *pName ;

    UINT
        status ,
        cpsr ;

    OSA_ASSERT(OsaRef) ;

	if(EEHandlerFlag != 1)
	{
		tx_timer_debug[0] = (UINT32)OsaRef;
        tx_timer_debug[1] = (UINT32)__return_address();
	}
/*
 * A simple Start case.
 */
    if ( ! pParams )
		status = tx_timer_activate( pTxTimer );

/*
 * Case when timer already exists but new input params.
 */
    else
    {
        if ( pTxTimer->tx_timer_id == TX_TIMER_ID )		//TX_TIMER_ID means it's invalid
        {
			status = tx_timer_deactivate( pTxTimer ) ;

            RETURN_STATUS_ON_FAILURE( status, TX_SUCCESS ) ;

			status = tx_timer_change(pTxTimer, pParams->initialTime, pParams->rescheduleTime);

			RETURN_STATUS_ON_FAILURE( status, TX_SUCCESS ) ;

			cpsr = disableInterrupts();

			if(pParams->callBackRoutine)
			    pTxTimer->tx_timer_internal.tx_timer_internal_timeout_function = pParams->callBackRoutine;

        	pTxTimer->tx_timer_internal.tx_timer_internal_timeout_param = pParams->timerArgc;

			restoreInterrupts(cpsr);

			status = tx_timer_activate(pTxTimer);

			RETURN_STATUS( status, TX_SUCCESS ) ;


//			status = tx_timer_delete( pTxTimer );

//            RETURN_STATUS_ON_FAILURE( status, TX_SUCCESS ) ;

//            pTxTimer->tx_timer_id = OSA_UNINITIALIZED_TIMER ;
        }

        //pName = (CHAR *)(pParams->name ? pParams->name : pTxTimer->tx_timer_name) ;
		if(pParams->name)
		{
			strncpy(pTxTimer->tx_timer_name, pParams->name, TX_MAX_NAME - 1);
			pTxTimer->tx_timer_name[TX_MAX_NAME - 1] = '\0';
		}

		pName = pTxTimer->tx_timer_name;
/*
 * Case timer doesn't exist.
 */
 		extern void timer_test(ULONG argv);
       	status = tx_timer_create( pTxTimer, pName, (void(*)(ULONG))pParams->callBackRoutine,
								(ULONG)pParams->timerArgc, (ULONG)pParams->initialTime, (ULONG)pParams->rescheduleTime, TX_AUTO_START) ;

    }

    RETURN_STATUS( status, TX_SUCCESS ) ;
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
    TX_TIMER
        *pTxTimer = (TX_TIMER *)OsaRef ;

    UINT
        status ;

	OSA_ASSERT(pTxTimer) ;

	if(EEHandlerFlag != 1)
	{
		tx_timer_debug[0] = (UINT32)OsaRef;
        tx_timer_debug[1] = (UINT32)__return_address();
	}

	if ( pTxTimer->tx_timer_id== OSA_UNINITIALIZED_TIMER )
        return OS_SUCCESS ;

	status = tx_timer_deactivate( pTxTimer ) ;

    RETURN_STATUS( status, TX_SUCCESS ) ;
}

#pragma arm section code="OSA_MEM"
OSA_STATUS	OsaPartitionAllocate(OsaRefT *pOsaRef, void **return_pointer, UINT32 suspend){

	TX_BLOCK_POOL
		*pTxPool;

	UINT
		status;

	OSA_ASSERT(pOsaRef);

	pTxPool = (TX_BLOCK_POOL *)(*pOsaRef);
	OSA_ASSERT(pTxPool);

	if(pTxPool->tx_block_pool_reserved == OSA_PRIORITY){
		status = tx_block_pool_prioritize(pTxPool);
		if(status != TX_SUCCESS)
			RETURN_STATUS( status, TX_SUCCESS ) ;
	}

	status = tx_block_allocate(pTxPool, return_pointer, Osa_TimeoutValue(suspend));

#if 0
if(status){
	//Pijing Liu debug

	uart_printf("status = 0x%x, name: %s, id = 0x%x\r\n", status, pTxPool->tx_block_pool_name, pTxPool->tx_block_pool_id);

	uart_printf("current thread name: %s\r\n", (_tx_thread_identify())->tx_thread_name);

	uart_printf("pjliu: FILE: %s, LINE:%d, FUNC:%s\r\n", __FILE__,__LINE__, __FUNCTION__);
}
#endif
//	RETURN_STATUS( status, TX_SUCCESS ) ;
	return status; //PS will check this return value by themselves

}


OSA_STATUS	OsaPartitionFree(OsaRefT OsaRef){
	void
		*pTxBlock = (void *)OsaRef;

	UINT
		status;

	OSA_ASSERT(OsaRef);

	status = tx_block_release(pTxBlock);

//	RETURN_STATUS( status, TX_SUCCESS ) ;
	return status; //PS will check this return value by themselves
}


UINT32 OsaPartitionGetPoolUsedCount(OsaRefT *OsaRef)
{
	if( (OsaRef != NULL) && (*OsaRef != NULL) )
	{
		TX_BLOCK_POOL *pTxPool;
		pTxPool = (TX_BLOCK_POOL *)(*OsaRef);
		return (pTxPool->tx_block_pool_total - pTxPool->tx_block_pool_available);
	}

	return 0;
}

#pragma arm section code


