/* ===========================================================================
File        : ^FILE
Programmer	: ^PROGRAMMER
Description : Software interface file for the ^PACKAGE_BASE/^PACKAGE package.
Create Date	: ^DATE
Notes       : 

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
=========================================================================== */

#if !defined(_^UP_PACKAGE_H_)
#define _^UP_PACKAGE_H_

/* ^CAP_PACKAGE package interface macros */

/* ^CAP_PACKAGE package interface types */

/* ^CAP_PACKAGE package system interface SAPs */
void ^CAP_PACKAGEPowerUp( void );
void ^CAP_PACKAGEInit ( void );
void ^CAP_PACKAGETerminate ( void );
void ^CAP_PACKAGEReset ( void );
void ^CAP_PACKAGEGetVersion ( void * Ptr );

/* ^CAP_PACKAGE package service interface SAPs */


#endif /* _^UP_PACKAGE_H_ */






