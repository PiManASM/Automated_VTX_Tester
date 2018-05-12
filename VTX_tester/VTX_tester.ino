#include "ArduinoTramp.h"
#include "TestPower.h"
#include "main_menu_OLED.h"

void setup(){
  Tramp::setup();
  Test::setup();
  UI::setup();
}

void loop(){
  Test::Tramp();
  UI::menu();
}
