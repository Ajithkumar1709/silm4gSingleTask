

function(app_compile_options libname opt)
target_compile_options(${libname} PUBLIC ${opt})
endfunction()

function(app_compile_options_c libname opt)
target_compile_options(${libname} PUBLIC "$<$<COMPILE_LANGUAGE:C>:${opt}>")
endfunction()

function(app_compile_options_cpp libname opt)
target_compile_options(${libname} PUBLIC "$<$<COMPILE_LANGUAGE:CXX>:${opt}>")
endfunction()

function(app_compile_options_c_cpp libname opt)
target_compile_options(${libname} PUBLIC "$<$<COMPILE_LANGUAGE:C>:${opt}>" "$<$<COMPILE_LANGUAGE:CXX>:${opt}>")
endfunction()




function(gen_gcc_lib_txt)

if(EXISTS ${STDLIB_FILE})
file(REMOVE_RECURSE ${STDLIB_FILE})
endif()

file(APPEND ${STDLIB_FILE} "${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/lib/thumb/v7/nofp/libm.a\n")
file(APPEND ${STDLIB_FILE} "${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/lib/thumb/v7/nofp/libc.a\n")
file(APPEND ${STDLIB_FILE} "${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/lib/thumb/v7/nofp/libstdc++.a\n")
file(APPEND ${STDLIB_FILE} "${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/lib/thumb/v7/nofp/libg.a\n")
file(APPEND ${STDLIB_FILE} "${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/lib/thumb/v7/nofp/libnosys.a\n")
file(APPEND ${STDLIB_FILE} "${TOOLCHAIN_PREFIX}/lib/gcc/arm-none-eabi/10.3.1/libgcc.a\n")
endfunction()


function(clean_file filename)
if(EXISTS ${filename})
file(REMOVE_RECURSE ${filename})
endif()
endfunction()


function(app_add_customer_lib lib_name)
#添加客户lib，用于添加客户第三方库
if(IS_ABSOLUTE ${lib_name})
  set(path ${lib_name})
else()
  set(path ${CMAKE_CURRENT_SOURCE_DIR}/${lib_name})
endif()

if(IS_DIRECTORY ${path})
  message(FATAL_ERROR "app_add_customer_lib() was called on a directory")
endif()

if(NOT DEFINED DEPENDENCY_LIB)
  set(DEPENDENCY_LIB ${DEPENDENCY_LIB} ${path} CACHE INTERNAL "customer lib" FORCE)
else()
  list(FIND DEPENDENCY_LIB ${path} index)
  if(index EQUAL -1)
	set(DEPENDENCY_LIB ${DEPENDENCY_LIB} ${path} CACHE INTERNAL "customer lib" FORCE)
  else()
	message(STATUS "customer lib already exist in cache")
  endif()
endif()  
endfunction()



function(app_add_library lib_name)
#添加编译文件，编译的文件会生成lib_name的库
add_library(${lib_name} STATIC)
set(CURRENT_TARGET ${lib_name} PARENT_SCOPE)
file(APPEND ${OBJLIST_FILE} "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_STATIC_LIBRARY_PREFIX}${lib_name}${CMAKE_STATIC_LIBRARY_SUFFIX}\n")


#编译参数
app_compile_options(${lib_name}  "-g")
app_compile_options(${lib_name}  "-mthumb")
   
app_compile_options_c_cpp(${lib_name}   -mcpu=cortex-r4)
app_compile_options_c_cpp(${lib_name}   -MMD)
#app_compile_options_c_cpp(-march=armv7-r)
app_compile_options_c_cpp(${lib_name}   -mlittle-endian)
app_compile_options_c_cpp(${lib_name}   -mthumb-interwork)
app_compile_options_c_cpp(${lib_name}   -mlong-calls)
app_compile_options_c_cpp(${lib_name}   -Wformat=0)
app_compile_options_c(${lib_name}   -Wno-pointer-sign)
app_compile_options_c_cpp(${lib_name}   -Wno-parentheses)
app_compile_options_c(${lib_name}   -Wno-incompatible-pointer-types)
app_compile_options_c_cpp(${lib_name}   -Wno-unused-variable)
app_compile_options_c_cpp(${lib_name}   -mfloat-abi=soft)
app_compile_options_c_cpp(${lib_name}   -Wall)
app_compile_options_c_cpp(${lib_name}   -ffunction-sections)
app_compile_options_c(${lib_name}   -fdata-sections)
app_compile_options_c_cpp(${lib_name}   -fno-builtin-malloc)
app_compile_options_c_cpp(${lib_name}   -fno-builtin-free)
app_compile_options_c_cpp(${lib_name}   -fno-builtin-printf)
app_compile_options_c_cpp(${lib_name}   -fno-builtin-time)
app_compile_options_c_cpp(${lib_name}   -fno-builtin-gettimeofday)
app_compile_options_c_cpp(${lib_name}   -fno-builtin-gmtime)
app_compile_options_c_cpp(${lib_name}   -Wno-unused-function)
app_compile_options_c(${lib_name}   -Wstrict-prototypes)
app_compile_options_c(${lib_name}   -std=c99)
app_compile_options_c_cpp(${lib_name}   -Os)
app_compile_options_cpp(${lib_name}   -Wno-write-strings)
app_compile_options_cpp(${lib_name}   -std=c++11)

endfunction()


