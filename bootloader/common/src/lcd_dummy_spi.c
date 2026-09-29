#ifdef LCD_DUMMY_SPI_3WIRE_2LANE_1IF
#ifdef CRANE_MCU_DONGLE
#include "panel_drv.h"
#else
#include "../../chip/lcd/panel_drv.h"
#endif

#define LCD_DUMMY_SPI_ID 0xF8F8F8F8

static int lcd_panel_interface_init(struct panel_spec *self, uint32_t sclk, int32_t work_mode)
{
	struct s_spi_ctx *spi_ctx = NULL;

	if(NULL == self){
		LCDLOGE("ERROR: panel_interface_init, Invalid param");
		return -1;
	}

	spi_ctx = spi_init(sclk, (struct spi_info *)self->info, work_mode);
	if(NULL == spi_ctx){
		LCDLOGE("ERROR: panel_interface_init, spi init fail!");
		return -1;
	}
	self->panel_if = (void*)spi_ctx;
	return 0;
}

static int lcd_panel_interface_update(struct panel_spec *self, int32_t work_mode)
{
	int ret;

	if(NULL == self || NULL == self->panel_if){
		LCDLOGE("ERROR: lcd_panel_interface_update, Invalid param\r\n");
		return -1;
	}
	
	ret = spi_update((struct s_spi_ctx *)self->panel_if, work_mode);
	return ret;
}

static struct panel_operations lcd_dummy_spi_ops = {
	lcd_panel_interface_init,
	lcd_panel_interface_update,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

static struct timing_spi lcd_dummy_spi_3wire_2lane_1if_timing = {
	5000, /*kHz*/
	5000, /*kHz*/
};

static struct spi_info lcd_dummy_spi_3wire_2lane_1if_info = {
	3,
	1, 
	2,
	SPI_FORMAT_RGB565,
	0,
	SPI_EDGE_RISING,
	0,
	SPI_ENDIAN_MSB,
	0,
	&lcd_dummy_spi_3wire_2lane_1if_timing,
};


struct panel_spec lcd_dummy_spi_3wire_2lane_1if_spec = {
	"dummy_spi",
	LCD_DUMMY_SPI_ID,
	LCD_CAP_FAKE,
	240,
	320,
	LCD_MODE_SPI,
	LCD_POLARITY_POS,
	&lcd_dummy_spi_3wire_2lane_1if_info,
	NULL,
	&lcd_dummy_spi_ops,
};
#endif /*LCD_DUMMY_SPI_3WIRE_2LANE_1IF*/
