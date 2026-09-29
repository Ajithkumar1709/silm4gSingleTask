/*------------------------------------------------------------
(C) Copyright [2006-2008] Marvell International Ltd.
All Rights Reserved
------------------------------------------------------------*/

/* ===========================================================================
File        : fsm_app.h
Description : App interface file for the
              genlib/fsm package.

Notes       : Modify the types and the SAP's as required.

Copyright (c) 2001 Intel CCD. All Rights Reserved
=========================================================================== */

#if !defined(_FSM_APP_H_)
#define _FSM_APP_H_

#include "fsm_types.h"

/* FSM Package - App Interface SAPs */
BOOL fsmAppInitialize ( FSMPtr fsm, FSMStateTable table,
                        UINT8 num_state, UINT8 num_event, UINT8 num_action,
                        UINT8 eventQ_depth, UINT8 eventQ_element_size, OSAPoolRef fsmMemPoolRef,
                        FSMState initial_state, FSMActionFuncTable action_table,
                        void* user_parms );

void fsmAppProcessEvent ( FSMPtr fsm, FSMEvent event );
void fsmAppProcessEventWithParms ( FSMPtr fsm, FSMEvent event,
                                   void* parm_struct, UINT8 size );

FSMEvent fsmAppGetCurrentEvent ( FSMPtr fsm );
void*    fsmAppGetCurrentEventParms ( FSMPtr fsm );
FSMState fsmAppGetCurrentState ( FSMPtr fsm );
#define  fsmAppGetUserParms(fsm) (fsm->user_parms)

BOOL fsmAppRelease ( FSMPtr fsm );
void fsmAppSetConditionalState ( FSMPtr fsm, FSMState cond_state );
void fsmAppSetTraceInfo ( FSMPtr fsm, const char* fsmName, UINT8 fsmId,
                          const char* stateTable[], const char* eventTable[] );

/* FSM App User Macros */

/* --------------------------------------------------------------------
 * The macro MAKEFSMTable is used to declare a FSM state table. 
 * The user provides the name of the table, the total number of states 
 * and the total number of events.
 *
 * Example Usage:
 * MAKEFSMTable(tableName, numStates, numInputs) =
 *   {  
 *     State 0  
 *     {    
 *       {nextState, action},  Input 0    
 *       {nextState, action},  Input 1
 *            :    
 *       {nextState, action}   Input "numInputs - 1"
 *     },
 *        :
 *        : 
 *     State "numStates - 1"  
 *     {
 *       {nextState, action},  Input 0
 *       {nextState, action},  Input 1 
 *            :    
 *       {nextState, action}   Input "numInputs - 1"
 *     }
 *   };
 *
 * --------------------------------------------------------------------*/
#define MAKEFSMTable(tableName,numStates,numInputs) \
static const UINT8 tableName[numStates][numInputs][2]


#endif /* _FSM_APP_H_ */

/*                      end of fsm_app.h
--------------------------------------------------------------------------- */









