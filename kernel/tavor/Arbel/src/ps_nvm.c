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

/******************************************************************************
 * Include Files
 *****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include "FDI_EXT.h"
#include "FDI_FILE.h"
#include "osa.h"
#if defined (INTEL_FDI)
#include "fdi_header_support.h"
#endif
#include "diags.h"
#include "ps_nvm.h"
#include "ps_nvm_defs.h"
#include "platform_nvm.h"
/*add by xyma for CQ00125818 begin*/
/* Added by Daniel for PSM 20180201, begin */
//#include "ps_psm.h"
/* Added by Daniel for PSM 20180201, end */
/*add by xyma for CQ00125818 begin*/
/******************************************************************************
 * Global Variables
 *****************************************************************************/

SystemcNvm_ts                systemcNvmParams;

//CellLockNvm_ts               cellLockParams;
IMSNWReportStatusNvm_ts      IMSNWReportModeParams;
TermProfileNvm_ts            termProfileParams;

/*add by xyma for CQ00125818 begin*/
/* Added by Daniel for PSM 20180201, begin */
//extern PsmContext psmContext;
//PsmContext psmContext[SIM_NUM];
//extern PsmContext psmContext[];
/* Added by Daniel for PSM 20180201, end */
//extern UINT8 bReadPsm [2];
//UINT8 readPsm[2];
/*add by xyma for CQ00125818 begin*/
/*Added by Alan for at+bglteplmn on 08032012, begin*/
//BackgroundSearchNvm_ts       backgroundSearchParams;

/*Added by Alan for at+bglteplmn on 08032012, end*/
/*Commented by Lilei for CQ48496 on 11192013, begin*/
//DipChannelChangeStruct_ts    dipChannelChangeParams;
/*Commented by Lilei for CQ48496 on 11192013, end*/
/*Added by Alan for PDN config on 09052012, begin*/ 
// moved to AB module
//PdnConfigNvm_ts    pdnConfigParams;
/*Added by Alan for PDN config on 09052012, end*/

/******************************************************************************
 * Local Functions Prototypes
 *****************************************************************************/

/*-----------------6/7/2007 2:30PM------------------
 * NVM programmable parameter for IOT
 * --------------------------------------------------*/
extern BOOL 	GetRelContextT3312ExpiryDefault(void);
extern UINT16	GetGrrLogDefault(void);
extern UINT8 	GetTotalRlcAMBufSizeDefault(void);
extern UINT8 	GetGeaAlgoAvailableDefault(void);
extern UINT8 	GetCipheringA5AlgoaDefault(void);
extern UINT8 	GetGetTotalRlcAMBufferSize_r5_ext_Default(void);
extern UINT16 	GetMaxRLCWimdowSizeDefault(void);
extern UINT8 	GetUeaCipheringAlgorithmCapDefault(void);

/* Data module platforms including 1802s/1803/1826/1828 */
extern void duster_updateprofile(char *profile, unsigned int profile_len);


/******************************************************************************
 * Local Functions
 *****************************************************************************/

