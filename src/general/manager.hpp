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
#include "../lunarlander/lunarlander_game.hpp"
#include "../cannon/cannon_game.hpp"
#include "../tempest/tempest_game.hpp"

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
        LunarLanderGame *_lunarLander;
        CannonGame *_cannon;
        TempestGame *_tempest;
        
        bool _secondControllerAvailable = false;
    public:
        int16_t CurrentGame;

        TFT_eSPI* Setup();
        void Start();
        void Loop();
        
};