/** 
* @file         simcom_uart.h 
* @brief        SIMCom OpenLinux UART API
* @author       HT
* @date         2019/2/13
* @version      V1.0.0 
* @par Copyright (c):  
*               SIMCom Co.Ltd 2003-2019
* @par History: 1:Create         
*   
*/

#ifndef SIMCOMUART_H
#define SIMCOMUART_H

#include "simcom_gpio.h"
#include "mbtk_uart.h"

typedef SC_GPIOReturnCode GPIOReturnCode;
typedef unsigned char   UINT8;
typedef unsigned short  UINT16;
//typedef unsigned long   UINT32;


#define NUMBER_OF_CUS_UART  1
#define CUS_UART 0

/****************************************************************************
    Define enum  
*****************************************************************************/

typedef enum   /* The number of ports in the UART  */
{
    SC_UART = OL_UART_PORT_STUART,
    SC_UART2 = OL_UART_PORT_FFUART,
    SC_UART3 = OL_UART_PORT_BTUART,
    SC_UART4 = OL_UART_PORT_UART4,
    SC_NUMBER_OF_PORTS
}SC_Uart_Port_Number;


typedef enum
{
    SC_UART_RETURN_CODE_OK = 0,
    SC_UART_RETURN_CODE_ERROR = -1
}SC_Uart_Return_Code;

typedef enum
{
    SC_UART_RX_IDLE,
    SC_UART_RX_BUSY
}SC_Uart_Rx_Status;

typedef enum
{
    SC_UART_OPEN,
    SC_UART_CLOSE,
}SC_Uart_Control;

typedef enum
{
    GPIO1
}Module_GPIONumbers;


typedef enum
{
    SC_UART_READY_READ = 1,
    SC_UART_READ_DONE ,
    SC_UART_READY_WRITE,
    SC_UART_EVENT_MAX
}SC_Uart_Event;

typedef enum
{
    SC_RX_BUF_LEN_256 = 256,    /*Only receive 256 Bytes every time*/
    SC_RX_BUF_LEN_512 = 512,    /*Only receive 512 Bytes every time*/
    SC_RX_BUF_LEN_1024 = 1024,  /*Only receive 1024 Bytes every time*/
    SC_RX_BUF_LEN_2048 = 2048   /*Only receive 2048 Bytes every time*/
}SC_RX_BUF_LEN_MAX;

typedef enum   /* All the UART Baud Rate that the UART Package supplay */
{
#ifdef  _QT_
	/* This baud rate is not supported on any "real" platform.
	   It can only be used on QT.
	*/
	SC_UART_BAUD_110       = 110,
#endif
    SC_UART_BAUD_150       = 150,
    SC_UART_BAUD_300       = 300,
    SC_UART_BAUD_600       = 600,
    SC_UART_BAUD_1200      = 1200,
    SC_UART_BAUD_2400      = 2400,
    SC_UART_BAUD_3600      = 3600,
    SC_UART_BAUD_4800      = 4800,
    SC_UART_BAUD_7200      = 7200,
    SC_UART_BAUD_9600      = 9600,
    SC_UART_BAUD_14400     = 14400,
    SC_UART_BAUD_19200     = 19200,
    SC_UART_BAUD_28800     = 28800,
    SC_UART_BAUD_38400     = 38400,
    SC_UART_BAUD_57600     = 57600,
    SC_UART_BAUD_115200    = 115200,
    SC_UART_BAUD_230400    = 230400,
    SC_UART_BAUD_460800    = 460800,
    SC_UART_BAUD_921600    = 921600,
    SC_UART_BAUD_1842000   = 1842000,
    SC_UART_BAUD_3686400   = 3686400,
    SC_UART_MAX_NUM_BAUD
}SC_UART_BaudRates;



typedef enum  /* The Word Len of the UART Frame Format  */
{
    SC_UART_WORD_LEN_5,                /* set Word Lengto to 5 Bits         */
    SC_UART_WORD_LEN_6,                /* set Word Lengto to 6 Bits         */
    SC_UART_WORD_LEN_7,                /* set Word Lengto to 7 Bits         */
    SC_UART_WORD_LEN_8                 /* set Word Lengto to 8 Bits         */
}SC_UART_WordLen;

typedef enum   /* The Stop Bits of the UART Frame Format */
{
    SC_UART_ONE_STOP_BIT,
    SC_UART_ONE_HALF_OR_TWO_STOP_BITS
}SC_UART_StopBits;

typedef enum  /* The Parity Bits of the UART Frame Format */
{
    SC_UART_NO_PARITY_BITS,
    SC_UART_EVEN_PARITY_SELECT,
    SC_UART_ODD_PARITY_SELECT
}SC_UART_ParityTBits;

