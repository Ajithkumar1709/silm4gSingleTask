
#define SSP0_DMA_TX_CH		(10)
#define SSP0_DMA_RX_CH		(11)
#define SSP2_DMA_TX_CH		(29)
#define SSP2_DMA_RX_CH 		(30)

int mbtk_get_ssp_dma_tx_channel(void)
{
	#if EXT_FLASH_SPI_PORT == 2
		return SSP2_DMA_TX_CH;
	#else
		return SSP0_DMA_TX_CH;
	#endif
}
int mbtk_get_ssp_dma_rx_channel(void)
{
	#if EXT_FLASH_SPI_PORT == 2
		return SSP2_DMA_RX_CH;
	#else
		return SSP0_DMA_RX_CH;
	#endif
}

int mbtk_get_ext_flash_ssp_port(void)
{
	int port = 0;//default

	#if EXT_FLASH_SPI_PORT == 0
		port = 0;
	#elif EXT_FLASH_SPI_PORT == 1
		port = 1;
	#elif EXT_FLASH_SPI_PORT ==2
	  port = 2;
	#endif

	return port;
}

int mbtk_get_auido_pwm_ssp_port(void)
{
	int port = 0;//default

	#if AUDIO_PWM_SPI_PORT == 0
		port = 0;
	#elif AUDIO_PWM_SPI_PORT == 1
		port = 1;
	#elif AUDIO_PWM_SPI_PORT ==2
	  port = 2;
	#endif

	return port;
}


int mbtk_get_ext_flash_ssp_clk(void)
{
	int clk = 1;//default 26M

	#if EXT_FLASH_SPI_CLK == 0
		clk = 0;//SSP_CLOCK_13M
	#elif EXT_FLASH_SPI_CLK == 1
		clk = 1;//SSP_CLOCK_26M
	#elif EXT_FLASH_SPI_CLK ==2
	  clk = 2;//SSP_CLOCK_52M
	#endif
	
	return clk;
}

extern int mbtk_ssp_sclk_gpio_mode_config(int port,int mfpr_value);
extern int mbtk_ssp_sfrm_gpio_mode_config(int port,int mfpr_value);
extern int mbtk_ssp_rxd_gpio_mode_config(int port,int mfpr_value);
extern int mbtk_ssp_txd_gpio_mode_config(int port,int mfpr_value);

#define MRFP_VALUE(AF)	(0x1800+AF)

void mbtk_config_ssp0_gpio_mode(void)
{
	#if defined(EXT_FLASH_SPI_PORT) && EXT_FLASH_SPI_PORT == 0
	mbtk_ssp_sclk_gpio_mode_config(0,MRFP_VALUE(1));
	//cs use gpio function
	mbtk_ssp_sfrm_gpio_mode_config(0,MRFP_VALUE(0));
	mbtk_ssp_rxd_gpio_mode_config(0,MRFP_VALUE(1));
	mbtk_ssp_txd_gpio_mode_config(0,MRFP_VALUE(1));
	#elif defined(AUDIO_PWM_SPI_PORT) && AUDIO_PWM_SPI_PORT == 0
	mbtk_ssp_sclk_gpio_mode_config(0,MRFP_VALUE(1));
	mbtk_ssp_sfrm_gpio_mode_config(0,MRFP_VALUE(1));
	mbtk_ssp_txd_gpio_mode_config(0,MRFP_VALUE(1));
	mbtk_ssp_rxd_gpio_mode_config(0,MRFP_VALUE(1));
	#endif
}

void mbtk_config_ssp1_gpio_mode(void)
{
	#if defined(EXT_FLASH_SPI_PORT) && EXT_FLASH_SPI_PORT == 1
	mbtk_ssp_sclk_gpio_mode_config(1,MRFP_VALUE(2));
	//cs use gpio function
	mbtk_ssp_sfrm_gpio_mode_config(1,MRFP_VALUE(0));
	mbtk_ssp_rxd_gpio_mode_config(1,MRFP_VALUE(2));
	mbtk_ssp_txd_gpio_mode_config(1,MRFP_VALUE(2));
	#elif defined(AUDIO_PWM_SPI_PORT) && AUDIO_PWM_SPI_PORT == 1
	mbtk_ssp_sclk_gpio_mode_config(1,MRFP_VALUE(2));
	mbtk_ssp_sfrm_gpio_mode_config(1,MRFP_VALUE(2));
	mbtk_ssp_txd_gpio_mode_config(1,MRFP_VALUE(2));
	mbtk_ssp_rxd_gpio_mode_config(1,MRFP_VALUE(2));
	#endif	
}

void mbtk_config_ssp2_gpio_mode(void)
{
	#if defined(EXT_FLASH_SPI_PORT) && EXT_FLASH_SPI_PORT == 2
	mbtk_ssp_sclk_gpio_mode_config(2,MRFP_VALUE(1));
	//cs use gpio function
	mbtk_ssp_sfrm_gpio_mode_config(2,MRFP_VALUE(0));
	mbtk_ssp_rxd_gpio_mode_config(2,MRFP_VALUE(1));
	mbtk_ssp_txd_gpio_mode_config(2,MRFP_VALUE(1));
	#elif defined(AUDIO_PWM_SPI_PORT) && AUDIO_PWM_SPI_PORT == 2
	mbtk_ssp_sclk_gpio_mode_config(2,MRFP_VALUE(1));
	mbtk_ssp_sfrm_gpio_mode_config(2,MRFP_VALUE(1));
	mbtk_ssp_txd_gpio_mode_config(2,MRFP_VALUE(1));
	mbtk_ssp_rxd_gpio_mode_config(2,MRFP_VALUE(1));
	#endif	
}
