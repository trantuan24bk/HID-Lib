/*
 * MSP430 USB Firmware Upgrade Example
 *
 * An example software to field firmware upgrade a MSP430 USB based device
 *
 * Copyright (C) {2010} Texas Instruments Incorporated - http://www.ti.com/ 
 * 
*/
#pragma once

#include "BSL430_dll.h"
#include <windows.h>
#include <Winuser.h>
#include <Dbt.h>
#include <string.h>

#using <mscorlib.dll>				// Invoke external process
#using <System.dll>

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Threading;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Data::SqlTypes;
using namespace System::Reflection;
using namespace System::Resources;
using namespace System::Diagnostics;
using namespace Microsoft::Win32;


namespace BSL_USB_GUI {

  /// <summary>
  /// Summary for DownloadView
  ///
  /// WARNING: If you change the name of this class, you will need to change the
  ///          'Resource File Name' property for the managed resource compiler tool
  ///          associated with all .resx files this class depends on.  Otherwise,
  ///          the designers will not be able to interact properly with localized
  ///          resources associated with this form.
  /// </summary>
  public ref class DownloadView : public System::Windows::Forms::Form
  {
  public:
    DownloadView(void)
    {
		InitializeComponent();
		InitializeVidPidFirmware();

		// Construct Software version for title
		Assembly^ myAsm = Assembly::GetExecutingAssembly();
		AssemblyName^ assemName = myAsm->GetName();
		int majorRevision = assemName->Version->Major;
		int minorRevision = assemName->Version->Minor;
		int buildNumber = assemName->Version->Build;
		this->Text = this->Text + " " + majorRevision + "." + minorRevision + "." + buildNumber;

		InitializeBackgroundWorker();
    }
  
  protected: static String^ myVID;
  protected: static String^ myPID;
  protected: static String^ myDeviceIndex = "0";
  protected: static DWORD numberOfUSBDevicesConnected = 0;
  protected: static bool scanDeviceAgain = false;			 

#pragma region Windows Forms Tools


  private: System::Windows::Forms::StatusStrip^  statusBar;
  private: System::Windows::Forms::ToolStripProgressBar^  progresBar;






private: System::Windows::Forms::SaveFileDialog^  saveLogFileDialog;
  private: System::Windows::Forms::Button^  btnSend;

  private: System::Windows::Forms::Label^  label1;
  private: System::Windows::Forms::TextBox^  txtBoxSend;

  private: System::Windows::Forms::Button^  btnConnect;
  private: System::Windows::Forms::TextBox^  txtBoxReceived;





  private: System::Windows::Forms::TextBox^  txtBoxVID;

  private: System::Windows::Forms::Label^  label3;
  private: System::Windows::Forms::Label^  label4;
  private: System::Windows::Forms::TextBox^  txtBoxPID;





  private: System::Windows::Forms::ToolStripStatusLabel^  statusLabel;
  
#pragma endregion

  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~DownloadView()
    {
      // Unregister USB devices before quiting program.
      UnRegisterUSBDevice();
      if (components)
      {
        delete components;
      }
    }

  private: BYTE RegisterUSBDevice(HWND hWnd);
  private: BYTE UnRegisterUSBDevice();
  private: void StringToChar(String^ str , BYTE * character);
    
  private: System::ComponentModel::BackgroundWorker^  backgroundWorkerCheckDevice;
  private: System::ComponentModel::IContainer^  components;

  private:
    /// <summary>
    /// Required designer variable.
    /// </summary>


#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
		System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(DownloadView::typeid));
		this->backgroundWorkerCheckDevice = (gcnew System::ComponentModel::BackgroundWorker());
		this->statusBar = (gcnew System::Windows::Forms::StatusStrip());
		this->progresBar = (gcnew System::Windows::Forms::ToolStripProgressBar());
		this->statusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
		this->saveLogFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
		this->btnSend = (gcnew System::Windows::Forms::Button());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->txtBoxSend = (gcnew System::Windows::Forms::TextBox());
		this->btnConnect = (gcnew System::Windows::Forms::Button());
		this->txtBoxReceived = (gcnew System::Windows::Forms::TextBox());
		this->txtBoxVID = (gcnew System::Windows::Forms::TextBox());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->txtBoxPID = (gcnew System::Windows::Forms::TextBox());
		this->statusBar->SuspendLayout();
		this->SuspendLayout();
		// 
		// statusBar
		// 
		this->statusBar->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->progresBar, this->statusLabel});
		this->statusBar->Location = System::Drawing::Point(0, 358);
		this->statusBar->Name = L"statusBar";
		this->statusBar->Size = System::Drawing::Size(534, 22);
		this->statusBar->TabIndex = 14;
		this->statusBar->Text = L"statusStrip1";
		// 
		// progresBar
		// 
		this->progresBar->Alignment = System::Windows::Forms::ToolStripItemAlignment::Right;
		this->progresBar->Name = L"progresBar";
		this->progresBar->RightToLeft = System::Windows::Forms::RightToLeft::No;
		this->progresBar->Size = System::Drawing::Size(150, 16);
		this->progresBar->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
		// 
		// statusLabel
		// 
		this->statusLabel->Name = L"statusLabel";
		this->statusLabel->Size = System::Drawing::Size(123, 17);
		this->statusLabel->Text = L"Searching for device...";
		// 
		// btnSend
		// 
		this->btnSend->Location = System::Drawing::Point(346, 34);
		this->btnSend->Name = L"btnSend";
		this->btnSend->Size = System::Drawing::Size(85, 35);
		this->btnSend->TabIndex = 15;
		this->btnSend->Text = L"Send";
		this->btnSend->UseVisualStyleBackColor = true;
		this->btnSend->Click += gcnew System::EventHandler(this, &DownloadView::btnSend_Click);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(12, 86);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(71, 13);
		this->label1->TabIndex = 16;
		this->label1->Text = L"Data to send:";
		// 
		// txtBoxSend
		// 
		this->txtBoxSend->Location = System::Drawing::Point(15, 102);
		this->txtBoxSend->Name = L"txtBoxSend";
		this->txtBoxSend->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->txtBoxSend->Size = System::Drawing::Size(507, 20);
		this->txtBoxSend->TabIndex = 17;
		// 
		// btnConnect
		// 
		this->btnConnect->Location = System::Drawing::Point(437, 34);
		this->btnConnect->Name = L"btnConnect";
		this->btnConnect->Size = System::Drawing::Size(85, 35);
		this->btnConnect->TabIndex = 18;
		this->btnConnect->Text = L"Connect";
		this->btnConnect->UseVisualStyleBackColor = true;
		// 
		// txtBoxReceived
		// 
		this->txtBoxReceived->Location = System::Drawing::Point(15, 142);
		this->txtBoxReceived->Multiline = true;
		this->txtBoxReceived->Name = L"txtBoxReceived";
		this->txtBoxReceived->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->txtBoxReceived->Size = System::Drawing::Size(507, 193);
		this->txtBoxReceived->TabIndex = 21;
		// 
		// txtBoxVID
		// 
		this->txtBoxVID->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtBoxVID->Location = System::Drawing::Point(46, 42);
		this->txtBoxVID->Name = L"txtBoxVID";
		this->txtBoxVID->Size = System::Drawing::Size(69, 20);
		this->txtBoxVID->TabIndex = 22;
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(12, 45);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(28, 13);
		this->label3->TabIndex = 23;
		this->label3->Text = L"VID:";
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Location = System::Drawing::Point(143, 45);
		this->label4->Name = L"label4";
		this->label4->Size = System::Drawing::Size(28, 13);
		this->label4->TabIndex = 25;
		this->label4->Text = L"PID:";
		// 
		// txtBoxPID
		// 
		this->txtBoxPID->CharacterCasing = System::Windows::Forms::CharacterCasing::Upper;
		this->txtBoxPID->Location = System::Drawing::Point(177, 42);
		this->txtBoxPID->Name = L"txtBoxPID";
		this->txtBoxPID->Size = System::Drawing::Size(64, 20);
		this->txtBoxPID->TabIndex = 24;
		// 
		// DownloadView
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->BackColor = System::Drawing::SystemColors::Control;
		this->ClientSize = System::Drawing::Size(534, 380);
		this->Controls->Add(this->label4);
		this->Controls->Add(this->txtBoxPID);
		this->Controls->Add(this->label3);
		this->Controls->Add(this->txtBoxVID);
		this->Controls->Add(this->txtBoxReceived);
		this->Controls->Add(this->btnConnect);
		this->Controls->Add(this->txtBoxSend);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->btnSend);
		this->Controls->Add(this->statusBar);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
		this->MaximizeBox = false;
		this->Name = L"DownloadView";
		this->Text = L"HID Interface [Vnelektronics Co.,Ltd]";
		this->statusBar->ResumeLayout(false);
		this->statusBar->PerformLayout();
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion

