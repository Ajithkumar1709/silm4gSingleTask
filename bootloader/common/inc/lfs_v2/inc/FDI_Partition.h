#ifndef _FDI_PARTITION_H_
#define _FDI_PARTITION_H_
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                FDI_Partition.h


GENERAL DESCRIPTION

    This file is for FDI Partition API.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS

   Copyright (c) 2023 by Marvell, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when         who        what, where, why
--------   ------     ----------------------------------------------------------
02/20/2023   zhoujin    Created module
===========================================================================*/


/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
//#include "UART.h"
#include <stdlib.h>
#include <string.h>
//#include "platform.h"
//#include "FDI_EXT.h"
#include "FDI_FILE.h"
#include "FDI_TYPE.h"
//#include "flash_trace.h"
#include "lfs_api.h"

/*===========================================================================

                                LOCAL MACRO
===========================================================================*/

/*
 *
 * FDI Volume Label
 *
 */

/* Volume_label C */
#define FDI_C_VOLUME        "C:/"

/* Volume_label D */
#define FDI_D_VOLUME        "U:/"

#if 1//def MBTK_OPENCPU_SUPPORT

/* Volume_label D */
#define FDI_E_VOLUME        "E:/"

/* Volume_label D */
#define FDI_F_VOLUME        "F:/"
#endif

/*
 *
 * The FDI special character
 *
 */

/* Character ':' */

#define FDI_COLON           ':'

/* Forward Slash */
#define FDI_SLASH           '/'


/* Max Volume label length */
#define MAX_VOLUME_LEN      8

/*===========================================================================

                          Struct definition.

===========================================================================*/

/* FDI file system type. */
typedef enum
{
    FDI_FSYS_LFS_0  = 0x0,
#if (NUM_OF_PARTITION >= 2)
    FDI_FSYS_LFS_1  = 0x1,
#endif
#if 1//def MBTK_OPENCPU_SUPPORT
    FDI_FSYS_LFS_2  = 0x2,
    FDI_FSYS_LFS_3  = 0x3,
#endif
    FDI_FSYS_YAFFS,
    FDI_FSYS_MAX
} FDI_Fsys_Type;

/* FDI file system info type. */
typedef struct FDI_file_system_info
{
    /* FDI file system type */
    FDI_Fsys_Type file_system;

    /* Volume Label name */
    char *volume_label;

} FDI_file_system_info;

/*===========================================================================

            EXTERN DECLARATIONS FOR MODULE

===========================================================================*/

/*===========================================================================

                        EXTERN FUNCTION DECLARATIONS

===========================================================================*/

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      FDI_Transport_Fsys_Register                                      */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function register FDI file system info.                      */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
void FDI_Transport_Fsys_Register(FDI_Fsys_Type fsys, char *volume);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      FDI_Transport_Vl2Dir_Name                                        */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function change Volume label to directory name.              */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      volume                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      dir                                N/A                          */
/*                                                                       */
/*************************************************************************/
BOOL FDI_Transport_Vl2Dir_Name(char *volume, char *dir);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      FDI_Transport_Dir2Vl_Name                                        */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function change directory to Volume label name.              */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      volume                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      dir                                N/A                          */
/*                                                                       */
/*************************************************************************/
BOOL FDI_Transport_Dir2Vl_Name(char *dir, char *volume);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      FDI_Transport_Get_Partition                                      */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function get the FDI partition number .                      */
/*                                                                       */
/* CALLED BY                                                             */
/*                                                                       */
/*      Application                                                      */
/*                                                                       */
/* CALLS                                                                 */
/*                                                                       */
/*      Application                         The application function     */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      block                                                            */
/*      buffer                                                           */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      None                                N/A                          */
/*                                                                       */
/*************************************************************************/
BOOL FDI_Transport_Get_Partition(const char *filename, FDI_Fsys_Type *fsys);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      FDI_Transport_findfirst                                          */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function FDI_findfirst begins a search for files specified   */
/*    wildcards.  The parameter filename_ptr is a string specifying the  */
/*    file name.  Wildcard match characters (* and ?) are supported. The */
/*    parameter fileinfo_ptr is a pointer to the type FILE_INFO which is */
/*    filled with the file information.                                  */
/*                                                                       */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      filename_ptr     const character string for file name specifier  */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      fileinfo_ptr     pointer to type FILE_INFO structure filled with */
/*                       located file information                        */
/*                                                                       */
/*************************************************************************/
int FDI_Transport_findfirst(FDI_Fsys_Type *Partition, const char *filename_ptr, FILE_INFO *fileinfo_ptr);

