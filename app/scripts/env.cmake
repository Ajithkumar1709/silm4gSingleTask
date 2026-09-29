

file(TO_CMAKE_PATH "${TOOLCHAIN_PREFIX}" TOOLCHAIN_PREFIX)
MESSAGE(STATUS "TOOLCHAIN_PREFIX: ${TOOLCHAIN_PREFIX}")

# Append current directory to CMAKE_MODULE_PATH for making device specific cmake modules visible
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Target definition
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm)

#---------------------------------------------------------------------------------------
# Set toolchain paths
#---------------------------------------------------------------------------------------
set(TOOLCHAIN arm-none-eabi)
if(NOT DEFINED TOOLCHAIN_PREFIX)
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
        set(TOOLCHAIN_PREFIX "/usr")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)
        set(TOOLCHAIN_PREFIX "/usr/local")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
        message(STATUS "Please specify the TOOLCHAIN_PREFIX !\n For example: -DTOOLCHAIN_PREFIX=\"C:/Program Files/GNU Tools ARM Embedded\" ")
    else()
        set(TOOLCHAIN_PREFIX "/usr")
        message(STATUS "No TOOLCHAIN_PREFIX specified, using default: " ${TOOLCHAIN_PREFIX})
    endif()
endif()

set(CMAKE_ASM_OUTPUT_EXTENSION .o)
set(CMAKE_C_OUTPUT_EXTENSION .o)
set(CMAKE_CXX_OUTPUT_EXTENSION .o)

set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)
set(CMAKE_EXECUTABLE_SUFFIX_C .elf)
set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)

set(CMAKE_STATIC_LIBRARY_PREFIX lib)
set(CMAKE_STATIC_LIBRARY_SUFFIX .a)

set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_PREFIX}/bin)
set(TOOLCHAIN_INC_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/include)


# Set system depended extensions
if(WIN32)
    set(TOOLCHAIN_EXT ".exe" )
else()
    set(TOOLCHAIN_EXT "" )
endif()



# Perform compiler test with static library
#set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
#---------------------------------------------------------------------------------------
# Set compiler/linker flags
#---------------------------------------------------------------------------------------

# Object build options
# -O0                   No optimizations, reduce compilation time and make debugging produce the expected results.
# -mthumb               Generat thumb instructions.
# -fno-builtin          Do not use built-in functions provided by GCC.
# -Wall                 Print only standard warnings, for all use Wextra
# -ffunction-sections   Place each function item into its own section in the output file.
# -fdata-sections       Place each data item into its own section in the output file.
# -fomit-frame-pointer  Omit the frame pointer in functions that don鈥檛 need one.
# -mabi=aapcs           Defines enums to be a variable sized type.
#set(OBJECT_GEN_FLAGS "-O0 -mthumb -fno-builtin -Wall -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs")


# -Wl,--gc-sections     Perform the dead code elimination.
# --specs=nano.specs    Link with newlib-nano.
# --specs=nosys.specs   No syscalls, provide empty implementations for the POSIX system calls.
#set(CMAKE_EXE_LINKER_FLAGS "-Wl,--gc-sections --specs=nano.specs --specs=nosys.specs -mthumb -mabi=aapcs -Wl,-Map=${CMAKE_PROJECT_NAME}.map" CACHE INTERNAL "Linker options")

#---------------------------------------------------------------------------------------
# Set debug/release build configuration Options
#---------------------------------------------------------------------------------------

# Options for DEBUG build
# -Og   Enables optimizations that do not interfere with debugging.
# -g    Produce debugging information in the operating system鈥檚 native format.
#set(CMAKE_C_FLAGS_DEBUG "-Og -g" CACHE INTERNAL "C Compiler options for debug build type")
#set(CMAKE_CXX_FLAGS_DEBUG "-Og -g" CACHE INTERNAL "C++ Compiler options for debug build type")
#set(CMAKE_ASM_FLAGS_DEBUG "-g" CACHE INTERNAL "ASM Compiler options for debug build type")
#set(CMAKE_EXE_LINKER_FLAGS_DEBUG "" CACHE INTERNAL "Linker options for debug build type")

# Options for RELEASE build
# -Os   Optimize for size. -Os enables all -O2 optimizations.
# -flto Runs the standard link-time optimizer.
#set(CMAKE_C_FLAGS_RELEASE "-Os -flto" CACHE INTERNAL "C Compiler options for release build type")
#set(CMAKE_CXX_FLAGS_RELEASE "-Os -flto" CACHE INTERNAL "C++ Compiler options for release build type")
#set(CMAKE_ASM_FLAGS_RELEASE "" CACHE INTERNAL "ASM Compiler options for release build type")
#set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-flto" CACHE INTERNAL "Linker options for release build type")


