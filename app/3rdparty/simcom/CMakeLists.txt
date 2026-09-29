app_add_library(simcom)

# add_definitions(-DFEATURE_SIMCOM_MSSL)

if(MBTK_SIMCOM_BUILD_WITH_SOURCE)
set(BUILD_SC_SYSTEM ON)
endif()

if(BUILD_SC_SYSTEM)
    add_subdirectory(sc_system)
    add_dependencies(simcom sc_system) 
endif()

add_subdirectory(sc_demo)
add_dependencies(simcom sc_demo)

app_source(
    empty_file.c
)
