#if defined(CONFIG_BOARD_CRANEM_EVB)
#if (defined(LCD_ST7735S_SPI_3WIRE_1LANE_1IF) || defined(LCD_ST7735S_SPI_4WIRE_1LANE_1IF))
#ifdef CRANE_MCU_DONGLE
	#include "panel_drv.h"
	#include "plat_types.h"
#else
	#include "../../chip/lcd/panel_drv.h"
	#include "plat_config_defs.h"
#endif
#include <ui_os_api.h>

#define HAL_GPIO_31 31
#define LCD_RST_GPIO HAL_GPIO_31
#define HAL_GPIO_121 121
#define CRANEM_SPI_4LINE_DCX HAL_GPIO_121

#define FORMAT_RGB565 16

static int lcd_panel_craneM_spi_init(struct panel_spec *self, uint32_t sclk, int32_t work_mode)
{
	struct s_spi_ctx *spi_ctx = NULL;
	struct spi_info * spi = NULL;

	LCDLOGI("INFO: lcd_panel_spi_init, spi+++\r\n");

	if (NULL == self) {
		LCDLOGE("ERROR: panel_interface_init, Invalid param\r\n");
		return -1;
	}

	spi = (struct spi_info *)self->info;

	spi_ctx = spi_init(sclk, spi, work_mode);
	if (NULL == spi_ctx){
		LCDLOGE("ERROR: panel_interface_init, spi init fail!\r\n");
		return -1;
	}
	self->panel_if = (void*)spi_ctx;

	return 0;
}

int lcd_panel_craneM_spi_uninit(struct panel_spec *self)
{
	struct s_spi_ctx *spi_ctx = NULL;

	LCDLOGD("DBG: lcd_panel_interface_uninit, spi+++\r\n");
#if 0
	if(NULL == self){
		LCDLOGE("ERROR: lcd_panel_interface_uninit, Invalid param\r\n");
		return -1;
	}

	spi_ctx = (struct s_spi_ctx*)self->panel_if;
	spi_uninit(spi_ctx);
	self->panel_if = NULL;
	LCDLOGD("DBG: lcd_panel_interface_uninit, spi---\r\n");
#endif
	return 0;
}

int lcd_panel_craneM_spi_reset(struct panel_spec *self)
{
	struct s_spi_ctx *spi_ctx = NULL;

	LCDLOGD("DBG: lcd_panel_interface_reset, spi+++\r\n");

	if (NULL == self) {
		LCDLOGE("ERROR: lcd_panel_interface_reset, Invalid param\r\n");
		return -1;
	}

	//spi_ctx = (struct s_spi_ctx*)self->panel_if;
	//spi_reset(spi_ctx);
	LCDLOGD("DBG: lcd_panel_interface_reset, spi---\r\n");

	return 0;
}

static int lcd_panel_craneM_spi_update(struct panel_spec *self, int32_t work_mode)
{
	int ret;
	struct s_spi_ctx* spi_ctx = NULL;

	if (NULL == self || NULL == self->panel_if) {
		LCDLOGE("ERROR: lcd_panel_interface_update, Invalid param\r\n");
		return -1;
	}
	ret = spi_update((struct s_spi_ctx *)self->panel_if, work_mode);
	return ret;
}

void lcd_panel_refresh(struct panel_spec *self, uint16_t* data)
{
	struct s_spi_ctx* spi_ctx = NULL;
	struct spi_info * spi = NULL;
	struct panel_spec *panel = self;

	if (NULL == self) {
		LCDLOGE("ERROR: panel is null\r\n");
		return;
	}

	if (NULL == self->panel_if) {
		LCDLOGE("ERROR: panel_init, mcu has not been inited!\r\n");
		return;
	}

	spi_ctx = (struct s_spi_ctx*)self->panel_if;
	spi = (struct spi_info *)self->info;

	spi_write_cmd (spi_ctx, 0x2C, 8);
	if (spi->line_num == 4) {
		gpio_set_output(CRANEM_SPI_4LINE_DCX);
		gpio_set_value(CRANEM_SPI_4LINE_DCX, 1);
	}
	/* data write with 26M */
	spi_set_clk_rate(SPI_26M);

	//LCDLOGE("%s panel name:%s width:%d height:%d \r\n", __func__, panel->name, panel->width, panel->height);
	ssp_write_data_to_LCD_Gram(data, panel->width * panel->height, FORMAT_RGB565, spi->line_num);

	wait_ssp_write_data_to_LCD_complete();
	if (spi->line_num == 4)
		gpio_set_value(CRANEM_SPI_4LINE_DCX, 0);
	
	/* data read with 812_5k */
	spi_set_clk_rate(SPI_812_5k);
}

