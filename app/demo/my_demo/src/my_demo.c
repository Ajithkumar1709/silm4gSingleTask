#include "mbtk_comm_api.h"
#include "common.h"
#include "mbtk_os.h"
#include "mbtk_gpio.h"
#include "mbtk_pmu.h"
#include "modules/lampStatusFinder.h"
#include <stdio.h>
#include <string.h>
#include "modules/publish.h"
#include "ntp_api.h"
#include "modules/memoryHandle.h"
#include "modules/pvcMeasure.h"
#include "modules/otaHandler.h"
#include "modules/dataStore.h"
#include "mqttTask.h"
/* mainProcessQueue is kept only so mqtt_task_message() (inbound RPC callback
 * in mqttTask.c) has something to check; my_demo no longer creates or reads
 * it, so RPC messages are dropped (logged) rather than processed. */
mbtk_msgqref mainProcessQueue=NULL;

/* otaHandler.c still reports OTA status via this queue; my_demo owns it now
 * and drains/publishes it once per cycle while connected. */
mbtk_msgqref mqttProcessQueue=NULL;

/* 30s @ 5ms/tick, matching ol_os_task_sleep() usage elsewhere in this file */
#define MY_DEMO_CYCLE_SLEEP_TICKS 3000//6000
#define MY_DEMO_CONNECT_RETRY_COUNT 3

#define TIMERCALLBACKSEC 30
static volatile uint32_t periodicCounter = 0;
static volatile unsigned char perodicStatus = false;

/* Fires every 30s off an independent RTOS timer (not tied to my_demo's own
 * sleep cadence, which can drift when a cycle spends extra time connecting
 * /publishing). Only accumulates a counter and sets a flag; the main loop
 * consumes/clears it. */
static void timecallBack(uint32_t arg)
{
    (void)arg;
    periodicCounter += TIMERCALLBACKSEC;
    if (configStore.periodicTime <= periodicCounter) {
        perodicStatus = true;
        periodicCounter = 0;
    }
}

/* ol_ntp_sync_time() is fired-and-forget in mqttTask.c right after the data
 * call connects, so it may still be in flight the first time we build a
 * telemetry packet (e.g. PKT_BOOTON right after mqtt_connected goes true).
 * Poll for a short bounded time instead of checking once, so we don't fall
 * back to utc=0 (renders as 1970-01-01 on the dashboard) just because NTP
 * hadn't finished yet. */
static uint32_t getUtcTimeWaitForSync(void)
{
    int retry;

    for (retry = 0; retry < 20; retry++) { /* 20 * 100ms = up to 2s */
        if (ol_ntp_get_status() == 1) {
            return (uint32_t)ol_ntp_get_utc_time();
        }
        ol_os_task_sleep(20); // 100ms (1 tick = 5ms)
    }
    op_uart_printf("-1-mydemo:NTP not synced after 2s wait, sending utc=0\r\n");
    return 0;
}

static void led_pin16_blink(void)
{
    mbtk_pin_config_struct config;
    config.gpio_af_num = mbtk_gpio_config_maf0;
    config.gpio_pull = mbtk_gpio_config_pull_low;
    config.gpio_sleep = mbtk_gpio_config_sleep_none;
    config.gpio_edge = mbtk_gpio_config_edge_none;

    if (ol_pin_config(mbtk_pin_16, &config) != 0) {
        op_uart_printf("led_pin16_blink : ol_pin_config fail\r\n");
        return;
    }

    if (ol_set_pin_dir(mbtk_pin_16, mbtk_gpio_dir_output) != 0) {
        op_uart_printf("led_pin16_blink : ol_set_pin_dir fail\r\n");
        return;
    }

    for (int i = 0; i < 10; i++) {
        ol_set_pin_level(mbtk_pin_16, mbtk_gpio_level_high);
        ol_os_task_sleep(100); // 500ms (1 tick = 5ms)
        ol_set_pin_level(mbtk_pin_16, mbtk_gpio_level_low);
        ol_os_task_sleep(100); // 500ms
    }
}

/* Pin 21 drives a hardware analog mux shared with the current-sense ADC
 * channel: LOW routes battery voltage onto that line, HIGH routes the
 * current-sense signal. Configured once here; pvcMeasure.c toggles the
 * level around each reading. */
static void pin21_output_init(void)
{
    mbtk_pin_config_struct config;
    /* Per L511-5 Series PIN Application spec: physical pin 21 (MAIN_DCD)'s
     * Aux Func.0 is VCXO_OUT, Aux Func.1 is GPIO86 -- maf0 (the default used
     * elsewhere in this file, e.g. led_pin16_blink()) leaves this pin acting
     * as VCXO_OUT, not GPIO, which is why toggling its level had no effect
     * on the ADC mux. maf1 selects the GPIO function. */
    config.gpio_af_num = mbtk_gpio_config_maf1;
    config.gpio_pull = mbtk_gpio_config_pull_low;
    config.gpio_sleep = mbtk_gpio_config_sleep_none;
    config.gpio_edge = mbtk_gpio_config_edge_none;

    if (ol_pin_config(mbtk_pin_21, &config) != 0) {
        op_uart_printf("pin21_output_init : ol_pin_config fail\r\n");
        return;
    }

    if (ol_set_pin_dir(mbtk_pin_21, mbtk_gpio_dir_output) != 0) {
        op_uart_printf("pin21_output_init : ol_set_pin_dir fail\r\n");
        return;
    }

    /* Default to HIGH (current-sense routed through) so behavior before the
     * first pvc_measure() call matches what it was before this pin existed. */
    
}

