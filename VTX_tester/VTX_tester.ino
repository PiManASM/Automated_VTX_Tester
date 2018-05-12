#include <SoftwareSerial.h>
#include <stdint.h>
#include "VTX_common.h"
#include "ArduinoTramp.h"
#include "TestPower.h"
#include "main_menu_OLED.h"
#include "Adafruit_SSD1306.h"

#define ADC_Pin 0
#define CmdDelay 3000 //mS between commands
#define OLED_RESET 4

//  setup serial & soft serial
SoftwareSerial mySerial(4, 3); //RX, TX
Adafruit_SSD1306 display(OLED_RESET);

void setup(){
  Serial.begin(9600);            
  mySerial.begin(9600);

  Serial.print(" MHz  ");
  Serial.println(" dBm  ");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();

//  menu(display);

}

void loop(){
  //TrampTest(Serial, mySerial);
  menu(7.0, display);
}
