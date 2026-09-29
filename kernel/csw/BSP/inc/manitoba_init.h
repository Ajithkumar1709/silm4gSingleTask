/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
INTEL CONFIDENTIAL
Copyright 2006 Intel Corporation All Rights Reserved.
The source code contained or described herein and all documents related to the source code ("Material") are owned
by Intel Corporation or its suppliers or licensors. Title to the Material remains with Intel Corporation or
its suppliers and licensors. The Material contains trade secrets and proprietary and confidential information of
Intel or its suppliers and licensors. The Material is protected by worldwide copyright and trade secret laws and
treaty provisions. No part of the Material may be used, copied, reproduced, modified, published, uploaded, posted,
transmitted, distributed, or disclosed in any way without Intel's prior express written permission.

No license under any patent, copyright, trade secret or other intellectual property right is granted to or
conferred upon you by disclosure or delivery of the Materials, either expressly, by implication, inducement,
estoppel or otherwise. Any license under such intellectual property rights must be express and approved by
Intel in writing.
-------------------------------------------------------------------------------------------------------------------*/

/*******************************************************************************
*               MODULE HEADER FILE
********************************************************************************
* Title: Manitoba_init Header
*
* Filename: manitoba_init.h
*
* Target, platform: Manitoba
*
* Authors:	Gideon Yuval
*
* Description: header for manitoba_init
*
* Last Updated:
*
* Notes:
*******************************************************************************/

#ifndef _MANITOBA_INIT_H_
#define _MANITOBA_INIT_H_

#include <nucleus.h>
/*----------- Global definitions ---------------------------------------------*/
#define INITIAL_FREQUENCY MANITOBA_FREQUENCY_MODE
#define HISR_STACK_SIZE         (2*1024)
#define HISR_PRIORITY_LEVELS    3
#define NUM_GSM_INTS  17  /* this should be set to at least the number of interrupts defined in dlcoreirq.h */
/*----------- Global type definitions ----------------------------------------*/
/*----------- Global macro definitions ---------------------------------------*/
/*----------- Global variable definitions ---------------------------------------*/
extern char hisrStack[HISR_PRIORITY_LEVELS][HISR_STACK_SIZE];
extern char osTickHISRStack[HISR_STACK_SIZE];
extern OS_HISR osTickHISR;
extern OS_HISR gpioHisrCb;
extern OS_HISR _L1FrameInterruptHISR;
extern OS_HISR _L1FrIdlePrachIntHISR;
extern OS_HISR _L1FrPtmOddIntHISR;
extern OS_HISR _dlSIMSendSigHISR;
extern OS_HISR _L120mIntHISR;  /*AUDIO_ISAR*/
extern OS_HISR _L1SdvrIntHISR;  /*AUDIO_ISAR*/
extern OS_HISR _suspendSignalsAfterSleepHISR;  /*PMU_SHUKI*/
extern OS_HISR _L1I2SIntHISR;

extern void mcuIrqCtrlIsr(void);
extern void L1FrameInterruptHISR (void);
extern void L1FrPtmOddIntHISR (void);
extern void L1FrIdlePrachIntHISR(void);
extern void dlSIMSendSigHISR  (void);
extern void Dl20msTickCodecHISR (void);  /*AUDIO_ISAR*/
extern void sdvrNotifyHISR (void);  /*AUDIO_ISAR*/
extern void I2SNotifyHISR (void);  /*AUDIO_ISAR*/
extern void suspendSignalsAfterSleepHISR (void);  /*PMU_SHUKI*/
extern void RTCAlarmHISR(void);


/*----------- Global function prototypes -------------------------------------*/
UINT32 diagSendVersion(void *Str);
void ConfigureAndInitPhase1UART(void);
void Delay(unsigned long  uSec); //GYU - this should go somewhere else, but where?
void DSPResetAck (void);
void GsmInterruptInit(void);
void InitTimers(void);
UINT32 diagGetXscClockType(void *Params);
UINT32 diagGetMSAClockType(void *Params);
UINT32 _SetRTC(void *pDateAndTime);
UINT32 _ReadRTC(void *);

#endif	/* _WATCHDOG_H_ */
