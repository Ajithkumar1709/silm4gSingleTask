/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : fsm_types.h
Description : Data types file for the genlib/fsm package

Notes       : 

Copyright (c) 2001 Intel CCD. All Rights Reserved
=========================================================================== */

#if !defined(_FSM_TYPES_H_)
#define _FSM_TYPES_H_

#include "gbl_types.h"
#include "osa.h"

/* ---------------------------------------------------------------------------
Constant Definitions - Used in state table declarations
--------------------------------------------------------------------------- */
#define	NO_ACTION               0xFE
#define	UNEXPECTED_EVENT_ACTION 0xFF
#define	CONDITIONAL_STATE       0xFF


/* ---------------------------------------------------------------------------
Interface Types
--------------------------------------------------------------------------- */
typedef UINT8 FSMState;
typedef UINT8 FSMEvent;
typedef UINT8 FSMAction;


/* ---------------------------------------------------------------------------
Struct name : FsmTBLEvent
Description : FSM Event Queue element
Notes       : 
--------------------------------------------------------------------------- */
typedef struct
{
  UINT8*   plist;
  FSMEvent event;
} FSMTBLEvent;

/* ---------------------------------------------------------------------------
Other Useful Typedef's
--------------------------------------------------------------------------- */
typedef const UINT8* FSMStateTable;
typedef struct FSMDescriptorStruct FSMDescriptor;
typedef FSMDescriptor* FSMPtr;
typedef BOOL (*FSMActionFunc) (FSMPtr fsm);
typedef const FSMActionFunc* FSMActionFuncTable;


/* ---------------------------------------------------------------------------
Struct name : FSMDescriptorStruct
Description : FSM Descriptor Structure
Notes       : 
--------------------------------------------------------------------------- */
struct FSMDescriptorStruct
{
  FSMState  state;                  /* Current State      */
  FSMState  conditional_state;      /* Conditional State  */

  FSMState  num_state;              /* Number of States   */
  FSMEvent  num_event;              /* Number of Events   */
  FSMAction num_action;             /* Number of Actions  */

  FSMStateTable state_table;        /* State Table        */
  UINT16        state_size;         /* State Entry Size   */
  UINT16        event_size;         /* Event Entry Size   */

  FSMTBLEvent* eventQ;              /* Event Queue                         */
  OSAPoolRef   fsmMemPool;          /* MemPool to allocate Event Q storage */
  UINT8        eventQ_depth;        /* Event Queue depth        */
  UINT8        eventQ_element_size; /* Event Queue element size	*/
  UINT8        put_index;           /* Put Index for Q          */
  UINT8        get_index;           /* Get Index for Q          */
  UINT8        num_in_queue;        /* Current number of entries in the queue */
  FSMTBLEvent  current_event;       /* Current Event and Parameters */

  /* Ptr to Action Handler Function Table */
  FSMActionFunc* action_table;

  /* Instance Related User Parameters */
  void*       user_parms;

  /* Tracing parameters */
#ifdef FSM_TRACING
  UINT8 id;
  BOOL  trace_enabled;

  const char* fsmName;
  const char** stateNameTable;
  const char** eventNameTable;
#endif  /* FSM_TRACING */
};



#endif /* _FSM_TYPES_H_ */


/*                      end of fsm_types.h
--------------------------------------------------------------------------- */




