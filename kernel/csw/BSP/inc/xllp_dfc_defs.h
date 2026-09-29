/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/******************************************************************************
**
** INTEL CONFIDENTIAL
** Copyright 2003-2004 Intel Corporation All Rights Reserved.
**
** The source code contained or described herein and all documents
** related to the source code (Material) are owned by Intel Corporation
** or its suppliers or licensors.  Title to the Material remains with
** Intel Corporation or its suppliers and licensors. The Material contains
** trade secrets and proprietary and confidential information of Intel
** or its suppliers and licensors. The Material is protected by worldwide
** copyright and trade secret laws and treaty provisions. No part of the
** Material may be used, copied, reproduced, modified, published, uploaded,
** posted, transmitted, distributed, or disclosed in any way without Intel's
** prior express written permission.
**
** No license under any patent, copyright, trade secret or other intellectual
** property right is granted to or conferred upon you by disclosure or
** delivery of the Materials, either expressly, by implication, inducement,
** estoppel or otherwise. Any license under such intellectual property rights
** must be express and approved by Intel in writing.
**
**  FILENAME: xllp_dfc_defs.h
**
**  PURPOSE:  XLLP DFC definitions. REFERENCE: Boerne PX Unit IAS, chapter 20 (DFC)
**
******************************************************************************/

#ifndef __XLLP_DFC_DEFS_H__
#define __XLLP_DFC_DEFS_H__


typedef enum {DMA_MODE, NONDMA_MODE}     TRANSFER_MODE;
typedef enum {ECC_ENABLE, ECC_DISABLE}   ECC_MODE;
typedef enum {NAND, CARBONDALE, PIXLEY}  FLASH_MODE;

typedef enum {
   SAMSUNG_CODE = 0xEC,
   SANDISK_CODE = 0xFF,  // NOTE: find this out
   TOSHIBA_CODE = 0xFE,   // NOTE: find this out
   MICRON_CODE = 0x2C
   } MAKER_CODE;
// Geometry info structure
typedef struct {
    unsigned char  manufacturerId;
    unsigned char  deviceId;
    unsigned int   blocks;
    unsigned int   sectorsPerBlock;
    unsigned int   sectorSize;
} NAND_INFO;

// NAND geometry info
#define g_Zylonite_Nand_Info	\
		{SAMSUNG_CODE, 0x46, 4096, 32, 512}

#define g_Zylonite_LB_Nand_Info	\
		{MICRON_CODE, 0xA1, 1024, 64, 2048}


// Buffer type passed in to the xllp routines for writing/reading.
typedef unsigned int *  P_DFC_BUFFER;

//
// DFC state information.
//
typedef struct {
   int  DMA_EN;     // DMA, or nonDMA mode.
   int  ECC_EN;     // Error correction on, off.
   int  SPARE_EN;   // Spare enable.
   int  ND_MODE;    // NAND, CARBONDALE, PIXLEY...
   int  DWIDTH_C;   // Control bus width.
   int  ND_ARB_EN;  // Data flash bus arbiter enable.
   int  chip;       // Monahans or Tavor
   } FLASH_STATE;


//
// Flash specifications.
//
typedef struct {
   /* timing */
   int  tCH;              // Enable signal hold time.
   int  tCS;              // Enable signal setup time.
   int  tWH;              // ND_nWE high duration.
   int  tWP;              // ND_nWE pulse time.
   int  tRH;              // ND_nRE high duration.
   int  tRP;              // ND_nRE pulse width.
   int  tR;               // ND_nWE high to ND_nRE low for read.
   int  tWHR;             // ND_nWE high to ND_nRE low delay for status read.
   int  tAR;              // ND_ALE low to ND_nRE low delay.
   /* command register values */
   int  NCSX;             // Chip select don't care bit.
   int  RA_START;         // Row address start position.
   int  PAGE_SZ;          // Page size in bytes.
   int  RD_ID_CNT;        // Number of bytes returned from read ID command.
   int  PG_PER_BLK;       // Pages per block.
   /* flash properties */
   int  addr_cycles;      // Number of cycles of addressing.
   int  DWIDTH_M;         // Width of memory configuration.
   /* command codes */
   int  read;
   int  write;
   int  readstatus;
   int  readID;
   int  erase;
   /*
   *  NOTE: I think I'm going to need a set of fields to hold the number of
    *       address cycles for EACH individual command... [02aug2004agapito]
   */
   } FLASH_SPECS;

