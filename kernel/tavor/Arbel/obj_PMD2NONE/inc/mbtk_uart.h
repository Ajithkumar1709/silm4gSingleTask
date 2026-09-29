
#ifndef __MBTKUART_H__
#define __MBTKUART_H__

typedef enum   /* The number of ports in the UART  */
{
    OL_UART_PORT_FFUART,
    OL_UART_PORT_BTUART,
    OL_UART_PORT_STUART,
    OL_UART_PORT_UART4,
#ifdef MBTK_CDC_UART_SUPPORT
	OL_UART_PORT_CDCUART,
#endif
    OL_NUMBER_OF_PORTS
}MBTK_UART_Port;

typedef enum     /* The Operation Mode that the UART could work */
{
    OL_UART_BYTE_CTL,              /* non fifo mode */
    OL_UART_FIFO_CTL,              /*  fifo mode */
    OL_UART_DMA_CTL                /* DMA mode */
}OL_UART_OpMode;


typedef enum   /* All the UART Baud Rate that the UART Package supplay */
{
    OL_UART_BAUD_150       = 150,
    OL_UART_BAUD_300       = 300,
    OL_UART_BAUD_600       = 600,
    OL_UART_BAUD_1200      = 1200,
    OL_UART_BAUD_2400      = 2400,
    OL_UART_BAUD_3600      = 3600,
    OL_UART_BAUD_4800      = 4800,
    OL_UART_BAUD_7200      = 7200,
    OL_UART_BAUD_9600      = 9600,
    OL_UART_BAUD_14400     = 14400,
    OL_UART_BAUD_19200     = 19200,
    OL_UART_BAUD_28800     = 28800,
    OL_UART_BAUD_38400     = 38400,
    OL_UART_BAUD_57600     = 57600,
    OL_UART_BAUD_115200    = 115200,
    OL_UART_BAUD_230400    = 230400,
    OL_UART_BAUD_256000    = 256000,
    OL_UART_BAUD_460800    = 460800,
    OL_UART_BAUD_921600    = 921600,
    OL_UART_MAX_NUM_BAUD
}OL_UART_BaudRates;

typedef enum  /* The Word Len of the UART Frame Format  */
{
    OL_UART_WORD_LEN_5,                /* set Word Lengto to 5 Bits         */
    OL_UART_WORD_LEN_6,                /* set Word Lengto to 6 Bits         */
    OL_UART_WORD_LEN_7,                /* set Word Lengto to 7 Bits         */
    OL_UART_WORD_LEN_8                 /* set Word Lengto to 8 Bits         */
}OL_UART_WordLen;


typedef enum  /* The Stop Bits of the UART Frame Format */
{
    OL_UART_ONE_STOP_BIT,
    OL_UART_ONE_HALF_OR_TWO_STOP_BITS
}OL_UART_StopBits;

typedef enum  /* The Parity Bits of the UART Frame Format */
{
	OL_UART_NO_PARITY_BITS = 0,
	OL_UART_ODD_PARITY_SELECT = 1,
	OL_UART_EVEN_PARITY_SELECT = 3,
}OL_UART_ParityTBits;

typedef enum
{
	OL_UART_CTL_CLEAR_RX,
	OL_UART_CTL_CLEAR_TX,
	OL_UART_CTL_RX_STATUS,
	OL_UART_CTL_TX_STATUS,
}OL_UART_IO_CTL;

typedef enum
{
	OL_UART_DELAY_MODE1,
	OL_UART_DELAY_MODE2,
	OL_UART_DELAY_MODE_MAX,
}OL_UART_DELAY_MODE;

typedef void (*OL_UART_CB)(MBTK_UART_Port p);


