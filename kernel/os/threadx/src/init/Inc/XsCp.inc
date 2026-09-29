;------------------------------------------------------------
; (C) Copyright [2006-2008] Marvell International Ltd.
; All Rights Reserved
;------------------------------------------------------------

;----------------------------------------------------------------------
;   Copyright (C) 2000 Intel Corp.
;
;   Filename XsCp.inc
;
;   This file contains general Intel(R) Xscale(TM) Microarchitecture 
;       coprocessor constants
;
;
;    2000-11-30: 11:30 EST
;


;/////////////////////////////////////////////////////////////////////////
;
;   Constant definitions
;
;  Simple symbolic constants for some opcode_2 values in the MRC/MCR instructions

Op2_0       EQU 0
Op2_1       EQU 1
Op2_2       EQU 2
Op2_3       EQU 3
Op2_4       EQU 4
Op2_5       EQU 5
Op2_6       EQU 6


;  Simple symbolic constants for some CRm values in the MRC/MCR instructions

CP15CRm_0   CN  0
CP15CRm_1   CN  1

; Macros for reading/writing Performance Monitoring registers
	MACRO
	CP14_READ_PMNC $reg
		 MRC p14, 0, $reg, c0, c1, 0
	MEND

	MACRO
	CP14_READ_CCNT $reg
		MRC p14, 0, $reg, c1, c1, 0
	MEND

	MACRO
	CP14_READ_INTEN $reg
		MRC p14, 0, $reg, c4, c1, 0
	MEND

	MACRO
	CP14_READ_FLAG $reg
		MRC p14, 0, $reg, c5, c1, 0
	MEND

	MACRO
	CP14_READ_EVTSEL $reg
		MRC p14, 0, $reg, c8, c1, 0
	MEND

	MACRO
	CP14_READ_PMN0 $reg
		MRC p14, 0, $reg, c0, c2, 0
	MEND

	MACRO
	CP14_READ_PMN1 $reg
		MRC p14, 0, $reg, c1, c2, 0
	MEND

	MACRO
	CP14_READ_PMN2 $reg
		MRC p14, 0, $reg, c2, c2, 0
	MEND

	MACRO
	CP14_READ_PMN3 $reg
		MRC p14, 0, $reg, c3, c2, 0
	MEND

	MACRO
	CP14_SET_PMNC $reg
		 MCR p14, 0, $reg, c0, c1, 0
	MEND

	MACRO
	CP14_SET_CCNT $reg
		MCR p14, 0, $reg, c1, c1, 0
	MEND

	MACRO
	CP14_SET_INTEN $reg
		MCR p14, 0, Rd, c4, c1, 0
	MEND

	MACRO
	CP14_SET_FLAG $reg
		MCR p14, 0, $reg, c5, c1, 0
	MEND

	MACRO
	CP14_SET_EVTSEL $reg
		MCR p14, 0, $reg, c8, c1, 0
	MEND

	MACRO
	CP14_SET_PMN0 $reg
		MCR p14, 0, $reg, c0, c2, 0
	MEND

	MACRO
	CP14_SET_PMN1 $reg
		MCR p14, 0, $reg, c1, c2, 0
	MEND

	MACRO
	CP14_SET_PMN2 $reg
		MCR p14, 0, $reg, c2, c2, 0
	MEND

	MACRO
	CP14_SET_PMN3 $reg
		MCR p14, 0, $reg, c3, c2, 0
	MEND


    END