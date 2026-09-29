#include "lcd_reg.h"
#include "spi_drv.h"
//#include "Gpio_api.h"
#include "lcd_drv.h"
#ifdef LCD_INTERRUPT_MODE
#include "lcd_common.h"
#include <ui_os_api.h>
#endif

struct s_spi_ctx g_spi_ctx;

#ifdef LCD_INTERRUPT_MODE
#ifdef CRANE_MCU_DONGLE
extern OSAFlagRef	g_lcd_interrupt_flag;
#else
extern u8 g_lcd_interrupt_flag;
#endif
extern int g_lcd_irq_waiter;
#endif

#define HAL_GPIO_21 21
#define HAL_GPIO_27 27
//#define SPI_4LINE_DCX LCD_GPIO_0
//#define SPI_4LINE_DCX 27
#ifdef __BOARD_CUSTOM_V__
#define SPI_4LINE_DCX HAL_GPIO_21
#else
#define SPI_4LINE_DCX 82 //gpio 82
#endif

#define HAL_GPIO_121 121
#define CRANEM_SPI_4LINE_DCX HAL_GPIO_121

static int set_spi_clk(uint32_t src_clk, uint32_t spi_clk)
{
	uint32_t dividor;

	dividor = src_clk/spi_clk;
	if(dividor > 0xFF){
		LCDLOGE("ERROR: src_clk/clk can't large than 0xFF\r\n");
		return -1;
	}
	lcd_write_bits(SPI_CTRL, dividor, MASK8, 24);

	LCDLOGI("Expect spi_clk = %d KHz, Real spi_clk = %d KHz\r\n",
		spi_clk, src_clk/dividor);
	
	return 0;
}

static void set_spi_path(struct s_spi_ctx* spi_ctx, uint32_t path)
{
	if(path == SPI_PATH_IMAGE)
		lcd_set_bits(MISC_CTRL, BIT_0);
	else
		lcd_clear_bits(MISC_CTRL, BIT_0);
	spi_ctx->cur_path = path;
}

#ifdef LCD_INTERRUPT_MODE
static void trigger_spi_interrupt(void)
{
	uint32_t actual_flags = 0;
	int i = 0;
	u8 ret = OS_FAIL;

	g_lcd_irq_waiter = 1;
	lcd_set_bits(SPI_CTRL, BIT_0);
    while(i < 10) {
		ret = UOS_WaitFlag(g_lcd_interrupt_flag, LCD_INTER_FLAG_SPIDONE, OSA_FLAG_OR_CLEAR,
			&actual_flags, COMMAND_TIMEOUT);
        if ((ret == OS_SUCCESS) && (0 != (actual_flags & LCD_INTER_FLAG_SPIDONE))){
            break;
        }else{
			LCDLOGW("Warning: trigger_spi_interrupt:wait to finish (0x%x)(%d)!\r\n", actual_flags, i);
        }
		i++;
    }
	g_lcd_irq_waiter = 0;

	if(i>= 10 & (0 != (actual_flags & LCD_INTER_FLAG_SPIDONE))){
		LCDLOGE("ERROR: trigger_spi_interrupt: got spi done timeout!\r\n");
	}
	lcd_clear_bits(SPI_CTRL, BIT_0);
}
#endif

static void trigger_spi_polling(int ass_mode)
{
	int reg = 0;
	
	lcd_set_bits(SPI_CTRL, BIT_0);
	reg = lcd_read(IRQ_ISR_RAW);
	while (0 == (reg & IRQ_SPI_DONE)){
#if 1		
		if(0 == ass_mode)
			UOS_Sleep(MS_TO_TICKS(5));
		else
			mdelay(10);
#else
		UOS_Sleep(MS_TO_TICKS(5));
#endif
		LCDLOGI("Info: trigger_spi_polling, wait to finish (0x%x)\r\n", reg);
		reg = lcd_read(IRQ_ISR_RAW);
	}
	lcd_write(IRQ_ISR_RAW, ~IRQ_SPI_DONE);
	lcd_clear_bits(SPI_CTRL, BIT_0);
}

