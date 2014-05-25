/*
 * MSP430 USB Firmware Upgrade Example
 *
 * An example software to field firmware upgrade a MSP430 USB based device
 *
 * Copyright (C) {2010} Texas Instruments Incorporated - http://www.ti.com/ 
 * 
*/
// BSL_USB_GUI.cpp : main project file.

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

using namespace BSL_USB_GUI;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
  // Check if .Net Exist on system or else throw error.

  // Enabling Windows XP visual effects before any controls are created
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false); 

  // Create the main window and run it
  Application::Run(gcnew DownloadView());
  return 0;
}
