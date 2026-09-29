#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "common.h"
#include "qspi_dma.h"
#include "qspi_flash.h"
#include "qspi_host.h"
#include "qspi_nor.h"
#include "loadtable.h"
#include "bsp.h"
#include "SPI.h"

#define RW_BUF_LEN 2048

struct spi_flash_chip *chip=NULL;
struct spinor_chip_info *spichip=NULL;

//static float rd_speed, wr_speed;

struct qspi_mode qspi_tx_mode[] = {
	{SPI_OPM_TX, "write_x1"},
	{SPI_OPM_TX_QUAD, "write_x4"},
};

struct qspi_mode qspi_rx_mode[] = {
	{SPI_OPM_RX, "read_x1"},
	{SPI_OPM_RX_DUAL, "read_x2"},
	{SPI_OPM_RX_QUAD, "read_x4"},
};

char *qspi_tx_mode_name(int mode)
{
	uint8_t i;

	for (i = 0; i < 2; i++) {
		if (qspi_tx_mode[i].mode == mode)
			return qspi_tx_mode[i].name;
	}

	return NULL;
}

char *qspi_rx_mode_name(int mode)
{
	uint8_t i;

	for (i = 0; i < 3; i++) {
		if (qspi_rx_mode[i].mode == mode)
			return qspi_rx_mode[i].name;
	}

	return NULL;
}

char log_buf[1024*3+1];

void buf_dump(unsigned char* buf, unsigned int len)
{

	unsigned int i;

	if(len>1024)
		len=1024;

	memset(log_buf,0,sizeof(log_buf));

	for(i=0;i<len;i++)
	{
		sprintf(log_buf+3*i,"%02x ",buf[i]);
	}

	uart_printf("\r\n");
	uart_printf(log_buf, i*3);
	uart_printf("\r\n");

}

#if 0
#define ASR_PROPERTY_QSPI_FLASH_ID_NAME		( "qspi_flash_id" )
#define ASR_PROPERTY_QSPI_INIT_FLAG_NAME	( "qspi_init_flag" )

void qspi_flash_id_save(void)
{
	UINT32 asr_property_data, qspi_id;

    qspi_id = (chip->mfr_id<<16)|(chip->dev_id);
    CP_LOGI("qspi_flash_id_save: 0x%x\r\n",qspi_id);
	transmit_data( ASR_PROPERTY_QSPI_INIT_FLAG_NAME ,0x1 );
	asr_property_data = get_transmit_data(ASR_PROPERTY_QSPI_INIT_FLAG_NAME);
	if( asr_property_data != 0xFFFFFFFF )
		CP_LOGI("%s:0x%x\r\n",ASR_PROPERTY_QSPI_INIT_FLAG_NAME,asr_property_data);
	
	transmit_data( ASR_PROPERTY_QSPI_FLASH_ID_NAME ,qspi_id );
	asr_property_data = get_transmit_data(ASR_PROPERTY_QSPI_FLASH_ID_NAME);
	if( asr_property_data != 0xFFFFFFFF )
		CP_LOGI("%s:0x%x\r\n",ASR_PROPERTY_QSPI_FLASH_ID_NAME,asr_property_data);

}
#endif
//comment to porting LCD
//unsigned char qspi_wr_buf[1024*64];
//unsigned char qspi_rd_buf[1024*64];

