@rem ------------------------------------------------------------
@rem (C) Copyright [2006-2008] Marvell International Ltd.
@rem All Rights Reserved
@rem ------------------------------------------------------------

REM INTEL CONFIDENTIAL
REM Copyright 2006 Intel Corporation All Rights Reserved. 
REM The source code contained or described herein and all documents related to the source code ("Material") are owned 
REM by Intel Corporation or its suppliers or licensors. Title to the Material remains with Intel Corporation or 
REM its suppliers and licensors. The Material contains trade secrets and proprietary and confidential information of 
REM Intel or its suppliers and licensors. The Material is protected by worldwide copyright and trade secret laws and 
REM treaty provisions. No part of the Material may be used, copied, reproduced, modified, published, uploaded, posted, 
REM transmitted, distributed, or disclosed in any way without Intel's prior express written permission.

REM No license under any patent, copyright, trade secret or other intellectual property right is granted to or 
REM conferred upon you by disclosure or delivery of the Materials, either expressly, by implication, inducement, 
REM stopped or otherwise. Any license under such intellectual property rights must be express and approved by 
REM Intel in writing.

REM Unless otherwise agreed by Intel in writing, you may not remove or alter this notice or any other notice embedded
REM in Materials by Intel or Intel's suppliers or licensors in any way.

REM Batch file to create and apply the PCA Components label

echo 

REM Create the label

cd ..
cleartool mklbtype -nc %1

REM Apply the labels

cd ..
cleartool mklabel %1 genlib

cd genlib
cleartool mklabel %1 fsm
cleartool mklabel %1 min_max
cleartool mklabel -recurse %1 doc
cleartool mklabel -recurse %1 env
cleartool mklabel %1 qmgr
cleartool mklabel %1 genlib


cd fsm
cleartool mklabel -recurse %1 build
cleartool mklabel -recurse %1 inc
cleartool mklabel -recurse %1 src
cleartool mklabel %1 DIRS

cd ..\min_max
cleartool mklabel -recurse %1 build
cleartool mklabel -recurse %1 inc
cleartool mklabel -recurse %1 src
cleartool mklabel %1 doc
cd doc
cleartool mklabel %1 release_notes.txt

cd ..\..\qmgr
cleartool mklabel -recurse %1 build
cleartool mklabel -recurse %1 inc
cleartool mklabel -recurse %1 src
cleartool mklabel %1 doc
cd doc
cleartool mklabel %1 release_notes.txt

cd ..\..\genlib
cleartool mklabel -recurse %1 build
cleartool mklabel -recurse %1 inc
cleartool mklabel -recurse %1 src
cleartool mklabel %1 doc
cd doc
cleartool mklabel %1 Genlib_Group_Release_Notes.doc