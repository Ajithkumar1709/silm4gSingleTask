# INTEL CONFIDENTIAL
# Copyright 2006 Intel Corporation All Rights Reserved. 
# The source code contained or described herein and all documents related to the source code ("Material") are owned 
# by Intel Corporation or its suppliers or licensors. Title to the Material remains with Intel Corporation or 
# its suppliers and licensors. The Material contains trade secrets and proprietary and confidential information of 
# Intel or its suppliers and licensors. The Material is protected by worldwide copyright and trade secret laws and 
# treaty provisions. No part of the Material may be used, copied, reproduced, modified, published, uploaded, posted, 
# transmitted, distributed, or disclosed in any way without Intel’s prior express written permission.
# 
# No license under any patent, copyright, trade secret or other intellectual property right is granted to or 
# conferred upon you by disclosure or delivery of the Materials, either expressly, by implication, inducement, 
# estoppel or otherwise. Any license under such intellectual property rights must be express and approved by 
# Intel in writing.
# 
# Unless otherwise agreed by Intel in writing, you may not remove or alter this notice or any other notice embedded
# in Materials by Intel or Intel’s suppliers or licensors in any way.

# GENLIB 1.2.0

element -dir /genlib	GENLIB_VOB_1.0.0

element -dir /genlib/doc 				GENLIB_DOC_DIR_1.0.0
element -file /genlib/doc/Genlib_Release_Notes.doc	FL_GENLIB_RELEASE_NOTES_1.0.0
element -dir /genlib/env				GENLIB_ENV_DIR_1.0.0
element -file /genlib/env/genlib_version.h		FL_GENLIB_VERSION_1.0.0
element -file /genlib/env/environment.cs		FL_GENLIB_ENVIRONMENT_1.0.0
element -file /genlib/env/LabelGenlib.bat		FL_GENLIB_LABELER_1.0.0

element /genlib/genlib/...	GP_GENLIB_1.1.0
element /genlib/fsm/...		PK_FSM_2.1.0
element /genlib/min_max/...	PK_MIN_MAX_1.0.0
element /genlib/qmgr/...	PK_QMGR_1.0.0