/* ================================================================
File        : UserMain.c
Programmer	: ^PROGRAMMER
Description : Main entry file for ^MODULE_BASE/^MODULE ^TARGET_TYPE.
Create Date	: ^DATE
Notes       : 

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
================================================================= */

/* Include groups APIs */
^GROUP_LIST(#include "LIST_ELEMENT.h")

/* Include packages APIs */
^PACKAGE_LIST(#include "LIST_ELEMENT.h")

/* -----------------------------------------------------------------
Function    : HWPowerUp
Description : Function to initialize basic HW. 
              It runs before main function as a part of the start-up code.
Inputs		: None.
Outputs		: None.
Return Value: None.
Notes       : 
----------------------------------------------------------------- */
void HWPowerUp(void) {
  return;
}

/* -----------------------------------------------------------------
Function    : main
Description : Main code entry point
Inputs		: 
Outputs		: 
Return Value: 
Notes       : 
----------------------------------------------------------------- */
// Attention !!!
// In case the target uses Operating system, then user can't use main function
// as an entry point for his program. It should be probably be a UserApplicationFunc function
int main ( void ) {

  // PowerUp the modules
  ^GROUP_LIST(CAP_LIST_ELEMENTPowerUp();)
  ^PACKAGE_LIST(CAP_LIST_ELEMENTPowerUp();)

  // Init the modules
  ^GROUP_LIST(CAP_LIST_ELEMENTInit();)
  ^PACKAGE_LIST(CAP_LIST_ELEMENTInit();)

  // Reset the modules
  ^GROUP_LIST(CAP_LIST_ELEMENTReset();)
  ^PACKAGE_LIST(CAP_LIST_ELEMENTReset();)
  
  return(0);
}
