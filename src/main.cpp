#include "main.h"

void loop() {
  // put your main code here, to run repeatedly:
  // delay(10);

    _mgr.Loop();

    _loopCount++;
    if(_loopCount == 100)
    {
        unsigned long end = millis();
        float duration = (float)(end - _loopStart) / (float)100.0;
        //Serial.print(duration);
        _screen.drawString("loop: " + String(duration) + "ms", 10, 113 , 2);
        _loopCount = 0;
        _loopStart = millis();
    }
}

void setup() {
  // put your setup code here, to run once:

  _mgr = Manager();
  _screen = _mgr.Setup();
  _loopStart = millis();
}