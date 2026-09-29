#ifndef _SIMCOM_USB_H_
#define _SIMCOM_USB_H_

typedef void (*SC_Usb_Callback_EX)(int len, void *para);

void sAPI_UsbVcomWrite(unsigned char* data, unsigned long length);
int sAPI_UsbVcomRead(unsigned char *Data, int len);
int sAPI_UsbVcomRegisterCallbackEX(SC_Usb_Callback_EX cb, void *reserve);


#endif
