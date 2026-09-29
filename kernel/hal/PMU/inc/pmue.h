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
* Title: pmu.h
*
* Filename: pmu.h
*
* PMU Header file
*
* Authors:    Yabbo Shuki
*
* Description:
*
* Last Updated:
*
* Notes:
*******************************************************************************/

#ifndef _PMUE_H_
#define _PMUE_H_

#include "syscfg.h"
#include "global_types.h"
#include "pmu.h"
#define PMUE_API_DECOUPLING_STAGE_1
#if defined(PERIPHERAL_CLOCKS_VIA_PMU_API) || defined(PMUE_API_DECOUPLING_STAGE_1)

////////////////////////////////////////////////////////////////////////////////
//                         APB EXT clock control API
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
  PMUE_CSSP0,
  PMUE_CSSP1,
  PMUE_CSSP2,
#if defined (_TAVOR_BOERNE_)
  PMUE_CSSP3,
#else //_TAVOR_BOERNE_
  PMUE_GSSP0,
  PMUE_GSSP1,
  PMUE_G_SIM,
  PMUE_GCRAPB1,
#endif //_TAVOR_BOERNE_
  PMUE_LCD0,
  PMUE_LCD1,
  PMUE_SLCD,
  PMUE_CAMIF,
  PMUE_ME,
  PMUE_ME_SRAM,
  PMUE_WCIPHER
}PMUEPeripherals;


typedef enum
{
    PMUE_KEYPAD_APB_SRC_NOT_BY_LOW_PWR   = 0,
    PMUE_KEYPAD_APB_SRC_BY_LOW_PWR       = 1
}   PMUE_KEYPAD_APB_SRC;


typedef enum
{
    PMUE_KEYPAD_APB_LOW_PWR_DISABLE      = 0,
    PMUE_KEYPAD_APB_LOW_PWR_ENABLE       = 2
}   PMUE_KEYPAD_APB_LOW_PWR_EN;


#ifdef _HERMON_A0_SILICON_

typedef enum
{
    PMUE_SSP_CLK_26MHZ   = 0,                            // For all SSP's
    PMUE_SSP_CLK_BITCLK1 = 1,                            // For GSSP0, GSSP1, CSSP1 only
    PMUE_SSP_CLK_EXTERN  = PMUE_SSP_CLK_BITCLK1,         // For CSSP2 only
    PMUE_I2S_BIT_CLOCK   = PMUE_SSP_CLK_BITCLK1,         // For CSSP0 only
    PMUE_SSP_CLK_SYSCLK1 = 2                             // For GSSP0, GSSP1, CSSP1 only
} PMUESSPClockSelection;
#endif


#ifdef _HERMON_B0_SILICON_
typedef enum
{
    PMUE_SYSCLK0 = 0,
    PMUE_SYSCLK1 = 1,
    PMUE_BITCLK1 = 2
} PMUESysClk;


typedef enum
{
    PMUE_SYSCLK_26MHZ  = 0,
    PMUE_SYSCLK_156MHZ = 1
} PMUESyslockSelection;

#endif

#endif //defined(PERIPHERAL_CLOCKS_VIA_PMU_API) || defined(PMUE_API_DECOUPLING_STAGE_1)


#if defined(PERIPHERAL_CLOCKS_VIA_PMU_API)
void PMUEPhase1Init( void );
void PMUEPhase2Init( void );
void                   PMUEPeripheralFunctionalClock      (PMUEPeripherals peripheralName, PMUOnOff onOff);
void                   PMUEPeripheralAPBClock             (PMUEPeripherals peripheralName, PMUOnOff onOff);
void                   PMUEPeripheralBothClocks           (PMUEPeripherals peripheralName, PMUOnOff onOff);

PMUOnOff               PMUEPeripheralFunctionalClockStatus(PMUEPeripherals peripheralName);
PMUOnOff               PMUEPeripheralAPBClockStatus       (PMUEPeripherals peripheralName);
PMU_BothClocksStatus   PMUEPeripheralBothClocksStatus     (PMUEPeripherals peripheralName);
void PMUEKeypadPeripheralAPBClock ( PMUOnOff    onOff );

