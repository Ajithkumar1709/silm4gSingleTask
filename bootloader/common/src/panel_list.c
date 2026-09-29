#ifdef CRANE_MCU_DONGLE
#include "plat_types.h"
#else
#include "plat_basic_api.h"
#endif
#include "panel_drv.h"
#include "panel_list.h"

#ifdef LCD_GC9305_MCU
extern struct panel_spec lcd_gc9305_mcu_spec;
#endif

#ifdef LCD_GC9305_SPI_3WIRE_1LANE_1IF
extern struct panel_spec lcd_gc9305_spi_3wire_1lane_1if_spec;
#endif

#ifdef LCD_GC9305_SPI_3WIRE_2LANE_1IF
extern struct panel_spec lcd_gc9305_spi_3wire_2lane_1if_spec;
#endif

#ifdef LCD_GC9305_SPI_4WIRE_1LANE_1IF
extern struct panel_spec lcd_gc9305_spi_4wire_1lane_1if_spec;
#endif

#ifdef LCD_GC9306_SPI_3WIRE_1LANE_1IF
extern struct panel_spec lcd_gc9306_spi_3wire_1lane_1if_spec;
#endif

#ifdef LCD_GC9306_SPI_3WIRE_2LANE_1IF
extern struct panel_spec lcd_gc9306_spi_3wire_2lane_1if_spec;
#endif

#ifdef LCD_GC9306_SPI_4WIRE_1LANE_1IF
extern struct panel_spec lcd_gc9306_spi_4wire_1lane_1if_spec;
#endif

#ifdef LCD_ST7789V_MCU
extern struct panel_spec lcd_st7789v_mcu_spec;
#endif

#ifdef LCD_ST7789V_SPI_3WIRE_1LANE_1IF
extern struct panel_spec lcd_st7789v_spi_3wire_1lane_1if_spec;
#endif

#ifdef LCD_ST7789V_SPI_3WIRE_2LANE_1IF
extern struct panel_spec lcd_st7789v_spi_3wire_2lane_1if_spec;
#endif

#ifdef LCD_ST7789V_SPI_4WIRE_1LANE_1IF
extern struct panel_spec lcd_st7789v_spi_4wire_1lane_1if_spec;
#endif

#ifdef LCD_ST7789V_SPI_4WIRE_1LANE_2IF
extern struct panel_spec lcd_st7789v_spi_4wire_1lane_2if_spec;
#endif

#ifdef LCD_DUMMY_MCU
extern struct panel_spec lcd_dummy_mcu_spec;
#endif

#ifdef LCD_DUMMY_SPI_3WIRE_2LANE_1IF
extern struct panel_spec lcd_dummy_spi_3wire_2lane_1if_spec;
#endif

#if defined(CONFIG_BOARD_CRANEM_EVB)
#ifdef LCD_ST7735S_SPI_4WIRE_1LANE_1IF
extern struct panel_spec lcd_st7735s_spi_4wire_1lane_1if_spec;
#endif

#ifdef LCD_ST7735S_SPI_3WIRE_1LANE_1IF
extern struct panel_spec lcd_st7735s_spi_3wire_1lane_1if_spec;
#endif
#endif

static struct panel_spec* panels[] = {
#ifdef LCD_GC9305_MCU
	&lcd_gc9305_mcu_spec,
#endif

#ifdef LCD_GC9305_SPI_3WIRE_1LANE_1IF
	&lcd_gc9305_spi_3wire_1lane_1if_spec,
#endif

#ifdef LCD_GC9305_SPI_3WIRE_2LANE_1IF
	&lcd_gc9305_spi_3wire_2lane_1if_spec,
#endif

#ifdef LCD_GC9305_SPI_4WIRE_1LANE_1IF
	&lcd_gc9305_spi_4wire_1lane_1if_spec,
#endif

#ifdef LCD_GC9306_SPI_3WIRE_1LANE_1IF
	&lcd_gc9306_spi_3wire_1lane_1if_spec,
#endif

#ifdef LCD_GC9306_SPI_3WIRE_2LANE_1IF
	&lcd_gc9306_spi_3wire_2lane_1if_spec,
#endif

#ifdef LCD_GC9306_SPI_4WIRE_1LANE_1IF
	&lcd_gc9306_spi_4wire_1lane_1if_spec,
#endif

#ifdef LCD_ST7789V_MCU
	&lcd_st7789v_mcu_spec,
#endif

#ifdef LCD_ST7789V_SPI_3WIRE_1LANE_1IF
	&lcd_st7789v_spi_3wire_1lane_1if_spec,
#endif

#ifdef LCD_ST7789V_SPI_3WIRE_2LANE_1IF
	&lcd_st7789v_spi_3wire_2lane_1if_spec,
#endif

#ifdef LCD_ST7789V_SPI_4WIRE_1LANE_1IF
	&lcd_st7789v_spi_4wire_1lane_1if_spec,
#endif

#ifdef LCD_ST7789V_SPI_4WIRE_1LANE_2IF
	&lcd_st7789v_spi_4wire_1lane_2if_spec,
#endif

#ifdef LCD_DUMMY_MCU
	&lcd_dummy_mcu_spec,
#endif

#ifdef LCD_DUMMY_SPI_3WIRE_2LANE_1IF
	&lcd_dummy_spi_3wire_2lane_1if_spec,
#endif

/* for CraneM spi interface LCD */
#if defined(CONFIG_BOARD_CRANEM_EVB)
#ifdef LCD_ST7735S_SPI_4WIRE_1LANE_1IF
	&lcd_st7735s_spi_4wire_1lane_1if_spec,
#endif

#ifdef LCD_ST7735S_SPI_3WIRE_1LANE_1IF
	&lcd_st7735s_spi_3wire_1lane_1if_spec,
#endif
#endif
};

int get_panel_list(struct panel_spec*** plist)
{
	if(NULL == plist){
		LCDLOGE("ERROR: get_panel_list: Invalid param!\r\n");
		return -1;
	}

	*plist = &panels[0];
	return PANEL_MAX;
}
