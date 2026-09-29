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

#ifndef _MUX_REGS_H_
#define _MUX_REGS_H_

#include "global_types.h"

//Base address of IOMCRG
#define MUX_REGS_BASE       0x42A00400

//IOMCRS address = 0x42a01000
#define IOMCRS_BASE         0x42A01000

//Number of IOMCRG registers
#define IOMCRG_GROUP        9

// Imaged General Regs (mostly for pin Mux use)
typedef struct
{
  UINT32 IOMCRG[9];
  UINT32 IOMCRS[3];
}muxRegs_t;

#endif
