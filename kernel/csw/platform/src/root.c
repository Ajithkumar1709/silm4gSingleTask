/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/***************************************************************************
*               MODULE IMPLEMENTATION FILE
****************************************************************************
* Title: Link root module
*
* Filename: root.c
*
* Target, platform: all
*
* Authors: Anton
*
* Description:
* 	ARM (ADS and RVCT) linker does not allow all the inputs to be libraries
*     (at least one object module is required, and external references in it
*     motivate the linker to search libraries.
*   CBA makes pack every component (package/group) into a library, thus
*     all linker inputs ARE libraries unless build target supply an object module.
*   This module is included into all builds at target level (see inc_PLAT.mak)
*     and should reference the image entry point.
*
* Notes:
*   The above linker behaviour might happen when no ENTRY definition,
*     or ambigous entry definition inside the image.
*     Therefore this module provides a simple and robust solution.
******************************************************************************/

//
//
// IMPORT image entry point to make it link
//

// for TTC: run from SQU/DDR use the below define
#define ROOT_SYMBOL_NAME INT_Vectors

extern void ROOT_SYMBOL_NAME(void);
void dummyRootFunction(void)
{
   ROOT_SYMBOL_NAME();
}

