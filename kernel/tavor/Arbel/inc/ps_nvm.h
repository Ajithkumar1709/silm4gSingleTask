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
#include "ps_nvm_defs.h"

#ifndef _PS_NVM_H_
#define _PS_NVM_H_

/***************************************************************************
 * Type Definitions
 **************************************************************************/
#define MAX_APN_NAME_NVM 100

//ICAT EXPORTED ENUM
typedef enum
{
  /* @ENUM_DESC@ Enable or Disable a feature */
  SYS_DISABLE = 0, /* @ENUM_VAL_DESC@ Enable this feature*/
  SYS_ENABLE  = 1  /* @ENUM_VAL_DESC@ Disable this feature*/
}systemfeatureenable_ts;

//ICAT EXPORTED ENUM
typedef enum    // 0 (disable), 1 (core only), 3 (core+PX), 7 (core+PX+drowsy), F (full)
{/* @ENUM_DESC@ Not used in Tavor */
  DISABLE = 0x0,
  CORE_ONLY  = 0x1,
  CORE_PX = 0x3,
  CORE_PX_DROWSY = 0x7,
  FULL = 0xF
}xscalePowerManagement_ts;

//ICAT EXPORTED ENUM
typedef enum    // 1 (ICAT ), 2 (Modem), 4 (Genie), 8 (MAST) ;; 3 (ICAT Modem), 5 (ICAT Genie), 7 (ICAT Modem Genie), A (ICAT Modem Genie MassStorage), F (full)
{
  /* @ENUM_DESC@ Defines the USB work mode - not to be changed for Tavor*/
  ICAT = 0x1,  /* @ENUM_VAL_DESC@ Configure USB to work with ACAT only*/
  MODEM = 0x2, /* @ENUM_VAL_DESC@ Configure USB to work as Modem only*/
  ICAT_MODEM = 0x3, /* @ENUM_VAL_DESC@ Configure USB to work with ACAT  and Modem*/
  GENIE = 0x4, /* @ENUM_VAL_DESC@ Configure USB to work with Genie only*/
  ICAT_GENIE = 0x5, /* @ENUM_VAL_DESC@ Configure USB to work with ACAT and Genie*/
  ICAT_MODEM_GENIE = 0x7, /* @ENUM_VAL_DESC@ Configure USB to work with ACAT Genie and as a Modem*/
  MAST = 0x8, /* @ENUM_VAL_DESC@ Configure USB to work as mass storage device only*/
  MODEM_MAST = 0xA, /* @ENUM_VAL_DESC@ Configure USB to work as Modem and mass storage device only*/
  USB_FULL = 0xF /* @ENUM_VAL_DESC@ Configure USB to work with ACAT, Genie, and as Modem and mass storage device in parallel*/
}USBConfiguration_ts;

//ICAT EXPORTED ENUM
typedef enum    // 0 (disable), 1 (core only), 3 (core+PX), 7 (core+PX+drowsy), F (full)
{ /* @ENUM_DESC@ Not used in Tavor */
  UF_NONE   = 0x0,
  UF_UART_1  = 0x1,
  UF_UART_2  = 0x2,
  UF_UART_1_2 = 0x3,
  UF_UART_3  = 0x4,
  UF_UART_1_3  = 0x5,
  UF_UART_2_3  = 0x6,
  UF_UART_1_2_3  = 0x7
}uartForceAwakeMode_ts;

