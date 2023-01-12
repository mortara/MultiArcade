#include <Arduino.h>
#include "../Input/joystick.h"
#include "../Input/rotary_encoder.h"
#include <TFT_eSPI.h>
#include <SPI.h>
#include "menu.h"
#include "config.h"
#include "Asteroids/asteroids_game.h"
#include "Pong/pong.h"

class Manager
{
    private:
        Joystick _stick;
        RotaryEncoder *_rotary;
        RotaryEncoder *_rotary2;
        Menu _menu;
        TFT_eSPI _screen;
        int16_t Width;
        int16_t Height;

        AsteroidsGame _asteroids;
        Pong _pong;

    public:
        int16_t CurrentGame;

        TFT_eSPI Setup();
        void Loop();
        
};