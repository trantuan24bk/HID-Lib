/*
 * MSP430 USB Firmware Upgrade Example
 *
 * An example software to field firmware upgrade a MSP430 USB based device
 *
 * Copyright (C) {2010} Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *
*/
#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>

#define MAX_BUFFER_SIZE			63
#define MAX_USB_FRAME_SIZE		255

typedef struct {
  unsigned long int size;
  unsigned char data [MAX_BUFFER_SIZE];
} dataBuffer;

typedef struct DataBlock_ {
  unsigned char data[10240];
  unsigned int numberOfBytes;
  unsigned long int startAddr;

} DataBlock;


// BSL could not find any devices
#define BSL_DEVICE_NOT_FOUND  0x01

// BSL failed to register USB HID with Windows Handle
#define BSL_USB_HANDLE_ERROR  0x06



/* =========================================================================
*Function:    USB_Close
*Valid Mode:  USB
*Description: This command closes the USB BSL port.
*Parameters: 
*             none
*Returns:
*             unsigned int      BSL_SUCCESS          - Success
*                               BSL_DEVICE_NOT_FOUND - Device not found
 * ========================================================================= */
extern unsigned char USB_Close( void );

/* =========================================================================
* Function		: USB_Initialize
*
* Description	: This command invokes the BSL. For UART, it initializes based on
*				COM port and the device into BSL mode. For USB, it
*				initializes the HID based on a VID or PID. If no VID and PID
*				supplied, a default TI VID and PID is used
* Parameters	: 
*
* Returns		:
*             unsigned int      BSL_SUCCESS          - Success
*                               BSL_DEVICE_NOT_FOUND - Device not found
 * ========================================================================= */
extern BYTE USB_Initialize(unsigned short VID = 0x04d8, unsigned short PID = 0x000F, unsigned long deviceIndex = 0x00);

/* =========================================================================
*Function:    USB_RegisterDeviceNotification
*Valid Mode:  USB
*Description: Registers USB BSL devices for automatic event notification when a
*             device is removed or inserted.
*Parameters: 
*             HWND hWnd         Current GUI Windows handle
*Returns:
*             unsigned char     BSL_SUCCESS           - Success
*                               BSL_USB_HANDLE_ERROR  - HID device handle error
 * ========================================================================= */
extern unsigned char USB_RegisterDeviceNotification(HWND hWnd);

/* =========================================================================
*Function:    USB_UnRegisterDeviceNotification
*Valid Mode:  USB
*Description: Unregisters USB device for Windows notification
*Parameters: 
*             none
*Returns:
*             unsigned char     BSL_SUCCESS           - Success
*                               BSL_USB_HANDLE_ERROR  - HID device handle error
 * ========================================================================= */
extern unsigned char USB_UnRegisterDeviceNotification(void);

/* =========================================================================
*Function:    USB_NumOfDevices
*Valid Mode:  USB
*Description: Search for number of USB devices based on a VID and PID
*Parameters: 
*             VID               USB Vendor ID 
*             PID               USB Product ID
*Returns:
*             unsigned long     Number of USB devices
 * ========================================================================= */
extern unsigned long USB_NumOfDevices(unsigned short VID, unsigned short PID);


/* =========================================================================
*Function:    USB_SendToDevice
*Description: 
*             
*Parameters: 
*             
*Returns:
*             
* ========================================================================= */
extern void USB_SendToDevice(BYTE* buff, unsigned int num_bytes );


/* =========================================================================
*Function:    USB_ReceiveFromDevice
*Description: 
*             
*Parameters: 
*             
*Returns:
*             
* ========================================================================= */
extern int USB_ReceiveFromDevice(BYTE* buf);

/* =========================================================================
*Function:    USB_FlushBuffer
*Description: 
*             
*Parameters: 
*             
*Returns:
*             
* ========================================================================= */
extern BYTE USB_FlushBuffer(void);


#ifdef __cplusplus
}
#endif