;------------------------------------------------------------
; (C) Copyright [2006-2008] Marvell International Ltd.
; All Rights Reserved
;------------------------------------------------------------

;----------------------------------------------------------------------
;   Copyright (C) 2000 Intel Corp.
;
;   Filename XsCp15.inc
;
;   This file contains Intel(R) Xscale(TM) Microarchitecture
;       Coprocessor 15 constants and macros.
;
;   Requires XsCP.inc
;
;    2000-12-11: 14:30 EST
;
;

;/////////////////////////////////////////////////////////////////////////
;
;   List of macros in alphabetical order
;
;   Note:   EnableMMU is not implemented as a macro, but only as a subroutine.
;           Other utilities are implemented only as subroutines, so as to avoid
;               the complexity of dealing with internal labels.
;           For these subroutines, see XsCp15.s
;
;   AllocateDCacheLineM
;   CleanDCacheFastM
;   CleanDCacheSlowM
;   CleanDCacheLineM
;   CPWAIT
;   CreateDataRAMM
;   DisableDCacheM
;   DisableDCacheLockModeM
;   DrainBuffersM
;   EnableDCacheLockModeM
;   EnableDCacheM
;   FetchAndLockICacheLineM
;   GetARMControlM
;   GetAuxControlM
;   GetCacheTypeM
;   GetCoprocessorAccessM
;   GetDomainAccessControlM
;   GetFaultAddressM
;   GetFaultStatusM
;   GetProcessIDM
;   GetProcVersionM
;   GetTransTableBaseM
;   InvalidateBTBM
;   InvalidateDCacheLineM
;   InvalidateDCacheM
;   InvalidateDTLBEntryM
;   InvalidateDTLBM
;   InvalidateIandDTLBsM
;   InvalidateICacheAndBTBM
;   InvalidateICacheLineM
;   InvalidateITLBEntryM
;   InvalidateITLBM
;   InvalidIAndDCachesAndBTBM
;   SetARMControlM
;   SetAuxControlM
;   SetCoprocessorAccessM
;   SetDomainAccessControlM
;   SetProcessIDM
;   SetTransTableBaseM
;   TransAndLockDTLB_EntryM
;   TransAndLockITLB_EntryM
;   UnlockDataCacheM
;   UnlockDataTLBM
;   UnlockInstructionCacheM
;   UnlockInstructionTLBM
;




  IF :DEF: L2_CACHE_ENABLE
	IF :LNOT: :DEF: _TAVOR_BOERNE_
	  WrongFlagCombination___L2_CACHE_ENABLE__supported_for_BOERNE_only
    ENDIF
  ENDIF



;/////////////////////////////////////////////////////////////////////////
;
;   Symbol definitions for Coprocessor 15 and Coprocessor 15 Registers
;
;   Note: Multiple symbols for the same register may occur.  The names are
;         defined for usage in the MRC/MCR commands that access various
;         Coprocessor 15 functions.
;

CP15    CP  15 ; Alias for Coprocessor 15 (rather than just "p15")

;
;  CP15, Reg 0
;

CP15IDReg                   CN  0

Op2ProcID                   EQU 0
Op2CacheType                EQU 1

;
;  CP15, Reg 1
;

CP15ArmControlReg           CN  1
; Some bit masks for ARM Control Register
CP15MMUEnable               EQU 1
CP15AlignmentFaultEnable    EQU 1:SHL:1
CP15DCacheEnable            EQU 1:SHL:2
CP15BigEndianEnable         EQU 1:SHL:7
CP15SystemProtection        EQU 1:SHL:8
CP15RomProtection           EQU 1:SHL:9
CP15SRMask                  EQU 3:SHL:8
CP15BranchTgtBufEnable      EQU 1:SHL:11
CP15ICacheEnable            EQU 1:SHL:12
CP15RelocateVectorTable     EQU 1:SHL:13



CP15AuxControlReg           CN  1

;
;  CP15, Reg 2
;

CP15TransTableBaseReg       CN  2

;
;  CP15, Reg 3
;

CP15DomainAccessControlReg  CN  3

;
;  CP15, Reg 5
;

CP15_FaultStatusReg         CN  5

;
;  CP15, Reg 6
;

CP15FaultAddressReg         CN  6

;
;  CP15, Reg 7
;

CP15CacheOpsReg             CN  7

CP15AllocateDCacheLineCRm   CN  2
CP15InvalidICacheCRm        CN  5
CP15InvalidDCacheCRm        CN  6
CP15InvalidIAndDCacheCRm    CN  7
CP15CleanDCacheCRm          CN  10
CP15DrainCacheCRm           CN  10

    IF :DEF: L2_CACHE_ENABLE     ;for _TAVOR_BOERNE_ only
CP15PrefetchFlushCRm                    CN  5
CP15InvalidL2CacheCRm                   CN  7
CP15CleanL2CacheLineCRm                 CN  11
CP15CleanAndInvalidateDCacheLineCRm     CN  14
CP15AllocateandLockCRm                  CN  5
   ENDIF    ; L2_CACHE_ENABLE

;
;  CP15, Reg 8
;

CP15InvalidateTLBReg        CN  8

CP15InvalidateITLBCRm       CN  5
CP15InvalidateDTLBCRm       CN  6
CP15InvalidateIandDTLBsCRm  CN  7

Op2InvalidateEntireTLB      EQU 0
Op2InvalidateTLBEntry       EQU 1

;
;  CP15, Reg 9
;

CP15LockCacheReg            CN  9
    IF :DEF: L2_CACHE_ENABLE     ;for _TAVOR_BOERNE_ only
CP15LockICacheCRm           CN  5
CP15LockDCacheCRm           CN  6
    ELSE
CP15LockICacheCRm           CN  1
CP15LockDCacheCRm           CN  2
    ENDIF

  ;; Two next are _TAVOR_BOERNE_ specific.
  ;; Using would be reconsiderd onto CP15LockICacheCRm, CP15LockDCacheCRm
  ;; for code unification purpose 
CP15Lock_ICacheCRm          CN  5
CP15Lock_DCacheCRm          CN  6

Op2LockCache                EQU 0
Op2UnlockCache              EQU 1

;
;  CP15, Reg 10
;

CP15LockTLBReg              CN  10

CP15LockITLBCRm             CN  4
CP15LockDTLBCRm             CN  8

Op2LockTLB                  EQU 0
Op2UnlockTLB                EQU 1

;
;  CP15, Reg 13
;

CP15ProcessIDReg            CN  13

;
;  CP15, Reg 15
;

CP15CoprocessorAccessReg    CN  15

CP15CoprocessorAccessCRm    CN  1

    IF :DEF: L2_CACHE_ENABLE     ;for _TAVOR_BOERNE_ only
