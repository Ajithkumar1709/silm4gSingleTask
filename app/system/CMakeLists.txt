
#���ӿ�
app_add_library(system)


app_sys_include_directories( 
  inc 
  inc/fs
  inc/network
  inc/drv
  inc/os
  inc/nw
  inc/device
  inc/softutil
  inc/customer_define
  inc/sms
  inc/wifi
  inc/crypt
  inc/lwipv4v6
  inc/mbedTLS/include
  inc/mbedTLS/asros
  inc/network/mqtt_ibm
  inc/aidialog
  ../demo/cdc_debug/include
)

app_source(
   src/api_customer_init_atok.c
   src/api_init.c
)



