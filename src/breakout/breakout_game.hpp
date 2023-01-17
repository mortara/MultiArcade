#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include "../general/gameobject.hpp"
#include "../Input/rotary_encoder.hpp"
#include "block.hpp"

class BreakoutGame
{
    private:
        unsigned long _lastLoop;
        TFT_eSPI _tft;
      
        RotaryEncoder *_rotary;

        int gamestage = 0;  // 0 = Before start,  1 = game running,  2 = game over
        bool firstloop = true;

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

        void ball(float elapsed);
        void paddle();
        void scores();
        void StartLevel(int l);
    public:
        void Setup(TFT_eSPI screen, RotaryEncoder *player1);
        void Loop();
};