static void trigger_spi(int work_mode)
{
#ifdef LCD_INTERRUPT_MODE
	if(LCD_WORK_MODE_INTERRUPT == work_mode)
		trigger_spi_interrupt();
	else if(LCD_WORK_MODE_ASS_POLLING == work_mode)
		trigger_spi_polling(1);
	else
		trigger_spi_polling(0);
#else /*polling mode*/
	if(LCD_WORK_MODE_ASS_POLLING == work_mode)
		trigger_spi_polling(1);
	else
		trigger_spi_polling(0);
#endif
}

struct s_spi_ctx* spi_init(uint32_t sclk, struct spi_info *info, int32_t work_mode)
{
	int ret;
	int dividor;
	struct s_spi_ctx *spi_ctx = &g_spi_ctx;
	int reg = 0;

	LCDLOGI("spi_init +++\r\n");

	if(info == NULL || info->timing == NULL){
		LCDLOGE("ERROR: spi_init, Invalid param!\r\n");
		return NULL;
	}

#ifndef LCD_INTERRUPT_MODE
	if(LCD_WORK_MODE_INTERRUPT == work_mode){
		LCDLOGW("WARNING: spi_init, no interrupt mode supported! change to polling mode!\r\n");
		work_mode = LCD_WORK_MODE_POLLING;
	}
#endif	

	if((info->format != SPI_FORMAT_RGB565) &&
		(info->format != SPI_FORMAT_RGB666) && (info->data_lane_num == 1)){
		LCDLOGE("ERROR: spi_init, Format error!\r\n");
		return NULL;
	}

	dividor = sclk/info->timing->rclk;
	if((dividor > 0xFF) || (dividor < 2)){
		LCDLOGE("ERROR: spi_init, Invalid read timing!\r\n");
		return NULL;
	}

	dividor = sclk/info->timing->wclk;	
	if((dividor > 0xFF) || (dividor < 2)){
		LCDLOGE("ERROR: spi_init, Invalid write timing!\r\n");
		return NULL;
	}
		
	*(volatile UINT32 *)0xD401E0D8 = 0xB842;//GPIO 77, BL
	*(volatile UINT32 *)0xD401E054 = 0xD842;//GPIO 81, SDA
	*(volatile UINT32 *)0xD401E058 = 0xD840;//GPIO 82, DCX
	*(volatile UINT32 *)0xD401E074 = 0xD841;//GPIO 89, CS
	*(volatile UINT32 *)0xD401E078 = 0xD841;//GPIO 90, RST
	*(volatile UINT32 *)0xD401E07C = 0xD842;//GPIO 91, CLK
	*(volatile UINT32 *)0xD401E088 = 0xD841;//GPIO 94, TE
	
	GuilinLite_Ldo_6_set_2_8();
	GuilinLite_Ldo_6_set(1);

#if 0
	memset(spi_ctx, 0, sizeof(struct s_spi_ctx));
#else
	spi_ctx->cur_path = 0;
	spi_ctx->cur_cs = 0;
	spi_ctx->status = 0;
#endif
	spi_ctx->base_addr = LCD_BASE_ADDR;
	spi_ctx->sclk = sclk;
#if 0
	memcpy(&spi_ctx->info, info, sizeof(struct spi_info));
#else
	spi_ctx->info.line_num = info->line_num;
	spi_ctx->info.interface_id = info->interface_id;
	spi_ctx->info.data_lane_num = info->data_lane_num;
	spi_ctx->info.format = info->format;
	spi_ctx->info.device_id = info->device_id;
	spi_ctx->info.sample_edge = info->sample_edge;
	spi_ctx->info.force_cs = info->force_cs;
	spi_ctx->info.endian = info->endian;
	spi_ctx->info.timing = info->timing;
#endif
	spi_ctx->work_mode = work_mode;

	if(info->interface_id == 1)
		reg |= BIT_1;

