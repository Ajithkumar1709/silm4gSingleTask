#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "qspi.h"
#include "reg.h"
#include "system.h"
//#include "uart.h"
#include "ptable.h"
#include "loadtable.h"
#include "lzop.h"
#include "sdio.h"
#include "pmic.h"
#include "ff.h"
#include "version_block.h"
#include "bspatch.h"
#include "fip.h"
#include "LzmaDec.h"
#include "FreqChange.h"
#include "fbf_parse.h"
#include "ota.h"
#include "tinyalloc.h"
#include "asr_property.h"
#include "secboot.h"
#include "updater_table.h"

#ifdef BOOT33_FOTA_SUPPORT
#define UpdaterExecAddress 0x7E040000//bind on updater build sct loader config
#define UpdaterVersionIndex 0x00800//bind on updater build sct loader config

UpdaterHeaderInfo updater_version_vb={0};
extern _ptentry *updater_Entry;

extern void   TransferControl(unsigned int);
extern int crane_qspi_read(unsigned int addr, unsigned int buf_addr, unsigned int size);
extern int crane_qspi_write(unsigned int addr, unsigned int buf_addr,unsigned int size);
extern int crane_qspi_erase(unsigned int addr, unsigned int size);
extern int malloc_init(unsigned int ta_base, unsigned int length);
extern unsigned int get_fota_param_end_addr(void);
extern unsigned int get_fota_param_start_addr(void);
extern unsigned int get_ddr_ro_exec_length(void);
extern unsigned int get_ddr_ro_exec_addr(void);


extern unsigned long mini_system_enable;

unsigned int get_ps_ncah_address(void)
{
	char region_compress_mark[8];
	unsigned schedule_count = 0;
	rw_region_item region_info;
	char * rw_cpz_struct_addr=(char*)get_rw_cpz_struct_addr();

	//load region compressed struct
	memcpy(region_compress_mark,
			rw_cpz_struct_addr,
			sizeof(region_compress_mark));

	if(!strncmp(region_compress_mark, RW_REGION_MARK_PRE_STRING ,strlen(RW_REGION_MARK_PRE_STRING)-1)){
		while(1){
			//read NEXT region cpz info struct
			memcpy(&region_info
					,(void*)(rw_cpz_struct_addr + (sizeof(rw_region_item)*schedule_count++))
					,sizeof(rw_region_item));


			//dump region info
			//uart_printf("[CP ] decompress [%8s] from [%.08x] to [%.08x]\r\n",
			//		region_info.RW_REGION_NAME,
			//		region_info.RW_REGION_COMPRESSED_ADDR,
			//		region_info.RW_REGION_EXEC_ADDR
			//		);
			
			if(!strncmp(region_info.RW_REGION_NAME,"PS_NCAH",7)){
				return region_info.RW_REGION_EXEC_ADDR;
			}

		}
	}
	else
	{
		uart_printf("[CP ] Region CPZ struct not detected from loadtable\r\n");
	}
	return 0;

}

static void fota_uudelay(int us)
{
	volatile uint32_t i;
	for(i=0; i<us*100;i++)
		i = i+1;
}

static void fota_mdelay(int ms){
	volatile uint32_t i;
	for(i=0; i<ms;i++)
		fota_uudelay(100);
}

static UINT32 CalcImageChecksum( UINT32* DownloadArea, UINT32 ImageLength,UINT32 checksum)
{
    UINT32 ImageChecksum = checksum;
    UINT32* ptr32 = DownloadArea;
    UINT32* pEnd = ptr32 + (ImageLength / sizeof(UINT32));
    UINT32 BytesSummed = 0;

    while ( ptr32 < pEnd )
    {
        // checksum format version 2 algorithm as defined by flasher
        ImageChecksum ^= (*ptr32);
        ptr32++;
        BytesSummed += sizeof(UINT32);
    }
    return ImageChecksum;
}

