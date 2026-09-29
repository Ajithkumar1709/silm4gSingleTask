/*
 *
 * Copyright (C) 2020-2021 Alibaba Group Holding Limited
*/
/**
 * @file bot_system.C
 *
 * @brief dedicated iot adapter system functions which need be impementd by customer.
 *
 *
 */
#include "bot_system.h"
#include "bot_hal_gnss.h"
#include "bot_network.h"
#include "bot_platform_user_config.h"

#define DEFAULT_TASK_PRIORITY (200)

#ifndef BOT_COMP_MEM_DEFAULT_HEAP_SIZE
#define BOT_COMP_MEM_DEFAULT_HEAP_SIZE 0x12000
#endif

static uint8_t g_mem_space[BOT_COMP_MEM_DEFAULT_HEAP_SIZE];

void* bot_os_alloc(unsigned int size)
{
    return ol_malloc(size);
}

void bot_os_free(void* addr)
{
    if(addr != NULL)
    {
        ol_free(addr);
    }
}

void* bot_os_realloc(void* addr, unsigned int newsize)
{
    return ol_realloc(addr, newsize);
}

unsigned long long bot_uptime(void)
{
    unsigned long long time_ms = 0;
    uint32_t ticks = ol_os_get_ticks();
    time_ms = (unsigned long long)(ticks * 5);
    return time_ms;
}

void bot_msleep(unsigned int ms)
{
    ol_os_task_sleep(ms/5);
}

// #if defined (__CC_ARM) || (__ICCARM__)
int bot_gettimeofday(ol_timeval *tv, void* dummy)
{
    if(tv == NULL)
    {
        return -1;
    }
    int time_num = (int)ol_time(NULL);
    tv->tv_sec = time_num;
    tv->tv_usec = 0;
    return 0;
}
// #endif

void *bot_mutex_create(void)
{
    mbtk_os_status* mutex = (mbtk_os_status*)bot_os_alloc(sizeof(mbtk_os_status));
    mbtk_os_status status = ol_os_mutex_creat(mutex, 0XFF);
    if(status != 0)
    {
        bot_printf("bot_mutex_create fail\n");
        bot_os_free(mutex);
        return NULL;
    }
    bot_printf("bot_mutex_create:%d", *mutex);
    return (void *)mutex;
}

void bot_mutex_delete(void *mutex)
{
    if (mutex == NULL) {
        bot_printf("bot_mutex_delete fail, because mutex is null\r");
        return;
    }
    bot_printf("bot_mutex_delete:%d", *(mbtk_mutexref*)mutex);
    mbtk_os_status status = ol_os_mutex_delete(*(mbtk_mutexref*)mutex);
    if(status != 0)
    {
        bot_printf("bot_mutex_delete fail\n");
        return;
    }
    if(mutex != NULL)
    {
        bot_os_free(mutex);
    }
}

void bot_mutex_lock(void *mutex)
{
    if (mutex == NULL) {
        bot_printf("bot_mutex_lock fail because mutex is null\r");
        return;
    }
    mbtk_os_status status = ol_os_mutex_lock(*(mbtk_mutexref*)mutex, MBTK_OS_SUSPEND);
    if(status != 0)
    {
        bot_printf("bot_mutex_lock fail\n");
        return;
    }
}

void bot_mutex_unlock(void *mutex)
{
    if (mutex == NULL) {
        bot_printf("bot_mutex_unlock fail because mutex is null\r");
        return;
    }
    mbtk_os_status status = ol_os_mutex_unlock(*(mbtk_mutexref*)mutex);
    if(status != 0)
    {
        bot_printf("bot_mutex_unlock fail\n");
        return;
    }
}

void *bot_sem_create(void)
{
#define INIT_SEM_COUNT 0
    mbtk_semref* sem = (mbtk_semref*)bot_os_alloc(sizeof(mbtk_semref));
    bot_printf("bot_sem_create :%d", (*(mbtk_semref*)sem));
    if (sem == NULL) {
        bot_printf("bot_sem_create fail, because malloc sem error\r");
        return NULL;
    }
    mbtk_os_status status = ol_os_sem_creat(sem, INIT_SEM_COUNT, MBTK_OS_FIFO);
    if(status != 0)
    {
        bot_printf("bot_sem_create fail\r");
        return NULL;
    }
    bot_printf("bot_sem_create :%d", (*(mbtk_semref*)sem));
    return (void *)sem;
}

void bot_sem_delete(void *sem)
{
    if (sem == NULL) {
        bot_printf("bot_sem_delete fail because the sem is null\n");
        return;
    }
    bot_printf("bot_sem_delete:%d", (*(mbtk_semref*)sem));
    mbtk_os_status status = ol_os_sem_delete((mbtk_semref)(*(mbtk_semref*)sem));
    if(status != 0)
    {
        bot_printf("bot_sem_delete fail\r");
        return;
    }
    if(sem != NULL)
    {
        bot_os_free(sem);
    }
}

void bot_sem_post(void *sem)
{
    bot_printf("bot_sem_post:%d", (*(mbtk_semref*)sem));
    if (sem == NULL) {
        bot_printf("bot_sem_post fail because of the sem is null\n");
        return;
    }
    mbtk_os_status status = ol_os_sem_release((mbtk_semref)(*(mbtk_semref*)sem));
    if(status != 0)
    {
        bot_printf("bot_sem_post fail\r");
        return;
    }
}