typedef enum  /*The type of flow control*/
{
    SC_UART_FLOWCONTROL_NONE = 0x00,
    SC_UART_FLOWCONTROL_RTS  = 0x01,
    SC_UART_FLOWCONTROL_CTS  = 0x02,
    SC_UART_FLOWCONTROL_FULL = 0x03,  //RTS&CTS    
    SC_UART_FLOWCONTROL_MAX  = 0xFF
}SC_UART_FlowControl_state;

typedef enum
{
    SC_RTS_NONE=-1,
    SC_RTS_DEASSERT=0,
    SC_RTS_ASSERT=1,
    SC_RTS_AUTO=2,
}SC_UartRtsControlType;

/****************************************************************************
    Define struct 
*****************************************************************************/
typedef struct SCrxDataMsg
{
    UINT8 * data;
    UINT32 length;
}SCrxDataMsg;

typedef struct SCuartConfiguration
{
    SC_UART_BaudRates BaudRate;  /* the baudrate of the uart(default - 115200)*/
    SC_UART_WordLen DataBits;   /* 5, 6, 7, or 8 number of data bits in the UART data frame (default - 8). */
    SC_UART_StopBits StopBits;  /* 1, 1.5 or 2 stop bits in the UART data frame (default - 1).   */
    SC_UART_ParityTBits ParityBit; /* Even, Odd or no-parity bit type in the UART data frame (default - Non). */
}SCuartConfiguration;


typedef void (*SC_Uart_Callback)(SC_Uart_Port_Number portNumber, void *para);
typedef void (*SC_Uart_CallbackEX)(SC_Uart_Port_Number portNumber, int len, void *reserve);

/*****************************************************************************
 * FUNCTION
 *  sAPI_UartWrite
 *
 * DESCRIPTION
 *  Send data to Tx
 *  
 * PARAMETERS
 *  [in]    port: Port number of the serial port (SC_UART / SC_UART2 / SC_UART3)
 *  [in]    data: Pointer to the data address to be written
 *  [in]    length: Maximum data length
 * RETURNS
 *  SC_UART_RETURN_CODE_OK: send done        SC_UART_RETURN_CODE_ERROR: fail  
 *
 * NOTE
 *  Pointer data is released in function sAPI_UartWrite.
 *****************************************************************************/
SC_Uart_Return_Code sAPI_UartWrite(SC_Uart_Port_Number port, UINT8 *data, UINT32 length);

/*****************************************************************************
 * FUNCTION
 *  sAPI_UartRead
 *
 * DESCRIPTION
 *  Read data from Rx
 *  
 * PARAMETERS
 *  [in]    port: Port number of the serial port (SC_UART / SC_UART2 / SC_UART3)
 *  [out]   data: Pointer to the data address returned by the data read from the serial port
 *  [in]    length: Maximum length of data to be read
 *
 * RETURNS
 *  The actual length of the bytes received. 
 *
 * NOTE
 *  
 *****************************************************************************/
SC_Uart_Return_Code sAPI_UartRead(SC_Uart_Port_Number port, unsigned char *data, int len);

/*****************************************************************************
 * FUNCTION
 *  sAPI_UartWriteString
 *
 * DESCRIPTION
 *  Used to send string data directly to the corresponding serial port
 *  
 * PARAMETERS
 *  [in]    port: Port number of the serial port (SC_UART / SC_UART2 / SC_UART3)
 *  [in]    data: Pointer to the data address to be written
 *
 * RETURNS
 *  SC_UART_RETURN_CODE_OK: send done        SC_UART_RETURN_CODE_ERROR: fail
 *
 * NOTE
 *  Pointer data is released in function sAPI_UartWrite.
 *****************************************************************************/
SC_Uart_Return_Code sAPI_UartWriteString(SC_Uart_Port_Number port, UINT8 *data);

/*****************************************************************************
 * FUNCTION
 *  sAPI_UartSetConfig
 *
 * DESCRIPTION
 *  Set the configuration of the UART, that includes baud-rate and the format of the frame.
 *  
 * PARAMETERS
 *  [in]    port: Port number of the serial port (SC_UART / SC_UART2 / SC_UART3)
 *  [in]    config: Pointer to the UART configuration block, of type SCuartConfiguration structure.
 *
 * RETURNS
 *  SC_UART_RETURN_CODE_OK: set done        SC_UART_RETURN_CODE_ERROR: fail  
 *
 * NOTE
 *  
 *****************************************************************************/
SC_Uart_Return_Code sAPI_UartSetConfig(SC_Uart_Port_Number port, const SCuartConfiguration *config);

/*****************************************************************************
 * FUNCTION
 *  sAPI_UartGetConfig
 *
 * DESCRIPTION
 *  Get the configuration of the UART, that includes baud-rate and the format of the frame.
 *  
 * PARAMETERS
 *  [in]    port: Port number of the serial port (SC_UART / SC_UART2 / SC_UART3)
 *  [out]   config: Pointer to the UART configuration block, of type SCuartConfiguration structure.
 *
 * RETURNS
 *  SC_UART_RETURN_CODE_OK: get done        SC_UART_RETURN_CODE_ERROR: get fail  
 *
 * NOTE
 *  
 *****************************************************************************/
