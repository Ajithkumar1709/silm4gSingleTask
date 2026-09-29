/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

#ifndef _IRQ_DEF_H
#define _IRQ_DEF_H
#include "global_types.h"
#include "intc_list.h"

typedef struct
{
	UINT32	InterruptNumber;	/* Absolute interrupt number */
	UINT32	InterruptPriority;
} INTC_emulation_priority_table_S;


#define IRQ_VECT_SIZE   (MAX_NUM_IRQ + NUM_OF_VIRTUAL_INT)

typedef struct INTC_HW_REGS_ST
{
	UINT32 IC_SWI_ENABLE_REG	;   /*0x00UL*/
	UINT32 IC_RI_ENABLE_REG		;   /*0x04UL*/
	UINT32 IC_XSWI_ENABLE_REG	;   /*0x08UL*/
	UINT32 IC_EIRQ_ENABLE_REG	;   /*0x0CUL*/
	UINT32 Reserved_1	[4]		;   /*0x10 0x14 0x18 0x1c*/
	UINT32 IC_HWI_ENABLE_REG_arr[4]	;   /*0x20 0x24 0x28 0x2c*/
	UINT32 Reserved_2   [4]		;   /* 0x30 0x34 0x38 0x3c */
	UINT32 IC_SWI_CLR_ENABLE_REG	; /*0x40UL*/
	UINT32 IC_RI_CLR_ENABLE_REG	; /*0x44UL*/
	UINT32 IC_EIRQ_CLR_ENABLE_REG	; /*0x48UL*/
	UINT32 Reserved_3   [5]		;   /*0x4c 0x50 0x54 0x58 0x5c */
	UINT32 IC_HWI_CLR_ENABLE_REG_arr[4]	; /*0x60 0x64 0x68 0x6C*/

}INTC_HW_CONF_REGS_Y;


#endif /* _IRQ_DEF_H */