#if 0
 // ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 //
 //  function: psNvmSetCellLockNvmDefaultParams
 //
 //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmSetCellLockNvmDefaultParams(void)
{
  cellLockParams.Mode = 0;
  cellLockParams.Arfcn = 0xFFFF;
  cellLockParams.CellParameterId = 0xFF;
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmReadCellLockInfo
//
//  This function reads CellLock's NVM file.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BOOL psNvmReadCellLockInfo(void)
{
#if defined (INTEL_FDI)
  FILE_ID  fdiID;
  FILE_INFO  fileInfo;
  //UINT8 count;
  char fileName[NVM_HEADER_FIELD_SIZE];

  psNvmSetCellLockNvmDefaultParams();

  strcpy(fileName,CELL_LOCK_FILE_NAME);

  if(FDI_findfirst((const FDI_TCHAR *)fileName, &fileInfo) == 0)
  {
    /* '0' open fail, !'0' open ok. */
    if((fdiID = FDI_fopen((const FDI_TCHAR *)fileName,"rb")) != 0)
    {
      FDI_fread((void *)(&cellLockParams), 1, sizeof(CellLockNvm_ts), fdiID);
      FDI_fclose(fdiID);  
    }
  }

  return TRUE;
#endif /* INTEL_FDI */
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreateCellLockInfo
//
//  This function creates CellLock's NVM file.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateCellLockInfo
BOOL psNvmCreateCellLockInfo(CellLockNvm_ts* params)
{
#if defined (INTEL_FDI)
  FILE_ID  fdiID;

  char fileName[NVM_HEADER_FIELD_SIZE];
  strcpy(fileName,CELL_LOCK_FILE_NAME);

  memcpy(&cellLockParams, params, sizeof(CellLockNvm_ts));

  fdiID = FDI_remove((const FDI_TCHAR *)fileName);

  /* '0' open fail, !'0' open ok. */
  if((fdiID = FDI_fopen((const FDI_TCHAR *)fileName,"wb+")) != 0)
  {
    FDI_fwrite ( &cellLockParams, sizeof(CellLockNvm_ts),1, fdiID );
    FDI_fclose(fdiID);
  }

  return TRUE;
#endif /* INTEL_FDI */
}




// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmGetCellLockInfo
//
//  This function Get CellLock Info.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmGetCellLockInfo(CellLockNvm_ts* params)
{
  memcpy(params, &cellLockParams, sizeof(CellLockNvm_ts));
}
#endif

/*add by xyma for CQ00125818 begin*/
//UINT8 ctxflag = 200;
 /* Added by Daniel for PSM 20180201, begin */
//BOOL psNvmReadPsmContext(void)

extern  UINT8 * getPSPsmContextP(UINT8 simId);
BOOL psNvmReadPsmContext(UINT8 simId)
{
#if defined (INTEL_FDI)
#if 0
    FILE_ID    fdiID;
    FILE_INFO  fileInfo;
    char fileName[NVM_HEADER_FIELD_SIZE];

    strcpy(fileName,PSM_CONTEXT_FILE_NAME);

    if(FDI_findfirst((const FDI_TCHAR *)fileName, &fileInfo) == 0)
    {
        /* '0' open fail, !'0' open ok. */
        if((fdiID = FDI_fopen((const FDI_TCHAR *)fileName,"rb")) != 0)
        {
            FDI_fread((void *)(&psmContext), 1, sizeof(PsmContext), fdiID);

            FDI_fclose(fdiID);  
        }
    }
#endif

    FILE_ID				fdiID;
	FILE_INFO 			fileInfo;
	NVMFormatHeader_ts	header;
	UINT8 *gPsPSMContextP = NULL;
	
//	bReadPsm[0] = 0;
//	bReadPsm[1] = 0;
	  	  
	if(simId == 0)
	{		
	    if (FDI_findfirst(PSM_CONTEXT_FILE_NAME, &fileInfo) != 0)
	    {
	      DIAG_FILTER(SYSTEM, SYSNVM, psNvmReadPsmContext_01,DIAG_INFORMATION)
	      diagPrintf ("File %s doesn't exist - using System defaults", PSM_CONTEXT_FILE_NAME);
	    //  ctxflag = 1;
	      return(FALSE);
	    }
	}
	else
	{
		if (FDI_findfirst(PSM_CONTEXT_FILE_NAME1, &fileInfo) != 0)
	    {
	      DIAG_FILTER(SYSTEM, SYSNVM, psNvmReadPsmContext_02,DIAG_INFORMATION)
	      diagPrintf ("File %s doesn't exist - using System defaults", PSM_CONTEXT_FILE_NAME1);
	  
	      return(FALSE);
	    }
	}
	  
	/* '0' open fail, !'0' open ok. */
	if((fdiID = FDI_fopen(fileInfo.file_name,"rb")) == 0)
	{
	  if(simId == 0)
	  {		  
	      DIAG_FILTER(SYSTEM, SYSNVM, psNvmReadPsmContext_03,DIAG_INFORMATION)
	      diagPrintf ("File %s OPEN error!", PSM_CONTEXT_FILE_NAME);
		  //ctxflag = 2;
      }	  
	  else
	  {
		   DIAG_FILTER(SYSTEM, SYSNVM, psNvmReadPsmContext_4,DIAG_INFORMATION)
	      diagPrintf ("File %s OPEN error!", PSM_CONTEXT_FILE_NAME1);
	  }
	  return(FALSE);
	}

	
    if(simId == 0)
	{		
	    DIAG_FILTER(SYSTEM, SYSNVM, psNvmReadPsmContext_05, DIAG_INFORMATION)
	    diagPrintf("Read %d words from file %s", fileInfo.size-sizeof(NVMFormatHeader_ts), PSM_CONTEXT_FILE_NAME);
	}
	else
	{
		DIAG_FILTER(SYSTEM, SYSNVM, psNvmReadPsmContext_06, DIAG_INFORMATION)
	    diagPrintf("Read %d words from file %s", fileInfo.size-sizeof(NVMFormatHeader_ts), PSM_CONTEXT_FILE_NAME1);
	}
	 
	 gPsPSMContextP = getPSPsmContextP(simId);
	if(gPsPSMContextP == NULL)
		 return(FALSE);
	
	/* Read the header first */
	FDI_fread((void *)(&header),1, sizeof(NVMFormatHeader_ts),fdiID);
	
	if(simId == 0)
	{
	   // FDI_fread((void *)(&psmContext[0]),1, fileInfo.size-sizeof(NVMFormatHeader_ts),fdiID);
		 FDI_fread((void *)gPsPSMContextP,1, fileInfo.size-sizeof(NVMFormatHeader_ts),fdiID);

//		ctxflag = psmContext[0].flag;
       //  bReadPsm[0] = 1;
	}
	else
	{
		//FDI_fread((void *)(&psmContext[1]),1, fileInfo.size-sizeof(NVMFormatHeader_ts),fdiID);
		FDI_fread((void *)gPsPSMContextP,1, fileInfo.size-sizeof(NVMFormatHeader_ts),fdiID);
		//bReadPsm[1] = 1;
	}
	FDI_fclose(fdiID);
   
    return TRUE;
#endif /* INTEL_FDI */

}

void psNvmSavePsmContext(UINT8 *psmCtx, unsigned char simId, unsigned short psmSize)
{
#if defined (INTEL_FDI)
#if 0
    FILE_ID  fdiID;
    FILE_INFO  fileInfo;
    char fileName[NVM_HEADER_FIELD_SIZE];

    if(simId == 0)
	{
        strcpy(fileName,PSM_CONTEXT_FILE_NAME);
	}
	else
	{
		strcpy(fileName,PSM_CONTEXT_FILE_NAME1);
	}

    fdiID = FDI_remove((const FDI_TCHAR *)fileName);

    /* '0' open fail, !'0' open ok. */
    if((fdiID = FDI_fopen((const FDI_TCHAR *)fileName,"wb+")) != 0)
    {
        FDI_fwrite (psmCtx, sizeof(PsmContext),1, fdiID );
        FDI_fclose(fdiID);
    }
#endif

	FILE_ID  fdiID;
	//UINT32 StructSize = sizeof(PsmContext);
	
	NVMFormatHeader_ts  header;
	
	if(simId == 0)
	{
	    DIAG_FILTER(SYSTEM, SYSNVM, psNvmSavePsmContext_01,DIAG_INFORMATION)
	    diagPrintf ("Save %s from PSM context", PSM_CONTEXT_FILE_NAME);
	
        fdiID = FDI_remove(PSM_CONTEXT_FILE_NAME);
	
	    fdiID = FDI_fopen(PSM_CONTEXT_FILE_NAME,"wb+");
    }
	else
	{
		DIAG_FILTER(SYSTEM, SYSNVM, psNvmSavePsmContext_02,DIAG_INFORMATION)
	    diagPrintf ("Save %s from PSM context", PSM_CONTEXT_FILE_NAME1);
	
        fdiID = FDI_remove(PSM_CONTEXT_FILE_NAME1);
	
	    fdiID = FDI_fopen(PSM_CONTEXT_FILE_NAME1,"wb+");
	}

	/* '0' open fail, !'0' open ok. */
    if(fdiID != 0)
    {
		// Create NVM standard header
		FDI_CreateNVMFormatHeader(&header, psmSize, 1,"PsmContext",SYSTEM_CURRENT_VERSION,"0", "0");
		FDI_fwrite(&header, sizeof(NVMFormatHeader_ts), 1, fdiID);
       // FDI_fwrite (psmCtx, sizeof(PsmContext),1, fdiID );
	   FDI_fwrite (psmCtx, psmSize,1, fdiID );
        FDI_fclose(fdiID);
    }
	
    
#endif /* INTEL_FDI */

}
extern unsigned short getPsPsmConextLen(void);
void psInitPsmContextNvm(UINT8 simId)
{
	unsigned short len = 0;
	UINT8* pTmp = NULL;  
	len = getPsPsmConextLen();
	pTmp = malloc(sizeof(len));
	ASSERT(pTmp != NULL);
	
	memset(pTmp, 0, sizeof(len));
	psNvmSavePsmContext(pTmp, simId, len);
	//psNvmSavePsmContext(pTmp, 1, len);
	 free(pTmp);
}

/* Added by Daniel for PSM 20180201, end */
/*add by xyma for CQ00125818 begin*/
 /*add for SRVCC & IMS at 20140321*/
 // ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 //
 //  function: psNvmSetIMSNWReportNvmDefaultParams
 //
 //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmSetIMSNWReportNvmDefaultParams(void)
{
  IMSNWReportModeParams.IMSNWReportStatus=0;
  IMSNWReportModeParams.NWIMSVoPS=0;
  IMSNWReportModeParams.EmerBearerSrvReportStatus=0;
  IMSNWReportModeParams.EmerBearerSRVIuStatus=0;
  IMSNWReportModeParams.EmerBearerSRVS1Status=0;
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmReadIMSNWReportInfo
//
//  This function reads IMSNWReport NVM file.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BOOL psNvmReadIMSNWReportInfo(void)
{
#if defined (INTEL_FDI)
  FILE_ID  fdiID;
  FILE_INFO  fileInfo;
  //UINT8 count;
  char fileName[NVM_HEADER_FIELD_SIZE];

  psNvmSetIMSNWReportNvmDefaultParams();

  strcpy(fileName,IMSNW_REPORTING_FILE_NAME);

  if(FDI_findfirst((const FDI_TCHAR *)fileName, &fileInfo) == 0)
  {
    /* '0' open fail, !'0' open ok. */
    if((fdiID = FDI_fopen((const FDI_TCHAR *)fileName,"rb")) != 0)
    {
      FDI_fread((void *)(&IMSNWReportModeParams), 1, sizeof(IMSNWReportStatusNvm_ts), fdiID);
      FDI_fclose(fdiID);  
    }
  }

  return TRUE;
#endif /* INTEL_FDI */
}


// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreateIMSNWReportInfo
//
//  This function creates IMSNWReport's NVM file.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateCellLockInfo
BOOL psNvmCreateIMSNWReportInfo(IMSNWReportStatusNvm_ts* params)
{
#if defined (INTEL_FDI)
  FILE_ID  fdiID;

  char fileName[NVM_HEADER_FIELD_SIZE];
  strcpy(fileName,IMSNW_REPORTING_FILE_NAME);

  memcpy(&IMSNWReportModeParams, params, sizeof(IMSNWReportStatusNvm_ts));

  fdiID = FDI_remove((const FDI_TCHAR *)fileName);

  /* '0' open fail, !'0' open ok. */
  if((fdiID = FDI_fopen((const FDI_TCHAR *)fileName,"wb+")) != 0)
  {
    FDI_fwrite ( &IMSNWReportModeParams, sizeof(IMSNWReportStatusNvm_ts),1, fdiID );
    FDI_fclose(fdiID);
  }

  return TRUE;
#endif /* INTEL_FDI */
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmGetIMSNWReportInfo
//
//  This function Get IMSNWReport Info.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmGetIMSNWReportInfo(IMSNWReportStatusNvm_ts* params)
{
  memcpy(params, &IMSNWReportModeParams, sizeof(IMSNWReportStatusNvm_ts));
  IMSNWReportModeParams.NWIMSVoPS=0;
}


 // ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 //
 //  function: psNvmSetTermProfileNvmDefaultParams
 //
 //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmSetTermProfileNvmDefaultParams(void)
{
#if defined (CRANE_MCU_DONGLE) || defined (NEZHA3_PLATFORM) || defined (FALCON_1803_PLATFORM) || defined (NEZHA_MCU_DONGLE) /* Modifed by Mason for #51367 on 01112022 */
#ifdef BIP_FUNC_SUPPORT
    //from duster_common.c API - duster_setprofile
    //sprintf(atstr, "AT+MSTK=1,3F01EDE2119C00070400001F4260000043\r");
    UINT8 satProfile[MAX_TERM_PROFILE_SIZE] = {0x3F,0x01,0xED,0xE2,0x19,0x9C,0x00,0x07,0x84,0x00,0x00,0x1F,0x42,0x60,0x00,0x00,0x43,0xC0,0x00,0x00,0x00,0x00,0x40};
    termProfileParams.LengthOfSatProfile = 23;

    //sprintf(atstr, "AT+MSTK=1,3F01EDE2119C00070400001F4260000043\r");
    UINT8 usatProfile[MAX_TERM_PROFILE_SIZE] = {0x3F,0x01,0xED,0xE2,0x19,0x9C,0x00,0x07,0x84,0x00,0x00,0x1F,0x42,0x60,0x00,0x00,0x43,0xC0,0x00,0x00,0x00,0x00,0x40};
    termProfileParams.LengthOfUsatProfile = 23;
#else
    //from duster_common.c API - duster_setprofile
    //sprintf(atstr, "AT+MSTK=1,3F01EDE011900007840000000060000043C00000000040\r");
    UINT8 satProfile[MAX_TERM_PROFILE_SIZE] = {0x3F,0x01,0xED,0xE0,0x19,0x90,0x00,0x07,0x84,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x43,0xC0,0x00,0x00,0x00,0x00,0x40};
    termProfileParams.LengthOfSatProfile = 23;

    //sprintf(atstr, "AT+MSTK=1,3F01EDE011900007840000000060000043C00000000040\r");
	UINT8 usatProfile[MAX_TERM_PROFILE_SIZE] = {0x3F,0x01,0xED,0xE0,0x19,0x90,0x00,0x07,0x84,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x43,0xC0,0x00,0x00,0x00,0x00,0x40};
    termProfileParams.LengthOfUsatProfile = 23;
#endif
	DIAG_FILTER(SYSTEM, SYSNVM, psNvmSetTermProfileNvmDefaultParams_0, DIAG_INFORMATION)
	diagPrintf("termProfileParams.LengthOfSatProfile=%d, termProfileParams.LengthOfUsatProfile=%d", termProfileParams.LengthOfSatProfile, termProfileParams.LengthOfUsatProfile);

#else /* here for other platforms */ 

    /* Mod by jungle for CQ00050447 on 2013-12-16 Begin */
    UINT8 satProfile[MAX_TERM_PROFILE_SIZE] = {0xFF,0xFF,0xFF,0xFF,0x7F,0x0F,0x00,0x9F,0x7F,0x00,0x00,0x1F,0xE2,0x00,0x00,0x00,0x03,0x00,0x00,0x00};
    /*2014.02.07, mod by Xili for CQ00056284, begin*/
    //UINT8 usatProfile[MAX_TERM_PROFILE_SIZE]= {0xFF,0xFF,0xFF,0xFF,0x7F,0x1F,0x00,0xDF,0xFF,0x00,0x00,0x1F,0xE2,0x00,0x00,0x00,0x03,0x00,0x00,0x00};
    /*2014.02.07, mod by Xili for CQ00056284, end*/

    /*2014.11.28, mod by Xili for GCF27.22.2 #514792, CQ00077482 begin*/
#ifdef SS_IPC_SUPPORT
    UINT8 usatProfile[MAX_TERM_PROFILE_SIZE] = {0xFF,0xFF,0xFF,0xFF,0x7F,0x9D,0x00,0xDF,0xBF,0x00,0x00,0x1F,0xE2,0x00,0x00,0x00,0xC3,0xC0,0x00,0x00,
                                            0x00,0x01,0x48,0x00,0x50,0x00,0x00,0x00,0x00,0x08,0x00,0x00};
#else  
    UINT8 usatProfile[MAX_TERM_PROFILE_SIZE] = {0xFF,0xFF,0xFF,0xFF,0x7F,0x9F,0x00,0xDF,0xFF,0x00,0x00,0x1F,0xE2,0x00,0x00,0x00,0x43,0xC0,0x00,0x00,
                                            0x00,0x00,0x48,0x00,0x10,0x00,0x00,0x00,0x00,0x08,0x00,0x00};
#endif
    /*2014.11.28, mod by Xili for 27.22.2 #514792, CQ00077482 end*/
    /* Mod by jungle for CQ00050447 on 2013-12-16 End */

    termProfileParams.LengthOfSatProfile = 17;
    termProfileParams.LengthOfUsatProfile = 32;
#endif

    memcpy(termProfileParams.SatProfile, satProfile, MAX_TERM_PROFILE_SIZE);
    memcpy(termProfileParams.UsatProfile, usatProfile, MAX_TERM_PROFILE_SIZE);
}


// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmReadTermProfile
//
//  This function reads Terminal Profile NVM file.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BOOL psNvmReadTermProfile(void)
{
#if defined (INTEL_FDI)
  FILE_ID  fdiID;
  FILE_INFO  fileInfo;
  //UINT8 count;
  char fileName[NVM_HEADER_FIELD_SIZE];

  psNvmSetTermProfileNvmDefaultParams();

  strcpy(fileName,TERMINAL_PROFILE_FILE_NAME);

  if(FDI_findfirst((const FDI_TCHAR *)fileName, &fileInfo) == 0)
  {
    /* '0' open fail, !'0' open ok. */
    if((fdiID = FDI_fopen((const FDI_TCHAR *)fileName,"rb")) != 0)
    {
      	FDI_fread((void *)(&termProfileParams), 1, sizeof(TermProfileNvm_ts), fdiID);

	  	if(termProfileParams.LengthOfSatProfile == 0 ||
	  		termProfileParams.LengthOfUsatProfile == 0 ||
	  		termProfileParams.LengthOfSatProfile > MAX_TERM_PROFILE_SIZE ||
	  		termProfileParams.LengthOfUsatProfile > MAX_TERM_PROFILE_SIZE)
  		{
  			psNvmSetTermProfileNvmDefaultParams();
  		}
		
      	FDI_fclose(fdiID);  
    }
  }

  duster_updateprofile((char*)termProfileParams.UsatProfile, termProfileParams.LengthOfUsatProfile);

  return TRUE;
#endif /* INTEL_FDI */
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreateTermProfile
//
//  This function creates Terminal Profile NVM file.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BOOL psNvmSaveTermProfile(UINT8 *satProfile, UINT8 len, BOOL isUsat)
{
#if defined (INTEL_FDI)
  FILE_ID  fdiID;

  char fileName[NVM_HEADER_FIELD_SIZE];
  strcpy(fileName,TERMINAL_PROFILE_FILE_NAME);

  /* Mod by jungle for CQ00032317 on 2013-04-12 Begin */
  if( isUsat )
  {
    termProfileParams.LengthOfUsatProfile = len;
    memcpy(termProfileParams.UsatProfile, satProfile, len);
  }
  else
  {
    termProfileParams.LengthOfSatProfile = len;
    memcpy(termProfileParams.SatProfile, satProfile, len);
  }
  /* Mod by jungle for CQ00032317 on 2013-04-12 End */

  fdiID = FDI_remove((const FDI_TCHAR *)fileName);

  /* '0' open fail, !'0' open ok. */
  if((fdiID = FDI_fopen((const FDI_TCHAR *)fileName,"wb+")) != 0)
  {
    FDI_fwrite ( &termProfileParams, sizeof(TermProfileNvm_ts),1, fdiID );
    FDI_fclose(fdiID);
  }

  return TRUE;
#endif /* INTEL_FDI */
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreateTermProfile
//
//  This function creates Terminal Profile NVM file.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateTermProfile
BOOL psNvmCreateTermProfile(TermProfileNvm_ts* params)
{
#if defined (INTEL_FDI)
  FILE_ID  fdiID;

  char fileName[NVM_HEADER_FIELD_SIZE];
  strcpy(fileName,TERMINAL_PROFILE_FILE_NAME);

  memcpy(&termProfileParams, params, sizeof(TermProfileNvm_ts));

  fdiID = FDI_remove((const FDI_TCHAR *)fileName);

  /* '0' open fail, !'0' open ok. */
  if((fdiID = FDI_fopen((const FDI_TCHAR *)fileName,"wb+")) != 0)
  {
    FDI_fwrite ( &termProfileParams, sizeof(TermProfileNvm_ts),1, fdiID );
    FDI_fclose(fdiID);
  }

  return TRUE;
#endif /* INTEL_FDI */
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//	function: psNvmSetIOTParamsDefault
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmSetIOTParamsDefault(void)
 {
    UINT16 BitMapGrrLogs;
    IOTParams_ts IOTParamsDefault;


	/*Fix coverity[uninit_use_in_call]*/
	memset(&IOTParamsDefault, 0, sizeof(IOTParamsDefault));
    /* Bit map for GrrLog is as follow:
 * -------------------------------------------------------------------------------------------------------------------------
 *        B9     |      B8  |B7 |   B6      |  B5     |  B4       |   B3        |  B2         |  B1        |   B0         |
 * |IrReselection|PktSysInfo|Pkt|PktIdleCcch|RetToIdle|CctSwtchDed|LogPlmnSearch|CctSwtchEstab|CctSwtchIdle|CellSelection |
 *  * ---------------------------------------------------------------------------------------------------------------------*/
#if !defined(ENABLE_DM_LTEONLY)
    BitMapGrrLogs = GetGrrLogDefault();
#endif//ENABLE_DM_LTEONLY
    IOTParamsDefault.GRRLogs.GRR_LOG_CELL_SELECTION_L3MSG = (systemfeatureenable_ts)(BitMapGrrLogs & 1);
    IOTParamsDefault.GRRLogs.GRR_LOG_CCT_SWTCH_IDLE_L3MSG = (systemfeatureenable_ts)((BitMapGrrLogs & 2)>>1);
    IOTParamsDefault.GRRLogs.GRR_LOG_CCT_SWTCH_ESTAB_L3MSG = (systemfeatureenable_ts)((BitMapGrrLogs & 4)>>2);
    IOTParamsDefault.GRRLogs.GRR_LOG_PLMN_SEARCH_L3MSG = (systemfeatureenable_ts)((BitMapGrrLogs & 8)>>3);
    IOTParamsDefault.GRRLogs.GRR_LOG_CCT_SWTC_DED_L3MSG = (systemfeatureenable_ts)((BitMapGrrLogs & 0x0010)>>4);
    IOTParamsDefault.GRRLogs.GRR_LOG_RET_TO_IDLE_L3MSG = (systemfeatureenable_ts)((BitMapGrrLogs & 0x0020)>>5);
    IOTParamsDefault.GRRLogs.GRR_LOG_PKT_IDLE_CCCH_L3MSG = (systemfeatureenable_ts)((BitMapGrrLogs & 0x0040)>>6);
    IOTParamsDefault.GRRLogs.GRR_LOG_PKT_L3MSG = (systemfeatureenable_ts)((BitMapGrrLogs & 0x0080)>>7);
    IOTParamsDefault.GRRLogs.GRR_LOG_PKT_SYS_INFO_MSG = (systemfeatureenable_ts)((BitMapGrrLogs & 0x0100)>>8);
    IOTParamsDefault.GRRLogs.GRR_LOG_IR_RESELECTION_L3MSG = (systemfeatureenable_ts)((BitMapGrrLogs & 0x0200)>>9);
    IOTParamsDefault.GRRLogs.RESERVED1 = SYS_DISABLE;
    IOTParamsDefault.GRRLogs.RESERVED2 = SYS_DISABLE;
    IOTParamsDefault.GMM_REL_CONTEXT_T3312_EXPIRY = (systemfeatureenable_ts)(GetRelContextT3312ExpiryDefault());
	IOTParamsDefault.mccForPcsClassmark3.isMccValid=SYS_DISABLE;
	IOTParamsDefault.mccForPcsClassmark3.mcc=0xFFFF;
    IOTParamsDefault.MobileEquipment.TOTAL_RLC_AM_BUFFER_SIZE_R5EXT = (TotalRLC_AM_BufferSize_r5ext_ts)(GetGetTotalRlcAMBufferSize_r5_ext_Default()); /*UTotalRLC_AM_BufferSize_r5_ext_kb200 */
    IOTParamsDefault.MobileEquipment.MAX_RLC_WINDOW_SIZE = (MaximumRLC_WindowSize_ts)(GetMaxRLCWimdowSizeDefault()); /*UMaximumRLC_WindowSize_mws2047 */
    IOTParamsDefault.MobileEquipment.TOTAL_RLC_AM_BUFFER_SIZE = (TotalRLC_AM_BufferSize_ts)(GetTotalRlcAMBufSizeDefault());
    IOTParamsDefault.MobileEquipment.BIT_MAP_UEA1_UEA0 = GetUeaCipheringAlgorithmCapDefault();
    IOTParamsDefault.MobileEquipment.BIT_MAP_ALGO_A5_AVAILABLE= GetCipheringA5AlgoaDefault();
    IOTParamsDefault.MobileEquipment.BIT_MAP_ALGO_GPRS_AVAILABLE = GetGeaAlgoAvailableDefault();
    IOTParamsDefault.MobileEquipment.BIT_MAP_UEA1_UEA0 = GetUeaCipheringAlgorithmCapDefault();
	IOTParamsDefault.GsmResideOnlyOnFollowingARFCNs.GrrCampOnDesArfcn =  SYS_DISABLE; 			// when IOT LAB has no RF cable...
	IOTParamsDefault.GsmResideOnlyOnFollowingARFCNs.GrrCampOnDesNumberOfArfcn2Search = 1;   // How many ARFCN are in tests (e.g for HO/Resel)
	IOTParamsDefault.GsmResideOnlyOnFollowingARFCNs.GrrCampOnDesArfcnList[0] = 1; 		    // ARFCN values 0-1023
	IOTParamsDefault.GsmResideOnlyOnFollowingARFCNs.GrrCampOnDesArfcnList[1] = 0;
	IOTParamsDefault.GsmResideOnlyOnFollowingARFCNs.GrrCampOnDesArfcnList[2] = 0;
	IOTParamsDefault.GsmResideOnlyOnFollowingARFCNs.GrrCampOnDesArfcnList[3] = 0;
	IOTParamsDefault.GsmResideOnlyOnFollowingARFCNs.GrrCampOnDesArfcnList[4] = 0;

    memcpy(&(systemcNvmParams.IOTParams),&IOTParamsDefault, sizeof(IOTParams_ts));
 }
 // end of changes for "NVM programmable parameter for IOT"

 // ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 //
 //  function: psNvmSetSystemcNvmDefaultParams
 //
 //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmSetSystemcNvmDefaultParams(void)
{
	systemfeatureenable_ts featuresParamsDefault  [SYSTEM_FEATURES_DEFAULT_DATA_SIZE] = SYSTEM_FEATURES_DEFAULT_DATA;
	systemfeaturesUnderDevelopment_ts tmpFeaturesUnderDevelopment [SYSTEM_DEV_FEATURES_DEFAULT_DATA_SIZE] = SYSTEM_DEV_FEATURES_DEFAULT_DATA;
	xscalePowerManagement_ts  xscalePowerManagementsDefaults = XSCALE_POWER_MANAGEMENT_DEFAULT_DATA;
	USBConfiguration_ts  USBConfigurationDefaults = USB_CONFIGURATION_DEFAULT_DATA;
	uartForceAwakeMode_ts UARTConfigurationDefaults = UART_CONFIGURATION_DEFAULT_DATA;
	VendorSpecificInfo_ts vendorSpecificInfo = VENDOR_SPECIFIC_INFO_DEFAULT_DATA;
/*Fixed CQ00024251 xyzheng for U+D optimistion start 2012-11-07*/
#if !defined (ON_PC)   
	/*Fixed for U+D begin date: 2010-08-11 yinfei*/ 

	/*Fixed for CQ00016055 begin date 2012-02-02 xyzheng*/
	UINT8	optMethodVersion = U_D_OPT_METHOD_VERSION_2;
    UINT8   ratioOfPdusDropped = 20; /*cgliu 20130922 for sync nvm*/

	/*Fixed for CQ00016055 end date 2012-02-02 xyzheng*/

	/*Fixed for U+D End date: 2010-08-11 yinfei*/
#endif	
/*Fixed CQ00024251 xyzheng for U+D optimistion end 2012-11-07*/
	// Clear the structure contents
	memset(&systemcNvmParams,0,sizeof(systemcNvmParams));

	// Create features enable parameters
	memcpy(&(systemcNvmParams.featuresParams),featuresParamsDefault,sizeof(systemfeaturesParams_ts));
	//FDI_fwrite(&(systemcNvmParams.featuresParams), sizeof(systemcNvmParams.featuresParams), 1, fileIndex);

	// Create development switch
	memcpy( &(systemcNvmParams.developmentSwitch), tmpFeaturesUnderDevelopment, sizeof(systemfeaturesUnderDevelopment_ts) );
	//FDI_fwrite( &(systemcNvmParams.developmentSwitch), sizeof(systemcNvmParams.developmentSwitch), 1, fileIndex );

	// Create Xscale Power Management Data
	memcpy( &(systemcNvmParams.xscalePowerManagement), &xscalePowerManagementsDefaults, sizeof(xscalePowerManagement_ts) );
	//FDI_fwrite( &(systemcNvmParams.xscalePowerManagement), sizeof(systemcNvmParams.xscalePowerManagement), 1, fileIndex );

	// Create USB Configuration Data
	memcpy( &(systemcNvmParams.USBConfiguration), &USBConfigurationDefaults, sizeof(USBConfiguration_ts) );
	//FDI_fwrite( &(systemcNvmParams.USBConfiguration), sizeof(systemcNvmParams.USBConfiguration), 1, fileIndex );

	// Create UART Configuration Data
	memcpy( &(systemcNvmParams.uartForceAwakeMode), &UARTConfigurationDefaults, sizeof(uartForceAwakeMode_ts) );
	//FDI_fwrite( &(systemcNvmParams.uartForceAwakeMode), sizeof(systemcNvmParams.uartForceAwakeMode), 1, fileIndex );

	// Create Vendor Specific Info Data
	systemcNvmParams.vendorSpecificInfo = vendorSpecificInfo;
	//FDI_fwrite( &(systemcNvmParams.vendorSpecificInfo), sizeof(systemcNvmParams.vendorSpecificInfo), 1, fileIndex );
/*Fixed CQ00024251 xyzheng for U+D optimistion start 2012-11-07*/
#if !defined (ON_PC)   
		/*Fixed for U+D begin date: 2010-08-11 yinfei*/ 
		// Create optimization version for U+D
		memcpy( &(systemcNvmParams.optMethodFlag), &optMethodVersion, sizeof(UINT8) );
        memcpy( &(systemcNvmParams.ratioForHWMDiscardData), &ratioOfPdusDropped, sizeof(UINT8) ); /*cgliu 20130922 for sync nvm*/

		//FDI_fwrite( &(systemcNvmParams.optMethodFlag), sizeof(systemcNvmParams.optMethodFlag), 1, fileIndex );
	/*Fixed for U+D End date: 2010-08-11 yinfei*/	
#endif
/*Fixed CQ00024251 xyzheng for U+D optimistion end 2012-11-07*/
	/*-----------------6/7/2007 2:51PM------------------
	* NVM programmable parameter for IOT
	* --------------------------------------------------*/
	psNvmSetIOTParamsDefault();
    systemcNvmParams.GCFTimingAdvance = 0; /*cgliu 20130922 for sync nvm*/

	// end of NVM programmable parameter for IOT

  //FDI_fwrite( &(systemcNvmParams.pad), /*UINT8*/ 1 , 1, fileIndex );

}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreate
//
//  This function creates default NVM file for SYSTEM.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreate
BOOL psNvmCreate(void)
{
#if defined (INTEL_FDI)

  FILE_ID  fileIndex;
  UINT32 StructSize = sizeof(SystemcNvm_ts);

#if 0
  NVMFormatHeader_ts  header;
#else
  NVMFormatHeader_ts  header =    {
								StructSize, 	          // StructSize
								1, 						  // NumofStructs
								"SystemcNvm_ts",		  // StructName
								"NULL",				  // Date
								"NULL",				  // time
								SYSTEM_CURRENT_VERSION,   // Version
								"0",					  // HW_ID
								"0"				          // CalibVersion
							     };
#endif /* GERAN_ONLY */

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew,DIAG_INFORMATION)
  diagPrintf ("Creating %s from SYSTEM_DEFAULT_DATA", SYSTEM_FILE_NAME);

  fileIndex = FDI_fopen(SYSTEM_FILE_NAME, "wb");

#if !defined(GERAN_ONLY)
  // Create NVM standard header
  FDI_CreateNVMFormatHeader(&header, StructSize, 1,"SystemcNvm_ts",SYSTEM_CURRENT_VERSION,"0", "0");
#endif
  FDI_fwrite(&header, sizeof(NVMFormatHeader_ts), 1, fileIndex);

  psNvmSetSystemcNvmDefaultParams();

  FDI_fwrite( &systemcNvmParams, sizeof(systemcNvmParams), 1, fileIndex );


  FDI_fclose(fileIndex);
  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateCompNew,DIAG_INFORMATION)
  diagPrintf ("%s create completed", SYSTEM_FILE_NAME);

  return(TRUE);
#else
  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNotSupported,DIAG_INFORMATION)
  diagTextPrintf ("Current build doesn't support intel FDI");
  return(FALSE);
#endif
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmRead
//
//  This function reads SYTEM's NVM file.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BOOL psNvmRead(void)
{
#if defined (INTEL_FDI)
  FILE_ID               fileIndex;
  FILE_INFO             info;
  NVMFormatHeader_ts    header;

  psNvmSetSystemcNvmDefaultParams();

  if (FDI_findfirst(SYSTEM_FILE_NAME, &info) != 0)
  {
     DIAG_FILTER(SYSTEM, SYSNVM, SYS_CREATE_NVM_FILE,DIAG_INFORMATION)
     diagPrintf ("File %s doesn't exist - using System defaults", SYSTEM_FILE_NAME);

     return(TRUE);
  }

  fileIndex = FDI_fopen(info.file_name, "rb");

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_READ_NVM, DIAG_INFORMATION)
  diagPrintf("Read %d words from file %s", info.size, SYSTEM_FILE_NAME);

  /* Read the header first */
  FDI_fread((void *)(&header),1, sizeof(NVMFormatHeader_ts),fileIndex);
  
  /*
  If the version is incompatible:
  [1] Ignore the file and use system defaults
  [2] Create SYSTEM_FILE with default values
  */
  if ( strcmp(header.Version, SYSTEM_CURRENT_VERSION) != 0  )
  {
    DIAG_FILTER(SYSTEM, SYSNVM, Warnning_OldVersionOfSystemControlNvmFile, DIAG_INFORMATION)
    diagPrintf("Warnning - incompatible version of %s. Version %s instead of %s. Deleting the file and using system defaults",
        SYSTEM_FILE_NAME, header.Version, SYSTEM_CURRENT_VERSION);

    FDI_fclose(fileIndex);

    FDI_remove(SYSTEM_FILE_NAME);
  }
  else
  {
    FDI_fread((void *)(&systemcNvmParams),1, info.size-sizeof(NVMFormatHeader_ts),fileIndex);
    
    FDI_fclose(fileIndex);
  }


  return TRUE;
  
#else
  psNvmSetSystemcNvmDefaultParams();

  DIAG_FILTER(SYSTEM, SYSNVM, NO_FDI_SUPPORT_RETURN_DEFAULT,DIAG_INFORMATION)
  diagTextPrintf ("Current build does not support FDI. Return default.");
  return FALSE;
#endif /* INTEL_FDI */

}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmEnableDisablePsInitAuto
//
//  This function creates default NVM file for SYSTEM.
//  In addition it set the PS_INIT_AUTO parameter according to entry parameter
//
//  mmode = 1 -> Enable
//  mmode = 0 -> Disable
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmEnableDisablePsInit
BOOL psNvmEnableDisablePsInitAuto(UINT16* mmode)
{
#if defined (INTEL_FDI)

  FILE_ID  fileIndex;
  UINT32 StructSize = sizeof(SystemcNvm_ts);

#if !defined (GERAN_ONLY)
  NVMFormatHeader_ts  header;
#else
  NVMFormatHeader_ts  header =    {
								StructSize, 	                     // StructSize
								1, 						  // NumofStructs
								"SystemcNvm_ts",			  // StructName
								"NULL",				  // Date
								"NULL",				  // time
								SYSTEM_CURRENT_VERSION,  // Version
								"0",					         // HW_ID
								"0"				               // CalibVersion
							     };
#endif /* GERAN_ONLY */

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreatePsInitAuto1,DIAG_INFORMATION)
  diagPrintf ("start Create %s from SYSTEM_DEFAULT_DATA", "SytemControl");

  fileIndex = FDI_fopen(SYSTEM_FILE_NAME, "wb");

#if !defined(GERAN_ONLY)
  // Create NVM standard header
  FDI_CreateNVMFormatHeader(&header, StructSize, 1,"SystemcNvm_ts",SYSTEM_CURRENT_VERSION,"0", "0");
#endif
  FDI_fwrite(&header, sizeof(NVMFormatHeader_ts), 1, fileIndex);

  psNvmSetSystemcNvmDefaultParams();

  if (*mmode == TRUE)
  {
       systemcNvmParams.featuresParams.PS_INIT_AUTO = SYS_ENABLE;
  }
  else
  {
       systemcNvmParams.featuresParams.PS_INIT_AUTO = SYS_DISABLE;
  }

  FDI_fwrite( &systemcNvmParams, sizeof(systemcNvmParams), 1, fileIndex );


  FDI_fclose(fileIndex);
  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateCompPsInitAuto,DIAG_INFORMATION)
  diagPrintf ("SystemControl create completed, PS_INIT_AUTO = %d",systemcNvmParams.featuresParams.PS_INIT_AUTO);

  return(TRUE);
#else
  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNotSupportedPsInitAuto,DIAG_INFORMATION)
  diagTextPrintf ("current build doesn't support intel FDI");
  return(FALSE);
#endif
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmAciSET
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmAciSET(void)
{
  FILE_INFO    info;
  // AciSacGki_ts temp = systemcNvmParams.aciSacGki;

  if(systemcNvmParams.aciSacGki == ACI_SW_DEFAULT)
  {
#if defined (INTEL_FDI)
    if(FDI_findfirst(ACI_RTOS_CFG_FILE_NAME, &info) != 0) //row-data file, may be empty
        systemcNvmParams.aciSacGki = ACI_SAC_ONLY;  //File not present. Supposed the APPS is not RTOS
    else
#endif
        systemcNvmParams.aciSacGki = ACI_GKI_ONLY;
  }
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmAciSacIsWorking
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BOOL psNvmAciSacIsWorking(void)
    { return ( (systemcNvmParams.aciSacGki == ACI_SAC_ONLY) || (systemcNvmParams.aciSacGki == ACI_COMBINED) ); }

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmAciGkiIsWorking
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BOOL psNvmAciGkiIsWorking(void)
    { return ( (systemcNvmParams.aciSacGki == ACI_GKI_ONLY) || (systemcNvmParams.aciSacGki == ACI_COMBINED) ); }

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmVendorSpecificEnabled
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BOOL psNvmVendorSpecificEnabled(UINT32 infoBitMask)/*CQ00047657 by zhangxia 20131106*/
	{ return (systemcNvmParams.vendorSpecificInfo & infoBitMask) != 0; }

/*CQ00047657 by zhangxia 20131106 begin*/

VendorSpecificInfo_ts psNvmReadVendorSpecificInfo(void)
     {return (VendorSpecificInfo_ts)(systemcNvmParams.vendorSpecificInfo);}

/*CQ00047657 by zhangxia 20131106 end*/


/*OneImage, 2013-08-19, begin */
BOOL psVendorPrintf(void )
{

if((UINT16)(systemcNvmParams.vendorSpecificInfo)==0)
 {
DIAG_FILTER(SYSTEM,SYSNVM,psVendorPrintf_1,DIAG_INFORMATION)
diagPrintf ("original vendor information VENDOR_SPECIFIC_INFO_NULL");
 }
if (psNvmVendorSpecificEnabled(1))

 {
	DIAG_FILTER(SYSTEM,SYSNVM,psVendorPrintf_2,DIAG_INFORMATION)
	diagPrintf ("original vendor information VENDOR_SPECIFIC_INFO_ATT");
 }
if (psNvmVendorSpecificEnabled(2))

 {
	DIAG_FILTER(SYSTEM,SYSNVM,psVendorPrintf_3,DIAG_INFORMATION)
	diagPrintf ("original vendor information VENDOR_SPECIFIC_INFO_CMCC");
 }
if (psNvmVendorSpecificEnabled(4))

 {
	DIAG_FILTER(SYSTEM,SYSNVM,psVendorPrintf_4,DIAG_INFORMATION)
	diagPrintf ("original vendor information VENDOR_SPECIFIC_INFO_RRM");
 }

if (psNvmVendorSpecificEnabled(8))
 {

 DIAG_FILTER(SYSTEM,SYSNVM,psVendorPrintf_5,DIAG_INFORMATION)
 diagPrintf ("original vendor information VENDOR_SPECIFIC_INFO_MTNET");
 }
if (psNvmVendorSpecificEnabled(32))
 {

 DIAG_FILTER(SYSTEM,SYSNVM,psVendorPrintf_7,DIAG_INFORMATION)
 diagPrintf ("original vendor information VENDOR_SPECIFIC_INFO_IOT");
 }
if (psNvmVendorSpecificEnabled(64))
 {

 DIAG_FILTER(SYSTEM,SYSNVM,psVendorPrintf_8,DIAG_INFORMATION)
 diagPrintf ("original vendor information VENDOR_SPECIFIC_INFO_SILENTRESET");
 }

if (psNvmVendorSpecificEnabled(128))
 {

 DIAG_FILTER(SYSTEM,SYSNVM,psVendorPrintf_9,DIAG_INFORMATION)
 diagPrintf ("original vendor information VENDOR_SPECIFIC_INFO_PSOPT");
 }

   /*Fix coverity[missing_return]*/
  return TRUE;

}
/*OneImage, 2013-08-19, end   */
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//	function: psNvmCreateVS Vendor Specific    Generic function for all type of vendors
//
//	This function creates default NVM file for SYSTEM.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
/*Fix coverity[incompatible_cast]*/
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateVS
#if 0
BOOL psNvmCreateVS(UINT32* mmode)
#else
BOOL psNvmCreateVS(VendorSpecificInfo_ts* mmode)
#endif
{
#if defined (INTEL_FDI)

  FILE_ID  fileIndex;
  UINT32 StructSize = sizeof(SystemcNvm_ts);

#if !defined (GERAN_ONLY)
  NVMFormatHeader_ts  header;
#else
  NVMFormatHeader_ts  header =	  {
								StructSize, 						 // StructSize
								1,						  // NumofStructs
								"SystemcNvm_ts",			  // StructName
								"NULL", 			  // Date
								"NULL", 			  // time
								SYSTEM_CURRENT_VERSION,  // Version
								"0",							 // HW_ID
								"0" 						   // CalibVersion
								 };
#endif /* GERAN_ONLY */

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew1,DIAG_INFORMATION)
  diagPrintf ("start Create %s from SYSTEM_DEFAULT_DATA and Vendor Specific 0x%x", "SytemControl", *mmode);

  fileIndex = FDI_fopen(SYSTEM_FILE_NAME, "wb");

#if !defined(GERAN_ONLY)
  // Create NVM standard header
  FDI_CreateNVMFormatHeader(&header, StructSize, 1,"SystemcNvm_ts",SYSTEM_CURRENT_VERSION,"0", "0");
#endif
  FDI_fwrite(&header, sizeof(NVMFormatHeader_ts), 1, fileIndex);

//  psNvmSetSystemcNvmDefaultParams(); //not set default values here, or else updating other items in CATS can't take effect. 

  systemcNvmParams.vendorSpecificInfo =  ((VendorSpecificInfo_ts) *mmode);
  FDI_fwrite( &systemcNvmParams, sizeof(systemcNvmParams), 1, fileIndex );


  FDI_fclose(fileIndex);
  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateCompNew1,DIAG_INFORMATION)
  diagTextPrintf ("SystemControl create completed");

  return(TRUE);
#else
  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNotSupported1,DIAG_INFORMATION)
  diagTextPrintf ("current build doesn't support intel FDI");
  return(FALSE);
#endif
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//	function: psNvmCreateH3G
//
//	This function creates default NVM file for SYSTEM.
//	  Vendor Specific Data is H3G
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateH3G
BOOL psNvmCreateH3G(void)
{
  VendorSpecificInfo_ts mmode = VENDOR_SPECIFIC_INFO_H3G;

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew2,DIAG_INFORMATION)
  diagPrintf ("start to create %s Vendor Specific Data", "H3G");
  return psNvmCreateVS(&mmode);
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//	function: psNvmCreateNull
//
//	This function creates default NVM file for SYSTEM.
//	  Vendor Specific Data is Null
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateNull
BOOL psNvmCreateNull(void)
{
  VendorSpecificInfo_ts mmode = VENDOR_SPECIFIC_INFO_NULL;

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew3,DIAG_INFORMATION)
  diagPrintf ("start to create %s Vendor Specific Data", "Null");
  return psNvmCreateVS(&mmode);
}


// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreate
//
//  This function creates default NVM file for SYSTEM.
//    Vendor Specific Data is AT&T
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateATT
BOOL psNvmCreateATT(void)
{
  VendorSpecificInfo_ts mmode = VENDOR_SPECIFIC_INFO_ATT;

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew2,DIAG_INFORMATION)
  diagPrintf ("start to create %s Vendor Specific Data", "AT&T");
  return psNvmCreateVS(&mmode);
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreate
//
//  This function creates default NVM file for SYSTEM.
//    Vendor Specific Data is CMCC
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateCMCC
BOOL psNvmCreateCMCC(void)
{
  VendorSpecificInfo_ts mmode = VENDOR_SPECIFIC_INFO_CMCC;

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew3,DIAG_INFORMATION)
  diagPrintf ("start to create %s Vendor Specific Data", "CMCC");
  return psNvmCreateVS(&mmode);
}



// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreate
//
//  This function creates default NVM file for SYSTEM.
//    Vendor Specific Data is ASUS
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateTELCE
BOOL psNvmCreateTELCE(void)
{
  VendorSpecificInfo_ts mmode = VENDOR_SPECIFIC_INFO_TELCEL;

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew6,DIAG_INFORMATION)
  diagPrintf ("start to create %s Vendor Specific Data", "TELCE");
  return psNvmCreateVS(&mmode);
}



// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreateVDF
//
//  This function creates default NVM file for SYSTEM.
//    Vendor Specific Data is VDF
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateVDF
BOOL psNvmCreateVDF(void)
{
  VendorSpecificInfo_ts mmode = VENDOR_SPECIFIC_INFO_VDF;

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew7,DIAG_INFORMATION)
  diagPrintf ("start to create %s Vendor Specific Data", "VDF");
  return psNvmCreateVS(&mmode);
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreatePLAY
//
//  This function creates default NVM file for SYSTEM.
//    Vendor Specific Data is VDF
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreatePLAY
/*BOOL psNvmCreatePLAY(void)
{
  UINT16 mmode = VENDOR_SPECIFIC_INFO_PLAY;

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew7,DIAG_INFORMATION)
  diagPrintf ("start to create %s Vendor Specific Data", "PLAY");
  return psNvmCreateVS(&mmode);
}*/

	// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	//
	//	function: psNvmCreatePLAY
	//
	//	This function creates default NVM file for SYSTEM.
	//	  Vendor Specific Data is VDF
	//
	//
	//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateMANUFACTURESILVER
	BOOL psNvmCreateMANUFACTURESILVER(void)
	{
	  VendorSpecificInfo_ts mmode = VENDOR_SPECIFIC_INFO_MANUFACTURE_SILVER;
	
	  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew71,DIAG_INFORMATION)
	  diagPrintf ("start to create %s Vendor Specific Data", "MANUFACTURE_SILVER");
	  return psNvmCreateVS(&mmode);
	}


// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreate2GROMING
//
//  This function creates default NVM file for SYSTEM.
//    Vendor Specific Data is VDF
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreate2GROMING
BOOL psNvmCreate2GROMING(void)
{
  VendorSpecificInfo_ts mmode = VENDOR_SPECIFIC_INFO_2G_ROAMING;

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew7,DIAG_INFORMATION)
  diagPrintf ("start to create %s Vendor Specific Data", "2G ROAMING");
  return psNvmCreateVS(&mmode);
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreate
//
//  This function creates default NVM file for SYSTEM.
//    Vendor Specific Data is IOT
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateCTA
BOOL psNvmCreateCTA(void)
{
  VendorSpecificInfo_ts mmode = VENDOR_SPECIFIC_INFO_IOT;

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew6,DIAG_INFORMATION)
  diagPrintf ("start to create %s Vendor Specific Data", "CTA");
  return psNvmCreateVS(&mmode);
}

/*Fixed CQ00024251 xyzheng for U+D optimistion start 2012-11-07*/
/*Alan DIP Channel support -- START*/
 /*Commented by Lilei for CQ48496 on 11192013, begin*/
#if 0
 // ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 //
 //  function: psNvmCreateDIPChannelChangeEnable
 //
 //  This function creates default NVM file for DIP
 //
 //
 //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateDIP
