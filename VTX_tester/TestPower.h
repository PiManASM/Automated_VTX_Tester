/*Test VTx power with external RF Log power detector*/

#include <Arduino.h>
#include <stdint.h>
#include <SoftwareSerial.h>

//get average ADC reading over 10 iterations
float ReadAvgRF_1024(void);

//convert ADC reading to dBm
float V2dBm(float RF_1024);

//print to serial monitor
void dataWrite(float dBm, HardwareSerial &Serial);

//get ADC reading and output dBm
void MeasureTx(void);

void TrampTest(HardwareSerial &Serial, SoftwareSerial &mySerial);

