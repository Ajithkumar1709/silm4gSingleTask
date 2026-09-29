#ifndef _OL_FOTA_UPGRADE_H_
#define _OL_FOTA_UPGRADE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdbool.h"

#define MBTK_FOTA_SERVER_CONTEXT_STRLEN	512

typedef enum
{
	MBTK_FOTA_INPROGRESS,
	MBTK_FOTA_SUCCEED,
	MBTK_FOTA_SETFLAG,
	MBTK_FOTA_FAIL,
	MBTK_FOTA_MINI_PRE_INPROGRESS
}MBTK_FOTA_STATUS;
    
typedef enum {
	FOTA_SUCCESS=0,
	FOTA_DOWNLOADING=50,
	FOTA_COMPLETED=100,
	FOTA_DOMAIN_NOT_EXIST=1001,
	FOTA_DOMAIN_TIMEOUT,
	FOTA_DOMAIN_UNKNOWN,
	FOTA_AUTH_FAILED,
	FOTA_FILE_NOT_EXIST,
	FOTA_FILE_SIZE_INVALID,
	FOTA_FILE_GET_ERR,
	FOTA_FILE_CHECK_ERR,
	FOTA_INTERNAL_ERR,
	FOTA_FILE_SIZE_TOO_LARGE,
	FOTA_SET_FLAG_FAILED,
	FOTA_PARAM_SIZE_INVALID,
	FOTA_NO_ENOUGH_MEMORY,
	FOTA_ENTRY_MINISYS_ERROR
} _FOTARes;

typedef struct {
    MBTK_FOTA_STATUS status;
    _FOTARes res;
}mbtk_fota_status_result_t;

typedef enum
{
    FOTA_UPGRED_NONE,
    FOTA_UPGRED_FAIL,
    FOTA_UPGRED_SUCCESS,    
}FOTA_UPGRED_RESULT;


typedef struct
{
	char host[MBTK_FOTA_SERVER_CONTEXT_STRLEN]; /*xx.xx.xx.xx:port, or URL*/	
	char username[MBTK_FOTA_SERVER_CONTEXT_STRLEN];
	char password[MBTK_FOTA_SERVER_CONTEXT_STRLEN];
	unsigned char mode; /*0: ftp, 1: http*/
}mbtk_fota_server_info;


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_fota_context_init
 * DESCRIPTION 
 *  	This API is used to init fota context
 * PARAMETERS 
 *    server_info : no use,ignore it
 *		package_size : fota package size
 *		need_check : set if have a package check or not
 *		callback : status reporter while fota process in cp
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_fota_context_init(mbtk_fota_server_info *server_info,int package_size,bool need_check,void (*callback(void *)));
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_fota_context_deinit
 * DESCRIPTION 
 *  	This API is used to release the fota context
 * PARAMETERS 
 *    NONE
 * RETURN VALUES
 *		NONE
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern void ol_fota_context_deinit(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_fota_pkg_write
 * DESCRIPTION 
 *  	This API is used to write fota data to flash
 * PARAMETERS 
 * 		data : fota package data
 *		dataLen : data length of input fota package data
 *		package_szie : total fota package size
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_fota_pkg_write(char * data, int dataLen ,unsigned int package_size);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_fota_pkg_flush_flash
 * DESCRIPTION 
 *  	This API is used to flush cache data into flash
 * PARAMETERS 
 *    NONE
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_fota_pkg_flush_flash(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_fota_image_verify
 * DESCRIPTION 
 *  	This API is used to verify fota package 
 * PARAMETERS 
 *    NONE
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern int ol_fota_image_verify(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_fota_firmware_download
 * DESCRIPTION 
 *  	This API is used to download fota package form network
 * PARAMETERS 
 *    server_info : a pointer to server info
 *		auto_reboot : set if auto reboot or not after download sucess
 *		callback : status reporter while fota process in cp
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern int ol_fota_firmware_download(mbtk_fota_server_info *server_info,bool auto_reboot,void (*callback(void *)));
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_fota_get_proccess
 * DESCRIPTION 
 *  	This API is used to get fota package proccess 
 * PARAMETERS 
 *    NONE
 * RETURN VALUES
 *		Process percentage :0-100
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern int ol_fota_get_proccess(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_fota_get_upgrade_result
 * DESCRIPTION 
 *  	This API is used to get fota upgrade result 
 * PARAMETERS 
 *    NONE
 * RETURN VALUES
 *		upgrade_result              typedef enum
                                    {
                                        FOTA_UPGRED_NONE,
                                        FOTA_UPGRED_FAIL,
                                        FOTA_UPGRED_SUCCESS,    
                                    }FOTA_UPGRED_RESULT;
    
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
extern int ol_fota_get_upgrade_result(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_mini_fota_firmware_download
 * DESCRIPTION 
 *  	This API is used to download minifota package form network
 * PARAMETERS 
 *    NONE
 * RETURN VALUES
 *		SUCCESS	: 0
 *		FAIL		: -1
 * RETURN MESSAGE
 * 		NONE
 *
 *****************************************************************************/
 extern int ol_mini_fota_firmware_download(mbtk_fota_server_info *server_info, void (*callback)(void *));

 /*****************************************************************************
	*
	* FUNCTIO 
	* 	 ol_mini_fota_force_app_update
	* DESCRIPTION 
	* 	 This API is used to set flag to download app update package(only) form network and do app upgrade
	* PARAMETERS 
	* 	 onoff : 1 enbale,0 disable 
	* RETURN VALUES
	* 	 NONE
	* RETURN MESSAGE
	* 	 NONE
	*
	*****************************************************************************/
 extern void ol_mini_fota_force_app_update(char onoff);

 /*****************************************************************************
  *
  * FUNCTIO 
  *      ol_fota_stop_reboot
  * DESCRIPTION 
  *      This API is used to stop to reboot
  * PARAMETERS 
  *    NONE
  * RETURN VALUES
  *    NONE
  * RETURN MESSAGE
  *      NONE
  *
  *****************************************************************************/
 extern void ol_fota_stop_reboot(void);

#ifdef __cplusplus
}
#endif

#endif