#---------------------------------------------------------------------------------------
# Set compilers
#---------------------------------------------------------------------------------------
set(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT} CACHE INTERNAL "C Compiler")
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-g++${TOOLCHAIN_EXT} CACHE INTERNAL "C++ Compiler")
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT} CACHE INTERNAL "ASM Compiler")

set(CMAKE_AR ${TOOLCHAIN_BIN_DIR}/$ENV{AR})
set(CMAKE_C_AR ${TOOLCHAIN_BIN_DIR}/$ENV{AR})
set(CMAKE_LINKER ${TOOLCHAIN_BIN_DIR}/$ENV{LD})
set(CMAKE_C_LINKER ${CMAKE_LINKER})
set(CMAKE_CXX_LINKER ${CMAKE_LINKER})
set(CMAKE_OBJCOPY ${TOOLCHAIN_BIN_DIR}/$ENV{FROMELF})
set(CMAKE_RANLIB ${TOOLCHAIN_BIN_DIR}/$ENV{RANLIB})

set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PREFIX}/bin ${CMAKE_PREFIX_PATH})
# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories:NEVER:ONLY
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)

set(CMAKE_C_USE_RESPONSE_FILE_FOR_OBJECTS 0)
set(CMAKE_C_USE_RESPONSE_FILE_FOR_INCLUDES 0)

execute_process(
  COMMAND
  ${CMAKE_C_COMPILER} -dumpversion
  OUTPUT_VARIABLE GCC_VERSION
)

#添加链接选项

if(${CONFIG_CMAKE_DEBUG})
    MESSAGE(STATUS "APP_COMPILE_OPTION_LIST		: ${APP_COMPILE_OPTION_LIST}")
    MESSAGE(STATUS "TOOL_ROOT_DIR		: ${TOOL_ROOT_DIR}")
    MESSAGE(STATUS "CMAKE_ASM_COMPILER		: ${CMAKE_ASM_COMPILER}")
    MESSAGE(STATUS "CMAKE_C_COMPILER		: ${CMAKE_C_COMPILER}")
    MESSAGE(STATUS "CMAKE_CXX_COMPILER		: ${CMAKE_CXX_COMPILER}")
    MESSAGE(STATUS "CMAKE_AR			: ${CMAKE_AR}")
    MESSAGE(STATUS "CMAKE_LINKER			: ${CMAKE_LINKER}")
    MESSAGE(STATUS "CMAKE_C_LINKER 			: ${CMAKE_C_LINKER}")
    MESSAGE(STATUS "CMAKE_CXX_LINKER			: ${CMAKE_CXX_LINKER}")
    MESSAGE(STATUS "CMAKE_OBJCOPY		: ${CMAKE_OBJCOPY}")

    MESSAGE(STATUS "CMAKE_HOME_DIRECTORY     : ${CMAKE_HOME_DIRECTORY}")
    MESSAGE(STATUS "CMAKE_SOURCE_DIR         : ${CMAKE_SOURCE_DIR}")
    MESSAGE(STATUS "CMAKE_BINARY_DIR         : ${CMAKE_BINARY_DIR}")
    MESSAGE(STATUS "CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")
    MESSAGE(STATUS "CMAKE_CURRENT_BINARY_DIR : ${CMAKE_CURRENT_BINARY_DIR}")
    MESSAGE(STATUS "CMAKE_PARENT_LIST_FILE   : ${CMAKE_PARENT_LIST_FILE}")
    MESSAGE(STATUS "CMAKE_CURRENT_LIST_DIR   : ${CMAKE_CURRENT_LIST_DIR}")
    MESSAGE(STATUS "CMAKE_CURRENT_LIST_FILE  : ${CMAKE_CURRENT_LIST_FILE}")
    MESSAGE(STATUS "PROJECT_SOURCE_DIR       : ${PROJECT_SOURCE_DIR}")
    MESSAGE(STATUS "PROJECT_BINARY_DIR       : ${PROJECT_BINARY_DIR}")
    MESSAGE(STATUS "<PROJECT-NAME>_SOURCE_DIR: ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}")
    MESSAGE(STATUS "<PROJECT-NAME>_BINARY_DIR: ${${CMAKE_PROJECT_NAME}_BINARY_DIR}")
    MESSAGE(STATUS "\n")
endif()