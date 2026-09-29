;------------------------------------------------------------
; (C) Copyright [2006-2008] Marvell International Ltd.
; All Rights Reserved
;------------------------------------------------------------

;*********************************************************************************
;
;        COPYRIGHT (c) 2004 Intel Corporation
;
;   The information in this file is furnished for informational use only,
;   is subject to change without notice, and should not be construed as
;   a commitment by Intel Corporation. Intel Corporation assumes no
;   responsibility or liability for any errors or inaccuracies that may appear
;   in this document or any software that may be provided in association with
;   this document.
;
;*********************************************************************************
;
;  FILENAME:       xlli_Tavor_defs.inc
;
; LAST MODIFIED:   26-Apr-2006
;
;******************************************************************************
;
; Include file for Tavor Processor based
; Cross Platform Low Level Initialization  (XLLI)
;

;
; GENERAL PURPOSE I/O (GPIO) base address and register offsets from the base address
;

xlli_GPIOREGS_PHYSICAL_BASE     EQU 	0x40E00000
xlli_MFPR_PHYSICAL_BASE         EQU     0x40E10000

; GPIO register offsets from the base address

xlli_GPLR0_offset       EQU     0x000   ; GPIO Level registers
xlli_GPLR1_offset       EQU     0x004
xlli_GPLR2_offset       EQU     0x008
xlli_GPLR3_offset       EQU     0x100

xlli_GPDR0_offset       EQU     0x00C   ; GPIO Direction registers
xlli_GPDR1_offset       EQU     0x010
xlli_GPDR2_offset       EQU     0x014
xlli_GPDR3_offset       EQU     0x10C

xlli_GPSR0_offset       EQU     0x018   ; GPIO Set registers
xlli_GPSR1_offset       EQU     0x01C
xlli_GPSR2_offset       EQU     0x020
xlli_GPSR3_offset       EQU     0x118

xlli_GPCR0_offset       EQU     0x024   ; GPIO Clear registers
xlli_GPCR1_offset       EQU     0x028
xlli_GPCR2_offset       EQU     0x02C
xlli_GPCR3_offset       EQU     0x124

;xlli_GAFR0_L_offset     EQU     0x054   ; Bulverde GPIO Alternate function registers (Bits 15:0)
;xlli_GAFR0_U_offset     EQU     0x058   ; Bits 31:16
;xlli_GAFR1_L_offset     EQU     0x05C   ; Bits 47:32
;xlli_GAFR1_U_offset     EQU     0x060   ; Bits 63:48
;xlli_GAFR2_L_offset     EQU     0x064   ; Bits 79:64
;xlli_GAFR2_U_offset     EQU     0x068   ; Bits 95:80
;xlli_GAFR3_L_offset     EQU     0x06C   ; Bits 111:96
;xlli_GAFR3_U_offset     EQU     0x070   ; Bits 127:112

;
; POWER MANAGER base address and register offsets from the base address (Bulverde)
;
xlli_PMRCREGS_PHYSICAL_BASE	 EQU 	0x40F00000 


xlli_PCFR_offset        EQU     (0x1C)  ; Power Manager General Configuration Register
xlli_PI2DBR_offset      EQU     (0x188) ; Power I2C Data Buffer Register
xlli_PI2CR_offset       EQU     (0x190) ; Power I2C Control Register
xlli_PI2SR_offset       EQU     (0x198) ; Power I2C Status Register
xlli_PI2SAR_offset      EQU     (0x1A0) ; Power I2C Slave Address Register

;
; POWER MANAGER base address and register offsets from the base address (Monahans)
;
xlli_PMCREGS_PHYSICAL_BASE      EQU     0x40F50000
;
;
; POWER MANAGER register bit masks 
;
xlli_PSSR_SSS           EQU     (0x01)  ; Software Sleep Status
xlli_PSSR_BFS           EQU     (0x02)  ; Battery Fault Status
xlli_PSSR_VFS           EQU     (0x04)  ; VCC Fault Status
xlli_PSSR_PH            EQU     (0x10)  ; Peripheral Control Hold
xlli_PSSR_RDH           EQU     (0x20)  ; Read Disable Hold