	if(info->device_id == 1)
		reg |= BIT_2;

	if(info->endian == SPI_ENDIAN_LSB){
		reg |= BIT_5 | BIT_4;
	}

	if(info->sample_edge == SPI_EDGE_FALLING)
		reg |= BIT_7;

	/*enable spi*/
	reg |= BIT_3;
	lcd_write(SPI_CTRL, reg);

#if 0
	/*temp for bringup*/
	lcd_set_bits(PN_CTRL1, BIT_21);
	lcd_write_bits(PN_SEPXLCNT, 7, MASK4, 28);
#endif

	reg = 0;
	if(info->line_num == 3)
		reg |= BIT_3;
	
	if(info->data_lane_num == 2)
		reg |= BIT_2;

	reg |= BIT_1; /*should be set, otherwith, color will error*/

	if(info->format == SPI_FORMAT_RGB666_2_3)
		reg |= BIT_5;
	else if(info->format == SPI_FORMAT_RGB888_2_3)
		reg |= BIT_4;
	lcd_write(MISC_CTRL, reg);

	if(info->line_num == 4){/*enable GPIO for D/CX pin for 4 line mode*/
//		lcd_write_bits(DUMB_CONTROL, SPI_4LINE_DCX, MASK8, 12);
		//gpio_direction_output(SPI_4LINE_DCX);
		//gpio_set_value(SPI_4LINE_DCX, 0);
		//set output
		gpio_set_output(SPI_4LINE_DCX);
		gpio_set_value(SPI_4LINE_DCX,0);
	}

	/*spi need set bit13, otherwith will lost some data*/
	/*spi need set bit6, otherwith color will error*/
	/*spi need open mcu, otherwidth can't send image data*/
	//lcd_set_bits(SMPN_CTRL, BIT_13 | BIT_6 | BIT_0);
	lcd_set_bits(SMPN_CTRL, BIT_13 | BIT_0);

	switch(info->format){
	case SPI_FORMAT_RGB565:
		if(info->data_lane_num == 2)
			lcd_write_bits(SMPN_CTRL, 5, MASK4, 8);
		else
			lcd_write_bits(SMPN_CTRL, 2, MASK4, 8);
		break;
	case SPI_FORMAT_RGB666:
		if(info->data_lane_num == 2)
			lcd_write_bits(SMPN_CTRL, 4, MASK4, 8);
		else
			lcd_write_bits(SMPN_CTRL, 1, MASK4, 8);
		break;
	case SPI_FORMAT_RGB666_2_3:
		lcd_write_bits(SMPN_CTRL, 6, MASK4, 8);
		break;
	case SPI_FORMAT_RGB888:
		lcd_write_bits(SMPN_CTRL, 3, MASK4, 8);
		break;
	case SPI_FORMAT_RGB888_2_3:
		lcd_write_bits(SMPN_CTRL, 0, MASK4, 8);
		break;
	default:
		LCDLOGE("ERROR: spi_init, Invalid format!\r\n");
		return NULL;
	}
	
 	/*set write clk as default*/
	ret = set_spi_clk(sclk, info->timing->wclk);
	if(-1 == ret){
		LCDLOGE("ERROR: spi_init, set spi clk error!\r\n");
		return NULL;
	}

	/*set register path as default*/
	set_spi_path(spi_ctx, SPI_PATH_REGISTER);

#if defined(CONFIG_BOARD_CRANEM_EVB)
	spi_lcd_init();
#endif 
	spi_ctx->status = SPI_STATUS_INIT;
	LCDLOGI("spi_init ----\r\n");
	return spi_ctx;
}

int spi_update(struct s_spi_ctx *spi_ctx, int32_t work_mode)
{

	LCDLOGI("spi_update +++\r\n");

#ifndef LCD_INTERRUPT_MODE
	if(LCD_WORK_MODE_INTERRUPT == work_mode){
		LCDLOGW("WARNING: spi_init, no interrupt mode supported! change to polling mode!\r\n");
		work_mode = LCD_WORK_MODE_POLLING;
	}
#endif	

	spi_ctx->work_mode = work_mode;
	LCDLOGI("spi_update ----\r\n");
	return 0;
}