/*************************************************************************/
/*                                                                       */
/* FUNCTION                                                              */
/*                                                                       */
/*      FDI_Transport_findnext                                           */
/*                                                                       */
/* DESCRIPTION                                                           */
/*                                                                       */
/*      The function begins a next search for files specified wildcards. */
/*    The parameter filename_ptr is a string specifying the file name.   */
/*    Wildcard match characters (* and ?) are supported. The parameter   */
/*    fileinfo_ptr is a pointer to the type FILE_INFO which is filled    */
/*    with the file information.                                         */
/*                                                                       */
/*                                                                       */
/* INPUTS                                                                */
/*                                                                       */
/*      filename_ptr     const character string for file name specifier  */
/*                                                                       */
/* OUTPUTS                                                               */
/*                                                                       */
/*      fileinfo_ptr     pointer to type FILE_INFO structure filled with */
/*                       located file information                        */
/*                                                                       */
/*************************************************************************/
int FDI_Transport_findnext(FDI_Fsys_Type Partition, FILE_INFO *fileinfo_ptr);

/*****************************************************************************
* Function Name: FDI_Transport_GetFreeSpaceSize()
*
* DESCRIPTION:
*    None.
*
* USAGE:
*    unsigned int FDI_Transport_GetFreeSpaceSize(void)
*
* PARAMETERS:
*
* INPUTS:
*  filename_ptr  const character null terminated string of the filename
*                to check
*
* OUTPUTS:
*
* RETURNS:
*  Returns TRUE if filename is valid; otherwise, it returns FALSE.
*
* HISTORY:
* 20.05.05 dmp Took from FDI5 from FDI_FILE.c:3875; and simplifyed.
*
***************************************************************************/
UINT32 FDI_Transport_GetFreeSpaceSize(void);


/****************************************************************************
* Functions: FDI_fopen(), FDI_fclose(),
*	     FDI_fread(),FDI_fwrite(),FDI_fseek()
*
* DESCRIPTION:
*    The function FDI_fopen takes as arguments a file name and a mode;
*    each is specified as a character string.  The file name is used in
*    an implementation-specified matter to open or create a file and
*    associate it with a stream.  Returns the StreamInfoTable index used
*    for the opened file.
*
* USAGE:
*    file_identifier = FDI_Transport_fopen(filename_ptr, wb);
*
* PARAMETERS:
*
* INPUTS:
*  filename_ptr         const character string for file name
*  mode                 const character string for type specification;
*                       modes supported: rb, wb, ab, rb+, wb+, ab+
* OUTPUTS:
*
* RETURNS:
*  Returns the StreamInfoTable index used for the opened file.
*  If an error is detected, FDI_fopen returns 0.
*
* History:
* 20.05.05  Dmitry P. Initial version. Originaly described in FDI_FILE.c:260
*
****************************************************************************/
FILE_ID  FDI_Transport_fopen(const char *filename_ptr, const char *mode);

/*****************************************************************************
* Function Name: FDI_Transport_fclose()
*
* DESCRIPTION:
*    None.
*
* USAGE:
*    int FDI_Transport_fclose(FILE_ID stream)
*
* PARAMETERS:
*
* INPUTS:
*  filename_ptr  const character null terminated string of the filename
*                to check
*
* OUTPUTS:
*
* RETURNS:
*  Returns TRUE if filename is valid; otherwise, it returns FALSE.
*
* HISTORY:
* 20.05.05 dmp Took from FDI5 from FDI_FILE.c:3875; and simplifyed.
*
***************************************************************************/
int FDI_Transport_fclose(FILE_ID stream);

/*****************************************************************************
* Function Name: FDI_Transport_fread()
*
* DESCRIPTION:
*    None.
*
* USAGE:
*    size_t FDI_Transport_fread(void *buff, size_t element_size, size_t count, FILE_ID stream)
*
* PARAMETERS:
*
* INPUTS:
*  filename_ptr  const character null terminated string of the filename
*                to check
*
* OUTPUTS:
*
* RETURNS:
*  Returns TRUE if filename is valid; otherwise, it returns FALSE.
*
* HISTORY:
* 20.05.05 dmp Took from FDI5 from FDI_FILE.c:3875; and simplifyed.
*
***************************************************************************/
size_t FDI_Transport_fread(void *buff, size_t element_size, size_t count, FILE_ID stream);

