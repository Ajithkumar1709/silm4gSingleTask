

app_include_directories(
    ${SHARED_INCLUDE_DIRS}
    ./../menu_demo
 )
 
app_source(
    datacall_demo.c
    icmp_ping_demo.c
    nw_demo.c
    socket_demo.c
    tcp_ssl_demo.c
    voicecall_demo.c
    websocket_demo.c
 )
 