CP15_CTRL_31_24_bits    EQU     0xFB000000  ; L2 cache bit
CP15_AUXCTRL_15_8_bits  EQU     0x0000F300  ; OC attribute
CP15_AUXCTRL_7_0_bits   EQU     0x00000030  ; IC attribute
    ELSE
CP15_CTRL_31_24_bits    EQU     0xFF000000  ; no L2 cache
CP15_AUXCTRL_15_8_bits  EQU     0x00FF0000
CP15_AUXCTRL_7_0_bits   EQU     0x000000CC
    ENDIF

;/////////////////////////////////////////////////////////////////////////
;
;   General Macro Definitions for CP 15 Register Access
;
;   - The M terminator is used for all macros.
;   - When using the macros, the "$xxxReg" macro parameter must be in
;       {R0..R10} and should normally be R0 or R1.
;

;=========================================================================
; CPWAIT
;
;   Standard macro to let CP15 commands complete before moving to
;   next operation.  Taken from Intel XScale Core user's manual.
;
;   Input:         None
;   Return:        None
;   Side Effects:  R0 undefined
;
;
;;  The following macro should be used when software needs to be
;;  assured that a CP15 update has taken effect.
;;  It may only be used while in a privileged mode, because it
;;  accesses CP15.

    MACRO
        CPWAIT
        MRC CP15, 0, R0, c2, c0, 0 ; arbitrary read of CP15
        MOV R0, R0 ; wait for it
        ADR PC,{PC}+4 ; branch to next instruction; legacy form was SUB PC,PC,#4 - modified to avoid ARM RVCT warning A1789W 
        ; At this point, any previous CP15 writes are
        ; guaranteed to have taken effect.
    MEND


;=========================================================================
; ID & Cache Type
;
;   CP15, CR0, opcod_2=0,1
;
;   Read-only
;

;----------------------------
; GetProcVersionM
;
;   Get processor version info
;
;   Input:   None
;   Return:  $retReg:  ID Register contents
;
;   Note: For first silicon of Cotulla, should be 0x69052000
;
;   CP 15, reg 0, opcode_2=0
;
;   Nonsymbolic core instructions:
;       MRC p15, 0, Rd, 0, 0, 0

    MACRO
        GetProcVersionM $retReg
        MRC     CP15,0,$retReg,CP15IDReg,CP15IDReg,Op2ProcID
    MEND

;----------------------------
; GetCacheTypeM
;
;   Get cache type info
;
;   Input:   None
;   Return:  $retReg:  ID Register contents
;
;   CP 15, reg 0, opcode_2=1
;   Nonsymbolic core instructions:
;       MRC p15, 0, Rd, 0, 0, 1

    MACRO
        GetCacheTypeM  $retReg
        MRC     CP15,0,$retReg,CP15IDReg,CP15IDReg,Op2CacheType
    MEND

;=========================================================================
; Control & Auxiliary Control
;
;   CP15, CR1, opcod_2=0,1
;
;   Read/Write
;


;----------------------------
; GetARMControlM
;
;   Get the value in the ARM Control Register.
;
;   Input:   None
;   Return:  $retReg:  ARM Control Register contents
;
;   CP 15, reg 1, opcode_2=0
;   Nonsymbolic core instructions:
;       MRC p15, 0, Rd, 1, 0, 0

    MACRO
        GetARMControlM   $retReg
        MRC     CP15,0,$retReg,CP15ArmControlReg,CP15CRm_0,Op2_0
        ; Zero reserved bits
        BIC     $retReg,$retReg,#0xff000000
        BIC     $retReg,$retReg,#0x00ff0000
        BIC     $retReg,$retReg,#0x0000c400
    MEND


;----------------------------
; SetARMControlM
;
;   Set the value of the ARM Control Register.
;
;   Input:   $setReg:  New ARM Control Register contents
;   Return:  None
;
;   CP 15, reg 1, opcode_2=0
;   Nonsymbolic core instructions:
;       MCR p15, 0, Rd, 1, 0, 0

    MACRO
        SetARMControlM $setReg
        ; Zero reserved bits
        BIC     $setReg,$setReg,#0xff000000
        BIC     $setReg,$setReg,#0x00ff0000
        BIC     $setReg,$setReg,#0x0000c400
        ; Force write-as-one bits
    IF  :LNOT: :DEF: _TAVOR_HARBELL_
        ORR     $setReg,$setReg, #0x00000078
    ELSE
        ORR     $setReg,$setReg, #0x0000004C  ; don't force alignment fault enb.
    ENDIF
        MCR     CP15,0,$setReg,CP15ArmControlReg,CP15CRm_0,Op2_0
    MEND


;----------------------------
; GetAuxControlM
;
;   Get the value in the Auxiliary Control Register.
;
;   Input:   None
;   Return:  $retReg:  Auxiliary Control Register contents
;
;   CP 15, reg 1, opcode_2=1
;   Nonsymbolic core instructions:
;       MRC p15, 0, Rd, 1, 0, 1

    MACRO
        GetAuxControlM  $retReg
        MRC     CP15,0,$retReg,CP15AuxControlReg,CP15AuxControlReg,Op2_1
        ; Zero reserved bits
        BIC     $retReg,$retReg,#0xff000000
        BIC     $retReg,$retReg,#0x00ff0000
        BIC     $retReg,$retReg,#0x0000ff00
        BIC     $retReg,$retReg,#0x000000cc
    MEND


;----------------------------
; SetAuxControlM
;
;   Set the value in the Auxiliary Control Register.
;
;   Input:   $setReg:  New Auxiliary Control Register contents
;   Return:  None
;
;   CP 15, reg 1, opcode_2=1
;   Nonsymbolic core instructions:
;       MCR p15, 0, Rd, 1, 0, 1

    MACRO
        SetAuxControlM $setReg
        ; Zero reserved bits
        BIC     $setReg,$setReg,#0xff000000
        BIC     $setReg,$setReg,#0x00ff0000
        BIC     $setReg,$setReg,#0x0000ff00
        BIC     $setReg,$setReg,#0x000000cc
        MCR     CP15,0,$setReg,CP15AuxControlReg,CP15CRm_0,Op2_1
    MEND


;=========================================================================
; Translation Table Base   CP15, CR2
;
;   Note: This is an MMU-related register
;
;   Read/Write
;

;----------------------------
; GetTransTableBaseM
;
;   Get physical address of the base of the first-level translation
;       table as known to the MMU. Sometimes called "page table"
;
;   Input:   None
;   Return:  $retReg:  Translation Table Base Register contents
;
;   CP 15, reg 2
;   Nonsymbolic core instructions:
;   MRC p15, 0, Rd, 2, 0, 0

    MACRO
        GetTransTableBaseM   $retReg
        MRC     CP15,0,$retReg,CP15TransTableBaseReg,CP15CRm_0,Op2_0
        ; Zero undefined bits
        BIC     $retReg,$retReg,#0x00003f00
        BIC     $retReg,$retReg,#0x000000ff
    MEND


