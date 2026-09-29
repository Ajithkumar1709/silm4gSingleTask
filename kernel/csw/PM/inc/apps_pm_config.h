/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************//*                                                                      */
/* Title: Boerne Power Manager configuration							*/
/*                                                                      */
/* Filename: apps_pm_config                                             */
/*                                                                      */
/* Author:   Amit Sharon                                                */
/*                                                                      */
/* Project, Target, subsystem: Tavor, Boerne, PMBRN						*/
/*																		*/
/* Remarks: -                                                           */
/*    													                */
/* Created: 03/06/2009                                                  */
/*                                                                      */
/* Modified:                                                            */
/************************************************************************/

#if !defined (APPS_PM_CONFIG_H)
#define APPS_PM_CONFIG_H
//#if defined (PM_DEBUG_MODE_ENABLED)
#if 0
#define APPS_PM_DEBUG_ENABLED
// from PM generic log - initiate printout under PMDEBUG
// TEMP - with PMDEBUG also other debug modes are enabled
#define PM_ENABLE_D0_TIME	// activate wait time in D0
#define PM_ENABLE_FC_PRINT	// activate print on Freq change
//#define TEST_D2_SRAM_REGS
#endif  /* PM_DEBUG_MODE_ENABLED */

// This allows the function PRMServiceFreqSet in prm_brn.c to actually change the frequency. it is now disabled.
// #define PRM_SET_SERVICE_FREQUENCY_ENABLE
#if defined (_QT_)

#define PRE_SILICON_FREQ_CHANGE_DISABLE

#endif  /* _QT_ */

#if defined (PLATFROM_ONLY)
// Activate GPIO106 toggling.
//#define BRN_PM_ENABLE_GPIO_DVFM_EXECUTE
#endif

#if !defined (PLATFORM_ONLY) && !defined(NO_AUDIO)

#define PM_BRN_ACM_TEST_ENABLE

#endif  /* PLATFORM_ONLY && NO_AUDIO*/
	//For testing only of very high freq... (for 1 Ghz)
	// #define BRN_FREQ_SYSTEM_TEST

	// BRN_LOCK_PM_LLD was not defined so it is disabled
	// #define BRN_LOCK_PM_LLD

	/*For each write to any service unit register, need to wait 2 slow clocks till next write to the same register.
	 *Hence, it is possible to check if 2 slow clocks passed before each write to register, or simply force delay
	 * after every write to service unit registers.
	 */
	#define	SCCU_FORCE_2_SC_DELAY_AFTER_EACH_WRITE

	/*For each write to any service unit register, need to wait 2 slow clocks till next write to the same register.
	 *Hence, it is possible to check if 2 slow clocks passed before each write to register, or simply force delay
	 * after every write to service unit registers.
	 */
	#define	MPMU_FORCE_2_SC_DELAY_AFTER_EACH_WRITE

// TTC configuration
//this configuration selects between AP and CP hardware PMU address.
#if defined (SILICON_TTC_CORE_SEAGULL)
	#define	MY_PMU_REGS_SELECT
#endif /* SILICON_TTC_CORE_SEAGULL */

//defining different frequency when running on emulator
#if defined (_QT_)
	#define PRE_SILICON_UCCR_FREQUENCY
#endif  /* _QT_ */
#endif  /* APPS_PM_INT_H */
