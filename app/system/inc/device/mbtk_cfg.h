#ifndef __MBTK_CFG_H
#define __MBTK_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mbtk_pub_type.h"
#include "stdbool.h"

// system pmu func
typedef enum
{
	DEVICE_SDCARD,
	DEVICE_EMMC
}SDIO_TYPE;



/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_set_sdio_type
 * DESCRIPTION 
 *  	This API is used to set sdio type
 * PARAMETERS 
 *      type  				DEVICE_SDCARD    0
							DEVICE_EMMC      1
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_set_sdio_type(int type);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_sdio_type
 * DESCRIPTION 
 *  	This API is used to get sdio type
 * PARAMETERS 
 *      NONE
 * RETURN VALUES
 *		int   SDIO_TYPE
          -1   not support
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_get_sdio_type();

#ifdef __cplusplus
}
#endif

#endif // #ifdef __MBTK_CFG_H