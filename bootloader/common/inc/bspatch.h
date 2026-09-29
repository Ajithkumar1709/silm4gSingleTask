/*-
 * Copyright 2003-2005 Colin Percival
 * Copyright 2012 Matthew Endsley
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted providing that the following conditions 
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BSPATCH_H
#define BSPATCH_H

//# include <stdint.h>
#include "common.h"
#include "fbf_parse.h"

//#define SUPPORT_MINI_SYSTEM
//#define SUPPORT_FOTA_NVM


#ifndef FS_ENABLE
#define SUPPORT_NEW_MINI_OTA_VERSION
#define SUPPORT_ADIFF_DFOTA_VERSION
#define SUPPORT_LTEONLY_MINI_OTA_8M8M
#else
#define SUPPORT_ADIFF_DFOTA_VERSION
#define SUPPORT_NEW_MINI_OTA_VERSION
#endif


#define FLASH_1M_SIZE 			0x00100000 //1M
#define CRANE_NOR_BLOCKSIZE 	0x00010000 //64K
#define FOTA_HEADER_MAGIC 		0x54524657
#define FLASH_4K_SIZE 			0x00001000
#define ALIGN_1K_SIZE 			0x0000000a
#define ASR_FOTA_FLAG_LEN_MAX   16
#define ASR_FOTA_FILE_NAME_SIZE 8
#define ASR_FOTA_HEAD_SIZE      2048


#define IMAGE_BSPATCH_READY		0x01
#define IMAGE_BSPATCH_NO_READY  0xFF

#define FOTA_MAGIC              0x464F5441

typedef enum {
	PSRAM_16M,
	PSRAM_8M,
	PSRAM_4M,
}PSRAM_TYPE;


struct bspatch_stream
{
	void* opaque;
	int (*read)(const struct bspatch_stream* stream, void* buffer, int length);
};

int bspatch(const uint8_t* old, int64_t oldsize, uint8_t* new, int64_t newsize, struct bspatch_stream* stream);


enum {
	MINI_SYS_DFOTA_START,
	MINI_SYS_DFOTA_DOWNLOAD_DONE=512,
	MINI_SYS_DFOTA_PRE_RO_BACKUP,
	MINI_SYS_DFOTA_PRE_RO_DONE,
	MINI_SYS_DFOTA_PRE_DDR_RW_BACKUP,
	MINI_SYS_DFOTA_PRE_DDR_RW_DONE,
	MINI_SYS_DFOTA_DDR_RW_BACKUP,
	MINI_SYS_DFOTA_DDR_RW_BACKUP_OLD_DONE,
	MINI_SYS_DFOTA_DDR_RW_DONE,
	MINI_SYS_DFOTA_PS_NCAH_BACKUP,
	MINI_SYS_DFOTA_PS_NCAH_BACKUP_OLD_DONE,
	MINI_SYS_DFOTA_PS_NCAH_DONE,
	MINI_SYS_DFOTA_USBNCAH_BACKUP,
	MINI_SYS_DFOTA_USBNCAH_BACKUP_OLD_DONE,
	MINI_SYS_DFOTA_USBNCAH_DONE,
	MINI_SYS_DFOTA_CODE_PS_BACKUP,
	MINI_SYS_DFOTA_CODE_PS_BACKUP_OLD_DONE,
	MINI_SYS_DFOTA_CODE_PS_DONE,
	MINI_SYS_DFOTA_CODEPSB_BACKUP,
	MINI_SYS_DFOTA_CODEPSB_BACKUP_OLD_DONE,
	MINI_SYS_DFOTA_CODEPSB_DONE,
	MINI_SYS_DFOTA_CODE_PLB_BACKUP,
	MINI_SYS_DFOTA_CODE_PLB_BACKUP_OLD_DONE,
	MINI_SYS_DFOTA_CODE_PLB_DONE,
	MINI_SYS_DFOTA_CODE_PL_BACKUP,
	MINI_SYS_DFOTA_CODE_PL_BACKUP_OLD_DONE,
	MINI_SYS_DFOTA_CODE_PL_DONE,
	MINI_SYS_DFOTA_DSP_RF_BACKUP,
	MINI_SYS_DFOTA_DSP_RF_BACKUP_OLD_DONE,
	MINI_SYS_DFOTA_DSP_DONE,
	MINI_SYS_DFOTA_RF_DONE,
	MINI_SYS_DFOTA_FIRST_MOVING,
	MINI_SYS_DFOTA_FIRST_MOVE_DONE,
	MINI_SYS_DFOTA_SECOND_MOVING,
	MINI_SYS_DFOTA_SECOND_MOVE_DONE,
	MINI_SYS_DFOTA_DONE=1024,
	MINI_SYS_DFOTA_PHASE2_DOWNLOAD_DONE=1036
};

typedef enum {
	PRE_RO,
	PRE_DDR_RW,
	DDR_RW,
	PS_NCAH,
	USBNCAH,
	CODE_PS,
	CODEPSB,
	CODE_PL,
	DSP,
	RF,
	RESERVED,
	CODE_PLB,
}IMAGE_ID;

typedef enum {
	LOCATE_RO,
	LOCATE_NON_OTA,
	LOCATE_RESERVED,
}LOCATE_ID;

typedef enum {
	MOVE_CP,
	MOVE_DSP_RF,
}MOVE_FLAG;







typedef struct _asr_non_diff_info{
	UINT32 roAddress;
	UINT32 roLen;
	UINT32 roChecksum;
	UINT32 nonfotaAddress;
	UINT32 nonfotaLen;
	UINT32 nonfotaChecksum;

	UINT32 app1PartionAddress;
	UINT32 app1PartionLen;
	UINT32 app1PartionChecksum;
	
	UINT32 app2PartionAddress;
	UINT32 app2PartionLen;
	UINT32 app2PartionChecksum;
	
	UINT32 app3PartionAddress;
	UINT32 app3PartionLen;
	UINT32 app3PartionChecksum;

#ifdef SUPPORT_INDEPENDENT_RF
	UINT32 RF_offset;
	UINT32 RF_size;
	UINT32 RF_addr;
#else
	UINT32 reserved[3];
#endif
	UINT32 updater_offset;
	UINT32 updater_size;
	UINT32 updater_addr;

}asr_non_diff_info;



typedef struct _asr_mini_ota_ImageStruct{
	UINT32 ImageID;
	UINT32 ImageOffset;
	UINT32 ImageLen;
	UINT32 ImageCheckSum;
	
	UINT32 oldDeviceFlashAddress;
	UINT32 oldDeviceLen;
	UINT32 oldDeviceCheckSum;
	UINT32 newDeviceFlashAddress;
	UINT32 newDeviceLen;
	UINT32 newDeviceCheckSum;
	UINT32 newDeviceUnpreLen;
	UINT32 reserved[1];

}asr_mini_ota_ImageStruct;

#if (defined(CRANEL_CHIP) || defined(CRANEM_SINGLE_SIM))
#define MINI_OTA_MAX_NUMBER_OF_IMAGE	32
#else
#define MINI_OTA_MAX_NUMBER_OF_IMAGE	12
#endif
typedef struct _asr_mini_ota_head_info{
	UINT32 magic;
	UINT32 format_version;
	
	/*add for mini sys fota*/
	unsigned int second_flash_address;
	unsigned int second_file_size;
	unsigned int first_backup_address;
	unsigned int first_backup_len;
	unsigned int second_backup_address;
	unsigned int second_backup_len;
	unsigned int old_backup_len;
	unsigned int mini_dfota_status;
	unsigned int DFota_CopyAddr;
	unsigned int DFota_CopyFlag;
	unsigned int DFota_TempAddr;
	
