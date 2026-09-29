/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/*=========================================================================
  
  File Name:    ci_mem.h

  Description:  This is the memory management function for Ci Client and  server stub 

  Revision:     Phillip Cho, 0.1
  
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

Unless otherwise agreed by Intel in writing, you may not remove or alter this notice or any other notice embedded
in Materials by Intel or Intel's suppliers or licensors in any way.
  ======================================================================== */
#if !defined(_CI_MEM_H_)
#define _CI_MEM_H_
#if defined(PC_TTCN_INT_TEST)
#include "diag.h"
#endif
#include "ci_api_types.h"
#ifndef NAS_UNIT_TEST
#include "ci_stub.h"
#include "ci_trace.h"
#include "msl_mem.h"
#endif//NAS_UNIT_TEST
#include "osa.h"

#define MAX_LEN_OF_UINT8 256

typedef struct CiSgCiVersionInfo_tag
{
    UINT8 number;
    CiVersion ciVer[CI_SH_SUPPORT_VERSION_MAX_NUM];
}CiSgCiVersionInfo;


// OSAMemPoolAlloc(poolRef, sizeOfBuf, &bufBegin, OSA_NO_SUSPEND);
#define CI_MEM_ALLOC(x) ((x)==0? NULL:malloc(x))

#define CI_MEM_FREE(x) 	if((x)!=NULL) free(x)

#if defined(PC_TTCN_INT_TEST)
#undef CCI_ASSERT
#define CCI_ASSERT(cond)   if (cond == 0) while (1){printf("ASSERT at %d %s",__LINE__,__FILE__);OSATaskSleep(1000);}
#endif

/******************************************************************************
 * functions
******************************************************************************/
typedef Boolean (*CiSgAdjustSacCiReq)(CiServiceHandle handle, CiPrimitiveID primId, void* paras);
typedef Boolean (*CiSgAdjustSacCiInd)(CiServiceGroupID sgId, CiPrimitiveID indPrimId, void *indParas);
typedef Boolean (*CiSgAdjustSacCiCnf)(CiServiceGroupID sgId, CiPrimitiveID cnfPrimId, void *cnfParas);

/* Memory Alloc and free for CI Shell operation */
void *cimem_CiShAllocReqMem (CiShOper);
void *cimem_CiShAllocCnfMem (CiShOper);
//void cimem_CiShFreeReqMem (CiShOpaqueHandle opShFreeHandle, CiShOper oper, void* reqParas);
void cimem_CiShFreeCnfMem (CiShOpaqueHandle opShFreeHandle, CiShOper oper, void* reqParas);
UINT32 cimem_GetCiShReqDataSize(CiShOper oper);
UINT32 cimem_GetCiShCnfDataSize(CiShOper oper,void* cnfParas);

#ifdef CI_STUB_CLIENT_INCLUDE
/* Memory Alloc and free for CI service group for Client */
void *cimem_CiSgCnfIndAllocMem (CiServiceGroupID id, CiPrimitiveID primId);
#endif

void *cimem_CiSgAllocMem (CiServiceHandle handle, CiPrimitiveID primId);
void cimem_CiSgFreeMem (CiSgOpaqueHandle, CiServiceGroupID, CiPrimitiveID, void* paras);
UINT32 cimem_GetCiPrimDataSize(CiServiceHandle handle,CiPrimitiveID primId, void *paras);

UINT32 cimem_GetCiNumericListDataSize( CiNumericList *pNumericLst );

void ciSgCiVersionInit(void);
void ciNegotiateSgCiVersion(CiShOperCIVersionNegoReq *ciVerNegoReq, CiShOperCIVersionNegoCnf *reCiVerCnf);
Boolean ciAdjustSacCiInd(CiServiceGroupID sgId, CiPrimitiveID indPrimId, void *indParas);
Boolean ciAdjustSacCiReq(CiServiceHandle handle, CiPrimitiveID primId, void* paras);
Boolean ciAdjustSacCiCnf(CiServiceGroupID sgId, CiPrimitiveID cnfPrimId, void *cnfParas);

#endif
