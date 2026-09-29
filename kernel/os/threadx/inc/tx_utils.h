#ifndef TX_UTILS_H
#define TX_UTILS_H

#if 0
typedef unsigned int timer_t;
typedef unsigned int clockid_t;

#define DEFAULT_TIME_SLICE  20

struct timespec
{
    timer_t tv_nsec;
    long    tv_sec;
};


struct itimerspec
{
    struct timespec it_interval;
    struct timespec it_value;
};

#define CLOCK_REALTIME    1
#else
#include "time.h"

#define DEFAULT_TIME_SLICE  20

extern size_t strnlen(const char *str, size_t maxlen);

#endif

#endif
