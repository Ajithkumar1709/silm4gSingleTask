cmake_minimum_required(VERSION 3.14)

include(${CMAKE_SOURCE_DIR}/scripts/util.cmake NO_POLICY_SCOPE)
set(COMPILE_TYPE COMP_TYPE_${COMP_TYPE})
import_kconfig(${CMAKE_CURRENT_SOURCE_DIR}/config/menuconfig/target/target.config GLOBLE_FEATURE_DEF)
add_compile_definitions(${GLOBLE_FEATURE_DEF} ${COMPILE_TYPE})

set(RELEASE_PATH ${CMAKE_CURRENT_BINARY_DIR}/../release)
if("${COMP_TYPE}" STREQUAL "GCC")
set(LINK_LD_FILE_PATH ${CMAKE_SOURCE_DIR}/config/gcc)
set(LINK_LD_FILE_POSTFIX .ld)
elseif("${COMP_TYPE}" STREQUAL "ARMCC")
set(LINK_LD_FILE_PATH ${CMAKE_SOURCE_DIR}/config/armcc)
set(LINK_LD_FILE_POSTFIX .scat)
else()
message(FATAL_ERROR "Select a compiler first...")
endif()
message(STATUS "Compiler Selected ${COMP_TYPE}")

set(LINK_LD_INC_FILE inc${LINK_LD_FILE_POSTFIX})
generate_linker_file(${CMAKE_CURRENT_BINARY_DIR}/${LINK_LD_INC_FILE})
if(${MBTK_IS_XIP})
  set(LINK_LD_FILE appldxip${LINK_LD_FILE_POSTFIX})
else()
  set(LINK_LD_FILE appld${LINK_LD_FILE_POSTFIX})
endif()
message(STATUS "Selected Link file ${LINK_LD_FILE}")

set(APP_PRO_NAME  user_app)
set(THIRD_PARTY_DIR 3rdparty)

project(${APP_PRO_NAME}_pro LANGUAGES C CXX)

#链接所需文件
set(OBJLIST_FILE ${CMAKE_BINARY_DIR}/objlist.txt)
clean_file(${OBJLIST_FILE})


set(SHARED_INCLUDE_DIRS CACHE INTERNAL "Shared include directories")

add_subdirectory(system)
#根目录,添加库
app_add_library(${APP_PRO_NAME})

target_sources(${APP_PRO_NAME} PRIVATE
   main.cpp
)
app_include_directories(
   ${SHARED_INCLUDE_DIRS}
)

if(${MBTK_SIMCOM_SUPPORT})
add_subdirectory(${THIRD_PARTY_DIR}/simcom)

add_dependencies(${APP_PRO_NAME} system)
add_dependencies(${APP_PRO_NAME} simcom)
target_link_libraries(${APP_PRO_NAME} PRIVATE simcom)
app_add_customer_lib(${THIRD_PARTY_DIR}/simcom/sc_system/lib/libsc_system.a)
else()
add_subdirectory(demo)

add_dependencies(${APP_PRO_NAME} system)
add_dependencies(${APP_PRO_NAME} demo)
target_link_libraries(${APP_PRO_NAME} PRIVATE demo)
endif()

if(${MBTK_MAAS_SUPPORT})
 #add_subdirectory(${THIRD_PARTY_DIR}/maas)
endif()

if(${MBTK_AZURE_SUPPORT})
 add_subdirectory(${THIRD_PARTY_DIR}/azure)
 app_add_customer_lib(${THIRD_PARTY_DIR}/azure/lib/Azure.lib)
endif()

if(${MBTK_QCLOUD_SUPPORT})
 add_subdirectory(${THIRD_PARTY_DIR}/qcloud)
 app_add_customer_lib(${THIRD_PARTY_DIR}/qcloud/lib/Qcloud.lib)
endif()

if(${MBTK_CJSON_SUPPORT})
 add_subdirectory(${THIRD_PARTY_DIR}/cjson)
endif()

if(${MBTK_TTS_SUPPORT})
 #add_subdirectory(${THIRD_PARTY_DIR}/tts)
endif()

#添加第三方链接库，可以如下方法
#app_add_customer_lib(lib/xxx.lib)

#添加编译文件，可以直接查看demo下方法，使用add_subdirectory即可。一般无需app_add_library
#add_subdirectory(xxxx)  方法可查看demo/xxx_demo下cmakelist.txt

