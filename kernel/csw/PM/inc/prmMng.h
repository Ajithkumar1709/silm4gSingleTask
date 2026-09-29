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
* Title: prmMng.h
*
* Filename: prmMng.h
*
* PMU Header file
*
* Authors:    Idan Bartura
*
* Description:
*
* Last Updated:
*
* Notes:
*******************************************************************************/
#ifndef _PRMMNG_H_
#define _PRMMNG_H_

#include "global_types.h"
#include "syscfg.h"


#if defined _PMU_H_ && defined FLAVOR_COM
#define PMU_PRM_MNG_ALREADY_DONE_SKIP_THIS
#endif

#ifndef PMU_PRM_MNG_ALREADY_DONE_SKIP_THIS

#if defined FLAVOR_COM
#include "commpm.h"
#include "aam.h"
#include "prm.h"
#endif

#if defined FLAVOR_APP
#include "prm.h"
#endif

#define PRMMNG_INCLUDE_FILE_IN_USE


/* Those defined should be enveloped in PMU define to avoid conflict till pmu.h is removed*/
#if !defined (PMU_INCLUDE_FILE_IN_USE) 
typedef enum
{
	PMU_RC_WRONG_VALUE = -100,
    PMU_RC_OK = 0,
	PMU_RC_POR,
	PMU_RC_EMR,
    PMU_RC_WDTR = (PMU_RC_EMR+2)
}PMU_ReturnCode;

typedef struct
{
	UINT32  _PmuMSAUsersStatus;
	UINT32  _PmuBBLogicUsersStatus;
	UINT32	pmueFuncStatus;
	UINT32	_dmaChannelStatus;
}PMStatus_type;
#endif

/*----------- Global function prototypes -------------------------------------*/
/*Those functions were implemented in BRN APPS for Power backward compatibility with BSP*/
PMU_ReturnCode         PMUPhase1Init(void);                       /* implemented in pm_brn_apps.c */
void			       PMUPhase2Init(void);                       /* implemented in pm_brn_apps.c */
void PMUendInit(void);											  /* implemented in pm_brn_apps.c */
void PMUendInitForce(void);										  /* implemented in pm_brn_apps.c */


/*----------- TAVOR API - these API should be used from managing resources -------------------------------------*/

/* the new API which should be used are from prm.h - these are the TAVOR power resource management APIs */

/* PRM_EXTERN void                 PRMManage			(PRM_ServiceE		resource,
											 		 PRM_AllocFreeE		pmallocFree);

PRM_EXTERN PRM_ReturnCodeE      PRMServiceFreqSet(PRM_ServiceE   resource,
                                           PRM_ServiceFreqE newServiceFreq);

PRM_EXTERN PRM_ServiceFreqE     PRMServiceFreqGet(PRM_ServiceE   resource);


PRM_EXTERN PRM_ReturnCodeE      PRMSWReset  (PRM_ServiceE resource);


PRM_EXTERN PRM_resourceStatusE  PRMGetResourceStatus(PRM_ServiceE resource);


PRM_EXTERN PRM_ReturnCodeE PRMRegisterWakeupControl (PRM_WU_ServiceE resource,
									 PRM_CallbackFuncWakeupT CBwakeupfunction,
									 PM_PowerStatesE FromDxState,
									 PM_PowerStatesE ToDxState);


PRM_EXTERN PRM_ReturnCodeE PRMRegisterForNonRetainState(PRM_NRS_ServiceE resource,
									   	PRM_CallbackFuncPrepareT CBprepare,
									   	PRM_CallbackFuncRecoverT CBrecover);


PRM_EXTERN PRM_ReturnCodeE PRMUnRegisterForNonRetainState (PRM_NRS_ServiceE resource);

//The below functions are used in Harbell before interrupt disable in LPT.
PRM_EXTERN void PRMRegisterBeforeIntDisable (PRM_ServiceE resource,
					                    PRM_CallbackFuncBeforeIntT    cbkBeforeIntDis);

PRM_EXTERN void PRMDoBeforeIntDis(void);
// API for exception handling - to set resource clock but ignore it for D2 decisions/deepSleep
PRM_EXTERN void PRMTurnOnAndIgnoreLpmSrvc(PRM_ServiceE Srvc, UINT32 bExceptionState); */




/*----------- Old APIs of Hermon - should be removed!!!!!!!!!!!!!!!!! -------------------------------------*/

/* All below functions are Hermon API and should be removed from the code - they should be called. */

