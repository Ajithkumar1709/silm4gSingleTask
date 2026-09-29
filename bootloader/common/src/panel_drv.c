#include "panel_drv.h"
#include "lcd_drv.h"
#include "lcd_reg.h"
//#include "Gpio_api.h"
#ifdef CRANE_MCU_DONGLE
#include "ui_os_api.h"
#include "panel_list.h"
#else
#include "ui_os_timer.h"
#include "ui_os_task.h"
#include "../../device/lcd/panel_list.h"
#endif

enum{
	PANEL_STATUS_POWEROFF,
	PANEL_STATUS_POWERON,
	PANEL_STATUS_LIMIT
};

int g_panel_status = PANEL_STATUS_POWEROFF;
int g_panel_mode = PANEL_MODE_NORMAL;

static void lcm_reset(void)
{
	lcd_set_bits(SMPN_CTRL, BIT_3);
	panel_delay(20);
	lcd_clear_bits(SMPN_CTRL, BIT_3);
	panel_delay(20);
}

int panel_init(struct panel_spec* panel, uint32_t sclk, int32_t work_mode, int panel_is_ready)
{
#ifdef LCD_LOG_LEVEL_INFO
	unsigned int id = 0;
#endif
	LCDLOGD("INFO: panel_init +++\r\n");

	if(NULL == panel){
		LCDLOGE("ERROR: panel_init, Invalid param\r\n");
		return -1;
	}

	if(LCD_WORK_MODE_ASS_POLLING == work_mode)
		g_panel_mode = PANEL_MODE_ASSERT;
	else
		g_panel_mode = PANEL_MODE_NORMAL;

#if 1
	if(g_panel_status == PANEL_STATUS_POWERON){
		if(NULL != panel->ops->panel_interface_update){
			panel->ops->panel_interface_update(panel, work_mode);
		}
		return 0;
	}
#endif

	/*for fpga only*/
#ifdef LCD_FPGA_TEST
	if(panel->type == LCD_MODE_MCU){
		gpio_direction_output(HAL_GPIO_21);
		gpio_set_value(HAL_GPIO_21, 0);
	} else {
		gpio_direction_output(HAL_GPIO_21);
		gpio_set_value(HAL_GPIO_21, 1);
	}
#endif

	if(NULL != panel->ops->panel_interface_init){
		panel->ops->panel_interface_init(panel, sclk, work_mode);
	}

	if(panel_is_ready == 1){
		LCDLOGI("INFO: do not panel init panel_is_ready = %d \r\n",panel_is_ready);
	}else{
		LCDLOGI("INFO: do panel init panel_is_ready = %d \r\n",panel_is_ready);

		if(LCD_CAP_FAKE != (panel->cap & LCD_CAP_FAKE)){
			lcm_reset();

#ifdef LCD_LOG_LEVEL_INFO
		if(NULL != panel->ops->panel_readid){
			id = panel->ops->panel_readid(panel);
			LCDLOGI("INFO: panel_init: panel id is 0x%x\r\n", id);
		}
#endif

			if(NULL != panel->ops->panel_init){
				panel->ops->panel_init(panel);
			}
		}
	}

	g_panel_status = PANEL_STATUS_POWERON;
	LCDLOGD("INFO: panel_init ---\r\n");
	return 0;
}

static void dump_lcd_panel_spec(struct panel_spec* panel)
{
	LCDLOGI("dump_lcd_panel_spec +++\r\n ");
	LCDLOGI("name %s \r\n",panel->name);
	LCDLOGI("width %d \r\n",panel->width);
	LCDLOGI("height %d \r\n",panel->height);
	LCDLOGI("panel_id 0x%x \r\n",panel->panel_id);
	LCDLOGI("dump_lcd_panel_spec ---\r\n");
}

struct panel_spec* find_panel(uint32_t sclk, int32_t work_mode)
{
	struct panel_spec** panel_list = NULL;
	int panel_num;
	int i, ret;
	int panel_id = 0;

	LCDLOGE("DBG: find_panel (%d)++\r\n", work_mode);
	panel_num = get_panel_list(&panel_list);
	if(panel_num <= 0){
		LCDLOGE("ERROR: find_panel:panel list is NULL\r\n");
		return NULL;
	}

