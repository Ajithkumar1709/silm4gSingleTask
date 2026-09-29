#ifndef __MBTK_I2C_H
#define __MBTK_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    mbtk_i2c_standrd_mode = 0,					/*100Kbps*/
    mbtk_i2c_fast_mode = 1,						/*400Kbps*/
    mbtk_high_speed_i2c_standrd_mode = 2,		/*3.4 Mbps slave/3.3 Mbps master,standard mode when not doing a high speed transfer*/
    mbtk_high_speed_i2c_fast_mode = 3,	        /*3.4 Mbps slave/3.3 Mbps master,fast mode when not doing a high speed transfer*/
}mbtk_i2c_mode_enum;


typedef enum 
{
	mbtk_i2c_devno_0, 							// not open
	mbtk_i2c_devno_1, 							// not open
	mbtk_i2c_devno_2  							// only  support devno_2
}mbtk_i2c_devno_enum;




/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_i2c_init
 * DESCRIPTION 
 *          This API is to init i2c. 
 * PARAMETERS 
 *        i2c_no      [IN]: i2c_no, enum see mbtk_i2c_devno_enum
 *        i2c_mode    [IN]: i2c_mode, enum see mbtk_i2c_mode_enum
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_i2c_init(mbtk_i2c_devno_enum i2c_no, mbtk_i2c_mode_enum i2c_mode);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_i2c_write
 * DESCRIPTION 
 *          This API is to write data to reg. 
 * PARAMETERS 
 *        i2c_no      [IN]: i2c_no, enum see mbtk_i2c_devno_enum
 *        slave_addr  [IN]: slave_addr
 *        cmd         [IN]: cmd
 *        cmdlen      [IN]: cmdlen
 *        data        [IN]: data
 *        datalen     [IN]: datalen
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_i2c_write(mbtk_i2c_devno_enum i2c_no, uint8_t slave_addr, uint8_t *cmd, uint32_t cmdlen,uint8_t *data, uint32_t datalen);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_i2c_read
 * DESCRIPTION 
 *          This API is to read data from reg. 
 * PARAMETERS 
 *        i2c_no      [IN]: i2c_no, enum see mbtk_i2c_devno_enum
 *        slave_addr  [IN]: slave_addr
 *        cmd         [IN]: cmd
 *        cmdlen      [IN]: cmdlen
 *        data        [IN]: data
 *        datalen     [IN]: datalen
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_i2c_read(mbtk_i2c_devno_enum i2c_no, uint8_t slave_addr, uint8_t *cmd, uint32_t cmdlen, uint8_t *data, uint32_t datalen);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_i2c_deinit
 * DESCRIPTION 
 *          This API is to deinit i2c. 
 * PARAMETERS 
 *        i2c_no     [IN]: i2c_no, enum see mbtk_i2c_devno_enum
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_i2c_deinit(mbtk_i2c_devno_enum i2c_no);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_i2c_get_ver
 * DESCRIPTION 
 *          This API is to get i2c version. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *        NULL : fail
 *        other  : i2c version str
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern unsigned char *ol_i2c_get_ver(void);

#ifdef __cplusplus
}
#endif

#endif