int spi_set_cs(struct s_spi_ctx *spi_ctx, uint32_t enable)
{
	if(NULL == spi_ctx){
		LCDLOGE("ERROR: spi_set_cs, Invalid param\r\n");
		return -1;
	}

	if(SPI_STATUS_INIT != spi_ctx->status){
		LCDLOGE("ERROR: spi_set_cs, Invalid mcu status\r\n");
		return -1;
	}

	if(spi_ctx->info.force_cs == 0){
		LCDLOGE("ERROR: spi_set_cs, Not force CS mode, can't set CS!\r\n");
		return -1;
	}

	if(enable)
		lcd_set_bits(SPI_CTRL, BIT_6);
	else
		lcd_clear_bits(SPI_CTRL, BIT_6);
	spi_ctx->cur_cs = enable;
	return 0;
}

int spi_write_cmd(struct s_spi_ctx *spi_ctx, uint32_t cmd, uint32_t bits)
{
	uint32_t wcmd, wbits;

	if(NULL == spi_ctx || bits > 32 || 0 == bits){
		LCDLOGE("ERROR: spi_write_cmd, Invalid param\r\n");
		return -1;
	}

	if(SPI_STATUS_INIT != spi_ctx->status){
		LCDLOGE("ERROR: spi_write_cmd, Invalid mcu status\r\n");
		return -1;
	}

	if((spi_ctx->info.force_cs == 1) && (spi_ctx->cur_cs == 0)){
		LCDLOGE("ERROR: spi_write_cmd, Invalid CS status\r\n");
		return -1;
	}

#if defined(CONFIG_BOARD_CRANEM_EVB)
	if (4 == spi_ctx->info.line_num) {
		gpio_set_output(CRANEM_SPI_4LINE_DCX);
		gpio_set_value(CRANEM_SPI_4LINE_DCX, 0);
	}
	ssp_write_cmd_data_to_LCD(0, cmd, bits, spi_ctx->info.line_num);
	mdelay(10);
#else
	if(spi_ctx->cur_path == SPI_PATH_IMAGE)
		set_spi_path(spi_ctx, SPI_PATH_REGISTER);

	if(3 == spi_ctx->info.line_num){/*3 line mode*/
		if(bits == 32){
			LCDLOGE("ERROR: spi_write_cmd, too many write bits for 3 line mode!\r\n");
			return -1;
		}
		wbits = bits + 1;
		wcmd = cmd;/*0 -command, 1-data*/
	} else { /*4 line mode*/
		wbits = bits;
		wcmd = cmd;
	}

	if(4 == spi_ctx->info.line_num){/*4 line mode, set DCX pin first*/
//		lcd_write_bits(DUMB_CONTROL, 0, MASK8, 20);
		//gpio_direction_output(SPI_4LINE_DCX);
		//gpio_set_value(SPI_4LINE_DCX, 0);
		gpio_set_output(SPI_4LINE_DCX);
		gpio_set_value(SPI_4LINE_DCX,0);
	}

	lcd_write(SPI_TXDATA, wcmd);
	lcd_write_bits(SPI_CTRL, wbits - 1, MASK16, 8);
	trigger_spi(spi_ctx->work_mode);
#endif
	return 0;
}

