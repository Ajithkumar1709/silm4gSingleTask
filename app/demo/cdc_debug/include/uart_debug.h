#ifndef UART_DEBUG_H
#define UART_DEBUG_H

void init_cdc_uart(void);
void cdc_uart_printf(const char *format, ...);

#endif