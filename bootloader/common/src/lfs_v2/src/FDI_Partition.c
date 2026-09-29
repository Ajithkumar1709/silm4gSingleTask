/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                FDI_Partition.c


GENERAL DESCRIPTION

    This file is for FDI Partition API.

EXTERNALIZED FUNCTIONS

INITIALIZATION AND SEQUENCING REQUIREMENTS

   Copyright (c) 2023 by ASR, Incorporated.  All Rights Reserved.
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

#include "FDI_Partition.h"

/*===========================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

===========================================================================*/

/* FDI file system partition. */
FDI_Fsys_Type FDI_Fsys_Partition;

/* FDI file system info */
FDI_file_system_info FDI_fsys_info[FDI_FSYS_MAX];

/*===========================================================================

            EXTERN DECLARATIONS FOR MODULE

===========================================================================*/

/*===========================================================================

            EXTERN DEFINITIONS AND DECLARATIONS FOR MODULE

===========================================================================*/

/*===========================================================================

                          INTERNAL FUNCTION DEFINITIONS

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
void FDI_Transport_Fsys_Register(FDI_Fsys_Type fsys, char *volume)
{

/*---------------------------------------------------------------------*/

    ASSERT(fsys < FDI_FSYS_MAX);
    ASSERT(strlen(volume) <= MAX_VOLUME_LEN);

    FDI_fsys_info[fsys].file_system     = fsys;
    FDI_fsys_info[fsys].volume_label    = volume;

    CP_LOGD("%s: %d, %s\r\n", __FUNCTION__, fsys, volume);

    return;
}