static int lcd_panel_init(struct panel_spec *self)
{
	struct s_spi_ctx* spi_ctx = NULL;
	struct spi_info * spi = NULL;

	if (NULL == self) {
		LCDLOGE("ERROR: panel_init, Invalid param\r\n");
		return -1;
	}

	if (NULL == self->panel_if) {
		LCDLOGE("ERROR: panel_init, mcu has not been inited!\r\n");
		return -1;
	}

	spi_ctx = (struct s_spi_ctx*)self->panel_if;
	spi = (struct spi_info *)self->info;

    spi_write_cmd(spi_ctx,  0x11, 8); 
	mdelay(120);
    spi_write_cmd(spi_ctx,  0xB1, 8); 
    spi_write_data(spi_ctx, 0x05, 8); 
    spi_write_data(spi_ctx, 0x3A, 8); 
    spi_write_data(spi_ctx, 0x3A, 8); 

    spi_write_cmd(spi_ctx,  0xB2, 8); 
    spi_write_data(spi_ctx, 0x05, 8); 
    spi_write_data(spi_ctx, 0x3A, 8); 
    spi_write_data(spi_ctx, 0x3A, 8); 

    spi_write_cmd(spi_ctx,  0xB3, 8); 
    spi_write_data(spi_ctx, 0x05, 8); 
    spi_write_data(spi_ctx, 0x3A, 8); 
    spi_write_data(spi_ctx, 0x3A, 8); 
    spi_write_data(spi_ctx, 0x05, 8); 
    spi_write_data(spi_ctx, 0x3A, 8); 
    spi_write_data(spi_ctx, 0x3A, 8); 

    spi_write_cmd(spi_ctx,  0xB4, 8); 
    spi_write_data(spi_ctx, 0x03, 8); 

    spi_write_cmd(spi_ctx,  0xC0, 8); 
    spi_write_data(spi_ctx, 0x62, 8); 
    spi_write_data(spi_ctx, 0x02, 8); 
    spi_write_data(spi_ctx, 0x04, 8); 

    spi_write_cmd(spi_ctx,  0xC1, 8); 
    spi_write_data(spi_ctx, 0xC0, 8); 

    spi_write_cmd(spi_ctx,  0xC2, 8); 
    spi_write_data(spi_ctx, 0x0D, 8); 
    spi_write_data(spi_ctx, 0x00, 8); 

    spi_write_cmd(spi_ctx,  0xC3, 8); 
    spi_write_data(spi_ctx, 0x8D, 8); 
    spi_write_data(spi_ctx, 0x6A, 8); 

    spi_write_cmd(spi_ctx,  0xC4, 8); 
    spi_write_data(spi_ctx, 0x8D, 8); 
    spi_write_data(spi_ctx, 0xEE, 8); 

    spi_write_cmd(spi_ctx,  0xC5, 8); 
    spi_write_data(spi_ctx, 0x12, 8); 
    
    spi_write_cmd(spi_ctx,  0x36, 8); 
    spi_write_data(spi_ctx, 0xC8, 8); 
    mdelay(120);
    spi_write_cmd(spi_ctx,  0xE0, 8); 
    spi_write_data(spi_ctx, 0x03, 8); 
    spi_write_data(spi_ctx, 0x1B, 8); 
    spi_write_data(spi_ctx, 0x12, 8); 
    spi_write_data(spi_ctx, 0x11, 8); 
    spi_write_data(spi_ctx, 0x3F, 8); 
    spi_write_data(spi_ctx, 0x3A, 8); 
    spi_write_data(spi_ctx, 0x32, 8); 
    spi_write_data(spi_ctx, 0x34, 8); 
    spi_write_data(spi_ctx, 0x2F, 8); 
    spi_write_data(spi_ctx, 0x2B, 8); 
    spi_write_data(spi_ctx, 0x30, 8); 
    spi_write_data(spi_ctx, 0x3A, 8); 
    spi_write_data(spi_ctx, 0x00, 8); 
    spi_write_data(spi_ctx, 0x01, 8); 
    spi_write_data(spi_ctx, 0x02, 8); 
    spi_write_data(spi_ctx, 0x05, 8); 

    spi_write_cmd(spi_ctx,  0xE1, 8); 
    spi_write_data(spi_ctx, 0x03, 8); 
    spi_write_data(spi_ctx, 0x1B, 8); 
    spi_write_data(spi_ctx, 0x12, 8); 
    spi_write_data(spi_ctx, 0x11, 8); 
    spi_write_data(spi_ctx, 0x32, 8); 
    spi_write_data(spi_ctx, 0x2F, 8); 
    spi_write_data(spi_ctx, 0x2A, 8); 
    spi_write_data(spi_ctx, 0x2F, 8); 
    spi_write_data(spi_ctx, 0x2E, 8); 
    spi_write_data(spi_ctx, 0x2C, 8); 
    spi_write_data(spi_ctx, 0x35, 8); 
    spi_write_data(spi_ctx, 0x3F, 8); 
    spi_write_data(spi_ctx, 0x00, 8); 
    spi_write_data(spi_ctx, 0x00, 8); 
    spi_write_data(spi_ctx, 0x01, 8); 
    spi_write_data(spi_ctx, 0x05, 8); 

    spi_write_cmd(spi_ctx,  0x3A, 8); 
    spi_write_data(spi_ctx, 0x05, 8);  /* Format is RGB565, if for RGB666, 0x05 -> 0x06 */
#if 0
    spi_write_cmd (spi_ctx, 0x35, 8);
	spi_write_data(spi_ctx, 0x00, 8);
	spi_write_cmd (spi_ctx, 0x29, 8);  //display on
	//spi_write_cmd (spi_ctx, 0x2C, 8);
	mdelay(120);
	
	spi_write_cmd(spi_ctx, 0x2A, 8);
		spi_write_data(spi_ctx, 0, 8);
		spi_write_data(spi_ctx, 2, 8);
		spi_write_data(spi_ctx, 0, 8);
		spi_write_data(spi_ctx, 129, 8);
	
		spi_write_cmd(spi_ctx, 0x2B, 8);
		spi_write_data(spi_ctx, 0, 8);
		spi_write_data(spi_ctx, 3, 8);
		spi_write_data(spi_ctx, 0, 8);
		spi_write_data(spi_ctx, 130, 8);
#endif
    spi_write_cmd(spi_ctx,  0x29, 8); 
	//mdelay(120);
	LCDLOGE("lcd_panel_init, spi has been inited!\r\n");

	return 0;
}

