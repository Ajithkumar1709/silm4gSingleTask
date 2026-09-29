#ifndef _SIMCOM_DEBUG_H
#define _SIMCOM_DEBUG_H

extern int op_uart_printf(const char *fmt, ...);

//void sAPI_Debug(const char *format, ...);
#define sAPI_Debug op_uart_printf
#define printf op_uart_printf



#endif



