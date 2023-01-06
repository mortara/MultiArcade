#include "main.h"

void loop() {
  // put your main code here, to run repeatedly:
  // delay(10);
    if(_loopCount == 0)
    {
        _loopStart = millis();
    }

    _mgr.Loop();

    
    _loopCount++;
    if(_loopCount == 50)
    {
        unsigned long end = millis();
        float duration = (float)(end - _loopStart) / (float)50.0;
        //Serial.print(duration);
        _screen.drawString("loop: " + String(duration) + "ms", 10, 113 , 2);
        _loopCount = 0;
    }
}

void setup() {
  // put your setup code here, to run once:

  _mgr = Manager();
  _screen = _mgr.Setup();
 
}