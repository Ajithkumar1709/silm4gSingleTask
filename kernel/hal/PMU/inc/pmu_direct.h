/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

#ifndef _PMU_DIRECT_H_
#define _PMU_DIRECT_H_
/***************************************************************************************************/
/***************************************************************************************************/

#include "pmu.h"

/***************************************************************************************************/
/***************************************************************************************************/

typedef enum
{
	XPCR,
	XPSR,
	FCCR,
	POCR,
	POSR,
	UCCR,
	CGCR,
	XPRR1,
	XPRR2,
	XCGR,
	XRSR,
	XDCR,
	GPCR,
	RESERVED1,
	RESERVED2,
	XDWR,
	P_SEL_CLK_32K_REG_OFFSET = 0x100          // This is a new register in B3 and the physical offset is 0x400
} PMU_REGS;



typedef enum
{
	VCTCXO_DIV_25K,
	RTC_32K_CLK
}  _32_CLK_SOURCE;


void PMUPeripheralAPBClockDirect ( APBPeripherals     peripheralName , PMUOnOff     onOff );
void PMUPeripheralAPBResetEngageDirect ( APBPeripherals     peripheralName );
void PMUWriteRegisterDirect ( PMU_REGS     pmuReg , UINT32    value );
void PMUReadRegisterDirect ( PMU_REGS     pmuReg , UINT32    *value );
PMU_LastResetStatus PMUGetResetReasonDirect ( void );
void PMUChangeClkTo32K ( void );


/***************************************************************************************************/
/***************************************************************************************************/
#endif
