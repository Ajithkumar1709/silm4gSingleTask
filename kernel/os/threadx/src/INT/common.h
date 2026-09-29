#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "platform.h"

#define REG32(x)	*((volatile unsigned long*)(x))

#define INTC_BASE										0xd4282000
#define ICU_INT_CONF(x)							REG32(INTC_BASE + x * 4)
#define ICU_SEAGULL_IRQ_SEL_INT_NUM	REG32(INTC_BASE + 0x104)
#define ICU_MOHAWK_IRQ_SEL_INT_NUM	REG32(INTC_BASE + 0x10c)
#define ICU_SEAGULL_GBL_IRQ_MSK			REG32(INTC_BASE + 0x110)
#define ICU_MOHAWK_GBL_IRQ_MSK			REG32(INTC_BASE + 0x114)
#define ICU_INT_STATUS_0						REG32(INTC_BASE + 0x128)
#define ICU_INT_STATUS_1						REG32(INTC_BASE + 0x12C)

typedef void (*irq_handler_t)(int irqno);

int uart_printf(const char *fmt, ...);

void icu_init(void);
void icu_bind(int irqno, int priority, unsigned long handler);
void icu_handler(void);




#define BIT_0 (1 << 0)
#define BIT_1 (1 << 1)
#define BIT_2 (1 << 2)
#define BIT_3 (1 << 3)
#define BIT_4 (1 << 4)
#define BIT_5 (1 << 5)
#define BIT_6 (1 << 6)
#define BIT_7 (1 << 7)
#define BIT_8 (1 << 8)
#define BIT_9 (1 << 9)
#define BIT_10 (1 << 10)
#define BIT_11 (1 << 11)
#define BIT_12 (1 << 12)
#define BIT_13 (1 << 13)
#define BIT_14 (1 << 14)
#define BIT_15 (1 << 15)
#define BIT_16 (1 << 16)
#define BIT_17 (1 << 17)
#define BIT_18 (1 << 18)
#define BIT_19 (1 << 19)
#define BIT_20 (1 << 20)
#define BIT_21 (1 << 21)
#define BIT_22 (1 << 22)
#define BIT_23 (1 << 23)
#define BIT_24 (1 << 24)
#define BIT_25 (1 << 25)
#define BIT_26 (1 << 26)
#define BIT_27 (1 << 27)
#define BIT_28 (1 << 28)
#define BIT_29 (1 << 29)
#define BIT_30 (1 << 30)
#define BIT_31 ((unsigned)1 << 31)

#define BU_U32 			unsigned int 
#define BU_U16 			unsigned short 
#define BU_U8 			unsigned char


#define BU_REG_RDSET(x,y)  (BU_REG_WRITE(x,((BU_REG_READ(x))|y)))
#define BU_REG_RDCLEAR(x,y)  (BU_REG_WRITE(x,((BU_REG_READ(x))&(~y))))