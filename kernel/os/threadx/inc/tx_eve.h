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

#ifndef TX_EVE_H
#define TX_EVE_H

#include "tx_event_flags.h"

#define tx_event_flags_name     tx_event_flags_group_name
#define tx_event_flags_current  tx_event_flags_group_current
#define tx_event_flags_id       tx_event_flags_group_id

#endif

#endif
