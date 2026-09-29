/*------------------------------------------------------------
(C) Copyright [2006-2009] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/


/************************************************************************/
/*                                                                      */
/* Filename: cache_api.h                                                */ 
/*                                                                      */
/* description: contain generic API for cache operations                */
/*                                                                      */
/* Create by:   Eli Levy                                                */
/*                                                                      */
/* Remarks: -                                                           */
/*    										                        	*/
/* Created: 09/07/2009                                                  */
/*                                                                      */
/************************************************************************/

#ifndef CACHE_API_H
#define CACHE_API_H

/**** cache control API ****/



/**** cache operation API ****/

UINT32 CleanDataCache(UINT32 address, UINT32 size);


#endif //CACHE_API_H