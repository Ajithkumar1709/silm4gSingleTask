#include "bot_platform.h"
#include "bot_system_utils.h"
#include "bot_hal_uart.h"


typedef struct
{
    bot_uart_rx_cb cb;
    void* arg;
}UART_REV_CB_MAP;


#define MAX_REV_BUF_LEN   512  //The length of the received data buffer is not enough to be adjusted
uint8_t rev_data[MAX_REV_BUF_LEN] = {0};

static UART_REV_CB_MAP uart_rev_cb_map[OL_NUMBER_OF_PORTS] = {};
static void uart_rev_cb(MBTK_UART_Port p)
{
    bot_uart_rx_cb cb = NULL;
    if(p >= OL_UART_PORT_FFUART && p < OL_NUMBER_OF_PORTS)
    {
        cb = uart_rev_cb_map[p].cb;
    }
    if(cb != NULL)
    {   
        uint16_t read_len = 0;
        ol_Uart_Read(p, rev_data, MAX_REV_BUF_LEN, &read_len);
        if(read_len > 0)
        {
            cb(p, rev_data, read_len, uart_rev_cb_map[p].arg);
        }
        else
        {
            bot_printf("ol_Uart_Read NULL\r");
        }
    }
}

int bot_hal_uart_recv_cb_register(bot_uart_dev_t *uart, bot_uart_rx_cb cb, void *args)
{
    if(uart == NULL)
    {
        bot_printf("bot_hal_uart_recv_cb_register fail because uart is NULL\r");
        return -1;
    }
    if(uart->port >= OL_UART_PORT_FFUART && uart->port < OL_NUMBER_OF_PORTS)
    {
        uart_rev_cb_map[uart->port].cb = cb;
        uart_rev_cb_map[uart->port].arg = args;
        return 0;
    }
    return -1;
}

int bot_hal_uart_init(bot_uart_dev_t *uart)
{
    if(uart == NULL)
    {
        bot_printf("bot_hal_uart_init fail because uart is NULL\r");
        return -1;
    }
    
    OL_UART_DCB dcb = {0};
    OL_UART_ReturnCode ret_code = ol_Uart_GetDcb(uart->port, &dcb);
    if(ret_code != OL_UART_RC_OK)
    {
        bot_printf("bot_hal_uart_init uart get dcb fail(%d)\r", ret_code);
        return -1;
    }
    dcb.opMode = uart->config.mode;
    dcb.baudRate = uart->config.baud_rate;
    dcb.flowControl = uart->config.flow_control; 
    dcb.numDataBits = uart->config.data_width;
    dcb.parityBitType = uart->config.parity; 
    dcb.rd_cb = uart_rev_cb;
    ret_code = ol_Uart_SetDcb(uart->port, &dcb);
    if(ret_code != OL_UART_RC_OK)
    {
        bot_printf("bot_hal_uart_init uart set dcb fail(%d)\r", ret_code);
        return -1;
    }
    ret_code = ol_Uart_Open(uart->port);
    if(ret_code != OL_UART_RC_OK)
    {
        bot_printf("bot_hal_uart_init uart open fail(%d)\r", ret_code);
        return -1;
    }
    
    return 0;
}

int bot_hal_uart_send(bot_uart_dev_t *uart, const void *data, unsigned int size, unsigned int timeout)
{
    OL_UART_ReturnCode ret_code = ol_Uart_Write(uart->port, data, size);
    if(ret_code < 0)
    {
        bot_printf("bot_hal_uart_send fail(%d)\r", ret_code);
        return -1;
    }
    return 0;
}

int bot_hal_uart_recv(bot_uart_dev_t *uart, void *data, unsigned int expect_size, unsigned int *recv_size, unsigned int timeout)
{
    OL_UART_ReturnCode ret_code = ol_Uart_Read(uart->port, data, expect_size, recv_size);
    if(ret_code != OL_UART_RC_OK)
    {
        bot_printf("bot_hal_uart_recv fail(%d)\r", ret_code);
        return -1;
    }
    return 0;
}


int bot_hal_uart_deinit(bot_uart_dev_t *uart)
{
    if(uart == NULL)
    {
        bot_printf("bot_hal_uart_deinit fail because uart is NULL\r");
        return -1;
    }
    if(uart->port >= OL_UART_PORT_FFUART && uart->port < OL_NUMBER_OF_PORTS)
    {
        uart_rev_cb_map[uart->port].cb = NULL;
        uart_rev_cb_map[uart->port].arg = NULL;
        OL_UART_ReturnCode ret_code = ol_Uart_Close(uart->port);
        if(ret_code != OL_UART_RC_OK)
        {
            bot_printf("bot_hal_uart_deinit fail(%d)\r", ret_code);
            return -1;
        }
        return 0;
    }
    return -1;
}