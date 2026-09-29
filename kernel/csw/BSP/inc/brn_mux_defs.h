/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/******************************************************************************
**
**  COPYRIGHT (C) 2005 Intel Corporation.
**
**  This software as well as the software described in it is furnished under
**  license and may only be used or copied in accordance with the terms of the
**  license. The information in this file is furnished for informational use
**  only, is subject to change without notice, and should not be construed as
**  a commitment by Intel Corporation. Intel Corporation assumes no
**  responsibility or liability for any errors or inaccuracies that may appear
**  in this document or any software that may be provided in association with
**  this document.
**  Except as permitted by such license, no part of this document may be
**  reproduced, stored in a retrieval system, or transmitted in any form or by
**  any means without the express written consent of Intel Corporation.
**
**  FILENAME:	brn_mux_defs.h
**
**  PURPOSE: 	This file provides Tavor platform Pin MUX driver definitions
**
******************************************************************************/


// Tavor pin MUX  definitions//
#ifndef _TAVOR_MUX_DEFS_H_
#define _TAVOR_MUX_DEFS_H_

#include "brn_A0_mfpr.h"


// pull_sel, pullup_en, pulldn_en - bits 15:13
//ICAT EXPORTED ENUM
typedef	enum	_PadPull
{
	PULL_SEL_ALT_FUN		=  	0x0000,
	PULL_SEL_UP_RESISTOR    = 	0xC000,
	PULL_SEL_DN_RESISTOR    = 	0xA000
}PadPull;
#define	PULL_SEL_GET_MASK			0xE000
#define	PULL_SEL_SET_MASK			(~PULL_SEL_GET_MASK)

// drive - bits 12:10
//ICAT EXPORTED ENUM
typedef	enum	_PadDrive
{
	DRIVE_FAST_1mA	 =	0x0000,
	DRIVE_FAST_2mA	 =	0x0400,
	DRIVE_FAST_3mA	 =	0x0800,
	DRIVE_FAST_4mA	 =	0x0C00,
	DRIVE_SLOW_6mA	 =	0x1000,
	DRIVE_FAST_6mA	 =	0x1400,
	DRIVE_SLOW_10mA	 =	0x1800,
	DRIVE_FAST_10mA	 =	0x1C00
}PadDrive;

#define	DRIVE_GET_MASK   			0x1C00
#define	DRIVE_SET_MASK   			(~DRIVE_GET_MASK)

//ICAT EXPORTED ENUM
typedef	enum	_PadSleep
{
// sleep_sel - bit 9
	SLEEP_BPMU_MODE_CONTROL				=	0x000,    //BPMU firewall signal controls the sleep mode of the pin
	SLEEP_CPMU_MODE_CONTROL    			=	0x200,    //CPMU firewall signal controls the sleep mode of the pin
// sleep_data - bit 8
	SLEEP_DATA_1               			=	0x100,
	SLEEP_DATA_0               			=	0x000,
// sleep_oe_n - bit 7
	SLEEP_MODE_DIRECTION_OUTPUT  		=	0x00,
	SLEEP_MODE_DIRECTION_INTPUT  		=	0x80
}PadSleep;

#define	SLEEP_MODE_GET_MASK   			0x380
#define	SLEEP_MODE_SET_MASK   			(~SLEEP_MODE_GET_MASK)

// edge_clear, edge_fall_en, edge_rise_en - bits 6:4
//ICAT EXPORTED ENUM
typedef	enum	_PadEdge
{
	EDGE_FALL_ENABLE                	=	0x20,
	EDGE_RISE_ENABLE                	=	0x10,
	EDGE_RISE_AND_FALL_ENABLE       	=	0x30,
	EDGE_DISABLE                    	=	0x40
}PadEdge;

#define EDGE_GET_MASK					 0x70
#define EDGE_SET_MASK					 (~EDGE_GET_MASK)

// af_sel - bits 2:0
//ICAT EXPORTED ENUM
typedef	enum	_PadAltFn
{
	ALT_FUNC_0			=	0x0,
	ALT_FUNC_1			=	0x1,
	ALT_FUNC_2			=	0x2,
	ALT_FUNC_3			=	0x3,
	ALT_FUNC_4			=	0x4,
	ALT_FUNC_5			=	0x5,
	ALT_FUNC_6	    	=	0x6,
	ALT_FUNC_7			=	0x7
}PadAltFn;

#define ALT_FUNC_DEF   	ALT_FUNC_0
#define	ALT_FUNC_SET_MASK	(~ALT_FUNC_7)	//mask for setting new alt function value
#define	ALT_FUNC_GET_MASK	(ALT_FUNC_7)		//maks for getting current alt function value



//ICAT EXPORTED STRUCT
typedef	struct	_PadParams
{
	PadAltFn	AltFn;
	PadEdge		Edge;
	PadSleep	Sleep;
	PadDrive	Drive;
	PadPull		Pull;
}PadParams;


//ICAT EXPORTED ENUM
typedef	enum	_MUX_RC_Code
{
	MUX_RC_SUCCESS,				// = 0
	MUX_RC_LOCK_FAILED,			// = 1
	MUX_RC_PAD_LOCKED			// = 2
}MUX_RC_Code;

typedef	unsigned	long	PadLockID;

//ICAT EXPORTED STRUCT
typedef	struct	_PadLockInfo
{
	PadName		Name;
	PadLockID	LockID;
}PadLockInfo;

typedef	struct	_PadLockList
{
	unsigned long	NumberOfPads;
	PadLockInfo		PadInfo	[1];

}PadLockList;

#endif //_TAVOR_MUX_DEFS_H_