int bbu_qspi_init(void)
{
	struct qspi_host *host;
	int cs = QSPI_CS_A1;
	int mhz = (PLATFORM_IS_FPGA)?26:104;
	//int mhz = 52; fudan micro
	//int nand = 0;
	int use_xip = 1;
	int rx_mode = SPI_OPM_RX_QUAD;
	int tx_mode = SPI_OPM_TX_QUAD;
	int qpi = 0;
	int XMC_SMPR = 0;



	host = qspi_host_init(cs, mhz, use_xip);

	chip = spi_nor_init(host, cs, rx_mode, tx_mode, qpi);

    if(chip->mfr_id == SPIFLASH_MFR_XM){
        XMC_SMPR = 1;
        if(chip->dev_id == 0x5016){
            XMC_SMPR = 0;//chip->dev_id=0x5016 is XM25LU32C, no need set SMPR
        }
        if((CHIP_IS_CRANELR || CHIP_IS_CRANELG || CHIP_IS_CRANELRH) && (chip->dev_id == 0x5015)){
            XMC_SMPR = 0;//chip->dev_id=0x5015 is XM25QU16C, only on craneLR no need set SMPR
        }
    }
    if ((XMC_SMPR ||(chip->mfr_id == SPIFLASH_MFR_ZBIT))
		&&(mhz == 104))
    {
        qspi_enter_mode(QSPI_DISABLE_MODE);
        *(volatile unsigned int*)(QSPI0_SMPR) = (0x1<<5);
    	qspi_enter_mode(QSPI_NORMAL_MODE);
    }

	if (!chip) {
		CP_LOGE("SPI Nor/NAND flash init failed\r\n");

	}
	CP_LOGD("get flash total size[%llu] to set mpu\r\n",chip->size);
	set_mpu_reg_flash((size_t)chip->size);
	mpu_value_check();
	#if 0
	qspi_flash_id_save();
	#endif
	CP_LOGD("bbu qspi_init success\r\n");
	return 0;
}

int crane_qspi_write_uint(unsigned int addr , unsigned int value){
#if 0	//comment to porting LCD
	int block_addr   = (addr - FLASH_BASE_ADDR)&(~FLASH_BLOCK_MASK);
	int block_offset = (addr - FLASH_BASE_ADDR)&( FLASH_BLOCK_MASK);
    int ret;
    
    /*
    uart_printf("crane_qspi_write_uint block_addr   =[%.08x]\r\n",block_addr);
    uart_printf("crane_qspi_write_uint block_offset =[%.08x]\r\n",block_offset);
    uart_printf("crane_qspi_write_uint value        =[%.08x]\r\n",value);
    */

    //read from flash to buffer
	ret = chip->ops->read(chip, block_addr, FLASH_BLOCK_SIZE, (uint8_t *)qspi_rd_buf);
    //update buffer
    memcpy((uint8_t *)qspi_rd_buf + block_offset, &value, sizeof(value));
    //erase block and write buffer to flash
    //
    //TODO: any possiablity after erase succeed ,flash write failed or power shut?
    //      might seprate loadtable into a RO area and RW area to avoid this happen.
    //
	ret = chip->ops->erase(chip, block_addr, FLASH_BLOCK_SIZE);
	ret = chip->ops->write(chip, block_addr, FLASH_BLOCK_SIZE, (uint8_t *)qspi_rd_buf);

    return ret;
#endif
}

int crane_qspi_read_uint(unsigned int addr){
	int value = 0;
	chip->ops->read(chip, (addr-FLASH_BASE_ADDR), sizeof(value), (uint8_t *)&value);
    //uart_printf("crane_qspi_read_uint [%x]=[%x] !\r\n",addr,value);
    return value;
}

int crane_qspi_erase(unsigned int addr, unsigned int size)
{

	int ret = 0;
	//uart_printf("crane_qspi_erase addr[%x],size[%x] !\r\n",addr,size);
    //QSPI_MutexLock();
	ret = chip->ops->erase(chip, addr, size);
    //QSPI_MutexUnlock();
	return ret;

}

int crane_qspi_read(unsigned int addr, unsigned int buf_addr, unsigned int size)
{
	
	int ret = 0;
	//uart_printf("crane_qspi_read addr[%x],size[%x] !\r\n",addr,size);
    //QSPI_MutexLock();
	ret = chip->ops->read(chip, addr, size, (uint8_t *)buf_addr);
    //QSPI_MutexUnlock();
	return ret;
}

int crane_qspi_write(unsigned int addr, unsigned int buf_addr,unsigned int size)
{


	int ret = 0;
	//uart_printf("crane_qspi_write addr[%x],size[%x] !\r\n",addr,size);
    //QSPI_MutexLock();
	ret = chip->ops->write(chip, addr, size, buf_addr);
    //QSPI_MutexUnlock();

	return ret;
}



#include "SPI.h"
#include "ptable.h"
int crane_qspi_erase_ex(unsigned int addr, unsigned int size, char flash_type)
{

	int ret = 0;
	//uart_printf("crane_qspi_erase addr[%x],size[%x] !\r\n",addr,size);
    //QSPI_MutexLock();
    if(flash_type == 0){
		/*
		if(size<=0x00001000){
				ret = chip->ops->erase_sector(chip, addr);
		}
		else{*/
			ret = chip->ops->erase(chip, addr, size);
		//}
	}
	else 
	 ret = spichip->ops->erase(spichip, addr, size); //modify for norflash
    //QSPI_MutexUnlock();
	return ret;

}