BOOL psNvmCreateDIPChannelChangeEnable(INT32* value )
{
#if defined (INTEL_FDI)
   
  FILE_ID  fileIndex;
  UINT32 StructSize = sizeof(DipChannelChangeStruct_ts);
   
#if !defined (GERAN_ONLY)
  NVMFormatHeader_ts  header;
#else
  NVMFormatHeader_ts  header = {
                                 StructSize,					   // StructSize
                                 1,							  // NumofStructs
                                 "DipChannelChangeStruct_ts",   // StructName
                                 "NULL",					  // Date
                                 "NULL",					  // time
                                 SYSTEM_CURRENT_VERSION,		  // Version
                                 "0", 						  // HW_ID
                                 "0"							  // CalibVersion
                                 };
#endif /* GERAN_ONLY */

  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateDIPChannelChangeEnable,DIAG_INFORMATION)
  diagPrintf ("start Create %s enable value: %d", "DipChannelChange", *value);
   
  fileIndex = FDI_fopen(DIP_CHANNEL_CHANGE_FILE_NAME, "wb");
   
#if !defined(GERAN_ONLY)
  // Create NVM standard header
  FDI_CreateNVMFormatHeader(&header, StructSize, 1,"DipChannelChangeStruct_ts",SYSTEM_CURRENT_VERSION,"0", "0");
