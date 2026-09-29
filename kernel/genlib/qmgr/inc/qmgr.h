/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ============================================================================
File Name   : qmgr.h
Description : Circular Queue manager interface definition.

Contact     : Barrie Cassidy
Link        : copied from components/isolib/inc /main/2 
Notes       : name changes from iqmgr.h to qmrg.h

Copyright (c) 2001 Intel Corp. All Rights Reserved
============================================================================ */

#ifndef _QMGR_H_
#define _QMGR_H_ 1

typedef struct
{
  /* Static queue descriptors */
  UINT8* q;
  UINT16 numRecords;
  UINT16 recordSize;

  /* Dynamic queue descriptors */
  UINT16 putIndex;
  UINT16 getIndex;
  UINT16 numInQueue;

  UINT16 scanIndex;
  UINT16 numToScan;
} QDesc;

/* Returns FALSE if queue is full */
BOOL qPut (QDesc* qd, void* data);

/* Returns the number of records enqueued */ 
UINT16 qBlockPut (QDesc* qd, void* data, UINT16 recordsToPut);

/* Returns FALSE if queue is empty */
BOOL qGet (QDesc* qd, void* data);

/* Returns number of records retrieved */
UINT16 qBlockGet (QDesc* qd, void* data, UINT16 recordsToGet);

/* Returns a pointer to the first entry without dequing the record */
void* qGetRef (QDesc* qd);

/* Removes the first entry */
BOOL qDelete (QDesc* qd);

/* Returns number of records currently in the queue */
UINT16 qNum (QDesc* qd);

/* Returns number of unoccupied records in the queue */
UINT16 qRoom (QDesc* qd);

void qFlush (QDesc* qd);

void qResetScan (QDesc* qd, UINT16 start);

void* qScan (QDesc* qd);

void qInit (QDesc* qd, void* q, UINT16 numRecords, UINT16 recordSize);

#endif /* _QMGR_H_ */
