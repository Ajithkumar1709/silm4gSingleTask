/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : fdi_header_support.h
Description : definitions for the fdi header.

Copyright (c) 2004 Intel CCD. All Rights Reserved
=========================================================================== */

#if !defined(_FDI_HEADER_SUPPORT_H_)
#define _FDI_HEADER_SUPPORT_H_

#include "nvm_header.h"

#define NVM_HEADER_FIELD_SIZE  	        (30)
#define NVM_HEADER_FIELD_REG_SIZE       (32)
#define NVM_HEADER_FIELD_EXT_SIZE       (64)
//ICAT EXPORTED STRUCT
typedef struct
{
        UINT32  StructSize;
        char    StructNameString[NVM_HEADER_FIELD_SIZE];
        char    DateString[NVM_HEADER_FIELD_SIZE];
        char    TimeString[NVM_HEADER_FIELD_SIZE];
        char    HwId[NVM_HEADER_FIELD_SIZE];
        char    VersionString[NVM_HEADER_FIELD_SIZE];
        char    PcCalibrationSwVersionString[NVM_HEADER_FIELD_SIZE];
}NVMStructHeader_ts;


#define NVMFormatHeader_ts NVM_Header_ts


BOOL FDI_GetNVMFileVersion(char * data, char * versionString);
VOID FDI_CreateNVMHeader(NVMStructHeader_ts * NVMHeader, char * StructNameString, char * HwId, char *VersionString, char * PcCalibrationSwVersionString, UINT32 StructFileSize);

BOOL FDI_GetNVMFormatFileVersion(char * data, char * Version);
VOID FDI_CreateNVMFormatHeader(NVMFormatHeader_ts * NVMHeader, UINT32  StructSize, UINT32  NumOfStructs, char *StructName, char *Version, char *HW_ID, char *CalibVersion);


#endif /* _FDI_HEADER_SUPPORT_H_ */


/*                      end of _FDI_header_support.h
--------------------------------------------------------------------------- */
