/* ==================================================================  */
// This is a Arduino library of our product - Azufier
//
// For more information please visit out HP : http://www.azure-lab.com
/* ==================================================================  */

#include "AzufierCtrl.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include <stdio.h>

#define COMMAND_DELAY 10
#define defaultBaudRate 2400
#define SendDataLength 20
#define iBeaconCommandLength 4

bool connected = false;
int radioState = 0;

AzufierCtrl::AzufierCtrl(bool flag)
{
  _serial = &Serial1;
  _serial->begin(defaultBaudRate);

  reconnectFlag = flag;
}

AzufierCtrl::AzufierCtrl()
{
  _serial = &Serial1;
  _serial->begin(defaultBaudRate);

  reconnectFlag = false;
}

AzufierCtrl::~AzufierCtrl()
{
  /* Nothing to destruct*/
}

void AzufierCtrl::begin(long baud)
{
  _serial = &Serial1;
  _serial->begin(baud);
}

bool AzufierCtrl::available()
{
  _serial = &Serial1;
  return _serial->available();
}

void AzufierCtrl::autoReconnect(bool flag)
{
  reconnectFlag = flag;
}

String AzufierCtrl::getRawReceivedData()
{
  _serial = &Serial1;
  String data = _serial->readStringUntil('\n');
  data = data.substring(0,data.length()-1);
  if(data.substring(0,2) == "RT")
  {
    if((data.substring(3) == "00")&&(reconnectFlag))
    {
      connected = false;
      manualDiscoverable();
    }else if((data.substring(3) == "02")&&(reconnectFlag)){
      _serial = &Serial1;
      _serial->println("bc:md=00");
      delay(COMMAND_DELAY);
    }

    if(data.substring(3,5) == "05")
    {
      connected = true;
    }
    data = "";
  }else if(data.substring(0,2) == "ER")
  {
     data = "";
  }
  return data;
}

bool AzufierCtrl::sendDataInString(String str)
{
  if(str.length() >= SendDataLength)
  {
    return false;
  }else
  {
    if(!connected)
      return false;

    _serial = &Serial1;
    _serial->print("bc:dt=");
    _serial->println(str);

    delay(COMMAND_DELAY);

    String result = getRawReceivedData();
    if(result=="OK")
    {
      return true;
    }else
    {
      return false;
    }
  }
}

void AzufierCtrl::manualDiscoverable()
{
  _serial = &Serial1;
  _serial->println("bc:md=01");
  delay(COMMAND_DELAY);
}

String AzufierCtrl::getMacAddress()
{
  _serial = &Serial1;
  _serial->println("bc:ad");
  delay(COMMAND_DELAY);
  return getRawReceivedData();
}

bool AzufierCtrl::isConnected(){
  return connected;
}

void AzufierCtrl::startModuleMode(int mode)
{
    _serial = &Serial1;

    //0: beaconMode 1:iBeaconMode
    if(mode == 1)
    {
      _serial->println("bc:ft=e001");
      connected = true;
    }else if(mode == 0)
    {
      _serial->println("bc:ft=e000");
    }
  delay(COMMAND_DELAY);
  restartBTModule();
}

void AzufierCtrl::startModuleMode( int mode, int major, int minor)
{
  _serial = &Serial1;

  //0: beaconMode 1:iBeaconMode
  if(mode == 1)
  {
    _serial->println("bc:ft=e001");
  }else if(mode == 0)
  {
    _serial->println("bc:ft=e000");
  }
  delay(COMMAND_DELAY);

  //setting iBeacon Major
  String majorStr = String(major, HEX);
  majorStr = AddZeroIntoString(majorStr,iBeaconCommandLength);
  _serial->print("bc:ba=");
  _serial->println(majorStr);

  delay(COMMAND_DELAY);
  String result = getRawReceivedData();
  
  //setting iBeacon Minor
  String minorStr = String(minor, HEX);
  minorStr = AddZeroIntoString(minorStr,iBeaconCommandLength);
  _serial->print("bc:bi=");
  _serial->println(minorStr);
  delay(COMMAND_DELAY);
  String result1 = getRawReceivedData();

  restartBTModule();
}

bool AzufierCtrl::setiBeaconMajor(int value)
{
  _serial = &Serial1;
  if((value <= 65535)&&(!connected))
  {
    String major = String(value, HEX);
    major = AddZeroIntoString(major,iBeaconCommandLength);
    _serial->print("bc:ba=");
    _serial->println(major);

    delay(COMMAND_DELAY);

    //get indicator
    String result = getRawReceivedData();
    if(result=="OK")
    {
      return true;
    }else
    {
      return false;
    }
  }else
  {
    return false;
  }
}

bool AzufierCtrl::setiBeaconMinor(int value)
{
  _serial = &Serial1;
  if(value <= 65535)
  {
    String minor = String(value, HEX);
    minor = AddZeroIntoString(minor,iBeaconCommandLength);
    _serial->print("bc:bi=");
    _serial->println(minor);
    delay(COMMAND_DELAY);

    //get indicator
    String result = getRawReceivedData();
    if(result=="OK")
    {
      return true;
    }else
    {
      return false;
    }
  }else
  {
    return true;
  }
}

void AzufierCtrl::restartBTModule()
{
  _serial = &Serial1;
  _serial->println("bc:pd=02");
  delay(COMMAND_DELAY);
}

void AzufierCtrl::clearPairedList()
{
  _serial = &Serial1;
  _serial->println("bc:cp");
  delay(COMMAND_DELAY);
}

void AzufierCtrl::setServiceUUID(String uuid)
{
  String tmp;
  String str;
  int startIndex = 7;
  if((uuid.length()==32)&&(!connected))
  {
    for(int index=0; index<32; index+=4)
    {
      tmp = uuid.substring(index,index+4);
      str = swap(tmp);
      _serial = &Serial1;
      _serial->print("bc:ud=000");
      _serial->print(startIndex);
      _serial->print(",");
      _serial->println(str);
      
      delay(COMMAND_DELAY);
      String result = getRawReceivedData();

      startIndex--;
    }
  }
}


String AzufierCtrl::sendRawCommandToModule(String command)
{
  _serial = &Serial1;
  _serial->println(command);

  delay(COMMAND_DELAY);
  String response = getRawReceivedData();

  return response;
}


String AzufierCtrl::AddZeroIntoString(String data, int leng)
{
  String zero;
  if(data.length() != leng)
  {
    int zeros = leng - data.length();
    for(int i=0;i<zeros;i++)
    {
      zero += "0";
    }
    zero.concat(data);
    data = zero;
  }
  return data;
}

String AzufierCtrl::swap(String data)
{
  char data_tmp[4];
  char data_array[4];
  String returnDt;
  if(data.length()==4)
  {
     for(int i=0;i<4;i++)
     {
        data_tmp[i] = data.charAt(i);
     }
     data_array[0] = data_tmp[2];
     data_array[1] = data_tmp[3];
     data_array[2] = data_tmp[0];
     data_array[3] = data_tmp[1];
     
     returnDt = String(data_array).substring(0,4);
     
   }
   return returnDt;
}

