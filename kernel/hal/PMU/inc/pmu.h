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

#ifndef _PMU_H_
#define _PMU_H_

#include "global_types.h"
#include "syscfg.h"
#define PMU_API_DECOUPLING_STAGE_1
#if defined(PERIPHERAL_CLOCKS_VIA_PMU_API)
#include "pmu_config.h"

#ifdef _PMU_NO_EXTERN_
#define  MODULE_ID DIAGM_PMU_H
#endif
/*----------- Global defines -------------------------------------------------*/

/*----------- Global macro definitions ---------------------------------------*/

/*----------- Global type definitions ----------------------------------------*/
//ICAT EXPORTED STRUCT
typedef struct
{
    UINT8	PWM2C1_FuncClock;
    UINT8	PWM2C0_FuncClock;
    UINT8	PWM1C1_FuncClock;
    UINT8	PWM1C0_FuncClock;
	UINT8	PMU_FUNC_RESERVED_0;
	UINT8	PMU_FUNC_RESERVED_1;
	UINT8	PMU_FUNC_RESERVED_2;
	UINT8	I2S_FuncClock;
    UINT8	USIM_FuncClock;
    UINT8	SCI3_FuncClock;
    UINT8	SCI2_FuncClock;
    UINT8	SCI1_FuncClock;
    UINT8	ICP_FuncClock;
	UINT8	PMU_FUNC_RESERVED_3;
    UINT8	GPC_FuncClock;
    UINT8	SSP_FuncClock;
	UINT8	PMU_FUNC_RESERVED_4;
	UINT8	PMU_FUNC_RESERVED_5;
    UINT8	I2C_FuncClock;
    UINT8	KEYPAD_FuncClock;
    UINT8	MSHC_FuncClock;
	UINT8	PMU_FUNC_RESERVED_6;
    UINT8	MSL_FuncClock;
    UINT8	DSYTMR_FuncClock;
    UINT8	NDSYTMR_FuncClock;
	UINT8	PMU_FUNC_RESERVED_7;
    UINT8	ETM_FuncClock;
    UINT8	MMC_FuncClock;
    UINT8	USB_FuncClock;
    UINT8	UART3_FuncClock;
    UINT8	UART2_FuncClock;
    UINT8	UART1_FuncClock;
}PMU_PeriFuncClockStatus;

//ICAT EXPORTED STRUCT
typedef struct
{
    UINT8	UART1_APBClock;
    UINT8	UART2_APBClock;
    UINT8	UART3_APBClock;
    UINT8	I2C_APBClock;
    UINT8	IPC_APBClock;
    UINT8	USB_APBClock;
    UINT8	ICP_APBClock;
    UINT8	SSP_APBClock;
    UINT8	MMC_APBClock;
    UINT8	KEYPAD_APBClock;
    UINT8	USIM_APBClock;
    UINT8	LCD_IF_APBClock;
    UINT8	PWM_APBClock;
    UINT8	SCI1_APBClock;
    UINT8	SCI2_APBClock;
    UINT8	SCI3_APBClock;
    UINT8	MSL_APBClock;
    UINT8	RTC_APBClock;
    UINT8	GPIO_APBClock;
    UINT8	INTC_APBClock;
    UINT8	DSYTMR_APBClock;
    UINT8	NDSYTMR_APBClock;
    UINT8	ONE_WIRE_APBClock;
    UINT8	SIM_APBClock;
    UINT8	EXT_PERIPHERAL_1_APBClock;
    UINT8	ABTH_APBClock;
    UINT8	XCRG_APBClock;
    UINT8	TCU_SC_APBClock;
    UINT8	EXT_PERIPHERAL_5_APBClock;
    UINT8	EXT_PERIPHERAL_6_APBClock;
    UINT8	EXT_PERIPHERAL_7_APBClock;
    UINT8	MSHC_APBClock;
}PMU_PeriAPBClockStatus;

#endif
#if defined(PERIPHERAL_CLOCKS_VIA_PMU_API) || defined(PMU_API_DECOUPLING_STAGE_1)
typedef enum
{
	PMU_RC_WRONG_VALUE = -100,
    PMU_RC_OK = 0,
	PMU_RC_POR,
	PMU_RC_EMR,
    PMU_RC_WDTR = (PMU_RC_EMR+2)
}PMU_ReturnCode;