static unsigned int lcd_panel_readid(struct panel_spec *self)
{
	struct s_spi_ctx* spi_ctx = NULL;
    uint32_t read_id = 0;

	if (NULL == self){
		LCDLOGE("ERROR: panel_readid, Invalid param\r\n");
		return 0;
	}

	if (NULL == self->panel_if) {
		LCDLOGE("ERROR: panel_readid, spi has not been inited!\r\n");
		//return 0;
	}

	spi_ctx = (struct s_spi_ctx*)self->panel_if;
	gpio_set_output(LCD_RST_GPIO); //rst
	//mdelay(20);
	gpio_set_value(LCD_RST_GPIO, 0);
	//mdelay(20);
	gpio_set_value(LCD_RST_GPIO, 1);
	//mdelay(120);

	spi_read_data(spi_ctx, 0xDA, 8, &read_id, 8);
	if (read_id != 0x7c){
		LCDLOGE("ERROR: panel_readid, read 0xDA expect 0x7c, but receive 0x%x!\r\n", read_id);
		//return 0;
	}
	LCDLOGI("INFO: panel_readid, read 0xDA receive 0x%x!\r\n",read_id);

	spi_read_data(spi_ctx, 0xDB, 8, &read_id, 8);
	if(read_id != 0x89){
		LCDLOGE("ERROR: panel_readid, read 0xDB expect 0x89, but receive 0x%x!\r\n",
			read_id);
//		return 0;
	}
	LCDLOGI("INFO: panel_readid, read 0xDB receive 0x%x!\r\n",read_id);

	spi_read_data(spi_ctx, 0xDC, 8, &read_id, 8);
	if(read_id != 0xf0){
		LCDLOGE("ERROR: panel_readid, read 0xDC expect 0xf0, but receive 0x%x!\r\n",
			read_id);
//		return 0;
	}
	LCDLOGI("INFO: panel_readid, read 0xDC receive 0x%x!\r\n",read_id);


	spi_read_data(spi_ctx, 0x04, 8, &read_id, 24);
	if (read_id != 0x7c89f0){
		LCDLOGE("ERROR: panel_readid, read 0x04 expect 0x7c89f0, but receive 0x%x!\r\n", read_id);
		//return 0;
	}

	/*read status*/
	//spi_read_data(spi_ctx, 0x09, 8, &read_id, 32);
	//LCDLOGI("INFO: panel_readid, read 0x09 receive 0x%x!\r\n", read_id);

    return read_id;
}

static int lcd_panel_display_on(struct panel_spec *self)
{
	struct s_spi_ctx* spi_ctx = NULL;
	LCDLOGI("INFO: lcd_panel_display_on +++\r\n");

	if (NULL == self ){
		LCDLOGE("ERROR: lcd_panel_display_on, Invalid param\r\n");
		return -1;
	}

	if (NULL == self->panel_if) {
		LCDLOGE("ERROR: lcd_panel_display_on, mcu has not been inited!\r\n");
		return -1;
	}

	spi_ctx = (struct s_spi_ctx*)self->panel_if;

	spi_write_cmd(spi_ctx, 0x11, 8);
	mdelay(120);
	spi_write_cmd(spi_ctx, 0x29, 8);
	mdelay(20);

    return 0;
}

