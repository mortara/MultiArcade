#include <Arduino.h>
#include <TFT_eSPI.h>

class Asteroids
{
    private:
        long _lastLoop;
        TFT_eSPI _tft;

    public:
        void Setup(TFT_eSPI screen);
        void Loop();
};