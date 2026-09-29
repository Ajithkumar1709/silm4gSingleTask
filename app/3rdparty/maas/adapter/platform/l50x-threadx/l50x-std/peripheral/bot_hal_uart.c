#include "bot_platform.h"
#include "bot_system_utils.h"
#include "bot_hal_uart.h"

int bot_hal_uart_recv_cb_register(bot_uart_dev_t *uart, bot_uart_rx_cb cb, void *args)
{
    return -1;
}

int bot_hal_uart_init(bot_uart_dev_t *uart)
{
    return -1;
}

int bot_hal_uart_send(bot_uart_dev_t *uart, const void *data, unsigned int size, unsigned int timeout)
{
    return -1;
}

int bot_hal_uart_recv(bot_uart_dev_t *uart, void *data, unsigned int expect_size, unsigned int *recv_size, unsigned int timeout)
{
    return -1;
}


int bot_hal_uart_deinit(bot_uart_dev_t *uart)
{
    return -1;
}