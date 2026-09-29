element * CHECKEDOUT
 
# FULL ENVIRONMENT SPECIFICATION FOR
#     Tavor  &&   Hermon              System
#=========================================================

# TAVOR
element /tavor/env/... MAIN-FS.00.30      -nco
element /tavor/Arbel/...  	 TAVOR_ENV_01.125 -nco
#element /trustedboot/...  WTPTP_TAVOR_3_0_09_RC3 -nco

element /tavor_obm/app_bin/...   PTK_OBM_MAIN_00.029.6731 	 -nco
element /tavor_obm/Binaries/...  PTK_OBM_MAIN_00.029.1792 	 -nco
element /tavor_obm/DKB/...  	 PTK_OBM_MAIN_00.029.1955 	 -nco
element /tavor_obm/OBM/...  	 PTK_OBM_MAIN_00.029.9342 	 -nco
element /tavor_obm/TBB/...  	 PTK_OBM_MAIN_00.029.6734 	 -nco
element /tavor_obm/WTPTP/...  	 PTK_OBM_MAIN_00.029.1951 	 -nco
element /tavor_obm/RBOOT/...    Tavor_Rboot-01.00.31   -nco

# GENLIB
element /genlib/... GENLIB_1.2.1 -nco

#3G_PS
element /3g_ps/...  PS-R7.00.092.7425 -nco

# PCAC                     
element /pcac/...   PCAC_07.001.5707 -nco

# SAC
element /sac/...    SAC-07.00.07.3802  -nco
 
# L1P
element /l1p_fw_rls/...  L1P.Modem.036.F006.3520 	 -nco

element /aplp/...  	 L1P.Modem.036.V008.R011.C008.S006.61 	 -nco
element /CRD/...  	 L1P.Modem.036.V008.R011.C008.S006.7738	 -nco
element /drat/...  	 L1P.Modem.036.V008.R011.C008.S006.9203 	 -nco
element /gplc/...  	 L1P.Modem.036.V008.R011.C008.S006.1783 	 -nco
element /l1tw/...  	 L1P.Modem.036.V008.R011.C008.S006.7735	 -nco
element /SPI/...  	 L1P.Modem.036.V008.R011.C008.S006.1787 	 -nco

# AUDIO
element  /aud_sw/...   HTA.00.252  -nco 

# NUCLEUS
element /os/nu_xscale/src   -none
element /os/nu_xscale/...  NU1.15.17 -nco

# OSX
element /os/osx/...  OSX_01.02    -nco

# OSA
element /os/osa/... OSA-04.00.040.3286 -nco

# CBA and PrePass
element   /env/...  CBA01.04-180.1.3394   -nco

# UNIFIED DIAG and PREPASS
element /diag/...  	 DIAG-05.00.187.9231  -nco
element /prepass/...  	 DIAG-05.00.187.1821  -nco

# Platform
element /CrossPlatformSW/... HTP06.310.2223  -nco
element /csw/...  	     HTP06.310.7184  -nco
element /hal/...  	     HTP06.310.6106  -nco
element /hop/...  	     HTP06.310.8319  -nco
element /softutil/...  	     HTP06.310.1069  -nco
element /tavor_rtos/...      HTP06.310.6645  -nco
element /tools/...  	     HTP06.310.530  -nco


# DLM
element /aplp_etc/DLM/... DLM_00.01.40  -nco


#element /lib/... /main/LATEST/

# CONSTANT_PART: End
element -dir * /main/0

load \3g_ps
load \CRD
load \CrossPlatformSW
load \aplp
load \aplp_etc
load \aud_sw
load \csw
load \diag
load \drat
load \env
load \genlib
load \gplc
load \hal
load \hop
load \l1p_fw_rls
load \l1tw
load \os
load \pcac
load \prepass
load \sac
load \softutil
load \tavor
load \tavor_obm
load \tavor_rtos
load \tools
load \SPI


