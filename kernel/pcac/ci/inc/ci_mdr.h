/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/*===========================================================================
File name: ci_mdr.h
Purpose: Common data for stub functions.

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
===========================================================================*/
#ifndef _CI_MDR_H_
#define _CI_MDR_H_

#include "ci_api_types.h"
#include "ci_err.h"
#include "ci_stub.h"
#include "msl_sal_dr_type.h"
#include "msl_sal_dr_api.h"

typedef UINT32 enum_t;

/* ====================== MDR functions for CI CI APIs  =================== */
BOOL mdr_CiShRegisterReqArgs(MslDrStream *mdrs, CiShRegisterReqArgs* objp);
BOOL mdr_CiShDeregisterReqArgs(MslDrStream *mdrs, CiShDeregisterReqArgs* objp);
BOOL mdr_CiShRequestArgs(MslDrStream *mdrs, CiShRequestArgs* objp);
BOOL mdr_CiRequestArgs(MslDrStream *mdrs, CiRequestArgs* objp);
BOOL mdr_CiRespondArgs(MslDrStream *mdrs, CiRespondArgs* objp);

BOOL mdr_CiShConfirmArgs(MslDrStream* mdrs, CiShConfirmArgs* objp);
BOOL mdr_CiConfirmArgs(MslDrStream* mdrs, CiConfirmArgs* objp);
BOOL mdr_CiIndicateArgs(MslDrStream* mdrs, CiIndicateArgs* objp);  

BOOL mdr_CiReturnCode(MslDrStream* mdrs, CiReturnCode* objp);

/* ====================== Mdr Routing functions for each svc group=================== */
BOOL mdr_CiShReqDispatcher(MslDrStream* mdrs, void* objp, CiShOper oper);
BOOL mdr_CiShCnfDispatcher(MslDrStream* mdrs, void* objp, CiShOper oper);

BOOL mdr_CiDispatcher(MslDrStream *mdrs, void* objp, CiServiceGroupID svcGroupId, CiPrimitiveID primitiveId);
BOOL mdr_CiMmDispatcher(MslDrStream *mdrs, void* objp, CiPrimitiveID primitiveId);
BOOL mdr_CiSimDispatcher(MslDrStream *mdrs, void* objp, CiPrimitiveID primitiveId);
BOOL mdr_CiDevDispatcher(MslDrStream *mdrs, void* objp, CiPrimitiveID primitiveId);
BOOL mdr_CiCcDispatcher(MslDrStream *mdrs, void* objp, CiPrimitiveID primitiveId);
BOOL mdr_CiDatDispatcher(MslDrStream *mdrs, void* objp, CiPrimitiveID primitiveId);
BOOL mdr_CiMsgDispatcher(MslDrStream *mdrs, void* objp, CiPrimitiveID primitiveId);
BOOL mdr_CiPsDispatcher(MslDrStream *mdrs, void* objp, CiPrimitiveID primitiveId);
BOOL mdr_CiSsDispatcher(MslDrStream *mdrs, void* objp, CiPrimitiveID primitiveId);
BOOL mdr_CiPbDispatcher(MslDrStream *mdrs, void* objp, CiPrimitiveID primitiveId);

/* ====================== Mdr functions for Common CI Data Types =================== */
BOOL mdr_CiShConfirm(MslDrStream *mdrs, CiShConfirm* objp);
BOOL mdr_CiShFreeReqMem(MslDrStream* mdrs, CiShFreeReqMem* objp);
BOOL mdr_CiIndicationHandle(MslDrStream* mdrs, CiIndicationHandle* objp);
BOOL mdr_CiServiceHandle(MslDrStream* mdrs, CiServiceHandle* objp);

BOOL mdr_CiRequestHandle(MslDrStream *mdrs, CiRequestHandle* objp);
BOOL mdr_CiShRequestHandle(MslDrStream* mdrs, CiShRequestHandle* objp);
BOOL mdr_CiShHandle(MslDrStream* mdrs, CiShHandle* objp);
BOOL mdr_CiShOpaqueHandle(MslDrStream* mdrs, CiShOpaqueHandle* objp);
BOOL mdr_CiSgOpaqueHandle(MslDrStream* mdrs, CiSgOpaqueHandle* objp);
BOOL mdr_CiShOper(MslDrStream* mdrs, CiShOper* objp);

