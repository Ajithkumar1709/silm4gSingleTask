#ifndef __MBTK_OPEN_AT_H__
#define __MBTK_OPEN_AT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "mbtk_os.h"
#include "mbtk_pub_def.h"




/*****************************************************************************
 * FUNCTION
 *  ol_at_init
 * DESCRIPTION
 *  This API is to init at function
 *
 * PARAMETERS
 *  msgref         : [IN]  msgref ,  when get at response, will send message to by this msgref 
 * RETURN VALUES
 *  OL_E_NONE :  action successful
 *  OL_E_PARAM_INVALID
 *
 *****************************************************************************/
extern OL_ERROR_TYPE ol_at_init(mbtk_msgqref *msgref);


/*****************************************************************************
 * FUNCTION
 *  ol_send_at_command
 * DESCRIPTION
 *  This API is to send one at command to modem
 *
 * PARAMETERS
 *  command         : [IN]  AT string want send to modem, max size is 2048
 * RETURN VALUES
 *  OL_E_NONE :  action successful
 *  OL_E_PARAM_INVALID
 *
 *****************************************************************************/
extern int ol_send_at_command(char* command);



/*****************************************************************************
 * FUNCTION
 *  ol_read_at_response
 * DESCRIPTION
 *  This API is to read ap response ,  include  AT command response, or URC
 *
 * PARAMETERS
 *  data         : [OUT]    read buffer
 *  length       :[IN],   want read length
 * RETURN VALUES
 *  OL_E_INIT_FIRST :  action successful
 *  >=0:				length of real read
 *
 *****************************************************************************/
extern int ol_read_at_response(UINT8 *data, uint16 length);



/*****************************************************************************
 * FUNCTION
 *  ol_at_deinit
 * DESCRIPTION
 *  This API is to deinit at function
 *
 * PARAMETERS
 * RETURN VALUES
 *  void
 *
 *****************************************************************************/
extern void ol_at_deinit(void);

#ifdef __cplusplus
}
#endif

#endif
