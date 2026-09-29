cmake_minimum_required(VERSION 3.10)


set(HAS_UART ON)
set(HAS_USER_KDWL ON)
set(HAS_DEMO_UART ON)
set(HAS_DEMO_NETWORK ON)
set(HAS_DEMO_SIMCARD ON)
set(HAS_DEMO_TCPIP ON)
set(HAS_DEMO_FTPS ON)
set(HAS_DEMO_GNSS ON)
set(HAS_DEMO_FS ON)
set(HAS_DEMO_NTP ON)
set(HAS_DEMO_LBS ON)
set(HAS_DEMO_GPIO ON)
set(HAS_DEMO_APP_UPDATE ON)
set(HAS_URC ON)
set(HAS_USB ON)
set(HAS_DEMO_USB ON)
set(HAS_DEMO_AT ON)
set(HAS_DEMO_OTA ON)
set(HAS_DEMO_APP_DOWNLOAD ON)


set(sc_demo_define SIMCOM_UI_DEMO_TO_UART1_PORT)
# AUX_SOURCE_DIRECTORY(./src sc_demo_src)
# AUX_SOURCE_DIRECTORY(./src/token sc_demo_src)
# AUX_SOURCE_DIRECTORY(./src/utils sc_demo_src)

#########################
#       general config
#########################
if(HAS_UART)
    list(APPEND sc_demo_src ./src/uart_api.c)
    list(APPEND sc_demo_define HAS_UART SIMCOM_UI_DEMO_TO_UART1_PORT)
endif()

if(HAS_URC)
    list(APPEND sc_demo_src ./src/cus_urc.c)
    list(APPEND sc_demo_define HAS_UART HAS_URC)
endif()

if(HAS_USB)
    list(APPEND sc_demo_src ./src/cus_usb_vcom.c)
    list(APPEND sc_demo_define HAS_USB)
endif()
if(HAS_USER_KDWL)
list(APPEND sc_demo_src ./src/simcom_demo.c)

list(APPEND sc_demo_src ./src/demo_helloworld.c)
#########################
#       driver
#########################
if(HAS_DEMO_WTD)
    list(APPEND sc_demo_src ./src/demo_wtd.c)
endif()

if(HAS_DEMO_PMU)
    list(APPEND sc_demo_src ./src/demo_pm.c)
endif()

if(HAS_DEMO_GPIO)
    list(APPEND sc_demo_src ./src/demo_gpio.c)
    list(APPEND sc_demo_define HAS_DEMO_GPIO GPIO_INT_WAKEUP_TEST)
endif()

if(HAS_DEMO_PWM)
    list(APPEND sc_demo_src ./src/demo_pwm.c)
endif()

if(HAS_DEMO_UART)
    list(APPEND sc_demo_src ./src/demo_uart.c)
    list(APPEND sc_demo_define HAS_DEMO_UART)
endif()

if(HAS_DEMO_USB)
    list(APPEND sc_demo_define HAS_DEMO_USB)
endif()

if(HAS_DEMO_I2C)
    list(APPEND sc_demo_src ./src/demo_i2c.c)
endif()

if(HAS_DEMO_SPI)
    list(APPEND sc_demo_src ./src/demo_spi.c)
endif()

if(HAS_DEMO_FLASH)
    list(APPEND sc_demo_src ./src/demo_flash.c)
endif()

if(HAS_DEMO_OTA)
    list(APPEND sc_demo_src ./src/demo_fota.c)
    list(APPEND sc_demo_define HAS_DEMO_OTA)
endif()

if(HAS_DEMO_GNSS)
    list(APPEND sc_demo_src ./src/demo_gps.c)
    list(APPEND sc_demo_define HAS_DEMO_GNSS FEATURE_SIMCOM_GPS)
endif()

if(HAS_DEMO_LCD)
    list(APPEND sc_demo_src ./src/demo_lcd.c)
endif()

if(HAS_DEMO_CAM)
    list(APPEND sc_demo_src ./src/demo_cam.c ./src/demo_cam_dirver.c)
endif()
if(HAS_DEMO_SYS)
    list(APPEND sc_demo_src ./src/demo_cam.c ./src/demo_system.c)
endif()
#########################
#         modem
#########################
if(HAS_DEMO_NETWORK)
    list(APPEND sc_demo_src ./src/demo_network.c)
    list(APPEND sc_demo_define HAS_DEMO_NETWORK)
endif()

if(HAS_DEMO_SIMCARD)
    list(APPEND sc_demo_src ./src/demo_simcard.c)
    list(APPEND sc_demo_define HAS_DEMO_SIMCARD)
endif()

if(HAS_DEMO_CALL)
    list(APPEND sc_demo_src ./src/demo_call.c)
endif()

if(HAS_DEMO_SMS)
    list(APPEND sc_demo_src ./src/demo_sms.c)
endif()

if(HAS_DEMO_LBS)
    list(APPEND sc_demo_src ./src/demo_loc.c ./src/demo_loc_test.c)
    list(APPEND sc_demo_define HAS_DEMO_LBS)
endif()

