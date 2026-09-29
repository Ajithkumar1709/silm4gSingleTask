#ifndef __UART_HW2_H__
#define __UART_HW2_H__

#define MAX_UART_PORT  4

#define AP_UART1_BASE 0xD4017000UL
#define AP_UART2_BASE 0xD4018000UL
#define AP_UART3_BASE 0xD401F000UL
#define AP_UART4_BASE 0xD401F800UL

#define UART1_IRQ		(27)
#define UART2_IRQ		(59)
#define UART3_IRQ		(95)
#define UART4_IRQ       (34)

#define UART1_ID		0
#define UART2_ID		1
#define UART3_ID		2
#define UART4_ID		3

#define BIT_0 (1 << 0)
#define BIT_1 (1 << 1)
#define BIT_2 (1 << 2)
#define BIT_3 (1 << 3)
#define BIT_4 (1 << 4)
#define BIT_5 (1 << 5)
#define BIT_6 (1 << 6)
#define BIT_7 (1 << 7)
#define BIT_8 (1 << 8)
#define BIT_9 (1 << 9)

#define	APBC_UART_CLK_RST_APBCLK    BIT_0	/* UART APB Bus Clock Enable/Disable */
#define	APBC_UART_CLK_RST_FNCLK     BIT_1	/* UART Functional Clock Enable/Disable */
#define	APBC_UART_CLK_RST_RST       BIT_2	/* UART Reset Generation */
#define	APBC_UART_CLK_RST_FNCLKSEL  BIT_4	/* Functional Clock Select,bit4-6 */

#define	APBC_UART_CLK_RST_FNCLKSEL_MASK  (~(0x7<<4))	/* Functional Clock Select,bit4-6 */

#define APBC_UART_CLK_FNCLK_HIGH		(58500000)	//clock for high speed mode
#define APBC_UART_CLK_FNCLK_REGULAR		(14745600)	//clock for normal speed mode
#define APBC_UART_CLK_FNCLK_FPGA		(13000000)	//clock for normal speed mode on FPGA

#define UART_FIFO_DEPTH		64

#define UART_DATA_OK		0
#define UART_NONE_DATA		-1
#define UART_DATA_ERROR		-2

#ifndef UART_NEW_VERSION
#define BT_UART2_RX_DMA_DEV DMAC_UART2_RX
#define BT_UART2_TX_DMA_DEV DMAC_UART2_TX

#define BT_UART3_RX_DMA_DEV DMAC_UART3_RX
#define BT_UART3_TX_DMA_DEV DMAC_UART3_TX

#define BT_UART4_RX_DMA_DEV DMAC_UART4_RX
#define BT_UART4_TX_DMA_DEV DMAC_UART4_TX
#else
#define UART1_RX_DMA_DEV DMAC_UART1_RX
#define UART1_TX_DMA_DEV DMAC_UART1_TX

#define UART2_RX_DMA_DEV DMAC_UART2_RX
#define UART2_TX_DMA_DEV DMAC_UART2_TX

#define UART3_RX_DMA_DEV DMAC_UART3_RX
#define UART3_TX_DMA_DEV DMAC_UART3_TX

#define UART4_RX_DMA_DEV DMAC_UART4_RX
#define UART4_TX_DMA_DEV DMAC_UART4_TX
#endif //UART_NEW_VERSION

#define UART_RBR	0x0
#define UART_IER	0x4
#define UART_FCR	0x8
#define UART_LCR	0xC
#define UART_MCR	0x10
#define UART_LSR	0x14
#define UART_MSR	0x18
#define UART_SCR	0x1C
#define UART_ISR	0x20
#define UART_FOR	0x24
#define UART_ABR	0x28
#define UART_ACR	0x2C
#define UART_THR	UART_RBR
#define UART_IIR	UART_FCR
#define UART_DLL	UART_RBR
#define UART_DLH	UART_IER

/*
 * These are the definitions for the FIFO Control Register
 */
