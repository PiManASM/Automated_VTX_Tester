/*Test VTx power with external RF Log power detector*/

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>

#include "main_menu_OLED.h"
#include "VTX_common.h"
#include "ArduinoTramp.h"
#include "TestPower.h"

#define ADC_Pin 0
#define CmdDelay 3000 //minimum mS to wait between commands 

//get average ADC reading over 10 iterations

namespace Test {
  
  Adafruit_ADS1115 adc(0x48);
  static uint16_t MHz = 5000;
  static float dBm = 0;

  void setup () {
    Serial.begin(9600);    
    Serial.print(" MHz  ");
    Serial.println(" dBm  ");
    adc.begin();
  }

  uint16_t getMHz() {
    //uint16_t temp = rand() % 25;
    return MHz;
  }

  float getdBm() {
    return dBm;
  }
  
  //16 bit ADC
  float ReadAvgRF() {
    float Voltage = 0.0;
    int16_t adc0;  
   
    adc0 = adc.readADC_SingleEnded(0);
    Voltage = (adc0 * 0.1875)/1000;

    return Voltage;
  }

  //convert ADC voltage reading to dBm
  void V2dBm(float Voltage) {
    dBm = -34.924 * Voltage + 26.159;
  //  Serial.print(dBm);
  //  return dBm;
  }

  //get ADC reading and output dBm
  void MeasureTx(uint32_t MHz){
    float Voltage = ReadAvgRF();
    V2dBm(Voltage);
    dataWrite(MHz, dBm);
  }

  //print to serial monitor
  void dataWrite(uint32_t MHz, float dBm) {
    Serial.print(MHz);
    Serial.print(',');
    Serial.println(dBm);             // debug value
  }

  //test power output for every frequency in betaflight 
  void Tramp(){
  //for(int band = 0; band<VTX_STRING_BAND_COUNT; band++){
  //  for(int freq = 0; freq<VTX_STRING_CHAN_COUNT; freq++){  
        Tramp::Write(MHz);
        delay(1000); //wait for power to settle
        MeasureTx(MHz);
       // MHz = vtx58frequencyTable[band][freq]; //get valid MHz from table
        MHz = rand()%1000 + 5000;
  //  }
  //}  
  }
}
