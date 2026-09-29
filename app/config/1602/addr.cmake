if(${MBTK_L503C_2L})
#####################
#L503C_2L
#####################
set(APP_RAM_ADD 0x7e116000)
set(APP_ROM_ADD 0x801CE000)
elseif(${MBTK_L503C_2S})
#####################
#L503C_2S
#####################
set(APP_RAM_ADD 0x7e206000)
set(APP_ROM_ADD 0x80260000)
elseif(${MBTK_L511C_2S})	
#####################
#L511C_2S
#####################
set(APP_RAM_ADD 0x7e208000)
set(APP_ROM_ADD 0x8035A000)
elseif(${MBTK_L511C_X2S})	
#####################
#L511C_X2S
#####################
set(APP_RAM_ADD 0x7e1fc000)
set(APP_ROM_ADD 0x80369000)
elseif(${MBTK_L511CN_2S})	
#####################
#L511CN_2S
#####################
set(APP_RAM_ADD 0x7e212000)
set(APP_ROM_ADD 0x80353000)
elseif(${MBTK_L511CN_2S_NF})	
#####################
#L511CN_2S_NF
#####################
set(APP_RAM_ADD 0x7e209000)
set(APP_ROM_ADD 0x802BD000)
elseif(${MBTK_L511C_2C})	
#####################
#L511C_2C
#####################
set(APP_RAM_ADD 0x7e119000)
set(APP_ROM_ADD 0x801C7000)
elseif(${MBTK_L511C_X2C})	
#####################
#L511C_X2C
#####################
set(APP_RAM_ADD 0x7e119000)
set(APP_ROM_ADD 0x801C7000)
elseif(${MBTK_L511EN_2S})	
#####################
#L511EN_2S
#####################
set(APP_RAM_ADD 0x7e1E1000)
set(APP_ROM_ADD 0x80349000)
elseif(${MBTK_L511E_2S})	
#####################
#L511E_2S
#####################
set(APP_RAM_ADD 0x7e1CB000)
set(APP_ROM_ADD 0x80341000)
else()
message(FATAL_ERROR "no target project find...")
endif()