#ifdef FDI_MULTIPLE_PARTITION
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
BOOL FDI_Transport_Get_Partition(const char *filename, FDI_Fsys_Type *fsys)
{
    int i = 0, length = 0, PrefixLen = 0;

/*---------------------------------------------------------------------*/

    length = strlen(filename);
    if (( length <= 0) || ( length > FILE_NAME_SIZE))
    {
        return FALSE;
    }

    for (i = 0; i < FDI_FSYS_MAX; i++)
    {
        if (FDI_fsys_info[i].volume_label)
        {
            PrefixLen = strlen(FDI_fsys_info[i].volume_label);
            if((PrefixLen > 0) && (length >= PrefixLen) &&
                (memcmp((char *)filename, FDI_fsys_info[i].volume_label, PrefixLen) == 0))
            {
                *fsys = FDI_fsys_info[i].file_system;
                return TRUE;
            }
        }
    }

    return FALSE;
}

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
int FDI_Transport_findfirst(FDI_Fsys_Type *Partition, const char *filename_ptr, FILE_INFO *fileinfo_ptr)
{
    int ret = 0, length = 0;
    FDI_Fsys_Type fsys = FDI_FSYS_LFS_0;

/*---------------------------------------------------------------------*/

    FATSYS_TRACE("%s %s", __FUNCTION__, filename_ptr);

    length = strlen(filename_ptr);
    if (( length <= 0) || ( length > FILE_NAME_SIZE))
    {
        return -1;
    }

    FDI_Transport_Get_Partition(filename_ptr, &fsys);

    switch(fsys)
    {
        case FDI_FSYS_LFS_0:
#if (NUM_OF_PARTITION == 2)
        case FDI_FSYS_LFS_1:
#endif
        {
            ret = FDI_findfirst(filename_ptr, fileinfo_ptr);
            break;
        }

        case FDI_FSYS_YAFFS:
        {
            break;
        }

        default:
        {
            ASSERT(0);
            break;
        }
    }


    if(Partition)
    {
        *Partition = fsys;
    }

    FDI_Fsys_Partition = fsys;

    return ret;
}

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
int FDI_Transport_findnext(FDI_Fsys_Type Partition, FILE_INFO *fileinfo_ptr)
{
    int ret = 0;

    FATSYS_TRACE("%s[%d]", __FUNCTION__, Partition);

    ASSERT(FDI_Fsys_Partition == Partition);

    switch(Partition)
    {
        case FDI_FSYS_LFS_0:
#if (NUM_OF_PARTITION == 2)
        case FDI_FSYS_LFS_1:
#endif
        {
            ret = FDI_findnext(fileinfo_ptr);
            break;
        }

        case FDI_FSYS_YAFFS:
        {
            break;
        }

        default:
        {
            ASSERT(0);
            break;
        }
    }

    return ret;
}//FDI_findnext()

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
UINT32 FDI_Transport_GetFreeSpaceSize(void)
{
	UINT32 size = 0;
	FDI_Fsys_Type partition = FDI_Fsys_Partition;

    FATSYS_TRACE("%s: %d", __FUNCTION__, partition);

    switch(partition)
    {
        case FDI_FSYS_LFS_0:
#if (NUM_OF_PARTITION == 2)
        case FDI_FSYS_LFS_1:
#endif
        {
            char *path = FDI_fsys_info[partition].volume_label;

            size = FDI_GetPartitionFreeSpaceSize(path);

            break;
        }

        case FDI_FSYS_YAFFS:
        {
            break;
        }

        default:
        {
            ASSERT(0);
            break;
        }
    }

	return size;
}


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
FILE_ID  FDI_Transport_fopen(const char *filename_ptr, const char *mode)
{
    FILE_ID fd = 0;
    int length = 0;
    FDI_Fsys_Type partition = FDI_FSYS_LFS_0;

    FATSYS_TRACE("%s[%d]: %s", __FUNCTION__, partition, filename_ptr);

    length = strlen(filename_ptr);
    if (( length <= 0) || ( length > FILE_NAME_SIZE))
    {
        return 0;
    }

    FDI_Transport_Get_Partition(filename_ptr, &partition);

    switch(partition)
    {
        case FDI_FSYS_LFS_0:
#if (NUM_OF_PARTITION == 2)
        case FDI_FSYS_LFS_1:
#endif
        {
            fd = FDI_fopen(filename_ptr, mode) & 0xFF;
            break;
        }

        case FDI_FSYS_YAFFS:
        {
            break;
        }

        default:
        {
            ASSERT(0);
            break;
        }
    }

    return EXT_FILE_HANDLE(fd, partition);
}

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
int FDI_Transport_fclose(FILE_ID stream)
{
    int ret = 0;
    FDI_Fsys_Type partition = FDI_FSYS_LFS_0;

    /* Get the File System partition. */
    partition = (FDI_Fsys_Type)Get_Partition_From_Handle(stream);

    FATSYS_TRACE("%s[%d]: 0x%x", __FUNCTION__, partition, stream);

    switch(partition)
    {
        case FDI_FSYS_LFS_0:
#if (NUM_OF_PARTITION == 2)
        case FDI_FSYS_LFS_1:
#endif
        {
            ret = FDI_fclose(stream);
            break;
        }

        case FDI_FSYS_YAFFS:
        {
            break;
        }

        default:
        {
            ASSERT(0);
            break;
        }
    }

    return ret;
}


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
size_t FDI_Transport_fread(void *buff, size_t element_size, size_t count, FILE_ID stream)
{
    UINT32 length = 0;
    FDI_Fsys_Type partition = FDI_FSYS_LFS_0;

    /* Get the File System partition. */
    partition = (FDI_Fsys_Type)Get_Partition_From_Handle(stream);

    FATSYS_TRACE("%s[%d]: 0x%x", __FUNCTION__, partition, stream);

    switch(partition)
    {
        case FDI_FSYS_LFS_0:
#if (NUM_OF_PARTITION == 2)
        case FDI_FSYS_LFS_1:
#endif
        {
            length = FDI_fread(buff, element_size, count, stream);
            break;
        }

        case FDI_FSYS_YAFFS:
        {
            break;
        }

        default:
        {
            ASSERT(0);
            break;
        }
    }

    return length;
}

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
size_t FDI_Transport_freadEx(void *buff, size_t element_size, size_t count, FILE_ID stream, UINT32 filepostoread)
{
    UINT32 length = 0;
    FDI_Fsys_Type partition = FDI_FSYS_LFS_0;

    /* Get the File System partition. */
    partition = (FDI_Fsys_Type)Get_Partition_From_Handle(stream);

    FATSYS_TRACE("%s[%d]: 0x%x", __FUNCTION__, partition, stream);

    switch(partition)
    {
        case FDI_FSYS_LFS_0:
#if (NUM_OF_PARTITION == 2)
        case FDI_FSYS_LFS_1:
#endif
        {
            length = FDI_freadEx_fatsys(buff, element_size, count, stream, filepostoread);
            break;
        }

        case FDI_FSYS_YAFFS:
        {
            break;
        }

        default:
        {
            ASSERT(0);
            break;
        }
    }

    return length;
}

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

