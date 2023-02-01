#include "main.h"

void loop() {
  // put your main code here, to run repeatedly:
    //delay(_delay);

    _mgr.Loop();

    _loopCount++;
    if(_loopCount == 500 && _screen != NULL)
    {
        unsigned long end = millis();
        float duration = (float)(end - _loopStart) / (float)500.0;
        //Serial.print(duration);
        _screen->setTextColor(WHITE);
        _screen->drawString("loop: " + String(duration) + "ms", 10, 113 , 1);
        _loopCount = 0;
        _loopStart = end;
    }
}

void setup() {
  // put your setup code here, to run once:

  _mgr = Manager();
  _screen = _mgr.Setup();
  _loopStart = millis();
}