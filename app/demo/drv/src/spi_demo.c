#include "mbtk_comm_api.h"
#include "mbtk_spi.h"
#include "mbtk_gpio.h"
#include "menu_demo_api.h"


//L511-2
#define SSP2_RXD	mbtk_pin_32
#define SSP2_TXD	mbtk_pin_33
#define SSP2_FRM	mbtk_pin_30
#define SSP2_CLK	mbtk_pin_31

int spi_demo_master(void );
int spi_demo_slave(void );


#define SPI_TEST_PORT mbtk_spi_index_2

static demo_menu_info menu_info[] =
{
	{"slave spi","",spi_demo_slave,NULL},
	{"master spi","",spi_demo_master,NULL},
};

demo_menu_info *spi_demo_menu_info(unsigned int *num)
{
	*num = sizeof(menu_info)/sizeof(menu_info[0]);
	return menu_info;
}






int spi_send_recv_test(int port, int control_mode, char start_char)
{
	UINT32 Retval = mbtk_spi_error_none;

	char read_buf[64+1] = {0};
    char write_buf[64+1] = {0};	
    int size = sizeof(read_buf);
	mbtk_pin_config_struct config;
    config.gpio_af_num = mbtk_gpio_config_maf1;
    config.gpio_pull = mbtk_gpio_config_pull_none;
    config.gpio_sleep = mbtk_gpio_config_sleep_none;
    config.gpio_edge = mbtk_gpio_config_edge_none;
  	
    op_uart_printf("mbtk_spi_demo : spi gpio config first\n");
  
    
    if (ol_pin_config(SSP2_RXD, &config) != 0){
  	op_uart_printf("mbtk_spi_demo : SSP0_RXD fail \n");
  	return -1;
    }
  
  	if (ol_pin_config(SSP2_TXD, &config) != 0){
  	op_uart_printf("mbtk_spi_demo : SSP0_TXD fail \n");
  	return -1;
    }
  
  	 if (ol_pin_config(SSP2_FRM, &config) != 0){
  	op_uart_printf("mbtk_spi_demo : SSP0_FRM fail \n");
  	return -1;
    }
  
  	if (ol_pin_config(SSP2_CLK, &config) != 0){
  	op_uart_printf("mbtk_spi_demo : SSP0_CLK fail \n");
  	return -1;
    }
  	op_uart_printf("mbtk_spi_demo: pin config finish\n");

	Retval = ol_spi_init_ex(port, mbtk_spi_mode0, mbtk_spi_clk_3_25M, control_mode);

	if(Retval != 0){
		op_uart_printf("mbtk_spi_demo : mbtk_spi_init fail  %d\n",Retval);
		return -1;
	}


	memset(read_buf, 0, sizeof(read_buf));		
	memset(write_buf, 0, sizeof(write_buf));	

	for(int j=0;j<size;j++){
		write_buf[j] = j+start_char;
	}

    for(int cnt2=0;  cnt2 < 100;cnt2++){
		memset(read_buf,0, size);

		Retval = ol_spi_write_read(port, read_buf, write_buf, size);
		if(Retval != mbtk_spi_error_none){
			op_uart_printf("!!! SPI_DMA_Write_Read failed,ret=%d", Retval);
		}

	    op_uart_printf("cnt2 %d",cnt2);
		op_uart_printf("master in_buf %s",read_buf);
		op_uart_printf("master out_buf %s",write_buf);
		ol_os_task_sleep(100);
   }


	
	op_uart_printf("mbtk_spi_demo : test finish \n");
	return 0;
}




int spi_demo_master(void )
{
   spi_send_recv_test(SPI_TEST_PORT, mbtk_spi_master_mode, '0');
   return 0;
}


int spi_demo_slave(void )
{
   spi_send_recv_test(SPI_TEST_PORT, mbtk_spi_slave_mode, 'A');
   return 0;
}

