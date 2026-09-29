/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                 *
 *     File name:      diag_module_cfg.h                                           *
 *     Programmer:     Marcelo Brafman                                             *
 *                                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                 *
 *       Create Date:  June, 2009        	                                       *
 *                                                                                 *
 *       Description: DIAG Configuration File.   								   *
 *                                                                                 *
 *       Notes: This file is used to define all global defines( functionality)	   *
 *		 for Diag. Every define should be commeneted and detailed in this file.    *
 *		 Local defines should be kept in the local file.						   *
 *                                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if !defined (_DIAG_MODULE_CONFIG_H_)
#define _DIAG_MODULE_CONFIG_H_

/* DIAG_TMP_ROOT - the root of 'tmp' dir (Linux mainly, either /tmp or /mrvsys or..  */
#if defined (OSA_LINUX)
#include "paths_defs.h"
#define DIAG_TMP_ROOT TEMP_DIR_NAME
#else 
	#if defined (OSA_WINCE)
	#define DIAG_TMP_ROOT "tmp"
	#endif
#endif

#if defined (OSA_NUCLEUS)
// By default the interface is assumed to be USB - we need a define, as the USB interface
// does not exist in all platforms, and calls to the driver will not compile..
#if !defined (_DIAG_USE_SSP_) && !defined (_DIAG_USE_COMMSTACK_) && !defined (_DIAG_DISABLE_USB_)
	#define _DIAG_USE_USB_
#endif
#endif //OSA_NUCLEUS

/*Define The Working Mode for Internal Interface - Diag can be stand alone*/
#if defined (DIAG_OVER_MSL) && defined (DIAG_OVER_SHMEM)
#error Internal interface can be either MSL or Shared-Memory (not both)
#endif
#undef DIAG_INT_IF		// diag uses internal interface
#if defined (DIAG_OVER_MSL) || defined (DIAG_OVER_SHMEM)
#define DIAG_INT_IF
#endif



/* If we are working in the APP side*/
#if defined (DIAG_APPS)
//#define DIAG_TS_MEASUREMENT
#define DIAG_WRITE_TO_NULL_DEVICE
#define DIAG_DEBUG_MSG_FLOW
/*This define allows the Diag Satistics collection in APP side*/
#if !defined (DO_APPS_STATS)
#define DO_APPS_STATS
#endif

/* This is used to allow BootLoader to be called from Diag - Callback function Registration */
#if defined (OSA_NUCLEUS) 
	#if !defined (DIAG_BOOTLOADER_SUPPORT_ENABLED)
	#define DIAG_BOOTLOADER_SUPPORT_ENABLED
	#endif
#endif

/*This is used in APPS side to emulate the services from KIOS(timestamp and frame number)*/
#if !defined (DIAG_KIOS_SERVICES_EMULATE_ENABLED)
#define DIAG_KIOS_SERVICES_EMULATE_ENABLED
#endif


#else  /*COMM side*/

/*This define allows the Diag Satistics collection in COMM side*/
	#if !defined (DO_COMM_STATS)
		#define DO_COMM_STATS
	#endif

/*This defines the use of cyclic on internal interface*/	
#if defined (DIAG_INT_IF)
	#if !defined (INTIF_CYCLIC_BUFF)
//		#define INTIF_CYCLIC_BUFF 
	#endif
#endif

#endif /*APPS-COMM Side*/

/*This define activate the mode of testing the MMI for commands in Diag while working SD mode*/
#if !defined (ENABLE_DIAG_MMI_TEST)
#define ENABLE_DIAG_MMI_TEST
#endif


/*When working with QT*/
#if defined (DIAG_QT)
	/* The BAUD RATE for the UART should be reduced for support QT*/
	#if !defined (DIAG_USE_SLOW_CLOCK_RATE)
		#define DIAG_USE_SLOW_CLOCK_RATE
	#endif
#endif



#endif

