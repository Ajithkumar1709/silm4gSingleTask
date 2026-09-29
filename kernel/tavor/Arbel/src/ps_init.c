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

//
// WCDMA Wireless modem manager
//
#include <stdlib.h>
#include "hal_cfg.h"

#include "osa.h"
#include "diag.h"
#include "diag_types.h"
#include "os_tick.h"
#include "sys_version.h"

#if defined (_HERMON_) || defined (_DATAOMSL_ENABLED_)
#include "usb_device.h"
#include "usbmgr_apps_config.h"
#include "UsbMgr.h"
#include "usbmgrttpal.h"
extern void    USBMgrTTPALUpdateEnabledApps(UINT32 mask_app, UINT8 card);
#endif /* (_HERMON_) || (_DATAOMSL_ENABLED_)*/

#include "UART.h"

#if defined (_HERMON_)
#include "power_manager.h"
#endif//_HERMON_

#include "ps_nvm.h"

// Relevant WCDMA L1 APIs
#include "pl_d_api.h"
#include "pl_d_bind.h"

#if defined (INTEL_FDI)
#include "FDI_EXT.h"
#include "FDI_FILE.h"
#include "FDI_ERR.h"
#include "runvars.h"
#endif

#if defined(EE_HANDLER_ENABLE)
#include "EEHandler.h"
#endif

#if defined (MEMORY_TEST)
#include "diag_Mem_Test.h"
#endif //(MEMORY_TEST)

// Define the Init-task priority for running TTPCom initializations: MUST be higher than any TTPCom task
#if defined(OSA_API_VERSION) && (OSA_API_VERSION>=43) && !defined(OSA_NO_PRIORITY_CONVERSION)
	#define INIT_TASK_PRIORITY_FOR_PS_INIT 0
#else
	//RR Shuld be the higest PS & L1 TTPCom tasks priorities
	#define INIT_TASK_PRIORITY_FOR_PS_INIT 12
#endif
#if defined(ENABLE_DM_LTEONLY)
extern void L1aPsExternalInitialize (void);
#endif//ENABLE_DM_LTEONLY

extern UINT8 gPowerupSaveTimeFlag;
extern UINT8 gPowerupPsInitFastFlag;

/* CampOnDesired functions */
extern UINT8 GrrJetLeeNumberOfArfcn2Search;
extern void GrrJetLeeSetPermission(Boolean permission);																									   // Enable
extern void GrrJetLeeGetNumberOfArfcn2Search(Int8 NumArfcns2Search);
extern void GrrJetLeeGetArfcnList(Int16 *GrrCampOnDesArfcnList, Int8 NumArfcns2Search);
extern SystemcNvm_ts    systemcNvmParams;
extern IMSNWReportStatusNvm_ts      IMSNWReportModeParams;
//extern CellLockNvm_ts   cellLockParams;
extern TermProfileNvm_ts termProfileParams;
/*Commented by Lilei for CQ48496 on 11192013, begin*/
//extern DipChannelChangeStruct_ts    dipChannelChangeParams;
/*Commented by Lilei for CQ48496 on 11192013, end*/
/*Added by Alan for at+bglteplmn on 08032012, begin*/
//extern BackgroundSearchNvm_ts       backgroundSearchParams;
/*Added by Alan for at+bglteplmn on 08032012, end*/

/*Added by Alan for PDN config on 09052012, begin*/
//extern PdnConfigNvm_ts    pdnConfigParams;
/*Added by Alan for PDN config on 09052012, end*/

//UINT32 sys_L1InitDone;		// indicate L1 init was done to support the RF tool (gRait)

void setTxInitPower (INT8* txInitPower);
extern void ICATsetNetworkMode(int nmode);
extern void ICATsetServiceType(int svcType);
extern void ICATsetUserMode(int userMode);
extern void ICATsetHsdpaMode(INT8 enable);
/*-----------------6/6/2007 11:03AM-----------------
 *  NVM programmable parameter for IOT
 * --------------------------------------------------*/
extern void UpdateGrrlogs(Int16 Grr_logs);
extern void UpdateIsInProductionLine (Boolean isInProductionLine);
extern void UpdateRelContextT3312Expiry(unsigned char relCntxT3312Expiry);
extern void updateMccForClassmark3 (Mcc mcc);
extern void UpdateLlcDisableUiHistoryCheckOnSapi(Int16 bitmap);

extern unsigned char SetTotalRlcAMBufferSize_r5_ext (UINT8 size);
extern unsigned char SetMaxRLCWimdowSize (UINT16 size);
extern unsigned char SetTotalRlcAMBufferSize (UINT8 size);
extern unsigned char SetCipheringA5Algo (UINT8 algoA5);
extern unsigned char SetGprsAlgo (UINT8 GprsAlgo);
extern unsigned char SetUeaCapAlgo (UINT8 UeaCapAlgo);
// end of NVM programmable parameter for IOT

void setUSBApplications (UINT16* nmode);
void setUSBApplicationsInt (UINT16* nmode);

extern void ICATWbMeasBlock(void);
//extern void setHplmnATIsUMTS(void);
extern void hadSetUiccTransmissionProtocolT0Only (void);

#if defined (MEMORY_TEST)
extern signed long	    TTP_GetPeakDynamicPoolMemoryAllocated(void);
extern signed short 	TTP_GetPeakStaticPoolMemoryAllocated(signed short poolType);
extern signed long 		TTP_GetDynamicPoolMemorySize(void);
extern signed long 		TTP_GetStaticMemoryPoolSize(signed short poolType);
extern signed short 	TTP_GetStaticMemoryBlockSize(signed short poolType);
extern signed short 	TTP_GetStaticMemoryNumOfBlocks(signed short poolType);

extern void				TTP_ResetPeakDynamicPoolMemory(void);
extern void             TTP_ResetPeakStaticPoolMemory(void);

#endif //(MEMORY_TEST)


#if defined (_HERMON_)
extern   void ipcTriggerInit(void);
#else
/*STUB*/ void ipcTriggerInit(void) {;} // Activate the NVM based DSP command/message triggers - to be implemented for HARBELL
extern   void GKITickRegister(void);
#endif


#if defined (MSL_INCLUDE)
extern void    MslInit_Stubs(void);
extern void    MslServerAudioStubInit(void);
 #if !defined(MSL_EXCLUDE_CCI)
extern void ciServerStubInit(void);
 #endif