SC_Uart_Return_Code sAPI_UartGetConfig(SC_Uart_Port_Number port, SCuartConfiguration *config);

/*****************************************************************************
 * FUNCTION
 *  sAPI_UartPrintf
 *
 * DESCRIPTION
 *  For printing strings in the debug port
 *  
 * PARAMETERS
 *  [in]    data: Format string to be output
 * RETURNS
 *  The actual length of the string
 *
 * NOTE
 * 
 *****************************************************************************/
int sAPI_UartPrintf(const char *fmt, ...);

/*****************************************************************************
 * FUNCTION
 *  sAPI_SendATCMDWaitResp
 *
 * DESCRIPTION
 *  Used to send/receive internal AT commands.
 *  
 * PARAMETERS
 *  [in]    sATPInd: Channel Index, Recommended Channel 10
 *  [in]    in_str: AT command string
 *  [in]    timeout: timeout
 *  [in]    ok_fmt: Return format of the instruction when executed correctly
 *  [in]    ok_flag: ok_flag
 *  [in]    err_fmt: Return Format of Instructions on Error Execution
 *  [in]    out_str: Returns a string of AT commands
 *  [in]    outLen: Length of the string
 * RETURNS
 *  The actual length of the string
 *
 * NOTE
 * 
 *****************************************************************************/
int sAPI_SendATCMDWaitResp(int sATPInd, char *in_str, int timeout, char *ok_fmt, int ok_flag, char *err_fmt, char *out_str, int outLen);

/*****************************************************************************
 * FUNCTION
 *  sAPI_UartRxStatus
 *
 * DESCRIPTION
 *  Used to get the status of the serial port Rx.
 *  
 * PARAMETERS
 *  [in]    port: Port number of the serial port (SC_UART / SC_UART2 / SC_UART3)
 *  [in]    timeout: A threshold value, if Rx exceeds the threshold and no data is received, then Rx is idle, no
 *                   Rx is busy. The unit is milliseconds
 *
 * RETURNS
 *  0: set done        -1: set fail  
 *
 * NOTE
 *  
 *****************************************************************************/
SC_Uart_Rx_Status sAPI_UartRxStatus(SC_Uart_Port_Number port, int timeout);

/*****************************************************************************
 * FUNCTION
 *  sAPI_UartControl
 *
 * DESCRIPTION
 *  Used to control the opening and closing of the serial port
 *  
 * PARAMETERS
 *  [in]    port: Port number of the serial port (SC_UART / SC_UART2 / SC_UART3)
 *  [in]    ctl: Type of control, on or off
 *
 * RETURNS
 *  0: set done        -1: set fail  
 *
 * NOTE
 *  
 *****************************************************************************/
SC_Uart_Return_Code sAPI_UartControl(SC_Uart_Port_Number port, SC_Uart_Control ctl);

/*****************************************************************************
 * FUNCTION
 *  sAPI_UartRegisterCallback
 *
 * DESCRIPTION
 *  Used to bind callback functions for UART advanced interrupts
 *  
 * PARAMETERS
 *  [in]    port: Port number of the serial port (SC_UART / SC_UART2 / SC_UART3)
 *  [in]    cb: Binding callback functions to the serial port
 *
 * RETURNS
 *  0: set done        -1: set fail
 *
 * NOTE
 *  
 *****************************************************************************/
SC_Uart_Return_Code sAPI_UartRegisterCallback(SC_Uart_Port_Number port, SC_Uart_Callback cb);

/*****************************************************************************
 * FUNCTION
 *  sAPI_UartRegisterCallbackEX
 *
 * DESCRIPTION
 *  Used to bind callback functions for UART advanced interrupts
 *  
 * PARAMETERS
 *  [in]    port: Port number of the serial port (SC_UART / SC_UART2 / SC_UART3)
 *  [in]    cb: Binding callback functions to the serial port
 *  [in]    reserve: Reserved parameters
 *
 * RETURNS
 *  0: set done        -1: set fail
 *
 * NOTE
 *  
 *****************************************************************************/
SC_Uart_Return_Code sAPI_UartRegisterCallbackEX(SC_Uart_Port_Number port, SC_Uart_CallbackEX cb, void *reserve);

/*****************************************************************************
 * FUNCTION
 *  sAPI_UartRs485DePinAssign
 *
 * DESCRIPTION
 *  Used to assign the Rs485 dePin to the UART
 *  
 * PARAMETERS
 *  [in]    port: Port number of the serial port (SC_UART / SC_UART2 / SC_UART3)
 *  [in]    GpinNum: Binds GPIO to Rs485 dePin.
 *
 * RETURNS
 *  0: set done        -1: set fail
 *
 * NOTE
 *  
 *****************************************************************************/
GPIOReturnCode sAPI_UartRs485DePinAssign(SC_Uart_Port_Number port, Module_GPIONumbers GpinNum);

#endif


