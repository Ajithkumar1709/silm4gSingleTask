#ifndef __MBTK_KEYPAD_H
#define __MBTK_KEYPAD_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mbtk_keypad_handler)(uint32_t key_event, uint32_t key_value);

extern void ol_set_keypad_handler(mbtk_keypad_handler handler);
extern void ol_set_keymatrix(uint8_t (*keymatrix)[5]);

#ifdef __cplusplus
}
#endif

#endif // #ifdef MBTK_LCD_SUPPORT


