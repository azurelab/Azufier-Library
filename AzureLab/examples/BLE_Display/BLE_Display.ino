/*
  Display Dot Maker
  Draw simple dot drawing from iOS device!
  
  You can also use our sample app to test this feature.
  
  If you're unsure about these APIs,
  Check more info from our documenation at http://www.azure-lab.com/

  modified 23/10/2015
  by Azure Lab

  Thank you adafruit provide such awsome library!!!
  More information about Adafruit_GFX please visit here
  https://github.com/adafruit/Adafruit-GFX-Library
*/

#include "AzufierCtrl.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>

// any pins can be used
#define SCK 10
#define MOSI 11
#define SS 13

#define BLACK 0
#define WHITE 1

#define reconFlag true

//azufier class
AzufierCtrl azufier(reconFlag);

Adafruit_SharpMem display(SCK, MOSI, SS);

String command;

void setup() {
  
  //start serial port
  Serial.begin(9600);

  //start azufier under BLE mode
  //azufier.startModuleMode(0);
  
  display.begin();
  display.clearDisplay();
  display.refresh();
  delay(100);
}

void loop() {
  int parameter[2];
  if(azufier.available())
  {
    String data = azufier.getRawReceivedData();
    data = data.substring(3);
    
    if(data != "")  
    {
      String protocol = getValue(data, ',', 0);

      if(protocol == "dis"){
        String data1 = getValue(data, ',', 1);
        String data2 = getValue(data, ',', 2);
      
        //turn parameter int integer value
        int x = data1.toInt();
        int y = data2.toInt();

        drawRect(x,y);
      }
      
      if(protocol == "clr"){
        clearDisplay();
      }
    }
  }
}

void drawRect(int indexX,int indexY)
{
  //draw a rect with 3pixel * 3 pixel
  int width = 96/12;
  int height = 96/12;
  display.fillRect(indexX*width, indexY*height,width,height,BLACK);
  display.refresh();
  delay(100);
}

void clearDisplay(){
  display.clearDisplay();
  display.refresh();
  delay(10);
}

//split the string and get the object at index
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
