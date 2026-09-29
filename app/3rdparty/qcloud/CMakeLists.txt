
set(QCLOUD_INC inc)

app_include_directories(
    ${SHARED_INCLUDE_DIRS}
    ${QCLOUD_INC}/include
    ${QCLOUD_INC}/include/exports
 )
 
app_source(
    demo/qcloud_demo.c
 )
 