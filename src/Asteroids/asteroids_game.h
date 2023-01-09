#include <Arduino.h>
#include <TFT_eSPI.h>
#include "ship.h"
#include "bullet.h"
#include "asteroid.h"

class Asteroids
{
    private:
        long _lastLoop;
        TFT_eSPI _tft;

        Ship _ship;
        Bullet* _bullets;
        Asteroid* _asteroids;

    public:
        void Setup(TFT_eSPI screen);
        void Loop();
};