#ifdef BOOT33_SECBOOT_SUPPORT
UINT32 Mini_Fota_Verify_Trusted_Data(struct fota_firmwar_flag * pFOTA_T)
{
    struct fota_param *param = NULL;
	struct fota_firmwar_flag *fotaPara_1=NULL;
	struct fota_firmwar_flag *fotaPara_2=NULL;
	struct fota_firmwar_flag *fotaPara=NULL;
	char *param_buf=NULL;
    int sec_res=0;

	UINT32 FotaParamStartAddress = get_fota_param_start_addr();
	UINT32 FotaParamEndAddress   = get_fota_param_end_addr();

    UINT32 Retval = NoError, buf=0,len=0;
    asr_ota_trusted_info *trusted_info=NULL;
	asr_mini_ota_head_info *pMasterHeader = (asr_mini_ota_head_info *)&pFOTA_T->ota_header.mini_ota_head;


	UINT32 total_data_len = pMasterHeader->nonDiffInfo.roLen + pMasterHeader->nonDiffInfo.nonfotaLen + pMasterHeader->nonDiffInfo.app1PartionLen 
	        + pMasterHeader->nonDiffInfo.app2PartionLen + pMasterHeader->nonDiffInfo.app3PartionLen + FLASH_4K_SIZE;
	        
    len = FotaParamEndAddress - FotaParamStartAddress;
    CP_LOGD("[BOOT33][OTA] Mini_Fota_Verify_Trusted_Data,FotaParamStartAddress[0x%08x], len[0x%08x]\r\n",FotaParamStartAddress,len);

    if(len < 3*FLASH_4K_SIZE){
        CP_LOGE("[BOOT33][OTA]Fota Param size error\n\r");
        return SecCertError;
    }

	
	UINT32 LoadAddr = (UINT32)tiny_malloc(total_data_len);
	if(LoadAddr == 0){
		CP_LOGE("[BOOT33][OTA]malloc error\n\r");
		return NULLPointer;
	}
	memset((void *)LoadAddr,0,total_data_len);
	
    CP_LOGD("[BOOT33][OTA] LoadAddr[0x%08x], total_data_len[0x%08x]\r\n",LoadAddr,total_data_len);

    param_buf = (UINT32)tiny_malloc(len);
    if (!param_buf) {
        Retval = SecCertError;
        goto error;
    }

    crane_qspi_read(FotaParamStartAddress - QSPI_FLASH_BASE, param_buf, len);
    param = (struct fota_param *)param_buf;
    fotaPara_1 = (struct fota_firmwar_flag *)(param_buf + FLASH_4K_SIZE);
    fotaPara_2 = (struct fota_firmwar_flag *)(param_buf + 2*FLASH_4K_SIZE);
    
	
	trusted_info = (asr_ota_trusted_info *)tiny_malloc(sizeof(asr_ota_trusted_info));
	
	crane_qspi_read((FotaParamStartAddress - QSPI_FLASH_BASE + 3*FLASH_4K_SIZE),(unsigned int)trusted_info,sizeof(asr_ota_trusted_info));
    if((trusted_info->headSize == 0) 
        || (trusted_info->headSize > (TRUSTED_HEAD_SIZE + ASR_FOTA_FILE_NAME_SIZE + ASR_FOTA_HEAD_SIZE))
        || (trusted_info->tailSize == 0) 
        || (trusted_info->tailSize > TRUSTED_TAIL_SIZE)){
        CP_LOGE("[BOOT33][OTA]trusted_info error\n\r");
        Retval = SecCertError;
        goto error;
    }
    
    buf = LoadAddr;
    
	memcpy((void*)buf,(void*)trusted_info->head,trusted_info->headSize);
	buf += trusted_info->headSize;
    CP_LOGD("[BOOT33][OTA] trusted_info headSize[0x%08x]\r\n",trusted_info->headSize);

	if(pMasterHeader->nonDiffInfo.roLen){
        crane_qspi_read(pMasterHeader->nonDiffInfo.roAddress, buf, pMasterHeader->nonDiffInfo.roLen);
        buf += pMasterHeader->nonDiffInfo.roLen;
        CP_LOGD("[BOOT33][OTA] roLen[0x%08x]\r\n",pMasterHeader->nonDiffInfo.roLen);
	}

	if(pMasterHeader->nonDiffInfo.nonfotaLen){
        crane_qspi_read(pMasterHeader->nonDiffInfo.nonfotaAddress, buf, pMasterHeader->nonDiffInfo.nonfotaLen);
        buf += pMasterHeader->nonDiffInfo.nonfotaLen;
        CP_LOGD("[BOOT33][OTA] nonfotaLen[0x%08x]\r\n",pMasterHeader->nonDiffInfo.nonfotaLen);
	}

	if(pMasterHeader->nonDiffInfo.app1PartionLen){
        crane_qspi_read(pMasterHeader->nonDiffInfo.app1PartionAddress, buf, pMasterHeader->nonDiffInfo.app1PartionLen);
        buf += pMasterHeader->nonDiffInfo.app1PartionLen;
        CP_LOGD("[BOOT33][OTA] app1PartionLen[0x%08x]\r\n",pMasterHeader->nonDiffInfo.app1PartionLen);
	}

	if(pMasterHeader->nonDiffInfo.app2PartionLen){
        crane_qspi_read(pMasterHeader->nonDiffInfo.app2PartionAddress, buf, pMasterHeader->nonDiffInfo.app2PartionLen);
        buf += pMasterHeader->nonDiffInfo.app2PartionLen;
        CP_LOGD("[BOOT33][OTA] app2PartionLen[0x%08x]\r\n",pMasterHeader->nonDiffInfo.app2PartionLen);
	}
	
	if(pMasterHeader->nonDiffInfo.app3PartionLen){
        crane_qspi_read(pMasterHeader->nonDiffInfo.app3PartionAddress, buf, pMasterHeader->nonDiffInfo.app3PartionLen);
        buf += pMasterHeader->nonDiffInfo.app3PartionLen;
        CP_LOGD("[BOOT33][OTA] app3PartionLen[0x%08x]\r\n",pMasterHeader->nonDiffInfo.app3PartionLen);
	}
	
    memcpy((void*)buf,(void*)trusted_info->tail,trusted_info->tailSize);
    CP_LOGD("[BOOT33][OTA] trusted_info tailSize[0x%08x]\r\n",trusted_info->tailSize);
    


    //[sec.0]secboot init from fota file
    //    which is fota file with a secboot ToC struct with only one FIP header
    //    for dfota_file.bin
    //
    //      |----------------|
    //      | FIP Header     |
    //      |----------------|
    //      | DFOTA FILE     |
    //      |----------------|
    //      | Cerificate     |
    secboot_init_by_ram(LoadAddr);

    //[sec.1]do file verify
    Timer0_enable(TRUE);
    sec_res=secboot_item_check(ITEM_UPDATER,0);
    if (sec_res != 0){
        Retval = SecCertError;
        goto error;
    }
    Timer0_enable(FALSE);


#ifdef SECBOOT_ARB_SUPPORT
    sec_res = secboot_nv_ctr_item_check(ITEM_UPDATER,0);
    if( sec_res == -1 ){
        Retval = SecARBError;
        goto error;
    }
#endif

    
    //verify trusted data success, clear fotaFlag and mini_sys_enable
    memset(param->fotaFlag,0,ASR_FOTA_FLAG_LEN_MAX);
    param->mini_sys_enable = 0;
    
    crane_qspi_erase(FotaParamStartAddress - QSPI_FLASH_BASE, FLASH_4K_SIZE);
    crane_qspi_write(FotaParamStartAddress - QSPI_FLASH_BASE,param,sizeof(struct fota_param));
    if(trusted_info) tiny_free(trusted_info);
    if(param_buf) tiny_free(param_buf);
    if(LoadAddr) tiny_free(LoadAddr);
    CP_LOGD("[BOOT33][OTA] Verify Trusted Fota Data Pass\r\n");
    return Retval;
    
error:
    if(fotaPara_1->checksum!=CalcImageChecksum((UINT32*)fotaPara_1,sizeof(struct fota_firmwar_flag)-sizeof(unsigned int),0)
        || fotaPara_1->header != FOTA_HEADER_MAGIC){
        fotaPara = fotaPara_2;
        CP_LOGD("[BOOT33][OTA]param1 corrupted,need recover data using param2");
        crane_qspi_erase(FotaParamStartAddress - QSPI_FLASH_BASE + FLASH_4K_SIZE, FLASH_4K_SIZE); 
        crane_qspi_write(FotaParamStartAddress - QSPI_FLASH_BASE + FLASH_4K_SIZE, (unsigned int)fotaPara, sizeof(struct fota_firmwar_flag));
    
    }else{
        fotaPara = fotaPara_1;
        if(fotaPara_2->checksum!=CalcImageChecksum((UINT32*)fotaPara_2,sizeof(struct fota_firmwar_flag)-sizeof(unsigned int),0)
            || fotaPara_2->header != FOTA_HEADER_MAGIC){
            CP_LOGD("[BOOT33][OTA][OTA]param2 corrupted,need recover data using param1");
            crane_qspi_erase(FotaParamStartAddress - QSPI_FLASH_BASE + 2*FLASH_4K_SIZE, FLASH_4K_SIZE);
            crane_qspi_write(FotaParamStartAddress - QSPI_FLASH_BASE + 2*FLASH_4K_SIZE, (unsigned int)fotaPara, sizeof(struct fota_firmwar_flag));
        }
    }

    //verify trusted data failed,recover mini_dfota_status to MINI_SYS_DFOTA_DONE and enter mini system again
    fotaPara->ota_header.mini_ota_head.mini_dfota_status = MINI_SYS_DFOTA_DONE;
    fotaPara->checksum = CalcImageChecksum((UINT32*)fotaPara,sizeof(struct fota_firmwar_flag)-sizeof(unsigned int),0); 

    crane_qspi_erase(FotaParamStartAddress - QSPI_FLASH_BASE + FLASH_4K_SIZE, FLASH_4K_SIZE); 
    crane_qspi_write(FotaParamStartAddress - QSPI_FLASH_BASE + FLASH_4K_SIZE, (unsigned int)fotaPara, sizeof(struct fota_firmwar_flag));
    crane_qspi_erase(FotaParamStartAddress - QSPI_FLASH_BASE + 2*FLASH_4K_SIZE, FLASH_4K_SIZE);
    crane_qspi_write(FotaParamStartAddress - QSPI_FLASH_BASE + 2*FLASH_4K_SIZE, (unsigned int)fotaPara, sizeof(struct fota_firmwar_flag));
    crane_qspi_erase(FotaParamStartAddress - QSPI_FLASH_BASE + 3*FLASH_4K_SIZE, FLASH_4K_SIZE); 

    if(trusted_info) tiny_free(trusted_info);
    if(param_buf) tiny_free(param_buf);
    if(LoadAddr) tiny_free(LoadAddr);
    CP_LOGD("[BOOT33][OTA] Verify Trusted Fota Data Failed,Retval[%08x]\r\n",Retval);
    return Retval;

}
#endif



