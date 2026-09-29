#ifndef COMMON_H
#define COMMON_H

#include "mbtk_os.h"


// ILM PROCESS EVENTS
#define D_SEND_NO_DATA        -1
#define D_POWER_RETAIN         1
#define D_PERIODIC_INTERVAL    2
#define D_RPC                  3
#define D_GNSS_DPROCESS        4
#define D_POWER_FAIL           5
#define D_FIVESEC_COM          6
#define D_ICCID                7
#define D_ASTRO                8

#define APP_VERSION "77.00.00.00"
#define JSON_DATA_MAX_SIZE 225
#define D_FIVESEC_TIME  5
#define PERIODIC_DURATION  3600
typedef uint8_t U1 ;
typedef uint32_t U4 ;
typedef uint16_t U2 ;
typedef char S1 ;
typedef enum
{
    event_live = 0,
    event_lamp_on,
    event_lamp_off,
    event_lamp_dim,
    event_lamp_fault_set,
    event_lamp_fault_clear,
    event_config,
    event_power_retain,
    event_battery_power_retain,
    event_gnss_packet,
    event_onDemand_packet,
} event_type;

typedef struct __attribute__((packed)){
   U4 daySecs;
   U4 timeInSec;
   U4 status;
   U2 day;
   
}rtc_t;

typedef struct __attribute__((packed)){
U1 fsUpdateRequired;
U2 index;
}mqttFsStateUpdate_t;
typedef struct __attribute__((packed)){
  U1 data[200];
  U2 dataSize; //2
  U1 topic;
  U1 maxPayloadCheck;
  rtc_t rtc;
  mqttFsStateUpdate_t mqttFsInfo;
}
mqttQueue_t;

typedef struct __attribute__((packed)) {
  unsigned char data[JSON_DATA_MAX_SIZE];
  unsigned int dataSize;
  unsigned char pktType;
  unsigned char maxPayloadCheck;
}
ilmQueue_t;


typedef struct __attribute__((packed)){
uint32_t Minvoltage;
uint32_t Minpower;
uint32_t periodicTime;
uint8_t firstBoot;
uint8_t lastFaultStatus;
uint8_t checksum;
}configStore_t;




extern mbtk_msgqref mainProcessQueue;
extern mbtk_msgqref mqttProcessQueue;

#endif