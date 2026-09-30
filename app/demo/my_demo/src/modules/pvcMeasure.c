#include "pvcMeasure.h"
#include "math.h"
#include "mbtk_adc.h"
#include "mbtk_comm_api.h"
#include "mbtk_os.h"
#include "mbtk_gpio.h"
#define SAMPLE 5
void delay1(unsigned int i)
{
    while (i--);
}

/* No hardware timer/cycle-counter is exposed to app code on this SDK, so this
 * is a busy-wait loop, not a precise timer - actual delay depends on compiler
 * optimization level and interrupt activity.
 *
 * COUNT_PER_US is measured, not calculated, from UART start/end timestamps
 * around the 80-sample loop in pvc_measure() (previous target: 21ms total /
 * 80 = 262.5us per delay_us() call):
 *   COUNT_PER_US=153 (614MHz/4-cycles guess) -> measured ~66ms/80=~825us/call
 *   COUNT_PER_US=50  (153 * 262/825)         -> measured ~31ms/80=~388us/call
 *   COUNT_PER_US=34  (50 * 262/488)          -> measured ~39ms/80=~488us/call
 *   COUNT_PER_US=18  (34 * 262/488)          -> measured ~31ms/80=~388us/call
 *   COUNT_PER_US=12  (18 * 262/388)          -> on-device tick avg ~12.5ms/80=~156us/call
 *   COUNT_PER_US=20  (12 * 262/156)          -> on-device tick avg fluctuated 15-20ms
 *   COUNT_PER_US=24  (20 * 312/262)          -> new target 25ms total, re-verify
 * Trust the on-device "avg 80-sample loop elapsed" print (ol_os_get_ticks,
 * 5ms resolution) over serial-monitor line timestamps, which can batch
 * several lines into one received millisecond and hide the real gap.
 * Re-measure and rescale again (new = old * 312/actual_us_per_call) if the
 * next run isn't within ~25ms. */
#define COUNT_PER_US 24

void delay_us(unsigned int us)
{
    volatile unsigned int count = us * COUNT_PER_US;
    while (count--);
}

extern char buffer[150];

