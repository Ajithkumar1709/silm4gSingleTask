/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
INTEL CONFIDENTIAL
Copyright 2006 Intel Corporation All Rights Reserved.
The source code contained or described herein and all documents related to the source code ("Material") are owned
by Intel Corporation or its suppliers or licensors. Title to the Material remains with Intel Corporation or
its suppliers and licensors. The Material contains trade secrets and proprietary and confidential information of
Intel or its suppliers and licensors. The Material is protected by worldwide copyright and trade secret laws and
treaty provisions. No part of the Material may be used, copied, reproduced, modified, published, uploaded, posted,
transmitted, distributed, or disclosed in any way without Intel's prior express written permission.

No license under any patent, copyright, trade secret or other intellectual property right is granted to or
conferred upon you by disclosure or delivery of the Materials, either expressly, by implication, inducement,
estoppel or otherwise. Any license under such intellectual property rights must be express and approved by
Intel in writing.
-------------------------------------------------------------------------------------------------------------------*/

/*******************************************************************************
*               MODULE HEADER FILE
********************************************************************************
* Title: diag
*
* Filename: DiagSig_L1.h
*
* Target, platform: Common Platform, SW platform
*
* Authors:  Barak Witkowski
*
* Description: definitions of structures for L1 signals. Unlike PS definitions, these definitions are frozen
*              and should not be changed according to PS code changes
*
* Last Updated:
*
* Notes:
*******************************************************************************/

#if !defined (DIAG_SIG_L1_H)
#define DIAG_SIG_L1_H

#include "global_types.h"
#include "ICAT_config.h"
#include "diag_config.h"
#include "diag_pdu.h"
/*************************************************************************************
  NOTE ! NOTE ! NOTE ! NOTE ! NOTE ! NOTE ! NOTE ! NOTE ! NOTE ! NOTE ! NOTE ! NOTE !
 *************************************************************************************
The following structures are a copy of equivalent structure in the Manitoba GKI library.
The Manitoba GKI structures contains enum fields. They should not be treated as 32 bits.
Each enum should be translate according the optimized type that can contains it. e.g. A
8 values enum should be translate into UINT8.
*/

typedef struct DiagSignalBufferTag
{
    UINT32        *type;
    UINT8         *sig;
}
DiagSignalBuffer;

typedef struct DiagSignalDirectivesTag
{
#if (defined(DIAG_1_BYTE_TASK_IDS) || defined(KI_DISABLE_TASK_SETS))
    UINT8              source;
    UINT8              dest;
#else
#if defined(DIAG_4_BYTE_TASK_IDS)
    UINT32              source;
    UINT32              dest;
#else
    UINT16              source;
    UINT16              dest;
#endif
#endif
}
DiagSignalDirectives;

typedef union
{
  UINT8  body[4];
  UINT32 dummy;   //ensure the body is 32-bit aligned
}DiagSigBody;

typedef enum
{
  sig0=0,
#if defined(DIAG_4_BYTE_SIGNAL_IDS)
  sig1=0x10000 //ensure it's 32-bit;
#else
  sig1=0x100 //ensure it's 16-bit at least; will be 32-bit with "armcc -fy" (ccxsc default is 32-bit, but an option exists to change this)
#endif
}SigIdEnum;

typedef struct DiagSignalRecord
{

    DiagSignalDirectives    directives; // alignment for structures is configurable in ICAT

    UINT16              length;

    SigIdEnum           id;             // actually, enum: assume the number of signals is always below 64K

    DiagSigBody         sigBody;        // actually, union always containing a UINT32 field, thus 32-bit aligned.
}

#ifndef __cplusplus
//Signal,
#endif

DiagSignalRecord;

/*  This is needed for the Manitoba logging system */
typedef struct DiagLoggedSignalRecord
{
    DiagSignalDirectives    directives;
    UINT32              frameNumber;
    UINT32              time;
    UINT16              length;
    SigIdEnum           id;
    // No body should come here.	
}
#ifndef __cplusplus
DiagSerialSignalHeader,
#endif
DiagLoggedSignalRecord;

typedef enum DiagKiSignalFormatTag
{
    DIAG_KI_NO_FORMAT,
    DIAG_KI_SIGNAL_FORMAT,
    DIAG_KI_COMMAND_FORMAT,
    DIAG_KI_LOGGED_SIGNAL_FORMAT,
    DIAG_KI_NUM_SIGNAL_FORMATS

} DiagKiSignalFormat;

#if defined (KI_MEMORY_USAGE)
/** Memory debug info.
 * This structure is used to hold useful information for debugging memory
 * related issues. This is only defined if #KI_MEMORY_USAGE is defined. */
