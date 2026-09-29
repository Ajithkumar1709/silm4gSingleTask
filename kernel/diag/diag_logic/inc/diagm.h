/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
INTEL CONFIDENTIAL
Copyright 2006 Intel Corporation All Rights Reserved.
The source code contained or described herein and all documents related to the source code ("Material") are owned
by Intel Corporation or its suppliers or licensors. Title to the Material remains with Intel Corporation or
its suppliers and licensors. The Material contains trade secrets and proprietary and confidential information of
Intel or its suppliers and licensors. The Material is protected by worldwide copyright and trade secret laws and
treaty provisions. No part of the Material may be used, copied, reproduced, modified, published, uploaded, posted,
transmitted, distributed, or disclosed in any way without Intel's prior express written permission.

No license under any patent, copyright, trade secret or other intellectual property right is granted to or
conferred upon you by disclosure or delivery of the Materials, either expressly, by implication, inducement,
estoppel or otherwise. Any license under such intellectual property rights must be express and approved by
Intel in writing.
-------------------------------------------------------------------------------------------------------------------*/

#if !defined (DIAGM_H)
#define     DIAGM_H
/*
    File Id.
    --------
*/
/*0-10 for General traces*/
#define     DIAGM_PRINTF            0
#define     DIAGM_TTPCOM            1
#define     DIAGM_MODULE            2

/*10-200 for L1 traces */
#define     DIAGM_L1FRINT           11
#define     DIAGM_MAIN_INIT         12
#define     DIAGM_SQSFSRX           13
#define     DIAGM_L1BGTASK          14
#define     DIAGM_L1BGDED           15
#define     DIAGM_L1BGESTB          16
#define     DIAGM_L1BGIDLE          17
#define     DIAGM_L1BGMEAS          18
#define     DIAGM_L1BGSYNC          19
#define     DIAGM_L1FRDED           20
#define     DIAGM_L1FRIDLE          21
#define     DIAGM_SQSFSRAD          22
#define     DIAGM_L1FRMEAS          23
#define     DIAGM_L1FRNULL          24
#define     DIAGM_L1FRSYNC          25
#define     DIAGM_L1PHTASK          26
#define     DIAGM_L1FRSEQ           27
#define     DIAGM_L1FRTCB           28
#define     DIAGM_L1CELL            29
#define     DIAGM_L1SDTASK          30
#define     DIAGM_L1FRSIG           31
#define     DIAGM_SQSFSTX           32
#define     DIAGM_L1SDUTIL          33
#define     DIAGM_SIMSTATE          34
#define     DIAGM_DLDATAIF          40

#if defined (UPGRADE_EGPRS_M)  /* 3PT_NoyE_010103_EM */
#define     DIAGM_SQSFSRXEGPRS  50
#define     DIAGM_SQSFSTXEGPRS  51
#define     DIAGM_SFS_EGPRS_TEST      52
#define	    DIAGM_L1FRPT	53		/*added by J.S. Rx lab testing */
#define	    DIAGM_L1MACIF	54		/*added by J.S. Rx lab testing */
#define	    DIAGM_L1FRPTPA	55		/*added by J.S. Rx lab testing */
#define	    DIAGM_L1FRPTMC	56		/*added by J.S. Rx lab testing */
#define     DIAGM_L1BGPT	57		/*added by J.S. Rx lab testing */
#define	    DIAGM_L1SQRX	58		/*added by J.S. Rx lab testing */
#define     DIAGM_L1FRPTEV	59		/*added by J.S. Rx lab testing */
#define		DIAGM_RX_DSP_STUB_EGPRS 60	/*added by J.S. Rx lab testing - rx simulation */
#define		DIAGM_L1FRPTDS 61	/*added by E.Y. Rx lab testing - tx simulation */
#define		DIAGM_L1FRPTSH 62	/*added by E.Y. Rx lab testing - tx simulation */
#define	    DIAGM_TX_DSP_STUB_EGPRS 63	/*added by E.Y. lab testing - tx simulation */
#define		DIAGM_L1FRPTSH_EM 64		/*added by E.Y. lab testing - tx simulation */
#define		DIAGM_L1FRPTDS_EM 65		/*added by E.Y. lab testing - tx simulation */
#define	    DIAGM_L1FRPTMC_EM 66		/*added by E.Y. lab testing */
#define	    DIAGM_L1FRPTPA_EM 67		/*added by E.Y. lab testing */
#define	    DIAGM_L1BGPT_EM  68		/*added by E.Y. lab testing */
#define		DIAGM_CONTROL_STUB_EGPRS 69 /*added by E.Y. lab testing */
#define		DIAGM_TIMETRACKING_FRLOOP_TEST  70   /*added by YossiD for TimeTracking integration */
#define		DIAGM_TIMETRACKING_EGPRS_TEST   71   /*added by YossiD for TimeTracking integration */
#define     DIAGM_TT_INTEGRATION_SIMULATOR	72   /*added by YossiD for TimeTracking integration */
#define     DIAGM_TIMETRACKING_FRINT_TEST	73   /*added by YossiD for TimeTracking integration */
#define		DIAGM_TIMETRACKING_FRIDLE_TEST  74   /*added by YossiD for TimeTracking integration */
#define		DIAGM_TIMETRACKING_FRPTDS_TEST	75
#define		DIAGM_L1FRPTRC					76 /*added by Jonathan Segev for PTCCH/UL traces*/
#define		DIAGM_AFC_EGPRS_TEST			77  /*added by YossiD  for afc integration */
#define		DIAGM_L1SQTXID					78
#define		DIAGM_TRACE_FILTER_COMMANDS		79
#define		DIAGM_BLER_EGPRS_TEST			80  /*added by YossiD  for Bler integration */
#endif /* 3PT_EM */

