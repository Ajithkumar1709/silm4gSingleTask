#ifndef PVC_MEASURE_H
#define PVC_MEASURE_H
#include "stdint.h"
typedef struct __attribute__((packed)){
  float voltage;
  float current;
  float power;
  uint16_t batVolt;
}pvc_t;

extern pvc_t pvc_measure(void);
extern void delay_us(unsigned int us);
#endif // PVC_MEASURE_H