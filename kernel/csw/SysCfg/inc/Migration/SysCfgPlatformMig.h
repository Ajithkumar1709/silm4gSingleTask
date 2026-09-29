/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************/
/* Filename: SysCfgPlatfromMig.h                                        */
/*                                                                      */
/* Author:   Yossi hanin                                                */
/*                                                                      */
/* Description: all SW mini switches that are related to Platfrom       */
/* migration should be handle here. Mainly udef when they are == 0      */
/*                                                                      */
/* Remarks:                                                             */
/*                                                                      */
/* Created: 15/08/2007                                                  */
/*                                                                      */
/* Modified:                                                            */
/************************************************************************/
#if !defined(PLATFROM_CFG_MIG_H)
#define PLATFROM_CFG_MIG_H

/* Migration - temp*/
#if( _MICCO_A0_ == 0)
//#undef _MICCO_A0_
#endif
#if( PMC_MICCO_A0 == 0)
//#undef PMC_MICCO_A0
#endif
#if( _MICCO_B0_	== 0)
//#undef _MICCO_B0_
#endif
#if( PMC_MICCO_B0 == 0)
//#undef PMC_MICCO_B0
#endif

#endif /* PLATFROM_CFG_MIG_H */

