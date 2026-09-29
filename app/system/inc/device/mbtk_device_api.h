#ifndef __MBTK_DEVICE_API_H
#define __MBTK_DEVICE_API_H

#ifdef __cplusplus
extern "C" {
#endif


typedef void (*mbtk_usb_detect_callback)(int status);
typedef void (*mbtk_nitz_cb)(void);

typedef enum 
{
	mbtk_device_api_err = -1,
	mbtk_device_api_err_none = 0
}mbtk_device_api_err_enum;


typedef struct 
{
	char *company;
	char *projectname;
	char *softversion;
	char *realsedate;
}mbtk_device_firmware_ver_struct;


typedef struct 
{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
}mbtk_device_time_struct;

typedef enum 
{
	mbtk_modem_mini_fun,
	mbtk_modem_full_fun,
	mbtk_modem_disable_rf_recv,
	mbtk_modem_disable_rf_trans_recv,
	mbtk_modem_disable_sim,
	mbtk_modem_disable_second_rx
}mbtk_device_modem_fun_enum;

typedef enum
{
	OL_FACTORY_W,
	OL_FACTORY_R,
	OL_FACTORY_D
}OL_FACTORY_ENUM;


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_device_imei
 * DESCRIPTION 
 *  		This API is to get imei of device
 * PARAMETERS 
 *		imei[OUT]               get imei (string type), should equal or up to 16 byte
 * RETURN VALUES
 *		=0 	: success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_device_api_err_enum ol_get_device_imei(uint8_t *imei);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_firmware_version
 * DESCRIPTION 
 *  		This API is to get version number
 * PARAMETERS 
 *		version[OUT]               version info
 * RETURN VALUES
 *		=0 	: success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_device_api_err_enum ol_get_firmware_version(mbtk_device_firmware_ver_struct **version);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_device_current_time
 * DESCRIPTION 
 *  		This API is to get current of device
 * PARAMETERS 
 *		ptime[OUT]               get tm time of device
 * RETURN VALUES
 *		=0 	: success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_device_api_err_enum ol_get_device_current_time(mbtk_device_time_struct *ptime);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_device_sn
 * DESCRIPTION 
 *  		This API is to get sn of device
 * PARAMETERS 
 *		sn[OUT]                get sn (string type)
 * RETURN VALUES
 *		=0 	: success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_device_api_err_enum ol_get_device_sn(uint8_t *sn);



/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_device_sn
 * DESCRIPTION 
 *  		This API is to get sn of user
 * PARAMETERS 
 *		sn[OUT]                get sn (string type) [max length 16 byte]
 * RETURN VALUES
 *		=0 	: success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_device_api_err_enum ol_get_device_sn2(uint8_t *sn);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_set_modem_function
 * DESCRIPTION 
 *  		This API is to set play mp3 buffer cb.  
 * PARAMETERS 
 *		fun[IN]               cfun function  mbtk_device_modem_fun_enum
        rst[IN]               reboot system
 * RETURN VALUES
 *		=0 	: success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_device_api_err_enum ol_set_modem_function(mbtk_device_modem_fun_enum fun, uint8_t rst);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_modem_function
 * DESCRIPTION 
 *  		This API is to get modem current cfun function.  
 * PARAMETERS 
 *		fun[OUT]               current function
 * RETURN VALUES
 *		=0 	: success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern mbtk_device_api_err_enum ol_get_modem_function(uint8_t *fun);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_chipid
 * DESCRIPTION 
 *  		This API is to get device chipid
 * PARAMETERS 
 *		void            
 * RETURN VALUES
 *		uint32  chip id number
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern uint32_t ol_get_chipid( void );

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_cpu_useage
 * DESCRIPTION 
 *  		This API is to get cpu useage
 * PARAMETERS 
 *		void               get current cpu useage
 * RETURN VALUES
 *		uint8_t            cpu useage 
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern uint8_t ol_get_cpu_useage(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_cpuId
 * DESCRIPTION 
 *  		This API is to get cpuid
 * PARAMETERS 
 * RETURN VALUES
 *		UINT64  cpuid number
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern UINT64 ol_get_cpuId(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_cpu_bootmode
 * DESCRIPTION 
 *  		This API is to get boot mode
 * PARAMETERS 
 * RETURN VALUES
 *		uint8  boot mode of   OL_POWERUP_REASON
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern uint8_t ol_get_cpu_bootmode(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_mac
 * DESCRIPTION 
 *  		This API is to get mac of device  
 * PARAMETERS 
 *		mac[OUT]               6 char , 48bit, value not string
 * RETURN VALUES
 *		=0 	: success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *

    char freq[6]= {0};		  
	ol_get_mac(freq);
	op_uart_printf("\r\n%02x,%02x,%02x,%02x,%02x,%02x", freq[0],
		freq[1],freq[2],freq[3],freq[4],freq[5]);
 *****************************************************************************/
extern mbtk_device_api_err_enum ol_get_mac(uint8_t *mac);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_factory_operation
 * DESCRIPTION 
 *  		This API is to get or set factory data  
 * PARAMETERS 
 *		oper_type[IN]               OL_FACTORY_ENUM
 *		buffer[IN]/[OUT]            OL_FACTORY_W is in,  OL_FACTORY_R is out
 *		len[IN/OUT]               	in, length of buffer, 
 *									out, len of buffer ,only useful when OL_FACTORY_W, max is 16
        data_num[IN]				number of data, max is 2, each has max 16 len data area
 
 * RETURN VALUES
 *		=0 	: success
 *		<0   : error
 * RETURN MESSAGE
 * 		 NONE
 *

    ol_factory_operation(OL_FACTORY_R,NULL, 0,0);
	ol_factory_operation(OL_FACTORY_W,"hahaha1",strlen("hahaha1") , 0);
	ol_factory_operation(OL_FACTORY_R,NULL, 0, 0);
 *****************************************************************************/

extern mbtk_device_api_err_enum ol_factory_operation(OL_FACTORY_ENUM oper_type, char* buffer, uint8 len, uint8 data_num);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_secboot_status
 * DESCRIPTION 
 *  		This API is to get device secboot status 
 * RETURN VALUES
 *		0  : non-secboot
 *		1  : secboot
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern unsigned char ol_get_secboot_status(void);
/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_flash_id
 * DESCRIPTION 
 *  		This API is to get device flash id  
 * RETURN VALUES
 *		0     : non-ID
 *		ohter : flash ID
 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern unsigned short ol_get_flash_id(void);

extern void ol_set_nitz_ind_cb(mbtk_nitz_cb cb);

extern uint8_t ol_enable_sys_debug_uart_log(char enable);


/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_set_nitz_enable
 * DESCRIPTION 
 *  		This API is to set weather enable nitz
 * RETURN VALUES

 * RETURN MESSAGE
 * 		 NONE
 *
 *****************************************************************************/
extern void ol_set_nitz_enable(char nitz_enable);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_secboot_enable
 * DESCRIPTION 
 *  		This API is to get secboot enable or not
 * RETURN VALUES

 * RETURN MESSAGE
 * 		 0:secboot is disable
 *     1:secboot is enable
 *****************************************************************************/
extern int ol_get_secboot_enable(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *		ol_get_secboot_key_hash
 * DESCRIPTION 
 *  		This API is to get secboot pubilc key hash
 * RETURN VALUES

 * RETURN MESSAGE
 * 		 0:sucess
 *    -1:param error
 *****************************************************************************/
extern int ol_get_secboot_key_hash(unsigned int* buffer,unsigned int length);


#ifdef __cplusplus
}
#endif

#endif // #ifndef __MBTK_DEVICE_API_H


