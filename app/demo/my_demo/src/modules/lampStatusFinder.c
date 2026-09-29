
/* ---------------- lamp_monitor.c ---------------- */
#include "lampStatusFinder.h"
#include "memoryHandle.h"
#include "mbtk_comm_api.h"
#include <string.h>
/* Module-private state */
static uint8_t   lampPreviousState = LAMP_UNKNOWN;
static uint32_t  periodicDataTimer = 0;

static bool      bootOnPkt = true;
static uint8_t   faultStatusPrevious = FAULT_NONE;

/* Lamp-fault debounce state */
static uint8_t lampFaultSetCounter   = 0;
static uint8_t lampFaultClearCounter = 0;
static bool    lampFaultLatched      = false;

void lampMonitor_init(void)
{
    uint8_t persistedFaultStatus = memoryHandle_getConfigStore()->lastFaultStatus;

    periodicDataTimer   = 0;
    bootOnPkt           = true;
    faultStatusPrevious = persistedFaultStatus;

    lampPreviousState = LAMP_UNKNOWN;

    if (persistedFaultStatus & FAULT_LAMP_BIT) {
        /* Lamp fault was active before power-off: resume already-latched
         * so the fault is reported again without waiting for a fresh
         * debounce confirmation. */
        lampFaultSetCounter   = LAMP_FAULT_DEBOUNCE_COUNT;
        lampFaultClearCounter = 0;
        lampFaultLatched      = true;
    } else {
        lampFaultSetCounter   = 0;
        lampFaultClearCounter = LAMP_FAULT_DEBOUNCE_COUNT;
        lampFaultLatched      = false;
    }

    op_uart_printf("-1-lampStatusFinder:init persistedFaultStatus=%u\r\n", persistedFaultStatus);
}

void lampMonitor_requestBootOnPkt(void)
{
    bootOnPkt = true;
}

/* Pure function: raw instantaneous lamp state from voltage/current readings */
uint8_t lampMonitor_evaluateState(uint32_t voltage, uint32_t power, uint32_t minV, uint32_t minW)
{
    if ((voltage > minV) && (power > minW)) {
        return LAMP_ON;
    } else if ((voltage < minV) && (power < minW)) {
        return LAMP_OFF;
    } else if ((voltage > minV) && (power < minW)) {
        return LAMP_FAULT;
    }
    return LAMP_UNKNOWN;
}

/* Fault latch: LAMP_FAULT raw condition must occur LAMP_FAULT_DEBOUNCE_COUNT
 * times consecutively to SET, and LAMP_ON must occur LAMP_FAULT_DEBOUNCE_COUNT
 * times consecutively to CLEAR. LAMP_OFF/LAMP_UNKNOWN are ambiguous readings
 * and leave the latch untouched. While a fault is not yet confirmed, the
 * reported lmpState holds its previous value (see isPacketSendRequired).
 */
static void lampMonitor_updateFaultLatch(uint8_t rawState)
{
    if (rawState == LAMP_FAULT) {
        lampFaultClearCounter = 0;
        if (lampFaultSetCounter < LAMP_FAULT_DEBOUNCE_COUNT) {
            lampFaultSetCounter++;
        }
        if (lampFaultSetCounter >= LAMP_FAULT_DEBOUNCE_COUNT) {
            lampFaultLatched = true;
        }
    } else if (rawState == LAMP_ON) {
        lampFaultSetCounter = 0;
        if (lampFaultClearCounter < LAMP_FAULT_DEBOUNCE_COUNT) {
            lampFaultClearCounter++;
        }
        if (lampFaultClearCounter >= LAMP_FAULT_DEBOUNCE_COUNT) {
            lampFaultLatched = false;
        }
    }
    /* rawState == LAMP_OFF or LAMP_UNKNOWN: hold latch as-is */
}

#if FEATURE_BATVOLT_MONITOR
/* Pure function: decide low-battery bool with hysteresis */
static bool lampMonitor_evaluateBatLow(uint32_t batVolt, bool prevBatLow)
{
    if (!prevBatLow && (batVolt < BATVOLT_LOW_THRESHOLD)) {
        return true;
    }
    if (prevBatLow && (batVolt > (BATVOLT_LOW_THRESHOLD + BATVOLT_LOW_HYSTERESIS))) {
        return false;
    }
    return prevBatLow;
}
#endif

