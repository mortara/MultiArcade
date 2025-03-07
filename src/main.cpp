#include "main.h"

void loop() {
  if(!_setup)
    return;

  // put your main code here, to run repeatedly:
    //delay(_delay);
    unsigned long now = millis();
    _loopCount++;
    if(_loopCount == 500 && _screen != NULL)
    {
        
        float duration = (float)(now - _loopStart) / (float)500.0;
        //Serial.print(duration);
        _screen->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BG_COLOR, true);
        _screen->drawString("loop: " + String(duration) + "ms", 10, 113 , 1);
        _loopCount = 0;
        _loopStart = now;
    }

    pmCommonLib.Loop();

    

    if(Serial.available())
    {
        char c = Serial.read();
        if(c == 'r')
        {
            ESP.restart();
        }

        if(c == 'i')
        {
          pmCommonLib.WiFiManager.DisplayInfo();
          
        }
    }

    _mgr.Loop();
    
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting up...");

  pmCommonLib.Setup(true,true,true);
  _screen = _mgr.Setup();

  pmCommonLib.Start();
  _mgr.Start();

  Serial.println("Startup complete!");
  _setup = true;
  _loopStart = millis();
}