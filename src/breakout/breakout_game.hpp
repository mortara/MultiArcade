#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include "../general/gameobject.hpp"
#include "../Input/rotary_encoder.hpp"
#include "block.hpp"
#include "../sound/sound.hpp"
#include "../general/Game.hpp"

class BreakoutGame : Game
{
    private:
        unsigned long _lastLoop;
        bool firstloop;
        RotaryEncoder *_rotary;

        std::list<Block *> _objects;
      
        GameObject *_ball;
        GameObject *_paddle;
        
        void OutOfBoundsCheck(GameObject *go);
        GameObject* CollisionCheck(GameObject *go);
        
        long _lastrotarycount;
        float paddle_v = 2;

        int lives = 3;
        int score = 0;
        int level = 0;
        float ballbasespeed = 70;
        float ballspeedlvlmultiplier = 6;

        void ball(float elapsed);
        void paddle();
        void scores();
        void StartLevel(int l);
    public:
        BreakoutGame(TFT_eSPI* screen, RotaryEncoder *player1);
        void Loop();
};