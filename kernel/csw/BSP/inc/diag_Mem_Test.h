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
// diag_Mem_Test.h
//

#ifndef _DIAG_MEM_TEST_H_
#define _DIAG_MEM_TEST_H_

// External function poinetrs prototypes
typedef signed long	 (*EXT_PeakDynPoolAlloc_ptr)(void);
typedef signed short (*EXT_PeakStaticPoolAlloc_ptr)(signed short);

typedef void (*EXT_ResetPeakDynPool_ptr)(void);
typedef void (*EXT_ResetPeakStaticPools_ptr)(void);

typedef signed long	 (*EXT_DynPoolSize_ptr)(void);
typedef signed long	 (*EXT_StaticPoolSize_ptr)(signed short);
typedef signed short (*EXT_StaticBlockSize_ptr)(signed short);
typedef signed short (*EXT_StaticPoolNumOfBlocks_ptr)(signed short);


// Functions Prototypes
void EXT_SetMemoryFunctionsPtr(EXT_PeakDynPoolAlloc_ptr 		PeakDynPoolAlloc_FuncAddress,
							   EXT_PeakStaticPoolAlloc_ptr	PeakStaticPoolAlloc_FuncAddress,
						 	   EXT_DynPoolSize_ptr			DynPoolSize_FuncAddress,
						 	   EXT_StaticPoolSize_ptr			StaticPoolSize_FuncAddress,
						 	   EXT_StaticBlockSize_ptr			StaticBlockSize_FuncAddress,
						 	   EXT_StaticPoolNumOfBlocks_ptr	StaticPoolNumOfBlocks_FuncAddress,
							   EXT_ResetPeakDynPool_ptr			ResetPeakDynPool_FuncAddress,
							   EXT_ResetPeakStaticPools_ptr		ResetPeakStaticPools_FuncAddress);

#endif
