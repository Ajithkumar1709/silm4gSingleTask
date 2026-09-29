/* ================================================================
File        : ^FILE
Programmer	: ^PROGRAMMER
Description : Group linker definitions file for ^GROUP_BASE/^GROUP group.
Create Date	: ^DATE
Notes       : This file is for testing purposes only.

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
================================================================= */

/* Include groups ldfs */
^GROUP_LIST(#include "LIST_ELEMENT.ldf")

/* Include packages ldfs */
^PACKAGE_LIST(#include "LIST_ELEMENT.ldf")

#define ^GROUP_Code_INsec                        \
    ^GROUP_LIST(LIST_ELEMENT_Code_INsec)         \
    ^PACKAGE_LIST(LIST_ELEMENT_Code_INsec)       \
    /* end of ^GROUP_Code_INsec */

#define	^GROUP_Code_OUTsec ^GROUP_Code_OUT       \
 {                                               \
	  INPUT_SECTION_ALIGN(2)                     \
	  ^GROUP_Code_INsec                          \
 }

#define ^GROUP_Data_INsec                        \
    ^GROUP_LIST(LIST_ELEMENT_Data_INsec)         \
    ^PACKAGE_LIST(LIST_ELEMENT_Data_INsec)       \
    /* end of ^GROUP_Data_INsec */

#define	^GROUP_Data_OUTsec ^GROUP_Data_OUT       \
 {                                               \
	  ^GROUP_Data_INsec                          \
 }
