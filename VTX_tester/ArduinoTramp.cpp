/*Arduino partial implementation of the Tramp Protocol*/

#include <Arduino.h>
#include <stdint.h>
#include <SoftwareSerial.h>

#include "VTX_common.h"
#include "ArduinoTramp.h"

namespace Tramp{
  SoftwareSerial mySerial(4, 3); //RX, TX
  
  void setup () {
    mySerial.begin(9600);
  }
  
  static uint8_t trampReqBuffer[16];
  static uint8_t trampChecksum(uint8_t *trampBuf) {
    uint8_t cksum = 0;

    for (int i = 1 ; i < 14 ; i++) {
        cksum += trampBuf[i];
    }
    return cksum;
  }

  //send Tramp data packet (Freqeuncy only) 
  //void TrampWriteCMD(uint8_t cmd, uint16_t param)
  void Write (uint16_t data) {
    memset(trampReqBuffer, 0, 16);

    trampReqBuffer[0] = 15;
    //trampReqBuffer[1] = cmd;
    trampReqBuffer[1] = 'F';
    trampReqBuffer[2] = data & 0xff;
    trampReqBuffer[3] = (data >> 8) & 0xff;
    trampReqBuffer[14] = trampChecksum(trampReqBuffer);

    mySerial.write(trampReqBuffer, 16);
  }
}

