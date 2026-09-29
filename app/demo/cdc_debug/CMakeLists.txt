app_include_directories(
    ${SHARED_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

app_source(
    uart_debug.c
)