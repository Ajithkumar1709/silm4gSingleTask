#ifndef __UART_DRV_H__
#define __UART_DRV_H__

#include "UART_common_type.h"
#include "UART_HW2.h"

#define UART_DRV_DMA_RX_BUFFER_SIZE 1024
#define UART_DRV_DMA_TX_BUFFER_SIZE 1024

typedef int (*uartdrv_cb)(uint32 port_id);
typedef int (*uartdrv_dma_rx_cb)(char *buf, int size);
typedef void (*uartdrv_hisr_cb)(void);

typedef enum
{
    uartdrv_rx = 0,
    uartdrv_tx,
    uartdrv_max_dir,
}uartdrv_uartdir;

typedef enum
{
    uartdrv_int_none = 0,
    uartdrv_rx_int,
    uartdrv_tx_int,
    uartdrv_eor_int,
    uartdrv_all_int,
    uartdrv_int_max,
}uartdrv_irqtype;

typedef struct
{
    uint32_t port_id;
    uint32_t fifo;
    uint32_t dma;							//if set 1, dma_rx_callback must be set to get rx data, don't use uartdrv_recv_data().
    uint32_t loopback;
    uartdrv_irqtype int_tpye;       
    uint32_t highspeed;						//set 1 when baudrate>=1842000
    uint32_t flowctrl;
    uint32_t baudrate;
    uint32_t datawidth;
    uint32_t parity;
	uint32_t stopbit;						//0: 1 stopbit, default; 1: 1.5 or 2 stopbit
    uartdrv_cb rx_indicate_callback;  		//irq mode: indicate rx data; use when dma=0
    uartdrv_cb tx_complete_callback;  		//irq mode: indicate tx complete
    uartdrv_dma_rx_cb dma_rx_callback; 		//dma mode: to get rx data from dma buffer
    unsigned char usedrvbuffer;     		//must set when dma=1; 1:use uartdrv's local buffer(cached,dynamic memory,UART_DRV_DMA_RX_BUFFER_SIZE);0:use external noncache buffer    
    unsigned char *tx_dma_noncache_buffer; 	//must set when dma=1 && (usedrvbuffer==0)
    unsigned char *rx_dma_noncache_buffer; 	//must set when dma=1 && (usedrvbuffer==0)
    int tx_dma_noncache_buffer_size;    	//must set when dma=1 && (usedrvbuffer==0),<8192
    int rx_dma_noncache_buffer_size;    	//must set when dma=1 && (usedrvbuffer==0),<8192
    uint32_t priv;  						//private data for device
    uartdrv_cb autobaudrate_detected_callback; //if baudrate = 0, callback when baudrate was detected    
    int workinlowpowermode; //In CraneL A0,SCS mode,if want to use UART RX to wakeup SOC, only support baudrate(9600,38400,57600,115200) 
    int txzerocpy;	//don't copy to buffer for tx, if txzerocpy=1 & usedrvbuffer = 1, driver doesn't alloc memory for tx buffer 
    int diagfunc;	//use output diaglog by uart
}uartdrv_cfg;

typedef struct uartdrv_uartDmaRegister
{
    unsigned long DCSR;
} uartdrv_uartDmaRegisterT;

typedef struct uartdrv_uartDmaTxInfoStat
{
    unsigned long totalTxCnt;  // counter of tx
    unsigned long intrCnt;     // counter of intrrupt
    unsigned long toCnt;       // counter of timeout
    unsigned long lastLoopCnt;     // counter of loop after tx timeout at last
    unsigned long totalLoopCnt;     // counter of total loop after tx timeout
    unsigned long startTick;     // tick of start uart send
    unsigned long startOSTick;   // OS tick of start uart send
    unsigned long toTick;     // tick of uart send data timeout
    unsigned long toOSTick;     // OS tick of uart send data timeout
    struct uartdrv_uartDmaRegister reg; // dma register info
} uartdrv_uartDmaTxInfoStatT;

typedef struct uartdrv_uartDmaRxInfoStat
{
    unsigned long enDmaCnt;    // counter of enabel dma in uart rx intr, which equal to counter of entring to uart rx intr
    unsigned long dmaHisrCnt;  // counter of entring to dma hisr
} uartdrv_uartDmaRxInfoStatT;

typedef struct uartdrv_uartDmaInfoStat
{
	struct uartdrv_uartDmaTxInfoStat tx;
    struct uartdrv_uartDmaRxInfoStat rx;
} uartdrv_uartDmaInfoStatT;


//auto detect support 300,1200,4800,9600,14400,19200,38400,57600,115200,230400,460800,921600
#define BAUDRATE_AUTODETECT 0           
#define BAUDRATE_9600       9600
#define BAUDRATE_14400      14400
#define BAUDRATE_19200      19200
#define BAUDRATE_38400      38400
#define BAUDRATE_57600      57600
#define BAUDRATE_115200     115200
#define BAUDRATE_230400     230400
#define BAUDRATE_460800     460800
#define BAUDRATE_921600     921600
#define BAUDRATE_1000000    1000000
#define BAUDRATE_1125000    1125000
#define BAUDRATE_1842000    1842000
#define BAUDRATE_2000000    2000000
#define BAUDRATE_2100000    2100000
#define BAUDRATE_3000000    3000000
#define BAUDRATE_3686400    3686400

typedef enum
{
    UART_PARITY_NONE = 0,
    UART_PARITY_ODD  = 1,
    UART_PARITY_EVEN = 3,
} UART_PARITY_TYPE;

typedef enum
{
    UART_DATA_5 = 0,
    UART_DATA_6 = 1,
    UART_DATA_7 = 2,
    UART_DATA_8 = 3,
} UART_DATA_WIDTH;

typedef enum
{
    UART_ONE_STOPBIT = 0,
    UART_ONE_HALF_OR_TWO_STOPBITS = 1,
}UART_STOPBIT;

typedef struct
{
    uint32_t base_addr;
    uint32_t apbc_base;
    uint32_t irq;
    uint32_t fpga;
} uartdrv_glb_info;

void uartdrv_init(uartdrv_cfg *port);
void uartdrv_basic_init(uartdrv_cfg *port);
void uartdrv_irq_init(uartdrv_cfg *port);
uint32 uartdrv_send_data(uint32 port_id, uint8 *data, uint32_t size);
uint32 uartdrv_recv_data(uint32 port_id, uint8 *pbuf, uint32_t size);
void uartdrv_set_baudrate(uint32 port_id, uint32_t rate);
void uartdrv_enable (uint32 port_id, uint32 enable);
void uartdrv_change_to_115200(uint32 port_id);
void uartdrv_change_to_921600(uint32 port_id);
void uartdrv_change_to_3000000(uint32 port_id);
void uartdrv_enable_flowctrl (uint32 port_id, uint32 enable);
void uartdrv_rts_ctl(uint32 port_id, uint32 enable);
void uartdrv_dma_enable(uint32 port_id, uint32 enable);
void uartdrv_mask_RxInt(uint32 port_id, uint32 enable);
int uartdrv_get_dma_rx_channel(uint32 port_id);
void uartdrv_fifo_control (uint32 port_id, uint32 level, uint32 bwidth, uint32 trailingbyte, uint32 fenable);
int uartdrv_rts_is_enable(uint32 port_id);
uint32 uartdrv_get_private_data(uint32 port_id);
uint32 uartdrv_get_baudrate(uint32 port_id);
void uartdrv_dma_irq_preprocess(uint32_t DINT);

#endif