#define UART_FCR_FIFO_EN	0x01	/* Fifo enable */
#define UART_FCR_CLEAR_RCVR	0x02	/* Clear the RCVR FIFO */
#define UART_FCR_CLEAR_XMIT	0x04	/* Clear the XMIT FIFO */
#define UART_FCR_DMA_SELECT	0x08	/* For DMA applications */
#define UART_FCR_TRIGGER_MASK	0xC0	/* Mask for the FIFO trigger range */
#define UART_FCR_TRIGGER_1	0x00	/* Mask for trigger set at 1 */
#define UART_FCR_TRIGGER_4	0x40	/* Mask for trigger set at 4 */
#define UART_FCR_TRIGGER_8	0x80	/* Mask for trigger set at 8 */
#define UART_FCR_TRIGGER_14	0xC0	/* Mask for trigger set at 14 */

#define UART_FCR_RXSR		0x02	/* Receiver soft reset */
#define UART_FCR_TXSR		0x04	/* Transmitter soft reset */

/*
 * These are the definitions for the Modem Control Register
 */
#define UART_MCR_DTR		0x01	/* Data Terminal Ready */
#define UART_MCR_RTS		0x02	/* Request to Send */
#define UART_MCR_OUT1		0x04	/* Out 1 */
#define UART_MCR_OUT2		0x08	/* Out 2 */
#define UART_MCR_LOOP		0x10	/* Enable loopback test mode */
#define UART_MCR_AFE		0x20	/* Auto-flow Control Enable */

#ifdef CHIP_AQUILAC
#define UART_MCR_EOR_INT_MASK	0x40	/* mask bit for eor interrupt */
#define UART_MCR_EPT_RXREQ_EN	0x80	/* dma_rxreq for empty rx fifo enable */
#endif

#define UART_MCR_DMA_EN	0x04
#define UART_MCR_TX_DFR	0x08

/*
 * These are the definitions for the Line Control Register
 *
 * Note: if the word length is 5 bits (UART_LCR_WLEN5), then setting
 * UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.
 */
#define UART_LCR_WLS_MSK 0x03	/* character length select mask */
#define UART_LCR_WLS_5	0x00	/* 5 bit character length */
#define UART_LCR_WLS_6	0x01	/* 6 bit character length */
#define UART_LCR_WLS_7	0x02	/* 7 bit character length */
#define UART_LCR_WLS_8	0x03	/* 8 bit character length */
#define UART_LCR_STB	0x04	/* Number of stop Bits, off = 1, on = 1.5 or 2) */
#define UART_LCR_PEN	0x08	/* Parity eneble */
#define UART_LCR_EPS	0x10	/* Even Parity Select */
#define UART_LCR_STKP	0x20	/* Stick Parity */
#define UART_LCR_SBRK	0x40	/* Set Break */
#define UART_LCR_BKSE	0x80	/* Bank select enable */
#define UART_LCR_DLAB	0x80	/* Divisor latch access bit */

/*
 * These are the definitions for the Line Status Register
 */
#define UART_LSR_DR	0x01	/* Data ready */
#define UART_LSR_OE	0x02	/* Overrun */
#define UART_LSR_PE	0x04	/* Parity error */
#define UART_LSR_FE	0x08	/* Framing error */
#define UART_LSR_BI	0x10	/* Break */
#define UART_LSR_THRE	0x20	/* Xmit holding register empty */
#define UART_LSR_TEMT	0x40	/* Xmitter empty */
#define UART_LSR_ERR	0x80	/* Error */

#define UART_MSR_DCD	0x80	/* Data Carrier Detect */
#define UART_MSR_RI		0x40	/* Ring Indicator */
#define UART_MSR_DSR	0x20	/* Data Set Ready */
#define UART_MSR_CTS	0x10	/* Clear to Send */
#define UART_MSR_DDCD	0x08	/* Delta DCD */
#define UART_MSR_TERI	0x04	/* Trailing edge ring indicator */
#define UART_MSR_DDSR	0x02	/* Delta DSR */
#define UART_MSR_DCTS	0x01	/* Delta CTS */

