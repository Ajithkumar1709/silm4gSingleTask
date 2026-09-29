/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************/
/*  COPYRIGHT (C) 2002 Intel Corporation.                               */
/*                                                                      */
/*  This file and the software in it is furnished under                 */
/*  license and may only be used or copied in accordance with the terms */
/*  of the license. The information in this file is furnished for       */
/*  informational use only, is subject to change without notice, and    */
/*  should not be construed as a commitment by Intel Corporation.       */
/*  Intel Corporation assumes no responsibility or liability for any    */
/*  errors or inaccuracies that may appear in this document or any      */
/*  software that may be provided in association with this document.    */
/*  Except as permitted by such license, no part of this document may   */
/*  be reproduced, stored in a retrieval system, or transmitted in any  */
/*  form or by any means without the express written consent of Intel   */
/*  Corporation.                                                        */
/*                                                                      */
/* Title: Power Management Exceptions Header File                       */
/*                                                                      */
/* Filename: pm_exceptions.h                                            */
/*                                                                      */
/* Author:   Raviv Levi                                                 */
/*                                                                      */
/* Project, Target, subsystem: Tavor, Arbel, HOP     					*/
/*																		*/
/* Remarks: -                                                           */
/*    													                */
/* Created: 11/4/2005                                                   */
/*                                                                      */
/* Modified:  15/2/6 - Change exceptions to L1's request.               */
/*			  17 Dec 06 - remove exceptions solved so far (YK)			*/
/************************************************************************/

////////////////////////////////////////////////////////////
//
//  NOTE - the A0 preparation is in comment till tested on A0 board !!!
//
//   July 19 2006
//
////////////////////////////////////////////////////////////


#ifndef _PM_EXCEPTIONS_H_
    #define _PM_EXCEPTIONS_H_

    #include "global_types.h"
    #include "commccu_def.h"
    #include "mccu_def.h"
    #include "rm_def.h"

    /*
    *  GCKEN (CommCCU) clocks that should be turned on at init.
    * (this list will shorten as packages will start working with the resource manager)
    */

// check with driver!  (dssp bus is implicit from gsspx requests)
// as of July 2006 - I2C has code but under define
// 					GSSP2_CLK - in use by ssp driver (ssp.c) Q to Yossi Ch.
//						Due to problems in SSP - we leave the clock on by defautl and on start.
//						more investigation is needed for SSP with PM and wakeup !!! (6 Sep 2006)
//					USIM_CLK - in use by usim driver (usim_d2.c) Q to Yossi Ch.
// 					DSSP_BUS_CLK- needed fro RM_SRVC_DSSP0_GB (0 to 3) (any of them is set?) Should not be set for A0 (YK think..)
//
// According to Alex R (17 July 2006) GCKEN_GSSP2_CLK clk is not needed at A0
// default on - will be set only once at the chip startup
// Jan 2008 - clean up hte deafault on. For full system we leave only I2C since it will be turn off after driver starts anyway.
#if defined (PLATFORM_ONLY)
// For platform, we need the more clocks to ensure DSP will allow us D2... - not real product...
#define GCKEN_DEFAULT_ON_CLKS              (GCKEN_I2C_CLK   | \
											GCKEN_GSSP2_CLK | \
											GCKEN_DSSP_BUS_CLK | \
											GCKEN_USIM_CLK  )

#else
#define GCKEN_DEFAULT_ON_CLKS              (GCKEN_I2C_CLK) 
#endif
   /*
    * These clocks should not be turned off even if asked due to silicon issues - see
    * documentation for more details.
    *
    * These macros are used in the CommCCU C file.
    */
	// Jan 2008 - no always on in GCKEN. (for platoform, we dont care so much, think we need this for D2 with DSP doing nothing (C1)).
#if defined (PLATFORM_ONLY)
#define GCKEN_ALWAYS_ON_CLKS ( \
	GCKEN_GSSP2_CLK | \
	GCKEN_DSSP_BUS_CLK )
