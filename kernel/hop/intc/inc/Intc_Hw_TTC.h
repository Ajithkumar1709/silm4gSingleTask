/*--------------------------------------------------------------------------------------------------------------------
(C) Copyright 2006, 2007 Marvell DSPC Ltd. All Rights Reserved.
-------------------------------------------------------------------------------------------------------------------*/

/************************************************************************/
/*                                                                      */
/* Title: Interrupt Controller Hardware header file                     */
/*         TTC silicon                                                  */
/* Filename: Intc_Hw_TTC.h                                              */
/*                                                                      */
/* Author: Anton                                                        */
/*                                                                      */
/* Target, subsystem: Common Platform, HAL                              */
/* 																		*/
/************************************************************************/
#ifndef _INTC_HW_TTC_H_
#define _INTC_HW_TTC_H_

#include "intc_config.h"

#define INTERRUPT_CONTROLLER_HW_ADDRESS     0xD4282000L

#define P_ICU_NUM_SOURCES                   64
#define P_ICU_NUM_SOURCES_HELANLTE          96

/*-----------------------------------------------------------------------**
** Following mapping depicts the Interrupt controller registers          **
** location with offset of hte basic address.                            **
**-----------------------------------------------------------------------*/
union InterruptHWRegisters
{
  struct
  {
    UINT32       ICU_CONF[P_ICU_NUM_SOURCES];  // Mask, configuration, priority for 64 sources
	UINT32       ICU_CP_FIQ_PENDING;           // CP FIQ selected pending interrupt
	UINT32       ICU_CP_IRQ_PENDING;           // CP IRQ selected pending interrupt
	UINT32       ICU_AP_FIQ_PENDING;           // AP FIQ selected pending interrupt
	UINT32       ICU_AP_IRQ_PENDING;           // AP IRQ selected pending interrupt
	UINT32       ICU_CP_GLOBAL_MASK;           // CP mask all interrupts (for IDLE entry, automatically cleared by PMU)
	UINT32       ICU_AP_GLOBAL_MASK;           // AP mask all interrupts (for IDLE entry, automatically cleared by PMU)
	UINT32       ICU_CP_DMA_INT_MASK;          // CP interrupt mask for 32 DMA channels
	UINT32       ICU_AP_DMA_INT_MASK;          // AP interrupt mask for 32 DMA channels
	UINT32       ICU_CP_DMA_INT_STATUS;        // CP interrupt status for 32 DMA channels
	UINT32       ICU_AP_DMA_INT_STATUS;        // AP interrupt status for 32 DMA channels
	UINT32       ICU_INT_STATUS_0;             // Interrupt status (after masking) for sources [31..0]
	UINT32       ICU_INT_STATUS_1;             // Interrupt status (after masking) for sources [63..32]
	UINT32       ICU_VPRO_INT_MASK;            // VPRO interrupt mask
	UINT32       ICU_VPRO_INT_STATUS;          // VPRO interrupt status
	UINT32       ICU_INT_STATUS_2;             // Interrupt status (after masking) for sources 
	UINT32       ICU_INT_STATUS_3;             // Interrupt status (after masking) for sources 
  	UINT32	     ICU_CONF_H[P_ICU_NUM_SOURCES];  // Mask, configuration, priority for 64-127 sources
  }all;
  struct
  {
#if defined(INTC_CORE_AP) ||defined(_TAVOR_BOERNE_) //PHS_SW_DEMO_TTC
    UINT32       reserved0[P_ICU_NUM_SOURCES];
	UINT32       reserved1[2];
	UINT32       ICU_FIQ_PENDING;              // FIQ selected pending interrupt
	UINT32       ICU_IRQ_PENDING;              // IRQ selected pending interrupt
	UINT32       reserved2;
	UINT32       ICU_GLOBAL_MASK;              // mask all interrupts (for IDLE entry, automatically cleared by PMU)
	UINT32       reserved3;
	UINT32       ICU_DMA_INT_MASK;             // interrupt mask for 32 DMA channels
	UINT32       reserved4;
	UINT32       ICU_DMA_INT_STATUS;           // interrupt status for 32 DMA channels
	UINT32       reserved5[4];
#endif
//#if defined(INTC_CORE_CP) || defined(_TAVOR_HARBELL_) || defined (SILICON_PV2) //PHS_SW_DEMO_TTC
#if defined(INTC_CORE_CP) || defined (SILICON_PV2) //PHS_SW_DEMO_TTC
    UINT32       reserved0[P_ICU_NUM_SOURCES];
	UINT32       ICU_FIQ_PENDING;              // FIQ selected pending interrupt
	UINT32       ICU_IRQ_PENDING;              // IRQ selected pending interrupt
	UINT32       reserved1[2];
	UINT32       ICU_GLOBAL_MASK;              // mask all interrupts (for IDLE entry, automatically cleared by PMU)
	UINT32       reserved2;
	UINT32       ICU_DMA_INT_MASK;             // interrupt mask for 32 DMA channels
	UINT32       reserved3;
	UINT32       ICU_DMA_INT_STATUS;           // interrupt status for 32 DMA channels
	UINT32       reserved4;
	UINT32       reserved5[4];
#endif
  } own;
};

