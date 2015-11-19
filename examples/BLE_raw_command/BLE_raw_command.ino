/*
  Bluetooth Raw Command
  Send AT Command toward the onboard BLE Module
  
  If you're unsure what setting of the moduel is, this sample code
  will be helpful for you.
  
  Check those commands from our documenation at  http://www.azure-lab.com

  modified 23/10/2015
  by Azure Lab
*/

#include "AzufierCtrl.h"

//calling azufier class
AzufierCtrl azufier;

void setup() {
  
  //start serial port
  Serial.begin(9600);
  
  //there is no need to start azufier
  //azufier.startModuleMode(0);
}

void loop() {
  
  if(Serial.available())
  {
    //read string from Serial port
    String command = Serial.readStringUntil('\n');
    
    //get result from module
    String response = azufier.sendRawCommandToModule(command);
    Serial.println(response);
  }
}