#define TIMING_MAX_tCH       7
#define TIMING_MAX_tCS       7
#define TIMING_MAX_tWH       7
#define TIMING_MAX_tWP       7
#define TIMING_MAX_tRH       7
#define TIMING_MAX_tRP       7
#define TIMING_MAX_tR    65535
#define TIMING_MAX_tWHR     15
#define TIMING_MAX_tAR      15

#define DFC_DMA_COMMAND  16
#define DFC_DMA_DATA     17

/*
typedef struct {
   XLLP_DMAC_CHANNEL_T       dfcChannels[3];
   P_XLLP_DMAC_DESCRIPTOR_T  commandDesc;
   P_XLLP_DMAC_DESCRIPTOR_T  outputDesc;
   P_XLLP_DMAC_DESCRIPTOR_T  chain;
   } *P_XLLP_DMA_T;
*/


#define STATUS_PAD_2048  10
#define STATUS_PAD_512    2


//
// Relevant and common GPIO memory mapped register needed for configuring flash
// signal list.
//
#define APPS_PAD_BASE  0x40E10000


//
// Chip parameters.
//
typedef struct {
   volatile int *  ND_nWE;     // Write enable.
   volatile int *  ND_nRE;     // Read enable.
   volatile int *  ND_CLE;     // Command latch enable.
   volatile int *  ND_ALE;     // Address latch enable.
   volatile int *  NAND_RnB;   // Ready/Busy_n (low when busy).
   int             nWE_value;  // Write value.
   int             nRE_value;  // Write value.
   int             CLE_value;  // Write value.
   int             ALE_value;  // Write value.
   int             RnB_value;  // Write value.
   } CHIP_GPIO;

//
// Tavor mechanism to release DFI after GPIO configuration
//
#define TAVOR_DFI_RELEASE ((volatile int *)(APPS_PAD_BASE | 0x01FC))
#define TAVOR_RELEASE_8   0x00000200
#define TAVOR_RELEASE_16  0x00000700


//
// Masks to extract the address segments.
//
#define DFC_COL_MASK  0x000000FF
#define DFC_ROW_MASK  0x01FFFE00 // NOTE: Shift or mask bit 8 ? ?


//
// Data flash controller register locations.
//
#define  DFC_TIMING_0 ((volatile int *) 0x43100004)  // NDTR0CS0 : Timing reg 0.
#define  DFC_TIMING_1  ((volatile int *) 0x4310000C)  // NDTR1CS0 : Timing reg 1.
#define  DFC_CONTROL   ((volatile int *) 0x43100000)  // NDCR     : Control.
#define  DFC_STATUS    ((volatile int *) 0x43100014)  // NDSR     : Status.
#define  DFC_PAGES     ((volatile int *) 0x43100018)  // NDPCR    : Page count.
#define  DFC_BADBLOCK0 ((volatile int *) 0x4310001C)  // NDBDR0   : Bad block 0.
#define  DFC_BADBLOCK1 ((volatile int *) 0x43100020)  // NDBDR1   : Bad block 1.
#define  DFC_DATA      ((volatile int *) 0x43100040)  // NDDB     : Data buffer.
#define  DFC_COMMAND0  ((volatile int *) 0x43100048)  // NDCB0    : Command buffer.
#define  DFC_COMMAND1  ((volatile int *) 0x4310004C)  // NDCB1    : Command buffer.
#define  DFC_COMMAND2  ((volatile int *) 0x43100050)  // NDCB2    : Command buffer.

//
// Timing register parameter 0.
//
//  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
// +-------------------+-----+-----+---+-----+-----+---+-----+-----+
// |                   | tCH | tCS |   | tWH | tWP |   | tRH | tRP |
// +-------------------+-----+-----+---+-----+-----+---+-----+-----+
//
#define DFC_TIMING_tRP   0
#define DFC_TIMING_tRH   3
#define DFC_TIMING_tWP   8
#define DFC_TIMING_tWH  11
#define DFC_TIMING_tCS  16
#define DFC_TIMING_tCH  19

