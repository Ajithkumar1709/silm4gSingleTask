/*
##############################################################################
### Intel Confidential
### Copyright (c) Intel Corporation 2002
### All Rights Reserved.
### --------------------------------------------------------------------------
### Project: Flash Data Integrator (FDI)
###
### Module: fm_flt.h - The File Manager File Lookup Table
###
### $Archive: /FDI/SRC/FM_INC/fm_flt.h $
### $Revision: 7 $
### $Date: 3/03/03 12:45a $
### $Author: Xhuang4 $
###
### $NoKeywords: $
##############################################################################
*/

/*
 *****************************************************************
 * NOTICE OF LICENSE AGREEMENT
 *
 * This code is provided by Intel Corp., and the use is governed
 * under the terms of a license agreement. See license agreement
 * for complete terms of license.
 *
 * YOU MAY ONLY USE THE SOFTWARE WITH INTEL FLASH PRODUCTS.  YOUR
 * USE OF THE SOFTWARE WITH ANY OTHER FLASH PRODUCTS IS EXPRESSLY
 * PROHIBITED UNLESS AND UNTIL YOU APPLY FOR, AND ARE GRANTED IN
 * INTEL'S SOLE DISCRETION, A SEPARATE WRITTEN SOFTWARE LICENSE
 * FROM INTEL LICENSING ANY SUCH USE.
 *****************************************************************
 */


#ifndef FM_FLT_H
#define FM_FLT_H

#include "FDI_TYPE.h"

#if (FILE_MANAGER == TRUE)

/*
 * FLT_Error contains all the errors that can occur when performing operations
 * on the File Lookup Table.  A brief description of each error is as follows:
 *
 * FLT_ErrorNone              - The operation was completed successfully.
 * FLT_ErrorNotEnoughMemory   - Not enough memory is available to complete
 *                              the requested operation.
 * FLT_ErrorEntryDoesNotExist - The File Lookup Table does not contain an
 *                              entry that matches the one the operation
 *                              was performed on.
 * FLT_ErrorNoMoreEntries     - The File Lookup Table does not contain any
 *                              more entries to perform the requested
 *                              operation on.
 * FLT_ErrorRead              - An error occurred while reading the File
 *                              Lookup Table.
 */

typedef enum tagFltError
{
   FLT_ErrorNone,
   FLT_ErrorNotEnoughMemory,
   FLT_ErrorEntryDoesNotExist,
   FLT_ErrorNoMoreEntries,
   FLT_ErrorRead
} FLT_Error;



/*****************************************************************************
 *
 * FLT_Create
 *
 * DESCRIPTION:
 *    Creates the File Manager's File Lookup Table.  In this implementation,
 *    the File Lookup Table is created at boot time; therefore, this function
 *    initializes the variables it needs to maintain the table.  If the
 *    File Lookup Table were created dynamically, the function would
 *    allocate the memory needed to maintain the table.
 *
 * PARAMETERS:
 *    None
 *
 * RETURNS:
 *    If the File Lookup Table is created successfully, the function returns
 *    FLT_ErrorNone.  If not enough memory is available to create the File
 *    Lookup Table, the function returns FLT_ErrorNotEnoughMemory.  (This
 *    is only an issue if the File Lookup Table is dynamically created; in
 *    this implementation, the File Lookup Table is created statically.)
 *
 * ASSUMPTIONS:
 *    None
 *
 ****************************************************************************/

FLT_Error FLT_Create(void);



/*****************************************************************************
 *
 * FLT_Destroy
 *
 * DESCRIPTION:
 *    Releases all the resources obtained by the File Lookup Table during
 *    its lifetime.  When the File Lookup Table is created at boot time (as
 *    it is in this implementation), the function resets the variables needed
 *    to maintain the table.  When the File Lookup Table is created
 *    dynamically, the function releases all the memory it obtained during
 *    its lifetime.
 *
 * PARAMETERS:
 *    None
 *
 * RETURNS:
 *    The function returns FLT_ErrorNone.
 *
 * ASSUMPTIONS:
 *    None
 *
 ****************************************************************************/

FLT_Error FLT_Destroy(void);



/*****************************************************************************
 *
 * FLT_AddEntry
 *
 * DESCRIPTION:
 *    Adds a new mapping of a File Manager File to Data Manager Parameters.
 *
 * PARAMETERS:
 *    IN    filename    The File Manager file's name
 *          id          The Data Manager Parameter ID the file is mapped to
 *
 * RETURNS:
 *    If the function is able to successfully add the mapping to the File
 *    Lookup Table, FLT_ErrorNone is returned.  Otherwise, the function
 *    returns FLT_ErrorNotEnoughMemory.
 *
 * ASSUMPTIONS:
 *    None
 *
 ****************************************************************************/

FLT_Error FLT_AddEntry(
   const FDI_TCHAR *    filename,
   const UINT16         id
   );



/*****************************************************************************
 *
 * FLT_GetNumEntries
 *
 * DESCRIPTION:
 *    Returns the number of entries currently in the File Lookup Table.
 *
 * PARAMETERS:
 *    None.
 *
 * RETURNS:
 *    The number of entries currently in the File Lookup Table.
 *
 * ASSUMPTIONS:
 *    None.
 *
 ****************************************************************************/

UINT16 FLT_GetNumEntries(void);



