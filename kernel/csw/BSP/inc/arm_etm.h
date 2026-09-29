/* 2015 Petteri Aimonen <jpa@git.mail.kapsi.fi>
 * Public domain. */
 
#ifndef ARM_ETM_H
#define ARM_ETM_H

#define     __IO    volatile
#define uint32_t unsigned long

/* ETM Peripheral Register definitions.
 * See here for register documentation:
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ihi0014q/Chdfiagc.html
 *
 * Not all features are supported on Cortex-M3, see here for details:
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0337i/CHDBGEED.html
 *
 * The ETM peripheral has a lot of registers, but these are the main ones:
 * - LAR:       Allow write access to other ETM registers
 * - CR:        Enable/disable tracing
 * - TRIGGER:   Select tracing trigger event
 * - SR:        Current status
 * - TECR1      Select areas of code where to enable trace
 * - TECR2      Select comparator for trace enable
 * - TEEVR      Select event for trace enable
 */
 #if 1
typedef struct
{
    __IO uint32_t CR;           /* Main Control Register */
    __IO uint32_t CCR;          /* Configuration Code Register */
    __IO uint32_t TRIGGER;      /* Trigger Event */
    __IO uint32_t ASICCR;       /* ASIC Control Register */
    __IO uint32_t SR;           /* ETM Status Register */
    __IO uint32_t SCR;          /* System Configuration Register */
    __IO uint32_t TSSCR;        /* TraceEnable Start/Stop Control Register */
    __IO uint32_t TECR2;        /* TraceEnable Control 2 */
    __IO uint32_t TEEVR;        /* TraceEnable Event Register */
    __IO uint32_t TECR1;        /* TraceEnable Control 1 */
    __IO uint32_t FFRR;         /* 0x0A FIFOFULL Region Register */
    __IO uint32_t FFLR;         /* 0x0B FIFOFULL Level Register */
    __IO uint32_t VDEVR;        /* 0x0C ViewData Event Register */
    __IO uint32_t VDCR1;        /* 0x0D ViewData Control 1 */
    __IO uint32_t VDCR2;        /* 0x0E ViewData Control 2 */
    __IO uint32_t VDCR3;        /* 0x0F ViewData Control 3 */
    __IO uint32_t ACVR[16];     /* 0x10+ Address Comparator Value Registers */
    __IO uint32_t ACTR[16];     /* Address Comparator Access Type Registers */
    __IO uint32_t DCVR[16];     /* Data Comparator Value Registers */
    __IO uint32_t DCMR[16];     /* Data Comparator Mask Registers */
    __IO uint32_t CNTRLDVR[4];  /* Counter Reload Value Registers */
    __IO uint32_t CNTENR[4];    /* Counter Enable Registers */
    __IO uint32_t CNTRLDEVR[4]; /* Counter Reload Event Registers */
    __IO uint32_t CNTVR[4];     /* Counter Value Registers */
    __IO uint32_t SQabEVR[6];   /* Sequencer State Transition Event Registers */
    __IO uint32_t RESERVED0;
    __IO uint32_t SQR;          /* Current Sequencer State Register */
    __IO uint32_t EXTOUTEVR[4]; /* External Output Event Registers */
    __IO uint32_t CIDCVR[3];    /* Context ID Comparator Value Registers */
    __IO uint32_t CIDCMR;       /* Context ID Comparator Mask Register */
    __IO uint32_t IMPL[8];      /* Implementation specific registers */
    __IO uint32_t SYNCFR;       /* Synchronization Frequency Register */
    __IO uint32_t IDR;          /* ETM ID Register */
    __IO uint32_t CCER;         /* Configuration Code Extension Register */
    __IO uint32_t EXTINSELR;    /* Extended External Input Selection Register */
    __IO uint32_t TESSEICR;     /* TraceEnable Start/Stop EmbeddedICE Control Register */
    __IO uint32_t EIBCR;        /* EmbeddedICE Behavior Control Register */
    __IO uint32_t TSEVR;        /* Timestamp Event Register, ETMv3.5 */
    __IO uint32_t AUXCR;        /* Auxiliary Control Register, ETMv3.5 */
    __IO uint32_t TRACEIDR;     /* 0x80 CoreSight Trace ID Register */
    __IO uint32_t RESERVED1;
    __IO uint32_t IDR2;         /* ETM ID Register 2 */
    __IO uint32_t RESERVED2[13];
    __IO uint32_t VMIDCVR;      /* VMID Comparator Value Register, ETMv3.5 */
    __IO uint32_t RESERVED3[47];
    __IO uint32_t OSLAR;        /* OS Lock Access Register */
    __IO uint32_t OSLSR;        /* OS Lock Status Register */
    __IO uint32_t OSSRR;        /* OS Save and Restore Register */
    __IO uint32_t RESERVED4;
    __IO uint32_t PDCR;         /* Power Down Control Register, ETMv3.5 */
    __IO uint32_t PDSR;         /* Device Power-Down Status Register */
    __IO uint32_t RESERVED5[762];
    __IO uint32_t ITCTRL;       /* Integration Mode Control Register */
    __IO uint32_t RESERVED6[39];
    __IO uint32_t CLAIMSET;     /* Claim Tag Set Register */
    __IO uint32_t CLAIMCLR;     /* Claim Tag Clear Register */
    __IO uint32_t RESERVED7[2];
    __IO uint32_t LAR;          /* Lock Access Register */
    __IO uint32_t LSR;          /* Lock Status Register */
    __IO uint32_t AUTHSTATUS;   /* Authentication Status Register */
    __IO uint32_t RESERVED8[3];
    __IO uint32_t DEVID;        /* CoreSight Device Configuration Register */
    __IO uint32_t DEVTYPE;      /* CoreSight Device Type Register */
    __IO uint32_t PIDR4;        /* Peripheral ID4 */
    __IO uint32_t PIDR5;        /* Peripheral ID5 */
    __IO uint32_t PIDR6;        /* Peripheral ID6 */
    __IO uint32_t PIDR7;        /* Peripheral ID7 */
    __IO uint32_t PIDR0;        /* Peripheral ID0 */
    __IO uint32_t PIDR1;        /* Peripheral ID1 */
    __IO uint32_t PIDR2;        /* Peripheral ID2 */
    __IO uint32_t PIDR3;        /* Peripheral ID3 */
    __IO uint32_t CIDR0;        /* Component ID0 */
    __IO uint32_t CIDR1;        /* Component ID1 */
    __IO uint32_t CIDR2;        /* Component ID2 */
    __IO uint32_t CIDR3;        /* Component ID3 */
} ETM_Type;