#endif




void psInit_PS_INIT(void);

BOOL   USBConfiguration_ACATrequested=FALSE;
//mask for setting USB applications
//UINT16 ps_init_usb_app_mask= (UINT16)((UINT16)USBMGR_ICAT_APPID | (UINT16)USBMGR_MODEM_APPID | (UINT16)USBMGR_GENIE_APPID | (UINT16)USBMGR_MAST_APPID);
UINT16 ps_init_usb_app_mask = 0;
extern void UsbMgrTTPALSetMuxUSB(void);
extern void UsbMgrTTPALSetMuxUART(void);
extern void setUSBApplicationsMask (UINT16* nmode);

//extern BOOL psNvmReadPsmContext(unsigned char simId);
static BOOL psUsbCompositIsAvailable(void)
{
  BOOL useUsb = FALSE;
#if defined (_HERMON_) || defined (_DATAOMSL_ENABLED_)
  if(!psNvmAciSacIsWorking())
      useUsb = TRUE;
#endif
  return(useUsb);
}

static void psInit_Composite_ApplicationsMask(void)
{
    psNvmAciSET(); //set correct configuration

    if(USBConfiguration_ACATrequested == FALSE) //TRUE - do not modify. This is the User Request
    {
        ps_init_usb_app_mask = systemcNvmParams.USBConfiguration;
        //clean bits for unsupported configurations (Genie and Mass-Storage)
        ps_init_usb_app_mask &= ~((UINT16)(USBMGR_GENIE_APPID | USBMGR_MAST_APPID));

        if(!psUsbCompositIsAvailable())
          ps_init_usb_app_mask &= ~((UINT16)USBMGR_MODEM_APPID);
    }
    DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS9,DIAG_INFORMATION)
    diagPrintf("COMPOSITE USB status %e {USBConfiguration_ts}", ps_init_usb_app_mask);
}


#if !defined (INTEL_2CHIP_PLAT_BVD)

// This function is responsible for bringing the WCDMA L1 into the active state
// by executing plwReset and pldInit() asynchronously
// Then the Protocol stack initialization function is invoked


static OSSemaRef psiL1Sema;
static void pldCnf(void)
{
  if(psiL1Sema) OSASemaphoreRelease(psiL1Sema);
  else
  {
   #if !defined(UPGRADE_LTE_ONLY)
   #ifndef  REMOVE_WB
    DIAG_FILTER(APLP,INIT,PSINIT_ERR1,DIAG_ERROR)
    diagTextPrintf("PS_INIT: unexpected L1 callback invokation");
   #endif
	#endif
  }
}

extern void L1cPlpAdapterInit(void);//ma xinhua for temp test
#if defined (ENABLE_CAT1_LG) || defined(DS3_LTE_ONLY)
  #if !defined (NO_AUDIO)
void audioPhase2Init( void );
  #endif // !NO_AUDIO
#endif
static int L1Init(BOOL noL1autoStart)
{
#ifdef MACRO_FOR_LTG
	DIAG_FILTER(BOOT,BOOT_TASK,L1Init_1,DIAG_INFORMATION)
	diagPrintf("L1CTDDebug arbel L1Init is called");
	L1cPlpAdapterInit();
#endif
  if((OSASemaphoreCreate(&psiL1Sema,0,OS_FIFO))!=OS_SUCCESS) return 0;

  pldBindResetCnf(pldCnf);
  pldBindInitCnf(pldCnf);

  ipcTriggerInit(); // Activate the NVM based DSP command/message triggers (takes effect only if IpcTriggers.nvm file exist)

  if(!noL1autoStart)
  {

  DIAG_FILTER(BOOT,BOOT_TASK,L1Init_1,DIAG_INFORMATION)
  diagPrintf("plAMReset is called");

		/* CQ00107195 - htfeng: Single LTE for Cat1/m  begin */
#if defined (SUPPORT_LTE_IRAT)//CQ00108274
	  DIAG_FILTER(BOOT,BOOT_TASK,L1Init_x,DIAG_INFORMATION)
			  diagPrintf("pldReset() begin");

	  pldReset();
      DIAG_FILTER(BOOT,BOOT_TASK,L1Init_2,DIAG_INFORMATION)
        diagPrintf("pldReset() finish");

      #if 0 //dismiss by fhguan
	  #if !defined (ENABLE_CAT1_LG)
	  OSASemaphoreAcquire(psiL1Sema,OS_SUSPEND);
	  #endif
      	{
			pldInit();
		}
	  DIAG_FILTER(BOOT,BOOT_TASK,L1Init_3,DIAG_INFORMATION)
        diagPrintf("OSASemaphoreAcquire(psiL1Sema,OS_SUSPEND) suspend");
	  #if !defined (ENABLE_CAT1_LG)
	  OSASemaphoreAcquire(psiL1Sema,OS_SUSPEND);
	  #endif
	  #if defined (ENABLE_CAT1_LG)
	  #if !defined (NO_AUDIO)
           			audioPhase2Init();
      #endif /* NO_AUDIO */
	  #endif
      #else
      OSASemaphoreAcquire(psiL1Sema,OS_SUSPEND);

      pldInit();
      OSASemaphoreAcquire(psiL1Sema,OS_SUSPEND);
	  #endif
#else
	  {
		  extern void plAMReset(void);
		  plAMReset();
		  #if defined(DS3_LTE_ONLY)

          #if !defined (NO_AUDIO)
          audioPhase2Init();
          #endif /* NO_AUDIO */
		  #endif
	  }
#endif
	  /* CQ00107195 - htfeng: Single LTE for Cat1/m  end */


  }
  OSASemaphoreDelete(psiL1Sema);
  psiL1Sema=0;

#if defined (MEMORY_TEST)
	 EXT_SetMemoryFunctionsPtr(TTP_GetPeakDynamicPoolMemoryAllocated,
				  	 	 	   TTP_GetPeakStaticPoolMemoryAllocated,
						 	   TTP_GetDynamicPoolMemorySize,
							   TTP_GetStaticMemoryPoolSize,
						 	   TTP_GetStaticMemoryBlockSize,
						 	   TTP_GetStaticMemoryNumOfBlocks,
							   TTP_ResetPeakDynamicPoolMemory,
							   TTP_ResetPeakStaticPoolMemory);
#endif // (MEMORY_TEST)

#ifdef MACRO_FOR_LTG
  DIAG_FILTER(BOOT,BOOT_TASK,L1Init_2,DIAG_INFORMATION)
  diagPrintf("L1CTDDebug arbel L1Init is finished");
#endif
  return 1;
}
#endif //!(INTEL_2CHIP_PLAT_BVD)


