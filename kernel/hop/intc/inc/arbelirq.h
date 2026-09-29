/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/*******************************************************************************
 *  COPYRIGHT (C) 2003, 2004 Intel Corporation.
 *
 *  This software as well as the software described in it is furnished under
 *  license and may only be used or copied in accordance with the terms of the
 *  license. The information in this file is furnished for informational use
 *  only, is subject to change without notice, and should not be construed as
 *  a commitment by Intel Corporation. Intel Corporation assumes no
 *  responsibility or liability for any errors or inaccuracies that may appear
 *  in this document or any software that may be provided in association with
 *  this document.
 *  Except as permitted by such license, no part of this document may be
 *  reproduced, stored in a retrieval system, or transmitted in any form or by
 *  any means without the express written consent of Intel Corporation.
 *
 ******************************************************************************/

#if !defined (ARBELIRQ_H)
#define       ARBELIRQ_H

#include "xirq_config.h"
#include "osa.h"


#define INTC_SYS_REG_ADDR (IRQCTRL_BASE_ADDR+0x8C)
#define INTC_SYS_REG_REG16     (* (volatile UINT16*) INTC_SYS_REG_ADDR)
#define INTC_SYS_REG_SET16(val)  INTC_SYS_REG_REG16 = (val)

#ifndef PLAT_TEST
#define         NU_Control_Interrupts           TCT_Control_Interrupts
extern int NU_Control_Interrupts(int new_level);
#endif
/***************************************************************************
 * Manifest Constants
 **************************************************************************/

/* Masks */
#define IC_SWI_EN_MASK        0xFFFF
#define IC_RI_EN_MASK         0x00FF
#define IC_XSWI_EN_MASK       0x0001
#define IC_EIRQ_EN_MASK       0x0007
/* Mask of valid priority bits written to IC_xxx_PRI registers above */
#define IC_PRI_MASK           0xF


/* Flags */
#define IC_CLR_ENABLE         0x40
#define IC_SET_ENABLE         0x00


// Interrupt controller base address: IC_BASE_ADDRESS is defeatured, use IRQCTRL_BASE_ADDR

/* INTC registers offsets */
#define IC_SWI_ENABLE         0x00UL
#define IC_RI_ENABLE          0x04UL
#define IC_XSWI_ENABLE        0x08UL
#define IC_EIRQ_ENABLE        0x0CUL


/* NOTE: The number of HWIx_ENABLE registers actually implemented on target
 *       hardware depends on the NumHwi VHDL parameter that the IrqCtrl
 *       instance was instatiated with.
 */
#define IC_HWI0_ENABLE        0x20UL
#define IC_HWI1_ENABLE        0x24UL
#define IC_HWI2_ENABLE        0x28UL

#define IC_SWI_CLR_ENABLE     0x40UL
#define IC_REG_CLR_ENABLE     0x44UL
#define IC_EIRQ_CLR_ENABLE    0x48UL
#define IC_HWI0_CLR_ENABLE    0x60UL
#define IC_HWI1_CLR_ENABLE    0x64UL
#define IC_HWI2_CLR_ENABLE    0x68UL


#define IC_IRQ_PRI            0x80UL       /* Current Interrupt Priority */
#define IC_IRQ_NUM            0x84UL       /* Current Interrupt Number */

#define IC_ACTIVE_IRQ_MASK    0x88UL      /* Active Interrupt Mask */

#define IC_SYSTEM             0x8CUL       /* System Register */
#define IC_SYSTEM_RESET     0x0001       /* Reset bit in System Register */

#define IC_SWI_CARRY          0x90UL       /* SWI Carry Status (Bits 15:0) */
#define IC_RI_CARRY           0x94UL       /* RI Carry Status (Bits 7:0) */
#define IC_XSWI_CARRY         0x98UL       /* XSWI Carry Status (Bit 0) */
#define IC_CIN_VAL_REG        0x9CUL       /* Current Interrupt Number Value Register - same value as IC_IRQ_NUM, but
                                          * reading does not affect IC_ACTIVE_IRQ_MASK */

#define IC_SWI0_PRI           0xa0UL       /* SWIx Priority (bits 3:0) */
#define IC_SWI1_PRI           0xa4UL
#define IC_SWI2_PRI           0xa8UL
#define IC_SWI3_PRI           0xacUL
#define IC_SWI4_PRI           0xb0UL
#define IC_SWI5_PRI           0xb4UL
#define IC_SWI6_PRI           0xb8UL
#define IC_SWI7_PRI           0xbcUL
#define IC_SWI8_PRI           0xc0UL

#define IC_SWI9_PRI           0xc4UL
#define IC_SWI10_PRI          0xc8UL
#define IC_SWI11_PRI          0xccUL
#define IC_SWI12_PRI          0xd0UL
#define IC_SWI13_PRI          0xd4UL
#define IC_SWI14_PRI          0xd8UL
#define IC_SWI15_PRI          0xdcUL
//#define IC_SWIn_PRI(swi)     (IC_SWI0_PRI + (2*(swi)))
#define IC_SWIn_PRI(swi)     (IC_SWI0_PRI + (4*(swi)))