;----------------------------
; SetTransTableBaseM
;
;   Put physical address of the base of the first-level translation
;       table into the Translation Table Base Register so that the
;       MMU sees it.  Sometimes called "page table" base.
;
;   Input:   $setReg:  Translation Table base physical address
;   Return:  None
;
;   CP 15, reg 2
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, 2, 0, 0

    MACRO
        SetTransTableBaseM   $setReg
        MCR     CP15,0,$setReg,CP15TransTableBaseReg,CP15CRm_0,Op2_0
        ; Don't zero undefined bits.  If the table is not on a 16K
        ; boundary, the system won't work anyway.
        CPWAIT  ; Wait for it to happen!
    MEND


;=========================================================================
; Domain Access Control   CP15, CR3
;
;   Note: This is an MMU-related register
;
;   Read/Write
;


;----------------------------
; GetDomainAccessControlM
;
;   Get value of the Domain Access Control Register.
;
;   Input:   None
;   Return:  $retReg: Domain Access Control Register contents
;
;   CP 15, reg 3
;   Nonsymbolic core instruction:
;       MRC p15, 0, Rd, 3, 0, ss0

    MACRO
        GetDomainAccessControlM    $retReg
        MRC     CP15,0,$retReg,CP15DomainAccessControlReg,CP15CRm_0,Op2_0
    MEND


;----------------------------
; SetDomainAccessControlM
;
;   Set value of the Domain Access Control Register.
;
;   Input:   $setReg: New Domain Access Control Register contents
;   Return:  None
;
;   Note: No protection against placing the 0b10 Reserved value in
;           any of the individual domain access control fields.
;
;   CP 15, reg 3
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, 3, 0, 0

    MACRO
        SetDomainAccessControlM    $setReg
        MCR     CP15,0,$setReg,CP15DomainAccessControlReg,CP15CRm_0,Op2_0
    MEND



;=========================================================================
;
; Note: CP15 CR4 is reserved.
;


;=========================================================================
; Fault Status and Address   CP15, CR5 and CR6.
;
;   - Read only.
;

;----------------------------
; GetFaultStatusM
;
;   Get value of the Fault Status Register.
;
;   Input:   None
;   Return:  R0: Fault Status Register contents
;
;   CP 15, reg 5
;   Nonsymbolic core instruction:
;       MRC p15, 0, Rd, 5, 0, 0

    MACRO
        GetFaultStatusM   $retReg
        MRC     CP15,0,$retReg,CP15_FaultStatusReg,CP15CRm_0,Op2_0
        ; Zero undefined bits
        BIC     $retReg,$retReg,#0xff000000
        BIC     $retReg,$retReg,#0x00ff0000
        BIC     $retReg,$retReg,#0x0000f900
    MEND


;----------------------------
; GetFaultAddressM
;
;   Get value of the Fault Address Register.
;
;   Input:   None
;   Return:  R0: Fault Address Register contents
;
;   CP 15, reg 6
;   Nonsymbolic core instruction:
;       MRC p15, 0, Rd, 6, 0, 0

    MACRO
        GetFaultAddressM   $retReg
        MRC     CP15,0,$retReg,CP15FaultAddressReg,CP15CRm_0,Op2_0
    MEND


;=========================================================================
;  Cache operations.   CP15, CR7.
;
;   Write-only.
;
;   Notes: This is an MMU-related register
;          Be familiar with warnings, assumptions and usage examples in the
;            Intel XScale Core user's manual and the specific processor's
;            user's manual.  Especially be aware of the ABSENCE of side
;            effects.  For example,
;             - Invalidating a cache or cache line does not unlock it.
;             - Invalidating a single instruction cache line does not
;               automatically invalidate the Branch Target Buffer, which
;               must be done separately.
;             - Invalidating the caches and Branch Target Buffer does not
;               invalidate the Translation Lookaside Buffer
;
;
;   MVA = Modified Virtual Address (VA after possible ORing in of PID reg)
;
;   Function                     opcode_2  CRm    Data        Instruction
;
;   Invalidate I&D cache & BTB      0b000 0b0111 Ignored MCR p15, 0, Rd, c7, c7,  0
;   Invalidate I cache & BTB        0b000 0b0101 Ignored MCR p15, 0, Rd, c7, c5,  0
;   Invalidate I cache line         0b001 0b0101 MVA     MCR p15, 0, Rd, c7, c5,  1
;   Invalidate D cache              0b000 0b0110 Ignored MCR p15, 0, Rd, c7, c6,  0
;   Invalidate D cache line         0b001 0b0110 MVA     MCR p15, 0, Rd, c7, c6,  1
;   Clean D cache line              0b001 0b1010 MVA     MCR p15, 0, Rd, c7, c10, 1
;   Drain Write (& Fill) Buffer     0b100 0b1010 Ignored MCR p15, 0, Rd, c7, c10, 4
;   Invalidate Branch Target Buffer 0b110 0b0101 Ignored MCR p15, 0, Rd, c7, c5,  6
;   Allocate Line in the Data Cache 0b101 0b0010 MVA     MCR p15, 0, Rd, c7, c2,  5


;----------------------------
; InvalidIAndDCachesAndBTBM
;
;   Invalidate both the Instruction and Data caches,
;       plus the Branch Target Buffer.
;   - Individual cache lines can be invalidated using other commands.
;
;   Input:        None
;   Return:       None
;
;   CP 15, CR7, opcode_2=0, CRm7
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c7, c7, 0

    MACRO
        InvalidIAndDCachesAndBTBM    $anyReg
        MCR     CP15,0,$anyReg,CP15CacheOpsReg,CP15InvalidIAndDCacheCRm,Op2_0
    MEND


;----------------------------
; InvalidateICacheAndBTBM
;
;   Invalidate the Instruction cache, plus the Branch Target Buffer.
;   - Individual cache lines can be invalidated using other commands.
;
;   Input:        None
;   Return:       None
;
;   CP 15, CR7, opcode_2=0, CRm5
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c7, c5, 0

    MACRO
        InvalidateICacheAndBTBM    $anyReg
        MCR     CP15,0,$anyReg,CP15CacheOpsReg,CP15InvalidICacheCRm,Op2_0
    MEND