pvc_t pvc_measure(void)
{
    pvc_t pvc;
    int i, cnt;
    uint32_t tick_loop_start, tick_loop_end, tick_sum = 0;

    /* Now storing actual voltage readings, not raw ADC counts */
    float Voltage_temp[80];
    float current_temp[80];

    float voltage_max, current_max, voltage_min, current_min;
    float voltage_miDmv = 0, current_miDmA = 0;
    float voltage_adcsample = 0, current_adcsample = 0;
    float voltage_insta = 0, current_insta = 0;
    float current = 0;
    float voltage = 0, power = 0;
    float powerAvg = 0;
    float batVoltRaw;

    /* Pin 21 selects what the ADC sees: HIGH = battery sense,
     * LOW = AC voltage/current sense. Short settle delay after each switch. */

    /* Battery voltage is a steady DC signal (unlike the AC current/voltage
     * lines), so a plain 10-sample average is enough -- no RMS/min-max
     * midpoint calc needed. */
    ol_set_pin_level(mbtk_pin_21, mbtk_gpio_level_high);
     ol_os_task_sleep(10); // 50ms

    batVoltRaw = 0;
    for (i = 0; i < 10; i++) {
        uint32_t rawSample = ol_adc_get_vol(mbtk_adc_index_2);
      //  op_uart_printf("pvc_measure: batVolt raw sample[%d]=%lu\r\n", i, (unsigned long)rawSample);
        batVoltRaw += rawSample;
    }
    batVoltRaw /= 10;
    /* %f is avoided here since embedded printf implementations often don't
     * support floating point specifiers without extra linker support -
     * this codebase's other prints all stick to integer formats. */
    op_uart_printf("pvc_measure: batVolt raw avg=%lu\r\n", (unsigned long)batVoltRaw);

    /* Battery-sense divider on this hardware: VBAT -> R9(100k) -> tap -> R12(47k) -> GND.
     * ol_adc_get_vol() already returns millivolts, so just scale back up by
     * (R9+R12)/R12 = 147/47 to recover actual VBAT in mV -- no further unit
     * conversion needed. */
    pvc.batVolt = (uint16_t)(batVoltRaw * (147.0f / 47.0f));
    op_uart_printf("pvc_measure: batVolt scaled=%u\r\n", pvc.batVolt);

    ol_set_pin_level(mbtk_pin_21, mbtk_gpio_level_low);
   ol_os_task_sleep(10); // 50ms

    for (cnt = 0; cnt < SAMPLE; cnt++) {
        op_uart_printf("pvc_measure: 80-sample loop start cnt=%d\r\n", cnt);

        tick_loop_start = ol_os_get_ticks();
        for (i = 0; i < 80; i++) {
            /* Voltage channel - direct voltage value, no raw->volt conversion needed */
            Voltage_temp[i] = ol_adc_get_vol(mbtk_adc_index_2);
            op_uart_printf("pvc_measure: raw voltage[%d]=%lu\r\n", i, (unsigned long)Voltage_temp[i]);

            /* Current-sense channel - adjust index to whichever channel your
               current sense line is wired to */
            current_temp[i] = ol_adc_get_vol(mbtk_adc_index_1);
          //  op_uart_printf("pvc_measure: raw current[%d]=%lu\r\n", i, (unsigned long)current_temp[i]);

            delay_us(312); /* 25000us / 80 samples = 312.5us per iteration */
        }
        tick_loop_end = ol_os_get_ticks();
        tick_sum += (tick_loop_end - tick_loop_start);

        op_uart_printf("pvc_measure: 80-sample loop end cnt=%d elapsed=%ums\r\n",
                       cnt, (tick_loop_end - tick_loop_start) * 5);

        /* Find max/min for this batch of 80 samples */
        voltage_max = current_max = 0;
        voltage_min = current_min = 999999.0f; /* large sentinel instead of RESOLUTION */
        for (i = 0; i < 80; i++) {
            voltage_max = (Voltage_temp[i] > voltage_max) ? Voltage_temp[i] : voltage_max;
            voltage_min = (Voltage_temp[i] < voltage_min) ? Voltage_temp[i] : voltage_min;
            current_max = (current_temp[i] > current_max) ? current_temp[i] : current_max;
            current_min = (current_temp[i] < current_min) ? current_temp[i] : current_min;
        }
        op_uart_printf("pvc_measure: cnt=%d voltage max=%ldmV min=%ldmV | current max=%ldmV min=%ldmV\r\n",
                       cnt, (long)voltage_max, (long)voltage_min, (long)current_max, (long)current_min);

        /* ol_adc_get_vol() returns raw millivolts; convert to volts here the
         * same way the original Nuvoton code converted raw ADC counts to
         * volts (raw * REF_VOLT / RESOLUTION) before applying the sensor
         * calibration constants below unchanged. */
        voltage_miDmv = ((voltage_max + voltage_min) / 2.0f) / 1000.0f;
        current_miDmA = ((current_max + current_min) / 2.0f) / 1000.0f;
        /* printed in mV (x1000) since %f isn't supported */
        op_uart_printf("pvc_measure: cnt=%d voltage_miDmv=%ldmV current_miDmA=%ldmV\r\n",
                       cnt, (long)(voltage_miDmv * 1000.0f), (long)(current_miDmA * 1000.0f));

        voltage_adcsample = voltage_insta = current_adcsample = current_insta = power = 0;
        for (i = 0; i < 80; i++) {
            voltage_insta = (Voltage_temp[i] / 1000.0f) - voltage_miDmv;
            voltage_adcsample += voltage_insta * voltage_insta;

            current_insta = (current_temp[i] / 1000.0f) - current_miDmA;
            current_adcsample += current_insta * current_insta;

            power += (((current_insta / 1.0f) * 1000.0f) / 68.0f) *
                     ((voltage_insta * 440000.0f) /330.0f);
        }
        powerAvg += (power / 80);

        voltage += (sqrt(voltage_adcsample / 80) * 440000.0f) / 330.0f;
        current += (((sqrt(current_adcsample / 80)) / 1.0f) * 1000.0f) / 68.0f;
    }

    op_uart_printf("pvc_measure: avg 80-sample loop elapsed=%ums (tick, target=25ms)\r\n",
                   (tick_sum / SAMPLE) * 5);

    pvc.voltage = voltage / SAMPLE;
    pvc.current = (current / SAMPLE)*1000; /* convert to mA for storage in struct */
    powerAvg = powerAvg / SAMPLE;
    pvc.power = (powerAvg < 0) ? (powerAvg * -1.0f) : powerAvg;
    pvc.power = (pvc.power < 5) ? 0 : pvc.power;
   
    return pvc;
}