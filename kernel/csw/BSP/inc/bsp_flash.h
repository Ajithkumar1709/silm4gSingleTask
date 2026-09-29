/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

#ifndef _BSP_FLASH_H_
#define _BSP_FLASH_H_

#if (defined FLAVOUR_COM)
#define CLIENT_DIR_NAME "\\"    //  When using local NVM on the COM Side (i.e NVMORAM or TTC COM Only).
#else
#define CLIENT_DIR_NAME "com\\"
#endif

#if (defined _BSP_FLASH_C_)
const CHAR *comPrefix = CLIENT_DIR_NAME ;
#else
extern const CHAR *comPrefix ;
#endif


void bspGetFlashParams(void);
void bspMapFDIPartition(void);
void bspInitFDIVars(UINT32 *dsa, UINT32 *dbs, UINT16 *dbc, UINT32 *fsa, UINT32 *fbs, UINT16 *fbc);
int getOnenandBaseAddress(void);

#endif
