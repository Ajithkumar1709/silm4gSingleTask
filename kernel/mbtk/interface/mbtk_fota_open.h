#ifndef MBTK_FOTA_OPEN_H
#define MBTK_FOTA_OPEN_H

#define MBTK_FOTA_SERVER_CONTEXT_STRLEN 512
#define MI_FOTA_DATAEX_REQ  10

typedef struct
{
	char host[MBTK_FOTA_SERVER_CONTEXT_STRLEN]; /*xx.xx.xx.xx:port, or URL*/	
	char username[MBTK_FOTA_SERVER_CONTEXT_STRLEN];
	char password[MBTK_FOTA_SERVER_CONTEXT_STRLEN];
	unsigned char mode; /*0: ftp, 1: http*/
}mbtk_fota_server_info;


typedef enum{
	MFOTA_OPT_TYPE_PRE_VERIFY,
	MFOTA_OPT_TYPE_FIR,
	MFOTA_OPT_TYPE_SEC
}MFOTA_OPT_TYPE;

extern int mbtk_fota_context_init(mbtk_fota_server_info *server_info,int package_size,bool need_check,void (*callback)(void *));
extern void mbtk_fota_context_deinit(void);
extern int mbtk_fota_pkg_write(char * data, int dataLen ,unsigned int package_size);
extern int mbtk_fota_pkg_flush_flash(void);
extern int mbtk_fota_image_verify(void);

extern int mbtk_fota_firmware_download(mbtk_fota_server_info *server_info,bool auto_reboot,void (*callback)(void *));
extern int mbtk_fota_get_proccess(void);
extern void mbtk_fota_stop_reboot(void);
extern int mbtk_fota_get_upgrade_result(void);
int mbtk_mini_fota_firmware_download(mbtk_fota_server_info *server_info, void (*callback)(void *));
int mbtk_fota_set_firmware_limite(unsigned int limite);
#endif
