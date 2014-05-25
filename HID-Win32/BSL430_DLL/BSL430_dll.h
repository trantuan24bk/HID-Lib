/*
 * MSP430 USB Firmware Upgrade Example
 *
 * An example software to field firmware upgrade a MSP430 USB based device
 *
 * Copyright (C) {2010} Texas Instruments Incorporated - http://www.ti.com/ 
 * 
*/
#ifdef __cplusplus
extern "C" {
#endif


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


#ifdef __cplusplus
}
#endif