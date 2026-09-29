/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************/
/* Filename: SysCfgFlavorMig.h                                          */
/*                                                                      */
/* Author:   Yossi hanin                                                */
/*                                                                      */
/* Description: all SW mini switches that are related to Flavor         */
/* migration should be handle here. Mainly udef when they are == 0      */
/*                                                                      */
/* Remarks:                                                             */
/*                                                                      */
/* Created: 15/08/2007                                                  */
/*                                                                      */
/* Modified:                                                            */
/************************************************************************/

#if !defined(FLAVOR_CFG_MIG_H)
#define FLAVOR_CFG__MIG_H

/* Migration - temp*/
#if( MSL_INCLUDE ==0)
//#undef DIAG_OVER_MSL
#endif
#if( DIAG_OVER_MSL ==0)
//#undef DIAG_OVER_MSL
#endif
#if( _DATAOMSL_ENABLED_ ==0)
//#undef DIAG_OVER_MSL
#endif
#if( NVM_OVER_RAM ==0)
//#undef NVM_OVER_RAM
#endif
#if( _FDI_VER_71_ ==0)
//#undef _FDI_VER_71_
#endif
#if( INTEL_FDI ==0)
//#undef INTEL_FDI
#endif