function(app_add_compile_definitions def_name)
target_compile_definitions(${CURRENT_TARGET} PRIVATE 
   ${def_name}
)

endfunction()


function(app_source)
    foreach(arg ${ARGV})
        if(IS_ABSOLUTE ${arg})
        set(path ${arg})
        else()
        set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
        endif()

        if(IS_DIRECTORY ${path})
        message(FATAL_ERROR "app_source() was called on a directory")
        endif()

        target_sources(${CURRENT_TARGET} PRIVATE ${path})
  endforeach()
endfunction()


function(app_sys_include_directories)
  foreach(arg ${ARGV})
    if(IS_ABSOLUTE ${arg})
      set(path ${arg})
    else()
      set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
    endif()

    if(${CONFIG_CMAKE_DEBUG})
        message(STATUS "${CURRENT_TARGET}  path=${path}")
    endif()
    target_include_directories(${CURRENT_TARGET} SYSTEM PUBLIC ${path})
    set(SHARED_INCLUDE_DIRS ${SHARED_INCLUDE_DIRS} ${path} CACHE INTERNAL "Shared include directories" FORCE)
  endforeach()
endfunction()


function(app_include_directories)
  foreach(arg ${ARGV})
    if(IS_ABSOLUTE ${arg})
      set(path ${arg})
    else()
      set(path ${CMAKE_CURRENT_SOURCE_DIR}/${arg})
    endif()
    target_include_directories(${CURRENT_TARGET} PUBLIC ${path})
  endforeach()

  target_include_directories(${CURRENT_TARGET} PUBLIC ${SHARED_INCLUDE_DIRS})
endfunction()


function(import_kconfig config_file GLOBLE_FEATURE_DEF)
  # Parse the lines prefixed with CONFIG_ in ${config_file}
  file(
    STRINGS
    ${config_file}
    DOT_CONFIG_LIST
    REGEX "^CONFIG_"
    ENCODING "UTF-8"
  )

  message(STATUS "DEFINED LIST:")
  foreach (CONFIG ${DOT_CONFIG_LIST})
    # CONFIG looks like: CONFIG_NET_BUF=y

    # Match the first part, the variable name
    string(REGEX MATCH "[^=]+" CONF_VARIABLE_NAME ${CONFIG})

	#Replace CONFIG_ as MBTK_
	string(REPLACE "CONFIG_" "MBTK_" CONF_VARIABLE_NAME ${CONF_VARIABLE_NAME})

    # Match the second part, variable value
    string(REGEX MATCH "=(.+$)" CONF_VARIABLE_VALUE ${CONFIG})
    # The variable name match we just did included the '=' symbol. To just get the
    # part on the RHS we use match group 1
    set(CONF_VARIABLE_VALUE ${CMAKE_MATCH_1})

    if("${CONF_VARIABLE_VALUE}" MATCHES "^\"(.*)\"$") # Is surrounded by quotes
      set(CONF_VARIABLE_VALUE ${CMAKE_MATCH_1})
    endif()

    set("${CONF_VARIABLE_NAME}" "${CONF_VARIABLE_VALUE}" PARENT_SCOPE)
    message(STATUS "${CONF_VARIABLE_NAME}=${CONF_VARIABLE_VALUE}")
	
	if("${CONF_VARIABLE_VALUE}" STREQUAL "y")
		list(APPEND GLOBLE_FEATURE_DEF_TMP  "${CONF_VARIABLE_NAME}")
	else()
		list(APPEND GLOBLE_FEATURE_DEF_TMP  "${CONF_VARIABLE_NAME}=${CONF_VARIABLE_VALUE}")
	endif()
  endforeach()
	set(${GLOBLE_FEATURE_DEF} "${GLOBLE_FEATURE_DEF_TMP}" PARENT_SCOPE)
endfunction()

function(generate_linker_file file_path)

  if(${MBTK_CHIP_1602})
	set(DIR_SELECT 1602)
  elseif(${MBTK_CHIP_1603})
	set(DIR_SELECT 1603)
  elseif(${MBTK_CHIP_1605})
	set(DIR_SELECT 1605)
  elseif(${MBTK_CHIP_1606})
	set(DIR_SELECT 1606)
  else()
	set(DIR_SELECT 1607)
  endif()
  include(${CMAKE_SOURCE_DIR}/config/${DIR_SELECT}/addr.cmake)

  message(STATUS "Select app addr RAM:${APP_RAM_ADD} ROM:${APP_ROM_ADD}")
  
  if(${APP_ROM_ADD} LESS 0x90000000)
  message(STATUS "It's an internal flash address!!")
  else()
  message(STATUS "It's an external flash address!!")
  if(${MBTK_IS_XIP})
  message(FATAL_ERROR "App can't been XIP mode with external flash address")
  endif()
  endif()
  
  if("${COMP_TYPE}" STREQUAL "GCC")
	file(
	  WRITE
      ${file_path}
	  "__APP_ROM_ADDR = ${APP_ROM_ADD};\n__APP_RAM_ADDR = ${APP_RAM_ADD};\n"
	)
  elseif("${COMP_TYPE}" STREQUAL "ARMCC")
	file(
	  WRITE
      ${file_path}
	  "#define APP_ROM_ADDR ${APP_ROM_ADD}\n#define APP_RAM_ADDR ${APP_RAM_ADD}\n"
	)
  endif()
endfunction()