#endif
  FDI_fwrite(&header, sizeof(NVMFormatHeader_ts), 1, fileIndex);
   
  psNvmSetDIPChannelChangeNvmDefaultParams(*value);
   
  FDI_fwrite( &dipChannelChangeParams, sizeof(dipChannelChangeParams), 1, fileIndex );
   
  FDI_fclose(fileIndex);
  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateDIPChannelChangeEnable1,DIAG_INFORMATION)
  diagTextPrintf ("Set DIP Channel Change status is compeleted");
   
  return(TRUE);
#else
  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateDIPChannelChangeEnable2,DIAG_INFORMATION)
  diagTextPrintf ("current build doesn't support intel FDI");
  return(FALSE);
#endif
}

 // ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 //
 //  function: psNvmDIPChannelChangeRead
 //
 //  This function reads SYTEM's NVM file.
 //
 //
 //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 BOOL psNvmDIPChannelChangeRead(void)
 {
#if defined (INTEL_FDI)
   FILE_ID	fileIndex;
   FILE_INFO  info;
   //UINT8 count;
   char fileName[NVM_HEADER_FIELD_SIZE];
   NVMFormatHeader_ts  header;
 
   //psNvmSetDIPChannelChangeNvmDefaultParams(1);
 
   strcpy(fileName,DIP_CHANNEL_CHANGE_FILE_NAME);
 
   if (FDI_findfirst(fileName, &info) != 0)
   {
      INT32 enabled = 0; 
      psNvmCreateDIPChannelChangeEnable(&enabled);
   
      return(TRUE);
   }
 
   fileIndex = FDI_fopen(info.file_name, "rb");
 
   DIAG_FILTER(SYSTEM, SYSNVM, SYS_READ_DIP_NVM, DIAG_INFORMATION)
   diagPrintf("read %d words from file %s", info.size, fileName);
 
   //FDI_fseek(fileIndex,0,SEEK_SET);
 
   FDI_fread((void *)(&header),1, sizeof(NVMFormatHeader_ts),fileIndex);
 
   FDI_fread((void *)(&dipChannelChangeParams),1, info.size-sizeof(NVMFormatHeader_ts),fileIndex);

   FDI_fclose(fileIndex);
 
 
   return TRUE;
#else
   psNvmSetDIPChannelChangeNvmDefaultParams(0);
 
   DIAG_FILTER(SYSTEM, SYSNVM, NO_FDI_SUPPORT_RETURN_DEFAULT_DIP,DIAG_INFORMATION)
   diagTextPrintf ("Current build does not support FDI. return default.");
  return FALSE;
#endif /* INTEL_FDI */
 
 }

 // ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 //
 //  function: psNvmSetDIPChannelChangeNvmDefaultParams
 //
 //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmSetDIPChannelChangeNvmDefaultParams(INT32 value)
{
    DipChannelChangeStruct_ts  DipChannelChange;
    INT32 i;
    memset(&DipChannelChange,-1,sizeof(DipChannelChangeStruct_ts));
    DipChannelChange.DipEnable = value;/* 0-disabled.
                                          1-enable manual mode for all case.
                                          2-enable manual mode for special case(such as test SIMcards, no SIM card)
                                          3-enable auto mode for end-user:use cpufreqd auto mode, and only handle the result
                                            based on lab test result; possiblity that the system could not deep channel freq request.  */
    for(i = 0; i<CHAN_FREQ_MAP_STRUCT_MAP_ARRAY_SIZE; i++)
    {
      DipChannelChange.MapArray[i].CpuFreqBitMap = 1;
    }

    memcpy( &(dipChannelChangeParams), &DipChannelChange, sizeof(DipChannelChangeStruct_ts) );
}
 #endif
 /*Commented by Lilei for CQ48496 on 11192013, end*/
/*Alan DIP Channel support -- END*/
#if !defined (ON_PC)   

/*Fixed for U+D begin date: 2010-08-11 yinfei*/

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreateOptVersion
//
//  This function creates default NVM file for SYSTEM.
//    Vendor Specific Data is MTNET
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateOptVersion
void psNvmCreateOptVersion(UINT8 *versionNum)
{
#if defined (INTEL_FDI)
	
	FILE_ID  fileIndex;
	UINT32 StructSize = sizeof(SystemcNvm_ts);

#if !defined (GERAN_ONLY)
		NVMFormatHeader_ts	header;
#else
		NVMFormatHeader_ts	header =	{
									  StructSize,						   // StructSize
									  1,						// NumofStructs
									  "SystemcNvm_ts",				// StructName
									  "NULL",				// Date
									  "NULL",				// time
									  SYSTEM_CURRENT_VERSION,  // Version
									  "0",							   // HW_ID
									  "0"							 // CalibVersion
									   };
#endif /* GERAN_ONLY */


	psNvmRead();

    systemcNvmParams.optMethodFlag = *versionNum;
  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNew6,DIAG_INFORMATION)
  diagPrintf ("start to create OptVersion %d", *versionNum);




  fileIndex = FDI_fopen(SYSTEM_FILE_NAME, "wb");

#if !defined(GERAN_ONLY)
	// Create NVM standard header
	FDI_CreateNVMFormatHeader(&header, StructSize, 1,"SystemcNvm_ts",SYSTEM_CURRENT_VERSION,"0", "0");
#endif
	FDI_fwrite(&header, sizeof(NVMFormatHeader_ts), 1, fileIndex);



  FDI_fwrite( &systemcNvmParams, sizeof(systemcNvmParams), 1, fileIndex );


  FDI_fclose(fileIndex);

#else
  DIAG_FILTER(SYSTEM, SYSNVM, SYS_NVM_CreateNotSupported8,DIAG_INFORMATION)
  diagTextPrintf ("current build doesn't support intel FDI");
#endif  

}

/*Fixed for U+D End date: 2010-08-11 yinfei*/