;----------------------------
; InvalidateDCacheM
;
;   Invalidate the Data cache
;   - Individual cache lines can be invalidated using other commands.
;
;   Input:        None
;   Return:       None
;
;   CP 15, CR7, opcode_2=0, CRm6
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c7, c6, 0

    MACRO
        InvalidateDCacheM     $anyReg
        MCR     CP15,0,$anyReg,CP15CacheOpsReg,CP15InvalidDCacheCRm,Op2_0
    MEND


;----------------------------
; InvalidateICacheLineM
;
;   Invalidate a line in the Instruction cache.
;   - Does not invalidate the BTB.
;   - See the Invalidate Operation section of the
;       Intel XScale Core user's manual for notes concerning
;       the use of this operation.
;
;   Input:   R0: MVA identifying the Instruction cache line to be invalidated
;   Return:  None
;
;   CP 15, CR7, opcode_2=1, CRm5
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c7, c5, 1

    MACRO
        InvalidateICacheLineM   $addrReg
        MCR     CP15,0,$addrReg,CP15CacheOpsReg,CP15InvalidICacheCRm,Op2_1
    MEND


;----------------------------
; InvalidateDCacheLineM
;
;   Invalidate a line in the Data cache
;   - See the Invalidate Operation section of the
;       Intel XScale Core user's manual for notes concerning
;       the use of this operation.
;
;   Input:   $addrReg: Will contain MVA identifying the
;                        Data cache line to be invalidated
;   Return:  None
;
;   CP 15, CR7, opcode_2=1, CRm6
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c7, c6, 1

    MACRO
        InvalidateDCacheLineM   $addrReg
        MCR     CP15,0,$addrReg,CP15CacheOpsReg,CP15InvalidDCacheCRm,Op2_1
    MEND


;----------------------------
; CleanDCacheLineM
;
;   Clean a line in the Data cache
;
;   - Updates external memory with data from the "dirty" portions of
;       a specific line in data cache and clears the dirty bits.
;   - Leaves line marked as clean but still valid.
;
;   Input:   R0: MVA identifying the Data cache line to be cleaned
;   Return:  None
;
;   CP 15, CR7, opcode_2=1, CRm10
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c7, c10, 1

    MACRO
        CleanDCacheLineM    $addrReg
        MCR     CP15,0,$addrReg,CP15CacheOpsReg,CP15CleanDCacheCRm,Op2_1
    MEND


;----------------------------
; DrainBuffersM
;
;   Drain the write and fill buffers of the cache.
;
;   - Guarantees that before the next instruction executes,
;     core data requests to external memory have completed.
;
;   Input:         None
;   Return:        None
;
;   CP 15, CR7, opcode_2=4, CRm10
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c7, c10, 4

    MACRO
        DrainBuffersM  $anyReg
        MCR     CP15,0,$anyReg,CP15CacheOpsReg,CP15DrainCacheCRm,Op2_4
        ; In Manzano, a PF (Prefetch Flush) is required to be used in conjunction with
        ; DWB (Data Write Barrier which Drains Write and Fill buffer)
        ; to ensure any data memory hierarchy (by STR, SWP, etc.) are visible to instruction memory
        ; hirerachy accesses as well as page table walks for both instruction and data page table entries.
	IF :DEF: L2_CACHE_ENABLE    ; _TAVOR_BOERNE
        PrefetchFlushM $anyReg
	ENDIF
    MEND


;----------------------------
; InvalidateBTBM
;
;   Invalidate the Branch Target Buffer.
;   - Needed after invalidating individual instruction cache lines.
;
;   Input:         None
;   Return:        None
;
;   CP 15, CR7, opcode_2=6, CRm5
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c7, c5, 6

    MACRO
        InvalidateBTBM     $anyReg
        MCR     CP15,0,$anyReg,CP15CacheOpsReg,CP15InvalidICacheCRm,Op2_6
    MEND

;----------------------------
; AllocateDCacheLineM
;
;   Allocate a line in the Data cache
;
;   - Allocates a tag into the data cache specified by bits
;     [31:5] of $addrReg.  If a valid dirty line (with a different
;     MVA) already exists at this location it will be evicted.
;
;   WARNING: This command has limited uses and many conditions of
;            safe use.  See the Cache Functions section and Data Cache
;            section of the Core user's guide for details.
;
;   Input:   $addrReg bits[31:5]: Will contain MVA identifying the Data
;                                   cache tag to be allocated.
;   Return:  None
;
;   CP 15, CR7, opcode_2=5, CRm2
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c7, c2, 5

    MACRO
        AllocateDCacheLineM    $addrReg
        ; Clear out lower 5 bits, not used.
        BIC     $addrReg,$addrReg,#0x0000000001f
        MCR     CP15,0,$addrReg,CP15CacheOpsReg,CP15AllocateDCacheLineCRm,Op2_5
    MEND


;=========================================================================
; TLB (Translation Lookaside Buffer) operations.   CP15, CR8.
;
;   Write-only.
;
;   Notes: This is an MMU-related register
;          Invalidating a TLB entry or the entire TLB does not unlock it.
;
;
;   MVA = Modified Virtual Address (VA after possible ORing in of PID reg)
;
;   Function                     opcode_2  CRm    Data        Instruction
;
;   Invalidate I&D TLB              0b000 0b0111 Ignored MCR p15, 0, Rd, c8, c7, 0
;   Invalidate I TLB                0b000 0b0101 Ignored MCR p15, 0, Rd, c8, c5, 0
;   Invalidate I TLB entry          0b001 0b0101 MVA     MCR p15, 0, Rd, c8, c5, 1
;   Invalidate D TLB                0b000 0b0110 Ignored MCR p15, 0, Rd, c8, c6, 0
;   Invalidate D TLB entry          0b001 0b0110 MVA     MCR p15, 0, Rd, c8, c6, 1
;

;----------------------------
; InvalidateIandDTLBsM
;
;   Invalidate both the Instruction and Data TLBs
;   - When memory is remapped, all TLB entries relating to the old mapping must be
;       invalidated.
;   - Individual TLB entries may be invalidated by using other commands to CP15.
;
;   Input:         None
;   Return:        None
;   Side Effects:  R0 undefined
;
;   CP 15, CR8, opcode_2=0, CRm7
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c8, c7, 0

    MACRO
        InvalidateIandDTLBsM   $anyReg
        MCR     CP15,0,$anyReg,CP15InvalidateTLBReg,CP15InvalidateIandDTLBsCRm,Op2InvalidateEntireTLB
        CPWAIT  ; Wait for it to happen!

    MEND

