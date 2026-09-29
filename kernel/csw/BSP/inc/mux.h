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

#ifndef _MUX_H
#define _MUX_H

#include "muxregs.h"
#include "manitoba_pads_def.h"

//Map HW regs to image regs
#define IOMCRG0 IOMCRG[0]
#define IOMCRG1 IOMCRG[1]
#define IOMCRG2 IOMCRG[2]
#define IOMCRG3 IOMCRG[3]
#define IOMCRG4 IOMCRG[4]
#define IOMCRG5 IOMCRG[5]
#define IOMCRG6 IOMCRG[6]
#define IOMCRG7 IOMCRG[7]
#define IOMCRG8 IOMCRG[8]
#define IOMCRS0 IOMCRS[0]
#define IOMCRS1 IOMCRS[1]
#define IOMCRS2 IOMCRS[2]


typedef struct muxRegsImage
{
   muxRegs_t regs;             // Image
   UINT32 durty;           // H/W reg update required
}muxRegsImage_t;

extern muxRegsImage_t muxRegsImage;


#define IS_MUX(pADnAME,fUNCTION)                                                                           \
    (( (RGET(pADnAME##_REG) >> pADnAME##_SHIFT) & pADnAME##_MASK ) == pADnAME##_##fUNCTION)


#define GET_MUX(pADnAME)                                                                           \
    ( (RGET(pADnAME##_REG) >> pADnAME##_SHIFT) & pADnAME##_MASK )

#define SET_MUX(pADnAME,fUNCTION)                                                                  \
   RSET(pADnAME##_REG,(                                                                            \
            (RGET(pADnAME##_REG) & ~((UINT32)(pADnAME##_MASK) << pADnAME##_SHIFT)) |                       \
             ((UINT32)(pADnAME##_##fUNCTION & pADnAME##_MASK) << pADnAME##_SHIFT)  \
            ))

// Register access for internal use
#define RSET(reg,val) \
      (muxRegsImage.durty|=1<<((UINT32*)(&muxRegsImage.regs.reg) - (UINT32*)(&muxRegsImage.regs)), muxRegsImage.regs.reg=(val))
#define RGET(reg) \
      (muxRegsImage.regs.reg)

int muxUpdateIomRegs(void);

#endif
