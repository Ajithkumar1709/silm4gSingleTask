#ifndef _OL_QRCODE_H_
#define _OL_QRCODE_H_

#define CAM_SUPPORT_MAX_DECODE_LEN 2500

typedef enum 
{
	QR_DECODE,
	A_CODE,
	B_CODE,
}OL_CAM_DECODE_TYPE;

typedef struct
{
	unsigned char  Type;
	int            DecodeLen;
	int            result;
	unsigned char  DataBuf[CAM_SUPPORT_MAX_DECODE_LEN];
} CAL_IDENTITY_RESULT_STRUCT,*P_CAL_IDENTITY_RESULT_STRUCT;

typedef void (*qrcode_callback)(P_CAL_IDENTITY_RESULT_STRUCT outdata);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_qrcode_get_ver
 * DESCRIPTION 
 *        This API is to get the qr decoder lib version. 
 * PARAMETERS 
 *        ver      [OUT]: version string buffer
 *        versize  [IN]: version string buffer size
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
int ol_qrcode_get_ver(char *ver, int versize);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_qrcode_init
 * DESCRIPTION 
 *        This API is to init the qr decoder. 
 * PARAMETERS 
 *        dectaskprio  [IN]: pwm_no, enum see mbtk_pwm_no_enum
 *        height    	 [IN]: high_duty
 *        width  			 [IN]: pwm_no, enum see mbtk_pwm_no_enum
 *        decbufcnt    [IN]: pwm_no, enum see mbtk_pwm_no_enum
 *        decbufaddr   [IN]: pwm_no, enum see mbtk_pwm_no_enum
 *        decodecb     [IN]: pwm_no, enum see mbtk_pwm_no_enum
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
int ol_qrcode_init(unsigned char  dectaskprio,
	unsigned int height,
	unsigned int width,
	unsigned char decbufcnt,
	qrcode_callback decodecb);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_qrcode_deinit
 * DESCRIPTION 
 *        This API is to releae qr decoder resource. 
 * PARAMETERS 
 *        NONE
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
int ol_qrcode_deinit(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_pwm_enable
 * DESCRIPTION 
 *          This API is to enable pwm. 
 * PARAMETERS 
 *        pwm_no      [IN]: pwm_no, enum see mbtk_pwm_no_enum
 *        high_duty    [IN]: high_duty
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
int ol_qrcode_start(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_pwm_enable
 * DESCRIPTION 
 *          This API is to enable pwm. 
 * PARAMETERS 
 *        buffaddr     [IN]: the decode resource buffer
 *        dump_addr    [IN]: decoder cache buffer array
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
int ol_qrcode_set_buffer(unsigned int buffaddr,unsigned int dump_addr);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_qrcode_get_authorize_status
 * DESCRIPTION 
 *        This API is to get the qr edcoder lib authorize status. 
 * PARAMETERS 
 *        NONE
 * RETURN VALUES
 *        =0 : authorized
 *        !=0   : unauthorized
 * RETURN MESSAGE
 *        NONE
 *
 *****************************************************************************/
int ol_qrcode_get_authorize_status(void);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_qrcode_set_enable
 * DESCRIPTION 
 *        This API is to enable the qr decoder. 
 * PARAMETERS 
 *        enable      [IN]: enable value,1 enable,0 disable
 * RETURN VALUES
 *        NONE
 * RETURN MESSAGE
 *        NONE
 *
 *****************************************************************************/
void ol_qrcode_set_enable(unsigned char enable); 


#endif	// _CAMERA_TEST_H_