/*****************************************************************************
 *
 * FLT_GetEntryID
 *
 * DESCRIPTION:
 *    Determines the Data Manager ID of the File Manager File.
 *
 * PARAMETERS:
 *    IN    filename    The File Manager file's name
 *    OUT   id          The Data Manager Parameter ID the file is mapped to.
 *                      This value is undefined if the file is not present in
 *                      the File Lookup Table.
 *
 * RETURNS:
 *    If the file is present in the File Lookup Table, FLT_ErrorNone is
 *    returned.  If the file is not present in the File Lookup Table, the
 *    function returns FLT_ErrorEntryDoesNotExist.  If an error occurred while
 *    reading the File Lookup Table, the function returns FLT_ErrorRead.
 *
 * ASSUMPTIONS:
 *    None
 *
 ****************************************************************************/

FLT_Error FLT_GetEntryID(
   UINT16 *             id,
   const FDI_TCHAR *    filename
   );



/*****************************************************************************
 *
 * FLT_GetFirstEntryID
 *
 * DESCRIPTION:
 *    Returns the Data Manager Parameter ID of the first entry in the File
 *    Lookup Table.
 *
 * PARAMETERS:
 *    OUT   id    The Data Manager Parameter ID of the first entry.  This
 *                value is undefined if the File Lookup Table does not contain
 *                any entries.
 *
 * RETURNS:
 *    If the File Lookup Table contains at least one entry, the function
 *    returns FLT_ErrorNone.  If the File Lookup Table does not contain any
 *    entries, the function returns FLT_ErrorNoMoreEntries.  If an error
 *    occurred while reading the File Lookup Table, the function returns
 *    FLT_ErrorRead.
 *
 * ASSUMPTIONS:
 *    None
 *
 ****************************************************************************/

FLT_Error FLT_GetFirstEntryID(
   UINT16 *    id
   );



/*****************************************************************************
 *
 * FLT_GetNextEntryID
 *
 * DESCRIPTION:
 *    Returns the Data Manager Parameter ID of the next entry in the File
 *    Lookup Table.
 *
 * PARAMETERS:
 *    OUT   id    The Data Manager Parameter ID of the next entry.  This value
 *                is undefined if the File Lookup Table does not contain any
 *                additional entries to scan.
 *
 * RETURNS:
 *    If the File Lookup Table has more entries to scan, the function returns
 *    FLT_ErrorNone.  If the File Lookup Table does not have any more entries,
 *    the function returns FLT_ErrorNoMoreEntries.  If an error occurred while
 *    reading the File Lookup Table, the function returns FLT_ErrorRead.
 *
 * ASSUMPTIONS:
 *    None
 *
 ****************************************************************************/

FLT_Error FLT_GetNextEntryID(
   UINT16 *    id
   );



/*****************************************************************************
 *
 * FLT_GetFirstEntryName
 *
 * DESCRIPTION:
 *    Returns the File Manager filename of the first entry in the File
 *    Lookup Table.
 *
 * PARAMETERS:
 *    OUT   filename    The File Manager filename of the first entry.  This
 *                      value is undefined if the File Lookup Table does not
 *                      contain any entries.
 *
 * RETURNS:
 *    If the File Lookup Table contains at least one entry, the function
 *    returns FLT_ErrorNone.  If the File Lookup Table does not contain any
 *    entries, the function returns FLT_ErrorNoMoreEntries.  If an error
 *    occurred while reading the File Lookup Table, the function returns
 *    FLT_ErrorRead.
 *
 * ASSUMPTIONS:
 *    None
 *
 ****************************************************************************/

FLT_Error FLT_GetFirstEntryName(
   FDI_TCHAR *    filename
   );



/*****************************************************************************
 *
 * FLT_GetNextEntryName
 *
 * DESCRIPTION:
 *    Returns the File Manager filename of the next entry in the File
 *    Lookup Table.
 *
 * PARAMETERS:
 *    OUT   filename    The File Manager filename of the next entry.  This
 *                      value is undefined if the File Lookup Table does not
 *                      contain any additional entries to scan.
 *
 * RETURNS:
 *    If the File Lookup Table has more entries to scan, the function returns
 *    FLT_ErrorNone.  If the File Lookup Table does not have any more entries,
 *    the function returns FLT_ErrorNoMoreEntries.  If an error occurred while
 *    reading the File Lookup Table, the function returns FLT_ErrorRead.
 *
 * ASSUMPTIONS:
 *    None
 *
 ****************************************************************************/

FLT_Error FLT_GetNextEntryName(
   FDI_TCHAR *    filename
   );



/*****************************************************************************
 *
 * FLT_DeleteEntryByID
 *
 * DESCRIPTION:
 *    Deletes the entry whose Data Manager Parameter ID matches the value
 *    specified.
 *
 * PARAMETERS:
 *    IN id    The Data Manager Parameter ID to search for
 *
 * RETURNS:
 *    If the File Lookup Table contains an entry whose Data Manager Parameter
 *    ID matches the value specified, the function returns FLT_ErrorNone.
 *    If no entry has a matching Data Manager Parameter ID, the function
 *    returns FLT_ErrorEntryDoesNotExist.
 *
 * ASSUMPTIONS:
 *    None
 *
 ****************************************************************************/

FLT_Error FLT_DeleteEntryByID(
   const UINT16 id
   );


#endif /* FILE_MANAGER == TRUE */
#endif /* FM_FLT_H */
