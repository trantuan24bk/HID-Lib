/*
 * MSP430 USB Firmware Upgrade Example
 *
 * An example software to field firmware upgrade a MSP430 USB based device
 *
 * Copyright (C) {2010} Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
*/

#include <windows.h>


BYTE USB_initialize_BSL(void);
BYTE USB_close_BSL(void);
BYTE USB_RegisterForDeviceNotification(HWND hWnd);
BYTE USB_UnRegisterDeviceNotification(void);
DWORD USB_numOfDevices(unsigned short VID, unsigned short PID);


void USB_sendData( unsigned char* buf, unsigned int num_bytes );
int USB_receiveData( unsigned char* buf );
BYTE USB_FlushBuffer(void);

void USB_delay(int time);