#define ETM_CR_POWERDOWN                (1 << 0)
#define ETM_CR_MONITORCPRT              (1 << 1)
#define ETM_CR_TRACE_DATA               (1 << 2)
#define ETM_CR_TRACE_ADDR               (1 << 3)
#define ETM_CR_PORTSIZE_1BIT            0x00200000
#define ETM_CR_PORTSIZE_2BIT            0x00200010
#define ETM_CR_PORTSIZE_4BIT            0x00000000
#define ETM_CR_PORTSIZE_8BIT            0x00000010
#define ETM_CR_PORTSIZE_16BIT           0x00000020
#define ETM_CR_STALL_PROCESSOR          (1 << 7)
#define ETM_CR_BRANCH_OUTPUT            (1 << 8)
#define ETM_CR_DEBUGREQ                 (1 << 9)
#define ETM_CR_PROGRAMMING              (1 << 10)
#define ETM_CR_ETMEN                    (1 << 11)
#define ETM_CR_CYCLETRACE               (1 << 12)
#define ETM_CR_CONTEXTID_8BIT           0x00004000
#define ETM_CR_CONTEXTID_16BIT          0x00008000
#define ETM_CR_CONTEXTID_32BIT          0x0000C000
#define ETM_CR_CONTEXTID_8BIT           0x00004000
#define ETM_CR_PORTMODE_ONCHIP          0x00000000
#define ETM_CR_PORTMODE_2_1             0x00010000
#define ETM_CR_PORTMODE_IMPL            0x00030000
#define ETM_CR_PORTMODE_1_1             0x00002000
#define ETM_CR_PORTMODE_1_2             0x00022000
#define ETM_CR_PORTMODE_1_3             0x00012000
#define ETM_CR_PORTMODE_1_4             0x00032000
#define ETM_CR_SUPPRESS_DATA            (1 << 18)
#define ETM_CR_FILTER_CPRT              (1 << 19)
#define ETM_CR_DATA_ONLY                (1 << 20)
#define ETM_CR_BLOCK_DEBUGGER           (1 << 22)
#define ETM_CR_BLOCK_SOFTWARE           (1 << 23)
#define ETM_CR_ACCESS                   (1 << 24)
#define ETM_CR_PROCSEL_Pos              25
#define ETM_CR_TIMESTAMP_EN             (1 << 28)
#define ETM_CR_VMID_EN                  (1 << 30)

