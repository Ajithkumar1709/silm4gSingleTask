#ifndef _NL_API_GPIO_H_
#define _NL_API_GPIO_H_


#define SAPP_IO_ID_T uint16_t
#define SAPP_GPIO_CFG_T uint16_t

typedef void (*ISR_CB)(void* param);

typedef struct
{
	bool is_debounce;   // debounce enabled
	bool intr_enable;   //interrupt enabled, only for GPIO input
	bool intr_level;    // true for level interrupt, false for edge interrupt
	bool intr_falling;    //falling edge or level low interrupt enabled
	bool inte_rising;   //rising edge or level high interrupt enabled
	ISR_CB callback;    //interrupt callback
}oc_isr_t;

/**
 * @brief    设置对应PIN脚的输入输出方向。（仅对当前PIN脚做GPIO模式时有效）
 *
 * @param <id>PIN_num ,pin脚序列号
 * @param <cfg>设置输入输出方向；0为输入，1为输出
 * 
 * @return  1 - 表示成功   -1 - 表示失败
 */
INT32 nl_gpio_cfg(SAPP_IO_ID_T id,SAPP_GPIO_CFG_T cfg);

/**
 * @brief    设置当前PIN脚高低电平（仅对当前PIN脚做GPIO模式，且是output时有效）
 *
 * @param <id>PIN_num ,pin脚序列号
 * @param <level>用来设置当前PIN脚高低电平
 * 
 * @return  1 - 表示成功   -1 - 表示失败
 */
INT32 nl_gpio_set(SAPP_IO_ID_T id,UINT8 level);

/**
 * @brief    获取当前PIN脚高低电平（仅对当前PIN脚做GPIO模式，且是output时有效）
 *
 * @param <id>PIN_num ,pin脚序列号
 * @param <*level>用来获取当前PIN脚高低电平的入参 
 * 
 * @return  1 - 表示成功   -1 - 表示失败
 */
INT32 nl_gpio_get(SAPP_IO_ID_T id,UINT8 * level);

/**
 * @brief    设置PIN脚的复用模式
 *
 * @param <id>PIN_num ,pin脚序列号
 * @param <mode>复用成GPIO时的Function值
 * 
 * @return  1 - 表示成功   -1 - 表示失败
 */
INT32 nl_gpio_mode_set(SAPP_IO_ID_T id,UINT8 mode);

/**
 * @brief    将该PIN脚做内部上下拉，多用于当前PIN做输入模式的情景下。仅限于当前PIN脚是GPIO模式可用。
 *
 * @param <id>PIN_num ,pin脚序列号
 * @param <is_pull_up>是否拉高  True：拉高  False：拉低
 * 
 * @return  1 - 表示成功   -1 - 表示失败
 */
INT32 nl_gpio_pull_up_or_down(SAPP_IO_ID_T id,bool is_pull_up);

/**
 * @brief    将该PIN脚恢复到默认的模式
 *
 * @param <id>PIN_num ,pin脚序列号
 * 
 * @return  1 - 表示成功   -1 - 表示失败
 */
INT32 nl_gpio_pull_disable(SAPP_IO_ID_T id);

/**
 * @brief    控制外部PA的打开和关闭，打开和关闭都是通过拉高和拉低电平
 *
 * @param < pin_id >：外部PA接入的引脚
 * 
 * @return  0：成功  <0：失败
 */
INT32 nl_external_PA_enable_level(uint16_t pin_id);

/**
 * @brief    将该PIN脚恢复到默认的模式，如果默认就是GPIO模式，将其设置为GPIO的output模式，默认拉高。
 *
 * @param <id>PIN_num ,pin脚序列号
 * 
 * @return  1 - 表示成功  -1 - 表示失败
 */
INT32 nl_gpio_isr_deinit(SAPP_IO_ID_T id);

/**
 * @brief    将该PIN脚设置为中断模式
 *
 * @param <id>PIN_num ,pin脚序列号
 * 
 * @return  1 - 表示成功  -1 - 表示失败
 */
INT32 nl_gpio_isr_init(SAPP_IO_ID_T id,oc_isr_t * isr_cfg);

#endif