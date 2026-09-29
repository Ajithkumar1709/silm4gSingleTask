/* ================================================================
File        : ^FILE
Programmer	: ^PROGRAMMER
Description : Package linker definitions file for ^PACKAGE_BASE/^PACKAGE package.
Create Date	: ^DATE
Notes       : This file is for testing purposes only.

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
================================================================= */

#define ^PACKAGE_Code_INsec 

#define	^PACKAGE_Code_OUTsec ^PACKAGE_Code_OUT    \
 {                              \
	  INPUT_SECTION_ALIGN(2)    \
	  ^PACKAGE_Code_INsec       \
 }

#define ^PACKAGE_Data_INsec

#define	^PACKAGE_Data_OUTsec ^PACKAGE_Data_OUT    \
 {                              \
	  ^PACKAGE_Data_INsec       \
 }

