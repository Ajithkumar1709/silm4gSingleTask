/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************/
/* Filename: SysCfgPlatfrom.h                                           */
/*                                                                      */
/* Author:   Yossi hanin                                                */
/*                                                                      */
/* Description: all SW mini switches that are related to Platfrom       */
/* should be activate only here.                                        */
/* Remarks:                                                             */
/*                                                                      */
/* Created: 15/08/2007                                                  */
/*                                                                      */
/* Modified:                                                            */
/************************************************************************/

#if !defined(PLATFROM_CFG_H)
#define PLATFROM_CFG_H

#include "SysCfgMain.h"

#define     DP(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12)          \
           	   (                                                                        \
           	    (PLATFORM_TYPE == PLATFORM_HERMON_EVB)         	   ?   	   arg1  :(    	\
                (PLATFORM_TYPE == PLATFORM_HERMON_PDK)         	   ?   	   arg2  :(    	\
                (PLATFORM_TYPE == PLATFORM_TAVOR_EVB)          	   ?   	   arg3  :(    	\
                (PLATFORM_TYPE == PLATFORM_TAVOR_QT)           	   ?   	   arg4  :(    	\
                (PLATFORM_TYPE == PLATFORM_TAVOR_YARDEN_EVB)   	   ?   	   arg5  :(    	\
                (PLATFORM_TYPE == PLATFORM_TAVOR_PV_EVB)   	       ?   	   arg6  :(    	\
                (PLATFORM_TYPE == PLATFORM_TAVOR_PV_QT)    	       ?   	   arg7  :(    	\
                (PLATFORM_TYPE == PLATFORM_TAVOR_SAAR_RD)      	   ?   	   arg8  :(    	\
               	(PLATFORM_TYPE == PLATFORM_HERMON2_SAAR_RD)    	   ?   	   arg9  :(    	\
               	(PLATFORM_TYPE == PLATFORM_HERMON2_QT)     	       ?   	   arg10 :(    	\
               	(PLATFORM_TYPE == PLATFORM_MMP_EVB)            	   ?   	   arg11 :(    	\
               	(PLATFORM_TYPE == PLATFORM_MMP_QT)             	   ?   	   arg12 :(    	\
               	/*ADD HERE NEW PLATFORM_TYPE       	*/                                 	\
               	 PLATFORM_TYPE_ERROR ))))))))))))                                      	\
               	)

#if (DP == PLATFORM_TYPE_ERROR)
#error MUST_GET_PLATFORM_TYPE_FROM_SYSCFGMAIN
#endif

//                                 	                         +----------------------+--------------+----------+------------+----------------+----------+
//                                                          | HERMON |    TAVOR    | TAVOR_YARDEN | TAVOR_PV | TAVOR_SAAR |    HERMON2     |    MMP   |
//                                 	                         +---+----+------+------+-------+------+-----+----+------------+--------+-------+-----+----+
//                                 	                         |PDK| EVB|  EVB |  QT  |      EVB     | EVB | QT |     RD     |RD_SAAR |  QT   | EVB | QT |
//                                 	                         +---+----+------+------+--------------+-----+----+------------+--------+-------+-----+----+
/* mini switch size will be not more then 50 chars-------|*/
/* switch to insert mode when adding new switch
 * For migration phase each switch must be undefed
 * if it is == 0 in SysCfgPlatformMig.h*/
  #define PLAT_EXAMPLE_DEFINITION                          DP( 0 , 0  ,  0   ,  0   ,       0      ,  0   , 0 ,      0     ,   0    ,   0   ,  0  ,  0 )
//#define _MICCO_A0_                               	        DP( 0 , 0  ,  0   ,  0   ,       0      ,  0   , 0 ,      0     ,   0    ,   0   ,  0  ,  0 )
//#define PMC_MICCO_A0                                     DP( 0 , 0  ,  0   ,  0   ,       0      ,  0   , 0 ,      0     ,   0    ,   0   ,  0  ,  0 )
//#define _MICCO_B0_                                       DP( 0 , 0  ,  0   ,  1   ,       1      ,  0   , 0 ,      0     ,   0    ,   0   ,  0  ,  0 )
//#define PMC_MICCO_B0                                     DP( 0 , 0  ,  0   ,  1   ,       1      ,  0   , 0 ,      0     ,   0    ,   0   ,  0  ,  0 )


//                                                          +-----------------------+-----------------------+--------------+-----------------------+------------+-----------------------+------------------------+
//                                                          |        HERMON         |        TAVOR          | TAVOR_YARDEN |        TAVOR_PV       | TAVOR_SAAR |        HERMON2        |          MMP           |
//                                                          +-----------+-----------+-----------+-----------+--------------+-----------+-----------+------------+-----------+-----------+-----------+------------+
//                                                          |     EVB   |  PDK      |    EVB    |      QT   |      EVB     |   EVB     |     QT    |    RD      | RD_SAAR   |     QT    |    EVB    |     QT     |
//                                                          +-----------+-----------+-----------+-----------+--------------+-----------+-----------+------------+-----------+-----------+-----------+------------+
/* mini switch size will be not more then 50 chars-------|*/
/* switch to insert mode when adding new switch */
#define PLAT_EXAMPLE_ADDRESS                              DP( 0x11111111, 0x22222222, 0x33333333, 0x44444444, 0x55555555   , 0x66666666, 0x77777777, 0x88888888 , 0x99999999, 0xAAAAAAAA, 0xBBBBBBBB, 0xCCCCCCCC )

#include "SysCfgPlatformMig.h"


#endif /* PLATFROM_CFG_H */