#添加编译宏，可以在对应cmakeList.txt添加app_add_compile_definitions(xxxxxx)


#以下一般无需修改，如需添加编译文件或者库，请在此之上添加

#libc库
set(STDLIB_FILE ${CMAKE_BINARY_DIR}/stdlib.txt)
gen_gcc_lib_txt()

#生成link相关
set(EMPTY_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty_file.c)
if(NOT EXISTS ${EMPTY_FILE})
file(WRITE ${EMPTY_FILE})
endif()

set(LINK_TAGET "link_app")
add_executable(${LINK_TAGET})
target_sources(${LINK_TAGET} PRIVATE
      ${EMPTY_FILE}
)

if(${CONFIG_CMAKE_DEBUG})
      message(STATUS "link_objs_str =${link_objs_str}")
endif()


list(APPEND
     pre_link_commands
     COMMAND ${CMAKE_COMMAND} -E echo "pre link... do "
     COMMAND ${CMAKE_COMMAND} -E copy ${LINK_LD_FILE_PATH}/${LINK_LD_FILE} ${CMAKE_CURRENT_BINARY_DIR}/${LINK_LD_FILE}
     #COMMAND ${CMAKE_COMMAND} -E copy ${LINK_LD_FILE_PATH}/${LINK_LD_PRO} ${CMAKE_CURRENT_BINARY_DIR}/${LINK_LD_INC_FILE}
)


file(READ ${OBJLIST_FILE} objs_link)
string(REPLACE "\n" " " link_objs_str ${objs_link})
if(${CONFIG_CMAKE_DEBUG})
      message(STATUS "link_objs_str =${link_objs_str}")
endif()
set(APP_LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/sdk_api_stub.o ${CMAKE_CURRENT_SOURCE_DIR}/lib/sdk_api_stub_c.o")

file(READ ${STDLIB_FILE} std_libs)
string(REPLACE "\n" " " std_libs_str ${std_libs})
if(${CONFIG_CMAKE_DEBUG})
      message(STATUS "std_libs_str =${std_libs_str}")
endif()


string(REPLACE ";" " " DEPENDENCY_LIB_STR "${DEPENDENCY_LIB}")
set(link_commands_flags "-gc-sections --wrap=malloc --wrap=free --wrap=calloc --wrap=realloc -T${CMAKE_CURRENT_BINARY_DIR}/${LINK_LD_FILE} -nostdlib -Map ${APP_PRO_NAME}.map -o ${APP_PRO_NAME}.elf --whole-archive ${link_objs_str}  ${APP_LIB} --no-whole-archive --start-group ${std_libs_str} ${DEPENDENCY_LIB_STR} --end-group")

add_custom_command(
    TARGET ${LINK_TAGET}
    PRE_LINK
    ${pre_link_commands}
)

set(CMAKE_C_LINK_EXECUTABLE "${CMAKE_LINKER} ${link_commands_flags}")
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_C_LINK_EXECUTABLE}")

set_property(TARGET ${LINK_TAGET} APPEND PROPERTY LINK_DEPENDS
    ${OBJLIST_FILE}
)

set_property(TARGET ${LINK_TAGET} APPEND PROPERTY LINK_DEPENDS
    ${STDLIB_FILE}
)

list(APPEND
     post_build_commands
     COMMAND ${CMAKE_COMMAND} -E echo "post build... do "
     COMMAND ${CMAKE_OBJCOPY} -O binary ${APP_PRO_NAME}.elf  ${APP_PRO_NAME}.bin
     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${APP_PRO_NAME}.bin ${RELEASE_PATH}/${APP_PRO_NAME}.bin
     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${APP_PRO_NAME}.map ${RELEASE_PATH}/${APP_PRO_NAME}.map
     COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${APP_PRO_NAME}.elf ${RELEASE_PATH}/${APP_PRO_NAME}.elf
	 
)

if(${MBTK_IS_COMPRESS})
list(APPEND
     post_build_commands
	 COMMAND perl ${CMAKE_SOURCE_DIR}/scripts/app_image_compress.pl ${LZMA} ${APP_PRO_NAME}.bin ${APP_PRO_NAME}_compressed.bin
	 COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${APP_PRO_NAME}_compressed.bin ${RELEASE_PATH}/${APP_PRO_NAME}.bin	 
)
endif()
		

add_custom_command(
    TARGET ${LINK_TAGET}
    POST_BUILD
    ${post_build_commands}
)




