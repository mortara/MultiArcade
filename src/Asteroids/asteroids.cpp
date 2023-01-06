#include "asteroids.h"
#include "../general/config.h"

void Asteroids::Setup(TFT_eSPI screen)
{
    _tft = screen;
    _tft.fillScreen(BLACK);
}

void Asteroids::Loop()
{
    long time = millis();
    double elapsed = (double)(time - _lastLoop) / 1000.0;

    

    _lastLoop = time;
}