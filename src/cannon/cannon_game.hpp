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
      
        CannonBall *_cannonball = nullptr;
        Cannon *_cannon = nullptr;
        Target *_target = nullptr;
        CannonGround *_ground = nullptr;
        GameWorld *_world = nullptr;
        float _stagetimer = 5;
        long _lastrotarycount;
     
        int shots = 3;
        int score = 0;
        int level = 0;
       
        void paddle();
        void scores();
        void HUD();
        void StartLevel(int l);
    public:
        CannonGame(TFT_eSPI* screen, RotaryEncoder *player1);
        void Loop();
};