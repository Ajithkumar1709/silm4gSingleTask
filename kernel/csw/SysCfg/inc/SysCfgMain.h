/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************/
/* Filename: SysCfgMain.h                                               */
/*                                                                      */
/* Author:   Yossi hanin                                                */
/*                                                                      */
/* Description: main configuration file, here the Mega SW:silicon,      */
/* Platfrom and Flavor will be defined - inputs to this file from       */
/* make file: inc_sysCfg.mak                                            */
/* Remarks:                                                             */
/*                                                                      */
/* Created: 15/08/2007                                                  */
/*                                                                      */
/* Modified:                                                            */
/************************************************************************/

#if !defined(MAIN_CFG_H)
#define MAIN_CFG_H
/*########################## start of configure file #####################*/
#include "SysCfgTypes.h"

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

#define SILICON_TYPE   (                                                                   	   \
                           	    (HERMON	& STEP_B0)         	 ? SILICON_HERMON_B0   	    :(    \
                               	(TAVORP & COM & STEP_A0)   	 ? SILICON_HARBEL_P_A0 	    :(    \
                               	(TAVORP & APP & STEP_A0)   	 ? SILICON_BOERNE_P_A0     	:(    \
                               	(TAVORP & COM & STEP_B0)   	 ? SILICON_HARBEL_P_B0     	:(    \
                               	(TAVORP & APP & STEP_B0)   	 ? SILICON_BOERNE_P_B0     	:(    \
                               	(TAVORPV & COM & STEP_A0)  	 ? SILICON_HARBEL_PV_A0    	:(    \
                               	(TAVORPV & APP & STEP_A0)  	 ? SILICON_BOERNE_PV_A0    	:(    \
                               	(HERMON2 & COM & STEP_Z0)  	 ? SILICON_HERMON2_946_Z0  	:(    \
                               	(HERMON2 & APP & STEP_Z0)  	 ? SILICON_HERMON2_926_Z0  	:(    \
                               	(HERMON2 & COM & STEP_A0)  	 ? SILICON_HERMON2_946_A0  	:(    \
                                (HERMON2 & APP & STEP_A0)  	 ? SILICON_HERMON2_926_A0  	:(    \
                               	(MMP & COM & STEP_Z0)      	 ? SILICON_MMP_COM_Z0      	:(    \
                               	(MMP & APP & STEP_Z0)      	 ? SILICON_MMP_APP_Z0      	:(    \
                               	SILICON_TYPE_ERROR )))))))))))))                              \
                   	  )


#if (SILICON_TYPE == SILICON_TYPE_ERROR)
#error MUST_CHOOSE_SILICON_TYPE_FROM_TARGET_VARAINT
#endif

/* Defined from the make file: inc_SysCfg.mak    */
//# Platfrom  ######################################
// 	EVB
// 	PDK
// 	YARDEN
// SAAR
//  QT

#define PLATFORM_TYPE   (                                                                      \
                               	 (HERMON   	& EVB)     	   	? PLATFORM_HERMON_EVB      	 :(    \
                               	 (HERMON   	& PDK) 	       	? PLATFORM_HERMON_PDK      	 :(    \
                               	 (TAVORP   	& EVB)         	? PLATFORM_TAVOR_EVB   	     :(    \
                               	 (TAVORP   	& QT)           ? PLATFORM_TAVOR_QT          :(    \
                               	 (TAVORP   	& YARDEN)      	? PLATFORM_TAVOR_YARDEN_EVB  :(    \
                               	 (TAVORPV  	& EVB)         	? PLATFORM_TAVOR_PV_EVB    	 :(    \
                               	 (TAVORPV  	& QT)          	? PLATFORM_TAVOR_PV_QT     	 :(    \
                                 (TAVORPV  	& SAAR)        	? PLATFORM_TAVOR_SAAR_RD   	 :(    \
                               	 (HERMON2  	& SAAR)        	? PLATFORM_HERMON2_SAAR_RD 	 :(    \
                               	 (HERMON2  	& QT)          	? PLATFORM_HERMON2_QT      	 :(    \
                               	 (MMP      	& EVB)         	? PLATFORM_MMP_EVB         	 :(    \
                               	 (MMP      	& QT)          	? PLATFORM_MMP_QT          	 :(    \
                               	PLATFORM_TYPE_ERROR))))))))))))                                \
                       )


#if (PLATFORM_TYPE == PLATFORM_TYPE_ERROR)
#error MUST_CHOOSE_PLATFROM_TYPE_FROM_TARGET_VARAINT
#endif

/* Defined from the make file: inc_SysCfg.mak    */
//# Flavor  ######################################
// 	PLAT
// 	MODEM_ONLY
// 	L1
// 	FULSYS
// 	QT

#define FLAVOR_TYPE   (                                                                               \
                               	 ( PLAT    	& COM)     	           	? FLAVOR_PLATFROM_COM      	:(    \
                               	 ( PLAT    	& COM & MODEM_ONLY )   	? FLAVOR_MODEM_ONLY_COM	   	:(    \
                               	 ( L1      	& COM)                 	? FLAVOR_L1_COM            	:(    \
                                 (FULSYS   	& COM)                 	? FLAVOR_FULL_SYS_COM      	:(    \
                                 (QT       	& COM)                 	? FLAVOR_QT_COM            	:(    \
                                 ( PLAT    	& APP)     	           	? FLAVOR_PLATFROM_APP  	   	:(    \
                               	 ( PLAT    	& APP & MODEM_ONLY )   	? FLAVOR_MODEM_ONLY_APP	   	:(    \
                               	 ( L1      	& APP)                 	? FLAVOR_L1_APP            	:(    \
                               	 (FULSYS   	& APP)                 	? FLAVOR_FULL_SYS_APP      	:(    \
                               	 (QT       	& APP)                 	? FLAVOR_QT_APP            	:(    \
                                 FLAVOR_TYPE_ERROR))))))))))                                          \
                       )

#if (FLAVOR_TYPE == FLAVOR_TYPE_ERROR)
#error MUST_CHOOSE_FLAVOR_TYPE_FROM_TARGET_VARAINT
#endif

#include "SysCfgSanity.h"
/*###################### end of configure file ##########################*/
#endif /* MAIN_CFG_H */

