#ifndef _OL_NW_API_H_
#define _OL_NW_API_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ol_nw_pub.h"

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_nw_set_config
 * DESCRIPTION 
 *  		This API is to set the network config.  
 * PARAMETERS 
 *		config_info			[IN]:the pointer to config information struct,see ol_NW_CONFIG_INFO
 * RETURN VALUES
 *			0 		: operation success
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_nw_set_config(ol_NW_CONFIG_INFO *config_info);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_nw_get_config
 * DESCRIPTION 
 *  		This API is to get current network config.  
 * PARAMETERS 
 *		config_info		[OUT]:the pointer to config information struct,see ol_NW_CONFIG_INFO
 * RETURN VALUES
 *			0 		: operation success
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_nw_get_config(ol_NW_CONFIG_INFO *config_info);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_nw_get_csq
 * DESCRIPTION 
 *  		This API is get current CSQ value.  
 * PARAMETERS 
 *		csq					[OUT]:the pointer csq value
 * RETURN VALUES
 *			0 		: operation success
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_nw_get_csq(int *csq);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_nw_get_signal_strength
 * DESCRIPTION 
 *  		This API is to get current signal strength information detailedly.  
 * PARAMETERS 
 *		signal_strength		[OUT]:the pointer to signal strength information struct,see ol_SIGNAL_STRENGTH_INFO
 * RETURN VALUES
 *			0 		: operation success
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_nw_get_signal_strength(ol_SIGNAL_STRENGTH_INFO *signal_strength);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_nw_get_nitz_time
 * DESCRIPTION 
 *  		This API is get current base station time(NITZ).  
 * PARAMETERS 
 *		nitz_info		[OUT]:the pointer to nitz time information struct,see ol_NITZ_TIME_INFO
 * RETURN VALUES
 *			0 		: operation success
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_nw_get_nitz_time(ol_NITZ_TIME_INFO *nitz_info);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_nw_get_operator_info
 * DESCRIPTION 
 *  		This API is to get operator information.  
 * PARAMETERS 
 *		operator_info		[IN]:the pointer to operator information struct,see ol_OPERATOR_INFO
 * RETURN VALUES
 *			0 		: operation success
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_nw_get_operator_info(ol_OPERATOR_INFO *operator_info);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_nw_set_reject_callback
 * DESCRIPTION 
 *  		This API is to set a callback when reject event happen 
 * PARAMETERS 
 *			cb		[IN]:the pointer to callback function
 * RETURN VALUES
 *			NONE
 * RETURN MESSAGE
 * 		 	NONE
 *
 *****************************************************************************/