int spi_write_data(struct s_spi_ctx *spi_ctx, uint32_t data, uint32_t bits)
{
	uint32_t wdata, wbits;

	if(NULL == spi_ctx || bits > 32 || 0 == bits){
		LCDLOGE("ERROR: spi_write_data, Invalid param\r\n");
		return -1;
	}

	if(SPI_STATUS_INIT != spi_ctx->status){
		LCDLOGE("ERROR: spi_write_data, Invalid mcu status\r\n");
		return -1;
	}

	if((spi_ctx->info.force_cs == 1) && (spi_ctx->cur_cs == 0)){
		LCDLOGE("ERROR: spi_write_data, Invalid CS status\r\n");
		return -1;
	}
#if defined(CONFIG_BOARD_CRANEM_EVB)
	if (4 == spi_ctx->info.line_num) {
		gpio_set_output(CRANEM_SPI_4LINE_DCX);
		gpio_set_value(CRANEM_SPI_4LINE_DCX, 1);
	}
	ssp_write_cmd_data_to_LCD(1, data, bits, spi_ctx->info.line_num);
	mdelay(10);
#else
	if(spi_ctx->cur_path == SPI_PATH_IMAGE)
		set_spi_path(spi_ctx, SPI_PATH_REGISTER);

	if(3 == spi_ctx->info.line_num){
		if(bits == 32){
			LCDLOGE("ERROR: spi_write_data, too many write bits for 3 line mode!\r\n");
			return -1;
		}
		wbits = bits + 1;
		wdata = (1 << bits) | data;/*0 -command, 1-data*/
	} else { /*4 line mode*/
		wbits = bits;
		wdata = data;
	}

	if(4 == spi_ctx->info.line_num){/*4 line mode, set DCX pin first*/
		//lcd_write_bits(DUMB_CONTROL, SPI_4LINE_DCX, MASK8, 20);
		//gpio_direction_output(SPI_4LINE_DCX);
		//gpio_set_value(SPI_4LINE_DCX, 1);
		gpio_set_output(SPI_4LINE_DCX);
		gpio_set_value(SPI_4LINE_DCX,1);
	}

	lcd_write(SPI_TXDATA, wdata);
	lcd_write_bits(SPI_CTRL, wbits - 1, MASK16, 8);
	trigger_spi(spi_ctx->work_mode);
#endif
	return 0;
}

int spi_read_data(struct s_spi_ctx *spi_ctx, uint32_t cmd, uint32_t cmd_bits,
	uint32_t *data,  uint32_t data_bits)
{
	uint32_t wcmd, wbits, rbits;
	int ret;
	uint32_t value_and = 0;

	value_and = (1 << data_bits) - 1;

	if(NULL == spi_ctx || cmd_bits > 32 || data_bits > 32){
		LCDLOGE("ERROR: spi_read_data, Invalid param\r\n");
		return -1;
	}

	if(SPI_STATUS_INIT != spi_ctx->status){
		LCDLOGE("ERROR: spi_read_data, Invalid mcu status\r\n");
		return -1;
	}

	if((spi_ctx->info.force_cs == 1) && (spi_ctx->cur_cs == 0)){
		LCDLOGE("ERROR: spi_read_data, Invalid CS status\r\n");
		return -1;
	}
#if defined(CONFIG_BOARD_CRANEM_EVB)
	if (4 == spi_ctx->info.line_num) {
		gpio_set_output(CRANEM_SPI_4LINE_DCX);
		gpio_set_value(CRANEM_SPI_4LINE_DCX, 0);
	}
	ssp_write_cmd_data_to_LCD(0, cmd, cmd_bits, spi_ctx->info.line_num);

	UOS_Sleep(100);

	ssp_read_data_from_LCD(data, data_bits);
#else

	ret = set_spi_clk(spi_ctx->sclk, spi_ctx->info.timing->rclk);
	if(-1 == ret){
		LCDLOGE("ERROR: spi_read_data, set spi clk error!\r\n");
		return -1;
	}

	if(spi_ctx->cur_path == SPI_PATH_IMAGE)
		set_spi_path(spi_ctx, SPI_PATH_REGISTER);

	if(data_bits > 8)
		rbits = data_bits;
	else
		rbits = data_bits -1;
		

	if(3 == spi_ctx->info.line_num){
		if(cmd == 32){
			LCDLOGE("ERROR: spi_read_data, too many write bits for 3 line mode!\r\n");
			return -1;
		}
		wbits = cmd_bits;
		wcmd = cmd;/*0 -command, 1-data*/
	} else { /*4 line mode*/
		wbits = cmd_bits - 1;
		wcmd = cmd;
	}

	if(4 == spi_ctx->info.line_num){/*4 line mode, set DCX pin first*/
		//lcd_write_bits(DUMB_CONTROL, 0, MASK8, 20);
		//gpio_direction_output(SPI_4LINE_DCX);
		//gpio_set_value(SPI_4LINE_DCX, 0);
		gpio_set_output(SPI_4LINE_DCX);
		gpio_set_value(SPI_4LINE_DCX,0);
	}

	lcd_write(SPI_TXDATA, wcmd);
	lcd_write_bits(SPI_CTRL, wbits, MASK8, 8);
	lcd_write_bits(SPI_CTRL, rbits, MASK8, 16);
	trigger_spi(spi_ctx->work_mode);

	*data = lcd_read(SPI_RXDATA);
	*data &= value_and;

 	/*set write clk as default*/
	ret = set_spi_clk(spi_ctx->sclk, spi_ctx->info.timing->wclk);
	if(-1 == ret){
		LCDLOGE("ERROR: spi_read_data, set spi clk error!\r\n");
		return -1;
	}
#endif
	return 0;
}