#if (!defined(BOOT33_FOTA_NO_UPDATER) || !defined(LTEONLY_SINGLE_SIM))
#if (!defined(CRANEM_SINGLE_SIM))
#ifdef FS_ENABLE
#include "lfs_api.h"

#define MBTK_PATH_FOTA   MBTK_PATH_FOTA_V(MBTK_FOTA_FS_SUPPORT_PATH)":/"

#define MBTK_PATH_FOTA_V(s)  MBTK_PATH_FOTA_STR(s)
#define MBTK_PATH_FOTA_STR(s) #s

#define DFOTA_FILE_NAME MBTK_PATH_FOTA"asr_dfota_pro_file.bin"

int mbtk_fota_pack_file_read(char *buff,unsigned int len,unsigned int offset)
{
	int ret = 0;
	int fd = -1;
	unsigned size = 0;
			
	fd = lfs_io_open(DFOTA_FILE_NAME, LFS_O_RDONLY,0);
	if(fd < 0){
		uart_printf("Open pkg file fail\r\n");
		return NotFoundError;
	}
	lfs_io_lseek(fd, offset, LFS_SEEK_SET);
	ret = lfs_io_read(fd, (void *)buff,len);
	if(ret != len){
		uart_printf("Read pkg file fail\r\n");
		return WriteError;
	}
	lfs_io_close(fd);

	return NoError;
}

#endif
UINT32 OTA_Check_FotaImage(UINT32 buf, UINT32 size, UINT32 flash_Addr)
{
   UINT32 old_checksum = 0,new_checksum = 0;
   char *temp=NULL;
   

   temp =(char *) tiny_malloc(size);
   memset(temp,0,size);
   #ifdef SPINOR_SUPPORT
   if((flash_Addr & SPI_FLASH_BASE) == SPI_FLASH_BASE){
       crane_ext_spi_read(flash_Addr - SPI_FLASH_BASE, (unsigned int)temp, size);
   }
   else
   #endif
   {
        memcpy(temp,flash_Addr+QSPI_FLASH_BASE,size);
   }
   old_checksum = CalcImageChecksum((UINT32*)buf,size,0);
   new_checksum = CalcImageChecksum((UINT32*)temp,size,0);
   
   if(old_checksum != new_checksum){
       uart_printf("[BOOT33][OTA]OTA_Check_FotaImage,failed!!![0x%08X]:[0x%08X]\n\r",old_checksum,new_checksum);  
   }else{
       tiny_free(temp);
       return NoError;
   }
   tiny_free(temp);

   return DFota_WriteFlashCheckFailed;
    
}



static UINT32 OTA_Update_FotaParam(UINT32 buf, UINT32 size, UINT32 flash_Addr)
{
	UINT32 Retval = 0;
	int i=0;
	//char temp[FLASH_4K_SIZE];
	uart_printf("[BOOT33][OTA]OTA_Update_FotaParam, flash_Addr[0x%08X],size[0x%08X]\n\r", flash_Addr,size);	
	
	//temp =(char *) malloc(FLASH_4K_SIZE);
	//memcpy(temp,(char *)buf,size);
start:	
	
	Retval=crane_qspi_erase(flash_Addr, FLASH_4K_SIZE);
	if (Retval != 0)
		goto exit;
	
	
	Retval = crane_qspi_write(flash_Addr, buf, FLASH_4K_SIZE);
	if (Retval != 0)
		goto exit;
exit:

	Retval=OTA_Check_FotaImage(buf,size,flash_Addr);
	if(NoError!=Retval ){
		if(i>10){
			uart_printf("[BOOT33][OTA]OTA_Check_FotaImage filed,Wait...\n\r");
			while(1){
				fota_mdelay(10*1000);
			}
		}
		uart_printf("[BOOT33][OTA]OTA_Check_FotaImage filed,Wait (%d)sec ...\n\r",(i+1)*10);
		fota_mdelay((i+1)*10*1000);
		uart_printf("[BOOT33][OTA]OTA_Check_FotaImage filed,Wait (%d)sec end\n\r",(i+1)*10);
		i++;
		goto start;
	}

	
	uart_printf("[BOOT33][OTA]OTA_Update_FotaParam end\n\r");	
	return Retval;
	
}

