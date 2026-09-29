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

#if !defined (ARBEL_IRQCTRL_H)
#define       ARBEL__IRQCTRL_H

/****************************************************************************
 * Nested Include Files
 ****************************************************************************/
#include "xirq_config.h"
# include <arbelirq.h>

//  #define   WR_IRQCTRL_REG(bASE, rEG, vALUE)    WR_REG32((bASE), (rEG), (vALUE))
#define   WR_IRQCTRL_REG(bASE, rEG, vALUE)    WR_REG16((bASE), (rEG), (vALUE))
/*******************************************************************************
 *
 * @Define:         RD_IRQCTRL_REG @
 *
 * @Interface:      PLK/M@
 *
 * @Description:    Macro to read a value from specified ABP IRQCTRL register @
 *
 ******************************************************************************/
//#  define   RD_IRQCTRL_REG(bASE, rEG)           RD_REG16(bASE, rEG)
//#  define     RD_IRQCTRL_REG(bASE, rEG)           RD_REG32((bASE), (rEG))
#  define     RD_IRQCTRL_REG(bASE, rEG)           RD_REG16((bASE), (rEG))
/****************************************************************************/

#define SWI_ENABLE_CLR_OFFSET   (0x0)
#define RI_ENABLE_CLR_OFFSET    (0x4)
#define XSWI_ENABLE_OFFSET      (0x8)

#define EIRQ_ENABLE_OFFSET      (0xC)
#define EIRQ_CLR_OFFSET         (0x8)

#define HWI_ENABLE_CLR_OFFSET   (0x20)

#define RD_WR_TYPE      UINT16

void IRQCTRL_HWI_STATE  (UINT32 bASE, UINT32 fLAG, UINT32 hWInUM);
void IRQCTRL_EIRQ_STATE (UINT32 bASE, UINT32 fLAG, UINT32 EirqInUM);
void IRQCTRL_XSWI_STATE (UINT32 bASE, UINT32 fLAG, UINT32 XswiInUM);
void IRQCTRL_RI_STATE   (UINT32 bASE, UINT32 fLAG, UINT32 RiInUM);
void IRQCTRL_SWI_STATE  (UINT32 bASE, UINT32 fLAG, UINT32 SwInUM);

#define REG_BYTE_SZ      (4)

/****************************************************************************/

/* IRQCTRL_STATE enables or disables the interrupt specified by it's absolute
 * interrupt number within the IRQCTRL. See IRQCTRL_ENABLE and IRQCTRL_DISABLE for
 * possible values of fLAG.
 */
#define IRQCTRL_STATE(bASE, fLAG, iRQnUM)                                                 \
      if (iRQnUM < NUM_SWI)                                                               \
         IRQCTRL_SWI_STATE(bASE, fLAG, (iRQnUM - SWI0_ID));                               \
      else                                                                                \
         if (iRQnUM < (NUM_SWI + NUM_RI))                                                 \
			IRQCTRL_RI_STATE(bASE, fLAG, (iRQnUM - RI0_ID));                              \
         else                                                                             \
            if (iRQnUM < (NUM_SWI + NUM_RI + NUM_XSWI))                                   \
			   IRQCTRL_XSWI_STATE(bASE, fLAG, (iRQnUM - XSWI_ID));                        \
            else                                                                          \
               if (iRQnUM < (NUM_SWI + NUM_RI + NUM_XSWI + NUM_EIRQ))                     \
				  IRQCTRL_EIRQ_STATE(bASE, fLAG, (iRQnUM - EIRQ0_ID));\
               else                                                                       \
                  IRQCTRL_HWI_STATE(bASE, fLAG , (iRQnUM - HWI0_ID));

/****************************************************************************/

/* IRQ_PRI sets the priority of interrupt given the absolute IRQ number */
#define IRQ_PRI(bASE, iRQnUM, pRI)                                                        \
      if (iRQnUM < NUM_SWI)                                                               \
         WR_IRQCTRL_REG(bASE, IC_SWI0_PRI + (REG_BYTE_SZ*(iRQnUM)), pRI);                           \
      else                                                                                \
         if (iRQnUM < (NUM_SWI + NUM_RI))                                                 \
            WR_IRQCTRL_REG(bASE, IC_RI0_PRI + (REG_BYTE_SZ*(iRQnUM - RI0_ID)), pRI);                \
         else                                                                             \
            if (iRQnUM < (NUM_SWI + NUM_RI + NUM_XSWI))                                   \
               WR_IRQCTRL_REG(bASE, IC_XSWI_PRI + (REG_BYTE_SZ*(iRQnUM - XSWI_ID)), pRI);           \
            else                                                                          \
               if (iRQnUM < (NUM_SWI + NUM_RI + NUM_XSWI + NUM_EIRQ))                     \
                WR_IRQCTRL_REG(bASE, IC_EIRQ0_PRI + (REG_BYTE_SZ*(iRQnUM - EIRQ0_ID)), pRI);      \
               else                                                                       \
                  WR_IRQCTRL_REG(bASE, IC_HWI0_PRI + (REG_BYTE_SZ*(iRQnUM - HWI0_ID)), pRI);

