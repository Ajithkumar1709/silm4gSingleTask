#ifndef __JPTT_DEBUG_H__
#define __JPTT_DEBUG_H__
#include "uart.h"
#include "mbtk_log.h"


#ifdef NO_DEBUG_LOG
 #define DEBUG_D(format,...)
 #define DEBUG_I(format,...)
#else
 #define DEBUG_D(format,...) MLOG_D(MLOG_POC,POC, format,##__VA_ARGS__)
 #define DEBUG_I(format,...) MLOG_I(MLOG_POC,POC, format,##__VA_ARGS__)
#endif

#define DEBUG_E(format,...) MLOG_E(MLOG_POC,POC, format,##__VA_ARGS__)


#endif