int crane_qspi_read_ex(unsigned int addr, unsigned int buf_addr, unsigned int size, char flash_type)
{
	
	int ret = 0;
	//uart_printf("crane_qspi_read addr[%x],size[%x] !\r\n",addr,size);
    //QSPI_MutexLock();
    if(flash_type == 0)
		ret = chip->ops->read(chip, addr, size, (uint8_t *)buf_addr);
	else
		ret = spichip->ops->read(spichip, addr, size, (uint32_t)buf_addr);//modify for norflash
    //QSPI_MutexUnlock();
	return ret;
}

int crane_qspi_write_ex(unsigned int addr, unsigned int buf_addr,unsigned int size, char flash_type)
{


	int ret = 0;
	//uart_printf("crane_qspi_write addr[%x],size[%x] !\r\n",addr,size);
    //QSPI_MutexLock();
    if(flash_type == 0)
		ret = chip->ops->write(chip, addr, size, buf_addr);
	else
		ret = spichip->ops->write(spichip, addr, size, (uint32_t)buf_addr);//modify for norflash
    //QSPI_MutexUnlock();

	return ret;
}

// 1 ?¡ìaa2?spi
// 0 ??¡ì22?flash
 // 2 ram
int mbtk_spi_check_type(unsigned int *addr)
{
	int buffer_flah_type = 0;

	//CP_LOGI("mbtk_spi_check_type %x\r\n", *addr);

	if(*addr>=CRANE_SPI_BASE_ADDRESS && *addr < 0xA0000000){
		buffer_flah_type = 1;
		*addr -= CRANE_SPI_BASE_ADDRESS;
	}
	else if(*addr>=QSPI_FLASH_BASE && *addr < CRANE_SPI_BASE_ADDRESS){
		buffer_flah_type = 0;
		//*addr -= QSPI_FLASH_BASE;
	}else {
		buffer_flah_type=2 ;
	}

	return buffer_flah_type;
}



int mbtk_qspi_erase(unsigned int addr, unsigned int size)
{
	int buffer_flah_type = mbtk_spi_check_type(&addr);
	if(buffer_flah_type>2|| buffer_flah_type<0){
		uart_printf("mbtk_spi_check_type failed\r\n");
		return -1;
	}
	//uart_printf("mbtk_qspi_erase type %d, %x,%u\r\n", buffer_flah_type,addr , size);

	if(buffer_flah_type == 2){
		memset(addr, 0, size);
		return 0;
	}else{
		if(buffer_flah_type == 0)
			addr -=QSPI_FLASH_BASE;
		return crane_qspi_erase_ex(addr, size, buffer_flah_type);
	}
}


int mbtk_qspi_read(unsigned int addr, unsigned int buf_addr, unsigned int size)
{
	int addr_type = mbtk_spi_check_type(&addr);
	int buff_type = mbtk_spi_check_type(&buf_addr);
	
	if(addr_type>2|| addr_type<0){
		uart_printf("addr_type failed\r\n");
		return -1;
	}

	if(buff_type>2|| buff_type<0){
		uart_printf("buff_type failed\r\n");
		return -1;
	}
	//uart_printf("mbtk_qspi_read type %d,%d, %x,%x,%u\r\n", addr_type, buff_type, addr, buf_addr, size);

	if(buff_type == 2){
		if(addr_type == 2 || addr_type == 0)
			memcpy(buf_addr, addr, size);
		else{
			if(addr_type == 0)
				addr -= QSPI_FLASH_BASE;
			return crane_qspi_read_ex(addr,buf_addr, size, addr_type);
		}
	}else{
		uart_printf("mbtk_qspi_read error!!! not support now\r\n");
		return -1;
	}

	return 0;
}

