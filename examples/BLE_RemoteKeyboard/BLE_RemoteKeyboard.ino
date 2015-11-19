/*
  Remote Keyboard
  Turn your ios Device into wireless keyboard!
  
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

  //init keyboard
  Keyboard.begin();
}

void loop() {
  
  if(Serial.available())
  {
    //read the word you want to say
    String command = Serial.readStringUntil('\n');
    
    Serial.println("You say:" + command);
    
    //send your word to him
    azufier.sendDataInString(command);
  }
  
  if(azufier.available())
  {
    //get received command
    String data = azufier.getRawReceivedData();
    
    if(data != "")  
    {
      if(data.substring(3) == "BACK")
      {
        Keyboard.write(KEY_BACKSPACE); 
      }else
      {
        Keyboard.print(data.substring(3));
      }
    }
  }
}
