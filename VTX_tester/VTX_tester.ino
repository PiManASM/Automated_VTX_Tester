#include <SoftwareSerial.h>
#include <stdint.h>
#include "VTX_common.h"
#include "ArduinoTramp.h"
#include "TestPower.h"

#define ADC_Pin 0
#define CmdDelay 3000 //mS between commands

//  setup serial & soft serial
SoftwareSerial mySerial(4, 3); //RX, TX

void setup(){
  Serial.begin(9600);            
  mySerial.begin(9600);

  Serial.print(" MHz  ");
  Serial.println(" dBm  ");
}

void loop(){
  TrampTest(Serial, mySerial);
}