int mbtk_qspi_write(unsigned int addr, unsigned int buf_addr, unsigned int size)
{
	int addr_type = mbtk_spi_check_type(&addr);
	int buff_type = mbtk_spi_check_type(&buf_addr);
	if(addr_type>2|| addr_type<0){
		uart_printf("addr_type failed\r\n");
		return -1;
	}

	if(buff_type>2|| buff_type<0){
		uart_printf("buff_type failed\r\n");
		return -1;
	}
	
	//uart_printf("mbtk_qspi_write type %d,%d %x,%x,%u\r\n", addr_type, buff_type, addr, buf_addr, size);

	if(buff_type == 2){
		if(addr_type ==2){
			memcpy(addr, buf_addr, size);
		}else{
			if(addr_type == 0)
				addr -=QSPI_FLASH_BASE;
			return crane_qspi_write_ex(addr,buf_addr, size, addr_type);
		}
	}else{
		uart_printf("mbtk_qspi_read error!!! not support now\r\n");
		return -1;
	}

	return 0;
}

#ifdef SPINOR_SUPPORT

struct spinor_chip_info spinor_chip = {0};

static int spinor_reset(struct spinor_chip_info *chip)
{
	int ret = 0;
	int port = SPINOR_getSSPPort();

	SPINOR_SW_Reset(port);
	return ret;
}

static int spinor_read_id(struct spinor_chip_info *chip, uint8_t *buf)
{
	return 0;
}

static int spinor_read_uid(struct spinor_chip_info *chip, uint8_t *buf)
{
	return 0;
}

static int spinor_erase(struct spinor_chip_info *chip, int addr, int len)
{
	int ret = 0;
	int port = SPINOR_getSSPPort();

	ret = SPINOR_Erase(port, addr, len);

	return ret;
}
static int spinor_erase_sector(struct spinor_chip_info *chip, int addr, int len)
{
	int ret = 0;
	int port = SPINOR_getSSPPort();

	ret = SPINOR_EraseBySector(port, addr, len);
	return ret;
}

static int spinor_write(struct spinor_chip_info *chip, unsigned int addr, int size, unsigned int wbuf)
{
	int ret = 0;
	int port = SPINOR_getSSPPort();

	ret = SPINOR_Write(port, addr, (unsigned char*)wbuf, size);
	return ret;
}

static int spinor_read(struct spinor_chip_info *chip, unsigned int addr, int size, unsigned int rbuf)
{
	int ret = 0;
	int port = SPINOR_getSSPPort();

	ret = SPINOR_Read(port, addr, (unsigned char*)rbuf, size);
	return ret;
}

static const struct spinor_ops ext_nor_ops = {
    .reset      = spinor_reset,
    .read_id    = NULL,
    .read       = spinor_read,
    .write      = spinor_write,
    .erase      = spinor_erase,
    .erase_sector   = spinor_erase_sector
};

int external_spi_init(void)
{
	int ret = 0;
	int port = SPINOR_getSSPPort();
	struct spinor_chip_info *chip = &spinor_chip;
	spichip = chip;

	#if SPI_PORT == 0
		port = 0;
	#elif SPI_PORT == 1
		port = 1;
	#elif SPI_PORT ==2
	  port = 2;
	#endif

	SetSSPPort(port);
	uart_printf("external_spi_init %d\r\n", port);

	InitializeSPIDevice(port,SSP_CLOCK_26M); //SSP_CLOCK_52M
	chip->ops = (void *)&ext_nor_ops;
	if(!chip->ops->reset)
		return NULL;
	ret = chip->ops->reset(chip);

	return ret;
}

int crane_ext_spi_erase(unsigned int addr, unsigned int size)
{

	int ret = 0;
	//uart_printf("crane_qspi_erase addr[%x],size[%x] !\r\n",addr,size);
	//ret = spichip->ops->erase(spichip, addr, size);
	ret = spinor_erase(NULL, addr, size);
	return ret;

}
int crane_ext_spi_erase_4k(unsigned int addr, unsigned int size)
{

	int ret = 0;
	//uart_printf("crane_qspi_erase addr[%x],size[%x] !\r\n",addr,size);
	//ret = spichip->ops->erase(spichip, addr, size);
	ret = spinor_erase_sector(NULL, addr, size);
	return ret;

}

