/* ---------------- lamp_monitor.h ---------------- */
#ifndef LAMP_MONITOR_H
#define LAMP_MONITOR_H

#include <stdint.h>
#include <stdbool.h>

/* ---------------- Feature enable/disable (compile-time only) ---------------- */
#define FEATURE_BATVOLT_MONITOR   1   /* set to 0 to disable batVolt logic */
#define FEATURE_FAULT_MONITOR     1   /* set to 0 to disable fault logic */
#define DEBOUNCE_LAMPSTATE     1


/* Lamp-fault debounce: number of consecutive occurrences to set / clear */
#define LAMP_FAULT_DEBOUNCE_COUNT   3u


/* Thresholds */
#define MIN_VOLT           100u
#define MIN_POWER          10u


#define BATVOLT_LOW_THRESHOLD   3000u
#define BATVOLT_LOW_HYSTERESIS   100u


/* Lamp states */
#define LAMP_OFF      0
#define LAMP_ON       1
#define LAMP_UNKNOWN  2
#define LAMP_FAULT    3

/* Packet types */
#define PKT_NONE     0
#define PKT_BOOTON   1
#define PKT_TRIGGER  2
#define PKT_LIVE     3
#define ON_DEMAND    4
#define SEND_CONFIG_ATTRIBUTES 5
#define OTA_UPDATE   6

/* faultStatus bitmask */
#define FAULT_NONE      0x00u
#define FAULT_LAMP_BIT  0x01u   /* bit0 = lamp fault    -> 1 */
#define FAULT_BAT_BIT   0x02u   /* bit1 = battery fault -> 2 */
                                 /* both bits set        -> 3 */




typedef struct __attribute__((packed)) {
    uint8_t  pktType;
    uint8_t  lmpState;
    uint32_t voltage;
    uint32_t power;
    uint32_t batVolt;
    uint8_t  faultStatus;
    uint32_t  utc;
    uint32_t current;
} serveTransmitPkt_t;


void lampMonitor_init(void);
void lampMonitor_requestBootOnPkt(void);

uint8_t lampMonitor_evaluateState(uint32_t voltage, uint32_t power, uint32_t minV, uint32_t minW);
serveTransmitPkt_t lampMonitor_isPacketSendRequired(uint32_t voltage,
                                                     uint32_t power,
                                                     uint32_t batVolt,
                                                     bool periodicStatus,
                                                     uint32_t minW,
                                                     uint32_t minV);

#endif /* LAMP_MONITOR_H */