xlli_PCFR_OPDE          EQU     (0x01)  ; Processor (13MHz) osc power-down enable
xlli_PCFR_FP            EQU     (0x02)  ; Float PCMCIA during sleep modes
xlli_PCFR_FS            EQU     (0x04)  ; Float Static Chip Selects
xlli_PCFR_SYSEN_EN      EQU     (0x20)  ; SYS_EN pin
xlli_PCFR_DC_EN         EQU     (0x80)  ; Deep-Sleep Mode

xlli_PWER_WE0           EQU     (0x01)          ; Wake-up Enable GPIO pin 0
xlli_PWER_WE1           EQU     (0x02)          ; Wake-up Enable GPIO pin 1
xlli_PWER_WERTC         EQU     (0x80000000)    ; RTC Standby, Wake-up Enable-

;
; EXTERNAL MEMORY CONTROLLER base address and register offsets from the base address 
;

xlli_DMEMREGS_PHYSICAL_BASE     EQU     0x48100000

xlli_MDCNFG_offset      EQU     0x000
xlli_MDREFR_offset      EQU     0x004
xlli_MSC0_offset        EQU     0x008
xlli_MSC1_offset        EQU     0x00C
xlli_MSC2_offset        EQU     0x010
xlli_MECR_offset        EQU     0x014
xlli_SXLCR_offset       EQU     0x018
xlli_SXCNFG_offset      EQU     0x01C
xlli_FLYCNFG_offset     EQU     0x020
xlli_SXMRS_offset       EQU     0x024                                       
xlli_MCMEM0_offset      EQU     0x028
xlli_MCMEM1_offset      EQU     0x02C
xlli_MCATT0_offset      EQU     0x030
xlli_MCATT1_offset      EQU     0x034
xlli_MCIO0_offset       EQU     0x038
xlli_MCIO1_offset       EQU     0x03C
xlli_MDMRS_offset       EQU     0x040
xlli_BOOT_DEF_offset    EQU     0x044
xlli_ARB_CNTL_offset    EQU     0x048
xlli_BSCNTR0_offset     EQU     0x04C
xlli_DDR_SCAL_offset    EQU     0x050   ; Software Delay Line Cal/Config for DDR Memory read
xlli_DDR_HCAL_offset    EQU     0x060   ; Hardware Delay Line Cal/Config for DDR Memory read
xlli_BSCNTR3_offset     EQU     0x060
xlli_DDR_WCAL_offset    EQU     0x068   ; Delay Line Cal/Config for DDR Memory Write strobes
xlli_DMCIER_offset      EQU     0x070   ; 
xlli_DMCISR_offset      EQU     0x078   ; 
xlli_DDR_DLS_offset     EQU     0x080   ; DDR Dleay Line value Status Register for external DDR memory
xlli_EMPI_offset        EQU     0x090   ; EMPI Control Register
xlli_RCOMP_offset       EQU     0x100   ; RCOMP Control Register
xlli_PAD_MA_offset      EQU     0x110   ; Strength / Slew Settings for Pads MA [15:0]
xlli_PAD_MDMSB_offset   EQU     0x114   ; Strength / Slew Settings for Pads MD [31:16]
xlli_PAD_MDLSB_offset   EQU     0x118   ; Strength / Slew Settings for Pads MD [15:0]
xlli_PAD_DMEM_offset    EQU     0x11C   ; Strength / Slew Settings for Pads nSDCAS, nSDRAS, nSDWE....
xlli_PAD_SDCLK_offset   EQU     0x120   ; Strength / Slew settings for Pads SDCLK[1:0]
xlli_PAD_SDCS_offset    EQU     0x124   ; Strength / Slew settings for Pads nSDCS[1:0]
xlli_PAD_SMEM_offset    EQU     0x128   ; Strength / Slew settings for Pads nOE, nWE, nCS, nADV, nADV2
xlli_PAD_SCLK_offset    EQU     0x12C   ; Strength / Slew settings for Pads SCLK
xlli_CMA_offset         EQU     0xFFC   ; Controller Miscellaneous Access Register