extern void ol_nw_set_reject_callback(ol_nw_reject_callback_ptr cb);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_nw_get_reg_status
 * DESCRIPTION 
 *  		This API is to get current register state.  
 * PARAMETERS 
 *		reg_info				[OUT]:the pointer to register state information struct,see ol_REG_STATUS_INFO
 *		nw_mode				[IN]:current network mode,0:GSM 1:LTE
 * RETURN VALUES
 *			0 		: operation success
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_nw_get_reg_status(ol_REG_STATUS_INFO *reg_info,int nw_mode);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_nw_get_cell_info
 * DESCRIPTION 
 *  		This API is to get cell information.  
 * PARAMETERS 
 *		cell_info				[OUT]:the pointer to cell information struct,see ol_CELL_INFO
 * RETURN VALUES
 *			0 		: operation success
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_nw_get_cell_info(ol_CELL_INFO *cell_info);
extern int ol_nw_get_cell_info_ex(ol_CELL_INFO_EX *cell_info);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_nw_get_curr_band
 * DESCRIPTION 
 *  		This API is to get current band  
 * PARAMETERS 
 *		void				
 * RETURN VALUES
 *		   >0 	: band num
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_nw_get_curr_band(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_NW_GetCurrFerq
 * DESCRIPTION 
 *  		This API is to get current freq  
 * PARAMETERS 
 *		freq				[OUT]:get freq string like    UL:1900-1920,DL:1900-1920(Mhz)
                                  must a string size larger than 35;
 * RETURN VALUES
 *		   >0 	: band num
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_nw_get_curr_Ferq(char *freq);

extern int ol_nw_get_pagging_cycle(void);



/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_set_default_auth
 * DESCRIPTION 
 *  		This API is set default auth methord
 * PARAMETERS 
 *		auth_type				[IN]:OL_NW_AUTH_TYPE
		user					[IN]:USER NAME
		pwd						[IN]:password
                                  must a string size larger than 35;
 * RETURN VALUES
 *		   0 	: success
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_set_default_auth(OL_NW_AUTH_TYPE auth_type, char *user, char *pwd);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_default_auth
 * DESCRIPTION 
 *  		This API is get default auth methord
 * PARAMETERS 
 *		auth_type				[OUT]:OL_NW_AUTH_TYPE
		user					[OUT]:USER NAME
		pwd						[OUT]:password
 * RETURN VALUES
 *		   0 	: success
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_get_default_auth(OL_NW_AUTH_TYPE *auth_type, char *user, char *pwd);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_set_default_lte_apn
 * DESCRIPTION 
 *  		This API is to set default lte apn  
 * PARAMETERS 
 *		iptype				[IN]:OL_NW_IPTYPE
		apn					[IN]:APN string
                                  must a string size larger than 35;
 * RETURN VALUES
 *		   0 	: success
 *		  -1  	: operation fail
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern int ol_set_default_lte_apn(OL_NW_IPTYPE iptype, char *apn);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_default_lte_apn
 * DESCRIPTION 
 *  		This API is to get default lte apn  
 * PARAMETERS 
 *		iptype				[OUT]:OL_NW_IPTYPE
		apn					[OUT]:APN string
		
 * RETURN VALUES
 *		   0 	: success
 *		  -1  	: operation fail

 *
 *****************************************************************************/
extern int ol_get_default_lte_apn(OL_NW_IPTYPE *iptype, char *apn);

extern int ol_set_default_lte_apn_valid_in_ems(char is_valid);
extern int ol_get_default_lte_apn_valid_in_ems(char *is_valid);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_dns_by_cid
 * DESCRIPTION 
 *  		This API is to get dns 
 * PARAMETERS 
 *		cid				[IN]: mbtk_data_call_cid_index_enum
        dns1Str		    [OUT]: dns1
        dns2Str		    [OUT]: dns2
        
 * RETURN VALUES
 *		   0 	: success
 *		  -1  	: operation fail

 *
 *****************************************************************************/
extern int ol_get_dns(OL_NW_IPTYPE iptype, char *dns1Str, char *dns2Str);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_set_dns_by_cid
 * DESCRIPTION 
 *  		This API is to set dns 
 * PARAMETERS 
 *		cid				[IN]: mbtk_data_call_cid_index_enum
        dns1Str		    [IN]: dns1
        dns2Str		    [IN]: dns2
        
 * RETURN VALUES
 *		   0 	: success
 *		  -1  	: operation fail

 *
 *****************************************************************************/
extern int ol_set_dns(OL_NW_IPTYPE iptype, char *dns1Str, char *dns2Str);


/*****************************************************************************
 *
 * FUNCTIO
 *      ol_set_psm_config
 * DESCRIPTION
 *      This API is to set the psm config.
 * PARAMETERS
 *      psm_info         [IN]:the pointer to config information struct,see ol_psm_info
 * RETURN VALUES
 *      0                   : operation success
 *      -1                  : operation fail
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
extern int ol_set_psm_config(ol_psm_info *psm_info);


/*****************************************************************************
 *
 * FUNCTIO
 *      ol_get_psm_config
 * DESCRIPTION
 *      This API is to set the psm config.
 * PARAMETERS
 *      psm_info         [out]:the pointer to config information struct,see ol_psm_info
 * RETURN VALUES
 *      0                   : operation success
 *      -1                  : operation fail
 * RETURN MESSAGE
 *      NONE
 *
 *****************************************************************************/
extern int ol_get_psm_config(ol_psm_info *psm_info);

#ifdef __cplusplus
}
#endif

#endif

