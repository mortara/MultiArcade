
#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include "ship.hpp"
#include "bullet.hpp"
#include "asteroid.hpp"
#include "debris.hpp"
#include "../general/gameobject.hpp"
#include "../Input/rotary_encoder.hpp"
#include "../sound/sound.hpp"

class AsteroidsGame
{
    private:
        unsigned long _lastLoop;
        TFT_eSPI _tft;
        bool _firstloop = true;

        RotaryEncoder *_rotary;
        Ship *_ship;
        float _reloadtime = 0.3;
        float _lastshot = 0;

        Buzzer _buzz;

        std::list<GameObject *> _objects;

        GameObject* CollisionCheck(GameObject *go, int objecttype);
        void Explode(GameObject *go);

        int lives = 3;
        int score = 0;
        int level = 0;
        int gamestage = 0;
        float stagetimer = 0;
        void scores();
        void StartLevel(int l);

        void ProcessShip(float elapsed);
        void ProcessObjects(float elapsed);

    public:
        void Setup(TFT_eSPI screen, RotaryEncoder *player1);
        void Loop();
};