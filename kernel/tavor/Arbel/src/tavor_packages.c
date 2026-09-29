/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/**********************************************************************
 *
 * Filename: tavor_packages.c
 *
 *
 * Description:  Tavor release information
 * 
 * Cautions:     THIS FILE IS AOUTOGENERATED. MANUAL CHANGES ARE ALLOWED
 *               BUT THEY WILL BE REMOVED IN THE NEXT RELEASE.
 *
 **********************************************************************/
/************ External include files *****************************************/
#include "diag.h"
/************ Local include files ********************************************/
#include "tavor_packages.h"
/************ Local defines **************************************************/

//temporary for L1
#if !defined (L1V_VALIDATION)
int plValTSInit (void) {return 0;}
#endif
/***************************************************************************/
// Function: tavorPackagesGet
// ICAT EXPORTED FUNCTION - SW_PLAT, TAVOR, TAVOR_Packages
void tavorPackagesGet (void)
{
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages1, DIAG_INFORMATION)	
	diagPrintf (TAVOR_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages2, DIAG_INFORMATION)	
	diagPrintf (HOP_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages4, DIAG_INFORMATION)	
	diagPrintf (OSA_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages5, DIAG_INFORMATION)	
	diagPrintf (PREPASS_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages6, DIAG_INFORMATION)	
	diagPrintf (SOFTUTIL_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages8, DIAG_INFORMATION)	
	diagPrintf (ENV_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages9, DIAG_INFORMATION)	
	diagPrintf (APLP_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages10, DIAG_INFORMATION)	
	diagPrintf (GPLC_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages11, DIAG_INFORMATION)	
	diagPrintf (DRAT_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages12, DIAG_INFORMATION)	
	diagPrintf (AUD_SW_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages13, DIAG_INFORMATION)	
	diagPrintf (_3G_PS_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages14, DIAG_INFORMATION)	
	diagPrintf (L1P_FW_TARGETS_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages15, DIAG_INFORMATION)	
	diagPrintf (CFW_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages16, DIAG_INFORMATION)	
	diagPrintf (GSM_FW_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages17, DIAG_INFORMATION)	
	diagPrintf (WB_FW_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages18, DIAG_INFORMATION)	
	diagPrintf (WB_GSM_IF_VER);
	DIAG_FILTER(SW_PLAT, TAVOR_VER_INFO, TAVOR_Packages19, DIAG_INFORMATION)	
	diagPrintf (TAVOR_OBM_VER);
}

