



#ifndef __MBTK_SIM_API_H
#define __MBTK_SIM_API_H



#define MBTK_SIM_PIN_MAX_LEN   16
#define MBTK_SIM_PUK_MAX_LEN   16


#define MBTK_SIM_PH_BOOK_USER_LEN   33
#define MBTK_SIM_PH_BOOK_PH_NUM_LEN 25

typedef enum 
{
	mbtk_sim_api_err = -1,
	mbtk_sim_api_err_none = 0
}mbtk_sim_api_err_enum;



typedef enum 
{
	mbtk_sim_not_insert,
	mbtk_sim_ready,
	mbtk_sim_sim_pin,
	mbtk_sim_sim_puk,
	mbtk_sim_ph_sim_lock_pin,
	mbtk_sim_ph_sim_lock_puk,
	mbtk_sim_ph_fsim_pin,
	mbtk_sim_ph_fsim_puk,
	mbtk_sim_sim_pin2,
	mbtk_sim_sim_puk2,
	mbtk_sim_ph_net_pin,
	mbtk_sim_ph_net_puk,
	mbtk_sim_ph_net_sub_pin,
	mbtk_sim_ph_net_sub_puk,
	mbtk_sim_ph_sp_pin,
	mbtk_sim_ph_sp_puk,
	mbtk_sim_ph_corp_pin,
	mbtk_sim_ph_corp_puk,
	mbtk_sim_busy,
	mbtk_sim_blocked,
	mbtk_sim_unknown
}mbtk_sim_status_enum;


typedef enum 
{
	mbtk_ph_book_storge_dc,
	mbtk_ph_book_storge_en,
	mbtk_ph_book_storge_fd,
	mbtk_ph_book_storge_ld,
	mbtk_ph_book_storge_mc,
	mbtk_ph_book_storge_me,
	mbtk_ph_book_storge_mt,
	mbtk_ph_book_storge_on,
	mbtk_ph_book_storge_rc,
	mbtk_ph_book_storge_sm,
	mbtk_ph_book_storge_ap,
	mbtk_ph_book_storge_mbdn,
	mbtk_ph_book_storge_mn,
	mbtk_ph_book_storge_sdn,
	mbtk_ph_book_storge_ici,
	mbtk_ph_book_storge_oci
}mbtk_phone_book_storge_enum;

typedef struct 
{
	uint16_t index;
	uint8_t username[MBTK_SIM_PH_BOOK_USER_LEN];
	uint8_t phonenum[MBTK_SIM_PH_BOOK_PH_NUM_LEN];
}mbtk_phone_book_info_struct;



typedef struct 
{
	uint8_t mbtk_sim_pin_buf[MBTK_SIM_PIN_MAX_LEN];
}mbtk_sim_pin_struct;

typedef struct 
{
	uint8_t mbtk_old_sim_pin_buf[MBTK_SIM_PIN_MAX_LEN];
	uint8_t mbtk_new_sim_pin_buf[MBTK_SIM_PIN_MAX_LEN];
}mbtk_change_sim_pin_struct;


typedef struct 
{
	uint8_t mbtk_sim_puk_buf[MBTK_SIM_PUK_MAX_LEN];
	uint8_t mbtk_sim_pin_buf[MBTK_SIM_PIN_MAX_LEN];
}mbtk_unblock_sim_pin_struct;



void mbtk_sim_demo_run(void);

mbtk_sim_api_err_enum mbtk_get_sim_status(uint8_t *status);

int mbtk_sim_call_readly(void);
	
mbtk_sim_api_err_enum mbtk_sim_get_imsi(uint8_t *imsi);

mbtk_sim_api_err_enum mbtk_sim_get_iccid(uint8_t *iccid);

mbtk_sim_api_err_enum mbtk_sim_get_phnumber(uint8_t *phnumber);

mbtk_sim_api_err_enum mbtk_read_phone_book_record(mbtk_phone_book_storge_enum storge, uint8_t *username,
															uint16_t start_index, uint16_t end_index, mbtk_phone_book_info_struct *info);

mbtk_sim_api_err_enum mbtk_write_phone_book_record(mbtk_phone_book_storge_enum storge, uint8_t write_index, mbtk_phone_book_info_struct *info);

mbtk_sim_api_err_enum mbtk_sim_verify_pin(mbtk_sim_pin_struct *pin_buf);

mbtk_sim_api_err_enum mbtk_sim_change_pin(mbtk_change_sim_pin_struct *pin_buf);
mbtk_sim_api_err_enum mbtk_sim_unblock_pin(mbtk_unblock_sim_pin_struct *pin_buf);
mbtk_sim_api_err_enum mbtk_sim_enable_pin(mbtk_sim_pin_struct *pin_buf);
mbtk_sim_api_err_enum mbtk_sim_diable_pin(mbtk_sim_pin_struct *pin_buf);

mbtk_sim_api_err_enum mbtk_get_sim1_status(uint8_t *status);

mbtk_sim_api_err_enum mbtk_sim1_get_imsi(uint8_t *imsi);

mbtk_sim_api_err_enum mbtk_sim1_get_iccid(uint8_t *iccid);

mbtk_sim_api_err_enum mbtk_sim1_get_phnumber(uint8_t *phnumber);

mbtk_sim_api_err_enum mbtk_get_sim2_status(uint8_t *status);

mbtk_sim_api_err_enum mbtk_sim2_get_imsi(uint8_t *imsi);

mbtk_sim_api_err_enum mbtk_sim2_get_iccid(uint8_t *iccid);

mbtk_sim_api_err_enum mbtk_sim2_get_phnumber(uint8_t *phnumber);

mbtk_sim_api_err_enum mbtk_switch_sim(uint8_t simId);

int mbtk_get_current_master_sim(void);
#endif // #ifndef __MBTK_SIM_API_Hs