/* =========================================================================
 * Function     : InitializeVidPidFirmware
 * Description  : 
 * Agruments    :
 *				  
 * Return       : 
 *				  None.
 * ========================================================================= */
void InitializeVidPidFirmware(void)
{
	this->myVID = "04D8";
	this->myPID = "000F";
}

/* =========================================================================
 * Function     : InitializeBackgroundWorker
 * Description  : 
 * Agruments    :
 *				  
 * Return       : 
 *				  None.
 * ========================================================================= */
void InitializeBackgroundWorker(void)
{
	backgroundWorkerCheckDevice->DoWork += gcnew DoWorkEventHandler( this, &DownloadView::backgroundWorkerCheckDevice_DoWork);
	backgroundWorkerCheckDevice->RunWorkerCompleted += gcnew RunWorkerCompletedEventHandler( this, &DownloadView::backgroundWorkerCheckDevice_RunWorkerCompleted );
}

/* =========================================================================
 * Function     : backgroundWorkerCheckDevice_DoWork
 * Description  : Event handler thread for Checking # of devices
 * Agruments    :
 *					sender		Not in used.
 *					e			Contains number of devices connected to computer.
 * Return       : None.
 * ========================================================================= */
void backgroundWorkerCheckDevice_DoWork( Object^ sender, DoWorkEventArgs^ e )
{
	// Scan # of USB HID devices based on VID and PID
	DWORD numOfDevices = USB_NumOfDevices(System::Convert::ToUInt16(myVID->Replace("0x",""),16),
									      System::Convert::ToUInt16(myPID->Replace("0x",""),16));

	// Set # of USB devices into results inside this thread (safely)
	e->Result = numOfDevices; 
}