union InterruptHWRegisters_HelanLTE
{
  struct
  {
    UINT32       ICU_CONF[P_ICU_NUM_SOURCES_HELANLTE];  // Mask, configuration, priority for 96 sources
    UINT32       ICU_RESERVED1[32];
    UINT32       ICU_INT_STATUS_0;             // Interrupt status (after masking) for sources [31..0]
    UINT32       ICU_INT_STATUS_1;             // Interrupt status (after masking) for sources [63..32]
    UINT32       ICU_INT_STATUS_2;             // Interrupt status (after masking) for sources [95..64]
    UINT32       ICU_RESERVED2;
    UINT32       ICU_CP_FIQ_PENDING;           // CP FIQ selected pending interrupt
    UINT32       ICU_CP_IRQ_PENDING;           // CP IRQ selected pending interrupt
    UINT32       ICU_CP_GLOBAL_MASK;           // CP mask all interrupts (for IDLE entry, automatically cleared by PMU)
    UINT32       ICU_RESERVED3;
    UINT32       ICU_AP_FIQ_PENDING;           // AP FIQ selected pending interrupt
    UINT32       ICU_AP_IRQ_PENDING;           // AP IRQ selected pending interrupt
    UINT32       ICU_AP_GLOBAL_MASK;           // AP mask all interrupts (for IDLE entry, automatically cleared by PMU)
    UINT32       ICU_RESERVED4;
    UINT32       ICU_AP2_FIQ_PENDING;           // AP FIQ selected pending interrupt
    UINT32       ICU_AP2_IRQ_PENDING;           // AP IRQ selected pending interrupt
    UINT32       ICU_AP2_GLOBAL_MASK;           // AP mask all interrupts (for IDLE entry, automatically cleared by PMU)
    UINT32       ICU_RESERVED5;
    UINT32       ICU_AP3_FIQ_PENDING;           // AP FIQ selected pending interrupt
    UINT32       ICU_AP3_IRQ_PENDING;           // AP IRQ selected pending interrupt
    UINT32       ICU_AP3_GLOBAL_MASK;           // AP mask all interrupts (for IDLE entry, automatically cleared by PMU)
    UINT32       ICU_RESERVED6;
    UINT32       ICU_AP4_FIQ_PENDING;           // AP FIQ selected pending interrupt
    UINT32       ICU_AP4_IRQ_PENDING;           // AP IRQ selected pending interrupt
    UINT32       ICU_AP4_GLOBAL_MASK;           // AP mask all interrupts (for IDLE entry, automatically cleared by PMU)
    UINT32       ICU_RESERVED7[41];
    UINT32       ICU_ARM_INT_STATUS;
    UINT32       ICU_ARM_INT_MSK;
    UINT32       ICU_RESERVED8[2];
    UINT32       ICU_CP_DMA_INT_STATUS;        // CP interrupt status for 32 DMA channels
    UINT32       ICU_CP_DMA_INT_MASK;          // CP interrupt mask for 32 DMA channels
    UINT32       ICU_RESERVED9[2];
    UINT32       ICU_AP_DMA_INT_STATUS;        // AP interrupt status for 32 DMA channels
    UINT32       ICU_AP_DMA_INT_MASK;          // AP interrupt mask for 32 DMA channels
    UINT32       ICU_SECURE_AP_DMA_INT_STATUS;        // AP interrupt status for 32 DMA channels
    UINT32       ICU_SECURE_AP_DMA_INT_MASK;          // AP interrupt mask for 32 DMA channels
    UINT32       ICU_AP2_DMA_INT_STATUS;        // AP interrupt status for 32 DMA channels
    UINT32       ICU_AP2_DMA_INT_MASK;          // AP interrupt mask for 32 DMA channels
    UINT32       ICU_SECURE_AP2_DMA_INT_STATUS;        // AP interrupt status for 32 DMA channels
    UINT32       ICU_SECURE_AP2_DMA_INT_MASK;          // AP interrupt mask for 32 DMA channels
    UINT32       ICU_AP3_DMA_INT_STATUS;        // AP interrupt status for 32 DMA channels
    UINT32       ICU_AP3_DMA_INT_MASK;          // AP interrupt mask for 32 DMA channels
    UINT32       ICU_SECURE_AP3_DMA_INT_STATUS;        // AP interrupt status for 32 DMA channels
    UINT32       ICU_SECURE_AP3_DMA_INT_MASK;          // AP interrupt mask for 32 DMA channels
    UINT32       ICU_AP4_DMA_INT_STATUS;        // AP interrupt status for 32 DMA channels
    UINT32       ICU_AP4_DMA_INT_MASK;          // AP interrupt mask for 32 DMA channels
    UINT32       ICU_SECURE_AP4_DMA_INT_STATUS;        // AP interrupt status for 32 DMA channels
    UINT32       ICU_SECURE_AP4_DMA_INT_MASK;          // AP interrupt mask for 32 DMA channels
  }all;
  struct
  {
#if defined(INTC_CORE_AP) ||defined(_TAVOR_BOERNE_) //PHS_SW_DEMO_TTC
    UINT32       reserved0[P_ICU_NUM_SOURCES_HELANLTE];
    UINT32       reserved1[2];
    UINT32       ICU_FIQ_PENDING;              // FIQ selected pending interrupt
    UINT32       ICU_IRQ_PENDING;              // IRQ selected pending interrupt
    UINT32       reserved2;
    UINT32       ICU_GLOBAL_MASK;              // mask all interrupts (for IDLE entry, automatically cleared by PMU)
    UINT32       reserved3;
    UINT32       ICU_DMA_INT_MASK;             // interrupt mask for 32 DMA channels
    UINT32       reserved4;
    UINT32       ICU_DMA_INT_STATUS;           // interrupt status for 32 DMA channels
    UINT32       reserved5[4];
#endif
//#if defined(INTC_CORE_CP) || defined(_TAVOR_HARBELL_) || defined (SILICON_PV2) //PHS_SW_DEMO_TTC
#if defined(INTC_CORE_CP) || defined (SILICON_PV2) //PHS_SW_DEMO_TTC
    UINT32       reserved0[P_ICU_NUM_SOURCES_HELANLTE];
    UINT32       reserved1[36];
    UINT32       ICU_FIQ_PENDING;              // FIQ selected pending interrupt
    UINT32       ICU_IRQ_PENDING;              // IRQ selected pending interrupt
    UINT32       ICU_GLOBAL_MASK;              // mask all interrupts (for IDLE entry, automatically cleared by PMU)
    UINT32       reserved2[61];
    UINT32       ICU_DMA_INT_STATUS;           // interrupt status for 32 DMA channels
    UINT32       ICU_DMA_INT_MASK;             // interrupt mask for 32 DMA channels
    UINT32       reserved3[18];
#endif
  } own;
};