static int lcd_panel_display_off(struct panel_spec *self)
{
	struct s_spi_ctx* spi_ctx = NULL;
	LCDLOGI("INFO: lcd_panel_display_off +++\r\n");

	if (NULL == self ){
		LCDLOGE("ERROR: lcd_panel_display_off, Invalid param\r\n");
		return -1;
	}

	if (NULL == self->panel_if) {
		LCDLOGE("ERROR: lcd_panel_display_off, mcu has not been inited!\r\n");
		return -1;
	}

	spi_ctx = (struct s_spi_ctx*)self->panel_if;

	spi_write_cmd(spi_ctx, 0x28, 8);
	mdelay(20);
	spi_write_cmd(spi_ctx, 0x10, 8);
	mdelay(120);

    return 0;
}

/* panel st7735s size is 132X132, visable size is 128X128 */
#define UNVISIBLE_X 2
#define UNVISIBLE_Y 3
static int lcd_panel_invalid(struct panel_spec *self, uint32_t start_x,
	uint32_t start_y,  uint32_t end_x, uint32_t end_y)
{
	struct s_spi_ctx* spi_ctx = NULL;

	if (NULL == self){
		LCDLOGE("ERROR: panel_init, Invalid param\r\n");
		return -1;
	}

	if (NULL == self->panel_if){
		LCDLOGE("ERROR: panel_init, mcu has not been inited!\r\n");
		return -1;
	}
	start_x += UNVISIBLE_X;
	end_x += UNVISIBLE_X;
	start_y += UNVISIBLE_Y;
	end_y += UNVISIBLE_Y;

	spi_ctx = (struct s_spi_ctx*)self->panel_if;
	spi_write_cmd(spi_ctx, 0x2A, 8);
	spi_write_data(spi_ctx, ((start_x >> 8) & 0xFF), 8);
	spi_write_data(spi_ctx, (start_x & 0xFF), 8);
	spi_write_data(spi_ctx, ((end_x >> 8) & 0xFF), 8);
	spi_write_data(spi_ctx, (end_x & 0xFF), 8);

	spi_write_cmd(spi_ctx, 0x2B, 8);
	spi_write_data(spi_ctx, ((start_y >> 8) & 0xFF), 8);
	spi_write_data(spi_ctx, (start_y & 0xFF), 8);
	spi_write_data(spi_ctx, ((end_y >> 8) & 0xFF), 8);
	spi_write_data(spi_ctx, (end_y & 0xFF), 8);

	spi_write_cmd(spi_ctx, 0x2C, 8);

	return 0;
}

static struct panel_operations lcd_st7735s_spi_ops = {
	lcd_panel_craneM_spi_init,
	lcd_panel_craneM_spi_update,
	lcd_panel_init,
	lcd_panel_invalid,
	lcd_panel_display_off,
	lcd_panel_display_on,
	lcd_panel_readid,
};

/* Note: this timing is not used in CraneM */
static struct timing_spi lcd_st7735s_spi_timing = {
	13000, /*kHz*/
	5000, /*kHz*/
};

#ifdef LCD_ST7735S_SPI_4WIRE_1LANE_1IF
static struct spi_info lcd_st7735s_spi_4wire_1lane_1if_info = {
	4,
	1, 
	1,
	SPI_FORMAT_RGB565,
	0,
	SPI_EDGE_RISING,
	0,
	SPI_ENDIAN_MSB,
	0,
	&lcd_st7735s_spi_timing,
};

struct panel_spec lcd_st7735s_spi_4wire_1lane_1if_spec = {
	"st7735s_spi_4w_1l_1i",
	0x7c89f0,
	LCD_CAP_NOTE,
	128,
	128,
	LCD_MODE_SPI,,
	LCD_POLARITY_POS,
	&lcd_st7735s_spi_4wire_1lane_1if_info,
	NULL,
	&lcd_st7735s_spi_ops,
};
#endif

#ifdef LCD_ST7735S_SPI_3WIRE_1LANE_1IF
static struct spi_info lcd_st7735s_spi_3wire_1lane_1if_info = {
	3,
	1, 
	1,
	SPI_FORMAT_RGB565,
	0,
	SPI_EDGE_RISING,
	0,
	SPI_ENDIAN_MSB,
	0,
	&lcd_st7735s_spi_timing,
};

struct panel_spec lcd_st7735s_spi_3wire_1lane_1if_spec = {
	"st7735s_spi_3w_1l_1i",
	0x7c89f0,
	LCD_CAP_NOTE,
	128,
	128,
	LCD_MODE_SPI,
	LCD_POLARITY_POS,
	&lcd_st7735s_spi_3wire_1lane_1if_info,
	NULL,
	&lcd_st7735s_spi_ops,
};
#endif
#endif
#endif