BOOL mdr_CiServiceGroupID(MslDrStream* mdrs, CiServiceGroupID* objp);
BOOL mdr_CiPrimitiveID(MslDrStream* mdrs, CiPrimitiveID* objp);
BOOL mdr_CiAddrNumType(MslDrStream* mdrs, CiAddrNumType* objp);
BOOL mdr_CiAddrNumPlan(MslDrStream* mdrs, CiAddrNumPlan* objp);
BOOL mdr_CiAddressType(MslDrStream* mdrs, CiAddressType* objp);
BOOL mdr_CiAddressInfo(MslDrStream* mdrs, CiAddressInfo* objp);
BOOL mdr_CbMessageCoding(MslDrStream* mdrs, UINT8* objp);
BOOL mdr_CiOptAddressInfo(MslDrStream* mdrs, CiOptAddressInfo* objp);
BOOL mdr_CiSubaddrInfo(MslDrStream* mdrs, CiSubaddrInfo* objp);
BOOL mdr_CiNameInfo(MslDrStream* mdrs, CiNameInfo* objp);
BOOL mdr_CiOptNameInfo(MslDrStream* mdrs, CiOptNameInfo* objp);
BOOL mdr_CiCallerInfo(MslDrStream* mdrs, CiCallerInfo* objp);
BOOL mdr_CiSsiCallStatus(MslDrStream* mdrs, CiSsiCallStatus* objp);
BOOL mdr_CiSsiNotifyInfo(MslDrStream* mdrs, CiSsiNotifyInfo* objp);
BOOL mdr_CiSsuCallStatus(MslDrStream* mdrs, CiSsuCallStatus* objp);
BOOL mdr_CiSsuNotifyInfo(MslDrStream* mdrs, CiSsuNotifyInfo* objp);
BOOL mdr_CiBsTypeSpeed(MslDrStream* mdrs, CiBsTypeSpeed* objp);
BOOL mdr_CiPassword(MslDrStream* mdrs, CiPassword* objp);
BOOL mdr_CiString(MslDrStream* mdrs, CiString* objp);
BOOL mdr_CiNumericRange(MslDrStream* mdrs, CiNumericRange* objp);
BOOL mdr_CiBitRange(MslDrStream* mdrs, CiBitRange* objp);
BOOL mdr_CiNumericList(MslDrStream* mdrs, CiNumericList* objp);

/* ====================== Mdr unctions for error primitive =================== */
BOOL mdr_CiErrPrimHasInvalidParasCnf(MslDrStream* mdrs, CiErrPrimHasInvalidParasCnf* objp);
BOOL mdr_CiErrPrimAccessDeniedCnf(MslDrStream* mdrs, CiErrPrimAccessDeniedCnf* objp);
BOOL mdr_CiErrPrimInterlinkDownInd(MslDrStream* mdrs, CiErrPrimInterlinkDownInd* objp);
BOOL mdr_CiErrPrimInterlinkDownRsp(MslDrStream* mdrs, CiErrPrimInterlinkDownRsp* objp);

BOOL mdr_CiVoid(MslDrStream* mdrs, void* objp);
void mdr_CiMdrError(void);


/* ====================== Common Utility Mdr unctions  =================== */
BOOL mdr_CiCheckPointer(MslDrStream* mdrs);
/* Michal Bukai & Boris Tsatkin ?AT&T Smart Card support - Start*/
/*** AT&T- Smart Card   -BT1 ****/
BOOL mdr_CiLongAdrInfo(MslDrStream* mdrs, CiLongAdrInfo * objp);
BOOL mdr_CiEditCmdType(MslDrStream* mdrs, CiEditCmdType* objp);
/* Michal Bukai & Boris Tsatkin ?AT&T Smart Card support - End*/
#endif //_CI_MDR_H_




