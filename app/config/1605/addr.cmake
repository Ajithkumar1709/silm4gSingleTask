if(${MBTK_L511C_5S})
#####################
#L511C_5S
#####################
set(APP_RAM_ADD 0x7e1b2000)
set(APP_ROM_ADD 0x802CF000)
elseif(${MBTK_L511C_5SK})
#####################
#L511C_5SK
#####################
set(APP_RAM_ADD 0x7e1dc000)
set(APP_ROM_ADD 0x80362000)
elseif(${MBTK_L511C_5C})
#####################
#L511C_5C
#####################
set(APP_RAM_ADD 0x7e114000)
set(APP_ROM_ADD 0x801B6000)
else()
message(FATAL_ERROR "no target project find...")
endif()