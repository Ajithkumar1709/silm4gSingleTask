;------------------------------------------------------------
; (C) Copyright [2006-2008] Marvell International Ltd.
; All Rights Reserved
;------------------------------------------------------------

;;; Copyright ARM Ltd 2001. All rights reserved.

        AREA DLM_SECTION, CODE, READONLY

			 	INCLUDE dlm_jmptable.s      ;constants used in low-level initialization.

       ; EXPORT dlm_dummy
	EXPORT	 asm_dlm_dummy
asm_dlm_dummy
	MOV R0, #0x55
	MOV PC,LR


  ;dlm_dummy   SPACE   1

        END

