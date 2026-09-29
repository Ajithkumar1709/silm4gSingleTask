#ifndef __MBTK_PWM_H
#define __MBTK_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
{
	mbtk_pwm_no_0,
	mbtk_pwm_no_1,
	mbtk_pwm_no_2,
	mbtk_pwm_no_3,
	mbtk_pwm_no_max
}mbtk_pwm_no_enum;

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
extern int ol_pwm_enable(mbtk_pwm_no_enum pwm_no, uint8_t high_duty);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_pwm_enable_ex
 * DESCRIPTION 
 *          This API is to enable pwm. 
 * PARAMETERS 
 *        pwm_no      [IN]: pwm_no, enum see mbtk_pwm_no_enum
 *        high_duty    [IN]: high_duty
 *        freq    [IN]: freq
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_pwm_enable_ex(mbtk_pwm_no_enum pwm_no, uint8_t high_duty,uint32_t freq);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_pwm_disable
 * DESCRIPTION 
 *          This API is to disable pwm. 
 * PARAMETERS 
 *        pwm_no      [IN]: pwm_no, enum see mbtk_pwm_no_enum
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_pwm_disable(mbtk_pwm_no_enum pwm_no);

#ifdef __cplusplus
}
#endif

#endif