; Memory Controller bit defs

xlli_MDREFR_K0DB4       EQU     0x20000000      ; Sync Static Clock 0 divide by 4 control/status
xlli_MDREFR_K2FREE      EQU     0x02000000      ; Set to force SDCLK[2] to be free running
xlli_MDREFR_K1FREE      EQU     0x01000000      ; Set to force SDCLK[1] to be free running
xlli_MDREFR_K0FREE      EQU     0x00800000      ;  Set to force SDCLK[0] to be free running
xlli_MDREFR_SLFRSH      EQU     0x00400000      ; Self Refresh Control Status bit
xlli_MDREFR_APD         EQU     0x00100000      ; Auto Power Down bit
xlli_MDREFR_K2DB2       EQU     0x00080000      ; SDRAM clock pin 2 divide by 2 control/status
xlli_MDREFR_K1DB2       EQU     0x00020000      ; SDRAM clock pin 1 divide by 2 control/status
xlli_MDREFR_K1RUN       EQU     0x00010000      ; SDRAM clock pin 1 run/control status
xlli_MDREFR_E1PIN       EQU     0x00008000      ;  SDRAM clock Enable pin 1 level control/status
xlli_MDREFR_K0DB2       EQU     0x00004000      ; Sync Static Memory Clock divide by 2 control/status
xlli_MDREFR_K0RUN       EQU     0x00002000      ; Sync Static Memory Clock Pin 0
xlli_MDREFR_SWFREQ      EQU     0x00000200      ; Frequency Change Bit
xlli_MDREFR_E0PIN       EQU     0x00000100      ; SDRAM clock enable pin 0 (Cotulla ONLY!!)
;
;       MDCNFG bit settings
;
xlli_MDCNFG_DE0         EQU     0x00000001      ; SDRAM enable bit for partition 0 (PXA27x only)
xlli_MDCNFG_DE1         EQU     0x00000002      ; SDRAM enable bit for partition 1 (PXA27x only)
xlli_MDCNFG_DSCE        EQU     0x00000003      ; Dynamic Chip Select Enable bits (Monahans)
xlli_MDCNFG_DWID0       EQU     0x00000004      ; SDRAM bus width (clear = 32 bits, set = 16 bits)
xlli_MDCNFG_DE2         EQU     0x00010000      ; SDRAM enable bit for partition 2
xlli_MDCNFG_DE3         EQU     0x00020000      ; SDRAM enable bit for partition 3
xlli_MDCNFG_DMCEN       EQU     0x40000000      ; Enable Dynamic Memory Controller
;
;       MDMRS bit settings
;
xlli_MDMRS_MSCS1        EQU     0x80000000      ; Controls assertion of CS1 during MRS command
xlli_MDMRS_MSCS0        EQU     0x40000000      ; Controls assertion of CS0 during MRS command
xlli_MDMRS_MDCOND       EQU     0x20000000      ; MD Condition bit
;
;       MDCISR bit settings
;
xlli_DMCISR_SLFREF      EQU     0x00000080      ; Self refresh bit
;
;       RCOMP register bit settings
;
xlli_RCOMP_SWEVAL       EQU     0x80000000      ; Software Rcomp Evaluation Request bit
xlli_RCOMP_UPDATE       EQU     0x40000000      ; Pad Registers Update bit
xlli_RCOMP_RCNOP        EQU     0x01000000      ; Rcomp NOP bit
;
;       Misc External Memory Control bits
;
xlli_DDR_HCAL_HCEN      EQU     0x80000000      ; Hardware Calibration Phase Detector enable
xlli_DDR_HCAL_HCPW      EQU     0x20000000      ; Hardware Calibration Phase Detector Pulse Width
xlli_DDR_HCAL_HCPROG    EQU     0x10000000      ; Hardware calibration program mode bit 
xlli_DDR_HCAL_HCOD      EQU     0x08000000      ; Hardware Calibration Overhead Delay
xlli_CMA_APDD           EQU     0x02000000      ; Auto Power Down Disable
xlli_DMCISR_DLP         EQU     0x20000000      ; Delay Lines Programmed (HW Cal) done bit