//
// Timing register parameter 1.
//
//  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
// +-------------------------------+---------------+-------+-------+
// |               tR              |               | tWHR  |  tAR  |
// +-------------------------------+---------------+-------+-------+
//
#define DFC_TIMING_tAR   0
#define DFC_TIMING_tWHR  4
#define DFC_TIMING_tR   16


//
// DFC register values for each control point.
//
//  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
// +-+-+-+-+-+-+---+-+---+-+-+-----+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// | | | | | | |   | |   | | |     | | | | | | | | | | | | | | | | |
// +-+-+-+-+-+-+---+-+---+-+-+-----+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  S E D N D D  P  N  N  C C   R   R P r N R C C C C C C D S W R W
//  P C M D W W  A  C  D  L L   D   A G e D D S S S S S S B B R D R
//  A C A _ I I  G  S  _  R R   _   _ _ s _ Y 0 1 0 1 0 1 E E D D C
//  R _ _ R D D  E  X  M  _ _   I   S P e A M _ _ _ _ _ _ R R R R M
//  E E E U T T  _     O  P E   D   T E r R   P P C C B B R R E E D
//  _ N N N H H  S     D  G C   _   A R v B   A A M M B B M M Q Q R
//  E       _ _  Z     E  _ C   C   R _ e _   G G D D D D     M M E
//  N       C M           C     N   T B d E   E E D D M M         Q
//                        N     T     L   N   D D M M             M
//                        T           K       M M
//
#define DFC_CTRL_WRCMDREQM    0x00000001
#define DFC_CTRL_RDDREQM      0x00000002
#define DFC_CTRL_WRDREQM      0x00000004
#define DFC_CTRL_SBERRM       0x00000008
#define DFC_CTRL_DBERRM       0x00000010
#define DFC_CTRL_CS1_BBDM     0x00000020
#define DFC_CTRL_CS0_BBDM     0x00000040
#define DFC_CTRL_CS1_CMDDM    0x00000080
#define DFC_CTRL_CS0_CMDDM    0x00000100
#define DFC_CTRL_CS1_PAGEDM   0x00000200
#define DFC_CTRL_CS0_PAGEDM   0x00000400
#define DFC_CTRL_RDYM         0x00000800
#define DFC_CTRL_ND_ARB_EN    0x00001000
#define DFC_CTRL_PG_PER_BLK   0x00004000
#define DFC_CTRL_RA_START     0x00008000
#define DFC_CTRL_RD_ID_CNT0   0x00000000
#define DFC_CTRL_RD_ID_CNT1   0x00010000
#define DFC_CTRL_RD_ID_CNT2   0x00020000
#define DFC_CTRL_RD_ID_CNT3   0x00030000
#define DFC_CTRL_RD_ID_CNT4   0x00040000
#define DFC_CTRL_RD_ID_CNT5   0x00050000
#define DFC_CTRL_RD_ID_CNT6   0x00060000
#define DFC_CTRL_RD_ID_CNT7   0x00070000
#define DFC_CTRL_CLR_ECC      0x00080000
#define DFC_CTRL_CLR_PG_CNT   0x00100000
#define DFC_CTRL_ND_MODE0     0x00000000
#define DFC_CTRL_ND_MODE1     0x00200000
#define DFC_CTRL_ND_MODE2     0x00400000
#define DFC_CTRL_ND_MODE3     0x00600000
#define DFC_CTRL_NCSX         0x00800000
#define DFC_CTRL_PAGE_SZ0     0x00000000
#define DFC_CTRL_PAGE_SZ1     0x01000000
#define DFC_CTRL_PAGE_SZ2     0x02000000
#define DFC_CTRL_PAGE_SZ3     0x03000000
#define DFC_CTRL_DWIDTH_M     0x04000000
#define DFC_CTRL_DWIDTH_C     0x08000000
#define DFC_CTRL_ND_RUN       0x10000000
#define DFC_CTRL_DMA_EN       0x20000000
#define DFC_CTRL_ECC_EN       0x40000000
#define DFC_CTRL_SPARE_EN     0x80000000