typedef enum
{
    PMU_PLL_312_XSC_312 = 0,
    PMU_PLL_312_XSC_104,
    PMU_PLL_104_XSC_104,
    PMU_PLL_312_XSC_312_MSA_156,
    PMU_PLL_208_XSC_208_MSA_208
}PMU_Frequency_Modes;

typedef enum
{
    PMU_BOTH_CLOCKS_OFF = 0,
    PMU_ONLY_FUNCTIONAL_CLOCK_ON,
    PMU_ONLY_APB_CLOCK_ON,
    PMU_BOTH_CLOCKS_ON
}PMU_BothClocksStatus;

//ICAT EXPORTED ENUM
typedef enum
{
    PMU_POR = 1,
    PMU_EMR,
    PMU_WDTR = (PMU_EMR+2)
}PMU_LastResetStatus;

typedef enum
{
    PMU_PWM2C1 = 0,
    PMU_PWM2C0,
    PMU_PWM1C1,
    PMU_PWM1C0,
    PMU_I2S = 7,
    PMU_USIM,
#if !defined (_HERMON_B0_SILICON_)
    PMU_SCI3,
    PMU_SCI2,
    PMU_SCI1,
#endif
    PMU_ICP=12,
    PMU_GPC = 14,
    PMU_SSP,
#if defined (_HERMON_B0_SILICON_)
    PMU_GPIO=17,
#endif
    PMU_I2C = 18,
    PMU_KEYPAD,
    PMU_MSHC,
    PMU_MSL = 22,
    PMU_DSYTMR,
    PMU_NDSYTMR,
    PMU_ETM = 26,
    PMU_MMC,
    PMU_USB,
    PMU_UART3,
    PMU_UART2,
    PMU_UART1,
    PMU_NONE
}PMUPeripherals;

typedef struct
{
	UINT32  _PmuMSAUsersStatus;
	UINT32  _PmuBBLogicUsersStatus;
	UINT32	pmueFuncStatus;
	UINT32	_dmaChannelStatus;
}PMStatus_type;

#if defined(_HERMON_B0_SILICON_) && !defined (INTEL_2CHIP_PLAT_BVD)
typedef enum
{
    APB_UART1 = 0,
    APB_UART2,
    APB_UART3,
    APB_I2C,
    APB_IPC,
    APB_USB,
    APB_ICP,
    APB_EXT_PERIPHERAL_0,
    APB_MMC,
    APB_KEYPAD,
    APB_USIM = 10,
    APB_EXT_PERIPHERAL_5,
    APB_PWM,
    APB_RESERVED_0,
    APB_EGPIO,
    APB_RESERVED_1,
    APB_MSL,
    APB_RTC,
    APB_GPIO,
    APB_INTC,
    APB_EXT_PERIPHERAL_1 = 20,
    APB_NDSYTMR,
    APB_ONE_WIRE,
    APB_SSP_O_1,
    APB_SSP_2,
    APB_EXT_PERIPHERAL_2,
    APB_EXT_PERIPHERAL_3,
    APB_EXT_PERIPHERAL_4,
    APB_LCD_IF,
    APB_EXT_PERIPHERAL_6,
    APB_EXT_PERIPHERAL_7 = 30,
    APB_MSHC,
    APB_CAM_BIT,
    APB_NONE
}APBPeripherals;
#else
typedef enum
{
    APB_UART1 = 0,
    APB_UART2,
    APB_UART3,
    APB_I2C,
    APB_IPC,
    APB_USB,
    APB_ICP,
    APB_SSP,
    APB_MMC,
    APB_KEYPAD,
    APB_USIM,
    APB_LCD_IF,
    APB_PWM,
    APB_SCI1,
    APB_SCI2,
    APB_SCI3,
    APB_MSL,
    APB_RTC,
    APB_GPIO,
    APB_INTC,
    APB_DSYTMR,
    APB_NDSYTMR,
    APB_ONE_WIRE,
    APB_EXT_PERIPHERAL_0,
    APB_EXT_PERIPHERAL_1,
    APB_EXT_PERIPHERAL_2,
    APB_EXT_PERIPHERAL_3,
    APB_EXT_PERIPHERAL_4,
    APB_EXT_PERIPHERAL_5,
    APB_EXT_PERIPHERAL_6,
    APB_EXT_PERIPHERAL_7,
    APB_MSHC,
    APB_CAM_BIT,
    APB_NONE
}APBPeripherals;
#endif