static void TTPComStackStart(void);
static void psIsRunningAction(void);


#if !defined( GERAN_ONLY )
extern void hawExternalInitialize(void);
#else /* GERAN_ONLY */
extern void   hagExternalInitialize(void);
#endif /* GERAN_ONLY */
extern void expGetSteppingID(void);

/*add by xyma for CQ00125818 begin*/
/* Added by Daniel for CQ00114325 20190412, begin */
extern BOOL CommPMExitPSM(unsigned long *escape_time);
extern BOOL psmExitResult;
extern UINT32 t3412EscapeSecond;
extern void psInitPsmContextNvm(UINT8 simId);
/* Added by Daniel for CQ00114325 20190412, end */
/*add by xyma for CQ00125818 end*/
//UINT8 bReadPsm = 0;
/*************************************************************
*/

OSATaskRef		PsInitFastaskRef;
void* 			PsInitFastStack;
OSATimerRef 	TimerDeletePsInitFastTask;

void DeletePsInitFastTaskByTimer(UINT32 id)
{
    OSA_STATUS status;

	//RTI_LOG("DeletePsInitFastTaskByTimer");

    if(PsInitFastaskRef)
    {
        status = OSATaskDelete(PsInitFastaskRef);
        ASSERT(status == OS_SUCCESS);

        if(PsInitFastStack)
        {
            free(PsInitFastStack);
            PsInitFastStack = NULL;
        }
    }

    OSATimerDelete (TimerDeletePsInitFastTask);
}

void PS_init_fast_thread(void  * arg)
{
	 //RTI_LOG("PS_init_fast_thread");

   if (systemcNvmParams.featuresParams.PS_INIT_AUTO)
   	  psInit_PS_INIT();


#if defined (INTEL_2CHIP_PLAT_BVD)
    { //This is blocking procedure, so do it last!
     extern void ciRegisterClientApp(char/*CiServiceGroupID*/ dummy);
     ciRegisterClientApp(0);            // SAC client side registration
    }
#endif

}

void PS_init_fast_task(void)
{
	OSA_STATUS status = OS_SUCCESS;

	if(PsInitFastStack == NULL)
		PsInitFastStack = malloc(2048);

	if(PsInitFastaskRef == NULL)
	{
		status = OSATaskCreate(&PsInitFastaskRef, PsInitFastStack, 2048, 79, "PS_init_fast", PS_init_fast_thread, NULL); //higher than DmNvPTasK(80)
	    ASSERT(status == OS_SUCCESS);
    }

	if(TimerDeletePsInitFastTask == NULL)
		OSATimerCreate(&TimerDeletePsInitFastTask);
    OSATimerStart(TimerDeletePsInitFastTask, 200*10, 0, DeletePsInitFastTaskByTimer, 0);

//	RTI_LOG("%s, PsInitFastaskRef=0x%p, PsInitFastStack=0x%p",__func__,PsInitFastaskRef,PsInitFastStack);
}
extern unsigned char isPSMExit(unsigned char simId);
int WPSGMInit(void)
{
  /*-----------------6/7/2007 1:35PM------------------
  * NVM programmable parameter for IOT
  * --------------------------------------------------*/

  #if defined(LABEL_ID)
  char str[100];
  sprintf(str,"TTPCom Label: %s",LABEL_ID);
  DIAG_FILTER(SYSTEM,TTPCOM_LABEL,RELEASE_FULL_NAME,DIAG_INFORMATION)
  diagPrintf("%s",str );
  #endif
  DIAG_FILTER(SYSTEM,SYSTEM_BUILD,RELEASE_FULL_NAME,DIAG_INFORMATION)
  diagPrintf("Release: SYSTEM %s", SYSTEM_RELEASE_NAME);
  DIAG_FILTER(SYSTEM,SYSTEM_BUILD,RELEASE_DATE,DIAG_INFORMATION)
  diagPrintf("Release creation date: %s", SYSTEM_RELEASE_CREATION_DATE);
  DIAG_FILTER(SYSTEM,SYSTEM_BUILD,RELEASE_COMMENTS,DIAG_INFORMATION)
  diagPrintf("Release comments: SYSTEM %s", SYSTEM_RELEASE_COMMENTS);
#ifdef _HERMON_
  expGetSteppingID();
#endif
#if !defined(UPGRADE_LTE_ONLY)
#ifndef  REMOVE_WB
  DIAG_FILTER(APLP,INIT,PSINIT_START,DIAG_INFORMATION)
  diagTextPrintf("Starting the L1: Please, reset the DSP now...");
#endif
#endif
 psNvmRead();
 DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS1,DIAG_INFORMATION)
 diagPrintf("PS INIT AUTO status %e {systemfeatureenable_ts}",systemcNvmParams.featuresParams.PS_INIT_AUTO);
 DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS2,DIAG_INFORMATION)
 diagPrintf("GSM DRX SLEEP status %e {systemfeatureenable_ts}",systemcNvmParams.featuresParams.GSM_DRX_SLEEP);
 DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS3,DIAG_INFORMATION)
 diagPrintf("WBCDMA DRX SLEEP status %e {systemfeatureenable_ts}",systemcNvmParams.featuresParams.WBCDMA_DRX_SLEEP);
 DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS4,DIAG_INFORMATION)
 diagPrintf("GSM status %e {systemfeatureenable_ts}",systemcNvmParams.featuresParams.IN_GSM);
 DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS5,DIAG_INFORMATION)
 diagPrintf("CIRCUIT SWITCHED ONLY status %e {systemfeatureenable_ts}",systemcNvmParams.featuresParams.CIRCUIT_SWITCHED_ONLY);
 DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS6,DIAG_INFORMATION)
 diagPrintf("Xscale Power Management status %e {xscalePowerManagement_ts}",systemcNvmParams.xscalePowerManagement);
 DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS7,DIAG_INFORMATION)
 diagPrintf("ONLY GSM status %e {systemfeatureenable_ts}",systemcNvmParams.featuresParams.ONLY_GSM);
 //DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS8,DIAG_INFORMATION)
 //diagPrintf("HPLMN UMTS status %e {systemfeatureenable_ts}",systemcNvmParams.featuresParams.HPLMN_UMTS);
// DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS9,DIAG_INFORMATION)
// diagPrintf("COMPOSITE USB status %e {USBConfiguration_ts}",systemcNvmParams.USBConfiguration);
 DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS10,DIAG_INFORMATION)
 diagPrintf("UART force wake mode %e {uartForceAwakeMode_ts}",systemcNvmParams.uartForceAwakeMode);
 DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS11,DIAG_INFORMATION)
 diagPrintf("UICC use only T=0 transmission protocol %e {systemfeatureenable_ts}",systemcNvmParams.featuresParams.UICC_PROTOCOL_T0_ONLY);
 DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS12,DIAG_INFORMATION)
 diagPrintf("NvmAccessBehavior %e {psNvmAccessBehavior_e}",systemcNvmParams.developmentSwitch.psNvmAccessBehavior);

#ifdef MACRO_FOR_LTG
 psNvmReadIMSNWReportInfo();
 DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS313,DIAG_INFORMATION)
 diagStructPrintf("IMSNWReport info %S{IMSNWReportStatusNvm_ts}", &IMSNWReportModeParams, sizeof(IMSNWReportStatusNvm_ts));
#endif

 psNvmReadTermProfile();
 DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS14,DIAG_INFORMATION)
 diagStructPrintf("SAT/USAT terminal profile %S{TermProfileNvm_ts}", &termProfileParams, sizeof(TermProfileNvm_ts));

 /*Commented by Lilei for CQ48496 on 11182013, begin*/
 //psNvmDIPChannelChangeRead();
 //DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUS15,DIAG_INFORMATION)
 //diagStructPrintf("NvmDIPChannelChange %S{DipChannelChangeStruct_ts}",&dipChannelChangeParams,sizeof(DipChannelChangeStruct_ts));
 /*Commented by Lilei for CQ48496 on 11182013, end*/
 /*add by xyma for CQ00125818 begin*/
/* Added by Daniel for PSM 20180201, begin */
 //bReadPsm = 0;
 if(psNvmReadPsmContext(0) ==  TRUE)
{
   if(1 == isPSMExit(0))
	   psInitPsmContextNvm(0);
   // FDI_remove(PSM_CONTEXT_FILE_NAME);
}
 if(psNvmReadPsmContext(1) == TRUE)
 {
	 if(1 == isPSMExit(1))
	   psInitPsmContextNvm(1);
   // FDI_remove(PSM_CONTEXT_FILE_NAME1);
}

 /* Added by Daniel for CQ00114325 20190412, begin */
 psmExitResult = CommPMExitPSM(&t3412EscapeSecond);
/* Added by Daniel for CQ00114325 20190412, end */

/* Added by Daniel for PSM 20180201, end */
/*add by xyma for CQ00125818 begin*/
 psInit_Composite_ApplicationsMask();

#if defined (_HERMON_)
 // Set UART wake mode
 pmUartInitForce(systemcNvmParams.uartForceAwakeMode);
#endif

#if defined(EE_HANDLER_ENABLE)
  // Print the current EEHandler configuration
  {
   extern void eePrintConfiguration(void);
   eePrintConfiguration();
  }
#endif

#if defined (FULLYARDEN)
	DIAG_FILTER(APLP,INIT,Sleepb4L1Init,DIAG_INFORMATION)
    diagPrintf("calling Sleep before L1Init, 10 seconds");
	OSATaskSleep(2000); // 10 sec
#endif

#if !defined (INTEL_2CHIP_PLAT_BVD) || !defined (_TAVOR_BOERNE_)
  if(systemcNvmParams.developmentSwitch.RESERVED1 & (1<<1))
  {
      DIAG_FILTER(SYSTEM,SYSNVM,NVMSTATUSdbg,DIAG_INFORMATION)
      diagPrintf("NO L1 INIT AUTO - developmentSwitch.RESERVED1 BIT1 is set");
      L1Init(1);
  }
  else
  {
    if(!L1Init(0))
    {
	   #if !defined(UPGRADE_LTE_ONLY)
        #ifndef  REMOVE_WB
        DIAG_FILTER(APLP,INIT,PSINIT_ERROR,DIAG_ERROR)
        diagTextPrintf("L1 startup failed");
		#endif
		#endif
    }
    else
    {
	    #if !defined(UPGRADE_LTE_ONLY)
        #ifndef  REMOVE_WB
        DIAG_FILTER(APLP,INIT,PSINIT_DONE,DIAG_INFORMATION)
        diagTextPrintf("L1 ready: Starting the protocol stack...");
		#endif
		#endif
		//sys_L1InitDone=1;
    }
  }
#endif/*INTEL_2CHIP_PLAT_BVD*/


  TTPComStackStart();


#if defined(EE_HANDLER_ENABLE)
  {
  //Bind the TTPCom error handling functionality to EEHandler
  extern void CfErrorHandlerBind(void);  // NEW KIOSFAIL implementation and HAFAILCF adaptation module
  CfErrorHandlerBind();
  }
#endif

 // SETUP DSP (IPC) FILTERS
 {
  extern void setupDspFilters(void);
  setupDspFilters();
 }

if(gPowerupPsInitFastFlag) //move CI init to higher priority task than DmNvPTasK(80)
{
	PS_init_fast_task();
}
else
{
	 if (systemcNvmParams.featuresParams.PS_INIT_AUTO)
	   psInit_PS_INIT();


	#if defined (INTEL_2CHIP_PLAT_BVD)
		{ //This is blocking procedure, so do it last!
		 extern void ciRegisterClientApp(char/*CiServiceGroupID*/ dummy);
		 ciRegisterClientApp(0);            // SAC client side registration
		}
	#endif
}

#if 0
 extern void CPASendDVCSettingToDSP(void);
 CPASendDVCSettingToDSP();
#endif


 return 1;
}


typedef unsigned char Boolean;
extern Boolean  abmmGprsAttachAtPowerOn;
#if !defined (GERAN_ONLY)
extern void ICATsetTxInitPower(char txInitPower);
#endif

//ICAT EXPORTED FUNCTION - PS, UMTS, setAttachAtPwrOn
void setAttachAtPwrOn (UINT16* attach)
{
  abmmGprsAttachAtPowerOn = (Boolean)*attach;
}