/****************************************************************************/

/* IRQCTRL_ENABLE/DISABLE the interrupt specified by it's absolute IRQ number */
#define IRQCTRL_ENABLE(bASE, iRQnUM)      IRQCTRL_STATE(bASE, IC_SET_ENABLE, iRQnUM)
#define IRQCTRL_DISABLE(bASE, iRQnUM)     IRQCTRL_STATE(bASE, IC_CLR_ENABLE, iRQnUM)

#define   IRQCTRL_MCU    IRQCTRL_BASE_ADDR
#define   IRQCTRL_DSP    IRQCTRL_BASE_ADDR
#if 0
#if defined (EDEN_1928) || defined (NEZHA3_1826)
/* Sticky bit clears*/
#define   IRQ_STICKY_CLR0  (0xD0250000)
#define   IRQ_STICKY_CLR1  (0xD0250004)
#define   IRQ_STICKY_CLR2  (0xD0250018)

#define   IRQ_LVL_EDG0    (volatile UINT32 *)(0xD0250008)
#define   IRQ_LVL_EDG1    (volatile UINT32 *)(0xD025000C)
#define   IRQ_LVL_EDG2    (volatile UINT32 *)(0xD0250010)

#else
/* Sticky bit clears*/
#define   IRQ_STICKY_CLR0  (IRQCTRL_BASE_ADDR+XIRQ_STICKY_OFFSET)
#define   IRQ_STICKY_CLR16 (IRQ_STICKY_CLR0+0x04)
//#define   IRQ_STICKY_CLR1  (IRQ_STICKY_CLR0+0x80) - WRONG, UNUSED

/* Level or edge interrupt control */
//#define   IRQ_LVL_EDG0    (volatile UINT32 *)(0xD4000E00)
#define   IRQ_LVL_EDG0    (volatile UINT32 *)(IRQCTRL_BASE_ADDR+XIRQ_EDGELEVEL_OFFSET)

//#define   IRQ_LVL_EDG1    (volatile UINT32 *)(0xD4000E04)
#define   IRQ_LVL_EDG1    (volatile UINT32 *)(IRQCTRL_BASE_ADDR+XIRQ_EDGELEVEL_OFFSET+0x04)
//#define   WR_IRQCTRL_REG(bASE, rEG, vALUE)    WR_REG16(bASE, rEG, vALUE)
/* AlexR :Register value is multiplied by 2 , becouse all offsets (rEG) defined for 16-bits registers*/
#endif
#else//pyin new add
/* Sticky bit clears*/
#define   IRQ_STICKY_CLR0  (IRQCTRL_BASE_ADDR+XIRQ_STICKY_OFFSET)
#define   IRQ_STICKY_CLR16 (IRQ_STICKY_CLR0+0x04)
//#define   IRQ_STICKY_CLR1  (IRQ_STICKY_CLR0+0x80) - WRONG, UNUSED

/* Level or edge interrupt control */
//#define   IRQ_LVL_EDG0    (volatile UINT32 *)(0xD4000E00)
#define   IRQ_LVL_EDG0    (volatile UINT32 *)(IRQCTRL_BASE_ADDR+XIRQ_EDGELEVEL_OFFSET)

//#define   IRQ_LVL_EDG1    (volatile UINT32 *)(0xD4000E04)
#define   IRQ_LVL_EDG1    (volatile UINT32 *)(IRQCTRL_BASE_ADDR+XIRQ_EDGELEVEL_OFFSET+0x04)
//#define   WR_IRQCTRL_REG(bASE, rEG, vALUE)    WR_REG16(bASE, rEG, vALUE)
/* AlexR :Register value is multiplied by 2 , becouse all offsets (rEG) defined for 16-bits registers*/

#endif
// Moved here from intc.h: definitely a non-API stuff
//#define AIRQ_EDGE_OR_LEVEL0  (0xD4000E00UL)
#define AIRQ_EDGE_OR_LEVEL0			  (UINT32)(IRQ_LVL_EDG0)
//#define AIRQ_EDGE_OR_LEVEL32 (0xD4000E04UL)
#define AIRQ_EDGE_OR_LEVEL32			  (UINT32)(IRQ_LVL_EDG1)

#if defined (EDEN_1928) || defined (NEZHA3_1826)
#define AIRQ_EDGE_OR_LEVEL64		  (UINT32)(IRQ_LVL_EDG2)
#endif

void INTCEnableInterruptOutput(void);
void INTCDisableInterruptOutput	(void);

#endif /* PLK_IRQCTRL_H */
