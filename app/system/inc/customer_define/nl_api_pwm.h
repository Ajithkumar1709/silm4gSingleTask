#ifndef _NL_API_PWM_H_
#define _NL_API_PWM_H_

typedef unsigned int				uint32_t;
/**
 * @brief    打开pwm功能，初始化相关参数
 *
 * @return  True  成功  False  失败
 */
bool nl_pwmOpen(void);

/**
 * @brief    设置PWT输出的频率，占空比，
 * 输出频率=200Mhz/(prescaler+1)/(period_count*8 + 1)
 * 占空比 = duty/period_count
 *
 * @param <period_count>：period load data,must less than 2047.if period_count is 0,pwt can't output
 * @param <prescaler>：pwm clock prescaler
 * @param <duty>：duty must less than 1023,duty/period_count is the duty ratio.duty can't be 0 ,drvPwtStop can be called
 * 
 * @return  True  成功  False  失败
 */
bool nl_pwtConfig(uint32_t period_count,uint8_t prescaler,uint32_t duty);

/**
 * @brief    打开或者关闭PWT输出
 *
 * @param <is_start>打开或者关闭PWT输出  True：打开PWT输出  False：停止PWT输出
 * 
 * @return  True  成功  False  失败
 */
bool nl_pwtStartorStop(bool is_start);

/**
 * @brief    关闭pwm功能，释放pwm资源
 * 
 * @return  True  成功  False  失败
 */
void nl_pwmClose(void);

#endif