#endif
/*Added by Alan for at+bglteplmn on 08032012, begin*/
#if 0
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 //
 //  function: psNvmSetBackgroundSearchNvmDefaultParams
 //
 //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmSetBackgroundSearchNvmDefaultParams(void)
{
  backgroundSearchParams.isBackgroundSearch = FALSE;
  backgroundSearchParams.backgroundSearchInterval = 0xFFFF;
}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmReadBackgroundSearchInfo
//
//  This function reads BackgroundSearch's NVM file.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BOOL psNvmReadBackgroundSearchInfo(void)
{
#if defined (INTEL_FDI)
  FILE_ID  fdiID;
  FILE_INFO  fileInfo;
  NVMFormatHeader_ts  header;

  //UINT8 count;
  char fileName[NVM_HEADER_FIELD_SIZE];

  strcpy(fileName,BACKGROUND_SEARCH_FILE_NAME);

  if (FDI_findfirst(fileName, &fileInfo) != 0)
  {
    psNvmSetBackgroundSearchNvmDefaultParams();
    psNvmCreateBackgroundSearchInfo(&backgroundSearchParams);
    return(TRUE);
  }

  if(FDI_findfirst((const FDI_TCHAR *)fileName, &fileInfo) == 0)
  {
    /* '0' open fail, !'0' open ok. */
    if((fdiID = FDI_fopen((const FDI_TCHAR *)fileName,"rb")) != 0)
    {
	  FDI_fread((void *)(&header),1, sizeof(NVMFormatHeader_ts),fdiID);
	  if(header.StructSize != (fileInfo.size-sizeof(NVMFormatHeader_ts)) )
      {
        DIAG_FILTER(SYSTEM, SYSNVM, Warnning_psNvmReadBackgroundSearchInfo, DIAG_INFORMATION)
        diagTextPrintf("Warnning - BackgroundSearch.nvm may be destroied. use the default configuration");

	    FDI_fclose(fdiID);
	
        psNvmSetBackgroundSearchNvmDefaultParams();
        psNvmCreateBackgroundSearchInfo(&backgroundSearchParams);

	    return TRUE;
      }
	  FDI_fread((void *)(&backgroundSearchParams), 1, fileInfo.size-sizeof(NVMFormatHeader_ts), fdiID);
      FDI_fclose(fdiID);  
    }
  }

  return TRUE;
#else
  psNvmSetBackgroundSearchNvmDefaultParams();

  DIAG_FILTER(SYSTEM, SYSNVM, NO_FDI_SUPPORT_RETURN_DEFAULT_DIP,DIAG_INFORMATION)
  diagTextPrintf ("Current build does not support FDI. return default.");
  return FALSE;
#endif /* INTEL_FDI */

}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreateBackgroundSearchInfo
//
//  This function creates BackgroundSearch's NVM file.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateBackgroundSearchInfo
BOOL psNvmCreateBackgroundSearchInfo(BackgroundSearchNvm_ts* params)
{
#if defined (INTEL_FDI)

  FILE_ID  fileIndex;
  UINT32 StructSize = sizeof(BackgroundSearchNvm_ts);

#if !defined (GERAN_ONLY)
  NVMFormatHeader_ts  header;
#else
  NVMFormatHeader_ts  header =    {
								StructSize, 	                     // StructSize
								1, 						  // NumofStructs
								"BackgroundSearchNvm_ts",			  // StructName
								"NULL",				  // Date
								"NULL",				  // time
								"0",  // Version
								"0",					         // HW_ID
								"0"				               // CalibVersion
							     };
#endif /* GERAN_ONLY */


  fileIndex = FDI_fopen(BACKGROUND_SEARCH_FILE_NAME, "wb");

#if !defined(GERAN_ONLY)
  // Create NVM standard header
  FDI_CreateNVMFormatHeader(&header, StructSize, 1,"BackgroundSearchNvm_ts","0","0", "0");
#endif
  FDI_fwrite(&header, sizeof(NVMFormatHeader_ts), 1, fileIndex);
  memcpy(&backgroundSearchParams, params, sizeof(BackgroundSearchNvm_ts));
  FDI_fwrite( &backgroundSearchParams, sizeof(BackgroundSearchNvm_ts), 1, fileIndex );
  FDI_fclose(fileIndex);

  return(TRUE);
#else
  return(FALSE);
#endif

}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmGetBackgroundSearchInfo
//
//  This function Get BackgroundSearch Info.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmGetBackgroundSearchInfo(BackgroundSearchNvm_ts* params)
{
  memcpy(params, &backgroundSearchParams, sizeof(BackgroundSearchNvm_ts));
}
#endif
/*Added by Alan for at+bglteplmn on 08032012, end*/
/*Fixed CQ00024251 xyzheng for U+D optimistion end 2012-11-07*/
/*Added by Alan for PDN config on 09052012, begin*/

#if 0 /*zhangxia 20130801*/
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 //
 //  function: psNvmSetPdnConfigNvmDefaultParams
 //
 //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmSetPdnConfigNvmDefaultParams(void)
{
  UINT8 pcoData[] = {0x80,0x21,0x10,0x01,0x01,0x00,0x10,
                         0x81,0x06,0x00,0x00,0x00,0x00,
                         0x83,0x06,0x00,0x00,0x00,0x00,
                         0x00,0x0a,0x00,0x00,0x0d,0x00,0x00,0x0c,0x00};

  pdnConfigParams.PdnType = PDN_TYPE_IP_V4;
  pdnConfigParams.ReqType = REQ_TYPE_INITIAL;

  pdnConfigParams.pppConfigOpts.protocol = PDN_CONFIG_PROTOCOL_PPP;
  pdnConfigParams.pppConfigOpts.length = sizeof(pcoData);
  memcpy(pdnConfigParams.pppConfigOpts.data,
			   pcoData,
			   pdnConfigParams.pppConfigOpts.length);
  
  pdnConfigParams.eitfPresent = FALSE;
  pdnConfigParams.apnNamePresent = FALSE;
  pdnConfigParams.length = 0; //length of apnmae
  memset(pdnConfigParams.apnName,0,MAX_APN_NAME_NVM); 

}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmReadPdnConfigInfo
//
//  This function reads PdnConfig's NVM file.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
BOOL psNvmReadPdnConfigInfo(void)
{
#if defined (INTEL_FDI)
  FILE_ID  fdiID;
  FILE_INFO  fileInfo;
  NVMFormatHeader_ts  header;

  //UINT8 count;
  char fileName[NVM_HEADER_FIELD_SIZE];

  strcpy(fileName,PDN_CONFIG_FILE_NAME);

  if (FDI_findfirst(fileName, &fileInfo) != 0)
  {
    psNvmSetPdnConfigNvmDefaultParams();
    psNvmCreatePdnConfigInfo(&pdnConfigParams);
    return(TRUE);
  }

  if(FDI_findfirst((const FDI_TCHAR *)fileName, &fileInfo) == 0)
  {
    /* '0' open fail, !'0' open ok. */
    if((fdiID = FDI_fopen((const FDI_TCHAR *)fileName,"rb")) != 0)
    {
	  FDI_fread((void *)(&header),1, sizeof(NVMFormatHeader_ts),fdiID);
	  if(header.StructSize != (fileInfo.size-sizeof(NVMFormatHeader_ts)) )
      {
        DIAG_FILTER(SYSTEM, SYSNVM, Warnning_psNvmReadPdnConfigInfo, DIAG_INFORMATION)
        diagTextPrintf("Warnning - PdnConfig.nvm may be destroied. use the default configuration");

	    FDI_fclose(fdiID);
	
        psNvmSetPdnConfigNvmDefaultParams();
        psNvmCreatePdnConfigInfo(&pdnConfigParams);

	    return TRUE;
      }
      FDI_fread((void *)(&pdnConfigParams), 1, fileInfo.size-sizeof(NVMFormatHeader_ts), fdiID);
      FDI_fclose(fdiID);  
    }
  }

  return TRUE;
#else
  psNvmSetPdnConfigNvmDefaultParams();

  DIAG_FILTER(SYSTEM, SYSNVM, NO_FDI_SUPPORT_RETURN_DEFAULT_DIP,DIAG_INFORMATION)
  diagTextPrintf ("Current build does not support FDI. return default.");
  return FALSE;
#endif /* INTEL_FDI */

}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmCreatePdnConfigInfo
//
//  This function creates PdnConfig's NVM file.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//ICAT EXPORTED FUNCTION - PS, SYSNVM, psNvmCreateBackgroundSearchInfo
BOOL psNvmCreatePdnConfigInfo(PdnConfigNvm_ts* params)
{
#if defined (INTEL_FDI)

  FILE_ID  fileIndex;
  UINT32 StructSize = sizeof(PdnConfigNvm_ts);

#if !defined (GERAN_ONLY)
  NVMFormatHeader_ts  header;
#else
  NVMFormatHeader_ts  header =    {
								StructSize, 	                     // StructSize
								1, 						  // NumofStructs
								"PdnConfigNvm_ts",			  // StructName
								"NULL",				  // Date
								"NULL",				  // time
								"0",  // Version
								"0",					         // HW_ID
								"0"				               // CalibVersion
							     };
#endif /* GERAN_ONLY */


  fileIndex = FDI_fopen(PDN_CONFIG_FILE_NAME, "wb");

#if !defined(GERAN_ONLY)
  // Create NVM standard header
  FDI_CreateNVMFormatHeader(&header, StructSize, 1,"PdnConfigNvm_ts","0","0", "0");
#endif
  FDI_fwrite(&header, sizeof(NVMFormatHeader_ts), 1, fileIndex);
  memcpy(&pdnConfigParams, params, sizeof(PdnConfigNvm_ts));
  FDI_fwrite( &pdnConfigParams, sizeof(PdnConfigNvm_ts), 1, fileIndex );
  FDI_fclose(fileIndex);

  return(TRUE);
#else
  return(FALSE);
#endif

}

// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//
//  function: psNvmGetPdnConfigInfo
//
//  This function Get PdnConfig Info.
//
//
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void psNvmGetPdnConfigInfo(PdnConfigNvm_ts* params)
{
  memcpy(params, &pdnConfigParams, sizeof(PdnConfigNvm_ts));
}

/*Added by Alan for PDN config on 09052012, end*/
#endif
/* END OF FILE */