#ifdef _MANITOBA_SILICON_
#define APB_SIM APB_EXT_PERIPHERAL_0
#define APB_ABTH APB_EXT_PERIPHERAL_2
#define APB_XCRG APB_EXT_PERIPHERAL_3
#define APB_TCU_SC APB_EXT_PERIPHERAL_4
#endif

#if defined (INTEL_2CHIP_PLAT_BVD)
#define APB_ABTH APB_EXT_PERIPHERAL_2
#define APB_XCRG APB_EXT_PERIPHERAL_3
#define APB_TCU     APB_EXT_PERIPHERAL_6
#endif//INTEL_2CHIP_PLAT_BVD

#ifdef _HERMON_A0_SILICON_
#ifdef _HERMON_B0_SILICON_
#define APB_ME      APB_EXT_PERIPHERAL_2
#define APB_GENERAL APB_EXT_PERIPHERAL_3
#define APB_WCIPHER APB_EXT_PERIPHERAL_4
#define APB_SIM     APB_EXT_PERIPHERAL_6
#define APB_GSSP    APB_EXT_PERIPHERAL_6
#define APB_CAMIF   APB_EXT_PERIPHERAL_7
#else
// EXT APB
#define APB_CSSP_0  APB_EXT_PERIPHERAL_0 /*shared*/
#define APB_CSSP_1  APB_EXT_PERIPHERAL_0 /*shared*/
#define APB_CSSP_2  APB_EXT_PERIPHERAL_1
#define APB_CSSP_3  APB_EXT_PERIPHERAL_2
#define APB_GENERAL APB_EXT_PERIPHERAL_3
#define APB_WCIPHER APB_EXT_PERIPHERAL_4
#define APB_LCD_0   APB_EXT_PERIPHERAL_5 /*shared*/
#define APB_LCD_1   APB_EXT_PERIPHERAL_5 /*shared*/
#define APB_TCU     APB_EXT_PERIPHERAL_6
#define APB_CAMIF   APB_EXT_PERIPHERAL_7
#endif
#define APB_TCU_SC  APB_TCU
#endif

typedef enum
{
    BOTH_PWM2C1 = 0,
    BOTH_PWM2C0,
    BOTH_PWM1C1,
    BOTH_PWM1C0,
    BOTH_I2S,
    BOTH_USIM,
#ifndef _HERMON_B0_SILICON_
    BOTH_SCI3,
    BOTH_SCI2,
    BOTH_SCI1,
#endif
    BOTH_ICP,
    BOTH_GPC,
	BOTH_SSP,
    BOTH_I2C,
    BOTH_KEYPAD,
    BOTH_MSHC,
    BOTH_MSL,
    BOTH_DSYTMR,
    BOTH_NDSYTMR,
	BOTH_ETM,
    BOTH_MMC,
    BOTH_USB,
    BOTH_UART3,
    BOTH_UART2,
    BOTH_UART1,
    BOTH_IPC,
    BOTH_LCD_IF,
    BOTH_RTC,
    BOTH_GPIO,
    BOTH_INTC,
    BOTH_ONE_WIRE,
    BOTH_EXT_PERIPHERAL_0,
    BOTH_EXT_PERIPHERAL_1,
    BOTH_EXT_PERIPHERAL_2,
    BOTH_EXT_PERIPHERAL_3,
    BOTH_EXT_PERIPHERAL_4,
    BOTH_EXT_PERIPHERAL_5,
    BOTH_EXT_PERIPHERAL_6,
    BOTH_EXT_PERIPHERAL_7,
    BOTH_CAM_BIT
}BothPeripherals;

#ifdef _MANITOBA_SILICON_
#define BOTH_SIM BOTH_EXT_PERIPHERAL_0