;
; INTERNAL MEMORY CONTROLLER base address and register offsets from the base address 
;

xlli_IMEMORY_CONFIG_BASE        EQU     0x58000000

xlli_IMPMCR_offset      EQU     0x00    ; Internal Memory Power Manager Control Register
xlli_IMPMSR_offset      EQU     0x08    ; Internal Memory Power Management Status Register

;
;       Static Memory Controller offsets
;
xlli_STAMREGS_PHYSICAL_BASE     EQU     0x4A000000      ; Static memory controller base

xlli_CSADRCFG0_offset   EQU     0x80    ; Offset to Address Config Reg for Chip sel 0
xlli_CSADRCFG1_offset   EQU     0x84    ; Offset to Address Config Reg for Chip sel 1
xlli_CSADRCFG2_offset   EQU     0x88    ; Offset to Address Config Reg for Chip sel 2
xlli_CSADRCFG3_offset   EQU     0x8C    ; Offset to Address Config Reg for Chip sel 3
xlli_CSMSADRCFG_offset  EQU     0xA0    ; Offset from base to CSMSADRCFG register

; to be set at init (brn_init.s)
xlli_CSADRCFG3_value	EQU		0x003E080B ; Chip select 3 configuration

;
; CLOCK REGISTERS base address and register offsets from the base address
; 

xlli_CLKREGS_PHYSICAL_BASE      EQU     0x41340000      ; Clocks Register base

xlli_ACCR_offset        EQU     0x00    ; Application Clock Configuration Register
xlli_ACSR_offset        EQU     0x04    ; Application Clock Status Register
xlli_D0CKEN_A_offset    EQU     0x0C    ; Offset to D0CKEN_A Register
xlli_D0CKEN_B_offset    EQU     0x10    ; Offset to D0CKEN_B Register
xlli_OSCC_offset        EQU     0x08    ; Oscillator Configuration Register

xlli_CCCR_A_Bit_Mask    EQU     (0x1 << 25)     ; "A" bit is bit 25 in CCCR

;
; OS TIMER REGISTERS base address and register offsets from the base address
; 

xlli_OSTREGS_PHYSICAL_BASE        EQU     (0x40A00000)

xlli_OSCR0_offset       EQU     (0x10)  ; OS Timer Count Register 0

;
; REAL TIME CLOCK (RTC) REGISTERS base address and register offsets from the base address
; 

xlli_RTCREGS_PHYSICAL_BASE      EQU     (0x40900000)

xlli_RCNR_offset        EQU     (0x00)  ; RTC Counter Register
xlli_RTAR_offset        EQU     (0x04)  ; RTC Alarm Register
xlli_RTSR_offset        EQU     (0x08)  ; RTC Status Register
xlli_RTTR_offset        EQU     (0x0C)  ; RTC Timer Trim Register
xlli_RDCR_offset        EQU     (0x10)  ; RTC Day Counter Register
xlli_RYCR_offset        EQU     (0x14)  ; RTC Year Counter Register 
xlli_RDAR1_offset       EQU     (0x18)  ; RTC Day Alarm Register 1
xlli_RYAR1_offset       EQU     (0x1C)  ; RTC Year Alarm Register 2
xlli_RDAR2_offset       EQU     (0x20)  ; RTC Day Alarm Register 2
xlli_RYAR2_offset       EQU     (0x24)  ; RTC Year Alarm Register 2
xlli_SWCR_offset        EQU     (0x28)  ; Stopwatch Counter Register
xlli_SWAR1_offset       EQU     (0x2C)  ; Stopwatch Alarm Register 1
xlli_SWAR2_offset       EQU     (0x30)  ; Stopwatch Alarm Register 2
xlli_PICR_offset        EQU     (0x34)  ; Periodic Interrupt Counter Register
xlli_PIAR_offset        EQU     (0x38)  ; Periodic Interrupt Alarm Register