typedef struct DiagKiMemDebugInfoTag
{
    /** Address of calling code.
     * This is used to store the address of the code that called the GKI
     * function that allocated the associated memory. */
    UINT32                           callerAddress;

    /** Caller GKI task id.
     * This is the GKI task id of the task that called the GKI function
     * that allocated the associated memory. */
#if (defined(DIAG_1_BYTE_TASK_IDS) || defined(KI_DISABLE_TASK_SETS))
    UINT8              taskId;
#else
#if defined(DIAG_4_BYTE_TASK_IDS)
    UINT32              taskId;
#else
    UINT16              taskId;
#endif
#endif

    /** Function used to allocate the memory.
     * This is an id that indicates what function allocated the
     * associated memory. */
    UINT8                allocSource;
}
DiagKiMemDebugInfo;
#endif

/** Generic memory header.
 * This header is shared between the signal and memory headers. */
typedef struct DiagKiGenMemHeaderTag
{
#if defined (KI_MEMORY_USAGE) /* For memory leak debuging */
    /* Must be first field */
    /** Memory debug info.
     * This is used to store information required for debugging memory related
     * problems. This is only present if #KI_MEMORY_USAGE is defined. */
    DiagKiMemDebugInfo                  debugInfo;
#endif

    /*
    ** The memory pool that this structure/signal is stored in.
    */
    UINT8                pool;

    /* Whether the memory was Alloced (Created) or Requested */
    UINT8                priority;

} DiagKiGenMemHeader;

typedef struct DiagKiOsHeaderTag
{
    /** Generic header.
     * This is a generic memory header containing debug, pool and priority
     * information. Must be first in this structure. */
    DiagKiGenMemHeader                  genHeader;

    /*
    ** Signal identifier used to indicate to the
    ** EmmiRxTask what type of signal this is i.e.
    **  - Logged signal, Command, Normal Signal
    */
    UINT8                format;
}
DiagKiOsHeader;

typedef struct DiagSignalStructureTag
{
    DiagKiOsHeader                      header;
    DiagSignalRecord                    record;
}
DiagSignalStructure;

typedef struct DiagLoggedSignalStructureTag
{
    DiagKiOsHeader                      header;
    DiagLoggedSignalRecord              record;
}
DiagLoggedSignalStructure;

typedef union DiagSigCommandBodyTag
{
  UINT8  body[4];
  UINT32 dummy;   //ensure the body is 32-bit aligned
}
DiagSigCommandBody;

typedef struct DiagSigCommand
{
    UINT8           id;
    DiagSigCommandBody         body;
}
DiagSigCommand;


typedef struct DiagSigCommandStructureTag
{
    DiagKiOsHeader                  header;
    UINT16                          commandLength;
    DiagSigCommand                  record;
}
DiagSigCommandStructure;


typedef union DiagGenericStructureTag
{
    DiagKiOsHeader                      header;
    DiagSignalStructure                 signal;
    DiagSigCommandStructure             command;
    DiagLoggedSignalStructure           loggedSignal;
}
DiagGenericStructure;

/***********************************************************/
/* Signal filter matrix definition - coupled with ki_sig.h */
/***********************************************************/
#if defined(DIAG_4_BYTE_SIGNAL_IDS)

typedef struct KiSetsFilterMatrixTag
{
    /* Member: Int16 numSets = The number of signal sets in the matrix array. */
    UINT16    numSets;
    /* Member: Int32 numBases = The number of signal bases in the matrix array. */
    UINT32    numBases;
    /* Member: Int32 matrixSize = The size in bytes of the matrix array. */
    UINT32    matrixSize;
    /* Member: Int8 matrix[10] = The filter matrix. The size of this array is given
    **             by the matrixSize array rather than the statically defined
    **             dimension. This array has information on what signals within
    **             each base and set should be logged. */
    UINT8     matrix[10];

} KiSetsFilterMatrix;
#else

typedef struct TinyFilterDataTag
{
    UINT8   numberBases;
    UINT16  matrixSize;
    UINT8   baseOffsets[200];  /* Doesn`t matter how big/small this is */
    UINT8  *matrix;

} TinyFilterData;

typedef UINT8 **TinyFilterMatrix;
#endif	//#if defined(DIAG_4_BYTE_SIGNAL_IDS)

DIAG_EXPORT void TraceSignal( void * signalRecord );
DIAG_EXPORT void TraceLoggedSignal( void * loggedSignalRecord );
DIAG_EXPORT void diagmCreateandSendSignal(void *data);
DIAG_EXPORT void diagSendGkiCommandOrSignal(UINT8 DiagSAP , void* ptr , UINT16 dataLength);
#endif