#define     DIAGM_TRIAL             101
#define     DIAGM_DIEPSON           120
#define     DIAGM_DIKS0723          121
#define     DIAGM_DI8544            122
#define     DIAGM_PMU_TEST          123
#define     DIAGM_PMU               124
#define     DIAGM_PMU_H             125
#define     DIAGM_FDI_TEST          130
//#define     FDI                     135  //ruben
#define     DIAGM_VMP_TEST          136
#define     DIAGM_SDVR_TEST         137
#define     DIAGM_IPC_DATA          140
#define     DIAGM_IPC_ICAT_FUNC     141
#define     DIAGM_TESTER            142
#define     DIAGM_USIM              143
#define     DIAGM_FDI_TRANSPORT     144
#define     DIAGM_SQCFGPWR_O1       145
#define     DIAGM_MIPS_TEST         146
#define     DIAGM_AUDIO_TEST        147
#define     DIAGM_PMU_MONITORING    148
#define     DIAGM_SQCFGPWR_P2       149
#define     DIAGM_EEHANDLER         150
#define     DIAGM_EXCEPHANDLER      151




/* 200-400 for  GSMCore traces*/
#define     DIAGM_PLKMSORT          200
#define     DIAGM_L1PLKMELM         201

/* 400-600 for  PS traces*/
#define     DIAGM_GRR_H             400
//#if (MODULE_NAME == "GRRDCH")
//    #define     MODULE_ID         401
//#endif

#define     DIAGM_PSCcstmach        401
#define     DIAGM_PSMM              402
#define     DIAGM_PSss_main         403
#define     DIAGM_PSL2ack           404
#define     DIAGM_PSGRRCSEL         405
#define     DIAGM_PSGRRDCH          406






/* 600-800 for  AL traces (including PSA)*/
#define     DIAGM_PSA_MAIN          600
#define     DIAGM_PSA_DISP          601

/* 800-1000 for  KI traces*/
#define     DIAGM_KIEXOS_H          800

/* 1000-1200 for  Error traces*/
#define     DIAGM_KIOSFAIL          1000

/* 1200-1400 for  Test traces*/
#define     DIAGM_TEST              1200

/* 1400-1600 for  DIAG Internal Utils*/
#define     DIAGM_COMM_USB          1400
#define     DIAGM_CSW_MEM           1500

/* 1600-1700 for  DIAG Internal Utils*/
#define     DIAGM_DIAG_UTILS        1600
#define     DIAGM_DIAG_RX           1601

#define     DIAGM_LISR_TRACE_LENGTH         0x18
#define     DIAGM_LISR_STRING_MAX_LENGTH    8

#define 	DIAGM_TIMER_TEST_DVT      0


#if defined (MODULE_ID)
#define     PRINT_TEXT_MODULE_ID    MODULE_ID
#else
#define     PRINT_TEXT_MODULE_ID    DIAGM_PRINTF
#endif

#include "diag.h"

#endif