#if 0
/*//ICAT EXPORTED FUNCTION - PS, UMTS, setReconfigWithSyncA
Boolean icatSetReconfigWithSyncA = FALSE;
void setReconfigWithSyncA (UINT16* reconfigWithSyncA)
{
  icatSetReconfigWithSyncA = (Boolean)*reconfigWithSyncA;
}  */
#endif
#if !defined (GERAN_ONLY)
//ICAT EXPORTED FUNCTION - PS, UMTS, setTxInitPower
void setTxInitPower (INT8* txInitPower)
{
#if !defined(ENABLE_DM_LTEONLY)
	ICATsetTxInitPower((char)*txInitPower);
#endif//ENABLE_DM_LTEONLY
}
#endif

//ICAT EXPORTED FUNCTION - PS, UMTS, setServiceType
void setServiceType (UINT16* svcType)
{
    ICATsetServiceType((int)*svcType);
}

//ICAT EXPORTED FUNCTION - PS, UMTS, setNetworkMode
void setNetworkMode (UINT16* nmode)
{
	// sets the network mode to UMTS or GSM
	ICATsetNetworkMode((int)*nmode);
}

//ICAT EXPORTED FUNCTION - PS, UMTS, setUserMode
void setUserMode (UINT16* nmode)
{
	// sets the user mode
	ICATsetUserMode((int)*nmode);
}


#if 0 //defined (_HERMON_) || defined (_DATAOMSL_ENABLED_)
//this should be sent in the very begining to change the default mask
//ICAT EXPORTED FUNCTION - PS, USB, setUSBApplicationsMask
void setUSBApplicationsMask (UINT16* nmode)
{
  ps_init_usb_app_mask = *nmode;
  USBConfiguration_ACATrequested=TRUE;

}


UINT32 ps_init_ttpal_was_initialized=FALSE;

void setUSBApplicationsInt (UINT16* nmode)
{
    volatile UINT32 mask_app = (UINT32) *nmode;
	UINT32 apps;
	UINT8  card;

	apps = mask_app&0xFF;
	card = (mask_app&0xFF00)>>8;

    if(ps_init_ttpal_was_initialized == FALSE)
    {
        //call ttpal init
        UsbMgrTTPALInit();
        ps_init_ttpal_was_initialized=TRUE;
    }

    USBMgrTTPALUpdateEnabledApps(apps, card);

    //update the
    USBMgrTempFuncUpdateHardCodedUSBDescriptor(apps);
}

//ICAT EXPORTED FUNCTION - PS, USB, setUSBApplications
void setUSBApplications (UINT16* nmode)
{
    DIAG_FILTER(PS, USB, SET_USB_APP_REP,DIAG_INFORMATION)
    diagTextPrintf("USB Connection will be OFF now for ~3seconds");

    OSATaskSleep(60); //

    //unplug USB cable
    USBMgrDeviceUnplug();

    OSATaskSleep(600);

	setUSBApplicationsInt(nmode);

	//plug USB cable in again
    USBMgrDevicePlugIn();
}


//1 - USB,  AT commands are directed to USB
//0 - UART, AT commands are directed to UART
//ICAT EXPORTED FUNCTION - PS, AT_MUX, setATMux
void setATMux (UINT16* nmode)
{

    if(*nmode == 1)
    {
        UsbMgrTTPALSetMuxUSB();
        DIAG_FILTER(PS, AT_MUX, AT_MUX_SET_USB,DIAG_INFORMATION)
        diagTextPrintf("AT Commands Mux is set to USB");
    }
    else
    {
        if(*nmode == 0)
        {
            UsbMgrTTPALSetMuxUART();
            DIAG_FILTER(PS, AT_MUX, AT_MUX_SET_UART,DIAG_INFORMATION)
            diagTextPrintf("AT Commands Mux is set to UART");
        }
        else
        {
            DIAG_FILTER(PS, AT_MUX, AT_MUX_SET_WRONG,DIAG_INFORMATION)
            diagTextPrintf("Wrong Mux , no action taken");
        }
    }
}

#endif/*_HERMON_  *USB*/


// THE CK value is 128-bit (16 bytes) and is printed in little-endian format (lowest byte first)
#define SECURITY_KEY_LENGTH 16
void ICATexportCipheringInfo(int isCsDomain, unsigned char* pCk)
{
 if(isCsDomain)
 {
   DIAG_FILTER(PS, UMTS, CIPHERING_PARAMS_CS,DIAG_INFORMATION)
   diagStructPrintf("New ciphering parameters for CS domain:",pCk,SECURITY_KEY_LENGTH);
 }
 else
 {
   DIAG_FILTER(PS, UMTS, CIPHERING_PARAMS_PS,DIAG_INFORMATION)
   diagStructPrintf("New ciphering parameters for PS domain:",pCk,SECURITY_KEY_LENGTH);
 }
}

//ICAT EXPORTED FUNCTION - PS, UMTS, ICATtestCipheringInfo
void ICATtestCipheringInfo(UINT8* p)
{
   ICATexportCipheringInfo((p[0]!=0), &p[4]);
}

//ICAT EXPORTED FUNCTION - PS, FDI, PSInformationDelete
void PSInformationDelete(void)
{
#if defined (INTEL_FDI)
	FILE_INFO  info;

	while (FDI_findfirst("TTPCom_NRAM2_*.*", &info) == 0 )
	{
		FDI_remove (info.file_name);
	    DIAG_FILTER(PS,FDI,DATA_ERASE,DIAG_INFORMATION)
        diagPrintf("Erasing file %s", info.file_name );

	}
 #else
   DIAG_FILTER(PS,FDI,DATA_ERASE1,DIAG_INFORMATION)
   diagPrintf("FDI not supported");
#endif
}

#ifdef USE_ICAT_ASA_COMMAND_INSTEAD_REAL_USB_OR_UART
//ICAT EXPORTED FUNCTION - ASA,AT_COMM,ASADiagRcvAtCmd
void asaRcvAtCmd(char* rcvAtCmd)
{
	// print string to ICAT
//    DIAG_FILTER(ASA,AT_COMM,ASADiagRcvAtCmd,DIAG_INFORMATION);
//    diagPrintf("asaRevAtCmd: %s", rcvAtCmd);

	// call SPAL code
#if defined (OLDTTP_3GPS_USED)
	spalReceiveAtCmd(rcvAtCmd);
#endif
}

