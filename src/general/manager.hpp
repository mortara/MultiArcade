#include <Arduino.h>
#include "../Input/joystick.hpp"
#include "../Input/rotary_encoder.hpp"
#include <TFT_eSPI.h>
#include <SPI.h>
#include "menu.hpp"
#include "config.h"
#include "Asteroids/asteroids_game.hpp"
#include "Pong/pong.hpp"
#include "../breakout/breakout_game.hpp"
#include "../spaceinvaders/space_invaders_game.hpp"

class Manager
{
    private:
        Joystick _stick;
        RotaryEncoder *_rotary;
        RotaryEncoder *_rotary2;
        Menu* _menu;
        TFT_eSPI* _screen;
     
        AsteroidsGame *_asteroids;
        Pong *_pong;
        BreakoutGame* _breakout;
        SpaceInvadersGame *_spaceInvaders;

    public:
        int16_t CurrentGame;

        TFT_eSPI* Setup();
        void Loop();
        
};