#define ETM_SR_PROGSTATUS               0x00000002
#define ETM_SR_TRIGSTATUS               0x00000008

#define ETM_TECR1_EXCLUDE               0x01000000
#define ETM_TECR1_TSSEN                 0x02000000

#define ETM_FFRR_EXCLUDE                0x01000000

#define ETM_LAR_KEY                     0xC5ACCE55

#define ETM_TraceMode() ETM->CR &= ~ETM_CR_PROGRAMMING
#define ETM_SetupMode() ETM->CR |= ETM_CR_PROGRAMMING
#endif
#define BIT(n) (1<<(n))
#define EFAULT 1
#define EINVAL 1

#define TRACER_ACCESSED_BIT	0
#define TRACER_RUNNING_BIT	1
#define TRACER_CYCLE_ACC_BIT	2
#define TRACER_ACCESSED		BIT(TRACER_ACCESSED_BIT)
#define TRACER_RUNNING		BIT(TRACER_RUNNING_BIT)
#define TRACER_CYCLE_ACC	BIT(TRACER_CYCLE_ACC_BIT)

#define TRACER_TIMEOUT 100000

/* CoreSight Management Registers */
#define CSMR_LOCKACCESS 0xfb0
#define CSMR_LOCKSTATUS 0xfb4
#define CSMR_AUTHSTATUS 0xfb8
#define CSMR_DEVID	0xfc8
#define CSMR_DEVTYPE	0xfcc
/* CoreSight Component Registers */
#define CSCR_CLASS	0xff4

#define CS_LAR_KEY	0xc5acce55


/* ETM control register, "ETM Architecture", 3.3.1 
#define ETM_CR_STALL_PROCESSOR          0x00000080
#define ETM_CR_ETMEN                    0x00000800
#define ETM_CR_BRANCH_OUTPUT            0x00000100

    ETM->CR = ETM_CR_ETMEN // Enable ETM output port
            | ETM_CR_STALL_PROCESSOR // Stall processor when fifo is full
            | ETM_CR_BRANCH_OUTPUT; // Report all branches
*/
#define ETMR_CTRL		0
#define ETMCTRL_POWERDOWN	1
#define ETMCTRL_PROGRAM		(1 << 10)
#define ETMCTRL_PORTSEL		(1 << 11)
#define ETMCTRL_DO_CONTEXTID	(3 << 14)
#define ETMCTRL_PORTMASK1	(7 << 4)
#define ETMCTRL_PORTMASK2	(1 << 21)
#define ETMCTRL_PORTMASK	(ETMCTRL_PORTMASK1 | ETMCTRL_PORTMASK2)
#define ETMCTRL_PORTSIZE(x) ((((x) & 7) << 4) | (!!((x) & 8)) << 21)
#define ETMCTRL_DO_CPRT		(1 << 1)
#define ETMCTRL_DATAMASK	(3 << 2)
#define ETMCTRL_DATA_DO_DATA	(1 << 2)
#define ETMCTRL_DATA_DO_ADDR	(1 << 3)
#define ETMCTRL_DATA_DO_BOTH	(ETMCTRL_DATA_DO_DATA | ETMCTRL_DATA_DO_ADDR)
#define ETMCTRL_BRANCH_OUTPUT	(1 << 8)
#define ETMCTRL_CYCLEACCURATE	(1 << 12)
#define ETMCTRL_STALL_PROCESSOR (1 << 7)

