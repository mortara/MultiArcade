#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include "cannon.hpp"
#include "CannonGround.hpp"
#include "cannonball.hpp"
#include "target.hpp"
#include "../general/GameWorld.hpp"
#include "../Input/rotary_encoder.hpp"
#include "../sound/sound.hpp"
#include "../general/Game.hpp"

class CannonGame : Game
{
    private:
        bool firstloop;
        RotaryEncoder *_rotary;
        RotaryEncoder *_rotary2;

        CannonBall *_cannonball = nullptr;
        Cannon *_cannon;
        Target *_target;
        CannonGround *_ground;
        GameWorld *_world;
        
        long _lastrotarycount;
        long _lastrotarycount2;

        int shots = 3;
        int score = 0;
        int level = 0;
       
        void paddle();
        void scores();
        void HUD();
        void StartLevel(int l);
    public:
        CannonGame(TFT_eSPI* screen, RotaryEncoder *player1, RotaryEncoder *player2);
        void Loop();
};