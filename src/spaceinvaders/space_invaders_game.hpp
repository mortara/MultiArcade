#include <Arduino.h>
#include <list>
#include <TFT_eSPI.h>
#include "../general/gameobject.hpp"
#include "../Input/rotary_encoder.hpp"
#include "player.hpp"
#include "alien.hpp"
#include "beam.hpp"

class SpaceInvadersGame
{
    private:
        bool _firstloop;
        long _lastLoop;
        TFT_eSPI _tft;
     
        RotaryEncoder *_rotary;

        Player *_ship;
        float _reloadtime = 0.3;
        float _lastshot = 0;

        std::list<GameObject *> _objects;
    
        GameObject* CollisionCheck(GameObject *go, int objecttype);

        void ProcessShip(float elapsed);
        void ProcessObjects(float elapsed);

        int lives = 0;
        int score = 0;
        int level = 0;
        int gamestage;
        float stagetimer = 0;
        void scores();
        void StartLevel(int l);
    public:
        void Setup(TFT_eSPI screen, RotaryEncoder *player1);
        void Loop();
};