#ifdef _HERMON_B0_SILICON_
void  PMUESelectClock ( PMUEPeripherals   peripheralName , PMUESSPClockSelection   select_clk );
void  PMUESetClkRate ( PMUEPeripherals   peripheralName , UINT16   nom , UINT16    denom );
void  PMUESelectClockDivider ( PMUEPeripherals   peripheralName , UINT32      divValue );
void  PMUEGcrApb1Control ( UINT32    value , UINT32     mask );
void  PMUESysBitClock ( PMUESysClk   SysBitClk , PMUOnOff   onOff );
void  PMUESysClockSelect ( PMUESysClk   SysClk , PMUESyslockSelection   SysClkSelect );

void  PMUESelectClockStatus ( PMUEPeripherals   peripheralName , PMUESSPClockSelection   *select_clk );
void  PMUESelectClockDividerStatus ( PMUEPeripherals   peripheralName , UINT32      *divValue );
void  PMUESetClkRateStatus ( PMUEPeripherals   peripheralName , UINT16   *nom , UINT16    *denom );
void  PMUESysClockSelectStatus ( PMUESysClk   SysClk , UINT32   *SysClkSelect );

/*
 * GSM Peripherals
 */
#define PMUETcuFuncClk PMUETcuClockControl /*OLD name*/
void PMUETcuClockControl  ( PMUOnOff    onOff );
void PMUETcuSwReset       ( void );
void PMUEHslClockControl  ( PMUOnOff    onOff );
void PMUEDIRQClockControl ( PMUOnOff    onOff );
void PMUEXIRQClockControl ( PMUOnOff    onOff );
void PMUESSPInit( void );

/*
 * ME (Motion Estimation)
 */

// ME functional and SRAM clock rates
typedef enum
{
	PMUE_ME_104MHZ,
	PMUE_ME_78MHZ,
	PMUE_ME_156MHZ
} PMUEMeClockRate;

void PMUESetMeClkRate(PMUEMeClockRate rate);
void PMUESetMeSRAMClkRate(PMUEMeClockRate rate);
// ME resets
void PMUEMeFuncReset(void);
void PMUEMeSRAMReset(void);

/*
 *  SLEEP LOGIC MODE: WCDMA or GSM
 */
typedef enum
{
	PMUE_MODE_GSM,    /* GSM Slow Clock    controls BB */
	PMUE_MODE_WCDMA   /* WCDMA Sleep Timer controls BB */
}PMUE_SleepLogicMode;
void PMUESetSleepLogicMode(PMUE_SleepLogicMode mode);






/* General Control register on APB  */
#define TCU_CLK_ENABLE              0x400
#define HSL_CLK_ENABLE              0x200
#define DIRQ_CLK_ENABLE             0x100
#define DIRQ_CLK_DISABLE            0x000

#define GSSP1_SELECTOR_APB          0x80
#define GSSP1_SELECTOR_DPB          0x00
#define GSSP0_SELECTOR_APB          0x40
#define GSSP0_SELECTOR_DPB          0x00
#define TCU_SW_RESET                0x20
#define XIRQ_CLOCK_ENABLE           0x10
#define XIRQ_CLOCK_DISABLE          0x00

#define SIM_CLK_ENABLE              0x8
#define GSSP1_CLK_ENABLE            0x4
#define GSSP0_CLK_ENABLE            0x2
#define XIRQ_SW_RESET               0x1

#endif
#endif //defined(PERIPHERAL_CLOCKS_VIA_PMU_API)

#if defined(PERIPHERAL_CLOCKS_VIA_PMU_API) || defined(PMUE_API_DECOUPLING_STAGE_1)

////////////////////////////////////////////////////////////////////////////////
//                         APB TOP WAKEUP control API
////////////////////////////////////////////////////////////////////////////////

