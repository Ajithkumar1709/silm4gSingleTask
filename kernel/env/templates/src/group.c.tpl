/* ===========================================================================
File        : ^FILE
Programmer	: ^PROGRAMMER
Description : Implementation file for the software interface
              of the ^GROUP_BASE/^GROUP group.
Create Date	: ^DATE
Notes       : 

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
=========================================================================== */

#include "^GROUP_config.h"
#include "^GROUP.h"

// Included groups APIs
^GROUP_LIST(#include "LIST_ELEMENT.h")

// Included packages APIs
^PACKAGE_LIST(#include "LIST_ELEMENT.h")

/* -------------------------------------------------------------------------------------------------
Function Name:	^CAP_GROUPPowerUp
Description:	Performs power-up process of the ^GROUP group
Inputs:		    None.
Outputs:        None.
Return Value:	void
Notes:		    
--------------------------------------------------------------------------------------------------- */
void ^CAP_GROUPPowerUp ( void ) {

  ^GROUP_LIST(CAP_LIST_ELEMENTPowerUp();)
  ^PACKAGE_LIST(CAP_LIST_ELEMENTPowerUp();)
  return;
}

/* -------------------------------------------------------------------------------------------------
Function Name:	^CAP_GROUPInit
Description:	Perform initialization of the ^GROUP group
Inputs:		    None.
Outputs:        None.
Return Value:	void
Notes:		    
--------------------------------------------------------------------------------------------------- */
void ^CAP_GROUPInit ( void ) {
  ^GROUP_LIST(CAP_LIST_ELEMENTInit();)
  ^PACKAGE_LIST(CAP_LIST_ELEMENTInit();)
  return;
}

/* -------------------------------------------------------------------------------------------------
Function Name:	^CAP_GROUPTerminate
Description:	Perform termination of the ^GROUP group
Inputs:		    None.
Outputs:        None.
Return Value:	void
Notes:		    
--------------------------------------------------------------------------------------------------- */
void ^CAP_GROUPTerminate ( void ) {
  ^GROUP_LIST(CAP_LIST_ELEMENTTerminate();)
  ^PACKAGE_LIST(CAP_LIST_ELEMENTTerminate();)
  return;
}

/* -------------------------------------------------------------------------------------------------
Function Name:	^CAP_GROUPReset
Description:	Resets termination of the ^GROUP group
Inputs:		    None.
Outputs:        None.
Return Value:	void
Notes:		    
--------------------------------------------------------------------------------------------------- */
void ^CAP_GROUPReset ( void ) {
  ^GROUP_LIST(CAP_LIST_ELEMENTReset();)
  ^PACKAGE_LIST(CAP_LIST_ELEMENTReset();)
  return;
}

/* -------------------------------------------------------------------------------------------------
Function Name:	^CAP_GROUPGetVersion
Description:	Returns the version of the ^GROUP group
Inputs:		    
Outputs:     
Return Value:	void
Notes:		    The GetVersion protocol to be defined
--------------------------------------------------------------------------------------------------- */
void ^CAP_GROUPGetVersion ( void * Ptr ) {
  ^GROUP_LIST(CAP_LIST_ELEMENTGetVersion(0);)
  ^PACKAGE_LIST(CAP_LIST_ELEMENTGetVersion(0);)
  return;
}

/*                   end of ^FILE
--------------------------------------------------------------------------- */