#define ETMTECR1_EXCLUDE               0x01000000

/* ETM configuration code register */
#define ETMR_CONFCODE		(0x04)

/* ETM trace enable control  register */
#define ETMR_TEC2		(0x07)

/* ETM trace enable event register */
#define ETMR_TEEV		(0x08)

/* ETM trace enable control register */
#define ETMR_TEC1		(0x09)

/* ETM FIFOFULL Region Register */
#define ETMR_FFR		(0x0A)
#define ETM_FFRR_EXCLUDE                0x01000000


/* ETM trace start/stop resource control register */
#define ETMR_TRACESSCTRL	(0x18)

/* ETM trigger event register */
#define ETMR_TRIGEVT		(0x08)

/* address access type register bits, "ETM architecture",
 * table 3-27 */
/* - access type */
#define ETMAAT_IFETCH		0
#define ETMAAT_IEXEC		1
#define ETMAAT_IEXECPASS	2
#define ETMAAT_IEXECFAIL	3
#define ETMAAT_DLOADSTORE	4
#define ETMAAT_DLOAD		5
#define ETMAAT_DSTORE		6
/* - comparison access size */
#define ETMAAT_JAVA		(0 << 3)
#define ETMAAT_THUMB		(1 << 3)
#define ETMAAT_ARM		(3 << 3)
/* - data value comparison control */
#define ETMAAT_NOVALCMP		(0 << 5)
#define ETMAAT_VALMATCH		(1 << 5)
#define ETMAAT_VALNOMATCH	(3 << 5)
/* - exact match */
#define ETMAAT_EXACTMATCH	(1 << 7)
/* - context id comparator control */
#define ETMAAT_IGNCONTEXTID	(0 << 8)
#define ETMAAT_VALUE1		(1 << 8)
#define ETMAAT_VALUE2		(2 << 8)
#define ETMAAT_VALUE3		(3 << 8)
/* - security level control */
#define ETMAAT_IGNSECURITY	(0 << 10)
#define ETMAAT_NSONLY		(1 << 10)
#define ETMAAT_SONLY		(2 << 10)

#define ETMR_COMP_VAL(x)	(0x40 + (x) * 4)
#define ETMR_COMP_ACC_TYPE(x)	(0x80 + (x) * 4)

/* ETM status register, "ETM Architecture", 3.3.2 */
#define ETMR_STATUS		(0x10)
#define ETMST_OVERFLOW		BIT(0)
#define ETMST_PROGBIT		BIT(1)
#define ETMST_STARTSTOP		BIT(2)
#define ETMST_TRIGGER		BIT(3)

#define ETMR_TRACEENCTRL2	0x1c
#define ETMR_TRACEENCTRL1	0x24
#define ETMTE_INCLEXCL		BIT(24)
#define ETMR_TRACEENEVT		0x20
#define ETMCTRL_OPTS		(ETMCTRL_DO_CPRT | \
				ETMCTRL_DATA_DO_ADDR | \
				ETMCTRL_BRANCH_OUTPUT | \
				ETMCTRL_DO_CONTEXTID)
				
#define ETMCTRL_OPTS2		(ETMCTRL_BRANCH_OUTPUT | \
					ETMCTRL_DATA_DO_DATA | \
					ETMCTRL_PORTSEL)

/*
ETMCTRL_STALL_PROCESSOR | 
*/
/* ETM ID register, "ETM Architecture", 3.5.40 */
#define ETMR_ID		(0x79)