;----------------------------
; InvalidateITLBM
;
;   Invalidate the Instruction TLB
;   - When memory is remapped, all TLB entries relating to the old mapping must be
;       invalidated.
;   - Individual TLB entries may be invalidated by using other commands to CP15.
;
;   Input:         None
;   Return:        None
;   Side Effects:  R0 undefined
;
;   CP 15, CR8, opcode_2=0, CRm5
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c8, c5, 0

    MACRO
        InvalidateITLBM  $anyReg
        MCR     CP15,0,$anyReg,CP15InvalidateTLBReg,CP15InvalidateITLBCRm,Op2InvalidateEntireTLB
        CPWAIT  ; Wait for it to happen!
    MEND


;----------------------------
; InvalidateDTLBM
;
;   Invalidate the Data TLB
;   - When memory is remapped, all TLB entries relating to the old mapping must be
;       invalidated.
;   - Individual TLB entries may be invalidated by using other commands to CP15.
;
;   Input:         None
;   Return:        None
;
;   CP 15, CR8, opcode_2=0, CRm6
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c8, c6, 0

    MACRO
        InvalidateDTLBM   $anyReg
        MCR     CP15,0,$anyReg,CP15InvalidateTLBReg,CP15InvalidateDTLBCRm,Op2InvalidateEntireTLB
    MEND


;----------------------------
; InvalidateITLBEntryM
;
;   Invalidate an Instruction TLB Entry
;   - When memory is remapped, all TLB entries relating to the old
;       mapping must be invalidated.
;   - See the Invalidate Operation section of the
;       Intel XScale Core user's manual for notes concerning
;       the use of this operation.
;
;   Input:   $addrReg: Will contain MVA identifying the
;                        Instruction TLB entry to be invalidated
;   Return:  None
;
;   CP 15, CR8, opcode_2=1, CRm5
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c8, c5, 1

    MACRO
        InvalidateITLBEntryM    $addrReg
        MCR     CP15,0,$addrReg,CP15InvalidateTLBReg,CP15InvalidateITLBCRm,Op2InvalidateTLBEntry
    MEND


;----------------------------
; InvalidateDTLBEntryM
;
;   Invalidate a Data TLB Entry
;   - When memory is remapped, all TLB entries relating to the old mapping must be
;       invalidated.
;   - See the Invalidate Operation section of the
;       Intel XScale Core user's manual for notes concerning
;       the use of this operation.
;
;   Input:   $addrReg: Will contain MVA identifying the
;                        Data TLB entry to be invalidated
;   Return:  None
;
;   CP 15, CR8, opcode_2=1, CRm6
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c8, c6, 1

    MACRO
        InvalidateDTLBEntryM   $addrReg
        MCR     CP15,0,$addrReg,CP15InvalidateTLBReg,CP15InvalidateDTLBCRm,Op2InvalidateTLBEntry
    MEND


;=========================================================================
; Cache Lock Down.   CP15, CR9.
;
;   Write-only.
;
;   Notes: This is an MMU-related register
;          Lock/unlock operations on a disabled cache have an undefined effect.
;
;
;   MVA = Modified Virtual Address (VA after possible ORing in of PID reg)
;
;   Function                     opcode_2  CRm    Data        Instruction
;
;   Fetch and Lock I cache line     0b000 0b0001 MVA        MCR p15, 0, Rd, c9, c1, 0
;   Write data cache lock           0b000 0b0010 Set/Clear  MCR p15, 0, Rd, c9, c2, 0
;         register                                 lock mode
;   Unlock Instruction cache        0b001 0b0001 Ignored    MCR p15, 0, Rd, c9, c1, 1
;   Unlock Data Cache               0b001 0b0010 Ignored    MCR p15, 0, Rd, c9, c2, 1
;

;----------------------------
; FetchAndLockICacheLineM
;
;   Fetch and lock an instruction cache line from the specified MVA
;   - Avoids the overhead of cache misses when executing instructions
;       from this address in the future.
;
;   Input:   $addrReg contains target MVA
;   Return:  None
;
;   CP 15, CR9, opcode_2=0, CRm1
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c9, c1, 0

    MACRO
        FetchAndLockICacheLineM    $addrReg
  IF :DEF: L2_CACHE_ENABLE      ;_TAVOR_BOERNE
        MCR     CP15,0,$addrReg,CP15LockCacheReg,CP15Lock_ICacheCRm,Op2LockCache
  ELSE
        MCR     CP15,0,$addrReg,CP15LockCacheReg,CP15LockICacheCRm,Op2LockCache
  ENDIF
    MEND


;----------------------------
; EnableDCacheLockModeM
;
;   Begin Data cache lock mode enable by writing a "1" to the
;   Data Cache Lock Register.  Any fill into the data cache
;   during this mode gets locked in.
;
;   Notes:
;     - This is the only way to lock data into the D cache.
;     - Before locking, the programmer must ensure that no part of
;       the target data range is already resident in the cache.
;       The Intel XScale core will not refetch such data, which
;       will result in it not being locked into the cache.
;
;   Input:        None
;   Return:       None
;   Side Effect:  $anyReg = 1
;
;   CP 15, CR9, opcode_2=0, CRm2, Contents of Rd=1.
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c9, c2, 0

    MACRO
        EnableDCacheLockModeM   $anyReg
        MOV     $anyReg,#1
        MCR     CP15,0,$anyReg,CP15LockCacheReg,CP15LockDCacheCRm,Op2LockCache
    MEND


;----------------------------
; DisableDCacheLockModeM
;
;   End Data cache lock mode enable by writing a "0" to the
;   Data Cache Lock Register.  Fills to the data cache are
;   not locked in after this command.
;
;   Input:   None
;   Return:  $anyReg = 0
;
;   CP 15, CR9, opcode_2=0, CRm2, Contents of Rd=0.
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c9, c2, 0

    MACRO
        DisableDCacheLockModeM   $anyReg
        MOV     $anyReg,#0
        MCR     CP15,0,$anyReg,CP15LockCacheReg,CP15LockDCacheCRm,Op2LockCache
    MEND


;----------------------------
; UnlockInstructionCacheM
;
;   Unlock the entire the Instruction Cache.
;       Note: There is no way to unlock a subset of the ICache.
;
;   Input:        None
;   Return:       None
;
;   CP 15, CR9, opcode_2=1, CRm1
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c9, c1, 1

    MACRO
        UnlockInstructionCacheM   $anyReg
 IF :DEF: _TAVOR_BOERNE_
        MCR     CP15,0,$anyReg,CP15LockCacheReg,CP15Lock_ICacheCRm,Op2UnlockCache
 ELSE
        MCR     CP15,0,$anyReg,CP15LockCacheReg,CP15LockICacheCRm,Op2UnlockCache
 ENDIF
    MEND


