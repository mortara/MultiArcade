#include <Arduino.h>
#include "general/manager.hpp"

unsigned long _loopStart;
int _loopCount;
int _delay = 0;
TFT_eSPI* _screen;
Manager _mgr;