/* ==================================================================  */
// This is a Arduino library of our product - Azufier
//
// For more information please visit out HP : http://www.azure-lab.com
/* ==================================================================  */

#ifndef AzufierCtrl_h
#define AzufierCtrl_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <stdio.h>

class AzufierCtrl{
	public:
        AzufierCtrl(bool flag);
        AzufierCtrl();
        ~AzufierCtrl();

        bool available();

        String getRawReceivedData();
        bool sendDataInString(String str);
        void manualDiscoverable();
        String getMacAddress();
        bool isConnected();

        void startModuleMode(int mode);
        void startModuleMode(int mode, int major, int minor);
        bool setiBeaconMajor(int value);
        bool setiBeaconMinor(int value);

        void restartBTModule();
        void clearPairedList();
        void setServiceUUID(String uuid);
        String sendRawCommandToModule(String command);

  	private:
        bool reconnectFlag;
        void autoReconnect(bool flag);
        void begin(long baud);
        
        String AddZeroIntoString(String data, int leng);
        String swap(String data);
        HardwareSerial *_serial;

};
#endif