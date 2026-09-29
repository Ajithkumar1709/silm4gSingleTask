if(${MBTK_L503C_6C})
#####################
#L503C_6C
#####################
set(APP_RAM_ADD 0x7e181000)
set(APP_ROM_ADD 0x80361000)
elseif(${MBTK_L503CN_6C})
#####################
#L503CN_6C
#####################
set(APP_RAM_ADD 0x7e17c000)
set(APP_ROM_ADD 0x80361000)
elseif(${MBTK_L503C_6S}) 
#####################
#L503C_6S
#####################
set(APP_RAM_ADD 0x7e400000)
set(APP_ROM_ADD 0x805C6000)
elseif(${MBTK_L503CN_6S})
#####################
#L503CN_6S
#####################
set(APP_RAM_ADD 0x7e400000)
set(APP_ROM_ADD 0x805D5000)
elseif(${MBTK_L503C_6L})
#####################
#L503C_6L
##################### 
set(APP_RAM_ADD 0x7e119000)
set(APP_ROM_ADD 0x801CE000)
elseif(${MBTK_L505C_6C}) 
#####################
#L505C_6C
#####################
set(APP_RAM_ADD 0x7e14c000)
set(APP_ROM_ADD 0x80351000)
elseif(${MBTK_L505C_6L}) 
#####################
#L505C_6L
#####################	
set(APP_RAM_ADD 0x7e119000)
set(APP_ROM_ADD 0x801CE000)
elseif(${MBTK_L511C_6C}) 
#####################
#L511C_6C
#####################
set(APP_RAM_ADD 0x7e14c000)
set(APP_ROM_ADD 0x80318000)
elseif(${MBTK_L511C_6D}) 
#####################
#L511C_6D
#####################
set(APP_RAM_ADD 0x7e163000)
set(APP_ROM_ADD 0x80351000)
elseif(${MBTK_L511C_6S})
#####################
#L511C_6S
##################### 
set(APP_RAM_ADD 0x7e400000)
set(APP_ROM_ADD 0x805C6000)
elseif(${MBTK_L511CN_6C}) 
#####################
#L511CN_6C
#####################
set(APP_RAM_ADD 0x7e14c000)
set(APP_ROM_ADD 0x80383000)
elseif(${MBTK_L511AS_6D})
#####################
#L511AS_6D
##################### 
set(APP_RAM_ADD 0x7e460000)
set(APP_ROM_ADD 0x80408000)
elseif(${MBTK_L511CS_6D})
#####################
#L511CS_6D
##################### 
set(APP_RAM_ADD 0x7e460000)
set(APP_ROM_ADD 0x803FE000)
elseif(${MBTK_L511CN_6S}) 
#####################
#L511CN_6S
#####################
set(APP_RAM_ADD 0x7e400000)
set(APP_ROM_ADD 0x805C6000)
else()
message(FATAL_ERROR "no target project find...")
endif()