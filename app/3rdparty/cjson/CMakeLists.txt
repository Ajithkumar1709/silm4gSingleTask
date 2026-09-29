
set(CJSON_INC inc)
set(CJSON_SRC src)

app_include_directories(
    ${SHARED_INCLUDE_DIRS}
    ${CJSON_INC}
 )
 
app_source(
	${CJSON_SRC}/cJSON.c
    demo/json_demo.c
 )
 