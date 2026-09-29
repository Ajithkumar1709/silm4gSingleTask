#include "common.h"
#include "guilin_lite.h"
#include "bsp.h"

/****************************************************************
 * console output
 ****************************************************************/
 
#define CP_UART2_BASE   0xd4018000  //STUART CP_UART
#define CP_UART_BASE   0xd4017000	//FFUART AP_UART
 
void cp_uart_init()
{
	volatile unsigned long temp, *r;
	
	/* PMUM_ACGR */
	writel(0xffffffff,0xd4050024); 

	writel(0x03,0xd401503c); //AIB

	/* UART clock control/UCER */
	writel(0x13,0xd4015000);

    if (CHIP_IS_CRANELR || CHIP_IS_CRANELG || CHIP_IS_CRANELRH)
    {
        /* MFPR GPIO 71 */
        r = (volatile unsigned long*)0xd401e1bc; //AP_UART1_RXD
        *r = 0xd0c1;
        
        /* MFPR GPIO 72 */
        r = (volatile unsigned long*)0xd401e1c0; //AP_UART1_TXD
        *r = 0xd0c1;
    }
    else if (CHIP_IS_CRANELS_A0)
    {
        /* MFPR GPIO 27 */
        r = (volatile unsigned long*)0xd401e148; //AP_UART1_RXD
        *r = 0xd0c1;

        /* MFPR GPIO 28 */
        r = (volatile unsigned long*)0xd401e14C; //AP_UART1_TXD
        *r = 0xd0c1;

    }
    else
    {
    	/* MFPR GPIO 29 */
    	r = (volatile unsigned long*)0xd401e150; //UART1_RXD
    	*r = 0xd0c1;

    	/* MFPR GPIO 30 */
    	r = (volatile unsigned long*)0xd401e154; //UART1_TXD
    	*r = 0xd0c1;
    }

	// UALCR
	r = (volatile unsigned long*)(CP_UART_BASE + 0xc);
	*r = 0x83;

	// UADLL
	r = (volatile unsigned long*)(CP_UART_BASE + 0x0);
	*r = 0x08; //0x08 for 14.7456M on DKB, 0x7 for 13M on FPGA;
	temp = *r;

	// UADLH
	r = (volatile unsigned long*)(CP_UART_BASE + 0x4);
	*r = 0;

	// UALCR
	r = (volatile unsigned long*)(CP_UART_BASE + 0xC);
	*r &= ~0x80;

	// UAFCR
	r = (volatile unsigned long*)(CP_UART_BASE + 0x8);
	*r = 0x07;

	// UAIER
	r = (volatile unsigned long*)(CP_UART_BASE + 0x4);
	*r = 0x40;
}
 
void cp_uart_putc(const char ch)
{
	volatile unsigned long* ualsr;
	volatile unsigned long* uathr;

	ualsr = (volatile unsigned long*)(CP_UART_BASE + 0x14);
	uathr = (volatile unsigned long*)(CP_UART_BASE);

	while (!(*ualsr & 0x20));

	*uathr = ch;
}
 
int uart_printf(const char *fmt, ...)
{
#if !defined (ENABLE_SLT_FEATURE)
	va_list ap;
	char buffer[128], *ptr;
	void (*console_output)(const char ch);

	memset(buffer, 0, sizeof(buffer));
	va_start(ap, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, ap);
	va_end(ap);

	console_output = cp_uart_putc;

	ptr = &buffer[0];
	while (*ptr)
	{
		console_output(*ptr);
		ptr ++;
	}

	return ptr - buffer;
#else
    return 0;
#endif
}

void display_binary(void *data, size_t len)
{
#define XK_BYTE_COUNT_EACH_LINE 8

    static const char hex[] = "0123456789ABCDEF";
    static const char seperator = ' ';
    unsigned char *p = (unsigned char *)data;
    char stash[XK_BYTE_COUNT_EACH_LINE * (2 + 2 + 1) + 1];
    size_t j = 0;
    size_t i;

	uart_printf("\r\n----------------------------\r\n");
    uart_printf("BASE=[%0.8x]LEN=[%0.8x]",data,len);

    for (i = 0; i < len; i=i+2) {
        //stash[j++] = '0';
        //stash[j++] = 'x';
        stash[j++] = hex[(p[i] >> 4) & 0xF];
        stash[j++] = hex[p[i] & 0xF];

        stash[j++] = hex[(p[i+1] >> 4) & 0xF];
        stash[j++] = hex[p[i+1] & 0xF];

        stash[j++] = seperator;
        if (j == sizeof(stash) - 1) {
            stash[j] = '\0';
            uart_printf("\r\n[%0.8x]%s",((unsigned int)data + i - 0xe), stash);
            j = 0;
        }
    }
    if (j) {
        stash[j] = '\0';
        uart_printf("\r\n[%0.8x]%s",((unsigned int)data + i - 0xe + XK_BYTE_COUNT_EACH_LINE), stash);
    }
	uart_printf("\r\n----------------------------\r\n");
}