/*
 * These are the definitions for the Interrupt Identification Register
 */
#define UART_IIR_NO_INT	0x01	/* No interrupts pending */
#define UART_IIR_ID	0x06	/* Mask for the interrupt ID */

#define UART_IIR_MSI	0x00	/* Modem status interrupt */
#define UART_IIR_THRI	0x02	/* Transmitter holding register empty */
#define UART_IIR_RDI	0x04	/* Receiver data interrupt */
#define UART_IIR_RLSI	0x06	/* Receiver line status interrupt */
#define UART_IIR_TOD	0x08	/* Time Out Detected */
#define UART_IIR_EOC	0x20	/* DMA End of Descriptor Chain */
#define UART_IIR_EOR	0x100	/* UART End of receive Status */

/*
 * These are the definitions for the Interrupt Enable Register
 */
/*	UART_IER	0x0004	UART Interrupt Enable Register */

#define	UART_IER_EORIE		BIT_9	/* eor interrupt enable */
#define	UART_IER_HSE		BIT_8	/* High Speed UART Enable */
#define	UART_IER_DMAE		BIT_7	/* DMA Requests Enable */
#define	UART_IER_UUE		BIT_6	/* UART Unit Enable */
#define	UART_IER_NRZE		BIT_5	/* NRZ Coding Enable */
#define	UART_IER_RTOIE		BIT_4	/* Receiver Time-out Interrupt Enable */
#define	UART_IER_MIE		BIT_3	/* Modem Interrupt Enable */
#define	UART_IER_RLSE		BIT_2	/* Receiver Line Status Interrupt Enable */
#define	UART_IER_TIE		BIT_1	/* Transmit Data Request Interrupt Enable */
#define	UART_IER_RAVIE		BIT_0	/* Receiver Data Available Interrupt Enable */

#define	APBC_BASE               (0xD4015000)
#define	APBC_UART1_CLK_RST		(APBC_BASE+0x00)	/* 32 bit       APBClock Clock/Reset Control
								 * Register for UART 1*/
#define	APBC_UART2_CLK_RST		(APBC_BASE+0x04)	/* 32 bit       APBClock Clock/Reset Control
								 * Register for UART 2*/
#define	APBC_UART3_CLK_RST		(APBC_BASE+0x84)	/* 32 bit       APBClock Clock/Reset Control
								 * Register for UART 3, for BT use*/
#define	APBC_UART4_CLK_RST		(APBC_BASE+0x8C)	/* 32 bit       APBClock Clock/Reset Control
                                 * Register for UART 3, for BT use*/

#define APBC_AIB_CLK_RST		(APBC_BASE+0x3C)	//AIB bus clock and function enable/disable

#define	PMU_ACGR                (0XD4051024)		/* Application Clock Gating Register */
#define	PMU_ACGR_AP_FUART     	(1<<8)      		/* 52M clock */
#define	PMU_ACGR_AP_SUART     	(1<<1)      		/* Enable the functional M/N slow UART clock output */
#define	PMU_ACGR_AP_TWSI        (1<<6)      		/* Enable the 32M clock of the functional TWSI clock output
														of the main  to the Application Processor APB portion */

#define	PMU_CCGR                (0XD4050024)		/* CP Clock Gating Register */


#define	PMU_SUCCR               (0XD4050014)		/* Clock Generation Control Register */
#define	PMU_SUCCR_UARTDIVD_MASK	(0x1FFF<<0) 		/* UARTDIVD */
#define	PMU_SUCCR_UARTDIVD_BASE	0           		/* UARTDIVD */
#define	PMU_SUCCR_UARTDIVN_MASK	(0x1FFF<<16)		/* UARTDIVN */
#define	PMU_SUCCR_UARTDIVN_BASE	16          		/* UARTDIVN */

#ifndef UART_NEW_VERSION
#ifdef BT_SUPPORT
#ifndef BT_IPC
#define BT_UART_DMA_TX_ENABLE
#define BT_UART_DMA_RX_ENABLE
#endif
#endif

