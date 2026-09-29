;------------------------------------------------------------
; (C) Copyright [2006-2008] Marvell International Ltd.
; All Rights Reserved
;------------------------------------------------------------

;/*************************************************************************/
;/*                                                                       */
;/*            Copyright (c) 1994 -2001 Accelerated Technology, Inc.      */
;/*                                                                       */
;/* PROPRIETARY RIGHTS of Accelerated Technology are involved in the      */
;/* subject matter of this material.  All manufacturing, reproduction,    */
;/* use, and sales rights pertaining to this subject matter are governed  */
;/* by the license agreement.  The recipient of this software implicitly  */
;/* accepts the terms of the license.                                     */
;/*                                                                       */
;/*************************************************************************/
;
;/*************************************************************************/
;/*                                                                       */
;/* FILE NAME                                            VERSION          */
;/*                                                                       */
;/*      int_defs.inc                        PLUS/XSCALE IQ80310/1.13.1   */
;/*                                                                       */
;/* COMPONENT                                                             */
;/*                                                                       */
;/*      IN - Initialization                                              */
;/*                                                                       */
;/* DESCRIPTION                                                           */
;/*                                                                       */
;/*      This file contains the target processor dependent initialization */
;/*      values used in tct.s, and tmt.s                                  */
;/*                                                                       */
;/*                                                                       */
;/* DATA STRUCTURES                                                       */
;/*                                                                       */
;/*      NONE                                                             */
;/*                                                                       */
;/* FUNCTIONS                                                             */
;/*                                                                       */
;/*      NONE                                                             */
;/*                                                                       */
;/* DEPENDENCIES                                                          */
;/*                                                                       */
;/*      NONE                                                             */
;/*                                                                       */
;/* HISTORY                                                               */
;/*                                                                       */
;/* NAME                    DATE       REMARKS                            */
;/*                                                                       */
;/* B. Whatley              02-08-2001 Created the initial version 1.13.1 */
;/*                                    Fixed spr 1070                     */
;/* L. Rosenblat, INTEL     06-24-2001 Modified.                          */
;/*                                    Removed unrelated data.            */
;/*************************************************************************/
;/* Define constants used in low-level initialization.  */
;
;

LOCKOUT             EQU     &C0             ; Interrupt lockout value
LOCK_MSK            EQU     &C0             ; Interrupt lockout mask value
MODE_MASK           EQU     &1F             ; Processor Mode Mask
SUP_MODE            EQU     &13             ; Supervisor Mode (SVC)
IRQ_MODE            EQU     &12             ; Interrupt Mode (IRQ)
FIQ_MODE            EQU     &11             ; Fast Interrupt Mode (FIQ)
ABORT_MODE          EQU     &17             ; Exception Mode (ABORT)     ; -- Irit 14.3.2002
UNDEFINED_MODE      EQU     &1B             ; Exception Mode (UNDEFINED) ; -- Irit 14.3.2002
STACK_ALIGNMENT     EQU       8             ; Current Stack Alignment in BYTEs (8 required by RVCT compiler)
I_BIT               EQU     &80             ; IRQ Interrupt bit of CPSR and SPSR
F_BIT               EQU     &40             ; FIQ Interrupt bit of CPSR and SPSR
T_BIT               EQU     &20             ; Thumb mode indication in CPSR and SPSR

SYSTEM_MODE         EQU     &1F             ; System Mode (SYSTEM) ; Eitan 25.01.2004
USER_MODE           EQU     &10             ; User Mode (USER) ; Eitan 25.01.2004

  IF :DEF: _TAVOR_HARBELL_
PSR_IR              EQU     0xc0		; the I and R bits in PSR,used to dis/enable IRQ/FIQ
;***********************************
;* MACROS                          *
;***********************************

    ; This macro is used to unnest interrupts.  It switches to the correct
    ; interrupt mode (FIQ/IRQ), removes the interrupt controller mask registers
    ; off the interrupt stack, restores the interrupt controller mask values,
    ; and returns back to the mode it was in before invoking the macro.

    MACRO
    UNNEST_INTERRUPT    $INT_MODE

    ; Switch to correct mode

    MRS     r0,CPSR                         ; Pickup current CPSR
    ORR     r0,r0,#LOCKOUT                  ; Lock-out interrupts
    BIC     r1,r0,#MODE_MASK                ; Clear the mode bits (preserve
                                            ; current mode in r0)
    ORR     r1,r1,#$INT_MODE                ; Set the new mode bits
    MSR     CPSR_cxsf,r1                    ; Switch to correct mode

    ; ************ START TARGET SPECIFIC SECTION **************

    ; Get interrupt masks from stack

   ; LDMIA   sp!,{r1,r2}                     ; Get mask value and base
                                            ; address of IRQ / FIQ registers

   ; STR     r1,[r2,#INT_ENABLE_OFFSET]      ; Re-enable all lower priority
                                            ; interrupts

    ; ************ END TARGET SPECIFIC SECTION **************

    ; Return back to correct original mode with interrupts locked-out

    MSR     CPSR_cxsf,r0

    MEND    ; UNNEST_INTERRUPT

  ENDIF ;_TAVOR_HARBELL_

    END