//void                   PMUPeripheralFunctionalClock(PMUPeripherals peripheralName, PMUOnOff onOff); /* implemented in pmu.c */
//void                   PMUPeripheralAPBClock(APBPeripherals peripheralName, PMUOnOff onOff); /* implemented in pmu.c */
//void                   PMUPeripheralBothClocks(BothPeripherals peripheralName, PMUOnOff onOff); /* implemented in pmu.c */
//void                   PMUPeripheralReset(BothPeripherals peripheralName);  /* implemented in pmu.c */
//void 				   PMUResetAllPeripherals(void);  /* implemented in pmu.c */
//PMUOnOff               PMUPeripheralFunctionalClockStatus(PMUPeripherals peripheralName); /* implemented in pmu.c */
//PMUOnOff               PMUPeripheralAPBClockStatus(APBPeripherals peripheralName);  /* implemented in pmu.c */
//PMU_BothClocksStatus   PMUPeripheralBothClocksStatus(BothPeripherals peripheralName);  /* implemented in pmu.c */
//void                   PMUDSPReset(BOOL releaseFromReset);  /* implemented in pmu.c */
//void                   PMUDSPResetRelease(void);  /* implemented in pmu.c */
//void                   PMUBBLogicReset(BOOL releaseFromReset);   /* implemented in pmu.c */
//void                   PMUBBLogicResetRelease(void);  /* implemented in pmu.c */
//void                   PMUMemcClock(PMUOnOff onOff, PMUMemcUsers memcUser);  /* implemented in pmu.c */
//void                   PMUMSAClock(PMUOnOff onOff, PMUMsaUsers msaUser);  /* implemented in pmu.c */
//BOOL 				   PMUMsaClockUsersStatus(void);    /* implemented in pmu.c */
//void                   PMUBBLogicClock(PMUOnOff onOff, PMUBBLogicUsers bbLogicUser); /* implemented in pmu.c */
//BOOL 				   PMUIsApbRequired(void);   /* implemented in pmu.c */
//void 				   PMUAllowApbIdleMode(BOOL idleModeAllow);  /* implemented in pmu.c */
//BOOL 				   PMUIsPxIdleAllowed(void);  /* implemented in pmu.c */
//void 				   PMUSetSleepConditions(PMUSleepModes sleepMode);  /* implemented in pmu.c */
//void 				   PMUSleepExit(void); /* implemented in pmu.c */
//PMU_ReturnCode         PMUMfcReq(PMUFrequencies *frequencyCombination, PMUForce forceMfc);
//PMU_ReturnCode         PMUSfcReq(PMUSfcDividers clockDivider, UINT32 divValue);  /* implemented in pmu.c */
//void                   PMUDrowsyWakeupPortMask(PMUWakeupPortNumber portNumber, BOOL maskUnmask);  /* implemented in pmu.c */
//void                   PMUMSLClockDetectorControl(PMUOnOff onOff);    /* implemented in pmu.c */
//PMU_LastResetStatus    PMULastReset(void);  /* implemented in pmu.c */
//void                   PMUForceClockMode(PMUOnOff onOff);  /* implemented in pmu.c */
//void                   PMUAPBForceClockMode(PMUOnOff onOff);  /* implemented in pmu.c */
//void                   PMUAPBPowerConsumptionMode(PMUOnOff onOff);  /* implemented in pmu.c */
//UINT32                 PMUWriteReg(PMURegistersList pmuReg, UINT32 value, UINT32 mask);  /* implemented in pmu.c */
//UINT32                 PMUReadReg(PMURegistersList pmuReg);   /* implemented in pmu.c */
//UINT32                 PMUMultiClock(UINT32 value, UINT32 mask);  /* implemented in pmu.c */
//#define PMUGetVCXOStandbyTime PMUGetVCXOStabilizationTime        /*misspelled name left for compatibility*/
//UINT8 				   PMUGetVCXOStabilizationTime(void);   /* implemented in pmu.c */
//void 				   PMUSetMfcConditions(UINT32 sysFreqConfig); /* implemented in pmu.c */
//void 				   PMUMfcExit(void); /* implemented in pmu.c */
//void                   pmuEnableETMClkWorkAround(void);  /* implemented in pmu.c */
//void                   pmuDisableETMClkWorkAround(void);  /* implemented in pmu.c */
//BOOL                   pmuIsIdleAllowed(void); /* implemented in pmu.c */
//void                   PMUSSPclockSourceControlWrite ( UINT32   clkSrcCtrl ); /* implemented in pmu.c */

//void PMUI2cAPBClockOff( void );
//void PMUI2cFuncClockOff( void );
//void PMUI2cClockOff( void );

//void PMUI2cAPBClockOn( void );
//void PMUI2cFuncClockOn( void );
//void PMUI2cClockOn( void );

#endif //PMU_PRM_MNG_ALREADY_DONE_SKIP_THIS

#endif  /* _PRMMNG_H_ */
