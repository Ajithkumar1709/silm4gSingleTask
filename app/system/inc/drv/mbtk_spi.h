#ifndef __MBTK_SPI_H
#define __MBTK_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum 
{
	mbtk_spi_index_0,
	mbtk_spi_index_1,
	mbtk_spi_index_2,
}mbtk_spi_index_enum;



typedef enum 
{
	mbtk_spi_clk_812_5K,
	mbtk_spi_clk_1_625M,
	mbtk_spi_clk_3_25M,
	mbtk_spi_clk_6_5M,
	mbtk_spi_clk_13M,
	mbtk_spi_clk_26M,
	mbtk_spi_clk_52M,
}mbtk_spi_clk_enum;



typedef enum 
{
	mbtk_spi_master_mode,
	mbtk_spi_slave_mode
}mbtk_spi_control_mode;


typedef enum
{
	mbtk_spi_error_none,
	mbtk_spi_error_param = -1,
	mbtk_spi_error_init_first = -2,
	mbtk_spi_error_deinit_first = -3
}mbtk_spi_error;


typedef enum 
{
	mbtk_spi_mode0,
	mbtk_spi_mode1,
	mbtk_spi_mode2,
	mbtk_spi_mode3
}mbtk_spi_mode_enum;


/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_spi_init
 * DESCRIPTION 
 *          This API is to init spi. 
 * PARAMETERS 
 *        spi_num      [IN]: spi_num, enum see mbtk_spi_index_enum
 *        spi_mode      [IN]: spi_mode, enum see mbtk_spi_mode_enum
 *        spi_clk      [IN]: spi_clk, enum see mbtk_spi_clk_enum
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_spi_init(mbtk_spi_index_enum spi_num, mbtk_spi_mode_enum spi_mode, mbtk_spi_clk_enum spi_clk);


/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_spi_init_ex
 * DESCRIPTION 
 *          This API is to init spi. 
 * PARAMETERS 
 *        spi_num      [IN]: spi_num, enum see mbtk_spi_index_enum
 *        spi_mode      [IN]: spi_mode, enum see mbtk_spi_mode_enum
 *        spi_clk      [IN]: spi_clk, enum see mbtk_spi_clk_enum
          ctrl_mode    [IN] : ctrl_mode, enum see mbtk_spi_control_mode
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_spi_init_ex(mbtk_spi_index_enum spi_num, mbtk_spi_mode_enum spi_mode, mbtk_spi_clk_enum spi_clk, mbtk_spi_control_mode ctrl_mode);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_spi_write_read
 * DESCRIPTION 
 *          This API is to spi write and read. 
 * PARAMETERS 
 *        spi_num      [IN]: spi_num, enum see mbtk_spi_index_enum
 *        read_buf      [IN]: read_buf
 *        write_buf      [IN]: write_buf
 *        data_len      [IN]: data_len
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_spi_write_read(mbtk_spi_index_enum spi_num, uint8_t *read_buf, uint8_t *write_buf, uint32_t data_len);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_spi_write
 * DESCRIPTION 
 *          This API is to spi write. 
 * PARAMETERS 
 *        spi_num      [IN]: spi_num, enum see mbtk_spi_index_enum
 *        write_buf      [IN]: write_buf
 *        data_len      [IN]: data_len
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_spi_write(mbtk_spi_index_enum spi_num, uint8_t *write_buf, uint32_t data_len);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_spi_read
 * DESCRIPTION 
 *          This API is to spi read. 
 * PARAMETERS 
 *        spi_num      [IN]: spi_num, enum see mbtk_spi_index_enum
 *        read_buf      [IN]: read_buf
 *        data_len      [IN]: data_len
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_spi_read(mbtk_spi_index_enum spi_num, uint8_t *read_buf, uint32_t data_len);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_spi_deinit
 * DESCRIPTION 
 *          This API is to deinit spi. 
 * PARAMETERS 
 *        spi_num      [IN]: spi_num, enum see mbtk_spi_index_enum
 * RETURN VALUES
 *        =0 : successful
 *        <=0   : error
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern int ol_spi_deinit(mbtk_spi_index_enum spi_num);

/*****************************************************************************
 *
 * FUNCTIO 
 *        ol_spi_get_ver
 * DESCRIPTION 
 *          This API is to get spi version. 
 * PARAMETERS 
 *        NULL
 * RETURN VALUES
 *        NULL : fail
 *        other  : spi version str
 * RETURN MESSAGE
 *          NONE
 *
 *****************************************************************************/
extern unsigned char *ol_spi_get_ver(void);

#ifdef __cplusplus
}
#endif

#endif

