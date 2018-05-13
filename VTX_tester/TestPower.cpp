/*Test VTx power with external RF Log power detector*/

#include <Arduino.h>
#include <stdint.h>
#include <math.h> /*log10() */
#include <Wire.h>
#include <Adafruit_ADS1015.h>

#include "main_menu_OLED.h"
#include "VTX_common.h"
#include "ArduinoTramp.h"
#include "TestPower.h"

#define ADC_Pin 0
#define CmdDelay 3000 //minimum mS to wait between commands 

namespace Test {
  
  Adafruit_ADS1115 adc(0x48);
  //static float Power_on_channel[2][8];
  static uint16_t MHz = 5000;
  static float dBm = 0;
  //static float SWR = 0;

  void setup () {
    Serial.begin(9600);    
    Serial.print("MHz  ");
    Serial.println(" dBm  ");
    adc.begin();
  }

  uint16_t getMHz() {
    return MHz;
  }

  float getdBm() {
    return dBm;
  }

  float getSWR() {
   // return SWR;
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
    dBm = -34.924 * Voltage + 26.159 +17;
  }

  //get ADC reading and output dBm
  void MeasureTx(uint32_t MHz){
    float Voltage = ReadAvgRF();
    V2dBm(Voltage);
    dataWrite(MHz, dBm);
  }

  //print to serial monitor
  void dataWrite(uint32_t MHz, float dBm) {
    //Serial.print(MHz);
    static uint16_t count = 0;
    Serial.print(count);  
    count++;
    Serial.print(',');
    Serial.println(dBm);   
  }

  float calcSWR(float delta_power) {
    float R = pow(10.0, delta_power /-20.0);
    float SWR = (1 + R)/(1 - R);
    return SWR;
  }

  void sweepChannels(int band_max,int freq_max, bool delta) {
    for(int band = 0; band<band_max /*VTX_STRING_BAND_COUNT*/; band++){
      for(int freq = 0; freq<freq_max /*VTX_STRING_CHAN_COUNT*/; freq++){  
        //Serial.print("Hello, it's me");
        MHz = vtx58frequencyTable[band][freq]; //get valid MHz from table
        //Tramp::Write(MHz);
        delay(2000); //wait for power to settle
        MeasureTx(MHz);
        
        /*
        //if(!delta)
          //Power_on_channel[band][freq] = dBm;
        //else {
          //Serial.println(Power_on_channel[band][freq]);
          //Power_on_channel[band][freq] -= dBm;
          //Serial.println(Power_on_channel[band][freq]);
          //Power_on_channel[band][freq] = calcSWR(Power_on_channel[band][freq]);
        //}
        //UI::menu();
        */
      }
    } 
  }
  
  void sweepSWR() {
    Serial.println("Sweeping channels");
    sweepChannels(2, 8, 0);
    Serial.println("connect DUT");
    delay(20000);
    sweepChannels(2, 8, 1);
  }
  //test power output for every frequency in betaflight 
  void Tramp(){
    sweepChannels(1, 1, 0); 
  }
}
