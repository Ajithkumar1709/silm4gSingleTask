/***********************************************************
* (c) Copyright 2011 Marvell International Ltd.
*
*               Marvell Confidential
* ==========================================================
*/

/*
 *  This is a shim file to allow for compatability between ThreadX 4
 *  and ThreadX 5.1. 
 */
 
#ifdef PLAT_USE_THREADX 

#ifndef TX_THR_H
#define TX_THR_H

#include "tx_thread.h"

#define tx_stack_start            tx_thread_stack_start
#define tx_stack_end              tx_thread_stack_end
#define tx_stack_ptr              tx_thread_stack_ptr
#define tx_stack_size             tx_thread_stack_size
#define tx_created_next           tx_thread_created_next
#define tx_state                  tx_thread_state
#define tx_priority               tx_thread_priority
#define tx_run_count              tx_thread_run_count
#define tx_suspend_control_block  tx_thread_suspend_control_block
#define tx_suspend_option         tx_thread_suspend_option
#define tx_suspend_info           tx_thread_suspend_info
#define tx_remaining_ticks        tx_timer_internal_remaining_ticks

#endif

#endif
