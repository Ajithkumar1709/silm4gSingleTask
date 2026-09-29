/* ================================================================
File        : ^FILE
Programmer	: ^PROGRAMMER
Description : Target linker definitions file for ^TARGET_BASE/^TARGET ^TARGET_TYPE.
Create Date	: ^DATE
Notes       : 

Copyright (c) ^YEAR Intel CCD. All Rights Reserved
================================================================= */

#include "gbl_config.h"
#include "MSACore_.h"
#include "HWDefs_.h"

/* Include groups ldfs */
^GROUP_LIST(#include "LIST_ELEMENT.ldf")

/* Include packages ldfs */
^PACKAGE_LIST(#include "LIST_ELEMENT.ldf")

#define TARGET_SECTIONS                                   \
	/* Included groups Code */                            \
    ^GROUP_LIST(LIST_ELEMENT_Code_OUTsec > PROGRAM )      \
	/* Included packages Code */                          \
    ^PACKAGE_LIST(LIST_ELEMENT_Code_OUTsec > PROGRAM )    \
	/* Included groups Code */                            \
    ^GROUP_LIST(LIST_ELEMENT_Data_OUTsec > DATA_B )       \
	/* Included packages Code */                          \
    ^PACKAGE_LIST(LIST_ELEMENT_Data_OUTsec > DATA_B )     \
                                                          \
    /* end of TARGET_SECTIONS */
												          
#include "^HW_PLATFORM.ldf"
