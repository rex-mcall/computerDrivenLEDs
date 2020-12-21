#include <windows.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>

int main() {

    /*----------------------------------- Opening the Serial Port --------------------------------------------*/

    char commName[] = "COM3";
    HANDLE hComm; // global variable, serial handle
    hComm = CreateFile(commName,           // Name of the Port to be Opened
        GENERIC_READ | GENERIC_WRITE,      // Read/Write Access
        0,                                 // No Sharing, ports cant be shared
        NULL,                              // No Security
        OPEN_EXISTING,                     // Open existing port only
        0,                                 // Non Overlapped I/O
        NULL);                             // Null for Comm Devices

    if (hComm == INVALID_HANDLE_VALUE)
    {
        printf("Open COM failed!");
        exit(1);
    }
    else {
        printf("Successful opening of the COM port.");
    }

    /*------------------------------- Setting the Parameters for the SerialPort ------------------------------*/

    DCB dcbSerialParams = { 0 };                        // Initializing DCB structure
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    bool Status = GetCommState(hComm, &dcbSerialParams);     //retreives  the current settings

    if (Status == FALSE)
        printf("\n   Error! in GetCommState()");

    dcbSerialParams.BaudRate = CBR_9600;      // Setting BaudRate = 9600
    dcbSerialParams.ByteSize = 8;             // Setting ByteSize = 8
    dcbSerialParams.StopBits = ONESTOPBIT;    // Setting StopBits = 1
    dcbSerialParams.Parity = NOPARITY;      // Setting Parity = None 

    Status = SetCommState(hComm, &dcbSerialParams);  //Configuring the port according to settings in DCB 

    if (Status == FALSE)
    {
        printf("\n   Error! in Setting DCB Structure");
    }
    else
    {
        printf("\n       Setting DCB Structure Successfull\n");
        printf("\n       Baudrate = %d", dcbSerialParams.BaudRate);
        printf("\n       ByteSize = %d", dcbSerialParams.ByteSize);
        printf("\n       StopBits = %d", dcbSerialParams.StopBits);
        printf("\n       Parity   = %d", dcbSerialParams.Parity);
    }

    /*------------------------------------ Setting Timeouts --------------------------------------------------*/

    COMMTIMEOUTS timeouts = { 0 };

    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 50;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.WriteTotalTimeoutConstant   = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (SetCommTimeouts(hComm, &timeouts) == FALSE) {
        printf("\n   Error! in Setting Timeouts");
        exit(1);
    }

    /*----------------------------- Writing a Character to Serial Port----------------------------------------*/

    char   lpBuffer[] = "255,255,255";
    DWORD  dNoOFBytestoWrite;              //Number of bytes to write into the port
    DWORD  dNoOfBytesWritten = 0;          //Number of bytes written to the port

    dNoOFBytestoWrite = sizeof(lpBuffer); // Calculating the no of bytes to write into the port

    Status = WriteFile(hComm,               // Handle to the Serialport
        lpBuffer,            // Data to be written to the port, must be char array
        dNoOFBytestoWrite,   // Number of bytes to write into the port
        &dNoOfBytesWritten,  // Number of bytes written to the port
        NULL);

    if (Status == TRUE)
        printf("\n\n    %s - Written to %s", lpBuffer, commName);
    else
        printf("\n\n   Error %d in Writing to Serial Port", GetLastError());

    CloseHandle(hComm);  //Closing the Serial Port
}