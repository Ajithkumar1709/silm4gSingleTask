#include "rpcHandler.h"
#include "jsmn.h"
#include "../common.h"
#include"lampStatusFinder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mbtk_comm_api.h"
#include "memoryHandle.h"
#include "otaHandler.h"

extern storedDatas_t storedDatas;

#define OTA_FILE_NAME_MAX 64
static char otaFileName[OTA_FILE_NAME_MAX] = {0};

const char *rpcHandler_getOtaFileName(void)
{
	return otaFileName;
}

/* Turns a version string like "00.00.00.01" into the OTA file name the
 * server expects: "00000001.bin" (dots stripped, ".bin" appended). */
static void buildOtaFileNameFromVersion(const char *version, char *out, size_t outSize)
{
	size_t outLen = 0;

	while (*version != '\0' && outLen + 5 < outSize) { /* +5 reserves room for ".bin\0" */
		if (*version != '.') {
			out[outLen++] = *version;
		}
		version++;
	}
	out[outLen] = '\0';
	strcat(out, ".bin");
}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s)
{
	if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

int jsonextract(char *data)
{
	int i;
    int r;
	jsmn_parser p;
    static jsmntok_t t[250]; /* too large (4000 bytes) for the caller's stack
                              * (this is invoked from the MQTT client's own
                              * subscribe-callback context, not my_task) */
	char vv[20]={"\0"};
	int changed = 0;
	op_uart_printf("-1-rpcHandler:enter jsonextract\r\n");
    jsmn_init(&p);
	r = jsmn_parse(&p, data, strlen(data), t,sizeof(t) / sizeof(t[0]));
	if (r < 0) 
	{
		op_uart_printf("-1-rpcHandler:Failed to parse JSON: %d\n", r);
	}
	if (r < 1 || t[0].type != JSMN_OBJECT)
	{
		op_uart_printf("-1-rpcHandler:Object expected\n");
	}
	for (i = 1; i < r; i++)
	{
	if (jsoneq(data, &t[i], "OnDemand") == 0)                   
        {
		return ON_DEMAND;
		}
	//************OtaUpdate*************
	if (jsoneq(data, &t[i], "OtaUpdate") == 0)
        {
		int nameLen = t[i + 1].end - t[i + 1].start;
		if (nameLen < 0) {
			nameLen = 0;
		}
		if (nameLen >= OTA_FILE_NAME_MAX) {
			nameLen = OTA_FILE_NAME_MAX - 1;
		}
		memcpy(otaFileName, data + t[i + 1].start, nameLen);
		otaFileName[nameLen] = '\0';
		return OTA_UPDATE;
		}
	//************minV*****************
		if (jsoneq(data, &t[i], "minV") == 0)                   
        {
            sprintf(vv,"%.*s", t[i + 1].end - t[i + 1].start,data + t[i + 1].start);
            storedDatas.Minvoltage=atoi(vv);
            changed = 1;
            i++;
        }

    //************minW************
		if (jsoneq(data, &t[i], "minW") == 0)                    
        {
            sprintf(vv,"%.*s", t[i + 1].end - t[i + 1].start,data + t[i + 1].start);
            storedDatas.Minpower=atoi(vv);
            changed = 1;
            i++;
        }

    //************pint************
      if (jsoneq(data, &t[i], "pint") == 0)
        {
            sprintf(vv,"%.*s", t[i + 1].end - t[i + 1].start,data + t[i + 1].start);
            storedDatas.periodicTime=atoi(vv);
            changed = 1;
            i++;
        }

    //************maxPayload************
      if (jsoneq(data, &t[i], "maxPayload") == 0)
        {
            sprintf(vv,"%.*s", t[i + 1].end - t[i + 1].start,data + t[i + 1].start);
            storedDatas.maxPayload=atoi(vv);
            changed = 1;
            i++;
        }

    //************firmwareVersion************
      if (jsoneq(data, &t[i], "firmwareVersion") == 0)
        {
            sprintf(vv,"%.*s", t[i + 1].end - t[i + 1].start,data + t[i + 1].start);
            if (strcmp(vv, APP_VERSION) == 0)
            {
                op_uart_printf("-1-rpcHandler:firmwareVersion match, vv=%s, APP_VERSION=%s\r\n", vv, APP_VERSION);
            }
            else
            {
                char otaFile[20];

                buildOtaFileNameFromVersion(vv, otaFile, sizeof(otaFile));
                op_uart_printf("-1-rpcHandler:firmwareVersion not match, vv=%s, APP_VERSION=%s, otaFile=%s\r\n",
                               vv, APP_VERSION, otaFile);
                otaHandler_start(otaFile);
            }
            i++;
        }


	}
	if (changed) {
		memoryHandle_writeConfigStoreWithBackup();
	}
	return SEND_CONFIG_ATTRIBUTES;
}
