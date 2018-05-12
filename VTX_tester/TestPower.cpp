/*Test VTx power with external RF Log power detector*/

#include <Arduino.h>
#include <stdint.h>

#include "main_menu_OLED.h"
#include "VTX_common.h"
#include "ArduinoTramp.h"
#include "TestPower.h"

#define ADC_Pin 0
#define CmdDelay 3000 //minimum mS to wait between commands 

//get average ADC reading over 10 iterations

namespace Test {

  void setup () {
    Serial.begin(9600);    
    Serial.print(" MHz  ");
    Serial.println(" dBm  ");
  }

  uint16_t getMHz(){
    uint16_t temp = rand() % 25;
    return temp;
  }
  
  float ReadAvgRF_1024() {

   delay(1000); //wait for power to settle
   float RF_1024 = analogRead(ADC_Pin);     // read the input pin
  
   for(int i=0; i<10; i++) {
      float RF_1024 = (RF_1024 + analogRead(ADC_Pin))/2;     // TODO: better averaging/filtering 
    }
    return RF_1024;
  }

//convert ADC reading to dBm
float V2dBm(float RF_1024) {
   float RF_V= RF_1024 * (5.0 / 1023.0); // 0-1024 analogRead output to Voltage
   float dBm = -34.924 * RF_V +26.159;
   return dBm;
}

//print to serial monitor
void dataWrite(uint32_t MHz, float dBm) {
  Serial.print(MHz);
  Serial.print(',');
  Serial.println(dBm);             // debug value
}

//get ADC reading and output dBm
void MeasureTx(uint32_t MHz){
  float RF_1024 = ReadAvgRF_1024();
  float dBm = V2dBm(RF_1024);
  dataWrite(MHz, dBm);
}

//test power output for every frequency in betaflight 
void Tramp(){
  //uint16_t MHz = 5640;
  
  for(int band = 0; band<VTX_STRING_BAND_COUNT; band++){
    for(int freq = 0; freq<VTX_STRING_CHAN_COUNT; freq++){  
      Tramp::Write(MHz);
      MeasureTx(MHz);
      MHz = vtx58frequencyTable[band][freq]; //get valid MHz from table
      delay(CmdDelay);
    }
  }

}
}