//ICAT EXPORTED STRUCT
typedef struct
{ /* @STRUCT_DESC@ Protocol features */
  systemfeatureenable_ts PS_INIT_AUTO; /* @ITEM_DESC@ When enabled L2/3 will be initiated at power on. It is set to off mainly during calibration mode where L2\3 is not used. @ITEM_MODE@ ReadWrite @ITEM_UNIT@ Enable/Disable */
  systemfeatureenable_ts GSM_DRX_SLEEP; /* @ITEM_DESC@ Enables GSM DRX sleep @ITEM_MODE@ ReadWrite @ITEM_UNIT@ Enable/Disable */
  systemfeatureenable_ts WBCDMA_DRX_SLEEP; /* @ITEM_DESC@ Enables UMTS DRX sleep @ITEM_MODE@ ReadWrite @ITEM_UNIT@ Enable/Disable */
  systemfeatureenable_ts IN_GSM; /* @ITEM_DESC@ When enabled UE will start in GSM mode at power up @ITEM_MODE@ ReadWrite @ITEM_UNIT@ Enable/Disable */
  systemfeatureenable_ts ONLY_GSM; /* @ITEM_DESC@ prevent WCDMA measurements during GSM mode to prevent reselection to WCDMA - not used @ITEM_MODE@ ReadWrite @ITEM_UNIT@ Enable/Disable */
  systemfeatureenable_ts CIRCUIT_SWITCHED_ONLY; /* @ITEM_DESC@ if enabled it disables PS services @ITEM_MODE@ ReadWrite @ITEM_UNIT@ Enable/Disable */
  systemfeatureenable_ts RESERVED; /* @ITEM_DESC@ not used @ITEM_MODE@ ReadOnly @ITEM_UNIT@ not used */
  systemfeatureenable_ts UICC_PROTOCOL_T0_ONLY; /* @ITEM_DESC@ USIM - Force working with T=0 protocol @ITEM_MODE@ ReadWrite @ITEM_UNIT@ Enable/Disable */
}systemfeaturesParams_ts;


//ICAT EXPORTED ENUM
typedef enum    // 0 (disable), 1 (enable)
{ /* @ENUM_DESC@ PS-feature to reduce accesses to NVM */
    NVM_ACCESS_NORMAL_READ_WRITE,     /* @ENUM_VAL_DESC@ Always read,write GKI file from,to NVM*/
    NVM_ACCESS_REDUCED_ON_CFUN01_ONLY /* @ENUM_VAL_DESC@ Read GKI-file upon CFUN1, Write upon CFUN0 only*/
}psNvmAccessBehavior_e;

//ICAT EXPORTED STRUCT
typedef struct
{ /* @STRUCT_DESC@ Reserved - not used */
 psNvmAccessBehavior_e    psNvmAccessBehavior; /* @ITEM_DESC@ PS-feature to reduce NVM accesses, @ITEM_MODE@ ReadOnly, @ITEM_UNIT@ Enable/Disable */
 UINT8   isInProductionLine;
 UINT16  RESERVED1; /* @ITEM_DESC@ not used, @ITEM_MODE@ ReadOnly @ITEM_UNIT@ special dbg using */
}systemfeaturesUnderDevelopment_ts;

/*-----------------6/7/2007 3:09PM------------------
 * NVM programmable parameters for IOT
 * --------------------------------------------------*/
//ICAT EXPORTED STRUCT
typedef struct
{   /* @STRUCT_DESC@ Enables GSM GRR extended logging */
    systemfeatureenable_ts GRR_LOG_CELL_SELECTION_L3MSG; /* @ITEM_DESC@ Messages received in MphUnitDataInd during cell selection, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ Enable/Disable */
    systemfeatureenable_ts GRR_LOG_CCT_SWTCH_IDLE_L3MSG; /* @ITEM_DESC@ Messages received in MphUnitDataInd while in CCCH idle , @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ Enable/Disable */
    systemfeatureenable_ts GRR_LOG_CCT_SWTCH_ESTAB_L3MSG; /* @ITEM_DESC@ Messages received in MphUnitDataInd while establishing on RACH/AGCH, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ Enable/Disable */
    systemfeatureenable_ts GRR_LOG_PLMN_SEARCH_L3MSG; /* @ITEM_DESC@ Messages received in MphUnitDataInd while PLMN searching , @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ Enable/Disable */
    systemfeatureenable_ts GRR_LOG_CCT_SWTC_DED_L3MSG; /* @ITEM_DESC@ Messages received in DlUnitDataInd/DlDataInd in dedicated mode , @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ Enable/Disable */
    systemfeatureenable_ts GRR_LOG_RET_TO_IDLE_L3MSG; /* @ITEM_DESC@ Messages received in MphUnitDataInd while returning to idle state, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ Enable/Disable */
    systemfeatureenable_ts GRR_LOG_PKT_IDLE_CCCH_L3MSG; /* @ITEM_DESC@ All messages received in MphUnitDataInd in packet idle, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ Enable/Disable */
    systemfeatureenable_ts GRR_LOG_PKT_L3MSG; /* @ITEM_DESC@ Messages received in GrrMacPktControlInd (GRRPL3), @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ Enable/Disable */
    systemfeatureenable_ts GRR_LOG_PKT_SYS_INFO_MSG; /* @ITEM_DESC@ Packet System Information messages , @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ Enable/Disable */
    systemfeatureenable_ts GRR_LOG_IR_RESELECTION_L3MSG; /* @ITEM_DESC@ log Inter RAT reselection messages, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ Enable/Disable */
    systemfeatureenable_ts RESERVED1; /* @ITEM_DESC@ not used, @ITEM_MODE@ ReadOnly, @ITEM_UNIT@ not used */
    systemfeatureenable_ts RESERVED2; /* @ITEM_DESC@ not used, @ITEM_MODE@ ReadOnly, @ITEM_UNIT@ not used */
}GRRLogs_ts;

