#ifndef __MBTK_ADC_H
#define __MBTK_ADC_H

#ifdef __cplusplus
extern "C" {
#endif


typedef enum 
{
	mbtk_adc_index_0,
	mbtk_adc_index_1,
	mbtk_adc_index_2
}mbtk_adc_index_enum;



/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_adc_get_vol
 * DESCRIPTION 
 *          This API is to get adc value. 
 * PARAMETERS 
 *        adc_index        [IN]: adc_index
 * RETURN VALUES
 *        >=0 : adc value
 *        <0 : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern uint32_t ol_adc_get_vol(mbtk_adc_index_enum adc_index);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_adc_get_ver
 * DESCRIPTION 
 *          This API is to get adc ver. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *        NULL : error
 *        other : adc version str
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern unsigned char *ol_adc_get_ver(void);

#ifdef __cplusplus
}
#endif

#endif