#ifdef	SUPPORT_LTEONLY_MINI_OTA_8M8M
	UINT8 uncompressed_image_num;
	UINT8 loadtable_image_num;
	UINT8 update_status;
	UINT8 move_num;
	UINT8 move_ready;
	#ifdef SUPPORT_INDEPENDENT_RF
	UINT8 update_rf_ready;
	UINT8 reserved[2];
	#else
	UINT8 reserved[3];
	#endif
#else
    UINT8 move_num;
	UINT8 reserved[7];
#endif
	
	asr_non_diff_info nonDiffInfo;
	asr_mini_ota_ImageStruct Image[MINI_OTA_MAX_NUMBER_OF_IMAGE];
	#if (defined(CRANEL_CHIP) || defined(CRANEM_SINGLE_SIM))
	UINT32 reserved2[87];
	#else
	UINT32 reserved2[327];
	#endif

	UINT32 first_flash_addr;
	UINT32 first_file_size;

	UINT32 first_dfota_size;
	UINT32 second_dfota_size;
	UINT32 checksum;
}asr_mini_ota_head_info;

#if (defined(UPDATER_SECFOTA_SUPPORT) || defined(BOOT33_SECBOOT_SUPPORT))
#define TRUSTED_HEAD_SIZE (136)
#define TRUSTED_TAIL_SIZE (920)
typedef struct _asr_ota_trusted_info{
	UINT32 headSize;
	UINT32 tailSize;
    UINT8 head[TRUSTED_HEAD_SIZE + ASR_FOTA_FILE_NAME_SIZE + ASR_FOTA_HEAD_SIZE];
    UINT8 tail[TRUSTED_TAIL_SIZE];
}asr_ota_trusted_info;


typedef union{
	asr_ota_trusted_info trusted_info;
	unsigned char reserved[FLASH_4K_SIZE];
}ASR_TRUSTED_INFO;
#endif