//ICAT EXPORTED ENUM
typedef enum
{ /* @ENUM_DESC@ UMTS RLC release 5 extention - changing the Acknowldege Mode (AM) buffer size */
    R5_EXT_KB200=0, /* @ENUM_VAL_DESC@ 200Kbyte*/
    R5_EXT_KB300=1, /* @ENUM_VAL_DESC@ 300Kbyte*/
    R5_EXT_KB400=2, /* @ENUM_VAL_DESC@ 400Kbyte*/
    R5_EXT_KB750=3  /* @ENUM_VAL_DESC@ 750Kbyte*/
}TotalRLC_AM_BufferSize_r5ext_ts;

//ICAT EXPORTED ENUM
typedef enum
{ /* @ENUM_DESC@ UMTS RLC - changing the RLC maximum window size */
    MWS2047 = 2047, /* @ENUM_VAL_DESC@ 2047*/
    MWS4095 = 4095  /* @ENUM_VAL_DESC@ 4095 - not supported*/
}MaximumRLC_WindowSize_ts;

//ICAT EXPORTED ENUM
typedef enum
{ /* @ENUM_DESC@ UMTS RLC - changing the Acknowldege Mode (AM) buffer size */
    DUMMY=0, /* @ENUM_VAL_DESC@ dummy*/
    KB10=1, /* @ENUM_VAL_DESC@ 10Kbyte*/
    KB50=2, /* @ENUM_VAL_DESC@ 50Kbyte*/
    KB100=3, /* @ENUM_VAL_DESC@ 100Kbyte*/
    KB150=4, /* @ENUM_VAL_DESC@ 150Kbyte*/
    KB500=5, /* @ENUM_VAL_DESC@ 500Kbyte*/
    KB1000=6, /* @ENUM_VAL_DESC@ 1000Kbyte*/
    SPARE=7 /* @ENUM_VAL_DESC@ not used*/
}TotalRLC_AM_BufferSize_ts;

//ICAT EXPORTED STRUCT
typedef struct
{ /* @STRUCT_DESC@ Part of the Mobile Equipement parameters reported to the network that can be changed. */
    TotalRLC_AM_BufferSize_r5ext_ts   TOTAL_RLC_AM_BUFFER_SIZE_R5EXT; // int8, default is UTotalRLC_AM_BufferSize_r5_ext_kb200 /* @ITEM_DESC@ Total UMTS RLC AM release 5 extention buffer size @ITEM_MODE@ ReadWrite @ITEM_UNIT@ see Structure definition  */
    TotalRLC_AM_BufferSize_ts         TOTAL_RLC_AM_BUFFER_SIZE;       // int8 /* @ITEM_DESC@ Total UMTS RLC AM buffer size @ITEM_MODE@ ReadWrite @ITEM_UNIT@ see Structure definition  */
    MaximumRLC_WindowSize_ts          MAX_RLC_WINDOW_SIZE;            // int16(?) /* @ITEM_DESC@ Maximum UMTS RLC window size @ITEM_MODE@ ReadWrite @ITEM_UNIT@ see Structure definition  */
    UINT8                             BIT_MAP_ALGO_A5_AVAILABLE;      // int 8 /* @ITEM_DESC@ Decleration of supported chipering algoritm for GSM @ITEM_MODE@ ReadWrite @ITEM_UNIT@ bitmap */
    UINT8                             BIT_MAP_ALGO_GPRS_AVAILABLE;    /* @ITEM_DESC@ Decleration of supported chipering algoritm for GPRS @ITEM_MODE@ ReadWrite @ITEM_UNIT@ bitmap */
    UINT8                             BIT_MAP_UEA1_UEA0;              /* @ITEM_DESC@ Decleration of supported chipering algoritm for UMTS @ITEM_MODE@ ReadWrite @ITEM_UNIT@ bitmap */
}MobileEquipment_ts;



