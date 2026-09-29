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

#if !defined (_DIAG_RAM_DEBUG_H_)
#define _DIAG_RAM_DEBUG_H_

//#define DIAG_RAM_DEBUG_ENABLE    //enable this only if you want to use this feature

#if !defined (DIAG_RAM_DEBUG_ENABLE)
/* debug disable */
#define DIAG_CREATE_RAM_FORMATTED_BUFFER(bufferName,maxBufferEntries,maxSizeOfReport)
#define DIAG_REFERENCE_TO_RAM_BUFFER_FORMATTED(bufferName, maxBufferEntries, maxSizeOfReport)
#define DIAG_RESET_RAM_BUFFER(bufferName)
#define DIAG_RAM_REPORT_FORMATTED_INDEX_2P(bufferName, param1, param2)

#else
/* debug enable */
#if 1
#define DIAG_CREATE_RAM_FORMATTED_BUFFER(bufferName,maxBufferEntries,maxSizeOfReport)   \
            typedef struct {\
                UINT16  index;\
                UINT16  numOfEntries;\
                UINT8   isFormatted;\
                UINT8   entrySize;\
                UINT8   numOfWrapps;\
                UINT8   buffer[maxBufferEntries][maxSizeOfReport];\
            } bufferName##RAMBufferST;\
            bufferName##RAMBufferST bufferName##RAMBuffer = {0,maxBufferEntries,1,maxSizeOfReport, 0};

#define DIAG_REFERENCE_TO_RAM_BUFFER_FORMATTED(bufferName, maxBufferEntries, maxSizeOfReport)   \
            typedef struct {\
                UINT16  index;\
                UINT16  numOfEntries;\
                UINT8   isFormatted;\
                UINT8   entrySize;\
                UINT8   numOfWrapps;\
                UINT8   buffer[maxBufferEntries][maxSizeOfReport];\
            } bufferName##RAMBufferST;\
            extern bufferName##RAMBufferST bufferName##RAMBuffer;

