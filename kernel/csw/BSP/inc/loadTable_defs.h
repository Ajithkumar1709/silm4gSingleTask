/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/***************************************************************************
*               MODULE IMPLEMENTATION FILE
****************************************************************************
*
* Filename: loadTable.h
*
* The OBM is responsible to copy image from flash to the DDR.
* It doesn't know about real image size and always copy the maximum 7MB.
* The problems:
*  - long time for copying (about 2 sec),
*  - all ERR/spy/debug buffers are overwriten.
*
* SOLUTION:
* Put the Image BEGIN and END address onto predefined area - offset_0x1C0 size 0x40
* Add the the text-signature to recognize are these addresses present in image or not.
* The signature is following the BEGIN/END and is next ":BEGIN:END:LOAD_TABLE_SIGNATURE"
* OBM should check signature in flash and if it is present MAY use the size=(END-BEGIN).
* If signature is invalid the default 7MB is used.
* The IMAGE_END region added into scatter file
*
******************************************************************************/

#ifndef _LOAD_TABLE_DEFS_H_
#define _LOAD_TABLE_DEFS_H_

#if !defined (ADDR_CONVERT)   /*NU:mmap_phy.h,mmap.h; WINCE, LINUX have copy in EE_Postmortem.h, loadTable.h*/
#define APPSMAP_COM_ADDR_HW_PHY     0xBF000000
#define COMMMAP_COM_ADDR_HW_PHY     0xD0000000
#define APPSCOM_SELECT_MASK         0xFF000000

#if defined(FLAVOR_COM) && !defined(FLAVOR_APP)                                /*Convert into COM space*/
#define ADDR_CONVERT(aDDR)    ((UINT8*)((UINT32)(aDDR) &  ~APPSCOM_SELECT_MASK | COMMMAP_COM_ADDR_HW_PHY))
#else
#if !defined(FLAVOR_COM) && defined(FLAVOR_APP)                                /*Convert into APP space*/
#define ADDR_CONVERT(aDDR)    ((UINT8*)((UINT32)(aDDR) &  ~APPSCOM_SELECT_MASK | APPSMAP_COM_ADDR_HW_PHY))
#else
#define ADDR_CONVERT(aDDR)    ((UINT8*)((UINT32)(aDDR)))                      /*do nothing with addresss*/
#endif
#endif
#endif //ADDR_CONVERT

typedef enum
{
	RESET_BASIC_NONE = 0,
	RESET_BASIC_1    = 0x7CAFE001, //while(1)
	RESET_BASIC_2    = 0x7CAFE002, //LogStream
	RESET_BASIC_3    = 0x7CAFE003  //for future use
}enumResetType;

#if defined(FLAVOR_COM) && !defined(FLAVOR_APP) && defined(EE_HANDLER_ENABLE)
#define LOAD_TABLE_RW_COPY_SUPPORTED
extern LoadTableType loadTableRWcopy;
#endif

/***************************************************************************************/

UINT32  getCommLoadTableAddr(void);
UINT32  getCommImageBaseAddr(void);  //This address is UNAVALIABLE if the TAI register applied for whole CODE/CONST area!
UINT32  getCommPostmortemDescAddr(void);
void    getAppComShareMemAddr(UINT32* begin, UINT32* end);
void 	getAppCom_RDATA_MemAddr(UINT32* begin, UINT32* end);
void    commImageTableInit(void);
UINT32  getCommNumOfLife(void);
void    incrementCommNumOfLife(void);
BOOL    StrtupIsPowerup(void);


#if !defined MAP_PHYSICAL_TO_VIRTUAL_ADDRESS
#if defined (OSA_WINCE)
UINT32 ConvertPhysicalAddrToVirtualAddr(UINT32 PhysicalAddr);
void   commImageTableFree(void);

#define MAP_PHYSICAL_TO_VIRTUAL_ADDRESS(pHYaddr)    /*Returns (UINT32) virtual*/ \
			       ConvertPhysicalAddrToVirtualAddr((UINT32)(pHYaddr))
#else
#define MAP_PHYSICAL_TO_VIRTUAL_ADDRESS(pHYaddr)    (pHYaddr)
#endif
#endif//MAP_PHYSICAL_TO_VIRTUAL_ADDRESS

#ifndef _LOAD_TABLE_C_
extern LoadTableType   loadTable;   /* do NOT use "const" in EXTERN prototype */
#endif
extern LoadTableType  *pLoadTable;

#endif //_LOAD_TABLE_DEFS_H_

