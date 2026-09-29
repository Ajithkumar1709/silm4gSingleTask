#ifndef _NL_API_USBCDC_H_
#define _NL_API_USBCDC_H_

typedef	unsigned int	size_t;
typedef void (*usb_input_callback_t)(INT32 id, void *buf, size_t size, void *arg);
typedef int (*Report_UsbDev_Event) (int msg);

/**
 * @brief    注册usb端口
 *
 * @param Name：usb的宏名字，port6可用即可：DRV_NAME_USRL_COM6
 * @param recv_cb：用户注册的回调函数
 * @param th：端口的句柄
 * @param data：传输的数据
 * @param length：data的长度
 * 
 * @return  >=0 表示成功   < 0 表示失败
 */
INT32 nl_usbDevice_init(uint32_t name, usb_input_callback_t recv_cb);

/**
 * @brief    获取USB的插入状态。
 * 
 * @return  0 –未插入  1 –插入
 */
UINT8 nl_get_Usbisinsert(void);

/**
 * @brief    向usb驱动注册接收usb插拔事件的回调函数。该回调函数可以接收到usb的插入、拔出、端口打开、端口关闭四种消息。
 *
 * @param th：端口的句柄
 * @param usedev_Event：用户注册的回调函数
 * 
 * @return  >=0 表示成功   < 0 表示失败
 */
int nl_usbDevice_State_report(INT32 id, Report_UsbDev_Event  usedev_Event);

/**
 * @brief    向指定的usb端口发送数据
 *
 * @param th：端口的句柄
 * @param data：传输的数据
 * @param length：data的长度
 * 
 * @return  >0   – 发送的字节数  0  – 失败
 */
int nl_usbDevice_send(INT32 id, const void *data, size_t length);

/**
 * @brief    获取USB模式
 * 
 * @return  >=0 mode   < 0 表示失败
 */
INT32 nl_get_usbmode(void);

/**
 * @brief    设置USB模式
 *
 * @param usbmode：     NL_USB_DEBUG_7PORT = 31    NL_USB_RELEASE = 34    NL_USB_DEBUG_3PORT = 35
 * 
 * @return  >=0 表示成功   < 0 表示失败
 */
INT32 nl_set_usbmode(uint8_t usbmode);

#endif