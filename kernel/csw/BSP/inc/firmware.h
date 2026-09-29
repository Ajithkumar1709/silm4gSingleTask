#ifndef __FIRMWARE_H__
#define __FIRMWARE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include "Typedef.h"


/* refer .\bsp\firmware\inc\uuid_sys.h */

/* Length of a node address (an IEEE 802 address). */
#define _UUID_NODE_LEN      6

/* Length of UUID string including dashes. */
#define _UUID_STR_LEN       36

/*
 * See also:
 *      http://www.opengroup.org/dce/info/draft-leach-uuids-guids-01.txt
 *      http://www.opengroup.org/onlinepubs/009629399/apdxa.htm
 *
 * A DCE 1.1 compatible source representation of UUIDs.
 */
struct uuid {
    unsigned char time_low[4];
    unsigned char time_mid[2];
    unsigned char time_hi_and_version[2];
    unsigned char clock_seq_hi_and_reserved;
    unsigned char clock_seq_low;
    unsigned char node[_UUID_NODE_LEN];
};

/* XXX namespace pollution? */
typedef struct uuid uuid_t;

/* refer .\bsp\firmware\inc\firmware_image_package.h */

/* This is used as a signature to validate the blob header */
#define TOC_HEADER_NAME 0xAA640001

#define UUID_NON_TRUSTED_OS_USER1 \
    { { 0x8e, 0x24, 0x91, 0xf2 }, { 0x74, 0x09 }, { 0x11, 0xea }, 0xa9, 0xd0, { 0x8b, 0x58, 0xbb, 0x47, 0x65, 0x30 } }
#define UUID_NON_TRUSTED_OS_USER2 \
    { { 0xde, 0x29, 0x85, 0x86 }, { 0x74, 0x09 }, { 0x11, 0xea }, 0xb4, 0x57, { 0x73, 0x85, 0x08, 0xd6, 0xf2, 0x9a } }
#define UUID_NON_TRUSTED_OS_USER3 \
	{ {0x1d,  0x7f, 0x4d, 0x92 }, { 0x74, 0x0a }, { 0x11, 0xea }, 0xb1, 0x75, { 0x5f, 0xe0, 0xb3, 0x0b, 0xa5, 0x71 } }
#define UUID_NON_TRUSTED_OS_USER4 \
	{ {0xe6,  0x45, 0xe4, 0x11 }, { 0xeb, 0x9c }, { 0x4e, 0x2a }, 0xbb, 0xce, { 0x5c, 0x21, 0x29, 0x0d, 0x6d, 0x8a } }
#define UUID_NON_TRUSTED_OS_USER5 \
	{ {0xc9,  0x09, 0x83, 0x1a }, { 0x9e, 0x8e }, { 0x41, 0x32 }, 0x9a, 0x60, { 0xb9, 0xd3, 0x26, 0x86, 0x24, 0x20 } }
#define UUID_NON_TRUSTED_OS_USER6 \
	{ {0xb1,  0x40, 0xd4, 0x42 }, { 0xf0, 0xf8 }, { 0x4a, 0x09 }, 0x8f, 0x9d, { 0x9f, 0x31, 0x7c, 0x31, 0x84, 0xdb } }
#define UUID_NON_TRUSTED_OS_USER7 \
	{ {0x4a,  0xd8, 0x56, 0x0e }, { 0x4c, 0x06 }, { 0x48, 0xcb }, 0xb5, 0x9b, { 0xb7, 0x5a, 0xfa, 0x69, 0x9c, 0x9b } }
#define UUID_NON_TRUSTED_OS_USER8 \
	{ {0x38,  0x40, 0x34, 0xc4 }, { 0x41, 0xa7 }, { 0x48, 0x6d }, 0xb3, 0xa8, { 0x20, 0x0f, 0x3b, 0x27, 0x1d, 0x03 } }
#define UUID_NON_TRUSTED_OS_USER9 \
	{ {0x55,  0x65, 0x1b, 0xc1 }, { 0x41, 0xe2 }, { 0x45, 0xd4 }, 0xb3, 0xbf, { 0x44, 0x61, 0x95, 0x30, 0x9d, 0x2c } }

typedef struct fip_toc_header {
    unsigned int  name;
    unsigned int  serial_number;
    unsigned long long flags;
} fip_toc_header_t;

typedef struct fip_toc_entry {
    uuid_t uuid;
    unsigned long long offset_address;
    unsigned long long size;
    unsigned long long flags;
} fip_toc_entry_t;



/* .\bsp\firmware\inc\firmware.h */
#define PTABLE_NAME_MAX      32

/**
 * @brief           Firmware load information structure
 * @partition_name  Partition name where firmware stored
 * @offset          Firmware offset bytes from the partition base vaddr
 * @size            Firmware size in bytes
 */
typedef struct {
    char partition_name[PTABLE_NAME_MAX];
    unsigned offset;
    unsigned size;
} firmware_load_info_t;

/**
 * @brief           Firmware identity define
 */
typedef enum {
    FIRMWARE_WCN_HERON_CALIFW,
    FIRMWARE_WCN_HERON_FMACFW,
    FIRMWARE_WCN_BT_BTBIN,
    FIRMWARE_WCN_BT_BTLST,
    FIRMWARE_WCN_GNSS_JACANA,
} firmware_identity_t;

int firmware_get_load_info(firmware_identity_t id, firmware_load_info_t *info);

int firmware_load_gnss(void);
int pvt_load_gnss(void);
int firmware_load_btdm(void);


#ifdef __cplusplus
}
#endif

#endif /* __FIRMWARE_H__ */