#define DIAG_RESET_RAM_BUFFER(bufferName)                                           \
            memset(bufferName##RAMBuffer.buffer, 0, sizeof(bufferName##RAMBuffer.buffer));\
            bufferName##RAMBuffer.index = 0


#define DIAG_RAM_REPORT_FORMATTED_INDEX_2P(bufferName, param1, param2)      \
            if ( bufferName##RAMBuffer.index >= (bufferName##RAMBuffer.numOfEntries-3))                                                           \
            {\
                memset(bufferName##RAMBuffer.buffer, 0, sizeof(bufferName##RAMBuffer.buffer));\
                bufferName##RAMBuffer.index = 0;\
                bufferName##RAMBuffer.numOfWrapps++;\
            }\
            bufferName##RAMBuffer.buffer[bufferName##RAMBuffer.index][0] = (UINT8)param1; \
            bufferName##RAMBuffer.buffer[bufferName##RAMBuffer.index][1] = (UINT8)param2; \
            bufferName##RAMBuffer.index++


#else

#define DIAG_CREATE_RAM_FORMATTED_BUFFER(bufferName, maxBufferEntries, maxSizeOfReport)   \
            UINT8 bufferName##RAMBuffer[maxBufferEntries][maxSizeOfReport];               \
            UINT16 bufferName##RAMBufferIndex = 0;                                        \
            UINT16 bufferName##WrappedRAMBufferIndex = 0;          \
            const UINT8 bufferName##FormattedFlag = 1;                                    \
            const UINT16 bufferName##MaxReportSize = maxSizeOfReport;                     \
            const UINT16 bufferName##RAMBufferSize = maxBufferEntries


#define DIAG_REFERENCE_TO_RAM_BUFFER_FORMATTED(bufferName, size, maxSizeOfReport)   \
            extern UINT8 bufferName##RAMBuffer[size][maxSizeOfReport];            \
            extern UINT16 bufferName##RAMBufferIndex;        \
            extern UINT16 bufferName##WrappedRAMBufferIndex; \
            extern const UINT8 bufferName##FormattedFlag;    \
            extern const UINT16 bufferName##MaxReportSize;   \
            extern const UINT16 bufferName##RAMBufferSize


#define DIAG_RESET_RAM_BUFFER(bufferName)                                           \
            if (bufferName##FormattedFlag)                                          \
            {                                                                       \
                int i;                                                              \
                for ( i = 0; i < bufferName##RAMBufferSize; i++)                    \
                    memset(&bufferName##RAMBuffer[i], 0, bufferName##MaxReportSize);\
            }                                                                       \
            else                                                                    \
            {                                                                       \
                int i;                                                              \
                for ( i = 0; i < bufferName##RAMBufferSize; i++)                    \
                    memset(&bufferName##RAMBuffer[i], 0, 1);                        \
            }                                                                       \
            bufferName##RAMBufferIndex = 0


#define DIAG_RAM_REPORT_FORMATTED_INDEX_2P(bufferName, param1, param2)      \
            if ( bufferName##RAMBufferIndex >= (bufferName##RAMBufferSize-10))                                                           \
            {\
                memset(bufferName##RAMBuffer, 0, bufferName##MaxReportSize*bufferName##RAMBufferSize);\
                bufferName##RAMBufferIndex = 0;                                                                                     \
                bufferName##WrappedRAMBufferIndex++;\
            }\
            bufferName##RAMBuffer[bufferName##RAMBufferIndex][0] = (UINT8)param1; \
            bufferName##RAMBuffer[bufferName##RAMBufferIndex][1] = (UINT8)param2; \
            bufferName##RAMBufferIndex++

#endif /* 1/0 */
#endif /* DIAG_RAM_DEBUG_ENABLE */

#define DIAG_CREATE_RAM_BUFFER(bufferName, maxBufferEntries)       \
            UINT8 bufferName##RAMBuffer[maxBufferEntries];         \
            UINT16 bufferName##RAMBufferIndex = 0;                 \
			const UINT8 bufferName##FormattedFlag = 0;			   \
            const UINT16 bufferName##MaxReportSize = 1;			   \
            const UINT16 bufferName##RAMBufferSize = maxBufferEntries

#define DIAG_RAM_REPORT(bufferName, numID)                                 \
            if ( bufferName##RAMBufferIndex >= bufferName##RAMBufferSize)  \
                bufferName##RAMBufferIndex = 0;                            \
            bufferName##RAMBuffer[bufferName##RAMBufferIndex] = numID;     \
            bufferName##RAMBufferIndex++


#define DIAG_RAM_REPORT_BOOLEAN(bufferName, numID, onOff)                                    \
            if ( bufferName##RAMBufferIndex >= bufferName##RAMBufferSize)                    \
                bufferName##RAMBufferIndex = 0;                                              \
            bufferName##RAMBuffer[bufferName##RAMBufferIndex] = numID;                       \
			if ( (bufferName##RAMBufferIndex + 1) >= bufferName##RAMBufferSize)              \
            {                                                                                \
                bufferName##RAMBufferIndex = 0;                                              \
				bufferName##RAMBuffer[bufferName##RAMBufferIndex] = onOff;                   \
				bufferName##RAMBufferIndex++;												 \
            }                                                                                \
			else																			 \
            {                                                                                \
            bufferName##RAMBuffer[bufferName##RAMBufferIndex + 1] = onOff;                   \
            bufferName##RAMBufferIndex += 2;												 \
            }

#define DIAG_RAM_REPORT_FORMATTED(bufferName, reportRAMParams, sizeOfParams)                                                        \
            if ( bufferName##RAMBufferIndex >= bufferName##RAMBufferSize)                                                           \
                bufferName##RAMBufferIndex = 0;                                                                                     \
            memcpy(bufferName##RAMBuffer[bufferName##RAMBufferIndex], reportRAMParams, MIN(sizeOfParams,bufferName##MaxReportSize));\
            bufferName##RAMBufferIndex++

#define DIAG_RAM_REPORT_FORMATTED_INDEX(bufferName, param, paramIndex)                                                        \
            if ( bufferName##RAMBufferIndex >= bufferName##RAMBufferSize)                                                           \
                bufferName##RAMBufferIndex = 0;                                                                                     \
            bufferName##RAMBuffer[bufferName##RAMBufferIndex][paramIndex] = (UINT8)param; \
            bufferName##RAMBufferIndex++


#define DIAG_REFERENCE_TO_RAM_BUFFER(bufferName)             \
            extern UINT8 *bufferName##RAMBuffer;             \
            extern UINT16 bufferName##RAMBufferIndex;        \
			extern const UINT8 bufferName##FormattedFlag;	 \
			extern const UINT16 bufferName##MaxReportSize;   \
            extern const UINT16 bufferName##RAMBufferSize




#endif /*_DIAG_RAM_DEBUG_H_*/
