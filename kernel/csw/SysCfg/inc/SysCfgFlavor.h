/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/************************************************************************/
/* Filename: SysCfgFlavor.h                                             */
/*                                                                      */
/* Author:   Yossi hanin                                                */
/*                                                                      */
/* Description: all SW mini switches that are related to Flavor         */
/* should be activate only here.                                        */
/* Remarks:                                                             */
/*                                                                      */
/* Created: 15/08/2007                                                  */
/*                                                                      */
/* Modified:                                                            */
/************************************************************************/

#if !defined(FLAVOR_CFG__H)
#define FLAVOR_CFG_H

#include "SysCfgMain.h"


#define     DF(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10)                             	\
               (                                                                               \
           	    (FLAVOR_TYPE == FLAVOR_PLATFROM_COM)   	     ?   arg1    :(                    \
                (FLAVOR_TYPE == FLAVOR_MODEM_ONLY_COM)     	 ?   arg2    :(                    	\
                (FLAVOR_TYPE == FLAVOR_L1_COM)             	 ?   arg3    :(                    	\
                (FLAVOR_TYPE == FLAVOR_FULL_SYS_COM)       	 ?   arg4    :(                    \
                (FLAVOR_TYPE == FLAVOR_QT_COM)             	 ?   arg5    :(                    	\
                (FLAVOR_TYPE == FLAVOR_PLATFROM_APP)       	 ?   arg6    :(                    	\
                (FLAVOR_TYPE == FLAVOR_MODEM_ONLY_APP) 	     ?   arg7    :(                    	\
                (FLAVOR_TYPE == FLAVOR_L1_APP)             	 ?   arg8    :(                    	\
                (FLAVOR_TYPE == FLAVOR_FULL_SYS_APP)   	     ?   arg9    :(                    	\
                (FLAVOR_TYPE == FLAVOR_QT_APP)         	     ?   arg10   :(                    	\
               	/*ADD HERE NEW TYPE*/                                                          	\
                FLAVOR_TYPE_ERROR))))))))))                                                    \
               )

#if (DF == FLAVOR_TYPE_ERROR)
#error MUST_GET_FLAVOR_TYPE_FROM_SYSCFGMAIN
#endif

                                                                                                                                               	  /*for QT SW mini switches */                                                                              /*for QT SW mini switches */
//                                                           +---------------------+-----------------------+---------------+---------------------+---------------------+---------------------+-----------------------+-------------- +---------------------+---------------+
//                                                           | FLAVOR_PLATFORM_COM | FLAVOR_MODME_ONLY_COM | FLAVOR_L1_COM | FLAVOR_FULL_SYS_COM | FLAVOR_QT_COM       | FLAVOR_PLATFORM_APP | FLAVOR_MODME_ONLY_APP | FLAVOR_L1_APP | FLAVOR_FULL_SYS_APP | FLAVOR_QT_APP |
//                                                           +---------------------+-----------------------+---------------+---------------------+---------------------+---------------------+-----------------------+---------------+---------------------+---------------+
/* mini switch size will be not more then 50 chars-------|*/
/* switch to insert mode when adding new switch
 * For migration phase each switch must be undefed
 * if it is == 0 in SysCfgFlavorMig.h*/
#define FLAVOR_EXAMPLE_DEFINITION                          DF(           NOMSL     ,           0           ,       0       ,        NOMSL        ,           NOMSL     ,           NOMSL     ,            0          ,        0      ,         NOMSL       ,       0       )
//#define MSL_INCLUDE                                      DF(           NOMSL     ,           0           ,       0       ,        NOMSL        ,           NOMSL     ,           NOMSL     ,            0          ,        0      ,         NOMSL       ,       0       )
//#define DIAG_OVER_MSL                                    DF(        MSL_INCLUDE  ,           0           ,       0       ,     MSL_INCLUDE     ,        MSL_INCLUDE  ,        MSL_INCLUDE  ,            0          ,        0      ,      MSL_INCLUDE    ,       0       )
//#define _DATAOMSL_ENABLED_                               DF(        MSL_INCLUDE  ,           1           ,       1       ,     MSL_INCLUDE     ,        MSL_INCLUDE  ,        MSL_INCLUDE  ,            0          ,        0      ,      MSL_INCLUDE    ,       0       )
//#define NVM_OVER_RAM     	                                DF(        NVMORAM      ,           0           ,       0       ,         0           ,        NVMORAM      ,        NVMORAM      ,            0          ,        0      ,      NVMORAM        ,       0       )
//#define _FDI_VER_71_                                     DF(        FDI_71       ,           0           ,       0       ,         FDI_71      ,        NVMORAM      ,        NVMORAM      ,            FDI_71     ,        0      ,        FDI_71       ,       0       )
//#define INTEL_FDI    	                                    DF(        FDI_71       ,           0           ,       0       ,         FDI_71      ,        NVMORAM      ,        NVMORAM      ,            FDI_71     ,        0      ,        FDI_71       ,       0       )

//#if(_FDI_VER_71_ == 1)
//#error FDI71
//#endif



//                                                           +---------------------+-----------------------+---------------+---------------------+---------------------+-----------------------+-------------- +---------------------+
//                                                           | FLAVOR_PLATFORM_COM | FLAVOR_MODME_ONLY_COM | FLAVOR_L1_COM | FLAVOR_FULL_SYS_COM | FLAVOR_PLATFORM_APP | FLAVOR_MODME_ONLY_APP | FLAVOR_L1_APP | FLAVOR_FULL_SYS_APP |
//                                                           +---------------------+-----------------------+---------------+---------------------+---------------------+-----------------------+---------------+---------------------+
/* mini switch size will be not more then 50 chars-------|*/
/* switch to insert mode when adding new switch*/
#define  FLAVOR_EXAMPLE_DEFINTION                          DF(      0x11111111     ,      0x22222222       ,   0x33333333  ,    0x44444444       ,       0x55555555    ,        0x66666666     ,    0x77777777 ,    0x88888888       )


#include "SysCfgFlavorMig.h"

#endif /* FLAVOR_CFG_H */

