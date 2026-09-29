




#ifndef __MBTK_DEVICE_API_H
#define __MBTK_DEVICE_API_H




typedef void (*mbtk_usb_detect_callback)(int status);
typedef void (*mbtk_nitz_cb)(void);

#define MBTK_DEVICE_IMEI_LENGTH     15

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


void mbtk_device_api_demo_run(void);


mbtk_device_api_err_enum mbtk_get_imei(uint8_t *imei);

mbtk_device_api_err_enum mbtk_get_firmware_version(mbtk_device_firmware_ver_struct **version);

mbtk_device_api_err_enum mbtk_get_current_time(mbtk_device_time_struct *ptime);

mbtk_device_api_err_enum mbtk_get_sn(uint8_t *sn);

mbtk_device_api_err_enum mbtk_set_modem_function(mbtk_device_modem_fun_enum fun, uint8_t rst);

mbtk_device_api_err_enum mbtk_get_modem_function(uint8_t *fun);


extern void ol_usbdect_register_cb(mbtk_usb_detect_callback callback);

mbtk_device_api_err_enum mbtk_get_mac(uint8_t *mac);

mbtk_device_api_err_enum mbtk_factory_operation(uint8_t oper_type, char* buffer, uint8_t len, uint8_t data_num);

mbtk_device_api_err_enum mbtk_get_sn2(uint8_t *sn);

char* mbtk_get_buildtime();

void mbtk_set_syssleep_status(unsigned char status);

void mbtk_set_nitz_ind_cb(mbtk_nitz_cb cb);

#endif // #ifndef __MBTK_DEVICE_API_H