static UINT32 OTA_Update_FotaImage(UINT32 buf, UINT32 size, UINT32 flash_Addr)
{
	UINT32 Retval = 1;
	char *temp=NULL;
	UINT32 index=0;
	UINT32 tempsize = size;
	int i=0;
	uart_printf("[BOOT33][OTA]OTA_Update_FotaImage: flash_Addr[0x%08x], size: 0x%08x\n\r", flash_Addr, size);
start:
	
	temp =(char *) tiny_malloc(FLASH_4K_SIZE);

	while(size > FLASH_4K_SIZE){
		memcpy(temp,(char *)(buf+index),FLASH_4K_SIZE);
		
        #ifdef SPINOR_SUPPORT
        if((flash_Addr & SPI_FLASH_BASE) == SPI_FLASH_BASE){
            Retval=crane_ext_spi_erase_4k(flash_Addr  + index - SPI_FLASH_BASE, FLASH_4K_SIZE);
        }
        else
        #endif
		{
		    Retval=crane_qspi_erase(flash_Addr  + index, FLASH_4K_SIZE);
		}
		if (Retval != 0)
			goto error;

		if(index==0){
#if 0
			uart_printf("+++++++++++++++++++++++++++++OTA_Update_FotaImage,delay for poweroff test++++++++++++++\n\r"); 
			fota_delay();
			uart_printf("-----------------------------OTA_Update_FotaImage,delay end----------------------------\n\r"); 
#endif

		}
		if(index%FLASH_1M_SIZE==0){
			uart_printf("\r\n");
		}

		if(index%CRANE_NOR_BLOCKSIZE==0){
			uart_printf("...");
		}

		#ifdef SPINOR_SUPPORT
        if((flash_Addr & SPI_FLASH_BASE) == SPI_FLASH_BASE){
            Retval=crane_ext_spi_write(flash_Addr  + index - SPI_FLASH_BASE, (UINT32)temp, FLASH_4K_SIZE);
        }
        else
        #endif
        {
		    Retval = crane_qspi_write(flash_Addr  + index, (UINT32)temp, FLASH_4K_SIZE);
		}
		if (Retval != 0)
			goto error;
		
		index += FLASH_4K_SIZE;
		size -= FLASH_4K_SIZE;
		
	}


	if(size>0){
		memset(temp,0,FLASH_4K_SIZE);
		memcpy(temp,(char *)(buf+index),size);
		
		#ifdef SPINOR_SUPPORT
        if((flash_Addr & SPI_FLASH_BASE) == SPI_FLASH_BASE){
            Retval=crane_ext_spi_erase_4k(flash_Addr + index - SPI_FLASH_BASE, FLASH_4K_SIZE);
    		if (Retval != 0)
    			goto error;

    		Retval = crane_ext_spi_write(flash_Addr + index - SPI_FLASH_BASE, (UINT32)temp, FLASH_4K_SIZE);
    		if (Retval != 0)
    			goto error;
        }
        else
		#endif
        {
    		Retval=crane_qspi_erase(flash_Addr + index, FLASH_4K_SIZE);
    		if (Retval != 0)
    			goto error;

    		Retval = crane_qspi_write(flash_Addr + index, (UINT32)temp, FLASH_4K_SIZE);
    		if (Retval != 0)
    			goto error;
    	}
		
		index += size;
		size -= size;
	}

	Retval = 0;
error:
	
	if(temp) tiny_free(temp);
	
	Retval=OTA_Check_FotaImage(buf,tempsize,flash_Addr);
	if(NoError!=Retval ){
		if(i>10){
			uart_printf("[BOOT33][OTA]OTA_Check_FotaImage filed,Wait...\n\r");
			while(1){
				fota_mdelay(10*1000);
			}
		}
		uart_printf("[BOOT33][OTA]OTA_Check_FotaImage filed,Wait (%d)sec ...\n\r",(i+1)*10);
		fota_mdelay((i+1)*10*1000);
		uart_printf("[BOOT33][OTA]OTA_Check_FotaImage filed,Wait (%d)sec end\n\r",(i+1)*10);
		i++;
		size = tempsize;
		index = 0;//case79722:bug fix
		goto start;
	}

	
	uart_printf("OTA_Update_FotaImage end\n\r");
	return Retval;
	
}




