/*
  Bluetooth Simple IO Control
  Chat with to connected devices through Arduino Serial Monitor

  You can also use our sample app to test this feature.

  If you're unsure about these APIs,
  Check more info from our documenation at  http://www.azure-lab.com

  modified 23/10/2015
  by Azure Lab
*/

#include "AzufierCtrl.h"

#define reconFlag true

//calling azufier class
AzufierCtrl azufier(reconFlag);

void setup() {

  //start serial port
  Serial.begin(9600);

  //start azufier under BLE mode
  azufier.startModuleMode(0);

  Serial.println("Welcome to Azufier Simple IO");
}

void loop() {
  if (azufier.available())
  {
    //read data from azufier
    String data = azufier.getRawReceivedData();
    data = data.substring(3);

    if (data != "")
    {
      String protocol = getValue(data, ',', 0);
      String portNum = getValue(data, ',', 1);
      String modeValue = getValue(data, ',', 2);
      
      //turn parameter int integer value
      int port = portNum.toInt();
      int mode = modeValue.toInt();
      
      if (protocol == "setport")
      {
        SetPortMode(port, mode);
      }
      if (protocol == "dout")
      {
         SetDigitalOutpu(port,mode);
      }
      if(protocol == "aout")
      {
        SetAnalogOutpu(port,mode);
      }
    }
  }
}

void SetPortMode(int portNum, int mode)
{
  if (mode)
  {
    pinMode(portNum, OUTPUT);
    digitalWrite(portNum,LOW); 
  }
  else
  {
    pinMode(portNum, INPUT_PULLUP);
  }
}

void SetDigitalOutpu(int portNum, int outvalue)
{
  if (outvalue)
    digitalWrite(portNum, HIGH);
  else
    digitalWrite(portNum, LOW);
}

void SetAnalogOutpu(int portNum, int outvalue)
{
  analogWrite(portNum,outvalue);
}


String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {
    0, -1
  };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
