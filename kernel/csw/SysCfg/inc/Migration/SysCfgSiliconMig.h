/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************/
/* Filename: SysCfgSiliconMig.h                                         */
/*                                                                      */
/* Author:   Yossi hanin                                                */
/*                                                                      */
/* Description: all SW mini switches that are related to Silicon        */
/* migration should be handle here. Mainly udef when they are == 0      */
/*                                                                      */
/* Remarks:                                                             */
/*                                                                      */
/* Created: 15/08/2007                                                  */
/*                                                                      */
/* Modified:                                                            */
/************************************************************************/

#if !defined(SILICON_CFG_MIG_H)
#define SILICON_CFG_MIG_H

/* Migration - temp*/
#if( _TAVOR_B0_SILICON_ ==0)
//#undef _TAVOR_B0_SILICON_
#endif
#if( _TAVOR_BOERNE_ 	==0)
//#undef _TAVOR_BOERNE
#endif
#if( _TAVOR_HARBELL_ 	==0)
//#undef _TAVOR_HARBELL_
#endif


#endif /* SILICON_CFG_MIG_H */

