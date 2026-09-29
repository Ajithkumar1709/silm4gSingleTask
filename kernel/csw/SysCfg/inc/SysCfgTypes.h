/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************/
/* Filename: SysCfgTypes.h                                              */
/*                                                                      */
/* Author:   Yossi hanin                                                */
/*                                                                      */
/* Description: types that are being used by compile SW configuration   */
/* files.                                                               */
/* Remarks:                                                             */
/*                                                                      */
/* Created: 15/08/2007                                                  */
/*                                                                      */
/* Modified:                                                            */
/************************************************************************/

#if !defined(TYPE_CFG_H)
#define TYPE_CFG_H


/* silicon defines */
#define SILICON_HERMON_B0          0x01
#define SILICON_HARBEL_P_A0    	   0x02
#define SILICON_BOERNE_P_A0    	   0x03
#define SILICON_HARBEL_P_B0    	   0x04
#define SILICON_BOERNE_P_B0    	   0x05
#define SILICON_HARBEL_PV_A0   	   0x06
#define SILICON_BOERNE_PV_A0   	   0x07
#define SILICON_HARBEL_PV2_A0  	   0x08
#define SILICON_BOERNE_PV2_A0  	   0x09
#define SILICON_HERMON2_946_Z0 	   0x0A
#define SILICON_HERMON2_926_Z0 	   0x0B
#define SILICON_MMP_APP_Z0     	   0x0C
#define SILICON_MMP_COM_Z0     	   0x0D
#define SILICON_TYPE_ERROR         0x0E

/* Platforms defines */
#define PLATFORM_HERMON_EVB    	   0x10
#define PLATFORM_HERMON_PDK    	   0x11
#define PLATFORM_TAVOR_EVB     	   0x12
#define PLATFORM_TAVOR_QT          0x13
#define PLATFORM_TAVOR_YARDEN_EVB  0x14
#define PLATFORM_TAVOR_PV_EVB  	   0x15
#define PLATFORM_TAVOR_PV_QT       0x16
#define PLATFORM_TAVOR_SAAR_RD 	   0x17
#define PLATFORM_HERMON2_SAAR_RD   0x18
#define PLATFORM_HERMON2_QT        0x19
#define PLATFORM_MMP_EVB       	   0x1A
#define PLATFORM_MMP_QT            0x1B
#define PLATFORM_TYPE_ERROR    	   0x1C

/* Flavor defines */
#define FLAVOR_PLATFROM_COM        0x1D
#define FLAVOR_MODEM_ONLY_COM      0x1E
#define FLAVOR_L1_COM          	   0x1F
#define FLAVOR_FULL_SYS_COM    	   0x20
#define FLAVOR_QT_COM              0x21/*for changes that are related to SW features which are not used in QT such as: DATAOMSL*/
#define FLAVOR_PLATFROM_APP    	   0x22
#define FLAVOR_MODEM_ONLY_APP  	   0x23
#define FLAVOR_L1_APP          	   0x24
#define FLAVOR_FULL_SYS_APP    	   0x25
#define FLAVOR_QT_APP          	   0x26/*for changes that are related to SW features which are not used in QT such as: DATAOMSL*/
#define FLAVOR_TYPE_ERROR          0x27

#endif /* TYPE_CFG_H */