typedef UINT16 Mcc;
//ICAT EXPORTED STRUCT
typedef struct
{/* @STRUCT_DESC@ MCC for PCS classmark 3. Used for debug, mainly during IOT */
	systemfeatureenable_ts isMccValid;  // use/not use the mcc  /* @ITEM_DESC@ If Enabled the below Mcc is used @ITEM_MODE@ ReadWrite @ITEM_UNIT@ Enable/Disable */
	Mcc mcc; /* @ITEM_DESC@ Mcc to use, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ mcc */
}MccForClassmark3_ts;

//ICAT EXPORTED STRUCT
typedef struct
{/* @STRUCT_DESC@ List of desired ARFCN's to search. Used to ignore other cells which we do not want to camp on .Used for Debug only mainly during IOT. This chose will be relevant during the initial cell search only. It will have no effect on the measurements, reselections and HHO.  */
	systemfeatureenable_ts		GrrCampOnDesArfcn; /* @ITEM_DESC@ When enabled, only the following list of ARFCN's will be searched @ITEM_MODE@ ReadWrite @ITEM_UNIT@ Enable/Disable */
	INT8						GrrCampOnDesNumberOfArfcn2Search; /* @ITEM_DESC@ Number of ARFCN's to search, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ 1-5 */
	UINT16						GrrCampOnDesArfcnList[5]; /* @ITEM_DESC@ List of ARFCN's to search, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@  ARFCN list*/

}GsmResidesArfcn_ts;

//ICAT EXPORTED STRUCT
typedef struct
{/* @STRUCT_DESC@ protocol paramaters that used mainly during IOT */
  GRRLogs_ts                        	GRRLogs;                        // 12*int8 /* @ITEM_DESC@ When enabled, only a provided list of ARFCN's will be searched @ITEM_MODE@ ReadWrite @ITEM_UNIT@ see Structure definition  */
  systemfeatureenable_ts            	GMM_REL_CONTEXT_T3312_EXPIRY;   // int8 /* @ITEM_DESC@ If disabled GMM will not release PDP context on T3312 expiry. For debug use. @ITEM_MODE@ ReadWrite @ITEM_UNIT@ Enable/Disable  */
  MobileEquipment_ts                	MobileEquipment;                // int8 /* @ITEM_DESC@ Mobile equipement parameters, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ see Structure definition  */
  MccForClassmark3_ts               	mccForPcsClassmark3; /* @ITEM_DESC@ MCC for PCS classmark 3. Used for debug, mainly during IOT @ITEM_MODE@ ReadWrite @ITEM_UNIT@ see Structure definition  */
  GsmResidesArfcn_ts					GsmResideOnlyOnFollowingARFCNs; /* @ITEM_DESC@ When enabled, only a provided list of ARFCN's will be searched @ITEM_MODE@ ReadWrite @ITEM_UNIT@ see Structure definition  */
  UINT16								LlcDisableUiHistoryCheckOnSapi; /* @ITEM_DESC@ Discarding duplicate UI frames on certain SAPI @ITEM_MODE@ ReadWrite @ITEM_UNIT@ none  */
}IOTParams_ts;
// end of NVM programmable parameters for IOT

typedef UINT32 VendorSpecificInfo_ts;/*CQ00047657 by zhangxia 20131106*/


//ICAT EXPORTED ENUM
typedef enum
{/* @ENUM_DESC@ Used for internal debug only */
    ACI_SW_DEFAULT   = 0,  //use SW default
    ACI_SAC_ONLY     = 1,
    ACI_GKI_ONLY     = 2,
    ACI_COMBINED     = 3
}AciSacGki_ts;


//=========================================================================

