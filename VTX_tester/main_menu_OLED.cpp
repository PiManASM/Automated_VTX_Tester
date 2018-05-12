/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x64 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>       /* pow() */

#include "TestPower.h"
#include "main_menu_OLED.h"

namespace UI {
  Adafruit_SSD1306 display(OLED_RESET);
  
  void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.clearDisplay();
  }
  
  void menu() {
    
    uint16_t MHz = Test::getMHz(); 
    float    dBm = Test::getdBm();
    display.clearDisplay();
  
    // text display tests
    display.setCursor(0,0);
    display.println("VTx Power:");
    display.print(dBm); display.println(" dBm");
    display.print(pow(10,(dBm/10.0))); display.println(" mW");
    display.print("Freq: "); display.println(MHz);
    display.display();
    //delay(2000);
  }
}
