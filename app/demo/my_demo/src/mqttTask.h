
#ifndef MQTTTASK_H
#define MQTTTASK_H

#include <stddef.h>
#include "common.h"
#include "modules/lampStatusFinder.h"
#include "ol_mqttclient.h"

extern uint8_t mqtt_connected;
extern volatile unsigned char sharedAttrResponseReceived;

/* Ensures a live, subscribed MQTT connection (network register + data call +
 * connect + subscribe), reconnecting from scratch if needed. Returns 0 when
 * *client is ready to publish on, non-zero otherwise. */
int networkCheckRecovery(mqtt_client_t **client);

/* Publishes data on the given topic (1=telemetry, 2=attributes(raw json),
 * 3=config attributes). Returns 0 on success. */
int mqtt_publish(mqtt_client_t *client, void *data, size_t data_size, uint8_t topic);



typedef struct __attribute__((packed)){
    serveTransmitPkt_t serveTransmitPkt;
    int rssi; 
    int temp;

}sendToserverPkt_t;

typedef union{
    uint8_t  data[sizeof(sendToserverPkt_t)];
    sendToserverPkt_t sendToserverPkt;
}JsonExtractData_t;

#endif