;----------------------------
; UnlockDataCacheM
;
;   Unlock the entire Data Cache
;       Note: There is no way to unlock a subset of the DCache.
;
;   Input:        None
;   Return:       None
;
;   CP 15, CR9, opcode_2=1, CRm2
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c9, c2, 1

    MACRO
        UnlockDataCacheM   $anyReg
 IF :DEF: _TAVOR_BOERNE_
        MCR     CP15,0,$anyReg,CP15LockCacheReg,CP15Lock_DCacheCRm,Op2UnlockCache
 ELSE
        MCR     CP15,0,$anyReg,CP15LockCacheReg,CP15LockDCacheCRm,Op2UnlockCache
 ENDIF
    MEND



;=========================================================================
; TLB (Translation Lookaside Buffer) Lock Down.   CP15, CR10.
;
;   Write-only.
;
;   Notes: This is an MMU-related register
;          Lock/unlock operations when MMU is disabled have an undefined effect.
;          For applicable protocols, see the Memory Management section of the
;            Intel XScale Core user's manual.
;
;
;   MVA = Modified Virtual Address (VA after possible ORing in of PID reg)
;
;   Function                     opcode_2  CRm    Data        Instruction
;
;   Translate and Lock I TLB entry    0b000 0b0100 MVA        MCR p15, 0, Rd, c10, c4, 0
;   Translate and Lock D TLB entry    0b000 0b1000 MVA        MCR p15, 0, Rd, c10, c8, 0
;   Unlock I TLB                      0b001 0b0100 Ignored    MCR p15, 0, Rd, c10, c4, 1
;   Unlock D TLB                      0b001 0b1000 Ignored    MCR p15, 0, Rd, c10, c8, 1
;


;----------------------------
; TransAndLockITLB_EntryM
;
;   Translate an MVA to its physical address and lock it into the
;       Instruction TLB.
;   - Avoids the overhead of TLB misses when executing instructions
;       from this address in the future.
;
;   Input:   $addrReg: Will contain the MVA to be translated and
;                           locked in the ITLB.
;   Return:  None
;
;   CP 15, CR10, opcode_2=0, CRm4
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c10, c4, 0

    MACRO
        TransAndLockITLB_EntryM   $addrReg
        MCR     CP15,0,$addrReg,CP15LockTLBReg,CP15LockITLBCRm,Op2LockTLB
    MEND


;----------------------------
; TransAndLockDTLB_EntryM
;
;   Translate an MVA to its physical address and lock it into the
;       Data TLB.
;   - Avoids the overhead of TLB misses when accessing data
;       at this address in the future.
;
;   Input:   $addrReg: Will contain MVA to be translated and
;                           locked in the DTLB.
;   Return:  None
;
;   CP 15, CR10, opcode_2=0, CRm8
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c10, c8, 0

    MACRO
        TransAndLockDTLB_EntryM   $addrReg
        MCR     CP15,0,$addrReg,CP15LockTLBReg,CP15LockDTLBCRm,Op2LockTLB
    MEND


;----------------------------
; UnlockInstructionTLBM
;
;   Unlock the entire Instruction Translation Lookaside Buffer.
;       Note: There is no way to unlock a subset of the ITLB.
;
;   Input:        None
;   Return:       None
;
;   CP 15, CR10, opcode_2=1, CRm4
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c10, c4, 1

    MACRO
    UnlockInstructionTLBM   $anyReg
    MCR     CP15,0,$anyReg,CP15LockTLBReg,CP15LockITLBCRm,Op2UnlockTLB
    MEND


;----------------------------
; UnlockDataTLBM
;
;   Unlock the entire Data Translation Lookaside Buffer.
;       Note: There is no way to unlock a subset of the DTLB.
;
;   Input:   None
;   Return:       None
;
;   CP 15, CR10, opcode_2=1, CRm8
;   Nonsymbolic core instruction:
;       MCR p15, 0, Rd, c10, c8, 1

    MACRO
    UnlockDataTLBM   $anyReg
    MCR     CP15,0,$anyReg,CP15LockTLBReg,CP15LockDTLBCRm,Op2UnlockTLB
    MEND


;=========================================================================
;
;   Note: CP15's CR11 and CR12 are reserved.
;


;=========================================================================
; Process ID (PID)  CP15, CR13, no opcode_2
;
;   Note: This is an MMU-related register
;
;

;----------------------------
; GetProcessIDM
;
;   Get value of the Process ID (PID) Register.
;
;   Input:   None
;   Return:  $retReg contains existing value
;
;   CP 15, reg 13
;   Nonsymbolic core instruction:
;       MRC CP15, 0, Rd, c13, c0, 0

    MACRO
        GetProcessIDM    $retReg
        MRC     CP15,0,$retReg,CP15ProcessIDReg,CP15CRm_0,Op2_0
    MEND

;----------------------------
; SetProcessIDM
;
;  Set value of the Process ID (PID) Register.
;
;  Input:   $setReg contains new value
;  Return:  None
;
;  CP 15, reg 13
;  Nonsymbolic core instruction:
;      MCR CP15, 0, Rd, c13, c0, 0

    MACRO
        SetProcessIDM    $setReg
        MCR     CP15,0,$setReg,CP15ProcessIDReg,CP15CRm_0,Op2_0
    MEND


;=========================================================================
;  Breakpoint Registers  CP15, CR14, opcode_2 varies
;
;   Not implemented.
;
;   Note: It is unclear that macros or subroutines
;         for this purpose would be useful.
;


;=========================================================================
; Coprocessor Access Register  CP15, CR15, opcode_2 = 0, CRm=1
;
;   - Read/Write
;

;----------------------------
; GetCoprocessorAccessM
;
;   Get value of the Coprocessor Access Register.
;
;   Input:   None
;   Return:  $retReg contains existing value
;
;   CP 15, reg 15, opcode_2 = 0, CRm=1
;   Nonsymbolic core instruction:
;       MRC CP15, 0, Rd, c15, c1, 0

    MACRO
    GetCoprocessorAccessM   $retReg

    MRC     CP15,0,$retReg,CP15CoprocessorAccessReg,CP15CoprocessorAccessCRm,Op2_0
    ; Zero undefined bits, including those undefined for Cotulla
    BIC     $retReg,$retReg,#0xff000000
    BIC     $retReg,$retReg,#0x00ff0000
    IF  :LNOT: :DEF: _TAVOR_HARBELL_
;;   BIC     $retReg,$retReg,#0x0000df00  ;0-15 are allowed
;;   BIC     $retReg,$retReg,#0x000000fe  ;0-15 are allowed
    ELSE
     BIC     $retReg,$retReg,#0x0000df00
     BIC     $retReg,$retReg,#0x000000fe
    ENDIF
    MEND


