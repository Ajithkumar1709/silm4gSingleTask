#ifndef _OL_LBS_H_
#define _OL_LBS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    char longitude_str[50];
    char latitude_str[50];
}mbtk_lbs_info_t;

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_lbs_get_info
 * DESCRIPTION 
 *  	This API is used to get lbs information
 * PARAMETERS 
 *		hostname    :   lbs service hostname
 *		port        :   lbs service port
 *		info        :   lbs information
 *		timeout_sec :   lbs connet outtime
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL	: -1
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_lbs_get_info(char *hostname, uint32_t port, mbtk_lbs_info_t * info, uint32_t timeout_sec);

#ifdef __cplusplus
}
#endif

#endif

