/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/******************************************************************************
 *               MODULE IMPLEMENTATION FILE
 *******************************************************************************
 * Filename: privateAreaTable.h
 ******************************************************************************/

#ifndef _PRIVATE_AREA_TABLE_H_
#define _PRIVATE_AREA_TABLE_H_
// Private Area is NON-Initialized, NON-cacheable area

#include "global_types.h"

//#if defined (_TAVOR_HARBELL_)|| defined(SILICON_PV2)  
#if defined(SILICON_PV2)  
extern UINT32  Image$$DDR_PRIVATE_RW_AREA$$Base;
#define PRIVATE_AREA_ADDR       ((PrivateAreaTableType*)(&Image$$DDR_PRIVATE_RW_AREA$$Base))
#define PRIVATE_AREA_SIZE       (4*1024)

#else //_TAVOR_HARBELL_
//Currently supported for HARBELL memory mapping only
#undef  PRIVATE_AREA_ADDR
#define PRIVATE_AREA_SIZE       (0)

#endif//_TAVOR_HARBELL_

#endif  /* _PRIVATE_AREA_TABLE_H_ */