#define IC_RI0_PRI            0xe0UL       /* RIx Priority (bits 3:0) */
#define IC_RI1_PRI            0xe4UL
#define IC_RI2_PRI            0xe8UL
#define IC_RI3_PRI            0xecUL
#define IC_RI4_PRI            0xf0UL
#define IC_RI5_PRI            0xf4UL
#define IC_RI6_PRI            0xf8UL
#define IC_RI7_PRI            0xfcUL
//#define IC_RIn_PRI(ri)        (IC_RI0_PRI + (2*(ri)))
#define IC_RIn_PRI(ri)        (IC_RI0_PRI + (4*(ri)))

#define IC_XSWI_PRI           0x120UL       /* XSWI Priority (bits 3:0) */
# define IC_XSWI_EIRQ_PRI     0x140UL       /* Exception IRQ Priority (bits 3:0) */
# define IC_RI_EIRQ_PRI       0x144UL
# define IC_SWI_EIRQ_PRI      0x148UL
#define IC_EIRQ0_PRI          (IC_XSWI_EIRQ_PRI)       /* Exception IRQ Priority (bits 3:0) */


/* NOTE: The number of HWIx_PRI registers actually implemented on target
 *       hardware depends on the NumHwi VHDL parameter that the IrqCtrl
 *       instance was instatiated with.
 */
#define IC_HWI0_PRI           0x200UL      /* HWI0 Priority (bits 3:0) */
#define IC_HWIn_PRI(hwi)      (IC_HWI0_PRI + (4*(hwi)))



#define IC_SWI0_CNT           0x400UL      /* SWIx Count (bits 4:0) */
#define IC_SWI1_CNT           0x404UL
#define IC_SWI2_CNT           0x408UL
#define IC_SWI3_CNT           0x40cUL
#define IC_SWI4_CNT           0x410UL
#define IC_SWI5_CNT           0x414UL
#define IC_SWI6_CNT           0x418UL
#define IC_SWI7_CNT           0x41cUL
#define IC_SWI8_CNT           0x420UL
#define IC_SWI9_CNT           0x424UL
#define IC_SWI10_CNT          0x428UL
#define IC_SWI11_CNT          0x42cUL
#define IC_SWI12_CNT          0x430UL
#define IC_SWI13_CNT          0x434UL
#define IC_SWI14_CNT          0x438UL
#define IC_SWI15_CNT          0x43CUL
#define IC_SWIn_CNT(swi)      (IC_SWI0_CNT + (4*(swi)))

#define IC_RI_ASSERT          0x440UL      /* RI Register (bits 7:0) */

#define IC_XSWI_CNT           0x460UL      /* XSWI Count (bits 4:0) */
#define IC_XSWI_ASSERT        0x464UL      /* XSWI Assert (write any value) */
#define IC_IRQ_STATUS_CTRL    0x468UL

//#define IC_STICKY_CLR0        0x500UL - DUPLICATED, use IRQ_STICKY_CLR0
//#define IC_STICKY_CLR1        0x580UL - WRONG, UNUSED


/* Some other useful definitions */
#include "xirq_config.h"
#define PLKMERROR_XSWI          (MAX_NUM_IRQ)
#define VOICE_TASK_XSWI         (MAX_NUM_IRQ + 1)
#define SDVR_XSWI               (MAX_NUM_IRQ + 2)
#define I2S_XSWI                (MAX_NUM_IRQ + 3)
#define NUM_OF_VIRTUAL_INT       4

/***************************************************************************
 * Type Definitions
 **************************************************************************/


/***************************************************************************
 *  Macros
 **************************************************************************/

#define  WR_REG16(bASE, rEGoFFSET, vALUE)    (*(volatile UINT16 *) ((bASE) + (rEGoFFSET)) = (vALUE))
#define  RD_REG16(bASE, rEGoFFSET)           (*(volatile UINT16 *) ((bASE) + (rEGoFFSET)))
#define  WR_REG32(bASE, rEGoFFSET, vALUE)    (*(volatile UINT32 *) ((bASE) + (rEGoFFSET)) = (vALUE))
#define  RD_REG32(bASE, rEGoFFSET)           (*(volatile UINT32 *) ((bASE) + (rEGoFFSET)))
#ifdef PLAT_TEST
# define  DISABLE_ALL_IRUPTS()                OSAIsrEnable(0x80)
# define  ENABLE_ALL_IRUPTS()                 OSAIsrEnable(0x00)
# define  SET_ALL_IRUPTS( iRQsTATE )          OSAIsrEnable((iRQsTATE))
#else
# define  DISABLE_ALL_IRUPTS()                NU_Control_Interrupts(0xC0)
# define  ENABLE_ALL_IRUPTS()                 NU_Control_Interrupts(0x00)
# define  SET_ALL_IRUPTS( iRQsTATE )          NU_Control_Interrupts((iRQsTATE))
#endif
#define  IRQ_STATE_DISABLE   0x80
/***************************************************************************
 *  Function Prototypes
 **************************************************************************/
#endif /* #if !defined */

/* END OF FILE */