int bot_sem_wait(void *sem, unsigned int timeout_ms)
{
    bot_printf("bot_sem_wait:%d", (*(mbtk_semref*)sem));
    mbtk_os_status status = ol_os_sem_request((mbtk_semref)(*(mbtk_semref*)sem), timeout_ms / 5);
    if(status != 0)
    {
        bot_printf("bot_sem_wait fail\n");
        return -1;
    }
    return 0;
}

void *bot_queue_create(int queue_length, int item_size)
{
    mbtk_msgqref* queue = (mbtk_msgqref*)bot_os_alloc(sizeof(mbtk_msgqref));
    int status = ol_os_msgq_creat(queue, NULL, item_size, queue_length, MBTK_OS_FIFO);
    if(status != 0)
    {
        bot_printf("mbtk_os_msgq_creat fail\n");
        bot_os_free(queue);
        return NULL;
    }
    return (void *)queue;
}

int bot_queue_delete(void *mq)
{
    if (mq == NULL) {
        bot_printf("bot_queue_delete fail because of the mq is null\n");
        return -1;
    }
    int status = ol_os_msgq_delete(*(mbtk_msgqref*)mq);
    if(status != 0)
    {
        bot_printf("bot_queue_delete fail\n");
        return -1;
    }
    if(mq != NULL)
    {
        bot_os_free(mq);
    }
    return 0;
}

int bot_queue_recv(void *mq, void *msg, unsigned int size, unsigned int ms)
{
    if (mq == NULL) {
        bot_printf("bot_queue_recv fail because of the mq is null\n");
        return -1;
    }
    int status = ol_os_msgq_recv(*(mbtk_msgqref*)mq, (UINT8 *)msg,  size, ms / 5);
    if(status != 0)
    {
        bot_printf("bot_queue_recv fail\n");
        return -1;
    }
    return 0;
}


int bot_queue_send(void *mq, void *msg, unsigned int size, unsigned int ms)
{
    if (mq == NULL) {
        bot_printf("bot_queue_send fail because of the mq is null\n");
        return -1;
    }
    int status = ol_os_msgq_send(*(mbtk_msgqref*)mq, size, msg, ms / 5);
    if(status != 0)
    {
        bot_printf("bot_queue_send fail\n");
        return -1;
    }
    return 0;
}

int bot_queue_send_isr(void *mq, void *msg, unsigned int size)
{
    if (mq == NULL) {
        bot_printf("bot_queue_send_isr fail because of the mq is null\n");
        return -1;
    }
    int status = bot_queue_send(mq, msg, size, 1000);
    if(status != 0)
    {
        bot_printf("bot_queue_send_isr fail\n");
        return -1;
    }
    return 0;
}


int bot_task_default_priority_get()
{
    return DEFAULT_TASK_PRIORITY;
}

int bot_task_create(
            void **task_handle,
            void (*work_routine)(void *),
            void *arg,
            bot_task_param_t *task_param,
            int *stack_used)
{
    if(task_param == NULL)
    {
        bot_printf("bot_task_create fail because task_param is null\n");
        return -1;
    }

    if(task_param->stack_addr == NULL)
    {
        bot_printf("stack_addr is null\r");
    }
    
    if(task_param->stack_size <= 0)
    {
        bot_printf("stack_size <= 0\r");
    }
    bot_printf("bot_task_create task name:%s\r", task_param->name);
    int status = ol_os_task_creat(task_handle, task_param->stack_addr, 
        task_param->stack_size, task_param->priority,task_param->name, work_routine, arg);
    if(status != 0)
    {
        bot_printf("bot_task_create fail\r");
        return -1;
    }
    
    bot_printf("bot_task_create is:%u", *task_handle);
    return 0;

}

int bot_task_delete(void *task_handle)
{
    mbtk_taskref temp_handle = (mbtk_taskref)task_handle;
    bot_printf("bot_task_delete task is:%u", temp_handle);
    if(task_handle == NULL)
    {   
        bot_printf("bot_task_delete task_handle is null\n");
        mbtk_taskref self_handle;
        int ret = ol_os_task_get_current_ref(&self_handle);
        if(ret == 0)
        {
            temp_handle = self_handle;
            bot_printf("bot_task_delete oneself task_handle is:%u", temp_handle);
        }
        else
        {
            bot_printf("bot_task_delete fail\n");
            return -1;
        }
    }
    int status = ol_os_task_delete(temp_handle);
    if(status != 0)
    {
        bot_printf("bot_task_delete fail\n");
        return -1;
    }
    return 0;
}

int bot_mem_info_get(bot_mem_para_t *mem)
{
    if (mem == NULL) {
        return -1;
    }
    mem->start = (void*)&g_mem_space[0];
    mem->len   = BOT_COMP_MEM_DEFAULT_HEAP_SIZE;
    return 0;
}

/* platform init */
int bot_platform_init(void)
{
    int ret = 0;
    ret = bot_hal_flash_init();
    if (ret != 0) {
        bot_printf("bot_hal_flash_init fail , ret:%d\n\r", ret);
        return -1;
    }
    
    ret = bot_network_init();
    if (ret != 0) {
        bot_printf("bot_network_init fail , ret:%d\n\r", ret);
        return -1;
    }
#if BOT_COMP_GNSS
    ret = bot_hal_gnss_init();
    if (ret != 0) {
        bot_printf("bot_hal_gnss_init fail , ret:%d\n\r", ret);
        return -1;
    }
#endif
    return ret;
}

