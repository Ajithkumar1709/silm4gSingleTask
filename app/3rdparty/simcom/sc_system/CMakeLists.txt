
set(SC_SYSTEM_INC inc)
set(SC_SYSTEM_SRC src)

app_add_library(sc_system)

app_include_directories(
    ${SHARED_INCLUDE_DIRS}
    ${SC_SYSTEM_INC}
 )
 
app_source(
    ${SC_SYSTEM_SRC}/simcom_os.c
    ${SC_SYSTEM_SRC}/simcom_uart.c
    ${SC_SYSTEM_SRC}/simcom_pm.c
    ${SC_SYSTEM_SRC}/simcom_simcard.c
    ${SC_SYSTEM_SRC}/simcom_network.c
    ${SC_SYSTEM_SRC}/simcom_tcpip.c
    ${SC_SYSTEM_SRC}/simcom_system.c
    ${SC_SYSTEM_SRC}/simcom_ftps.c
    ${SC_SYSTEM_SRC}/simcom_gps.c
    ${SC_SYSTEM_SRC}/simcom_file_system.c
    ${SC_SYSTEM_SRC}/simcom_ntp_client.c
    ${SC_SYSTEM_SRC}/simcom_loc.c
    ${SC_SYSTEM_SRC}/simcom_gpio.c
    ${SC_SYSTEM_SRC}/simcom_app_updater.c
    ${SC_SYSTEM_SRC}/simcom_fota_download.c
    ${SC_SYSTEM_SRC}/simcom_usb_vcom.c
    ${SC_SYSTEM_SRC}/simcom_at.c
    ${SC_SYSTEM_SRC}/simcom_aes.c
    ${SC_SYSTEM_SRC}/simcom_common.c
    ${SC_SYSTEM_SRC}/simcom_ssl.c
 )
 
add_custom_command(TARGET sc_system POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            $<TARGET_FILE:sc_system>
            ${CMAKE_SOURCE_DIR}/3rdparty/simcom/sc_system/lib
    COMMENT "Copying libsc_system.a to ${CMAKE_CURRENT_SOURCE_DIR}/lib"
)
