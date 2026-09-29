#include "simcom_uart.h"
#include "mbtk_err.h"

SC_Uart_Callback SC_cb_hook[SC_NUMBER_OF_PORTS] = {0};
SC_Uart_CallbackEX SC_cb_hook_ex[SC_NUMBER_OF_PORTS] = {0};
void *SC_cb_hook_ex_reserve[SC_NUMBER_OF_PORTS] = {0};



static void mbtk_uart_cb(MBTK_UART_Port portNumber)
{
    if(SC_cb_hook[portNumber])
    {
        SC_cb_hook[portNumber](portNumber, "mbtk");
    }
}

static void mbtk_uart_cb_ex(MBTK_UART_Port portNumber)
{
    if(SC_cb_hook_ex[portNumber])
    {
        SC_cb_hook_ex[portNumber](portNumber, 100, SC_cb_hook_ex_reserve[portNumber]);
    }
}

SC_Uart_Return_Code sAPI_UartWrite(SC_Uart_Port_Number port, UINT8 *data, UINT32 length)
{
    OL_UART_ReturnCode rec;
    rec = ol_Uart_Write(port, data, length);
    
    if(rec != OL_UART_RC_OK)
        return SC_UART_RETURN_CODE_ERROR;
    
    return SC_UART_RETURN_CODE_OK;
}
SC_Uart_Return_Code sAPI_UartRead(SC_Uart_Port_Number port, unsigned char *data, int len)
{
    OL_UART_ReturnCode rec;
    u16 data_len;
   rec = ol_Uart_Read(port, data, len, &data_len);
    
    if(rec != OL_UART_RC_OK)
        return SC_UART_RETURN_CODE_ERROR;
    
    return data_len;
}

SC_Uart_Return_Code sAPI_UartWriteString(SC_Uart_Port_Number port, UINT8 *data)
{
    simcom_api_not_support();
    return SC_UART_RETURN_CODE_OK;
}

SC_Uart_Return_Code sAPI_UartSetConfig(SC_Uart_Port_Number port, const SCuartConfiguration *config)
{
    OL_UART_ReturnCode rec;
    OL_UART_DCB dcb = {0};

    rec = ol_Uart_GetDcb(port, &dcb);
    
    if(rec != OL_UART_RC_OK)
        return SC_UART_RETURN_CODE_ERROR;


    if(config != NULL)
    {
        dcb.baudRate = config->BaudRate;
        dcb.numDataBits = config->DataBits;
        dcb.stopBit = config->StopBits;
        dcb.parityBitType = config->ParityBit;
    }
    
//    ol_Uart_Close(port);

    rec = ol_Uart_SetDcb(port, &dcb);
    if(rec != OL_UART_RC_OK)
        return SC_UART_RETURN_CODE_ERROR;

    rec = ol_Uart_Open(port);
    if(rec != OL_UART_RC_OK)
        return SC_UART_RETURN_CODE_ERROR;
    
    return SC_UART_RETURN_CODE_OK;
}

SC_Uart_Return_Code sAPI_UartGetConfig(SC_Uart_Port_Number port, SCuartConfiguration *config)
{
    OL_UART_ReturnCode rec;
    OL_UART_DCB dcb = {0};
    
    rec = ol_Uart_GetDcb(port, &dcb);
    
    if(rec != OL_UART_RC_OK)
        return SC_UART_RETURN_CODE_ERROR;
    
    if(config == NULL)
        return SC_UART_RETURN_CODE_ERROR;
    
    config->BaudRate = dcb.baudRate;
    config->DataBits = dcb.numDataBits;
    config->StopBits = dcb.stopBit;
    config->ParityBit = dcb.parityBitType;
    return SC_UART_RETURN_CODE_OK;
}
#if 0

int sAPI_UartPrintf(const char *fmt, ...)
{

    return SC_UART_RETURN_CODE_OK;
}
#endif

int sAPI_SendATCMDWaitResp(int sATPInd, char *in_str, int timeout, char *ok_fmt, int ok_flag, char *err_fmt, char *out_str, int outLen)
{
    simcom_api_not_support();
    return SC_UART_RETURN_CODE_OK;
}

SC_Uart_Rx_Status sAPI_UartRxStatus(SC_Uart_Port_Number port, int timeout)
{
    simcom_api_not_support();
    return SC_UART_RX_IDLE;
}

SC_Uart_Return_Code sAPI_UartControl(SC_Uart_Port_Number port, SC_Uart_Control ctl)
{
    OL_UART_ReturnCode rec;
    
    switch(ctl)
    {
        case SC_UART_OPEN:
            rec = ol_Uart_Open(port);
            break;
        case SC_UART_CLOSE:
            rec = ol_Uart_Close(port);
            break;
        default:
            return SC_UART_RETURN_CODE_ERROR;
    }
    
    if(rec != OL_UART_RC_OK)
        return SC_UART_RETURN_CODE_ERROR;
    
    return SC_UART_RETURN_CODE_OK;
}
SC_Uart_Return_Code sAPI_UartRegisterCallback(SC_Uart_Port_Number port, SC_Uart_Callback cb)
{
    OL_UART_ReturnCode rec;
    OL_UART_DCB dcb = {0};

    rec = ol_Uart_GetDcb(port, &dcb);
    if(rec != OL_UART_RC_OK)
        return SC_UART_RETURN_CODE_ERROR;

    dcb.rd_cb = mbtk_uart_cb;

    rec = ol_Uart_SetDcb(port, &dcb);
    
    if(rec != OL_UART_RC_OK)
        return SC_UART_RETURN_CODE_ERROR;
    
    SC_cb_hook[port] = cb;
    return SC_UART_RETURN_CODE_OK;
}
SC_Uart_Return_Code sAPI_UartRegisterCallbackEX(SC_Uart_Port_Number port, SC_Uart_CallbackEX cb, void *reserve)
{
    OL_UART_ReturnCode rec;
    OL_UART_DCB dcb = {0};

    rec = ol_Uart_GetDcb(port, &dcb);
    if(rec != OL_UART_RC_OK)
        return SC_UART_RETURN_CODE_ERROR;

    dcb.rd_cb = mbtk_uart_cb;

    rec = ol_Uart_SetDcb(port, &dcb);
    
    if(rec != OL_UART_RC_OK)
        return SC_UART_RETURN_CODE_ERROR;
    
    SC_cb_hook_ex[port] = cb;
    SC_cb_hook_ex_reserve[port] = reserve;
    return SC_UART_RETURN_CODE_OK;
}

#if 0
GPIOReturnCode sAPI_UartRs485DePinAssign(SC_Uart_Port_Number port, Module_GPIONumbers GpinNum)
{

    return SC_GPIORC_OK;
}
#endif


