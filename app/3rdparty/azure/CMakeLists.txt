
set(AZURE_INC inc)

app_include_directories(
    ${SHARED_INCLUDE_DIRS}
    ${AZURE_INC}/c-utility/inc
    ${AZURE_INC}/c-utility/inc/azure_c_shared_utility
    ${AZURE_INC}/deps/parson
    ${AZURE_INC}/iothub_client/inc
    ${AZURE_INC}/iothub_client/inc/internal
    ${AZURE_INC}/serializer/inc
    ${AZURE_INC}/umqtt/inc
 )
 
app_source(
    demo/azure_demo.c
 )
 