	//step1: find non_fake panel
	for(i = 0; i < panel_num; i++){
		dump_lcd_panel_spec(panel_list[i]);

		if(LCD_CAP_FAKE == (panel_list[i]->cap & LCD_CAP_FAKE)){
			continue;
		}

		if (NULL != panel_list[i]->ops->panel_interface_init){
			ret = panel_list[i]->ops->panel_interface_init(panel_list[i], sclk, work_mode); // for set clk
			if(ret != 0){
				LCDLOGE("ERROR: find_panel: lcd (%d) interface init fail\r\n",i);
				return NULL;
			}
		}

#ifdef LCD_FPGA_TEST
		if(panel_list[i]->type == LCD_MODE_MCU){
			gpio_direction_output(HAL_GPIO_21);
			gpio_set_value(HAL_GPIO_21, 0);
		} else {
			gpio_direction_output(HAL_GPIO_21);
			gpio_set_value(HAL_GPIO_21, 1);
		}
#endif

		panel_id = 0;
		if(NULL != panel_list[i]->ops->panel_readid){
			panel_id = panel_list[i]->ops->panel_readid(panel_list[i]);
		}
		LCDLOGE("INFO: find_panel: %d of %d panel: read_id = 0x%x, panels[i]->panel_id = 0x%x\r\n",i, panel_num, panel_id, panel_list[i]->panel_id);
		if(panel_id == panel_list[i]->panel_id)
		{
			LCDLOGE("INFO: find_panel: The panel is %s, id = 0x%x \r\n",panel_list[i]->name, panel_id);
			return panel_list[i];
		}
	}

	//step2: find fake panel 
	for(i = 0; i < panel_num; i++){
		if(LCD_CAP_FAKE == (panel_list[i]->cap & LCD_CAP_FAKE)){
			LCDLOGE("INFO: find_panel: Select the dummy panel %s, id = 0x%x \r\n",panel_list[i]->name, panel_id);
			return panel_list[i];
		}
		
	}

	LCDLOGE("INFO: find_panel: Not find any panel!\r\n");
	LCDLOGE("DBG: find_panel ---\r\n");
	return NULL;
}


int panel_before_refresh(struct panel_spec* panel, uint32_t start_x,
						uint32_t start_y, uint32_t height, uint32_t width)
{
	int ret = 0;

	LCDLOGD("INFO: panel_before_refresh +++\r\n");

	if(panel->ops->panel_invalid){
		panel->ops->panel_invalid(panel, start_x, start_y, start_x + width -1,
			start_y + height - 1);
	}
#if defined(CONFIG_BOARD_CRANEM_EVB)
	//LCDLOGD("INFO: panel_before_refresh ---\r\n");
#else
	if(panel->type == LCD_MODE_MCU)
		ret = mcu_before_refresh((struct s_mcu_ctx *)panel->panel_if);
	else
		ret = spi_before_refresh((struct s_spi_ctx *)panel->panel_if);
#endif
	LCDLOGD("INFO: panel_before_refresh ---\r\n");
	return ret;
}

int panel_before_wb(struct panel_spec* panel)
{
	int ret;
	LCDLOGD("INFO: panel_before_wb +++\r\n");

	if(panel->type == LCD_MODE_MCU)
		ret = mcu_before_refresh((struct s_mcu_ctx *)panel->panel_if);
	else
		ret = spi_before_refresh((struct s_spi_ctx *)panel->panel_if);
	LCDLOGD("INFO: panel_before_wb ---\r\n");
	return ret;
}

int panel_after_refresh(struct panel_spec* panel)
{
	int ret;
	LCDLOGD("INFO: panel_after_refresh +++\r\n");

	if(panel->type == LCD_MODE_MCU)
		ret = mcu_after_refresh((struct s_mcu_ctx *)panel->panel_if);
	else
		ret = spi_after_refresh((struct s_spi_ctx *)panel->panel_if);
	LCDLOGD("INFO: panel_after_refresh ---\r\n");
	return ret;
}

int panel_sleep(struct panel_spec* panel)
{
	int ret = 0;
	LCDLOGD("INFO: panel_sleep +++\r\n");

	if(panel->ops->panel_suspend){
		ret = panel->ops->panel_suspend(panel);
	}
	return ret;
}

int panel_wakeup(struct panel_spec* panel)
{
	int ret = 0;
	LCDLOGD("INFO: panel_wakeup +++\r\n");

	if(panel->ops->panel_resume){
		ret = panel->ops->panel_resume(panel);
	}
	return ret;
}

int panel_reset(struct panel_spec* panel, uint32_t sclk, int32_t work_mode)
{
	if(NULL != panel->ops->panel_interface_init){
		panel->ops->panel_interface_init(panel, sclk, work_mode);
	}
	return 0;
}

void panel_uninit(struct panel_spec *panel)
{
	if(NULL == panel){
		LCDLOGE("ERROR: panel_init, Invalid param\r\n");
		return;
	}

	lcm_reset();
	g_panel_status = PANEL_STATUS_POWEROFF;
}

void panel_delay(int ms)
{
	if(PANEL_MODE_ASSERT == g_panel_mode)
		mdelay(ms);
	else
		UOS_Sleep(MS_TO_TICKS(ms));
}
