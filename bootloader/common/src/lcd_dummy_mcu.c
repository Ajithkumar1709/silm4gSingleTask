#ifdef LCD_DUMMY_MCU#ifdef CRANE_MCU_DONGLE#include "panel_drv.h"#else#include "../../chip/lcd/panel_drv.h"#endif#define LCD_DUMMY_MCU_ID 0xF7F7F7F7

static int lcd_panel_interface_init(struct panel_spec *self, uint32_t sclk, int32_t work_mode)
{
	struct s_mcu_ctx *mcu_ctx = NULL;

	if(NULL == self){
		LCDLOGE("ERROR: panel_interface_init, Invalid param");
		return -1;
	}

	mcu_ctx = mcu_init(sclk, (struct mcu_info*)self->info, work_mode);
	if(NULL == mcu_ctx){
		LCDLOGE("ERROR: panel_interface_init, mcu init fail!");
		return -1;
	}
	self->panel_if = (void*)mcu_ctx;
	return 0;
}
static int lcd_panel_interface_update(struct panel_spec *self, int32_t work_mode){	int ret;	if(NULL == self || NULL == self->panel_if){		LCDLOGE("ERROR: lcd_panel_interface_update, Invalid param\r\n");		return -1;	}		ret = mcu_update((struct s_mcu_ctx*)self->panel_if, work_mode);	return ret;}static struct panel_operations lcd_dummy_mcu_ops = {
	lcd_panel_interface_init,	lcd_panel_interface_update,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
};

static struct timing_mcu lcd_dummy_mcu_timing = {
 	200,
	200,
 	15,
	15,
};

static struct mcu_info lcd_dummy_mcu_info = {
	MCU_BUS_8080,
	MCU_FORMAT_RGB565,
	MCU_ENDIAN_MSB,
	0,
	0,
	0,
	&lcd_dummy_mcu_timing,
};


struct panel_spec lcd_dummy_mcu_spec = {	"dummy_mcu",	LCD_DUMMY_MCU_ID,
	LCD_CAP_FAKE,
	240,
	320,
	LCD_MODE_MCU,
	LCD_POLARITY_POS,
	&lcd_dummy_mcu_info,
	NULL,
	&lcd_dummy_mcu_ops,
};
#endif /*LCD_DUMMY_MCU*/