;
; Coprocessor 15 data bits
; 

xlli_control_icache  EQU     (0x1000)  ; bit 12 -  i-cache bit
xlli_control_btb     EQU     (0x0800)  ; bit 11 -  btb bit
xlli_control_r       EQU     (0x0200)  ; Bit 9
xlli_control_s       EQU     (0x0100)  ; Bit 8
xlli_control_dcache  EQU     (0x0004)  ; Bit 2  -  d-cache bit
xlli_control_mmu     EQU     (0x0001)  ; Bit 0  -  MMU bit


;
; CP 15 related settings
;

xlli_PID                   EQU     (0x00)
xlli_DACR                  EQU     (0x01)
xlli_CONTROL_DCACHE        EQU     (0x04)
xlli_CONTROL_MINIDATA_01   EQU     (0x10)
xlli_CONTROL_BTB           EQU     (0x800)   ; Brach Target Buffer bit

;
;  CPSR Processor constants
;
xlli_CPSR_Mode_MASK   EQU       (0x0000001F)
xlli_CPSR_Mode_USR    EQU       (0x10)
xlli_CPSR_Mode_FIQ    EQU       (0x11)
xlli_CPSR_Mode_IRQ    EQU       (0x12)
xlli_CPSR_Mode_SVC    EQU       (0x13)
xlli_CPSR_Mode_ABT    EQU       (0x17)
xlli_CPSR_Mode_UND    EQU       (0x1B)
xlli_CPSR_Mode_SYS    EQU       (0x1F)

xlli_CPSR_I_Bit       EQU       (0x80)
xlli_CPSR_F_Bit       EQU       (0x40)


xlli_PWRMODE_SLEEP    EQU       (0x00000003) ; Value for cp14: Reg7 to induce sleep.
;
;     Bit settings
;
xlli_BIT_0      EQU     0x00000001
xlli_BIT_1      EQU     0x00000002
xlli_BIT_2      EQU     0x00000004
xlli_BIT_3      EQU     0x00000008
xlli_BIT_4      EQU     0x00000010
xlli_BIT_5      EQU     0x00000020
xlli_BIT_6      EQU     0x00000040
xlli_BIT_7      EQU     0x00000080
xlli_BIT_8      EQU     0x00000100
xlli_BIT_9      EQU     0x00000200
xlli_BIT_10     EQU     0x00000400
xlli_BIT_11     EQU     0x00000800
xlli_BIT_12     EQU     0x00001000
xlli_BIT_13     EQU     0x00002000
xlli_BIT_14     EQU     0x00004000
xlli_BIT_15     EQU     0x00008000
xlli_BIT_16     EQU     0x00010000
xlli_BIT_17     EQU     0x00020000
xlli_BIT_18     EQU     0x00040000
xlli_BIT_19     EQU     0x00080000
xlli_BIT_20     EQU     0x00100000
xlli_BIT_21     EQU     0x00200000
xlli_BIT_22     EQU     0x00400000
xlli_BIT_23     EQU     0x00800000
xlli_BIT_24     EQU     0x01000000
xlli_BIT_25     EQU     0x02000000
xlli_BIT_26     EQU     0x04000000
xlli_BIT_27     EQU     0x08000000
xlli_BIT_28     EQU     0x10000000
xlli_BIT_29     EQU     0x20000000
xlli_BIT_30     EQU     0x40000000
xlli_BIT_31     EQU     0x80000000

;
; UART base address
;
app_FFUART_PHYSICAL_BASE    EQU    0x40100000   ; Full Featured UART base address
app_BTUART_PHYSICAL_BASE    EQU    0x40200000   ; BlueTooth UART base address
app_STUART_PHYSICAL_BASE    EQU    0x40700000   ; Standard UART base address


      END