void asaSendAtCmd(char* sendAtCmd)
{
	DIAG_FILTER(ASA,AT_COMM,ASADiagSendAtCmd,DIAG_INFORMATION);
    diagPrintf("%s", sendAtCmd);
}
#endif//ASA

/************************************************************************************
*
*   TTPCom stack Init/Start/Run procedures
*
*************************************************************************************
*/
// GKI publics
extern void   KiOsReset (void);
extern void   KiOsTick (UINT32    increment); /*FrameTicks increment*/
extern UINT32 KiOsMaximumSleep(UINT32 ticks);
extern BOOL   KiOsTimersStartedOrStopped(void);

/* Required for accurate Genie logging */
extern UINT32 GetTCRTimerCnt(void);
#ifdef _HERMON_
UINT32 timeAtKiOsTick;
#else
extern UINT32 timeAtKiOsTick; //from GKITick.c
#endif


void psKiOsTick (UINT32    increment)
{
  KiOsTick(increment*65);
  timeAtKiOsTick = GetTCRTimerCnt();
}


UINT32 psKiOsMaximumSleep(UINT32 ticks)
{
    // GKI (fine ticks, xK, K=65)  vs. OS (5ms ticks)
	// ticksToSleep (OS ticks)
	//  =   (ticksToSleepFine<=K) ? (1) : (ticksToSleepFine<=2*K) ? 2: (...)
	//	=   ((ticksToSleepFine+K-1)/K)
	return (KiOsMaximumSleep(ticks*65)+65-1)/65;
}


//=======================================================================
void TTPComStackStart(void)
{
  OSATaskRef rootTaskRef;
  UINT8      oldPriority;

 // TTPCom initialization requires the root task (running KiOsReset) to be the highest priority
  OSATaskGetCurrentRef(&rootTaskRef);
  OSATaskChangePriority(rootTaskRef,INIT_TASK_PRIORITY_FOR_PS_INIT,&oldPriority);

#if defined(INTEL_2CHIP_PLAT)
  {extern void reconfig_abcfDefaultForegroundTask(void);
    reconfig_abcfDefaultForegroundTask();
  }
#endif

  KiOsReset();

  //Set back default priority will really start the TTPCom stack
  OSATaskChangePriority(rootTaskRef,oldPriority,&oldPriority);

 /* Give a time for TTPCom task to start running */
  OSATaskSleep(5);
#ifdef _HERMON_  /*YANM to be modified */
  extTickBind(psKiOsTick, psKiOsMaximumSleep);
  extTickIdlecallBind(KiOsTimersStartedOrStopped );
#else
  GKITickRegister();
#endif
}

/*
*------------------------------------------------------------------------------
*   Some Intel's components are using the TTMCom Stack.
*          (diag and GENIE for example)
*   This "cooperation" must be synchronized on startup!
*   The EXPORT psIsRunningStatus() provides information "TTPCom Ready And Running".
*   Some components may require an action delayed until synchronization.
*   If this is required, open the define PS_RUNNING_NUM_ACTIONS.
*-------------------------------------------------------------------------------
*/
//////  #define PS_RUNNING_NUM_ACTIONS  4
typedef void pFuncVoidVoid(void);

#if defined (PS_RUNNING_NUM_ACTIONS)
static pFuncVoidVoid* psIsRunning_Actions[PS_RUNNING_NUM_ACTIONS] = {NULL};
#endif


/** Refer diag_API.h
typedef BOOL	(*DiagPSisRunningFn) (void);
void SetDiagSigPScheckFn(DiagPSisRunningFn diagSigPsCheckFn);
**/

static Boolean   psIsRunningStatusVar = FALSE;

Boolean psIsRunningStatus(void)
{
    return (psIsRunningStatusVar);
}

static void psIsRunningAction(void)
{
    SetDiagSigPScheckFn(psIsRunningStatus);
    #if !defined(UPGRADE_LTE_ONLY)
    #ifndef  REMOVE_WB
    DIAG_FILTER(APLP,INIT,PSINIT_PSDONE,DIAG_INFORMATION)
    diagTextPrintf("Done: Protocol stack is running");
	#endif
	#endif
    psIsRunningStatusVar = TRUE;

#if defined (PS_RUNNING_NUM_ACTIONS)
    {   int i = 0;
        for(i=0; i< PS_RUNNING_NUM_ACTIONS; i++)
        {
            if(psIsRunning_Actions[i] != NULL)
               psIsRunning_Actions[i]();
        }
    }
#endif
}

#if defined (PS_RUNNING_NUM_ACTIONS)
void psIsRunning_BindAction(pFuncVoidVoid* pFunc)
{
    int i = 0;
    //Mutex Get
    for(i=0; i< PS_RUNNING_NUM_ACTIONS; i++)
        if(psIsRunning_Actions[i] == NULL)
        {
           psIsRunning_Actions[i] = pFunc;
           break; //don't i++
        }
    ASSERT(i<PS_RUNNING_NUM_ACTIONS);
    //Mutex Restore
}
#endif//PS_RUNNING_NUM_ACTIONS
#if !defined(UPGRADE_LTE_ONLY)
#ifndef	REMOVE_WB
//ICAT EXPORTED FUNCTION - PS, UMTS, setHsdpaMode
void setHsdpaMode (UINT16* hmode)
{
	// sets the hsdpa mode
	if(*hmode)
	{
	    DIAG_FILTER(APLP,INIT,SET_HSDPA_MODE_SUP,DIAG_INFORMATION)
    	diagTextPrintf("setHsdpaMode called, mode = SUPPORTED");
		ICATsetHsdpaMode(TRUE);
	}
	else
	{
	    DIAG_FILTER(APLP,INIT,SET_HSDPA_MODE_UNSUP,DIAG_INFORMATION)
    	diagTextPrintf("setHsdpaMode called, mode = UNSUPPORTED");
		ICATsetHsdpaMode(FALSE);
	}

	DIAG_FILTER(APLP,INIT,SET_HSDPA_MODE_RESET,DIAG_INFORMATION)
   	diagTextPrintf("P L E A S E   R E S E T   T H E   U E , HSDPA Mode has been changed.");
}
#endif
#endif
#ifdef MACRO_FOR_LTG
Boolean GetSystemcNvmMobileEquipment()
{
    Boolean changed=FALSE;

    changed |= SetTotalRlcAMBufferSize(systemcNvmParams.IOTParams.MobileEquipment.TOTAL_RLC_AM_BUFFER_SIZE);
    changed |= SetTotalRlcAMBufferSize_r5_ext(systemcNvmParams.IOTParams.MobileEquipment.TOTAL_RLC_AM_BUFFER_SIZE_R5EXT);
    changed |= SetMaxRLCWimdowSize (systemcNvmParams.IOTParams.MobileEquipment.MAX_RLC_WINDOW_SIZE);
    //changed |= SetCipheringA5Algo (systemcNvmParams.IOTParams.MobileEquipment.BIT_MAP_ALGO_A5_AVAILABLE); /*CQ00046171 20131021 by zhangxia for samsung need change A5*/
    changed |= SetGprsAlgo (systemcNvmParams.IOTParams.MobileEquipment.BIT_MAP_ALGO_GPRS_AVAILABLE);
    changed |= SetUeaCapAlgo (systemcNvmParams.IOTParams.MobileEquipment.BIT_MAP_UEA1_UEA0);
    return(changed);
}
#endif

