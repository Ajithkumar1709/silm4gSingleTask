app_include_directories(
    ${SHARED_INCLUDE_DIRS}
)

app_source(
    src/my_demo.c
    src/mqttTask.c
    src/periodicTask.c
    src/modules/lampStatusFinder.c
    src/modules/publish.c
    src/modules/memoryHandle.c
    src/modules/rpcHandler.c
    src/modules/pvcMeasure.c
    src/modules/otaHandler.c
    src/modules/dataStore.c
)