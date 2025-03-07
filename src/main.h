#include <Arduino.h>
#include "general/manager.hpp"
#include "pmCommonLib.hpp"

unsigned long _loopStart;
int _loopCount;
bool _setup = false;
int _delay = 0;
TFT_eSPI* _screen;
Manager _mgr;
