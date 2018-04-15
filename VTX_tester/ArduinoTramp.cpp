/*Arduino partial implementation of the Tramp Protocol*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <stdint.h>
#include "VTX_common.h"

#ifndef ArduinoTramp
#define ArduinoTramp

static uint8_t trampReqBuffer[16];

static uint8_t trampChecksum(uint8_t *trampBuf)
{
    uint8_t cksum = 0;

    for (int i = 1 ; i < 14 ; i++) {
        cksum += trampBuf[i];
    }
    return cksum;
}

//send Tramp data packet (Freqeuncy only) 
//void TrampWriteCMD(uint8_t cmd, uint16_t param)
void TrampWrite (uint16_t Freq, SoftwareSerial &mySerial){
    memset(trampReqBuffer, 0, 16);

    trampReqBuffer[0] = 15;
    //trampReqBuffer[1] = cmd;
    trampReqBuffer[1] = 'F';
    trampReqBuffer[2] = Freq & 0xff;
    trampReqBuffer[3] = (Freq >> 8) & 0xff;
    trampReqBuffer[14] = trampChecksum(trampReqBuffer);

    mySerial.write(trampReqBuffer, 16);
}

#endif
