#include "mbtk_os.h"
#include "string.h"
#include "ol_wifi_api.h"
#include "mbtk_comm_api.h"

#define WIFI_TIMEOUT 20

void mbtk_wifi_scan_callback(app_adp_wifi_result_t result, app_adp_wifi_ap_list * ap_list)
{
  int i;
  op_uart_printf("wifi_result:%d \n", result);
  op_uart_printf("wifi_ap_list count: %d \n", ap_list->count);
  op_uart_printf("Ap_list MAC rssi \n");
  for(i = 0; i < ap_list->count; i++)
  {
    uint8_t *mac = ap_list->item[i].mac;
    op_uart_printf(" [%d] [%02x %02x %02x %02x %02x %02x] [%d]\n", i+1,
    mac[0],mac[1],mac[2],mac[3],mac[4],mac[5], ap_list->item[i].rssi);
  }
  return;
}

void wifi_demo(void)
{
  int ret = 0;
	app_adp_wifi_option option = {0};

  op_uart_printf("===wifi demo start!!===\r\n");

	option.scan_mode = 2;
	option.fast_rrc_release = 1;
	option.scan_round = 3;
	option.bssid_num = 10;
	option.scan_priority = 1;
	
	ret =ol_wifi_mac_scan_option(1,&option,sizeof(app_adp_wifi_option));
 	if(ret != 0)
  {
    op_uart_printf("===wifi mac sacn set option error!!===\r\n");
    goto exit;
  }
	
  ret = ol_wifi_mac_scan(WIFI_TIMEOUT,mbtk_wifi_scan_callback);
  if(ret != 0)
  {
    op_uart_printf("===wifi mac sacn error!!===\r\n");
    goto exit;
  }

  op_uart_printf("===wifi demo end!!===\r\n");
  return;

exit:
  op_uart_printf("===wifi demo error %d!!===\r\n",ret);
  return;
}