#define DFC_OFFSET_RD_ID_CNT          16

//
// DFC register offsets for each control point in command buffer 0.
//
//  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
// +-----------+-+-+-----+-+-+-----+---------------+---------------+
// |           | | |     | | |     |               |               |
// +-----------+-+-+-----+-+-+-----+---------------+---------------+
//   reserved   A C   C   N D   A         CMD2            CMD1
//              U S   M   C B   D
//              T E   D     C   D
//              O L   _         R
//              _     T         _
//              R     Y         C
//              S     P         Y
//                    E         C
//
#define DFC_CMD_OFFSET_AUTO_RS   25
#define DFC_CMD_OFFSET_CSEL      24
#define DFC_CMD_OFFSET_CMD_TYPE  21
#define DFC_CMD_OFFSET_NC        20
#define DFC_CMD_OFFSET_DBC       19
#define DFC_CMD_OFFSET_ADDR_CYC  16
#define DFC_CMD_OFFSET_CMD2       8
#define DFC_CMD_OFFSET_CMD1       0

// To set the AUTO_RS bit, the flash's read status command must be equal to this.
#define DFC_AUTO_RS_CMD 0x70

//
// DFC register offsets for each control point in command buffer 1.
//
//  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
// +---------------+---------------+---------------+---------------+
// |               |               |               |               |
// +---------------+---------------+---------------+---------------+
//      ADDR4           ADDR3           ADDR2           ADDR1 
//
#define DFC_CMD_OFFSET_ADDR4  24
#define DFC_CMD_OFFSET_ADDR3  16
#define DFC_CMD_OFFSET_ADDR2   8
#define DFC_CMD_OFFSET_ADDR1   0

//
// DFC register offsets for each control point in command buffer 2.
//
//  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
// +-----------------------------------+-----------+---------------+
// |                                   |           |               |
// +-----------------------------------+-----------+---------------+
//               reserved                PAGE_COUNT     ADDR5    
//
#define DFC_CMD_OFFSET_PAGE_COUNT  8
#define DFC_CMD_OFFSET_ADDR5       0

typedef enum {
   DFC_CMDTYPE_READ,    // b000
   DFC_CMDTYPE_WRITE,   // b001
   DFC_CMDTYPE_ERASE,   // b010
   DFC_CMDTYPE_READID,  // b011
   DFC_CMDTYPE_STATUS,  // b100
   DFC_CMDTYPE_RESET    // b101
   } DFC_CMD_TYPE;


//
// DFC status register masks for each status bit.
//
//  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
// +---------------------------------------+-+-+-+-+-+-+-+-+-+-+-+-+
// |                                       | | | | | | | | | | | | |
// +---------------------------------------+-+-+-+-+-+-+-+-+-+-+-+-+
//                 reserved                 R C C C C C C D S W R W
//                                          D S S S S S S B B R D R
//                                          Y 0 1 0 1 0 1 E E D D C
//                                            _ _ _ _ _ _ R R R R M
//                                            P P C C B B R R E E D
//                                            A A M M B B     Q Q R
//                                            G G D D D D         E
//                                            E E D D             Q
//                                            D D                  
//
#define DFC_SR_RDY        0x00000800
#define DFC_SR_CS0_PAGED  0x00000400
#define DFC_SR_CS1_PAGED  0x00000200
#define DFC_SR_CS0_CMDD   0x00000100
#define DFC_SR_CS1_CMDD   0x00000080
#define DFC_SR_CS0_BBD    0x00000040
#define DFC_SR_CS1_BBD    0x00000020
#define DFC_SR_DBERR      0x00000010
#define DFC_SR_SBERR      0x00000008
#define DFC_SR_WRDREQ     0x00000004
#define DFC_SR_RDDREQ     0x00000002
#define DFC_SR_WRCMDREQ   0x00000001


//
// Some handy dandy error codes.
//
#define ERR_DBERR    -DFC_SR_DBERR
#define ERR_SBERR    -DFC_SR_SBERR
#define ERR_CS0_BBD  -DFC_SR_CS0_BBD
#define ERR_CS1_BBD  -DFC_SR_CS1_BBD


#endif


