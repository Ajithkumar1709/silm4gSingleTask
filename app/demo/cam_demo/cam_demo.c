#include "mbtk_cam.h"
#include "mbtk_comm_api.h"
#include "mbtk_lcd.h"
#include "mbtk_qrcode.h"
#include "qrcode_demo_resources.h"

#define QR_CDEC_WHIT_CAM	(0)

#define CAMERA_PREVIEW_WIDTH     240
#define CAMERA_PREVIEW_HEIGHT    240
#define CAMERA_PREVIEW_TIME    15  //秒
#define CAMERA_PREVIEW_FRAME_RATE    10  //帧

void camera_demo(void)
{
	int ret;
	int i =0;
	int sleep_period = (1000/5)/10;  //sleep函数1表示5毫秒
	int max_i = CAMERA_PREVIEW_TIME*CAMERA_PREVIEW_FRAME_RATE;
	op_uart_printf("\r\ncamera_demo finish");
}

#define CONFIG_CAMERA_DECODE_CNT	(1)
#define CONFIG_CAMERA_DECODE_BUF_SIZE    	(IMG_WIDTH*IMG_HEIGHT*3/2*CONFIG_CAMERA_DECODE_CNT)

void qrcode_demo_callback(P_CAL_IDENTITY_RESULT_STRUCT outdata)
{
	printf("<-- result=%d\r\n",outdata->result);
	printf("<-- databuf=%s\r\n",outdata->DataBuf);
}

void qrcode_demo(void)
{
	int ret = 0;
	unsigned char *cache_buffer = NULL;
	unsigned char version[32] = {0};
	
	ol_qrcode_get_ver(version,32);
	op_uart_printf("get qr decoder lib version %s",version);
	op_uart_printf("get qr decoder authorize status %d",ol_qrcode_get_authorize_status());

	cache_buffer = ol_malloc(CONFIG_CAMERA_DECODE_BUF_SIZE);
	if(!cache_buffer)
	{
		op_uart_printf("qr decoder can't malloc memory for  cache buffer");
		return;
	}
	memset(cache_buffer,0x00,CONFIG_CAMERA_DECODE_BUF_SIZE);

	ret = ol_qrcode_init(230,IMG_HEIGHT,IMG_WIDTH,CONFIG_CAMERA_DECODE_CNT,qrcode_demo_callback);
	if(ret != 0)
	{
		op_uart_printf("qr decoder init fail %d",ret);
		goto err;
	}

	ol_qrcode_set_enable(1);
	ol_qrcode_set_buffer(qrcode_buffer,cache_buffer);
	
	ol_qrcode_start();

	ol_os_task_sleep(200*5);
	

err:
	if(cache_buffer) ol_free(cache_buffer);
	ol_qrcode_deinit();
	
	return;
}