int spi_before_refresh(struct s_spi_ctx *spi_ctx)
{
	if(NULL == spi_ctx){
		LCDLOGE("ERROR: spi_before_refresh, Invalid param\r\n");
		return -1;
	}
	
	if(SPI_STATUS_INIT != spi_ctx->status){
		LCDLOGE("ERROR: spi_before_refresh, Invalid spi status\r\n");
		return -1;
	}

	if(spi_ctx->cur_path != SPI_PATH_IMAGE)
		set_spi_path(spi_ctx, SPI_PATH_IMAGE);

	if(2 == spi_ctx->info.data_lane_num){
		/*2 data lane*/
		switch(spi_ctx->info.format){
		case SPI_FORMAT_RGB565:
			lcd_write_bits(SPI_CTRL, 15, MASK8, 8);
			break;
		case SPI_FORMAT_RGB666:
			lcd_write_bits(SPI_CTRL, 17, MASK8, 8);
			break;
		case SPI_FORMAT_RGB666_2_3:
			lcd_write_bits(SPI_CTRL, 11, MASK8, 8);
			break;
		case SPI_FORMAT_RGB888:
			lcd_write_bits(SPI_CTRL, 23, MASK8, 8);
			break;
		case SPI_FORMAT_RGB888_2_3:
			lcd_write_bits(SPI_CTRL, 15, MASK8, 8);
			break;
		}
	} else{
		/*1 data lane*/
		lcd_write_bits(SPI_CTRL, 7, MASK8, 8);
	}

	if(4 == spi_ctx->info.line_num){/*4 line mode, set DCX pin first*/
		//lcd_write_bits(DUMB_CONTROL, SPI_4LINE_DCX, MASK8, 20);
		//gpio_direction_output(SPI_4LINE_DCX);
		//gpio_set_value(SPI_4LINE_DCX, 1);
		gpio_set_output(SPI_4LINE_DCX);
		gpio_set_value(SPI_4LINE_DCX,1);
	}

	return 0;

}

int spi_after_refresh(struct s_spi_ctx *spi_ctx)
{
	if(NULL == spi_ctx){
		LCDLOGE("ERROR: spi_after_refresh, Invalid param\r\n");
		return -1;
	}

	if(SPI_STATUS_INIT != spi_ctx->status){
		LCDLOGE("ERROR: spi_after_refresh, Invalid spi status\r\n");
		return -1;
	}

	if(spi_ctx->cur_path != SPI_PATH_REGISTER)
		set_spi_path(spi_ctx, SPI_PATH_REGISTER);
	return 0;
}

void spi_uninit(struct s_spi_ctx *spi_ctx)
{
	if(NULL == spi_ctx){
		LCDLOGE("ERROR: spi_uninit, Invalid param\r\n");
		return;
	}

	lcd_write(SPI_CTRL, 0);
	lcd_write(MISC_CTRL, 0);
	spi_ctx->status = SPI_STATUS_UNINIT;
}