//ICAT EXPORTED STRUCT
typedef struct
{
   /* @STRUCT_DESC@ System and common Protocol configurable parameters */
   /* @STRUCT_NVM_FILE_NAME@ SystemControl.nvm */

   systemfeaturesParams_ts            featuresParams; /* @ITEM_DESC@ Protocol features @ITEM_MODE@ ReadWrite  @ITEM_UNIT@ see Structure definition   */
   systemfeaturesUnderDevelopment_ts  developmentSwitch; /* @ITEM_DESC@ reserved @ITEM_MODE@ ReadOnly  @ITEM_UNIT@ not used  */
   xscalePowerManagement_ts           xscalePowerManagement; /* @ITEM_DESC@ Not used in Tavor @ITEM_MODE@ ReadOnly  @ITEM_UNIT@ obsolate  */
   USBConfiguration_ts                USBConfiguration; /* @ITEM_DESC@ Defines the USB work mode - not to be changed for Tavor @ITEM_MODE@ ReadOnly  @ITEM_UNIT@ see Structure definition   */
   uartForceAwakeMode_ts              uartForceAwakeMode; /* @ITEM_DESC@ Not used in Tavor @ITEM_MODE@ ReadOnly  @ITEM_UNIT@ obsolate  */
   AciSacGki_ts                       aciSacGki; /* @ITEM_DESC@ Used for internal debug only @ITEM_MODE@ ReadOnly  @ITEM_UNIT@ see Structure definition   */
   VendorSpecificInfo_ts			  vendorSpecificInfo; /* @ITEM_DESC@ Enables Vendor specific requirements @ITEM_MODE@ ReadWrite @ITEM_UNIT@ bitmap of supported vendors.  */
   /*-----------------6/7/2007 3:11PM------------------
   * NVM programmable parameters for IOT
   * --------------------------------------------------*/
   IOTParams_ts                       IOTParams; /* @ITEM_DESC@ paremeters used mainly during IOT @ITEM_MODE@ ReadWrite  @ITEM_UNIT@ see Structure definition   */
   // end of NVM programmable parameters for IOT
/*Fixed CQ00024251 xyzheng for U+D optimistion start 2012-11-07*/
#if !defined(ON_PC)
    /*Fixed for U+D begin date: 2010-08-11 yinfei*/
   UINT8     						  optMethodFlag; /*@ITEM_DESC@ 0: optimization off  1: 1000 threhold version  2: test version for higher quility default is 1 */
  /*cgliu 20130922 for sync nvm*/
   //UINT8							   reserved2[3];
   UINT8                              ratioForHWMDiscardData; 
   UINT16                             GCFTimingAdvance;
   /*Fixed for U+D End date: 2010-08-11 yinfei*/ 
#endif
/*Fixed CQ00024251 xyzheng for U+D optimistion end 2012-11-07*/
   
   UINT32                             reserved2;  /* @ITEM_DESC@ reserved, @ITEM_MODE@ ReadOnly , @ITEM_UNIT@ not used  */
   UINT32                             reserved3;  /* @ITEM_DESC@ reserved @ITEM_MODE@ ReadOnly  @ITEM_UNIT@ not used  */
}SystemcNvm_ts;

#if 0
//ICAT EXPORTED STRUCT AutoDoc System
typedef struct
{
   /* @STRUCT_DESC@ System and common Protocol configurable parameters */
   /* @STRUCT_NVM_FILE_NAME@ CellLockProfile */
   UINT8 Mode; /*@ITEM_DESC@ 0: Unlocked  1: Arfcn locked  2: Arfcn and CellParameterId locked  3: LTE Cell sync detection enabled, default is 0*/
   UINT8 NetworkMode; /*@ITEM_DESC@ 0: GSM  1: TDD  2: TD LTE, default is 0(not supported) */

   UINT16 Arfcn; /*@ITEM_DESC@ if Unlocked, set it to 0xFFFF; TD number 10054-10121 and 9404-9596, TD LTE  37750-38249 and 38650-39649*/
   UINT16 CellParameterId; /*@ITEM_DESC@ if Unlocked or Arfcn locked, set it to 0xFFFF; TD 0-127, and TD LTE 0-503*/
   INT8  TddOffset; /*@ITEM_DESC@ if IRAT optimization disabled, set it to -85 */
}CellLockNvm_ts;
#endif

/*Alan DIP Channel support -- START*/
/*Commented by Lilei for CQ48496 on 11192013, begin*/