#define BOTH_ABTH BOTH_EXT_PERIPHERAL_2
#define BOTH_XCRG BOTH_EXT_PERIPHERAL_3
#define BOTH_TCU_SC BOTH_EXT_PERIPHERAL_4
#endif

typedef enum
{
    PMU_XPCR = 0,
    PMU_XPSR,
    PMU_FCCR,
    PMU_POCR,
    PMU_POSR,
    PMU_UCCR,
    PMU_CGCR,
    PMU_XPRR1,
    PMU_XPRR2,
    PMU_XCGR,
    PMU_XRSR,
    PMU_XDCR,
    PMU_GPCR,
    PMU_XDWR
}PMURegistersList;

typedef enum
{
	PMU_OFF = 0,
    PMU_ON,
    PMU_ON_PLUS_DMA
}PMUOnOff;

typedef enum
{
	PMU_VCTCXO_STABLE_TIME = 0,
	PMU_PLL_LOCK_TIME,
	PMU_TI4,
	PMU_TO2
}PMUParamreters;

typedef enum
{
    PMU_PORT_ZERO = 0,
    PMU_PORT_ONE,
	PMU_PORT_TWO,
    PMU_PORT_THREE
}PMUWakeupPortNumber;

typedef enum
{
	PMU_CORE_ONLY = 0,
	PMU_PX_IDLE,
	PMU_DROWSY,
	PMU_DROWSY_AND_VCTCXOSD,
    PMU_NO_SLEEP
}PMUSleepModes;

typedef enum
{
	PMU_NO_FORCE = 0,
	PMU_FORCE
}PMUForce;

typedef enum
{
	PMU_MEMC_DIV = 0,
	PMU_I2S_DIV,
    PMU_MSHC_DIV,
    PMU_GPC_DIV
}PMUSfcDividers;

typedef struct
{
	UINT8 pll_mf;
	UINT8 xsc_div;
	UINT8 dsp_div;
	UINT8 px_div;
	UINT8 px2dsp_div;
	UINT8 dpb2dsp_div;
	UINT8 apb_div;
}PMUFrequencies;



/*----------- Extern definition ----------------------------------------------*/

//GYU GCSR0
#define M_SetBit(x,y) (*(volatile UINT32 *)y) = (*(volatile UINT32 *)y) | (1<<(x))
#define M_ClrBit(x,y) (*(volatile UINT32 *)y) = (*(volatile UINT32 *)y) & ~(1<<(x))
#ifdef _MANITOBA_SILICON_
#define M_GCSR0SetBit(x) PMUPeripheralAPBClock(APB_XCRG, PMU_ON);M_SetBit(x,0x42a00800);PMUPeripheralAPBClock(APB_XCRG, PMU_OFF);
#define M_GCSR0ClrBit(x) PMUPeripheralAPBClock(APB_XCRG, PMU_ON);M_ClrBit(x,0x42a00800);PMUPeripheralAPBClock(APB_XCRG, PMU_OFF);
#else
#define M_GCSR0SetBit(x)
#define M_GCSR0ClrBit(x)
#endif
#endif // defined(PERIPHERAL_CLOCKS_VIA_PMU_API) || defined(PMU_API_DECOUPLING_STAGE_1)
/*----------- Global variable declarations -----------------------------------*/

#if defined(PERIPHERAL_CLOCKS_VIA_PMU_API)
/*----------- Global constant definitions ------------------------------------*/
#define INTC_ICHP_REG                   0x40d00018L //ICHP register addres
#undef EXTERN
#ifndef _PMU_NO_EXTERN_
  #define EXTERN extern
#else
  #define EXTERN
#endif /* _PMU_NO_EXTERN_ */