#define AIB_UART_IO_REG                  0xD401E81C
extern int GuilinLite_LDO_Set_VOUT(unsigned char reg, unsigned char value);

void _AIB_Secure_Write(unsigned int address, unsigned int value)
{
	BU_REG_WRITE(0xd4015050, 0xBABA);	
	BU_REG_WRITE(0xd4015054, 0xEB10);
	BU_REG_WRITE(address, value);
}

UINT32 _AIB_Secure_Read(unsigned int address)
{
	UINT32 val;
	BU_REG_WRITE(0xd4015050, 0xBABA);	
	BU_REG_WRITE(0xd4015054, 0xEB10);
	val = BU_REG_READ(address);
	return val;
}

void AIB_UART_IO_Set_1_8V(void)
{
    volatile unsigned int val = 0;

    val = _AIB_Secure_Read(AIB_UART_IO_REG); //AIB_UART_IO_REG
    val |= 0x85;
    _AIB_Secure_Write(AIB_UART_IO_REG, val);
}

void PMIC_Set_UART_1_8V(void)
{
    if(PMIC_IS_PM803())
    {
        GuilinLite_LDO_Set_VOUT(GUILIN_LITE_LDO7_ACTIVE_VOUT_REG, GUILIN_LITE_LDO7_ACTIVE_1V80);
    }
    AIB_UART_IO_Set_1_8V();
}

void PMIC_Set_UART_Poweron(void)
{
    if(PMIC_IS_PM803())
    {
        GuilinLite_Ldo_7_set(TRUE);
    }
}

void cp_uart2_init()
{
	volatile unsigned long temp, *r;

	if (IsChipCraneL() || IsChipCraneL_Z1() || IsChipCraneLS()) {
      PMIC_Set_UART_1_8V();
      PMIC_Set_UART_Poweron();
    }

#if 0
	/* PMUM_ACGR */
	writel(0xdffefffe,0xd4051024); //0x2DFFFF; //0xdffefffe;

	writel(0x03,0xd401503c); //AIB

	/* UART clock control/UCER */
	writel(0x3,0xd403b01c);

	/* MFPR GPIO 120 */
	r = (volatile unsigned long*)0xd401e384;
	*r = 0xd0c2;

	/* MFPR GPIO 121 */
	r = (volatile unsigned long*)0xd401e388;
	*r = 0xd0c2;
#else
	/* PMUM_ACGR */
	writel(0xfffffffe,0xd4050024);
	
	writel(0x03,0xd401503c); //AIB 

	/* UART clock control/UCER */
	writel(0x13,0xd4015004);

	/* MFPR GPIO 51 */
	r = (volatile unsigned long*)0xd401e1a8;
	*r = 0xd0c1;	

	/* MFPR GPIO 52 */
	r = (volatile unsigned long*)0xd401e1ac;
	*r = 0xd0c1;
#endif

	// UALCR
	r = (volatile unsigned long*)(CP_UART2_BASE + 0xc);
	*r = 0x83;

	// UADLL
	r = (volatile unsigned long*)(CP_UART2_BASE + 0x0);
	*r = 0x08; //0x08 for 14.7456M on DKB, 0x7 for 13M on FPGA;

	// UADLH
	r = (volatile unsigned long*)(CP_UART2_BASE + 0x4);
	*r = 0;
	temp = *r;

	// UALCR
	r = (volatile unsigned long*)(CP_UART2_BASE + 0xC);
	*r &= ~0x80;

	// UAFCR
	r = (volatile unsigned long*)(CP_UART2_BASE + 0x8);
	*r = 0x07;

	// UAIER
	r = (volatile unsigned long*)(CP_UART2_BASE + 0x4);
	*r = 0x40;
}
 
