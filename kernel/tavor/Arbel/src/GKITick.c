/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/*******************************************************************************
* Title: Tavor GKI Adaptation tick provider  file
*
* Filename: GKI .c
*
* Target, platform: Common Platform, SW platform
*
* Authors: Miriam Yovel
*
* Description:   This pacakge provide Tick manager services for GKI usage
*
* Last Updated:
*
* Notes:
******************************************************************************/
#include "osa.h"
#include "tick_manager.h"
#include "bsp_hisr.h"
#include "kernel.h"

/*-----------  defines  -----------------------------------------*/

//#define  MAX_GKI_TICKS_TO_SLEEP  1000
#define  MAX_GKI_TIME_TO_SLEEP  MAX_TimeIn32KhzUnit/2

/*----------- External defines  -----------------------------------------*/

extern UINT32 KiOsMaximumSleep(UINT32 ticks);  /*registered callback for TM to check maximum time alowed for sleep*/
extern Boolean KiOsTimersStartedOrStopped (void);
extern void KiOsTick(KernelTicks increment);
extern UINT32 GetTCRTimerCnt(void);

/*----------- global variables   -----------------------------------------*/
static OS_HISR extTickUpdateHISR;    /*HISR TM to supply GKI Ticks */
static UINT32 GKITickDeltaTicks;       /* GKI Ticks */
extern BOOL   TickSuspendContext;
UINT32        timeAtKiOsTick;
/*----------- for debug     -----------------------------------------*/
#ifdef TICK_MANAGER_TEST
#error TICK_MANAGER_TEST defined
static UINT32  maxSleepLog1[64];
static UINT64  maxSleepLog2[64];
static UINT32  maxSleepLog3[64];
static UINT32 GKICounter = 0;
#endif

//static UINT32 maxSleepLog[512];
//static UINT32 GKICounter = 0;

/******************************************************************************
* Function: GKIPsKiOsMaximumSleep
*******************************************************************************
* Description: GKI PS routine that provides time until next GKI Event
*
* Parameters:  None.
*
* Return value: maximum time to suspend in 32KHZUnit.
*
* Notes:
******************************************************************************/
static void GKIPrepareTimesBeforeDisableInt(void)
{
   KiOsTimersStartedOrStopped();

}
/******************************************************************************
* Function: GKIPsKiOsMaximumSleep
*******************************************************************************
* Description: GKI PS routine that provides time until next GKI Event
*
* Parameters:  None.
*
* Return value: maximum time to suspend in 32KHZUnit.
*
* Notes:
******************************************************************************/

static UINT32 GKIPsKiOsMaximumSleep(UINT32 ticks)
{
	return KiOsMaximumSleep(ticks*65)/65;


}

/******************************************************************************
* Function: GKIPsKiOsTick
*******************************************************************************
* Description:  GKI PS  routine that provides ticks update to GKI
*
* Parameters: none
*
* Return value: none.
*
* Notes:
******************************************************************************/
static void GKIPsKiOsTick (UINT32    increment)
{
  KiOsTick(increment*65);
  timeAtKiOsTick = GetTCRTimerCnt();

}

/******************************************************************************
* Function: GKIExtTickFunc
*******************************************************************************
* Description:  HISR Activated from TM Expiration Lisr
*
* Parameters: none
*
* Return value: none.
*
* Notes:
******************************************************************************/
void GKIExtTickFunc( void )
{
	UINT32  deltaTicks;
	UINT32  cpsrReg;

	cpsrReg = disableInterrupts(); //lock interrupts
	deltaTicks = GKITickDeltaTicks;
	// Now that we are going to report GKI with its ticks, we need to zero them for further
	// updates (via os-tick interrupt or via LPM-exit update) since they are accumulated
	GKITickDeltaTicks =0;
	restoreInterrupts(cpsrReg); //unlock interrupts

	if ( deltaTicks)
	{
		GKIPsKiOsTick (deltaTicks );
	}


}

/******************************************************************************
* Function: GKIExtTickFuncCallBack
*******************************************************************************
* Description:  TM registration callback by GKI modoule
*
* Parameters: deltaInTicks - ticks that passed and need to be updated to GKI AL
*
* Return value: none.
*
* Notes:
******************************************************************************/

void GKIExtTickFuncCallBack(UINT32 deltaInTicks)
{
	STATUS  osStatus;
	UINT32  cpsrReg;

	cpsrReg = disableInterrupts(); //lock interrupts
	  	// Since in rare conditions the ticks after LPM are not processed 
	  	// and OS-tick interrupt happens, we need to accumulate 
	  	// the ticks to report GKI (and NOT override). The counter will be zeroed,
	  	// when GKI tick-process is actually called, so we do not accumulate ticks for ever...
		GKITickDeltaTicks  += deltaInTicks;
	restoreInterrupts(cpsrReg); //unlock interrupts

    osStatus = OS_Activate_HISR(&extTickUpdateHISR);
    ASSERT(osStatus == OS_SUCCESS);
}

/******************************************************************************
* Function: GKIOsMaximumSuspend
*******************************************************************************
* Description: registered callback to return minimum time until next GKI Event
*
* Parameters:  None.
*
* Return value: maximum time to suspend in 32KHZUnit.
*
* Notes:
******************************************************************************/
TimeIn32KhzUnit GKIMaximumSuspend( void )
{

	UINT64          Maxsleep64 = MAX_GKI_TIME_TO_SLEEP; /*maximun time  to next event */
	UINT32          Maxsleep32;
  //	UINT32          Maxsleep = MAX_GKI_TICKS_TO_SLEEP;  /*maximun time in ticks to next event */
  	UINT32          Maxsleep;  /*maximun time in ticks to next event */


	Maxsleep64  = ( (UINT64) Maxsleep64 << 10 )/ MAX_CYCLES_1024_TICKS;       /*convert  to ticks ,casting UINT64 to prevent overflow*/

   // maxSleepLog1[GKICounter] = Maxsleep64;

  	Maxsleep32 = GKIPsKiOsMaximumSleep((UINT32) Maxsleep64 );    /*get minium time to next GKI event */

 // 	Maxsleep32 = GKIPsKiOsMaximumSleep((UINT32) Maxsleep );    /*get minium time to next GKI event */


	//maxSleepLog2[GKICounter] = Maxsleep32;


	Maxsleep64 = ((UINT64)(Maxsleep32) * MAX_CYCLES_1024_TICKS ) >> 10;   /*convert to 32khzunit*/

	//maxSleepLog3[GKICounter] = Maxsleep64;

	Maxsleep = (TimeIn32KhzUnit)( Maxsleep64 );

    /*Miriam!!!!!!!!!!!!!!***********/
#if 0
	if (GKICounter < 512)
    {
        maxSleepLog[GKICounter] = Maxsleep;
        GKICounter++;
    }

#endif
	return (Maxsleep);
}

 /******************************************************************************
* Function: GKITickRegister
*******************************************************************************
* Description: Register to Tick Manager services
*
* Parameters:  None.
*
* Return value:  None.
*
* Notes:
******************************************************************************/
void GKITickRegister(void)

{
 /*Create HISR for GKI Tick supplied by TM */
 OS_Create_HISR(&extTickUpdateHISR, "ExtTick", GKIExtTickFunc, 1);
 TickSubmit( GKIExtTickFuncCallBack , GKIMaximumSuspend ,GKIPrepareTimesBeforeDisableInt);
}



