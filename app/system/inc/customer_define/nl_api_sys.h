#ifndef _NL_API_SYS_H_
#define _NL_API_SYS_H_


#include "mbtk_os.h"

#if 0
typedef signed char     INT8;
typedef unsigned char   UINT8;
typedef short           INT16;
typedef unsigned short  UINT16;
typedef int             INT32;
typedef unsigned int    UINT32;

typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef signed short        int16_t;
typedef unsigned short      uint16_t;
typedef signed int          int32_t;
typedef unsigned int        uint32_t;
typedef signed long long    int64_t;
typedef unsigned long long  uint64_t;
#endif

typedef struct
{
    uint8_t sec;   ///< Second
    uint8_t min;   ///< Minute
    uint8_t hour;  ///< Hour
    uint8_t day;   ///< Day
    uint8_t month; ///< Month
    uint16_t year;  ///< Year
    uint8_t wDay;  ///< Week Day
} hal_rtc_time_t;

typedef enum osiShutdownMode
{
    OSI_SHUTDOWN_RESET = 0,               ///< normal reset
    OSI_SHUTDOWN_FORCE_DOWNLOAD = 0x5244, ///< 'RD' reset to force download mode
    OSI_SHUTDOWN_DOWNLOAD = 0x444e,       ///< 'DN' reset to download mode
    OSI_SHUTDOWN_BL_DOWNLOAD = 0x4244,    ///< 'BD' reset to bootloader download mode
    OSI_SHUTDOWN_CALIB_MODE = 0x434c,     ///< 'CL' reset to calibration mode
    OSI_SHUTDOWN_NB_CALIB_MODE = 0x4e43,  ///< 'NC' reset to NB calibration mode
    OSI_SHUTDOWN_BBAT_MODE = 0x4241,      ///< 'BA' reset to BBAT mode
    OSI_SHUTDOWN_UPGRADE = 0x4654,        ///< 'FT' reset to upgrade mode
    OSI_SHUTDOWN_POWER_OFF = 0x4f46,      ///< 'OF' power off
    OSI_SHUTDOWN_PSM_SLEEP = 0x5053,      ///< 'PS' power saving mode
    OSI_SHUTDOWN_PANIC = 0x504e,          ///< 'PN' panic reset
} osiShutdownMode_t;

/**
 * @brief    设置RTC时间。
 *
 * @param < time >设置日期数据指针
 * 
 * @return  0 - 表示成功  <0 - 表示失败
 */
INT32 nl_setRTC(hal_rtc_time_t *time);

/**
 * @brief    获取RTC时间。
 *
 * @param < time >获取日期数据指针
 * 
 * @return  0 - 表示成功  <0 - 表示失败
 */
INT32 nl_getRTC(hal_rtc_time_t *time);

/**
 * @brief    申请内存
 *
 * @param <size>申请内存大小，以字节为单位
 * 
 * @return  申请到的内存首地址，申请不到返回NULL（0）
 */
void *nl_malloc(UINT32 size);

/**
 * @brief    释放内存
 *
 * @param < buffer > nl_malloc分配到的内存首地址
 * 
 * @return  0 - 表示成功  <0 - 表示失败
 */
INT32 nl_free(void *buffer);

/**
 * @brief    申请一个信号量资源
 *
 * @param <inivalue>信号量初始化值  Inivalue为0或者1
 * 
 * @return  >0 - 成功，表示信号量ID  = 0 - 失败
 */
UINT32 nl_sem_new(UINT8 inivalue);

/**
 * @brief    释放一个信号量资源
 *
 * @param <semid>信号量ID
 * 
 * @return  无返回
 */
void nl_sem_free(UINT32 semid);

/**
 * @brief    信号量减一操作，若变为0，则产生线程调度
 *
 * @param <semid>信号量ID
 * 
 * @return  无返回
 */
void nl_sem_wait(UINT32 semid);

/**
 * @brief    信号量减一操作，若变为0，则产生线程调度,增加了超时机制
 *
 * @param <semid>信号量ID
 * @param <timeout>超时时长，单位为ms
 * 
 * @return  true – 成功获取信号量  false – 超时返回，未获取到信号量
 */
bool nl_sem_try_wait(UINT32 semid, UINT32 timeout);

/**
 * @brief    信号量加一操作
 *
 * @param <semid>信号量ID
 * 
 * @return  无返回
 */
void nl_sem_signal(UINT32 semid);

/**
 * @brief    创建一个锁
 * 
 * @return  ＞0 - 成功，表示锁ID  = 0 - 失败
 */