static UINT32 System_ota_updater(struct fota_firmwar_flag* pFOTA_T,struct fota_param *param,unsigned long FotaParamStartAddress)
{
	UINT32 Retval = GeneralError;
	UINT32 LoadAddr = 0;
	MasterBlockHeader *pMasterHeader = NULL;
	PDeviceHeader_11 pDevHeader_11=NULL;
	PImageStruct_11 pImage_11 = NULL;
	UINT32 temp_p = NULL;
	UINT32 imageChecksum = 0;
	UINT32 imagenum;
	UINT32 ImageAddr;
	UINT32 updaterSize=0,updateImageSize=0;

	_ptentry * fota_pkg=ptable_find_entry("fota_pkg");
	if(fota_pkg==NULL){
		uart_printf("[BOOT33][OTA] not found fota_pkg\r\n");
		return NotFoundError;
	}

    if (pFOTA_T->header != FOTA_HEADER_MAGIC)
    {
        uart_printf("[BOOT33][OTA] FBF Flag mismatch,Header[%.08x]\r\n",pFOTA_T->header);
        return NotFoundError;
    }

    if (pFOTA_T->upgrade_flag != 1)
    {
        uart_printf("[BOOT33][OTA] No need to upgrade[%d]\r\n",pFOTA_T->upgrade_flag);
        return NotFoundError;
    }

	
	if(pFOTA_T->upgrade_method != 1)
	{
        uart_printf("[BOOT33][OTA] Not ota upgrader\r\n");
        return NotOtaUpdaterError;
    }

	
	LoadAddr = (UINT32)tiny_malloc(pFOTA_T->fbf_file_size);
	if(LoadAddr == 0){
		uart_printf("[BOOT33][OTA] tiny_malloc error\n\r");
		return InvalidSizeError;
	}
	//uart_printf("LoadAddr: 0x%08x\n\r", LoadAddr);
	memset((void *)LoadAddr,0,pFOTA_T->fbf_file_size);
#ifdef FS_ENABLE
	mbtk_fota_pack_file_read(LoadAddr,pFOTA_T->fbf_file_size,0);
#else
	//fota_dump_buffer("MasterBlockHeader",(unsigned char *)pFOTA_T->fbf_flash_address+QSPI_FLASH_BASE,0,sizeof(MasterBlockHeader));

	#ifdef SPINOR_SUPPORT
    if((pFOTA_T->fbf_flash_address & SPI_FLASH_BASE) == SPI_FLASH_BASE){
        crane_ext_spi_read((unsigned int)(pFOTA_T->fbf_flash_address - SPI_FLASH_BASE),(unsigned int)LoadAddr,(unsigned int)pFOTA_T->fbf_file_size);
    }
    else
    #endif
	{
		memcpy((void *)LoadAddr,(void*)(pFOTA_T->fbf_flash_address+QSPI_FLASH_BASE),pFOTA_T->fbf_file_size);
	}
#endif 
#ifdef BOOT33_SECBOOT_SUPPORT
    fip_image_t fip_item;

    //[sec.0]secboot init from fota file
    //    which is fota file with a secboot ToC struct with only one FIP header
    //    for fota_file.bin
    //
    //      |----------------|
    //      | FIP Header     |
    //      |----------------|
    //      | DFOTA FILE     |
    //      |----------------|
    //      | Cerificate     |
    secboot_init_by_ram(LoadAddr);

    //[sec.1]do file verify
    Timer0_enable(TRUE);
    secboot_item_check(ITEM_UPDATER,1);
    Timer0_enable(FALSE);

#ifdef SECBOOT_ARB_SUPPORT
    secboot_nv_ctr_item_check(ITEM_UPDATER,1);
#endif

    //[sec.2]get info from fip of fota_file.bin
    secboot_item_get_img_addr_size(ITEM_UPDATER,(fip_image_handle)&fip_item,1);

    //[sec.3]get fota file.bin start address
    LoadAddr = (UINT32)(fip_item.start+fip_item.offset);
#endif

 
	pMasterHeader = (MasterBlockHeader *)LoadAddr;

	if (pMasterHeader->Format_Version != 11){
		Retval = FBF_VersionNotMatch;
		goto error;
	}

	if (pMasterHeader->nOfDevices != 1){
		Retval = FBF_DeviceMoreThanOne;
		goto error;
	}

	temp_p = pMasterHeader->deviceHeaderOffset[0] + LoadAddr;
	pDevHeader_11 = (PDeviceHeader_11)temp_p;
	
	
	for ( imagenum = pDevHeader_11->nOfImages; imagenum > 0; imagenum -- )
	{
		temp_p = (UINT32)&pDevHeader_11->imageStruct_11[imagenum - 1];
		pImage_11 = (PImageStruct_11)temp_p;

		updaterSize = get_updater_copy_size();
		updateImageSize = pImage_11->length;
		uart_printf("[BOOT33][OTA] Flash_Start_Address: 0x%08x length: 0x%08x\n\r", pImage_11->Flash_Start_Address,updateImageSize);
		uart_printf("[BOOT33][OTA] get_updater_start_addr: 0x%08x get_updater_copy_size: 0x%08x\n\r", get_updater_start_addr(),updaterSize);

		if(updateImageSize & (FLASH_4K_SIZE-1)){
			updateImageSize += (FLASH_4K_SIZE - updateImageSize & (FLASH_4K_SIZE-1));
		}
		#ifdef SPINOR_SUPPORT
		if((pImage_11->Flash_Start_Address & SPI_FLASH_BASE) == SPI_FLASH_BASE){
		    if(get_updater_start_addr()!=(pImage_11->Flash_Start_Address) || updaterSize < updateImageSize)
		    {
		        Retval = NotOtaUpdaterError;
		        goto error;
            
		    }
		}
		else
		#endif
        {
            if(get_updater_start_addr()!=(pImage_11->Flash_Start_Address+QSPI_FLASH_BASE) || updaterSize < updateImageSize)
            {
                Retval = NotOtaUpdaterError;
                goto error;
            
            }
        }
		uart_printf("[BOOT33][OTA] boot ota updater, nOfImages: %d\n\r",pDevHeader_11->nOfImages);

 
		ImageAddr = LoadAddr+((pImage_11->First_Sector+7)<<ALIGN_1K_SIZE);
		
		// add checksum for images in FBF file
		imageChecksum = CalcImageChecksum((UINT32*)ImageAddr, pImage_11->length,0);
		if (imageChecksum != pImage_11->ChecksumFormatVersion2){
			Retval = CRCFailedError;
			uart_printf("[BOOT33][OTA]fbf file CORRUPT,checksum failed\n\r");
			goto error;
		}
		
		if(pImage_11->ChecksumFormatVersion2==0){
			continue;
		}

		
		uart_printf("[BOOT33][OTA] Flash_Start_Address: 0x%08X, EraseLen: 0x%08X, length=0x%08X\n\r", 
			pImage_11->Flash_Start_Address,pImage_11->Flash_erase_size,pImage_11->length);
		Retval=OTA_Update_FotaImage( ImageAddr, pImage_11->length, pImage_11->Flash_Start_Address);
		if (Retval != NoError )
			goto error;

		
	}

	tiny_free((void*)LoadAddr);
	LoadAddr=0;
	
	memset(param->fotaFlag,0,ASR_FOTA_FLAG_LEN_MAX);
	param->mini_sys_enable = 0;
	OTA_Update_FotaParam((UINT32)param, sizeof(struct fota_param),get_fota_param_start_addr()-QSPI_FLASH_BASE);
	
	
	uart_printf("[BOOT33][OTA] Clear upgrade flag OK\r\n"); 	
	pFOTA_T->header = 0;
	pFOTA_T->upgrade_flag = 0;
	pFOTA_T->upgrade_method = 0;
	pFOTA_T->checksum = 0;
	Retval = OTA_Update_FotaParam((UINT32)pFOTA_T, sizeof(struct fota_firmwar_flag),FotaParamStartAddress);
	if (Retval != NoError)
		return Retval;
	
	Retval = OTA_Update_FotaParam((UINT32)pFOTA_T, sizeof(struct fota_firmwar_flag),FotaParamStartAddress + FLASH_4K_SIZE);
	if (Retval != NoError)
		return Retval;
	uart_printf("[BOOT33][OTA] Clear fota param OK\r\n");
	


	return NoError;


error:
	//free buffers
	uart_printf("[BOOT33][OTA]ota updater,Retval=%x\n\r", Retval);
	if(LoadAddr) tiny_free((void*)LoadAddr);

	return Retval;

}
#endif
#endif



void get_updater_vb(void)
{
#ifdef BOOT33_SECBOOT_SUPPORT
    return;
#else
    #ifdef SPINOR_SUPPORT
    if((get_updater_start_addr() & SPI_FLASH_BASE) == SPI_FLASH_BASE){
        crane_ext_spi_read((unsigned int)(get_updater_start_addr() - SPI_FLASH_BASE),(unsigned int)&updater_version_vb,(unsigned int)sizeof(UpdaterHeaderInfo));
    }
    else
    #endif
    {
        memcpy(&updater_version_vb,get_updater_start_addr(),sizeof(UpdaterHeaderInfo));
    }
    asr_property_set("updater.version",updater_version_vb.version_union.version_info_block.string);
    asr_property_set("updater.solution",updater_version_vb.fota_solution_union.fota_solution_block.string);
    CP_LOGD("[BOOT33][OTA] get updater version %s !\r\n",updater_version_vb.version_union.version_info_block.string);
    CP_LOGD("[BOOT33][OTA] get updater solution %s !\r\n",updater_version_vb.fota_solution_union.fota_solution_block.string);
#endif
}