/*******************************************************************
* psInit_PS_INIT()      - utilities to be called AUTO
* psInit_PS_INIT_ACAT() -       or manually from ACAT
********************************************************************/
void psInit_PS_INIT(void)
{
      Int16 BitMap = 0;

#if defined (_HERMON_) || defined (_DATAOMSL_ENABLED_)  /*USB*/
  USBDevice_StatusE usb_status = USB_DEVICE_STATUS_NOT_CONNECTED;

  volatile  UINT32 usb_enum_cnt=0;
  volatile  UINT32 diag_ready_cnt=0;
#endif /* (_HERMON_) || (_DATAOMSL_ENABLED_) */

#if(0) //enable MSA clock manager
{
  /*POWER_MANAGER_DEBUG_COMMAND, STATE_CHANGE (7), core_idle=ON, XFU (flash protection)=ON, clock_manager=OFF*/
  extern void IPCICATSendDSPData (void* pv);
  UINT16 data1[] = {0x00E5, 0x0002, 0x000C};
  UINT16 msaPmMode[] = {0x00F6, 0x0004, 0x0007, 0x0004 };
  IPCICATSendDSPData((void*)msaPmMode);
}
#endif


  psIsRunningAction();


#if !defined (INTEL_2CHIP_PLAT_BVD)
 // Configure sleep and power management
 {
  extern UINT32 L1GsmPmDisableDrxSleep(void *s);
  extern UINT32 L1GsmPmEnableDrxSleep(void *s);
  extern void plwEnableSleepMode(BOOL* en);
  extern void plDratEnableSleepMode(BOOL* en);
  UINT8 WBCDMA_DRX_SLEEP=FALSE;
  // GSM DRX_SLEEP
  if (systemcNvmParams.featuresParams.GSM_DRX_SLEEP)
	L1GsmPmEnableDrxSleep(0);
  else    L1GsmPmDisableDrxSleep(0);
  // WBCDMA DRX_SLEEP
  if (systemcNvmParams.featuresParams.WBCDMA_DRX_SLEEP)
	   WBCDMA_DRX_SLEEP=TRUE;

#ifdef MACRO_FOR_LWG
  plwEnableSleepMode(&WBCDMA_DRX_SLEEP);
#endif
#ifdef MACRO_FOR_LTG
  plDratEnableSleepMode(&WBCDMA_DRX_SLEEP);
#endif
#ifdef _HERMON_
  // Enable XScale Power Management
  pmModeSet (systemcNvmParams.xscalePowerManagement); // 0 (disable), 1 (core only), 3 (core+PX), 7 (core+PX+drowsy), F (full)
#endif//_HERMON_
 }

if (systemcNvmParams.featuresParams.IN_GSM)
	 ICATsetNetworkMode(0);//GSM
if (systemcNvmParams.featuresParams.ONLY_GSM)
{
#if !defined(ENABLE_DM_LTEONLY)
	ICATsetNetworkMode(0);//GSM
	ICATWbMeasBlock();
#endif//ENABLE_DM_LTEONLY
}
//if (systemcNvmParams.featuresParams.HPLMN_UMTS)
//	setHplmnATIsUMTS();

//#if defined(_HERMON_) || defined(_TAVOR_HARBELL_)
#if defined(_HERMON_)
if(systemcNvmParams.featuresParams.UICC_PROTOCOL_T0_ONLY)
	hadSetUiccTransmissionProtocolT0Only();
#endif// (defined _HERMON_) || (defined _TAVOR_HARBELL_)

if (systemcNvmParams.featuresParams.CIRCUIT_SWITCHED_ONLY)
	 ICATsetServiceType(0);//CIRCUIT_SWITCHED_ONLY

/*-----------------6/7/2007 1:35PM------------------
 * NVM programmable parameter for IOT
 * --------------------------------------------------*/
  /* Bit map for GrrLog is as follow:
 * -------------------------------------------------------------------------------------------------------------------------
 *        B9     |      B8  |B7 |   B6      |  B5     |  B4       |   B3        |  B2         |  B1        |   B0         |
 * |IrReselection|PktSysInfo|Pkt|PktIdleCcch|RetToIdle|CctSwtchDed|LogPlmnSearch|CctSwtchEstab|CctSwtchIdle|CellSelection |
 *  * ----------------------------------------------------------------------------------------------------------------------*/

    BitMap=
    (systemcNvmParams.IOTParams.GRRLogs.GRR_LOG_CELL_SELECTION_L3MSG) |
    (systemcNvmParams.IOTParams.GRRLogs.GRR_LOG_CCT_SWTCH_IDLE_L3MSG << 1) |
    (systemcNvmParams.IOTParams.GRRLogs.GRR_LOG_CCT_SWTCH_ESTAB_L3MSG << 2) |
    (systemcNvmParams.IOTParams.GRRLogs.GRR_LOG_PLMN_SEARCH_L3MSG << 3) |
    (systemcNvmParams.IOTParams.GRRLogs.GRR_LOG_CCT_SWTC_DED_L3MSG << 4) |
    (systemcNvmParams.IOTParams.GRRLogs.GRR_LOG_RET_TO_IDLE_L3MSG << 5) |
    (systemcNvmParams.IOTParams.GRRLogs.GRR_LOG_PKT_IDLE_CCCH_L3MSG << 6) |
    (systemcNvmParams.IOTParams.GRRLogs.GRR_LOG_PKT_L3MSG << 7) |
    (systemcNvmParams.IOTParams.GRRLogs.GRR_LOG_PKT_SYS_INFO_MSG << 8) |
    (systemcNvmParams.IOTParams.GRRLogs.GRR_LOG_IR_RESELECTION_L3MSG << 9);

#if !defined(ENABLE_DM_LTEONLY)
    UpdateGrrlogs(BitMap);
#endif//ENABLE_DM_LTEONLY
    UpdateRelContextT3312Expiry(systemcNvmParams.IOTParams.GMM_REL_CONTEXT_T3312_EXPIRY);
#if !defined(ENABLE_DM_LTEONLY)
	UpdateIsInProductionLine(systemcNvmParams.developmentSwitch.isInProductionLine);
#endif//ENABLE_DM_LTEONLY

	if(systemcNvmParams.IOTParams.mccForPcsClassmark3.isMccValid == SYS_ENABLE)
	{
#if !defined(ENABLE_DM_LTEONLY)
		updateMccForClassmark3(systemcNvmParams.IOTParams.mccForPcsClassmark3.mcc);
#endif//ENABLE_DM_LTEONLY
	}

	if(systemcNvmParams.IOTParams.GsmResideOnlyOnFollowingARFCNs.GrrCampOnDesArfcn == SYS_ENABLE)
	{
#if !defined(ENABLE_DM_LTEONLY)
		GrrJetLeeSetPermission(TRUE);                                                                      							       // Enable
		GrrJetLeeGetNumberOfArfcn2Search(systemcNvmParams.IOTParams.GsmResideOnlyOnFollowingARFCNs.GrrCampOnDesNumberOfArfcn2Search);  // How many ARFCNs
		GrrJetLeeGetArfcnList(&systemcNvmParams.IOTParams.GsmResideOnlyOnFollowingARFCNs.GrrCampOnDesArfcnList[0], GrrJetLeeNumberOfArfcn2Search); // Copy the ARFCN from NVM to GRR data base
#endif//ENABLE_DM_LTEONLY
	}

	UpdateLlcDisableUiHistoryCheckOnSapi(systemcNvmParams.IOTParams.LlcDisableUiHistoryCheckOnSapi);

  // end of changes for "NVM programmable parameter for IOT" */
#endif/*INTEL_2CHIP_PLAT_BVD*/

//if (!systemcNvmParams.featuresParams.COMPOSITE_USB)
//	 ps_init_usb_app_mask= (UINT16)USBMGR_ICAT_APPID;



//============ Full start for the TTPCom ============
#if defined (INTEL_2CHIP_PLAT_SRV)
  {void Srv_hawExternalInitialize(int forceParam);   Srv_hawExternalInitialize(0);}
#else
#if !defined( GERAN_ONLY )
#if !defined(ENABLE_DM_LTEONLY)
   hawExternalInitialize();
#else//ENABLE_DM_LTEONLY
   L1aPsExternalInitialize();
#endif//ENABLE_DM_LTEONLY
#else /* GERAN_ONLY */
hagExternalInitialize();
#endif /* GERAN_ONLY */
#endif

//------------- MSL Stubs init --------------------------------
#if defined(MSL_INCLUDE)
  #ifdef _HERMON_
     MslInit_Stubs(); //TTPCom must be running at this point
  #else /* not _HERMON_ but _TAVOR_HARBELL_ */
    //COMM side  with MSL
    #if !defined(MSL_EXCLUDE_CCI)
	if(0 == gPowerupSaveTimeFlag)
	{
     	ciServerStubInit();
	}
	else
	{
		extern void ciRegisterClientApp(char/*CiServiceGroupID*/ dummy);
		ciRegisterClientApp(0);
	}
    #endif
//	if (GetCpuVersion() < CPU_NEVO_B0) //AG - PROCIDA does not supported from NEVO B0 and ESHEL LTE

    //2012-0612, don't need this in Wujing audio
    #ifndef PHS_SW_DEMO_TTC
     MslServerAudioStubInit();
    #endif
  #endif
#endif
//-------------------------------------------------------------
}