#if (defined BT_UART_DMA_TX_ENABLE) || (defined BT_UART_DMA_RX_ENABLE)
#include "xllp_dmac.h"
#include "UART_HW2.h"
#include "dma.h"
#include "UART_CommonControl.h"
#include "bt_api.h"
#include "UART_common_type.h"

typedef struct btuartDmaRegister
{
    UINT32 DCSR;
} btuartDmaRegisterT;

typedef struct btuartDmaTxInfoStat
{
    UINT32 totalTxCnt;  // counter of tx
    UINT32 intrCnt;     // counter of intrrupt
    UINT32 toCnt;       // counter of timeout
    UINT32 lastLoopCnt;     // counter of loop after tx timeout at last
    UINT32 totalLoopCnt;     // counter of total loop after tx timeout
    UINT32 startTick;     // tick of start uart send
    UINT32 startOSTick;   // OS tick of start uart send
    UINT32 toTick;     // tick of uart send data timeout
    UINT32 toOSTick;     // OS tick of uart send data timeout
    struct btuartDmaRegister reg; // dma register info
} btuartDmaTxInfoStatT;

typedef struct btuartDmaRxInfoStat
{
    UINT32 enDmaCnt;    // counter of enabel dma in uart rx intr, which equal to counter of entring to uart rx intr
    UINT32 dmaHisrCnt;  // counter of entring to dma hisr
} btuartDmaRxInfoStatT;

typedef struct btuartDmaInfoStat
{
	struct btuartDmaTxInfoStat tx;
    struct btuartDmaRxInfoStat rx;
} btuartDmaInfoStatT;
#endif

#ifdef GPS_SUPPORT
#define GPS_UART_DMA_TX_ENABLE
#define GPS_UART_DMA_RX_ENABLE
#endif

#if (defined GPS_UART_DMA_TX_ENABLE) || (defined GPS_UART_DMA_RX_ENABLE)
#include "UART_common_type.h"
#include "UART_CommonControl.h"

typedef struct gpsuartDmaRegister
{
    UINT32 DCSR;
} gpsuartDmaRegisterT;

typedef struct gpsuartDmaTxInfoStat
{
    UINT32 totalTxCnt;  // counter of tx
    UINT32 intrCnt;     // counter of intrrupt
    UINT32 toCnt;       // counter of timeout
    UINT32 lastLoopCnt;     // counter of loop after tx timeout at last
    UINT32 totalLoopCnt;     // counter of total loop after tx timeout
    UINT32 startTick;     // tick of start uart send
    UINT32 startOSTick;   // OS tick of start uart send
    UINT32 toTick;     // tick of uart send data timeout
    UINT32 toOSTick;     // OS tick of uart send data timeout
    struct gpsuartDmaRegister reg; // dma register info
} gpsuartDmaTxInfoStatT;

typedef struct gpsuartDmaRxInfoStat
{
    UINT32 enDmaCnt;    // counter of enabel dma in uart rx intr, which equal to counter of entring to uart rx intr
    UINT32 dmaHisrCnt;  // counter of entring to dma hisr
} gpsuartDmaRxInfoStatT;

typedef struct gpsuartDmaInfoStat
{
    struct gpsuartDmaTxInfoStat tx;
    struct gpsuartDmaRxInfoStat rx;
} gpsuartDmaInfoStatT;

#endif



#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#ifdef BT_SUPPORT
void bt_uart_enable_flowctrl (unsigned int port_id, unsigned int enable);

void bt_uart_change_to_115200(uint32 port_id);

void bt_uart_change_to_921600(unsigned int port_id);

void bt_uart_change_to_3000000(unsigned int port_id);

void bt_uart_enable_flowctrl (unsigned int  port_id, unsigned int enable);

void bt_uart_dma_enable (unsigned int port_id, unsigned int enable);
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif //UART_NEW_VERSION
#endif
