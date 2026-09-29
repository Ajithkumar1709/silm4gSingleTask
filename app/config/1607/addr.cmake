if(${MBTK_L511CN_7S})
#####################
#L511CN_7S
#####################
set(APP_RAM_ADD 0x7e182800)
set(APP_ROM_ADD 0x80393000)
else()
message(FATAL_ERROR "no target project find...")
endif()