/*****************************************************************************
* Function Name: FDI_freadEx()
*
* DESCRIPTION:
*    None.
*
* USAGE:
*    size_t FDI_freadEx(void *buff, size_t element_size, size_t count, FILE_ID stream)
*
* PARAMETERS:
*
* INPUTS:
*  filename_ptr  const character null terminated string of the filename
*                to check
*
* OUTPUTS:
*
* RETURNS:
*  Returns TRUE if filename is valid; otherwise, it returns FALSE.
*
* HISTORY:
* 20.05.05 dmp Took from FDI5 from FDI_FILE.c:3875; and simplifyed.
*
***************************************************************************/
size_t FDI_Transport_freadEx(void *buff, size_t element_size, size_t count, FILE_ID stream, UINT32 filepostoread);

/*****************************************************************************
* Function Name: FDI_Transport_fwrite()
*
* DESCRIPTION:
*    None.
*
* USAGE:
*    size_t FDI_Transport_fwrite(const void *buff, size_t element_size,
                  size_t count, FILE_ID stream)
*
* PARAMETERS:
*
* INPUTS:
*  filename_ptr  const character null terminated string of the filename
*                to check
*
* OUTPUTS:
*
* RETURNS:
*  Returns TRUE if filename is valid; otherwise, it returns FALSE.
*
* HISTORY:
* 20.05.05 dmp Took from FDI5 from FDI_FILE.c:3875; and simplifyed.
*
***************************************************************************/

size_t FDI_Transport_fwrite(const void *buff, size_t element_size, size_t count, FILE_ID stream);

/*****************************************************************************
* Function Name: FDI_Transport_fwriteEx()
*
* DESCRIPTION:
*    None.
*
* USAGE:
*    size_t FDI_Transport_fwriteEx(const void *buff, size_t element_size,
                  size_t count,, FILE_ID stream,UINT32 filePostowrite)
*
* PARAMETERS:
*
* INPUTS:
*  filename_ptr  const character null terminated string of the filename
*                to check
*
* OUTPUTS:
*
* RETURNS:
*  Returns TRUE if filename is valid; otherwise, it returns FALSE.
*
* HISTORY:
* 20.05.05 dmp Took from FDI5 from FDI_FILE.c:3875; and simplifyed.
*
***************************************************************************/

size_t FDI_Transport_fwriteEx(const void *buff, size_t element_size, size_t count, FILE_ID stream,UINT32 filePostowrite);

/*****************************************************************************
* Function Name: FDI_Transport_fseek()
*
* DESCRIPTION:
*    None.
*
* USAGE:
*    int FDI_Transport_fseek(FILE_ID stream, long offset, int wherefrom)
*
* PARAMETERS:
*
* INPUTS:
*  filename_ptr  const character null terminated string of the filename
*                to check
*
* OUTPUTS:
*
* RETURNS:
*  Returns TRUE if filename is valid; otherwise, it returns FALSE.
*
* HISTORY:
* 20.05.05 dmp Took from FDI5 from FDI_FILE.c:3875; and simplifyed.
*
***************************************************************************/

int FDI_Transport_fseek(FILE_ID stream, long offset, int wherefrom);

/*****************************************************************************
* Function Name: FDI_Transport_remove()
*
* DESCRIPTION:
*    None.
*
* USAGE:
*    int FDI_Transport_remove(const char *filename_ptr)
*
* PARAMETERS:
*
* INPUTS:
*  filename_ptr  const character null terminated string of the filename
*                to check
*
* OUTPUTS:
*
* RETURNS:
*  Returns TRUE if filename is valid; otherwise, it returns FALSE.
*
* HISTORY:
* 20.05.05 dmp Took from FDI5 from FDI_FILE.c:3875; and simplifyed.
*
***************************************************************************/
int FDI_Transport_remove(const char *filename_ptr);

/*****************************************************************************
* Function Name: FDI_Transport_rename()
*
* DESCRIPTION:
*    None.
*
* USAGE:
*    int FDI_Transport_rename(const FDI_TCHAR *name, const FDI_TCHAR *new_name)
*
* PARAMETERS:
*
* INPUTS:
*  filename_ptr  const character null terminated string of the filename
*                to check
*
* OUTPUTS:
*
* RETURNS:
*  Returns TRUE if filename is valid; otherwise, it returns FALSE.
*
* HISTORY:
* 20.05.05 dmp Took from FDI5 from FDI_FILE.c:3875; and simplifyed.
*
***************************************************************************/
int FDI_Transport_rename(const char *name, const char *new_name);

#endif /* _FDI_PARTITION_H_ */
