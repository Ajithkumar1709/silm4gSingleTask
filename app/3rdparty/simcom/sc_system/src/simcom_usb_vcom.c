#include <string.h>
#include "simcom_usb_vcom.h"
#include "mbtk_uart.h"


#define SIMCOM_USB_PORT             OL_UART_PORT_CDCUART
#define SIMCOM_USB_DATA_BUFF_LEN    2048

typedef struct {

    SC_Usb_Callback_EX Simcom_Usb_Cb_EX;
    void *reserve;
}SC_Usb_Callback_Info;


bool Usb_Is_Open = false;

SC_Usb_Callback_Info Simcom_Usb_Cb_Info = {0};

static char Simcom_Usb_Data_Buf[SIMCOM_USB_DATA_BUFF_LEN] = {0};

void Mbtk_Usb_Open(void)
{
    ol_Uart_Close(SIMCOM_USB_PORT);
    ol_Uart_Open(SIMCOM_USB_PORT);
}

void Mbtk_Usb_Callback(MBTK_UART_Port portNumber)
{
	u16 read_len = 0;
    int data_len = 0;
    if(Simcom_Usb_Cb_Info.Simcom_Usb_Cb_EX)
    {
        do
        {
            memset(Simcom_Usb_Data_Buf, 0x0, SIMCOM_USB_DATA_BUFF_LEN);
        	ol_Uart_Read(portNumber, Simcom_Usb_Data_Buf, SIMCOM_USB_DATA_BUFF_LEN - 1, &read_len);
            
            if(read_len <= 0)
                break;
            Simcom_Usb_Cb_Info.Simcom_Usb_Cb_EX(read_len, Simcom_Usb_Cb_Info.reserve);
        }while(1);
    }
}

void sAPI_UsbVcomWrite(unsigned char* data, unsigned long length)
{
    if(!Usb_Is_Open)
    {
        Mbtk_Usb_Open();
        Usb_Is_Open = true;
    }
    ol_Uart_Write(SIMCOM_USB_PORT, data, length);
}

int sAPI_UsbVcomRead(unsigned char* Data, int len)
{
    
    if(!Usb_Is_Open)
    {
        Mbtk_Usb_Open();
        Usb_Is_Open = true;
    }
    memset(Data, 0x0, len);
    if(!Simcom_Usb_Cb_Info.Simcom_Usb_Cb_EX)
    {
        u16 read_len = 0;
        ol_Uart_Read(SIMCOM_USB_PORT, Data, len, &read_len);
        return read_len;
    }
    else
    {
        strncpy(Data, Simcom_Usb_Data_Buf, len);
        return strlen(Data);
    }
}

int sAPI_UsbVcomRegisterCallbackEX(SC_Usb_Callback_EX cb, void *reserve)
{
    OL_UART_DCB uart_dcb = {0};
    
    Simcom_Usb_Cb_Info.Simcom_Usb_Cb_EX = cb;
    Simcom_Usb_Cb_Info.reserve = reserve;
    
    if(ol_Uart_Close(SIMCOM_USB_PORT) != OL_UART_RC_OK)
        return -1;
    if(ol_Uart_GetDcb(SIMCOM_USB_PORT, &uart_dcb) != OL_UART_RC_OK)
        return -1;
    uart_dcb.rd_cb = Mbtk_Usb_Callback; 
    if(ol_Uart_SetDcb(SIMCOM_USB_PORT, &uart_dcb) != OL_UART_RC_OK)
        return -1;
    if(ol_Uart_Open(SIMCOM_USB_PORT) != OL_UART_RC_OK)
        return -1;

    return 0;
}