//ICAT EXPORTED FUNCTION - PS, PS_INIT, PS_INIT
void psInit_PS_INIT_ACAT(void)
{
    if(systemcNvmParams.featuresParams.PS_INIT_AUTO)
        return; //Already done

    DIAG_FILTER(PS,PS_INIT,Started,DIAG_INFORMATION)
    diagPrintf("PS_INIT manual Started");

    psInit_PS_INIT();

    DIAG_FILTER(PS,PS_INIT,Finished,DIAG_INFORMATION)
    diagPrintf("PS_INIT manual Finished");
}


int psNvmAccessIs_ReducedOnlyCfun0Cfun1(void)
{
  return((int)(systemcNvmParams.developmentSwitch.psNvmAccessBehavior == NVM_ACCESS_REDUCED_ON_CFUN01_ONLY));
}

#ifdef MACRO_FOR_LTG
void ICATsetTxInitPower(char txInitPower)
{
    return;
}
#endif


/*********************************************************************************************************************************************
function: GetCampedPlmnImeiSvn
description: customer can define different imeisvn according to camped plmn, this api called by PS.
input: UINT16 mcc,UINT16 mnc,UINT8 mncLength , attach mcc mnc 
output: UINT8* imeisvn
return:
       TRUE,  PS will get imeisvn and send to network in attach procedure
       FALSE, will use default imeisv in mobile equiment nvm file 
***********************************************************************************************************************************************/

BOOL GetCampedPlmnImeiSvn(Int16 mcc,Int16 mnc,Boolean bThreeDigitsMncLength,Int8* imeisvn)
{
#if 0
    DIAG_FILTER(PS,PS_INIT,GETIMEISV,DIAG_INFORMATION)
    diagPrintf("GetCampedPlmnImeiSvn,mcc=0x%x,mnc=0x%x,bThreeDigitsMncLength=%d,imeisvn=0x%x",mcc,mnc,bThreeDigitsMncLength,imeisvn);

    if(imeisvn == NULL)
    {
    	return FALSE;
    }
	
    if(mcc == 0x460 && mnc == 0x00)
	{
	    imeisvn[0] = 1;
		imeisvn[1] = 2;
		return TRUE;
	}
	else if(mcc == 0x460 && mnc == 0x01)
	{
	    imeisvn[0] = 1;
		imeisvn[1] = 3;
		return TRUE;
	}
    return FALSE;
#else
    return FALSE;
#endif
}