#else
#define GCKEN_ALWAYS_ON_CLKS 0
#endif
    /*
    *  CCCR (CommCCU) clocks that should be turned on at init.
    * (this list will shorten as packages will start working with the resource manager)
	*  CCCR_MODEM_CLK_104MHZ will always be on (needed for the AIRQ)
    */
	// questino to Tsofnat (July 2006)  - 
	// Dec 2006 (YK) - not clear why we must have 208 and 312, but full system does 
	// 		not come up without 312, and does not function well without 208. 
	//		need further investigation. Jan 2008 - still, must have all those clocks present. 
	// 		when trying to remove (312, 208) system does not start up...
	// default on - will be set only once at the chip startup (Jan 2008, to investigate the 312, 208... ?)
    #define CCCR_DEFAULT_ON_CLKS_INIT               (CCCR_MODEM_CLK_104MHZ  | \
													CCCR_MODEM_CLK_312MHZ | \
													CCCR_MODEM_CLK_208MHZ)

    /*
     * These clocks should not be turned off even if asked due to silicon issues - see
     * documentation for more details.	TRUE in Z0/A0 - need to check in ohter silicon versions
     *
     * modem 104 - needed for the AIRQ.
     * These macros are used in the CommCCU C file.
     */
    #define CCCR_ALWAYS_ON_CLKS_INIT                (CCCR_MODEM_CLK_104MHZ)

    /*
    * MCCU clocks that should be turned on at init. (all in one register)
    *
    * The TCU is active low and thus it's bit (#0) needs to be handled separately.
    * SCK (set on and forget z0/a0/and-on  - done by HW. Tsofnat July 18 06)
    */

	#define MCCU_DEFAULT_ON_CLKS_INIT          (SCK_FUNC_CLK_EN_MASK)

    /*
    *  MCCU clocks that should never be turned off.
    * (These clocks are L1 related, L1 code should provide that functionality in the future)
    *
    * The TCU is active low and thus it's bit (#0) needs to be handled separately.
    *
    * Note: The MCCU_ALWAYS_ON_CLKS macro is used to filter out unwanted clock state
    *       changes and should not (!!) be used to turn on clocks at startup.
    *       (Because of the TCU bit...)
    *
    */

	#define MCCU_ALWAYS_ON_CLKS_INIT         (TCU_FUNC_CLK_EN_MASK)

    #define MCCU_FREQ_SEL_BITS                 (SCK_CLK_SEL_MASK        |       \
                                                VITERBI_CLK_SEL_MASK    |       \
                                                EQUALIZER_CLK_SEL_MASK  |       \
                                                CIPHER_CLK_SEL_MASK     |       \
                                                DSSP0_CLK_SEL_MASK      |       \
                                                DSSP1_CLK_SEL_MASK      |       \
                                                DSSP2_CLK_SEL_MASK      |       \
                                                DSSP3_CLK_SEL_MASK)


	// if ISPT is working, it needs the DSSP freq. at 26Mhz
#if defined (ISPT_OVER_SSP)
    #define MCCU_DEFAULT_FREQS                 (SCK_CLK_SEL_26MHZ       |   \
                                                DSSP3_CLK_SEL_26MHZ)
#else
	#define MCCU_DEFAULT_FREQS                 (SCK_CLK_SEL_26MHZ       |   \
											 	DSSP3_CLK_SEL_13MHZ)
#endif

    /*
     * Arbel resources that should not be regarded
     * when making D2 decisions
     *
     * Timer 0 13Mhz should be ignored (there is currently a
     * silicon issue when working with 32KHz)  - still true, Jan 2008
	 * Modem 104 is always on and should be ignored (It is feeding the IRQ)
	 * TCU should be always on (L1 logic request - they never turn the request off, but
	 * 	notify us in different way when they are ready for D2)
	 * VCTCXO- should be ignored as it is external source and we don't care - user use.
     *
     */

    #define RM_D2_DECISION_IGNORED_RSRCS_INIT       (RSRC_TIMER0_13M		 |   \
													RSRC_TCU               |   \
                                                	RSRC_MODEM_104MHZ      |   \
                                                	RSRC_VCTCXO)

    #define DISREGARD_D2_EXCEPTIONS(rEG, iGNOREDrSRCS)         TURN_BIT_OFF((rEG),(iGNOREDrSRCS))
 

#endif  /* _PM_EXCEPTIONS_H_ */
