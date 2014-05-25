/*
 * MSP430 USB Firmware Upgrade Example
 *
 * An example software to field firmware upgrade a MSP430 USB based device
 *
 * Copyright (C) {2010} Texas Instruments Incorporated - http://www.ti.com/ 
 * 
*/
/*==========================================================================*\
|                                                                            |
|                                                                            |
| PC-side Bootstrap Loader communication Application                         |
|                                                                            |
| See main.c for full version and legal information                          |
|                                                                            |
\*==========================================================================*/

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <conio.h>
#include "hiddevice.h"
#include "BSL_IO_USB.h"

int    USB_verbose = 0;			/* verbose mode flag, default off */
struct strHidDevice device;				/*HID device to use */
HDEVNOTIFY deviceNotifyHandle;

BYTE USB_initializeCommPort(unsigned short VID, unsigned short PID , unsigned long INDEX);








}