
#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include "ship.h"
#include "bullet.h"
#include "asteroid.h"
#include "../general/gameobject.h"
#include "../Input/rotary_encoder.h"

class AsteroidsGame
{
    private:
        long _lastLoop;
        TFT_eSPI _tft;
        int16_t w;
        int16_t h;

        RotaryEncoder *_rotary;
        Ship *_ship;
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
        void Setup(TFT_eSPI screen, RotaryEncoder *player1, int16_t screen_width, int16_t screen_height);
        void Loop();
};