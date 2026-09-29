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

#define DEFAULT_TASK_PRIORITY 24

#ifndef BOT_COMP_MEM_DEFAULT_HEAP_SIZE
#define BOT_COMP_MEM_DEFAULT_HEAP_SIZE 0x12000
#endif

static uint8_t g_mem_space[BOT_COMP_MEM_DEFAULT_HEAP_SIZE];

void* bot_os_alloc(unsigned int size)
{
//    return malloc(size);
   return NULL;
}

void bot_os_free(void* addr)
{
//    free(addr);
}

void* bot_os_realloc(void* addr, unsigned int newsize)
{
//    return realloc(addr, newsize);
    return NULL;
}

unsigned long long bot_uptime(void)
{
    unsigned long long time_ms = 0;
    // unsigned long long us = 0;

    // us=osiUpTimeUS();

    // time_ms = us/1000;

    return time_ms;
}

void bot_msleep(unsigned int ms)
{
    ol_os_task_sleep(ms/5);
}

// #if defined (__CC_ARM) || (__ICCARM__)
int bot_gettimeofday(struct timeval *tv, void* dummy)
{
    return ol_gettimeofday(tv, dummy);
}
// #endif

void *bot_mutex_create(void)
{
    unsigned int *mutex = (unsigned int *)bot_os_alloc(sizeof(unsigned int));
    // if (NULL == mutex) {
    //     return NULL;
    // }
    // // TODO *mutex = ol_os_mutex_creat();
    // if (0 == *mutex) {
    //     bot_os_free(mutex);
    //     return NULL;
    // }

    return (void *)mutex;
}

void bot_mutex_delete(void *mutex)
{
    // if (mutex == NULL) {
    //     return;
    // }
    // // TODO fibo_mutex_delete(*(unsigned int*) mutex);
    // bot_os_free(mutex);
}

void bot_mutex_lock(void *mutex)
{
    if (mutex == NULL) {
        return;
    }
    // TODO fibo_mutex_lock(*(unsigned int*) mutex);
}

void bot_mutex_unlock(void *mutex)
{
    if (mutex == NULL) {
        return;
    }
    // TODO fibo_mutex_unlock(*(unsigned int*) mutex);
}

void *bot_sem_create(void)
{
    // unsigned int *sem = (unsigned int *)bot_os_alloc(sizeof(unsigned int));
    // if (NULL == sem) {
    //     return NULL;
    // }

    // // TODO *sem = fibo_sem_new(0);
    // if (NULL == sem) {
    //     bot_os_free(sem);
    //     return NULL;
    // }

    // return sem;
    return NULL;
}

void bot_sem_delete(void *sem)
{
    if (sem == NULL) {
        return;
    }
    // TODO fibo_sem_free(*(unsigned int*)sem);
    bot_os_free(sem);
}

void bot_sem_post(void *sem)
{
    if (sem == NULL) {
        return;
    }
    // TODO fibo_sem_signal(*(unsigned int*) sem);
}

int bot_sem_wait(void *sem, unsigned int timeout_ms)
{
    // int ret = 0;
    // if (sem == NULL) {
    //     return -1;
    // }
    // if (PLATFORM_WAIT_INFINITE == timeout_ms) {
    //     // TODO fibo_sem_wait(*(unsigned int*) sem);
    //     return 0;
    // } else {
    //     // TODO ret= fibo_sem_try_wait(*(unsigned int*) sem, timeout_ms);
    //     return (ret == 0) ? 0 : -1;
    // }
    return 0;
}

void *bot_queue_create(int queue_length, int item_size)
{
    // uint32_t *mq;
    // mq = (uint32_t *)bot_os_alloc(sizeof(uint32_t));
    // // TODO *mq = fibo_queue_create(queue_length, item_size);
    // return (void *)mq;
    return NULL;
}

int bot_queue_delete(void *mq)
{
    // int ret = -1;

    // if (mq == NULL) {
    //     return ret;
    // }

    // // TODO fibo_queue_delete(*(uint32_t*) mq);

    // bot_os_free(mq);

    return 0;
}

int bot_queue_recv(void *mq, void *msg, unsigned int size, unsigned int ms)
{
//     int ret = -1;

//     if (mq == NULL || msg == NULL) {
//         return ret;
//     }

//     // TODO if (fibo_queue_get(*(uint32_t *)mq, msg, ms) < 0) {
//     // TODO     return ret;
//    // TODO  }

    return 0;
}


int bot_queue_send(void *mq, void *msg, unsigned int size, unsigned int ms)
{
    // int ret = -1;

    // if (mq == NULL || msg == NULL) {
    //     return ret;
    // }

    // // TODO if (fibo_queue_put(*(uint32_t*)mq, msg, ms) < 0) {
    // // TODO     return ret;
    // // TODO }

    return 0;
}

int bot_queue_send_isr(void *mq, void *msg, unsigned int size)
{
    // int ret = -1;

    // if (mq == NULL || msg == NULL) {
    //     return ret;
    // }

    // // TODO if (fibo_queue_put_isr(*(uint32_t*)mq, msg) < 0) {
    // // TODO     return ret;
    // // TODO }

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
    // int ret = -1;

    // if (stack_used) {
    //     *stack_used = 0;
    // }

    // // TODO ret=fibo_thread_create(work_routine, task_param->name, task_param->stack_size, (void *)arg, task_param->priority);
    // if (ret != 0) {
    //     return -1;
    // }

    return 0;
}

int bot_task_delete(void *task_handle)
{
    // TODO fibo_thread_delete();
    return 0;
}

int bot_mem_info_get(bot_mem_para_t *mem)
{
    // if (mem == NULL) {
    //     return -1;
    // }

    // mem->start = (void*)&g_mem_space[0];
    // mem->len   = BOT_COMP_MEM_DEFAULT_HEAP_SIZE;

    return 0;
}

/* platform init */
int bot_platform_init(void)
{
    int ret = 0;

//     ret = bot_network_init();
//     if (ret != 0) {
//         bot_printf("bot_network_init fail , ret:%d\n\r", ret);
//         return -1;
//     }

// #if BOT_COMP_GNSS
//     ret = bot_hal_gnss_init();
//     if (ret != 0) {
//         bot_printf("bot_hal_gnss_init fail , ret:%d\n\r", ret);
//         return -1;
//     }
// #endif
    return ret;
}