int crane_ext_spi_read(unsigned int addr, unsigned int buf_addr, unsigned int size)
{
	
	int ret = 0;
	//uart_printf("crane_qspi_read addr[%x],size[%x] !\r\n",addr,size);
	//ret = spichip->ops->read(spichip, addr, size, (uint8_t *)buf_addr);
	ret = spinor_read(NULL, addr, size, buf_addr);
	return ret;
}

int crane_ext_spi_write(unsigned int addr, unsigned int buf_addr,unsigned int size)
{

	int ret = 0;
	//uart_printf("crane_qspi_write addr[%x],size[%x] !\r\n",addr,size);
	//ret = spichip->ops->write(spichip, addr, size, buf_addr);
	ret = spinor_write(NULL, addr, size, buf_addr);
	return ret;
}
#endif


int bbu_qspi_test(unsigned int base_addr)
{

#if 0  //comment to porting LCD
	unsigned int flash_addr;
	unsigned int mem_addr;
	unsigned int size;
	int ret = 0;
	unsigned int i;

	flash_addr=base_addr;
	mem_addr=(unsigned int)qspi_wr_buf;
	size=64*1024;

	for(i=0;i<sizeof(qspi_wr_buf);i++)
		qspi_wr_buf[i]=i;

    //dump original empty read bufer
	uart_printf("1st dump\r\n");
	buf_dump(qspi_rd_buf,size);
	uart_printf("erase\r\n");

    //erase and write to target flash
	ret = chip->ops->erase(chip, flash_addr, 64*1024);
	uart_printf("write\r\n");
	ret = chip->ops->write(chip, flash_addr, size, (uint8_t *)mem_addr);

    //read out and dump the read buffer for local check
	mem_addr=(unsigned int)qspi_rd_buf;
	memset(qspi_rd_buf,0,sizeof(qspi_rd_buf));
	uart_printf("read\r\n");
	ret = chip->ops->read(chip, flash_addr, size, (uint8_t *)mem_addr);

	uart_printf("2nd dump\r\n");
	buf_dump(qspi_rd_buf,size);

	uart_printf("bbu_qspi_test baseaddr=[%x] done\r\n",base_addr);
	
	for (i=0;i<size;i++){
		if (qspi_rd_buf[i]!=qspi_wr_buf[i])
			uart_printf("qspi wrong @0x%x\r\n", i);
	}
	uart_printf("qspi good!!\r\n");

	return 0;

#endif

}


#if 0
#ifdef SPINOR_SUPPORT
#include "SPI.h"


static int spinor_reset(struct spinor_chip_info *chip)
{
	int ret = 0;
	int port = SPINOR_getSSPPort();

	SPINOR_SW_Reset(port);
	return ret;
}

static int spinor_read_id(struct spinor_chip_info *chip, uint8_t *buf)
{
	return 0;
}

static int spinor_read_uid(struct spinor_chip_info *chip, uint8_t *buf)
{
	return 0;
}

static int spinor_erase(struct spinor_chip_info *chip, int addr, int len)
{
	int ret = 0;
	int port = SPINOR_getSSPPort();

	ret = SPINOR_EraseByBlock(port, addr, len);

	return ret;
}
static int spinor_erase_sector(struct spinor_chip_info *chip, int addr, int len)
{
	int ret = 0;
	int port = SPINOR_getSSPPort();

	ret = SPINOR_EraseBySector(port, addr, len);
	return ret;
}

static int spinor_write(struct spinor_chip_info *chip, unsigned int addr, int size, unsigned int wbuf)
{
	int ret = 0;
	int port = SPINOR_getSSPPort();

	ret = SPINOR_Write(port, addr, (unsigned char*)wbuf, size);
	return ret;
}

static int spinor_read(struct spinor_chip_info *chip, unsigned int addr, int size, unsigned int rbuf)
{
	int ret = 0;
	int port = SPINOR_getSSPPort();

	ret = SPINOR_Read(port, addr, (unsigned char*)rbuf, size);
	return ret;
}


struct spinor_chip_info spinor_chip = {0};
static const struct spinor_ops ext_nor_ops = {
    .reset      = spinor_reset,
    .read_id    = NULL,
    .read       = spinor_read,
    .write      = spinor_write,
    .erase      = spinor_erase,
    .erase_sector   = spinor_erase_sector
};


