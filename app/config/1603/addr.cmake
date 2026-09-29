if(${MBTK_L501E_3E})
#####################
#L501E_3E
#####################
set(APP_RAM_ADD 0x7e969000)
set(APP_ROM_ADD 0x806BD000)
elseif(${MBTK_L501E_3S})
#####################
#L501E_3S
#####################
set(APP_RAM_ADD 0x7e9ff000)
set(APP_ROM_ADD 0x80556000)
elseif(${MBTK_L501E_3SKP})
#####################
#L501E_3SKP
#####################
set(APP_RAM_ADD 0x7e969000)
set(APP_ROM_ADD 0x804F2000)
elseif(${MBTK_L503E_3S})
#####################
#L503E_3S
#####################
set(APP_RAM_ADD 0x7e9b8000)
set(APP_ROM_ADD 0x80562000)
elseif(${MBTK_L503E_3C})
#####################
#L503E_3C
#####################
set(APP_RAM_ADD 0x7e3b7000)
set(APP_ROM_ADD 0x8058E000)
elseif(${MBTK_L503C_3E})
#####################
#L503C_3E
#####################
set(APP_RAM_ADD 0x7e730000)
set(APP_ROM_ADD 0x806BD000)
elseif(${MBTK_L505C_3E})	
#####################
#L505C_3E
#####################
set(APP_RAM_ADD 0x7e600000)
set(APP_ROM_ADD 0x80CF2000)
elseif(${MBTK_L510C_3S})
#####################
#L510C_3S
#####################
set(APP_RAM_ADD 0x7e969000)
set(APP_ROM_ADD 0x804F2000)
elseif(${MBTK_L510CN_3S})
#####################
#L510CN_3S
#####################
set(APP_RAM_ADD 0x7e969000)
set(APP_ROM_ADD 0x80567000)
elseif(${MBTK_L510E_3S})
#####################
#L510E_3S
#####################
set(APP_RAM_ADD 0x7e959100)
set(APP_ROM_ADD 0x804F2000)
elseif(${MBTK_L510LAN_3S})
#####################
#L510LAN_3S
#####################
set(APP_RAM_ADD 0x7e969000)
set(APP_ROM_ADD 0x80532000)
elseif(${MBTK_L510E_3C})
#####################
#L510E_3C
#####################
set(APP_RAM_ADD 0x7e357000)
set(APP_ROM_ADD 0x80598000)
elseif(${MBTK_L510EN_3C})
#####################
#L510EN_3C
#####################
set(APP_RAM_ADD 0x7e357000)
set(APP_ROM_ADD 0x805AE000)
else()
message(FATAL_ERROR "no target project find...")
endif()