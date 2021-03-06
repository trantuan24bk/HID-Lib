/* ==============================================================================
 *  File name:
 *      		main.c
 *	Description:
 * 		
 *
 *  Created on: 
 * 				February 25, 2014
 *  Author: 
 * 				TRAN KHAC TUAN
 *	Address:
 * 		Vnelektronics Co.Ltd
 * 		776 Ton Duc Thang, Lien Chieu, Danang
 *		website: www.vnelek.vn
 *
 * 	Complier: 
 * 			IAR v5.3
 * ==============================================================================*/
#include <msp430f5510.h>
#include <intrinsics.h>
#include <string.h>

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/types.h"               //Basic Type declarations
#include "USB_API/USB_Common/usb.h"                 //USB-specific functions

#include "F5xx_F6xx_Core_Lib/HAL_UCS.h"
#include "F5xx_F6xx_Core_Lib/HAL_PMM.h"
#include "USB_API/USB_HID_API/UsbHid.h"
#include "usbConstructs.h"

#ifndef MCLK_24MHZ
	#define MCLK_24MHZ			1
#endif

#define BUFFER_SIZE 256

volatile BYTE bHIDDataReceived_event = FALSE;   		// Flag set by event handler to indicate data has been received into USB buffer

BYTE hexBuffer[BUFFER_SIZE];                   			// User buffer to hold the data
BYTE usbBuffer[BUFFER_SIZE];							// Contains TX buffer data

#include "main.h"										// Main header

/*===============================================================================================
  Name         :  main program
  Description  :  
  Argument(s)  :  
  Return value :  None.
================================================================================================*/
VOID main (VOID)
{
	WORD count;
	BYTE SendError = 0;
	BYTE ReceiveError = 0;
	
    WDTCTL = WDTPW + WDTHOLD;                                   //Stop watchdog timer
    Init_Ports();                                               // Do first ports because clocks do change ports
    SetVCore(3);
    Init_Clock();                                               //Init clocks
	
    P1DIR |= BIT0;
    
    USB_init();	
    USB_setEnabledEvents(kUSB_VbusOnEvent + kUSB_VbusOffEvent + kUSB_receiveCompletedEvent +
						 kUSB_dataReceivedEvent + kUSB_UsbSuspendEvent + kUSB_UsbResumeEvent +
						 kUSB_UsbResetEvent);

    //See if we're already attached physically to USB, and if so, connect to it
    //Normally applications don't invoke the event handlers, but this is an exception.
    if (USB_connectionInfo() & kUSB_vbusPresent)
	{
        if (USB_enable() == kUSB_succeed)
		{
            USB_reset();
            USB_connect();
        }
    }

    __enable_interrupt();                           //Enable interrupts globally
	
    while(TRUE)
    {        
        //Check the USB state and loop accordingly
        switch (USB_connectionState())
        {
            case ST_ENUM_ACTIVE:
                __bis_SR_register(LPM0_bits + GIE);                     //Enter LPM0 until awakened by an event handler
                __no_operation();                                       //For debugger

				//Exit LPM because of a data-receive event, and fetch the received data
                if (bHIDDataReceived_event)
				{
					//Clear flag early -- just in case execution breaks below because of an error
                    bHIDDataReceived_event = FALSE;
					
                    count = hidReceiveDataInBuffer(hexBuffer, BUFFER_SIZE, HID0_INTFNUM);

                    __delay_cycles(950000);
                    __delay_cycles(950000);
                    __delay_cycles(950000);                    
                    if(count == 63)
                      P1OUT |= BIT0;
                    else
                      P1OUT &= ~BIT0;
                    hidSendDataInBackground(hexBuffer, count, HID0_INTFNUM,1);
                }
                break;

			case ST_USB_DISCONNECTED:
                __bis_SR_register(LPM3_bits + GIE);                             //Enter LPM3 until USB is connected
                _NOP();
                break;
            case ST_USB_CONNECTED_NO_ENUM:
                break;
            case ST_ENUM_SUSPENDED:
                __bis_SR_register(LPM3_bits + GIE);                     		//Enter LPM3 w/interrupt
                break;
            case ST_ENUM_IN_PROGRESS:
                break;
            case ST_NOENUM_SUSPENDED:
                __bis_SR_register(LPM3_bits + GIE);
                break;
            case ST_ERROR:
                _NOP();
                break;
            default: break;
        }
		
        if (ReceiveError || SendError){
            //TO DO: User can place code here to handle error
        }
    }
}

/*===============================================================================================
  Name         :  UNMI_ISR
  Description  :  
  Argument(s)  :  
  Return value :  None.
================================================================================================*/
#pragma vector = UNMI_VECTOR
__interrupt VOID UNMI_ISR (VOID)
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG ))
    {
        case SYSUNIV_NONE:
            __no_operation();
            break;
        case SYSUNIV_NMIIFG:
            __no_operation();
            break;
        case SYSUNIV_OFIFG:
            UCSCTL7 &= ~(DCOFFG + XT1LFOFFG + XT2OFFG); //Clear OSC flaut Flags fault flags
            SFRIFG1 &= ~OFIFG;                          //Clear OFIFG fault flag
            break;
        case SYSUNIV_ACCVIFG:
            __no_operation();
            break;
        case SYSUNIV_BUSIFG:
                                                    //If bus error occured - the cleaning of flag and re-initializing of USB is
                                                    //required.
            SYSBERRIV = 0;                          //clear bus error flag
            USB_disable();                          //Disable
    }
}

