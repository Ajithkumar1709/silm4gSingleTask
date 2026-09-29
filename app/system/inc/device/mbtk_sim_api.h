#ifndef __MBTK_SIM_API_H
#define __MBTK_SIM_API_H

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define MBTK_SIM_PH_BOOK_USER_LEN   33
#define MBTK_SIM_PH_BOOK_PH_NUM_LEN 25
#define MBTK_SIM_PIN_MAX_LEN   16
#define MBTK_SIM_PUK_MAX_LEN   16



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
//此状态对应AT手册的AT+CPIN 返回


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


/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_sim_status
 * DESCRIPTION 
 *          This API is to get the sim status. 
 * PARAMETERS 
 *        status        [IN]: sim status
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_get_sim_status(uint8_t *status);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_sim_call_readly
 * DESCRIPTION 
 *          This API is to get call readly status. 
 * PARAMETERS 
 *        NONE
 * RETURN VALUES
 *        = 0 : call not readly
 *				= 1 : call readly
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
 extern int ol_sim_call_readly(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_sim_imsi
 * DESCRIPTION 
 *          This API is to get the sim imsi. 
 * PARAMETERS 
 *        imsi        [IN]: sim imsi
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/

extern mbtk_sim_api_err_enum ol_get_sim_imsi(uint8_t *imsi);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_sim_iccid
 * DESCRIPTION 
 *          This API is to get the sim iccid. 
 * PARAMETERS 
 *        iccid        [IN]: sim iccid
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_get_sim_iccid(uint8_t *iccid);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_sim_phonenumber
 * DESCRIPTION 
 *          This API is to set the sim phnumber. 
 * PARAMETERS 
 *        phnumber        [IN]: sim phnumber
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_get_sim_phonenumber(uint8_t *phnumber);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_read_phonebook_record
 * DESCRIPTION 
 *          This API is to read the sim phonebook. 
 * PARAMETERS 
 *        storge        [IN]: storge type
 *        username        [IN]: username
 *        start_index        [IN]: start_index
 *        end_index        [IN]: end_index
 *        info        [IN]: phone book info
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_read_phonebook_record(mbtk_phone_book_storge_enum storge, uint8_t *username, uint16_t start_index, uint16_t end_index, mbtk_phone_book_info_struct *info);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_write_phonebook_record
 * DESCRIPTION 
 *          This API is to read the sim phonebook. 
 * PARAMETERS 
 *        storge        [IN]: storge type
 *        write_index        [IN]: write_index
 *        info        [IN]: phone book info
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_write_phonebook_record(mbtk_phone_book_storge_enum storge, uint8_t write_index, mbtk_phone_book_info_struct *info);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_sim1_status
 * DESCRIPTION 
 *          This API is to get the sim1 status. 
 * PARAMETERS 
 *        status        [IN]: status
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_get_sim1_status(uint8_t *status);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_sim1_imsi
 * DESCRIPTION 
 *          This API is to get the sim1 imsi. 
 * PARAMETERS 
 *        imsi        [IN]: imsi
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_get_sim1_imsi(uint8_t *imsi);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_sim1_iccid
 * DESCRIPTION 
 *          This API is to get the sim1 iccid. 
 * PARAMETERS 
 *        iccid        [IN]: iccid
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_get_sim1_iccid(uint8_t *iccid);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_sim1_phonenumber
 * DESCRIPTION 
 *          This API is to get the sim1 phnumber. 
 * PARAMETERS 
 *        phnumber        [IN]: phnumber
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_get_sim1_phonenumber(uint8_t *phnumber);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_sim2_status
 * DESCRIPTION 
 *          This API is to get the sim2 status. 
 * PARAMETERS 
 *        status        [IN]: status
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_get_sim2_status(uint8_t *status);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_sim2_imsi
 * DESCRIPTION 
 *          This API is to get the sim2 imsi. 
 * PARAMETERS 
 *        imsi        [IN]: imsi
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_get_sim2_imsi(uint8_t *imsi);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_sim2_iccid
 * DESCRIPTION 
 *          This API is to get the sim2 iccid. 
 * PARAMETERS 
 *        iccid        [IN]: iccid
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_get_sim2_iccid(uint8_t *iccid);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_sim2_phonenumber
 * DESCRIPTION 
 *          This API is to get the sim2 phnumber. 
 * PARAMETERS 
 *        phnumber        [IN]: phnumber
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_get_sim2_phonenumber(uint8_t *phnumber);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_switch_sim
 * DESCRIPTION 
 *          This API is to switch master sim. 
 * PARAMETERS 
 *        simId        [IN]: simId
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_switch_sim(uint8_t simId);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_get_current_master_sim
 * DESCRIPTION 
 *          This API is to get current master simid. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *        current_master_sim
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_get_current_master_sim(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_sim_verify_pin
 * DESCRIPTION 
 *          This API is to verify pin. 
 * PARAMETERS 
 *        pin_buf        [IN]: pin_buf
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_sim_verify_pin(mbtk_sim_pin_struct *pin_buf);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_sim_change_pin
 * DESCRIPTION 
 *          This API is to change pin. 
 * PARAMETERS 
 *        pin_buf        [IN]: pin_buf
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_sim_change_pin(mbtk_change_sim_pin_struct *pin_buf);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_sim_unblock_pin
 * DESCRIPTION 
 *          This API is to unblock pin. 
 * PARAMETERS 
 *        pin_buf        [IN]: pin_buf
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_sim_unblock_pin(mbtk_unblock_sim_pin_struct *pin_buf);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_sim_enable_pin
 * DESCRIPTION 
 *          This API is to enable pin. 
 * PARAMETERS 
 *        pin_buf        [IN]: pin_buf
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_sim_enable_pin(mbtk_sim_pin_struct *pin_buf);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_sim_diable_pin
 * DESCRIPTION 
 *          This API is to diable pin. 
 * PARAMETERS 
 *        pin_buf        [IN]: pin_buf
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error ,see enum mbtk_sim_api_err_enum
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern mbtk_sim_api_err_enum ol_sim_diable_pin(mbtk_sim_pin_struct *pin_buf);

#ifdef __cplusplus
}
#endif

#endif // #ifndef __MBTK_SIM_API_Hs

