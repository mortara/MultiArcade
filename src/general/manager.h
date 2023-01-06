#include <Arduino.h>
#include "../Input/joystick.h"
#include "../Input/rotary_encoder.h"
#include <TFT_eSPI.h>
#include <SPI.h>
#include "menu.h"
#include "config.h"
#include "Asteroids/asteroids.h"
#include "Pong/pong.h"

class Manager
{
    private:
        Joystick _stick;
        RotaryEncoder *_rotary;
        Menu _menu;
        TFT_eSPI _screen;

        

        

        Asteroids _asteroids;
        Pong _pong;

    public:
        int16_t CurrentGame;

        TFT_eSPI Setup();
        void Loop();
        
};