;----------------------------
; SetCoprocessorAccessM
;
;   Set value of the Coprocessor Access Register.
;
;   Input:   $setReg contains new value
;   Return:  None
;
;   CP 15, reg 15, opcode_2 = 0, CRm=1
;   Nonsymbolic core instruction:
;       MCR CP15, 0, Rd, c15, c1, 0

    MACRO
    SetCoprocessorAccessM    $setReg
    ; Zero undefined bits, including those undefined for Cotulla
    BIC     $setReg,$setReg,#0xff000000
    BIC     $setReg,$setReg,#0x00ff0000
    IF  :LNOT: :DEF: _TAVOR_HARBELL_
;;   BIC     $setReg,$setReg,#0x0000df00 ;0-15 are allowed
;;   BIC     $setReg,$setReg,#0x000000fe ;0-15 are allowed
    ELSE
     BIC     $setReg,$setReg,#0x0000df00
     BIC     $setReg,$setReg,#0x000000fe
    ENDIF


    MCR     CP15,0,$setReg,CP15CoprocessorAccessReg,CP15CoprocessorAccessCRm,Op2_0
    MEND

;=========================================================================
;  Utility macros
;

;----------------------------
; EnableDCacheM
;
;   Enable the Data Cache, using necessary protections.
;
;   From the code example in the Intel XScale Core user's manual.
;
;   Input:        None
;   Return:       None
;   Side Effects: $anyReg undefined
;   Assumptions:  MMU already enabled
;
;   CP 15, reg 1, opcode_2=0
;   Nonsymbolic core instructions:
;       MCR p15, 0, $anyReg, c7, c10, 4
;       MRC p15, 0, $anyReg, c1, c0,  0
;       MCR p15, 0, $anyReg, c1, c0,  0


    MACRO
    EnableDCacheM  $anyReg

    ; Drain pending data operations...
    DrainBuffersM  $anyReg      ; MCR p15, 0, $anyReg, c7, c10, 4

    GetARMControlM   $anyReg    ; MRC p15, 0, $anyReg, 1, 0, 0
    ; Enable DCache by setting ‘C' (bit 2)
    ORR $anyReg, $anyReg, #CP15DCacheEnable;
    SetARMControlM   $anyReg   ; MCR p15, 0, $anyReg, 1, 0, 0

    MEND


;----------------------------
; DisableDCacheM
;
;   Disable the Data Cache, using necessary protections.
;
;   Input:        None
;   Return:       None
;   Side Effects: $anyReg undefined
;
;   CP 15, reg 1, opcode_2=0
;   Nonsymbolic core instructions:
;       MCR p15, 0, $anyReg, c7, c10, 4
;       MRC p15, 0, $anyReg, c1, c0,  0
;       MCR p15, 0, $anyReg, c1, c0,  0
;
;   NOTE from the from Intel XScale Core user's manual:
;              Operation When Data Caching is Disabled
;     The data/mini-data cache is still accessed even though it is
;     disabled. If a load hits the cache it will return the requested
;     data to the destination register. If a store hits the cache,
;     the data is written into the cache. Any access that misses the
;     cache will not allocate a line in the cache when it's disabled,
;     even if the MMU is enabled and the memory region's cacheability
;     attribute is set.
;
;   (Therefore, effective disabling of the data cache requires additional
;   action.  That action is performing the global clean and invalidate
;   procedure using dedicated virtual memory locations.  This is exampled
;   in the Intel XScale Core user's manual and implemented in CleanDCache()
;   (fast version).)
;

    MACRO
    DisableDCacheM  $anyReg

    ; Drain pending data operations...
    DrainBuffersM  $anyReg      ; MCR p15, 0, $anyReg, c7, c10, 4

    GetARMControlM   $anyReg    ; MRC p15, 0, $anyReg, 1, 0, 0
    ; Disable DCache by clearing ‘C' (bit 2)
    BIC $anyReg, $anyReg, #CP15DCacheEnable;
    SetARMControlM   $anyReg   ; MCR p15, 0, $anyReg, 1, 0, 0

    MEND



    IF   :DEF: L2_CACHE_ENABLE     ;for _TAVOR_BOERNE_ only
    ;===========================
    
; DisableInterruptsM(A, B)
;
;	Disable interrupts: IRQ and FIQ
;
;	Input:		A: temporaty register
;	Output:		CPSR value during interrupt disabling
;
; Note: this macro is similar to disableInterrupts function.
; disableInterrupts cannot be used as it uses bx instrction.

    MACRO
    DisableInterruptsM $A, $B
    mrs	$A, cpsr					; Save CPSR
	orr $B, $A, #PSR_IF
	msr cpsr_c, $B					; Disable Interrupts
    MEND

PSR_IF			EQU		0xC0    ; both IRQ and FIQ
L_INV			EQU		0x01    ; invalidate cache, boolean value
M_LOCKED		EQU		0x01    ; lock mode value
M_NOT_LOCKED	EQU		0x00    ; unlock mode value
LINE_SIZE		EQU		0x20    ; I, D, L2 cache line size - 32 bytes
DCACHE_NUMSETS	EQU		0x100   ; D cache number of sets - 256 on Boerne
WAYINDEX		EQU		0x40000000
SETINDEX		EQU		0x20
TTBR_OC         EQU     0x18    ; page table entries are outer cacheable (i.e. cache I/D TLB in L2 cache)


; GET_L2_PRESENT(reg)
;
;   This macro sets CPSR.z = 1 if L2 cache not present, else CPSR.z = 0
;
; Note: According to Manzano EAS, CTRL minimum issue latency is 4 cycles,
;       thus it's unsuitable to call it on every L2 cache operation,
;       instead _TAVOR_BOERNE_L2CACHE_ define is used.
;       Should be used in non-critical path only.
;
    MACRO
	GET_L2_PRESENT $Reg
		mrc p15, 1, $Reg, CP15IDReg, CP15IDReg, Op2CacheType	; Read L2 Cache Type Register for Associativity
		ands $Reg, $Reg, #0xf8		; See if the L2 Cache is absent
 	MEND


    MACRO
    BARRIER $Reg
    mcr p15, 0, $Reg, CP15CacheOpsReg, CP15DrainCacheCRm, Op2_5
    MEND

    ; This macro enables L2 cache by setting bit 26 in Control Register of CP15
	MACRO
	L2CacheEnableM $Reg
	    mrc p15, 0, $Reg, CP15ArmControlReg, CP15CRm_0, Op2_0
	    orr $Reg, $Reg, #0x04000000
	    mcr p15, 0, $Reg, CP15ArmControlReg, CP15CRm_0, Op2_0
	MEND


; DCacheLinesCleanInvalidateM(reg0, reg1)
;
;	Clean, invalidate and  unlock cache lines corresponding to a region of memory in the L1
;   data cache.
;
; Input:	Reg0: contains the virtual address of the region of memory to clean & unlock
;			Reg1: is the number of 32-byte lines to clean, invalidate and unlock in the data cache.
;
; Note: this is new feature added in Manzano core, previous implementations acheived in two operations.

	MACRO
	DCacheLinesCleanInvalidateM	$Reg0, $Reg1
