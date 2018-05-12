/*Test VTx power with external RF Log power detector*/

#include <Arduino.h>
#include <stdint.h>

#ifndef TestPower_H
#define TestPower_H

namespace Test {
  void setup();
  uint16_t getMHz(); 
  float getdBm(); 
  
  //get average ADC reading over 10 iterations
  float ReadAvgRF(void);

  //convert ADC reading to dBm
  void V2dBm(float RF_1024);

  //print to serial monitor
  void dataWrite(uint32_t MHz, float dBm);

  //get ADC reading and output dBm
  void MeasureTx();

  void Tramp();

  class VTx_Data;
}

#endif