typedef struct   /* This is structure of the UART Configuration  */
{
    OL_UART_OpMode              opMode;             /* fifo mode, non fifo mode or DMA for basic interface*/
    OL_UART_BaudRates	     baudRate;			/* the rate of the transmit and the receive up to 111520 (default - 9600).*/
    OL_UART_WordLen	     numDataBits;		/* 5, 6, 7, or 8 number of data bits in the UART data frame (default - 8). */
    OL_UART_ParityTBits	     parityBitType;		/* Even, Odd or no-parity bit type in the UART data frame (default - Non). */
	OL_UART_StopBits         stopBit;      //0  one  1  ONE_HALF 
    bool                    flowControl;       /* enable Auto flow Control - TRUE, disable Auto flow Control - FALSE  */
	bool    			is_int;
	OL_UART_CB   rd_cb;
	OL_UART_CB   td_cb;
}OL_UART_DCB;

typedef enum	// change the order -1 to +
{
    OL_UART_RC_OK                              =   1,      /* 1 - no errors                                            */

    OL_UART_RC_PORT_NUM_ERROR                  =   -100,   /* -100 - Error in the UART port number                     */
    OL_UART_RC_NO_DATA_TO_READ,                            /* -99 -  Eror no data to read from the FIFO UART           */
    OL_UART_RC_ILLEGAL_BAUD_RATE,                          /* -98 -  Error in the UART Bayd Rate                       */
    OL_UART_RC_UART_PARITY_BITS_ERROR,                     /* -97 - Error in parity bit                                */
    OL_UART_RC_UART_ONE_STOP_BIT_ERROR,                    /* -96 - Error in one stop bit                              */
    OL_UART_RC_ONE_HALF_OR_TWO_STOP_BIT_ERROR,             /* -95 - Error in two stop bit                              */
    OL_UART_RC_BAD_INTERFACE_TYPE,                         /* -94 - Error in the Interface Type                        */
    OL_UART_RC_UART_NOT_AVAILABLE,                         /* -93 - Error in try to open UART that is open             */
    OL_UART_RC_NO_DATA_TO_WRITE,                           /* -92 - Error No data to writ the len = 0                  */
    OL_UART_RC_NOT_ALL_BYTE_WRITTEN,                       /* -91 - Error Not all the Byte write to the UART FIFO      */
    OL_UART_RC_ISR_ALREADY_BIND,                           /* -90 - Error try to bind ISR for Basic Interface          */
    OL_UART_RC_WRONG_ISR_UNBIND,                           /* -89 - Error in the UnBind ISR for Basic Interface        */
    OL_UART_RC_FIFO_NOT_EMPTY,                             /* -88 - Error, the UART FIFO not empty                     */
    OL_UART_RC_UART_OPEN,                                  /* -87 - Error try chance the configurr when the UART open  */
    OL_UART_RC_GPIO_ERR,                                   /* -86 - Error in the Configure of the GPIO                 */
    OL_UART_RC_IRDA_CONFIG_ERR                             /* -85 - Illegal IrDA configuration                         */
}OL_UART_ReturnCode;
	


OL_UART_ReturnCode ol_Uart_Open(MBTK_UART_Port portNumber);
OL_UART_ReturnCode ol_Uart_Close(MBTK_UART_Port portNumber);
OL_UART_ReturnCode ol_Uart_Write(MBTK_UART_Port portNumber, const unsigned char *data, unsigned length);
OL_UART_ReturnCode ol_Uart_Read(MBTK_UART_Port portNumber, unsigned char *data, unsigned length, unsigned short *read_len);
OL_UART_ReturnCode ol_Uart_GetDcb(MBTK_UART_Port portNumber,OL_UART_DCB *dcb);
OL_UART_ReturnCode ol_Uart_SetDcb(MBTK_UART_Port portNumber,OL_UART_DCB *dcb);
OL_UART_ReturnCode ol_Uart_Control(MBTK_UART_Port portNumber,OL_UART_IO_CTL cmd,void *parma);
OL_UART_ReturnCode ol_Uart_Rx_Seting(MBTK_UART_Port portNumber,unsigned char delay_mode,unsigned int time);

#endif

