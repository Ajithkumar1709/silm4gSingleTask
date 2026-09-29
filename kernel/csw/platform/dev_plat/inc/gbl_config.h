/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ============================================================================
File        : gbl_config.h
Description : Global configuration file for testing the
              os/kal package.

Notes       : This file is only used to test the compilation and
              archiving for the os/kal package.

Copyright 2001, Intel Corporation, All rights reserved.
============================================================================ */

#if !defined(_GBL_CONFIG_H_)
#define _GBL_CONFIG_H_

#ifdef OSA_MEM_POOLS // from osa_config.h
#undef OSA_MEM_POOLS
#undef OSA_SEMAPHORES
#undef OSA_MBOX_QUEUES
#undef OSA_TASKS
#undef OSA_MESSAGING_POOL_SIZE
#undef OSA_MSG_QUEUES
#undef OSA_TIMERS

// Re-define according to system needs
//---------------------------------------------
#if defined(INTEL_2CHIP_PLAT) || defined (HERMON_MCP2_CFG)
//     Decrease RAM usage...
//---------------------------------------------
	#define OSA_MEM_POOLS       36
	#define OSA_TASKS           20
	#if defined (_TAVOR_BOERNE_)		//when working with UART needs more tasks
		#undef OSA_TASKS
		#define OSA_TASKS           30
	#endif
	#define OSA_SEMAPHORES      OSA_MEM_POOLS
	#define OSA_MBOX_QUEUES     OSA_TASKS
	#define OSA_MESSAGING_POOL_SIZE 16384	//Decrease pool to former size, no need for 90000
	#define OSA_MSG_QUEUES      25
	#define OSA_TIMERS          30
	#undef  OSA_MUTEXES
#define OSA_MUTEXES         16 /*24*/
#undef  OSA_INTERRUPTS
#define OSA_INTERRUPTS      1
//---------------------------------------------
#else  /*INTEL_2CHIP_PLAT*/

//---------------------------------------------
#if defined(HERMON_MVT)

#define OSA_MVT_ADD_TASKS           10
#define OSA_MVT_ADD_SEMAPHORES      190
#define OSA_MVT_ADD_MBOX_QUEUES     14
#define OSA_MVT_ADD_MSG_QUEUES      15
#define OSA_MVT_ADD_TIMERS 			30
#undef  OSA_MUTEXES
#define OSA_MUTEXES      			45

#else  /*------- HERMON_MVT ------*/

#define OSA_MVT_ADD_TASKS           0
#define OSA_MVT_ADD_SEMAPHORES      0
#define OSA_MVT_ADD_MBOX_QUEUES     0
#define OSA_MVT_ADD_MSG_QUEUES      0
#define OSA_MVT_ADD_TIMERS 			0

#endif  /*------- HERMON_MVT ------*/

#if (NO_APLP==1)
  #define OSA_MEM_POOLS       		40
#if !defined(_DIAG_USE_COMMSTACK_)
  #define OSA_TASKS         		22
  #define OSA_SEMAPHORES      		30
#else // _DIAG_USE_COMMSTACK_
  #define OSA_TASKS         		30	// increased for UART
  #define OSA_SEMAPHORES      		40  // increase number for UART usage (diag)
#endif
  #define OSA_MBOX_QUEUES     		10
  #define OSA_MESSAGING_POOL_SIZE 	30000
  #define OSA_MSG_QUEUES      		20
  #define OSA_TIMERS                16
#else
#define OSA_MEM_POOLS       50
#define OSA_TASKS           (OSA_MVT_ADD_TASKS + 20)
#define OSA_SEMAPHORES      (OSA_MVT_ADD_SEMAPHORES  + (OSA_MEM_POOLS + 10))
#define OSA_MBOX_QUEUES     (OSA_MVT_ADD_MBOX_QUEUES + OSA_MEM_POOLS)
#define OSA_MESSAGING_POOL_SIZE 65536	//Decrease pool to former size, no need for 90000
#define OSA_MSG_QUEUES      (OSA_MVT_ADD_MSG_QUEUES + 25)
#define OSA_TIMERS 			(OSA_MVT_ADD_TIMERS + 50)
#endif//NO_APLP

//---------------------------------------------
#endif/*INTEL_2CHIP_PLAT*/

#endif/*OSA_MEM_POOLS*/



//#if !defined (INTEL_2CHIP_PLAT) && !defined(_TAVOR_HARBELL_) && !defined(SILICON_PV2)
#if !defined (INTEL_2CHIP_PLAT) && !defined(SILICON_PV2)
#undef  OSA_INTERRUPTS
#define OSA_INTERRUPTS 0
#else
#undef  OSA_INTERRUPTS
#define OSA_INTERRUPTS 1
#endif

#if defined (INTEL_2CHIP_PLAT) && !defined (INTEL_2CHIP_PLAT_BVD)
 /* Global configurations required and used by 2CHIP PCA components only */
  #ifdef CI_PS_MAX_PDP_CTX_NUM
  #undef  CI_PS_MAX_PDP_CTX_NUM
  #define CI_PS_MAX_PDP_CTX_NUM 2
  #endif

  #ifdef CI_SYS_INIT_TIME_OUT
  #undef  CI_SYS_INIT_TIME_OUT
  #define CI_SYS_INIT_TIME_OUT  0x00007530 // configurable
  #undef  CI_SYS_DEINIT_TIME_OUT
  #define CI_SYS_DEINIT_TIME_OUT 0x00001000
  #endif

  #ifdef MSL_MTU_SIZE
  #undef  MSL_MTU_SIZE

  #ifdef MSL_DATA_CHECKSUM
    #define MSL_MTU_SIZE 0x782
  #else
    #define MSL_MTU_SIZE 0x780
  #endif

  #endif
#endif


#define OSA_DEBUG
/* OSA 2.3.4 and above support queue names as an API option to supply a queue name to OSAMsgQCreate
 * (enabled by macro OSA_QUEUE_NAMES, default: off).
 * This presents a non backwards-compatible API change.
 * Any code using OSAMsgQCreate must be able to supply the added parameter.
 * For compatibility with previous OSA version undefine the below switch.
 * A compilation failure would occur if an old OSA version was used along with OSA_QUEUE_NAMES defined.
 * */
#if !defined(OSA_QUEUE_NAMES)
#define OSA_QUEUE_NAMES
#endif

#define OSA_NO_PRIORITY_CONVERSION

#if defined(HERMON_MVT)
#define OSA_TLS
#endif

#endif /* _GBL_CONFIG_H_ */

/*                      end of gbl_config.h
--------------------------------------------------------------------------- */