#if defined(BOOT33_FOTA_NO_UPDATER) && !defined(PRO_DFOTA_SUUPORT_NO_UPDATER)
UINT32 UncompressUpdater(struct fota_firmwar_flag *fotaPara,unsigned char * address)
{
	UINT32 res = NoError;
	int outLen = -1;
	unsigned int inLen = fotaPara->ota_header.mini_ota_head.nonDiffInfo.updater_size;
	unsigned int offset = fotaPara->ota_header.mini_ota_head.nonDiffInfo.updater_offset;
	
	unsigned char * inAddr = NULL,*dfota_buf=NULL;
	

	if(inLen==0){
		return NotFoundError;
	}
	CP_LOGD("[BOOT33][OTA] updater_addr [0x%.08x]\r\n", fotaPara->ota_header.mini_ota_head.nonDiffInfo.updater_addr);
	if(fotaPara->ota_header.mini_ota_head.nonDiffInfo.updater_addr){
		inAddr = fotaPara->ota_header.mini_ota_head.nonDiffInfo.updater_addr;
		inAddr += QSPI_FLASH_BASE;
	}else{
		CP_LOGD("[BOOT33][OTA] first_flash_addr[0x%.08x], first_file_size[0x%.08x]\r\n", fotaPara->ota_header.mini_ota_head.first_flash_addr,fotaPara->ota_header.mini_ota_head.first_file_size);
		CP_LOGD("[BOOT33][OTA] second_flash_address[0x%.08x], second_file_size[0x%.08x]\r\n", fotaPara->ota_header.mini_ota_head.second_flash_address,fotaPara->ota_header.mini_ota_head.second_file_size);
		dfota_buf = (unsigned char *)tiny_malloc(fotaPara->ota_header.mini_ota_head.first_file_size + fotaPara->ota_header.mini_ota_head.second_file_size);

		crane_qspi_read(fotaPara->ota_header.mini_ota_head.first_flash_addr - QSPI_FLASH_BASE, dfota_buf, fotaPara->ota_header.mini_ota_head.first_file_size);

		if(fotaPara->ota_header.mini_ota_head.second_flash_address && fotaPara->ota_header.mini_ota_head.second_file_size){
			crane_qspi_read(fotaPara->ota_header.mini_ota_head.second_flash_address - QSPI_FLASH_BASE, dfota_buf + fotaPara->ota_header.mini_ota_head.first_file_size, fotaPara->ota_header.mini_ota_head.second_file_size);
		}
		inAddr = dfota_buf + offset; 
	}
	
	
	if(!LzmaUncompress((unsigned char *)address,(size_t *)&outLen, (const unsigned char *)inAddr, (size_t *)&inLen))
	{
		CP_LOGD("[BOOT33][OTA] released updater size [0x%.08x] inLen[0x%.08x]\r\n", outLen,inLen);

#ifdef BOOT33_SECBOOT_SUPPORT
        fip_image_t fip_item;

        //[sec.0]secboot init from updater partition
        //    which is updater.bin with a secboot ToC struct with only one FIP header
        //    for updater.bin
        //
        //      |----------------|
        //      | FIP Header     |
        //      |----------------|
        //      | Updater.bin    |
        //      |----------------|
        //      | Cerificate     |
        secboot_init_by_ram(address);

        //[sec.1]do updater verify
        Timer0_enable(TRUE);
        secboot_item_check(ITEM_UPDATER,1);
        Timer0_enable(FALSE);

#ifdef SECBOOT_ARB_SUPPORT
        secboot_nv_ctr_item_check(ITEM_UPDATER,1);
#endif
        //[sec.2]get info from fip of updater.bin
        secboot_item_get_img_addr_size(ITEM_UPDATER,(fip_image_handle)&fip_item,1);

        //[sec.3]load updater.bin to UpdaterExecAddress
        memmove((void *)address,(void *)(fip_item.start+fip_item.offset),fip_item.size);
        outLen = fip_item.size;
#endif	
		memcpy(&updater_version_vb,address,sizeof(UpdaterHeaderInfo));
		if(updater_version_vb.loadtable_union.loadtable_block.magic != UPDATER_VALID_MAGIC){
			res = UpdaterMagicError;
		}else{
			res=check_updater_ram(address,outLen);
			if(res){
				res = CheckUpdaterError;
			}

		}

	}else{
		res = UnpressedUpdaterError;
    }
    if(dfota_buf) tiny_free(dfota_buf);
	return res;
}
#endif

#if  defined(BOOT33_FOTA_NO_UPDATER) && defined(PRO_DFOTA_SUPPORT_NO_UPDATER)
UINT32 UncompressUpdater_pro(struct fota_firmwar_flag *fotaPara,unsigned char * address)
{
	UINT32 res = NoError;
	int outLen = -1;
	unsigned int inLen = fotaPara->ota_header.ota_adiffhead.updater_size;
	unsigned int offset = fotaPara->ota_header.ota_adiffhead.updater_offset;
	
	unsigned char * inAddr = NULL,*dfota_buf=NULL;
	

	if(inLen==0){
		return NotFoundError;
	}
	CP_LOGD("[OTA] updater_addr [0x%.08x]\r\n", fotaPara->ota_header.ota_adiffhead.updater_offset);
	CP_LOGD("[OTA] fbf_flash_address[0x%.08x], fbf_file_size[0x%.08x]\r\n", fotaPara->fbf_flash_address,fotaPara->fbf_file_size);
	dfota_buf = (unsigned char *)tiny_malloc(fotaPara->fbf_file_size);

	#ifdef SPINOR_SUPPORT
    if((fotaPara->fbf_flash_address & SPI_FLASH_BASE) == SPI_FLASH_BASE){
		crane_ext_spi_read(fotaPara->fbf_flash_address - SPI_FLASH_BASE, dfota_buf, fotaPara->fbf_file_size);
    }
    else
	#endif
    {
		crane_qspi_read(fotaPara->fbf_flash_address, dfota_buf, fotaPara->fbf_file_size);
	}
	inAddr = dfota_buf + offset; 

	if(!LzmaUncompress((unsigned char *)address,(size_t *)&outLen, (const unsigned char *)inAddr, (size_t *)&inLen))
	{
		CP_LOGD("[OTA] released updater size [0x%.08x] inLen[0x%.08x]\r\n", outLen,inLen);
		memcpy(&updater_version_vb,address,sizeof(UpdaterHeaderInfo));
		if(updater_version_vb.loadtable_union.loadtable_block.magic != UPDATER_VALID_MAGIC){
			res = UpdaterMagicError;
		}else{
			res=check_updater_ram(address,outLen);
			if(res){
				res = CheckUpdaterError;
			}

		}

	}else{
		res = UnpressedUpdaterError;
    }
    tiny_free(dfota_buf);
	return res;
}
#endif
#ifdef BOOT33_SECBOOT_SUPPORT
UINT32 get_psram_size(void)
{
    UINT32 poolLen = 0x00800000;
	UINT8 psramtype = readPsramFuse();
	switch (psramtype) {
    	case AP_16M:
    	case WB_16M:
    	case AP_8M8M:
    	case WB_8M8M:
    	case WB_250MHZ_8M8M:
    	case WB_XCCELA_8M8M:
    	case AP_250MHZ_16M:
    	case WB_250MHZ_16M:
    	case AP_250MHZ_8M8M:
    	case AP_UHS_8M8M:
    		poolLen = 0x01000000;
    		break;
    	case AP_8M:
    	case WB_8M:
    	case WB_250MHZ_8M:
    	case WB_XCCELA_8M:
    	case AP_250MHZ_8M:
    		poolLen = 0x00800000;
    		break;
    	case WB_4M:
    	case AP_4M:
    	case WB_XCCELA_4M:
    	case UNIIC_4M:
    	    poolLen = 0x00400000; 
    	    break;
    	default:
    		break;
    }
    return poolLen;
}
#endif