/* Build bitwise faultStatus from the (debounced) fault latch + batlow flag */
static uint8_t lampMonitor_buildFaultStatus(bool lampFault, bool batLow)
{
    uint8_t fault = FAULT_NONE;

#if FEATURE_FAULT_MONITOR
    if (lampFault) {
        fault |= FAULT_LAMP_BIT;
    }

    #if FEATURE_BATVOLT_MONITOR
    if (batLow) {
        fault |= FAULT_BAT_BIT;
    }
    #else
    (void)batLow;
    #endif

#else
    (void)lampFault;
    (void)batLow;
#endif

    return fault;
}

/* Decide whether/what packet to send */
serveTransmitPkt_t lampMonitor_isPacketSendRequired(uint32_t voltage,
                                                     uint32_t power,
                                                     uint32_t batVolt,
                                                     bool periodicStatus,
                                                     uint32_t minW,
                                                     uint32_t minV)
{
    serveTransmitPkt_t pkt;
    bool batLowNow = false;
    bool lampFaultNow;
    bool lampChanged, faultChanged;
    uint8_t rawState;

   memset(&pkt,0,sizeof(pkt));
    pkt.voltage = voltage;
    pkt.power = power;
    pkt.pktType = PKT_NONE;

    rawState = lampMonitor_evaluateState(voltage, power, minV, minW);
    pkt.lmpState = rawState;

#if DEBOUNCE_LAMPSTATE
    lampMonitor_updateFaultLatch(rawState);
    lampFaultNow = lampFaultLatched;
#else
    lampFaultNow = (rawState == LAMP_FAULT);
#endif

    /* Fault SET/CLEAR needs LAMP_FAULT_DEBOUNCE_COUNT consecutive readings.
     * - Latched: always report LAMP_FAULT (held until 3x ON clears it).
     * - Raw FAULT not yet confirmed: hold the last reported state, or
     *   LAMP_UNKNOWN on a boot packet (no trustworthy previous state).
     * - Otherwise ON/OFF is reported immediately (single reading). */
    if (lampFaultNow) {
        pkt.lmpState = LAMP_FAULT;
    } else if (rawState == LAMP_FAULT) {
        pkt.lmpState = bootOnPkt ? LAMP_UNKNOWN : lampPreviousState;
    }

#if FEATURE_BATVOLT_MONITOR
    pkt.batVolt = batVolt;
    batLowNow = lampMonitor_evaluateBatLow(batVolt, (faultStatusPrevious & FAULT_BAT_BIT) != 0);
#else
    pkt.batVolt = 0;
#endif

    pkt.faultStatus = lampMonitor_buildFaultStatus(lampFaultNow, batLowNow);

    lampChanged  = (pkt.lmpState != lampPreviousState);
    faultChanged = (pkt.faultStatus != faultStatusPrevious);

    /* 1. Boot packet has highest priority */
    if (bootOnPkt) {
        lampPreviousState   = pkt.lmpState;
        faultStatusPrevious = pkt.faultStatus;
        bootOnPkt = false;
        pkt.pktType = PKT_BOOTON;
        op_uart_printf("-1-lampStatusFinder:PKT_BOOTON, lmpState=%u, faultStatus=%u\r\n", pkt.lmpState, pkt.faultStatus);
        return pkt;
    }

    /* 2. Trigger packet - lamp state changed OR fault status changed */
    if (lampChanged || faultChanged) {
        lampPreviousState   = pkt.lmpState;
        faultStatusPrevious = pkt.faultStatus;
        pkt.pktType = PKT_TRIGGER;
        op_uart_printf("-1-lampStatusFinder:PKT_TRIGGER, lmpState=%u, faultStatus=%u\r\n", pkt.lmpState, pkt.faultStatus);

        if (faultChanged) {
            memoryHandle_getConfigStore()->lastFaultStatus = pkt.faultStatus;
            memoryHandle_writeConfigStoreWithBackup();
        }

        return pkt;
    }

    /* 3. Periodic live packet */
    if (periodicStatus) {
        pkt.pktType = PKT_LIVE;
        return pkt;
    }

    return pkt;
}