/*
 * NOTES:
 * - ICU_INT_STATUS_n registers indicate interrupt status for interrupts routed to all cores (AP and CP)
 *   Therefore these cannot be used to determine if specific core has an interrupt pending.
*/

// ICU_CONF registers structure
#define ICU_CONF_PRIO_BITS                 0x0F
#define ICU_CONF_PRIO_MASKED               0x0
#define ICU_CONF_TYPE_BITS                 0x10
#define ICU_CONF_TYPE_FIQ                  0x00
#define ICU_CONF_TYPE_IRQ                  0x10

#define ICU_CONF_CP_INT                    0x20
#define ICU_CONF_AP_INT                    0x40
#define ICU_CONF_OWNER_BITS                (ICU_CONF_CP_INT|ICU_CONF_AP_INT)
#if defined(INTC_CORE_AP) ||defined(_TAVOR_BOERNE_) //PHS_SW_DEMO_TTC
#define ICU_CONF_THIS_CORE_INT             ICU_CONF_AP_INT
#endif
//#if defined(INTC_CORE_CP) || defined(_TAVOR_HARBELL_) || defined (SILICON_PV2) //PHS_SW_DEMO_TTC
#if defined(INTC_CORE_CP) || defined (SILICON_PV2) //PHS_SW_DEMO_TTC
#define ICU_CONF_THIS_CORE_INT             ICU_CONF_CP_INT
#endif
#define ICU_CONF_OTHER_CORE_INT            (ICU_CONF_THIS_CORE_INT^ICU_CONF_OWNER_BITS)

