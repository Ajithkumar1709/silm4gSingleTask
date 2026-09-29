#include "uart_debug.h"
#include <stdarg.h>
#include <stdio.h>

void init_cdc_uart(void)
{
}

void cdc_uart_printf(const char *format, ...)
{
    char buffer[256];
    va_list args;

    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    op_uart_printf("%s", buffer);
}