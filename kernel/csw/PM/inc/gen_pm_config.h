/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************//*                                                                      */
/* Title: General power managment configuration file                    */
/*                                                                      */
/* Filename: gen_pm_config.h                                            */
/*                                                                      */
/* Author:  Idan Bartura & Amit Sharon                                  */
/*                                                                      */
/* Project, Target, subsystem: Tavor, Boerne, PM Module  		    	*/
/*												                        */
/* Remarks: -                                                           */
/*    										                        	*/
/* Created: 08/06/2009                                                  */
/*                                                                      */
/* Modified:                                                            */
/************************************************************************/
#if !defined (GEN_PM_CONFIG_H)
#define GEN_PM_CONFIG_H

#include "hal_cfg.h"

#if defined FLAVOR_COM
#include "commpm_config.h"
#endif
#if defined FLAVOR_APP
#include "apps_pm_config.h"
#endif
#endif  /* GEN_PM_CONFIG_H */
