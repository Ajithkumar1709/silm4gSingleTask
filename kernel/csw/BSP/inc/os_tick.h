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

#ifndef _OS_TICK_H_
#define _OS_TICK_H_

#include "global_types.h"
#include "hal_cfg.h"

/* Power Manager Interface */
UINT32 OsMaximumSleep(void);
void   OsTickUpdate(UINT32 ticks);

/* OS tick (Timer ISR handler) */
/* NOTE: OSTick is a macro defined in osa.h, so consider it reserved */
void OSTickHandler(void);

/* Extended tick interface (GKI) */
typedef void TickAdvance_ft(UINT32 ticks);
typedef UINT32 TicksToSkip_ft(UINT32 ticks);
typedef BOOL TickLptCall_ft(void);
void extTickBind(TickAdvance_ft* pA, TicksToSkip_ft* pS);
void extTickIdlecallBind(TickLptCall_ft pL) ;


#endif //_OS_TICK_H_
