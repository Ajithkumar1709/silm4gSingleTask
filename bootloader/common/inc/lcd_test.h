#ifndef _LCD_TEST_H_
#define _LCD_TEST_H_

/**
 * Note: If battery value is not more than "BATTERY_LOW_THRESHOLD", not display logo.
 * Note: When battery value is less than 2900 mv, software can not run.
 */
#define BATTERY_LOW_THRESHOLD (3000)
#define BATTERY_HIGH_VALUE	  (3400)

/**
 * BackLight Brightness Level
 * Range [ 0 - 5]: 	0  --- off
 */
#define Normal_BackLight_Brightness_Level		(3)
#define LowerBattery_BackLight_Brightness_Level	(1)

//int test_LcdSetBrightness(unsigned char level);
int test_LcdShowBGColor(void);
int test_LcdComposeFunc(void);


#endif	// _LCD_TEST_H_
