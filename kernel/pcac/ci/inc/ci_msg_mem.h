/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/*=========================================================================
  
  File Name:    ci_msg_mem.h

  Description:  This is the memory management function for CI SIM Client and  server stub 

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
#if !defined(_CI_MSG_MEM_H_)
#define _CI_MSG_MEM_H_

#include "ci_api_types.h"

#if 0
#ifndef CCI_MSG_CONTIGUOUS

#include "ci_stub.h"
#include "msl_mem.h"
#include "osa.h"

UINT32 cimem_GetMsgPrimDataSize(CiPrimitiveID primId, void *paras);
void *cimem_CiMsgAllocMem (CiPrimitiveID primId);
void cimem_CiMsgFreeMem (CiPrimitiveID primId, void*);

#endif
#endif

#define CI_MSG_VERSION_0001 0x0001


Boolean ciMsgAdjustSacCiReq(CiServiceHandle handle, CiPrimitiveID primId, void* paras);
Boolean ciMsgAdjustSacCiInd(CiServiceGroupID sgId, CiPrimitiveID indPrimId, void *indParas);
Boolean ciMsgAdjustSacCiCnf(CiServiceGroupID sgId, CiPrimitiveID cnfPrimId, void *cnfParas);

#endif

