# Azufier-Library

This is an Arduino library for [Azufier](http://www.azure-lab.com).

Azufier is an BLE chip onboard with Atmega32u4 microcontroller. See [www.azure-lab.com](http://www.azure-lab.com) for more details

###Setup (Arduino IDE version 1.6.4 or higher for this guide)
1. Install [Arduino IDE](https://www.arduino.cc/en/Main/Software).
2. Azufier is compatible with SparkFun SF32u4 boards.Adding SparkFun Boards to library by following steps
  - Open Arduino IDE,Go to "Arduino" -> "Prefrences" @ Mac ("File" -> "Preferences" @ Windows)
  - Add following url(https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json)to "Additional Boards Manager URLs:", and press "OK".
  - Go to "Board" -> "Boards Manager".
  - Choose "Contributed" at "Type" option.
  - "SparkFun AVR Boards" option will be able to download now.Click once on the option and press "Install".
  - Boards install done :)
3. [Download](https://github.com/azurelab/Azufier-Library/archive/master.zip) this respo.
4. At Arduino IDE, go to "Sketch" -> "Include Library" -> "Add .ZIP Library...". Select the .zip you just downloaded.[Detail Guide here](https://www.arduino.cc/en/Guide/Libraries#toc4)
5. Go to "Tools" -> "Board:", select "SparkFun Pro Micro"
6. Go to "Tools" -> "Processor", select "ATMEGA32u4 3.3V/8MHZ"
7. Setup complete! Try upload others sketch at "File" -> "Examples" -> "Azufier"

###Documentation
See more library details at [here](http://www.azure-lab.com/documentation/index.html)

###Reference
1. [Azufier-Hardware](https://github.com/azurelab/Azufier-Hardware)
2. [Azufier-iOS-SDK](https://github.com/azurelab/Azufier_iOS)
3. [Azufier-Library](https://github.com/azurelab/Azufier-Library)
