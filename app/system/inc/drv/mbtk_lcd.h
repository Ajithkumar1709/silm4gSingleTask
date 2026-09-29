#ifndef __MBTK_LCD_H__
#define __MBTK_LCD_H__

#ifdef __cplusplus
extern "C" {
#endif


typedef enum 
{
	mbtk_lcd_screen_turn_off,
	mbtk_lcd_screen_turn_on
}mbtk_lcd_screen_switch_enum;


typedef enum 
{
	mbtk_lcd_pmic_power_off,
	mbtk_lcd_pmic_power_on
}mbtk_lcd_power_switch_enum;


typedef union
{
    struct
    {
        uint16_t blue  :5;
        uint16_t green :6;
        uint16_t red   :5;
    };
    uint16_t full;
}mbtk_lcd_color_struct;


/*****************************************************************************
 * FUNCTION
 *  ol_lcd_flush
 * DESCRIPTION
 *  This API is to flush rgb565 buffer to lcd with lcd set size   (lv_conf.h)
 *
 * PARAMETERS
 *  color         : [IN]  rgb565 buffer 
 * RETURN VALUES
 *  void
 *
 *****************************************************************************/
extern void ol_lcd_flush(const mbtk_lcd_color_struct *color);


/*****************************************************************************
 * FUNCTION
 *  ol_lcd_power_switch
 * DESCRIPTION
 *  This API is to power on / off lcd
 *
 * PARAMETERS
 *  on_off      : [IN]  mbtk_lcd_power_switch_enum type  on / off
 * 
 * RETURN VALUES
 *  0: success	
 *  -1: fail
 *
 *****************************************************************************/
extern int ol_lcd_power_switch(mbtk_lcd_power_switch_enum on_off);

/*****************************************************************************
 * FUNCTION
 *  ol_lcd_get_dimension
 * DESCRIPTION
 *  This API is to get lcd dimension
 *
 * PARAMETERS
 *  width      : [OUT]  lcd width 
    height      : [OUT]  lcd height
 *
 * RETURN VALUES
 * void
 *
 *****************************************************************************/
 extern void ol_lcd_get_dimension(uint16_t *width, uint16_t *height);


/*****************************************************************************
 * FUNCTION
 *  ol_lcd_set_backlight_level
 * DESCRIPTION
 *  This API is to modify backlight level
 *
 * PARAMETERS
 *  level      : [IN]  backlight level 0/1                            
 * RETURN VALUES
 *  0: success	
 *  -1: fail
 *
 *****************************************************************************/
extern int ol_lcd_set_backlight_level(uint8_t level);


/*****************************************************************************
 * FUNCTION
 *  ol_lcd_clean_screen
 * DESCRIPTION
 *  This API is to flush rgb565 buffer to lcd with lcd with set size
 *
 * PARAMETERS
 *  start_x      : [IN]  stat x
 *  start_y      : [IN]  stat y
 *  end_x        : [IN]  end x
 *  end_y        : [IN]  end y
 *  color        : [IN]  RGB buffer 
 
 * RETURN VALUES
 *
 *****************************************************************************/
extern int ol_lcd_clean_screen(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, const mbtk_lcd_color_struct *color);
/*****************************************************************************
 * FUNCTION
 *  ol_lcd_clean_screen
 * DESCRIPTION
 *  This API is to flush rgb565 buffer to lcd with lcd with set size
 *
 * PARAMETERS
 *  start_x      : [IN]  stat x
 *  start_y      : [IN]  stat y
 *  end_x        : [IN]  end x
 *  end_y        : [IN]  end y
 *  color        : [IN]  RGB buffer 
 *  switch_flag  : [IN]  switch lcd
 * RETURN VALUES
 *
 *****************************************************************************/
extern int ol_lcd_clean_screen2(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, const mbtk_lcd_color_struct *color);//zhengzhou for anfu rgb lcd+fstn lcd

extern int ol_lcd_clean_screen_ex(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, const mbtk_lcd_color_struct *color);//zhengzhou for anfu rgb lcd+fstn lcd


extern void ol_lcd_wakeup(void);
extern void ol_lcd_sleep(void);

#ifdef __cplusplus
}
#endif

#endif
