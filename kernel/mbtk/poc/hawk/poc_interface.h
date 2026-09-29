#ifndef _POC_INTERFACE_
#define _POC_INTERFACE_

/*
 * Function:   virtual_uart_read
 * Description:
 *       Poc task call function notify UI task cmd response
 * 
 * Parameters:
 *       data: cmd response
 *       len: response len
 *
 * Explain:
 *       module should define this function,this is just declare
 *
 * Example:
 *       data = "+POC:8202000000014b6dd58b31000000\r\n"
 * 
 * Return:
 *       none
 *
 */
extern void virtual_uart_read(char *data, int len);

/*
 * Function:   virtual_uart_write
 * Description:
 *       Other task send at cmd to poc task
 * 
 * Parameters:
 *       cmd: cmd body
 *       len: cmd body len
 *
 * Explain:
 *       module can call this function poc task have defined 
 *
 * Example:
 *       virtual_uart_write("AT+POC=0000000101\r\n", strlen("AT+POC=0000000101\r\n"));
 * 
 * Return:
 *       none
 *
 */
void virtual_uart_write(char *cmd, int len);

/*
 * Function:   OEM_PocInit
 * Description:
 *       Poc Lib Init
 * 
 * Parameters:
 *       none
 *
 * Explain:
 *       module can call this function init poc lib 
 *
 * Example:
 *       OEM_PocInit();
 * 
 * Return:
 *       none
 *
 */
void OEM_PocInit(void);


#endif