UINT32 nl_mutex_create(void);

/**
 * @brief    加锁
 *
 * @param <mutex_id>锁ID
 * 
 * @return  无返回
 */
void nl_mutex_lock(UINT32 mutex_id);

/**
 * @brief    解锁
 *
 * @param <mutex_id>锁ID
 * 
 * @return  无返回
 */
void nl_mutex_unlock(UINT32 mutex_id);

/**
 * @brief    删除已创建的锁
 *
 * @param <mutex_id>锁ID
 * 
 * @return  无返回
 */
void nl_mutex_delete(UINT32 mutex_id);

/**
 * @brief    加锁
 *
 * @param <mutex_id>锁ID
 * @param <timeout>超时时间
 * 
 * @return  = 0 – 加锁成功，返回  <0 – 加锁等待超时返回
 */
INT32 nl_mutex_try_lock(UINT32 mutex_id, UINT32 timeout);

/**
 * @brief    申请一个队列资源
 *
 * @param <msg_count>队列中可存储的Item最大个数
 * @param <msg_size>队列中单个Item大小
 * 
 * @return  >0 - 成功，表示队列ID  = 0 - 失败
 */
UINT32 nl_queue_create(UINT32 msg_count, UINT32 msg_size);

/**
 * @brief    将数据从队列中取出
 *
 * @param <msg_id>队列ID
 * @param <msg>从队列中取出数据存入空间。大小与Item大小一致
 * @param <timeout>等待超时时间。当设置为0时，表示一直等待
 * 
 * @return  =0 - 成功  <0 - 失败
 */
INT32 nl_queue_get(UINT32 msg_id, void *msg, UINT32 timeout);

/**
 * @brief    将数据放入队列中
 *
 * @param <msg_id>队列ID
 * @param <msg>从队列中取出数据存入空间。大小与Item大小一致
 * @param <timeout>等待超时时间。当设置为0时，表示一直等待
 * 
 * @return  =0 - 成功  <0 - 失败
 */
INT32 nl_queue_put(UINT32 msg_id, const void *msg, UINT32 timeout);

/**
 * @brief    清空队列只放入的数据
 *
 * @param <msg_id>队列ID
 * 
 * @return  无
 */
void nl_queue_reset(UINT32 msg_id);

/**
 * @brief    删除队列资源
 *
 * @param <msg_id>队列ID
 * 
 * @return  无
 */
void nl_queue_delete(UINT32 msg_id);

/**
 * @brief    查询队列空闲空间
 *
 * @param <msg_id>队列ID
 * 
 * @return  返回值为队列剩余可以放入的空闲item数量
 */
UINT32 nl_queue_space_available(UINT32 msg_id);

/**
 * @brief    在中断处理程序中调用此函数将数据放入队列中
 *
 * @param <msg_id>队列ID
 * @param <msg>放入队列中数据指针。数据大小必须与Item大小一致
 * 
 * @return  =0 - 成功  <0 - 失败
 */
INT32 nl_queue_put_isr(UINT32 msg_id, const void *msg);

/**
 * @brief    获取当前线程的线程ID
 * 
 * @return  >0 - 成功，表示线程ID  = 0 - 失败
 */
UINT32 nl_thread_id(void);

/**
 * @brief    创建task函数接口
 *
 * @param <pvTaskCode>任务函数接口
 * @param <pcName>任务名称
 * @param <usStackDepth>任务栈大小
 * @param <pvParameters>任务函数输入参数
 * @param <uxPriority>任务优先级
 * @param <pThreadId>出参，返回创建线程的线程ID。线程ID类型为UINT32
 * 
 * @return  =0 - 成功  <0 - 失败
 */
INT32 nl_thread_create_ex(void *pvTaskCode, INT8 *pcName, UINT32 usStackDepth, void *pvParameters, UINT32 uxPriority, UINT32* pThreadId);

/**
 * @brief    创建task函数接口
 *
 * @param <pvTaskCode>任务函数接口
 * @param <pcName>任务名称
 * @param <usStackDepth>任务栈大小
 * @param <pvParameters>任务函数输入参数
 * @param <uxPriority>任务优先级
 * @param <pThreadId>出参，返回创建线程的线程ID。线程ID类型为UINT32
 * 
 * @return  =0 - 成功  <0 - 失败
 */
INT32 nl_thread_create(void *pvTaskCode, INT8 *pcName, UINT32 usStackDepth, void *pvParameters, UINT32 uxPriority);

