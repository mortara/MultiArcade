#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include "../general/gameobject.h"
#include "../Input/rotary_encoder.hpp"

class SpaceInvadersGame
{
    private:
        long _lastLoop;
        TFT_eSPI _tft;
        int16_t w;
        int16_t h;

        RotaryEncoder *_rotary;

        float _reloadtime = 0.3;
        float _lastshot = 0;

        std::list<GameObject *> _objects;
        std::list<GameObject *> _removedobjects;
        
        void OutOfBoundsCheck(GameObject *go);
        GameObject* CollisionCheck(GameObject *go);

        int score = 0;
        int level = 0;

        void scores();
        void StartLevel(int l);
    public:
        void Setup(TFT_eSPI screen, RotaryEncoder *player1, int16_t screen_height, int16_t screen_width);
        void Loop();
};