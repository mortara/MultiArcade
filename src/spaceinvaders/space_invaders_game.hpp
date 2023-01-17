#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include "../general/gameobject.hpp"
#include "../Input/rotary_encoder.hpp"

class SpaceInvadersGame
{
    private:
        long _lastLoop;
        TFT_eSPI _tft;
     
        RotaryEncoder *_rotary;

        float _reloadtime = 0.3;
        float _lastshot = 0;

        std::list<GameObject *> _objects;
    
        void OutOfBoundsCheck(GameObject *go);
        GameObject* CollisionCheck(GameObject *go);

        int score = 0;
        int level = 0;

        void scores();
        void StartLevel(int l);
    public:
        void Setup(TFT_eSPI screen, RotaryEncoder *player1);
        void Loop();
};