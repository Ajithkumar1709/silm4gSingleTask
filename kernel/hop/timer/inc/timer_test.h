/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/******************************************************************************
*                MODULE HEADER FILE
*******************************************************************************
*  COPYRIGHT (C) 2001 Intel Corporation.
*
*  This file and the software in it is furnished under
*  license and may only be used or copied in accordance with the terms of the
*  license. The information in this file is furnished for informational use
*  only, is subject to change without notice, and should not be construed as
*  a commitment by Intel Corporation. Intel Corporation assumes no
*  responsibility or liability for any errors or inaccuracies that may appear
*  in this document or any software that may be provided in association with
*  this document.
*  Except as permitted by such license, no part of this document may be
*  reproduced, stored in a retrieval system, or transmitted in any form or by
*  any means without the express written consent of Intel Corporation.
*
*  Title: timer_test header file
*
*  Filename: timer_test.h
*
*  Target, subsystem: Common Platform, HAL
*
*  Authors:  Levy Eli
*
*  Description:  timer unit test header file.
*
*  Create : 17-Jul-2005
*
*  Notes:
******************************************************************************/

// TT - Timer Test
#ifndef _Timer_Test_H_
#define _Timer_Test_H_

//#define DEBUG_PIN_ENABLE 1
//#define DEBUG_PIN_SET     (*(UINT32 *)0xD4060208 = 0x1) /* set GPB test register bit 0 */
//#define DEBUG_PIN_CLEAR   (*(UINT32 *)0xD406020C = 0x1) /* Clear GPB test register bit 0 */

#define TIMER_PM_DEBUG_MODE_ENABLE 1 /* Timer test flag */
#define SELECTED_TIMER TCR_2   // the timer that will be tested
#define TIMER_DELAY 1000000   // delay in uSec for testing the timerDelay function
#define NUM_OF_INT	10		 // the number of interupt that will be counted in periodic mode until we deactivate the timer
#define TIC_PER_HOUR 0x7090992 // 3600*1000000/30.5
//#define TIC_PER_HOUR 0x8012 // 1000000/30.5
#define NUM_OF_SAMPLE_FOR_COUNT_TEST 2000 /* the number of iteration for TTtimerCountStableRead routine*/

#define CWER_ADDRESS 0xF00E0120
#define NUM_OF_TIMER_SAMPLE 4 // the number of reading we like to see when testing free run mode
#define NUM_OF_TEST_SCENARIO 4 /* define the number of tests we want to perform */


#if !defined(_TAVOR_Z0_SILICON_)
#define DEBUG_PIN_SET
#define DEBUG_PIN_CLEAR
#define DEBUG_PINS_CLEAR(x)
#define DEBUG_PINS_SET(x)
#else
#define DEBUG_PIN_SET     (*(UINT32 *)0xD4060208 = 0x100) /* set GPB test register bit 0 */
#define DEBUG_PIN_CLEAR   (*(UINT32 *)0xD406020C = 0x100) /* Clear GPB test register bit 0 */
#define DEBUG_PINS_CLEAR(x) (*(UINT32 *)0xD406020C = x)
#define DEBUG_PINS_SET(x) (*(UINT32 *)0xD4060208 = x)
#endif
//********************
//uncomment this to enable the debug pin, need to setup the platform before using this option
#define DEBUG_PIN_ENABLE
//**********************************/
#define MAX_CHR_IN_LINE 100 /* max character in the TTprintTCRConfig line  */

#define TmrController  (* (volatile struct TIMER_HW_REGISTERS *) TIMER_BASE_ADDRESS) /* HW register for TTprintTCRConfig*/

typedef enum
{
    TT_OK,
    TT_INCORRECT_MODE,
    TT_TIMER_CONF_ERR

}TT_ReturnCodeE;

void TTtestTimer (void);
void TTPeriodicISRRoutine (UINT8 cookies);
void TTOneshotISRRoutine (UINT8 cookies);
void TTprintTCRConfig (void);
void TTGetCnt1Value (void);
void TTGetCnt2Value (void);
void TTGetCnt3Value (void);
void TTGetCnt4Value (void);
void TTtimerDelayTest (void *delay);
void TTtimerElapsedTimeGetTest (void);



#endif // _Timer_Test_H_