if(HAS_DEMO_SJDR)
    list(APPEND sc_demo_src ./src/demo_sjdr.c)
endif()

if(HAS_DEMO_INTERNET_SERVICE)
endif()

#########################
#         app
#########################
if(HAS_DEMO_SSL)
    list(APPEND sc_demo_src ./src/demo_ssl.c ./src/demo_ssl_test.c)
endif()

if(HAS_DEMO_TCPIP)
    list(APPEND sc_demo_src ./src/demo_tcpip.c)
    list(APPEND sc_demo_define HAS_DEMO_TCPIP)
endif()

if(HAS_DEMO_HTTPS)
    list(APPEND sc_demo_src ./src/demo_https.c)
endif()

if(HAS_DEMO_FTPS)
    list(APPEND sc_demo_src ./src/demo_ftps.c ./src/demo_ftps_test.c)
    list(APPEND sc_demo_define HAS_DEMO_FTPS FEATURE_SIMCOM_FTPS)
endif()

if(HAS_DEMO_MQTTS)
    list(APPEND sc_demo_src ./src/demo_mqtt.c ./src/mqtt_OneNET.c ./src/mqtt_tencent.c)
endif()

if(HAS_DEMO_NTP)
    list(APPEND sc_demo_src ./src/demo_ntp.c)
    list(APPEND sc_demo_define HAS_DEMO_NTP)
endif()

if(HAS_DEMO_HTP)
    list(APPEND sc_demo_src ./src/demo_htp.c)
endif()

if(HAS_DEMO_AUDIO)
    list(APPEND sc_demo_src ./src/demo_audio.c)
endif()

if(HAS_DEMO_TTS)
    list(APPEND sc_demo_src ./src/demo_tts.c)
endif()

if(HAS_DEMO_POC)
    list(APPEND sc_demo_src ./src/demo_poc.c)
endif()

if(HAS_DEMO_WIFI)
    list(APPEND sc_demo_src ./src/demo_wifi.c)
endif()

if(HAS_DEMO_RTC)
    list(APPEND sc_demo_src ./src/demo_rtc.c)
endif()

if(HAS_DEMO_BLE)
    list(APPEND sc_demo_src ./src/demo_ble.c)
endif()

if(HAS_DEMO_FS)
    list(APPEND sc_demo_src ./src/demo_file_system.c)
    list(APPEND sc_demo_define HAS_DEMO_FS)
endif()

if(HAS_DEMO_FS_OLD)
endif()

if(HAS_DEMO_APP_DOWNLOAD)
    list(APPEND sc_demo_src ./src/demo_app_download.c)
    list(APPEND sc_demo_define HAS_DEMO_APP_DOWNLOAD)
endif()

if(HAS_DEMO_APP_UPDATE)
    list(APPEND sc_demo_src ./src/demo_app_updater.c)
    list(APPEND sc_demo_define HAS_DEMO_APP_UPDATE)
endif()
endif()
#########################
#       other libs
#########################
if(HAS_ZLIB)
    list(APPEND sc_demo_src ./src/demo_zlib.c)
endif()

if(HAS_SM2)
    list(APPEND sc_demo_src ./src/demo_sm2.c)
endif()

if(HAS_CJSON)
    list(APPEND sc_demo_src ./src/demo_cjson.c)
endif(HAS_CJSON)

if(HAS_MBEDTLS)
    list(APPEND sc_demo_src ./src/demo_mbedtls.c)
endif(HAS_MBEDTLS)

if(HAS_DEMO_AT)
    list(APPEND sc_demo_src ./src/demo_at.c)
    list(APPEND sc_demo_define HAS_DEMO_AT)
endif(HAS_DEMO_AT)

list(APPEND sc_demo_src ./src/demo_aes.c ./src/demo_rsa.c)



# Add the static library
# add_library(sc_demo STATIC ${sc_demo_src})
app_add_library(sc_demo)
app_source(${sc_demo_src})
add_dependencies(sc_demo system)

add_compile_definitions(${sc_demo_define})
target_compile_options(sc_demo PUBLIC -Werror)
target_include_directories(sc_demo PUBLIC
    ./inc
    ${CMAKE_SOURCE_DIR}/sc_demo/inc
    ${CMAKE_SOURCE_DIR}/config
    ${SHARED_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/${THIRD_PARTY_DIR}/simcom/sc_system/inc
)

if(HAS_SM2)
    target_include_directories(sc_demo PUBLIC
        ${CMAKE_SOURCE_DIR}/public_libs/sm2
        ${CMAKE_SOURCE_DIR}/public_libs/miracl
    )
endif(HAS_SM2)

if(HAS_ZLIB)
    target_include_directories(sc_demo PUBLIC
        ${CMAKE_SOURCE_DIR}/public_libs/zlib
        ${CMAKE_SOURCE_DIR}/public_libs/zlib/minizip
    )
endif(HAS_ZLIB)

if(HAS_CJSON)
    target_include_directories(sc_demo PUBLIC
        ${CMAKE_SOURCE_DIR}/public_libs/cjson
    )
endif(HAS_CJSON)

# SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
