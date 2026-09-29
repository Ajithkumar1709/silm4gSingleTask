@rem ------------------------------------------------------------
@rem (C) Copyright Mobiletek Ltd.
@rem All Rights Reserved
@rem ------------------------------------------------------------


set TARGET_PROJECT=L511C_5S
set TARGET_CHIPTYPE=M1605
set TARGET_RF=L511C_5

@rem Setting flash information
set ASR_PROJECT_NAME=ASR_CRANELRH_EVB
set ASR_PRODUCT_TYPE=CRANELRH_A0_04MB
set COMP_BAT=module_lteonly_buildcust_4mram_4mflash_craneLRH_single_sim_sms.bat

@rem Custom Name Config,example ZZD, GWSD,SHANLI,TCYUN, HAIER
@rem Default "TARGET_CUSTOM=NONE"
set TARGET_CUSTOM=NONE
set MBTK_GSM_SUPPORT=n
set MBTK_OPENCPU_SUPPORT=y
@rem CUSTOMER_NAME for open
set CUSTOMER_NAME=COMMON

set RELEASE_PROFILE_LIST[0]=ASR_CRANELRH_EVB

set mrule=%1rule

call makerule.bat %mrule%