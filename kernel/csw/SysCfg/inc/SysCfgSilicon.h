/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************/
/* Filename: SysCfgSilicon.h                                            */
/*                                                                      */
/* Author:   Yossi hanin                                                */
/*                                                                      */
/* Description: all SW mini switches that are related to silicon        */
/* should be activate only here.                                        */
/* Remarks:                                                             */
/*                                                                      */
/* Created: 15/08/2007                                                  */
/*                                                                      */
/* Modified:                                                            */
/************************************************************************/

#if !defined(SILICON_CFG_H)
#define SILICON_CFG_H

#include "SysCfgMain.h"


#define     DS(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13)       	\
               (                                                                           	\
           	    (SILICON_TYPE == SILICON_HERMON_B0)    	 ?  arg1    :(                     	\
                (SILICON_TYPE == SILICON_HARBEL_P_A0)  	 ?  arg2    :(                     	\
                (SILICON_TYPE == SILICON_BOERNE_P_A0)  	 ?  arg3    :(                     	\
                (SILICON_TYPE == SILICON_HARBEL_P_B0)  	 ?  arg4    :(                     	\
                (SILICON_TYPE == SILICON_BOERNE_P_B0)  	 ?  arg5    :(                     	\
                (SILICON_TYPE == SILICON_HARBEL_PV_A0) 	 ?  arg6    :(                     	\
                (SILICON_TYPE == SILICON_BOERNE_PV_A0)   ?  arg7    :(                     	\
                (SILICON_TYPE == SILICON_HARBEL_PV2_A0)	 ?  arg8    :(                     	\
                (SILICON_TYPE == SILICON_BOERNE_PV2_A0)  ?  arg9    :(                     	\
               	(SILICON_TYPE == SILICON_HERMON2_946_Z0) ?  arg10   :(                     	\
                (SILICON_TYPE == SILICON_HERMON2_926_Z0) ?  arg11   :(                     	\
               	(SILICON_TYPE == SILICON_MMP_COM_Z0)   	 ?  arg12   :(                     	\
                (SILICON_TYPE == SILICON_MMP_APP_Z0)   	 ?  arg13   :(     	                \
               	/*ADD HERE NEW  TYPE*/         	                                            \
                 SILICON_TYPE_ERROR )))))))))))))                                          \
               	)

#if (DS == SILICON_TYPE_ERROR)
#error MUST_GET_SILICON_TYPE_FROM_SYSCFGMAIN
#endif
//                                                     	      +--------+-------------+--------------+--------------+--------------+-----------+-----------+
//                                                           | HERMON |  TAVOR_P_A0 |  TAVOR_P_B0  | TAVOR_PV_A0  | TAVOR_PV2_A0 | HERMON2 Z0|   MMP Z0  |
//                                                           +--------+------+------+-------+------+-------+------+-------+------+-----+-----+-----+-----+
//                                                           |        |HARBEL|BOERNE| HARBEL|BOERNE| HARBEL|BOERNE| HARBEL|BOERNE| 946 | 926 | COM | APP |
//                                                           +--------+------+------+-------+------+-------+------+-----+--------+-----+-----+-----+-----+
/* mini switch size will be not more then 50 chars-------|*/
/* switch to insert mode when adding new switch
 * For migration phase each switch must be undefed
 * if it is == 0 in SysCfgSiliconMig.h*/
  #define  SILICON_EXAMPLE_DEFINITION                      DS(   0    ,  0   ,   0  ,   1   ,  1   ,   0   ,  0   ,  0  ,   0    ,  0  ,  0  ,  0  , 0   )
//#define  _TAVOR_B0_SILICON_  	                            DS(   0    ,  0   ,   0  ,   1   ,  1   ,   0   ,  0   ,  0  ,   0    ,  0  ,  0  ,  0  , 0   )
//#define  _TAVOR_BOERNE_                                  DS(   0    ,  1   ,   1  ,   1   ,  1   ,   0   ,  0   ,  0  ,   0    ,  0  ,  0  ,  0  , 0   )
//#define  _TAVOR_HARBELL_                                 DS(   0    ,  1   ,   1  ,   1   ,  1   ,   0   ,  0   ,  0  ,   0    ,  0  ,  0  ,  0  , 0   )

//                                                           +-----------+----------+-----------+-----------------------+-----------------------+-----------------------+-----------------------+------------------------+
//                                                           | HERMON    |  TAVOR_P_A0          |  TAVOR_P_B0           | TAVOR_PV_A0           | TAVOR_PV2_A0          | HERMON2 Z0            |    MMP Z0              |
//                                                           +-----------+----------+-----------+-----------+-----------+-----------------------+-----------------------+-----------+-----------+-----------+------------+
//                                                           |           |HARBEL    |BOERNE     | HARBEL    |BOERNE     | HARBEL    |BOERNE     | HARBEL    |BOERNE     | 946       | 926       | COM       | APP        |
//                                                           +-----------+----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+------------+
/* mini switch size will be not more then 50 chars-------|*/
/* switch to insert mode when adding new switch */
#define SILICON_EXAMPLE_ADDRESS                            DS(0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555, 0x66666666, 0x77777777,0x88888888, 0x99999999, 0x66666666, 0x77777777, 0x88888888, 0x99999999)

#include "SysCfgSiliconMig.h"

#endif /* SILICON_CFG_H */