/* ETM Trace ID register, "ETM Architecture", 3.5.47 */
#define ETMR_TRACEID		(0x80)

/* ETM management registers, "ETM Architecture", 3.5.24 */
#define ETMMR_OSLAR	0x300
#define ETMMR_OSLSR	0x304
#define ETMMR_OSSRR	0x308
#define ETMMR_PDSR	0x314


/* ETM Lock Access register, "ETM Architecture", 3.5.61 */
#define ETMR_LAR	0x3EC

/* ETM Lock Status register, "ETM Architecture", 3.5.62 */
#define ETMR_LSR	0x3ED

/* ETB registers, "CoreSight Components TRM", 9.3 */
#define ETBR_DEPTH		0x04
#define ETBR_STATUS		0x0c
#define ETBR_READMEM		0x10
#define ETBR_READADDR		0x14
#define ETBR_WRITEADDR		0x18
#define ETBR_TRIGGERCOUNT	0x1c
#define ETBR_CTRL		0x20
#define ETBR_FFSTATUS	0x300
#define ETBR_FORMATTERCTRL	0x304
#define ETBFF_ENFTC		1
#define ETBFF_ENFCONT		BIT(1)
#define ETBFF_FONFLIN		BIT(4)
#define ETBFF_MANUAL_FLUSH	BIT(6)
#define ETBFF_TRIGIN		BIT(8)
#define ETBFF_TRIGEVT		BIT(9)
#define ETBFF_TRIGFL		BIT(10)

#define ETBR_LAR		0xFB0
#define ETBR_LSR		0xFB4


//CoreSight base address: 0xD410_0000
//MTER5 offset: 0x0e, 4k per offset
#define ETM_BASE 0xD410E000
#define ETM_p ((ETM_Type*)ETM_BASE)

#define etm_writel(value, offset) (*(volatile unsigned int *)(ETM_BASE + (offset)))=(value)
#define etm_readl(offset) (*((volatile unsigned int *)(ETM_BASE + (offset))))


#define ETB_BASE 0xD4105000

#define etb_writel(value, offset) (*(volatile unsigned int *)(ETB_BASE + (offset)))=(value)
#define etb_readl(offset) (*((volatile unsigned int *)(ETB_BASE + (offset))))


#define etm_lock(t) do { ETM->LAR = 0; } while (0)
//do { etm_writel(0, ETMR_LAR); } while (0)
#define etm_unlock(t) do { ETM->LAR = CS_LAR_KEY; } while (0)

//	do { etm_writel(CS_LAR_KEY, ETMR_LAR); } while (0)

#define etb_lock(t) do { etb_writel(0, CSMR_LOCKACCESS); } while (0)
#define etb_unlock(t) \
	do { etb_writel(CS_LAR_KEY, CSMR_LOCKACCESS); } while (0)


#define TPIU_BASE 0xD4108000

#define tpiu_writel(value, offset) (*(volatile unsigned int *)(TPIU_BASE + (offset)))=(value)
#define tpiu_readl(offset) (*((volatile unsigned int *)(TPIU_BASE + (offset))))

#define tpiu_lock() do { tpiu_writel(0, CSMR_LOCKACCESS); } while (0)
#define tpiu_unlock() \
	do { tpiu_writel(CS_LAR_KEY, CSMR_LOCKACCESS); } while (0)

#define FUNNEL_BASE 0xD4107000

#define funnel_writel(value, offset) (*(volatile unsigned int *)(FUNNEL_BASE + (offset)))=(value)
#define funnel_readl(offset) (*((volatile unsigned int *)(FUNNEL_BASE + (offset))))

#define funnel_lock() do { funnel_writel(0, CSMR_LOCKACCESS); } while (0)
#define funnel_unlock() \
	do { funnel_writel(CS_LAR_KEY, CSMR_LOCKACCESS); } while (0)

void ETM_init(void);
int etb_trace_start(unsigned long start, unsigned long stop);
int etb_trace_stop(void);
void etb_dump(void);

#endif
