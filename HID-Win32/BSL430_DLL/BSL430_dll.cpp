/*
 * MSP430 USB Firmware Upgrade Example
 *
 * An example software to field firmware upgrade a MSP430 USB based device
 *
 * Copyright (C) {2010} Texas Instruments Incorporated - http://www.ti.com/ 
 * 
*/



#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <conio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "BSL430_dll.h"
#include "HidDevice.h"

struct strHidDevice device;				/*HID device to use */
HDEVNOTIFY deviceNotifyHandle;


/* =========================================================================
*Function:    USB_Initialize
*Description: initializes USB port for communication
*Parameters: 
*             WORD VID          USB VID
*             WORD PID          USB PID
*Returns:
*             BYTE              0x00 - Success
*                               0x01 - HID device not found
*
 * ========================================================================= */
__declspec(dllexport) BYTE USB_Initialize(unsigned short VID = 0x04d8, unsigned short PID = 0x000F, 
											  unsigned long deviceIndex = 0x00)
{
	HID_Init( &device );
	return HID_Open( &device, VID, PID, deviceIndex );
}

/* =========================================================================
*Function:    USB_Close
*Description: Closes USB port for communication
*Parameters: 
*             none
*Returns:
*             BYTE              0x00 - Success
*                               0x01 - HID device not found
*
 * ========================================================================= */
__declspec(dllexport) BYTE USB_Close(void)
{
  return HID_Close( &device );
}


/* =========================================================================
*Function:    USB_RegisterDeviceNotification
*Description: Registers USB device for Windows notification
*Parameters: 
*             HWND hWnd         Current GUI Windows handle
*Returns:
*             BYTE              0x00 - Success
*                               0x06 - HID device handle error
*
 * ========================================================================= */
__declspec(dllexport) BYTE USB_RegisterDeviceNotification(HWND hWnd)
{
  return HID_RegisterForDeviceNotification(hWnd, &deviceNotifyHandle);
}

/* =========================================================================
*Function:    USB_RegisterDeviceNotification
*Description: Registers USB device for Windows notification
*Parameters: 
*             HWND hWnd         Current GUI Windows handle
*Returns:
*             BYTE              0x00 - Success
*                               0x06 - HID device handle error
*
 * ========================================================================= */
__declspec(dllexport) BYTE USB_UnRegisterDeviceNotification(void)
{
  return HID_UnRegisterForDeviceNotification(&deviceNotifyHandle);
}

/* =========================================================================
*Function:    USB_numOfDevices
*Description: Returns the number of USB device based on a vid or pid
*Parameters: 
*             void
*Returns:
*             DWORD             # of USB device based on VID or PID
*
 * ========================================================================= */
__declspec(dllexport) DWORD USB_NumOfDevices(unsigned short VID , unsigned short PID)
{
  return HID_GetNumOfDevices(VID , PID);
}


/* =========================================================================
 * Function		: USB_SendToDevice
 * Description	:
 *				  Send data in buffer to connected HID device.
 * Parameters	: 
 *
 * Returns		:
 * 
 * ========================================================================= */
__declspec(dllexport) void USB_SendToDevice( BYTE* buf, unsigned int num_bytes )
{
	unsigned int i;
	BYTE USB_buf[MAX_USB_FRAME_SIZE];

	memset( USB_buf, 0xAC, MAX_USB_FRAME_SIZE );

	USB_buf[0]= (char)num_bytes;
	num_bytes++;

	for( i = 1; i < num_bytes; i++)
	{
		USB_buf[i] = buf[i-1];
	}

	HID_WriteFile( &device, USB_buf, num_bytes+1);
	return;
}


/* =========================================================================
 * Function		: USB_ReceiveFromDevice
 * Description	:
 *				  Receive data from connected HID device and store in buffer.
 *				  Return status if error.
 * Parameters	: 
 *
 * Returns		:
 * 
 * ========================================================================= */
__declspec(dllexport) int USB_ReceiveFromDevice( BYTE* buf )
{
	int retVal = 0;
	BYTE status;
	BYTE buf2[MAX_USB_FRAME_SIZE+1];
	
	status = HID_ReadFile( &device, buf2);

	if ( status == HID_DEVICE_SUCCESS)
	{
		int i;
		retVal = buf2[1];

		for( i = 0; i<= retVal; i++ )
		{
			buf[i] = buf2[i+2];
		}
	}
	else
	{
		// Return error status from HID
		retVal = status;
	}

	return retVal;
}

/* =========================================================================
 * Function		: USB_FlushBuffer
 * Description	:
 *				  Flush all data store in TX/RX buffer.
 * Parameters	: 
 *
 * Returns		:
 * 
 * ========================================================================= */
__declspec(dllexport) BYTE USB_FlushBuffer(void)
{
	return HID_FlushBuffer(&device);
}

/* =========================================================================
 * Function		: USB_DelayTime
 * Description	:
 *				  Delay with a specific time.
 * Parameters	: 
 *
 * Returns		:
 * 
 * ========================================================================= */
__declspec(dllexport) void USB_DelayTime(int time)		
{ 
	#ifndef WIN32
		DWORD startTime= GetTickCount();
		while (UART_calcTimeout(startTime) < time);
	#else
		Sleep(time);
	#endif
}


#ifdef __cplusplus
}
#endif