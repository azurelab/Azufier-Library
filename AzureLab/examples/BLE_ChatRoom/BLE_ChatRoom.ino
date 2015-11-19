/*
  Bluetooth Mini Chat Room
  Chat with connected ios devices through Serial Monitor
  
  You can also use our sample app to test this feature.
  
  If you're unsure about these APIs,
  Check more info from our documenation at our website http://www.azure-lab.com/
  
  modified 23/10/2015
  by Azure Lab
*/

#include "AzufierCtrl.h"

#define reconFlag true

//define azufier class
AzufierCtrl azufier(reconFlag);

void setup() {
  
  //start serial port
  Serial.begin(9600);
  
  //start azufier under BLE mode
//  azufier.startModuleMode(0);

  Serial.println("Welcome to Azufier Mini Chat Room!!");
}

void loop() {
  if(Serial.available())
  {
    //read the word you want to say
    String command = Serial.readStringUntil('\n');
    
    String msg = "You:" + command;
    Serial.println(msg);
    
    //send your word to him
    azufier.sendDataInString(command);
  }
  
  if(azufier.available())
  {
    //read the words from him
    String data = azufier.getRawReceivedData();
    
    //print those received data
    //for more info check out documentation!
    if(data != "")  
    {
      String msg1 = "He:" + data.substring(3);
      Serial.println(msg1);
    }
  }
}