#if defined(CONFIG_BOARD_CRANEM_EVB)
/* 2021-01-27 added by schan for CraneM */
#define TX_FIFO_INT_EN		(0x1<<3)   //SSP_INT_EN[3]
#define RX_FIFO_INT_EN		(0x1<<2)   //SSP_INT_EN[2]
#define TIMEOUT_EN			(0x1<<1)   //SSP_INT_EN[1]
#define PERI_TRAIL_EN		(0x1<<0)   //SSP_INT_EN[0]
#define SSPSFRM_M			(0x0<<4)   //SSP_TOP_CTRL[4]
#define SSPSCLK_M			(0x0<<3)   //SSP_TOP_CTRL[3]
#define FRF_SPI				(0x0<<1)   //SSP_TOP_CTRL[2:1]
#define SSP_FORMAT			FRF_SPI
#define RX_AUTO_FULL_CTRL_EN (0x1<<17)  //SSP_FIFO_CTRL[17]
#define FIFO_UNPACKING		(0x0<<16)  //SSP_FIFO_CTRL[16]
#define RX_THRES_7			(0x7<<5)   //SSP_FIFO_CTRL[9:5]
#define TX_THRES_7			(0x7<<0)   //SSP_FIFO_CTRL[4:0]
#define SSE_EN				(0x1<<0)   //SSP_TOP_CTRL[0]

#define SSP0_BASE_ADDRESS	0xD401B000
#define APB_SSP0_CLK_RST	0xd401501c
#define DW_9BITS			(0x8 << 5)
#define SSP_DATAR			0x10 
#define SSP_STATUS			0x14

static reg_write(uint32_t reg, uint32_t val)
{
	(*(volatile unsigned long *)(reg)) = val;
}

static void ssp0_reg_write(uint32_t reg, uint32_t val)
{
	reg_write(SSP0_BASE_ADDRESS + reg, val);
}

static uint32_t ssp0_reg_read(uint32_t reg)
{
	return (*(volatile uint32_t *)(SSP0_BASE_ADDRESS + reg));
}

void spi_dump(void)
{
	UINT32 i = 0;

	for ( i = 0; i < 12; i++) {
		LCDLOGE("---SSP0 start dump---\r\n");
		LCDLOGE("SSPI0 offset: 0x%x, value:0x%lx\r\n", i * 4, ssp0_reg_read(i * 4));
	}
	LCDLOGE("SPS0 offset: 0x54, value:0x%lx\r\n", ssp0_reg_read(0x54));
	LCDLOGE("---SSP0 dump end---\r\n");

}

void spi_set_clk_rate(unsigned int clk_dev)
{
	if (clk_dev >= SPI_CLK_LIMIT) {
		LCDLOGE("[Error]: not supported spi clk\r\n");
		return;
	}

	reg_write(APB_SSP0_CLK_RST, 0x3 | (clk_dev << 4));
}

void spi_lcd_init(void)
{
	uint32_t ssp_top_cfg,  ssp_fifo_cfg;
  	uint32_t ssp_int_en_cfg, ssp_to_cfg;

	reg_write(APB_SSP0_CLK_RST, 0x7);
	spi_set_clk_rate(SPI_812_5k);

	ssp_top_cfg	 = 0x4d00;
	ssp_to_cfg = 0x200;
	ssp_fifo_cfg = 0x200e7;
	ssp_int_en_cfg = 0xf;

	ssp0_reg_write(0, ssp_top_cfg);
	ssp0_reg_write(0x4, ssp_fifo_cfg);
	ssp0_reg_write(0x8, ssp_int_en_cfg);
	ssp0_reg_write(0xc, ssp_to_cfg);
	ssp0_reg_write(0, ssp_top_cfg | 0x1);
}