/*----------- Global function prototypes -------------------------------------*/
void                   PMUPeripheralFunctionalClock(PMUPeripherals peripheralName, PMUOnOff onOff);
void                   PMUPeripheralAPBClock(APBPeripherals peripheralName, PMUOnOff onOff);
void                   PMUPeripheralBothClocks(BothPeripherals peripheralName, PMUOnOff onOff);
void                   PMUPeripheralReset(BothPeripherals peripheralName);
void 				   PMUResetAllPeripherals(void);
PMUOnOff               PMUPeripheralFunctionalClockStatus(PMUPeripherals peripheralName);
PMUOnOff               PMUPeripheralAPBClockStatus(APBPeripherals peripheralName);
PMU_BothClocksStatus   PMUPeripheralBothClocksStatus(BothPeripherals peripheralName);
void                   PMUDSPReset(BOOL releaseFromReset);
void                   PMUDSPResetRelease(void);
void                   PMUBBLogicReset(BOOL releaseFromReset);
void                   PMUBBLogicResetRelease(void);
void                   PMUMemcClock(PMUOnOff onOff, PMUMemcUsers memcUser);
void                   PMUMSAClock(PMUOnOff onOff, PMUMsaUsers msaUser);
BOOL 				   PMUMsaClockUsersStatus(void);
void                   PMUBBLogicClock(PMUOnOff onOff, PMUBBLogicUsers bbLogicUser);
BOOL 				   PMUIsApbRequired(void);
void 				   PMUAllowApbIdleMode(BOOL idleModeAllow);
BOOL 				   PMUIsPxIdleAllowed(void);
void 				   PMUSetSleepConditions(PMUSleepModes sleepMode);
void 				   PMUSleepExit(void);
//PMU_ReturnCode         PMUMfcReq(PMUFrequencies *frequencyCombination, PMUForce forceMfc);
PMU_ReturnCode         PMUSfcReq(PMUSfcDividers clockDivider, UINT32 divValue);
void                   PMUDrowsyWakeupPortMask(PMUWakeupPortNumber portNumber, BOOL maskUnmask);
void                   PMUMSLClockDetectorControl(PMUOnOff onOff);
PMU_LastResetStatus    PMULastReset(void);
void                   PMUForceClockMode(PMUOnOff onOff);
void                   PMUAPBForceClockMode(PMUOnOff onOff);
void                   PMUAPBPowerConsumptionMode(PMUOnOff onOff);
UINT32                 PMUWriteReg(PMURegistersList pmuReg, UINT32 value, UINT32 mask);
UINT32                 PMUReadReg(PMURegistersList pmuReg);
UINT32                 PMUMultiClock(UINT32 value, UINT32 mask);
PMU_ReturnCode         PMUPhase1Init(void);
#define PMUGetVCXOStandbyTime PMUGetVCXOStabilizationTime        /*misspelled name left for compatibility*/
UINT8 				   PMUGetVCXOStabilizationTime(void);
void 				   PMUSetMfcConditions(UINT32 sysFreqConfig);
void 				   PMUMfcExit(void);
void                   pmuEnableETMClkWorkAround(void);
void                   pmuDisableETMClkWorkAround(void);
BOOL                   pmuIsIdleAllowed(void);
void                   PMUSSPclockSourceControlWrite ( UINT32   clkSrcCtrl );

void PMUI2cAPBClockOff( void );
void PMUI2cFuncClockOff( void );
void PMUI2cClockOff( void );

void PMUI2cAPBClockOn( void );
void PMUI2cFuncClockOn( void );
void PMUI2cClockOn( void );

#undef EXTERN

#else // !PERIPHERAL_CLOCKS_VIA_PMU_API
#define PMUPeripheralBothClocks(x,y)
#define PMUPeripheralAPBClock(x,y)
#define PMUPeripheralFunctionalClock(x,y)
#define PMUPeripheralReset(x)
#define PMUMSAClock(x,y)
#if !defined(PMU_API_DECOUPLING_STAGE_1)
#define	PMU_OFF FALSE
#define	PMU_ON  TRUE
typedef Bool PMUOnOff;
#define PMU_POR  1
#define PMU_EMR  2
#define PMU_WDTR 3
typedef struct
{
	UINT32  _PmuMSAUsersStatus;
	UINT32  _PmuBBLogicUsersStatus;
	UINT32	pmueFuncStatus;
	UINT32	_dmaChannelStatus;
}PMStatus_type;
typedef UINT32 PMU_LastResetStatus;
#endif  // !defined(PMU_API_DECOUPLING_STAGE_1)
#endif  // defined(PERIPHERAL_CLOCKS_VIA_PMU_API)
#endif  /* _PMU_H_ */

