#ifndef PUBLISH_H
#define PUBLISH_H   

#include "../common.h"
#include "lampStatusFinder.h"
//mqttQueue_t publishTelementryPacketJson(serveTransmitPkt_t serveTransmitPkt);
mqttQueue_t publishattributesPacketCcidImsiJson(void);
mqttQueue_t publish_req_shared_attributes_JSON(void);
extern char* extractJsonData(uint8_t *data, uint8_t dataSize);
extern char* extractJsonConfigAttributesData(uint8_t *data, uint8_t dataSize);
#endif // PUBLISH_H