void ssp_write_cmd_data_to_LCD(uint32_t cmd, uint32_t data,uint32_t data_bits,uint16_t line_num)
{
	int reg;

	if ((data_bits < 1) || (data_bits > 31)) {
		LCDLOGE("[Error]: not supported spi data bits\r\n");
		return;
	}

	ssp0_reg_write(0x54, 0x5);

	reg = ssp0_reg_read(0) & ~(0x1f << 5);

	if (line_num == 3) {
		ssp0_reg_write(0, reg | (data_bits << 5));//9 bits
		if (!cmd)
			ssp0_reg_write(SSP_DATAR, data);
		else
			ssp0_reg_write(SSP_DATAR, (1 << data_bits) | data);
	} else if (line_num == 4) {
		ssp0_reg_write(0, reg | ((data_bits - 1) << 5));
		ssp0_reg_write(SSP_DATAR, data);
	} else
		LCDLOGE("[ERROR]: not supported spi line number!\r\n");

	UOS_Sleep(2);
}

void ssp_write_data_to_LCD_Gram(uint16_t* data, uint32_t sum_pixel,
		uint32_t data_bits, uint16_t line_num)
{
	int i, cnt, reg;

	if ((data_bits < 1) || (data_bits > 31)) {
		LCDLOGE("[Error]: not supported spi data bits\r\n");
		return;
	}

	ssp0_reg_write(0x54, 0x5);

	reg = ssp0_reg_read(0) & ~(0x1f << 5);

	if (line_num == 3) {
		ssp0_reg_write(0, reg | (8 << 5));
	} else if (line_num == 4) {
		ssp0_reg_write(0, reg | ((data_bits -1) << 5));
	}

	for (i = 0; i < sum_pixel; i++) {
		cnt = 0;
		/* wait for TX not full */
		while (!(ssp0_reg_read(SSP_STATUS) & (0x1 << 6))) {
			if (cnt ++ > 1000000) {
				LCDLOGE("ERROR: spi write byte error!\r\n");
				return;
			}
		}
		if (line_num == 3) {
			if ((data_bits == 16) || (data_bits == 8)) {
				ssp0_reg_write(SSP_DATAR, (1 << 8) | (*(data + i) >> 8));
				cnt = 0;

				while (!(ssp0_reg_read(SSP_STATUS) & (0x1 << 6))) {
					if (cnt ++ > 1000000) {
						LCDLOGE("ERROR: spi write byte error!\r\n");
						return;
					}
				}
				ssp0_reg_write(SSP_DATAR, (0x1 << 8) | (*(data + i) & 0xff));
			} else
				LCDLOGE("spi write byte not support length!\r\n");
		} else if (line_num == 4) {
			ssp0_reg_write(SSP_DATAR, *(data + i));
		} else {
			LCDLOGE("ERROR: spi line number error!\r\n");
			return;
		}
	}
}

void ssp_read_data_from_LCD(uint32_t *data,  uint32_t data_bits)
{ 
	int reg;
	int status = 0;
 
	reg = ssp0_reg_read(0) & ~(0x1f << 5);

	if ((data_bits < 1) || (data_bits > 31)) {
		LCDLOGE("[Error]: not supported spi data bits\r\n");
		return;
	}

	if (data_bits > 8)
		ssp0_reg_write(0, reg | (data_bits << 5));
	else
		ssp0_reg_write(0, reg | ((data_bits -1) << 5)); //8 bit

	ssp0_reg_write(0x54, 0x7);
	ssp0_reg_write(SSP_DATAR, 0x0);

    while (((status = ssp0_reg_read(SSP_STATUS)) & (0x1 << 14)) == 0);

	*data = ssp0_reg_read(SSP_DATAR);
}

void wait_ssp_write_data_to_LCD_complete(void)
{
	int cnt = 0;

	/* wait for TX empty */
	while ((ssp0_reg_read(SSP_STATUS) & 0xfc0) != 0x40) {
		if (cnt++ > 1000000) {
			LCDLOGE("ERROR: spi write byte error!\r\n");
			return;
		}
	}
}
#endif