/*add for SRVCC & IMS at 20140321*/
//ICAT EXPORTED STRUCT AutoDoc System
typedef struct
{
   /* @STRUCT_DESC@ System and common Protocol configurable parameters */
   BOOL IMSNWReportStatus;
   BOOL NWIMSVoPS;
   BOOL EmerBearerSrvReportStatus;
   BOOL EmerBearerSRVIuStatus;
   BOOL EmerBearerSRVS1Status;
}IMSNWReportStatusNvm_ts;
#if 0
//ICAT EXPORTED STRUCT
typedef struct
{/* @STRUCT_DESC@ protocol paramaters that used mainly during Dip Channel Change */
  INT32                                 Band;                           //band: Dip band GSM : 0: EGSM 1:DCS 2:PCS 3:EGSM850;WCDMA: BAND1 BAND2...BAND14
  INT32                                 Arfcn;                          //dip_map_curr_num: Indicate current vlaid entry of map_array[].
  UINT32                                CpuFreqBitMap;                   //cpu_freq_bit_map:Every bit map a cpu frequency. bit is 1 indicate the channel not influenced by thi frequency, bit  is 0 indicate trhe channel is influenced by this frequency and system should not works on this frequency while in this channel.
  INT32                                 Resrve[CHAN_FREQ_MAP_STRUCT_RESERVE_SIZE]; 
  UINT8                                 NetworkMode;   //0: CI_DEV_NW_GSM; 1:CI_DEV_NW_UMTS
}ChanFreqMapStruct_ts;

//ICAT EXPORTED STRUCT
typedef struct
{/* @STRUCT_DESC@ protocol paramaters that used mainly during Dip Channel Change */
  INT32                                 DipEnable;                      //dip_enabled:A flag to disable and enable dip feature.0: dip feature disabled 1: dip feature enabled
  ChanFreqMapStruct_ts                  MapArray[CHAN_FREQ_MAP_STRUCT_MAP_ARRAY_SIZE];                   //map_array[64]
}DipChannelChangeStruct_ts;
#endif
/*Commented by Lilei for CQ48496 on 11192013, end*/
/*Alan DIP Channel support -- END*/
/*2014.02.07, mod by Xili for CQ00056284, begin*/
//#define MAX_TERM_PROFILE_SIZE    20
#define MAX_TERM_PROFILE_SIZE    64
/*2014.02.07, mod by Xili for CQ00056284, end*/

//ICAT EXPORTED STRUCT
typedef struct
{
   /* @STRUCT_DESC@ System and common Protocol configurable parameters */
   /* @STRUCT_NVM_FILE_NAME@ TermnialProfile */
   UINT8 LengthOfSatProfile; /* @ITEM_DESC@ Length of SAT profile, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ 0-20 */
   UINT8 SatProfile[MAX_TERM_PROFILE_SIZE]; /* @ITEM_DESC@ SAT Terminal Profile, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@  SAT profile*/
   
   UINT8 LengthOfUsatProfile; /* @ITEM_DESC@ Length of USAT profile, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@ 0-20 */
   UINT8 UsatProfile[MAX_TERM_PROFILE_SIZE]; /* @ITEM_DESC@ USAT Terminal Profile, @ITEM_MODE@ ReadWrite, @ITEM_UNIT@  USAT profile*/
}TermProfileNvm_ts;

/*Added by Alan for at+bglteplmn on 08032012, begin*/
#if 0
//ICAT EXPORTED STRUCT AutoDoc System
typedef struct
{
   /* @STRUCT_DESC@ System and common Protocol configurable parameters */
   /* @STRUCT_NVM_FILE_NAME@ BackgroundSearch */
   BOOL isBackgroundSearch; /* TRUE: enabled,FALSE: disabled*/
   UINT16 backgroundSearchInterval; /* uint:minutes,00:immediately search;15,30,60 minutes;0xFFFF don't search*/
}BackgroundSearchNvm_ts;
#endif
/*Added by Alan for at+bglteplmn on 08032012, end*/

#if 0
/*Added by Alan for PDN config on 09052012, begin*/

//ICAT EXPORTED ENUM autoDoc
typedef enum
{
   /* @STRUCT_DESC@ System and common Protocol configurable parameters */
   /* @STRUCT_NVM_FILE_NAME@ BackgroundSearch */
   PDN_TYPE_IP_V4 = 0x1,
   PDN_TYPE_IP_V6 = 0x2,
   PDN_TYPE_IP_V4_V6 = 0x3,
   PDN_TYPE_UNUSED = 0x4
}PdnType_ts;

