#include "cJSON.h"
#include "mbtk_comm_api.h"


static char json_test_value[] = {
"	{"
"		\"name\": \"ASR_CRANEL_EVB\","
"		\"product\": \"arom-tiny\","
"		\"version\": \"0.6\","
"		\"version-bootrom\": \"2022.11.06\","
"		\"template\": \"CRANEL_A0_TEMPLATE\","
"		\"layout\": \"CRANEL_SINGLE_FLASH_LAYOUT\","
"		\"keyAlg\": \"rsa\","
"		\"hashAlg\": \"sha256\","
"		\"secureBoot\": false,"
"		\"firmwareGenerator\": "
"		{"
"			\"name\": \"crane\","
"			\"call-max-download-size\": \"60KiB\","
"			\"flash-max-download-size\": \"1MiB\","
"			\"use-lzma-compression\": true"
"		},"
"		\"fota\": [\"system\"],"
"		\"variants\": ["
"			{"
"				\"name\": \"CRANEL_A0_02MB\","
"				\"flashes\":["
"					{"
"						\"name\": \"qspi\","
"						\"port\": \"QSPI\","
"						\"flash\": \"QSPI_NOR_2MB_B64KB_S4KB_P256\""
"					},"
"					{"
"						\"name\": \"external\","
"						\"port\": \"SSP2\","
"						\"flash\": \"SPI_NOR_8MB_B64KB_S4KB_P256\""
"					}"
"				]"
"			},"
"			{"
"				\"name\": \"CRANEL_A0_08MB\","
"				\"flashes\": ["
"					\{"
"						\"name\": \"qspi\","
"						\"port\": \"QSPI\","
"						\"flash\": \"QSPI_NOR_8MB_B64KB_S4KB_P256\""
"					}"
"				]"
"			}"
"		]"
"	}"
};

void json_demo(void)
{
	cJSON_Hooks js_hook = {0};
	cJSON *js_root = NULL;
	cJSON *js_item = NULL;
	cJSON *sub_item = NULL;
	
	op_uart_printf("json demo entry\n");
	op_uart_printf("json lib version %s",cJSON_Version());

	js_hook.malloc_fn = ol_malloc;
	js_hook.free_fn = ol_free;
	cJSON_InitHooks(&js_hook);

	js_root = cJSON_Parse(json_test_value);
	if(js_root == NULL)
	{
		op_uart_printf("cJSON_Parse error");
		return;
	}
	
	js_item = cJSON_GetObjectItem(js_root ,"template");
	if(js_item != NULL)
	{
		op_uart_printf("template value = %s",cJSON_GetStringValue(js_item));
	}

	js_item = cJSON_GetObjectItem(js_root ,"firmwareGenerator");
	if(js_item != NULL)
	{
		sub_item = cJSON_GetObjectItem(js_item,"use-lzma-compression");
		if(sub_item != NULL)
			op_uart_printf("use-lzma-compression is false = %d",cJSON_IsFalse(sub_item));
	}

	js_item = cJSON_GetObjectItem(js_root,"variants");
	if(js_item != NULL)
	{
		op_uart_printf("array size %d",cJSON_GetArraySize(js_item));
		sub_item = cJSON_GetArrayItem(js_item,0);
		if(sub_item != NULL)
			op_uart_printf("array index 0 name value = %s",cJSON_GetStringValue(cJSON_GetObjectItem(sub_item,"name")));
	}
	
	cJSON_Delete(js_root);
	op_uart_printf("json demo exit\n");
}
