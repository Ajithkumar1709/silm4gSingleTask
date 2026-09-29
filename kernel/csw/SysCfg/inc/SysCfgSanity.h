/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************/
/* Filename: SysCfgSanity.h                                             */
/*                                                                      */
/* Author:   Yossi hanin                                                */
/*                                                                      */
/* Description: Sanity file , all check-up for correct user target      */
/* variants are made here - checks legal Mega swithces                  */
/* TV from make file: inc_sysCfg.mak                                    */
/* Remarks:                                                             */
/*                                                                      */
/* Created: 15/08/2007                                                  */
/*                                                                      */
/* Modified:                                                            */
/************************************************************************/

#if !defined(SANITY_CFG_H)
#define SANITY_CFG_H
/*########################## start of configure file #####################*/

/* Defined from the make file: inc_SysCfg.mak    */
//# SIDE ######################################
// 	APP
// 	COM
//# SILICON ###################################
// 	HERMON
// 	TAVORP
// 	TAVORPV
// 	HERMON2
// 	MMP
//# STEPPING ##################################
// 	STEP_Z0
// 	STEP_A0
// 	STEP_B0
// 	STEP_C0

/*### test >>>###*/
//#if (TAVORP & APP & STEP_B0)
//#error TAVORP & APP & STEP_B0
//#endif

//#if (MMP & APP & STEP_Z0 & EVB)
//#error MMP & APP & STEP_Z0 & EVB
//#endif
/*### test <<<###*/

/*### sanity SILICON_TYPE >>>###*/
#if (( HERMON + TAVORP + TAVORPV + HERMON2 + MMP) == 0)
#error NO_SILICON_WAS_DEFINE_IN_TARGET_VARIANT
#elif (( HERMON + TAVORP + TAVORPV + HERMON2 + MMP) > 1)
#error MORE_THEN_ONE_SILICON_TYPE_WAS_DEFINE_IN_TARGET_VARIANT
#endif
/*### sanity <<<###*/


/* Defined from the make file: inc_SysCfg.mak    */
//# Platfrom  ######################################
// 	EVB
// 	PDK
// 	YARDEN
// SAAR
//  QT

/*### sanity PLATFORM_TYPE >>>###*/
#if (( EVB + PDK + YARDEN + SAAR  ) == 0)
#error NO_PLATFROM_WAS_DEFINE_IN_TARGET_VARIANT
#elif (( EVB + PDK + YARDEN + SAAR) > 1)
#error MORE_THEN_ONE_PLATFROM_TYPE_WAS_DEFINE_IN_TARGET_VARIANT
#endif
/*### sanity <<<###*/


/* Defined from the make file: inc_SysCfg.mak    */
//# Flavor  ######################################
// 	PLAT
// 	MODEM_ONLY
// 	L1
// 	FULSYS
// 	QT
/*### sanity  FLAVOR_TYPE >>>###*/
#if (( COM + APP  ) == 0)
#error NO_SIDE_WAS_DEFINE_IN_TARGET_VARIANT
#elif (( COM + APP  ) > 1)
#error MORE_THEN_ONE_SIDE_WAS_DEFINE_IN_TARGET_VARIANT
#endif
#if (( PLAT + L1 + FULSYS + QT  ) == 0)
#error NO_FLAVOR_WAS_DEFINE_IN_TARGET_VARIANT
#elif (( PLAT + L1 + FULSYS + QT  ) > 1)
#error MORE_THEN_ONE_FLAVOR_TYPE_WAS_DEFINE_IN_TARGET_VARIANT
#endif
/*### sanity <<<###*/

/*### test >>>###*/
//#if (SILICON_TYPE == SILICON_MMP_APP_Z0)
//#error SILICON_MMP_APP_Z0
//#endif
//#if (PLATFORM_TYPE == PLATFORM_MMP_EVB)
//#error PLATFORM_MMP_EVB
//#endif
//#if (FLAVOR_TYPE == FLAVOR_PLATFROM_APP)
//#error FLAVOR_PLATFROM_APP
//#endif
/*### test <<<###*/


/*###################### end of configure file ##########################*/
#endif /* SANITY_CFG_H */

