
#include "../common.h"
#include "lampStatusFinder.h"
#include "mbtk_sim_api.h"
#include "ntp_api.h"
#include <stdio.h>
#include <string.h>
#include "../mqttTask.h"
#include "mbtk_comm_api.h"
char* extractJsonData(uint8_t *data, uint8_t dataSize) {
 static char JsonBuffer[500];

JsonExtractData_t JsonExtractData;

 op_uart_printf("-1-publish:enter extractJsonData\r\n");

//measure rssi
 memset(JsonBuffer, 0, sizeof(JsonBuffer));
 memset(&JsonExtractData, 0, sizeof(JsonExtractData));
 memcpy(&JsonExtractData.data, data, dataSize);
 
  sprintf(
    JsonBuffer,
    "{\"ts\":%lu,\"pkt\":%u,\"lamp\":%u,"
    "\"volt\":%lu,\"power\":%lu,\"bat\":%lu,\"fault\":%u,\"current\":%lu}",
    JsonExtractData.sendToserverPkt.serveTransmitPkt.utc,
    JsonExtractData.sendToserverPkt.serveTransmitPkt.pktType,
    JsonExtractData.sendToserverPkt.serveTransmitPkt.lmpState,
    JsonExtractData.sendToserverPkt.serveTransmitPkt.voltage,
    JsonExtractData.sendToserverPkt.serveTransmitPkt.power,
    JsonExtractData.sendToserverPkt.serveTransmitPkt.batVolt,
    JsonExtractData.sendToserverPkt.serveTransmitPkt.faultStatus,
    JsonExtractData.sendToserverPkt.serveTransmitPkt.current
  );
  op_uart_printf("-1-publish:extractJsonData result=%s\r\n", JsonBuffer);
  return JsonBuffer;  //

}

char* extractJsonConfigAttributesData(uint8_t *data, uint8_t dataSize) {
 static char configJsonBuffer[200];
 configStore_t configData;

 op_uart_printf("-1-publish:enter extractJsonConfigAttributesData\r\n");
 memset(configJsonBuffer, 0, sizeof(configJsonBuffer));
 memset(&configData, 0, sizeof(configData));
 memcpy(&configData, data, dataSize);

 sprintf(
   configJsonBuffer,
   "{\"minVoltage\":%lu,\"minCurrent\":%lu,\"periodicTime\":%lu}",
   configData.Minvoltage,
   configData.Minpower,
   configData.periodicTime
 );
 return configJsonBuffer;
}

mqttQueue_t publishattributesPacketCcidImsiJson(void)
{
  mqttQueue_t mqttQueue = {0};
  char json_data[JSON_DATA_MAX_SIZE] = {0};
  char iccid[32] = {0};
  char imsi[24] = {0};

  op_uart_printf("-1-publish:enter publishattributesPacketCcidImsiJson\r\n");
  if (ol_get_sim_iccid((uint8_t *)iccid) != 0)
  {
    op_uart_printf("-1-publish:ICCID read failed\r\n");
    strcpy(iccid, "unknown");
  }

  if (ol_get_sim_imsi((uint8_t *)imsi) != 0)
  {
    op_uart_printf("-1-publish:IMSI read failed\r\n");
    strcpy(imsi, "unknown");
  }

  snprintf(
    json_data,
    sizeof(json_data),
    "{\"iccid\":\"%s\",\"imsi\":\"%s\",\"version\":\"%s\"}",
    iccid,
    imsi,
    APP_VERSION
  );

  mqttQueue.dataSize = strlen(json_data);
  if (mqttQueue.dataSize > sizeof(mqttQueue.data))
  {
    mqttQueue.dataSize = sizeof(mqttQueue.data);
  }

  memcpy(mqttQueue.data, json_data, mqttQueue.dataSize);
  mqttQueue.topic = 2;

  return mqttQueue;
}

mqttQueue_t publish_req_shared_attributes_JSON(void)
{
  mqttQueue_t mqttSendData;
  char bufferSA[] = "{\"sharedKeys\":\"minV,minW,pint,firmwareVersion\"}";

  memset(&mqttSendData, 0, sizeof(mqttSendData));
  memcpy(mqttSendData.data, bufferSA, strlen(bufferSA));
  mqttSendData.dataSize = strlen(bufferSA);
  mqttSendData.topic = 4;

  return mqttSendData;
}
