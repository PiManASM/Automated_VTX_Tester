/*Arduino partial implementation of Tramp Protocol*/

#include <stdint.h>
#include <SoftwareSerial.h>

#ifndef ArduinoTramp
#define ArduinoTramp

//static uint8_t trampChecksum(uint8_t *trampBuf);

//send Tramp data packet
//void TrampWriteCMD(uint8_t cmd, uint16_t param)
namespace Tramp {
void TrampWrite (uint16_t Freq, SoftwareSerial &mySerial);
}
#endif