typedef enum
{
   //Keypress detector
   PMUE_WAKE_KPD0=0x00000001,
   PMUE_WAKE_KPD1=0x00000002,
   PMUE_WAKE_KPD2=0x00000004,
   PMUE_WAKE_KPD3=0x00000008,
   PMUE_WAKE_KPD4=0x00000010,
   PMUE_WAKE_KPD5=0x00000020,
   PMUE_WAKE_KPD6=0x00000040,
   PMUE_WAKE_KPD7=0x00000080,
   // Direct keys
   PMUE_WAKE_DK0=0x00000100,
   PMUE_WAKE_DK1=0x00000200,
   PMUE_WAKE_DK2=0x00000400,
   PMUE_WAKE_DK3=0x00000800,
   PMUE_WAKE_DK4=0x00001000,
   PMUE_WAKE_DK5=0x00002000,
   PMUE_WAKE_DK6=0x00004000,
   PMUE_WAKE_DK7=0x00008000,
   //Reserved
   PMUE_WAKE_RESERVED0=0x00010000,
   PMUE_WAKE_RESERVED1=0x00020000,
   PMUE_WAKE_PWE0=0x00040000,      //PMIC port: 2-bit value
   PMUE_WAKE_PWE1=0x00080000,      //PMIC port: 2-bit value
   PMUE_WAKE_URE=0x00100000,       //USB client
   // TOP
   PMUE_WAKE_TIMER=0x00200000,
   PMUE_WAKE_ICU=0x00400000,
   PMUE_WAKE_GPIO=0x00800000,
   PMUE_WAKE_ALARM=0x01000000,
   PMUE_WAKE_SCK_WAKEUP=0x02000000,//GSM slow clock
   PMUE_WAKE_SM=0x04000000,        //WCDMA sleep module
   PMUE_WAKE_SCK=0x08000000,
   PMUE_WAKE_XIRQ_NAIRQ=0x10000000,
   PMUE_WAKE_MSL=0x20000000,
   PMUE_WAKE_USB2=0x40000000
}PMUE_WakeupSource;

#define PMUE_WAKE_DIRQ_NAIRQ 0x80000000 /*Separate definition as enum above is SIGNED int*/


#define PMUE_WAKE_ALL  (0xffffffff&~(PMUE_WAKE_RESERVED0|PMUE_WAKE_RESERVED1))
#define PMUE_WAKE_KPD_ALL (0x000000ff)
#define PMUE_WAKE_DK_ALL  (0x0000ff00)

#define PMUE_WAKE_USB1 PMUE_WAKE_MSL /* alias for backward compatibility */

#endif // defined(PERIPHERAL_CLOCKS_VIA_PMU_API) || defined(PMUE_API_DECOUPLING_STAGE_1)
#if defined(PERIPHERAL_CLOCKS_VIA_PMU_API)
UINT32                 PMUEWakeupControl(UINT32 source, UINT32 mask);
UINT32                 PMUEWakeupControlStatus(void);
#endif

#if defined(PERIPHERAL_CLOCKS_VIA_PMU_API) || defined(PMUE_API_DECOUPLING_STAGE_1)
typedef enum
{
   //CLK_13M_REQ's
   PMUE_VCTCXO_REQ_0=0x00000001,
   PMUE_VCTCXO_REQ_1=0x00000002,
   PMUE_VCTCXO_REQ_2=0x00000004,
   PMUE_VCTCXO_REQ_3=0x00000008
}PMUE_VCTCXO_Request;

#define PMUE_VCTCXO_REQ_ALL (0x0f)
#endif
#if defined(PERIPHERAL_CLOCKS_VIA_PMU_API)
UINT32                 PMUEVCTCXOReqControl(UINT32 source, UINT32 mask);
UINT32                 PMUEVCTCXOReqStatus(void);
void                   PMUEVCTCXOReqSetPolarity(PMUE_VCTCXO_Request req, BOOL activeHigh);

void PMUESetGsmSlowClockEndlessSleep(void);
void PMUESetModemEndlessSleep(void);

/*
 *  PMUEMSLClockDetectorControl()
 *  this is a wrapper that calls PMUMSLClockDetectorControl and also enables/disables the MSL detector wakeup event
 */
void                   PMUEMSLClockDetectorControl(PMUOnOff onOff);
#endif

#if !defined(PERIPHERAL_CLOCKS_VIA_PMU_API)
#define PMUEPeripheralFunctionalClock(x,y)
#define PMUEPeripheralAPBClock(x,y)
#define PMUEPeripheralBothClocks(x,y)
#define PMUEPeripheralFunctionalClockStatus(x)
#define PMUEPeripheralAPBClockStatus(x)
#define PMUEPeripheralBothClocksStatus(x)
#define PMUEKeypadPeripheralAPBClock(x)
#define PMUESetModemEndlessSleep(x)
#define PMUEWakeupControl(x,y)
#endif
#endif
