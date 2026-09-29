#ifndef _MBTK_ERR_H_
#define _MBTK_ERR_H_
extern void op_uart_printf(const char * fmt, ...);

#define simcom_api_not_support()     op_uart_printf("[%s] MBTK_NOT_SUPPORT", __FUNCTION__)

#endif