enum {
	SYS_ADIFF_DFOTA_FIRST,
	SYS_ADIFF_DFOTA_SECOND
};

enum {
	SYS_ADIFF_DFOTA_STATUS_BACKUP,
	SYS_ADIFF_DFOTA_STATUS_BACKUP_OLD,
	SYS_ADIFF_DFOTA_STATUS_UPDATE
};


#ifdef SUPPORT_ADIFF_DFOTA_VERSION

typedef struct _asr_ota_ImageStruct{
	UINT32 ImageID;
	UINT32 ImageOffset;
	UINT32 ImageLen;
	UINT32 ImageCheckSum;
	
	UINT32 oldDeviceFlashAddress;
	UINT32 oldDeviceLen;
	UINT32 oldDeviceCheckSum;
	UINT32 newDeviceFlashAddress;
	UINT32 newDeviceLen;
	UINT32 newDeviceCheckSum;
	UINT32 newDeviceUnpreLen;
	UINT32 reserved[1];

}asr_ota_ImageStruct;

#define OTA_MAX_NUMBER_OF_IMAGE	32

typedef struct _asr_ota_head_info{
	UINT32 magic;
	UINT32 format_version;
#if defined(LFS_SUPPORT_V2)
	UINT32 reserved1[1];
	UINT32 MaxBackupSize;
#else
	UINT32 reserved1[2];
#endif
	UINT32 uncompressed_image_num;
	UINT32 loadtable_image_num;

	UINT32 update_num;
	UINT32 update_status;
	UINT32 move_num;
	UINT32 move_ready;
	
	UINT32 first_backup_address;
	UINT32 first_backup_len;
	UINT32 old_backup_len;
	UINT32 DFota_CopyAddr;
	UINT32 DFota_TempAddr;
	UINT32 dsp_later_num;
	UINT32 app_num;
	
	UINT32 fota_pkg;
	asr_ota_ImageStruct Image[OTA_MAX_NUMBER_OF_IMAGE];
	UINT32 updater_offset;
	UINT32 updater_size;
	UINT32 updater_addr;
	UINT32 reserved[107];
}asr_ota_head_info;
#endif

#ifdef	SUPPORT_LTEONLY_MINI_OTA_8M8M
enum {
	BACKUP_UNPRESSED,
	BACKUP_LOADTABLE,
	BACKUP_MOVE,
	BACKUP_MOVE_UPDATER,
};
#endif



typedef union{

	asr_mini_ota_head_info mini_ota_head;//new mini ota

	#ifdef SUPPORT_ADIFF_DFOTA_VERSION
	asr_ota_head_info ota_adiffhead;//new adiff ota
	#endif
	unsigned char reserved[2048];
}ASR_OTA_HEADER;

struct fota_firmwar_flag {
	unsigned int header;
	unsigned int upgrade_flag;
	unsigned int fbf_flash_address;
	unsigned int fbf_file_size;
	unsigned int upgrade_method; // 4, DFOTA; 5, MINI SYSTEM DFOTA
	unsigned int version_Flag;
	unsigned char version[64];
	unsigned int DFota_nOfImages;
	unsigned int DFota_NeedCopyOnly;
	unsigned int DFota_CopyLen;
	unsigned char image_status[MAX_NUMBER_OF_IMAGE_STRUCTS_IN_DEVICE_HEADER];
	unsigned int index;

	ASR_OTA_HEADER ota_header;
	unsigned int reserved[447];

	unsigned int checksum;
};


struct fota_param{
	unsigned char fotaFlag[ASR_FOTA_FLAG_LEN_MAX];
	unsigned int buadrate_flag;
	unsigned int buadrate;
	unsigned int mini_sys_enable;
};

UINT32 get_NewFileFlashOffset(struct fota_firmwar_flag* pFOTA_T);

#endif

#ifdef LFS_SUPPORT_V2

#define MBTK_PATH_FOTA   MBTK_PATH_FOTA_V(MBTK_FOTA_FS_SUPPORT_PATH)":/"
#define MBTK_PATH_FOTA_V(s)  MBTK_PATH_FOTA_STR(s)
#define MBTK_PATH_FOTA_STR(s) #s

#define FOTA_FBF_FILE_NAME 	MBTK_PATH_FOTA"asr_fbf_file.bin"
#define DFOTA_FILE_NAME MBTK_PATH_FOTA"asr_dfota_pro_file.bin"
#define DFOTA_BCKU_NAME MBTK_PATH_FOTA"asr_backup_pro_file.bin"
#define DFOTA_OLBK_NAME MBTK_PATH_FOTA"asr_olbkup_pro_file.bin"
#define DFOTA_OLBK_NAME_HD MBTK_PATH_FOTA"asr_olbkup_pro_file_hd.bin"
#endif