void cp_uart2_putc(const char ch)
{
	volatile unsigned long* ualsr;
	volatile unsigned long* uathr;

	ualsr = (volatile unsigned long*)(CP_UART2_BASE + 0x14);
	uathr = (volatile unsigned long*)(CP_UART2_BASE);

	while (!(*ualsr & 0x20));

	*uathr = ch;
}
 
int uart2_printf(const char *fmt, ...)
{
	va_list ap;
	char buffer[128], *ptr;
	void (*console_output)(const char ch);

	memset(buffer, 0, sizeof(buffer));
	va_start(ap, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, ap);
	va_end(ap);

	console_output = cp_uart2_putc;

	ptr = &buffer[0];
	while (*ptr)
	{
		console_output(*ptr);
		ptr ++;
	}

	return ptr - buffer;
}

//added by xiehaifei AT uart output string to mcu
#define UPDATER_AT_UART_SUPPORT
#ifdef UPDATER_AT_UART_SUPPORT
 #define AT_UART1_BASE   0xd4018000	
void updater_at_uart1_init(void)
{
	volatile unsigned long *r;
	if (IsChipCraneL() || IsChipCraneL_Z1() || IsChipCraneLS()||IsChipCraneLR()) {
      PMIC_Set_UART_1_8V();
      PMIC_Set_UART_Poweron();
    }
	/* PMUM_ACGR */
	writel(0xffffffff,0xd4050024); 

	writel(0x03,0xd401503c); /* AIB clock */
	
	/* UART clock control/UCER */
	writel(0x00,0xd4015004);

	{
		unsigned long uart_delay = 0xffff;
		while(uart_delay--);
	}

	/* UART clock control/UCER */
	writel(0x13,0xd4015004);

	/* MFPR GPIO 51 */
	r = (volatile unsigned long*)0xd401e1a8;
	*r = 0xd0c1;

	/* MFPR GPIO 52 */
	r = (volatile unsigned long*)0xd401e1ac;
	*r = 0xd0c1;

	// UALCR
	r = (volatile unsigned long*)(AT_UART1_BASE + 0xc);
	*r = 0x83;

	// UADLL
	r = (volatile unsigned long*)(AT_UART1_BASE + 0x0);
	*r = 0x08; //0x08 for 14.7456M on DKB, 0x7 for 13M on FPGA;

	// UADLH
	r = (volatile unsigned long*)(AT_UART1_BASE + 0x4);
	*r = 0;

	// UALCR
	r = (volatile unsigned long*)(AT_UART1_BASE + 0xC);
	*r &= ~0x80;

	// UAFCR
	r = (volatile unsigned long*)(AT_UART1_BASE + 0x8);
	*r = 0x07;

	// UAIER
	r = (volatile unsigned long*)(AT_UART1_BASE + 0x4);
	*r = 0x40;
}
void updater_at_uart1_write(UINT8 *data, UINT16 *dataLength)
{
	volatile unsigned long* ualsr;
	volatile unsigned long* uathr;
	int  counter=32;

	ualsr = (volatile unsigned long*)(AT_UART1_BASE + 0x14);
	uathr = (volatile unsigned long*)(AT_UART1_BASE);

	while (!(*ualsr & 0x20));

	if (counter > *dataLength)
		counter = *dataLength;

	do
	{
		*uathr = *data;

		data++;
		(*dataLength)--;
		counter--;
	} while(counter);

} 

int updater_at_send_data_2uart(UINT8 *bufPtr, UINT32 length)
{
	UINT16 send_len = 0;
	UINT16 unsend_len = (UINT16)length;

	/* We only support one RX interrupt UART port now.
	   So the other two port don't allow to send TX data except
	   CP UART log via STUART.
	*/
	if(bufPtr != NULL)
	{
		while(send_len < length)
		{
			updater_at_uart1_write((UINT8*)(bufPtr+send_len),&unsend_len);
			send_len = length - unsend_len;
		}

		return 0;
	}
	else
	{
		return -1;
    }
}

void updater_at_uart_demo(void)
{
	char ATUartTestMsg [1024];
	UINT16 datalen;

	//at uart1 test write string
	memset(ATUartTestMsg, 0, sizeof(ATUartTestMsg));
	sprintf (ATUartTestMsg, "updater---AT UART1 write -1234567890-abcdefghijklmnopqrstuvwxyz");
	datalen=strlen(ATUartTestMsg);
	updater_at_send_data_2uart(ATUartTestMsg, datalen);
}
#endif