LOOP1
	mcr p15, 0, $Reg0, CP15CacheOpsReg, CP15CleanAndInvalidateDCacheLineCRm, Op2_1	; Clean and Invalidate in one operation
	add $Reg0, $Reg0, #LINE_SIZE		; increment addr in r1 to the next cache line

	subs $Reg1, $Reg1, #1				; Decrement loop count
	bne LOOP1
	; The data at the addresses in r0 has been written out if dirty, unlocked
	; and the cache lines are now invalid.
	MEND


; DCacheLinesCleanSetWayM(set_way)
;
;	Clean data cache line by set and way
;
;	Input:		Reg0: set/way
;
; Note: this is new feature added in Manzano core.

	MACRO
	DCacheLinesCleanSetWayM $Reg0
	mcr p15, 0, $Reg0, CP15CacheOpsReg, CP15CleanDCacheCRm, Op2_2	; clean set/way specified in $Reg0
	MEND



; DCacheGloballyCleanM(r0, r1)
;
;	Globally clean the L1 data cache, if invalidate is TRUE invalidate too
;
;	Input:		Reg0: invalidate if TRUE, otherwise clean only
;               Reg1: temp register used localy only
;
; Note: set/way commands are most robust.
; Affects performance optimized code (tuned to 32-way cache).
	MACRO
	DCacheGloballyCleanM $Reg0, $Reg1
	mov $Reg1, #DCACHE_NUMSETS
	sub $Reg1, $Reg1, #1
	mov $Reg1, $Reg1, lsl #5		; Put number of sets into bits 12:5 of r1

90
    mov $Reg0, #L_INV
	cmp	$Reg0, #L_INV
	; The below two lines do not incur any branch misprediction penalties
	mcreq p15, 0, $Reg1, CP15CacheOpsReg, CP15CleanAndInvalidateDCacheLineCRm, Op2_2 ; clean set/way specified in r1
	mcrne p15, 0, $Reg1, CP15CacheOpsReg, CP15CleanDCacheCRm, Op2_2 ; clean/invalidate set/way specified in r1

	adds $Reg1, $Reg1, #WAYINDEX	; Increment shifted way index
	bcc %b90          		        ; Clean the next way if not done with this set
	subs $Reg1, $Reg1, #SETINDEX	; Decrement shifted set index
	bpl %b90           		        ; Go to next set if not at last one
	MEND


; DCacheLLREnableM(Reg)
;
;	enable LLR capability for L1 data cache if enable is TRUE, otherwise disable
;
;	Input:		Reg0: LLR IC attribute. This is two bit value, see Manzano Core IAS/EAS.
;
; Note: This feature allows an application to confine data in LLR memory regions
; to a single way of the L1 data cache, instead of polluting the entire cache.
; Manzano core does not have mini data cache, but it accomplishes roughly the same task
; without the extra hardware by enabling LLR memory within the cache.
; See Auxiliary Control Register for more.

	MACRO
	DCacheLLREnableM $Reg
	mov $Reg, $Reg, lsl #4	; Put LLR IC attribute into bits 5:4 of $Reg0
	mcr p15, 0, $Reg, CP15AuxControlReg, CP15CRm_0, Op2_1
	MEND

; L2CacheLineCleanM(Reg)
;
;   clean L2 cache line by MVA (modified virtual address) if it was modified.
;
;   Input:  Reg: MVA
;
    MACRO
    L2CacheLineCleanM $Reg
    mcr p15, 1, $Reg, CP15CacheOpsReg, CP15CleanL2CacheLineCRm, Op2_1
    MEND



; L2CacheLineInvalidateM(Reg)
;
;   invalidate L2 cache line by MVA (modified virtual address).
;
;   Input:  Reg: MVA
;
    MACRO
    L2CacheLineInvalidateM $Reg
    mcr p15, 1, $Reg, CP15CacheOpsReg, CP15InvalidL2CacheCRm, Op2_1
    MEND


    MACRO
    PrefetchFlushM $Reg
    mcr p15, 0, $Reg, CP15CacheOpsReg, CP15PrefetchFlushCRm, Op2_4
    MEND


; 	L2CacheCreateIRamM(Reg0, Reg1) (start, lines)
;		Allocate and Lock L2 Cache Line
;
; Input:	Reg0: contains the virtual address of the region of memory to lock
;			Reg1: is the number of 32-byte lines to Allocate and lock.
;
; Note: this is new feature to creat RAM from L2$.

	MACRO
	L2CacheCreateIRamM	$Reg0, $Reg1
LOOP2
		mcr p15, 1, $Reg0, CP15LockCacheReg, CP15AllocateandLockCRm, Op2_0	; fetch and Lock L2 Cache Line
		add $Reg0, $Reg0, #LINE_SIZE		; increment addr in r1 to the next cache line

	subs $Reg1, $Reg1, #1				; Decrement loop count
	bne LOOP2
	MEND

; 	L2CacheCreateRamM(Reg0, Reg1) (start, lines)
;		Allocate and Lock L2 Cache Line
;
; Input:	Reg0: contains the virtual address of the region of memory to lock
;			Reg1: is the number of 32-byte lines to Allocate and lock.
;
; Note: this is new feature to creat RAM from L2$.

	MACRO
	L2CacheCreateRamM	$Reg0, $Reg1
LOOP3
		mcr p15, 1, $Reg0, CP15LockCacheReg, CP15AllocateandLockCRm, Op2_2	; Allocate and Lock L2 Cache Line
		add $Reg0, $Reg0, #LINE_SIZE		; increment addr in r1 to the next cache line

	subs $Reg1, $Reg1, #1				; Decrement loop count
	bne LOOP3
	MEND




; L2CacheCleanInvalidateM(Reg)
;
;   clean and invalidate entire L2 cache.
;
;   Input:  Reg:
;
    MACRO
    L2CacheCleanInvalidateM $Reg

    BARRIER $Reg

    mrc p15, 1, $Reg, c0, c0, 1
    and $Reg, $Reg, #0xF00
    tst $Reg, #0x200
    moveq $Reg, #0x7F00
    movne $Reg, #0xFF00
    orr $Reg, $Reg, #0x00E0

91
    mcr p15, 1, $Reg, c7, c15, 2
    adds $Reg, $Reg, #0x20000000
    bcc %b91
    subs $Reg, $Reg, #0x00000020
    bpl %b91

    BARRIER $Reg

    MEND


    ;==========================
    ENDIF   ;L2_CACHE_ENABLE

		
    END