void ota_entry(void) {
	volatile unsigned long FotaParamStartAddress;
	volatile unsigned long FotaParamEndAddress;
	struct fota_param param;
	unsigned long entry_mini_system_only=0;
	struct fota_firmwar_flag *fotaPara_1=NULL;
	struct fota_firmwar_flag *fotaPara_2=NULL;
	struct fota_firmwar_flag *fotaPara=NULL;
	UINT32 Retval = NoError;
	UpdaterHeaderInfo updater_version;

	//detect whether fota partition supported
	FotaParamStartAddress = get_fota_param_start_addr();
	FotaParamEndAddress   = get_fota_param_end_addr();
	if(FotaParamStartAddress == FotaParamEndAddress){
		CP_LOGE("[BOOT33][OTA] FotaParamStartAddress == FotaParamEndAddress , FOTA not supported\r\n");
		return;
	}

#if 0
	if(updater_Entry){
		get_updater_vb();
		asr_property_dump();
	}
#endif

	//check OTA flag or
	memcpy(&param,(void *)FotaParamStartAddress,sizeof(struct fota_param));

	//if(!strncmp(fota_flag,"ASROTA",6) || Keypad_OTA_Flag_Check_B()){
	if(!strncmp((char *)param.fotaFlag,"ASROTA",6) ){
		UINT32 stack=0x7e200000;
		#ifdef BOOT33_SECBOOT_SUPPORT
		UINT32 poolLen = get_psram_size() - 0x00200000;
		#else
		UINT32 poolLen = 0x00600000;
		#endif
		//The bspatch/lzma lib needs malloc/free APIs
		malloc_init(stack, poolLen);

#ifdef FS_ENABLE
		uart_printf("FOTA fs enbale,start init \r\n");
		lfs_sys_init();
		uart_printf("FOTA fs enbale,end init \r\n");
#endif

#if (!defined(BOOT33_FOTA_NO_UPDATER) || !defined(LTEONLY_SINGLE_SIM))
#if (!defined(CRANEM_SINGLE_SIM))
		if(updater_Entry){
			#ifdef SPINOR_SUPPORT
            if((get_updater_start_addr() & SPI_FLASH_BASE) == SPI_FLASH_BASE){
                crane_ext_spi_read((unsigned int)(get_updater_start_addr() - SPI_FLASH_BASE),(unsigned int)&updater_version,(unsigned int)sizeof(UpdaterHeaderInfo));
            }
            else
			#endif      
            {
			    memcpy(&updater_version,get_updater_start_addr(),sizeof(UpdaterHeaderInfo));
			}
			
			CP_LOGD("[BOOT33][OTA] get updater version %s !\r\n",updater_version.version_union.version_info_block.string); 
		}
#endif
#endif

		
		fotaPara_1=(struct fota_firmwar_flag*)tiny_malloc(sizeof(struct fota_firmwar_flag));
		fotaPara_2=(struct fota_firmwar_flag*)tiny_malloc(sizeof(struct fota_firmwar_flag));
		
		memcpy(fotaPara_1,(void *)(FotaParamStartAddress+FLASH_4K_SIZE),sizeof(struct fota_firmwar_flag));
		memcpy(fotaPara_2,(void *)(FotaParamStartAddress+2*FLASH_4K_SIZE),sizeof(struct fota_firmwar_flag));
		
		if(fotaPara_1->checksum!=CalcImageChecksum((UINT32*)fotaPara_1,sizeof(struct fota_firmwar_flag)-sizeof(unsigned int),0)
			|| fotaPara_1->header != FOTA_HEADER_MAGIC){
			if(fotaPara_2->checksum!=CalcImageChecksum((UINT32*)fotaPara_2,sizeof(struct fota_firmwar_flag)-sizeof(unsigned int),0)
				|| fotaPara_2->header != FOTA_HEADER_MAGIC){
				CP_LOGD("[BOOT33][OTA] fotaPara error!!!\r\n");
				goto done;
			}else{
				CP_LOGD("[BOOT33][OTA]using fotaPara_2,not copy temp flash\r\n");
				fotaPara = fotaPara_2;
			}
		
		}else{
			if(fotaPara_2->checksum!=CalcImageChecksum((UINT32*)fotaPara_2,sizeof(struct fota_firmwar_flag)-sizeof(unsigned int),0)
				|| fotaPara_2->header != FOTA_HEADER_MAGIC){
				fotaPara = fotaPara_1;
				CP_LOGD("[BOOT33][OTA]using fotaPara_1,need copy temp flash\r\n");
		
			}else{
				if(fotaPara_1->index > fotaPara_2->index){
					fotaPara = fotaPara_1;
					CP_LOGD("[BOOT33][OTA]using fotaPara_1,need copy temp flash\r\n");
				}else{
					fotaPara = fotaPara_2;
					CP_LOGD("[BOOT33][OTA]using fotaPara_2,not copy temp flash,checksum[%08x]\r\n",fotaPara_2->checksum);
				}
		
			}
		}

#if  defined(BOOT33_FOTA_NO_UPDATER) && defined(PRO_DFOTA_SUPPORT_NO_UPDATER)
		if(!updater_Entry){
			Retval=UncompressUpdater_pro(fotaPara,UpdaterExecAddress);
			CP_LOGD("[OTA]UncompressUpdater[%d] %s !!!\r\n",Retval,Retval?"error":"success");
			if(Retval != NoError){
				CP_LOGE("[OTA] no updater paritition,parse updater failed[%02x]!!!\r\n",Retval);
				tiny_free(fotaPara_1);
				tiny_free(fotaPara_2);
				return;
			}
			goto jump;
			
		} 
#endif
		
		if(param.mini_sys_enable==1){
			mini_system_enable=1;
            #ifdef BOOT33_SECBOOT_SUPPORT
            if(fotaPara->ota_header.mini_ota_head.mini_dfota_status==MINI_SYS_DFOTA_PHASE2_DOWNLOAD_DONE){
                Retval=Mini_Fota_Verify_Trusted_Data(fotaPara);
                if(NoError == Retval){
                    //verify trusted data success, clear mini_system_enable and enter full system
                	tiny_free(fotaPara_1);
				    tiny_free(fotaPara_2);	
                    mini_system_enable=0;
                    return;
                }
                
                entry_mini_system_only = 1;
            }else 
            #endif
            if(fotaPara->ota_header.mini_ota_head.mini_dfota_status==MINI_SYS_DFOTA_START){
				CP_LOGD("[BOOT33][OTA]MINI_SYS_DFOTA_START\r\n");
				entry_mini_system_only = 1;
			}else if(fotaPara->ota_header.mini_ota_head.mini_dfota_status>=MINI_SYS_DFOTA_DONE){
				entry_mini_system_only = 1;
				CP_LOGD("[BOOT33][OTA]MINI_SYS_DFOTA_DONE\r\n");
			}


			if(entry_mini_system_only==1){
				asr_property_set("mini.sys.enable","1");
				tiny_free(fotaPara_1);
				tiny_free(fotaPara_2);	
				uart_printf("[BOOT33][OTA]ENTRY MINI SYSTEM ONLY\r\n");
				return;
			}
			#if defined(BOOT33_FOTA_NO_UPDATER) && !defined(PRO_DFOTA_SUPPORT_NO_UPDATER)
			if(!updater_Entry){
				Retval=UncompressUpdater(fotaPara,UpdaterExecAddress);
				CP_LOGD("[BOOT33][OTA]UncompressUpdater[%d] %s !!!\r\n",Retval,Retval?"error":"success");
				if(Retval != NoError){
					CP_LOGE("[BOOT33][OTA] no updater paritition,parse updater failed[%02x]!!!\r\n",Retval);
					tiny_free(fotaPara_1);
					tiny_free(fotaPara_2);
					return;
				}
				
			}
			#endif
			tiny_free(fotaPara_1);
			tiny_free(fotaPara_2);

		}
		#if (!defined(BOOT33_FOTA_NO_UPDATER) || !defined(LTEONLY_SINGLE_SIM))
		#if (!defined(CRANEM_SINGLE_SIM))
		else
		{ 
			Retval=System_ota_updater(fotaPara,&param,FotaParamStartAddress+FLASH_4K_SIZE-QSPI_FLASH_BASE);
			if(Retval==0){
				CP_LOGD("[BOOT33][OTA]System_ota_updater success!\r\n");
				#ifdef SPINOR_SUPPORT
                if((get_updater_start_addr() & SPI_FLASH_BASE) == SPI_FLASH_BASE){
                    crane_ext_spi_read((unsigned int)(get_updater_start_addr() - SPI_FLASH_BASE),(unsigned int)&updater_version,(unsigned int)sizeof(UpdaterHeaderInfo));
                }
                else
                #endif
                {
				    memcpy(&updater_version,get_updater_start_addr(),sizeof(UpdaterHeaderInfo));
				}
				CP_LOGD("[BOOT33][OTA] get new updater version %s !\r\n",updater_version.version_union.version_info_block.string);
				
				tiny_free(fotaPara_1);
				tiny_free(fotaPara_2);	
				return;
			}
			tiny_free(fotaPara_1);
			tiny_free(fotaPara_2);
		}
		#endif
		#endif

done:
#if (!defined(BOOT33_FOTA_NO_UPDATER) || !defined(LTEONLY_SINGLE_SIM))
#if (!defined(CRANEM_SINGLE_SIM))
#ifdef 	ADD_VIBRATOR_IN_CODE
		//[0] Before jump to updater, disable vibrator
		NingboVibratorDisable();
#endif

		//[1] TODO:detect ADUPS flags
		CP_LOGD("[BOOT33][OTA] ASROTA prefix detected or Keypad Flag detect!\r\n");
		if(!updater_Entry){
			if(Retval != NoError){
				CP_LOGE("[BOOT33][OTA] no updater paritition,parse updater failed[%02x]!!!\r\n",Retval);
				return;
			}
			goto jump;
		}
#ifdef BOOT33_SECBOOT_SUPPORT
    	fip_image_t fip_item;

    	//[sec.0]secboot init from updater partition
    	//    which is updater.bin with a secboot ToC struct with only one FIP header
    	//    for updater.bin
    	//
    	//      |----------------|
    	//      | FIP Header     |
    	//      |----------------|
    	//      | Updater.bin    |
    	//      |----------------|
    	//      | Cerificate     |
    	secboot_init("updater");

    	//[sec.1]do updater verify
    	Timer0_enable(TRUE);
    	secboot_item_check(ITEM_UPDATER,1);
    	Timer0_enable(FALSE);

#ifdef SECBOOT_ARB_SUPPORT
        secboot_nv_ctr_item_check(ITEM_UPDATER,1);
#endif

    	//[sec.2]get info from fip of updater.bin
    	secboot_item_get_img_addr_size(ITEM_UPDATER,(fip_image_handle)&fip_item,1);


    	//[sec.3]load updater.bin to psram
    	memcpy( (void *)UpdaterExecAddress,
    		(void *)(fip_item.start+fip_item.offset),
    		fip_item.size
    		);
#else
    //[2] TODO:load updater_a or updater_b to psram
    #ifdef SPINOR_SUPPORT
    CP_LOGD("get_updater_start_addr : 0x%x",get_updater_start_addr());
    if((get_updater_start_addr() & SPI_FLASH_BASE) == SPI_FLASH_BASE){
        crane_ext_spi_read((unsigned int)(get_updater_start_addr() - SPI_FLASH_BASE),(unsigned int)UpdaterExecAddress,(unsigned int)get_updater_copy_size());
    }
    else
    #endif
    {
    	//[2] TODO:load updater.bin to psram
    	memcpy( (void *)UpdaterExecAddress,
    		(void *)get_updater_start_addr(),
    		get_updater_copy_size());
	}
#endif
#endif
#endif

jump:
		//[3] jump to execute updater
		CP_LOGD("\r\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
		CP_LOGD("\r\n >> BOOTLOADER DONE JUMP TO UPDATER");
		CP_LOGD("\r\n >> PC      : 0x%x",UpdaterExecAddress);
		CP_LOGD("\r\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\r\n");
		TransferControl(UpdaterExecAddress);
	}else{
		CP_LOGD("[BOOT33]NO FOTA FLAG DETECTED \r\n");
	}
}
#endif

