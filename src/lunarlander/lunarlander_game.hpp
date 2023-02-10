#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include "../general/GameWorld.hpp"
#include "../Input/rotary_encoder.hpp"
#include "../sound/sound.hpp"
#include "../general/Game.hpp"
#include "capsule.hpp"
#include "ground.hpp"

class LunarLanderGame : Game
{
    private:
        bool firstloop;
        float _stagetimer = 5;
        int _level = 0;
        RotaryEncoder *_rotary;

        Capsule *_ship;
        Ground *_ground;
        GameWorld *_world;
         
        void StartLevel(int l);
        void HUD();

    public:
        LunarLanderGame(TFT_eSPI* screen, RotaryEncoder *player1);
        void Loop();
};