// all _PENDING  registers structure
#define ICU_PENDING_INT_NUM_BITS           0x7F
#define ICU_PENDING_INT_VALID_BITS         0x80

#define ICU_PENDING_INT_NUM_BITS_CRANE           0x7F
#define ICU_PENDING_INT_VALID_BITS_CRANE         0x80


#define ICU_PENDING_INT_NUM_BITS_HELANLTE     0x7F
#define ICU_PENDING_INT_VALID_BITS_HELANLTE   0x80

// ICU_CP_GLOBAL_MASK/ICU_AP_GLOBAL_MASK registers structure
#define ICU_GLOBAL_MASK_FIQ                1
#define ICU_GLOBAL_MASK_IRQ                2
#define ICU_GLOBAL_MASK_ALL                (ICU_GLOBAL_MASK_FIQ|ICU_GLOBAL_MASK_IRQ)

// ICU_VPRO_INT_MASK/ICU_VPRO_INT_STATUS registers structure
#define ICU_VPRO_DMA_BITS                  0x7             // bits [2..0]
#define ICU_VPRO_SEM_BITS                  0x38            // bits [5..3]


#define     InterruptController    (* (volatile union InterruptHWRegisters *) INTERRUPT_CONTROLLER_HW_ADDRESS)
#define     InterruptController_HelanLTE    (* (volatile union InterruptHWRegisters_HelanLTE *) INTERRUPT_CONTROLLER_HW_ADDRESS)

//Macro to check whether there is an interrupt pending for service
//#define INTC_CHECK_INTERRUPT_PENDING    \
//   ((InterruptController.own.ICU_FIQ_PENDING&ICU_PENDING_INT_VALID_BITS) | (InterruptController.own.ICU_IRQ_PENDING&ICU_PENDING_INT_VALID_BITS))

#define ICU_INT_OWNED_BY_CORE_CONF(conf) \
   (((conf)&ICU_CONF_OWNER_BITS)==ICU_CONF_THIS_CORE_INT)

#define ICU_INT_OWNED_BY_OTHER_CORE_CONF(conf) \
   (((conf)&ICU_CONF_OWNER_BITS)==ICU_CONF_OTHER_CORE_INT)

#define ICU_INT_OWNED_BY_CORE(i) ICU_INT_OWNED_BY_CORE_CONF(InterruptController.all.ICU_CONF[i])
#define ICU_INT_OWNED_BY_CORE_HELANLTE(i) ICU_INT_OWNED_BY_CORE_CONF(InterruptController_HelanLTE.all.ICU_CONF[i])

//#define ICU_INT_OWNED_BY_OTHER_CORE(i) ICU_INT_OWNED_BY_OTHER_CORE_CONF(InterruptController.all.ICU_CONF[i])
#define ICU_INT_OWNED_BY_OTHER_CORE(i) 0

#define ICU_MASK_INT(i) {(InterruptController.all.ICU_CONF[i] &= ~ICU_CONF_PRIO_BITS);(InterruptController.all.ICU_CONF_H[i] &= ~ICU_CONF_PRIO_BITS);}
#define ICU_MASK_INT_HELANLTE(i) (InterruptController_HelanLTE.all.ICU_CONF[i] &= ~ICU_CONF_PRIO_BITS)

#endif /* _INTC_HW_H_ */