void my_demo(void *arg)
{
    (void)arg;

    pvc_t pvc;
    serveTransmitPkt_t serveTransmitPkt;
    mqtt_client_t *client = NULL;
    mqttQueue_t mqttQueue = {0};
    unsigned char mqttConnectedToserver;
    int retry;
    mbtk_ostimerref periodicTimerRef = NULL;
    U2 lastStoredIndex = 0;

    led_pin16_blink();
    pin21_output_init();
    ol_os_msgq_creat(&mqttProcessQueue, "mqttProcessQueue", sizeof(mqttQueue), 5, MBTK_OS_FIFO);
    memoryHandle_readConfigStoreWithBackup();
    otaHandler_checkUpgradeResult();
    lampMonitor_init();
    dataStore_init();

    ol_os_timer_creat(&periodicTimerRef);
    ol_os_timer_start(periodicTimerRef, MY_DEMO_CYCLE_SLEEP_TICKS, MY_DEMO_CYCLE_SLEEP_TICKS, timecallBack, 0);

    /* No fixed-duration "deep sleep for N seconds" API exists in this SDK.
     * This only lets the RTOS idle loop opportunistically drop into low
     * power between cycles; the 30s cadence is still just a tick sleep. */
   // ol_set_syssleep_status(MBTK_SLEEP_ENABLE);

    while (1) {

//================================measuring pvc and checking if packet needs to be sent===============================
        op_uart_printf("-1-mydemo:my_demo Process:configStore.Minvoltage=%d,configStore.Minpower=%d,configStore.periodicTime=%d",configStore.Minvoltage,configStore.Minpower,configStore.periodicTime);
        op_uart_printf("-1-mydemo:periodicCounter=%lu\r\n", periodicCounter);

        pvc = pvc_measure();
        op_uart_printf("-1-mydemo:pvc voltage=%d, power=%d, batVolt=%d\r\n",(int)pvc.voltage, (int)pvc.power, (int)pvc.batVolt);
        serveTransmitPkt = lampMonitor_isPacketSendRequired(pvc.voltage, pvc.power, pvc.batVolt, perodicStatus, configStore.Minpower, configStore.Minvoltage);
        serveTransmitPkt.utc = getUtcTimeWaitForSync();
        serveTransmitPkt.current = (uint32_t)pvc.current;
        mqttConnectedToserver = false;
//if packet needs to be sent, connect mqtt
        if (serveTransmitPkt.pktType) {
             if (serveTransmitPkt.pktType == PKT_LIVE) {
                perodicStatus=false;
              }
            mqttQueue = storeDtata(serveTransmitPkt);
            lastStoredIndex = mqttQueue.mqttFsInfo.index;
            op_uart_printf("-1-mydemo:lastStoredIndex=%d\r\n", lastStoredIndex);
            op_uart_printf("-1-mydemo:stored packet pktType=%d utc=%lu, mqttQueue index=%d dataSize=%d fsUpdateRequired=%d\r\n",
                           serveTransmitPkt.pktType, (unsigned long)serveTransmitPkt.utc,
                           mqttQueue.mqttFsInfo.index, mqttQueue.dataSize, mqttQueue.mqttFsInfo.fsUpdateRequired);

            for (retry = 0; retry < MY_DEMO_CONNECT_RETRY_COUNT; retry++) {
                if (networkCheckRecovery(&client) == 0) {
                    mqttConnectedToserver = true;
                    break;
                }
            }
        }
//if connected to server, sending the packet and requesting shared attributes
        if (mqttConnectedToserver) {
            if (serveTransmitPkt.pktType == PKT_BOOTON) {
                static mqttQueue_t mqttAttrQueue;

                op_uart_printf("-1-mydemo:PKT_BOOTON -> publish attributes\r\n");
                mqttAttrQueue = publishattributesPacketCcidImsiJson();
                if (mqtt_publish(client, mqttAttrQueue.data, mqttAttrQueue.dataSize, mqttAttrQueue.topic) != 0) {
                    op_uart_printf("-1-mydemo:PKT_BOOTON publish failed, retry next cycle\r\n");
                    lampMonitor_requestBootOnPkt();
                }
            }

            op_uart_printf("-1-mydemo:pktType=%d -> publish telemetry\r\n", serveTransmitPkt.pktType);
            op_uart_printf("-1-mydemo:before publish, mqttQueue index=%d dataSize=%d fsUpdateRequired=%d\r\n",
                           mqttQueue.mqttFsInfo.index, mqttQueue.dataSize, mqttQueue.mqttFsInfo.fsUpdateRequired);
            if ((mqtt_publish(client, mqttQueue.data, mqttQueue.dataSize, mqttQueue.topic) == 0)&& (mqttQueue.mqttFsInfo.fsUpdateRequired)) {
                op_uart_printf("-1-mydemo:publish succeeded, marking index=%d uploaded\r\n", mqttQueue.mqttFsInfo.index);
                fsDataUpdateUploadState(mqttQueue.mqttFsInfo.index);
            }


            op_uart_printf("-1-mydemo:requesting shared attributes\r\n");
            sharedAttrResponseReceived = 0;
            mqttQueue = publish_req_shared_attributes_JSON();
            mqtt_publish(client, mqttQueue.data, mqttQueue.dataSize, mqttQueue.topic);

            /* bounded wait for the response callback (mqttTask.c) to fire,
             * same pattern as getUtcTimeWaitForSync() above */
            for (retry = 0; retry < 20 && !sharedAttrResponseReceived; retry++) { /* 20*100ms = up to 2s */
                ol_os_task_sleep(20);
            }
            if (sharedAttrResponseReceived) {
                op_uart_printf("-1-mydemo:shared attributes response received\r\n");
            } else {
                op_uart_printf("-1-mydemo:shared attributes response timed out\r\n");
            }

            payLoadAutoUpload(lastStoredIndex, client);
        }
        ol_os_task_sleep(MY_DEMO_CYCLE_SLEEP_TICKS);
    }

}