/* =========================================================================
 * Function     : backgroundWorkerCheckDevice_RunWorkerCompleted
 * Description  : This event handler deals with the results of the
 *				  background operation for checking the number of USB devices.
 *				  Before exit this function, run background check device again.
 * Agruments    :
 *					sender		Not in used.
 *					e			Contains number of devices connected to computer,
 *								cancelled message or error message.
 * Return       : None.
 * ========================================================================= */
void backgroundWorkerCheckDevice_RunWorkerCompleted( Object^ /*sender*/, RunWorkerCompletedEventArgs^ e )
{
	if ( e->Error != nullptr )
	{

	}
	else if ( e->Cancelled )
	{

	}
	else
	{
		// Read passed value from backgroundWorkerCheckDevice thread
		numberOfUSBDevicesConnected = System::Convert::ToUInt32(e->Result->ToString());

		String^ structText;

		if(numberOfUSBDevicesConnected > 0)
		{
			structText = "Connected!";
			// Update label
			statusLabel->Text = structText;
		}
		else if(numberOfUSBDevicesConnected == 0)
		{
			structText = "Disconnected!";	  
			// Update label
			statusLabel->Text = structText;
		}
	}

	if(scanDeviceAgain)
	{
		scanDeviceAgain = false;
		backgroundWorkerCheckDevice->RunWorkerAsync();
	}
}


