/*Arduino partial implementation of Tramp Protocol*/

#include <stdint.h>

#ifndef ArduinoTramp_H
#define ArduinoTramp_H

namespace Tramp {
  void setup();
  static uint8_t trampChecksum (uint8_t *trampBuf);
  //send Tramp data packet
  //void TrampWriteCMD(uint8_t cmd, uint16_t param)
  void Write (uint16_t Freq);
}
#endif
