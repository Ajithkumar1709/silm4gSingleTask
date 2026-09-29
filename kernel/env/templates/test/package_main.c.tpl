/* ================================================================
File        : UserMain.c
Programmer	: ^PROGRAMMER
Description : Main entry file for ^PACKAGE_BASE/^PACKAGE package.
Create Date	: ^DATE
Notes       : This file is for testing purposes only.

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
================================================================= */

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

  return(0);
}

/*                        end of UserMain.c
------------------------------------------------------------------ */