/* =========================================================================
*Function:    OnHandleCreated
*Description: Function that overrides OnHandleCreated for the purpose of 
*             registering USB notification to windows
*Parameters: 
*             EventArgs^ e          Events arguments
*Returns:
*             void
* ========================================================================= */
protected: virtual void OnHandleCreated(System::EventArgs^ e) override
{
	// Runs the original constructor of OnHandleCreated
	Form::OnHandleCreated(e);

	// Register USB devices
	BYTE status = RegisterUSBDevice((HWND) Handle.ToPointer());

	if(status == 0x00)
	{
		// If registration is good, scan for # of USB devices
		backgroundWorkerCheckDevice->RunWorkerAsync();
	}
	else
	{
		statusLabel->Text = "Unable to register device!";
	}
}

/* =========================================================================
*Function:    WndProc
*Description: Overrides windows form processor function
*Parameters: 
*             Message% m            Takes windows message
*Returns:
*             void
 * ========================================================================= */
protected: virtual void WndProc(Message% m) override
{
  ParseMessages(m);
  Form::WndProc(m);	                        // pass message on to base form
}

/* =========================================================================
*Function:    ParseMessages
*Description: Parses message from Windows to identify if device was removed or
*             inserted
*Parameters: 
*             Message% m            Takes windows message
*Returns:
*             void
 * ========================================================================= */
private: void ParseMessages(Message% m)
{
	if (m.Msg == WM_DEVICECHANGE)	          // Received a device change message.
	{                                       // A USB device was either inserted or removed.
		switch (m.WParam.ToInt32())	          // Check the W parameter to see if a device was inserted or removed
		{
			case DBT_DEVICEARRIVAL:	            // Device was inserted
				if(!(backgroundWorkerCheckDevice->IsBusy))
				{
					// Run check number of devices thread
					backgroundWorkerCheckDevice->RunWorkerAsync(); 
				}
				else
				{
					scanDeviceAgain = true;
				}
				break;
			case DBT_DEVICEREMOVECOMPLETE:	    // Device was removed
				if(!(backgroundWorkerCheckDevice->IsBusy))
				{
					// Run check number of devices thread
					backgroundWorkerCheckDevice->RunWorkerAsync();
				}
				else
				{
					scanDeviceAgain = true;
				}
				break;
		}
	}
}

private: System::Void btnSend_Click(System::Object^  sender, System::EventArgs^  e) 
{
	int i;
	int numOfBytes;
	dataBuffer* buff = new dataBuffer;

	for( i = 0; i < MAX_BUFFER_SIZE; i++)
	{
		buff->data[i] = i;
	}

	if(USB_Initialize() == BSL_DEVICE_NOT_FOUND)
	{
		// Update to message log
		statusLabel->Text = "Initialize to device failed!";
		return;
	}

	// Send data to device
	USB_SendToDevice(buff->data, MAX_BUFFER_SIZE-1);

	numOfBytes = USB_ReceiveFromDevice(buff->data);

	//for(i = 0; i < 20; i++)
	//{
	//	// Sleep & wait for data in 10ms...
	//	Thread::Sleep(200);

	//	// Read data from USB buffer
	//	numOfBytes = USB_ReceiveFromDevice(buff->data);

	//	if(numOfBytes >= 4)
	//	{			
	//		break;	// Exit for loop
	//	}
	//}

	// Display data
	txtBoxReceived->Text = "";
	for(i = 0; i < numOfBytes; i++)
	{
		txtBoxReceived->Text += buff->data[i].ToString() + Environment::NewLine;
	}

	USB_Close();

}

}; // End of class DownloadView

}  // End of namespace