int external_spi_init(void)
{
	int ret = 0;
	int port = SPINOR_getSSPPort();
	struct spinor_chip_info *chip = &spinor_chip;
	spichip = chip;

	InitializeSPIDevice(port,SSP_CLOCK_52M); //SSP_CLOCK_52M//SSP_CLOCK_26M

	chip->ops = (void *)&ext_nor_ops;
	if(!chip->ops->reset)
		return NULL;
	ret = chip->ops->reset(chip);

	//spinor_reset(NULL);
	return ret;
}

int crane_ext_spi_erase(unsigned int addr, unsigned int size)
{

	int ret = 0;
	//uart_printf("crane_qspi_erase addr[%x],size[%x] !\r\n",addr,size);
	//ret = spichip->ops->erase(spichip, addr, size);
	ret = spinor_erase(NULL, addr, size);
	return ret;

}
int crane_ext_spi_erase_4k(unsigned int addr, unsigned int size)
{

	int ret = 0;
	//uart_printf("crane_qspi_erase addr[%x],size[%x] !\r\n",addr,size);
	//ret = spichip->ops->erase(spichip, addr, size);
	ret = spinor_erase_sector(NULL, addr, size);
	return ret;

}

int crane_ext_spi_read(unsigned int addr, unsigned int buf_addr, unsigned int size)
{
	
	int ret = 0;
	//uart_printf("crane_qspi_read addr[%x],size[%x] !\r\n",addr,size);
	//ret = spichip->ops->read(spichip, addr, size, (uint8_t *)buf_addr);
	ret = spinor_read(NULL, addr, size, buf_addr);
	return ret;
}

int crane_ext_spi_write(unsigned int addr, unsigned int buf_addr,unsigned int size)
{

	int ret = 0;
	//uart_printf("crane_qspi_write addr[%x],size[%x] !\r\n",addr,size);
	//ret = spichip->ops->write(spichip, addr, size, buf_addr);
	ret = spinor_write(NULL, addr, size, buf_addr);
	return ret;
}
#endif



int spi_nor_do_erase(unsigned int addr, unsigned int size, BOOL flashType)	//flashType:0, qspi flash;,1,spi flash
{

	int ret = -1;
    if(flashType == 0)
		ret = chip->ops->erase(chip, addr, size);
	else if (flashType == 2 && spichip)
    	ret = spichip->ops->erase_sector(spichip, addr, size);
	//uart_printf("spi_nor_do_eraseaddr[%08x],size[%08x],flashType[%d],ret[%d]\r\n",addr,size,flashType,ret);
	return ret;

}

int spi_nor_do_erase_4k(unsigned int addr, unsigned int size, BOOL flashType)
{

	int ret = -1;
	if(size!=0x1000 || ((addr & (0x1000-1))!=0)){
		uart_printf("spi_nor_do_erase_4k size=%x,addr=%x\r\n",size,addr);
		ASSERT(0);
	}
    if(flashType==0){
		ret = chip->ops->erase(chip, addr, size);
		//ret = chip->ops->erase_sector(chip, addr);
	}
    else if (flashType == 2 && spichip){
        ret = spichip->ops->erase_sector(spichip, addr, size);
	}

	//uart_printf("spi_nor_do_erase_4k addr[%08x],size[%08x],flashType[%d],ret[%d]\r\n",addr,size,flashType,ret);
	return ret;

}

int spi_nor_do_read(unsigned int addr, unsigned int buf_addr, unsigned int size, BOOL flashType)
{
	int ret = -1;
	if(flashType == 0){
		ret = chip->ops->read(chip, addr, size, (uint8_t *)buf_addr);
	}    
    else if (flashType == 2 && spichip){
		ret = spichip->ops->read(spichip, addr, size, (uint32_t)buf_addr);
	}
	return ret;
}

int spi_nor_do_write(unsigned int addr, unsigned int buf_addr,unsigned int size, BOOL flashType)
{

	int ret = -1;
    if(flashType==0)
		ret = chip->ops->write(chip, addr, size, (uint8_t *)buf_addr);
	else if (flashType == 2 && spichip)
		ret = spichip->ops->write(spichip, addr, size, (uint32_t)buf_addr);

	//uart_printf("spi_nor_do_write addr[%08x],size[%08x],flashType[%d],ret[%d]\r\n",addr,size,flashType,ret);
	return ret;

}
#endif