/**
 * @brief    删除task函数接口
 * 
 * @return  无
 */
void nl_thread_delete(void);

/**
 * @brief    删除task函数接口
 * 
 * @param <uThread>要删除线程的ID
 *
 * @return  无
 */
void nl_specify_thread_delete(UINT32 uThread);

/**
 * @brief    让当前线程睡眠一段时间，让出CPU给其他线程使用，睡眠的时间精度为20ms，也就是支持最小的睡眠时间必须大于等于20ms，并且以20ms为基本单位。
 * 
 * @param < msec >睡眠时间，单位为毫秒
 *
 * @return  无
 */
void nl_taskSleep(UINT32 msec);

/**
 * @brief    停止并释放定时器或循环定时器
 * 
 * @param <timerid>定时器ID
 *
 * @return  0 - 成功  <0 - 失败
 */
INT32 nl_timer_free(UINT32 timerid);

/**
 * @brief    软定时器。创建并启动定时器，时间和函数都不能是0（NULL）
 * 
 * @param <ms>定时时间（单位：毫秒）
 * @param <fd>回调函数
 * @param <arg>回调函数参数
 *
 * @return  >0 - 成功，表示定时器ID  <0 - 失败
 */
UINT32 nl_timer_new(UINT32 ms, void (*fn)(void *arg), void *arg);

/**
 * @brief    软定时器。创建并启动循环定时器，时间和函数都不能是0（NULL）
 * 
 * @param <ms>定时时间（单位：毫秒）
 * @param <fd>回调函数
 * @param <arg>回调函数参数
 *
 * @return  >0 - 成功，表示定时器ID  <0 - 失败
 */
UINT32 nl_timer_period_new(UINT32 ms, void (*fn)(void *arg), void *arg);

/**
 * @brief    软定时器。设置并启动看门狗，当设置的时间到达前没有喂狗，系统重启。设置的等待时间范围是1秒至1000秒。
 * 
 * @param <sec>看门狗时间，单位秒，可设置范围：1 - 1000
 *
 * @return  0 - 成功  <0 - 失败
 */
INT32 nl_watchdog_enable(UINT32 sec);

/**
 * @brief    设置和读取关机模式。
 * 
 * @param < rwmode >: 0-读取     1-写入
 * @param < sysmode >: 0-PSM     1-normal
 *
 * @return  = 0 - 成功  <0 - 失败
 */
int nl_shutdown_normal_info(uint8_t rwmode,uint8_t sysmode);

/**
 * @brief    设置shutdown模式。
 * 
 * @param < mode >: 参见 osiShutdownMode_t 数据；取值0 重启；取值：0x4f46 ，关机
 *
 * @return  1 - 成功  0 - 失败
 */
INT32 nl_set_shutdown_mode(osiShutdownMode_t mode);

/**
 * @brief    系统关机
 *
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_softPowerOff(void);

/**
 * @brief    获取签名安全标志位
 *
 * @return  true – 签名固定    false – 签名开放
 */
bool nl_get_security_flag(void);

/**
 * @brief    获取开机原因
 *
 * @return  0：软件重启开机  1，RST脚重启开机  2，Power键重启开机  3，插入USB开机（仅限于充电项目）
 */
UINT8 nl_getbootcause(void);

/**
 * @brief    开启休眠功能
 * 
 * @param <time>设置几秒后进入休眠，为0时关闭休眠
 *
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_setSleepMode(UINT8 time);

/**
 * @brief    获取硬随机数
 * 
 * @param <buf>入参，由调用者设置大小
 * @param <len>指定的buf长度
 *
 * @return  = 0 - 成功  <0 - 失败
 */
INT32 nl_rng_generate(void *buf, UINT32 len);

/**
 * @brief    当前的VBat电压
 *
 * @return  当前的VBat电压
 */
INT32 nl_getVbatStaticVol(void);

/**
 * @brief    LPG灯开关控制功能
 * 
 * @param < ucLpgSwitch >LPG灯控制开关，0为关闭，1为开启，并且掉电保存
 *
 * @return  =1 -表示成功  =0 - 表示失败
 */
INT32 nl_lpg_switch(UINT8 ucLpgSwitch);

/**
 * @brief    获取系统启动至今所累计的TICK
 *
 * @return  系统TICK
 */
UINT32 nl_getSysTick(void);

/**
 * @brief    获取系统tick将其转为us输出
 *
 * @return  系统us
 */
UINT64 nl_getSysTick_ext(void);

#endif