//ICAT EXPORTED ENUM autoDoc
typedef enum
{
  PDN_CONFIG_PROTOCOL_PPP = 0,
  PDN_CONFIG_PROTOCOL_OSP_IHOSS = 1
}ConfigurationProtocol_ts;

//ICAT EXPORTED STRUCT AutoDoc System
typedef struct
{
    ConfigurationProtocol_ts   protocol;
    UINT16             length;
    UINT8              data [250];
}ProtocolConfigOptions_ts;

//ICAT EXPORTED ENUM autoDoc
typedef enum
{
  REQ_TYPE_INITIAL = 1,  /* initial request */
  REQ_TYPE_HANDOVER = 2, /* Handover */
  REQ_TYPE_UNUSED = 3,   /* If received, the network shall interpret this as "initial request". */
  REQ_TYPE_EMERGENCY = 4 /* emergency */
}RequestType_ts;
#if 0
//ICAT EXPORTED STRUCT AutoDoc System
typedef struct
{
   /* @STRUCT_DESC@ System and common Protocol configurable parameters */
   /* @STRUCT_NVM_FILE_NAME@ PdnConfig */
   PdnType_ts PdnType; 
   RequestType_ts ReqType;
   ProtocolConfigOptions_ts   pppConfigOpts;
   BOOL   eitfPresent;
   BOOL   apnNamePresent;
   UINT8  length; //length of apname
   UINT8  apnName[MAX_APN_NAME_NVM];
}PdnConfigNvm_ts;
/*Added by Alan for PDN config on 09052012, end*/
#endif
#endif

/***************************************************************************
 * Functions Prototypes
 **************************************************************************/
BOOL psNvmCreate(void);
BOOL psNvmRead(void);
void psNvmAciSET(void);
BOOL psNvmAciSacIsWorking(void);
BOOL psNvmAciGkiIsWorking(void);
BOOL psNvmVendorSpecificEnabled(UINT32);/*CQ00047657 by zhangxia 20131106*/

/* add by yuling for printf vendor information 20101102 begin */
BOOL psVendorPrintf(void );
/* add by yuling for printf vendor information 20101102 end */

//BOOL psNvmReadCellLockInfo(void);
//BOOL psNvmCreateCellLockInfo(CellLockNvm_ts* params);
//void psNvmGetCellLockInfo(CellLockNvm_ts* params);

BOOL psNvmReadIMSNWReportInfo(void);
BOOL psNvmCreateIMSNWReportInfo(IMSNWReportStatusNvm_ts* params);
void psNvmGetIMSNWReportInfo(IMSNWReportStatusNvm_ts* params);
/*Alan DIP Channel support -- START*/
/*Commented by Lilei for CQ48496 on 11192013, begin*/
//BOOL psNvmDIPChannelChangeRead(void);
/*Commented by Lilei for CQ48496 on 11192013, end*/
/*Alan DIP Channel support -- END*/

BOOL psNvmReadTermProfile(void);
BOOL psNvmSaveTermProfile(UINT8 *satProfile, UINT8 len, BOOL isUsat);
/*add by xyma for CQ00125818 begin*/
BOOL psNvmReadPsmContext(UINT8 simId);
void psNvmSavePsmContext(UINT8 *psmCtx, UINT8 simId, unsigned short psmSize);
/*add by xyma for CQ00125818 end*/
/*Added by Alan for at+bglteplmn on 08032012, begin*/
//BOOL psNvmReadBackgroundSearchInfo(void);
//BOOL psNvmCreateBackgroundSearchInfo(BackgroundSearchNvm_ts* params);
//void psNvmGetBackgroundSearchInfo(BackgroundSearchNvm_ts* params);
/*Added by Alan for at+bglteplmn on 08032012, end*/

/*Added by Alan for PDN config on 09052012, begin*/
BOOL psNvmReadPdnConfigInfo(void);
//BOOL psNvmCreatePdnConfigInfo(PdnConfigNvm_ts* params);/*zhangxia 20130801*/
//void psNvmGetPdnConfigInfo(PdnConfigNvm_ts* params);
/*Added by Alan for PDN config on 09052012, end*/


#endif