size_t FDI_Transport_fwrite(const void *buff, size_t element_size,
                  size_t count, FILE_ID stream)
{
    UINT32 length = 0;
    FDI_Fsys_Type partition = FDI_FSYS_LFS_0;

    /* Get the File System partition. */
    partition = (FDI_Fsys_Type)Get_Partition_From_Handle(stream);

    FATSYS_TRACE("%s[%d]: 0x%x", __FUNCTION__, partition, stream);

    switch(partition)
    {
        case FDI_FSYS_LFS_0:
#if (NUM_OF_PARTITION == 2)
        case FDI_FSYS_LFS_1:
#endif
        {
            length = FDI_fwrite(buff, element_size, count, stream);
            break;
        }

        case FDI_FSYS_YAFFS:
        {
            break;
        }

        default:
        {
            ASSERT(0);
            break;
        }
    }

    return length;
}


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

size_t FDI_Transport_fwriteEx(const void *buff, size_t element_size,
                  size_t count, FILE_ID stream,UINT32 filePostowrite)
{
    UINT32 length = 0;
    FDI_Fsys_Type partition = FDI_FSYS_LFS_0;

    /* Get the File System partition. */
    partition = (FDI_Fsys_Type)Get_Partition_From_Handle(stream);

    FATSYS_TRACE("%s[%d]: 0x%x", __FUNCTION__, partition, stream);

    switch(partition)
    {
        case FDI_FSYS_LFS_0:
#if (NUM_OF_PARTITION == 2)
        case FDI_FSYS_LFS_1:
#endif
        {
            length = FDI_fwriteEx_fatsys(buff, element_size, count, stream, filePostowrite);
            break;
        }

        case FDI_FSYS_YAFFS:
        {
            break;
        }

        default:
        {
            ASSERT(0);
            break;
        }
    }

    return length;
}


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

int FDI_Transport_fseek(FILE_ID stream, long offset, int wherefrom)
{
    int ret = 0;
    FDI_Fsys_Type partition = FDI_FSYS_LFS_0;

    /* Get the File System partition. */
    partition = (FDI_Fsys_Type)Get_Partition_From_Handle(stream);

    FATSYS_TRACE("%s[%d]: 0x%x", __FUNCTION__, partition, stream);

    switch(partition)
    {
        case FDI_FSYS_LFS_0:
#if (NUM_OF_PARTITION == 2)
        case FDI_FSYS_LFS_1:
#endif
        {
            ret = FDI_fseek(stream, offset, wherefrom);
            break;
        }

        case FDI_FSYS_YAFFS:
        {
            break;
        }

        default:
        {
            ASSERT(0);
            break;
        }
    }

    return ret;
}

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
int FDI_Transport_remove(const char *filename_ptr)
{
    int ret = 0;
    int length = 0;
    FDI_Fsys_Type partition = FDI_FSYS_LFS_0;

/*---------------------------------------------------------------------*/

    length = strlen(filename_ptr);
    if (( length <= 0) || ( length > FILE_NAME_SIZE))
    {
        return -1;
    }

    FDI_Transport_Get_Partition(filename_ptr, &partition);

    FATSYS_TRACE("%s[%d]: %s", __FUNCTION__, partition, filename_ptr);

    switch(partition)
    {
        case FDI_FSYS_LFS_0:
#if (NUM_OF_PARTITION == 2)
        case FDI_FSYS_LFS_1:
#endif
        {
            ret = FDI_remove(filename_ptr);
            break;
        }

        case FDI_FSYS_YAFFS:
        {
            break;
        }

        default:
        {
            ASSERT(0);
            break;
        }
    }

    return ret;
}

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
int FDI_Transport_rename(const char *name, const char *new_name)
{
    int ret = 0, NewLen = 0;
    FDI_Fsys_Type partition = FDI_FSYS_LFS_0;

/*---------------------------------------------------------------------*/

    NewLen = strlen(new_name);
    if (( NewLen <= 0) || ( NewLen > FILE_NAME_SIZE))
    {
        return -1;
    }

    FDI_Transport_Get_Partition(name, &partition);

    FATSYS_TRACE("%s[%d]: %s -> %s", __FUNCTION__, partition, name, new_name);

    switch(partition)
    {
        case FDI_FSYS_LFS_0:
#if (NUM_OF_PARTITION == 2)
        case FDI_FSYS_LFS_1:
#endif
        {
            ret = FDI_rename((char*)name, (char*)new_name);
            break;
        }

        case FDI_FSYS_YAFFS:
        {
            break;
        }

        default:
        {
            ASSERT(0);
            break;
        }
    }

    return ret;
}
#endif
