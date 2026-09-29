/* ===========================================================================
File        : ^FILE
Programmer	: ^PROGRAMMER
Description : Software interface file for the ^GROUP_BASE/^GROUP group.
Create Date	: ^DATE
Notes       : 

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
=========================================================================== */

#if !defined(_^UP_GROUP_H_)
#define _^UP_GROUP_H_

/* ^CAP_GROUP group interface macros */

/* ^CAP_GROUP group interface types */

/* ^CAP_GROUP group system interface SAPs */
void ^CAP_GROUPPowerUp( void );
void ^CAP_GROUPInit ( void );
void ^CAP_GROUPTerminate ( void );
void ^CAP_GROUPReset ( void );
void ^CAP_GROUPGetVersion ( void * Ptr );

/* ^CAP_GROUP group service interface SAPs */


#endif /* _^UP_GROUP_H_ */