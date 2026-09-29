#ifndef _NL_API_UART_H_
#define _NL_API_UART_H_


#include "mbtk_uart.h"
#include "stdint.h"

typedef int hal_uart_port_t;

enum hal_uart_data_bits_s
{
    HAL_UART_DATA_BITS_7 = 7,
    HAL_UART_DATA_BITS_8 = 8
};

enum hal_uart_stop_bits_s
{
    HAL_UART_STOP_BITS_1 = 1,
    HAL_UART_STOP_BITS_2 = 2
};

typedef enum
{
    HAL_UART_NO_PARITY,   ///< No parity check
    HAL_UART_ODD_PARITY,  ///< Parity check is odd
    HAL_UART_EVEN_PARITY, ///< Parity check is even
}hal_uart_parity_t;

typedef enum hal_uart_data_bits_s hal_uart_data_bits_t;
typedef enum hal_uart_stop_bits_s hal_uart_stop_bits_t;

struct hal_uart_config_s
{
    uint32_t baud;                  ///< baudrate, 0 for auto baud
    hal_uart_data_bits_t data_bits; ///< data bits
    hal_uart_stop_bits_t stop_bits; ///< stop bits
    hal_uart_parity_t parity;
    bool cts_enable;                ///< enable cts or not
    bool rts_enable;                ///< enable rts or not
    size_t rx_buf_size;             ///< rx buffer size
    size_t tx_buf_size;             ///< tx buffer size
    uint32_t recv_timeout;          //ms
};
typedef struct hal_uart_config_s hal_uart_config_t;
typedef void (*uart_input_callback_t)(hal_uart_port_t uart_port, UINT8 *data, UINT16 len, void *arg);

/**
 * @brief    UART Open接口。UART口接收到的数据，通过回调函数通知DEMO，Uart_port序列从0-2
 *
 * @param <uart_port> 串口号 
 * @param <uart_config>串口配置
 * @param <recv_cb> 回调函数
 * @param <arg> 回调函数用户数据
 * 
 * @return  0：成功  -1：失败  -2：参数错误
 */
INT32 nl_hal_uart_init(hal_uart_port_t uart_port, hal_uart_config_t *uart_config, uart_input_callback_t recv_cb, void *arg);

/**
 * @brief    UART write接口，要注意目前是从模块串口输出buff
 *
 * @param <uart_port> 串口号
 * @param <buff>写入串口buff
 * @param <len>写入串口buff长度
 * 
 * @return  <=0 - 表示失败
 */
INT32 nl_hal_uart_put(hal_uart_port_t uart_port, UINT8 *buff, UINT32 len);

/**
 * @brief    UART Close接口
 *
 * @param <uart_port> 串口号
 * 
 * @return  0 - 表示成功  <0 - 表示失败
 */
INT32 nl_hal_uart_deinit(hal_uart_port_t uart_port);

#endif